// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "GameOver.generated.h"

/**
 *
 */
UCLASS()
class FLAPPYBIRD_API UGameOver : public UUserWidget {
  GENERATED_BODY()

public:
  void SetPointsTexts();

private:
  UPROPERTY(meta = (BindWidget))
  class UTextBlock *PointsText;

  UPROPERTY(meta = (BindWidget))
  class UTextBlock *PersonalBestText;
};
