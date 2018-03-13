// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "MrdanjeHUD.h"
#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"
#include "TextureResource.h"
#include "MrdanjeCharacter.h"
#include "Core/MrdanjeGameInstance.h"
#include "CanvasItem.h"
#include "UObject/ConstructorHelpers.h"

AMrdanjeHUD::AMrdanjeHUD()
{
	// Set the crosshair texture
	//static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshairTexObj(TEXT("/Game/FirstPerson/Textures/FirstPersonCrosshair"));
	//CrosshairTex = CrosshairTexObj.Object;
}


void AMrdanjeHUD::DrawHUD()
{
	Super::DrawHUD();

	// Draw very simple crosshair

	// find center of the Canvas
	const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

	// offset by half the texture's dimensions so that the center of the texture aligns with the center of the Canvas
	const FVector2D CrosshairDrawPosition( (Center.X),
										   (Center.Y + 20.0f));

	//DrawText("AHHAHA", FLinearColor::Blue, 100, 100);
	
	
	AMrdanjeCharacter* Player = Cast<AMrdanjeCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	DrawText(FString::Printf(TEXT("BATTERY POWER:  %.0f"), Player->GetCurrentBatteryPower()), FLinearColor::Green, 100, 100);

	DrawText(FString::Printf(TEXT("POWER RESERVE:  %.0f"), Cast<UMrdanjeGameInstance>(GetWorld()->GetGameInstance())->GetPowerReserve()), FLinearColor::Yellow, 100, 120);
	

	if (Messages.Num() > 0)
	{
		Messages[0].Duration -= 1;
		//DrawText(*Messages[0].Message, FLinearColor::Blue, 50, 700);
		DrawText(Messages[0].Message, FLinearColor::Blue, 100, 400);

		if (Messages[0].Duration == 0)
		{
			Messages.RemoveAt(0);
		}
	}

	// draw the crosshair
	//FCanvasTileItem TileItem( CrosshairDrawPosition, CrosshairTex->Resource, FLinearColor::White);
	//TileItem.BlendMode = SE_BLEND_Translucent;
	//Canvas->DrawItem( TileItem );
}

void AMrdanjeHUD::AddMessage(FString Text, int TimeDisplayed)
{
	FHUDMessageStruct NewMessage(Text, TimeDisplayed);

	Messages.Add(NewMessage);
}