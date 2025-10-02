// UnrealEngine Plugin - by Arthur Durand

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractiveInterface.generated.h"

UINTERFACE(MinimalAPI,BlueprintType, Blueprintable)
class UInteractiveInterface : public UInterface
{
	GENERATED_BODY()
};

class GENERIC_INTERACTIVE_SYSTEM_API IInteractiveInterface
{
	GENERATED_BODY()

	////////////////////////////////
	/// 	PRIMARY INTERACT	 ///
	////////////////////////////////
	
public:
	UFUNCTION()
	virtual void OnPrimaryInteract(AActor* Interactor) PURE_VIRTUAL(IInteractiveInterface::OnPrimaryInteract);
	
	////////////////////////////////
	/// 	SECONDARY INTERACT	 ///
	////////////////////////////////

public:
	UFUNCTION()
	virtual void OnSecondaryInteract(AActor* Interactor) PURE_VIRTUAL(IInteractiveInterface::OnSecondaryInteract);
};
