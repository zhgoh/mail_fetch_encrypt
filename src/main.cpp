/*
Create a C++ console application to retrieve items in specific Gmail mailbox 
(filtered by specified period of time) and store them in the same folder in encrypted form 
(algorithm should be chosen by yourself). 

Parameters are: mailbox name, mailbox password, start of the retrieval period, end of the retrieval period. 
You need to use official API provided by Google, no IMAP/POP3. 
*/

#include <iostream>
#include <string>

bool RetrieveMail(const std::string &mailBox, const std::string &pass, int start, int end);

int main()
{
    std::cout << "aaa";
    return 0;
}