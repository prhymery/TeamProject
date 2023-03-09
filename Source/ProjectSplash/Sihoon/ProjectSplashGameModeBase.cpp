// Copyright Epic Games, Inc. All Rights Reserved.


#include "ProjectSplashGameModeBase.h"
#include "MyPlayerController.h"

#include "Kismet/GameplayStatics.h"

AProjectSplashGameModeBase::AProjectSplashGameModeBase()
{

	PlayerControllerClass = AMyPlayerController::StaticClass();

}

// 이긴 팀의 색을 TileColor Enum으로 반환하는 함수
TileColor AProjectSplashGameModeBase::CheckWinColor()
{
    TileColor Result = TileColor::TE_Default;
    int32 Temp = 0;

    // Get all the actors of class MyActorClass in the current level
    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATile::StaticClass(), FoundActors);
    // Iterate through the array of found actors and do something with them
    for (AActor* Actor : FoundActors)
    {
        // Do something with the actor, such as cast to a specific subclass and call a function
        ATile* Tile = Cast<ATile>(Actor);
        if (Tile)
        {
            switch (Tile->GetTileColor())
            {
            case TileColor::TE_Blue:
                Temp++;
                break;
            case TileColor::TE_Red:
                Temp--;
                break;
            default:
                break;
            }
        }
    }

    // 어느 팀이 이겼는지 확인
    if (Temp > 0)
    {
        Result = TileColor::TE_Blue;
    }
    else if (Temp < 0)
    {
        Result = TileColor::TE_Red;
    }
    else
    {
        Result = TileColor::TE_Default;
    }

    return Result;
}
