// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DonkeyKongGameMode.generated.h"

//class AMuro;
class AMuroLadrillo;
class AMuroPegajoso;
class AMuroElectrico;
class AMuroCongelado;
class APlataformas;
class ANave;
class ACompuertas;
class ACapsula;
//class ADonkeyKongCharacter;
/**
 *
 */
UCLASS(minimalapi)
class ADonkeyKongGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADonkeyKongGameMode();
	void Chocar();
protected:
	virtual void BeginPlay() override;
	// Platform class to spawn
	void crearPlataforma();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Plataformas")	
	TArray<APlataformas*> componentesPlataforma;

public:

public:
	virtual void Tick(float DeltaTime) override;

};



