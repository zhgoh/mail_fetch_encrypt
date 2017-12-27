//
// Created by zgoh on 26/12/17.
//

#include "MyCrypt.h"
#include <openssl/evp.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>

/* Please choose an encryption mode in the following defines value.
   Only 1 encryption mode is allow at a time. Blowfish CBC mode is
   the default encryption in this file.
 */

// BlowFish
#define MY_CIPHER_MODE EVP_bf_cbc()     // Blowfish CBC mode
//#define MY_CIPHER_MODE EVP_bf_ecb()   // Blowfish ECB mode

// DES
//#define MY_CIPHER_MODE EVP_des_cbc()    // DES CBC mode
//#define MY_CIPHER_MODE EVP_des_ecb()    // DES ECB mode
//#define MY_CIPHER_MODE EVP_des_ede()    // DES EDE mode
//#define MY_CIPHER_MODE EVP_des_ede3()   // DES EDE3 mode

// RC2
//#define MY_CIPHER_MODE EVP_rc2_cbc()    // RC2 CBC mode
//#define MY_CIPHER_MODE EVP_rc2_ecb()    // RC2 ECB mode

// RC4
//#define MY_CIPHER_MODE EVP_rc4()      // RC4 mode
//#define MY_CIPHER_MODE EVP_rc4_40()   // RC4 40 mode

// TODO: Don't store keys here
static const unsigned char key[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
static const unsigned char iv[] = {1,2,3,4,5,6,7,8};


class CipherText
{
public:
    CipherText(const char *str, size_t len) :
            ptr(new char[len]), length(int(len))
    {
        memcpy(ptr, str, len);
    }
    
    ~CipherText()
    {
        delete[] ptr;
    }
    
    char *str()
    {
        return ptr;
    }
    
    int &len()
    {
        return length;
    }
    
private:
    char *ptr;
    int length;
};

void EncryptFile(const char *plainMessage, const char *outputFile)
{
    CipherText encrypted(plainMessage, strlen(plainMessage));
    if (Encrypt(plainMessage, encrypted.str(), &encrypted.len()))
    {
        FILE *file = fopen(outputFile, "wb");
        if (file)
        {
            fwrite(encrypted.str(), sizeof(char), encrypted.len(), file);
        }
        fclose(file);
    }
}

void DecryptFile(const char *inputFile, std::string &plainMessage)
{
    FILE *file = fopen(inputFile, "rb");
    if (file)
    {
        // obtain file size:
        fseek (file , 0 , SEEK_END);
        long lSize = ftell (file);
        rewind (file);
    
        // allocate memory to contain the whole file:
        char *buffer = new char[lSize];
        size_t result = fread (buffer, 1, size_t(lSize), file);
        
        CipherText decrypted(buffer, size_t(lSize));
        if (Decrypt(buffer, int(lSize), decrypted.str()))
        {
            plainMessage = decrypted.str();
            //std::cout << plainMessage << std::endl;
        }
    }
}


bool Encrypt(const char *plainMessage, char *cipherText, int *cipherLen)
{
    int bufLen, tmpLen;
    
    EVP_CIPHER_CTX *ctx = nullptr;
    ctx = EVP_CIPHER_CTX_new();
    if (!ctx)
        return false;
    
    EVP_EncryptInit_ex(ctx, MY_CIPHER_MODE, nullptr, key, iv);
    
    if(!EVP_EncryptUpdate(ctx, (unsigned char *)cipherText, &bufLen, (unsigned char *)plainMessage, strlen(plainMessage)))
    {
        return false;
    }
    
    if(!EVP_EncryptFinal_ex(ctx, (unsigned char *)cipherText + bufLen, &tmpLen))
    {
        return false;
    }
    
    bufLen += tmpLen;
    *cipherLen = bufLen;
    EVP_CIPHER_CTX_cleanup(ctx);
    
    return true;
}

bool Decrypt(const char *cipherText, int cipherLen, char *plainText)
{
    int bufLen, tmpLen;
    
    EVP_CIPHER_CTX *ctx = nullptr;
    ctx = EVP_CIPHER_CTX_new();
    if (!ctx)
        return false;
    
    EVP_DecryptInit_ex(ctx, MY_CIPHER_MODE, nullptr, key, iv);
    
    if(!EVP_DecryptUpdate(ctx, (unsigned char *)plainText, &bufLen, (const unsigned char *)cipherText, cipherLen))
    {
        return false;
    }
    
    if(!EVP_DecryptFinal_ex(ctx, (unsigned char *)plainText + bufLen, &tmpLen))
    {
        return false;
    }
    
    int decryptedLength = bufLen + tmpLen;
    plainText[decryptedLength] = '\0';
    EVP_CIPHER_CTX_cleanup(ctx);
    
    return true;
}