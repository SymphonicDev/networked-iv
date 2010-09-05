//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CString.cpp
// Project: Shared
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#include <StdInc.h>

//#define C_STRING
#define BUFFER_SIZE 8192
#ifdef WIN32
#define stricmp _stricmp
#endif
#ifdef C_STRING
#define M_STRING (m_szString)
#else
#define M_STRING (*m_strString)
#endif

String::String()
{
	Init();
}

String::String(const char * szFormat, ...)
{
	Init();

	if(szFormat)
	{
		char szString[BUFFER_SIZE];
		va_list vaArgs;
		va_start(vaArgs, szFormat);
		vsprintf(szString, szFormat, vaArgs);
		va_end(vaArgs);
		Set(szString);
	}
}

String::~String()
{
#ifdef C_STRING
	if(IsAllocated())
	{
		Free();
	}
#else
	delete m_strString;
#endif
}

String& String::operator = (const char * szString)
{
	Set(szString);
	return *this;
}

String& String::operator += (const char * szString)
{
	Append(szString);
	return *this;
}

String& String::operator += (const unsigned char ucChar)
{
	Append(ucChar);
	return *this;
}

unsigned char String::operator [] (size_t sOffset)
{
	return GetChar(sOffset);
}

bool String::operator == (const char * szString)
{
	return (Compare(szString) == 0);
}

bool String::operator != (const char * szString)
{
	return (Compare(szString) != 0);
}

bool String::operator > (const char * szString)
{
	return (Compare(szString) > 0);
}

bool String::operator >= (const char * szString)
{
	return (Compare(szString) >= 0);
}

bool String::operator < (const char * szString)
{
	return (Compare(szString) < 0);
}

bool String::operator <= (const char * szString)
{
	return (Compare(szString) <= 0);
}

void String::Init()
{
#ifdef C_STRING
	m_sBytesAllocated = 0;
	m_szString = NULL;
	m_szEmptyString[0] = '\0';
#else
	m_strString = new std::string();
#endif
	m_sLimit = -1;
}

const char * String::Get() const
{
#ifdef C_STRING
	if(IsAllocated())
	{
		return m_szString;
	}

	return m_szEmptyString;
#else
	return m_strString->c_str();
#endif
}

const char * String::C_String() const
{
	return Get();
}

void String::Set(const char * szString)
{
	// Make sure the string is valid
	if(szString)
	{
#ifdef C_STRING
		// Get the string length
		size_t sLength = strlen(szString);

		// Make sure we have enough or not too much memory allocated
		Allocate(sLength + 1);

		// Set the string
		strncpy(m_szString, szString, sLength);

		// Truncate the string
		m_szString[sLength] = '\0';
#else
		// Set the string
		m_strString->assign(szString);
#endif

		// Ensure we havn't passed the string limit
		LimitTruncate();
	}
}

void String::Format(const char * szFormat, ...)
{
	char szString[BUFFER_SIZE];
	va_list vaArgs;
	va_start(vaArgs, szFormat);
	vsprintf(szString, szFormat, vaArgs);
	va_end(vaArgs);
	Set(szString);
}

size_t String::GetLength() const
{
#ifdef C_STRING
	if(IsAllocated())
	{
		return strlen(m_szString);
	}

	return 0;
#else
	return m_strString->size();
#endif
}

bool String::IsEmpty() const
{
#ifdef C_STRING
	if(IsAllocated())
	{
		return (GetLength() == 0);
	}

	return true;
#else
	return m_strString->empty();
#endif
}

void String::ToLower()
{
#ifdef C_STRING
	if(IsAllocated())
	{
#endif
		for(size_t i = 0; i < GetLength(); i++)
		{
			M_STRING[i] = tolower(M_STRING[i]);
		}
#ifdef C_STRING
	}
#endif
}

