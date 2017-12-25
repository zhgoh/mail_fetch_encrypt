//
// Created by zgoh on 24/12/17.
//

#include "Display.h"
#include "google/gmail_api/message.h"
#include "googleapis/client/service/client_service.h"

using googleapis::client::ClientServiceRequest;
using googleapis::client::HttpResponse;

using google_gmail_api::Message;
using google_gmail_api::MessagePart;
using google_gmail_api::MessagePartHeader;
using google_gmail_api::MessagePartBody;

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

void Display(const Message &entry)
{
    std::cout << "Message Entry" << std::endl;
    std::cout << "  Thread ID: " << entry.get_thread_id() << std::endl;
    
    if (entry.has_payload())
    {
        // Display Message Part
        Display(entry.get_payload());
    }
}

void Display( const MessagePart &entry)
{
    std::cout << "Message Parts" << std::endl;
    if (entry.has_headers())
    {
        for (const auto &elem : entry.get_headers())
        {
            // Display Headers
            Display(elem);
        }
    }
    
    if (entry.has_parts())
    {
        for (const auto &elem : entry.get_parts())
        {
            // Display Message Part
            Display(elem);
        }
    }
    
    if (entry.has_body())
    {
        Display(entry.get_body());
    }
}

void Display(const MessagePartHeader &entry)
{
    if (entry.has_name())
    {
        std::cout << "name: " << entry.get_name() << std::endl;
    }
    
    if (entry.has_value())
    {
        std::cout << "value: " << entry.get_value() << std::endl;
    }
}

void Display(const MessagePartBody &entry)
{
    std::cout << "Message Part Body" << std::endl;
    if (entry.has_data())
    {
        std::cout << "  Data: " << entry.get_data() << std::endl;
    }
}