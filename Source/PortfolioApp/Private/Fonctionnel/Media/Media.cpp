#include "PortfolioApp.h"


#include "Media.h"



UMedia::UMedia()
{
}


UMedia::~UMedia()
{
}


void UMedia::Initializer(FString p_sPath, FString p_sFullPath, uint8 p_sExtension)
{
	m_sName = p_sPath;
	m_sFullPath = p_sFullPath;
	m_iExtension = p_sExtension;
}