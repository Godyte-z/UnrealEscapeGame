// Copy right Goda Zalalyte 2017.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEGAME_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    void OpenDoor();                 //NOT SURE IF THIS SHOULD BE HERE OR IF IT'S CORRECT!
    void CloseDoor();
    
private:
    UPROPERTY(EditAnywhere)
    float OpenAngle = -90.0f;         //DOOR OPEN ANGLE??
    
    UPROPERTY(EditAnywhere)
    ATriggerVolume* PressurePlate;
    
    UPROPERTY(EditAnywhere)
    float DoorCloseDelay = 1.f;      //this is our starting value
    
    float LastDoorOpenTime;
    
    //UPROPERTY(EditAnywhere)
    
    AActor* Owner;                    //the owning doo
    
    // Returns total mass in kg
    float GetTotalMassOfActorsOnPlate();
	
};
