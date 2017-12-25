/*
Create a C++ console application to retrieve items in specific Gmail mailbox 
(filtered by specified period of time) and store them in the same folder in encrypted form 
(algorithm should be chosen by yourself). 

Parameters are: mailbox name, mailbox password, start of the retrieval period, end of the retrieval period. 
You need to use official API provided by Google, no IMAP/POP3. 
*/
#include "Client.h"
#include <glog/logging.h>
#include "googleapis/client/util/date_time.h"
#include <iostream>

int main(int argc, char *argv[])
{
    // Init google logging otherwise it will complain
    google::InitGoogleLogging(argv[0]);
    
    if (argc < 2)
    {
        LOG(ERROR) << "Specify the secrets for google dev console.";
        return 0;
    }
    
    std::cout << "Welcome to the Mail Retrieve App.\n";
    std::cout << "Choose one of the options \n";
    std::cout << "1: Retrieve a mail with specified date. \n";
    std::cout << "2: Clear saved email profile. \n";
    std::cout << "Choice: ";
    
    int options = 1;
    //std::cin >> options;
    switch(options)
    {
        case 1:
        {
            std::string profile = LoadProfile();
            if (Init(argv[1], profile))
            {
                std::cout << "Type a start date, YYYY-MM-DD with dash: ";
                std::string from = "2017-12-24";
                //std::cin >> from;
        
                std::cout << "Type an end date, YYYY-MM-DD with dash: ";
                std::string to = "2017-12-25";
                //std::cin >> to;
                GetMail(googleapis::client::Date(from), googleapis::client::Date(to));
            }
        } break;
    
        case 2:
        {
            DeleteProfile();
        } break;
    }
    return 0;
}
