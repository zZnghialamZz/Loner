// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/Interface.h"
#include "PickableObjects.generated.h"

UINTERFACE()
class UPickableObjectInterface : public UInterface
{
	GENERATED_BODY()
};

class IPickableObjectInterface
{
	GENERATED_BODY()

public:
	virtual void PickUp() {}
	virtual void DropDown() {}
};