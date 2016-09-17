// RandomChars.h

#pragma once

using namespace System;
using namespace System::Text;

namespace Randoms {

	public ref class GetRandoms
	{
	public:
		static wchar_t GetOneChineseCharacter()
		{
			String^ list = gcnew String("0123456789abcdef");
			Random^ theRandom = gcnew Random(Guid::NewGuid().GetHashCode());
			String^ str1 = "" + list[theRandom->Next(11, 14)] + list[theRandom->Next(0, 7)];
			String^ str2 = "" + list[theRandom->Next(10, 16)] + list[theRandom->Next(1, 15)];
			Text::Encoding^ gb = Text::Encoding::GetEncoding("gb2312"); 
			return gb->GetString(gcnew array<Byte>(2){Convert::ToByte(str1, 16), Convert::ToByte(str2, 16)})[0];
		}
		static wchar_t GetOneAlphabet()
		{
			Random^ theRandom = gcnew Random(Guid::NewGuid().GetHashCode());
			int index = theRandom->Next(0, 52);
			if( index < 26 )
			{
				return wchar_t(index + 65);
			}
			else
			{
				return wchar_t(index + 71);
			}
		}
		static wchar_t GetOneDigit()
		{
			Random^ theRandom = gcnew Random(Guid::NewGuid().GetHashCode());
			return wchar_t(theRandom->Next(48, 58));
		}
		static int GetOneInteger(int lowIncluded, int highExcluded)
		{
			Random^ theRandom = gcnew Random(Guid::NewGuid().GetHashCode());
			return theRandom->Next(lowIncluded, highExcluded);
		}
	};
}
