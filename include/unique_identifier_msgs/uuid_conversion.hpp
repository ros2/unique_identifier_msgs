// Copyright 2024 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef UNIQUE_IDENTIFIER_MSGS__UUID_CONVERSION_HPP_
#define UNIQUE_IDENTIFIER_MSGS__UUID_CONVERSION_HPP_

#include "uuid/uuid.h"

#include <algorithm>
#include <string>

#include "unique_identifier_msgs/msg/uuid.hpp"

namespace unique_identifier_msgs
{
/** @brief Create UUID object from UUID ROS message.
 *
 *  @param msg unique_identifier_msgs/msg/UUID message.
 *  @returns uuid_t object.
 */
static inline void fromMsg(const msg::UUID & msg, uuid_t & uuid)
{
  std::copy(msg.uuid.begin(), msg.uuid.end(), std::begin(uuid));
}

/** @brief Create a UniqueID message from a UUID object.
 *
 *  @param uuid uuid_t object.
 *  @returns unique_identifier_msgs/msg/UUID message.
 */
static inline msg::UUID toMsg(const uuid_t & uuid)
{
  msg::UUID msg;
  std::copy(std::begin(uuid), std::end(uuid), msg.uuid.begin());
  return msg;
}

/** @brief Generate a random UUID object.
 *
 *  @returns unique_identifier_msgs/msg/UUID message.
 *
 *  Different calls to this function at any time or place will almost
 *  certainly generate different UUIDs. The method used is RFC 4122
 *  variant 4.
 */
static inline msg::UUID fromRandom()
{
  uuid_t uuid;
  uuid_generate_random(uuid);
  return toMsg(uuid);
}

/** @brief Get the canonical string representation for a UUID.
 *
 *  @param uuid uuid_t object.
 *  @returns canonical UUID hex string: "01234567-89ab-cdef-0123-456789abcdef".
 *
 *  A @c boost::uuids::uuid object yields the same representation via
 *  its @c << operator or @c to_string() function.
 */
static inline std::string toHexString(const uuid_t & uuid)
{
  uuid_string_t str;
  uuid_unparse_lower(uuid, str);
  return std::string(str);
}

/** @brief Get the canonical string representation for a UUID message.
 *
 *  @param msg unique_identifier_msgs/msg/UUID message.
 *  @returns canonical UUID hex string: "01234567-89ab-cdef-0123-456789abcdef".
 */
static inline std::string toHexString(const unique_identifier_msgs::msg::UUID & msg)
{
  uuid_t uuid;
  fromMsg(msg, uuid);
  return toHexString(uuid);
}
}  // namespace unique_identifier_msgs

#endif  // UNIQUE_IDENTIFIER_MSGS__UUID_CONVERSION_HPP_
