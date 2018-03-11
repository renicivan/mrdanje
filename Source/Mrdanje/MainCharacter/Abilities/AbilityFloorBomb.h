// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "GameFramework/Character.h"
//#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Weapons/FloorBomb.h"
#include "ConstructorHelpers.h"
#include "Engine/World.h"
#include "MainCharacter/Abilities/Ability.h"
#include "AbilityFloorBomb.generated.h"

template <typename ObjectType>
static FORCEINLINE ObjectType* SpawnBlueprint(UWorld* World, UClass* BP, const FVector& Location, const FRotator& Rotation,
	const bool bNoCollisionFail = true, AActor* Owner = NULL, APawn* Instigator = NULL
) {
	if (!World) return NULL;
	if (!BP) return NULL;
	//~~

	FActorSpawnParameters SpawnInfo;
	//SpawnInfo.bNoCollisionFail = bNoCollisionFail;
	SpawnInfo.Owner = Owner;
	SpawnInfo.Instigator = Instigator;
	SpawnInfo.bDeferConstruction = false;

	return World->SpawnActor<ObjectType>(BP, Location, Rotation, SpawnInfo);
}

/**
 * 
 */
UCLASS()
class MRDANJE_API UAbilityFloorBomb : public UAbility
{
	GENERATED_BODY()
	
public:
	UAbilityFloorBomb();
	void Init(class UInputComponent* InputComponentUsed, ACharacter* CharacterWithAbility, class UCharacterAbilities* AbilityManager);
	void Tick(float DeltaTime) override;
	
protected:
	void Trigger();
	void FireBomb();
	void ExplodeBomb();

	ACharacter* PlayerCharacter;
	AFloorBomb* ActiveProjectile;

	float ForceApplyTime;
	FVector ForceVector;
};
