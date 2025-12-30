// © Artem Podorozhko. All Rights Reserved. This project, including all associated assets, code, and content, is the property of Artem Podorozhko. Unauthorized use, distribution, or modification is strictly prohibited.

#pragma once

#include "CoreMinimal.h"
#include "ConfigForgeFactory_Base.h"
#include "Factories/BlueprintFactory.h"
#include "ConfigForgeSetupFactory.generated.h"

/**
 * 
 */
UCLASS()
class CONFIGFORGEEDITOR_API UConfigForgeSetupFactory : public UConfigForgeFactory_Base
{
	GENERATED_BODY()

public:
	UConfigForgeSetupFactory();

public:
	
	virtual FString GetDefaultNewAssetName() const override { return FString(TEXT("BP_ConfigSetup_")); }
	virtual bool CanCreateNew() const override { return true; }
};