// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/DoorInteractionComponent.h"
#include "Engine/TriggerBox.h"

// Sets default values for this component's properties
UDoorInteractionComponent::UDoorInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UDoorInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	StartRotation = GetOwner()->GetActorRotation();
	FinalRotation = GetOwner()->GetActorRotation() + DesiredRotation;
	StartLocation = GetOwner()->GetActorLocation();
	FinalLocation = GetOwner()->GetActorLocation() + DesiredLocation;

	CurrentInteractionTime = 0.0f;

	if (TriggerArea && GetWorld() && GetWorld()->GetFirstLocalPlayerFromController())
	{
		UInputComponent* InputComponent = GetWorld()->GetFirstPlayerController()->InputComponent;
		if (InputComponent != nullptr)
			InputComponent->BindAction("Interact", IE_Pressed, this, &UDoorInteractionComponent::OnInteraction);
	}
}


// Called every frame
void UDoorInteractionComponent::TickComponent(const float DeltaTime, const ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	switch (DoorState)
	{
	case EDoorState::Opening:
		OpenRotateDoor(DeltaTime);
		break;
	case EDoorState::Closing:
		CloseRotateDoor(DeltaTime);
		break;
	default:
		break;
	}
}

void UDoorInteractionComponent::OnInteraction()
{
	const APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (PlayerPawn && TriggerArea->IsOverlappingActor(PlayerPawn))
	{
		switch (DoorState)
		{
		case EDoorState::Closed:
			DoorState = EDoorState::Opening;
			break;
		case EDoorState::Opened:
			DoorState = EDoorState::Closing;
			break;
		default:
			break;
		}
	}
}

void UDoorInteractionComponent::OpenRotateDoor(const float DeltaTime)
{
	if (CurrentInteractionTime >= TimeToRotate)
	{
		DoorState = EDoorState::Opened;
		GetOwner()->SetActorRotation(FinalRotation);
		CurrentInteractionTime = 0.0f;
		return;
	}

	CurrentInteractionTime += DeltaTime;
	const float TimeRatio = FMath::Clamp(CurrentInteractionTime / TimeToRotate, 0.0f, 1.0f);
	const float RotationAlpha = InteractionCurve.GetRichCurveConst()->Eval(TimeRatio);
	const FRotator CurrentRotation = FMath::Lerp(StartRotation, FinalRotation, RotationAlpha);
	GetOwner()->SetActorRotation(CurrentRotation);
}

void UDoorInteractionComponent::CloseRotateDoor(const float DeltaTime)
{
	if (CurrentInteractionTime >= TimeToRotate)
	{
		DoorState = EDoorState::Closed;
		GetOwner()->SetActorRotation(StartRotation);
		CurrentInteractionTime = 0.0f;
		return;
	}

	CurrentInteractionTime += DeltaTime;
	const float TimeRatio = FMath::Clamp(CurrentInteractionTime / TimeToRotate, 0.0f, 1.0f);
	const float RotationAlpha = InteractionCurve.GetRichCurveConst()->Eval(TimeRatio);
	const FRotator CurrentRotation = FMath::Lerp(FinalRotation, StartRotation, RotationAlpha);
	GetOwner()->SetActorRotation(CurrentRotation);
}
