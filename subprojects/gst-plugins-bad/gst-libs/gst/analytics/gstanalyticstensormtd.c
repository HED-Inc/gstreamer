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


static void gst_analytics_tensor_mtd_clear (GstBuffer * buffer,
    GstAnalyticsMtd * mtd);

static const GstAnalyticsMtdImpl tensor_impl = {
  "tensor",
  NULL,
  gst_analytics_tensor_mtd_clear
};

typedef GstTensor GstAnalyticsTensorMtdData;

GstAnalyticsMtdType
gst_analytics_tensor_mtd_get_mtd_type (void)
{
  return (GstAnalyticsMtdType) & tensor_impl;
}

GstTensor *
gst_analytics_tensor_mtd_get_tensor (GstAnalyticsTensorMtd * handle)
{
  GstAnalyticsTensorMtdData *mtddata;

  g_return_val_if_fail (handle, NULL);

  mtddata = gst_analytics_relation_meta_get_mtd_data (handle->meta, handle->id);
  g_return_val_if_fail (mtddata != NULL, NULL);

  return mtddata;
}

gboolean
gst_analytics_relation_meta_add_tensor_mtd (GstAnalyticsRelationMeta * instance,
    GQuark id, gsize num_dims, GstTensorDimOrder dims_order,
    GstTensorLayout layout, GstTensorDataType data_type, gsize batch_size,
    GstBuffer * tensor_buffer, gsize * dims, GstAnalyticsTensorMtd * tensor_mtd)
{
  const gsize dims_size = sizeof (gsize) * num_dims;
  const gsize size = sizeof (GstAnalyticsTensorMtdData) + dims_size;

  GstAnalyticsTensorMtdData *mtddata = NULL;
  mtddata = (GstAnalyticsTensorMtdData *)
      gst_analytics_relation_meta_add_mtd (instance, &tensor_impl, size,
      tensor_mtd);

  if (mtddata) {
    mtddata->id = id;
    mtddata->num_dims = num_dims;
    mtddata->dims_order = dims_order;
    mtddata->layout = layout;
    mtddata->data_type = data_type;
    mtddata->batch_size = batch_size;
    mtddata->data = tensor_buffer;
    memcpy (mtddata->dims, dims, num_dims);
  }

  return mtddata != NULL;
}

static void
gst_analytics_tensor_mtd_clear (GstBuffer * buffer, GstAnalyticsMtd * mtd)
{
  GstAnalyticsTensorMtdData *tensordata;
  tensordata = gst_analytics_relation_meta_get_mtd_data (mtd->meta, mtd->id);
  g_return_if_fail (tensordata != NULL);
  gst_clear_buffer (&tensordata->data);
}
