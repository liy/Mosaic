// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

UENUM(BlueprintType)
enum class EInputType : uint8
{
	Light,
	Medium,
	Heavy,
	Defence,
	Action,
	Up,
	Left,
	Right,
	Down,
	Jump
};

// Implement TSet::GetTypeHash make sure TSet work properly
// https://answers.unrealengine.com/questions/135766/do-tmap-and-rpcs-support-enum-classes.html
inline uint8 GetTypeHash(const EInputType A)
{
	return (uint8)A;
}

UCLASS(config=Game)
class ACharacterBase : public ACharacter
{
	GENERATED_BODY()

	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

protected:

	// Track the number of jumps in the air
	uint16 JumpCounter;

	/** Called for side to side input */
	void MoveRight(float value);

	/**
	 * Note that move up and down does not require updating the orientation of the character
	 */
	void MoveUp(float value);

	/**
	 * Handle multiple jumps in the air
	 */
	void Jump() override;

	/**
	 * Reset JumpCounter
	 */
	void OnMovementModeChanged(EMovementMode prevMovementMode, uint8 prevCustomMode) override;

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* inputComponent) override;
	// End of APawn interface

public:
	ACharacterBase(const FObjectInitializer& objectInitializer);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Action)
	class USphereComponent* CollectionSphere;

	// Maximum number of jump can performed in the air.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Jump)
	uint16 MaxJumps;

	virtual void BeginPlay() override;

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	UFUNCTION(BlueprintCallable, Category=Action)
	void CollectPickUps();

	// Directly get the CharacterController, fed up with casting...
	UFUNCTION(BlueprintCallable, Category = "Character")
	class ACharacterController* GetCharacterController() const;

private:
	/**
	 * Handle the character orientation
	 **/
	void OrientationProcess(float value);

private:

	// action related
	void LightPressed();
	void LightReleased();

	void MediumPressed();
	void MediumReleased();

	void HeavyPressed();
	void HeavyReleased();

	void DefencePressed();
	void DefenceReleased();

	void JumpPressed();
	void JumpReleased();

	void ActionPressed();
	void ActionReleased();

	void UpPressed();
	void UpReleased();

	void DownPressed();
	void DownReleased();

	void LeftPressed();
	void LeftReleased();

	void RightPressed();
	void RightReleased();

	// every time input action is added, delay reset timer
	void PushInputAction(EInputType input);

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Action)
	float ResetInputSetInterval = 0.01f;

	// 
	UFUNCTION(BlueprintImplementableEvent, meta = (FriendlyName = "OnInput"), Category=Action)
	virtual void ReceiveOnInput(EInputType action, EInputEvent event);
	virtual void OnInput(EInputType action, EInputEvent event = EInputEvent::IE_Pressed);

	UFUNCTION(BlueprintNativeEvent, Category=Action)
	void ResetInputSet();

	TSet<EInputType> GetInputSet();

	UFUNCTION(BlueprintCallable, Category=Skill)
	class ASkill* GetSkill(FName name);

	UFUNCTION(BlueprintCallable, Category=Skill)
	void AddSkill(TSubclassOf<ASkill> skillClass);

	UFUNCTION(BlueprintCallable, Category = Skill)
	void RemoveSkill(class ASkill* skill);

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "RemoveSkill"), Category = Skill)
	ASkill* RemoveSkillByName(FName name);

	UFUNCTION(BlueprintCallable, Category = Skill)
	bool CanTrigger(FName skillName);

protected:

	// Contains current inputs
	TSet<EInputType> InputSet;

	// Contains skills
	TMap<FName, class ASkill*> SkillMap;
};
