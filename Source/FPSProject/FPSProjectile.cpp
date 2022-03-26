// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSProjectile.h"

// Sets default values
AFPSProjectile::AFPSProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InitialLifeSpan = 3.0f;

	if (CollisionComponent == nullptr)
	{
		CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("ProjectileCollisionComponent"));
		check(CollisionComponent != nullptr);

		CollisionComponent->SetSphereRadius(15.f);
		RootComponent = CollisionComponent;
	}

	if (ProjectileMovementComponent == nullptr)
	{
		ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
		check(ProjectileMovementComponent != nullptr);

		ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
		ProjectileMovementComponent->InitialSpeed = 3000.0f;
		ProjectileMovementComponent->MaxSpeed = 3000.0f;
		ProjectileMovementComponent->bRotationFollowsVelocity = true;
		ProjectileMovementComponent->bShouldBounce = true;
		ProjectileMovementComponent->Bounciness = 0.3f;
		ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	}

	if (MeshComponent == nullptr)
	{
		MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("/Game/Meshes/Projectiles/Sphere.Sphere"));
		if (Mesh.Succeeded())
		{
			MeshComponent->SetStaticMesh(Mesh.Object);
		}
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("/Game/Meshes/Projectiles/SphereMaterial.SphereMaterial"));
	if (Material.Succeeded())
	{
		MaterialInstance = UMaterialInstanceDynamic::Create(Material.Object, MeshComponent);
	}
	MeshComponent->SetMaterial(0, MaterialInstance);
	MeshComponent->SetRelativeScale3D(FVector(0.09f, 0.09f, 0.09f));
	MeshComponent->SetupAttachment(RootComponent);
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

void AFPSProjectile::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}