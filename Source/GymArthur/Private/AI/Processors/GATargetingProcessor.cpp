// // Copyright (c) 2025, Arthur Durand. All rights reserved.


#include "AI/Processors/GATargetingProcessor.h"
#include "MassCommonTypes.h"
#include "MassExecutionContext.h"
#include "AI/Fragments/GAFragments.h"
#include "AI/Subsystems/GAPlayerInfoSubsystem.h"

UGATargetingProcessor::UGATargetingProcessor() : EntityQuery(*this)
{
	bAutoRegisterWithProcessingPhases = true;
	ExecutionFlags = (int32)(EProcessorExecutionFlags::All);
	ExecutionOrder.ExecuteBefore.Add(UE::Mass::ProcessorGroupNames::Avoidance);
}

void UGATargetingProcessor::ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager)
{
	EntityQuery.AddRequirement<FGATargetFragment>(EMassFragmentAccess::ReadWrite);
	EntityQuery.AddSubsystemRequirement<UGAPlayerInfoSubsystem>(EMassFragmentAccess::ReadOnly);
}

void UGATargetingProcessor::Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context)
{
	EntityQuery.ForEachEntityChunk( Context, [this](FMassExecutionContext& Context)
	{
		const TArrayView<FGATargetFragment> TargetList = Context.GetMutableFragmentView<FGATargetFragment>();
		const auto PlayerInfoSubsystem = Context.GetSubsystem<UGAPlayerInfoSubsystem>();
		
		const FVector PlayerLocation = PlayerInfoSubsystem->GetPlayerLocation();

		for (int32 EntityIndex = 0; EntityIndex < Context.GetNumEntities(); ++EntityIndex)
		{
			TargetList[EntityIndex].Target = PlayerLocation;
		}
	});
}
