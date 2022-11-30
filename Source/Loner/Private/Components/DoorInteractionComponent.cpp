// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/DoorInteractionComponent.h"

#include "Actors/Doorkey.h"
#include "Actors/LunarCharacter.h"
#include "Utilities/LMathLib.h"
#include "Utilities/Logging.h"


static TAutoConsoleVariable<bool> CVarIsDebugDoor(
	TEXT("Loner.DoorInteractionComponent.Debug"),
	false,
	TEXT("Toggle the DoorInteractionComponent Debug Display."),
	ECVF_Default
);


// Sets default values for this component's properties
UDoorInteractionComponent::UDoorInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	CVarIsDebugDoor.AsVariable()->SetOnChangedCallback(FConsoleVariableDelegate::CreateStatic(&UDoorInteractionComponent::OnDebugToggled));
}


// Called when the game starts
void UDoorInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentInteractionTime = 0.0f;

	DoorMesh = GetOwner()->FindComponentByClass<UStaticMeshComponent>();
	if (GetWorld() && GetWorld()->GetFirstLocalPlayerFromController())
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

#if ENABLE_DRAW_DEBUG
	DebugDraw();
#endif
	
}


void UDoorInteractionComponent::OnInteraction()
{
	const APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (PlayerPawn && CanInteractWithDoor(PlayerPawn))
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


void UDoorInteractionComponent::OnDebugToggled(IConsoleVariable* Var)
{
	LONER_DISPLAY("DoorInteractionComponent Debug Toggle");
}


void UDoorInteractionComponent::OpenRotateDoor(const float DeltaTime)
{
	if (CurrentInteractionTime >= TimeToRotate)
	{
		CurrentInteractionTime = 0.0f;
		DoorState = EDoorState::Opened;
		DoorMesh->SetRelativeRotation(TargetRotation);
		OpenedEvent.Broadcast();
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
		ClosedEvent.Broadcast();
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
	FHitResult HitResult;
	FCollisionQueryParams CollisionQuery;
	CollisionQuery.AddIgnoredActor(Target);
	
	const FVector Start = Target->GetActorLocation();
	const FVector End = Start + Target->GetActorForwardVector() * PlayerGrabDistance;
	const bool HasHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, TraceChannelProperty, CollisionQuery);
	if (HasHit)
	{
		const AActor* HitActor = HitResult.GetActor();
		if (HitActor == GetOwner())
			return true;
	}
	return false;
}


bool UDoorInteractionComponent::DoesTargetHasKey(const APawn* Target) const
{
	if (bUsedKey == false) return true;

	const ALunarCharacter* Lunar = Cast<ALunarCharacter>(Target);
	if (Lunar)
		return DoorKey->Host == Lunar;

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

#if ENABLE_DRAW_DEBUG
void UDoorInteractionComponent::DebugDraw()
{
	if (CVarIsDebugDoor->GetBool())
	{
		const FVector DoorStateOffset(0.0f, 0.0f, LMathLib::GetMeters(2.5f));
		const FString DoorStateAsString = TEXT("Door State:") + UEnum::GetDisplayValueAsText(DoorState).ToString();
		DrawDebugString(GetWorld(), DoorStateOffset, DoorStateAsString, GetOwner(), FColor::Blue, 0.0f);
	}
}
#endif
