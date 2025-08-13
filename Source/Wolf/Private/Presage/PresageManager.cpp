// Fill out your copyright notice in the Description page of Project Settings.


#include "Presage/PresageManager.h"

#include "ActorState.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

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

		OriginalCharacterStates.Add(NewState);
	}
}

