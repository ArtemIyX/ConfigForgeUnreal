// © Artem Podorozhko. All Rights Reserved. This project, including all associated assets, code, and content, is the property of Artem Podorozhko. Unauthorized use, distribution, or modification is strictly prohibited.

#pragma once

#include "CoreMinimal.h"
#include "ConfigForgeFactory_Base.h"
#include "Factories/BlueprintFactory.h"
#include "PathProviderFactory.generated.h"


UCLASS()
class CONFIGFORGEEDITOR_API UPathProviderFactory : public UConfigForgeFactory_Base
{
	GENERATED_BODY()

public:
	UPathProviderFactory();

public:
	virtual FString GetDefaultNewAssetName() const override { return FString(TEXT("BP_PathProvider_")); }
	virtual bool CanCreateNew() const override { return true; }
};