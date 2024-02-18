// Fill out your copyright notice in the Description page of Project Settings.

#include "FlappyCharacter.h"

#include "GameFramework/GameModeBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "FlappyBirdGameInstance.h"
#include "FlappyBirdGameModeBase.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "HUD/FlappyHUD.h"
#include "HUD/FlappyOverlay.h"

AFlappyCharacter::AFlappyCharacter() {
  PrimaryActorTick.bCanEverTick = true;

  CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
  CapsuleComponent->SetSimulatePhysics(true);
  CapsuleComponent->SetNotifyRigidBodyCollision(true);
  SetRootComponent(CapsuleComponent);

  BirdMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BirdMesh"));
  BirdMesh->SetupAttachment(GetRootComponent());

  SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
  SpringArm->SetupAttachment(GetRootComponent());
  SpringArm->TargetArmLength = 400.0f;
  SpringArm->bDoCollisionTest = false;

  Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
  Camera->SetupAttachment(SpringArm);
}

void AFlappyCharacter::BeginPlay() {
  Super::BeginPlay();

  // Add Input Mapping Context
  if (APlayerController *PlayerController = Cast<APlayerController>(Controller)) {
    if (UEnhancedInputLocalPlayerSubsystem *Subsystem =
          ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
      Subsystem->AddMappingContext(DefaultMappingContext, 0);
    }
  }

  auto PlayerController = Cast<APlayerController>(GetController());
  if (PlayerController) {
    auto FlappyHUD = Cast<AFlappyHUD>(PlayerController->GetHUD());
    if (FlappyHUD) {
      FlappyOverlay = FlappyHUD->GetFlappyOverlay();
      if (FlappyOverlay) {
        FlappyOverlay->SetPoints(0);
      }
    }
  }

  CapsuleComponent->OnComponentHit.AddDynamic(this, &AFlappyCharacter::OnHit);
}

void AFlappyCharacter::OnHit(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp,
                             FVector NormalImpulse, const FHitResult &Hit) {
  bDied = true;

  if (auto World = GetWorld()) {
    UGameplayStatics::SetGamePaused(World, true);

    auto FlappyBirdGameInstance = Cast<UFlappyBirdGameInstance>(GetGameInstance());
    if (FlappyBirdGameInstance) {
      FlappyBirdGameInstance->SetPoints(Points);
    }

    auto PlayerController = Cast<APlayerController>(GetController());
    if (PlayerController) {
      auto FlappyHUD = Cast<AFlappyHUD>(PlayerController->GetHUD());
      if (FlappyHUD) {
        FlappyHUD->ShowGameOver();
      }
    }
  }
}

void AFlappyCharacter::AddPoints(const int32 PointsToAdd) {
  if (FlappyOverlay) {
    this->Points += PointsToAdd;
    this->FlappyOverlay->SetPoints(this->Points);
  }
}

void AFlappyCharacter::Flap() {
  CapsuleComponent->SetPhysicsLinearVelocity(FVector(0.f, 0.f, 0.f));
  CapsuleComponent->AddImpulse(FVector(0.f, 0.f, FlapStrength));
}

void AFlappyCharacter::OnRestart() {
  if (bDied) {
    if (auto World = GetWorld()) {
      if (auto GameMode = Cast<AFlappyBirdGameModeBase>(UGameplayStatics::GetGameMode(World))) {
        UGameplayStatics::OpenLevel(this, FName("FlappyMap"), true);
      }
    }
  }
}

void AFlappyCharacter::Tick(float DeltaTime) {
  Super::Tick(DeltaTime);

  CapsuleComponent->AddImpulse(FVector(0.f, 0.f, GravityAmount));
}

void AFlappyCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent) {
  Super::SetupPlayerInputComponent(PlayerInputComponent);

  const auto EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
  if (!EnhancedInputComponent) {
    return;
  }

  if (FlapAction) {
    EnhancedInputComponent->BindAction(FlapAction, ETriggerEvent::Triggered, this, &AFlappyCharacter::Flap);
  }
  if (ResetAction) {
    ResetAction->bTriggerWhenPaused = true;
    EnhancedInputComponent->BindAction(ResetAction, ETriggerEvent::Triggered, this, &AFlappyCharacter::OnRestart);
  }
}
