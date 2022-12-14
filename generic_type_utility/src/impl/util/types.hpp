// Copyright 2021 Takagi, Isamu
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

#ifndef IMPL__UTIL__TYPES_HPP_
#define IMPL__UTIL__TYPES_HPP_

#include <rosidl_typesupport_introspection_cpp/message_introspection.hpp>
#include <rosidl_typesupport_introspection_cpp/service_introspection.hpp>
#include <stdexcept>

namespace generic_type_utility
{

using IntrospectionHandle = rosidl_message_type_support_t;
using IntrospectionService = rosidl_typesupport_introspection_cpp::ServiceMembers;
using IntrospectionMessage = rosidl_typesupport_introspection_cpp::MessageMembers;
using IntrospectionField = rosidl_typesupport_introspection_cpp::MessageMember;

class TypeSupportService;
class TypeSupportMessage;
class TypeSupportField;

class TypeSupportIdentifierError : public std::runtime_error
{
  using std::runtime_error::runtime_error;
};

}  // namespace generic_type_utility

#endif  // IMPL__UTIL__TYPES_HPP_
