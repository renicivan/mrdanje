// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "MrdanjeGameMode.h"
#include "MrdanjeHUD.h"
#include "MrdanjeCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMrdanjeGameMode::AMrdanjeGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AMrdanjeHUD::StaticClass();
}
