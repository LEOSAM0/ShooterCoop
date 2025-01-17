// Fill out your copyright notice in the Description page of Project Settings.

#include "ActorTest.h"
#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "MyActor.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FMyActorTest, "ShooterCoop.Items.MyActor",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter);


bool FMyActorTest::RunTest(const FString& Parameters)
{
	AMyActor MyActor;
	MyActor.SetInteger(1);
	int32 integer = 0;
	TestGreaterEqual("Greater or equal", MyActor.GetInteger(), integer);
	

	return true;
}
