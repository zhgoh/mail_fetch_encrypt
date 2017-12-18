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
#ifndef  GOOGLE_GMAIL_API_FILTER_H_
#define  GOOGLE_GMAIL_API_FILTER_H_

#include <string>
#include "googleapis/base/macros.h"
#include "googleapis/client/data/jsoncpp_data.h"
#include "googleapis/strings/stringpiece.h"

#include "google/gmail_api/filter_action.h"
#include "google/gmail_api/filter_criteria.h"

namespace Json {
class Value;
}  // namespace Json

namespace google_gmail_api {
using namespace googleapis;

/**
 * Resource definition for Gmail filters. Filters apply to specific messages
 * instead of an entire email thread.
 *
 * @ingroup DataObject
 */
class Filter : public client::JsonCppData {
 public:
  /**
   * Creates a new default instance.
   *
   * @return Ownership is passed back to the caller.
   */
  static Filter* New();

  /**
   * Standard constructor for an immutable data object instance.
   *
   * @param[in] storage  The underlying data storage for this instance.
   */
  explicit Filter(const Json::Value& storage);

  /**
   * Standard constructor for a mutable data object instance.
   *
   * @param[in] storage  The underlying data storage for this instance.
   */
  explicit Filter(Json::Value* storage);

  /**
   * Standard destructor.
   */
  virtual ~Filter();

  /**
   * Returns a string denoting the type of this data object.
   *
   * @return <code>google_gmail_api::Filter</code>
   */
  const StringPiece GetTypeName() const {
    return StringPiece("google_gmail_api::Filter");
  }

  /**
   * Determine if the '<code>action</code>' attribute was set.
   *
   * @return true if the '<code>action</code>' attribute was set.
   */
  bool has_action() const {
    return Storage().isMember("action");
  }

  /**
   * Clears the '<code>action</code>' attribute.
   */
  void clear_action() {
    MutableStorage()->removeMember("action");
  }


  /**
   * Get a reference to the value of the '<code>action</code>' attribute.
   */
  const FilterAction get_action() const;

  /**
   * Gets a reference to a mutable value of the '<code>action</code>' property.
   *
   * Action that the filter performs.
   *
   * @return The result can be modified to change the attribute value.
   */
  FilterAction mutable_action();

  /**
   * Determine if the '<code>criteria</code>' attribute was set.
   *
   * @return true if the '<code>criteria</code>' attribute was set.
   */
  bool has_criteria() const {
    return Storage().isMember("criteria");
  }

  /**
   * Clears the '<code>criteria</code>' attribute.
   */
  void clear_criteria() {
    MutableStorage()->removeMember("criteria");
  }


  /**
   * Get a reference to the value of the '<code>criteria</code>' attribute.
   */
  const FilterCriteria get_criteria() const;

  /**
   * Gets a reference to a mutable value of the '<code>criteria</code>'
   * property.
   *
   * Matching criteria for the filter.
   *
   * @return The result can be modified to change the attribute value.
   */
  FilterCriteria mutable_criteria();

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
   * The server assigned ID of the filter.
   *
   * @param[in] value The new value.
   */
  void set_id(const StringPiece& value) {
    *MutableStorage("id") = value.data();
  }

 private:
  void operator=(const Filter&);
};  // Filter
}  // namespace google_gmail_api
#endif  // GOOGLE_GMAIL_API_FILTER_H_
