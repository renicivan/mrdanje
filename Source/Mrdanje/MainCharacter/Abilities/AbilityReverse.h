// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EngineUtils.h"
#include "MainCharacter/Abilities/Ability.h"
#include "LevelElements/MoveableActor.h"
#include "AbilityReverse.generated.h"

/**
 * 
 */
UCLASS()
class MRDANJE_API UAbilityReverse : public UAbility
{
	GENERATED_BODY()
	
public:
	UAbilityReverse();
	void Init(class UInputComponent* InputComponentUsed, ACharacter* CharacterWithAbility, class UCharacterAbilities* AbilityManager);
	
protected:
	virtual void Reverse();

	ETileTypesEnum TileType;
	int TileColor;
	ACharacter* PlayerCharacter;
	class UCharacterAbilities* AbilityManager;
};
