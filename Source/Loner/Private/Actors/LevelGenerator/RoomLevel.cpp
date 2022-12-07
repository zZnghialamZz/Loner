// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/LevelGenerator/RoomLevel.h"

#include "Engine/LevelStreaming.h"
#include "Engine/LevelStreamingDynamic.h"
#include "Kismet/GameplayStatics.h"
#include "Utilities/Logging.h"

ARoomLevel::ARoomLevel()
{
	Instance = nullptr;
}

void ARoomLevel::Instantiate(UWorld* World)
{
	if (Instance != nullptr) return;

	bool IsSucceed = false;
	const FQuat Rotation = FQuat::Identity;
	const FVector Position(0.0f, 0.0f, 0.0f);
	Instance = ULevelStreamingDynamic::LoadLevelInstance(World, this->GetName(), Position, Rotation.Rotator(), IsSucceed);
	if (!IsSucceed)
		LONER_LVGENERATOR_ERROR("Cannot Instantiate Level %s", *this->GetName());
}

void ARoomLevel::Remove(UWorld* World)
{
	if (Instance == nullptr) return;

	FString LevelName = Instance->GetWorldAssetPackageName();
	FLatentActionInfo LatentInfo;
	UGameplayStatics::UnloadStreamLevel(World, *LevelName, LatentInfo, false);
}
