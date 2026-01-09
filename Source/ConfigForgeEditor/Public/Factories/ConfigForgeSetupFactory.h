// © Artem Podorozhko. All Rights Reserved. This project, including all associated assets, code, and content, is the property of Artem Podorozhko. Unauthorized use, distribution, or modification is strictly prohibited.

#pragma once

#include "CoreMinimal.h"
#include "ConfigForgeSetupFactory.generated.h"

/**
 * 
 */
UCLASS()
class CONFIGFORGEEDITOR_API UConfigForgeSetupFactory : public UFactory
{
	GENERATED_BODY()

public:
	UConfigForgeSetupFactory();

public:
	virtual FString GetDefaultNewAssetName() const override { return FString(TEXT("BP_ConfigSetup_")); }
	virtual bool CanCreateNew() const override { return true; }
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext) override;
};