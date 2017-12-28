//
// Created by zgoh on 26/12/17.
//

#ifndef MAILRETRIEVE_CRYPT_H
#define MAILRETRIEVE_CRYPT_H

#include <string>

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
    Buffer(size_t sz);
    char *Get() const;
    ~Buffer();
    
private:
    char *ptr;
};

class CipherText
{
public:
    CipherText(const char *str, int len);
    ~CipherText();
    char *str();
    int &len();
    size_t size() const;

private:
    char *ptr;
    int length;
};

void EncryptInit();
void EncryptFile(const char *plainMessage, const char *outputFile);
void DecryptFile(const char *inputFile, std::string &plainMessage);
bool Encrypt(const char *plainMessage, char *cipherText, int *cipherLen);
bool Decrypt(const char *cipherText, int cipherLen, char *plainText);

#endif //MAILRETRIEVE_CRYPT_H
