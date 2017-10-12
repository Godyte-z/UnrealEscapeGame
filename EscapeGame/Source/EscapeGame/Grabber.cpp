// Copy right Goda Zalalyte 2017.

#include "Grabber.h"
#include "DrawDebugHelpers.h"

#define OUT //THIS DOES NOTHING 


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Grabber ready for duty!"));
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;
	// Get player view point this tick
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint( OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);
    
    //Log out to test
   /* UE_LOG(LogTemp, Warning, TEXT("Location: %s, Rotation: %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString()); */
    
    FVector LineTraceEnd = PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * Reach); //drawing out a 50cm long line
    
    // Draw a red trace in the world to visualise
    
    DrawDebugLine(GetWorld(), PlayerViewPointLocation, LineTraceEnd, FColor(255,0,0), false, 0.f, 0.f, 10.f); //FColor(red,green,blue)
    
    // Ray-cast out to reach distance
    
    // See what we hit
}

