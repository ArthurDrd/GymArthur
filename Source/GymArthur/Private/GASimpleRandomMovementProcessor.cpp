// // Copyright (c) 2025, Arthur Durand. All rights reserved.

#include "GASimpleRandomMovementProcessor.h"
#include "MassCommonFragments.h"
#include "GASimpleRandomMovementTrait.h"
#include "MassCommonTypes.h"
#include "MassExecutionContext.h"

UGASimpleRandomMovementProcessor::UGASimpleRandomMovementProcessor(): EntityQuery(*this)
{
	bAutoRegisterWithProcessingPhases = true;
	ExecutionFlags = (int32)(EProcessorExecutionFlags::All);
	ExecutionOrder.ExecuteBefore.Add(UE::Mass::ProcessorGroupNames::Avoidance);
}

void UGASimpleRandomMovementProcessor::ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager)
{
	EntityQuery.AddRequirement<FTransformFragment>(EMassFragmentAccess::ReadWrite);
	EntityQuery.AddRequirement<FGATargetFragment>(EMassFragmentAccess::ReadWrite);
}

void UGASimpleRandomMovementProcessor::Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context)
{
	EntityQuery.ForEachEntityChunk( Context, [this](FMassExecutionContext& Context)
	{
		const TArrayView<FTransformFragment> TransformsList = Context.GetMutableFragmentView<FTransformFragment>();
		const TArrayView<FGATargetFragment> SimpleMovementsList =
			Context.GetMutableFragmentView<FGATargetFragment>();
		const float WorldDeltaTime = Context.GetDeltaTimeSeconds();

		for (int32 EntityIndex = 0; EntityIndex < Context.GetNumEntities(); ++EntityIndex)
		{
			FTransform& Transform = TransformsList[EntityIndex].GetMutableTransform();
			FVector& MoveTarget = SimpleMovementsList[EntityIndex].Target;

			FVector CurrentLocation = Transform.GetLocation();

			if (FVector TargetVector = MoveTarget - CurrentLocation; TargetVector.Size()<= 20.f)
			{
				MoveTarget =  FVector(FMath::RandRange(-1.f, 1.f) * 1000.f, FMath::RandRange(-1.f, 1.f) * 1000.f, CurrentLocation.Z);
			}
			else
			{
				Transform.SetLocation(CurrentLocation + TargetVector.GetSafeNormal() * 400.f * WorldDeltaTime);
			}
		}
	});
}