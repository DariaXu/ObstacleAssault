// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetActorLocation();
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
}

void AMovingPlatform::MovePlatform(float DeltaTime){
	FVector CurrentLocation = GetActorLocation();
	CurrentLocation += velocity*DeltaTime;
	SetActorLocation(CurrentLocation);

	if (ShouldPlatformReturn()){
		// UE_LOG(LogTemp,Display, TEXT("%s Overshoot: %f"), *GetName(),distance-MovedDistance);
		StartLocation += velocity.GetSafeNormal()*MovedDistance;
		SetActorLocation(StartLocation);
		// StartLocation= CurrentLocation;
		velocity *= -1;
	}
}

void AMovingPlatform::RotatePlatform(float DeltaTime){
	// UE_LOG(LogTemp, Display, TEXT("%s Rotating..."), *GetName());
	AddActorLocalRotation(RotationVelocity*DeltaTime);
}

bool AMovingPlatform::ShouldPlatformReturn() const
{
	return GetDistanceMoved() > MovedDistance;
}

float AMovingPlatform::GetDistanceMoved() const
{
	return FVector::Dist(StartLocation,GetActorLocation());
}