#pragma once

#include "FormulaCore.h"

class FKeyword
{
public:
	FKeyword(const FKeyword&) = delete;

	FKeyword(const char* StringPtr, uint8 Length)
		: StringPtr(StringPtr), Length(Length)
	{}

	template<uint8 StringLength>
	bool operator == (const FStringLiteral<StringLength>& String) const
	{
        if (Length != StringLength - 1)
            return false;

        for (size_t i = 0; i < Length; i++)
        {
			if (StringPtr[i] != String[i])
				return false;
        }

        return true;
	}

	const uint8 Length;

private:
	const char* const StringPtr;
};