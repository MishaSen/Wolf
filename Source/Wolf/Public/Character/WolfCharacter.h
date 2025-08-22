// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/WolfAbilitySystemComponent.h"
#include "AbilitySystem/WolfAttributeSet.h"
#include "GameFramework/Character.h"
#include "WolfCharacter.generated.h"

UCLASS()
class WOLF_API AWolfCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWolfCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UWolfAbilitySystemComponent* ASC;

	UPROPERTY()
	UWolfAttributeSet* AtSet;
};
