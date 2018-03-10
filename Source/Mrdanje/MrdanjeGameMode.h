// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Core/MrdanjeGameInstance.h"
#include "MrdanjeGameMode.generated.h"

namespace EGameState
{
	enum Type
	{
		Playing,
		Finished,
	};
}

UCLASS(minimalapi)
class AMrdanjeGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMrdanjeGameMode();

	void RegisterMainCharacter(class AMrdanjeCharacter* character);
	class AMrdanjeCharacter* GetMainCharacter();

	EGameState::Type GetGameState() const;
	void StartLevel();
	void FinishLevel();

private:
	AMrdanjeCharacter* MainCharacter;
	EGameState::Type GameState;
};



