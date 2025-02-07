// Fill out your copyright notice in the Description page of Project Settings.


#include "ASAttachmentComponent.h"


TMap<FName, TSoftClassPtr<AASAttachment>>* UASAttachmentComponent::GetAttachmentMapByType(ETypeAttachment TypeAttachment)
{
	switch (TypeAttachment)
	{
	case ETypeAttachment::Clip:
		return &ClipAttachments;
	case ETypeAttachment::Muzzle:
		return &MuzzleAttachments;
	case ETypeAttachment::Grip:
		return  &GripAttachments;
	case ETypeAttachment::Sight:
		return  &SightAttachments;
	case ETypeAttachment::Other:
	default:
		return  &OtherAttachments;
	}
}

TObjectPtr<AASAttachment>* UASAttachmentComponent::GetAttachmentByType(ETypeAttachment TypeAttachment)
{
	switch (TypeAttachment)
	{
	case ETypeAttachment::Clip:
		return  &EquippedClip;
	case ETypeAttachment::Muzzle:
		return &EquippedMuzzle;
	case ETypeAttachment::Grip:
		return &EquippedGrip;
	case ETypeAttachment::Sight:
		return &EquippedSight;
	case ETypeAttachment::Other:
	default:
		return &EquippedOther;
	}
}

void UASAttachmentComponent::ChangeByGameplayTag(FGameplayTag NewTag, ETypeAttachment TypeAttachment)
{
	TMap<FName, TSoftClassPtr<AASAttachment>>* Attachments = GetAttachmentMapByType(TypeAttachment);

	for (const auto& Attachment : *Attachments)
	{
		Manager.RequestAsyncLoad(Attachment.Value.ToSoftObjectPath(),
		                         FStreamableDelegate::CreateUObject(this, &ThisClass::OnLoad, Attachment.Value, NewTag,
		                                                            TypeAttachment));
	}
}

void UASAttachmentComponent::ChangeClipByGameplayTag(FGameplayTag NewClip)
{
	ChangeByGameplayTag(NewClip, ETypeAttachment::Clip);
}

void UASAttachmentComponent::ChangeMuzzleByGameplayTag(FGameplayTag NewMuzzle)
{
	ChangeByGameplayTag(NewMuzzle, ETypeAttachment::Muzzle);
}

void UASAttachmentComponent::ChangeGripByGameplayTag(FGameplayTag NewGrip)
{
	ChangeByGameplayTag(NewGrip, ETypeAttachment::Grip);
}

void UASAttachmentComponent::ChangeSightByGameplayTag(FGameplayTag NewSight)
{
	ChangeByGameplayTag(NewSight, ETypeAttachment::Sight);
}

void UASAttachmentComponent::ChangeOtherByGameplayTag(FGameplayTag NewOther)
{
	ChangeByGameplayTag(NewOther, ETypeAttachment::Other);
}

void UASAttachmentComponent::ChangeAttachmentByKey(FName AttachmentName, ETypeAttachment TypeAttachment)
{
	TObjectPtr<AASAttachment>* AttachObj = GetAttachmentByType(TypeAttachment);
	TMap<FName, TSoftClassPtr<AASAttachment>>* Attachments = GetAttachmentMapByType(TypeAttachment);

	if (const auto& AttachmentRef = Attachments->Find(AttachmentName))
	{
		if (AttachObj->Get())
		{
			OnAttachmentRemoved.Broadcast(AttachObj->Get()->GetAttachmentInfo(),
			                              AttachObj->Get()->GetAttachmentInfo().GameplayTag, TypeAttachment);
			AttachObj->Get()->Destroy();
		}
		Manager.RequestAsyncLoad(AttachmentRef->ToSoftObjectPath(),
		                         FStreamableDelegate::CreateUObject(this, &ThisClass::OnLoadByKey,
		                                                            AttachmentRef,
		                                                            TypeAttachment));
	}
}

void UASAttachmentComponent::OnLoad(TSoftClassPtr<AASAttachment> AttachmentRef, FGameplayTag AttachmentTag,
                                    ETypeAttachment TypeAttachment)
{
	if (AttachmentRef.IsValid())
	{
		const auto AttachmentActor = Cast<AASAttachment>(AttachmentRef->GetDefaultObject());
		ensure(AttachmentActor);
		if (AttachmentActor->GetAttachmentInfo().GameplayTag.MatchesTagExact(AttachmentTag))
		{
			DestroyCurrentAttachment(TypeAttachment);
			switch (TypeAttachment)
			{
			case ETypeAttachment::Clip:
				EquippedClip = ChangeAttachment(ClipSocketName, AttachmentRef);
				OnAttachmentAdded.Broadcast(EquippedClip->GetAttachmentInfo(),
				                            EquippedClip->GetAttachmentInfo().GameplayTag, ETypeAttachment::Clip);
				break;
			case ETypeAttachment::Muzzle:
				EquippedMuzzle = ChangeAttachment(MuzzleSocketName, AttachmentRef);
				OnAttachmentAdded.Broadcast(EquippedMuzzle->GetAttachmentInfo(),
				                            EquippedMuzzle->GetAttachmentInfo().GameplayTag, ETypeAttachment::Muzzle);
				break;
			case ETypeAttachment::Grip:
				EquippedGrip = ChangeAttachment(GripSocketName, AttachmentRef);
				OnAttachmentAdded.Broadcast(EquippedGrip->GetAttachmentInfo(),
				                            EquippedGrip->GetAttachmentInfo().GameplayTag, ETypeAttachment::Grip);
				break;
			case ETypeAttachment::Sight:
				EquippedSight = ChangeAttachment(SightSocketName, AttachmentRef);
				OnAttachmentAdded.Broadcast(EquippedSight->GetAttachmentInfo(),
				                            EquippedSight->GetAttachmentInfo().GameplayTag, ETypeAttachment::Sight);
				break;
			case ETypeAttachment::Other:
				EquippedOther = ChangeAttachment(OtherSocketName, AttachmentRef);
				OnAttachmentAdded.Broadcast(EquippedOther->GetAttachmentInfo(),
				                            EquippedOther->GetAttachmentInfo().GameplayTag, ETypeAttachment::Other);
				break;
			}
		}
	}
}

