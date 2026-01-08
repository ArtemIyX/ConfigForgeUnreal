#pragma once
#include "CoreMinimal.h"
#include "AssetTypeActions_ConfigForge.h"
#include "Data/ConfigForgeMetaDataObject.h"

class CONFIGFORGEEDITOR_API FAssetTypeActions_MetaObject : public FAssetTypeActions_ConfigForge
{
public:
	FAssetTypeActions_MetaObject()
	{
		Name = FText::FromString("Meta Data Object");
		SupportedClass = UConfigForgeMetaDataObject::StaticClass();
	}
};