// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/MapGameSubsystem.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void UMapGameSubsystem::CreateStageNameWidget(TSubclassOf<UUserWidget> StageNameWidgetClass)
{
	if (StageNameWidget == nullptr)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		StageNameWidget = CreateWidget<UUserWidget>(PlayerController, StageNameWidgetClass);
	}
}

void UMapGameSubsystem::DisplayStageNameWidget() const
{
	ensureMsgf(StageNameWidget, TEXT("Cannot create StageNameWidget!!"));
	StageNameWidget->AddToViewport();
}

FString UMapGameSubsystem::GetCurrentWorldName() const
{
	FString LevelName = GetWorld()->GetMapName();
	LevelName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);
	LevelName.RemoveFromStart(TEXT("LV_"));
	return FName::NameToDisplayString(LevelName, false);;
}
