// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelFinish.h"


// Sets default values
ALevelFinish::ALevelFinish()
{
	PrimaryActorTick.bCanEverTick = false;

	// Add the collision box which will be used to check if the player has entered the finish area.
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetBoxExtent(FVector(20.0f, 20.0f, 20.0f));
	BoxCollision->SetupAttachment(GetRootComponent());

	// Bind the overlap event to our overlap function.
	BoxCollision->bGenerateOverlapEvents = true;
	BoxCollision->SetCollisionResponseToAllChannels(ECR_Overlap);
	FScriptDelegate HitDelegate;
	HitDelegate.BindUFunction(this, "OnTestOverlapBegin");
	BoxCollision->OnComponentBeginOverlap.Add(HitDelegate);

}

// Called when the game starts or when spawned
void ALevelFinish::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALevelFinish::OnTestOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMrdanjeGameMode* GameMode = Cast<AMrdanjeGameMode>(GetWorld()->GetAuthGameMode());
	GameMode->FinishLevel();
}
