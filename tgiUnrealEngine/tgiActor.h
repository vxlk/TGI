/*
The Actor to be inherited from in the game
*/

//#ifdef TGI_UNREAL

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "tgiCppAPI.h"
#include "TGIActor.generated.h"

/*
Inherit from this object to put twitch functionality into your actor
*/
UCLASS(config = Game)
class ATGIActor : public AActor
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	ATGIActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	// Called every frame - do not change - needed for bot to run
	void Tick(float DeltaTime) override;
	//a customizable version of the tick function
	virtual void TGITick(float DeltaTime);

	//API Functions
	inline const bool isRunning() { return tgi.Get()->isRunning; }
	//todo: check if start is ok -> display error message
	inline void startPoll()		  { tgi.Get()->startPoll(); }
	void closePoll()				  { if (this->isRunning()) this->tgi.Get()->closePoll(); }
	void Update();

protected:
	TSharedPtr<TGIUnrealAPI> tgi;
	
};

//#endif