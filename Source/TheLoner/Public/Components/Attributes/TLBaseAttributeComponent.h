// @ The Loner Game, Nghia Lam.All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TLBaseAttributeComponent.generated.h"

UENUM()
enum class EStatModifierType : uint8
{
	Flat,
	PercentAdd,
	PercentMultiply,
};

USTRUCT(BlueprintType, Blueprintable)
struct FTLAttributeStatsModifier
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Attribute Stats Modifier")
	float Value;

	UPROPERTY(VisibleAnywhere, Category = "Attribute Stats Modifier")
	int Order;

	UPROPERTY(VisibleAnywhere, Category = "Attribute Stats Modifier")
	EStatModifierType Type;

	UPROPERTY(VisibleAnywhere, Category = "Attribute Stats Modifier")
	TObjectPtr<UObject> Source;

public:

	FTLAttributeStatsModifier() : Value(0.0f), Order(0), Type(EStatModifierType::Flat), Source(nullptr) {}
	FTLAttributeStatsModifier(float Value, EStatModifierType Type) : Value(Value), Order((int)Type), Type(Type), Source(nullptr) {}
	FTLAttributeStatsModifier(float Value, EStatModifierType Type, TObjectPtr<UObject> FromSource) : Value(Value), Order((int)Type), Type(Type), Source(FromSource) {}
	FTLAttributeStatsModifier(float Value, int Order, EStatModifierType Type, TObjectPtr<UObject> FromSource) : Value(Value), Order(Order), Type(Type), Source(FromSource) {}

	bool operator==(const FTLAttributeStatsModifier& Other) const
	{
		return Value == Other.Value && Order == Other.Order && Type == Other.Type && Source == Other.Source;
	}
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class THELONER_API UTLBaseAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	// Sets default values for this component's properties
	UTLBaseAttributeComponent();
	UTLBaseAttributeComponent(const float BaseValue);

public:

	UFUNCTION(BlueprintCallable, Category = "Attributes Component")
	FORCEINLINE float GetValue()
	{
		if (!IsDirty && LastBaseValue == BaseValue) return CurrentValue;

		IsDirty = false;
		LastBaseValue = BaseValue;
		CurrentValue = CalculateCurrentValue();

		return CurrentValue;
	}

	UFUNCTION(BlueprintCallable, Category = "Attributes Component")
	virtual void AddModifier(const FTLAttributeStatsModifier& Modifier);

	UFUNCTION(BlueprintCallable, Category = "Attributes Component")
	virtual void RemoveModifier(const FTLAttributeStatsModifier& Modifier);

	UFUNCTION(BlueprintCallable, Category = "Attributes Component")
	virtual float CalculateCurrentValue();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes Component")
	TArray<FTLAttributeStatsModifier> ListModifiers;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes Component")
	float BaseValue;

	float CurrentValue = 0.0f;
	float LastBaseValue = FLT_MIN;

	bool IsDirty = true;
};
