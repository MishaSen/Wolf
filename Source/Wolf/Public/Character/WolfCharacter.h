// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/WolfAbilitySystemComponent.h"
#include "AbilitySystem/WolfAttributeSet.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "WolfCharacter.generated.h"

UCLASS()
class WOLF_API AWolfCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AWolfCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UWolfAbilitySystemComponent* ASC;

	UPROPERTY()
	UWolfAttributeSet* AtSet;

	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	TSubclassOf<UGameplayEffect> DefaultAttributes;

	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;

	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void QueueAbility(FGameplayAbilitySpecHandle SpecHandle, float ScheduledTime);

protected:
	virtual void BeginPlay() override;
};