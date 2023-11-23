// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

DECLARE_STATS_GROUP(TEXT("ROGUELIKE_Game"), STATGROUP_ROGUELIKE, STATCAT_Advanced);

static void LogOnScreen(UObject* WorldContext, FString Message, FColor Color = FColor::White, float Duration = 0.5f)
{
	if(!ensure(WorldContext)){ return; }

	UWorld* World = WorldContext->GetWorld();
	if (!ensure(World)) { return; }

	FString NetPrefix = World->IsNetMode(NM_Client) ? "[CLIENT] " : "[SERVER] ";
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, Duration, Color, NetPrefix + Message);
	}
}