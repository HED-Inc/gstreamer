/* GStreamer
 *
 * unit test for GstIdStr
 *
 * Copyright (C) 2024 Sebastian Dröge <sebastian@centricular.com>
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

#include <gst/gst.h>
#include <gst/check/gstcheck.h>
#include "gst/gstidstr-private.h"

#define GST_ID_STR_PRIVATE(s) ((GstIdStrPrivate *)s)

GST_START_TEST (test_init)
{
  GstIdStr s = GST_ID_STR_INIT;

  fail_unless_equals_string (gst_id_str_as_str (&s), "");

  // Should be stack allocated
  gst_id_str_set (&s, "Hello, World!");
  fail_unless_equals_int (GST_ID_STR_PRIVATE (&s)->s.string_type.t, 0);
  fail_unless_equals_string (gst_id_str_as_str (&s), "Hello, World!");

  // Should become the empty string again
  gst_id_str_clear (&s);
  fail_unless_equals_string (gst_id_str_as_str (&s), "");

  // Should be heap allocated
  gst_id_str_set (&s, "Hello, World! Goodbye, World!");
  fail_unless_equals_int (GST_ID_STR_PRIVATE (&s)->s.string_type.t, 1);
  fail_unless_equals_string (gst_id_str_as_str (&s),
      "Hello, World! Goodbye, World!");

  // Should become the empty string again
  gst_id_str_clear (&s);
  fail_unless_equals_string (gst_id_str_as_str (&s), "");
}

GST_END_TEST;

GST_START_TEST (test_alloc)
{
  GstIdStr *s = gst_id_str_new ();
  GstIdStr *copy;

  fail_unless_equals_string (gst_id_str_as_str (s), "");

  // Should be stack allocated
  gst_id_str_set (s, "Hello, World!");
  fail_unless_equals_int (GST_ID_STR_PRIVATE (s)->s.string_type.t, 0);
  fail_unless_equals_string (gst_id_str_as_str (s), "Hello, World!");

  // Should be a full copy
  copy = gst_id_str_copy (s);
  fail_unless_equals_int (GST_ID_STR_PRIVATE (copy)->s.string_type.t, 0);
  fail_unless_equals_string (gst_id_str_as_str (copy), "Hello, World!");
  // Strings are the same, but pointers should be different because the strings should be inlined
  fail_unless_equals_string (gst_id_str_as_str (s), gst_id_str_as_str (copy));
  fail_unless (gst_id_str_as_str (s) != gst_id_str_as_str (copy));
  gst_id_str_free (copy);

  // Should become the empty string again
  gst_id_str_clear (s);
  fail_unless_equals_string (gst_id_str_as_str (s), "");

  // Should be heap allocated
  gst_id_str_set (s, "Hello, World! Goodbye, World!");
  fail_unless_equals_int (GST_ID_STR_PRIVATE (s)->s.string_type.t, 1);
  fail_unless_equals_string (gst_id_str_as_str (s),
      "Hello, World! Goodbye, World!");

  // Should be a full copy
  copy = gst_id_str_copy (s);
  fail_unless_equals_int (GST_ID_STR_PRIVATE (copy)->s.string_type.t, 1);
  fail_unless_equals_string (gst_id_str_as_str (copy),
      "Hello, World! Goodbye, World!");
  gst_id_str_free (copy);

  // Should be stored by pointer but not heap allocated
  gst_id_str_set_static_str (s, "Hello, World! Goodbye, World!");
  fail_unless_equals_int (GST_ID_STR_PRIVATE (s)->s.string_type.t, 2);
  fail_unless_equals_string (gst_id_str_as_str (s),
      "Hello, World! Goodbye, World!");

  // Should be a shallow copy because it's a static string
  copy = gst_id_str_copy (s);
  fail_unless_equals_int (GST_ID_STR_PRIVATE (copy)->s.string_type.t, 2);
  fail_unless_equals_string (gst_id_str_as_str (copy),
      "Hello, World! Goodbye, World!");
  fail_unless_equals_pointer (GST_ID_STR_PRIVATE (copy)->s.pointer_string.s,
      GST_ID_STR_PRIVATE (s)->s.pointer_string.s);
  gst_id_str_free (copy);

  // Should become the empty string again
  gst_id_str_clear (s);
  fail_unless_equals_string (gst_id_str_as_str (s), "");

  gst_id_str_free (s);
}

GST_END_TEST;

GST_START_TEST (test_compare)
{
  GstIdStr s1 = GST_ID_STR_INIT;
  GstIdStr s2 = GST_ID_STR_INIT;

  fail_unless (gst_id_str_is_equal (&s1, &s2));
  fail_unless (gst_id_str_is_equal (&s1, &s1));
  fail_unless (gst_id_str_is_equal_to_str (&s1, ""));
  fail_if (gst_id_str_is_equal_to_str (&s1, "Hello, World!"));

  // Should be stack allocated
  gst_id_str_set (&s1, "Hello, World!");

  fail_if (gst_id_str_is_equal (&s1, &s2));
  fail_unless (gst_id_str_is_equal (&s1, &s1));
  fail_unless (gst_id_str_is_equal_to_str (&s1, "Hello, World!"));
  fail_if (gst_id_str_is_equal_to_str (&s1, "Hello, World?"));
  fail_if (gst_id_str_is_equal_to_str (&s1, ""));

  // Should be heap allocated
  gst_id_str_set (&s1, "Hello, World! Goodbye, World!");

  fail_if (gst_id_str_is_equal (&s1, &s2));
  fail_unless (gst_id_str_is_equal (&s1, &s1));
  fail_unless (gst_id_str_is_equal_to_str (&s1,
          "Hello, World! Goodbye, World!"));
  fail_if (gst_id_str_is_equal_to_str (&s1, ""));
  fail_if (gst_id_str_is_equal_to_str (&s1, "Hello, World? Goodbye, World!"));

  gst_id_str_set (&s2, "Hello, World!");
  fail_if (gst_id_str_is_equal (&s1, &s2));

  gst_id_str_set (&s1, "Hello, World!");
  fail_unless (gst_id_str_is_equal (&s1, &s2));

  gst_id_str_clear (&s1);
  gst_id_str_clear (&s2);
}

GST_END_TEST;

static Suite *
gst_id_str_suite (void)
{
  Suite *s = suite_create ("GstIdStr");
  TCase *tc_chain = tcase_create ("general");

  suite_add_tcase (s, tc_chain);

  tcase_add_test (tc_chain, test_init);
  tcase_add_test (tc_chain, test_alloc);
  tcase_add_test (tc_chain, test_compare);

  return s;
}

GST_CHECK_MAIN (gst_id_str);
