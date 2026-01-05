// © Artem Podorozhko. All Rights Reserved. This project, including all associated assets, code, and content, is the property of Artem Podorozhko. Unauthorized use, distribution, or modification is strictly prohibited.


#include "Data/Value/ConfigValueObjectRuntime.h"

#include "Data/Value/ConfigValueObject.h"

void UConfigValueObjectRuntime::SetToFile(const TSharedPtr<FConfigForgeIniFile>& InFilePtr, const FString& InSection)
{
	if (!InFilePtr.IsValid())
		return;

	if (!RuntimeValue)
		return;

	RuntimeValue->SetToFile(InFilePtr, InSection);
}

bool UConfigValueObjectRuntime::GetFromFile(const TSharedPtr<FConfigForgeIniFile>& InFilePtr, const FString& InSection)
{
	if (!InFilePtr.IsValid())
		return false;

	if (!RuntimeValue)
		return false;

	return RuntimeValue->GetFromFile(InFilePtr, InSection);
}