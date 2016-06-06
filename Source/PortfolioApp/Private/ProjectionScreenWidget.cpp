// Fill out your copyright notice in the Description page of Project Settings.

#include "PortfolioApp.h"
#include "ProjectionScreenWidget.h"

UJoySoftEdgeImage::UJoySoftEdgeImage( const FObjectInitializer& ObjectInitializer )
    : Super( ObjectInitializer )
    , ColorAndOpacity( FLinearColor( 0, 0, 1, 0.0333 ) )
    , Thickness( 24 )
{
    //Default Values Set Here, see above

    static ConstructorHelpers::FObjectFinder<UMaterial> animMaterial( TEXT( "Material'/Game/Material/OldAnimMaterial.OldAnimMaterial'" ) );
    if ( animMaterial.Object != NULL )
    {
        InterfaceToAnimMaterial = ( UMaterial* )animMaterial.Object;
    }
}

//Rebuild using custom Slate Widget 
//		-Rama
TSharedRef<SWidget> UJoySoftEdgeImage::RebuildWidget()
{
    MyImage = SNew( SImage );
    
    return MyImage.ToSharedRef();
}

//Set Thickness
void UJoySoftEdgeImage::SetThickness( float InThickness )
{
    Thickness = InThickness;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//This is where the SSoftEdgeImage slate widget gets updated 
//		when the UPROPERTY() is changed in the Editor
//		-Rama
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void UJoySoftEdgeImage::SynchronizeProperties()
{
    Super::SynchronizeProperties();

    //Thickness Delegate Version
    //TAttribute<float> ThickBind = OPTIONAL_BINDING(float, Thickness);
    //MyImage->SetThickness(ThickBind.Get());   

   
    //Color and Opacity
    TAttribute<FSlateColor> ColorAndOpacityBinding = OPTIONAL_BINDING( FSlateColor, ColorAndOpacity );
    MyImage->SetColorAndOpacity( ColorAndOpacityBinding );

    //Image
    TAttribute<const FSlateBrush*> ImageBinding = OPTIONAL_BINDING_CONVERT( FSlateBrush, Brush, const FSlateBrush*, ConvertImage );
    MyImage->SetImage( ImageBinding );

    //Mouse
    MyImage->SetOnMouseButtonDown( BIND_UOBJECT_DELEGATE( FPointerEventHandler, HandleMouseButtonDown ) );
}


//~~~ Rest is copied from UMG Image.h ~~~

void UJoySoftEdgeImage::ReleaseSlateResources( bool bReleaseChildren )
{
    Super::ReleaseSlateResources( bReleaseChildren );

    MyImage.Reset();
}

void UJoySoftEdgeImage::SetColorAndOpacity( FLinearColor InColorAndOpacity )
{
    ColorAndOpacity = InColorAndOpacity;
    if ( MyImage.IsValid() )
    {
        MyImage->SetColorAndOpacity( ColorAndOpacity );
    }
}

void UJoySoftEdgeImage::SetOpacity( float InOpacity )
{
    ColorAndOpacity.A = InOpacity;
    if ( MyImage.IsValid() )
    {
        MyImage->SetColorAndOpacity( ColorAndOpacity );
    }
}

const FSlateBrush* UJoySoftEdgeImage::ConvertImage( TAttribute<FSlateBrush> InImageAsset ) const
{
    UJoySoftEdgeImage* MutableThis = const_cast<UJoySoftEdgeImage*>( this );
    MutableThis->Brush = InImageAsset.Get();

    return &Brush;
}

void UJoySoftEdgeImage::SetBrushFromAsset( USlateBrushAsset* Asset )
{
    Brush = Asset ? Asset->Brush : FSlateBrush();

    if ( MyImage.IsValid() )
    {
        MyImage->SetImage( &Brush );
    }
}

void UJoySoftEdgeImage::SetBrushFromTexture( UTexture2D* Texture )
{
    Brush.SetResourceObject( Texture );

    if ( MyImage.IsValid() )
    {
        MyImage->SetImage( &Brush );
    }
}

void UJoySoftEdgeImage::SetBrushFromMaterial( UMaterialInterface* Material )
{
    Brush.SetResourceObject( Material );

    //TODO UMG Check if the material can be used with the UI

    if ( MyImage.IsValid() )
    {
        MyImage->SetImage( &Brush );
    }
}

UMaterialInstanceDynamic* UJoySoftEdgeImage::GetDynamicMaterial()
{
    UMaterialInterface* Material = NULL;

    UObject* Resource = Brush.GetResourceObject();
    Material = Cast<UMaterialInterface>( Resource );

    if ( Material )
    {
        UMaterialInstanceDynamic* DynamicMaterial = Cast<UMaterialInstanceDynamic>( Material );

        if ( !DynamicMaterial )
        {
            DynamicMaterial = UMaterialInstanceDynamic::Create( Material, this );
            Brush.SetResourceObject( DynamicMaterial );

            if ( MyImage.IsValid() )
            {
                MyImage->SetImage( &Brush );
            }
        }

        return DynamicMaterial;
    }

    //TODO UMG can we do something for textures?  General purpose dynamic material for them?

    return NULL;
}

FReply UJoySoftEdgeImage::HandleMouseButtonDown( const FGeometry& Geometry, const FPointerEvent& MouseEvent )
{
    if ( OnMouseButtonDownEvent.IsBound() )
    {
        return OnMouseButtonDownEvent.Execute( Geometry, MouseEvent ).NativeReply;
    }

    return FReply::Unhandled();
}

#if WITH_EDITOR

const FSlateBrush* UJoySoftEdgeImage::GetEditorIcon()
{
    return FUMGStyle::Get().GetBrush( "Widget.Image" );
}

#endif




void UJoySoftEdgeImage::LoadAnimTexture( )
{
    FString url = FPaths::Combine( *FPaths::GameContentDir(), TEXT( "Movies/UE4_Logo.mp4" ) );
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

    m_mediaPlayer->SetLooping( false );

    m_mediaTexture->SetMediaPlayer( m_mediaPlayer );


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

void UJoySoftEdgeImage::SetAnimatedMaterial()
{
    UMaterialInstanceDynamic* dynamicMatInstance = UMaterialInstanceDynamic::Create( InterfaceToAnimMaterial, this );
    
    //UMaterialInstanceDynamic* dynamicMatInstance = GetDynamicMaterial();
    dynamicMatInstance->SetTextureParameterValue( FName( "T2DParam" ), m_mediaTexture );
    SetBrushFromMaterial( InterfaceToAnimMaterial );
}