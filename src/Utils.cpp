//
// Created by zgoh on 23/12/17.
// This file is taken from the Calendar Sample and modified to my own use
//

#include "Utils.h"
#include <iostream>

#include "googleapis/client/auth/oauth2_authorization.h"
#include "googleapis/strings/strcat.h"


using googleapis::util::Status;
using googleapis::client::StatusInvalidArgument;
using googleapis::client::StatusCanceled;
using googleapis::client::StatusOk;
using googleapis::client::OAuth2AuthorizationFlow;
using googleapis::client::OAuth2RequestOptions;
using googleapis::StrCat;

Status PromptShellForAuthorizationCode(
        googleapis::client::OAuth2AuthorizationFlow *flow,
        const googleapis::client::OAuth2RequestOptions &options,
        std::string *authorization_code)
{
    std::string url = flow->GenerateAuthorizationCodeRequestUrlWithOptions(options);
    std::cout << "Enter the following URL into a browser:\n" << url << std::endl;
    std::cout << std::endl;
    std::cout << "Enter the browser's response to confirm authorization: ";
    
    authorization_code->clear();
    std::cin >> *authorization_code;
    if (authorization_code->empty())
    {
        return StatusCanceled("Canceled");
    }
    else
    {
        return StatusOk();
    }
}

Status ValidateUserName(const std::string &name)
{
    if (name.find('/') != string::npos)
    {
        return StatusInvalidArgument("UserNames cannot contain '/'");
    }
    else if (name == "." || name == "..")
    {
        return StatusInvalidArgument(StrCat("'", name, "' is not a valid UserName"));
    }
    return StatusOk();
}