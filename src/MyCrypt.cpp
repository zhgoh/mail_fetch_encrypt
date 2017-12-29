//
// Created by zgoh on 26/12/17.
//

#include "MyCrypt.h"

#include <glog/logging.h>
#include <openssl/pem.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include <algorithm>

#include <arpa/inet.h> /* For htonl() */

static EVP_PKEY *PUB_KEY = nullptr;
static EVP_PKEY *PRI_KEY = nullptr;

int Envelope_Seal(const unsigned char *plainMessage, int messageLen, File &outputFile);
int Envelope_Open(File &inputFile, File &outputFile);

void EncryptInit()
{
    File pub_keyFile("rsa_pubkey.pem", "rb");
    if (pub_keyFile.IsOpen())
    {
        PUB_KEY = PEM_read_PUBKEY(pub_keyFile.Get(), nullptr, nullptr, nullptr);
        if (!PUB_KEY)
        {
            LOG(ERROR) << "Load Public Key Failed" << std::endl;
        }
        else
        {
            std::cout << "Loaded Public Key successfully" << std::endl;
        }
    }
    
    File pri_keyFile("rsa_privkey.pem", "rb");
    if (pri_keyFile.IsOpen())
    {
        PRI_KEY = PEM_read_PrivateKey(pri_keyFile.Get(), nullptr, nullptr, nullptr);
        if (!PRI_KEY)
        {
            LOG(ERROR) << "Load Private Key Failed" << std::endl;
        }
        else
        {
            std::cout << "Loaded Private Key successfully" << std::endl;
        }
    }
}

void EncryptFile(const char *plainMessage, const char *outputFile)
{
    auto len = static_cast<int>(strlen(plainMessage));
    File file(outputFile, "wb");
    if (file.IsOpen())
    {
        if (!Envelope_Seal(reinterpret_cast<const unsigned char *>(plainMessage), len, file))
        {
            std::cout << "EVP_Seal Success!\n";
            return;
        }
    }
    
    LOG(ERROR) << "EVP_Seal Failed! \n";
}

void DecryptFile(const char *inputFileName, const char *outputFileName)
{
    File input(inputFileName, "rb");
    if (input.IsOpen())
    {
        File output(outputFileName, "wb");
        if (output.IsOpen())
        {
            if (!Envelope_Open(input, output))
            {
                std::cout << "EVP_Open Success!\n";
                return;
            }
        }
    }
    
    LOG(ERROR) << "EVP_Open Failed! \n";
}

int Envelope_Seal(const unsigned char *plainMessage, int messageLen, File &outputFile)
{
    EVP_CIPHER_CTX *ctx = nullptr;
    EKey encryptedKey(PUB_KEY);
    
    uint32_t encryptedKeyLen_n;
    unsigned char iv[EVP_MAX_IV_LENGTH];
    
    ctx = EVP_CIPHER_CTX_new();
    if (!ctx)
    {
        fprintf(stderr, "EVP_CIPHER_CTX_new: failed.\n");
    }
    
    if (!EVP_SealInit(ctx, EVP_aes_256_cbc(), encryptedKey.GetPtr(), encryptedKey.LengthPtr(), iv, &PUB_KEY, 1))
    {
        fprintf(stderr, "EVP_SealInit: failed.\n");
        return 3;
    }
    
    /* First we write out the encrypted key length, then the encrypted key,
     * then the iv (the IV length is fixed by the cipher we have chosen).
     */
    
    encryptedKeyLen_n = htonl(encryptedKey.USize());
    if (fwrite(&encryptedKeyLen_n, sizeof encryptedKeyLen_n, 1, outputFile.Get()) != 1)
    {
        perror("output file");
        return 5;
    }
    
    if (fwrite(encryptedKey.Get(), encryptedKey.Size(), 1, outputFile.Get()) != 1)
    {
        perror("output file");
        return 5;
    }
    
    if (fwrite(iv, static_cast<size_t>(EVP_CIPHER_iv_length(EVP_aes_256_cbc())), 1, outputFile.Get()) != 1)
    {
        perror("output file");
        return 5;
    }
    
    /* Now we process the input file and write the encrypted data to the
     * output file. */
    CipherText text(plainMessage, messageLen);
    if (!EVP_SealUpdate(ctx, text.str(), text.len(), plainMessage, messageLen))
    {
        fprintf(stderr, "EVP_SealUpdate: failed.\n");
        return 3;
    }
    
    if (fwrite(text.str(), text.size(), 1, outputFile.Get()) != 1)
    {
        perror("output file");
        return 5;
    }

    
    if (!EVP_SealFinal(ctx, text.str(), text.len()))
    {
        fprintf(stderr, "EVP_SealFinal: failed.\n");
        return 3;
    }
    
    if (fwrite(text.str(), text.size(), 1, outputFile.Get()) != 1)
    {
        perror("output file");
        return 5;
    }
    
    return 0;
}

