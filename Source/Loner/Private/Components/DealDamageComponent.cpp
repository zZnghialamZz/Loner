// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/DealDamageComponent.h"

#include "Components/CapsuleComponent.h"
#include "Actors/LunarCharacter.h"
#include "Utilities/Logging.h"

// Sets default values for this component's properties
UDealDamageComponent::UDealDamageComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	TriggerCapsule = CreateDefaultSubobject<UCapsuleComponent>("Trigger Capsule");
	TriggerCapsule->OnComponentBeginOverlap.AddDynamic(this, &UDealDamageComponent::OnOverlapBegin);
	TriggerCapsule->OnComponentEndOverlap.AddDynamic(this, &UDealDamageComponent::OnOverlapEnd);
}


// Called when the game starts
void UDealDamageComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UDealDamageComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == GetOwner()) return;

	LONER_WARNING("UDealDamageComponent::OnOverlapBegin");

	ALunarCharacter* Player = Cast<ALunarCharacter>(OtherActor);
	if (Player)
	{
		TSubclassOf<UDamageType> const ValidDamageTypeClass = TSubclassOf<UDamageType>(UDamageType::StaticClass());
		FDamageEvent DamageEvent(ValidDamageTypeClass);

		Player->TakeDamage(BaseDamage, DamageEvent, nullptr, GetOwner());
	}
}

void UDealDamageComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	LONER_WARNING("UDealDamageComponent::OnOverlapEnd");
}


