// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/InteractableDoor.h"

#include "Components/BoxComponent.h"
#include "Components/DoorInteractionComponent.h"

AInteractableDoor::AInteractableDoor()
{
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Default Root"));
	DefaultSceneRoot->SetupAttachment(RootComponent);
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComponent->SetupAttachment(DefaultSceneRoot);
	StaticMeshComponent->SetMobility(EComponentMobility::Movable);
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	BoxComponent->SetupAttachment(DefaultSceneRoot);
	BoxComponent->SetMobility(EComponentMobility::Stationary);
	
	DoorInteractionComponent = CreateDefaultSubobject<UDoorInteractionComponent>(TEXT("DoorInteraction"));
}
