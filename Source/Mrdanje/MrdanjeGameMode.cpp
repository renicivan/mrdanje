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

	UE_LOG(LogTemp, Warning, TEXT("GAME MODE CREATED!!!"));
}

void AMrdanjeGameMode::RegisterMainCharacter(AMrdanjeCharacter* character)
{
	this->MainCharacter = character;
}

AMrdanjeCharacter* AMrdanjeGameMode::GetMainCharacter()
{
	return this->MainCharacter;
}

EGameState::Type AMrdanjeGameMode::GetGameState() const
{
	return GameState;
}

void AMrdanjeGameMode::StartLevel()
{
	UE_LOG(LogTemp, Warning, TEXT("Level started!"));
	GameState = EGameState::Playing;

	UMrdanjeGameInstance* GameInstance = Cast<UMrdanjeGameInstance>(GetGameInstance());
	UE_LOG(LogTemp, Warning, TEXT("Power reserve at %.2f!"), GameInstance->GetPowerReserve());
}

void AMrdanjeGameMode::FinishLevel()
{
	UE_LOG(LogTemp, Warning, TEXT("Level finished!"));
	GameState = EGameState::Finished;

	if (MainCharacter != NULL)
	{
		MainCharacter->OnLevelFinished();
	}

	// get game instance
	UMrdanjeGameInstance* GameInstance = Cast<UMrdanjeGameInstance>(GetGameInstance());
	GameInstance->OnLevelFinished();
}

void AMrdanjeGameMode::SetLastCheckpoint(ALevelCheckpoint* Checkpoint)
{
	if (Checkpoint != LastCheckpoint)
	{
		Cast<UMrdanjeGameInstance>(GetGameInstance())->PrintMessageToScreen("Checkpoint reached.", 180);
	}
	UE_LOG(LogTemp, Warning, TEXT("Checkpoint reached!"));
	LastCheckpoint = Checkpoint;
}

ALevelCheckpoint * AMrdanjeGameMode::GetLastCheckpoint()
{
	return LastCheckpoint;
}
