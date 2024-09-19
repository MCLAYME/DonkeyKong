// Fill out your copyright notice in the Description page of Project Settings.

#include "Proyectil.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProyectil::AProyectil()
{
    // Set this actor to call Tick() every frame.
    PrimaryActorTick.bCanEverTick = true;

    // Inicializar el componente de colisión
    CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
    CollisionComp->InitSphereRadius(15.0f);
    CollisionComp->SetCollisionProfileName("Projectile");
    CollisionComp->OnComponentHit.AddDynamic(this, &AProyectil::OnHit);
    RootComponent = CollisionComp;

    // Inicializar la malla del proyectil
    ProyectilMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProyectilMesh"));
    ProyectilMesh->SetupAttachment(RootComponent);

    // Cargar la malla estática del proyectil
    static ConstructorHelpers::FObjectFinder<UStaticMesh> ProyectilMeshAsset(TEXT("StaticMesh'/Game/Content/Meshes/BulletLevel2.BulletLevel2'"));
    if (ProyectilMeshAsset.Succeeded())
    {
        ProyectilMesh->SetStaticMesh(ProyectilMeshAsset.Object);
        ProyectilMesh->SetRelativeScale3D(FVector(0.5f, 1.5f, 2.0f));
    }

    // Inicializar la velocidad del proyectil
    ProyectilSpeed = 1000.0f;

    // Cargar el efecto de explosión
    static ConstructorHelpers::FObjectFinder<UParticleSystem> ExplosionEffectAsset(TEXT("ParticleSystem'/Game/Path/To/YourExplosionEffect.YourExplosionEffect'"));
    if (ExplosionEffectAsset.Succeeded())
    {
        ExplosionEffect = ExplosionEffectAsset.Object;
    }

    // Crear el componente de movimiento del proyectil
    ProyectilMovimiento = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProyectilMovimiento"));
    ProyectilMovimiento->InitialSpeed = ProyectilSpeed;
    ProyectilMovimiento->MaxSpeed = ProyectilSpeed;
    ProyectilMovimiento->ProjectileGravityScale = 0.0f; // Sin gravedad
}

// Called when the game starts or when spawned
void AProyectil::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void AProyectil::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Función para manejar colisiones
void AProyectil::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (OtherActor && OtherActor != this)
    {
        // Si el sistema de partículas está disponible, generar la explosión
        if (ExplosionEffect)
        {
            UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, GetActorLocation());
        }

        // Aplicar daño al actor impactado
        UGameplayStatics::ApplyDamage(OtherActor, 10.0f, GetInstigatorController(), this, UDamageType::StaticClass());

        // Destruir el proyectil después del impacto
        Destroy();
    }
}

// Función para mover el proyectil manualmente
void AProyectil::MoverProyectil(FVector Direccion)
{
    if (ProyectilMovimiento)
    {
        ProyectilMovimiento->Velocity = Direccion * ProyectilSpeed;
    }
}
