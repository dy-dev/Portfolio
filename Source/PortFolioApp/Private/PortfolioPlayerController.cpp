// Fill out your copyright notice in the Description page of Project Settings.

#include "PortFolioApp.h"
#include "PortFolioPlayerController.h"
#include "ImageLoader.h"
#include "ImagesHolder.h"

APortFolioPlayerController::APortFolioPlayerController( const class FObjectInitializer& ObjectInitializer )
    : Super( ObjectInitializer ),
    m_pImageLoader(nullptr),
    m_pImagesHolder(nullptr)
{

}