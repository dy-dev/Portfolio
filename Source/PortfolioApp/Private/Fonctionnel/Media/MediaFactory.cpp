#include "PortfolioApp.h"

#include "MediaFactory.h"
#include "Media.h"
#include "Picture.h"
#include "Anim.h"
#include "Sound.h"
#include "Object3D.h"
#include "Enums.h"
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

UMedia* MediaFactory::createMedia(FString p_sPath, FString p_sFullPath)
{

	UMedia* media = nullptr;
	FString sExtension = FPaths::GetExtension(p_sPath).ToLower();
	TPair<EMedia, EExtension> iType = MediaFactory::returnType(sExtension);
	switch ((uint8) iType.Key )
	{
	case (uint8) EMedia::EPicture :
		//media = new UPicture(p_sPath, (uint8) iType.Value);
		media = NewObject<UPicture>(UPicture::StaticClass());
		media->Initializer(p_sPath, p_sFullPath, (uint8)iType.Value);
		break;
	case (uint8) EMedia::EAnim :
		media = new Anim((uint8) iType.Value);
		break;
	case (uint8)EMedia::ESound:
		media = new Sound((uint8) iType.Value);
		break;
	case (uint8) EMedia::EObject3D:
		media = new Object3D((uint8) iType.Value);
		break;
	}
	return media;
}

TPair<EMedia, EExtension> MediaFactory::returnType(FString p_sExtension)
{
	EExtension ext = EExtension::EUndefined;
	if (p_sExtension == "jpg" ||
		p_sExtension == "jpeg" ||
		p_sExtension == "png" ||
		p_sExtension == "bmp")
	{
		return TPairInitializer<EMedia, EExtension> (EMedia::EPicture, returnExtension(p_sExtension));
	}
	else if (p_sExtension == "avi" ||
			p_sExtension == "mp4" ||
			p_sExtension == "mpeg4" ||
			p_sExtension == "wmv")
	{
		return TPairInitializer<EMedia, EExtension>(EMedia::EAnim, returnExtension(p_sExtension));
	}
	else if (p_sExtension == "mp3" ||
		p_sExtension == "wav" )
	{
		return TPairInitializer<EMedia, EExtension>(EMedia::ESound, returnExtension(p_sExtension));
	}
	else if (p_sExtension == "obj" ||
		p_sExtension == "fbx" ||
		p_sExtension == "3ds")
	{
		return TPairInitializer<EMedia, EExtension>(EMedia::EObject3D, returnExtension(p_sExtension));
	}
	return TPairInitializer<EMedia, EExtension>(EMedia::EUndefined, EExtension::EUndefined);
}

EExtension MediaFactory::returnExtension(FString p_sExtension)
{
	//PICTURE
	if (p_sExtension == "jpg" ||
		p_sExtension == "jpeg")
		return  EExtension::EJPG;
	else if (p_sExtension == "png")
		return  EExtension::EPNG;
	else if (p_sExtension == "bmp")
		return  EExtension::EBMP;

	//ANIM
	else if (p_sExtension == "avi")
		return  EExtension::EAVI;
	else if (p_sExtension == "mp4" ||
		p_sExtension == "mpeg4")
		return  EExtension::EMP4;
	else if (p_sExtension == "wmv")
		return  EExtension::EWMV;

	//SOUND
	else if (p_sExtension == "mp3")
		return  EExtension::EMP3;
	else if (p_sExtension == "wav")
		return  EExtension::EWAV;
	else if (p_sExtension == "obj")

	//3D
		return  EExtension::EOBJ;
	else if (p_sExtension == "fbx")
		return  EExtension::EFBX;
	else if (p_sExtension == "3ds")
		return  EExtension::E3DS;

	//UNDEFINED
	else return EExtension::EUndefined;
}