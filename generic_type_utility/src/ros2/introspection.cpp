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

#include "generic_type_utility/ros2/introspection.hpp"
#include "temp/type_node.hpp"
#include <rclcpp/typesupport_helpers.hpp>

//
#include <iostream>

namespace generic_type_utility
{

class RosIntrospection::Impl
{
public:
  explicit Impl(const std::string & type_name);

private:
  std::shared_ptr<rcpputils::SharedLibrary> library_;
  std::unique_ptr<RosTypeNode> rostype_;
};

RosIntrospection::Impl::Impl(const std::string & type_name)
{
  constexpr char identifier[] = "rosidl_typesupport_introspection_cpp";
  library_ = rclcpp::get_typesupport_library(type_name, identifier);

  const auto handle = rclcpp::get_typesupport_handle(type_name, identifier, *library_);
  rostype_ = std::make_unique<RosTypeNode>(nullptr, handle);
}

RosIntrospection::RosIntrospection(const std::string & type_name)
{
  impl_ = std::make_unique<Impl>(type_name);
}

RosIntrospection::~RosIntrospection()
{
}

}  // namespace generic_type_utility
