// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSProjectile.h"

// Sets default values
AFPSProjectile::AFPSProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (CollisionComponent == nullptr)
	{
		CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("ProjectileCollisionComponent"));
		check(CollisionComponent != nullptr);

		CollisionComponent->SetSphereRadius(15.f);
		RootComponent = CollisionComponent;
	}
}

// Called when the game starts or when spawned
void AFPSProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AFPSProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
