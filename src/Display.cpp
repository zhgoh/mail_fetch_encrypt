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
using googleapis::client::JsonCppArray;

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

const int tabSize = 2;

void Display(const JsonCppArray<std::string> &entry, int tabs)
{
    for (const auto &elem : entry)
    {
        Indent(tabs + tabSize) << elem << ",\n";
    }
}

void Display(const Message &entry)
{
    int tabs = 0;
    std::cout << "{" << std::endl;
    WriteLine("id", entry.get_thread_id(), tabs + tabSize);
    WriteLine("threadid", entry.get_thread_id(), tabs + tabSize);
    
    if (entry.has_label_ids())
    {
        Indent(tabs + tabSize) << "\"labelIds\": [\n";
        // Display Label party
        Display(entry.get_label_ids(), tabs + tabSize);
        Indent(tabs + tabSize) << "],\n";
    }
    
    if (entry.has_snippet())
    {
    
    }
    
    if (entry.has_payload())
    {
        Indent(tabs + tabSize) << "\"payload\": {\n";
        // Display Message Part
        Display(entry.get_payload(), tabs + tabSize);
        Indent(tabs + tabSize) << "}\n";
    }
    std::cout << "}" << std::endl;
}

void Display(const MessagePart &entry, int tabs)
{
    if (entry.has_headers())
    {
        Indent(tabs + tabSize) << "\"headers\": [\n";
        for (const auto &elem : entry.get_headers())
        {
            Indent(tabs + tabSize) << "{\n";
            // Display Headers
            Display(elem, tabs + tabSize);
            Indent(tabs + tabSize) << "},\n";
        }
        Indent(tabs + tabSize) << "],\n";
    }
    
    if (entry.has_parts())
    {
        for (const auto &elem : entry.get_parts())
        {
            // Display Message Part
            //Display(elem, tabs + tabSize);
        }
    }
    
    if (entry.has_body())
    {
        //Display(entry.get_body(), tabs + tabSize);
    }
}

void Display(const MessagePartHeader &entry, int tabs)
{
    if (entry.has_name())
    {
        WriteLine("name", entry.get_name(), tabs + tabSize);
    }
    
    if (entry.has_value())
    {
        WriteLine("value", entry.get_value(), tabs + tabSize);
    }
}

void Display(const MessagePartBody &entry, int tabs)
{
    if (entry.has_data())
    {
        //WriteLine("Data", entry.get_data(), tabs + tabSize);
    }
}

std::ostream &Indent(int tabs)
{
    for (int i = 0; i < tabs; ++i)
    {
        std::cout << " ";
    }
    return std::cout;
}