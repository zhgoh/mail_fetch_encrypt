cmake_minimum_required (VERSION 3.1)
project (MailRetrieve)

set (CMAKE_CXX_STANDARD 14)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/certs/roots.pem DESTINATION ${EXECUTABLE_OUTPUT_PATH}/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/certs/README DESTINATION ${EXECUTABLE_OUTPUT_PATH}/)

# Bring the headers into the project
include_directories(include)

set (   PROJECT_LINK_LIBS
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

# Compile the google service headers
#file(GLOB google_headers
#        "include/google/gmail_api/*.h")

# Compile my cpp files
set(SOURCES src/main.cpp src/Client.cpp)
#set(SOURCES src/samples/calendar/Calendar_main.cpp src/samples/calendar/CalendarSample.cpp)

add_executable(Acronis_Mail ${SOURCES})
target_link_libraries(Acronis_Mail ${PROJECT_LINK_LIBS} pthread dl)