// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObstacleGenerator.generated.h"

class APillar;

UCLASS()
class FLAPPYBIRD_API AObstacleGenerator : public AActor {
  GENERATED_BODY()

public:
  AObstacleGenerator();

  virtual void Tick(float DeltaTime) override;

  UFUNCTION(BlueprintCallable)
  void SpawnPillars();

protected:
  virtual void BeginPlay() override;

  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pillar)
  float PillarGap = 100.f;

private:
  UPROPERTY(EditAnywhere, Category = Pillar, Meta = (MakeEditWidget = true))
  FVector GapMaxSpot;

  UPROPERTY(EditAnywhere, Category = Pillar, Meta = (MakeEditWidget = true))
  FVector GapMinSpot;

  UPROPERTY(EditAnywhere, Category = Pillar)
  float PillarMoveSpeed = 100.f;

  UPROPERTY(EditAnywhere, Category = Pillar)
  float PillarSpawnInterval = 10.f;

  UPROPERTY(EditDefaultsOnly, Category = Pillar)
  TSubclassOf<APillar> PillarClass;

  UPROPERTY(VisibleAnywhere, Category = Pillar)
  TArray<APillar *> Pillars;
};
