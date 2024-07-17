/* GStreamer
 * Copyright (C) 2024 Collabora Ltd
 *  @author: Daniel Morin <daniel.morin@collabora.com>
 *
 * gstanalyticssegmentmeta.c
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
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "gstanalyticstensormtd.h"

/**
 * SECTION: gstanalyticstensormtd
 * @title: GstAnalyticsTensorMtd
 * @short_description: Analytics metadata to store tensor inside a
 * #GstAnalyticsRelationMeta
 * @symbols:
 * - GstAnalyticsTensorMtd
 * @see_also: #GstAnalyticsMtd, #GstAnalyticsRelationMeta
 *
 * This type of metadata holds a tensor. It can be useful to store tensor as
 * analytics-meta for their ability to relate to each others. For example
 * in a multi-model analytics pipeline, we sometime have one model input match
 * the output of the other model. In this context it can be useful to keep the
 * ancestry relation between first tensor, output of first inference, and the
 * second tensor, output from second inference. Another use-case for
 * #GstAnalyticsTensorMtd is to transport tensors from inference element to a
 * post-processing element using a computing graph framework, like ONNX.
 * Essentially #GstAnalyticsTensorMtd is a GstBuffer encapsulated by a
 * analytics-meta with additional parameters describing the tensor.
 *
 * Since 1.26
 */


static void gst_analytics_tensor_mtd_clear (GstBuffer * buffer, GstAnalyticsMtd
    * mtd);
