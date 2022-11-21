// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/LunarController.h"

#include "Actors/LunarCharacter.h"
#include "Utilities/Logging.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ALunarController::ALunarController()
{
}

void ALunarController::BeginPlay()
{
	Super::BeginPlay();
	
	const ALunarCharacter* Lunar = Cast<ALunarCharacter>(GetPawn());
	if (Lunar)
	{
		PlayerCamera = Lunar->FindComponentByClass<UCameraComponent>();
		if (PlayerCamera == nullptr)
			LONER_FATAL("Lunar Character need a camera setup !!!");
	}
}

void ALunarController::MovePlayer(const float MoveForwardAxis, const float MoveRightAxis) const
{
	const FVector InputVector = PlayerCamera->GetForwardVector() * MoveForwardAxis + PlayerCamera->GetRightVector() * MoveRightAxis;
	const ALunarCharacter* Lunar = Cast<ALunarCharacter>(GetPawn());
	UPawnMovementComponent* MovementComponent = Lunar->GetMovementComponent();
	
	if (MovementComponent)
		MovementComponent->AddInputVector(InputVector);
}
