// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "GeniusGrid.generated.h"

UCLASS()
class GENIUS_API AGeniusGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGeniusGrid();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	bool Verify(class AGeniusColor* ColorClicked);
	void GameOver();

	void SetFreeze(bool NewFreeze);
	bool GetFreeze();

private:

	UPROPERTY(EditAnywhere)
	USceneComponent* Root;

	TSubclassOf<class AGeniusColor> Red;
	TSubclassOf<class AGeniusColor> Blue;
	TSubclassOf<class AGeniusColor> Green;
	TSubclassOf<class AGeniusColor> Yellow;
	TSubclassOf<class UUserWidget> GameOverWidget;
	int Index;
	bool bLight;
	FTimerHandle ShowGenius;
	int NumOfClicks;
	bool bFreeze;

	TArray<class AGeniusColor*> GeniusParts;
	TArray<int> Sequence;

	void AddNewColor();
	void Show();
	
};
