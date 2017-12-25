//
// Created by zgoh on 25/12/17.
//

#include "Crypto.h"
#include "openssl/evp.h"
#include "openssl/pem.h"
#include "openssl/err.h"
#include "openssl/aes.h"

#define KEY_SERVER_PRI 0
#define KEY_SERVER_PUB 1
#define KEY_CLIENT_PUB 2
#define KEY_AES        3
#define KEY_AES_IV 4

#define RSA_KEYLEN 2048
#define AES_KEYLEN 256
#define AES_ROUNDS 6

#include <iostream>

EVP_PKEY *Crypto::localKeyPair = nullptr;

Crypto::Crypto() :
        localKeyPair(nullptr),
        remotePubKey(nullptr)
{
    Init();
}

Crypto::Crypto(unsigned char *remotePubKey, size_t remotePubKeyLen) :
        localKeyPair(nullptr),
        remotePubKey(nullptr)
{
    SetRemotePublicKey(remotePubKey, remotePubKeyLen);
    Init();
}

Crypto::~Crypto()
{
    EVP_PKEY_free(remotePubKey);
    
    EVP_CIPHER_CTX_free(rsaEncryptCtx);
    EVP_CIPHER_CTX_free(aesEncryptCtx);
    
    EVP_CIPHER_CTX_free(rsaDecryptCtx);
    EVP_CIPHER_CTX_free(aesDecryptCtx);
    
    free(aesKey);
    free(aesIV);
}

int Crypto::Init()
{
    rsaEncryptCtx = EVP_CIPHER_CTX_new();
    aesEncryptCtx = EVP_CIPHER_CTX_new();
    
    rsaDecryptCtx = EVP_CIPHER_CTX_new();
    aesDecryptCtx = EVP_CIPHER_CTX_new();
    
    if (!rsaEncryptCtx || !aesEncryptCtx || !rsaDecryptCtx || !aesDecryptCtx)
    {
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}

int Crypto::WriteKeyToFile(const char *filePath, int key)
{
    FILE *file = fopen(filePath, "rb");
    
    switch(key)
    {
        case KEY_SERVER_PRI:
            if(!PEM_write_PrivateKey(file, localKeyPair, NULL, NULL, 0, 0, NULL)) {
                return EXIT_FAILURE;
            }
            break;
        
        case KEY_SERVER_PUB:
            if(!PEM_write_PUBKEY(file, localKeyPair))
            {
                return EXIT_FAILURE;
            }
            break;
        
        case KEY_CLIENT_PUB:
            if(!PEM_write_PUBKEY(file, remotePubKey))
            {
                return EXIT_FAILURE;
            }
            break;
        
        case KEY_AES:
            fwrite(aesKey, 1, AES_KEYLEN, file);
            break;
        
        case KEY_AES_IV:
            fwrite(aesIV, 1, AES_KEYLEN, file);
            break;
        
        default:
            return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}

void handleErrors()
{

}

int envelope_seal(EVP_PKEY **pub_key, unsigned char *plaintext, int plaintext_len,
                  unsigned char **encrypted_key, int *encrypted_key_len, unsigned char *iv,
                  unsigned char *cipherText)
{
    /* Create and initialise the context */
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if(!ctx)
    {
        handleErrors();
    }
    
    /* Initialise the envelope seal operation. This operation generates
     * a key for the provided cipher, and then encrypts that key a number
     * of times (one for each public key provided in the pub_key array). In
     * this example the array size is just one. This operation also
     * generates an IV and places it in iv. */
    if (!EVP_SealInit(ctx, EVP_aes_256_cbc(), encrypted_key, encrypted_key_len, iv, pub_key, 1))
    {
        handleErrors();
    }
    
    int cipherTextLength = 0;
    int len = 0;
    
    /* Provide the message to be encrypted, and obtain the encrypted output.
     * EVP_SealUpdate can be called multiple times if necessary
     */
    if (!EVP_SealUpdate(ctx, cipherText, &len, plaintext, plaintext_len))
    {
        handleErrors();
    }
    
    cipherTextLength = len;
    
    /* Finalise the encryption. Further ciphertext bytes may be written at
     * this stage.
     */
    if (!EVP_SealFinal(ctx, cipherText + len, &len))
    {
        handleErrors();
    }
    
    cipherTextLength += len;
    
    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);
    return cipherTextLength;
}

int envelope_open(EVP_PKEY *priv_key, unsigned char *ciphertext, int ciphertext_len,
                  unsigned char *encrypted_key, int encrypted_key_len, unsigned char *iv,
                  unsigned char *plaintext)
{
    EVP_CIPHER_CTX *ctx;
    
    int len;
    
    int plaintext_len;
    
    
    /* Create and initialise the context */
    if(!(ctx = EVP_CIPHER_CTX_new())) handleErrors();
    
    /* Initialise the decryption operation. The asymmetric private key is
     * provided and priv_key, whilst the encrypted session key is held in
     * encrypted_key */
    if(1 != EVP_OpenInit(ctx, EVP_aes_256_cbc(), encrypted_key,
                         encrypted_key_len, iv, priv_key))
        handleErrors();
    
    /* Provide the message to be decrypted, and obtain the plaintext output.
     * EVP_OpenUpdate can be called multiple times if necessary
     */
    if(1 != EVP_OpenUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))
        handleErrors();
    plaintext_len = len;
    
    /* Finalise the decryption. Further plaintext bytes may be written at
     * this stage.
     */
    if(1 != EVP_OpenFinal(ctx, plaintext + len, &len)) handleErrors();
    plaintext_len += len;
    
    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);
    
    return plaintext_len;
}


void Encrypt(const std::string &file)
{

}

void Decrypt(const std::string &file)
{

}