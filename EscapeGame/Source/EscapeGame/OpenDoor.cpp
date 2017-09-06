// Copy right Goda Zalalyte 2017.

#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
    
    //here we are sending a pawn into an actor //finds the actor that we are controlling...
    ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn(); //GetFirstPlayerController is the link between the pawn and the player's mind
	
}

void UOpenDoor::OpenDoor()
{
    //Find the owning actor
    AActor* Owner = GetOwner(); //GameOwner here is a pointer to AActor
    
    //Create a rotator
    FRotator NewRotation = FRotator(0.f, -60.f, 0.f);
    
    //Set the door rotation
    Owner->SetActorRotation(NewRotation);
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the Trigger Volume
    if (PressurePlate->IsOverlappingActor(ActorThatOpens))
    {
        OpenDoor();
    }
    // If ActorThatOpens is in the volume
}

