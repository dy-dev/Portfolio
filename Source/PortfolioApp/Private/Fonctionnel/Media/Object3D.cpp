#include "PortfolioApp.h"


#include "Object3D.h"



Object3D::Object3D(FString p_sExtension)
{
	m_sType = "Object3D";
	m_sExtension = p_sExtension;
}


Object3D::~Object3D()
{
}
