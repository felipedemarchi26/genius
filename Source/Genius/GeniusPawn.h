// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "GeniusPawn.generated.h"

UCLASS()
class GENIUS_API AGeniusPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGeniusPawn();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	void SetScore(int NewScore);
	UFUNCTION(BlueprintCallable, Category = "Score")
	int GetScore();

private:

	UPROPERTY(EditAnywhere)
		UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
		int Score;
	
};
