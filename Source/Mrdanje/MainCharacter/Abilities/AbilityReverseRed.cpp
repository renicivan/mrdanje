// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilityReverseRed.h"
#include "MainCharacter/CharacterAbilities.h"

void UAbilityReverseRed::Init(class UInputComponent* InputComponentUsed, ACharacter* CharacterWithAbility, class UCharacterAbilities* AbilityManager)
{
	Super::Init(InputComponentUsed, CharacterWithAbility, AbilityManager);
	InputComponentUsed->BindAction("ReverseRed", IE_Pressed, this, &UAbilityReverseRed::Reverse);

	TileType = ETileTypesEnum::VE_Red;
	TileColor = 255;
}

void UAbilityReverseRed::Reverse()
{
	UAbilityReverse::Reverse();
}