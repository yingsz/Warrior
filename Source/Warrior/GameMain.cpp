// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMain.h"
#include "LuaManager.h"
#include "Application.h"
// Sets default values
AGameMain::AGameMain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGameMain::BeginPlay()
{
	Super::BeginPlay();
	Singleton<LuaManager>::GetInstance()->DoFile(TEXT("MobileStarterContent/Lua/launch.lua"));
}

void AGameMain::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	Singleton<Application>::GetInstance()->Quit();
	Singleton<Application>::Dispose();
	Singleton<LuaManager>::Dispose();
}

// Called every frame
void AGameMain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Singleton<Application>::GetInstance()->Update(DeltaTime);
}

