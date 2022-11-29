// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickableObjects.h"
#include "GameFramework/Actor.h"
#include "Doorkey.generated.h"

class ALunarCharacter;

UCLASS()
class LONER_API ADoorkey : public AActor, public IPickableObjectInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoorkey();

	/** called when something enters the sphere component */
    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void PickUp() override;
	virtual void DropDown() override;

	UPROPERTY(Transient)
	TObjectPtr<ALunarCharacter> Host;
	
protected:
	UPROPERTY(EditDefaultsOnly, NoClear)
    TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
};
