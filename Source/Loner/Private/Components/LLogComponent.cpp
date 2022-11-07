// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/LLogComponent.h"
#include "Loner/Loner.h"


// Sets default values for this component's properties
ULLogComponent::ULLogComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	UE_LOG(LonerGame, Display, TEXT("Log Component Start!!"));
}


// Called when the game starts
void ULLogComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	UE_LOG(LonerGame, Warning, TEXT("Log Component Begin!!"));
}


// Called every frame
void ULLogComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

