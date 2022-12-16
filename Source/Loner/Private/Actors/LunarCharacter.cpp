// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/LunarCharacter.h"

#include "Utilities/Logging.h"
#include "Components/HealthComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ALunarCharacter::ALunarCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	UCharacterMovementComponent* MovementComponent = Cast<UCharacterMovementComponent>(ACharacter::GetMovementComponent());
	if (MovementComponent)
	{
		MovementComponent->bOrientRotationToMovement = true;
		MovementComponent->bConstrainToPlane = true;
		MovementComponent->bSnapToPlaneAtStart = true;
		MovementComponent->bUseControllerDesiredRotation  = false;
	}

	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");
}

// Called when the game starts or when spawned
void ALunarCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ALunarCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ALunarCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float ALunarCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	if (HealthComponent)
	{
		HealthComponent->TakeDamage(Damage);
		LONER_DISPLAY("ALunarCharacter::TakeDamage %.2f", __FILE__, Damage);

		if (HealthComponent->IsDead())
		{
			OnDead();
		}
	}

	return Damage;
}

void ALunarCharacter::OnDead()
{
	APlayerController* PlayerController = GetController<APlayerController>();
	if (PlayerController)
	{
		PlayerController->RestartLevel();
	}
}

