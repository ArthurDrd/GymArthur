// UnrealEngine Plugin - by Arthur Durand

#include "Components/InteractiveComponent.h"

#include "GameFramework/Character.h"
#include "Interfaces/InteractiveInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UInteractiveComponent::UInteractiveComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UInteractiveComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<ACharacter>(GetOwner());
	checkf(Owner, TEXT("Owner is not an ACharacter"));

	if (Owner->HasAuthority())
	{
		FTimerDelegate ResearchTimerDelegate;
		ResearchTimerDelegate.BindUObject(this, &UInteractiveComponent::GetAllInteractible);
		GetWorld()->GetTimerManager().SetTimer(ResearchTimerHandle, ResearchTimerDelegate, 0.1f, true);
	}
}

// Called when the game ends
void UInteractiveComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	GetWorld()->GetTimerManager().ClearTimer(ResearchTimerHandle);
}

void UInteractiveComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UInteractiveComponent, BestInteractible, COND_OwnerOnly, REPNOTIFY_Always);
}

// Primary interaction called by the player
void UInteractiveComponent::PrimaryInteract()
{
	ServerPrimaryInteract();
}

// Server side primary interaction
void UInteractiveComponent::ServerPrimaryInteract_Implementation()
{
	if (BestInteractible != nullptr && BestInteractible->Implements<UInteractiveInterface>())
	{
		Cast<IInteractiveInterface>(BestInteractible)->OnPrimaryInteract(Owner);
	}
}

// Server side primary interaction validation
bool UInteractiveComponent::ServerPrimaryInteract_Validate()
{
	// Check if the owner is valid and has authority and if the player is close enough to the interactible
	if (ensureAlways(Owner) && Owner->HasAuthority() && BestInteractible->GetDistanceTo(Owner) < 100.f)
	{
		return true;
	}
	return false;
}

// Secondary interaction called by the player
void UInteractiveComponent::SecondaryInteract()
{
	ServerSecondaryInteract();
}

// Server side secondary interaction
void UInteractiveComponent::ServerSecondaryInteract_Implementation()
{
	// Check if the owner is valid and has authority and if the player is close enough to the interactible
	if (BestInteractible != nullptr && BestInteractible->Implements<UInteractiveInterface>())
	{
		Cast<IInteractiveInterface>(BestInteractible)->OnSecondaryInteract(Owner);
	}
}

// Server side secondary interaction validation
bool UInteractiveComponent::ServerSecondaryInteract_Validate()
{
	if (ensureAlways(Owner) && Owner->HasAuthority()  && BestInteractible->GetDistanceTo(Owner) < 100.f)
	{
		return true;
	}
	return false;
}

// Get all the actors that implement the IInteractiveInterface
void UInteractiveComponent::GetAllInteractible()
{
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UInteractiveInterface::StaticClass(), ListOfInteractibles);
	if (ListOfInteractibles.Num() > 0 )
	{
		AActor* NewBestInteractible = ListOfInteractibles[0];
		for (AActor* Interactible : ListOfInteractibles)
		{
			if (Interactible->GetDistanceTo(Owner) < NewBestInteractible->GetDistanceTo(Owner))
			{
				NewBestInteractible = Interactible;
			}
		}
		TrySetNewBestInteractible(NewBestInteractible);
	}
}

// Try to set the new best interactible by comparing the distance between the current best interactible and the new one
void UInteractiveComponent::TrySetNewBestInteractible(AActor* RelevantActor)
{
	if (BestInteractible != RelevantActor)
	{
		if (RelevantActor->GetDistanceTo(Owner) < BestInteractible->GetDistanceTo(Owner))
		{
			BestInteractible = RelevantActor;
		}
	}
}
