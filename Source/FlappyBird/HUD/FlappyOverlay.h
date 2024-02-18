// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "FlappyOverlay.generated.h"

/**
 *
 */
UCLASS()
class FLAPPYBIRD_API UFlappyOverlay : public UUserWidget {
  GENERATED_BODY()

public:
  void SetPoints(const int32 Points) const;

private:
  UPROPERTY(meta = (BindWidget))
  class UTextBlock *PointsText;
};
