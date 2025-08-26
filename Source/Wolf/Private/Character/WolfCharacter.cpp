// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/WolfCharacter.h"

// Sets default values
AWolfCharacter::AWolfCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ASC = CreateDefaultSubobject<UWolfAbilitySystemComponent>(TEXT("Ability System Component"));
	AtSet = CreateDefaultSubobject<UWolfAttributeSet>(TEXT("Attribute Set"));

	/* Multiplayer would need to replicate ASC. Replication Mode either Mixed or Full.
	 * 
	 * ASC = CreateDefaultSubobject<UWolfAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	 * ASC->SetIsReplicated(true);
	 * ASC->SetReplicationMode(EGameplayEffect ReplciationMode::Mixed);
	 */
}

// Called when the game starts or when spawned
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

	if (HasAuthority() && ASC)
	{
		for (TSubclassOf<UGameplayAbility> AbilityClass : DefaultAbilities)
		{
			ASC->GiveAbility(FGameplayAbilitySpec(AbilityClass, 1, 0, this));
		}
	}

	/* Input Binding (maybe future use)
	 *
	 * FGameplayAbilityInputBinds(
	 * "Confirm",
	 * "Cancel",
	 * "EAbilityInputID",
	 * static_cast<int32>(EAbilityInputID::Confirm),
	 * static_cast<int32(EAbilityInputID::Cancel)));
	 */
}

// Called every frame
void AWolfCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AWolfCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

UAbilitySystemComponent* AWolfCharacter::GetAbilitySystemComponent() const
{
	return ASC;
}
