//
// Created by zgoh on 19/12/17.
//


#include "googleapis/util/status.h"
#include "googleapis/strings/strcat.h"
#include "googleapis/client/util/status.h"
#include "googleapis/client/auth/oauth2_authorization.h"
#include "google/gmail_api/gmail_service.h"
#include "googleapis/client/transport/curl_http_transport.h"
#include "googleapis/client/auth/file_credential_store.h"


static googleapis::util::Status
PromptShellForAuthorizationCode(
        googleapis::client::OAuth2AuthorizationFlow *flow,
        const googleapis::client::OAuth2RequestOptions &options,
        string *authorization_code)
{
    string url = flow->GenerateAuthorizationCodeRequestUrlWithOptions(options);
    std::cout << "Enter the following URL into a browser:\n" << url << std::endl;
    std::cout << std::endl;
    std::cout << "Enter the browser's response to confirm authorization: ";
    
    authorization_code->clear();
    std::cin >> *authorization_code;
    if (authorization_code->empty())
    {
        return googleapis::client::StatusCanceled("Canceled");
    }
    else
    {
        return googleapis::client::StatusOk();
    }
}

static std::unique_ptr<google_gmail_api::GmailService> service_;
static std::unique_ptr<googleapis::client::OAuth2AuthorizationFlow> flow_;
static std::unique_ptr<googleapis::client::HttpTransportLayerConfig> config_;
static googleapis::client::OAuth2Credential credential_;

static googleapis::util::Status ValidateUserName(const string &name)
{
    if (name.find('/') != string::npos)
    {
        return googleapis::client::StatusInvalidArgument("UserNames cannot contain '/'");
    }
    else if (name == "." || name == "..")
    {
        return googleapis::client::StatusInvalidArgument(
                googleapis::StrCat("'", name, "' is not a valid UserName"));
    }
    return googleapis::client::StatusOk();
}

googleapis::util::Status Startup(int argc, char *argv[])
{
    if ((argc < 2) || (argc > 3))
    {
        string error = googleapis::StrCat("Invalid Usage:\n", argv[0], " <client_secrets_file> [<cacerts_path>]\n");
        return googleapis::client::StatusInvalidArgument(error);
    }
    
    // Set up HttpTransportLayer.
    googleapis::util::Status status;
    config_ = std::make_unique<googleapis::client::HttpTransportLayerConfig>();
    googleapis::client::HttpTransportFactory *factory = new googleapis::client::CurlHttpTransportFactory(config_.get());
    config_->ResetDefaultTransportFactory(factory);
    
    if (argc > 2)
    {
        config_->mutable_default_transport_options()->set_cacerts_path(argv[2]);
    }
    
    // Set up OAuth 2.0 flow for getting credentials to access personal data.
    const string client_secrets_file = argv[1];
    flow_.reset(googleapis::client::OAuth2AuthorizationFlow::MakeFlowFromClientSecretsPath(client_secrets_file, config_->NewDefaultTransportOrDie(), &status));
    
    if (!status.ok())
        return status;
    
    flow_->set_default_scopes(google_gmail_api::GmailService::SCOPES::MAIL_GOOGLE_COM);
    flow_->mutable_client_spec()->set_redirect_uri(
            googleapis::client::OAuth2AuthorizationFlow::kOutOfBandUrl);
    flow_->set_authorization_code_callback(googleapis::NewPermanentCallback(&PromptShellForAuthorizationCode, flow_.get()));
    
    
    string home_path;
    status = googleapis::client::FileCredentialStoreFactory::GetSystemHomeDirectoryStorePath(&home_path);
    if (status.ok())
    {
        googleapis::client::FileCredentialStoreFactory store_factory(home_path);
        // Use a credential store to save the credentials between runs so that
        // we don't need to get permission again the next time we run. We are
        // going to encrypt the data in the store, but leave it to the OS to
        // protect access since we do not authenticate users in this sample.
        
        flow_->ResetCredentialStore(store_factory.NewCredentialStore("CalendarSample", &status));
    }
    
    if (!status.ok())
        return status;
    
    // Now we'll initialize the calendar service proxy that we'll use
    // to interact with the calendar from this sample program.
    googleapis::client::HttpTransport *transport = config_->NewDefaultTransport(&status);
    
    if (!status.ok())
        return status;
    
    service_ = std::make_unique<google_gmail_api::GmailService>(transport);
    return status;
}

googleapis::util::Status Authorize()
{
    std::cout
            << std::endl
            << "Welcome to the Google APIs for C++ CalendarSample.\n"
            << "  You will need to authorize this program to look at your calendar.\n"
            << "  If you would like to save these credentials between runs\n"
            << "  (or restore from an earlier run) then enter a Google Email "
                    "Address.\n"
            << "  Otherwise just press return.\n" << std::endl
            << "  Address: ";
    string email;
    
    std::getline(std::cin, email);
    if (!email.empty())
    {
        googleapis::util::Status status = ValidateUserName(email);
        if (!status.ok())
        {
            return status;
        }
    }
    
    googleapis::client::OAuth2RequestOptions options;
    options.email = email;
    googleapis::util::Status status = flow_->RefreshCredentialWithOptions(options, &credential_);
    if (!status.ok())
    {
        return status;
    }
    
    credential_.set_flow(flow_.get());
    std::cout << "Authorized " << email << std::endl;
    return googleapis::client::StatusOk();
}

