// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

namespace LMathLib
{
	FORCEINLINE float AngleBetweenVectors(const FVector& A, const FVector& B)
	{
		const float Scaler = A.Size() + B.Size();
		const float DotProduct = FVector::DotProduct(A, B) / Scaler;
		const float AngleRadian = FMath::Acos(DotProduct);

		return FMath::RadiansToDegrees(AngleRadian);
	}
} // namespace LMathLib
