// @ The Loner Game, Nghia Lam.All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/Attributes/TLBaseAttributeComponent.h"
#include "TLHealthComponent.generated.h"

/**
 *
 */
UCLASS()
class THELONER_API UTLHealthComponent : public UTLBaseAttributeComponent
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Health Component")
	FORCEINLINE float GetHealth()
	{
		return CurrentHealth;
	}

	UFUNCTION(BlueprintCallable, Category = "Health Component")
	FORCEINLINE float GetMaxHealth()
	{
		return GetValue();
	}

	UFUNCTION()
	void OnTakeDamageHandle(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

protected:

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health Component")
	float CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health Component", meta = (ClampMin = "0.0", ClampMax = "100"))
	float DefaultMaxHealth;
};
