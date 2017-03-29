// Fill out your copyright notice in the Description page of Project Settings.

#include "Genius.h"
#include "GeniusGrid.h"
#include "GeniusColor.h"
#include "GeniusPawn.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/UMGStyle.h"
#include "Runtime/UMG/Public/Slate/SObjectWidget.h"
#include "Runtime/UMG/Public/IUMGModule.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Blueprint/WidgetBlueprintLibrary.h"

// Sets default values
AGeniusGrid::AGeniusGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	ConstructorHelpers::FObjectFinder<UClass> RedBP(TEXT("Blueprint'/Game/Blueprints/GeniusColorRed.GeniusColorRed_C'"));
	ConstructorHelpers::FObjectFinder<UClass> BlueBP(TEXT("Blueprint'/Game/Blueprints/GeniusColorBlue.GeniusColorBlue_C'"));
	ConstructorHelpers::FObjectFinder<UClass> GreenBP(TEXT("Blueprint'/Game/Blueprints/GeniusColorGreen.GeniusColorGreen_C'"));
	ConstructorHelpers::FObjectFinder<UClass> YellowBP(TEXT("Blueprint'/Game/Blueprints/GeniusColorYellow.GeniusColorYellow_C'"));

	if (RedBP.Succeeded()) {
		Red = Cast<UClass>(RedBP.Object);
	}
	if (BlueBP.Succeeded()) {
		Blue = Cast<UClass>(BlueBP.Object);
	}
	if (GreenBP.Succeeded()) {
		Green = Cast<UClass>(GreenBP.Object);
	}
	if (YellowBP.Succeeded()) {
		Yellow = Cast<UClass>(YellowBP.Object);
	}

	ConstructorHelpers::FClassFinder<UUserWidget> Widget
	(TEXT("WidgetBlueprint'/Game/Blueprints/GameOverBP.GameOverBP_C'"));
	if (Widget.Succeeded()) {
		GameOverWidget = Widget.Class;
	}
}

// Called when the game starts or when spawned
void AGeniusGrid::BeginPlay()
{
	Super::BeginPlay();
	
	UWorld* World = GetWorld();
	if (World) {
		FActorSpawnParameters SpawnParameters;
		AGeniusColor* GeniusRed = World->SpawnActor<AGeniusColor>(Red, FVector(0.0f, 0.0f, 0.0f), FRotator::ZeroRotator, SpawnParameters);
		AGeniusColor* GeniusBlue = World->SpawnActor<AGeniusColor>(Blue, FVector(250.0f, 0.0f, 0.0f), FRotator::ZeroRotator, SpawnParameters);
		AGeniusColor* GeniusGreen = World->SpawnActor<AGeniusColor>(Green, FVector(0.0f, 0.0f, 250.0f), FRotator::ZeroRotator, SpawnParameters);
		AGeniusColor* GeniusYellow = World->SpawnActor<AGeniusColor>(Yellow, FVector(250.0f, 0.0f, 250.0f), FRotator::ZeroRotator, SpawnParameters);
		GeniusRed->SetIndex(0);
		GeniusBlue->SetIndex(1);
		GeniusGreen->SetIndex(2);
		GeniusYellow->SetIndex(3);
		
		GeniusRed->SetOwnerGrid(this);
		GeniusBlue->SetOwnerGrid(this);
		GeniusGreen->SetOwnerGrid(this);
		GeniusYellow->SetOwnerGrid(this);

		GeniusParts.Add(GeniusRed);
		GeniusParts.Add(GeniusBlue);
		GeniusParts.Add(GeniusGreen);
		GeniusParts.Add(GeniusYellow);
	}

	AddNewColor();

}

// Called every frame
void AGeniusGrid::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AGeniusGrid::AddNewColor() {
	int Rand = FMath::RandRange(0, 3);
	Sequence.Add(Rand);
	Index = 0;
	bLight = false;
	NumOfClicks = 0;
	bFreeze = true;

	UWorld* World = GetWorld();
	if (World) {
		GetWorldTimerManager().SetTimer(ShowGenius, this,
			&AGeniusGrid::Show, 1.0f, true);
	}
}

void AGeniusGrid::Show() {
	int ActualSequence = Sequence[Index];
	GeniusParts[ActualSequence]->ChangeSprite();

	if (bLight) {
		bLight = false;
		GetWorldTimerManager().ClearTimer(ShowGenius);
		Index++;
		if (Index < Sequence.Num()) {
			GetWorldTimerManager().SetTimer(ShowGenius, this,
				&AGeniusGrid::Show, 1.0f, true);
		} else {
			bFreeze = false;
		}
	} else {
		bLight = true;
		GetWorldTimerManager().ClearTimer(ShowGenius);
		GetWorldTimerManager().SetTimer(ShowGenius, this,
			&AGeniusGrid::Show, 1.0f, true);
	}
}

bool AGeniusGrid::Verify(class AGeniusColor* ColorClicked) {
	if (Sequence[NumOfClicks] == ColorClicked->GetIndex()) {
		NumOfClicks++;
		if (NumOfClicks == Sequence.Num()) {
			UWorld* World = GetWorld();
			if (World) {
				APawn* Pawn = UGameplayStatics::GetPlayerController(World, 0)->GetControlledPawn();
				AGeniusPawn* GeniusPawn = Cast<AGeniusPawn>(Pawn);
				GeniusPawn->SetScore(GeniusPawn->GetScore() + 5);
			}
			AddNewColor();
		}
		return true;
	}
	return false;
}

void AGeniusGrid::SetFreeze(bool NewFreeze) {
	bFreeze = NewFreeze;
}

bool AGeniusGrid::GetFreeze() {
	return bFreeze;
}

void AGeniusGrid::GameOver() {
	UWorld* World = GetWorld();
	if (World) {
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(World, 0);
		if (PlayerController && GameOverWidget != NULL) {
			PlayerController->SetPause(true);
			UUserWidget* UserW = UWidgetBlueprintLibrary::Create(World, GameOverWidget, PlayerController);
			if (UserW) {
				UserW->AddToViewport();
			}
		}
	}
}