int Envelope_Open(File &inputFile, File &outputFile)
{
    size_t len;
    int len_out;
    uint32_t encryptedKeyLen_n;
    
    unsigned char iv[EVP_MAX_IV_LENGTH];
    unsigned char buffer[4096];
    unsigned char buffer_out[4096 + EVP_MAX_IV_LENGTH];
    
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx)
    {
        return 1;
    }
    
    /* First need to fetch the encrypted key length, encrypted key and IV */
    if (fread(&encryptedKeyLen_n, sizeof encryptedKeyLen_n, 1, inputFile.Get()) != 1)
    {
        perror("input file");
        return 4;
    }
    
    EKey encryptionKey(PRI_KEY, ntohl(encryptedKeyLen_n));
    if (encryptionKey.Length() > EVP_PKEY_size(PRI_KEY))
    {
        fprintf(stderr, "Bad encrypted key length (%u > %d)\n", encryptionKey.Length(), EVP_PKEY_size(PRI_KEY));
        return 4;
    }
    
    if (fread(encryptionKey.Get(), encryptionKey.Size(), 1, inputFile.Get()) != 1)
    {
        perror("input file");
        return 4;
    }
    
    if (fread(iv, static_cast<size_t>(EVP_CIPHER_iv_length(EVP_aes_256_cbc())), 1, inputFile.Get()) != 1)
    {
        perror("input file");
        return 4;
    }
    
    if (!EVP_OpenInit(ctx, EVP_aes_256_cbc(), encryptionKey.Get(), encryptionKey.Length(), iv, PRI_KEY))
    {
        fprintf(stderr, "EVP_OpenInit: failed.\n");
        return 3;
    }
    
    while ((len = fread(buffer, 1, sizeof buffer, inputFile.Get())) > 0)
    {
        if (!EVP_OpenUpdate(ctx, buffer_out, &len_out, buffer, static_cast<int>(len)))
        {
            fprintf(stderr, "EVP_OpenUpdate: failed.\n");
            return 3;
        }
        
        if (fwrite(buffer_out, static_cast<size_t>(len_out), 1, outputFile.Get()) != 1)
        {
            perror("output file");
            return 5;
        }
    }
    
    if (!EVP_OpenFinal(ctx, buffer_out, &len_out))
    {
        fprintf(stderr, "EVP_SealFinal: failed.\n");
        return 3;
    }
    
    if (fwrite(buffer_out, static_cast<size_t>(len_out), 1, outputFile.Get()) != 1)
    {
        perror("output file");
        return 5;
    }
    
    return 0;
}

File::File(const char *file, const char *mode) :
        file(fopen(file, mode))
{
}

File::~File()
{
    fclose(file);
}

bool File::IsOpen() const
{
    return file != nullptr;
}

FILE *File::Get() const
{
    return file;
}

Buffer::Buffer(int sz):
        ptr(new char[sz])
{
}

char *Buffer::Get() const
{
    return ptr;
}

Buffer::~Buffer()
{
    delete[] ptr;
}

CipherText::CipherText(const unsigned char *str, int len) :
        ptr(new unsigned char[len]), length(len)
{
    std::copy(str, str + len, ptr);
}

CipherText::~CipherText()
{
    delete[] ptr;
}

unsigned char *CipherText::str()
{
    return ptr;
}

const unsigned char *CipherText::str() const
{
    return ptr;
}

int *CipherText::len()
{
    return &length;
}

size_t CipherText::size() const
{
    return static_cast<size_t>(length);
}

PKey::PKey(const File &file) :
        key(nullptr)
{
    if (file.IsOpen())
    {
        key = PEM_read_PUBKEY(file.Get(), nullptr, nullptr, nullptr);
    }
    
}

PKey::~PKey()
{
    EVP_PKEY_free(key);
}

EKey::EKey(EVP_PKEY *pKey, int len)
        : key(new unsigned char[EVP_PKEY_size(pKey)]), keyLength(len)
{
}

EKey::~EKey()
{
    free(key);
}

unsigned char **EKey::GetPtr()
{
    return &key;
}

unsigned char *EKey::Get()
{
    return key;
}

int *EKey::LengthPtr()
{
    return &keyLength;
}

int EKey::Length() const
{
    return keyLength;
}

size_t EKey::Size() const
{
    return static_cast<size_t>(keyLength);
}

uint32_t EKey::USize() const
{
    return static_cast<uint32_t>(keyLength);
}