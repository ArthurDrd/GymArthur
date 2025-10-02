// UnrealEngine Plugin - by Arthur Durand

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractiveComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GENERIC_INTERACTIVE_SYSTEM_API UInteractiveComponent : public UActorComponent
{
	GENERATED_BODY()

	////////////////////////////////
	/// 	   PROPERTIES       ///
	////////////////////////////////
	
public:
	// Sets default values for this component's properties
	UInteractiveComponent();
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Called when the game ends
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	/**
	 * @brief Reference to the ACharacter owning this component
	 */
	UPROPERTY()
	TObjectPtr<ACharacter> Owner;

	////////////////////////////////
	/// 	   INTERACTION       ///
	////////////////////////////////
	
public:
	/**
	 * @brief Primary interaction called by the player
	 */
	UFUNCTION(BlueprintCallable)
	void PrimaryInteract();

	/**
	 * @brief Secondary interaction called by the player
	 */
	UFUNCTION(BlueprintCallable)
	void SecondaryInteract();
	
protected:
	
	/**
	 * @brief Server side primary interaction
	 */
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerPrimaryInteract();

	/**
	 * @brief Server side secondary interaction
	 */
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSecondaryInteract();
	
	/**
     * @brief List of all the actor that implement the IInteractiveInterface
     */
    UPROPERTY()
    TArray<AActor*> ListOfInteractibles;

	
	/**
	 * @brief Best actor to interact with (the closest one from the player for now)
	 */
	UPROPERTY(Replicated)
	AActor* BestInteractible;
	
	////////////////////////////////
	/// 	   RESEARCH	         ///
	////////////////////////////////

protected:
	// Reference to the timer handle used to call the GetAllInteractible function
	FTimerHandle ResearchTimerHandle;
	
	/**
	 * @brief Function to get all the actors that implement the IInteractiveInterface
	 */
	void GetAllInteractible();
	
private:
	
	/**
	 * @brief Compare the distance between the current BestInteractible and the RelevantActor and set the new BestInteractible if the RelevantActor is closer
	 * @param RelevantActor : The actor to compare with the current BestInteractible
	 */
	void TrySetNewBestInteractible(AActor* RelevantActor);
};