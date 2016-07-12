#pragma once

#include <string>
#include <Runtime/Core/Public/Containers/Map.h>
#include "Enums.h"


class Media;



class MediaFactory
{
public:
	static MediaFactory* getInstance();

	Media* createMedia(FString p_sPath);
	TPair<EMedia, EExtension> returnType(FString p_sPath);
	EExtension returnExtension(FString p_sExtension);

private :
	MediaFactory();
	~MediaFactory();

	static MediaFactory* uniqueInstance;
};

