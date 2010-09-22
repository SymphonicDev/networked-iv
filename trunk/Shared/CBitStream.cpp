//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CBitStream.cpp
// Project: Shared
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#include <StdInc.h>

extern CNetModule * g_pNetModule;

CBitStream::CBitStream()
{
	m_pBitStream = g_pNetModule->GetBitStreamInterface1();
}

CBitStream::CBitStream(const unsigned int initialBytesToAllocate)
{
	m_pBitStream = g_pNetModule->GetBitStreamInterface2(initialBytesToAllocate);
}

CBitStream::CBitStream(unsigned char* _data, const unsigned int lengthInBytes, bool _copyData)
{
	m_pBitStream = g_pNetModule->GetBitStreamInterface3(_data, lengthInBytes, _copyData);
}

CBitStream::~CBitStream()
{
	delete m_pBitStream;
}

CNetBitStreamInterface * CBitStream::GetBitStream()
{
	return m_pBitStream;
}

void CBitStream::Reset(void)
{
	m_pBitStream->Reset();
}

void CBitStream::Write(const bool &inVar)
{
	m_pBitStream->Write(inVar);
}

void CBitStream::Write(const char &inVar)
{
	m_pBitStream->Write(inVar);
}

void CBitStream::Write(const unsigned char &inVar)
{
	m_pBitStream->Write(inVar);
}

void CBitStream::Write(const short &inVar)
{
	m_pBitStream->Write(inVar);
}

void CBitStream::Write(const unsigned short &inVar)
{
	m_pBitStream->Write(inVar);
}

void CBitStream::Write(const int &inVar)
{
	m_pBitStream->Write(inVar);
}

void CBitStream::Write(const unsigned int &inVar)
{
	m_pBitStream->Write(inVar);
}

void CBitStream::Write(const long &inVar)
{
	m_pBitStream->Write(inVar);
}

void CBitStream::Write(const unsigned long &inVar)
{
	m_pBitStream->Write(inVar);
}

void CBitStream::Write(const float &inVar)
{
	m_pBitStream->Write(inVar);
}

void CBitStream::Write(const double &inVar)
{
	m_pBitStream->Write(inVar);
}

void CBitStream::WriteCompressed(const bool &inVar)
{
	m_pBitStream->WriteCompressed(inVar);
}

void CBitStream::WriteCompressed(const char &inVar)
{
	m_pBitStream->WriteCompressed(inVar);
}

void CBitStream::WriteCompressed(const unsigned char &inVar)
{
	m_pBitStream->WriteCompressed(inVar);
}

void CBitStream::WriteCompressed(const short &inVar)
{
	m_pBitStream->WriteCompressed(inVar);
}

void CBitStream::WriteCompressed(const unsigned short &inVar)
{
	m_pBitStream->WriteCompressed(inVar);
}

void CBitStream::WriteCompressed(const int &inVar)
{
	m_pBitStream->WriteCompressed(inVar);
}

void CBitStream::WriteCompressed(const unsigned int &inVar)
{
	m_pBitStream->WriteCompressed(inVar);
}

void CBitStream::WriteCompressed(const long &inVar)
{
	m_pBitStream->WriteCompressed(inVar);
}

void CBitStream::WriteCompressed(const unsigned long &inVar)
{
	m_pBitStream->WriteCompressed(inVar);
}

void CBitStream::WriteCompressed(const float &inVar)
{
	m_pBitStream->WriteCompressed(inVar);
}

void CBitStream::WriteCompressed(const double &inVar)
{
	m_pBitStream->WriteCompressed(inVar);
}

bool CBitStream::Read(bool &outVar)
{
	return m_pBitStream->Read(outVar);
}

bool CBitStream::Read(char &outVar)
{
	return m_pBitStream->Read(outVar);
}

bool CBitStream::Read(unsigned char &outVar)
{
	return m_pBitStream->Read(outVar);
}

bool CBitStream::Read(short &outVar)
{
	return m_pBitStream->Read(outVar);
}

bool CBitStream::Read(unsigned short &outVar)
{
	return m_pBitStream->Read(outVar);
}

bool CBitStream::Read(int &outVar)
{
	return m_pBitStream->Read(outVar);
}

bool CBitStream::Read(unsigned int &outVar)
{
	return m_pBitStream->Read(outVar);
}

bool CBitStream::Read(long &outVar)
{
	return m_pBitStream->Read(outVar);
}

bool CBitStream::Read(unsigned long &outVar)
{
	return m_pBitStream->Read(outVar);
}

bool CBitStream::Read(float &outVar)
{
	return m_pBitStream->Read(outVar);
}

bool CBitStream::Read(double &outVar)
{
	return m_pBitStream->Read(outVar);
}

bool CBitStream::ReadCompressed(bool &outVar)
{
	return m_pBitStream->ReadCompressed(outVar);
}

bool CBitStream::ReadCompressed(char &outVar)
{
	return m_pBitStream->ReadCompressed(outVar);
}

bool CBitStream::ReadCompressed(unsigned char &outVar)
{
	return m_pBitStream->ReadCompressed(outVar);
}

bool CBitStream::ReadCompressed(short &outVar)
{
	return m_pBitStream->ReadCompressed(outVar);
}

bool CBitStream::ReadCompressed(unsigned short &outVar)
{
	return m_pBitStream->ReadCompressed(outVar);
}

bool CBitStream::ReadCompressed(int &outVar)
{
	return m_pBitStream->ReadCompressed(outVar);
}

bool CBitStream::ReadCompressed(unsigned int &outVar)
{
	return m_pBitStream->ReadCompressed(outVar);
}

bool CBitStream::ReadCompressed(long &outVar)
{
	return m_pBitStream->ReadCompressed(outVar);
}

bool CBitStream::ReadCompressed(unsigned long &outVar)
{
	return m_pBitStream->ReadCompressed(outVar);
}

bool CBitStream::ReadCompressed(float &outVar)
{
	return m_pBitStream->ReadCompressed(outVar);
}

bool CBitStream::ReadCompressed(double &outVar)
{
	return m_pBitStream->ReadCompressed(outVar);
}

void CBitStream::Write(const char * inputByteArray, const unsigned int numberOfBytes)
{
	m_pBitStream->Write(inputByteArray, numberOfBytes);
}

bool CBitStream::Read(char * outputByteArray, const unsigned int numberOfBytes)
{
	return m_pBitStream->Read(outputByteArray, numberOfBytes);
}

void CBitStream::Write0(void)
{
	m_pBitStream->Write0();
}

void CBitStream::Write1(void)
{
	m_pBitStream->Write1();
}

bool CBitStream::ReadBit(void)
{
	return m_pBitStream->ReadBit();
}

unsigned char * CBitStream::GetData()
{
	return m_pBitStream->GetData();
}

unsigned int CBitStream::GetNumberOfBitsUsed()
{
	return m_pBitStream->GetNumberOfBitsUsed();
}

unsigned int CBitStream::GetNumberOfBytesUsed()
{
	return m_pBitStream->GetNumberOfBytesUsed();
}

unsigned int CBitStream::GetNumberOfUnreadBits()
{
	return m_pBitStream->GetNumberOfUnreadBits();
}

void CBitStream::Write(const String &inString)
{
	m_pBitStream->Write(inString);
}

bool CBitStream::Read(String &outString)
{
	return m_pBitStream->Read(outString);
}
