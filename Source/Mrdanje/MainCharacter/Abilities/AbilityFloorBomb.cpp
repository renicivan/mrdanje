// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilityFloorBomb.h"
#include "MainCharacter/CharacterAbilities.h"


UAbilityFloorBomb::UAbilityFloorBomb()
{
}

void UAbilityFloorBomb::Init(class UInputComponent* InputComponentUsed, ACharacter* CharacterWithAbility, UCharacterAbilities* AbilityManager)
{
	UE_LOG(LogTemp, Warning, TEXT("Floor bomb INITIALIZED!"));
	InputComponentUsed->BindAction("FloorBomb", IE_Pressed, this, &UAbilityFloorBomb::Trigger);

	PlayerCharacter = CharacterWithAbility;
	MinPowerNeeded = 20.0f;

	this->AbilityManager = AbilityManager;
}

void UAbilityFloorBomb::Trigger()
{
	if (bActive)
	{
		UE_LOG(LogTemp, Warning, TEXT("Floor bomb activity triggered!"));

		if (!ActiveProjectile) {
			FireBomb();
		}
		else {
			ExplodeBomb();
		}
	}
	

	/*if (!ActiveProjectile) {
		FireBomb();
	}
	else {
		ExplodeBomb();
	}	*/
}

void UAbilityFloorBomb::FireBomb()
{
	UE_LOG(LogTemp, Warning, TEXT("Spawning floor bomb!"));

	
	/*UObject* ProjectileBP = StaticLoadObject(UObject::StaticClass(), nullptr, TEXT("/Game/Mrdanje/Weapons/FloorBomb/BP_FloorBomb"));
	UBlueprint* bp = Cast<UBlueprint>(ProjectileBP);
	TSubclassOf<class AFloorBomb> ProjectileBlueprint;
	ProjectileBlueprint = (UClass*)bp->GeneratedClass;*/

	FVector Location = PlayerCharacter->GetActorLocation();
	FRotator Rotation = FRotator(0);
	UWorld* World = PlayerCharacter->GetWorld();

	ActiveProjectile = Utilities::SpawnBlueprint<AFloorBomb>("/Game/Mrdanje/Weapons/FloorBomb/BP_FloorBomb", World, Location, Rotation, PlayerCharacter);

	//ActiveProjectile = SpawnBlueprint<AFloorBomb>(World, ProjectileBlueprint, Location, Rotation, true, PlayerCharacter, NULL);
	

	
	ForceApplyTime = 0.1f;
	TArray<UCameraComponent*> Cameras;
	PlayerCharacter->GetComponents<UCameraComponent>(Cameras);
	FRotator CameraRotation = Cameras[0]->GetComponentRotation();
	CameraRotation.Normalize();
	ForceVector = FRotationMatrix(CameraRotation).GetScaledAxis(EAxis::X) * 50000.0f;
	ForceVector.Z += 20000.0f;

	bNeedToTick = true;
	AbilityManager->AddPower(-MinPowerNeeded);
}

void UAbilityFloorBomb::ExplodeBomb()
{
	UE_LOG(LogTemp, Warning, TEXT("Detonating projectile!!"));
	ActiveProjectile->Detonate();
	ActiveProjectile = NULL;
}

void UAbilityFloorBomb::Tick(float DeltaTime)
{
	UE_LOG(LogTemp, Warning, TEXT("FLOOR BOMB TICKING %2.3f"), ForceApplyTime);
	if (ForceApplyTime > 0.0f && ActiveProjectile != nullptr)
	{
		ActiveProjectile->ProjectileMesh->AddForce(ForceVector);
		ForceApplyTime -= DeltaTime;
	}
	else {
		ForceApplyTime = 0.0f;
		bNeedToTick = false;
	}
}