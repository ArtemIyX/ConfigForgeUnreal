// © Artem Podorozhko. All Rights Reserved. This project, including all associated assets, code, and content, is the property of Artem Podorozhko. Unauthorized use, distribution, or modification is strictly prohibited.


#include "Factories/ConfigForgeSetupFactory.h"

#include "Data/ConfigForgeSetup.h"

UConfigForgeSetupFactory::UConfigForgeSetupFactory()
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UConfigForgeSetup::StaticClass();
}