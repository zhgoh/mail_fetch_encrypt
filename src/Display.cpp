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

void Display(const std::string &prefix, const Message &entry)
{
    std::cout << prefix << "Message Entry" << std::endl;
    std::cout << prefix << "  Thread ID: " << entry.get_thread_id() << std::endl;
    
    if (entry.has_payload())
    {
        Display(prefix, entry.get_payload());
    }
}

void Display(const std::string &prefix, const MessagePart &entry)
{
    std::cout << prefix << "Message Part" << std::endl;
    std::cout << prefix << "  ID: " << entry.get_part_id() << std::endl;
    
    if (entry.has_body())
    {
        Display(prefix, entry.get_body());
    }
}

void Display(const std::string &prefix, const MessagePartBody &entry)
{
    std::cout << prefix << "Message Part Body" << std::endl;
    std::cout << prefix << "  Data: " << entry.get_data() << std::endl;
}