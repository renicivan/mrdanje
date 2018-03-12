// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainCharacter/Abilities/AbilityReverse.h"
#include "AbilityReverseRed.generated.h"

/**
 * 
 */
UCLASS()
class MRDANJE_API UAbilityReverseRed : public UAbilityReverse
{
	GENERATED_BODY()
	
public:
	void Init(class UInputComponent* InputComponentUsed, ACharacter* CharacterWithAbility, class UCharacterAbilities* AbilityManager);
	void Reverse();
	
};
