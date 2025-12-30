// © Artem Podorozhko. All Rights Reserved. This project, including all associated assets, code, and content, is the property of Artem Podorozhko. Unauthorized use, distribution, or modification is strictly prohibited.

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_ConfigForge.h"
#include "Data/ConfigPathProvider.h"


class CONFIGFORGEEDITOR_API FAssetTypeActions_PathProvider : public FAssetTypeActions_ConfigForge
{
public:
	FAssetTypeActions_PathProvider()
	{
		Name = FText::FromString(TEXT("Path Provider"));
		SupportedClass = UConfigPathProvider::StaticClass();
	}
};