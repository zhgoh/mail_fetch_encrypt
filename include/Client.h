//
// Created by zgoh on 23/12/17.
//

#ifndef MAILRETRIEVE_CLIENT_H
#define MAILRETRIEVE_CLIENT_H

bool Init(const char *client_secrets_path);
bool Authorize();
void GetMail();

#endif //MAILRETRIEVE_CLIENT_H
