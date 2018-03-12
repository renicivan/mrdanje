// Fill out your copyright notice in the Description page of Project Settings.

#include "TogglerTile.h"

ATogglerTile::ATogglerTile()
	: AToggleableTile()
{
	EmptyMesh->SetCollisionResponseToAllChannels(ECR_Overlap);
	EmptyMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);

	EmptyMesh->bGenerateOverlapEvents = true;
	FScriptDelegate OverlapBeginDelegate;
	OverlapBeginDelegate.BindUFunction(this, "OnOverlapBegin");
	EmptyMesh->OnComponentBeginOverlap.Add(OverlapBeginDelegate);
	FScriptDelegate OverlapEndDelegate;
	OverlapEndDelegate.BindUFunction(this, "OnOverlapEnd");
	EmptyMesh->OnComponentEndOverlap.Add(OverlapEndDelegate);
}


void ATogglerTile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMoveableActor* OverlappingTile = Cast<AMoveableActor>(OtherActor);
	if (OverlappingTile)
	{
		UE_LOG(LogTemp, Warning, TEXT("toggler triggered"));

		if (TileType == OverlappingTile->GetTileType())
		{
			UE_LOG(LogTemp, Warning, TEXT("IT'S THE CORRECT COLOR!!!"));

			for (int i = 0; i < TilesAffected.Num(); i++)
			{
				if (TilesAffected[i]->TileType == TileType)
				{
					TilesAffected[i]->Toggle();
				}
			}

			Toggle();
		}
	}
}

void ATogglerTile::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMoveableActor* OverlappingTile = Cast<AMoveableActor>(OtherActor);
	if (OverlappingTile)
	{
		UE_LOG(LogTemp, Warning, TEXT("toggler overlap ended"));

		if (TileType == OverlappingTile->GetTileType())
		{
			UE_LOG(LogTemp, Warning, TEXT("IT'S THE CORRECT COLOR!!!"));

			for (int i = 0; i < TilesAffected.Num(); i++)
			{
				if (TilesAffected[i]->TileType == TileType)
				{
					TilesAffected[i]->Toggle();
				}
			}

			Toggle();
		}
	}
}