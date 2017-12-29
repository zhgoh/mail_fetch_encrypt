//
// Created by zgoh on 26/12/17.
//

#ifndef MAILRETRIEVE_CRYPT_H
#define MAILRETRIEVE_CRYPT_H

#include <string>
#include <openssl/evp.h>

class File
{
public:
    File(const char *file, const char *mode);
    ~File();
    
    bool IsOpen() const;
    FILE *Get() const;

private:
    FILE *file;
};

class Buffer
{
public:
    Buffer(int sz);
    char *Get() const;
    ~Buffer();
    
private:
    char *ptr;
};

class CipherText
{
public:
    CipherText(const unsigned char *str, int len);
    ~CipherText();
    
    unsigned char *str();
    const unsigned char *str() const;
    int *len();
    size_t size() const;

private:
    unsigned char *ptr;
    int length;
};

class PKey
{
public:
    PKey(const File &file);
    ~PKey();

private:
    EVP_PKEY *key;
};

class EKey
{
public:
    EKey(EVP_PKEY *pKey, int len = 0);
    ~EKey();
    
    unsigned char **GetPtr();
    unsigned char *Get();
    
    int *LengthPtr();
    int Length() const;
    size_t Size() const;
    uint32_t USize() const;

private:
    unsigned char *key;
    int keyLength;
};

void EncryptInit();
void EncryptFile(const char *plainMessage, const char *outputFile);
void DecryptFile(const char *inputFileName, const char *outputFileName);

#endif //MAILRETRIEVE_CRYPT_H
