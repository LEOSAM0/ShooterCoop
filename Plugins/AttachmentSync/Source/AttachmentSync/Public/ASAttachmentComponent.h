// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ASAttachment.h"
#include "Engine/StreamableManager.h"
#include "ASAttachmentComponent.generated.h"


UENUM(BlueprintType)
enum class ETypeAttachment : uint8
{
	Clip	UMETA(DisplayName = "Clip"),
	Muzzle  UMETA(DisplayName = "Muzzle"),
	Grip	UMETA(DisplayName = "Grip"),
	Sight	UMETA(DisplayName = "Sight"),
	Other	UMETA(DisplayName = "Other")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAttachmentAdded, FAttachmentInfo, AttachmentInfo, FGameplayTag, 
AttachmentGameplayTag, ETypeAttachment, AttachmentType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAttachmentRemoved, FAttachmentInfo, AttachmentInfo, FGameplayTag, 
AttachmentGameplayTag, ETypeAttachment, AttachmentType);


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ATTACHMENTSYNC_API UASAttachmentComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY()
	TObjectPtr<class USkeletalMeshComponent> WeaponMesh;
	FStreamableManager Manager;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AttachmentName", meta = (AllowPrivateAccess = "true"))
	FName ClipSocketName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AttachmentName", meta = (AllowPrivateAccess = "true"))
	FName MuzzleSocketName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AttachmentName", meta = (AllowPrivateAccess = "true"))
	FName GripSocketName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AttachmentName", meta = (AllowPrivateAccess = "true"))
	FName SightSocketName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AttachmentName", meta = (AllowPrivateAccess = "true"))
	FName OtherSocketName;

	UPROPERTY(BlueprintReadOnly, Category = "Attachment", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AASAttachment> EquippedClip;
	UPROPERTY(BlueprintReadOnly, Category = "Attachment", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AASAttachment> EquippedMuzzle;
	UPROPERTY(BlueprintReadOnly, Category = "Attachment", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AASAttachment> EquippedGrip;
	UPROPERTY(BlueprintReadOnly, Category = "Attachment", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AASAttachment> EquippedSight;
	UPROPERTY(BlueprintReadOnly, Category = "Attachment", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AASAttachment> EquippedOther;

	UPROPERTY(EditDefaultsOnly, Category = "Attachment", meta = (AllowPrivateAccess = "true", EditFixedSize=true))
	TMap<FName, TSoftClassPtr<AASAttachment>> ClipAttachments;
	UPROPERTY(EditDefaultsOnly, Category = "Attachment", meta = (AllowPrivateAccess = "true", EditFixedSize=true))
	TMap<FName, TSoftClassPtr<AASAttachment>> MuzzleAttachments;
	UPROPERTY(EditDefaultsOnly, Category = "Attachment", meta = (AllowPrivateAccess = "true", EditFixedSize=true))
	TMap<FName, TSoftClassPtr<AASAttachment>> GripAttachments;
	UPROPERTY(EditDefaultsOnly, Category = "Attachment", meta = (AllowPrivateAccess = "true", EditFixedSize=true))
	TMap<FName, TSoftClassPtr<AASAttachment>> SightAttachments;
	UPROPERTY(EditDefaultsOnly, Category = "Attachment", meta = (AllowPrivateAccess = "true", EditFixedSize=true))
	TMap<FName, TSoftClassPtr<AASAttachment>> OtherAttachments;

	UFUNCTION(BlueprintCallable, Category = "Attachment", meta = (AllowPrivateAccess = "true"))
	void ChangeByGameplayTag(FGameplayTag NewTag, ETypeAttachment TypeAttachment);
	UFUNCTION(BlueprintCallable, Category = "Attachment", meta = (AllowPrivateAccess = "true"))
	void ChangeClipByGameplayTag(FGameplayTag NewClip);
	UFUNCTION(BlueprintCallable, Category = "Attachment", meta = (AllowPrivateAccess = "true"))
	void ChangeMuzzleByGameplayTag(FGameplayTag NewMuzzle);
	UFUNCTION(BlueprintCallable, Category = "Attachment", meta = (AllowPrivateAccess = "true"))
	void ChangeGripByGameplayTag(FGameplayTag NewGrip);
	UFUNCTION(BlueprintCallable, Category = "Attachment", meta = (AllowPrivateAccess = "true"))
	void ChangeSightByGameplayTag(FGameplayTag NewSight);
	UFUNCTION(BlueprintCallable, Category = "Attachment", meta = (AllowPrivateAccess = "true"))
	void ChangeOtherByGameplayTag(FGameplayTag NewOther);
	UFUNCTION(BlueprintCallable, Category = "Attachment", meta = (AllowPrivateAccess = "true"))
	void ChangeAttachmentByKey(FName AttachmentName, ETypeAttachment TypeAttachment);

	void OnLoad(TSoftClassPtr<AASAttachment> AttachmentRef, FGameplayTag AttachmentTag, ETypeAttachment TypeAttachment);
	void OnLoadByKey(TSoftClassPtr<AASAttachment>* AttachmentPtr,ETypeAttachment TypeAttachment);

	UPROPERTY(BlueprintAssignable)
	FOnAttachmentAdded OnAttachmentAdded;
	UPROPERTY(BlueprintAssignable)
	FOnAttachmentRemoved OnAttachmentRemoved;

	UFUNCTION(BlueprintCallable, Category = "Attachment")
	FORCEINLINE AASAttachment* GetCurrentAttachmentClip() const { return EquippedClip; }
	UFUNCTION(BlueprintCallable, Category = "Attachment")
	FORCEINLINE AASAttachment* GetCurrentAttachmentMuzzle() const { return EquippedMuzzle; }
	UFUNCTION(BlueprintCallable, Category = "Attachment")
	FORCEINLINE AASAttachment* GetCurrentAttachmentGrip() const { return EquippedGrip; }
	UFUNCTION(BlueprintCallable, Category = "Attachment")
	FORCEINLINE AASAttachment* GetCurrentAttachmentSight() const { return EquippedSight; }
	UFUNCTION(BlueprintCallable, Category = "Attachment")
	FORCEINLINE AASAttachment* GetCurrentAttachmentOther() const { return EquippedOther; }

	UFUNCTION(BlueprintCallable, Category = "Attachment")
	FORCEINLINE TMap<FName, TSoftClassPtr<AASAttachment>> GetAllCurrentAttachmentClip() const { return ClipAttachments; }
	UFUNCTION(BlueprintCallable, Category = "Attachment")
	FORCEINLINE TMap<FName, TSoftClassPtr<AASAttachment>> GetAllCurrentAttachmentMuzzle() const { return MuzzleAttachments; }
	UFUNCTION(BlueprintCallable, Category = "Attachment")
	FORCEINLINE TMap<FName, TSoftClassPtr<AASAttachment>> GetAllCurrentAttachmentGrip() const { return GripAttachments; }
	UFUNCTION(BlueprintCallable, Category = "Attachment")
	FORCEINLINE TMap<FName, TSoftClassPtr<AASAttachment>> GetAllCurrentAttachmentSight() const { return SightAttachments; }
	UFUNCTION(BlueprintCallable, Category = "Attachment")
	FORCEINLINE TMap<FName, TSoftClassPtr<AASAttachment>> GetAllCurrentAttachmentOther() const { return OtherAttachments; }
	
	UFUNCTION(BlueprintCallable, Category = "Attachment")
	void DestroyCurrentAttachment(ETypeAttachment TypeAttachment);

	AASAttachment* ChangeAttachment(FName AttachmentName, const TSoftClassPtr<AASAttachment>& AttachmentSoftRef) const;
	TMap<FName, TSoftClassPtr<AASAttachment>>* GetAttachmentMapByType(ETypeAttachment TypeAttachment);
	TObjectPtr<AASAttachment>* GetAttachmentByType(ETypeAttachment TypeAttachment);


public:
	// Sets default values for this component's properties
	UASAttachmentComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
