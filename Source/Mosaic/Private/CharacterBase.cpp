// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "Mosaic.h"
#include "CharacterBase.h"
#include "Pickup.h"
#include "Inventory.h"
#include "CharacterController.h"

ACharacterBase::ACharacterBase(const FObjectInitializer& objectInitializer)
	: Super(objectInitializer)
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom attached to the root (capsule)
	CameraBoom = objectInitializer.CreateDefaultSubobject<USpringArmComponent>(this, TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Rotation of the character should not affect rotation of boom
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->SocketOffset = FVector(0.f,0.f,75.f);
	CameraBoom->RelativeRotation = FRotator(0.f,180.f,0.f);

	// Create a camera and attach to boom
	SideViewCameraComponent = objectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("SideViewCamera"));
	SideViewCameraComponent->AttachTo(CameraBoom, USpringArmComponent::SocketName);
	SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = false; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
	


	
	

	// Default max number of the jumps allowed in the air
	MaxJumps = 2;
	JumpCounter = 0;

	// User hold the button control the jump height
	JumpMaxHoldTime = 0.1;

	CollectionSphere = objectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("CollectionSphere"));
	CollectionSphere->SetSphereRadius(100.0f);
	CollectionSphere->AttachTo(RootComponent);
}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void ACharacterBase::SetupPlayerInputComponent(class UInputComponent* inputComponent)
{
	// set up gameplay key bindings
	inputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	inputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	// fire collect pickups
	inputComponent->BindAction("Pick", IE_Pressed, this, &ACharacterBase::CollectPickUps);

	inputComponent->BindAxis("MoveRight", this, &ACharacterBase::MoveRight);
	inputComponent->BindAxis("MoveUp", this, &ACharacterBase::MoveUp);
}

void ACharacterBase::MoveRight(float value)
{
	// add movement in that direction
	AddMovementInput(FVector(0.f,-1.f,0.f), value);
	// update custom orientation of the character depending on the move direction
	this->OrientationProcess(value);
}

void ACharacterBase::MoveUp(float value)
{
	AddMovementInput(FVector(-1.0f, 0.0f, 0.0f), value);
}

void ACharacterBase::OrientationProcess(float value)
{
	// Flip character facing direction
	if (value > 0.0f)
	{
		this->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
	}
	else if (value < 0.0f)
	{
		this->SetActorRotation(FRotator(0.0f, 180.0f, 0.0f));
	}
}

void ACharacterBase::OnMovementModeChanged(EMovementMode prevMovementMode, uint8 prevCustomMode)
{
	Super::OnMovementModeChanged(prevMovementMode, prevCustomMode);

	// Reset JumpCounter to 0, if character is no longer falling
	if (GetCharacterMovement()->IsMovingOnGround())
	{
		JumpCounter = 0;
	}
}

void ACharacterBase::Jump()
{
	// If character is falling, check whether it is allowed to do extra jumps
	// Special case: if we allow double jump, when character walks off the edge without jump, only 1 jump is allowed.
	if (GetCharacterMovement()->IsFalling())
	{
		if (++JumpCounter < MaxJumps)
		{
			Super::Jump();
		}
	}
	else
	{
		Super::Jump();
	}
}

void ACharacterBase::CollectPickUps()
{
	TArray<AActor*> actors;
	CollectionSphere->GetOverlappingActors(actors);

	for (AActor* actor : actors)
	{
		APickup* const pickup = Cast<APickup>(actor);
		if (pickup && !pickup->IsPendingKill() && pickup->bIsActive)
		{
			pickup->OnCollection(*GetCharacterController());
		}
	}
}

ACharacterController* ACharacterBase::GetCharacterController() const
{
	return Cast<ACharacterController>(GetController());
}