#pragma once

#include "Media.h"

class Sound : public Media
{
public:
	Sound(FString p_sExtension);
	~Sound();
};

