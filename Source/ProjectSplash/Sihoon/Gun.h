// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"

#include "Gun.generated.h"

UCLASS()
class PROJECTSPLASH_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// RPC. 서버에서 실행. 신뢰성 체크
	UFUNCTION(Server, Reliable, BlueprintCallable, meta = (KeyWords = "Sihoon"))
	void Fire();

	UPROPERTY(VisibleAnywhere, Category = "Components", BlueprintReadOnly)
	class USkeletalMeshComponent* Body;

	UPROPERTY(EditAnywhere, Category = "Actors", BlueprintReadOnly)
	//TSubclassOf<AActor> Bullet;
	//AActor* Bullet;
	UClass* Bullet;

	UPROPERTY(EditAnywhere, Category = "Properties", BlueprintReadOnly)
	int32 MaxAmmo;

	UPROPERTY(EditAnywhere, Category = "Properties", BlueprintReadOnly)
	int32 CurrentAmmo;

};
