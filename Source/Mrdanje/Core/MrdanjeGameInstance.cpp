// Fill out your copyright notice in the Description page of Project Settings.

#include "MrdanjeGameInstance.h"

UMrdanjeGameInstance::UMrdanjeGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	CurrentLevel = 0;

	CreateMapOrder();
}

void UMrdanjeGameInstance::CreateMapOrder()
{
	// Create map order
	MapOrder.Add("TestLevel");
	MapOrder.Add("L0102");
}

void UMrdanjeGameInstance::OnLevelFinished()
{
	CurrentLevel += 1;
	if (MapOrder.IsValidIndex(CurrentLevel))
	{
		FString NewLevel = MapOrder[CurrentLevel];
		UE_LOG(LogTemp, Warning, TEXT("NEW level is %02d - %s"), CurrentLevel, *NewLevel);
		UGameplayStatics::OpenLevel(GetWorld(), *NewLevel);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("CONGRATULATIONS - Reached the end of final level!"));
	}
}

int UMrdanjeGameInstance::GetCurrentLevel()
{
	return CurrentLevel;
}