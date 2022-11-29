// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MapGameSubsystem.generated.h"

UCLASS()
class LONER_API UMapGameSubsystem final : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	void CreateStageNameWidget(TSubclassOf<UUserWidget> StageNameWidgetClass);
	void DisplayStageNameWidget() const;

protected:
	UFUNCTION(BlueprintCallable)
	FString GetCurrentWorldName() const;

private:
	TObjectPtr<UUserWidget> StageNameWidget;
};
