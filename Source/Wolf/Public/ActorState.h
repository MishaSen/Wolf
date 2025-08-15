// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorState.generated.h"

class AActor;
class UAnimSequence;
class UAnimMontage;

USTRUCT(BlueprintType)
struct FActorState
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActorState")
	AActor* ActorRef = ActorRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActorState")
	FVector Location = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActorState")
	FRotator Rotation = FRotator::ZeroRotator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActorState")
	FVector Velocity = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActorState")
	TEnumAsByte<EMovementMode> MovementMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActorState")
	uint8 CustomMovementMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActorState")
	UAnimSequence* CurrentSequence = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActorState")
	UAnimMontage* CurrentMontage = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActorState")
	float AnimationTime = 0.0f;
};