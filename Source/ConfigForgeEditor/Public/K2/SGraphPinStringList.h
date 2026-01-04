// © Artem Podorozhko. All Rights Reserved. This project, including all associated assets, code, and content, is the property of Artem Podorozhko. Unauthorized use, distribution, or modification is strictly prohibited.

#pragma once

#include "CoreMinimal.h"
#include "SGraphPin.h"


/**
 * @brief Custom pin widget that displays a dropdown list of strings.
 */
class CONFIGFORGEEDITOR_API SGraphPinStringList : public SGraphPin
{
public:
	SLATE_BEGIN_ARGS(SGraphPinStringList) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);

protected:
	// SGraphPin interface
	virtual TSharedRef<SWidget> GetDefaultValueWidget() override;
	// End of SGraphPin interface

private:
	// Dropdown options
	TArray<TSharedPtr<FString>> OptionsList;

	// Currently selected option
	TSharedPtr<FString> CurrentSelection;

	// Handlers
	void OnSelectionChanged(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo);
	TSharedRef<SWidget> OnGenerateWidget(TSharedPtr<FString> InItem);
	FText GetSelectedText() const;

	// Refresh the options list
	void RefreshOptionsList();
};
