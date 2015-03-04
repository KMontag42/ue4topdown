// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "TopDownGame.h"
#include "TopDownGamePlayerController.h"
#include "AI/Navigation/NavigationSystem.h"

ATopDownGamePlayerController::ATopDownGamePlayerController(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
    bShowMouseCursor = true;
    DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ATopDownGamePlayerController::PlayerTick(float DeltaTime)
{
    Super::PlayerTick(DeltaTime);
}

void ATopDownGamePlayerController::SetupInputComponent()
{
    // set up gameplay key bindings
    Super::SetupInputComponent();
    
    InputComponent->BindAction("Jump", IE_Pressed, this, &ATopDownGamePlayerController::Jump);
    InputComponent->BindAction("ShootProjectile", IE_Pressed, this, &ATopDownGamePlayerController::ShootProjectile);
    
    InputComponent->BindAxis("MoveForward", this, &ATopDownGamePlayerController::MoveForward);
    InputComponent->BindAxis("MoveRight", this, &ATopDownGamePlayerController::MoveRight);
}

void ATopDownGamePlayerController::MoveForward(float AxisValue)
{
    if (AxisValue != 0.0f)
    {
        // find out which way is right
        FRotator Rotation = GetControlRotation();
        // Limit pitch when walking or falling
        UCharacterMovementComponent* CM = GetCharacter()->GetCharacterMovement();
        if ( CM->IsMovingOnGround() || CM->IsFalling() )
        {
            Rotation.Pitch = 0.0f;
        }
        const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
        // add movement in that direction
        GetCharacter()->AddMovementInput(Direction, AxisValue);
    }
}

void ATopDownGamePlayerController::MoveRight(float AxisValue)
{
    if (AxisValue != 0.0f)
    {
        // find out which way is right
        const FRotator Rotation = GetControlRotation();
        const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
        // add movement in that direction
        GetCharacter()->AddMovementInput(Direction, AxisValue);
    }
}

void ATopDownGamePlayerController::Jump()
{
    GetCharacter()->Jump();
}

void ATopDownGamePlayerController::ShootProjectile()
{
    // try and fire a projectile
    ATopDownGameCharacter* character = Cast<ATopDownGameCharacter>(GetCharacter());
    if (character->ProjectileClass != NULL)
    {
        UWorld* const World = GetWorld();
        if (World)
        {
            FActorSpawnParameters SpawnParams;
            SpawnParams.Owner = this;
            SpawnParams.Instigator = Instigator;
            // spawn the projectile at the muzzle
            AFPSProjectile* const Projectile = World->SpawnActor<AFPSProjectile>(character->ProjectileClass, GetCharacter()->GetActorLocation(), GetCharacter()->GetActorRotation(), SpawnParams);
            if (Projectile)
            {
                // find launch direction
                // Trace to see what is under the mouse cursor
                FHitResult Hit;
                GetHitResultUnderCursor(ECC_Visibility, false, Hit);
                
                if (Hit.bBlockingHit)
                {
                    FVector location = FVector::CrossProduct(Hit.ImpactPoint, GetCharacter()->GetActorLocation());
                    location.Normalize();
                    Projectile->InitVelocity(location);
                }
            }
        }
    }
}

