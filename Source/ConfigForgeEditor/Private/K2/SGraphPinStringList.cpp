// SGraphPinStringList.cpp
#include "K2/SGraphPinStringList.h"
#include "K2/K2Node_GetConfigForgeFile.h"
#include "Widgets/Input/SComboBox.h"

void SGraphPinStringList::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);
	RefreshOptionsList();
}

TSharedRef<SWidget> SGraphPinStringList::GetDefaultValueWidget()
{
	RefreshOptionsList();

	// Find current selection
	FString CurrentValue = GraphPinObj->GetDefaultAsString();
	CurrentSelection = nullptr;

	for (TSharedPtr<FString>& Option : OptionsList)
	{
		if (Option.IsValid() && *Option == CurrentValue)
		{
			CurrentSelection = Option;
			break;
		}
	}

	// If no match, select first option
	if (!CurrentSelection.IsValid() && OptionsList.Num() > 0)
	{
		CurrentSelection = OptionsList[0];
	}

	return SNew(SComboBox<TSharedPtr<FString>>)
		.OptionsSource(&OptionsList)
		.OnGenerateWidget(this, &SGraphPinStringList::OnGenerateWidget)
		.OnSelectionChanged(this, &SGraphPinStringList::OnSelectionChanged)
		.Content()
		[
			SNew(STextBlock)
			.Text(this, &SGraphPinStringList::GetSelectedText)
			.Font(FAppStyle::GetFontStyle(TEXT("PropertyWindow.NormalFont")))
		];
}

void SGraphPinStringList::OnSelectionChanged(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo)
{
	if (NewSelection.IsValid())
	{
		CurrentSelection = NewSelection;
		GraphPinObj->GetSchema()->TrySetDefaultValue(*GraphPinObj, *NewSelection);
	}
}

TSharedRef<SWidget> SGraphPinStringList::OnGenerateWidget(TSharedPtr<FString> InItem)
{
	return SNew(STextBlock)
		.Text(FText::FromString(*InItem))
		.Font(FAppStyle::GetFontStyle(TEXT("PropertyWindow.NormalFont")));
}

FText SGraphPinStringList::GetSelectedText() const
{
	if (CurrentSelection.IsValid())
	{
		return FText::FromString(*CurrentSelection);
	}
	return FText::FromString(TEXT("Select File"));
}

void SGraphPinStringList::RefreshOptionsList()
{
	OptionsList.Empty();

	if (UK2Node_GetConfigForgeFile* OwningNode = Cast<UK2Node_GetConfigForgeFile>(GraphPinObj->GetOwningNode()))
	{
		OptionsList = OwningNode->GetFileNameOptions();
	}
}