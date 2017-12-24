//
// Created by zgoh on 23/12/17.
//

#define GOOGLE_STRIP_LOG 1
#include <iostream>
#include <memory>

#include "googleapis/util/status.h"
#include "googleapis/client/data/data_reader.h"
#include "googleapis/client/transport/http_request.h"
#include "googleapis/client/transport/http_transport.h"
#include "googleapis/client/transport/curl_http_transport.h"
#include "googleapis/strings/stringpiece.h"
#include "googleapis/client/auth/file_credential_store.h"
#include "googleapis/client/auth/oauth2_authorization.h"
#include "google/gmail_api/gmail_service.h"
#include "googleapis/strings/strcat.h"

#include "Display.h"

using googleapis::StrCat;
using googleapis::NewPermanentCallback;
using googleapis::util::Status;
using googleapis::client::HttpResponse;
using googleapis::client::HttpTransport;
using googleapis::client::DataReader;
using googleapis::client::HttpRequest;
using googleapis::client::HttpTransportFactory;
using googleapis::client::CurlHttpTransportFactory;
using googleapis::client::OAuth2AuthorizationFlow;
using googleapis::client::FileCredentialStoreFactory;
using googleapis::client::NewUnmanagedInMemoryDataReader;
using googleapis::client::OAuth2RequestOptions;
using googleapis::client::HttpTransportLayerConfig;
using googleapis::client::OAuth2Credential;
using googleapis::client::StatusInvalidArgument;
using googleapis::client::StatusInvalidArgument;
using googleapis::client::StatusCanceled;
using googleapis::client::StatusOk;
using googleapis::client::OAuth2AuthorizationFlow;
using googleapis::client::OAuth2RequestOptions;

using google_gmail_api::GmailService;
using google_gmail_api::UsersResource_MessagesResource_ListMethod;
using google_gmail_api::ListMessagesResponse;


static std::unique_ptr<HttpTransportLayerConfig> config;
static std::unique_ptr<OAuth2AuthorizationFlow> flow;
static std::unique_ptr<OAuth2Credential> credential;
static std::unique_ptr<GmailService> service;

Status PromptShellForAuthorizationCode(
        OAuth2AuthorizationFlow *flow,
        const OAuth2RequestOptions &options,
        std::string *authorization_code);

Status ValidateUserName(const std::string &name);

bool Init(const char *client_secrets_path)
{
    // Set up the credential
    credential = std::make_unique<OAuth2Credential>();
    
    // Set up HttpTransportLayer config
    //credential
    config = std::make_unique<HttpTransportLayerConfig>();
    
    /* TODO: Check how to get rid of this Memory leak, making it a smart pointer
             or deleting at the end will make the app return status 11 */
    HttpTransportFactory *factory = new CurlHttpTransportFactory(config.get());
    config->ResetDefaultTransportFactory(factory);

    Status status;
    flow.reset(OAuth2AuthorizationFlow::MakeFlowFromClientSecretsPath(client_secrets_path, config->NewDefaultTransportOrDie(), &status));

    CHECK(status.ok()) << status.error_message();

    std::string dir;
    status = FileCredentialStoreFactory::GetSystemHomeDirectoryStorePath(&dir);

    if (!status.ok())
    {
        LOG(ERROR) << "Not adding a credential store: " << status.error_message();
        return false;
    }
    
    // NOTE: Whenever there's a new API, change the Credential Store for different APIS
    FileCredentialStoreFactory store_factory(dir);
    flow->ResetCredentialStore(store_factory.NewCredentialStore("Mail Retrieve", &status));


    flow->set_default_scopes(google_gmail_api::GmailService::SCOPES::MAIL_GOOGLE_COM);
    flow->mutable_client_spec()->set_redirect_uri(OAuth2AuthorizationFlow::kOutOfBandUrl);
    flow->set_authorization_code_callback(NewPermanentCallback(&PromptShellForAuthorizationCode, flow.get()));

    auto httpTransport = config->NewDefaultTransport(&status);
    if (!status.ok())
    {
        LOG(ERROR) << "Failed to create transport" << std::endl;
        return false;
    }
    
    service = std::make_unique<GmailService>(httpTransport);
}

// Taken from Calendar sample
bool Authorize()
{
    std::cout
            << std::endl
            << "Welcome to the Google APIs for C++ Mail Retrieve.\n"
            << "You will need to authorize this program to look at your mail.\n"
            << "If you would like to save these credentials between runs\n"
            << "(or restore from an earlier run) then enter a Google Email Address.\n"
            << "Otherwise just press return.\n" << std::endl
            << "Address: ";
    
    std::string email;
    email = "ggneverdie92@gmail.com";
    //std::getline(std::cin, email);
    
    if (!email.empty())
    {
        Status status = ValidateUserName(email);
        if (!status.ok())
        {
            LOG(ERROR) << "Validate User Name failed " << status.error_message();
            return false;
        }
    }
    
    OAuth2RequestOptions options;
    options.email = "ggneverdie92@gmail.com";
    // options.email = email;
    
    Status status = flow->RefreshCredentialWithOptions(options, credential.get());
    if (!status.ok())
    {
        LOG(ERROR) << "Refresh credentials failed " << status.error_message();
        return false;
    }
    
    credential->set_flow(flow.get());
    std::cout << "Authorized " << email << std::endl;
    return true;
}

Status PromptShellForAuthorizationCode(
        OAuth2AuthorizationFlow *flow,
        const OAuth2RequestOptions &options,
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

void GetMail()
{
    auto &users = service->get_users();
    auto &messages = users.get_messages();
    std::unique_ptr<UsersResource_MessagesResource_ListMethod> listMethod((messages.NewListMethod(credential.get(), "me")));
    std::unique_ptr<ListMessagesResponse> messageList(ListMessagesResponse::New());
    
    if (!listMethod->ExecuteAndParseResponse(messageList.get()).ok())
    {
        DisplayError(listMethod.get());
        return;
    }
    
    //DisplayList<google_gmail_api::CalendarList, google_calendar_api::CalendarListEntry>("", "CalendarList", *calendar_list);
    std::cout << std::endl;
}