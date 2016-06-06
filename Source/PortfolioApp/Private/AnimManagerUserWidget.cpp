// Fill out your copyright notice in the Description page of Project Settings.

#include "PortfolioApp.h"
#include "Runtime/Media/Public/IMediaPlayer.h"
#include "AnimManagerUserWidget.h"

UAnimManagerUserWidget::UAnimManagerUserWidget( const FObjectInitializer& ObjectInitializer )
    : Super( ObjectInitializer )
{
    //Default Values Set Here, see above

    static ConstructorHelpers::FObjectFinder<UMaterial> animMaterial( TEXT( "Material'/Game/Material/OldAnimMaterial.OldAnimMaterial'" ) );
    if ( animMaterial.Object != NULL )
    {
        InterfaceToAnimMaterial = ( UMaterial* )animMaterial.Object;
    }
}


void UAnimManagerUserWidget::LoadAnimTexture( FString movieName, UMediaSoundWave * sound )
{
    FString url =  "D:/Personal Dev Projects/PortfolioApp/Content/Movies/" + movieName;
    GEngine->AddOnScreenDebugMessage( -1,60.f, FColor::Red, FPaths::LaunchDir() );

   // FString dir = TEXT( "Movies/" ) + movieName;
  //  FString url = FPaths::Combine( *FPaths::GameContentDir(), *dir );
    UMediaPlayer * m_mediaPlayer = NewObject<UMediaPlayer>( UMediaPlayer::StaticClass() );

    if ( m_mediaPlayer != NULL )
    {
        GEngine->AddOnScreenDebugMessage( -1, 5.f, FColor::Red, TEXT( "Play_MediaTexture:m_mediaPlayer successfully created!" ) );
    }
    else
    {
        GEngine->AddOnScreenDebugMessage( -1, 5.f, FColor::Red, TEXT( "Play_MediaTexture:m_mediaPlayer creation failed!" ) );
    }

    m_mediaTexture = NewObject<UMediaTexture>( UMediaTexture::StaticClass() );

    if ( m_mediaTexture != NULL )
    {
        GEngine->AddOnScreenDebugMessage( -1, 5.f, FColor::Red, TEXT( "Play_MediaTexture:m_mediaTexture successfully created!" ) );
    }
    else
    {
        GEngine->AddOnScreenDebugMessage( -1, 5.f, FColor::Red, TEXT( "Play_MediaTexture:m_mediaTexture creation failed!" ) );
    }

    m_mediaPlayer->SetLooping( true );

    m_mediaTexture->SetMediaPlayer( m_mediaPlayer );
/*
    if ( sound != NULL )
    {
        GEngine->AddOnScreenDebugMessage( -1, 5.f, FColor::Red, TEXT( "sound successfully created!" ) );
        IMediaPlayerPtr Player = sound->GetPlayer();
        if ( Player.IsValid() )
        {
            Player.Get()->Play();

            GEngine->AddOnScreenDebugMessage( -1, 5.f, FColor::Red, TEXT( "player sound found and started!" ) );
        }
        else
        {
            GEngine->AddOnScreenDebugMessage( -1, 5.f, FColor::Red, TEXT( "player sound found failed to start!" ) );
        }
    }
    else
    {
        GEngine->AddOnScreenDebugMessage( -1, 5.f, FColor::Red, TEXT( "sound creation failed!" ) );
    }


*/
    GEngine->AddOnScreenDebugMessage( -1, 5.f, FColor::Red, FString::Printf( TEXT( "Play_MediaTexture: url name: %s" ), *url ) );

    if ( m_mediaPlayer->OpenUrl( url ) )
    {
        GEngine->AddOnScreenDebugMessage( -1, 5.f, FColor::Red, TEXT( "Play_MediaTexture:OpenUrl success!" ) );
    }
    else
    {
        GEngine->AddOnScreenDebugMessage( -1, 5.f, FColor::Red, TEXT( "Play_MediaTexture:OpenUrl failed!" ) );
    }
    m_mediaPlayer->Rewind();
    m_mediaPlayer->Play();
}

void UAnimManagerUserWidget::SetAnimatedMaterial( UImage* image, FString path, UMediaSoundWave * sound )
{
    LoadAnimTexture( path, sound );
    UMaterialInstanceDynamic* dynamicMatInstance = UMaterialInstanceDynamic::Create( InterfaceToAnimMaterial, image );

    dynamicMatInstance->SetTextureParameterValue( FName( "T2DParam" ), m_mediaTexture );
    FSlateBrush Brush = FSlateBrush();
    Brush.SetResourceObject( dynamicMatInstance );

    //TODO UMG Check if the material can be used with the UI

    if ( image )
    {
        image->SetBrush( Brush );
    }
}
