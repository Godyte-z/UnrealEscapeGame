// Copy right Goda Zalalyte 2017.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Grabber.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEGAME_API UGrabber : public UActorComponent //UActor here inherits the features from UGrabber
{
    GENERATED_BODY()
    
public:
    // Sets default values for this component's properties
    UGrabber();
    
protected:
    // Called when the game starts
    virtual void BeginPlay() override;
    
public:
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    
private:
    // How far ahead of the player we can reach in cm
    float Reach = 100.f;
    
    UPhysicsHandleComponent* PhysicsHandle = nullptr;
    
    UInputComponent* InputComponent = nullptr;
    
    // Ray-cast and grab what's in reach 
    void Grab();
    // Called when grab is released
    void GrabRelease();
    
    
    
};

