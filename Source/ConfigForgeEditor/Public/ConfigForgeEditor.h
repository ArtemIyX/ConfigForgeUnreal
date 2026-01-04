#pragma once

#include "CoreMinimal.h"
#include "EdGraphUtilities.h"
#include "IAssetTypeActions.h"
#include "IAssetTools.h"
#include "Modules/ModuleManager.h"

class FConfigForgeEditorModule : public IModuleInterface
{
protected:
	TArray<TSharedPtr<IAssetTypeActions>> AssetActions;

	TArray<TSharedPtr<FGraphPanelPinFactory>> PinFactories;

protected:
	template <typename T>
	void RegisterAssetActions(IAssetTools& InAssetTools)
	{
		TSharedRef<IAssetTypeActions> stateActions = MakeShareable(new T());
		AssetActions.Add(stateActions);
		InAssetTools.RegisterAssetTypeActions(stateActions);
	}

	template <typename T>
	void RegisterPinFactory()
	{
		TSharedPtr<FGraphPanelPinFactory> pinFactory = MakeShareable(new T());
		PinFactories.Add(pinFactory);
		FEdGraphUtilities::RegisterVisualPinFactory(pinFactory);
	}

	void UnregisterAssetActions();
	void UnregisterPinFactories();

public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

public:
	static TSharedPtr<FSlateStyleSet> StyleSet;

private:
	TSharedRef<FSlateStyleSet> Create() const;
};