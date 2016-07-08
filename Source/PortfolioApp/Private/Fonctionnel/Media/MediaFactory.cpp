#include "PortfolioApp.h"

#include "MediaFactory.h"
#include "Media.h"
#include "Picture.h"
#include "Anim.h"
#include "Sound.h"
#include "Object3D.h"
#include <iostream>



MediaFactory::MediaFactory()
{
}


MediaFactory::~MediaFactory()
{
}


Media* MediaFactory::createMedia(FString p_sPath)
{

	Media* media = nullptr;
	uint8 iType = (uint8) MediaFactory::returnType(p_sPath);
	switch (iType)
	{
	case (uint8) EMedia::EPicture :
		media = new Picture();
		break;
	case (uint8) EMedia::EAnim :
		media = new Anim();
		break;
	case (uint8)EMedia::ESound:
		media = new Sound();
		break;
	case (uint8) EMedia::EObject3D:
		media = new Object3D();
		break;
	}
	return media;
}

EMedia MediaFactory::returnType(FString p_sPath)
{
	if (FPaths::GetExtension(p_sPath).ToLower() == "jpg" ||
		FPaths::GetExtension(p_sPath).ToLower() == "jpeg" ||
		FPaths::GetExtension(p_sPath).ToLower() == "png" ||
		FPaths::GetExtension(p_sPath).ToLower() == "bmp")
	{
		return EMedia::EPicture;
	}
	else if (FPaths::GetExtension(p_sPath).ToLower() == "avi" ||
			FPaths::GetExtension(p_sPath).ToLower() == "mpg4" ||
			FPaths::GetExtension(p_sPath).ToLower() == "mpeg4" ||
			FPaths::GetExtension(p_sPath).ToLower() == "wmv")
	{
		return EMedia::EAnim;
	}
	else if (FPaths::GetExtension(p_sPath).ToLower() == "mp3" ||
			FPaths::GetExtension(p_sPath).ToLower() == "wav" )
	{
		return EMedia::ESound;
	}
	else if (FPaths::GetExtension(p_sPath).ToLower() == "obj" ||
			FPaths::GetExtension(p_sPath).ToLower() == "fbx" ||
			FPaths::GetExtension(p_sPath).ToLower() == "3ds")
	{
		return EMedia::EObject3D;
	}
	else return EMedia::EUndefined;
}