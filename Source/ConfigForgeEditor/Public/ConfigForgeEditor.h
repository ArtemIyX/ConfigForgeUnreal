#pragma once

#include "CoreMinimal.h"
#include "IAssetTypeActions.h"
#include "IAssetTools.h"
#include "Modules/ModuleManager.h"

class FConfigForgeEditorModule : public IModuleInterface
{
protected:

	TArray<TSharedPtr<IAssetTypeActions>> AssetActions;

protected:
	template<typename T>
	void RegisterAssetActions(IAssetTools& InAssetTools)
	{
		TSharedRef<IAssetTypeActions> stateActions = MakeShareable(new T());
		AssetActions.Add(stateActions);
		InAssetTools.RegisterAssetTypeActions(stateActions);
	}

	void UnregisterAssetActions();
public:

    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

public:
	static TSharedPtr<FSlateStyleSet> StyleSet;

private:
	TSharedRef<FSlateStyleSet> Create() const;
};
