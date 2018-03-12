// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"

template <typename ObjectType>
static FORCEINLINE ObjectType* SpawnBP(UWorld* World, UClass* BP, const FVector& Location, const FRotator& Rotation,
	const bool bNoCollisionFail = true, AActor* Owner = NULL, APawn* Instigator = NULL
) {
	if (!World) return NULL;
	if (!BP) return NULL;

	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Owner = Owner;
	SpawnInfo.Instigator = Instigator;
	SpawnInfo.bDeferConstruction = false;

	return World->SpawnActor<ObjectType>(BP, Location, Rotation, SpawnInfo);
}

class MRDANJE_API Utilities
{
public:
	Utilities();
	~Utilities();

	template <typename ObjectType>
	static ObjectType* SpawnBlueprint(FString Path, UWorld* World, FVector Location, FRotator Rotation, AActor* Owner)
	{
		UObject* LoadedBlueprint = StaticLoadObject(UObject::StaticClass(), nullptr, *Path);
		UBlueprint* bp = Cast<UBlueprint>(LoadedBlueprint);
		UClass* Blueprint = (UClass*)bp->GeneratedClass;

		return SpawnBP<ObjectType>(World, Blueprint, Location, Rotation, true, Owner, NULL);
	}
};
