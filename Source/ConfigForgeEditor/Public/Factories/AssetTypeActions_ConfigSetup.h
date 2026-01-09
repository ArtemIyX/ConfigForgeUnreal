// © Artem Podorozhko. All Rights Reserved. This project, including all associated assets, code, and content, is the property of Artem Podorozhko. Unauthorized use, distribution, or modification is strictly prohibited.

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_ConfigForge.h"
#include "Data/Asset/ConfigForgeSetup.h"


class CONFIGFORGEEDITOR_API FAssetTypeActions_ConfigSetup : public FAssetTypeActions_ConfigForge
{
public:
	FAssetTypeActions_ConfigSetup()
	{
		Name = FText::FromString("Config Setup");
		SupportedClass = UConfigForgeSetup::StaticClass();
	}
};