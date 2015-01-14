// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

UENUM(BlueprintType)
enum class EInputAction : uint8
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
inline uint8 GetTypeHash(const EInputAction A)
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
	void PushInputAction(EInputAction action);

	void ResetInputSet();

	void ResetInputStack();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Action)
	float ResetInputSetInterval = 0.01f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Action)
	float ResetInputStackInterval = 0.03f;

	// If you expect a sequence of inputs, use the stack
	UPROPERTY()
	TArray<EInputAction> ActionStack;

	// If you expect a simultaneous inputs, use the set.
	TSet<EInputAction> ActionSet;

	// 
	UFUNCTION(BlueprintImplementableEvent, meta = (FriendlyName = "OnActionInput"))
	virtual void ReceiveOnActionInput(EInputAction action, EInputEvent event);
	virtual void OnActionInput(EInputAction action, EInputEvent event = EInputEvent::IE_Pressed);

	//UFUNCTION(BlueprintImplementableEvent, meta = (FriendlyName = "OnActionInput"))
	//virtual void ReceiveOnActionInput(EInputAction action, EInputEvent event);
	//virtual void OnActionInput(EInputAction action, EInputEvent event = EInputEvent::IE_Pressed);

	UFUNCTION(BlueprintImplementableEvent, meta = (FriendlyName = "OnTriggerAction"))
	virtual void ReceiveOnTriggerAction();
	virtual void OnTriggerAction();
};
