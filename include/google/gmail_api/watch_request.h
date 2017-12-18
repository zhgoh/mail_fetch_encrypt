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
#ifndef  GOOGLE_GMAIL_API_WATCH_REQUEST_H_
#define  GOOGLE_GMAIL_API_WATCH_REQUEST_H_

#include <string>
#include "googleapis/base/macros.h"
#include "googleapis/client/data/jsoncpp_data.h"
#include "googleapis/strings/stringpiece.h"

namespace Json {
class Value;
}  // namespace Json

namespace google_gmail_api {
using namespace googleapis;

/**
 * Set up or update a new push notification watch on this user's mailbox.
 *
 * @ingroup DataObject
 */
class WatchRequest : public client::JsonCppData {
 public:
  /**
   * Creates a new default instance.
   *
   * @return Ownership is passed back to the caller.
   */
  static WatchRequest* New();

  /**
   * Standard constructor for an immutable data object instance.
   *
   * @param[in] storage  The underlying data storage for this instance.
   */
  explicit WatchRequest(const Json::Value& storage);

  /**
   * Standard constructor for a mutable data object instance.
   *
   * @param[in] storage  The underlying data storage for this instance.
   */
  explicit WatchRequest(Json::Value* storage);

  /**
   * Standard destructor.
   */
  virtual ~WatchRequest();

  /**
   * Returns a string denoting the type of this data object.
   *
   * @return <code>google_gmail_api::WatchRequest</code>
   */
  const StringPiece GetTypeName() const {
    return StringPiece("google_gmail_api::WatchRequest");
  }

  /**
   * Determine if the '<code>labelFilterAction</code>' attribute was set.
   *
   * @return true if the '<code>labelFilterAction</code>' attribute was set.
   */
  bool has_label_filter_action() const {
    return Storage().isMember("labelFilterAction");
  }

  /**
   * Clears the '<code>labelFilterAction</code>' attribute.
   */
  void clear_label_filter_action() {
    MutableStorage()->removeMember("labelFilterAction");
  }


  /**
   * Get the value of the '<code>labelFilterAction</code>' attribute.
   */
  const StringPiece get_label_filter_action() const {
    const Json::Value& v = Storage("labelFilterAction");
    if (v == Json::Value::null) return StringPiece("");
    return StringPiece(v.asCString());
  }

  /**
   * Change the '<code>labelFilterAction</code>' attribute.
   *
   * Filtering behavior of labelIds list specified.
   *
   * @param[in] value The new value.
   */
  void set_label_filter_action(const StringPiece& value) {
    *MutableStorage("labelFilterAction") = value.data();
  }

  /**
   * Determine if the '<code>labelIds</code>' attribute was set.
   *
   * @return true if the '<code>labelIds</code>' attribute was set.
   */
  bool has_label_ids() const {
    return Storage().isMember("labelIds");
  }

  /**
   * Clears the '<code>labelIds</code>' attribute.
   */
  void clear_label_ids() {
    MutableStorage()->removeMember("labelIds");
  }


  /**
   * Get a reference to the value of the '<code>labelIds</code>' attribute.
   */
  const client::JsonCppArray<string > get_label_ids() const {
     const Json::Value& storage = Storage("labelIds");
    return client::JsonValueToCppValueHelper<client::JsonCppArray<string > >(storage);
  }

  /**
   * Gets a reference to a mutable value of the '<code>labelIds</code>'
   * property.
   *
   * List of label_ids to restrict notifications about. By default, if
   * unspecified, all changes are pushed out. If specified then dictates which
   * labels are required for a push notification to be generated.
   *
   * @return The result can be modified to change the attribute value.
   */
  client::JsonCppArray<string > mutable_labelIds() {
    Json::Value* storage = MutableStorage("labelIds");
    return client::JsonValueToMutableCppValueHelper<client::JsonCppArray<string > >(storage);
  }

  /**
   * Determine if the '<code>topicName</code>' attribute was set.
   *
   * @return true if the '<code>topicName</code>' attribute was set.
   */
  bool has_topic_name() const {
    return Storage().isMember("topicName");
  }

  /**
   * Clears the '<code>topicName</code>' attribute.
   */
  void clear_topic_name() {
    MutableStorage()->removeMember("topicName");
  }


  /**
   * Get the value of the '<code>topicName</code>' attribute.
   */
  const StringPiece get_topic_name() const {
    const Json::Value& v = Storage("topicName");
    if (v == Json::Value::null) return StringPiece("");
    return StringPiece(v.asCString());
  }

  /**
   * Change the '<code>topicName</code>' attribute.
   *
   * A fully qualified Google Cloud Pub/Sub API topic name to publish the events
   * to. This topic name **must** already exist in Cloud Pub/Sub and you
   * **must** have already granted gmail "publish" permission on it. For
   * example, "projects/my-project-identifier/topics/my-topic-name" (using the
   * Cloud Pub/Sub "v1" topic naming format).
   *
   * Note that the "my-project-identifier" portion must exactly match your
   * Google developer project id (the one executing this watch request).
   *
   * @param[in] value The new value.
   */
  void set_topic_name(const StringPiece& value) {
    *MutableStorage("topicName") = value.data();
  }

 private:
  void operator=(const WatchRequest&);
};  // WatchRequest
}  // namespace google_gmail_api
#endif  // GOOGLE_GMAIL_API_WATCH_REQUEST_H_