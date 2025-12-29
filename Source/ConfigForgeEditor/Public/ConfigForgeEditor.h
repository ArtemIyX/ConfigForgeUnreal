#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FConfigForgeEditorModule : public IModuleInterface
{
public:

    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

public:
	static TSharedPtr<FSlateStyleSet> StyleSet;

private:
	TSharedRef<FSlateStyleSet> Create() const;
};
