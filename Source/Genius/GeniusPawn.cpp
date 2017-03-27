// Fill out your copyright notice in the Description page of Project Settings.

#include "Genius.h"
#include "GeniusPawn.h"


// Sets default values
AGeniusPawn::AGeniusPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->ProjectionMode = ECameraProjectionMode::Orthographic;
	Camera->OrthoWidth = 2048.0f;
	Camera->SetupAttachment(RootComponent);

	AutoPossessPlayer = EAutoReceiveInput::Player0;

}

// Called when the game starts or when spawned
void AGeniusPawn::BeginPlay()
{
	Super::BeginPlay();
	Score = 0;

}

// Called every frame
void AGeniusPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AGeniusPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void AGeniusPawn::SetScore(int NewScore) {
	Score = NewScore;
}

int AGeniusPawn::GetScore() {
	return Score;
}