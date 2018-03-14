// Fill out your copyright notice in the Description page of Project Settings.

#include "TileCheckpoint.h"
#include "MoveableActor.h"


// Sets default values
ATileCheckpoint::ATileCheckpoint()
{
	PrimaryActorTick.bCanEverTick = false;

	CheckpointMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CheckpointMesh"));
	CheckpointMesh->SetCollisionResponseToAllChannels(ECR_Ignore);

	RootComponent = CheckpointMesh;
}

// Called when the game starts or when spawned
void ATileCheckpoint::BeginPlay()
{
	Super::BeginPlay();
	
}

TArray<FCheckpointCommandStruct> ATileCheckpoint::GetCommands()
{
	return Commands;
}

void ATileCheckpoint::SetTileType(ETileTypesEnum TileType)
{
	FString MaterialPath;

	if (TileType == ETileTypesEnum::VE_Red)
	{
		MaterialPath = "Material'/Game/Mrdanje/MaterialLibrary/LevelUnits/M_RedTile.M_RedTile'";
	}
	else if (TileType == ETileTypesEnum::VE_Blue)
	{
		MaterialPath = "Material'/Game/Mrdanje/MaterialLibrary/LevelUnits/M_BlueTile.M_BlueTile'";
	}
	else
	{
		MaterialPath = "Material'/Game/Mrdanje/MaterialLibrary/LevelUnits/M_WhiteTile.M_WhiteTile'";
	}

	UMaterial* NewMaterial = Cast<UMaterial>(StaticLoadObject(UMaterial::StaticClass(), NULL, *MaterialPath));
	CheckpointMesh->SetMaterial(0, NewMaterial);
}

void ATileCheckpoint::ConnectToNextCheckpoint(ATileCheckpoint* NextCheckpoint)
{	
}