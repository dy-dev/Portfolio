// Fill out your copyright notice in the Description page of Project Settings.

#include "PortfolioApp.h"
#include "PortfolioPlayerController.h"
#include "PortfolioPlayerState.h"
#include "ImageLoader.h"
#include "ImagesHolder.h"

APortFolioPlayerController::APortFolioPlayerController( const class FObjectInitializer& ObjectInitializer )
    : Super( ObjectInitializer ),
    m_pImageLoader(nullptr),
    ImagesHolder(nullptr)
{
   // APortfolioPlayerState* PortfolioPlayerState = Cast<APortfolioPlayerState>( this->PlayerState );
    m_pImageLoader = ConstructObject<UImageLoader>( UImageLoader::StaticClass() );
    ImagesHolder = ConstructObject<UImagesHolder>( UImagesHolder::StaticClass() );
    
    m_pImageLoader->CreateSearchPaths( FPaths::Combine( *FPaths::GameSavedDir(), TEXT( "DiapoAssets" ) ), ImagesHolder );
}