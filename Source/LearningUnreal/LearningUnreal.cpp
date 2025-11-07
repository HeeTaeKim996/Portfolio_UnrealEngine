// Copyright Epic Games, Inc. All Rights Reserved.

#include "LearningUnreal.h"
#include "Modules/ModuleManager.h"




#if 1
IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, LearningUnreal, "LearningUnreal" );
#else

#include "R1LogChannels.h"

class MainModule : public FDefaultGameModuleImpl
{
	virtual void StartupModule() override
	{
		UE_LOG(LogR1, Log, TEXT("HelloWorld"));
	}

	virtual void ShutdownModule() override
	{

	}
};


IMPLEMENT_PRIMARY_GAME_MODULE(MainModule, LearningUnreal, "LearningUnreal");
#endif