//
// Created by zgoh on 26/12/17.
//

#include "MyCrypt.h"

#include <glog/logging.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include <algorithm>

bool Envelope_Seal(const unsigned char *plain_text, int plain_text_len,
                   unsigned char **encrypted_key, int *encrypted_key_len,
                   unsigned  char *iv,
                   unsigned char *cipher_text, int *cipher_text_len);

bool Envelope_Open(unsigned char *cipher_text, int cipher_text_len,
                   unsigned char *encrypted_key, int encrypted_key_len, unsigned char *iv,
                   unsigned char *plain_text, int *plain_text_len);

static EVP_PKEY *PUB_KEY = nullptr;
static EVP_PKEY *PRI_KEY = nullptr;
static unsigned char IV[] = "45213456a23fdg";

static unsigned char encryptedKey[512];
static unsigned char *eKeys = encryptedKey;
static int encryptedKeyLen = 0;

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
    

    CipherText encrypted(plainMessage, len);
    if (Envelope_Seal(reinterpret_cast<const unsigned char *>(plainMessage), len,
                      &eKeys, &encryptedKeyLen,
                      IV,
                      reinterpret_cast<unsigned char *>(encrypted.str()), &encrypted.len()))
    {
        File ec("ec", "wb");
        if (ec.IsOpen())
        {
            //PEM_write(ec.Get(), "EncryptedKey", "", encryptedKey, encryptedKeyLen);
        }
        
        File file(outputFile, "wb");
        if (file.IsOpen())
        {
            fwrite(file.Get(), sizeof(char), encrypted.size(), file.Get());
        }
    }
    
}

void DecryptFile(const char *inputFile, std::string &plainMessage)
{
    File file(inputFile, "rb");
    if (file.IsOpen())
    {
        // obtain file size:
        fseek (file.Get() , 0 , SEEK_END);
        long lSize = ftell (file.Get());
        rewind (file.Get());
    
        // allocate memory to contain the whole file:
        Buffer buffer(static_cast<size_t>(lSize));
        fread (buffer.Get(), 1, size_t(lSize), file.Get());

        CipherText decrypted(buffer.Get(), static_cast<int>(lSize));
        if (Envelope_Open(reinterpret_cast<unsigned char *>(buffer.Get()), static_cast<int>(lSize),
                          encryptedKey, encryptedKeyLen, IV,
                          reinterpret_cast<unsigned char *>(decrypted.str()), &decrypted.len()))
        {
            plainMessage = decrypted.str();
            //std::cout << plainMessage << std::endl;
        }
    }
}


void handleErrors()
{
    LOG(ERROR) << "Error in OpenSSL functionality\n";
}

// https://wiki.openssl.org/index.php/EVP_Asymmetric_Encryption_and_Decryption_of_an_Envelope
bool Envelope_Seal(const unsigned char *plain_text, int plain_text_len,
                  unsigned char **encrypted_key, int *encrypted_key_len,
                  unsigned char *iv,
                  unsigned char *cipher_text, int *cipher_text_len)
{
    int len = 0;
    
    /* Create and initialise the context */
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if(!ctx)
        handleErrors();
    
    /* Initialise the envelope seal operation. This operation generates
     * a key for the provided cipher, and then encrypts that key a number
     * of times (one for each public key provided in the pub_key array). In
     * this example the array size is just one. This operation also
     * generates an IV and places it in iv. */
    if(EVP_SealInit(ctx, EVP_aes_256_cbc(), encrypted_key, encrypted_key_len, iv, &PUB_KEY, 1) != 1)
        handleErrors();
    
    /* Provide the message to be encrypted, and obtain the encrypted output.
     * EVP_SealUpdate can be called multiple times if necessary
     */
    if(EVP_SealUpdate(ctx, cipher_text, cipher_text_len, plain_text, plain_text_len) != 1)
        handleErrors();
    *cipher_text_len = len;
    
    /* Finalise the encryption. Further cipher_text bytes may be written at
     * this stage.
     */
    if(EVP_SealFinal(ctx, cipher_text + len, &len) != 1)
        handleErrors();
    *cipher_text_len += len;
    
    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);
    
    return true;
}

bool Envelope_Open(unsigned char *cipher_text, int cipher_text_len,
                  unsigned char *encrypted_key, int encrypted_key_len, unsigned char *iv,
                  unsigned char *plain_text, int *plain_text_len)
{
    int len = 0;
    
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    
    /* Create and initialise the context */
    if(!ctx)
        handleErrors();
    
    /* Initialise the decryption operation. The asymmetric private key is
     * provided and priv_key, whilst the encrypted session key is held in
     * encrypted_key */
    if(EVP_OpenInit(ctx, EVP_aes_256_cbc(), encrypted_key, encrypted_key_len, iv, PRI_KEY) != 1)
        handleErrors();
    
    /* Provide the message to be decrypted, and obtain the plaintext output.
     * EVP_OpenUpdate can be called multiple times if necessary
     */
    if(EVP_OpenUpdate(ctx, plain_text, &len, cipher_text, cipher_text_len) != 1)
        handleErrors();
    *plain_text_len = len;
    
    /* Finalise the decryption. Further plaintext bytes may be written at
     * this stage.
     */
    if(EVP_OpenFinal(ctx, plain_text + len, &len) != 1)
        handleErrors();
    *plain_text_len += len;
    
    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);
    return true;
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

Buffer::Buffer(size_t sz):
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

CipherText::CipherText(const char *str, int len) :
        ptr(new char[len]), length(len)
{
    std::copy(str, str + len, ptr);
}

CipherText::~CipherText()
{
    delete[] ptr;
}

char *CipherText::str()
{
    return ptr;
}

int &CipherText::len()
{
    return length;
}

size_t CipherText::size() const
{
    return static_cast<size_t>(length);
}
