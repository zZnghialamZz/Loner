// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/LevelGenerator/LevelGenerator.h"

#include "Actors/LevelGenerator/RoomLevel.h"
#include "Utilities/Logging.h"

// Sets default values
ALevelGenerator::ALevelGenerator()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	if (!IsInit)
		Init();
}

// Called when the game starts or when spawned
void ALevelGenerator::BeginPlay()
{
	Super::BeginPlay();

	if (bGenerateAtBeginPlay)
		SetState(ELevelGeneratorState::Generating);
}

void ALevelGenerator::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	UnLoadAllRooms();
}

void ALevelGenerator::Tick(const float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	OnStateTick(CurrentState);
}

void ALevelGenerator::Init()
{
	IsInit = true;
	SetState(ELevelGeneratorState::Initializing);
}

void ALevelGenerator::GenerateLevel()
{
	RandomStream.GenerateNewSeed();
	Seed = RandomStream.GetCurrentSeed();

	// TODO(Nghia Lam): Getting the rooms from graphs data here. Try finding out the way to work with seed.
	SetState(ELevelGeneratorState::Loading);
}

void ALevelGenerator::SetState(const ELevelGeneratorState NewState)
{
	OnStateEnd(CurrentState);
	CurrentState = NewState;
	OnStateBegin(CurrentState);
}

void ALevelGenerator::OnStateBegin(const ELevelGeneratorState State)
{
	switch (State)
	{
	case ELevelGeneratorState::Loading:
		LONER_LVGENERATOR_DISPLAY("Begin loading all levels ...")
		LoadAllRooms();
		break;
	case ELevelGeneratorState::Unloading:
		LONER_LVGENERATOR_DISPLAY("Begin unloading all levels ...")
		UnLoadAllRooms();
		break;
	case ELevelGeneratorState::Generating:
		LONER_LVGENERATOR_DISPLAY("Begin generating this current map ...")
		GenerateLevel();
		break;
	case ELevelGeneratorState::Initializing:
		LONER_LVGENERATOR_DISPLAY("Begin initializing the Level Generator ...")
		break;
	default:
		break;
	}
}

void ALevelGenerator::OnStateTick(const ELevelGeneratorState State)
{
	switch (State)
	{
	case ELevelGeneratorState::Loading:
		break;
	case ELevelGeneratorState::Unloading:
		break;
	case ELevelGeneratorState::Generating:
		break;
	case ELevelGeneratorState::Initializing:
		break;
	default:
		break;
	}
}

void ALevelGenerator::OnStateEnd(const ELevelGeneratorState State)
{
	switch (State)
	{
	case ELevelGeneratorState::Loading:
		LONER_LVGENERATOR_DISPLAY("Finish loading all levels !!")
		break;
	case ELevelGeneratorState::Unloading:
		LONER_LVGENERATOR_DISPLAY("Finish unloading all levels !!")
		break;
	case ELevelGeneratorState::Generating:
		LONER_LVGENERATOR_DISPLAY("Finish generating this map !!")
		break;
	case ELevelGeneratorState::Initializing:
		LONER_LVGENERATOR_DISPLAY("Finish initialzing the Level Generator !!")
		break;
	default:
		break;
	}
}

void ALevelGenerator::LoadAllRooms()
{
	for (int i = 0; i < RoomLevelList.Num(); i++)
	{
		RoomLevelList[i]->Instantiate(GetWorld());
	}
}

void ALevelGenerator::UnLoadAllRooms()
{
	for (int i = 0; i < RoomLevelList.Num(); i++)
	{
		RoomLevelList[i]->Remove(GetWorld());
	}
}
