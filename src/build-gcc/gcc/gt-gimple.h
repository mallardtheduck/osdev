/* Type information for gimple.c.
   Copyright (C) 2004-2013 Free Software Foundation, Inc.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 3, or (at your option) any later
version.

GCC is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING3.  If not see
<http://www.gnu.org/licenses/>.  */

/* This file is machine generated.  Do not edit.  */

/* GC roots.  */

EXPORTED_CONST struct ggc_cache_tab gt_ggc_rc_gt_gimple_h[] = {
  {
    &canonical_type_hash_cache,
    1,
    sizeof (canonical_type_hash_cache),
    &gt_ggc_mx_tree_int_map,
    &gt_pch_nx_tree_int_map,
    &tree_int_map_marked_p
  },
  {
    &gimple_canonical_types,
    1,
    sizeof (gimple_canonical_types),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node,
    &ggc_marked_p
  },
  LAST_GGC_CACHE_TAB
};

EXPORTED_CONST struct ggc_root_tab gt_pch_rc_gt_gimple_h[] = {
  {
    &canonical_type_hash_cache,
    1,
    sizeof (canonical_type_hash_cache),
    &gt_ggc_m_P12tree_int_map4htab,
    &gt_pch_n_P12tree_int_map4htab
  },
  {
    &gimple_canonical_types,
    1,
    sizeof (gimple_canonical_types),
    &gt_ggc_m_P9tree_node4htab,
    &gt_pch_n_P9tree_node4htab
  },
  LAST_GGC_ROOT_TAB
};

