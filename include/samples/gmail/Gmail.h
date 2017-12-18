//
// Created by zgoh on 18/12/17.
//

#ifndef MAILRETRIEVE_GMAILSAMPLE_H
#define MAILRETRIEVE_GMAILSAMPLE_H

#include "googleapis/client/util/status.h"
#include <memory>
#include "googleapis/client/auth/oauth2_authorization.h"
#include "google/gmail_api/gmail_service.h"
#include "googleapis/client/transport/http_transport.h"

namespace googleapis
{
    class Gmail
    {
    public:
        void Get();
    };
}

#endif //MAILRETRIEVE_GMAILSAMPLE_H
