// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Doorkey.h"

#include "Actors/LunarCharacter.h"

// Sets default values
ADoorkey::ADoorkey()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComponent->SetMobility(EComponentMobility::Movable);
	SetRootComponent(StaticMeshComponent);

	StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ADoorkey::OnOverlapBegin);

	Host = nullptr;
}

void ADoorkey::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ALunarCharacter* Lunar = Cast<ALunarCharacter>(OtherActor);
	if (Lunar)
	{
		StaticMeshComponent->SetVisibility(false);
		Host = Lunar;
	}
}
