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

#include <ignition/common/Console.hh>
#include <ignition/math/Color.hh>

#include "test_config.h"  // NOLINT(build/include)
#include "ignition/gui/Conversions.hh"

using namespace ignition;
using namespace gui;

/////////////////////////////////////////////////
TEST(ConversionsTest, Color)
{
  // Ignition to Qt to Ignition
  {
    double red = 0.1;
    double green = 0.3;
    double blue = 0.5;
    double alpha = 0.7;

    double tol = 0.01;

    math::Color color(red, green, blue, alpha);
    auto newColor = convert(convert(color));

    EXPECT_NEAR(newColor.R(), newColor.R(), tol);
    EXPECT_NEAR(newColor.G(), newColor.G(), tol);
    EXPECT_NEAR(newColor.B(), newColor.B(), tol);
    EXPECT_NEAR(newColor.A(), newColor.A(), tol);
  }

  // Qt to Ignition to Qt
  {
    int red = 100;
    int green = 150;
    int blue = 200;
    int alpha = 186;

    QColor color(red, green, blue, alpha);
    EXPECT_EQ(convert(convert(color)), color);
  }
}

/////////////////////////////////////////////////
TEST(ConversionsTest, Point2d)
{
  double x = -0.5;
  double y = 123;

  // Ignition to Qt to Ignition
  {
    math::Vector2d point(x, y);
    EXPECT_EQ(convert(convert(point)), point);
  }

  // Qt to Ignition to Qt
  {
    QPointF point(x, y);
    EXPECT_EQ(convert(convert(point)), point);
  }
}

/////////////////////////////////////////////////
TEST(ConversionsTest, Vector3d)
{
  double x = -0.1;
  double y = 0;
  double z = 1234;

  // Ignition to Qt to Ignition
  {
    math::Vector3d vec(x, y, z);
    EXPECT_EQ(convert(convert(vec)), vec);
  }

  // Qt to Ignition to Qt
  {
    QVector3D vec(x, y, z);
    EXPECT_EQ(convert(convert(vec)), vec);
  }
}
