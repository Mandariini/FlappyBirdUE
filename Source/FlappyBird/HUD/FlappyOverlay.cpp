// Fill out your copyright notice in the Description page of Project Settings.

#include "FlappyOverlay.h"

#include "Components/TextBlock.h"

void UFlappyOverlay::SetPoints(const int32 Points) const {
  check(PointsText);

  const auto PointsTextValue = FText::FromString(FString::Printf(TEXT("Points: %d"), Points));
  PointsText->SetText(PointsTextValue);
}
