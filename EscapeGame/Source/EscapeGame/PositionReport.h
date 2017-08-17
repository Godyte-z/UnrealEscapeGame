// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PositionReport.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEGAME_API UPositionReport : public UActorComponent //positionreport inherits from actor component
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPositionReport(); //declaration of the constructor

protected:
	// Called when the game starts
	virtual void BeginPlay() override; //declaration of begin play

public:	
	// Called every frame
    //declaration of a tick component
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	
};
