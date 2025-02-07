// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
#include "ASAttachment.generated.h"

USTRUCT(BlueprintType)
struct FAttachmentInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attachment")
	FGameplayTag GameplayTag;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attachment")
	FGameplayTagContainer GameplayTagContainer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attachment")
	float DamageBonus{};
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attachment")
	float AccuracyBonus{};
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attachment")
	float ShieldBonus{};
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attachment")
	float ReloadSpeedBonus{};
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attachment")
	TObjectPtr<class UTexture2D> Icon;
};


UCLASS()
class ATTACHMENTSYNC_API AASAttachment : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attachment", meta = (AllowPrivateAccess = "true"))
	FAttachmentInfo AttachmentAttributes;


public:
	// Sets default values for this actor's properties
	AASAttachment();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Attachment")
	FAttachmentInfo GetAttachmentInfo()
	{
		return AttachmentAttributes;
	}
	UFUNCTION(BlueprintCallable, Category = "Attachment")
	void SetAttachmentInfo(FAttachmentInfo NewInfo)
	{
		AttachmentAttributes = NewInfo;
	}


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
