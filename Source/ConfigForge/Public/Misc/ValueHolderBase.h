#pragma once
#include "CoreMinimal.h"

class CONFIGFORGE_API FValueHolderBase
{
public:
	virtual ~FValueHolderBase() = default;
	virtual FValueHolderBase* Clone() const = 0;
	
};

