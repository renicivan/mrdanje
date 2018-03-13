// Fill out your copyright notice in the Description page of Project Settings.

#include "DeathArea.h"

void ADeathArea::OnTestOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMrdanjeCharacter* MainCharacter = Cast<AMrdanjeCharacter>(OtherActor);
	if (MainCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("DIED!"));

		AMrdanjeGameMode* GameMode = Cast<AMrdanjeGameMode>(GetWorld()->GetAuthGameMode());
		ALevelCheckpoint* LastCheckpoint = GameMode->GetLastCheckpoint();

		MainCharacter->SetActorLocation(LastCheckpoint->GetActorLocation());
		MainCharacter->PrintMessageToScreen("When you die, you are returned automatically to your previous checkpoint.", 180);

		UMrdanjeGameInstance* GameInstance = Cast<UMrdanjeGameInstance>(GetGameInstance());
		GameInstance->AddPower(-100.0f);
	}
}


