// Some copyright should be here...

#pragma once

#include "ModuleManager.h"



class FSwarmingModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};