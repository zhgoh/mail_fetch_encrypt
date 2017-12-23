
#include "samples/calendar/CalendarSample.h"
#include "samples/calendar/Display.h"
#include "googleapis/client/transport/curl_http_transport.h"
#include "googleapis/client/transport/http_request_batch.h"
#include "googleapis/client/auth/file_credential_store.h"


const char kSampleStepPrefix[] = "SAMPLE:  ";

static googleapis::util::Status PromptShellForAuthorizationCode(
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

/* static */
googleapis::util::Status googleapis::CalendarSample::Startup(int argc, char *argv[])
{
    if ((argc < 2) || (argc > 3))
    {
        string error = googleapis::StrCat("Invalid Usage:\n", argv[0], " <client_secrets_file> [<cacerts_path>]\n");
        return googleapis::client::StatusInvalidArgument(error);
    }
    
    // Set up HttpTransportLayer.
    googleapis::util::Status status;
    config_ = std::make_unique<googleapis::client::HttpTransportLayerConfig>();
    googleapis::client::HttpTransportFactory *factory =
            new googleapis::client::CurlHttpTransportFactory(config_.get());
    config_->ResetDefaultTransportFactory(factory);
    if (argc > 2)
    {
        config_->mutable_default_transport_options()->set_cacerts_path(argv[2]);
    }
    
    // Set up OAuth 2.0 flow for getting credentials to access personal data.
    const string client_secrets_file = argv[1];
    flow_.reset(googleapis::client::OAuth2AuthorizationFlow::MakeFlowFromClientSecretsPath(
            client_secrets_file, config_->NewDefaultTransportOrDie(), &status));
    if (!status.ok())
        return status;
    
    flow_->set_default_scopes(google_calendar_api::CalendarService::SCOPES::CALENDAR);
    flow_->mutable_client_spec()->set_redirect_uri(
            googleapis::client::OAuth2AuthorizationFlow::kOutOfBandUrl);
    flow_->set_authorization_code_callback(
            NewPermanentCallback(&PromptShellForAuthorizationCode, flow_.get()));
    
    string home_path;
    status = googleapis::client::FileCredentialStoreFactory::GetSystemHomeDirectoryStorePath(&home_path);
    if (status.ok())
    {
        googleapis::client::FileCredentialStoreFactory store_factory(home_path);
        // Use a credential store to save the credentials between runs so that
        // we dont need to get permission again the next time we run. We are
        // going to encrypt the data in the store, but leave it to the OS to
        // protect access since we do not authenticate users in this sample.
#if HAVE_OPENSSL
        OpenSslCodecFactory* openssl_factory = new OpenSslCodecFactory;
        status = openssl_factory->SetPassphrase(
            flow_->client_spec().client_secret());
        if (!status.ok()) return status;
        store_factory.set_codec_factory(openssl_factory);
#endif
        
        flow_->ResetCredentialStore(
                store_factory.NewCredentialStore("CalendarSample", &status));
    }
    
    if (!status.ok())
        return status;
    
    // Now we'll initialize the calendar service proxy that we'll use
    // to interact with the calendar from this sample program.
    googleapis::client::HttpTransport *transport = config_->NewDefaultTransport(&status);
    if (!status.ok())
        return status;
    
    service_ = std::make_unique<google_calendar_api::CalendarService>(transport);
    return status;
}


googleapis::util::Status google_calendar_api::CalendarSample::Authorize()
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
    googleapis::util::Status status =
            flow_->RefreshCredentialWithOptions(options, &credential_);
    if (!status.ok())
    {
        return status;
    }
    
    credential_.set_flow(flow_.get());
    std::cout << "Authorized " << email << std::endl;
    return googleapis::client::StatusOk();
}


void googleapis::CalendarSample::ShowCalendars()
{
    std::unique_ptr<google_calendar_api::CalendarListResource_ListMethod> method(
            service_->get_calendar_list().NewListMethod(&credential_));
    
    std::unique_ptr<google_calendar_api::CalendarList> calendar_list(google_calendar_api::CalendarList::New());
    if (!method->ExecuteAndParseResponse(calendar_list.get()).ok())
    {
        DisplayError(method.get());
        return;
    }
    DisplayList<google_calendar_api::CalendarList, google_calendar_api::CalendarListEntry>(
            "", "CalendarList", *calendar_list);
    std::cout << std::endl;
}

