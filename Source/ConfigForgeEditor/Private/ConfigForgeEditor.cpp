#include "ConfigForgeEditor.h"

#include "AssetToolsModule.h"
#include "EdGraphUtilities.h"
#include "Factories/AssetTypeActions_ConfigSetup.h"
#include "Factories/AssetTypeActions_PathProvider.h"
#include "Interfaces/IPluginManager.h"

#include "Styling/SlateStyleRegistry.h"

TSharedPtr<FSlateStyleSet> FConfigForgeEditorModule::StyleSet;

#define LOCTEXT_NAMESPACE "FConfigForgeEditorModule"

void FConfigForgeEditorModule::UnregisterAssetActions()
{
	IAssetTools& assetTools = IAssetTools::Get();
	const int32 n = AssetActions.Num();
	for (int32 i = 0; i < n; ++i)
	{
		assetTools.UnregisterAssetTypeActions(AssetActions[i].ToSharedRef());
	}
	AssetActions.Empty();
}

void FConfigForgeEditorModule::UnregisterPinFactories()
{
	const int32 n = PinFactories.Num();
	for (int32 i = 0; i < n; ++i)
	{
		FEdGraphUtilities::UnregisterVisualPinFactory(PinFactories[i]);
	}
	PinFactories.Empty();
}

void FConfigForgeEditorModule::StartupModule()
{
	if (GEditor)
	{
		if (!StyleSet.IsValid())
		{
			StyleSet = Create();
			FSlateStyleRegistry::RegisterSlateStyle(*StyleSet.Get());
		}

		IAssetTools& assetTools = IAssetTools::Get();
		assetTools.RegisterAdvancedAssetCategory(FName(TEXT("Config")), FText::FromString(TEXT("Config Forge")));
		RegisterAssetActions<FAssetTypeActions_PathProvider>(assetTools);
		RegisterAssetActions<FAssetTypeActions_ConfigSetup>(assetTools);
		
		//RegisterPinFactory<FStringListPinFactory>();
	}
}

void FConfigForgeEditorModule::ShutdownModule()
{
	if (GEditor && FSlateApplication::IsInitialized())
	{
		if (StyleSet.IsValid())
		{
			FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet.Get());
			StyleSet.Reset();
		}
		UnregisterAssetActions();
		UnregisterPinFactories();
	}
}

TSharedRef<FSlateStyleSet> FConfigForgeEditorModule::Create() const
{
	TSharedRef<FSlateStyleSet> style = MakeShareable(new FSlateStyleSet("ConfigForgeStyle"));

	// Get plugin base directory
	FString contentDir = IPluginManager::Get().FindPlugin(TEXT("ConfigForge"))->GetBaseDir() / TEXT("Resources");

	style->SetContentRoot(contentDir);

	// Define the thumbnail brush (128x128 size)
	const FVector2D icon16(16.0f, 16.0f);

	// Smaller icon for lists/context menus (16x16)
	const FVector2D icon128(128.0f, 128.0f);

	style->Set("ClassThumbnail.ConfigForgeFile",
		new FSlateImageBrush(style->RootToContentDir(TEXT("ConfigForgeFile128.png")), icon128));

	style->Set("ClassIcon.ConfigForgeFile",
		new FSlateImageBrush(style->RootToContentDir(TEXT("ConfigForgeFile16.png")), icon16));

	style->Set("ClassThumbnail.ConfigForgeCategory",
		new FSlateImageBrush(style->RootToContentDir(TEXT("ConfigForgeCategory128.png")), icon128));

	style->Set("ClassIcon.ConfigForgeCategory",
		new FSlateImageBrush(style->RootToContentDir(TEXT("ConfigForgeCategory16.png")), icon16));

	style->Set("ClassThumbnail.ConfigValueObject",
		new FSlateImageBrush(style->RootToContentDir(TEXT("ConfigValueObject128.png")), icon128));

	style->Set("ClassIcon.ConfigValueObject",
		new FSlateImageBrush(style->RootToContentDir(TEXT("ConfigValueObject16.png")), icon16));

	style->Set("ClassThumbnail.BoolConfigObject",
		new FSlateImageBrush(style->RootToContentDir(TEXT("BoolConfigObject128.png")), icon128));

	style->Set("ClassIcon.BoolConfigObject",
		new FSlateImageBrush(style->RootToContentDir(TEXT("BoolConfigObject16.png")), icon16));

	style->Set("ClassThumbnail.DoubleConfigObject",
		new FSlateImageBrush(style->RootToContentDir(TEXT("DoubleConfigObject128.png")), icon128));

	style->Set("ClassIcon.DoubleConfigObject",
		new FSlateImageBrush(style->RootToContentDir(TEXT("DoubleConfigObject16.png")), icon16));

	style->Set("ClassThumbnail.FloatConfigObject",
		new FSlateImageBrush(style->RootToContentDir(TEXT("FloatConfigObject128.png")), icon128));

	style->Set("ClassIcon.FloatConfigObject",
		new FSlateImageBrush(style->RootToContentDir(TEXT("FloatConfigObject16.png")), icon16));

	style->Set("ClassThumbnail.Int8ConfigObject",
		new FSlateImageBrush(style->RootToContentDir(TEXT("Int8ConfigObject128.png")), icon128));

	style->Set("ClassIcon.Int8ConfigObject",
		new FSlateImageBrush(style->RootToContentDir(TEXT("Int8ConfigObject16.png")), icon16));

	style->Set("ClassThumbnail.Int32ConfigObject",
		new FSlateImageBrush(style->RootToContentDir(TEXT("Int32ConfigObject128.png")), icon128));

	style->Set("ClassIcon.Int32ConfigObject",
		new FSlateImageBrush(style->RootToContentDir(TEXT("Int32ConfigObject16.png")), icon16));

	style->Set("ClassThumbnail.IntConfigObject",
		new FSlateImageBrush(style->RootToContentDir(TEXT("Int32ConfigObject128.png")), icon128));

	style->Set("ClassIcon.IntConfigObject",
		new FSlateImageBrush(style->RootToContentDir(TEXT("Int32ConfigObject16.png")), icon16));

	style->Set("ClassThumbnail.Int64ConfigObject",
		new FSlateImageBrush(style->RootToContentDir(TEXT("Int64ConfigObject128.png")), icon128));

	style->Set("ClassIcon.Int64ConfigObject",
		new FSlateImageBrush(style->RootToContentDir(TEXT("Int64ConfigObject16.png")), icon16));

	style->Set("ClassThumbnail.StringConfigObject",
		new FSlateImageBrush(style->RootToContentDir(TEXT("StringConfigObject128.png")), icon128));

	style->Set("ClassIcon.StringConfigObject",
		new FSlateImageBrush(style->RootToContentDir(TEXT("StringConfigObject16.png")), icon16));

	style->Set("ClassThumbnail.ConfigForgeSetup",
		new FSlateImageBrush(style->RootToContentDir(TEXT("ConfigForgeSetup128.png")), icon128));

	style->Set("ClassIcon.ConfigForgeSetup",
		new FSlateImageBrush(style->RootToContentDir(TEXT("ConfigForgeSetup16.png")), icon16));

	style->Set("ClassThumbnail.ConfigPathProvider",
		new FSlateImageBrush(style->RootToContentDir(TEXT("ConfigPathProvider128.png")), icon128));

	style->Set("ClassIcon.ConfigPathProvider",
		new FSlateImageBrush(style->RootToContentDir(TEXT("ConfigPathProvider16.png")), icon16));

	return style;
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FConfigForgeEditorModule, ConfigForgeEditor)