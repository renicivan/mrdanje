// Fill out your copyright notice in the Description page of Project Settings.

#include "FloorBombTile.h"


// Sets default values
AFloorBombTile::AFloorBombTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TileMesh"));
	TileMesh->SetWorldScale3D(FVector(0.1f, 0.1f, 0.1f));
	TileMesh->SetCollisionResponseToAllChannels(ECR_Block);
	//TileMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	TileMesh->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AFloorBombTile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFloorBombTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

