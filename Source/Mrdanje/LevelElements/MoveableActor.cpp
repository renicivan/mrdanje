// Fill out your copyright notice in the Description page of Project Settings.

#include "MoveableActor.h"


// Sets default values
AMoveableActor::AMoveableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetCollisionResponseToAllChannels(ECR_Ignore);
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
	
	AActor* InitialCheckpoint = Checkpoints[StartCheckpoint];
	SetActorLocation(InitialCheckpoint->GetActorLocation());

	LastCheckpoint = StartCheckpoint;

	SetTileProperties(TileType, true);
}

void AMoveableActor::SetTileProperties(ETileTypesEnum TileType, bool Force = false)
{
	if (CurrentTileType == TileType && !Force)
	{
		return;
	}

	FTileProperties* NewProperties = TileProperties.Find(TileType);

	// Apply new tile properties
	//ConstructorHelpers::FObjectFinder<UMaterial> ReferenceVariable(*NewProperties->MaterialPath);
	//TCHAR* Path = ;
	//ConstructorHelpers::FObjectFinder<UMaterial> ReferenceVariable(_T("Material'/Game/Mrdanje/MaterialLibrary/LevelUnits/M_WhiteTile.M_WhiteTile'"));
	UMaterial* NewMaterial = Cast<UMaterial>(StaticLoadObject(UMaterial::StaticClass(), NULL, *NewProperties->MaterialPath));


	//USkeletalMesh* skeletalMesh = Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), NULL, TEXT("SkeletalMesh'/Game/Dir/abc.abc'")));
	Mesh->SetMaterial(0, NewMaterial);
	
	CurrentTileType = TileType;
}

// Called every frame
void AMoveableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bShouldMove)
	{
		return;
	}

	if (bWaitingOnCheckpoint)
	{
		WaitTimeLeft -= DeltaTime;

		if (WaitTimeLeft <= 0.0f)
		{
			WaitTimeLeft = 0.0f;
			bWaitingOnCheckpoint = false;
		}

		if (bNeedToReverse)
		{
			ExecuteReverse();
		}
	}
	else
	{
		AActor* ALastCheckpoint = Checkpoints[LastCheckpoint];
		AActor* ANextCheckpoint = Checkpoints[(LastCheckpoint + 1) % Checkpoints.Num()];

		FVector CurrentLocation = GetActorLocation();
		FVector LastCheckpointLocation = ALastCheckpoint->GetActorLocation();
		FVector NextCheckpointLocation = ANextCheckpoint->GetActorLocation();

		float t = FVector::Dist(CurrentLocation, LastCheckpointLocation) / FVector::Dist(NextCheckpointLocation, LastCheckpointLocation);
		t += DeltaTime / TileProperties.Find(CurrentTileType)->CycleDuration;
		t = FMath::Clamp(t, 0.0f, 1.0f);

		float NewX = LastCheckpointLocation.X + t * (NextCheckpointLocation.X - LastCheckpointLocation.X);
		float NewY = LastCheckpointLocation.Y + t * (NextCheckpointLocation.Y - LastCheckpointLocation.Y);
		float NewZ = LastCheckpointLocation.Z + t * (NextCheckpointLocation.Z - LastCheckpointLocation.Z);

		SetActorLocation(FVector(NewX, NewY, NewZ));

		if (t == 1.0f)
		{
			LastCheckpoint = (LastCheckpoint + 1) % Checkpoints.Num();
			bWaitingOnCheckpoint = true;
			FTileProperties* CurrentProperties = TileProperties.Find(CurrentTileType);
			WaitTimeLeft = CurrentProperties->CycleDuration * CurrentProperties->WaitCycles;
		}
	}
}

void AMoveableActor::Reverse()
{
	/*UE_LOG(LogTemp, Warning, TEXT("reeeeeeeeeeeeverse meeeeeeeeeee"));

	Algo::Reverse(Checkpoints);
	LastCheckpoint = Checkpoints.Num() - ((LastCheckpoint + 1) % Checkpoints.Num()) - 1;

	if (bWaitingOnCheckpoint)
	{
		LastCheckpoint = (LastCheckpoint + 1) % Checkpoints.Num();
	}*/

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

	bNeedToReverse = false;
}

ETileTypesEnum AMoveableActor::GetTileType()
{
	return TileType;
}