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

#ifndef IGNITION_GUI_PLUGINS_IMAGEDISPLAY_HH_
#define IGNITION_GUI_PLUGINS_IMAGEDISPLAY_HH_

#ifndef Q_MOC_RUN
  #include <ignition/gui/qt.h>
#endif

#include <ignition/msgs.hh>

#include "ignition/gui/Plugin.hh"

namespace ignition
{
namespace gui
{
namespace plugins
{
  class ImageDisplayPrivate;

  /// \brief Display images coming through an Ignition transport topic.
  ///
  /// ## Configuration
  ///
  /// <topic> : Set the topic to receive image messages.
  /// <topic_picker> : Whether to show the topic picker, true by default. If
  ///                  this is false, a <topic> must be specified.
  class ImageDisplay : public Plugin
  {
    Q_OBJECT

    /// \brief Constructor
    public: ImageDisplay();

    /// \brief Destructor
    public: virtual ~ImageDisplay();

    // Documentation inherited
    public: virtual void LoadConfig(const tinyxml2::XMLElement *_pluginElem);

    /// \brief Callback in main thread when image changes
    public slots: void ProcessImage();

    /// \brief Update from rx'd RGB_INT8
    private: void UpdateFromRgbInt8();

    /// \brief Subscriber callback when new image is received
    /// \param[in] _msg New image
    private: void OnImageMsg(const ignition::msgs::Image &_msg);

    /// \brief Callback when refresh button is pressed.
    private slots: void OnRefresh();

    /// \brief Callback when a new topic is chosen on the combo box.
    private slots: void OnTopic(const QString _topic);

    /// \internal
    /// \brief Pointer to private data.
    private: std::unique_ptr<ImageDisplayPrivate> dataPtr;
  };
}
}
}

#endif