// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableDoor.generated.h"

class UBoxComponent;
class UDoorInteractionComponent;

UCLASS()
class LONER_API AInteractableDoor final : public AActor
{
	GENERATED_BODY()

public:
	AInteractableDoor();

protected:
	UPROPERTY(EditAnywhere, NoClear)
	UStaticMeshComponent* StaticMeshComponent;
	
	UPROPERTY(EditAnywhere, NoClear)
	UBoxComponent* BoxComponent;
	
	UPROPERTY(EditAnywhere, NoClear)
	UDoorInteractionComponent* DoorInteractionComponent;
};
