// Fill out your copyright notice in the Description page of Project Settings.

#include "TriggerArea.h"


// Sets default values
ATriggerArea::ATriggerArea()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Add the collision box which will be used to check if the player has entered the trigger area.
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = BoxCollision;

	// Bind the overlap event to our overlap function.
	BoxCollision->bGenerateOverlapEvents = true;
	BoxCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	FScriptDelegate OverlapBeginDelegate;
	OverlapBeginDelegate.BindUFunction(this, "OnTestOverlapBegin");
	BoxCollision->OnComponentBeginOverlap.Add(OverlapBeginDelegate);
	FScriptDelegate OverlapEndDelegate;
	OverlapEndDelegate.BindUFunction(this, "OnTestOverlapEnd");
	BoxCollision->OnComponentEndOverlap.Add(OverlapEndDelegate);
}

// Called when the game starts or when spawned
void ATriggerArea::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATriggerArea::OnTestOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void ATriggerArea::OnTestOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}