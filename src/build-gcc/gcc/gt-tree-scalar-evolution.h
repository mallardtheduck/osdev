/* Type information for tree-scalar-evolution.c.
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
gt_ggc_mx_scev_info_str (void *x_p)
{
  struct scev_info_str * const x = (struct scev_info_str *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_15basic_block_def ((*x).instantiated_below);
      gt_ggc_m_9tree_node ((*x).var);
      gt_ggc_m_9tree_node ((*x).chrec);
    }
}

void
gt_ggc_m_P13scev_info_str4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      {
        size_t l0 = (size_t)(((*x)).size);
        if ((*x).entries != NULL) {
          size_t i0;
          for (i0 = 0; i0 != (size_t)(l0); i0++) {
            gt_ggc_m_13scev_info_str ((*x).entries[i0]);
          }
          ggc_mark ((*x).entries);
        }
      }
    }
}

void
gt_pch_nx_scev_info_str (void *x_p)
{
  struct scev_info_str * const x = (struct scev_info_str *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_13scev_info_str))
    {
      gt_pch_n_15basic_block_def ((*x).instantiated_below);
      gt_pch_n_9tree_node ((*x).var);
      gt_pch_n_9tree_node ((*x).chrec);
    }
}

void
gt_pch_n_P13scev_info_str4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_P13scev_info_str4htab))
    {
      {
        size_t l0 = (size_t)(((*x)).size);
        if ((*x).entries != NULL) {
          size_t i0;
          for (i0 = 0; i0 != (size_t)(l0); i0++) {
            gt_pch_n_13scev_info_str ((*x).entries[i0]);
          }
          gt_pch_note_object ((*x).entries, x, gt_pch_p_P13scev_info_str4htab);
        }
      }
    }
}

void
gt_pch_p_13scev_info_str (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct scev_info_str * x ATTRIBUTE_UNUSED = (struct scev_info_str *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).instantiated_below), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).var), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).chrec), cookie);
}

void
gt_pch_p_P13scev_info_str4htab (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct htab * x ATTRIBUTE_UNUSED = (struct htab *)x_p;
  {
    size_t l0 = (size_t)(((*x)).size);
    if ((*x).entries != NULL) {
      size_t i0;
      for (i0 = 0; i0 != (size_t)(l0) && ((void *)(*x).entries == this_obj); i0++) {
        if ((void *)((*x).entries) == this_obj)
          op (&((*x).entries[i0]), cookie);
      }
      if ((void *)(x) == this_obj)
        op (&((*x).entries), cookie);
    }
  }
}

/* GC roots.  */

EXPORTED_CONST struct ggc_root_tab gt_ggc_r_gt_tree_scalar_evolution_h[] = {
  {
    &scalar_evolution_info,
    1,
    sizeof (scalar_evolution_info),
    &gt_ggc_m_P13scev_info_str4htab,
    &gt_pch_n_P13scev_info_str4htab
  },
  LAST_GGC_ROOT_TAB
};

