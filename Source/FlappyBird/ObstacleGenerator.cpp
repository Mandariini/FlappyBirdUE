// Fill out your copyright notice in the Description page of Project Settings.

#include "ObstacleGenerator.h"

#include "Pillar.h"

AObstacleGenerator::AObstacleGenerator() { PrimaryActorTick.bCanEverTick = true; }

void AObstacleGenerator::BeginPlay() { Super::BeginPlay(); }

void AObstacleGenerator::Tick(float DeltaTime) {
  Super::Tick(DeltaTime);

  // Move pillars towards player
  for (const auto Pillar : Pillars) {
    if (IsValid(Pillar)) {
      Pillar->SetActorLocation(Pillar->GetActorLocation() + FVector(-1.f, 0.f, 0.f) * PillarMoveSpeed * DeltaTime);
    }
  }
}

void AObstacleGenerator::SpawnPillars() {
  if (!PillarClass) {
    return;
  }

  auto World = GetWorld();
  if (World) {
    const auto GapMiddlePosition = FMath::RandRange(GapMinSpot.Z, GapMaxSpot.Z);
    const auto SpawnLocation = GetActorLocation() + FVector(0.f, 0.f, GapMiddlePosition);

    const auto SpawnedPillar = World->SpawnActor<APillar>(PillarClass, SpawnLocation, FRotator::ZeroRotator);
    if (!SpawnedPillar) {
      return;
    }

    SpawnedPillar->SetGapSize(PillarGap);
    SpawnedPillar->SetLifeSpan(10.f);

    Pillars.Push(SpawnedPillar);
  }
}
