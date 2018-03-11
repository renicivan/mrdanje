// Fill out your copyright notice in the Description page of Project Settings.

#include "Ability.h"


UAbility::UAbility()
{

}

void UAbility::Init(class UInputComponent* InputComponentUsed, ACharacter* CharacterWithAbility, class UCharacterAbilities* AbilityManager)
{
}

bool UAbility::NeedToTick()
{
	return bNeedToTick;
}

void UAbility::Tick(float DeltaTime)
{
}

void UAbility::SetActive(bool Active)
{
	bActive = Active;
}

bool UAbility::IsActive()
{
	return bActive;
}

float UAbility::PowerNeededToActivate()
{
	return MinPowerNeeded;
}