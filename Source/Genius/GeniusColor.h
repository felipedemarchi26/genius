// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "GeniusColor.generated.h"

UCLASS()
class GENIUS_API AGeniusColor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGeniusColor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void SetIndex(int NewIndex);
	int GetIndex();
	void ChangeSprite();
	void SetOwnerGrid(class AGeniusGrid* Grid);

private:

	UPROPERTY(EditAnywhere)
	class UPaperSpriteComponent* Sprite;

	UPROPERTY(EditAnywhere)
	class UPaperSprite* SpriteOff;

	UPROPERTY(EditAnywhere)
	class UPaperSprite* SpriteOn;

	class AGeniusGrid* OwnerGrid;
	
	int Index;
	FTimerHandle ShowClicked;

	UFUNCTION()
	void OnTouchBegin(ETouchIndex::Type Type, UPrimitiveComponent* TouchedComponent);
	void WaitColorOn();
};
