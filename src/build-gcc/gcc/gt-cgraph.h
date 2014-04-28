/* Type information for cgraph.c.
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

EXPORTED_CONST struct ggc_root_tab gt_ggc_r_gt_cgraph_h[] = {
  {
    &version_info_node,
    1,
    sizeof (version_info_node),
    &gt_ggc_mx_cgraph_function_version_info,
    &gt_pch_nx_cgraph_function_version_info
  },
  {
    &free_edges,
    1,
    sizeof (free_edges),
    &gt_ggc_mx_cgraph_edge,
    &gt_pch_nx_cgraph_edge
  },
  {
    &free_nodes,
    1,
    sizeof (free_nodes),
    &gt_ggc_mx_cgraph_node,
    &gt_pch_nx_cgraph_node
  },
  LAST_GGC_ROOT_TAB
};

