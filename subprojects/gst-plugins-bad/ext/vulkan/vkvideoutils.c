/*
 * GStreamer
 * Copyright (C) 2024 Igalia, S.L.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "vkvideoutils.h"

gboolean
gst_vulkan_video_get_chroma_info_from_format (GstVideoFormat format,
    VkVideoChromaSubsamplingFlagBitsKHR * chroma_format,
    VkVideoComponentBitDepthFlagsKHR * bit_depth_luma,
    VkVideoComponentBitDepthFlagsKHR * bit_depth_chroma)
{
  switch (format) {
    case GST_VIDEO_FORMAT_GRAY8:
      *chroma_format = VK_VIDEO_CHROMA_SUBSAMPLING_MONOCHROME_BIT_KHR;
      *bit_depth_luma = VK_VIDEO_COMPONENT_BIT_DEPTH_8_BIT_KHR;
      *bit_depth_chroma = VK_VIDEO_COMPONENT_BIT_DEPTH_INVALID_KHR;
      break;
    case GST_VIDEO_FORMAT_I420:
    case GST_VIDEO_FORMAT_NV12:
      *chroma_format = VK_VIDEO_CHROMA_SUBSAMPLING_420_BIT_KHR;
      *bit_depth_luma = VK_VIDEO_COMPONENT_BIT_DEPTH_8_BIT_KHR;
      *bit_depth_chroma = VK_VIDEO_COMPONENT_BIT_DEPTH_8_BIT_KHR;
      break;
    case GST_VIDEO_FORMAT_NV16:
    case GST_VIDEO_FORMAT_YUY2:
    case GST_VIDEO_FORMAT_YVYU:
    case GST_VIDEO_FORMAT_UYVY:
      *chroma_format = VK_VIDEO_CHROMA_SUBSAMPLING_422_BIT_KHR;
      *bit_depth_luma = VK_VIDEO_COMPONENT_BIT_DEPTH_8_BIT_KHR;
      *bit_depth_chroma = VK_VIDEO_COMPONENT_BIT_DEPTH_8_BIT_KHR;
      break;
    case GST_VIDEO_FORMAT_GRAY10_LE32:
      *chroma_format = VK_VIDEO_CHROMA_SUBSAMPLING_MONOCHROME_BIT_KHR;
      *bit_depth_luma = VK_VIDEO_COMPONENT_BIT_DEPTH_10_BIT_KHR;
      *bit_depth_chroma = VK_VIDEO_COMPONENT_BIT_DEPTH_INVALID_KHR;
      break;
    case GST_VIDEO_FORMAT_NV12_10LE32:
      *chroma_format = VK_VIDEO_CHROMA_SUBSAMPLING_420_BIT_KHR;
      *bit_depth_luma = *bit_depth_chroma =
          VK_VIDEO_COMPONENT_BIT_DEPTH_10_BIT_KHR;
      break;
    case GST_VIDEO_FORMAT_NV16_10LE32:
      *chroma_format = VK_VIDEO_CHROMA_SUBSAMPLING_422_BIT_KHR;
      *bit_depth_luma = *bit_depth_chroma =
          VK_VIDEO_COMPONENT_BIT_DEPTH_10_BIT_KHR;
      break;
    default:
      return FALSE;
  }

  return TRUE;
}
