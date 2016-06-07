// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Runtime/MediaAssets/Public/MediaTexture.h"
#include "AnimLoaderComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTFOLIOAPP_API UAnimLoaderComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAnimLoaderComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;



    UFUNCTION( BlueprintCallable, Category = "Diaporama" )
        void LoadVideo( FString url, UStaticMeshComponent * mesh );
    //Interface to the material we need to modify
    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "3D Loader" )
        UMaterialInterface* InterfaceToMainMaterial;
    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "3D Loader" )
        UMaterialInterface* InterfaceToAnimMaterial;

    UTexture2D* LoadTexture( const FString& TextureFilename );

    UFUNCTION( BlueprintCallable, Category = "3D Loader" )
        void SetMaterialToProceduralMeshComp( UStaticMeshComponent* mesh );

    UFUNCTION( BlueprintCallable, Category = "3D Loader" )
        void SetAnimatedMaterial( UStaticMeshComponent* mesh );

    //Texture for the model
    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "3D Loader" )
        UTexture2D* ModelTexture;

    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "3D Loader" )
    UMediaTexture * m_mediaTexture;
	
};
