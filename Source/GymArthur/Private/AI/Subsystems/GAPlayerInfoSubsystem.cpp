// // Copyright (c) 2025, Arthur Durand. All rights reserved.


#include "AI/Subsystems/GAPlayerInfoSubsystem.h"


FVector UGAPlayerInfoSubsystem::GetPlayerLocation() const
{
	return PlayerLocation;
}

void UGAPlayerInfoSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	CachedPlayerPawn = InWorld.GetFirstPlayerController()->GetPawn();
}

void UGAPlayerInfoSubsystem::Tick(float DeltaTime)
{
	if(CachedPlayerPawn)
	{
		PlayerLocation = CachedPlayerPawn->GetActorLocation();
	}
		
}

TStatId UGAPlayerInfoSubsystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UBulletHellSubsystem, STATGROUP_Tickables);
}
