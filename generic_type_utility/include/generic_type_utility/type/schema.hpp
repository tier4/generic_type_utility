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

#ifndef GENERIC_TYPE_UTILITY__TYPE__SCHEMA_HPP_
#define GENERIC_TYPE_UTILITY__TYPE__SCHEMA_HPP_

#include <memory>
#include <string>
#include <unordered_map>

namespace generic_type_utility
{

class TypeSchema
{
public:
  using SharedPtr = std::shared_ptr<TypeSchema>;
  using ConstSharedPtr = std::shared_ptr<const TypeSchema>;

  TypeSchema() = default;
  virtual ~TypeSchema() = default;
  virtual std::string name() const = 0;
};

class TypeReal : public TypeSchema
{
};
class TypeText : public TypeSchema
{
};
class TypeUInt : public TypeSchema
{
};
class TypeSInt : public TypeSchema
{
};

class TypeUInt8 : public TypeUInt
{
public:
  std::string name() const override { return "uint8"; }
};

class TypeClass : public TypeSchema
{
public:
  std::string name() const override { return name_; }

private:
  std::string name_;
  std::unordered_map<std::string, TypeSchema::SharedPtr> members_;
};

}  // namespace generic_type_utility

#endif  // GENERIC_TYPE_UTILITY__TYPE__SCHEMA_HPP_
