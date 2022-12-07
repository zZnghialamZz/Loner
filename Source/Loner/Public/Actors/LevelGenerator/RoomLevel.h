// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "RoomLevel.generated.h"

/**
 * 
 */
UCLASS()
class LONER_API ARoomLevel final : public ALevelScriptActor
{
	GENERATED_BODY()

public:
	ARoomLevel();

	UFUNCTION()
	void Instantiate(UWorld* World);
	
	UFUNCTION()
	void Remove(UWorld* World);

private:
	UPROPERTY()
	ULevelStreaming* Instance;
};
