// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSCharacter.h"

// Sets default values
AFPSCharacter::AFPSCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FPSCamera"));
	check(FPSCameraComponent != nullptr);

	FPSCameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));
	FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));
	FPSCameraComponent->bUsePawnControlRotation = true;

	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FPSMesh"));
	check(FPSMesh != nullptr);

	FPSMesh->SetOnlyOwnerSee(true);
	FPSMesh->SetupAttachment(FPSCameraComponent);
	// Disable shadows for uniform mesh
	FPSMesh->bCastDynamicShadow = false;
	FPSMesh->CastShadow = false;
	GetMesh()->SetOwnerNoSee(true);

	JumpMaxCount = 2;
}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(GEngine != nullptr);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("I'm a FPS Character"));
}

// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AFPSCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AFPSCharacter::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AFPSCharacter::LookUp);

	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AFPSCharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Released, this, &AFPSCharacter::StopJumping);
}

void AFPSCharacter::MoveForward(float value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, value);
}

void AFPSCharacter::MoveRight(float value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, value);
}

void AFPSCharacter::Turn(float value)
{
	AddControllerYawInput(value);
}

void AFPSCharacter::LookUp(float value)
{
	AddControllerPitchInput(value);
}