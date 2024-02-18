// Fill out your copyright notice in the Description page of Project Settings.

#include "FlappyHUD.h"

#include "Blueprint/UserWidget.h"

#include "FlappyOverlay.h"
#include "GameOver.h"

void AFlappyHUD::ShowGameOver() {
  if (GameOverWidget) {
    GameOverWidget->SetPointsTexts();
    GameOverWidget->AddToViewport();
  }
}

void AFlappyHUD::BeginPlay() {
  Super::BeginPlay();

  UWorld *World = GetWorld();
  if (World) {
    APlayerController *Controller = World->GetFirstPlayerController();
    if (Controller && FlappyOverlayClass) {
      FlappyOverlay = CreateWidget<UFlappyOverlay>(Controller, FlappyOverlayClass);
      FlappyOverlay->AddToViewport();

      GameOverWidget = CreateWidget<UGameOver>(Controller, GameOverWidgetClass);
    }
  }
}
