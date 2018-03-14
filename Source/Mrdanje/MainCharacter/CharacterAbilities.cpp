// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterAbilities.h"


// Sets default values for this component's properties
UCharacterAbilities::UCharacterAbilities()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UCharacterAbilities::BeginPlay()
{
	Super::BeginPlay();

	MaxPower= 100.0f;
	CurrentPower = MaxPower;
	PowerRecoveryPerSecond = 30.0f;

	// Create all the abilities available to the character.
	Abilities.Empty();
	for (auto& AbilityAvailable : AbilitiesAvailable)
	{
		CreateAbility(AbilityAvailable);
	}

	UE_LOG(LogTemp, Warning, TEXT("Current POWER is %.2f."), CurrentPower);
}

void UCharacterAbilities::CreateAbility(EAbilitiesEnum Ability)
{
	if (Ability == EAbilitiesEnum::VE_Levitate) {
		UE_LOG(LogTemp, Warning, TEXT("Adding Levitate ability to the character."));
		// Create a new Levitation ability
		UAbilityLevitate* LevitationAbility = NewObject<UAbilityLevitate>();
		LevitationAbility->Init(PlayerInputComponent, Cast<ACharacter>(GetOwner()), this);
		
		Abilities.Add(LevitationAbility);
	}
	else if (Ability == EAbilitiesEnum::VE_FloorBomb) {
		UE_LOG(LogTemp, Warning, TEXT("Adding Floor Bomb ability to the character."));
		// Create a new Floor Bomb ability
		UAbilityFloorBomb* FloorBombAbility = NewObject<UAbilityFloorBomb>();
		FloorBombAbility->Init(PlayerInputComponent, Cast<ACharacter>(GetOwner()), this);

		Abilities.Add(FloorBombAbility);
	}
	else if (Ability == EAbilitiesEnum::VE_ReverseRed) {
		UE_LOG(LogTemp, Warning, TEXT("Adding Reverse Red ability to the character."));
		// Create a new Reverse Red ability
		UAbilityReverseRed* ReverseRedAbility = NewObject<UAbilityReverseRed>();
		ReverseRedAbility->Init(PlayerInputComponent, Cast<ACharacter>(GetOwner()), this);

		Abilities.Add(ReverseRedAbility);
	}
	else if (Ability == EAbilitiesEnum::VE_ReverseBlue) {
		UE_LOG(LogTemp, Warning, TEXT("Adding Reverse Blue ability to the character."));
		// Create a new Reverse Blue ability
		UAbilityReverseBlue* ReverseBlueAbility = NewObject<UAbilityReverseBlue>();
		ReverseBlueAbility->Init(PlayerInputComponent, Cast<ACharacter>(GetOwner()), this);

		Abilities.Add(ReverseBlueAbility);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("WARNING: Tried adding an unknown ability to the player."));
	}
}


// Called every frame
void UCharacterAbilities::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	/*for (UAbility* Ability: Abilities)
	{
		if (Ability->NeedToTick()) {
			Ability->Tick(DeltaTime);
		}
	}*/

	if (bStandingInSunlight)
	{
		AddPower(PowerRecoveryPerSecond * DeltaTime);
	}
}

void UCharacterAbilities::SetupPlayerInputComponent(class UInputComponent* CurrentPlayerInputComponent)
{
	PlayerInputComponent = CurrentPlayerInputComponent;
}

void UCharacterAbilities::AddPower(float PowerDelta)
{
	//CurrentPower = FMath::Clamp(CurrentPower + PowerDelta, 0.0f, MaxPower);
	CurrentPower += PowerDelta;

	UMrdanjeGameInstance* GameInstance = Cast<UMrdanjeGameInstance>(GetOwner()->GetGameInstance());
	float TotalPower = GameInstance->GetPowerReserve() + CurrentPower;

	for (auto& Ability : Abilities)
	{
		if (!Ability->IsActive() && TotalPower > Ability->PowerNeededToActivate()) {
			Ability->SetActive(true);
		}
		else if (Ability->IsActive() && TotalPower < Ability->PowerNeededToActivate())
		{
			Ability->SetActive(false);
		}
	}
	

	if (CurrentPower < 0)
	{
		GameInstance->AddPower(CurrentPower);
		CurrentPower = 0;

		if (!bTutorializedPowerSystem)
		{
			GameInstance->PrintMessageToScreen("If you run out of battery power, the reserve will be used.", 180);
			bTutorializedPowerSystem = true;
		}
	}

	CurrentPower = FMath::Clamp(CurrentPower, 0.f, MaxPower);
	UE_LOG(LogTemp, Warning, TEXT("%2.2f power added! Current power: %2.2f"), PowerDelta, CurrentPower);
}

void UCharacterAbilities::SetStandingInSunlight(bool StandingInSunlight)
{
	bStandingInSunlight = StandingInSunlight;
}

float UCharacterAbilities::GetCurrentPower()
{
	return CurrentPower;
}