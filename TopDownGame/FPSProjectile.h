// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "FPSProjectile.generated.h"

UCLASS()
class TOPDOWNGAME_API AFPSProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSProjectile();
    AFPSProjectile(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

    /** Sphere collision component */
    UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
    USphereComponent* CollisionComp;
    
    /** Projectile movement component */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Movement)
    UProjectileMovementComponent* ProjectileMovement;
    
    /** inits velocity of the projectile in the shoot direction */
    UFUNCTION()
    void InitVelocity(const FVector& ShootDirection);
};
