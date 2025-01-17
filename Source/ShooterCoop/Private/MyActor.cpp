// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Hello!"));

}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogSubtitle, Error, TEXT("Here I am Will you send me an angel?"))

	GEngine->AddOnScreenDebugMessage(3, 2.f, FColor::Green, TEXT("Sleep Now In The Fire!"));
	
}


//Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}