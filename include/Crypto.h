//
// Created by zgoh on 25/12/17.
//

#ifndef MAILRETRIEVE_CRYPT_H
#define MAILRETRIEVE_CRYPT_H

#include <string>
#include "openssl/evp.h"

void Encrypt(const std::string &file);
void Decrypt(const std::string &file);

class Crypto
{
public:
    Crypto();
    Crypto(unsigned char *remotePubKey, size_t remotePubKeyLen);
    ~Crypto();
    
    int GetRemotePublicKey(unsigned char **publicKey);
    int SetRemotePublicKey(unsigned char *publicKey, size_t publicKeyLen);
    
    int WriteKeyToFile(const char *filePath, int key);
    
private:
    static EVP_PKEY *localKeyPair;
    EVP_PKEY *remotePubKey;
    
    EVP_CIPHER_CTX *rsaEncryptCtx;
    EVP_CIPHER_CTX *aesEncryptCtx;
    
    EVP_CIPHER_CTX *rsaDecryptCtx;
    EVP_CIPHER_CTX *aesDecryptCtx;
    
    unsigned char *aesKey;
    unsigned char *aesIV;
    
    int Init();
};

#endif //MAILRETRIEVE_CRYPT_H
