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

	UE_LOG(LogTemp, Warning, TEXT("AAAAAAAAAAAAAaaaaaaaaaaaaaaaAAAAAAAAAAAAAAAAAAA"));

	Abilities.Empty();
	UE_LOG(LogTemp, Warning, TEXT("prije %02d"), Abilities.Num());

	for (auto& AbilityAvailable : AbilitiesAvailable)
	{
		if (AbilityAvailable == EAbilitiesEnum::VE_Dash)
		{
			UE_LOG(LogTemp, Warning, TEXT("dashhhhhhh"));
		}
		else if (AbilityAvailable == EAbilitiesEnum::VE_Levitate) {
			UE_LOG(LogTemp, Warning, TEXT("levitate"));
			AbilityLevitate* ab = new AbilityLevitate();
			Abilities.Add(*ab);

			PlayerInputComponent->BindAction("Levitate", IE_Pressed, this, &UCharacterAbilities::Levitate);
			//PlayerInputComponent->BindAction("Jump", IE_Pressed, this, );
			//PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("unknown ability"));
		}
	}


	UE_LOG(LogTemp, Warning, TEXT("nakon %02d"), Abilities.Num());

	// ...
	
}

void UCharacterAbilities::Levitate()
{
	UE_LOG(LogTemp, Warning, TEXT("LEVITATE"));
}

void UCharacterAbilities::CreateAbilities()
{

}


// Called every frame
void UCharacterAbilities::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCharacterAbilities::SetupPlayerInputComponent(class UInputComponent* CurrentPlayerInputComponent)
{
	PlayerInputComponent = CurrentPlayerInputComponent;
}