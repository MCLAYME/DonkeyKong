// Copyright Epic Games, Inc. All Rights Reserved.

#include "DonkeyKongGameMode.h"
#include "DonkeyKongCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "MuroLadrillo.h"
#include "MuroPegajoso.h"
#include "MuroElectrico.h"
#include "MuroCongelado.h"
#include "Plataformas.h"
#include "Engine/Engine.h"
#include "Nave.h"
#include "Compuertas.h"
#include "Capsula.h"



ADonkeyKongGameMode::ADonkeyKongGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ADonkeyKongGameMode::Chocar()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Chocaste con un muro."));
}

void ADonkeyKongGameMode::BeginPlay()
{
	Super::BeginPlay();
	//SPAWNEAR MURO LADRILLO
	FVector MLadrilloPosition(-0.86f, 903.0f, 148.0f);
	FRotator MLadrilloRotation(0.0f, 0.0f, 0.0f);
	GetWorld()->SpawnActor<AMuroLadrillo>(AMuroLadrillo::StaticClass(), MLadrilloPosition, MLadrilloRotation);
	//SPAWNEAR MURO PEGAJOSO
	FVector MPegajosoPosition(-0.86f, 800.0f, 148.0f);
	FRotator MPegajosoRotation(0.0f, 0.0f, 0.0f);
	GetWorld()->SpawnActor<AMuroPegajoso>(AMuroPegajoso::StaticClass(), MPegajosoPosition, MPegajosoRotation);
	//SPAWNEAR MURO ELECTRICO
	FVector MElectricoPosition(-0.86f, 700.0f, 148.0f);
	FRotator MElectricoRotation(0.0f, 0.0f, 0.0f);
	GetWorld()->SpawnActor<AMuroElectrico>(AMuroElectrico::StaticClass(), MElectricoPosition, MElectricoRotation);
	//SPAWNEAR MURO CONGELADO
	FVector MCongeladoPosition(-0.86f, 600.0f, 148.0f);
	FRotator MCongeladoRotation(0.0f, 0.0f, 0.0f);
	GetWorld()->SpawnActor<AMuroCongelado>(AMuroCongelado::StaticClass(), MCongeladoPosition, MCongeladoRotation);
	//SPAWNEAR PLATAFORMAS
	crearPlataforma();
	FRotator Rotation(10.0f, 0.0f, 90.0f);  // Sin rotación
	FVector Location(-0.80, 1300.0f, 130.0f);  // Posición inicial

	// Crear el objeto Nave en el mundo
	GetWorld()->SpawnActor<ANave>(ANave::StaticClass(), Location, Rotation);

	//SPAWNEAR COMPUERTAS
	 // Referencia al mundo
	UWorld* World = GetWorld();
	if (World)
	{
		// Definir posiciones para 3 compuertas
		FVector PosicionesCompuertas[3] = {
			FVector(100.0f, 100.0f, 100.0f),
			FVector(300.0f, 200.0f, 100.0f),
			FVector(500.0f, 300.0f, 100.0f)
		};

		// Definir destinos de teletransporte para 3 compuertas
		FVector DestinosTeletransporte[3] = {
			FVector(1000.0f, 0.0f, 300.0f),
			FVector(1500.0f, 500.0f, 300.0f),
			FVector(2000.0f, -500.0f, 300.0f)
		};

		// Ciclo para crear y configurar las compuertas
		for (int i = 0; i < 3; i++)
		{
			// Spawnear una nueva compuerta
			ACompuertas* NuevaCompuerta = World->SpawnActor<ACompuertas>(ACompuertas::StaticClass(), PosicionesCompuertas[i], FRotator::ZeroRotator);

			if (NuevaCompuerta)
			{
				// Asignar el destino de teletransporte correspondiente
				NuevaCompuerta->DestinoTeletransporte = DestinosTeletransporte[i];
			}
		}
	}
	//SPAWNEAR CAPSULAS

	FVector PosicionesCapsulas[4] = {
		FVector(200.0f, 100.0f, 300.0f),
		FVector(400.0f, 200.0f, 300.0f),
		FVector(600.0f, 300.0f, 300.0f),
		FVector(800.0f, 400.0f, 300.0f)
	};

	for (int i = 0; i < 4; i++)
	{
		GetWorld()->SpawnActor<ACapsula>(ACapsula::StaticClass(), PosicionesCapsulas[i], FRotator::ZeroRotator);
	}

}

