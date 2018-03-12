// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilityReverse.h"
#include "MainCharacter/CharacterAbilities.h"

UAbilityReverse::UAbilityReverse()
{
}

void UAbilityReverse::Init(class UInputComponent* InputComponentUsed, ACharacter* CharacterWithAbility, class UCharacterAbilities* AbilityManager)
{
	//InputComponentUsed->BindAction("FloorBomb", IE_Pressed, this, &UAbilityFloorBomb::Trigger);
	UE_LOG(LogTemp, Warning, TEXT("++++++++++++++++++++++++ REJOIIIIIIIIIIIIIIICEEEEEEEEEE"));
	MinPowerNeeded = 20.0f;

	this->AbilityManager = AbilityManager;
	PlayerCharacter = CharacterWithAbility;
}

void UAbilityReverse::Reverse()
{
	if (bActive)
	{
		UE_LOG(LogTemp, Warning, TEXT("REVERSING %02d!"), TileColor);
		for (TActorIterator<AMoveableActor> ActorItr(PlayerCharacter->GetWorld()); ActorItr; ++ActorItr)
		{
			if (ActorItr->GetTileType() == this->TileType)
			{
				ActorItr->Reverse();
			}
		}

		//AbilityManager->AddPower(-MinPowerNeeded);
	}
}