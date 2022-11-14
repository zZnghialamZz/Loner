// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DoorInteractionComponent.generated.h"

class ATriggerBox;

UENUM()
enum class EDoorState
{
	Opened,
	Opening,
	Closed,
	Closing
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LONER_API UDoorInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDoorInteractionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere, Category="InteractableDoor")
	EDoorState DoorState = EDoorState::Closed;

	UPROPERTY(EditAnywhere, Category="InteractableDoor")
	ATriggerBox* TriggerArea;
	
	UPROPERTY(EditAnywhere, Category="InteractableDoor")
	FRuntimeFloatCurve InteractionCurve;
	
	UPROPERTY(EditAnywhere, Category="InteractableDoor|Rotation")
	float TimeToRotate = 2.0f;
	
	UPROPERTY(EditAnywhere, Category="InteractableDoor|Rotation")
	FRotator DesiredRotation = FRotator::ZeroRotator;
	FRotator StartRotation = FRotator::ZeroRotator;
	FRotator FinalRotation = FRotator::ZeroRotator;

	// TODO(Nghia Lam): Support location changing
	UPROPERTY(EditAnywhere, Category="InteractableDoor|Moving")
	float TimeToMove = 2.0f;
	
	UPROPERTY(EditAnywhere, Category="InteractableDoor|Moving")
	FVector DesiredLocation = FVector::ZeroVector;
	FVector StartLocation = FVector::ZeroVector;
	FVector FinalLocation = FVector::ZeroVector;

	float CurrentInteractionTime = 0.0f;

	void OnInteraction();
	void OpenRotateDoor(const float DeltaTime);
	void CloseRotateDoor(const float DeltaTime);
};