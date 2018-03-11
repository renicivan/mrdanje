// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilityFloorBomb.h"


UAbilityFloorBomb::UAbilityFloorBomb()
{
}

void UAbilityFloorBomb::Init(class UInputComponent* InputComponentUsed, ACharacter* CharacterWithAbility)
{
	UE_LOG(LogTemp, Warning, TEXT("Floor bomb INITIALIZED!"));
	InputComponentUsed->BindAction("FloorBomb", IE_Pressed, this, &UAbilityFloorBomb::Trigger);

	PlayerCharacter = CharacterWithAbility;
}

void UAbilityFloorBomb::Trigger()
{
	UE_LOG(LogTemp, Warning, TEXT("Floor bomb activity triggered!"));

	FireBomb();

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

	
	UObject* ProjectileBP = StaticLoadObject(UObject::StaticClass(), nullptr, TEXT("/Game/Mrdanje/Weapons/FloorBomb/BP_FloorBomb"));
	UBlueprint* bp = Cast<UBlueprint>(ProjectileBP);
	TSubclassOf<class AFloorBomb> ProjectileBlueprint;
	ProjectileBlueprint = (UClass*)bp->GeneratedClass;

	FVector Location = PlayerCharacter->GetActorLocation();
	FRotator Rotation = FRotator(0);
	UWorld* World = PlayerCharacter->GetWorld();

	ActiveProjectile = SpawnBlueprint<AFloorBomb>(World, ProjectileBlueprint, Location, Rotation, true, PlayerCharacter, NULL);
	

	
	ForceApplyTime = 0.1f;
	TArray<UCameraComponent*> Cameras;
	PlayerCharacter->GetComponents<UCameraComponent>(Cameras);
	FRotator CameraRotation = Cameras[0]->GetComponentRotation();
	CameraRotation.Normalize();
	ForceVector = FRotationMatrix(CameraRotation).GetScaledAxis(EAxis::X) * 50000.0f;
	ForceVector.Z += 20000.0f;

	bNeedToTick = true;
}

void UAbilityFloorBomb::ExplodeBomb()
{
	UE_LOG(LogTemp, Warning, TEXT("Detonating projectile!!"));
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