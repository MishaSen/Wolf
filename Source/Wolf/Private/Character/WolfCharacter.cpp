// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/WolfCharacter.h"

#include "Presage/PresageAbilityRequest.h"
#include "Presage/PresageSubsystem.h"

AWolfCharacter::AWolfCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	ASC = CreateDefaultSubobject<UWolfAbilitySystemComponent>(TEXT("Ability System Component"));
	AtSet = CreateDefaultSubobject<UWolfAttributeSet>(TEXT("Attribute Set"));
}

UAbilitySystemComponent* AWolfCharacter::GetAbilitySystemComponent() const
{
	return ASC;
}

FGameplayAbilitySpecHandle AWolfCharacter::GetAbilitySpecHandle(const TSubclassOf<UGameplayAbility>& AbilityClass) const
{
	if (GrantedAbilityHandles.Contains(AbilityClass))
	{
		return GrantedAbilityHandles[AbilityClass];
	}
	return FGameplayAbilitySpecHandle();
}

void AWolfCharacter::QueueAbility(const FGameplayAbilitySpecHandle SpecHandle, const float ScheduledTime,
                                  const FGameplayTag AbilityTag)
{
	if (!ASC) return;

	const FGameplayAbilitySpec* Spec = ASC->FindAbilitySpecFromHandle(SpecHandle);
	if (!Spec || !Spec->Ability)
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid Ability or Spec Handle"));
		return;
	}
	const FPresageAbilityRequest Request(ASC, SpecHandle, ScheduledTime, AbilityTag);

	if (UWorld* World = GetWorld())
	{
		if (UPresageSubsystem* Presage = UPresageSubsystem::Get(World))
		{
			Presage->QueueAbilityRequest(Request);
			UE_LOG(LogTemp, Log, TEXT("Queued ability at %s at time %f"),
			       *Spec->Ability->GetClass()->GetName(),
			       ScheduledTime)
		}
	}
}

void AWolfCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (ASC && DefaultAttributes)
	{
		FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(DefaultAttributes, 1, EffectContext);
		if (SpecHandle.IsValid())
		{
			ASC->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), ASC);
		}
	}
}

void AWolfCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWolfCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AWolfCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (ASC)
	{
		if (HasAuthority())
		{
			ASC->AddCharacterAbilities(DefaultAbilities, GrantedAbilityHandles);
		}
	}
}
