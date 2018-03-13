// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TileCheckpoint.generated.h"

UCLASS()
class MRDANJE_API ATileCheckpoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATileCheckpoint();

	UPROPERTY(Category = Meshes, VisibleAnywhere)
	UStaticMeshComponent* CheckpointMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
