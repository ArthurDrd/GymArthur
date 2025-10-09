// // Copyright (c) 2025, Arthur Durand. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputMappingContext.h"
#include "Characters/GACharacterBase.h"
#include "Inputs/GAInputConfig.h"
#include "GAPlayerControllerBase.generated.h"

UCLASS()
class GYMARTHUR_API AGAPlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

public:
	AGAPlayerControllerBase();

protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputMappingContext> IMC;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UGAInputConfig> InputConfig;

	bool bIsSprinting = false;
	
	/**
	 * @brief Move
	 * @param InputActionValue : Value of the input 
	 */
	void InputMove(const FInputActionValue& InputActionValue);

	/**
	 * @brief : Zoom/Unzoom
	 * @param InputActionValue : Value of the input
	 */
	void InputZoom(const FInputActionValue& InputActionValue);

	/**
	 * @brief : Sprint
	 * @param InputActionValue : Value of the input
	 */
	void InputSprint(const FInputActionValue& InputActionValue);

	private:

	UPROPERTY()
	AGACharacterBase* CachedCharacter = nullptr;
};
