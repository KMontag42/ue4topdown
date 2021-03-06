// Fill out your copyright notice in the Description page of Project Settings.

#include "TopDownGame.h"
#include "FPSProjectile.h"


// Sets default values
AFPSProjectile::AFPSProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

AFPSProjectile::AFPSProjectile(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
    // Use a sphere as a simple collision representation
    CollisionComp = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("SphereComp"));
    CollisionComp->InitSphereRadius(15.0f);
    RootComponent = CollisionComp;
    
    // Use a ProjectileMovementComponent to govern this projectile's movement
    ProjectileMovement = ObjectInitializer.CreateDefaultSubobject<UProjectileMovementComponent>(this, TEXT("ProjectileComp"));
    ProjectileMovement->UpdatedComponent = CollisionComp;
    ProjectileMovement->InitialSpeed = 3000.f;
    ProjectileMovement->MaxSpeed = 3000.f;
    ProjectileMovement->bRotationFollowsVelocity = true;
    ProjectileMovement->bShouldBounce = true;
    ProjectileMovement->Bounciness  = 0.3f;
}

void AFPSProjectile::InitVelocity(const FVector& ShootDirection)
{
    if (ProjectileMovement)
    {
        // set the projectile's velocity to the desired direction
        ProjectileMovement->Velocity = ShootDirection * ProjectileMovement->InitialSpeed;
    }
}

// Called when the game starts or when spawned
void AFPSProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSProjectile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

