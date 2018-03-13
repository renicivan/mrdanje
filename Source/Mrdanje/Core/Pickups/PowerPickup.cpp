// Fill out your copyright notice in the Description page of Project Settings.

#include "PowerPickup.h"

void APowerPickup::OnPickedUp()
{
	UMrdanjeGameInstance* GameInstance = Cast<UMrdanjeGameInstance>(GetGameInstance());
	GameInstance->AddPower(PowerAmount);
	GameInstance->PrintMessageToScreen("Picking up power cells replenishes your power reserves.", 180);

	Destroy();
}