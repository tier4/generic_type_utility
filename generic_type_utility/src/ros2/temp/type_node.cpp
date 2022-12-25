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
#include <rosidl_typesupport_introspection_cpp/field_types.hpp>
#include <memory>
#include <string>

//
#include <iostream>

namespace generic_type_utility
{

RosTypeNode::RosTypeNode(const IntrospectionField * field, const rosidl_message_type_support_t * handle)
{
  std::cout << "==================================================" << std::endl;
  field_ = field;
  klass_ = handle ? reinterpret_cast<const IntrospectionClass *>(handle->data) : nullptr;

  if (field_)
  {
    std::cout << "field: " << field_->name_ << std::endl;
  }

  if (klass_)
  {
    std::cout << "class: " << klass_->message_namespace_ << "::" << klass_->message_name_ << std::endl;
    for (uint32_t i = 0; i < klass_->member_count_; ++i)
    {
      const IntrospectionField * node = klass_->members_ + i;
      nodes_.push_back(std::make_unique<RosTypeNode>(node, node->members_));
    }
  }
}

const RosTypeNode::IntrospectionClass * RosTypeNode::get_introspection_class()
{
  return klass_;
}

const std::string RosTypeNode::get_class_name()
{
  if (!klass_)
  {
    throw std::logic_error("RosTypeNode::get_class_name");
  }
  return klass_->message_namespace_ + std::string("::") + klass_->message_name_;
}

const std::string RosTypeNode::get_field_name()
{
  if (!field_)
  {
    throw std::logic_error("RosTypeNode::get_field_name");
  }
  return field_->name_;
}

YAML::Node RosTypeNode::make_yaml(const void * memory)
{
  memory = static_cast<const uint8_t *>(memory) + (field_ ? field_->offset_ : 0);
  return (field_ && field_->is_array_) ? make_yaml_array(memory) : make_yaml_value(memory);
}

YAML::Node RosTypeNode::make_yaml_class(const void * memory)
{
  YAML::Node yaml;
  for (const auto & node : nodes_)
  {
    yaml[node->get_field_name()] = node->make_yaml(memory);
  }
  return yaml;
}

YAML::Node RosTypeNode::make_yaml_array(const void * memory)
{
  YAML::Node yaml;
  for (size_t i = 0, n = field_->size_function(memory); i < n; ++i)
  {
    yaml.push_back(make_yaml_value(field_->get_const_function(memory, i)));
  }
  return yaml;
}

YAML::Node RosTypeNode::make_yaml_value(const void * memory)
{
  using namespace rosidl_typesupport_introspection_cpp;  // NOLINT(build/namespaces)

  if (klass_)
  {
    return make_yaml_class(memory);
  }

  switch (field_->type_id_)
  {
    case ROS_TYPE_FLOAT:
      return YAML::Node(*reinterpret_cast<const float *>(memory));
    case ROS_TYPE_DOUBLE:
      return YAML::Node(*reinterpret_cast<const double *>(memory));
    case ROS_TYPE_LONG_DOUBLE:
      return YAML::Node(*reinterpret_cast<const long double *>(memory));
    case ROS_TYPE_CHAR:
      return YAML::Node(*reinterpret_cast<const char *>(memory));
    case ROS_TYPE_WCHAR:
      return YAML::Node("[ERROR: WCHAR IS NOT SUPPORTED]");
    case ROS_TYPE_BOOLEAN:
      return YAML::Node(*reinterpret_cast<const bool *>(memory));
    case ROS_TYPE_OCTET:
      return YAML::Node(static_cast<uint32_t>(*reinterpret_cast<const uint8_t *>(memory)));
    case ROS_TYPE_UINT8:
      return YAML::Node(static_cast<uint32_t>(*reinterpret_cast<const uint8_t *>(memory)));
    case ROS_TYPE_INT8:
      return YAML::Node(static_cast<int32_t>(*reinterpret_cast<const int8_t *>(memory)));
    case ROS_TYPE_UINT16:
      return YAML::Node(*reinterpret_cast<const uint16_t *>(memory));
    case ROS_TYPE_INT16:
      return YAML::Node(*reinterpret_cast<const int16_t *>(memory));
    case ROS_TYPE_UINT32:
      return YAML::Node(*reinterpret_cast<const uint32_t *>(memory));
    case ROS_TYPE_INT32:
      return YAML::Node(*reinterpret_cast<const int32_t *>(memory));
    case ROS_TYPE_UINT64:
      return YAML::Node(*reinterpret_cast<const uint64_t *>(memory));
    case ROS_TYPE_INT64:
      return YAML::Node(*reinterpret_cast<const int64_t *>(memory));
    case ROS_TYPE_STRING:
      return YAML::Node(*reinterpret_cast<const std::string *>(memory));
    case ROS_TYPE_WSTRING:
      return YAML::Node("[ERROR: WSTRING IS NOT SUPPORTED]");
    case ROS_TYPE_MESSAGE:
      return YAML::Node("[PARSE: NO MESSAGE HANDLE]");
  }
  return YAML::Node("[ERROR: UNKNOWN TYPE]");
}

}  // namespace generic_type_utility
