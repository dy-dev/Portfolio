#include "PortfolioApp.h"

#include "Picture.h"



Picture::Picture(FString p_sExtension)
{
	m_sType = "Picture";
	m_sExtension = p_sExtension;
	//FillData();
}


Picture::~Picture()
{
}
