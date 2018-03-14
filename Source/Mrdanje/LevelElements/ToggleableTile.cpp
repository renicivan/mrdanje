// Fill out your copyright notice in the Description page of Project Settings.

#include "ToggleableTile.h"


// Sets default values
AToggleableTile::AToggleableTile()
{
	PrimaryActorTick.bCanEverTick = false;
	USceneComponent* RootComponent = GetRootComponent();

	EmptyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EmptyMesh"));
	EmptyMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	EmptyMesh->SetupAttachment(RootComponent);

	FillMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FillMesh"));
	FillMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	FillMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	FillMesh->SetupAttachment(RootComponent);

	FullScale = EmptyMesh->GetComponentScale();
	SetState(bFilled);
}

// Called when the game starts or when spawned
void AToggleableTile::BeginPlay()
{
	Super::BeginPlay();
	
	SetState(bFilled);
	SetTypeProperties();
}

// Called every frame
void AToggleableTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AToggleableTile::Toggle()
{
	SetState(!bFilled);
}

void AToggleableTile::SetState(bool Filled)
{
	if (Filled)
	{
		FillMesh->SetRelativeScale3D(FullScale);
	}
	else
	{
		FillMesh->SetRelativeScale3D(FVector(0.0f, 0.0f, 0.0f));
	}

	FillMesh->SetRelativeLocation(FVector(0, 0, 0));

	bFilled = Filled;
}

void AToggleableTile::SetTypeProperties()
{
	FString MaterialPath;
	FString TransparentMaterialPath;

	if (TileType == ETileTypesEnum::VE_Red)
	{
		MaterialPath = "Material'/Game/Mrdanje/MaterialLibrary/LevelUnits/M_RedTileTransparent.M_RedTileTransparent'";
		TransparentMaterialPath = "Material'/Game/Mrdanje/MaterialLibrary/LevelUnits/M_RedTileTransparent.M_RedTileTransparent'";
	}
	else if (TileType == ETileTypesEnum::VE_Blue)
	{
		MaterialPath = "Material'/Game/Mrdanje/MaterialLibrary/LevelUnits/M_BlueTileTransparent.M_BlueTileTransparent'";
		TransparentMaterialPath = "Material'/Game/Mrdanje/MaterialLibrary/LevelUnits/M_BlueTileTransparent.M_BlueTileTransparent'";
	}
	else if (TileType == ETileTypesEnum::VE_Yellow)
	{
		MaterialPath = "Material'/Game/Mrdanje/MaterialLibrary/LevelUnits/M_YellowTileTransparent.M_YellowTileTransparent'";
		TransparentMaterialPath = "Material'/Game/Mrdanje/MaterialLibrary/LevelUnits/M_YellowTileTransparent.M_YellowTileTransparent'";
	}
	else
	{
		MaterialPath = "Material'/Game/Mrdanje/MaterialLibrary/LevelUnits/M_WhiteTileTransparent.M_WhiteTileTransparent'";
		TransparentMaterialPath = "Material'/Game/Mrdanje/MaterialLibrary/LevelUnits/M_WhiteTileTransparent.M_WhiteTileTransparent'";
	}

	UMaterial* EmptyMaterial = Cast<UMaterial>(StaticLoadObject(UMaterial::StaticClass(), NULL, *TransparentMaterialPath));
	EmptyMesh->SetMaterial(0, EmptyMaterial);

	UMaterial* NewMaterial = Cast<UMaterial>(StaticLoadObject(UMaterial::StaticClass(), NULL, *MaterialPath));
	FillMesh->SetMaterial(0, NewMaterial);
}