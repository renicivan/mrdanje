// Fill out your copyright notice in the Description page of Project Settings.

#include "FloorBomb.h"


// Sets default values
AFloorBomb::AFloorBomb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileMesh->SetWorldScale3D(FVector(0.05f, 0.05f, 0.05f));
	ProjectileMesh->SetSimulatePhysics(true);
	ProjectileMesh->SetCollisionResponseToAllChannels(ECR_Block);
	ProjectileMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	ProjectileMesh->SetupAttachment(GetRootComponent());

	ProjectileMesh->bGenerateOverlapEvents = true;
	FScriptDelegate HitDelegate;
	HitDelegate.BindUFunction(this, "OnOverlapBegin");
	ProjectileMesh->OnComponentBeginOverlap.Add(HitDelegate);
}

// Called when the game starts or when spawned
void AFloorBomb::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFloorBomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFloorBomb::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Floor bomb projectile hit something!"));

	FAttachmentTransformRules* AttachmentRules = new FAttachmentTransformRules(EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, true);
	GetRootComponent()->AttachToComponent(OtherActor->GetRootComponent(), *AttachmentRules);

	ProjectileMesh->SetSimulatePhysics(false);
	Detonate();
}

void AFloorBomb::Detonate()
{
	FVector Location = ProjectileMesh->GetOwner()->GetActorLocation();
	FRotator Rotation = FRotator(0);
	UWorld* World = ProjectileMesh->GetWorld();

	AFloorBombTile* Tile1 = Utilities::SpawnBlueprint<AFloorBombTile>("/Game/Mrdanje/Weapons/FloorBomb/BP_FloorBombTile", World, Location, Rotation, NULL);
	
	FAttachmentTransformRules* AttachmentRules = new FAttachmentTransformRules(EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, true);
	Tile1->AttachToComponent(GetRootComponent(), *AttachmentRules);

	float DistanceBetweenTiles = Tile1->GetComponentsBoundingBox().GetSize().Y;
	int Angle = 30;
	int NumTiles = 6;

	for (int i = 0; i < NumTiles; i++)
	{
		float x = Tile1->GetActorLocation().X + DistanceBetweenTiles * FMath::Cos(FMath::DegreesToRadians(Angle));
		float y = Tile1->GetActorLocation().Y + DistanceBetweenTiles * FMath::Sin(FMath::DegreesToRadians(Angle));
		float z = Tile1->GetActorLocation().Z;
		FVector Location = FVector(x, y, z);

		AFloorBombTile* Tile = Utilities::SpawnBlueprint<AFloorBombTile>("/Game/Mrdanje/Weapons/FloorBomb/BP_FloorBombTile", World, Location, Rotation, NULL);
		Tile->AttachToComponent(GetRootComponent(), *AttachmentRules);

		Angle += 360 / NumTiles;
	}

	ProjectileMesh->DestroyComponent();
}