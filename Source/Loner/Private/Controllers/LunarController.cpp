// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/LunarController.h"

#include "Actors/LunarCharacter.h"
#include "Utilities/Logging.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

ALunarController::ALunarController()
{
}

void ALunarController::BeginPlay()
{
	Super::BeginPlay();
	
	LunarCharacter = Cast<ALunarCharacter>(GetPawn());
	if (LunarCharacter)
	{
		PlayerCamera = LunarCharacter->FindComponentByClass<UCameraComponent>();
		if (PlayerCamera == nullptr)
			LONER_FATAL("Lunar Character need a camera setup !!!");
	}
}

void ALunarController::MovePlayer(const float MoveForwardAxis, const float MoveRightAxis) const
{
	if (LunarCharacter == nullptr) return;
	
	const FVector InputVector = PlayerCamera->GetForwardVector() * MoveForwardAxis + PlayerCamera->GetRightVector() * MoveRightAxis;
	UPawnMovementComponent* MovementComponent = LunarCharacter->GetMovementComponent();
	
	if (MovementComponent)
		MovementComponent->AddInputVector(InputVector);
}

void ALunarController::RotateCamera(const float RotateAxis) const
{
	if (LunarCharacter == nullptr) return;
	
	USpringArmComponent* SpringArmComponent = LunarCharacter->FindComponentByClass<USpringArmComponent>();
	if (SpringArmComponent)
		SpringArmComponent->AddWorldRotation(FRotator(0.0f, RotateAxis, 0.0f));
}
