// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UObject/ConstructorHelpers.h"
#include "Algo/Reverse.h"
#include "Materials/Material.h"
#include "TileCheckpoint.h"
#include "Core/Utilities.h"
#include "MoveableActor.generated.h"

struct FTileProperties {
	int WaitCycles;
	float CycleDuration;
	FString MaterialPath;
};

UCLASS()
class MRDANJE_API AMoveableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMoveableActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void InitTilePropertySets();
	void ExecuteReverse();
	void CheckForReverse();

	ETileTypesEnum CurrentTileType;
	bool bShouldMove = true;
	int LastCheckpoint;
	bool bWaitingOnCheckpoint = false;
	bool bNeedToReverse = false;
	float WaitTimeLeft;
	TMap<ETileTypesEnum, FTileProperties> TileProperties;
	TArray<FCheckpointCommandStruct> ActiveCommands;
	int CurrentCommandIndex;
	float CurrentCommandTimeLeft;

	void PrintActiveCommands();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetTileProperties(ETileTypesEnum TileType, bool Force);
	void Reverse();
	ETileTypesEnum GetTileType();

	UPROPERTY(Category = Meshes, VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	TArray<ATileCheckpoint*> Checkpoints;

	UPROPERTY(EditAnywhere)
	int StartCheckpoint;
	
	UPROPERTY(EditAnywhere)
	ETileTypesEnum TileType;
};
