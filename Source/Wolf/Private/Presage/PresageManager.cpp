// Fill out your copyright notice in the Description page of Project Settings.


#include "Presage/PresageManager.h"

#include "ActorState.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/PrimitiveComponent.h"

// Sets default values for this component's properties
UPresageManager::UPresageManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called every frame
void UPresageManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

// Called when the game starts
void UPresageManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

void UPresageManager::CaptureCharacterStates()
{
	OriginalCharacterStates.Empty();

	TArray<AActor*> Characters;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACharacter::StaticClass(), Characters);
	for (AActor* Actor : Characters)
	{
		ACharacter* Char = Cast<ACharacter>(Actor);
		if (!Char) continue;

		FActorState NewState;
		NewState.ActorRef = Char;
		NewState.Location = Char->GetActorLocation();
		NewState.Rotation = Char->GetActorRotation();
		NewState.Velocity = Char->GetVelocity();
		NewState.MovementMode = Char->GetCharacterMovement()->MovementMode;
		NewState.CustomMovementMode = Char->GetCharacterMovement()->CustomMovementMode;

		OriginalCharacterStates.Add(NewState);
	}
}

void UPresageManager::RevertCharacterStates()
{
	TArray<AActor*> Characters;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACharacter::StaticClass(), Characters);
	for (AActor* Actor : Characters)
	{
		ACharacter* Char = Cast<ACharacter>(Actor);
		if (!Char) continue;

		//Find saved state with matching ActorRef
		const FActorState* FoundState = OriginalCharacterStates.FindByPredicate([Char](const FActorState& State)
		{
			return State.ActorRef == Char;
		});
		if (!FoundState) continue;

		// Send Character back to saved original position
		Char->SetActorLocationAndRotation(
			FoundState->Location,
			FoundState->Rotation,
			false,
			nullptr,
			ETeleportType::TeleportPhysics);

		// Set movement velocity and mode
		if (UCharacterMovementComponent* MoveComp = Char->GetCharacterMovement())
		{
			MoveComp->SetMovementMode(FoundState->MovementMode, FoundState->CustomMovementMode);
			MoveComp->Velocity = FoundState->Velocity;
			MoveComp->UpdateComponentVelocity();
		}

		// If Character simulates physics, set physics velocity
		if (UPrimitiveComponent* PrimComp = Cast<UPrimitiveComponent>(Char->GetRootComponent()))
		{
			if (PrimComp->IsSimulatingPhysics())
			{
				PrimComp->SetPhysicsLinearVelocity(FoundState->Velocity);
			}
		}
	}
}
