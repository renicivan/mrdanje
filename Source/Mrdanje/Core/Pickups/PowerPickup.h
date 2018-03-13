// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Pickups/Pickup.h"
#include "Core/MrdanjeGameInstance.h"
#include "PowerPickup.generated.h"

/**
 * 
 */
UCLASS()
class MRDANJE_API APowerPickup : public APickup
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	float PowerAmount;
	
protected:
	void OnPickedUp() override;
	
	
};
