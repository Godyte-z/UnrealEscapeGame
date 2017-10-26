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
    if (PhysicsHandle)
    {
        // Physics handle is found
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("%s missing physics handle component"), *GetOwner()->GetName())
    }
}


///Look for attached Input Component (only appears at run time)
void UGrabber::SetupInputComponent()
{
    InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
    if (InputComponent)
    {
        UE_LOG(LogTemp, Warning, TEXT("Input Component found"), *GetOwner()->GetName())
        //Bind the input action
        InputComponent->BindAction("Grab",IE_Pressed, this, &UGrabber::Grab); //UGrabber is the class name here and Grab is the method
        InputComponent->BindAction("Grab",IE_Released, this, &UGrabber::GrabRelease);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("%s missing Input Component"), *GetOwner()->GetName())
    }
}


void UGrabber::Grab()
{
    UE_LOG(LogTemp, Warning, TEXT("Grab pressed"))
    
    /// LINE TRACE and see if we reach any actors with physics body collision channel set
    auto HitResult = GetFirstPhysicsBodyInReach();
    auto ComponentToGrab = HitResult.GetComponent();
    auto ActorHit = HitResult.GetActor();
    
    /// If we hit something then attach a physics handle
    if (ActorHit)
    {
    // attach physics handle
        PhysicsHandle->GrabComponent(ComponentToGrab, //what part of the object you want to grab
                                     NAME_None,
                                     ComponentToGrab->GetOwner()->GetActorLocation(),
                                     true); // allow rotation
    }
}

void UGrabber::GrabRelease()
{
    UE_LOG(LogTemp, Warning, TEXT("Grab Released"))
    // TODO: release phycis handle
    PhysicsHandle->ReleaseComponent();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    /// Get player view point this tick
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

    FVector LineTraceEnd = PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * Reach);
    
    // If the physics handle is attached
    if (PhysicsHandle->GrabbedComponent) //if we have a grabbed component then....
    {
        // move the object that we're holding
        PhysicsHandle->SetTargetLocation(LineTraceEnd);
        
        
    }
    
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
    /// Get player view point this tick
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint( OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);
    
    ///Log out to test
    /* UE_LOG(LogTemp, Warning, TEXT("Location: %s, Rotation: %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString()); */
    
    FVector LineTraceEnd = PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * Reach); //drawing out a 50cm long line
    
    /*/// Draw a red trace in the world to visualise
     
     DrawDebugLine(GetWorld(), PlayerViewPointLocation, LineTraceEnd, FColor(255,0,0), false, 0.f, 0.f, 10.f); //FColor(red,green,blue)*/
    
    /// Set-up query parameters
    FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
    
    /// Line-trace (AKA Ray-cast) out to reach distance
    FHitResult Hit;
    GetWorld()->LineTraceSingleByObjectType(OUT Hit, PlayerViewPointLocation, LineTraceEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParameters);
    
    /// See what we hit
    AActor* ActorHit = Hit.GetActor();
    if (ActorHit) {
        UE_LOG(LogTemp, Warning, TEXT("Line trace hit: %s"),*(ActorHit->GetName()));
    }
    return Hit;
}

