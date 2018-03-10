// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilityLevitate.h"


UAbilityLevitate::UAbilityLevitate()
{
}

void UAbilityLevitate::Init(class UInputComponent* InputComponentUsed, ACharacter* CharacterWithAbility)
{
	InputComponentUsed->BindAction("Levitate", IE_Pressed, this, &UAbilityLevitate::Levitate);
	InputComponentUsed->BindAction("Levitate", IE_Released, this, &UAbilityLevitate::StopLevitating);

	bLevitating = false;
	PlayerCharacter = CharacterWithAbility;
}

void UAbilityLevitate::Levitate()
{
	bLevitating = true;
	bNeedToTick = true;
}

void UAbilityLevitate::StopLevitating()
{
	bLevitating = false;
	bNeedToTick = false;
}

void UAbilityLevitate::Tick(float DeltaTime)
{
	if (bLevitating)
	{
		if (PlayerCharacter->GetCharacterMovement()->Velocity.Z < 700.0f)
		{
			PlayerCharacter->GetCharacterMovement()->AddImpulse(FVector(0.0f, 0.0f, 50.0f), true);
			UE_LOG(LogTemp, Warning, TEXT("floating up %2.4f"), PlayerCharacter->GetCharacterMovement()->Velocity.Z);
		}
	}
}