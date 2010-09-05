#include <StdInc.h>

#if 0
// Default values
// Can be changed at runtime
#define TEA_DELTA_VALUE 0x9E3779B9
// Can be changed at runtime
#define TEA_ROUND_COUNT 32
// Cannot be changed at runtime
#define TEA_KEY_SIZE 16
// Cannot be changed at all
#define TEA_BLOCK_COUNT 2

// Encryption rounds
#define TEA_ROUND(vec, key0, key1, sum) ((vec << 4) + key0) ^ (vec + sum) ^ ((vec >> 5) + key1)
#define XTEA_ROUND(vec, key, sum) (((vec << 4) ^ (vec >> 5)) + vec) ^ (sum + key)
#define XXTEA_ROUND(vec0, vec1, key, sum) ((vec0 >> 5 ^ vec1 << 2) + (vec1 >> 3 ^ vec0 << 4)) ^ ((sum ^ vec1) + (key ^ vec0))

// Encryption type
//#define USE_TEA
//#define USE_XTEA
#define USE_XXTEA

class TEAEncryptor
{
private:
	// Delta value
	unsigned int m_uiDelta;

	// Encryption key set
	bool m_bKeySet;

	// Encryption key
	BYTE m_byteKey[TEA_KEY_SIZE];

	// Number of internal encryption rounds
	unsigned int m_uiInternalRounds;

public:
	// Constructor
	TEAEncryptor()
	{
		m_uiDelta = TEA_DELTA_VALUE;
		m_bKeySet = false;
		memset(m_byteKey, 0, TEA_KEY_SIZE);
		m_uiInternalRounds = TEA_ROUND_COUNT;
	}

	// Destructor
	~TEAEncryptor()
	{

	}

	// Set the encryption key
	void         SetKey(BYTE * byteKey)
	{
		for(unsigned int i = 0; i < TEA_KEY_SIZE; i++)
			m_byteKey[i] = byteKey[i];

		m_bKeySet = true;
	}

	// Get the encryption key
	BYTE *       GetKey()
	{
		if(m_bKeySet)
			return m_byteKey;

		return NULL;
	}

	void         SetInternalRounds(unsigned int uiInternalRounds)
	{
		m_uiInternalRounds = uiInternalRounds;
	}

	unsigned int GetInternalRounds()
	{
		return m_uiInternalRounds;
	}

	bool         CanEncrypt()
	{
		return (m_bKeySet && m_uiInternalRounds);
	}

	// Encrypt a block of data
	bool         EncryptBlock(unsigned int * uiVector)
	{
		if(CanEncrypt())
		{
			unsigned int uiSum = 0;
			unsigned int * uiKey = (unsigned int *)m_byteKey;
#ifdef USE_XXTEA
			// XXTEA
			unsigned e;
#endif

			for(unsigned int i = 0; i < m_uiInternalRounds; i++)
			{
#if defined(USE_TEA)
				// Standard TEA
				uiSum += m_uiDelta;
				uiVector[0] += TEA_ROUND(uiVector[1], uiKey[0], uiKey[1], uiSum);
				uiVector[1] += TEA_ROUND(uiVector[0], uiKey[2], uiKey[3], uiSum);
#elif defined(USE_XTEA)
				// XTEA
				uiVector[0] += XTEA_ROUND(uiVector[1], uiKey[uiSum & 3], uiSum);
				uiSum += m_uiDelta;
				uiVector[1] += XTEA_ROUND(uiVector[0], uiKey[(uiSum >> 11) & 3], uiSum);
#else
				// XXTEA
				uiSum += m_uiDelta;
				e = ((uiSum >> 2) & 3);

				uiVector[0] += XXTEA_ROUND(uiVector[1], uiVector[1], uiKey[e], uiSum);
				uiVector[1] += XXTEA_ROUND(uiVector[0], uiVector[0], uiKey[e], uiSum);
#endif
			}

			return true;
		}

		return false;
	}

	// Decrypt a block of data
	bool         DecryptBlock(unsigned int * uiVector)
	{
		if(CanEncrypt())
		{
			unsigned int uiSum = (TEA_DELTA_VALUE * m_uiInternalRounds);
			unsigned int * uiKey = (unsigned int *)m_byteKey;
#ifdef USE_XXTEA
			// XXTEA
			unsigned e;
#endif

			for(unsigned int i = 0; i < m_uiInternalRounds; i++)
			{
#if defined(USE_TEA)
				// Standard TEA
				uiVector[1] -= TEA_ROUND(uiVector[0], uiKey[2], uiKey[3], uiSum);
				uiVector[0] -= TEA_ROUND(uiVector[1], uiKey[0], uiKey[1], uiSum);
				uiSum -= m_uiDelta;
#elif defined(USE_XTEA)
				// XTEA
				uiVector[1] -= XTEA_ROUND(uiVector[0], uiKey[(uiSum >> 11) & 3], uiSum);
				uiSum -= m_uiDelta;
				uiVector[0] -= XTEA_ROUND(uiVector[1], uiKey[uiSum & 3], uiSum);
#else
				// XXTEA
				e = (uiSum >> 2) & 3;

				uiVector[1] -= XXTEA_ROUND(uiVector[0], uiVector[0], uiKey[e], uiSum);
				uiVector[0] -= XXTEA_ROUND(uiVector[1], uiVector[1], uiKey[e], uiSum);

				uiSum -= m_uiDelta;
#endif
			}

			return true;
		}

		return false;
	}

