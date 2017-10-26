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
    
}


// Called when the game starts
void UGrabber::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("Grabber ready for duty!"));
    FindPhysicsHandleComponent();
    SetupInputComponent();
}


/// Look for attached Physics Handle
void UGrabber::FindPhysicsHandleComponent()
{
    PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
    if (PhysicsHandle == nullptr)
    { // if no Physics handle is found then log error
        UE_LOG(LogTemp, Error, TEXT("%s missing physics handle component"), *GetOwner()->GetName())
    }
}


///Look for attached Input Component (only appears at run time)
void UGrabber::SetupInputComponent()
{
    InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
    if (InputComponent)
    {
        InputComponent->BindAction("Grab",IE_Pressed, this, &UGrabber::Grab); //UGrabber is the class name here and Grab is the method
        InputComponent->BindAction("Grab",IE_Released, this, &UGrabber::GrabRelease);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("%s missing Input Component"), *GetOwner()->GetName())
    }
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    // If the physics handle is attached
    if (PhysicsHandle->GrabbedComponent) //if we have a grabbed component then....
    {
        // move the object that we're holding
        PhysicsHandle->SetTargetLocation(GetReachLineEnd());
    }
    
}


void UGrabber::Grab()
{
    /// LINE TRACE and see if we reach any actors with physics body collision channel set
    auto HitResult = GetFirstPhysicsBodyInReach();
    auto ComponentToGrab = HitResult.GetComponent(); //grabs the mesh in our case
    auto ActorHit = HitResult.GetActor();
    
    /// If we hit something then attach a physics handle
    if (ActorHit)
    {
    // attach physics handle
        PhysicsHandle->GrabComponent(ComponentToGrab, //what part of the object you want to grab
                                     NAME_None,       //no bones needed
                                     ComponentToGrab->GetOwner()->GetActorLocation(),
                                     true); // allow rotation
    }
}

void UGrabber::GrabRelease()
{
    PhysicsHandle->ReleaseComponent();
}


FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
    /// Set-up query parameters
    FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
    /// Line-trace (AKA Ray-cast) out to reach distance
    FHitResult Hit;
    GetWorld()->LineTraceSingleByObjectType(OUT Hit, GetReachLineStart(), GetReachLineEnd(), FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParameters);
    
    return Hit;
}


FVector UGrabber::GetReachLineStart() const // Get player view point
{
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);
    
    return PlayerViewPointLocation;
}


FVector UGrabber::GetReachLineEnd() const // Get player view point
{
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);
    
    return PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * Reach);
}

