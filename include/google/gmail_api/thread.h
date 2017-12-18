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
#ifndef  GOOGLE_GMAIL_API_THREAD_H_
#define  GOOGLE_GMAIL_API_THREAD_H_

#include <string>
#include "googleapis/base/integral_types.h"
#include "googleapis/base/macros.h"
#include "googleapis/client/data/jsoncpp_data.h"
#include "googleapis/strings/stringpiece.h"

#include "google/gmail_api/message.h"

namespace Json {
class Value;
}  // namespace Json

namespace google_gmail_api {
using namespace googleapis;

/**
 * A collection of messages representing a conversation.
 *
 * @ingroup DataObject
 */
class Thread : public client::JsonCppData {
 public:
  /**
   * Creates a new default instance.
   *
   * @return Ownership is passed back to the caller.
   */
  static Thread* New();

  /**
   * Standard constructor for an immutable data object instance.
   *
   * @param[in] storage  The underlying data storage for this instance.
   */
  explicit Thread(const Json::Value& storage);

  /**
   * Standard constructor for a mutable data object instance.
   *
   * @param[in] storage  The underlying data storage for this instance.
   */
  explicit Thread(Json::Value* storage);

  /**
   * Standard destructor.
   */
  virtual ~Thread();

  /**
   * Returns a string denoting the type of this data object.
   *
   * @return <code>google_gmail_api::Thread</code>
   */
  const StringPiece GetTypeName() const {
    return StringPiece("google_gmail_api::Thread");
  }

  /**
   * Determine if the '<code>historyId</code>' attribute was set.
   *
   * @return true if the '<code>historyId</code>' attribute was set.
   */
  bool has_history_id() const {
    return Storage().isMember("historyId");
  }

  /**
   * Clears the '<code>historyId</code>' attribute.
   */
  void clear_history_id() {
    MutableStorage()->removeMember("historyId");
  }


  /**
   * Get the value of the '<code>historyId</code>' attribute.
   */
  uint64 get_history_id() const {
    const Json::Value& storage = Storage("historyId");
    return client::JsonValueToCppValueHelper<uint64 >(storage);
  }

  /**
   * Change the '<code>historyId</code>' attribute.
   *
   * The ID of the last history record that modified this thread.
   *
   * @param[in] value The new value.
   */
  void set_history_id(uint64 value) {
    client::SetJsonValueFromCppValueHelper<uint64 >(
      value, MutableStorage("historyId"));
  }

  /**
   * Determine if the '<code>id</code>' attribute was set.
   *
   * @return true if the '<code>id</code>' attribute was set.
   */
  bool has_id() const {
    return Storage().isMember("id");
  }

  /**
   * Clears the '<code>id</code>' attribute.
   */
  void clear_id() {
    MutableStorage()->removeMember("id");
  }


  /**
   * Get the value of the '<code>id</code>' attribute.
   */
  const StringPiece get_id() const {
    const Json::Value& v = Storage("id");
    if (v == Json::Value::null) return StringPiece("");
    return StringPiece(v.asCString());
  }

  /**
   * Change the '<code>id</code>' attribute.
   *
   * The unique ID of the thread.
   *
   * @param[in] value The new value.
   */
  void set_id(const StringPiece& value) {
    *MutableStorage("id") = value.data();
  }

  /**
   * Determine if the '<code>messages</code>' attribute was set.
   *
   * @return true if the '<code>messages</code>' attribute was set.
   */
  bool has_messages() const {
    return Storage().isMember("messages");
  }

  /**
   * Clears the '<code>messages</code>' attribute.
   */
  void clear_messages() {
    MutableStorage()->removeMember("messages");
  }


  /**
   * Get a reference to the value of the '<code>messages</code>' attribute.
   */
  const client::JsonCppArray<Message > get_messages() const;

  /**
   * Gets a reference to a mutable value of the '<code>messages</code>'
   * property.
   *
   * The list of messages in the thread.
   *
   * @return The result can be modified to change the attribute value.
   */
  client::JsonCppArray<Message > mutable_messages();

  /**
   * Determine if the '<code>snippet</code>' attribute was set.
   *
   * @return true if the '<code>snippet</code>' attribute was set.
   */
  bool has_snippet() const {
    return Storage().isMember("snippet");
  }

  /**
   * Clears the '<code>snippet</code>' attribute.
   */
  void clear_snippet() {
    MutableStorage()->removeMember("snippet");
  }


  /**
   * Get the value of the '<code>snippet</code>' attribute.
   */
  const StringPiece get_snippet() const {
    const Json::Value& v = Storage("snippet");
    if (v == Json::Value::null) return StringPiece("");
    return StringPiece(v.asCString());
  }

  /**
   * Change the '<code>snippet</code>' attribute.
   *
   * A short part of the message text.
   *
   * @param[in] value The new value.
   */
  void set_snippet(const StringPiece& value) {
    *MutableStorage("snippet") = value.data();
  }

 private:
  void operator=(const Thread&);
};  // Thread
}  // namespace google_gmail_api
#endif  // GOOGLE_GMAIL_API_THREAD_H_
