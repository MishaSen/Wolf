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
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintPure, Category = "Abilities")
	FGameplayAbilitySpecHandle GetAbilitySpecHandle(const TSubclassOf<UGameplayAbility>& AbilityClass) const;

	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void QueueAbility(const FGameplayAbilitySpecHandle SpecHandle,
	                  const float ScheduledTime,
	                  const FGameplayTag AbilityTag);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PossessedBy(AController* NewController) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UWolfAbilitySystemComponent* ASC;

	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	TSubclassOf<UGameplayEffect> DefaultAttributes;

private:
	UPROPERTY(EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;

	UPROPERTY()
	UWolfAttributeSet* AtSet;

	UPROPERTY()
	TMap<TSubclassOf<UGameplayAbility>, FGameplayAbilitySpecHandle> GrantedAbilityHandles;
};