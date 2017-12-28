//
// Created by zgoh on 24/12/17.
//

#ifndef MAILRETRIEVE_DISPLAY_H
#define MAILRETRIEVE_DISPLAY_H

#include <iostream>
#include <google/gmail_api/message_part.h>
#include "googleapis/strings/strcat.h"
#include "googleapis/client/data/data_reader.h"

using googleapis::StrCat;

namespace googleapis
{
    namespace client
    {
        class ClientServiceRequest;
    }
}

namespace google_gmail_api
{
    class Message;
    class MessagePart;
    class MessagePartHeader;
    class MessagePartBody;
}

std::ostream &Indent(int tabs);

void DisplayError(googleapis::client::ClientServiceRequest *request);
void Display(const google_gmail_api::Message &entry);
void Display(const google_gmail_api::MessagePart &entry, int tabs = 0);
void Display(const google_gmail_api::MessagePartBody &entry, int tabs = 0);
void Display(const google_gmail_api::MessagePartHeader &entry, int tabs = 0);

template<typename T>
void DisplayMessages(const std::string &prefix, const std::string &title, const T &list)
{
    std::cout << prefix << "====  " << title << "  ====" << std::endl;
    std::string sub_prefix = StrCat(prefix, "  ");
    bool first = true;
    auto &items = list.get_messages();
    std::cout << "Num of items:" << items.size() << std::endl;
    for (const auto &elem : items)
    {
        if (first)
        {
            first = false;
        }
        else
        {
            std::cout << std::endl;
        }
        
        Display(elem);
    }
    
    if (first)
    {
        std::cout << sub_prefix << "<no items>" << std::endl;
    }
}

template <typename T>
void WriteLine( const char *key, const T &val, int tabs)
{
    Indent(tabs) << "\"" << key << "\":\"" << val << "\", \n";
}

#endif //MAILRETRIEVE_DISPLAY_H
