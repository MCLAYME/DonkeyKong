#include "Proyectil.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProyectil::AProyectil()
{
	// Set this actor to call Tick() every frame.
	PrimaryActorTick.bCanEverTick = true;
	// Initialize collision component
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AProyectil::OnHit);
	RootComponent = CollisionComp;

	// Initialize mesh
	ProyectilMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProyectilMesh"));
	ProyectilMesh->SetupAttachment(RootComponent);


	static ConstructorHelpers::FObjectFinder<UStaticMesh> ProyectilMeshAsset(TEXT("StaticMesh'/Game/Meshes/BulletLevel2.BulletLevel2'"));
	if (ProyectilMeshAsset.Succeeded())
	{
		ProyectilMesh->SetStaticMesh(ProyectilMeshAsset.Object);
		ProyectilMesh->SetRelativeScale3D(FVector(0.5f, 1.5f, 2.0f));
		//FVector ProyectilSpawnLocation = GetActorLocation() + GetActorForwardVector() * 1000.0f;  // 100 unidades frente al personaje
		//ProyectilMesh->SetWorldLocation(ProyectilSpawnLocation);
	}

	ProyectilSpeed = 200.0f;
	// Cargar el efecto de explosión
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ExplosionEffectAsset(TEXT("StaticMesh'/Game/Meshes/BulletLevel1.BulletLevel1''"));
	if (ExplosionEffectAsset.Succeeded())
	{
		ExplosionEffect = ExplosionEffectAsset.Object;
	}

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

	// Move the projectile forward every frame
	FVector NewLocation = GetActorLocation() + GetActorForwardVector() * ProyectilSpeed * DeltaTime;
	SetActorLocation(NewLocation);
}

void AProyectil::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Destroy the projectile on hit
	if (OtherActor != nullptr && OtherActor != this)
	{
		// Si el sistema de partículas está disponible, generamos la explosión
		if (ExplosionEffect)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, GetActorLocation());
		}
		Destroy();
	}
}

void AProyectil::MoverProyectil(FVector Direccion)
{
	// Function to manually move the projectile (if needed)
	FVector NewLocation = GetActorLocation() + Direccion * ProyectilSpeed * GetWorld()->DeltaTimeSeconds;
	SetActorLocation(NewLocation);
	// Crear un offset para la posición del proyectil, por ejemplo, un poco más adelante
	FVector Offset(100.0f, 0.0f, 0.0f); // Ajusta el offset según sea necesario

}


