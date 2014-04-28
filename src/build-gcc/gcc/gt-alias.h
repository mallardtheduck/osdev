/* Type information for alias.c.
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

void
gt_ggc_mx_vec_alias_set_entry_va_gc_ (void *x_p)
{
  vec<alias_set_entry,va_gc> * const x = (vec<alias_set_entry,va_gc> *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_mx (x);
    }
}

void
gt_ggc_mx (struct alias_set_entry_d *& x)
{
  if (x)
    gt_ggc_mx_alias_set_entry_d ((void *) x);
}

void
gt_ggc_mx_alias_set_entry_d (void *x_p)
{
  struct alias_set_entry_d * const x = (struct alias_set_entry_d *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_II12splay_tree_s ((*x).children);
    }
}

void
gt_pch_nx_vec_alias_set_entry_va_gc_ (void *x_p)
{
  vec<alias_set_entry,va_gc> * const x = (vec<alias_set_entry,va_gc> *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_26vec_alias_set_entry_va_gc_))
    {
      gt_pch_nx (x);
    }
}

void
gt_pch_nx (struct alias_set_entry_d *& x)
{
  if (x)
    gt_pch_nx_alias_set_entry_d ((void *) x);
}

void
gt_pch_nx_alias_set_entry_d (void *x_p)
{
  struct alias_set_entry_d * const x = (struct alias_set_entry_d *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_17alias_set_entry_d))
    {
      gt_pch_n_II12splay_tree_s ((*x).children);
    }
}

void
gt_pch_p_26vec_alias_set_entry_va_gc_ (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct vec<alias_set_entry,va_gc> * x ATTRIBUTE_UNUSED = (struct vec<alias_set_entry,va_gc> *)x_p;
  if ((void *)(x) == this_obj)
    gt_pch_nx (&((*x)), op, cookie);
}

void
gt_pch_p_17alias_set_entry_d (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct alias_set_entry_d * x ATTRIBUTE_UNUSED = (struct alias_set_entry_d *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).children), cookie);
}

/* GC roots.  */

EXPORTED_CONST struct ggc_root_tab gt_ggc_r_gt_alias_h[] = {
  {
    &alias_sets,
    1,
    sizeof (alias_sets),
    &gt_ggc_mx_vec_alias_set_entry_va_gc_,
    &gt_pch_nx_vec_alias_set_entry_va_gc_
  },
  {
    &reg_known_value,
    1,
    sizeof (reg_known_value),
    &gt_ggc_mx_vec_rtx_va_gc_,
    &gt_pch_nx_vec_rtx_va_gc_
  },
  {
    &arg_base_value,
    1,
    sizeof (arg_base_value),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &reg_base_value,
    1,
    sizeof (reg_base_value),
    &gt_ggc_mx_vec_rtx_va_gc_,
    &gt_pch_nx_vec_rtx_va_gc_
  },
  LAST_GGC_ROOT_TAB
};

EXPORTED_CONST struct ggc_root_tab gt_ggc_rd_gt_alias_h[] = {
  { &old_reg_base_value, 1, sizeof (old_reg_base_value), NULL, NULL },
  LAST_GGC_ROOT_TAB
};

EXPORTED_CONST struct ggc_root_tab gt_pch_rs_gt_alias_h[] = {
  { &frame_set, 1, sizeof (frame_set), NULL, NULL },
  { &varargs_set, 1, sizeof (varargs_set), NULL, NULL },
  LAST_GGC_ROOT_TAB
};