void ADonkeyKongGameMode::crearPlataforma()
{
/*GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Yellow, TEXT("Creando plataforma"));

		FVector posicionInicial = FVector(0.50f, -2400.0f, 1000.0f); 
		FRotator rotacionInicial = FRotator(0.0f, 0.0f, 10.0f);
		FTransform SpawnLocationCP;
		float anchoComponentePlataforma = 600.0f; 
		float incrementoAltoComponentePlataforma = -105.0f; 
		float incrementoAltoEntrePisos = 1200.0f; 
		float incrementoInicioPiso = 100.0f;

		for (int npp = 0; npp < 5; npp++) {
			rotacionInicial.Roll = rotacionInicial.Roll * -1;
			incrementoInicioPiso = incrementoInicioPiso * -1;
			incrementoAltoComponentePlataforma = incrementoAltoComponentePlataforma * -1;
			SpawnLocationCP.SetRotation(FQuat(rotacionInicial));
			for (int ncp = 0; ncp < 5; ncp++) {
				SpawnLocationCP.SetLocation(FVector(posicionInicial.X, posicionInicial.Y + anchoComponentePlataforma * ncp, posicionInicial.Z));
				APlataformas* cp = GetWorld()->SpawnActor<APlataformas>(APlataformas::StaticClass(), SpawnLocationCP);
				posicionInicial.Z -= 0.50f;

				if ((npp == 0 || npp == 2 || npp == 4) && (ncp == 1 || ncp == 3)) {
					cp->bMoverVerticalmente = true;
					cp->StartPoint = SpawnLocationCP.GetLocation();
					cp->EndPoint = cp->StartPoint + FVector(0.0f, 0.0f, 500.0f); 
				}
			if ((npp == 1 || npp == 3) && (ncp == 1 || ncp == 3)) {
				cp->bMoverHorizontalmente = true;
				cp->StartPoint = SpawnLocationCP.GetLocation();
				cp->EndPoint = cp->StartPoint + FVector(0.0f, 200.0f, 0.0f); 
			}
				componentesPlataforma.Add(cp);
				if (ncp < 4) {
					posicionInicial.Z = posicionInicial.Z + incrementoAltoComponentePlataforma;
				}
			}
			posicionInicial.Z = posicionInicial.Z + incrementoAltoEntrePisos;
			posicionInicial.Y = posicionInicial.Y + incrementoInicioPiso;
	}
	*/
	//PISO HACIA LA DERECHA
	FVector posicionInicial = FVector(-250.0f,-2000.0f, 550.0f);                        //Codigo del ingeniero X2
	FRotator rotacionInicial = FRotator(0.0f, 0.0f, 15);
	FTransform SpawnLocationCP;

	for (int npp = 0; npp < 3; npp++)                        //NUMERO DE PISOS
	{
		rotacionInicial.Roll = rotacionInicial.Roll * -1;
		posicionInicial.Z += 450.0f;

		SpawnLocationCP.SetRotation(FQuat(rotacionInicial));
		for (int ncp = 0; ncp < 3; ncp++) {                               //NUMERO DE PLATAFORMAS

			SpawnLocationCP.SetLocation(FVector(posicionInicial.X, posicionInicial.Y, posicionInicial.Z));
			componentesPlataforma.Add(GetWorld()->SpawnActor<APlataformas>(APlataformas::StaticClass(), SpawnLocationCP));
			if (ncp == 1) {
				componentesPlataforma.Last()->bMoverHorizontalmente = true;
				componentesPlataforma.Last()->StartPoint = SpawnLocationCP.GetLocation();
				componentesPlataforma.Last()->EndPoint = componentesPlataforma.Last()->StartPoint + FVector(0.0f, 200.0f, 0.0f);
			
			
			}


			posicionInicial.Y += 520.0f;
			posicionInicial.Z += 140.0f;
			rotacionInicial.Roll = rotacionInicial.Roll * -1;

		}
		posicionInicial.Y -= 1530.0f;
		posicionInicial.Z += 450.0f;
	}

	//PISO HACIA LA IZQUIERDA

	FVector posicionInicialI = FVector(-250.f,-2100.0f, 1460.f);
	FRotator rotacionInicialI = FRotator(0.0f, 0.0f, -15);

	for (int nppI = 0; nppI < 3; nppI++)                        //NUMERO DE PISOS
	{
		rotacionInicialI.Roll = rotacionInicialI.Roll * -1;
		posicionInicialI.Z += 900.0f;

		SpawnLocationCP.SetRotation(FQuat(rotacionInicialI));
		for (int ncpI = 0; ncpI < 3; ncpI++) {                               //NUMERO DE PLATAFORMAS

			SpawnLocationCP.SetLocation(FVector(posicionInicialI.X, posicionInicialI.Y, posicionInicialI.Z));
			componentesPlataforma.Add(GetWorld()->SpawnActor<APlataformas>(APlataformas::StaticClass(), SpawnLocationCP));
			if (ncpI == 1)
			{
				componentesPlataforma.Last()->bMoverVerticalmente = true;
				componentesPlataforma.Last()->StartPoint = SpawnLocationCP.GetLocation();
				componentesPlataforma.Last()->EndPoint = componentesPlataforma.Last()->StartPoint + FVector(0.0f, 0.0f, 400.0f);
				

			}
			posicionInicialI.Y += 520.0f;
			posicionInicialI.Z -= 140.0f;
			rotacionInicialI.Roll = rotacionInicialI.Roll * -1;

		}

		posicionInicialI.Y -= 1530.0f;
		posicionInicialI.Z += 850.0f;
	}


}




void ADonkeyKongGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
