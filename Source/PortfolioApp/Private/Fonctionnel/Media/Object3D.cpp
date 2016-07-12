#include "PortfolioApp.h"


#include "Object3D.h"



Object3D::Object3D(uint8 p_iExtension)
{
	m_sType = "Object3D";
	m_iExtension = p_iExtension;
}


Object3D::~Object3D()
{
}
