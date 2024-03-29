// Fill out your copyright notice in the Description page of Project Settings.

#include "PortfolioApp.h"
#include "PortfolioPlayerController.h"
#include "PortfolioPlayerState.h"
#include "ImageLoader.h"
#include "AnimLoader.h"
#include "ImagesHolder.h"

APortFolioPlayerController::APortFolioPlayerController( const class FObjectInitializer& ObjectInitializer )
    : Super( ObjectInitializer ),
    m_pImageLoader( nullptr ),
    AnimLoader(nullptr),
    ImagesHolder(nullptr)
{
   // APortfolioPlayerState* PortfolioPlayerState = Cast<APortfolioPlayerState>( this->PlayerState );
   }


void APortFolioPlayerController::BeginPlay()
{
    Super::BeginPlay();
    m_pImageLoader = NewObject<UImageLoader>( UImageLoader::StaticClass() );
    AnimLoader = NewObject<UAnimLoader>( UImagesHolder::StaticClass() );
    ImagesHolder = NewObject<UImagesHolder>( UImagesHolder::StaticClass() );


}

void APortFolioPlayerController::FillImageArray( const FString& FilePath )
{
    m_pImageLoader->CreateSearchPaths( FilePath, ImagesHolder );
}
