#include "PortfolioApp.h"

#include "MediaFactory.h"
#include "Media.h"
#include "Picture.h"
#include "Anim.h"
#include "Sound.h"
#include "Object3D.h"
#include <iostream>


MediaFactory* MediaFactory::uniqueInstance = nullptr;

MediaFactory::MediaFactory()
{
}


MediaFactory::~MediaFactory()
{
}


MediaFactory* MediaFactory::getInstance()
{
	if (nullptr == uniqueInstance )
	{
		uniqueInstance = new MediaFactory();
	}
		return uniqueInstance;
}

Media* MediaFactory::createMedia(FString p_sPath)
{

	Media* media = nullptr;
	FString sExtension = FPaths::GetExtension(p_sPath).ToLower();
	uint8 iType = (uint8) MediaFactory::returnType(sExtension);
	switch (iType)
	{
	case (uint8) EMedia::EPicture :
		media = new Picture(sExtension);
		break;
	case (uint8) EMedia::EAnim :
		media = new Anim(sExtension);
		break;
	case (uint8)EMedia::ESound:
		media = new Sound(sExtension);
		break;
	case (uint8) EMedia::EObject3D:
		media = new Object3D(sExtension);
		break;
	}
	return media;
}

EMedia MediaFactory::returnType(FString p_sExtension)
{
	if (p_sExtension == "jpg" ||
		p_sExtension == "jpeg" ||
		p_sExtension == "png" ||
		p_sExtension == "bmp")
	{
		return EMedia::EPicture;
	}
	else if (p_sExtension == "avi" ||
			p_sExtension == "mpg4" ||
			p_sExtension == "mpeg4" ||
			p_sExtension == "wmv")
	{
		return EMedia::EAnim;
	}
	else if (p_sExtension == "mp3" ||
		p_sExtension == "wav" )
	{
		return EMedia::ESound;
	}
	else if (p_sExtension == "obj" ||
		p_sExtension == "fbx" ||
		p_sExtension == "3ds")
	{
		return EMedia::EObject3D;
	}
	else return EMedia::EUndefined;
}