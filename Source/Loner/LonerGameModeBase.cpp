// Copyright Epic Games, Inc. All Rights Reserved.


#include "LonerGameModeBase.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void ALonerGameModeBase::StartPlay()
{
	Super::StartPlay();

	if (StageNameWidget == nullptr)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		StageNameWidget = CreateWidget<UUserWidget>(PlayerController, StageNameWidgetClass);
	}

	if (StageNameWidget)
	{
		StageNameWidget->AddToViewport();
	}
}
