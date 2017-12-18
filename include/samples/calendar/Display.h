#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include "../../googleapis/client/service/client_service.h"
#include "../../googleapis/client/transport/http_response.h"
#include "../../googleapis/strings/strcat.h"
#include "../../googleapis/client/data/data_reader.h"

void DisplayError(googleapis::client::ClientServiceRequest *request)
{
    const googleapis::client::HttpResponse &response = *request->http_response();
    std::cout << "====  ERROR  ====" << std::endl;
    std::cout << "Status: " << response.status().error_message() << std::endl;
    if (response.transport_status().ok())
    {
        std::cout << "HTTP Status Code = " << response.http_code() << std::endl;
        std::cout << std::endl
                  << response.body_reader()->RemainderToString() << std::endl;
    }
    std::cout << std::endl;
}

void Display(const string &prefix, const google_calendar_api::CalendarListEntry &entry)
{
    std::cout << prefix << "CalendarListEntry" << std::endl;
    std::cout << prefix << "  ID: " << entry.get_id() << std::endl;
    std::cout << prefix << "  Summary: " << entry.get_summary() << std::endl;
    if (entry.has_description())
    {
        std::cout << prefix << "  Description: " << entry.get_description()
                  << std::endl;
    }
}

void Display(const string &prefix, const google_calendar_api::Calendar &entry)
{
    std::cout << prefix << "Calendar" << std::endl;
    std::cout << prefix << "  ID: " << entry.get_id() << std::endl;
    std::cout << prefix << "  Summary: " << entry.get_summary() << std::endl;
    if (!entry.get_description().empty())
    {
        std::cout << prefix << "  Description: " << entry.get_description()
                  << std::endl;
    }
}

void Display(const string &prefix, const google_calendar_api::Event &event)
{
    std::cout << prefix << "Event" << std::endl;
    std::cout << prefix << "  ID: " << event.get_id() << std::endl;
    if (event.has_summary())
    {
        std::cout << prefix << "  Summary: " << event.get_summary() << std::endl;
    }
    if (event.get_start().has_date_time())
    {
        std::cout << prefix << "  Start Time: "
                  << event.get_start().get_date_time().ToString() << std::endl;
    }
    
    if (event.get_end().has_date_time())
    {
        std::cout << prefix
                  << "  End Time: " << event.get_end().get_date_time().ToString()
                  << std::endl;
    }
}

template<class LIST, typename ELEM>
void DisplayList(const googleapis::string &prefix, const googleapis::string &title, const LIST &list)
{
    std::cout << prefix << "====  " << title << "  ====" << std::endl;
    string sub_prefix = googleapis::StrCat(prefix, "  ");
    bool first = true;
    const googleapis::client::JsonCppArray<ELEM> &items = list.get_items();
    for (typename googleapis::client::JsonCppArray<ELEM>::const_iterator it = items.begin();
         it != items.end();
         ++it)
    {
        if (first)
        {
            first = false;
        } else
        {
            std::cout << std::endl;
        }
        Display(sub_prefix, *it);
    }
    if (first)
    {
        std::cout << sub_prefix << "<no items>" << std::endl;
    }
}

#endif