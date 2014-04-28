/* Type information for trans-mem.c.
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

EXPORTED_CONST struct ggc_cache_tab gt_ggc_rc_gt_trans_mem_h[] = {
  {
    &tm_wrap_map,
    1,
    sizeof (tm_wrap_map),
    &gt_ggc_mx_tree_map,
    &gt_pch_nx_tree_map,
    &tree_map_marked_p
  },
  LAST_GGC_CACHE_TAB
};

EXPORTED_CONST struct ggc_root_tab gt_pch_rc_gt_trans_mem_h[] = {
  {
    &tm_wrap_map,
    1,
    sizeof (tm_wrap_map),
    &gt_ggc_m_P8tree_map4htab,
    &gt_pch_n_P8tree_map4htab
  },
  LAST_GGC_ROOT_TAB
};

