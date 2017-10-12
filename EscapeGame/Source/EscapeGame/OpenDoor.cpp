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
    
    Owner = GetOwner();  //Find the owning actor
    //here we are sending a pawn into an actor //finds the actor that we are controlling...
    ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn(); //GetFirstPlayerController is the link between the pawn and the player's mind
	
}

void UOpenDoor::OpenDoor()
{
    //Create a rotator
    //-60.f //THIS IS ACTUALLY WHAT DETERMINES THE DOOR ROTATION....BUT IT'S GLOBAL NOT LOCAL TO OBJECT ROTATION!?
    //Set the door rotation
    Owner->SetActorRotation(FRotator(0.f, OpenAngle, 0.f));
}

void UOpenDoor::CloseDoor()
{
    //Set the door rotation
    Owner->SetActorRotation(FRotator(0.f, 0.f, 0.f));
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the Trigger Volume
    if (PressurePlate->IsOverlappingActor(ActorThatOpens))
    {
        OpenDoor(); //open the door
        LastDoorOpenTime = GetWorld()->GetTimeSeconds(); //store when last opened door
    }
    
  //check if it's time to close the door
    //if we do then call a CloseDoor method
    if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay)
    {
        CloseDoor();
    }
}

