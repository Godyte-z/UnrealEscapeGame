// Copy right Goda Zalalyte 2017.

#include "OpenDoor.h"

#define OUT


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
    
    if(!PressurePlate)
    {
        UE_LOG(LogTemp, Error, TEXT("%s missing pressure plate"), *GetOwner()->GetName());
    }
}

void UOpenDoor::OpenDoor()
{
    //Create a rotator
    //-60.f //THIS IS ACTUALLY WHAT DETERMINES THE DOOR ROTATION....BUT IT'S GLOBAL NOT LOCAL TO OBJECT ROTATION!?
    //Set the door rotation
    //Owner->SetActorRotation(FRotator(0.f, OpenAngle, 0.f));
    OnOpenRequest.Broadcast();
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
    if (GetTotalMassOfActorsOnPlate() > 30.f) // TODO: make into a parameter
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

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
    float TotalMass = 0.f;
    
    //Find all the overlapping actors
    TArray<AActor*> OverlappingActors;//here we are saying give me a TArray of AActor pointers
    if(!PressurePlate){return TotalMass;}
    PressurePlate->GetOverlappingActors(OUT OverlappingActors);
    //Iterate through them adding their masses
    for (const auto* Actor : OverlappingActors)
    {
        TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
        UE_LOG(LogTemp, Warning, TEXT("%s on pressure plate"), *Actor->GetName() );
    }
    
    return TotalMass;
}









