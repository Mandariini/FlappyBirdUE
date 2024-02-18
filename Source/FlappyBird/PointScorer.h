// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "PointScorer.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPointScorer : public UInterface {
  GENERATED_BODY()
};

/**
 *
 */
class FLAPPYBIRD_API IPointScorer {
  GENERATED_BODY()

public:
  virtual void AddPoints(const int32 PointsToAdd) = 0;
};
