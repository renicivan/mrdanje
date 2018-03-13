// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/GameInstance.h"
#include "MrdanjeHUD.h"
#include "MrdanjeGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MRDANJE_API UMrdanjeGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UMrdanjeGameInstance(const FObjectInitializer& ObjectInitializer);

	int GetCurrentLevel();
	void OnLevelFinished();
	void AddPower(float PowerDelta);
	float GetPowerReserve();

	void PrintMessageToScreen(FString Message, int Duration);
	
private:
	int CurrentLevel;
	TArray<FString> MapOrder;
	float PowerReserve;

	void CreateMapOrder();
	
};
