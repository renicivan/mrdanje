// Fill out your copyright notice in the Description page of Project Settings.

#include "MoveableActor.h"


// Sets default values
AMoveableActor::AMoveableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bAllowTickBeforeBeginPlay = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetCollisionResponseToAllChannels(ECR_Overlap);
	Mesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	Mesh->SetupAttachment(GetRootComponent());

	InitTilePropertySets();
}

void AMoveableActor::InitTilePropertySets()
{
	// White tile properties
	FTileProperties White;
	White.WaitCycles = 1;
	White.CycleDuration = 2.0f;
	White.MaterialPath = "Material'/Game/Mrdanje/MaterialLibrary/LevelUnits/M_WhiteTile.M_WhiteTile'";
	TileProperties.Add(ETileTypesEnum::VE_White, White);

	// Red tile properties
	FTileProperties Red;
	Red.WaitCycles = 1;
	Red.CycleDuration = 2.0f;
	Red.MaterialPath = "Material'/Game/Mrdanje/MaterialLibrary/LevelUnits/M_RedTile.M_RedTile'";
	TileProperties.Add(ETileTypesEnum::VE_Red, Red);

	// Blue tile properties
	FTileProperties Blue;
	Blue.WaitCycles = 1;
	Blue.CycleDuration = 2.0f;
	Blue.MaterialPath = "Material'/Game/Mrdanje/MaterialLibrary/LevelUnits/M_BlueTile.M_BlueTile'";
	TileProperties.Add(ETileTypesEnum::VE_Blue, Blue);

	// Yellow tile properties
	FTileProperties Yellow;
	Yellow.WaitCycles = 1;
	Yellow.CycleDuration = 2.0f;
	Yellow.MaterialPath = "Material'/Game/Mrdanje/MaterialLibrary/LevelUnits/M_YellowTile.M_YellowTile'";
	TileProperties.Add(ETileTypesEnum::VE_Yellow, Yellow);
}

// Called when the game starts or when spawned
void AMoveableActor::BeginPlay()
{
	Super::BeginPlay();
	
	if (Checkpoints.Num() < 1)
	{
		bShouldMove = false;
		return;
	}

	StartCheckpoint = FMath::Clamp(StartCheckpoint, 0, Checkpoints.Num() - 1);
	
	ATileCheckpoint* InitialCheckpoint = Checkpoints[StartCheckpoint];
	SetActorLocation(InitialCheckpoint->GetActorLocation());

	LastCheckpoint = StartCheckpoint;
	ActiveCommands = Checkpoints[LastCheckpoint]->GetCommands();
	CurrentCommandIndex = 0;
	CurrentCommandTimeLeft = ActiveCommands[CurrentCommandIndex].Duration;

	SetTileProperties(TileType, true);
}

void AMoveableActor::SetTileProperties(ETileTypesEnum TileType, bool Force = false)
{
	if (CurrentTileType == TileType && !Force)
	{
		return;
	}

	FTileProperties* NewProperties = TileProperties.Find(TileType);
	UMaterial* NewMaterial = Cast<UMaterial>(StaticLoadObject(UMaterial::StaticClass(), NULL, *NewProperties->MaterialPath));
	Mesh->SetMaterial(0, NewMaterial);

	for (int i = 0; i < Checkpoints.Num(); i++)
	{
		Checkpoints[i]->SetTileType(TileType);
		Checkpoints[i]->ConnectToNextCheckpoint(Checkpoints[(i + 1) % Checkpoints.Num()]);
	}
	
	CurrentTileType = TileType;
}

void AMoveableActor::PrintActiveCommands()
{
	UE_LOG(LogTemp, Warning, TEXT("====== CURRENT COMMANDS ======"));
	UE_LOG(LogTemp, Warning, TEXT("------------------------------"));

	for (int i = 0; i < ActiveCommands.Num(); i++)
	{
		if (ActiveCommands[i].Command == ECheckpointCommandsEnum::VE_Go)
		{
			UE_LOG(LogTemp, Warning, TEXT("Move for %.3f seconds!"), ActiveCommands[i].Duration);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("WAIT for %.3f seconds!"), ActiveCommands[i].Duration);
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("------------------------------"));
}

void AMoveableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentCommandTimeLeft -= DeltaTime;

	if (ActiveCommands[CurrentCommandIndex].Command == ECheckpointCommandsEnum::VE_Go)
	{
		ATileCheckpoint* ALastCheckpoint = Checkpoints[LastCheckpoint];
		ATileCheckpoint* ANextCheckpoint = Checkpoints[(LastCheckpoint + 1) % Checkpoints.Num()];

		FVector CurrentLocation = GetActorLocation();
		FVector LastCheckpointLocation = ALastCheckpoint->GetActorLocation();
		FVector NextCheckpointLocation = ANextCheckpoint->GetActorLocation();

		float t = FVector::Dist(CurrentLocation, LastCheckpointLocation) / FVector::Dist(NextCheckpointLocation, LastCheckpointLocation);
		t += DeltaTime / ActiveCommands[CurrentCommandIndex].Duration;
		t = FMath::Clamp(t, 0.0f, 1.0f);

		float NewX = LastCheckpointLocation.X + t * (NextCheckpointLocation.X - LastCheckpointLocation.X);
		float NewY = LastCheckpointLocation.Y + t * (NextCheckpointLocation.Y - LastCheckpointLocation.Y);
		float NewZ = LastCheckpointLocation.Z + t * (NextCheckpointLocation.Z - LastCheckpointLocation.Z);

		SetActorLocation(FVector(NewX, NewY, NewZ));

		if (t >= 1.0f)
		{
			LastCheckpoint = (LastCheckpoint + 1) % Checkpoints.Num();
			ActiveCommands = Checkpoints[LastCheckpoint]->GetCommands();
			CurrentCommandIndex = 0;
			CurrentCommandTimeLeft = ActiveCommands[CurrentCommandIndex].Duration;


			if (ActiveCommands[CurrentCommandIndex].Command == ECheckpointCommandsEnum::VE_Go)
			{
				CheckForReverse();
			}

			return;
		}
	}

	if (CurrentCommandTimeLeft <= 0.0f)
	{
		CurrentCommandIndex += 1;
		CurrentCommandTimeLeft = ActiveCommands[CurrentCommandIndex].Duration;

		if (ActiveCommands[CurrentCommandIndex].Command == ECheckpointCommandsEnum::VE_Go)
		{
			CheckForReverse();
		}

		if (ActiveCommands[CurrentCommandIndex].Command == ECheckpointCommandsEnum::VE_Stay)
		{
			UE_LOG(LogTemp, Warning, TEXT("Waiting %.3f seconds!"), CurrentCommandTimeLeft);
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Moving to the next checkpoint for %.3f seconds!"), CurrentCommandTimeLeft);
		}

		// AKO IMA ZVUKA, SVIRAJ OVDJE!!
	}
}

void AMoveableActor::CheckForReverse()
{
	if (bNeedToReverse)
	{
		ExecuteReverse();
	}
}

void AMoveableActor::Reverse()
{
	bNeedToReverse = true;
}

void AMoveableActor::ExecuteReverse()
{
	UE_LOG(LogTemp, Warning, TEXT("reeeeeeeeeeeeverse meeeeeeeeeee"));

	Algo::Reverse(Checkpoints);
	LastCheckpoint = Checkpoints.Num() - ((LastCheckpoint + 1) % Checkpoints.Num()) - 1;

	if (bWaitingOnCheckpoint)
	{
		LastCheckpoint = (LastCheckpoint + 1) % Checkpoints.Num();
	}

	LastCheckpoint = (LastCheckpoint + 1) % Checkpoints.Num();

	bNeedToReverse = false;
}

ETileTypesEnum AMoveableActor::GetTileType()
{
	return TileType;
}