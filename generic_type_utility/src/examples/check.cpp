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

#include <generic_type_utility/generic_message.hpp>
#include <iostream>

int main()
{
  const auto message = generic_type_utility::GenericMessage("std_msgs/msg/Header");
  const auto access1 = generic_type_utility::TypeAccessor("stamp.nsec");
  const auto access2 = generic_type_utility::TypeAccessor("stamp.nanosec");
  std::cout << std::boolalpha << message.validate(access1) << std::endl;
  std::cout << std::boolalpha << message.validate(access2) << std::endl;
}
