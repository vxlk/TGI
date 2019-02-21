// Fill out your copyright notice in the Description page of Project Settings.

#include "tgiActor.h"

//#ifdef TGI_UNREAL

// Sets default values
ATGIActor::ATGIActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	tgi = MakeShareable(new TGIUnrealAPI);
}

// Called when the game starts or when spawned
void ATGIActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame -> needed for the app to work - do not override
void ATGIActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (tgi.Get()->isRunning) tgi.Get()->update();
}

//An overridable version of tick
void ATGIActor::TGITick(float DeltaTime)
{
	this->Tick(DeltaTime);
}

void ATGIActor::Update()
{
	tgi.Get()->update();
}

//#endif