#include "samples/gmail/Gmail.h"
#include "samples/gmail/Client.h"

void googleapis::Gmail::Get()
{
    std::cout << "Getting User Authorization" << std::endl;
    googleapis::util::Status status = Authorize();
    
    if (!status.ok())
    {
        std::cout << "Could not authorize: " << status.error_message() << std::endl;
        return;
    }
    
    std::cout << "Getting emails ..." << std::endl;
    
    
}


