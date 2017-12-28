//
// Created by zgoh on 26/12/17.
//

#ifndef MAILRETRIEVE_CRYPT_H
#define MAILRETRIEVE_CRYPT_H

#include <string>

void EncryptFile(const char *plainMessage, const char *outputFile);
void DecryptFile(const char *inputFile, std::string &plainMessage);
bool Encrypt(const char *plainMessage, char *cipherText, int *cipherLen);
bool Decrypt(const char *cipherText, int cipherLen, char *plainText);

#endif //MAILRETRIEVE_CRYPT_H
