// Fill out your copyright notice in the Description page of Project Settings.


#include "TestActorModule.h"


// Sets default values
ATestActorModule::ATestActorModule()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ATestActorModule::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestActorModule::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

