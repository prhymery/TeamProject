// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
//#include "Kismet/GameplayStatics.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Body = CreateDefaultSubobject<USkeletalMeshComponent >(TEXT("Body"));
	RootComponent = Body;
	Bullet = nullptr;

	Body->SetCollisionProfileName(TEXT("NoCollision"));

	MaxAmmo = 100;
	CurrentAmmo = 30;

	SetReplicates(true);

}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();


}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::Fire()
{
	if (Bullet != nullptr)
	{
		GetWorld()->SpawnActor<AActor>(Bullet, Body->GetSocketTransform(FName(TEXT("Muzzle"))));
	}
	
	
}