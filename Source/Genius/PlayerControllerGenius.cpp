// Fill out your copyright notice in the Description page of Project Settings.

#include "Genius.h"
#include "PlayerControllerGenius.h"

APlayerControllerGenius::APlayerControllerGenius() {
	//Apenas para testes na Unreal
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
	//Habilitar os eventos de touch
	bEnableTouchEvents = true;
}


