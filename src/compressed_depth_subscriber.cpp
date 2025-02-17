/*********************************************************************
* Software License Agreement (BSD License)
*
*  Copyright (c) 2012, Willow Garage, Inc.
*  All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   * Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions and the following
*     disclaimer in the documentation and/or other materials provided
*     with the distribution.
*   * Neither the name of the Willow Garage nor the names of its
*     contributors may be used to endorse or promote products derived
*     from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
*  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
*  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
*  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
*  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
*  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
*  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*  POSSIBILITY OF SUCH DAMAGE.
*********************************************************************/

#include "compressed_depth_image_transport/compressed_depth_subscriber.h"

#include "compressed_depth_image_transport/codec.h"
#include "compressed_depth_image_transport/compression_common.h"

namespace compressed_depth_image_transport
{
void CompressedDepthSubscriber::subscribeImpl(
    rclcpp::Node * node,
    const std::string& base_topic,
    const Callback& callback,
    rmw_qos_profile_t custom_qos)
{
  this->subscribeImpl(node, base_topic, callback, custom_qos, rclcpp::SubscriptionOptions{});
}

void CompressedDepthSubscriber::subscribeImpl(
    rclcpp::Node * node,
    const std::string& base_topic,
    const Callback& callback,
    rmw_qos_profile_t custom_qos,
    rclcpp::SubscriptionOptions options)
{
    typedef image_transport::SimpleSubscriberPlugin<sensor_msgs::msg::CompressedImage> Base;
    Base::subscribeImplWithOptions(node, base_topic, callback, custom_qos, options);
}

void CompressedDepthSubscriber::internalCallback(
  const sensor_msgs::msg::CompressedImage::ConstSharedPtr& message,
  const Callback& user_cb)
{
  auto image = decodeCompressedDepthImage(*message);
  if (image)
  {
    user_cb(image);
  }
}

} //namespace compressed_depth_image_transport
