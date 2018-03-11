// Fill out your copyright notice in the Description page of Project Settings.

#include "Sunlight.h"


// Sets default values
ASunlight::ASunlight()
{
	PrimaryActorTick.bCanEverTick = false;

	// Add the collision box which will be used to check if the player has entered the finish area.
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetBoxExtent(FVector(20.0f, 20.0f, 20.0f));
	BoxCollision->SetupAttachment(GetRootComponent());

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
void ASunlight::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASunlight::OnTestOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMrdanjeCharacter* MainCharacter = Cast<AMrdanjeCharacter>(OtherActor);
	if (MainCharacter)
	{
		MainCharacter->SetStandingInSunlight(true);
	}
}

void ASunlight::OnTestOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMrdanjeCharacter* MainCharacter = Cast<AMrdanjeCharacter>(OtherActor);
	if (MainCharacter)
	{
		MainCharacter->SetStandingInSunlight(false);
	}
}