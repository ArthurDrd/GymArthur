// // Copyright (c) 2025, Arthur Durand. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "MassProcessor.h"
#include "GAMovementProcessor.generated.h"

UCLASS()
class GYMARTHUR_API UGAMovementProcessor : public UMassProcessor
{
	GENERATED_BODY()
public:
	UGAMovementProcessor();
	
protected:
	virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;
	virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;

private:
	FMassEntityQuery EntityQuery;
};
