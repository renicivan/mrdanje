// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilityReverseBlue.h"
#include "MainCharacter/CharacterAbilities.h"

void UAbilityReverseBlue::Init(class UInputComponent* InputComponentUsed, ACharacter* CharacterWithAbility, class UCharacterAbilities* AbilityManager)
{
	Super::Init(InputComponentUsed, CharacterWithAbility, AbilityManager);
	InputComponentUsed->BindAction("ReverseBlue", IE_Pressed, this, &UAbilityReverseBlue::Reverse);

	TileType = ETileTypesEnum::VE_Blue;
	TileColor = 0;
}

void UAbilityReverseBlue::Reverse()
{
	UAbilityReverse::Reverse();
}
