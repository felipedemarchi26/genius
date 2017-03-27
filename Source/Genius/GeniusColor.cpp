// Fill out your copyright notice in the Description page of Project Settings.

#include "Genius.h"
#include "GeniusColor.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"
#include "GeniusGrid.h"


// Sets default values
AGeniusColor::AGeniusColor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
	Sprite->SetSprite(SpriteOff);
	Sprite->OnInputTouchBegin.AddDynamic(this, &AGeniusColor::OnTouchBegin);
	RootComponent = Sprite;
}

// Called when the game starts or when spawned
void AGeniusColor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGeniusColor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AGeniusColor::SetIndex(int NewIndex) {
	Index = NewIndex;
}

int AGeniusColor::GetIndex() {
	return Index;
}

void AGeniusColor::ChangeSprite() {
	if (Sprite->GetSprite() == SpriteOff) {
		Sprite->SetSprite(SpriteOn);
	} else {
		Sprite->SetSprite(SpriteOff);
	}
}

void AGeniusColor::OnTouchBegin(ETouchIndex::Type Type, UPrimitiveComponent* TouchedComponent) {
	if (!OwnerGrid->GetFreeze()) {
		if (OwnerGrid->Verify(this)) {
			Sprite->SetSprite(SpriteOn);
			OwnerGrid->SetFreeze(true);
			UWorld* World = GetWorld();
			if (World) {
				GetWorldTimerManager().SetTimer(ShowClicked, this,
					&AGeniusColor::WaitColorOn, 0.5f, true);
			}
		} else {
			UE_LOG(LogTemp, Warning, TEXT("GAME OVER!"));
			OwnerGrid->GameOver();
		}
	}
}

void AGeniusColor::WaitColorOn() {
	Sprite->SetSprite(SpriteOff);
	OwnerGrid->SetFreeze(false);
	GetWorldTimerManager().ClearTimer(ShowClicked);
}

void AGeniusColor::SetOwnerGrid(class AGeniusGrid* Grid) {
	OwnerGrid = Grid;
}