// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectSplashGameModeBase.h"
#include "MyGameInstance.h"

void AMyPlayerController::CloseChat()
{
	MyGI = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	// 캐스팅 성공 여부 확인
	if (IsValid(MyGI))
	{
		MyGI->CloseSocket();
	}
}

void AMyPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (EndPlayReason == EEndPlayReason::Destroyed)
	{
		CloseChat();
	}
}
