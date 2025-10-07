// // Copyright (c) 2025, Arthur Durand. All rights reserved.


#include "AI/Processors/GAMovementProcessor.h"

#include "MassCommonFragments.h"
#include "MassCommonTypes.h"
#include "MassExecutionContext.h"
#include "MassEntityManager.h"
#include "MassMovementFragments.h"
#include "MassNavigationFragments.h"

UGAMovementProcessor::UGAMovementProcessor(): EntityQuery(*this)
{
	bAutoRegisterWithProcessingPhases = true;
	ExecutionFlags = (int32)(EProcessorExecutionFlags::All);
	ExecutionOrder.ExecuteBefore.Add(UE::Mass::ProcessorGroupNames::Avoidance);
}

void UGAMovementProcessor::ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager)
{
	EntityQuery.AddRequirement<FTransformFragment>(EMassFragmentAccess::ReadOnly);
	EntityQuery.AddRequirement<FMassMoveTargetFragment>(EMassFragmentAccess::ReadWrite);
	EntityQuery.AddConstSharedRequirement<FMassMovementParameters>(EMassFragmentPresence::All);
}

void UGAMovementProcessor::Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context)
{
	EntityQuery.ForEachEntityChunk( Context, [this](FMassExecutionContext& Context)
	{
		const TConstArrayView<FTransformFragment> TransformsList = Context.GetFragmentView<FTransformFragment>();
		const TArrayView<FMassMoveTargetFragment> NavTargetsList = Context.GetMutableFragmentView<FMassMoveTargetFragment>();
		const FMassMovementParameters& MovementParams = Context.GetConstSharedFragment<FMassMovementParameters>();

		for (int32 EntityIndex = 0; EntityIndex < Context.GetNumEntities(); ++EntityIndex)
		{
			const FTransform& Transform = TransformsList[EntityIndex].GetTransform();
			FMassMoveTargetFragment& MoveTarget = NavTargetsList[EntityIndex];
			
			FVector CurrentLocation = Transform.GetLocation();
			FVector TargetVector = MoveTarget.Center - Transform.GetLocation();
			TargetVector.Z = 0.f;
			MoveTarget.DistanceToGoal = TargetVector.Size();
			MoveTarget.Forward = TargetVector.GetSafeNormal();

			if(MoveTarget.DistanceToGoal <=20.f || MoveTarget.Center == FVector::ZeroVector)
			{
				MoveTarget.Center  = FVector(FMath::RandRange(-1.f,1.f) * 1000.f, FMath::RandRange(-1.f,1.f) * 1000.f, CurrentLocation.Z);
				MoveTarget.DistanceToGoal = (MoveTarget.Center - Transform.GetLocation()).Size();
				MoveTarget.Forward = (MoveTarget.Center - Transform.GetLocation()).GetSafeNormal();
				MoveTarget.DesiredSpeed =FMassInt16Real(MovementParams.DefaultDesiredSpeed);
			}
		}
	});
}
