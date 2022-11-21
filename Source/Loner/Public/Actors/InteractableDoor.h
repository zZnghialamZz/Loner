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
	TObjectPtr<USceneComponent> DefaultSceneRoot;
	
	UPROPERTY(EditDefaultsOnly, NoClear)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	
	UPROPERTY(EditDefaultsOnly, NoClear)
	TObjectPtr<UBoxComponent> BoxComponent;
	
	UPROPERTY(EditDefaultsOnly, NoClear)
	TObjectPtr<UDoorInteractionComponent> DoorInteractionComponent;
};
