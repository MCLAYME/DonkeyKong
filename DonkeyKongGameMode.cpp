// Copyright Epic Games, Inc. All Rights Reserved.

#include "DonkeyKongGameMode.h"
#include "DonkeyKongCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Nave.h"
#include "Compuertas.h"

ADonkeyKongGameMode::ADonkeyKongGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("StaticMesh'/Game/Geometry/Meshes/Escenario/Donkey_Kong_Level_1_Platform049.Donkey_Kong_Level_1_Platform049'"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

}

void ADonkeyKongGameMode::CrearCompuertas()
{

	if (CompuertaClass == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("CompuertaClass no está configurado en el GameMode."));
		return;
	}

	FVector Posiciones[5] = {
		FVector(-0.50f, -1450.0f, -200.0f),
		FVector(-0.50f, -1450.0f, -200.0f + 780.0f),
		FVector(-0.50f, -1450.0f + 600.0f, -200.0f + 780.0f),
		FVector(-0.50f, -1450.0f + 600.0f, -200.0f + 2 * 780.0f),
		FVector(-0.50f, -1450.0f + 2 * 600.0f, -200.0f + 2 * 780.0f)
	};

	for (int i = 0; i < 5; i++)
	{
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(Posiciones[i]);
		SpawnTransform.SetRotation(FQuat::Identity);

		ACompuertas* Compuerta = GetWorld()->SpawnActor<ACompuertas>(CompuertaClass, SpawnTransform);
		if (Compuerta)
		{
			// Añadir la compuerta al TMap con un identificador único
			CompuertaMap.Add(i + 1, Compuerta);
		}
	}

	// Configurar destinos de las compuertas
	if (CompuertaMap.Num() > 0)
	{
		if (ACompuertas** CompuertaPtr = CompuertaMap.Find(1)) (*CompuertaPtr)->CompuertaDestino = CompuertaMap.FindRef(3); // Compuerta 1 -> Compuerta 3
		if (ACompuertas** CompuertaPtr = CompuertaMap.Find(2)) (*CompuertaPtr)->CompuertaDestino = CompuertaMap.FindRef(5); // Compuerta 2 -> Compuerta 5
		if (ACompuertas** CompuertaPtr = CompuertaMap.Find(3)) (*CompuertaPtr)->CompuertaDestino = CompuertaMap.FindRef(4); // Compuerta 3 -> Compuerta 4
		if (ACompuertas** CompuertaPtr = CompuertaMap.Find(4)) (*CompuertaPtr)->CompuertaDestino = CompuertaMap.FindRef(1); // Compuerta 4 -> Compuerta 1
		if (ACompuertas** CompuertaPtr = CompuertaMap.Find(5)) (*CompuertaPtr)->CompuertaDestino = CompuertaMap.FindRef(2); // Compuerta 5 -> Compuerta 2
	}
}




void ADonkeyKongGameMode::BeginPlay()
{
	Super::BeginPlay();
	/*// PISO HACIA LA DERECHA
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Yellow, TEXT("Creando plataforma"));
	// Spawn an instance of the AMyFirstActor class at the
	// default location.
	FTransform SpawnLocation;
	SpawnLocation.SetLocation(FVector(-0.50f, -1420.0f, -400.0f));
	SpawnLocation.SetRotation(FQuat(FRotator(0.0f, 0.0f, 0.0f)));

	FVector posicionInicial = FVector(-0.50f, -1450.0f, -200.0f);                        //Codigo del ingeniero X2
	FRotator rotacionInicial = FRotator(0.0f, 0.0f, 10.0f);
	FTransform SpawnLocationCP;
	float anchoPlataforma = 600.0f;
	float incrementoAltoPlataforma = -105.0f;
	float incrementoAltoEntrePisos = 780.0f;
	float incrementoInicioPiso = 80.0f;
	float tamanoPlataforma = 600.0f;
	for (int npp = 0; npp < 5; npp++) {
		rotacionInicial.Roll = rotacionInicial.Roll * -1;
		incrementoInicioPiso = incrementoInicioPiso * -1;
		incrementoAltoPlataforma = incrementoAltoPlataforma * -1;
		SpawnLocationCP.SetRotation(FQuat(rotacionInicial));

		for (int ncp = 0; ncp < 5; ncp++) {
			SpawnLocationCP.SetLocation(FVector(posicionInicial.X, posicionInicial.Y + anchoPlataforma * ncp, posicionInicial.Z));
			Plataformass.Add(GetWorld()->SpawnActor<APlataformas>(APlataformas::StaticClass(), SpawnLocationCP));
			if (ncp < 4) {
				posicionInicial.Z = posicionInicial.Z + incrementoAltoPlataforma;
			}
		}

		posicionInicial.Z = posicionInicial.Z + incrementoAltoEntrePisos;
		posicionInicial.Y = posicionInicial.Y + incrementoInicioPiso;

	}*/
	/*for (int npp = 0; npp < 5; npp++)                        //NUMERO DE PISOS
	{
		rotacionInicial.Roll = rotacionInicial.Roll * -1;
		posicionInicial.Z += 450.0f;

		SpawnLocationCP.SetRotation(FQuat(rotacionInicial));
		for (int ncp = 0; ncp < 5; ncp++) {                               //NUMERO DE PLATAFORMAS

			SpawnLocationCP.SetLocation(FVector(posicionInicial.X, posicionInicial.Y, posicionInicial.Z));
			Plataformass.Add(GetWorld()->SpawnActor<APlataformas>(APlataformas::StaticClass(), SpawnLocationCP));
			posicionInicial.Y += 600.0f;
			posicionInicial.Z += 140.0f;
			rotacionInicial.Roll = rotacionInicial.Roll * -1;

		}
		posicionInicial.Y -= 1530.0f;
		posicionInicial.Z += 450.0f;
	}*/

	//PISO HACIA LA IZQUIERDA
/*
	FVector posicionInicialI = FVector(0.50f, -1200.0f, 700.f);
	FRotator rotacionInicialI = FRotator(0.0f, 0.0f, -15);

	for (int nppI = 0; nppI < 5; nppI++)                        //NUMERO DE PISOS
	{
		rotacionInicialI.Roll = rotacionInicialI.Roll * -1;
		posicionInicialI.Z += 900.0f;

		SpawnLocationCP.SetRotation(FQuat(rotacionInicialI));
		for (int ncpI = 0; ncpI < 4; ncpI++) {                               //NUMERO DE PLATAFORMAS

			SpawnLocationCP.SetLocation(FVector(posicionInicialI.X, posicionInicialI.Y, posicionInicialI.Z));
			Plataformass.Add(GetWorld()->SpawnActor<APlataformas>(APlataformas::StaticClass(), SpawnLocationCP));
			posicionInicialI.Y += 520.0f;
			posicionInicialI.Z -= 140.0f;
			rotacionInicialI.Roll = rotacionInicialI.Roll * -1;

		}

		posicionInicialI.Y -= 1530.0f;
		posicionInicialI.Z += 850.0f;
	}*/

	//spaw de la nave 
	// Location(100.0f, 1200.0f, 4600.0f);  // Posición inicial
	FRotator Rotation(10.0f, 0.0f, 90.0f);  // Sin rotación
	FVector Location(-0.80, 1300.0f, 130.0f);  // Posición inicial

	// Crear el objeto Nave en el mundo
	GetWorld()->SpawnActor<ANave>(ANave::StaticClass(), Location, Rotation);
	GetWorld()->SpawnActor<ACompuertas>(ACompuertas::StaticClass(), Location, Rotation);
}


void ADonkeyKongGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
/*void ADonkeyKongGameMode::crearPlataforma()
{
	/*if (GetWorld())
	{
		FVector ubicacion1(-0.90f, -310.0f, 100.5f);
		FRotator rotacion1(0.0f, 90.0f, 0.0f);
		FTransform SpawnLocationNP;

		for (int i = 0; i < 5; i++)
		{

			for (int j = 0; j < 5; j++)
			{
				//SpawnLocationNP.SetLocation(FVector(ubicacion1.X, ubicacion1.Y, ubicacion1.Z));
				APlataformas* plataforma1 = GetWorld()->SpawnActor<APlataformas>(ubicacion1, rotacion1);
				PlataformaMap.Add(1, plataforma1);
				ubicacion1.Z += 90.0f;
				ubicacion1.Y -= 367.0f;
				rotacion1.Roll = rotacion1.Roll * -1;
			}
			ubicacion1.Y += 1000.0f;
			ubicacion1.Z += 700.0f;

		}


		FVector ubicacion2(0.50f, 620.0f, 800.0f);
		FRotator rotacion2(0.0f, 90.0f, 0.0f);

		for (int i = 0; i < 5; i++)
		{

			for (int j = 0; j < 3; j++)
			{
				//SpawnLocationNP.SetLocation(FVector(ubicacion2.X, ubicacion2.Y, ubicacion2.Z));
				APlataformas* plataforma2 = GetWorld()->SpawnActor<APlataformas>(ubicacion2, rotacion2);
				PlataformaMap.Add(2, plataforma2);
				ubicacion2.Z += 90.0f;
				ubicacion2.Y += 367.0f;
				rotacion2.Roll = rotacion2.Roll * -
				1;
			}
			ubicacion2.Y -= 1150.0f;
			ubicacion2.Z += 700.0f;

		}

	}
	 if (PlataformaClass == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlataformaClass no está configurado en el GameMode."));
		return;
	}

	FVector PosicionesPlataforma[5] = {
		FVector(-0.50f, -1450.0f, -200.0f),
		FVector(-0.50f, -1450.0f + 600.0f, -200.0f),
		FVector(-0.50f, -1450.0f + 2 * 600.0f, -200.0f),
		FVector(-0.50f, -1450.0f + 3 * 600.0f, -200.0f),
		FVector(-0.50f, -1450.0f + 4 * 600.0f, -200.0f)
	};

	for (int i = 0; i < 5; i++)
	{
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(PosicionesPlataforma[i]);
		SpawnTransform.SetRotation(FQuat::Identity);

		APlataformas* Plataforma = GetWorld()->SpawnActor<APlataformas>(PlataformaClass, SpawnTransform);
		if (Plataforma)
		{
			// Añadir la plataforma al TMap con un identificador único
			PlataformaMap.Add(i + 1, Plataforma);
		}
	}
}
*/