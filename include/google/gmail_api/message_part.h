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
#ifndef  GOOGLE_GMAIL_API_MESSAGE_PART_H_
#define  GOOGLE_GMAIL_API_MESSAGE_PART_H_

#include <string>
#include "googleapis/base/macros.h"
#include "googleapis/client/data/jsoncpp_data.h"
#include "googleapis/strings/stringpiece.h"

#include "google/gmail_api/message_part.h"
#include "google/gmail_api/message_part_body.h"
#include "google/gmail_api/message_part_header.h"

namespace Json
{
    class Value;
}  // namespace Json

namespace google_gmail_api
{
    using namespace googleapis;

/**
 * A single MIME message part.
 *
 * @ingroup DataObject
 */
    class MessagePart : public client::JsonCppData
    {
    public:
        /**
         * Creates a new default instance.
         *
         * @return Ownership is passed back to the caller.
         */
        static MessagePart *New();
        
        /**
         * Standard constructor for an immutable data object instance.
         *
         * @param[in] storage  The underlying data storage for this instance.
         */
        explicit MessagePart(const Json::Value &storage);
        
        /**
         * Standard constructor for a mutable data object instance.
         *
         * @param[in] storage  The underlying data storage for this instance.
         */
        explicit MessagePart(Json::Value *storage);
        
        /**
         * Standard destructor.
         */
        virtual ~MessagePart();
        
        /**
         * Returns a string denoting the type of this data object.
         *
         * @return <code>google_gmail_api::MessagePart</code>
         */
        const StringPiece GetTypeName() const
        {
            return StringPiece("google_gmail_api::MessagePart");
        }
        
        /**
         * Determine if the '<code>body</code>' attribute was set.
         *
         * @return true if the '<code>body</code>' attribute was set.
         */
        bool has_body() const
        {
            return Storage().isMember("body");
        }
        
        /**
         * Clears the '<code>body</code>' attribute.
         */
        void clear_body()
        {
            MutableStorage()->removeMember("body");
        }
        
        
        /**
         * Get a reference to the value of the '<code>body</code>' attribute.
         */
        const MessagePartBody get_body() const;
        
        /**
         * Gets a reference to a mutable value of the '<code>body</code>' property.
         *
         * The message part body for this part, which may be empty for container MIME
         * message parts.
         *
         * @return The result can be modified to change the attribute value.
         */
        MessagePartBody mutable_body();
        
        /**
         * Determine if the '<code>filename</code>' attribute was set.
         *
         * @return true if the '<code>filename</code>' attribute was set.
         */
        bool has_filename() const
        {
            return Storage().isMember("filename");
        }
        
        /**
         * Clears the '<code>filename</code>' attribute.
         */
        void clear_filename()
        {
            MutableStorage()->removeMember("filename");
        }
        
        
        /**
         * Get the value of the '<code>filename</code>' attribute.
         */
        const StringPiece get_filename() const
        {
            const Json::Value &v = Storage("filename");
            if (v == Json::Value::null) return StringPiece("");
            return StringPiece(v.asCString());
        }
        
        /**
         * Change the '<code>filename</code>' attribute.
         *
         * The filename of the attachment. Only present if this message part
         * represents an attachment.
         *
         * @param[in] value The new value.
         */
        void set_filename(const StringPiece &value)
        {
            *MutableStorage("filename") = value.data();
        }
        
        /**
         * Determine if the '<code>headers</code>' attribute was set.
         *
         * @return true if the '<code>headers</code>' attribute was set.
         */
        bool has_headers() const
        {
            return Storage().isMember("headers");
        }
        
        /**
         * Clears the '<code>headers</code>' attribute.
         */
        void clear_headers()
        {
            MutableStorage()->removeMember("headers");
        }
        
        
        /**
         * Get a reference to the value of the '<code>headers</code>' attribute.
         */
        const client::JsonCppArray<MessagePartHeader> get_headers() const;
        
        /**
         * Gets a reference to a mutable value of the '<code>headers</code>' property.
         *
         * List of headers on this message part. For the top-level message part,
         * representing the entire message payload, it will contain the standard RFC
         * 2822 email headers such as To, From, and Subject.
         *
         * @return The result can be modified to change the attribute value.
         */
        client::JsonCppArray<MessagePartHeader> mutable_headers();
        
        /**
         * Determine if the '<code>mimeType</code>' attribute was set.
         *
         * @return true if the '<code>mimeType</code>' attribute was set.
         */
        bool has_mime_type() const
        {
            return Storage().isMember("mimeType");
        }
        
        /**
         * Clears the '<code>mimeType</code>' attribute.
         */
        void clear_mime_type()
        {
            MutableStorage()->removeMember("mimeType");
        }
        
        
        /**
         * Get the value of the '<code>mimeType</code>' attribute.
         */
        const StringPiece get_mime_type() const
        {
            const Json::Value &v = Storage("mimeType");
            if (v == Json::Value::null) return StringPiece("");
            return StringPiece(v.asCString());
        }
        
        /**
         * Change the '<code>mimeType</code>' attribute.
         *
         * The MIME type of the message part.
         *
         * @param[in] value The new value.
         */
        void set_mime_type(const StringPiece &value)
        {
            *MutableStorage("mimeType") = value.data();
        }
        
        /**
         * Determine if the '<code>partId</code>' attribute was set.
         *
         * @return true if the '<code>partId</code>' attribute was set.
         */
        bool has_part_id() const
        {
            return Storage().isMember("partId");
        }
        
        /**
         * Clears the '<code>partId</code>' attribute.
         */
        void clear_part_id()
        {
            MutableStorage()->removeMember("partId");
        }
        
        
        /**
         * Get the value of the '<code>partId</code>' attribute.
         */
        const StringPiece get_part_id() const
        {
            const Json::Value &v = Storage("partId");
            if (v == Json::Value::null) return StringPiece("");
            return StringPiece(v.asCString());
        }
        
        /**
         * Change the '<code>partId</code>' attribute.
         *
         * The immutable ID of the message part.
         *
         * @param[in] value The new value.
         */
        void set_part_id(const StringPiece &value)
        {
            *MutableStorage("partId") = value.data();
        }
        
        /**
         * Determine if the '<code>parts</code>' attribute was set.
         *
         * @return true if the '<code>parts</code>' attribute was set.
         */
        bool has_parts() const
        {
            return Storage().isMember("parts");
        }
        
        /**
         * Clears the '<code>parts</code>' attribute.
         */
        void clear_parts()
        {
            MutableStorage()->removeMember("parts");
        }
        
        
        /**
         * Get a reference to the value of the '<code>parts</code>' attribute.
         */
        const client::JsonCppArray<MessagePart> get_parts() const;
        
        /**
         * Gets a reference to a mutable value of the '<code>parts</code>' property.
         *
         * The child MIME message parts of this part. This only applies to container
         * MIME message parts, for example multipart. For non- container MIME message
         * part types, such as text/plain, this field is empty. For more information,
         * see RFC 1521.
         *
         * @return The result can be modified to change the attribute value.
         */
        client::JsonCppArray<MessagePart> mutable_parts();
    
    private:
        void operator=(const MessagePart &);
    };  // MessagePart
}  // namespace google_gmail_api
#endif  // GOOGLE_GMAIL_API_MESSAGE_PART_H_
