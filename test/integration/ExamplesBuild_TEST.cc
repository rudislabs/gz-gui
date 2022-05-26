/*
 * Copyright (C) 2017 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <gtest/gtest.h>
#include <string>

#include <ignition/common/Console.hh>
#include <ignition/common/Filesystem.hh>
#include <ignition/common/TempDirectory.hh>
#include <ignition/utils/ExtraTestMacros.hh>

#include "test_config.h"  // NOLINT(build/include)

using namespace ignition;

auto kExampleTypes = std::vector<std::string>{"plugin", "standalone"};

//////////////////////////////////////////////////
struct ExampleEntry
{
  /// Type of example (eg plugin/standalone)
  std::string type;

  /// Example plugin directory name
  std::string base;

  /// Full path to the source directory of the example
  std::string sourceDir;

  /// Used to pretty print with gtest
  /// \param[in] _os stream to print to
  /// \param[in] _example Entry to print to the stream
  friend std::ostream& operator<<(std::ostream &_os,
                                  const ExampleEntry &_entry)
  {
    return _os << "[" << _entry.type << ", " << _entry.base << "]";
  }
};

//////////////////////////////////////////////////
/// Generate a list of examples to be built.
std::vector<ExampleEntry> GetExamples()
{
  std::vector<ExampleEntry> examples;
  for (auto type : kExampleTypes)
  {
    auto examplesDir =
      common::joinPaths(PROJECT_SOURCE_PATH, "/examples/", type);

    // Iterate over directory
    ignition::common::DirIter endIter;
    for (ignition::common::DirIter dirIter(examplesDir);
        dirIter != endIter; ++dirIter)
    {
      auto base = ignition::common::basename(*dirIter);
      auto sourceDir = common::joinPaths(examplesDir, base);
      examples.push_back({ type, base, sourceDir });
    }
  }
  return examples;
}

//////////////////////////////////////////////////
class ExamplesBuild : public ::testing::TestWithParam<ExampleEntry>
{
  /// \brief Build code in a temporary build folder.
  /// \param[in] _entry Example source code to build
  public: void Build(const ExampleEntry &_entry);
};

//////////////////////////////////////////////////
void ExamplesBuild::Build(const ExampleEntry &_entry)
{
  common::Console::SetVerbosity(4);

  // Path to examples of the given type
  ASSERT_TRUE(ignition::common::exists(_entry.sourceDir));

  igndbg << "Source: " << _entry.sourceDir << std::endl;

  // Create a temp build directory
  common::TempDirectory tmpBuildDir;
  ASSERT_TRUE(tmpBuildDir.Valid());
  igndbg << "Build directory: " << tmpBuildDir.Path() << std::endl;

  char cmd[1024];

  // cd build && cmake source
  snprintf(cmd, sizeof(cmd), "cd %s && cmake %s",
    tmpBuildDir.Path().c_str(), _entry.sourceDir.c_str());

  ASSERT_EQ(system(cmd), 0);
  ASSERT_EQ(system("make"), 0);
}

//////////////////////////////////////////////////
// See https://github.com/ignitionrobotics/ign-gui/issues/75
TEST_P(ExamplesBuild, IGN_UTILS_TEST_ENABLED_ONLY_ON_LINUX(Build))
{
  Build(GetParam());
}

//////////////////////////////////////////////////
INSTANTIATE_TEST_SUITE_P(Plugins, ExamplesBuild,
    ::testing::ValuesIn(GetExamples()),
    [](const ::testing::TestParamInfo<ExamplesBuild::ParamType>& param) {
      return param.param.type + "_" + param.param.base;
    });

//////////////////////////////////////////////////
int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