string googleapis::CalendarSample::AddCalendar()
{
    std::unique_ptr<google_calendar_api::Calendar> calendar(google_calendar_api::Calendar::New());
    calendar->set_summary("Calendar added by CalendarSample");
    
    std::unique_ptr<google_calendar_api::CalendarsResource_InsertMethod> method(
            service_->get_calendars().NewInsertMethod(&credential_, *calendar));
    
    if (!method->ExecuteAndParseResponse(calendar.get()).ok())
    {
        DisplayError(method.get());
        return "";
    }
    
    string result = calendar->get_id().as_string();
    std::cout << "Added new calendar ID=" << result << ":" << std::endl;
    Display("  ", *calendar);
    std::cout << std::endl;
    
    return result;
}

void googleapis::CalendarSample::AddEvent(const string &calendar_id, google_calendar_api::Event *event)
{
    std::unique_ptr<google_calendar_api::EventsResource_InsertMethod> method(
            service_->get_events().NewInsertMethod(
                    &credential_, calendar_id, *event));
    
    if (!method->ExecuteAndParseResponse(event).ok())
    {
        DisplayError(method.get());
        return;
    }
    
    std::cout << "Added new event ID=" << event->get_id() << ":" << std::endl;
    Display("  ", *event);
    std::cout << std::endl;
}

void googleapis::CalendarSample::PageThroughAllEvents(
        const string &calendar_id, int num_per_page)
{
    std::cout << "All Events" << std::endl;
    std::unique_ptr<google_calendar_api::EventsResource_ListMethodPager> pager(
            service_->get_events().NewListMethodPager(&credential_, calendar_id));
    pager->request()->set_max_results(num_per_page);
    while (pager->NextPage())
    {
        DisplayList<google_calendar_api::Events, google_calendar_api::Event>("  ", "EventList", *pager->data());
    }
}


googleapis::util::Status googleapis::CalendarSample::GetEvent(
        const string &calendar_id, const string &event_id, google_calendar_api::Event *event)
{
    std::unique_ptr<google_calendar_api::EventsResource_GetMethod> method(
            service_->get_events().NewGetMethod(
                    &credential_, calendar_id, event_id));
    
    return method->ExecuteAndParseResponse(event);
}

void googleapis::CalendarSample::PatchEvent(
        const string &calendar_id, const google_calendar_api::Event &event)
{
    std::unique_ptr<google_calendar_api::EventsResource_PatchMethod> method(
            service_->get_events().NewPatchMethod(
                    &credential_, calendar_id, event.get_id(), event));
    
    if (!method->Execute().ok())
    {
        DisplayError(method.get());
        return;
    }
    
    std::unique_ptr<google_calendar_api::Event> cloud_event(google_calendar_api::Event::New());
    googleapis::util::Status status =
            GetEvent(calendar_id, event.get_id().as_string(), cloud_event.get());
    if (status.ok())
    {
        std::cout << "Patched event:" << std::endl;
        Display("  ", *cloud_event);
    }
    else
    {
        std::cout << "** Could not get patched event: " << status.error_message()
                  << std::endl;
    }
    std::cout << std::endl;
}

void googleapis::CalendarSample::UpdateEvent(
        const string &calendar_id, const google_calendar_api::Event &event)
{
    std::unique_ptr<google_calendar_api::EventsResource_UpdateMethod> method(
            service_->get_events().NewUpdateMethod(
                    &credential_, calendar_id, event.get_id(), event));
    
    if (!method->Execute().ok())
    {
        DisplayError(method.get());
        return;
    }
    
    std::unique_ptr<google_calendar_api::Event> cloud_event(google_calendar_api::Event::New());
    googleapis::util::Status status =
            GetEvent(calendar_id, event.get_id().as_string(), cloud_event.get());
    if (status.ok())
    {
        std::cout << "Updated event:" << std::endl;
        Display("  ", *cloud_event);
    }
    else
    {
        std::cout << "** Could not get updated event: " << status.error_message()
                  << std::endl;
    }
    std::cout << std::endl;
}

void googleapis::CalendarSample::DeleteCalendar(const string &id)
{
    std::unique_ptr<google_calendar_api::CalendarsResource_DeleteMethod> method(
            service_->get_calendars().NewDeleteMethod(&credential_, id));
    
    if (!method->Execute().ok())
    {
        DisplayError(method.get());
        return;
    }
    std::cout << "Deleted ID=" << id << std::endl;
    std::cout << std::endl;
}


