// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "MrdanjeGameMode.h"
#include "MrdanjeHUD.h"
#include "MrdanjeCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMrdanjeGameMode::AMrdanjeGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Mrdanje/Core/Characters/MainCharacter/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AMrdanjeHUD::StaticClass();
}

void AMrdanjeGameMode::RegisterMainCharacter(AMrdanjeCharacter* character)
{
	this->MainCharacter = character;
}

AMrdanjeCharacter* AMrdanjeGameMode::GetMainCharacter()
{
	return this->MainCharacter;
}