#pragma once

#include "Media.h"

class Picture : public Media
{
public:
	Picture(FString p_sExtension);
	~Picture();
};

