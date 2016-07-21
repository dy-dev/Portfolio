#pragma once

#include <string>
#include <Runtime/Core/Public/Containers/Map.h>
#include "Enums.h"


class UMedia;



class MediaFactory
{
public:
	static MediaFactory* getInstance();

	UMedia* createMedia(FString p_sPath, FString p_sFullPath);
	TPair<EMedia, EExtension> returnType(FString p_sPath);
	EExtension returnExtension(FString p_sExtension);

private :
	MediaFactory();
	~MediaFactory();

	static MediaFactory* uniqueInstance;
};

