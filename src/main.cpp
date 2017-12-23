/*
Create a C++ console application to retrieve items in specific Gmail mailbox 
(filtered by specified period of time) and store them in the same folder in encrypted form 
(algorithm should be chosen by yourself). 

Parameters are: mailbox name, mailbox password, start of the retrieval period, end of the retrieval period. 
You need to use official API provided by Google, no IMAP/POP3. 
*/
#include "Client.h"
#include <glog/logging.h>

int main(int argc, char *argv[])
{
    // Init google logging otherwise it will complain
    google::InitGoogleLogging(argv[0]);
    
    Init("./secrets.json");
    Authorize();
    GetMail();
    
    return 0;
}
