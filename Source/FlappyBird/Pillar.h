// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pillar.generated.h"

class UBoxComponent;

UCLASS()
class FLAPPYBIRD_API APillar : public AActor {
  GENERATED_BODY()

public:
  APillar();

  UFUNCTION()
  void SetGapSize(float NewGapSize);

protected:
  virtual void BeginPlay() override;

  UFUNCTION()
  virtual void OnAfterPipeBoxOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
                                     UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                     const FHitResult &SweepResult);

private:
  UPROPERTY(EditAnywhere, Category = Pillar)
  UStaticMeshComponent *PillarMeshUpper;

  UPROPERTY(EditAnywhere, Category = Pillar)
  UStaticMeshComponent *PillarMeshLower;

  UPROPERTY(EditAnywhere, Category = Pillar)
  UBoxComponent *AfterPipeBoxCollision;

  UPROPERTY(EditAnywhere, Category = Pillar)
  float GapSize;
};
