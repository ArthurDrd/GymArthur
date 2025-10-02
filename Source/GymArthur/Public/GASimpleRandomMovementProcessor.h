// // Copyright (c) 2025, Arthur Durand. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "MassProcessor.h"
#include "GASimpleRandomMovementProcessor.generated.h"



UCLASS()
class GYMARTHUR_API UGASimpleRandomMovementProcessor : public UMassProcessor
{
	GENERATED_BODY()
public:
	UGASimpleRandomMovementProcessor();
	
protected:
	virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;
	virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;

private:
	FMassEntityQuery EntityQuery;
};