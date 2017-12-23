//
// Created by zgoh on 23/12/17.
//

#ifndef MAILRETRIEVE_UTILS_H
#define MAILRETRIEVE_UTILS_H

#include "googleapis/util/status.h"

namespace googleapis
{
    namespace client
    {
        class OAuth2AuthorizationFlow;
        class OAuth2RequestOptions;
    }
}

googleapis::util::Status PromptShellForAuthorizationCode(
        googleapis::client::OAuth2AuthorizationFlow *flow,
        const googleapis::client::OAuth2RequestOptions &options,
        std::string *authorization_code);

googleapis::util::Status ValidateUserName(const std::string &name);

#endif //MAILRETRIEVE_UTILS_H
