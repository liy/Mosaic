// Fill out your copyright notice in the Description page of Project Settings.

#include "Mosaic.h"
#include "Skill.h"


bool ASkill::CanTrigger()
{
	ACharacterBase* owner = Cast<ACharacterBase>(GetOwner());
	if (owner){
		TSet<EInputType> inputSet = owner->GetInputSet();

		// The number of inputs does not match, fail the check
		if (TriggerInputs.Num() != inputSet.Num())
		{
			return false;
		}

		for (EInputType input : TriggerInputs)
		{
			if (!inputSet.Contains(input))
			{
				return false;
			}
		}

		return true;
	}

	return false;
}
