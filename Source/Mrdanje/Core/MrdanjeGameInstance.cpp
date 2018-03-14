// Fill out your copyright notice in the Description page of Project Settings.

#include "MrdanjeGameInstance.h"

UMrdanjeGameInstance::UMrdanjeGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	CurrentLevel = 0;
	PowerReserve = 1000.0f;

	CreateMapOrder();
}

void UMrdanjeGameInstance::CreateMapOrder()
{
	// Create map order
	MapOrder.Add("L0101");
	MapOrder.Add("L0102");
	MapOrder.Add("L0103");
}

void UMrdanjeGameInstance::OnLevelFinished()
{
	CurrentLevel += 1;
	if (MapOrder.IsValidIndex(CurrentLevel))
	{
		FString NewLevel = MapOrder[CurrentLevel];
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

	if (PowerReserve <= 0)
	{
		PowerReserve = 0.f;

		if (!bTutorializedGameOver)
		{
			PrintMessageToScreen("Running out of reserve power would usually be game over, but this is a demo.", 180);
			bTutorializedGameOver = true;
		}
	}
}

float UMrdanjeGameInstance::GetPowerReserve()
{
	return PowerReserve;
}

void UMrdanjeGameInstance::PrintMessageToScreen(FString Message, int Duration)
{
	Cast<AMrdanjeHUD>(GetWorld()->GetFirstPlayerController()->GetHUD())->AddMessage(Message, Duration);
}