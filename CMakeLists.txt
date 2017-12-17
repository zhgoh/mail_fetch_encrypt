cmake_minimum_required (VERSION 3.1)
project (MailRetrieve)

set (CMAKE_CXX_STANDARD 11)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

# Bring the headers into the project
include_directories(include)

#For the static library:
# set ( PROJECT_LINK_LIBS 
#     google_calendar_api.a 
#     google_gmail_api.a
#     google_storage_api.a
#     googleapis_oauth2.a
#     googleapis_curl_http.a
#     googleapis_http.a
#     googleapis_jsonplayback.a
#     googleapis_scribes.a
#     jsoncpp.a
#     googleapis_jsoncpp.a
#     googleapis_json.a
#     googleapis_utils.a
#     pthread.a
#     curl.a
#     ssl.a
#     crypto.a
#     dl.a
#     googleapis_openssl_codec.a
#     glog.a
#     googleapis_internal.a
# )

set ( PROJECT_LINK_LIBS 
    google_calendar_api.a 
    google_gmail_api.a
    google_storage_api.a
    googleapis_oauth2.a
    googleapis_curl_http.a
    googleapis_http.a
    googleapis_jsonplayback.a
    googleapis_scribes.a
    jsoncpp.a
    googleapis_jsoncpp.a
    googleapis_json.a
    googleapis_utils.a
    curl.a
    ssl.a
    crypto.a
    googleapis_openssl_codec.a
    glog.a
    googleapis_internal.a
)

link_directories( lib )

set(SOURCES src/Calendar_main.cpp src/CalendarSample.cpp)
#file(GLOB SOURCES "src/*.cpp")
add_executable(main ${SOURCES})
target_link_libraries(main ${PROJECT_LINK_LIBS} pthread dl)