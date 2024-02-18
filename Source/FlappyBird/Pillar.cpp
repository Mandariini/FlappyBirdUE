// Fill out your copyright notice in the Description page of Project Settings.

#include "Pillar.h"

#include "Components/BoxComponent.h"

#include "PointScorer.h"

APillar::APillar() {
  PrimaryActorTick.bCanEverTick = false;

  RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

  PillarMeshUpper = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PillarMeshUpper"));
  PillarMeshUpper->SetupAttachment(RootComponent);

  PillarMeshLower = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PillarMeshLower"));
  PillarMeshLower->SetupAttachment(RootComponent);

  AfterPipeBoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapBox"));
  AfterPipeBoxCollision->SetupAttachment(RootComponent);
}

void APillar::SetGapSize(float NewGapSize) {
  PillarMeshUpper->AddRelativeLocation(FVector(0.f, 0.f, NewGapSize));
  PillarMeshLower->AddRelativeLocation(FVector(0.f, 0.f, -NewGapSize));
}

void APillar::BeginPlay() {
  Super::BeginPlay();

  AfterPipeBoxCollision->OnComponentBeginOverlap.AddDynamic(this, &APillar::OnAfterPipeBoxOverlap);
}

void APillar::OnAfterPipeBoxOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
                                    UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                    const FHitResult &SweepResult) {
  const auto PointScorerInterface = Cast<IPointScorer>(OtherActor);
  if (PointScorerInterface) {
    PointScorerInterface->AddPoints(1);
  }
}
