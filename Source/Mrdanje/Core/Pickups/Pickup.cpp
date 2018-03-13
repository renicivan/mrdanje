// Fill out your copyright notice in the Description page of Project Settings.

#include "Pickup.h"


// Sets default values
APickup::APickup()
{
	PrimaryActorTick.bCanEverTick = true;

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	PickupMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	PickupMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	PickupMesh->SetupAttachment(GetRootComponent());

	PickupMesh->bGenerateOverlapEvents = true;
	FScriptDelegate OverlapBeginDelegate;
	OverlapBeginDelegate.BindUFunction(this, "OnOverlapBegin");
	PickupMesh->OnComponentBeginOverlap.Add(OverlapBeginDelegate);
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	
	RotationT = 0.0f;
	InitialPosition = GetActorLocation();
	PickupMesh->SetRelativeRotation(FRotator(MeshPitch, 0, 0));
}

void APickup::OnPickedUp()
{
}

void APickup::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OnPickedUp();
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	RotationT += DeltaTime;
	float DeltaRotation = (DeltaTime / RotationPeriod) * 360;
	PickupMesh->AddWorldRotation(FRotator(0, DeltaRotation, 0));
	
	float CurrentHeightOffset = 0.5 * RotationHeightDifference* FMath::Sin(6.28f * RotationT / RotationPeriod) + RotationHeightDifference;
	FVector CurrentPosition = FVector(InitialPosition.X, InitialPosition.Y, InitialPosition.Z + CurrentHeightOffset);
	PickupMesh->SetWorldLocation(CurrentPosition);
}