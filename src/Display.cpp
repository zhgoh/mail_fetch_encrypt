//
// Created by zgoh on 24/12/17.
//

#include "Display.h"
#include "google/gmail_api/message.h"
#include "googleapis/client/service/client_service.h"

using googleapis::client::ClientServiceRequest;
using googleapis::client::HttpResponse;

using google_gmail_api::Message;

void DisplayError(ClientServiceRequest *request)
{
    const HttpResponse &response = *request->http_response();
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

void Display(const string &prefix, const Message &entry)
{
//    std::cout << prefix << "CalendarListEntry" << std::endl;
//    std::cout << prefix << "  ID: " << entry.get_id() << std::endl;
//    std::cout << prefix << "  Summary: " << entry.get_summary() << std::endl;
//    if (entry.has_description())
//    {
//        std::cout << prefix << "  Description: " << entry.get_description()
//                  << std::endl;
//    }
}