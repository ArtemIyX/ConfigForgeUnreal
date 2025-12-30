// © Artem Podorozhko. All Rights Reserved. This project, including all associated assets, code, and content, is the property of Artem Podorozhko. Unauthorized use, distribution, or modification is strictly prohibited.


#include "Factories/AssetTypeActions_ConfigForge.h"
#include "AssetToolsModule.h"

FAssetTypeActions_ConfigForge::FAssetTypeActions_ConfigForge()
{
	SupportedClass = UObject::StaticClass();
	Name = FText::FromString(FString(TEXT("DefaultName")));
}

uint32 FAssetTypeActions_ConfigForge::GetCategories()
{
	if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
	{
		uint32 res = FAssetToolsModule::GetModule().Get().FindAdvancedAssetCategory(FName("Config"));
		return res;
	}

	return EAssetTypeCategories::Misc;
}