bool String::IsLower()
{
#ifdef C_STRING
	if(IsAllocated())
	{
#endif
		for(size_t i = 0; i < GetLength(); i++)
		{
			unsigned char cChar = M_STRING[i];

			if(((cChar >= 'a' && cChar <= 'Z') || (cChar >= 'A' && cChar <= 'Z')) && !islower(cChar))
			{
				return false;
			}
		}

		return true;
#ifdef C_STRING
	}

	return false;
#endif
}

void String::ToUpper()
{
#ifdef C_STRING
	if(IsAllocated())
	{
#endif
		for(size_t i = 0; i < GetLength(); i++)
		{
			M_STRING[i] = toupper(M_STRING[i]);
		}
#ifdef C_STRING
	}
#endif
}

bool String::IsUpper()
{
#ifdef C_STRING
	if(IsAllocated())
	{
#endif
		for(size_t i = 0; i < GetLength(); i++)
		{
			unsigned char cChar = M_STRING[i];

			if(((cChar >= 'a' && cChar <= 'Z') || (cChar >= 'A' && cChar <= 'Z')) && !isupper(cChar))
			{
				return false;
			}
		}

		return true;
#ifdef C_STRING
	}

	return false;
#endif
}

void String::Truncate(size_t sOffset)
{
#ifdef C_STRING
	if(IsAllocated())
	{
#endif
		// TODO: Use allocated size instead of/aswell as the string length?
		if(sOffset < GetLength())
		{
			M_STRING[sOffset] = '\0';
		}
#ifdef C_STRING
	}
#endif
}

void String::Erase(size_t sOffset, size_t sCount)
{
#ifdef C_STRING
	if(IsAllocated())
	{
		if((sOffset + sCount) < GetLength())
		{
			// Copy the string
			memcpy((m_szString + sOffset), (m_szString + (sOffset + sCount)), sCount);

			// Free any extra memory
			Allocate(sOffset);
		}
	}
#else
	m_strString->erase(sOffset, sCount);
#endif
}

void String::Clear()
{
#ifdef C_STRING
	if(IsAllocated())
	{
		Free();
	}
#else
	m_strString->clear();
#endif
}

int String::Compare(const char * szString)
{
	return strcmp(Get(), szString);
}

int String::ICompare(const char * szString)
{
	return stricmp(Get(), szString);
}

int String::ToInteger()
{
#ifdef C_STRING
	if(IsAllocated())
	{
#endif
		return atoi(Get());
#ifdef C_STRING
	}

	return 0;
#endif
}

bool String::ToBoolean()
{
	if(IsAllocated())
	{
		return (ToInteger() != 0);
	}

	return false;
}

void String::SetChar(size_t sOffset, unsigned char cChar)
{
#ifdef C_STRING
	if(IsAllocated())
	{
#endif
		// TODO: Use allocated size instead of/aswell as the string length?
		if(sOffset < GetLength())
		{
			M_STRING[sOffset] = cChar;
		}
#ifdef C_STRING
	}
#endif
}

unsigned char String::GetChar(size_t sOffset)
{
#ifdef C_STRING
	if(IsAllocated())
	{
#endif
		// TODO: Use allocated size instead of/aswell as the string length?
		if(sOffset < GetLength())
		{
			return M_STRING[sOffset];
		}
#ifdef C_STRING
	}
#endif

	return 0;
}

const char * String::SubStr(size_t sOffset, size_t sCount) const
{
#ifdef C_STRING
	// TODO
	// FIXME
	return 0;
#else
	return m_strString->substr(sOffset, sCount).c_str();
#endif
}

//void String::Replace(size_t sOffset, const char * szString)
//{
	// TODO:
//}

