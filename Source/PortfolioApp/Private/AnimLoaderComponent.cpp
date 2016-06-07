// Fill out your copyright notice in the Description page of Project Settings.

#include "PortfolioApp.h"
#include "AnimLoaderComponent.h"

#include "DDSLoader.h"

#include "Runtime/ImageWrapper/Public/Interfaces/IImageWrapper.h"
#include "Runtime/ImageWrapper/Public/Interfaces/IImageWrapperModule.h"

#include "Runtime/MediaAssets/Public/MediaPlayer.h"



#include <string>

// Sets default values for this component's properties
UAnimLoaderComponent::UAnimLoaderComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    bWantsBeginPlay = true;
    PrimaryComponentTick.bCanEverTick = true;

    // ...

    static ConstructorHelpers::FObjectFinder<UMaterial> mainMaterial( TEXT( "Material'/Game/Material/AssetMaterial.AssetMaterial'" ) );
    if ( mainMaterial.Object != NULL )
    {
        InterfaceToMainMaterial = ( UMaterial* )mainMaterial.Object;
    }
    static ConstructorHelpers::FObjectFinder<UMaterial> animMaterial( TEXT( "Material'/Game/Material/OldAnimMaterial.OldAnimMaterial'" ) );
    if ( animMaterial.Object != NULL )
    {
        InterfaceToAnimMaterial = ( UMaterial* )animMaterial.Object;
    }
}

// Called when the game starts
void UAnimLoaderComponent::BeginPlay()
{
    Super::BeginPlay();

    // ...

}

// Called every frame
void UAnimLoaderComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
    Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

    // ...
}

void UAnimLoaderComponent::LoadVideo( FString url1, UStaticMeshComponent * mesh )
{
    FString url = FPaths::Combine( *FPaths::GameContentDir(), TEXT( "Movies/UE4_Logo.mp4" ) );
    UMediaPlayer * m_mediaPlayer = ConstructObject<UMediaPlayer>( UMediaPlayer::StaticClass() );

    if ( m_mediaPlayer != NULL )
    {
        GEngine->AddOnScreenDebugMessage( -1, 5.f, FColor::Red, TEXT( "Play_MediaTexture:m_mediaPlayer successfully created!" ) );
    }
    else
    {
        GEngine->AddOnScreenDebugMessage( -1, 5.f, FColor::Red, TEXT( "Play_MediaTexture:m_mediaPlayer creation failed!" ) );
    }

    m_mediaTexture = ConstructObject<UMediaTexture>( UMediaTexture::StaticClass() );

    if ( m_mediaTexture != NULL )
    {
        GEngine->AddOnScreenDebugMessage( -1, 5.f, FColor::Red, TEXT( "Play_MediaTexture:m_mediaTexture successfully created!" ) );
    }
    else
    {
        GEngine->AddOnScreenDebugMessage( -1, 5.f, FColor::Red, TEXT( "Play_MediaTexture:m_mediaTexture creation failed!" ) );
    }

    m_mediaPlayer->SetLooping( false );

    m_mediaTexture->SetMediaPlayer( m_mediaPlayer );

    //add the media texture to the mesh

    /* UStaticMeshComponent * mesh = nullptr;
    for ( TActorIterator<AActor> ActorItr( GetWorld() ); ActorItr; ++ActorItr )
    {
    if ( ActorItr->GetName().Contains( "ProjectionCube" ) )
    {
    GEngine->AddOnScreenDebugMessage( -1, 5.f, FColor::Red, TEXT( "mesh found!" ) );
    TArray<UStaticMeshComponent*> comps;

    ActorItr->GetComponents( comps );
    comps.IsValidIndex(0)? mesh = comps[0] : mesh =nullptr;
    break;
    }
    }
    */

    if ( mesh != NULL )
    {
        GEngine->AddOnScreenDebugMessage( -1, 5.f, FColor::Red, TEXT( "Play_MediaTexture:mesh successfully created!" ) );
    }
    else
    {
        GEngine->AddOnScreenDebugMessage( -1, 5.f, FColor::Red, TEXT( "Play_MediaTexture:mesh creation failed!" ) );
    }


    /* UMaterialInstanceDynamic  * material = mesh->CreateDynamicMaterialInstance( 0 );
    material->SetTextureParameterValue( "Video", m_mediaTexture );
    mesh->SetMaterial( 0, material );
    */
    FString urlTex = FPaths::Combine( *FPaths::GameSavedDir(), TEXT( "DiapoAssets/Bird/Island1.jpg" ) );

    UMaterialInstanceDynamic* material = UMaterialInstanceDynamic::Create( InterfaceToMainMaterial, this );
    if ( mesh )
        mesh->SetMaterial( 0, material );

    //material->SetTextureParameterValue( FName( "T2DParam" ), m_mediaTexture );
    LoadTexture( urlTex );

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

void UAnimLoaderComponent::SetMaterialToProceduralMeshComp( UStaticMeshComponent* mesh )
{
    UMaterialInstanceDynamic* dynamicMatInstance = UMaterialInstanceDynamic::Create( InterfaceToMainMaterial, this );
    if ( mesh )
        mesh->SetMaterial( 0, dynamicMatInstance );
    dynamicMatInstance->SetTextureParameterValue( FName( "T2DParam" ), ModelTexture );
}

void UAnimLoaderComponent::SetAnimatedMaterial( UStaticMeshComponent* mesh )
{
    UMaterialInstanceDynamic* dynamicMatInstance = UMaterialInstanceDynamic::Create( InterfaceToAnimMaterial, this );

    if ( mesh )
        mesh->SetMaterial( 0, dynamicMatInstance );
    dynamicMatInstance->SetTextureParameterValue( FName( "T2DParam" ), m_mediaTexture );
   
}

UTexture2D* UAnimLoaderComponent::LoadTexture( const FString& FilePath )
{
    IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>( FName( "ImageWrapper" ) );
    // Note: PNG format.  Other formats are supported
    IImageWrapperPtr ImageWrapper = ImageWrapperModule.CreateImageWrapper( EImageFormat::JPEG );
    TArray<uint8> RawFileData;
    FString TexturePath = FPaths::GetPath( FilePath ) / FPaths::GetBaseFilename( FilePath ) + FString( ".jpg" );
    std::string strname( TCHAR_TO_ANSI( *TexturePath ) );
    if ( FFileHelper::LoadFileToArray( RawFileData, *TexturePath ) )
    {
        if ( ImageWrapper.IsValid() && ImageWrapper->SetCompressed( RawFileData.GetData(), RawFileData.Num() ) )
        {
            const TArray<uint8>* UncompressedBGRA = NULL;
            if ( ImageWrapper->GetRaw( ERGBFormat::BGRA, 8, UncompressedBGRA ) )
            {
                ModelTexture = UTexture2D::CreateTransient( ImageWrapper->GetWidth(), ImageWrapper->GetHeight(), PF_B8G8R8A8 );
                // Fill in the source data from the file
                FTexture2DMipMap& Mip = ModelTexture->PlatformData->Mips[0];
                void* Data = Mip.BulkData.Lock( LOCK_READ_WRITE );
                FMemory::Memcpy( Data, UncompressedBGRA->GetData(), UncompressedBGRA->Num() );
                Mip.BulkData.Unlock();
                ModelTexture->UpdateResource();
            }
        }
    }
    return ModelTexture;
}
