// @ The Loner Game, Nghia Lam.All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TLBaseCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UTLHealthComponent;

UCLASS()
class THELONER_API ATLBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	// Sets default values for this character's properties
	ATLBaseCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(EditAnywhere, Category = "Components")
	TObjectPtr<UTLHealthComponent> HealthComponent;

	void MoveForward(const float Amount);
	void MoveRight(const float Amount);
};