void String::Append(const char * szString)
{
	// Make sure the string is valid
	if(szString)
	{
#ifdef C_STRING
		// Get the string length
		size_t sLength = strlen(szString);

		// Get our length
		size_t sOurLength = GetLength();

		// Get the new length
		size_t sNewLength = (sOurLength + sLength);

		// Make sure we have enough memory allocated
		Allocate(sNewLength + 1);

		printf("Append %s, length is %d, str length is %d, need to allocate is %d\n", szString, GetLength(), sLength, (sNewLength + 1));

		// Copy the string to the end of our string
		memcpy((m_szString + sOurLength), szString, sLength);
		
		// Truncate the string
		m_szString[sNewLength] = '\0';
#else
		// Copy the string to the end of our string
		m_strString->append(szString);
#endif

		// Ensure we havn't passed the string limit
		LimitTruncate();
	}
}

void String::Append(const unsigned char ucChar)
{
#ifdef C_STRING
	size_t sLength = GetLength();
	Allocate(sLength + 2);

	char cTest[2];
	cTest[0] = ucChar;
	cTest[1] = '\0';

	if(sLength == 0)
	{
		Set(cTest);
	}
	else
	{
		strcat(m_szString, cTest);
	}

	//CLogFile::Printf("Length is %d, bytes allocated is %d", sLength, m_sBytesAllocated);

	//if(sLength + 1 < )
	//m_szString[sLength] = ucChar;
	//m_szString[sLength + 1] = '\0';
#else
	// TODO: Find another way to do this
	// Construct the string to append
	char szString[2];
	szString[0] = ucChar;
	szString[1] = '\0';

	// Copy the string to the end of our string
	m_strString->append(szString);
#endif

	LimitTruncate();
}

void String::Insert(size_t sOffset, const char * szString)
{
#ifdef C_STRING
	// TODO
#else
	m_strString->insert(sOffset, szString);
#endif

	LimitTruncate();
}

size_t String::Find(const char * szString) const
{
#ifdef C_STRING
	// TODO
#else
	return m_strString->find(szString);
#endif

	return -1;
}

bool String::Contains(const char * szString) const
{
	return (Find(szString) != -1);
}

size_t String::ReverseFind(const char * szString) const
{
#ifdef C_STRING
	// TODO
	return -1;
#else
	return m_strString->rfind(szString);
#endif
}

bool String::SetLimit(size_t sLimit)
{
	if(sLimit >= -1)
	{
		m_sLimit = sLimit;
		return true;
	}

	return false;
}

size_t String::GetLimit()
{
	return m_sLimit;
}

bool String::LimitTruncate()
{
	if(m_sLimit > -1 && GetLength() > m_sLimit)
	{
		M_STRING[m_sLimit] = '\0';
		return true;
	}

	return false;
}

// NOTE: If size is less than is allocated this will
// free the extra memory, so allocate is bad naming,
// should be something along the lines of "Reallocate"
void String::Allocate(size_t sSize)
{
	// If the size is 0 or less free the buffer
	/*if(sSize == 0)
	{
		Free();
		return;
	}*/

#ifdef C_STRING
	// Make sure we don't already have a suitable buffer
	if(m_sBytesAllocated < sSize)
	{
		m_szString = (char *)realloc(m_szString, sSize);
		m_sBytesAllocated = sSize;
	}
#else
	m_strString->reserve(sSize);
#endif
}

void String::Free()
{
	// Make sure we have a buffer allocated
#ifdef C_STRING
	if(m_sBytesAllocated > 0)
	{
		free(m_szString);
		m_szString = NULL;
		m_sBytesAllocated = 0;
	}
#else
	m_strString->clear();
#endif
}

size_t String::GetSize() const
{
#ifdef C_STRING
	return m_sBytesAllocated;
#else
	return m_strString->capacity();
#endif
}

bool String::IsAllocated() const
{
#ifdef C_STRING
	return (m_sBytesAllocated > 0);
#else
	//return (m_strString->capacity() > 0);
	return true;
#endif
}

char * String::GetData() const
{
#ifdef C_STRING
	return m_szString;
#else
	// TODO: Better way?
	return (char *)m_strString->data();
#endif
}
