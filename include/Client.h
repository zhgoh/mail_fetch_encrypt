//
// Created by zgoh on 23/12/17.
//

#ifndef MAILRETRIEVE_CLIENT_H
#define MAILRETRIEVE_CLIENT_H

#include <string>

namespace googleapis
{
    namespace client
    {
        class Date;
    }
}

std::string LoadProfile();
void DeleteProfile();

bool Init(const std::string &client_secrets_path, const std::string &profile);
void GetMail(const googleapis::client::Date &from, const googleapis::client::Date &to);

#endif //MAILRETRIEVE_CLIENT_H
