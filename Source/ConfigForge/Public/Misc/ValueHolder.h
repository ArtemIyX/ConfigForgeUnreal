#pragma once
#include "CoreMinimal.h"
#include "ValueHolderBase.h"

// Templated derived class that holds the actual value
template<typename T>
class FValueHolder : public FValueHolderBase
{
public:
	T Value;
    
	explicit FValueHolder(const T& InValue) : Value(InValue) {}
	explicit FValueHolder(T&& InValue) : Value(MoveTemp(InValue)) {}
    
	virtual FValueHolderBase* Clone() const override
	{
		return new FValueHolder<T>(Value);
	}
};