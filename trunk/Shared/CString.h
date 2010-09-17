//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CString.h
// Project: Shared
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#pragma once

#include <StdInc.h>

class String
{
private:
	std::string m_strString;
	size_t m_sLimit;

	void          Init();

public:
	String();
	String(const char * szFormat, ...);
	~String();

	operator const char * () { return Get(); }
	String& operator = (const String strString);
	String& operator = (const char * szString);
	String& operator += (const char * szString);
	String& operator += (const unsigned char ucChar);
	unsigned char operator [] (size_t sOffset);
	bool operator == (const char * szString);
	bool operator != (const char * szString);
	bool operator > (const char * szString);
	bool operator >= (const char * szString);
	bool operator < (const char * szString);
	bool operator <= (const char * szString);

	// Return the non editable string
	const char *  Get() const;
	const char *  C_String() const;

	// Set the string
	void          Set(const char * szString);

	// Format the string
	void          Format(const char * szFormat, ...);

	// Return the string length
	size_t        GetLength() const;

	// Return true if the string length is 0,
	// false if not
	bool          IsEmpty() const;

	// Convert all a-z chars in the string to
	// lowercase
	void          ToLower();

	// Return true if all a-z chars in the string
	// are lowercase, false if not
	bool          IsLower();

	// Convert all a-z chars in the string to
	// uppercase
	void          ToUpper();

	// Return true if all a-z chars in the string
	// are uppercase, false if not
	bool          IsUpper();

	// Truncate (null terminate) the string at sOffset
	void          Truncate(size_t sOffset);

	// Erase sCount amount of bytes at sOffset in the
	// string
	void          Erase(size_t sOffset, size_t sCount);

	// Clear the string contents and free the allocated
	// memory
	void          Clear();
	
	// Compare the string with szString (case sensitive)
	int           Compare(const char * szString);

	// Compare the string with szString (case insensitive)
	int           ICompare(const char * szString);

	// Return the value of the string as an integer
	int           ToInteger();

	// Return the value of the string as a boolean
	bool          ToBoolean();

	// Set the char at sOffset to cChar
	void          SetChar(size_t sOffset, unsigned char cChar);

	// Return the char at sOffset
	unsigned char GetChar(size_t sOffset);


	const char *  SubStr(size_t sOffset, size_t sCount) const;

	// Append szString to the string
	void          Append(const char * szString);

	// Append ucChar to the string
	void          Append(const unsigned char ucChar);

	// Insert szString into the string at sOffset
	void          Insert(size_t sOffset, const char * szString);

	// Attempt to find szString in the string, 
	// if found return its index, if not return -1
	size_t        Find(const char * szString) const;

	// Return true if the string contains szString, 
	// false if not
	bool          Contains(const char * szString) const;

	// Starting at the end, attempt to find szString 
	// in the string, if found return its index, if 
	// not return -1
	size_t        ReverseFind(const char * szString) const;

	// Set the string limit
	bool          SetLimit(size_t sLimit);

	// Return the string limit
	size_t        GetLimit();

	// Truncate (null terminate) if the string is
	// longer than the set limit
	bool          LimitTruncate();

	// Ensure we have sSize amount of memory
	// allocated
	void          Allocate(size_t sSize);

	// Free any allocated memory
	void          Free();

	// Return the amount of memory allocated
	size_t        GetSize() const;

	// Return true if we have any memory allocated,
	// false if not
	bool          IsAllocated() const;

	// Return the data string
	char *        GetData() const;
};
