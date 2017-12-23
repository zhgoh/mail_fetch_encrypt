/*
Create a C++ console application to retrieve items in specific Gmail mailbox 
(filtered by specified period of time) and store them in the same folder in encrypted form 
(algorithm should be chosen by yourself). 

Parameters are: mailbox name, mailbox password, start of the retrieval period, end of the retrieval period. 
You need to use official API provided by Google, no IMAP/POP3. 
*/
#include "Client.h"
#include <iostream>

int main(int argc, char *argv[])
{
    std::string path;
    if (argc == 3)
    {
        path = argv[2];
    }
    
    Init("./secrets.json");
    Authorize();
    
    return 0;
}
