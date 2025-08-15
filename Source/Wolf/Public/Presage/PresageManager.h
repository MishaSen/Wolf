// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PresageManager.generated.h"


struct FActorState;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WOLF_API UPresageManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPresageManager();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "Presage")
	TArray<FActorState> OriginalCharacterStates;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Presage", meta=(ClampMin = "0.0", UIMin = "0.0"))
	float FlowTime = 3.f;

	UFUNCTION(BlueprintCallable, Category = "Presage")
	void CaptureCharacterStates();

	UFUNCTION(BlueprintCallable, Category = "Presage")
	void RevertCharacterStates();
};
