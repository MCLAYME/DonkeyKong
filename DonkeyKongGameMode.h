// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DonkeyKongGameMode.generated.h"

class ANave;
class ACompuertas;
/**
 *
 */
UCLASS(minimalapi)
class ADonkeyKongGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADonkeyKongGameMode();
	void CrearCompuertas();

public:
	TMap<int32, ACompuertas*> CompuertaMap; // TMap para las compuertas

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Compuertas")
	TSubclassOf<ACompuertas> CompuertaClass;
	//Creamos nuestro TMap
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};

	


