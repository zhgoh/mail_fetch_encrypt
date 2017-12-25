// Copyright 2010 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License"); you may not
// use this file except in compliance with the License. You may obtain a copy of
// the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
// WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
// License for the specific language governing permissions and limitations under
// the License.

// This code was generated by google-apis-code-generator 1.5.1
//   Build date: 2017-11-07 19:12:12 UTC
//   on: 2017-12-15, 21:53:31 UTC
//   C++ generator version: 0.1.4

// ----------------------------------------------------------------------------
// NOTE: This file is generated from Google APIs Discovery Service.
// Service:
//   Gmail API (gmail/v1)
// Generated from:
//   Version: v1
//   Revision: 76
// Generated by:
//    Tool: google-apis-code-generator 1.5.1
//     C++: 0.1.4
#ifndef  GOOGLE_GMAIL_API_LIST_MESSAGES_RESPONSE_H_
#define  GOOGLE_GMAIL_API_LIST_MESSAGES_RESPONSE_H_

#include <string>
#include "googleapis/base/integral_types.h"
#include "googleapis/base/macros.h"
#include "googleapis/client/data/jsoncpp_data.h"
#include "googleapis/strings/stringpiece.h"

#include "google/gmail_api/message.h"

namespace Json
{
    class Value;
}  // namespace Json

namespace google_gmail_api
{
    using namespace googleapis;

/**
 * No description provided.
 *
 * @ingroup DataObject
 */
    class ListMessagesResponse : public client::JsonCppData
    {
    public:
        /**
         * Creates a new default instance.
         *
         * @return Ownership is passed back to the caller.
         */
        static ListMessagesResponse *New();
        
        /**
         * Standard constructor for an immutable data object instance.
         *
         * @param[in] storage  The underlying data storage for this instance.
         */
        explicit ListMessagesResponse(const Json::Value &storage);
        
        /**
         * Standard constructor for a mutable data object instance.
         *
         * @param[in] storage  The underlying data storage for this instance.
         */
        explicit ListMessagesResponse(Json::Value *storage);
        
        /**
         * Standard destructor.
         */
        virtual ~ListMessagesResponse();
        
        /**
         * Returns a string denoting the type of this data object.
         *
         * @return <code>google_gmail_api::ListMessagesResponse</code>
         */
        const StringPiece GetTypeName() const
        {
            return StringPiece("google_gmail_api::ListMessagesResponse");
        }
        
        /**
         * Determine if the '<code>messages</code>' attribute was set.
         *
         * @return true if the '<code>messages</code>' attribute was set.
         */
        bool has_messages() const
        {
            return Storage().isMember("messages");
        }
        
        /**
         * Clears the '<code>messages</code>' attribute.
         */
        void clear_messages()
        {
            MutableStorage()->removeMember("messages");
        }
        
        
        /**
         * Get a reference to the value of the '<code>messages</code>' attribute.
         */
        const client::JsonCppArray<Message> get_messages() const;
        
        /**
         * Gets a reference to a mutable value of the '<code>messages</code>'
         * property.
         *
         * List of messages.
         *
         * @return The result can be modified to change the attribute value.
         */
        client::JsonCppArray<Message> mutable_messages();
        
        /**
         * Determine if the '<code>nextPageToken</code>' attribute was set.
         *
         * @return true if the '<code>nextPageToken</code>' attribute was set.
         */
        bool has_next_page_token() const
        {
            return Storage().isMember("nextPageToken");
        }
        
        /**
         * Clears the '<code>nextPageToken</code>' attribute.
         */
        void clear_next_page_token()
        {
            MutableStorage()->removeMember("nextPageToken");
        }
        
        
        /**
         * Get the value of the '<code>nextPageToken</code>' attribute.
         */
        const StringPiece get_next_page_token() const
        {
            const Json::Value &v = Storage("nextPageToken");
            if (v == Json::Value::null) return StringPiece("");
            return StringPiece(v.asCString());
        }
        
        /**
         * Change the '<code>nextPageToken</code>' attribute.
         *
         * Token to retrieve the next page of results in the list.
         *
         * @param[in] value The new value.
         */
        void set_next_page_token(const StringPiece &value)
        {
            *MutableStorage("nextPageToken") = value.data();
        }
        
        /**
         * Determine if the '<code>resultSizeEstimate</code>' attribute was set.
         *
         * @return true if the '<code>resultSizeEstimate</code>' attribute was set.
         */
        bool has_result_size_estimate() const
        {
            return Storage().isMember("resultSizeEstimate");
        }
        
        /**
         * Clears the '<code>resultSizeEstimate</code>' attribute.
         */
        void clear_result_size_estimate()
        {
            MutableStorage()->removeMember("resultSizeEstimate");
        }
        
        
        /**
         * Get the value of the '<code>resultSizeEstimate</code>' attribute.
         */
        uint32 get_result_size_estimate() const
        {
            const Json::Value &storage = Storage("resultSizeEstimate");
            return client::JsonValueToCppValueHelper<uint32>(storage);
        }
        
        /**
         * Change the '<code>resultSizeEstimate</code>' attribute.
         *
         * Estimated total number of results.
         *
         * @param[in] value The new value.
         */
        void set_result_size_estimate(uint32 value)
        {
            client::SetJsonValueFromCppValueHelper<uint32>(
                    value, MutableStorage("resultSizeEstimate"));
        }
    
    private:
        void operator=(const ListMessagesResponse &);
    };  // ListMessagesResponse
}  // namespace google_gmail_api
#endif  // GOOGLE_GMAIL_API_LIST_MESSAGES_RESPONSE_H_
