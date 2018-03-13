// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

UCLASS()
class MRDANJE_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup();

	UPROPERTY(Category = Meshes, VisibleAnywhere)
	UStaticMeshComponent* PickupMesh;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnPickedUp();

	float MeshPitch = 20.0f;
	float RotationPeriod = 8.0f;
	float RotationHeightDifference = 20.0f;
	float RotationT;
	FVector InitialPosition;
};
