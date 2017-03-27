// Fill out your copyright notice in the Description page of Project Settings.

#include "Genius.h"
#include "GeniusGameModeBase.h"
#include "PlayerControllerGenius.h"

AGeniusGameModeBase::AGeniusGameModeBase() {
	//Define para utilizar o player controller criado para o jogo
	PlayerControllerClass = APlayerControllerGenius::StaticClass();

}


