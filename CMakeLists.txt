cmake_minimum_required (VERSION 3.1)
project (MailRetrieve)

set(CMAKE_CXX_STANDARD 14)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(USE_LIB true)

file(MAKE_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}/messages/enc)
file(MAKE_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}/messages/dec)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data/secrets.json DESTINATION ${EXECUTABLE_OUTPUT_PATH}/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data/rsa_pubkey.pem DESTINATION ${EXECUTABLE_OUTPUT_PATH}/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data/rsa_privkey.pem DESTINATION ${EXECUTABLE_OUTPUT_PATH}/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data/roots.pem DESTINATION ${EXECUTABLE_OUTPUT_PATH}/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/README.md DESTINATION ${EXECUTABLE_OUTPUT_PATH}/)


# Bring the headers into the project
include_directories(include)
link_directories(lib)

# Compile my cpp files
set(SOURCES src/main.cpp src/Client.cpp src/Display.cpp src/MyCrypt.cpp)
#set(SOURCES src/samples/calendar/Calendar_main.cpp src/samples/calendar/CalendarSample.cpp)

if(USE_LIB)
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
file(GLOB_RECURSE google_api_src "src/googleapis/*.cc")
file(GLOB_RECURSE google_service_src "src/google/gmail_api/*.cc")
else()
set (   PROJECT_LINK_LIBS
        jsoncpp.a
        curl.a
        ssl.a
        crypto.a
        glog.a
        )
endif()

# Compile the google service headers
#file(GLOB google_headers
#        "include/google/gmail_api/*.h")

if(USE_LIB)
add_executable(MailRetrieve ${SOURCES})
target_link_libraries(MailRetrieve ${PROJECT_LINK_LIBS} pthread dl)
else()
add_executable(MailRetrieve ${google_api_src} ${google_service_src} ${SOURCES})
target_link_libraries(MailRetrieve ${PROJECT_LINK_LIBS} pthread dl)
endif()
