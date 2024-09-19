// Fill out your copyright notice in the Description page of Project Settings.

#include "Capsula.h"
#include "DonkeyKongCharacter.h"
#include "Proyectil.h" // Asegúrate de tener esta clase creada
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "Materials/MaterialInstanceDynamic.h"

// Sets default values
ACapsula::ACapsula()
{
    // Set this actor to call Tick() every frame.
    PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> ExplosionParticleAsset(TEXT("StaticMesh'/Game/Content/Meshes/Shapes/Shape_NarrowCapsule.Shape_NarrowCapsule'"));
	if (ExplosionParticleAsset.Succeeded())
	{
		ExplosionParticle = ExplosionParticleAsset.Object;
	}

    // Inicializar el componente visual
    CapsulaVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualCuerpo"));
    RootComponent = CapsulaVisual;

    // Inicializar variables de patrullaje
    RangoPatrullaje = 400.0f;
    VelocidadPatrullaje = 100.0f;
    DireccionPatrullaje = 1;
    TiempoEntreDisparos = 2.0f;

    // Configurar colisiones si es necesario
    CapsulaVisual->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    CapsulaVisual->SetCollisionResponseToAllChannels(ECR_Block);
}

// Called when the game starts or when spawned
void ACapsula::BeginPlay()
{
    Super::BeginPlay();

    // Obtener referencia al personaje del jugador
    PlayerCharacter = Cast<ADonkeyKongCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

    // Iniciar el temporizador para disparar
    GetWorld()->GetTimerManager().SetTimer(TimerDisparo, this, &ACapsula::Disparar, TiempoEntreDisparos, true);

    // Crear material dinámico para cambiar color
    if (CapsulaVisual)
    {
        MaterialInstance = CapsulaVisual->CreateAndSetMaterialInstanceDynamic(0);
    }
}

// Called every frame
void ACapsula::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (PlayerCharacter)
    {
        FVector PlayerLocation = PlayerCharacter->GetActorLocation();
        FVector CapsulaLocation = GetActorLocation();

        // Movimiento vertical: seguir la altura del jugador
        float NuevaAltura = FMath::FInterpTo(CapsulaLocation.Z, PlayerLocation.Z, DeltaTime, 5.0f);
        CapsulaLocation.Z = NuevaAltura;

        // Movimiento horizontal: patrullaje
        CapsulaLocation.X += VelocidadPatrullaje * DireccionPatrullaje * DeltaTime;

        // Verificar si se ha excedido el rango de patrullaje
        float DeltaPatrullaje = FMath::Abs(CapsulaLocation.X - GetActorLocation().X);
        if (DeltaPatrullaje > RangoPatrullaje)
        {
            DireccionPatrullaje *= -1; // Cambiar dirección
        }

        // Actualizar la posición de la cápsula
        SetActorLocation(CapsulaLocation);
    }

    // Nota: No es necesario reasignar TiempoEntreDisparos aquí
}

void ACapsula::Disparar()
{
    if (PlayerCharacter)
    {
        FVector PosicionDisparo = GetActorLocation();
        FVector DireccionDisparo = (PlayerCharacter->GetActorLocation() - PosicionDisparo).GetSafeNormal();

        // Añadir dispersión al disparo
        DireccionDisparo.X += FMath::FRandRange(-0.2f, 0.2f);
        DireccionDisparo.Y += FMath::FRandRange(-0.2f, 0.2f);

        // Crear parámetros para el spawn del proyectil
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        SpawnParams.Instigator = GetInstigator();

        // Rotación basada en la dirección de disparo
        FRotator RotacionDisparo = DireccionDisparo.Rotation();

        // Spawn del proyectil
        AProyectil* Proyectil = GetWorld()->SpawnActor<AProyectil>(AProyectil::StaticClass(), PosicionDisparo, RotacionDisparo, SpawnParams);

        if (Proyectil)
        {
            // Mover el proyectil en la dirección calculada
            Proyectil->MoverProyectil(DireccionDisparo);
        }

        // Ajustar la frecuencia de disparo basada en la distancia al jugador
        float DistanciaAlJugador = FVector::Dist(GetActorLocation(), PlayerCharacter->GetActorLocation());
        float NuevaFrecuenciaDeDisparo = FMath::Clamp(DistanciaAlJugador / 500.0f, 0.5f, 3.0f);

        // Reiniciar el temporizador con la nueva frecuencia
        GetWorld()->GetTimerManager().ClearTimer(TimerDisparo);
        GetWorld()->GetTimerManager().SetTimer(TimerDisparo, this, &ACapsula::Disparar, NuevaFrecuenciaDeDisparo, true);
    }
}

void ACapsula::DetectarCharacter()
{
    if (MaterialInstance && PlayerCharacter)
    {
        // Cambiar el color a rojo cuando detecta al jugador
        MaterialInstance->SetVectorParameterValue(FName("BaseColor"), FLinearColor::Red);
    }
}

void ACapsula::Explote()
{
    if (ExplosionParticle)
    {
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticle, GetActorLocation());
    }

    Destroy();
}
