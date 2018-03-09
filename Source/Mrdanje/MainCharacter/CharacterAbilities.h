// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Abilities/AbilityLevitate.h"
#include "CharacterAbilities.generated.h"

UENUM(BlueprintType)
enum class EAbilitiesEnum : uint8
{
	VE_Levitate 	UMETA(DisplayName = "Levitate"),
	VE_Dash			UMETA(DisplayName = "Dash")
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
	void CreateAbilities();

	TArray<Ability> Abilities;
	UInputComponent* PlayerInputComponent;

	void Levitate();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);

		
	
};
