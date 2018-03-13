// Fill out your copyright notice in the Description page of Project Settings.

#include "TileCheckpoint.h"


// Sets default values
ATileCheckpoint::ATileCheckpoint()
{
	PrimaryActorTick.bCanEverTick = false;

	CheckpointMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CheckpointMesh"));
	CheckpointMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	CheckpointMesh->SetupAttachment(GetRootComponent());
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