void UASAttachmentComponent::OnLoadByKey(TSoftClassPtr<AASAttachment>* AttachmentPtr, ETypeAttachment TypeAttachment)
{
	DestroyCurrentAttachment(TypeAttachment);

	if (AttachmentPtr)
	{
		switch (TypeAttachment)
		{
		case ETypeAttachment::Clip:
			EquippedClip = ChangeAttachment(ClipSocketName, AttachmentPtr->Get());
			OnAttachmentAdded.Broadcast(EquippedClip->GetAttachmentInfo(),
			                            EquippedClip->GetAttachmentInfo().GameplayTag, ETypeAttachment::Clip);
			break;
		case ETypeAttachment::Muzzle:
			EquippedMuzzle = ChangeAttachment(ClipSocketName, AttachmentPtr->Get());
			OnAttachmentAdded.Broadcast(EquippedMuzzle->GetAttachmentInfo(),
			                            EquippedMuzzle->GetAttachmentInfo().GameplayTag, ETypeAttachment::Muzzle);
			break;
		case ETypeAttachment::Grip:
			EquippedGrip = ChangeAttachment(ClipSocketName, AttachmentPtr->Get());
			OnAttachmentAdded.Broadcast(EquippedGrip->GetAttachmentInfo(),
			                            EquippedGrip->GetAttachmentInfo().GameplayTag, ETypeAttachment::Grip);
			break;
		case ETypeAttachment::Sight:
			EquippedSight = ChangeAttachment(ClipSocketName, AttachmentPtr->Get());
			OnAttachmentAdded.Broadcast(EquippedSight->GetAttachmentInfo(),
			                            EquippedSight->GetAttachmentInfo().GameplayTag, ETypeAttachment::Sight);
			break;
		case ETypeAttachment::Other:
			EquippedOther = ChangeAttachment(ClipSocketName, AttachmentPtr->Get());
			OnAttachmentAdded.Broadcast(EquippedOther->GetAttachmentInfo(),
			                            EquippedOther->GetAttachmentInfo().GameplayTag, ETypeAttachment::Other);
			break;
		}
	}
}

void UASAttachmentComponent::DestroyCurrentAttachment(ETypeAttachment TypeAttachment)
{
	TObjectPtr<AASAttachment>* AttachObj = GetAttachmentByType(TypeAttachment);
	
	if (AttachObj->Get())
	{
		OnAttachmentRemoved.Broadcast(AttachObj->Get()->GetAttachmentInfo(),
		                              AttachObj->Get()->GetAttachmentInfo().GameplayTag, TypeAttachment);
		AttachObj->Get()->Destroy();
	}
}

AASAttachment* UASAttachmentComponent::ChangeAttachment(FName AttachmentName,
                                                        const TSoftClassPtr<AASAttachment>& AttachmentSoftRef) const
{
	const FVector SocketLocation = WeaponMesh->GetSocketLocation(AttachmentName);
	const FRotator SocketRotator = WeaponMesh->GetSocketRotation(AttachmentName);
	const FActorSpawnParameters SpawnParams{};

	AASAttachment* ActorAttachment = GetWorld()->SpawnActor<AASAttachment>(
		AttachmentSoftRef.Get(), SocketLocation, SocketRotator, SpawnParams);
	if (ActorAttachment)
	{
		ActorAttachment->AttachToComponent(WeaponMesh, FAttachmentTransformRules::KeepWorldTransform, AttachmentName);
	}
	return ActorAttachment;
}


// Sets default values for this component's properties
UASAttachmentComponent::UASAttachmentComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	WeaponMesh = nullptr;
}


// Called when the game starts
void UASAttachmentComponent::BeginPlay()
{
	Super::BeginPlay();

	WeaponMesh = Cast<USkeletalMeshComponent>(GetOwner()->GetComponentByClass(USkeletalMeshComponent::StaticClass()));
	
}


// Called every frame
void UASAttachmentComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                           FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

