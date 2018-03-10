// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Ability.generated.h"

/**
 * 
 */
UCLASS()
class MRDANJE_API UAbility : public UObject
{
	GENERATED_BODY()
	
public:
	UAbility();
	void Init();
	bool NeedToTick();
	virtual void Tick(float DeltaTime);
	
protected:
	bool bNeedToTick= false;
};
