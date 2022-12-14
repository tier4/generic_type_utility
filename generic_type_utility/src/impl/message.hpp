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

#ifndef IMPL__MESSAGE_HPP_
#define IMPL__MESSAGE_HPP_

#include "util/types.hpp"
#include <string>
#include <vector>

namespace generic_type_utility
{

class TypeSupportMessage
{
public:
  explicit TypeSupportMessage(const IntrospectionMessage * message);
  explicit TypeSupportMessage(const IntrospectionHandle * handle);
  ~TypeSupportMessage();
  const std::string GetTypeName() const;
  const std::vector<TypeSupportField> & GetFields() const;
  const TypeSupportField GetField(const std::string name) const;
  void CreateMemory(void *& data) const;
  void DeleteMemory(void *& data) const;

private:
  const IntrospectionMessage * message_;
  std::vector<TypeSupportField> fields_;
};

}  // namespace generic_type_utility

#endif  // IMPL__MESSAGE_HPP_
