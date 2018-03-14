// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Utilities.h"
#include "Camera/CameraComponent.h"
#include "Weapons/FloorBomb.h"
#include "ConstructorHelpers.h"
#include "Engine/World.h"
#include "MainCharacter/Abilities/Ability.h"
#include "AbilityFloorBomb.generated.h"

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
