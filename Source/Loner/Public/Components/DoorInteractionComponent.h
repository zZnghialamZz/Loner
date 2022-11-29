// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DoorInteractionComponent.generated.h"

class UBoxComponent;
class ADoorkey;

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

	DECLARE_EVENT(UDoorInteractionComponent, FOpenedEvent)
	FOpenedEvent& OnOpenedEvent() { return OpenedEvent; }
	
	DECLARE_EVENT(UDoorInteractionComponent, FClosedEvent)
	FClosedEvent& OnClosedEvent() { return ClosedEvent; }

private:
	UPROPERTY(VisibleAnywhere, Category="InteractableDoor")
	EDoorState DoorState = EDoorState::Closed;
	
	UPROPERTY(EditAnywhere, Category="InteractableDoor")
	bool bUsedKey = false;
	
	UPROPERTY(EditAnywhere, Category="InteractableDoor")
	TObjectPtr<ADoorkey> DoorKey;
	
	UPROPERTY(EditAnywhere, Category="InteractableDoor")
	float PlayerGrabDistance = 150.0f;
	
	UPROPERTY(EditAnywhere, Category="InteractableDoor")
	float DoorFOV = 80.0f;
	
	UPROPERTY(EditAnywhere, Category="InteractableDoor")
	FRuntimeFloatCurve InteractionCurve;
	
	UPROPERTY(EditAnywhere, Category="InteractableDoor|Rotation")
	float TimeToRotate = 2.0f;
	
	UPROPERTY(EditAnywhere, Category="InteractableDoor|Rotation")
	FRotator DesiredRotation = FRotator::ZeroRotator;
	FRotator TargetRotation = FRotator::ZeroRotator;

	TObjectPtr<UStaticMeshComponent> DoorMesh;
	
	float CurrentInteractionTime = 0.0f;

	FOpenedEvent OpenedEvent;
	FClosedEvent ClosedEvent;
	
	// Methods
	// ---
	
	bool CanInteractWithDoor(const APawn* Target) const;
	bool DoesTargetFaceDoor(const APawn* Target) const;
	bool DoesTargetHasKey(const APawn* Target) const;
	
	void OnInteraction();
	
	void OpenRotateDoor(const float DeltaTime);
	void CloseRotateDoor(const float DeltaTime);
	void CalculateTargetRotation(const APawn* Target);

#if ENABLE_DRAW_DEBUG
	void DebugDraw();
#endif  
	
	static void OnDebugToggled(IConsoleVariable* Var);
};