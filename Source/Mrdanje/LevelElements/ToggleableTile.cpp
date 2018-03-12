// Fill out your copyright notice in the Description page of Project Settings.

#include "ToggleableTile.h"


// Sets default values
AToggleableTile::AToggleableTile()
{
	PrimaryActorTick.bCanEverTick = false;
	USceneComponent* RootComponent = GetRootComponent();

	EmptyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EmptyMesh"));
	EmptyMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	//EmptyMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	EmptyMesh->SetupAttachment(RootComponent);

	/*EmptyMesh->bGenerateOverlapEvents = true;
	FScriptDelegate HitDelegate;
	HitDelegate.BindUFunction(this, "OnOverlapBegin");
	EmptyMesh->OnComponentBeginOverlap.Add(HitDelegate);*/

	FillMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FillMesh"));
	FillMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	FillMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	FillMesh->SetupAttachment(RootComponent);

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
		FillMesh->SetWorldScale3D(EmptyMesh->GetComponentScale());
	}
	else
	{
		FillMesh->SetWorldScale3D(FVector(0.0f, 0.0f, 0.0f));
	}

	bFilled = Filled;
}

void AToggleableTile::SetTypeProperties()
{
	FString MaterialPath;
	FString TransparentMaterialPath;

	if (TileType == ETileTypesEnum::VE_Red)
	{
		MaterialPath = "Material'/Game/Mrdanje/MaterialLibrary/LevelUnits/M_RedTile.M_RedTile'";
		TransparentMaterialPath = "Material'/Game/Mrdanje/MaterialLibrary/LevelUnits/M_RedTileTransparent.M_RedTileTransparent'";
	}
	else if (TileType == ETileTypesEnum::VE_Blue)
	{
		MaterialPath = "Material'/Game/Mrdanje/MaterialLibrary/LevelUnits/M_BlueTile.M_BlueTile'";
		TransparentMaterialPath = "Material'/Game/Mrdanje/MaterialLibrary/LevelUnits/M_BlueTileTransparent.M_BlueTileTransparent'";
	}
	else if (TileType == ETileTypesEnum::VE_Yellow)
	{
		MaterialPath = "Material'/Game/Mrdanje/MaterialLibrary/LevelUnits/M_YellowTile.M_YellowTile'";
		TransparentMaterialPath = "Material'/Game/Mrdanje/MaterialLibrary/LevelUnits/M_YellowTileTransparent.M_YellowTileTransparent'";
	}
	else
	{
		MaterialPath = "Material'/Game/Mrdanje/MaterialLibrary/LevelUnits/M_WhiteTile.M_WhiteTile'";
		TransparentMaterialPath = "Material'/Game/Mrdanje/MaterialLibrary/LevelUnits/M_WhiteTileTransparent.M_WhiteTileTransparent'";
	}

	UMaterial* EmptyMaterial = Cast<UMaterial>(StaticLoadObject(UMaterial::StaticClass(), NULL, *TransparentMaterialPath));
	EmptyMesh->SetMaterial(0, EmptyMaterial);

	UMaterial* NewMaterial = Cast<UMaterial>(StaticLoadObject(UMaterial::StaticClass(), NULL, *MaterialPath));
	FillMesh->SetMaterial(0, NewMaterial);
}