// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterAbilities.h"


// Sets default values for this component's properties
UCharacterAbilities::UCharacterAbilities()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UCharacterAbilities::BeginPlay()
{
	Super::BeginPlay();

	// Create all the abilities available to the character.
	Abilities.Empty();
	for (auto& AbilityAvailable : AbilitiesAvailable)
	{
		CreateAbility(AbilityAvailable);
	}
}

void UCharacterAbilities::CreateAbility(EAbilitiesEnum Ability)
{
	if (Ability == EAbilitiesEnum::VE_Dash)
	{
	}
	else if (Ability == EAbilitiesEnum::VE_Levitate) {
		UE_LOG(LogTemp, Warning, TEXT("Adding Levitate ability to the character."));
		// Create a new Levitation ability
		UAbilityLevitate* LevitationAbility = NewObject<UAbilityLevitate>();
		LevitationAbility->Init(PlayerInputComponent, Cast<ACharacter>(GetOwner()));
		
		Abilities.Add(LevitationAbility);
	}
	else if (Ability == EAbilitiesEnum::VE_FloorBomb) {
		UE_LOG(LogTemp, Warning, TEXT("Adding Floor Bomb ability to the character."));
		// Create a new Floor Bomb ability
		UAbilityFloorBomb* FloorBombAbility = NewObject<UAbilityFloorBomb>();
		FloorBombAbility->Init(PlayerInputComponent, Cast<ACharacter>(GetOwner()));

		Abilities.Add(FloorBombAbility);
	} else {
		UE_LOG(LogTemp, Warning, TEXT("WARNING: Tried adding an unknown ability to the player."));
	}
}


// Called every frame
void UCharacterAbilities::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	for (auto& Ability: Abilities)
	{
		if (Ability->NeedToTick()) {
			Ability->Tick(DeltaTime);
		}
	}
}

void UCharacterAbilities::SetupPlayerInputComponent(class UInputComponent* CurrentPlayerInputComponent)
{
	PlayerInputComponent = CurrentPlayerInputComponent;
}