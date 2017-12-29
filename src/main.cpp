/*
Create a C++ console application to retrieve items in specific Gmail mailbox 
(filtered by specified period of time) and store them in the same folder in encrypted form 
(algorithm should be chosen by yourself). 

Parameters are: mailbox name, mailbox password, start of the retrieval period, end of the retrieval period. 
You need to use official API provided by Google, no IMAP/POP3. 
*/
#include <glog/logging.h>
#include <iostream>
#include <dirent.h>
#include <googleapis/client/util/date_time.h>

#include "Client.h"
#include "MyCrypt.h"

void DecryptFolder();

int main(int argc, char *argv[])
{
    // Init google logging otherwise it will complain
    google::InitGoogleLogging(argv[0]);
    EncryptInit();
    
    if (argc == 1)
    {
        // Decrypt mode
        DecryptFolder();
    }
    else if (argc == 2)
    {
        // Show console prompt
        std::cout << "\nWelcome to the Mail Retrieve App.\n";
        std::cout << "Choose one of the options \n";
        std::cout << "\n1: Retrieve mails with specified date. \n";
        std::cout << "2: Decrypt messages \n";
        std::cout << "\nChoice: ";
    
        int options;
        std::cin >> options;
        std::cin.ignore();
    
        switch(options)
        {
            case 1:
            {
                std::string profile = LoadProfile();
                if (InitClient(argv[1], profile))
                {
                    std::cout << "Type a start date, YYYY-MM-DD with dash: ";
                    std::string from;
                    std::getline(std::cin, from, '\n');
                
                    std::cout << "Type an end date, YYYY-MM-DD with dash: ";
                    std::string to;
                    std::getline(std::cin, to, '\n');
                
                    std::cout << "Type a folder to get messages from [default = inbox]: ";
                    std::string folder;
                    std::getline(std::cin, folder, '\n');
                
                    GetMail(googleapis::client::Date(from), googleapis::client::Date(to), folder.c_str());
                }
            } break;
        
            case 2:
            {
                DecryptFolder();
            } break;
        }
    }
    else if (argc == 5)
    {
        // ./a ./secrets.json inbox 2017-12-24 2017-12-27
        std::string profile = LoadProfile();
        if (InitClient(argv[1], profile))
        {
            std::string folder = argv[2];
            std::string from = argv[3];
            std::string to = argv[4];
    
            GetMail(googleapis::client::Date(from), googleapis::client::Date(to), folder.c_str());
        }
    }
    
    
    return 0;
}

void DecryptFolder()
{
    DIR *dir;
    struct dirent *ent;
    const std::string inputFolder ="./messages/enc/";
    const std::string outputFolder ="./messages/dec/";
    
    if ((dir = opendir(inputFolder.c_str())) != nullptr) {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != nullptr) {
            if (!strcmp(ent->d_name, ".") || !strcmp(ent->d_name, ".."))
            {
                continue;
            }
            
            const std::string inputFile = inputFolder + ent->d_name;
            std::cout <<"Decrypting " << inputFile << std::endl;
            
            const std::string outputFile = outputFolder + ent->d_name;
            DecryptFile(inputFile.c_str(), outputFile.c_str());
        }
        closedir (dir);
    } else {
        /* could not open directory */
        LOG(ERROR) << "Could not open dir";
    }
}
