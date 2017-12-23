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

#include "Utils.h"

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

using googleapis::NewPermanentCallback;

static std::unique_ptr<HttpTransportLayerConfig> config;
static std::unique_ptr<HttpTransport> httpTransport;
static std::unique_ptr<OAuth2AuthorizationFlow> flow;
static OAuth2Credential credential;



bool Init(const char *client_secrets_path)
{
    // Set up HttpTransportLayer.
    config = std::make_unique<HttpTransportLayerConfig>();
    
    /* TODO: Check how to get rid of this Memory leak, making it a smart pointer
             or deleting at the end will make the app return status 11 */
    HttpTransportFactory *factory = new CurlHttpTransportFactory(config.get());
    config->ResetDefaultTransportFactory(factory);

    googleapis::util::Status status;
    flow.reset(OAuth2AuthorizationFlow::MakeFlowFromClientSecretsPath(
                    client_secrets_path, config->NewDefaultTransportOrDie(), &status));

    CHECK(status.ok()) << status.error_message();

    std::string dir;
    status = FileCredentialStoreFactory::GetSystemHomeDirectoryStorePath(&dir);

    if (!status.ok())
    {
        LOG(ERROR) << "Not adding a credential store: " << status.error_message();
        return false;
    }

    FileCredentialStoreFactory store_factory(dir);
    flow->ResetCredentialStore(store_factory.NewCredentialStore("CalendarSample", &status));


    flow->set_default_scopes(google_gmail_api::GmailService::SCOPES::GMAIL_READONLY);
    flow->mutable_client_spec()->set_redirect_uri(OAuth2AuthorizationFlow::kOutOfBandUrl);
    flow->set_authorization_code_callback(NewPermanentCallback(&PromptShellForAuthorizationCode, flow.get()));

    httpTransport = std::unique_ptr<HttpTransport>(config->NewDefaultTransport(&status));
    if (!status.ok())
    {
        LOG(ERROR) << "Failed to create transport" << std::endl;
        return false;
    }
}

// Taken from Calendar sample
bool Authorize()
{
    std::cout
            << std::endl
            << "Welcome to the Google APIs for C++ Mail Retrieve.\n"
            << "You will need to authorize this program to look at your calendar.\n"
            << "If you would like to save these credentials between runs\n"
            << "(or restore from an earlier run) then enter a Google Email Address.\n"
            << "Otherwise just press return.\n" << std::endl
            << "Address: ";
    
    std::string email;
    std::getline(std::cin, email);
    
    if (!email.empty())
    {
        Status status = ValidateUserName(email);
        if (!status.ok())
        {
            return false;
        }
    }
    
    googleapis::client::OAuth2RequestOptions options;
    options.email = email;
    
    Status status = flow->RefreshCredentialWithOptions(options, &credential);
    if (!status.ok())
    {
        return false;
    }
    
    credential.set_flow(flow.get());
    std::cout << "Authorized " << email << std::endl;
    return true;
}

static void Send(const char *url, HttpRequest::HttpMethod method, const char *data = nullptr)
{
    std::unique_ptr<googleapis::client::HttpRequest> request(httpTransport->NewHttpRequest(method));
    request->set_url(url);
    
    if (data)
    {
        DataReader *reader = NewUnmanagedInMemoryDataReader(data);
        request->set_content_reader(reader);
        request->set_content_type("text/plain");
    }
    
    googleapis::util::Status status = request->Execute();
    if (!status.ok())
    {
        std::cerr << status.error_message();
    }
    
    
    HttpResponse *response = request->response();
    if (response->ok())
    {
        std::cout << "Success" << std::endl;
    }
    else
    {
        std::cout << "Failed with status=" << response->status().error_message() << std::endl;
    }
}

void SendGet(const char *url)
{
    Send(url, HttpRequest::GET);
}

void SendPost(const char *url)
{
    Send(url, HttpRequest::POST);
}

void SendPostWithData(const char *url)
{
    Send(url, HttpRequest::POST, "Hello World");
}