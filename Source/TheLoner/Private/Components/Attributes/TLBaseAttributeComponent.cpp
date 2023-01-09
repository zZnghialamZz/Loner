// @ The Loner Game, Nghia Lam.All Right Reserved

#include "Components/Attributes/TLBaseAttributeComponent.h"

UTLBaseAttributeComponent::UTLBaseAttributeComponent() : BaseValue(0.0f) {}

// Sets default values for this component's properties
UTLBaseAttributeComponent::UTLBaseAttributeComponent(const float BaseValue) : BaseValue(BaseValue)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

void UTLBaseAttributeComponent::AddModifier(const FTLAttributeStatsModifier& Modifier)
{
	IsDirty = true;
	ListModifiers.Add(Modifier);
	ListModifiers.Sort(
		[](const FTLAttributeStatsModifier& m1, const FTLAttributeStatsModifier& m2)
		{
			return m1.Order < m2.Order;
		});
}

void UTLBaseAttributeComponent::RemoveModifier(const FTLAttributeStatsModifier& Modifier)
{
	IsDirty = true;
	ListModifiers.RemoveSwap(Modifier, false);
}

float UTLBaseAttributeComponent::CalculateCurrentValue()
{
	float Result = BaseValue;

	float SumPercentAdd = 0;
	for (int i = 0; i < ListModifiers.Num(); i++)
	{
		switch (ListModifiers[i].Type)
		{
			case EStatModifierType::Flat:
			{
				Result += ListModifiers[i].Value;
				break;
			}
			case EStatModifierType::PercentAdd:
			{
				SumPercentAdd += ListModifiers[i].Value;

				// If we're at the end of the list OR the next modifer isn't of this type (We did the sort when adding modifier).
				if (i + 1 >= ListModifiers.Num() || ListModifiers[i + 1].Type != EStatModifierType::PercentAdd)
				{
					Result *= 1 + SumPercentAdd;
					SumPercentAdd = 0;
				}

				break;
			}
			case EStatModifierType::PercentMultiply:
			{
				Result *= (1 + ListModifiers[i].Value);
				break;
			}
			default: break;
		}
	}

	return Result;
}
