// Fill out your copyright notice in the Description page of Project Settings.

#include "PositionReport.h"
#include "Gameframework/Actor.h"


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
    
    FString ObjectName = GetOwner()->GetName(); //GameOwner here is a pointer to AActor, we then look throug that pointer to get to the GetName method which returns an FString. This is then put into ObjectName
    FString ObjectPos = GetOwner()->GetTransform().GetLocation().ToString();
	UE_LOG(LogTemp, Warning, TEXT("%s is at %s"), *ObjectName, *ObjectPos); //a bit confusing but the * is not being used as a pointer here?
	
}


// Called every frame
void UPositionReport::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

