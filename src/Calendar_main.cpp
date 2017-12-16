/*
 * \copyright Copyright 2013 Google Inc. All Rights Reserved.
 * \license @{
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * @}
 */

//
// This is a sample application illustrating the use of the GoogleApis C++
// Client. The application makes calls into the Google Calendar service.
// The application itself is not particularly useful, rather it just
// illustrates how to interact with a live service.
//
// Usage:
//
// Calendar requires OAuth2 authorization, which in turn requires that the
// application be authorized using the https://code.google.com/apis/console.
// You will need to do this yourself -- creating your own client ID and
// secret in order to run it.
//
// For this example, you want to create an Installed Application
//    From the "API Access" tab, create an "Installed Application" client ID
//       Download the client secrets JSON file.
//    From the "Services" tab, give access to the Calendar API.
//
// If you already know the ID and secret, you can create the json file yourself
// from teh following example (including outer {}). Replace the "..." with
// your values, but be sure to quote them  (i.e. "mysecret" }
// {
//    "installed": {
//       "client_id": "...",
//       "client_secret": "..."
//    }
//  }
//
//
// When the program starts up you will be asked to authorize by copying
// a URL into a browser and copying the response back. From there the
// program executes a shell that takes commands. Type 'help' for a list
// of current commands and 'quit' to exit.

#include <iostream>
#include "googleapis/client/util/status.h"
#include "sample/calendar/CalendarSample.h"

int main(int argc, char* argv[]) 
{
  googleapis::util::Status status = googleapis::CalendarSample::Startup(argc, argv);
  if (!status.ok()) 
  {
    std::cerr << "Could not initialize application." << std::endl;
    std::cerr << status.error_message() << std::endl;
    return -1;
  }

  googleapis::CalendarSample sample;
  sample.Run();
  std::cout << "Done!" << std::endl;

  return 0;
}
