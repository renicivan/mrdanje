// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Abilities/Ability.h"
#include "Abilities/AbilityFloorBomb.h"
#include "Abilities/AbilityLevitate.h"
#include "Abilities/AbilityReverseRed.h"
#include "Abilities/AbilityReverseBlue.h"
#include "CharacterAbilities.generated.h"

UENUM(BlueprintType)
enum class EAbilitiesEnum : uint8
{
	VE_Levitate 	UMETA(DisplayName = "Levitate"),
	VE_FloorBomb	UMETA(DisplayName = "Floor Bomb"),
	VE_ReverseRed	UMETA(DisplayName = "Reverse Red"),
	VE_ReverseBlue	UMETA(DisplayName = "Reverse Blue")
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MRDANJE_API UCharacterAbilities : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacterAbilities();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<EAbilitiesEnum> AbilitiesAvailable;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	TArray<UAbility*> Abilities;
	UInputComponent* PlayerInputComponent;
	float MaxPower;
	float CurrentPower;
	bool bStandingInSunlight;
	float PowerRecoveryPerSecond;
	
	void CreateAbility(EAbilitiesEnum Ability);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);
	void AddPower(float PowerDelta);
	void SetStandingInSunlight(bool StandingInSunlight);
};
