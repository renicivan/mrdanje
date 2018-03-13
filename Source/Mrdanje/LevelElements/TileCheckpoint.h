// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Materials/Material.h"
#include "Core/Utilities.h"
#include "TileCheckpoint.generated.h"

UENUM(BlueprintType)
enum class ECheckpointCommandsEnum : uint8
{
	VE_Stay 	UMETA(DisplayName = "Stay"),
	VE_Go		UMETA(DisplayName = "Go")
};

USTRUCT(BlueprintType)
struct FCheckpointCommandStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECheckpointCommandsEnum Command;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Duration;
	// SOUND TO PLAY
};

UCLASS()
class MRDANJE_API ATileCheckpoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATileCheckpoint();
	TArray<FCheckpointCommandStruct> GetCommands();
	void SetTileType(ETileTypesEnum TileType);
	void ConnectToNextCheckpoint(ATileCheckpoint* NextCheckpoint);

	UPROPERTY(Category = Meshes, VisibleAnywhere)
	UStaticMeshComponent* CheckpointMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<struct FCheckpointCommandStruct> Commands;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UStaticMeshComponent* LinkMesh;
};
