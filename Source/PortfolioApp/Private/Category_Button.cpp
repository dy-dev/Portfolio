// Fill out your copyright notice in the Description page of Project Settings.

#include "PortfolioApp.h" 
#include "Categories_ScrollBox.h"
#include "Category_Button.h"



UCategory_Button::UCategory_Button( class FObjectInitializer const & ObjectInitializer )
    : Super( ObjectInitializer )
    , m_pScrollBox(nullptr)
    , subCategoryPath("")
{
    //Default Values Set Here, see above
}

TSharedRef<SWidget> UCategory_Button::RebuildWidget()
{
    TSharedRef<SWidget> OurWidget = Super::RebuildWidget();
    return OurWidget;
}

void UCategory_Button::SetScrollBox( UCategories_ScrollBox* p_pScrollBox )
{
    m_pScrollBox = p_pScrollBox;
}

void UCategory_Button::SetSubCategoryPath( FString p_sPath )
{
    subCategoryPath = p_sPath;
}

void UCategory_Button::exploreSubCategory()
{
    m_pScrollBox->ClearChildren();
    m_pScrollBox->RootPath = subCategoryPath;
    m_pScrollBox->FillButtons();
}

