//
// Created by zgoh on 19/12/17.
//

#ifndef MAILRETRIEVE_CLIENT_H
#define MAILRETRIEVE_CLIENT_H
#include "googleapis/util/status.h"

googleapis::util::Status Startup(int argc, char *argv[]);
googleapis::util::Status Authorize();

#endif //MAILRETRIEVE_CLIENT_H
