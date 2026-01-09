// © Artem Podorozhko. All Rights Reserved. This project, including all associated assets, code, and content, is the property of Artem Podorozhko. Unauthorized use, distribution, or modification is strictly prohibited.


#include "Factories/ConfigForgeSetupFactory.h"
#include "Data/Asset/ConfigForgeSetup.h"

UConfigForgeSetupFactory::UConfigForgeSetupFactory()
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UConfigForgeSetup::StaticClass();
}

UObject* UConfigForgeSetupFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext)
{
	return NewObject<UConfigForgeSetup>(InParent, SupportedClass, InName, Flags);
}