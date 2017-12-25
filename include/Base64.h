//
// Created by zgoh on 25/12/17.
// https://stackoverflow.com/questions/180947/base64-decode-snippet-in-c/31322410#31322410

#ifndef _BASE64_H_
#define _BASE64_H_

#include <vector>
#include <string>
typedef unsigned char BYTE;

class Base64
{
public:
    static std::string encode(const std::vector<BYTE>& buf);
    static std::string encode(const BYTE* buf, unsigned int bufLen);
    static std::vector<BYTE> decode(std::string encoded_string);
};

#endif