// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/Material.h"
#include "MoveableActor.h"
#include "ToggleableTile.generated.h"

UCLASS()
class MRDANJE_API AToggleableTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AToggleableTile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void SetState(bool Filled);
	void SetTypeProperties();
	bool bFilled = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(Category = Meshes, VisibleAnywhere)
	UStaticMeshComponent* EmptyMesh;

	UPROPERTY(Category = Meshes, VisibleAnywhere)
	UStaticMeshComponent* FillMesh;

	UPROPERTY(EditAnywhere)
	ETileTypesEnum TileType;

	void Toggle();
	
};
