// © Artem Podorozhko. All Rights Reserved. This project, including all associated assets, code, and content, is the property of Artem Podorozhko. Unauthorized use, distribution, or modification is strictly prohibited.


#include "Factories/MetaDataObjectFactory.h"
#include "Data/User/ConfigForgeMetaDataObject.h"

UMetaDataObjectFactory::UMetaDataObjectFactory()
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UConfigForgeMetaDataObject::StaticClass();
}