	void         ProcessExtraBytes(BYTE * byteData, unsigned int uiSize, bool bEncrypt)
	{
		// Is the size not a multiple of 4?
		if((uiSize & 3))
		{
			// Create a pad using the remaining bytes
			BYTE bytePad[sizeof(unsigned int) * TEA_BLOCK_COUNT];
			unsigned int uiBlockCount = (uiSize / 4);
			unsigned int uiBytesEncrypted = (4 * uiBlockCount);
			unsigned int uiBytesLeft = (uiSize - (uiBlockCount * 4));
			printf("BlockCount(%d) BytesEncrypted(%d) BytesLeft(%d)\n", uiBlockCount, uiBytesEncrypted, uiBytesLeft);

			// Reset the pad data
			memset(bytePad, 0, sizeof(bytePad));

			// Add the remaining bytes to the pad data
			for(unsigned int i = 0; i < uiBytesLeft; i++)
			{
				printf("Get(DataByte(%d) PadByte(%d))\n", (uiBytesEncrypted + i), i);
				bytePad[i] = byteData[uiBytesEncrypted + i];
			}

			// Encrypt/decrypt the padding
			unsigned int * uiVector = (unsigned int *)bytePad;
			if(bEncrypt)
			{
				EncryptBlock(uiVector);
			}
			else
			{
				DecryptBlock(uiVector);
			}

			// Replace the original data with the encrypted data
			for(unsigned int i = 0; i < uiBytesLeft; i++)
			{
				printf("Set(DataByte(%d) PadByte(%d))\n", (uiBytesEncrypted + i), i);
				byteData[uiBytesEncrypted + i] = bytePad[i];
			}
		}
	}

	// Encrypt an array of data
	bool         Encrypt(BYTE * byteData, unsigned int uiSize)
	{
		if(CanEncrypt())
		{
			unsigned int * uiVector = (unsigned int *)byteData;
			unsigned int uiBlockCount = (uiSize / 4);

			for(unsigned int i = 0; i < uiBlockCount; i += TEA_BLOCK_COUNT)
			{
				EncryptBlock(uiVector + i);
			}

			//ProcessExtraBytes(byteData, uiSize, true);
			return true;
		}

		return false;
	}

	// Decrypt an array of data
	bool         Decrypt(BYTE * byteData, unsigned int uiSize)
	{
		if(CanEncrypt())
		{
			unsigned int * uiVector = (unsigned int *)byteData;
			unsigned int uiBlockCount = (uiSize / 4);

			for(unsigned int i = 0; i < uiBlockCount; i += TEA_BLOCK_COUNT)
			{
				DecryptBlock(uiVector + i);
			}

			//ProcessExtraBytes(byteData, uiSize, false);
			return true;
		}

		return false;
	}
};

unsigned int GenerateKey(unsigned short usPort)
{
	unsigned int uiFinalKey[4];
	unsigned int uiKey = usPort;
	uiKey *= 8;
	uiFinalKey[3] = uiKey;
	uiKey ^= 2;
	uiFinalKey[0] = uiKey;
	uiKey *= 8;
	uiFinalKey[2] = uiKey;
	uiKey ^= 2;
	uiFinalKey[1] = uiKey;
	printf("final key is (%d, %d, %d, %d)\n", uiFinalKey[0], uiFinalKey[1], uiFinalKey[2], uiFinalKey[3]);
	return uiKey;
}

/*
/*
	BYTE byteKey[TEA_KEY_SIZE] = { 0x95, 0x92, 0x13, 0x55, 0x85, 0x94, 0x27, 0x13, 0x84, 0x93, 0x12, 0x04, 0x92, 0x31, 0x93, 0x53 };
	TEAEncryptor encryptor;
	encryptor.SetKey(byteKey);

	char szArray[39];
	memset(szArray, 0, sizeof(szArray));
	sprintf(szArray, "Hello World");

	//DWORD dwStart = GetTickCount();
	//for(unsigned int i = 0; i < 32000; i++)
	//{		
		printf("%s\n", szArray);
		encryptor.Encrypt((BYTE *)szArray, sizeof(szArray));
		printf("%s\n", szArray);
		encryptor.Decrypt((BYTE *)szArray, sizeof(szArray));
		printf("%s\n", szArray);
	//}
	//DWORD dwEnd = GetTickCount();
	//printf("Took %dms\n", (dwEnd - dwStart));*/
*/
#endif