// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstance.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 초기화
	Color = TileColor::TE_Default;
	TileMaterials.Init(nullptr, 3);
	Tile = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tile"));
	RootComponent = Tile;

	// Tile의 콜리전프리셋 기본값 설정
	Tile->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();

	// 처음엔 Default 머티리얼로 설정
	SetTileMaterial();
	
	// 플레이가 시작되면 델리게이트 함수 바인딩
	OnActorBeginOverlap.AddDynamic(this, &ATile::ProcessBeginOverlap);

}

void ATile::ProcessBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	// 태그값이 Blue, Red 중 어느 값인지 확인 후 색 변경
	if (OtherActor->ActorHasTag(FName(TEXT("Blue"))))
	{
		Color = TileColor::TE_Blue;
		if (Tile->GetStaticMesh() != nullptr)
		{
			SetTileMaterial();
		}
	}
	else if (OtherActor->ActorHasTag(FName(TEXT("Red"))))
	{
		Color = TileColor::TE_Red;
		if (Tile->GetStaticMesh() != nullptr)
		{
			SetTileMaterial();
		}
	}

}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TileColor ATile::GetTileColor()
{
	return Color;
}

void ATile::SetTileColor(TileColor InputColor)
{
	Color = InputColor;
}

void ATile::SetTileMaterial()
{
	// Color가 Enum이어서 (int32)로 캐스팅 후 머티리얼 배열의 인덱스 값으로 사용
	Tile->SetMaterial(0, TileMaterials[(int32)Color]);
}