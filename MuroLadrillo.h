#pragma once

#include "CoreMinimal.h"
#include "Muro.h"
#include "Components/StaticMeshComponent.h"
#include "MuroLadrillo.generated.h"

UCLASS()
class DONKEYKONG_API AMuroLadrillo : public AMuro
{
	GENERATED_BODY()

public:
	AMuroLadrillo();

	// Sobrescribir el método Chocar
	virtual void Chocar();

protected:
	// Llamado cuando el juego comienza o cuando se genera el actor
	virtual void BeginPlay() override;

	// Componente de malla estática del muro
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MuroLadrilloMesh;

	// Material del muro
	UPROPERTY(EditAnywhere, Category = "Materials")
	UMaterial* BrickMaterial;


public:
	// Llamado cada cuadro
	virtual void Tick(float DeltaTime) override;
};
