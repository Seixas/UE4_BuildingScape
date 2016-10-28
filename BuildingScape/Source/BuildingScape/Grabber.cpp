// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingScape.h"
#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandleComponent();
	SetupInputComponent();

}

/// look for attached Physics Handle
void UGrabber::FindPhysicsHandleComponent(){
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle)
	{
		// Physics handle is found
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing physics handle component"), *GetOwner()->GetName());
	}
}

///look for attached InputComponent (only appears at run time
void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Input component component found"));
		///bind the input axis
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing input component component"), *GetOwner()->GetName());
	}
}


void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab key pressed"));

	/// LINE TRACE and reach any actors with physics body collision channel
	GetFirstPhysicsBodyInReach();

	// if we hit something then attach a physics handle
	// TODO attach physics handle
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab key release"));
	// TODO release physics handle
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// if the physics handle is attached
		//move the object that we're holding
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	/// get player view point this tick
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	FVector LineTraceEnd = PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * Reach);

	// draw a red trace in the world to visualise
	DrawDebugLine(
		GetWorld(),
		PlayerViewPointLocation,
		LineTraceEnd,
		FColor(255, 0, 0),
		false,
		0.f,
		0.f,
		10.f
	);

	/// Setup query parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	/// Line-trace (AKA ray-cast) out to reach distance
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);
	/// see what we hit
	AActor* ActorHit = Hit.GetActor(); //get an AActor* from Hit
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Line trace hit Object: %s"), *(ActorHit->GetName()));
	}
	return FHitResult();
}


