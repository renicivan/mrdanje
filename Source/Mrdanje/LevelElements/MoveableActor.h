// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/Material.h"
#include "MoveableActor.generated.h"

UENUM(BlueprintType)
enum class ETileTypesEnum : uint8
{
	VE_White 	UMETA(DisplayName = "White"),
	VE_Red		UMETA(DisplayName = "Red"),
	VE_Blue		UMETA(DisplayName = "Blue"),
	VE_Yellow	UMETA(DisplayName = "Yellow")
};

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

	ETileTypesEnum CurrentTileType;
	bool bShouldMove = true;
	int LastCheckpoint;
	bool bWaitingOnCheckpoint = false;
	float WaitTimeLeft;

	TMap<ETileTypesEnum, FTileProperties> TileProperties;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetTileProperties(ETileTypesEnum TileType, bool Force);

	UPROPERTY(Category = Meshes, VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	TArray<AActor*> Checkpoints;

	UPROPERTY(EditAnywhere)
	int StartCheckpoint;
	
	UPROPERTY(EditAnywhere)
	ETileTypesEnum TileType;
};
