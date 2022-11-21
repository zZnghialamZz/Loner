// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/DoorInteractionComponent.h"

#include "Actors/Doorkey.h"
#include "Actors/LunarCharacter.h"
#include "Components/BoxComponent.h"
#include "Utilities/LMathLib.h"

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

	CurrentInteractionTime = 0.0f;

	DoorMesh = GetOwner()->FindComponentByClass<UStaticMeshComponent>();
	TriggerArea = GetOwner()->FindComponentByClass<UBoxComponent>();
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
	if (PlayerPawn && TriggerArea->IsOverlappingActor(PlayerPawn) && CanInteractWithDoor(PlayerPawn))
	{
		switch (DoorState)
		{
		case EDoorState::Closed:
			CalculateTargetRotation(PlayerPawn);
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
		CurrentInteractionTime = 0.0f;
		DoorState = EDoorState::Opened;
		DoorMesh->SetRelativeRotation(TargetRotation);
		return;
	}

	CurrentInteractionTime += DeltaTime;
	const float TimeRatio = FMath::Clamp(CurrentInteractionTime / TimeToRotate, 0.0f, 1.0f);
	const float RotationAlpha = InteractionCurve.GetRichCurveConst()->Eval(TimeRatio);
	const FRotator CurrentRotation = FMath::Lerp(FRotator::ZeroRotator, TargetRotation, RotationAlpha);
	DoorMesh->SetRelativeRotation(CurrentRotation);
}

void UDoorInteractionComponent::CloseRotateDoor(const float DeltaTime)
{
	if (CurrentInteractionTime >= TimeToRotate)
	{
		CurrentInteractionTime = 0.0f;
		DoorState = EDoorState::Closed;
		DoorMesh->SetRelativeRotation(FRotator::ZeroRotator);
		return;
	}

	CurrentInteractionTime += DeltaTime;
	const float TimeRatio = FMath::Clamp(CurrentInteractionTime / TimeToRotate, 0.0f, 1.0f);
	const float RotationAlpha = InteractionCurve.GetRichCurveConst()->Eval(TimeRatio);
	const FRotator CurrentRotation = FMath::Lerp(TargetRotation, FRotator::ZeroRotator, RotationAlpha);
	DoorMesh->SetRelativeRotation(CurrentRotation);
}

bool UDoorInteractionComponent::CanInteractWithDoor(const APawn* Target) const
{
	return DoesTargetFaceDoor(Target) && DoesTargetHasKey(Target);
}

bool UDoorInteractionComponent::DoesTargetFaceDoor(const APawn* Target) const
{
	// TODO(Nghia Lam): Consider change this to raycast method?
	const FVector TargetForwardVector = Target->GetActorForwardVector();
	const FVector DirectionToDoor = GetOwner()->GetActorLocation() - Target->GetActorLocation();

	const float Degree = LMathLib::AngleBetweenVectors(TargetForwardVector, DirectionToDoor);
	return Degree <= PlayerFOV;
}

bool UDoorInteractionComponent::DoesTargetHasKey(const APawn* Target) const
{
	if (bUsedKey == false) return true;

	const ALunarCharacter* Lunar = Cast<ALunarCharacter>(Target);
	if (Lunar)
	{
		return DoorKey->Host == Lunar;
	}

	return false;
}

void UDoorInteractionComponent::CalculateTargetRotation(const APawn* Target)
{
	// Check if the door can see the player.
	const FVector DoorForwardVector = GetOwner()->GetActorRightVector();
	const FVector DirectionToPlayer = Target->GetActorLocation() - GetOwner()->GetActorLocation();
	
	const float Degree = LMathLib::AngleBetweenVectors(DoorForwardVector, DirectionToPlayer);
	if (Degree <= DoorFOV)
		TargetRotation = DesiredRotation;
	else
		TargetRotation = DesiredRotation * -1;
}
