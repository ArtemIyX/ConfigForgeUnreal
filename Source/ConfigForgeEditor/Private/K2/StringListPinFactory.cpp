#include "K2/StringListPinFactory.h"
#include "K2/K2Node_GetConfigForgeFile.h"

TSharedPtr<SGraphPin> FStringListPinFactory::CreatePin(UEdGraphPin* InPin) const
{
	// Check if this pin belongs to our specific K2Node and has the 'StringList' tag
	if (InPin->PinType.PinCategory == UEdGraphSchema_K2::PC_String && InPin->PinName == "FileName")
	{
		if (InPin->GetOwningNode()->IsA<UK2Node_GetConfigForgeFile>())
		{
			return SNew(SGraphPinStringList, InPin);
		}
	}
	return nullptr;

}