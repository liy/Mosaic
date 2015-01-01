// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

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

	UPROPERTY(VisibleAnywhere, BLueprintReadOnly, Category=Action)
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
};
