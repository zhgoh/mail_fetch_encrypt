/*
Create a C++ console application to retrieve items in specific Gmail mailbox 
(filtered by specified period of time) and store them in the same folder in encrypted form 
(algorithm should be chosen by yourself). 

Parameters are: mailbox name, mailbox password, start of the retrieval period, end of the retrieval period. 
You need to use official API provided by Google, no IMAP/POP3. 
*/
#define GOOGLE_STRIP_LOG 1
#include <iostream>
#include "googleapis/util/status.h"
#include "samples/gmail/Gmail.h"
#include "samples/gmail/Client.h"

int main(int argc, char *argv[])
{
    auto status = Startup(argc, argv);
    if (!status.ok())
    {
        std::cerr << "Could not initialize application." << std::endl;
        std::cerr << status.error_message() << std::endl;
        return -1;
    }
    
    googleapis::Gmail mail;
    mail.Get();
    
    std::cout << "Done!" << std::endl;
    return 0;
}

