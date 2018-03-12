// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainCharacter/Abilities/AbilityReverse.h"
#include "AbilityReverseBlue.generated.h"

/**
 * 
 */
UCLASS()
class MRDANJE_API UAbilityReverseBlue : public UAbilityReverse
{
	GENERATED_BODY()
	
public:
	void Init(class UInputComponent* InputComponentUsed, ACharacter* CharacterWithAbility, class UCharacterAbilities* AbilityManager);
	void Reverse() override;
	
};
