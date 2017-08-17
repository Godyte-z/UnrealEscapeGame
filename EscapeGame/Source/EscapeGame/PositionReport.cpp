// Fill out your copyright notice in the Description page of Project Settings.

#include "PositionReport.h"


// Sets default values for this component's properties
UPositionReport::UPositionReport() //this is the constructor
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true; //things that tick happen every frame

	// ...
}


// Called when the game starts
void UPositionReport::BeginPlay()
{
	Super::BeginPlay(); //super is just saying run anything that's at the top of the inheritance stream first before running anything that down below here

	// ...
	
}


// Called every frame
void UPositionReport::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

