// @ The Loner Game, Nghia Lam.All Right Reserved

#include "Components/Attributes/TLHealthComponent.h"

#include "GameFramework/Actor.h"

void UTLHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	BaseValue = DefaultMaxHealth;
	CurrentHealth = GetMaxHealth();

	AActor* ComponentOwner = GetOwner();
	if (ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UTLHealthComponent::OnTakeDamageHandle);
	}
}

void UTLHealthComponent::OnTakeDamageHandle(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	CurrentHealth -= Damage;
}
