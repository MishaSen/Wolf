// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/WolfPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "Input/WolfInputComponent.h"

AWolfPlayerController::AWolfPlayerController()
{
}

void AWolfPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
}

void AWolfPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UpdateInputContext(EInputContext::OutOfCombat);
}

void AWolfPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UWolfInputComponent* WolfInputComponent = Cast<UWolfInputComponent>(InputComponent))
	{
		WolfInputComponent->BindAbilityActions(
			InputConfig,
			this,
			&ThisClass::AbilityInputTagPressed,
			&ThisClass::AbilityInputTagReleased,
			&ThisClass::AbilityInputTagHeld
		);
	}
}

void AWolfPlayerController::UpdateInputContext(const EInputContext NewInputContext)
{
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		GetLocalPlayer()))
	{
		Subsystem->ClearAllMappings();

		switch (NewInputContext)
		{
		case EInputContext::OutOfCombat:
			if (OutOfCombatContext)
			{
				Subsystem->AddMappingContext(OutOfCombatContext, 0);
			}
			break;
		case EInputContext::InCombatRT:
			if (InCombatRTContext)
			{
				Subsystem->AddMappingContext(InCombatRTContext, 0);
			}
			break;
		case EInputContext::InCombatTB:
			if (InCombatTBContext)
			{
				Subsystem->AddMappingContext(InCombatTBContext, 0);
			}
			break;

		default:
			break;
		}

		CurrentInputContext = NewInputContext;
	}
}

void AWolfPlayerController::AbilityInputTagPressed(const FGameplayTag InputTag)
{
}

void AWolfPlayerController::AbilityInputTagReleased(const FGameplayTag InputTag)
{
}

void AWolfPlayerController::AbilityInputTagHeld(const FGameplayTag InputTag)
{
}
