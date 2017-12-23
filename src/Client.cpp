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
using googleapis::StrCat;

using googleapis::NewPermanentCallback;

static std::unique_ptr<HttpTransportLayerConfig> config;
static std::unique_ptr<HttpTransport> httpTransport;
static std::unique_ptr<OAuth2AuthorizationFlow> flow;
static OAuth2Credential credential;

Status PromptShellForAuthorizationCode(
        OAuth2AuthorizationFlow *flow,
        const OAuth2RequestOptions &options,
        std::string *authorization_code);

Status ValidateUserName(const std::string &name);

void SendGet(const char *url);
void SendPost(const char *url);
void SendPostWithData(const char *url);

bool Init(const char *client_secrets_path)
{
    // Set up HttpTransportLayer.
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
            << "You will need to authorize this program to look at your mail.\n"
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
            LOG(ERROR) << "Validate User Name failed " << status.error_message();
            return false;
        }
    }
    
    OAuth2RequestOptions options;
    options.email = email;
    
    Status status = flow->RefreshCredentialWithOptions(options, &credential);
    if (!status.ok())
    {
        LOG(ERROR) << "Refresh credentials failed " << status.error_message();
        return false;
    }
    
    credential.set_flow(flow.get());
    std::cout << "Authorized " << email << std::endl;
    return true;
}

static void Send(const char *url, const HttpRequest::HttpMethod &method, const char *data = nullptr)
{
    std::unique_ptr<HttpRequest> request(httpTransport->NewHttpRequest(method));
    request->set_url(url);
    
    if (data)
    {
        DataReader *reader = NewUnmanagedInMemoryDataReader(data);
        request->set_content_reader(reader);
        request->set_content_type("text/plain");
    }
    
    Status status = request->Execute();
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
    SendGet("https://www.googleapis.com/gmail/v1/users/ggneverdie92%40gmail.com/profile");
}