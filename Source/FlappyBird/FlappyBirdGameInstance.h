// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "FlappyBirdGameInstance.generated.h"

/**
 *
 */
UCLASS()
class FLAPPYBIRD_API UFlappyBirdGameInstance : public UGameInstance {
  GENERATED_BODY()

public:
  void SetPoints(const int32 NewPoints);

  FORCEINLINE int32 GetLatestPoints() { return CurrentPoints; }
  FORCEINLINE int32 GetPersonalBest() { return PersonalBestPoints; }

private:
  UPROPERTY()
  int32 CurrentPoints = 0;

  UPROPERTY()
  int32 PersonalBestPoints = 0;
};
