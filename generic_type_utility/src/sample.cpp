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

#include <generic_type_utility/ros2/introspection.hpp>
#include <generic_type_utility/ros2/message.hpp>
#include <generic_type_utility/ros2/serialization.hpp>
#include <generic_type_utility/type/schema.hpp>
#include <generic_type_utility/yaml.hpp>
#include <rclcpp/rclcpp.hpp>
#include <yaml-cpp/yaml.h>
#include <algorithm>
#include <array>
#include <iostream>
using namespace generic_type_utility;  // NOLINT

void test1();
void test2();
void test3();

int main()
{
  test3();
}

void test3()
{
  rclcpp::SerializedMessage serialized;
  {
    // clang-format off
    const auto data = std::array<uint8_t, 28> ({
      0x00, 0x01, 0x00, 0x00,
      0x95, 0xfc, 0xa6, 0x63,
      0x38, 0xcc, 0x50, 0x30,
      0x09, 0x00, 0x00, 0x00,
      0x66, 0x72, 0x61, 0x6d,
      0x65, 0x20, 0x33, 0x30,
      0x00, 0x00, 0x00, 0x00
    });
    // clang-format on

    rcutils_uint8_array_t & buffer = serialized.get_rcl_serialized_message();
    serialized.reserve(data.size());
    buffer.buffer_length = data.size();
    std::copy(data.begin(), data.end(), buffer.buffer);

    std::cout << serialized.size() << std::endl;
    std::cout << serialized.capacity() << std::endl;
  }

  const auto introspection = std::make_shared<RosIntrospection>("std_msgs/msg/Header");
  const auto serialization = std::make_shared<RosSerialization>("std_msgs/msg/Header");

  const auto message = introspection->create_message();
  {
    std::cout << "==================================================" << std::endl;
    YAML::Node yaml = introspection->make_yaml(*message);
    std::cout << yaml << std::endl;
  }

  serialization->deserialize(serialized, *message);
  {
    std::cout << "==================================================" << std::endl;
    YAML::Node yaml = introspection->make_yaml(*message);
    std::cout << yaml << std::endl;
  }
}

void test2()
{
  TypeSchema::ConstSharedPtr t1 = std::make_shared<TypeUInt8>();
  std::cout << std::boolalpha << t1->name() << std::endl;
}

void test1()
{
  const auto access = generic_type_utility::TypeAccess("test.yaml.data@1");
  std::cout << access.string() << std::endl;

  YAML::Node yaml;
  yaml["hoge"] = "hoge";
  yaml["fuga"] = "fuga";
  yaml["test"]["yaml"]["data"][0] = 123;
  yaml["test"]["yaml"]["data"][1] = 456;
  yaml["test"]["yaml"]["data"][2] = 789;

  YAML::Node node = generic_type_utility::apply(access, yaml);
  std::cout << yaml << std::endl;
  std::cout << node << std::endl;
}
