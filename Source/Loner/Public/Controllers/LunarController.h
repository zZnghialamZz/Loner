// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LunarController.generated.h"

class UCameraComponent;

/**
 * 
 */
UCLASS()
class LONER_API ALunarController final : public APlayerController
{
	GENERATED_BODY()

public:
	
	ALunarController();
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
protected:
	
	UFUNCTION(BlueprintCallable)
	void MovePlayer(const float MoveForwardAxis, const float MoveRightAxis) const;

private:
	
	UPROPERTY(Transient)
	UCameraComponent* PlayerCamera;
};
