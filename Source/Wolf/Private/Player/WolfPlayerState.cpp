// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/WolfPlayerState.h"

#include "AbilitySystem/WolfAbilitySystemComponent.h"
#include "AbilitySystem/WolfAttributeSet.h"

AWolfPlayerState::AWolfPlayerState()
{
	ASC = CreateDefaultSubobject<UWolfAbilitySystemComponent>(TEXT("Ability System Component"));
	ASC->SetIsReplicated(true);
	ASC->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	ASet = CreateDefaultSubobject<UWolfAttributeSet>(TEXT("AttributeSet"));

	SetNetUpdateFrequency(100.f);
}

UAbilitySystemComponent* AWolfPlayerState::GetAbilitySystemComponent() const
{
	return ASC;
}
