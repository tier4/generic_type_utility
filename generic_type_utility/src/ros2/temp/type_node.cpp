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
  field_ = field;
  klass_ = handle ? reinterpret_cast<const IntrospectionClass *>(handle->data) : nullptr;

  if (field_)
  {
    std::cout << "field: " << field_->name_ << std::endl;
  }

  if (klass_)
  {
    std::cout << "class: " << klass_->message_namespace_ << "::" << klass_->message_name_ << std::endl;
    if (klass_->members_)
    {
      for (uint32_t i = 0; i < klass_->member_count_; ++i)
      {
        const IntrospectionField * f = klass_->members_ + i;
        RosTypeNode temp(f, f->members_);
      }
    }
  }
}

const RosTypeNode::IntrospectionClass * RosTypeNode::get_introspection_class()
{
  return klass_;
}

}  // namespace generic_type_utility
