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
#include <generic_type_utility/type/schema.hpp>
#include <generic_type_utility/yaml.hpp>
#include <yaml-cpp/yaml.h>
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
  RosIntrospection t1("std_msgs/msg/Header");
  RosIntrospection t2("std_msgs/msg/Header");
  RosIntrospection t3("std_msgs/msg/UInt32");
  RosIntrospection t4("geometry_msgs/msg/Pose");
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
