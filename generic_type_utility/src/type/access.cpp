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

#include "generic_type_utility/type/access.hpp"

namespace generic_type_utility
{

std::string join(const std::vector<std::string> & input, const std::string & delimiter)
{
  std::string result;
  for (size_t i = 0; i < input.size(); ++i)
  {
    result += (i ? delimiter : "") + input[i];
  }
  return result;
}

std::vector<std::string> split(const std::string & input, char delimiter)
{
  std::vector<std::string> result;
  size_t found = input.find(delimiter);
  size_t start = 0;
  while (found != std::string::npos)
  {
    result.push_back(input.substr(start, found - start));
    start = found + 1;
    found = input.find(delimiter, start);
  }
  result.push_back(input.substr(start));
  return result;
}

TypeAccessNode::TypeAccessNode(const std::string & access)
{
  const auto token = split(access, '@');
  field_ = token[0];
  index_ = token.size() == 2 ? std::optional(std::stoi(token[1])) : std::nullopt;
}

std::string TypeAccessNode::string() const
{
  return field_ + (index_ ? "@" + std::to_string(index_.value()) : "");
}

TypeAccess::TypeAccess(const std::string & access)
{
  if (!access.empty())
  {
    for (const auto & token : split(access, '.'))
    {
      nodes_.emplace_back(token);
    }
  }
}

std::string TypeAccess::string() const
{
  std::vector<std::string> fields;
  for (const auto & node : nodes_)
  {
    fields.push_back(node.string());
  }
  return join(fields, ".");
}

}  // namespace generic_type_utility
