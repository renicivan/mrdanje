// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "GameFramework/Character.h"
//#include "GameFramework/CharacterMovementComponent.h"
#include "MainCharacter/Abilities/Ability.h"
#include "AbilityLevitate.generated.h"

/**
 * 
 */
UCLASS()
class MRDANJE_API UAbilityLevitate : public UAbility
{
	GENERATED_BODY()
	
public:
	UAbilityLevitate();
	void Init(class UInputComponent* InputComponentUsed, ACharacter* CharacterWithAbility, class UCharacterAbilities* AbilityManager);
	void Tick(float DeltaTime) override;
	
protected:
	void Levitate();
	void StopLevitating();

	bool bLevitating;
	ACharacter* PlayerCharacter;
	float PowerUsedPerSecond = 50.0f;
};
