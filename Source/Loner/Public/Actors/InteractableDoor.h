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
	UPROPERTY(EditDefaultsOnly, NoClear)
	USceneComponent* DefaultSceneRoot;
	
	UPROPERTY(EditDefaultsOnly, NoClear)
	UStaticMeshComponent* StaticMeshComponent;
	
	UPROPERTY(EditDefaultsOnly, NoClear)
	UBoxComponent* BoxComponent;
	
	UPROPERTY(EditDefaultsOnly, NoClear)
	UDoorInteractionComponent* DoorInteractionComponent;
};
