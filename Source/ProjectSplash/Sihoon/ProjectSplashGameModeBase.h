// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "Tile.h"

#include "ProjectSplashGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSPLASH_API AProjectSplashGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:

public:
	AProjectSplashGameModeBase();

	UFUNCTION(BlueprintCallable, Category = "Functions", meta = (KeyWords = "Sihoon"))
	TileColor CheckWinColor();
};
