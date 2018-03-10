// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MrdanjeGameMode.generated.h"

UCLASS(minimalapi)
class AMrdanjeGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMrdanjeGameMode();

	void RegisterMainCharacter(class AMrdanjeCharacter* character);
	class AMrdanjeCharacter* GetMainCharacter();

private:
	AMrdanjeCharacter* MainCharacter;
};



