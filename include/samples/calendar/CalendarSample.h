#ifndef CALENDERSAMPLE
#define CALENDERSAMPLE

#include <memory>
#include "googleapis/client/auth/oauth2_authorization.h"
#include "google/calendar_api/calendar_service.h"
#include "googleapis/client/transport/http_transport.h"

namespace google_calendar_api
{
    class Event;
}

namespace googleapis
{
    class CalendarSample 
    {
    public:
    static googleapis::util::Status Startup(int argc, char* argv[]);
    void Run();

    private:
    // Gets authorization to access the user's personal calendar data.
    googleapis::util::Status Authorize();

    // Prints some current calendar data to the console to show the effects
    // from the calls that the sample has made.
    void ShowCalendars();

    // Demonstrates adding a new resource. For this example, it is a calendar.
    // Returns a proxy to the calendar added in the Calendar Service (cloud).
    // We only really need the ID so that's all we return.
    googleapis::string AddCalendar();

    // Demonstrates adding an embedded resource.
    // For this example it is a calendar event.
    //
    // This takes a calendar ID such as that returned by AddCalendar().
    // We'll take a configured event as input and modify its ID with the
    // ID assigned by the Calendar Service (cloud). We could have just returned
    // the ID as in the case of Calendar but we are doing it differently for
    // demonstration purposes.
    void AddEvent(const string& calendar_id, google_calendar_api::Event* event);

    // Demonstrates using a ServiceRequestPager to list all the events on the
    // given calendar.
    void PageThroughAllEvents(const string& calendar_id, int events_per_page);

    // Demonstrates deleting a resource. For this example, it is a calendar.
    // We are deleting the calendar in the Calendar Service (cloud) that
    // has the given calendar_id.
    void DeleteCalendar(const string& calendar_id);

    // Demonstrates getting a resource.
    // For this example, it is a calendar event.
    // Returns the final status for the request. If not ok() then event wasn't
    // populated.
    googleapis::util::Status GetEvent(
        const string& calendar_id, const string& event_id, google_calendar_api::Event* event);

    // Demonstrates patching a resource.
    // For this example, it is a calendar event.
    void PatchEvent(const string& calendar_id, const google_calendar_api::Event& event);

    // Demonstrates updating a resource.
    // For this example, it is a calendar event.
    void UpdateEvent(const string& calendar_id, const google_calendar_api::Event& event);

    googleapis::client::OAuth2Credential credential_;
    static std::unique_ptr<google_calendar_api::CalendarService> service_;
    static std::unique_ptr<googleapis::client::OAuth2AuthorizationFlow> flow_;
    static std::unique_ptr<googleapis::client::HttpTransportLayerConfig> config_;
    };
}
#endif