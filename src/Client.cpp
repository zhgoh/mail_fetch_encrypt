//
// Created by zgoh on 23/12/17.
//

#define GOOGLE_STRIP_LOG 1
#include <iostream>
#include <fstream>
#include <memory>

#include "googleapis/util/status.h"
#include "googleapis/client/data/data_reader.h"
#include "googleapis/client/transport/http_request.h"
#include "googleapis/client/transport/http_transport.h"
#include "googleapis/client/transport/curl_http_transport.h"
#include "googleapis/strings/stringpiece.h"
#include "googleapis/client/auth/file_credential_store.h"
#include "googleapis/client/auth/oauth2_authorization.h"
#include "googleapis/client/data/base64_codec.h"
#include "google/gmail_api/gmail_service.h"
#include "googleapis/strings/strcat.h"

#include "Display.h"
#include "MyCrypt.h"

static const char folder[] = "./Messages/";

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
using googleapis::client::Date;

using googleapis::client::Codec;
using googleapis::client::Base64CodecFactory;
using googleapis::client::Base64Codec;

using google_gmail_api::GmailService;
using google_gmail_api::Message;
using google_gmail_api::UsersResource_MessagesResource_ListMethod;
using google_gmail_api::ListMessagesResponse;
using google_gmail_api::UsersResource_MessagesResource_GetMethod;
using google_gmail_api::ListMessagesResponse;

static std::unique_ptr<HttpTransportLayerConfig> config;
static std::unique_ptr<OAuth2AuthorizationFlow> flow;
static std::unique_ptr<OAuth2Credential> credential;
static std::unique_ptr<GmailService> service;

static Status PromptShellForAuthorizationCode(
        OAuth2AuthorizationFlow *flow,
        const OAuth2RequestOptions &options,
        std::string *authorization_code);

static Status ValidateUserName(const std::string &name);
static bool Authorize(const std::string &profile);

bool InitClient(const std::string &client_secrets_path, const std::string &profile)
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
    
    return Authorize(profile);
}

static bool Authorize(const std::string &profile)
{
    if (!profile.empty())
    {
        Status status = ValidateUserName(profile);
        if (!status.ok())
        {
            LOG(ERROR) << "Validate User Name failed " << status.error_message();
            return false;
        }
    }
    
    OAuth2RequestOptions options;
    options.email = profile;
    
    Status status = flow->RefreshCredentialWithOptions(options, credential.get());
    if (!status.ok())
    {
        LOG(ERROR) << "Refresh credentials failed " << status.error_message();
        return false;
    }
    
    credential->set_flow(flow.get());
    std::cout << "Authorized profile " << profile << std::endl;
    return true;
}

static Status PromptShellForAuthorizationCode(
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

static Status ValidateUserName(const std::string &name)
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

void GetMail(const Date &from, const Date &to)
{
    auto &messages = service->get_users().get_messages();
    std::unique_ptr<UsersResource_MessagesResource_ListMethod> listMethod((messages.NewListMethod(credential.get(), "me")));
    std::unique_ptr<ListMessagesResponse> messageList(ListMessagesResponse::New());
    
    std::string query = std::string("in:inbox after:") + from.ToYYYYMMDD() + std::string(" before:") + to.ToYYYYMMDD();
    std::cout << "Query: " << query << std::endl;
    listMethod->set_q(query.c_str());
    
    if (!listMethod->ExecuteAndParseResponse(messageList.get()).ok())
    {
        DisplayError(listMethod.get());
        return;
    }
    
    //DisplayMessages<ListMessagesResponse>("", "Messages", *messageList);
    std::cout << std::endl;
    
    for (const auto &elem : messageList->get_messages())
    {
        auto msgID = elem.get_id();
        //std::cout << msgID << std::endl;
        std::unique_ptr<UsersResource_MessagesResource_GetMethod> getMethod((messages.NewGetMethod(credential.get(), "me", msgID)));
        std::unique_ptr<Message> msg(Message::New());
        getMethod->set_format("full");
    
        if (!getMethod->ExecuteAndParseResponse(msg.get()).ok())
        {
            DisplayError(getMethod.get());
            return;
        }
        
        // Write the JSON to a string stream
        std::stringstream ss;
        msg->StoreToJsonStream(&ss);
        
        // Store all messages inside folder
        const std::string file = std::string(folder) + msgID.data();
        const std::string encryptedFileName = file + "_enc";
        const std::string decryptedFileName = file + "_dec";
        
        EncryptFile(ss.str().c_str(), encryptedFileName.c_str());
        
        std::string message_decrypted;
        DecryptFile(encryptedFileName.c_str(), decryptedFileName.c_str());
        //Display(*msg);
    }
    
    std::cout << std::endl;
}

std::string LoadProfile()
{
    std::string profile;
    std::ifstream ifs("./profile");
    if (ifs.good())
    {
        ifs >> profile;
        if (!profile.empty())
        {
            std::cout << "Profile "<< profile << " successfully loaded!\n";
            return profile;
        }
    }
    
    ifs.close();
    std::ofstream ofs("./profile");

    std::cout << "There is no profile found, please create a new profile using your email. \n";
    std::cout << "Enter your email address (Profile): ";
    std ::cin >> profile;
    ofs << profile;
    
    std::cout << "Profile "<< profile << " successfully created and loaded!\n";
    return profile;
    
}

// Note: Only delete the profile file and not the credentials file
void DeleteProfile()
{
    if(remove("./profile"))
    {
        LOG(ERROR) << "Error deleting file";
    }
    else
    {
        std::cout << "Profile successfully deleted!\n";
    }
}