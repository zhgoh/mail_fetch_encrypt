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
#ifndef  GOOGLE_GMAIL_API_WATCH_RESPONSE_H_
#define  GOOGLE_GMAIL_API_WATCH_RESPONSE_H_

#include "googleapis/base/integral_types.h"
#include "googleapis/base/macros.h"
#include "googleapis/client/data/jsoncpp_data.h"
#include "googleapis/strings/stringpiece.h"

namespace Json
{
    class Value;
}  // namespace Json

namespace google_gmail_api
{
    using namespace googleapis;

/**
 * Push notification watch response.
 *
 * @ingroup DataObject
 */
    class WatchResponse : public client::JsonCppData
    {
    public:
        /**
         * Creates a new default instance.
         *
         * @return Ownership is passed back to the caller.
         */
        static WatchResponse *New();

        /**
         * Standard constructor for an immutable data object instance.
         *
         * @param[in] storage  The underlying data storage for this instance.
         */
        explicit WatchResponse(const Json::Value &storage);

        /**
         * Standard constructor for a mutable data object instance.
         *
         * @param[in] storage  The underlying data storage for this instance.
         */
        explicit WatchResponse(Json::Value *storage);

        /**
         * Standard destructor.
         */
        virtual ~WatchResponse();

        /**
         * Returns a string denoting the type of this data object.
         *
         * @return <code>google_gmail_api::WatchResponse</code>
         */
        const StringPiece GetTypeName() const
        {
            return StringPiece("google_gmail_api::WatchResponse");
        }

        /**
         * Determine if the '<code>expiration</code>' attribute was set.
         *
         * @return true if the '<code>expiration</code>' attribute was set.
         */
        bool has_expiration() const
        {
            return Storage().isMember("expiration");
        }

        /**
         * Clears the '<code>expiration</code>' attribute.
         */
        void clear_expiration()
        {
            MutableStorage()->removeMember("expiration");
        }


        /**
         * Get the value of the '<code>expiration</code>' attribute.
         */
        int64 get_expiration() const
        {
            const Json::Value &storage = Storage("expiration");
            return client::JsonValueToCppValueHelper<int64>(storage);
        }

        /**
         * Change the '<code>expiration</code>' attribute.
         *
         * When Gmail will stop sending notifications for mailbox updates (epoch
         * millis). Call watch again before this time to renew the watch.
         *
         * @param[in] value The new value.
         */
        void set_expiration(int64 value)
        {
            client::SetJsonValueFromCppValueHelper<int64>(
                    value, MutableStorage("expiration"));
        }

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

    private:
        void operator=(const WatchResponse &);
    };  // WatchResponse
}  // namespace google_gmail_api
#endif  // GOOGLE_GMAIL_API_WATCH_RESPONSE_H_
