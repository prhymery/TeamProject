// Fill out your copyright notice in the Description page of Project Settings.


#include "AICEnemy.h"
#include "UObject/ConstructorHelpers.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionSystem.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AIPerceptionComponent.h"


AAICEnemy::AAICEnemy()
{
	SetPerceptionSystem();
}

void AAICEnemy::SetPerceptionSystem()
{
	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception"));
	if (AIPerception == nullptr)
	{
		return;
	}
	SetPerceptionComponent(*AIPerception);

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));

	if (SightConfig)
	{
		SightConfig->SightRadius = 2500.0f;
		SightConfig->LoseSightRadius = SightConfig->SightRadius + 100.0f;
		SightConfig->PeripheralVisionAngleDegrees = 120.0f;
		SightConfig->DetectionByAffiliation.bDetectEnemies =
			SightConfig->DetectionByAffiliation.bDetectFriendlies =
			SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

		GetPerceptionComponent()->ConfigureSense(*SightConfig);
	}

	HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("Hearing Config"));

	if (HearingConfig)
	{
		HearingConfig->HearingRange = 3000.0f;
		HearingConfig->DetectionByAffiliation.bDetectEnemies =
			HearingConfig->DetectionByAffiliation.bDetectFriendlies =
			HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;

		GetPerceptionComponent()->ConfigureSense(*HearingConfig);
	}
}

void AAICEnemy::BeginPlay()
{
	Super::BeginPlay();

	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AAICEnemy::TargetPerceptionUpdate);
}

void AAICEnemy::OnPossess(APawn* InPawn)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("OnPossess"));
	Super::OnPossess(InPawn);
	RunAI();
}

void AAICEnemy::RunAI()
{
	if (UseBlackboard(BlackboardData, (UBlackboardComponent*&)Blackboard))
	{
		RunBehaviorTree(BehaviorTree);
	}
}

void AAICEnemy::StopAI()
{
	UBehaviorTreeComponent* BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (BehaviorTreeComponent == nullptr)
	{
		return;
	}

	BehaviorTreeComponent->StopTree(EBTStopMode::Safe);
}

void AAICEnemy::TargetPerceptionUpdate(AActor* actor, FAIStimulus const Stimulus)
{
	if (Stimulus.WasSuccessfullySensed())
	{
		UAISenseConfig* SenseConfig = GetPerceptionComponent()->GetSenseConfig(Stimulus.Type);
		// 아래의 두 방법 모두 동일한 방법
		//if (SenseConfig->GetClass() == UAISenseConfig_Sight::StaticClass())
		//if (SenseConfig->GetClass() == SightConfig->GetClass())
		if (Cast<UAISenseConfig_Sight>(SenseConfig))
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("TargetFoundWithSight"));
			// 아래의 방법도 동일한 방법
			//Blackboard->SetValueAsObject(TEXT("TargetActor"), actor);
			GetBlackboardComponent()->SetValueAsObject(TEXT("TargetActor"), actor);
		}

		if (Cast<UAISenseConfig_Hearing>(SenseConfig))
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("TargetFoundWithHearing"));
			GetBlackboardComponent()->SetValueAsVector(TEXT("TargetLocation"), Stimulus.StimulusLocation);
		}
	}
}