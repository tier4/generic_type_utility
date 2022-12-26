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

#ifndef GENERIC_TYPE_UTILITY__TYPE__ACCESS_HPP_
#define GENERIC_TYPE_UTILITY__TYPE__ACCESS_HPP_

#include <yaml-cpp/yaml.h>
#include <optional>
#include <string>
#include <vector>

namespace generic_type_utility
{

struct TypeAccessorElement
{
  const std::optional<std::string> field;
  const std::optional<int> index;
};

class TypeAccessor
{
public:
  using Elements = std::vector<TypeAccessorElement>;
  using Iterator = std::vector<TypeAccessorElement>::const_iterator;
  explicit TypeAccessor(const std::string & path = "");
  const std::vector<TypeAccessorElement> & elements() const { return elements_; }
  const std::string path() const;
  YAML::Node apply(const YAML::Node & yaml) const;

private:
  std::vector<TypeAccessorElement> elements_;
};

}  // namespace generic_type_utility

#endif  // GENERIC_TYPE_UTILITY__TYPE__ACCESS_HPP_
