//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CBitStream.h
// Project: Shared
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#pragma once

#include <StdInc.h>

class CBitStream : public CBitStreamInterface
{
private:
	CNetBitStreamInterface * m_pBitStream;

public:
	CBitStream();
	CBitStream(const unsigned int initialBytesToAllocate);
	CBitStream(unsigned char* _data, const unsigned int lengthInBytes, bool _copyData);
	~CBitStream();

	// Return the BitStream.
	CNetBitStreamInterface * GetBitStream();

	// Reset the BitStream for reuse.
	void                     Reset(void);

	// Write any integral type to the BitStream.
	void                     Write(const bool &inVar);
	void                     Write(const char &inVar);
	void                     Write(const unsigned char &inVar);
	void                     Write(const short &inVar);
	void                     Write(const unsigned short &inVar);
	void                     Write(const int &inVar);
	void                     Write(const unsigned int &inVar);
	void                     Write(const long &inVar);
	void                     Write(const unsigned long &inVar);
	void                     Write(const float &inVar);
	void                     Write(const double &inVar);

	// Write any integral type compressed to the BitStream.
	void                     WriteCompressed(const bool &inVar);
	void                     WriteCompressed(const char &inVar);
	void                     WriteCompressed(const unsigned char &inVar);
	void                     WriteCompressed(const short &inVar);
	void                     WriteCompressed(const unsigned short &inVar);
	void                     WriteCompressed(const int &inVar);
	void                     WriteCompressed(const unsigned int &inVar);
	void                     WriteCompressed(const long &inVar);
	void                     WriteCompressed(const unsigned long &inVar);
	void                     WriteCompressed(const float &inVar);
	void                     WriteCompressed(const double &inVar);

	// Read any integral type from the BitStream.
	bool                     Read(bool &outVar);
	bool                     Read(char &outVar);
	bool                     Read(unsigned char &outVar);
	bool                     Read(short &outVar);
	bool                     Read(unsigned short &outVar);
	bool                     Read(int &outVar);
	bool                     Read(unsigned int &outVar);
	bool                     Read(long &outVar);
	bool                     Read(unsigned long &outVar);
	bool                     Read(float &outVar);
	bool                     Read(double &outVar);

	// Read any compressed integral type from the BitStream.
	bool                     ReadCompressed(bool &outVar);
	bool                     ReadCompressed(char &outVar);
	bool                     ReadCompressed(unsigned char &outVar);
	bool                     ReadCompressed(short &outVar);
	bool                     ReadCompressed(unsigned short &outVar);
	bool                     ReadCompressed(int &outVar);
	bool                     ReadCompressed(unsigned int &outVar);
	bool                     ReadCompressed(long &outVar);
	bool                     ReadCompressed(unsigned long &outVar);
	bool                     ReadCompressed(float &outVar);
	bool                     ReadCompressed(double &outVar);

	// Write an array or casted stream or raw data to the BitStream.
	void                     Write(const char * inputByteArray, const unsigned int numberOfBytes);

	// Read an array or casted stream or raw data from the BitStream.
	bool                     Read(char * outputByteArray, const unsigned int numberOfBytes);

	// TODO: Write/Read compressed array

	// Write a 0 to the BitStream.
	void                     Write0(void);

	// Write a 1 to the BitStream
	void                     Write1(void);

	// Returns true if the next data read is a 1, false if it is a 0.
	bool                     ReadBit(void);

	// Returns a pointer to the data in the BitStream.
	unsigned char *          GetData();

	// Returns the number of bits used in the BitStream.
	unsigned int             GetNumberOfBitsUsed();

	// Returns the number of bytes used in the BitStream.
	unsigned int             GetNumberOfBytesUsed();

	// Returns the number of unread bits left in the BitStream.
	unsigned int             GetNumberOfUnreadBits();

	// TODO: Move the actual method to CNetBitStream
	// Write a String to the BitStream.
	void                     Write(const String &inString);

	// Read a String from the BitStream.
	bool                     Read(String &outString);
};
