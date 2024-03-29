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
#ifndef  GOOGLE_GMAIL_API_HISTORY_H_
#define  GOOGLE_GMAIL_API_HISTORY_H_

#include "googleapis/base/integral_types.h"
#include "googleapis/base/macros.h"
#include "googleapis/client/data/jsoncpp_data.h"
#include "googleapis/strings/stringpiece.h"

#include "google/gmail_api/history_label_added.h"
#include "google/gmail_api/history_label_removed.h"
#include "google/gmail_api/history_message_added.h"
#include "google/gmail_api/history_message_deleted.h"
#include "google/gmail_api/message.h"

namespace Json
{
    class Value;
}  // namespace Json

namespace google_gmail_api
{
    using namespace googleapis;

/**
 * A record of a change to the user's mailbox. Each history change may affect
 * multiple messages in multiple ways.
 *
 * @ingroup DataObject
 */
    class History : public client::JsonCppData
    {
    public:
        /**
         * Creates a new default instance.
         *
         * @return Ownership is passed back to the caller.
         */
        static History *New();

        /**
         * Standard constructor for an immutable data object instance.
         *
         * @param[in] storage  The underlying data storage for this instance.
         */
        explicit History(const Json::Value &storage);

        /**
         * Standard constructor for a mutable data object instance.
         *
         * @param[in] storage  The underlying data storage for this instance.
         */
        explicit History(Json::Value *storage);

        /**
         * Standard destructor.
         */
        virtual ~History();

        /**
         * Returns a string denoting the type of this data object.
         *
         * @return <code>google_gmail_api::History</code>
         */
        const StringPiece GetTypeName() const
        {
            return StringPiece("google_gmail_api::History");
        }

        /**
         * Determine if the '<code>id</code>' attribute was set.
         *
         * @return true if the '<code>id</code>' attribute was set.
         */
        bool has_id() const
        {
            return Storage().isMember("id");
        }

        /**
         * Clears the '<code>id</code>' attribute.
         */
        void clear_id()
        {
            MutableStorage()->removeMember("id");
        }


        /**
         * Get the value of the '<code>id</code>' attribute.
         */
        uint64 get_id() const
        {
            const Json::Value &storage = Storage("id");
            return client::JsonValueToCppValueHelper<uint64>(storage);
        }

        /**
         * Change the '<code>id</code>' attribute.
         *
         * The mailbox sequence ID.
         *
         * @param[in] value The new value.
         */
        void set_id(uint64 value)
        {
            client::SetJsonValueFromCppValueHelper<uint64>(
                    value, MutableStorage("id"));
        }

        /**
         * Determine if the '<code>labelsAdded</code>' attribute was set.
         *
         * @return true if the '<code>labelsAdded</code>' attribute was set.
         */
        bool has_labels_added() const
        {
            return Storage().isMember("labelsAdded");
        }

        /**
         * Clears the '<code>labelsAdded</code>' attribute.
         */
        void clear_labels_added()
        {
            MutableStorage()->removeMember("labelsAdded");
        }


        /**
         * Get a reference to the value of the '<code>labelsAdded</code>' attribute.
         */
        const client::JsonCppArray<HistoryLabelAdded> get_labels_added() const;

        /**
         * Gets a reference to a mutable value of the '<code>labelsAdded</code>'
         * property.
         *
         * Labels added to messages in this history record.
         *
         * @return The result can be modified to change the attribute value.
         */
        client::JsonCppArray<HistoryLabelAdded> mutable_labelsAdded();

        /**
         * Determine if the '<code>labelsRemoved</code>' attribute was set.
         *
         * @return true if the '<code>labelsRemoved</code>' attribute was set.
         */
        bool has_labels_removed() const
        {
            return Storage().isMember("labelsRemoved");
        }

        /**
         * Clears the '<code>labelsRemoved</code>' attribute.
         */
        void clear_labels_removed()
        {
            MutableStorage()->removeMember("labelsRemoved");
        }


        /**
         * Get a reference to the value of the '<code>labelsRemoved</code>' attribute.
         */
        const client::JsonCppArray<HistoryLabelRemoved> get_labels_removed() const;

        /**
         * Gets a reference to a mutable value of the '<code>labelsRemoved</code>'
         * property.
         *
         * Labels removed from messages in this history record.
         *
         * @return The result can be modified to change the attribute value.
         */
        client::JsonCppArray<HistoryLabelRemoved> mutable_labelsRemoved();

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
         * List of messages changed in this history record. The fields for specific
         * change types, such as messagesAdded may duplicate messages in this field.
         * We recommend using the specific change-type fields instead of this.
         *
         * @return The result can be modified to change the attribute value.
         */
        client::JsonCppArray<Message> mutable_messages();

        /**
         * Determine if the '<code>messagesAdded</code>' attribute was set.
         *
         * @return true if the '<code>messagesAdded</code>' attribute was set.
         */
        bool has_messages_added() const
        {
            return Storage().isMember("messagesAdded");
        }

        /**
         * Clears the '<code>messagesAdded</code>' attribute.
         */
        void clear_messages_added()
        {
            MutableStorage()->removeMember("messagesAdded");
        }


        /**
         * Get a reference to the value of the '<code>messagesAdded</code>' attribute.
         */
        const client::JsonCppArray<HistoryMessageAdded> get_messages_added() const;

        /**
         * Gets a reference to a mutable value of the '<code>messagesAdded</code>'
         * property.
         *
         * Messages added to the mailbox in this history record.
         *
         * @return The result can be modified to change the attribute value.
         */
        client::JsonCppArray<HistoryMessageAdded> mutable_messagesAdded();

        /**
         * Determine if the '<code>messagesDeleted</code>' attribute was set.
         *
         * @return true if the '<code>messagesDeleted</code>' attribute was set.
         */
        bool has_messages_deleted() const
        {
            return Storage().isMember("messagesDeleted");
        }

        /**
         * Clears the '<code>messagesDeleted</code>' attribute.
         */
        void clear_messages_deleted()
        {
            MutableStorage()->removeMember("messagesDeleted");
        }


        /**
         * Get a reference to the value of the '<code>messagesDeleted</code>'
         * attribute.
         */
        const client::JsonCppArray<HistoryMessageDeleted> get_messages_deleted() const;

        /**
         * Gets a reference to a mutable value of the '<code>messagesDeleted</code>'
         * property.
         *
         * Messages deleted (not Trashed) from the mailbox in this history record.
         *
         * @return The result can be modified to change the attribute value.
         */
        client::JsonCppArray<HistoryMessageDeleted> mutable_messagesDeleted();

    private:
        void operator=(const History &);
    };  // History
}  // namespace google_gmail_api
#endif  // GOOGLE_GMAIL_API_HISTORY_H_
