// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UObject/NoExportTypes.h"
#include "Ability.generated.h"

/**
 * 
 */
UCLASS()
class MRDANJE_API UAbility : public UObject
{
	GENERATED_BODY()
	
public:
	UAbility();
	void Init(class UInputComponent* InputComponentUsed, ACharacter* CharacterWithAbility, class UCharacterAbilities* AbilityManager);
	bool NeedToTick();
	virtual void Tick(float DeltaTime);
	void SetActive(bool Active);
	bool IsActive();
	float PowerNeededToActivate();
	
protected:
	bool bNeedToTick = false;
	bool bActive = true;
	float MinPowerNeeded;
	class UCharacterAbilities* AbilityManager;
};
