// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "PointScorer.h"

#include "FlappyCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class FLAPPYBIRD_API AFlappyCharacter : public APawn, public IPointScorer {
  GENERATED_BODY()

public:
  AFlappyCharacter();
  virtual void Tick(float DeltaTime) override;
  virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

  UPROPERTY(EditDefaultsOnly, Category = Flying)
  float GravityAmount = 15.f;

  UPROPERTY(EditDefaultsOnly, Category = Flying)
  float FlapStrength = 1000.f;

protected:
  virtual void BeginPlay() override;

  UFUNCTION()
  virtual void OnHit(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp,
                     FVector NormalImpulse, const FHitResult &Hit);

  UFUNCTION() // TODO: Use or not?
  virtual void AddPoints(const int32 PointsToAdd) override;

  UFUNCTION() // TODO: Use or not?
  void Flap();

private:
  void OnRestart();

  /**
   * Components
   */
  UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
  UCapsuleComponent *CapsuleComponent;

  UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
  UStaticMeshComponent *BirdMesh;

  UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
  USpringArmComponent *SpringArm;

  UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
  UCameraComponent *Camera;

  /**
   * Input
   */
  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
  UInputMappingContext *DefaultMappingContext;

  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
  UInputAction *FlapAction;

  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
  UInputAction *ResetAction;

  /**
   * Attributes
   */
  UPROPERTY(VisibleAnywhere)
  int32 Points;

  /**
   * Other
   */
  UPROPERTY()
  class UFlappyOverlay *FlappyOverlay;

  bool bDied = false;
};
