// Fill out your copyright notice in the Description page of Project Settings.

#include "GameOver.h"

#include "Components/TextBlock.h"
#include "FlappyBird/FlappyBirdGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UGameOver::SetPointsTexts() {
  auto FlappyBirdGameInstance = Cast<UFlappyBirdGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
  if (!FlappyBirdGameInstance) {
    return;
  }

  const auto PointsTextValue =
    FText::FromString(FString::Printf(TEXT("Points: %d"), FlappyBirdGameInstance->GetLatestPoints()));
  PointsText->SetText(PointsTextValue);

  const auto PersonalBestTextValue =
    FText::FromString(FString::Printf(TEXT("Personal best: %d"), FlappyBirdGameInstance->GetPersonalBest()));
  PersonalBestText->SetText(PersonalBestTextValue);
}
