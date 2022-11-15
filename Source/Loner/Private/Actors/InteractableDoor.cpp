// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/InteractableDoor.h"

#include "Components/BoxComponent.h"
#include "Components/DoorInteractionComponent.h"

AInteractableDoor::AInteractableDoor()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComponent->SetupAttachment(RootComponent);
	StaticMeshComponent->SetMobility(EComponentMobility::Movable);
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	BoxComponent->SetupAttachment(StaticMeshComponent);
	BoxComponent->SetMobility(EComponentMobility::Stationary);
	
	DoorInteractionComponent = CreateDefaultSubobject<UDoorInteractionComponent>(TEXT("DoorInteraction"));
}
