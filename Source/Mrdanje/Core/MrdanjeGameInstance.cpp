// Fill out your copyright notice in the Description page of Project Settings.

#include "MrdanjeGameInstance.h"

UMrdanjeGameInstance::UMrdanjeGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	CurrentLevel = 0;
	PowerReserve = 100.0f;

	CreateMapOrder();
}

void UMrdanjeGameInstance::CreateMapOrder()
{
	// Create map order
	MapOrder.Add("TestLevel");
	MapOrder.Add("L0101");
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

void UMrdanjeGameInstance::AddPower(float PowerDelta)
{
	PowerReserve += PowerDelta;
	UE_LOG(LogTemp, Warning, TEXT("Current power reserves at %.2f!"), PowerReserve);

	if (PowerReserve <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("G A M E   O V E R !"));
	}
}

float UMrdanjeGameInstance::GetPowerReserve()
{
	return PowerReserve;
}