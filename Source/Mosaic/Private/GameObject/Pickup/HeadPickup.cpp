// Fill out your copyright notice in the Description page of Project Settings.

#include "Mosaic.h"
#include "HeadPickup.h"
#include "CharacterController.h"
#include "Engine.h"

AHeadPickup::AHeadPickup(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
	Data.Tags.Add(EPickupType::Head);
}

void AHeadPickup::OnCollection(ACharacterController& controller)
{
	// TODO: chanage head etc. Update the inventory
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, TEXT("HEAD onpickup"));
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("%d"), bIsActive));
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, Data.Info.ToString());

	UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	Super::OnCollection(controller);
}