void googleapis::CalendarSample::Run()
{
    std::cout << kSampleStepPrefix << "Getting User Authorization" << std::endl;
    googleapis::util::Status status = Authorize();
    if (!status.ok())
    {
        std::cout << "Could not authorize: " << status.error_message() << std::endl;
        return;
    }
    
    std::cout << std::endl
              << kSampleStepPrefix << "Showing Initial Calendars" << std::endl;
    ShowCalendars();
    
    std::cout << std::endl
              << kSampleStepPrefix << "Adding Calendar" << std::endl;
    string calendar_id = AddCalendar();
    
    std::cout << std::endl
              << kSampleStepPrefix << "Showing Updated Calendars" << std::endl;
    ShowCalendars();
    
    googleapis::client::DateTime now;
    std::unique_ptr<google_calendar_api::Event> event(google_calendar_api::Event::New());
    event->set_summary("Calendar event added by CalendarSample");
    event->mutable_start().set_date_time(now);
    event->mutable_end().set_date_time(googleapis::client::DateTime(now.ToEpochTime() + 60 * 60));
    
    std::cout << std::endl
              << kSampleStepPrefix << "Add Calendar Event" << std::endl;
    AddEvent(calendar_id, event.get());
    
    std::cout << std::endl
              << kSampleStepPrefix << "Patch Calendar Event" << std::endl;
    event->clear_start();
    event->clear_end();
    event->set_summary("Event patched by CalendarSample");
    PatchEvent(calendar_id, *event);
    
    std::cout << std::endl
              << kSampleStepPrefix << "Update Calendar Event" << std::endl;
    // An update requires a time.
    // Go back a year and one day to distinguish it from the old value.
    event->mutable_start().set_date_time(
            googleapis::client::DateTime(now.ToEpochTime() - 60 * 60 * 24 * 367));
    event->mutable_end().set_date_time(
            googleapis::client::DateTime(now.ToEpochTime() - 60 * 60 * 24 * 366));
    event->clear_summary();
    UpdateEvent(calendar_id, *event);
    
    std::cout << std::endl
              << "Adding bulk events using a batch request" << std::endl;
    googleapis::client::HttpRequestBatch batch(service_->transport(), service_->batch_url());
    batch.mutable_http_request()->set_credential(&credential_);
    
    for (int i = 0; i < 10; ++i)
    {
        std::unique_ptr<google_calendar_api::Event> the_event(google_calendar_api::Event::New());
        
        // Space the events at hour intervals with 15 minute durations.
        the_event->set_summary(googleapis::StrCat("Extra event ", i));
        the_event->mutable_start().set_date_time(
                googleapis::client::DateTime(now.ToEpochTime() + i * 60 * 60));
        the_event->mutable_end().set_date_time(
                googleapis::client::DateTime(now.ToEpochTime() + i * 60 * 60 + 15 * 60));
        
        google_calendar_api::EventsResource_InsertMethod *method(
                service_->get_events().NewInsertMethod(
                        &credential_, calendar_id, *the_event));
        
        method->ConvertIntoHttpRequestBatchAndDestroy(&batch);
    }
    
    status = batch.Execute();
    if (!status.ok())
    {
        std::cout << "Entire batch execution failed: " << status.error_message()
                  << std::endl;
    }
    for (int i = 0; i < 10; ++i)
    {
        googleapis::client::HttpResponse *response = batch.requests()[i]->response();
        if (!response->ok())
        {
            googleapis::string detail;
            if (response->body_reader())
            {
                detail = response->body_reader()->RemainderToString();
            }
            else
            {
                detail = "No response data available.";
            }
            std::cout << "Error adding batched event " << i << std::endl
                      << response->status().ToString() << std::endl
                      << detail << std::endl;
        }
    }
    
    PageThroughAllEvents(calendar_id, 7);
    std::cout << std::endl
              << kSampleStepPrefix << "Deleting Calendar" << std::endl;
    DeleteCalendar(calendar_id);
    
    std::cout << std::endl
              << kSampleStepPrefix << "Showing Final Calendars" << std::endl;
    ShowCalendars();
}

// static
std::unique_ptr<google_calendar_api::CalendarService> googleapis::CalendarSample::service_;
std::unique_ptr<googleapis::client::OAuth2AuthorizationFlow> googleapis::CalendarSample::flow_;
std::unique_ptr<googleapis::client::HttpTransportLayerConfig> googleapis::CalendarSample::config_;
