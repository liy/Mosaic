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

	GetWorldTimerManager().SetTimer(this, &ACharacterBase::ResetInputStack, ResetDelay, true);
}

void ACharacterBase::SetupPlayerInputComponent(class UInputComponent* inputComponent)
{
	// set up gameplay key bindings
	inputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	inputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	// fire collect pickups
	inputComponent->BindAction("Action", IE_Pressed, this, &ACharacterBase::CollectPickUps);

	inputComponent->BindAxis("MoveRight", this, &ACharacterBase::MoveRight);
	inputComponent->BindAxis("MoveUp", this, &ACharacterBase::MoveUp);

	// fighting related
	inputComponent->BindAction("Action", IE_Pressed, this, &ACharacterBase::ActionPressed);
	inputComponent->BindAction("Action", IE_Released, this, &ACharacterBase::ActionReleased);
	inputComponent->BindAction("Light", IE_Pressed, this, &ACharacterBase::LightPressed);
	inputComponent->BindAction("Light", IE_Released, this, &ACharacterBase::LightReleased);
	inputComponent->BindAction("Medium", IE_Pressed, this, &ACharacterBase::MediumPressed);
	inputComponent->BindAction("Medium", IE_Released, this, &ACharacterBase::MediumReleased);
	inputComponent->BindAction("Heavy", IE_Pressed, this, &ACharacterBase::HeavyPressed);
	inputComponent->BindAction("Heavy", IE_Released, this, &ACharacterBase::HeavyReleased);
	inputComponent->BindAction("Defence", IE_Pressed, this, &ACharacterBase::DefencePressed);
	inputComponent->BindAction("Defence", IE_Released, this, &ACharacterBase::DefenceReleased);
	inputComponent->BindAction("Jump", IE_Pressed, this, &ACharacterBase::JumpPressed);
	inputComponent->BindAction("Jump", IE_Released, this, &ACharacterBase::JumpReleased);
}

void ACharacterBase::MoveRight(float value)
{
	if (value < 0){
		OnActionInput(EInputAction::Left);
	}
	else if (value > 0)
	{
		OnActionInput(EInputAction::Right);
	}

	// add movement in that direction
	AddMovementInput(FVector(0.f,-1.f,0.f), value);
	// update custom orientation of the character depending on the move direction
	this->OrientationProcess(value);
}

void ACharacterBase::MoveUp(float value)
{
	if (value < 0){
		OnActionInput(EInputAction::Down);
	}
	else if (value > 0)
	{
		OnActionInput(EInputAction::Up);
	}

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
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("JumpFirst"));

	OnActionInput(EInputAction::Jump, EInputEvent::IE_Pressed);

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

///////
// Action related
///////
void ACharacterBase::LightPressed()
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("LightPressed"));

	OnActionInput(EInputAction::Light);
}

void ACharacterBase::LightReleased()
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("LightReleased"));
}

void ACharacterBase::MediumPressed()
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("MediumPressed"));
	OnActionInput(EInputAction::Medium);
}

void ACharacterBase::MediumReleased()
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("MediumReleased"));
}

void ACharacterBase::HeavyPressed()
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("HeavyPressed"));
	OnActionInput(EInputAction::Heavy);
}

void ACharacterBase::HeavyReleased()
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("HeavyReleased"));
}

void ACharacterBase::DefencePressed()
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("DefencePressed"));
	OnActionInput(EInputAction::Defence);
}

void ACharacterBase::DefenceReleased()
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("DefenceReleased"));
}

void ACharacterBase::JumpPressed()
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("JumpPressed"));
	OnActionInput(EInputAction::Jump);
}

void ACharacterBase::JumpReleased()
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("JumpReleased"));
}

void ACharacterBase::ActionPressed()
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("ActionPressed"));
	OnActionInput(EInputAction::Action);
}

void ACharacterBase::ActionReleased()
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("ActionReleased"));
}

void ACharacterBase::OnActionInput(EInputAction action, EInputEvent event)
{
	PushInputAction(action);

	// TODO: Check the stack for triggering action pattern
	for (int i = 0; i < ActionStack.Num()-1; ++i)
	{
		if ((ActionStack[i] == EInputAction::Light && ActionStack[i+1] == EInputAction::Medium) || (ActionStack[i] == EInputAction::Medium && ActionStack[i+1] == EInputAction::Light))
		{
			GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Green, TEXT("!!"));
		}
	}
}

void ACharacterBase::PushInputAction(EInputAction action)
{
	// Delay stack reset timer
	GetWorldTimerManager().SetTimer(this, &ACharacterBase::ResetInputStack, ResetDelay, true);

	ActionStack.Add(action);
}

void ACharacterBase::ResetInputStack()
{
	//GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Red, TEXT("ResetInputStack"));
	ActionStack.Reset();
}

// Need a typed paramter to determin which action to trigger
void ACharacterBase::OnTriggerAction()
{

}