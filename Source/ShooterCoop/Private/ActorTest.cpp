// Fill out your copyright notice in the Description page of Project Settings.

#include "ActorTest.h"
#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "MyActor.h"
#include "Tests/AutomationCommon.h"
#include "Engine/World.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FMyActorTest, "ShooterCoop.Items.MyActor",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter);


//from AutomationOpenMap() from UWorld* TestWorld = AutomationCommon::GetAnyGameWorld(); 'GetAnyGameWorld()' rename to 'GetTestGameWorld'
UWorld* GetTestGameWorld()
{
	const TIndirectArray<FWorldContext>& WorldContexts = GEngine->GetWorldContexts();
	for (const FWorldContext& Context : WorldContexts)
	{
		if ((Context.WorldType == EWorldType::PIE || Context.WorldType == EWorldType::Game) && Context.World())
		{
			return Context.World();
		}
	}

	return nullptr;
}



// /Script/Engine.World'/Game/Maps/TestLevel.TestLevel'
bool FMyActorTest::RunTest(const FString& Parameters)
{
	AutomationOpenMap("/Game/Maps/TestLevel");

	UWorld* World = GetTestGameWorld();
	if (!TestNotNull("World exists", World))
	{
		return false;
	}

	AMyActor* MyActor = World->SpawnActor<AMyActor>(AMyActor::StaticClass(), FTransform::Identity);
	if (!TestNotNull("Actor exists", MyActor))
	{
		return false;
	}
	TestGreaterEqual("GreaterEqual", MyActor->GetInteger(), 0);
	
	ADD_LATENT_AUTOMATION_COMMAND(FExitGameCommand);
	return true;
}
