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

#include <generic_type_utility/yaml.hpp>

namespace generic_type_utility
{

YAML::Node apply(const TypeAccess & access, const YAML::Node & yaml)
{
  YAML::Node data = yaml;
  for (const auto & node : access.nodes())
  {
    const auto & field = node.field();
    const auto & index = node.index();
    data.reset(index ? data[field][index.value()] : data[field]);
  }
  return data;
}

}  // namespace generic_type_utility
