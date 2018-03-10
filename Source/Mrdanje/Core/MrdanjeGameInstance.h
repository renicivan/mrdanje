// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/GameInstance.h"
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
	
private:
	int CurrentLevel;
	TArray<FString> MapOrder;

	void CreateMapOrder();
	
};
