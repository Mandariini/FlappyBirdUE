// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FlappyHUD.generated.h"

class UGameOver;
class UFlappyOverlay;
/**
 *
 */
UCLASS()
class FLAPPYBIRD_API AFlappyHUD : public AHUD {
  GENERATED_BODY()

public:
  void ShowGameOver();

protected:
  virtual void BeginPlay() override;

private:
  UPROPERTY(EditDefaultsOnly, Category = FlappyBird)
  TSubclassOf<UFlappyOverlay> FlappyOverlayClass;

  UPROPERTY()
  UFlappyOverlay *FlappyOverlay;

  UPROPERTY(EditDefaultsOnly, Category = FlappyBird)
  TSubclassOf<UGameOver> GameOverWidgetClass;

  UPROPERTY()
  UGameOver *GameOverWidget;

public:
  FORCEINLINE UFlappyOverlay *GetFlappyOverlay() const { return FlappyOverlay; }
};
