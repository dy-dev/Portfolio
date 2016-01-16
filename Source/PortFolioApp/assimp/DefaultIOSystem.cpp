/*
---------------------------------------------------------------------------
Open Asset Import Library (assimp)
---------------------------------------------------------------------------

Copyright (c) 2006-2012, assimp team

All rights reserved.

Redistribution and use of this software in source and binary forms, 
with or without modification, are permitted provided that the following 
conditions are met:

* Redistributions of source code must retain the above
  copyright notice, this list of conditions and the
  following disclaimer.

* Redistributions in binary form must reproduce the above
  copyright notice, this list of conditions and the
  following disclaimer in the documentation and/or other
  materials provided with the distribution.

* Neither the name of the assimp team, nor the names of its
  contributors may be used to endorse or promote products
  derived from this software without specific prior
  written permission of the assimp team.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
---------------------------------------------------------------------------
*/
/** @file Default implementation of IOSystem using the standard C file functions */
#include "PortFolioApp.h"

#include "AssimpPCH.h"

#include <stdlib.h>
#include "DefaultIOSystem.h"
#include "DefaultIOStream.h"

#ifdef __unix__
#include <sys/param.h>
#include <stdlib.h>
#endif

using namespace Assimp;

// ------------------------------------------------------------------------------------------------
// Constructor. 
DefaultIOSystem::DefaultIOSystem()
{
	// nothing to do here
}

// ------------------------------------------------------------------------------------------------
// Destructor. 
DefaultIOSystem::~DefaultIOSystem()
{
	// nothing to do here
}

// ------------------------------------------------------------------------------------------------
// Tests for the existence of a file at the given path.
bool DefaultIOSystem::Exists( const char* pFile) const
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "bool DefaultIOSystem::Exists");
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, pFile);
	FILE* file = nullptr;//::fopen( pFile, "rb");
	if (!file)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, std::string("Error opening file unexist.ent: " + std::string( strerror(errno))).c_str() );
		if (FPaths::FileExists(FString(pFile)))
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "the UE way works");
			return true;
		}
		return false;
	}
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "fopen succeedded");
	::fclose( file);
	return true;
}

// ------------------------------------------------------------------------------------------------
// Open a new file with a given path.
IOStream* DefaultIOSystem::Open( const char* strFile, const char* strMode)
{
	ai_assert(NULL != strFile);
	ai_assert(NULL != strMode);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "fopen will fail again");
	FILE* file = nullptr;// ::fopen(strFile, strMode);
	if (file != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "fopen HAS NOT failed this time");
		return new DefaultIOStream(file, (std::string) strFile);
	}
	else if (FPaths::FileExists(FString(strFile)))
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "fopen HAS INDEED failed again");
		IPlatformFile& PlatformFile = IPlatformFile::GetPlatformPhysical();
		IFileHandle* pFileHandle = PlatformFile.OpenRead(*FString(strFile));
		if (pFileHandle == nullptr)
		{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "fopen HAS INDEED failed again");
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Platformfile failed to openread : " + FString(strFile));
			return nullptr;
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "platform file opened file : " + FString(strFile));
		}
		return new DefaultIOStream(pFileHandle, (std::string) strFile);
	}
	return nullptr;
}

// ------------------------------------------------------------------------------------------------
// Closes the given file and releases all resources associated with it.
void DefaultIOSystem::Close( IOStream* pFile)
{
	delete pFile;
}

// ------------------------------------------------------------------------------------------------
// Returns the operation specific directory separator
char DefaultIOSystem::getOsSeparator() const
{
#ifndef _WIN32
	return '/';
#else
	return '\\';
#endif
}

// ------------------------------------------------------------------------------------------------
// IOSystem default implementation (ComparePaths isn't a pure virtual function)
bool IOSystem::ComparePaths (const char* one, const char* second) const
{
	return !ASSIMP_stricmp(one,second);
}

// maximum path length
// XXX http://insanecoding.blogspot.com/2007/11/pathmax-simply-isnt.html 
#ifdef PATH_MAX
#	define PATHLIMIT PATH_MAX
#else
#	define PATHLIMIT 4096
#endif

// ------------------------------------------------------------------------------------------------
// Convert a relative path into an absolute path
inline void MakeAbsolutePath (const char* in, char* _out)
{
	ai_assert(in && _out);
	char* ret;
#ifdef _WIN32
	ret = ::_fullpath(_out, in,PATHLIMIT);
#else
    	// use realpath
    	ret = realpath(in, _out);
#endif  
	if(!ret) {
		// preserve the input path, maybe someone else is able to fix
		// the path before it is accessed (e.g. our file system filter)
		DefaultLogger::get()->warn("Invalid path: "+std::string(in));
		strcpy(_out,in);
	}  
}

// ------------------------------------------------------------------------------------------------
// DefaultIOSystem's more specialized implementation
bool DefaultIOSystem::ComparePaths (const char* one, const char* second) const
{
	// chances are quite good both paths are formatted identically,
	// so we can hopefully return here already
	if( !ASSIMP_stricmp(one,second) )
		return true;

	char temp1[PATHLIMIT];
	char temp2[PATHLIMIT];
	
	MakeAbsolutePath (one, temp1);
	MakeAbsolutePath (second, temp2);

	return !ASSIMP_stricmp(temp1,temp2);
}

#undef PATHLIMIT