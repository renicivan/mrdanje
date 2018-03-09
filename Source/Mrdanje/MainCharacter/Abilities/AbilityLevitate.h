// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability.h"

/**
 * 
 */
class MRDANJE_API AbilityLevitate : public Ability
{
public:
	AbilityLevitate();
	~AbilityLevitate();

	void Levitate();
};
