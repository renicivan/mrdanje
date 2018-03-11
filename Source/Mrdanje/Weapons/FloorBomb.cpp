// Fill out your copyright notice in the Description page of Project Settings.

#include "FloorBomb.h"


// Sets default values
AFloorBomb::AFloorBomb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileMesh->SetWorldScale3D(FVector(0.05f, 0.05f, 0.05f));
	ProjectileMesh->SetSimulatePhysics(true);
	ProjectileMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);

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
	ProjectileMesh->SetSimulatePhysics(false);
}