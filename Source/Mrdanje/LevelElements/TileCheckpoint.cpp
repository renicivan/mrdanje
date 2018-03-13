// Fill out your copyright notice in the Description page of Project Settings.

#include "TileCheckpoint.h"
#include "MoveableActor.h"


// Sets default values
ATileCheckpoint::ATileCheckpoint()
{
	PrimaryActorTick.bCanEverTick = false;

	CheckpointMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CheckpointMesh"));
	CheckpointMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	//CheckpointMesh->SetupAttachment(GetRootComponent());

	RootComponent = CheckpointMesh;

	//LinkMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LinkMesh"));
	//LinkMesh->SetupAttachment(GetRootComponent());
	//LinkMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
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
	
	float Distance = FVector::Dist(GetActorLocation(), NextCheckpoint->GetActorLocation());
	UE_LOG(LogTemp, Warning, TEXT("X size: %.3f!"), Distance);
	//LinkMesh->SetRelativeScale3D(FVector(Distance, 1.0f, 1.0f));
	//LinkMesh->SetRelativeLocation(FVector(0, 0, 0));

	
}