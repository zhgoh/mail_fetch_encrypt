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
#ifndef  GOOGLE_GMAIL_API_LIST_HISTORY_RESPONSE_H_
#define  GOOGLE_GMAIL_API_LIST_HISTORY_RESPONSE_H_

#include <string>
#include "googleapis/base/integral_types.h"
#include "googleapis/base/macros.h"
#include "googleapis/client/data/jsoncpp_data.h"
#include "googleapis/strings/stringpiece.h"

#include "google/gmail_api/history.h"

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
    class ListHistoryResponse : public client::JsonCppData
    {
    public:
        /**
         * Creates a new default instance.
         *
         * @return Ownership is passed back to the caller.
         */
        static ListHistoryResponse *New();

        /**
         * Standard constructor for an immutable data object instance.
         *
         * @param[in] storage  The underlying data storage for this instance.
         */
        explicit ListHistoryResponse(const Json::Value &storage);

        /**
         * Standard constructor for a mutable data object instance.
         *
         * @param[in] storage  The underlying data storage for this instance.
         */
        explicit ListHistoryResponse(Json::Value *storage);

        /**
         * Standard destructor.
         */
        virtual ~ListHistoryResponse();

        /**
         * Returns a string denoting the type of this data object.
         *
         * @return <code>google_gmail_api::ListHistoryResponse</code>
         */
        const StringPiece GetTypeName() const
        {
            return StringPiece("google_gmail_api::ListHistoryResponse");
        }

        /**
         * Determine if the '<code>history</code>' attribute was set.
         *
         * @return true if the '<code>history</code>' attribute was set.
         */
        bool has_history() const
        {
            return Storage().isMember("history");
        }

        /**
         * Clears the '<code>history</code>' attribute.
         */
        void clear_history()
        {
            MutableStorage()->removeMember("history");
        }


        /**
         * Get a reference to the value of the '<code>history</code>' attribute.
         */
        const client::JsonCppArray<History> get_history() const;

        /**
         * Gets a reference to a mutable value of the '<code>history</code>' property.
         *
         * List of history records. Any messages contained in the response will
         * typically only have id and threadId fields populated.
         *
         * @return The result can be modified to change the attribute value.
         */
        client::JsonCppArray<History> mutable_history();

        /**
         * Determine if the '<code>historyId</code>' attribute was set.
         *
         * @return true if the '<code>historyId</code>' attribute was set.
         */
        bool has_history_id() const
        {
            return Storage().isMember("historyId");
        }

        /**
         * Clears the '<code>historyId</code>' attribute.
         */
        void clear_history_id()
        {
            MutableStorage()->removeMember("historyId");
        }


        /**
         * Get the value of the '<code>historyId</code>' attribute.
         */
        uint64 get_history_id() const
        {
            const Json::Value &storage = Storage("historyId");
            return client::JsonValueToCppValueHelper<uint64>(storage);
        }

        /**
         * Change the '<code>historyId</code>' attribute.
         *
         * The ID of the mailbox's current history record.
         *
         * @param[in] value The new value.
         */
        void set_history_id(uint64 value)
        {
            client::SetJsonValueFromCppValueHelper<uint64>(
                    value, MutableStorage("historyId"));
        }

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
         * Page token to retrieve the next page of results in the list.
         *
         * @param[in] value The new value.
         */
        void set_next_page_token(const StringPiece &value)
        {
            *MutableStorage("nextPageToken") = value.data();
        }

    private:
        void operator=(const ListHistoryResponse &);
    };  // ListHistoryResponse
}  // namespace google_gmail_api
#endif  // GOOGLE_GMAIL_API_LIST_HISTORY_RESPONSE_H_
