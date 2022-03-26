// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"

#include "FPSProjectile.generated.h"


UCLASS()
class FPSPROJECT_API AFPSProjectile : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleDefaultsOnly, Category = "Projectile")
	USphereComponent* CollisionComponent;

public:
	// Sets default values for this actor's properties
	AFPSProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
