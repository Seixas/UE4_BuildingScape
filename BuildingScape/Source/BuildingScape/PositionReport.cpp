// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingScape.h"
#include "PositionReport.h"


// Sets default values for this component's properties
UPositionReport::UPositionReport() //constructor
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPositionReport::BeginPlay()
{
	Super::BeginPlay();
	// getowner is returning a pointer to AActor, we look through that pointer
	// to return a FString method (hover the functions to see what they do)
	FString ObjectName = GetOwner()->GetName();
	//if i use only GetTransform() we get all info about location/rotation/scale, we can specify Getting what we want
	FString ObjectPos = GetOwner()->GetTransform().GetLocation().ToString();
	UE_LOG(LogTemp, Warning, TEXT("%s is at %s"), *ObjectName, *ObjectPos);


}


// Called every frame
void UPositionReport::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

