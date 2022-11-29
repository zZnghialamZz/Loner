// Copyright Epic Games, Inc. All Rights Reserved.


#include "LonerGameModeBase.h"

#include "Subsystems/MapGameSubsystem.h"

void ALonerGameModeBase::StartPlay()
{
	Super::StartPlay();

	UMapGameSubsystem* MapGameSubsystem = GetGameInstance()->GetSubsystem<UMapGameSubsystem>();
	if (MapGameSubsystem)
	{
		MapGameSubsystem->CreateStageNameWidget(StageNameWidgetClass);
		MapGameSubsystem->DisplayStageNameWidget();
	}
}
