// Copyright (c) 2025, Arthur Durand. All rights reserved.


#include "Inputs/GAInputConfig.h"

const UInputAction* UGAInputConfig::FindInputActionForTag(const FGameplayTag& InputTag) const
{
	for (const FGATaggedInputAction& TaggedInputAction : TaggedInputActions)
	{
		if (TaggedInputAction.InputAction && TaggedInputAction.InputTag == InputTag)
		{
			return TaggedInputAction.InputAction;
		}
	}

	return nullptr;
}