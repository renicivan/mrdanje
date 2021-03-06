// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter/CharacterAbilities.h"
#include "Engine/World.h"
#include "MrdanjeGameMode.h"
#include "MrdanjeHUD.h"
#include "MrdanjeCharacter.generated.h"

class UInputComponent;

UCLASS(config=Game)
class AMrdanjeCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	class USkeletalMeshComponent* Mesh1P;

	/** Location on player mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent* ProjectileSpawnLocation;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class UStaticMeshComponent* DiamondRed;

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class UStaticMeshComponent* DiamondBlue;

	/** Ability manager */
	UPROPERTY(VisibleAnywhere, Category = Component)
	class UCharacterAbilities* CharacterAbilities;


public:
	AMrdanjeCharacter();

	void OnLevelFinished();
	USceneComponent* GetProjectileSpawnLocation();

protected:
	virtual void BeginPlay();

public:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	void SetStandingInSunlight(bool StandingInSunlight);
	float GetCurrentBatteryPower();

protected:

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	bool bStandingInSunlight = false;

	bool bTutorializedSun = false;
	
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	/** Returns Mesh1P subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	UFUNCTION(BlueprintCallable)
	void PrintMessageToScreen(FString Message, int Duration);
};

