// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelGenerator.generated.h"

class ARoomLevel;

UENUM()
enum class ELevelGeneratorState : uint8
{
	None          UMETA(DisplayName="None"),
	Loading       UMETA(DisplayName="Loading"),
	Unloading     UMETA(DisplayName="Unloading"),
	Generating    UMETA(DisplayName="Generating"),
	Initializing  UMETA(DisplayName="Initialzing")
};

UCLASS()
class LONER_API ALevelGenerator final : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALevelGenerator();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaSeconds) override;

public:
	UFUNCTION(BlueprintCallable, Category = "Level Generator")
	void Init();
	
	UFUNCTION(BlueprintCallable, Category = "Level Generator")
	void GenerateLevel();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Generator")
	bool bGenerateAtBeginPlay = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Generator")
	TObjectPtr<ARoomLevel> RootRoomLevel;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Generator")
	TArray<ARoomLevel*> RoomLevelList;

private:
	UFUNCTION()
	void SetState(const ELevelGeneratorState NewState);
	
	UFUNCTION()
	void OnStateBegin(const ELevelGeneratorState State);
	
	UFUNCTION()
	void OnStateTick(const ELevelGeneratorState State);
	
	UFUNCTION()
	void OnStateEnd(const ELevelGeneratorState State);
	
	UFUNCTION()
	void LoadAllRooms();
	
	UFUNCTION()
	void UnLoadAllRooms();
	
	UPROPERTY(VisibleAnywhere, Category = "Level Generator")
	uint32 Seed = 123456789;

	bool IsInit = false;
	
	FRandomStream RandomStream;
	ELevelGeneratorState CurrentState = ELevelGeneratorState::None;
};
