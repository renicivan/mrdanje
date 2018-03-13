// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelElements/TriggerArea.h"
#include "LevelElements/LevelCheckpoint.h"
#include "Core/MrdanjeGameInstance.h"
#include "MrdanjeCharacter.h"
#include "DeathArea.generated.h"

/**
 * 
 */
UCLASS()
class MRDANJE_API ADeathArea : public ATriggerArea
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void OnTestOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;	
};
