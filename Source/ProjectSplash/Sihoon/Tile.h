// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"

#include "Tile.generated.h"

// 타일 색에 관련된 ENUM클래스
UENUM(BlueprintType)
enum class TileColor : uint8
{
	TE_Default UMETA(DisplayName = "Default"),
	TE_Blue UMETA(DisplayName = "Blue"),
	TE_Red UMETA(DisplayName = "Red"),
};


UCLASS()
class PROJECTSPLASH_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

	/** 프로퍼티 리플리케이션 */
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// RepNotfy로 설정
	UPROPERTY(ReplicatedUsing = OnRep_Color)
	TileColor Color;

	UFUNCTION()
	void OnRep_Color();

	// OnActorBeginOverlap에 델리게이트할 함수
	UFUNCTION()
	void ProcessBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 머티리얼 저장용 배열
	UPROPERTY(EditAnywhere, Category = "Materials", BlueprintReadOnly)
	TArray<class UMaterialInstance*> TileMaterials;

	// 스태틱메시 변수
	UPROPERTY(VisibleAnywhere, Category = "Components", BlueprintReadOnly)
	class UStaticMeshComponent* Tile;

	// 함수들
	UFUNCTION(BlueprintCallable, Category = "Functions", meta = (KeyWords = "Sihoon"))
	TileColor GetTileColor();

	UFUNCTION(BlueprintCallable, Category = "Functions", meta = (KeyWords = "Sihoon"))
	void SetTileColor(TileColor BulletColor);

	UFUNCTION(BlueprintCallable, Category = "Functions", meta = (KeyWords = "Sihoon"))
	void SetTileMaterial();

};
