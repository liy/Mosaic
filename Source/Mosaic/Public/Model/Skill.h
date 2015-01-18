// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "CharacterBase.h"
#include "Skill.generated.h"

/**
 * 
 */
UCLASS()
class MOSAIC_API ASkill : public AActor
{
	GENERATED_BODY()
	
public:

	// The name of the skill
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	FName Name;

	// The inputs triggers this skill
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Input)
	TArray<EInputType> TriggerInputs;

	UFUNCTION(BlueprintCallable, Category=Input)
	bool CanTrigger();
};
