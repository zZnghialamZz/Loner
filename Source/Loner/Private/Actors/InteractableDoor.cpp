// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/InteractableDoor.h"
#include "Components/DoorInteractionComponent.h"

AInteractableDoor::AInteractableDoor()
{
	DoorInteractionComponent = CreateDefaultSubobject<UDoorInteractionComponent>(TEXT("DoorInteraction"));
}
