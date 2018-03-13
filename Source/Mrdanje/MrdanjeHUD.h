// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MrdanjeHUD.generated.h"

struct FHUDMessageStruct
{
	FString Message;
	int Duration;

	FHUDMessageStruct(FString NewMessage, int NewDuration)
	{
		Message = NewMessage;
		Duration = NewDuration;
	}
};

UCLASS()
class AMrdanjeHUD : public AHUD
{
	GENERATED_BODY()

public:
	AMrdanjeHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

	void AddMessage(FString Text, int TimeDisplayed);

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;
	TArray<FHUDMessageStruct> Messages;
	bool bShowingMessage = false;
	int TimeLeftForMessage;

};

