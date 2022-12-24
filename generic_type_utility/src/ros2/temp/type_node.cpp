// Copyright 2022 Takagi, Isamu
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

#include "type_node.hpp"

//
#include <iostream>

namespace generic_type_utility
{

RosTypeNode::RosTypeNode(const IntrospectionField * field, const rosidl_message_type_support_t * handle)
{
  std::cout << "==================================================-" << std::endl;

  if (field)
  {
    std::cout << "field: " << field->name_ << std::endl;
  }

  if (handle)
  {
    const auto * klass = reinterpret_cast<const IntrospectionClass *>(handle->data);
    std::cout << "class: " << klass->message_namespace_ << "::" << klass->message_name_ << std::endl;
    if (klass->members_)
    {
      for (uint32_t i = 0; i < klass->member_count_; ++i)
      {
        const IntrospectionField * f = klass->members_ + i;
        RosTypeNode temp(f, f->members_);
      }
    }
  }
}

}  // namespace generic_type_utility
