// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "AICEnemy.generated.h"

/**
 *
 */
UCLASS()
class PROJECTSPLASH_API AAICEnemy : public AAIController
{
	GENERATED_BODY()

public:
	AAICEnemy();
	virtual void OnPossess(APawn* InPawn) override;

	void RunAI();
	void StopAI();

	UFUNCTION()
	void TargetPerceptionUpdate(AActor* actor, FAIStimulus const Stimulus);
	UFUNCTION()
		void SetPerceptionSystem();

	UPROPERTY(EditDefaultsOnly, Category = "AIC", BlueprintReadWrite)
		class UBehaviorTree* BehaviorTree;

	UPROPERTY(EditDefaultsOnly, Category = "AIC", BlueprintReadWrite)
		class UBlackboardData* BlackboardData;

	UPROPERTY(VisibleAnywhere, Category = "AIC", BlueprintReadOnly)
		class UAIPerceptionComponent* AIPerception;

	class UBlackboardComponent* Blackboard;
	class UAISenseConfig_Sight* SightConfig;
	class UAISenseConfig_Hearing* HearingConfig;

protected:
	virtual void BeginPlay() override;
};
