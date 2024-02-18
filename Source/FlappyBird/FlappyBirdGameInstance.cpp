// Fill out your copyright notice in the Description page of Project Settings.

#include "FlappyBirdGameInstance.h"

void UFlappyBirdGameInstance::SetPoints(const int32 NewPoints) {
  CurrentPoints = NewPoints;
  if (CurrentPoints > PersonalBestPoints) {
    PersonalBestPoints = CurrentPoints;
  }
}
