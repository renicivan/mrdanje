// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelCheckpoint.h"

void ALevelCheckpoint::OnTestOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMrdanjeCharacter* MainCharacter = Cast<AMrdanjeCharacter>(OtherActor);
	if (MainCharacter)
	{
		AMrdanjeGameMode* GameMode = Cast<AMrdanjeGameMode>(GetWorld()->GetAuthGameMode());
		GameMode->SetLastCheckpoint(this);
	}
}


