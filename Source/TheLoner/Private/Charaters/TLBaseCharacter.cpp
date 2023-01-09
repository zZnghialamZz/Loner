// @ The Loner Game, Nghia Lam.All Right Reserved

#include "Charaters/TLBaseCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Components/Attributes/TLHealthComponent.h"

// Sets default values
ATLBaseCharacter::ATLBaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	HealthComponent = CreateDefaultSubobject<UTLHealthComponent>("Health Attribute");

	UCharacterMovementComponent* MovementComponent = Cast<UCharacterMovementComponent>(ACharacter::GetMovementComponent());
	if (MovementComponent)
	{
		bUseControllerRotationYaw = false;

		MovementComponent->bOrientRotationToMovement = true;
		MovementComponent->bConstrainToPlane = true;
		MovementComponent->bSnapToPlaneAtStart = true;
		MovementComponent->bUseControllerDesiredRotation = false;

		SpringArmComponent->bInheritYaw = false;
	}
}

// Called when the game starts or when spawned
void ATLBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(HealthComponent);
}

void ATLBaseCharacter::MoveForward(const float Amount)
{
	AddMovementInput(CameraComponent->GetForwardVector(), Amount);
}

void ATLBaseCharacter::MoveRight(const float Amount)
{
	AddMovementInput(CameraComponent->GetRightVector(), Amount);
}

// Called every frame
void ATLBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATLBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ATLBaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATLBaseCharacter::MoveRight);
}
