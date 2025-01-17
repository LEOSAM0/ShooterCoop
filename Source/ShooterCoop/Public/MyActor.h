// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

class UStaticMeshComponent;

UCLASS()
class SHOOTERCOOP_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

	int32 GetInteger() const { return Integer1; }

	void SetInteger(int32 val) { val = Integer1; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Location")
	int32 Integer1 = 0;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};

