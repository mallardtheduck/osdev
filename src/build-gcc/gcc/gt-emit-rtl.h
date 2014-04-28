/* Type information for emit-rtl.c.
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

EXPORTED_CONST struct ggc_root_tab gt_ggc_r_gt_emit_rtl_h[] = {
  {
    &spill_slot_decl,
    1,
    sizeof (spill_slot_decl),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  LAST_GGC_ROOT_TAB
};

EXPORTED_CONST struct ggc_root_tab gt_ggc_rd_gt_emit_rtl_h[] = {
  { &hard_reg_clobbers, 1, sizeof (hard_reg_clobbers), NULL, NULL },
  { &free_sequence_stack, 1, sizeof (free_sequence_stack), NULL, NULL },
  LAST_GGC_ROOT_TAB
};

EXPORTED_CONST struct ggc_cache_tab gt_ggc_rc_gt_emit_rtl_h[] = {
  {
    &const_fixed_htab,
    1,
    sizeof (const_fixed_htab),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def,
    &ggc_marked_p
  },
  {
    &const_double_htab,
    1,
    sizeof (const_double_htab),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def,
    &ggc_marked_p
  },
  {
    &reg_attrs_htab,
    1,
    sizeof (reg_attrs_htab),
    &gt_ggc_mx_reg_attrs,
    &gt_pch_nx_reg_attrs,
    &ggc_marked_p
  },
  {
    &mem_attrs_htab,
    1,
    sizeof (mem_attrs_htab),
    &gt_ggc_mx_mem_attrs,
    &gt_pch_nx_mem_attrs,
    &ggc_marked_p
  },
  {
    &const_int_htab,
    1,
    sizeof (const_int_htab),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def,
    &ggc_marked_p
  },
  LAST_GGC_CACHE_TAB
};

EXPORTED_CONST struct ggc_root_tab gt_pch_rc_gt_emit_rtl_h[] = {
  {
    &const_fixed_htab,
    1,
    sizeof (const_fixed_htab),
    &gt_ggc_m_P7rtx_def4htab,
    &gt_pch_n_P7rtx_def4htab
  },
  {
    &const_double_htab,
    1,
    sizeof (const_double_htab),
    &gt_ggc_m_P7rtx_def4htab,
    &gt_pch_n_P7rtx_def4htab
  },
  {
    &reg_attrs_htab,
    1,
    sizeof (reg_attrs_htab),
    &gt_ggc_m_P9reg_attrs4htab,
    &gt_pch_n_P9reg_attrs4htab
  },
  {
    &mem_attrs_htab,
    1,
    sizeof (mem_attrs_htab),
    &gt_ggc_m_P9mem_attrs4htab,
    &gt_pch_n_P9mem_attrs4htab
  },
  {
    &const_int_htab,
    1,
    sizeof (const_int_htab),
    &gt_ggc_m_P7rtx_def4htab,
    &gt_pch_n_P7rtx_def4htab
  },
  LAST_GGC_ROOT_TAB
};

EXPORTED_CONST struct ggc_root_tab gt_pch_rs_gt_emit_rtl_h[] = {
  { &label_num, 1, sizeof (label_num), NULL, NULL },
  LAST_GGC_ROOT_TAB
};

