//
// Created by zgoh on 24/12/17.
//

#ifndef MAILRETRIEVE_DISPLAY_H
#define MAILRETRIEVE_DISPLAY_H

#include <iostream>
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
}

void DisplayError(googleapis::client::ClientServiceRequest *request);
void Display(const std::string &prefix, const google_gmail_api::Message &entry);

//void Display(const string &prefix, const google_calendar_api::Calendar &entry)
//{
//    std::cout << prefix << "Calendar" << std::endl;
//    std::cout << prefix << "  ID: " << entry.get_id() << std::endl;
//    std::cout << prefix << "  Summary: " << entry.get_summary() << std::endl;
//    if (!entry.get_description().empty())
//    {
//        std::cout << prefix << "  Description: " << entry.get_description()
//                  << std::endl;
//    }
//}
//
//void Display(const string &prefix, const google_calendar_api::Event &event)
//{
//    std::cout << prefix << "Event" << std::endl;
//    std::cout << prefix << "  ID: " << event.get_id() << std::endl;
//    if (event.has_summary())
//    {
//        std::cout << prefix << "  Summary: " << event.get_summary() << std::endl;
//    }
//    if (event.get_start().has_date_time())
//    {
//        std::cout << prefix << "  Start Time: "
//                  << event.get_start().get_date_time().ToString() << std::endl;
//    }
//
//    if (event.get_end().has_date_time())
//    {
//        std::cout << prefix
//                  << "  End Time: " << event.get_end().get_date_time().ToString()
//                  << std::endl;
//    }
//}

template<typename T>
void DisplayList(const std::string &prefix, const std::string &title, const T &list)
{
    std::cout << prefix << "====  " << title << "  ====" << std::endl;
    std::string sub_prefix = StrCat(prefix, "  ");
    bool first = true;
    auto &items = list.get_items();
    
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
        
        //Display(sub_prefix, elem);
    }
    
    if (first)
    {
        std::cout << sub_prefix << "<no items>" << std::endl;
    }
}

#endif //MAILRETRIEVE_DISPLAY_H
