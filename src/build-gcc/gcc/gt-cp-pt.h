/* Type information for cp/pt.c.
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
gt_ggc_mx_spec_entry (void *x_p)
{
  struct spec_entry * const x = (struct spec_entry *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_9tree_node ((*x).tmpl);
      gt_ggc_m_9tree_node ((*x).args);
      gt_ggc_m_9tree_node ((*x).spec);
    }
}

void
gt_ggc_mx_pending_template (void *x_p)
{
  struct pending_template * x = (struct pending_template *)x_p;
  struct pending_template * xlimit = x;
  while (ggc_test_and_set_mark (xlimit))
   xlimit = ((*xlimit).next);
  while (x != xlimit)
    {
      gt_ggc_m_16pending_template ((*x).next);
      gt_ggc_m_11tinst_level ((*x).tinst);
      x = ((*x).next);
    }
}

void
gt_ggc_m_P10spec_entry4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      {
        size_t l0 = (size_t)(((*x)).size);
        if ((*x).entries != NULL) {
          size_t i0;
          for (i0 = 0; i0 != (size_t)(l0); i0++) {
            gt_ggc_m_10spec_entry ((*x).entries[i0]);
          }
          ggc_mark ((*x).entries);
        }
      }
    }
}

void
gt_pch_nx_spec_entry (void *x_p)
{
  struct spec_entry * const x = (struct spec_entry *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_10spec_entry))
    {
      gt_pch_n_9tree_node ((*x).tmpl);
      gt_pch_n_9tree_node ((*x).args);
      gt_pch_n_9tree_node ((*x).spec);
    }
}

void
gt_pch_nx_pending_template (void *x_p)
{
  struct pending_template * x = (struct pending_template *)x_p;
  struct pending_template * xlimit = x;
  while (gt_pch_note_object (xlimit, xlimit, gt_pch_p_16pending_template))
   xlimit = ((*xlimit).next);
  while (x != xlimit)
    {
      gt_pch_n_16pending_template ((*x).next);
      gt_pch_n_11tinst_level ((*x).tinst);
      x = ((*x).next);
    }
}

void
gt_pch_n_P10spec_entry4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_P10spec_entry4htab))
    {
      {
        size_t l0 = (size_t)(((*x)).size);
        if ((*x).entries != NULL) {
          size_t i0;
          for (i0 = 0; i0 != (size_t)(l0); i0++) {
            gt_pch_n_10spec_entry ((*x).entries[i0]);
          }
          gt_pch_note_object ((*x).entries, x, gt_pch_p_P10spec_entry4htab);
        }
      }
    }
}

void
gt_pch_p_10spec_entry (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct spec_entry * x ATTRIBUTE_UNUSED = (struct spec_entry *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).tmpl), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).args), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).spec), cookie);
}

void
gt_pch_p_16pending_template (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct pending_template * x ATTRIBUTE_UNUSED = (struct pending_template *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).next), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).tinst), cookie);
}

void
gt_pch_p_P10spec_entry4htab (ATTRIBUTE_UNUSED void *this_obj,
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

EXPORTED_CONST struct ggc_root_tab gt_ggc_r_gt_cp_pt_h[] = {
  {
    &last_error_tinst_level,
    1,
    sizeof (last_error_tinst_level),
    &gt_ggc_mx_tinst_level,
    &gt_pch_nx_tinst_level
  },
  {
    &canonical_template_parms,
    1,
    sizeof (canonical_template_parms),
    &gt_ggc_mx_vec_tree_va_gc_,
    &gt_pch_nx_vec_tree_va_gc_
  },
  {
    &type_specializations,
    1,
    sizeof (type_specializations),
    &gt_ggc_m_P10spec_entry4htab,
    &gt_pch_n_P10spec_entry4htab
  },
  {
    &decl_specializations,
    1,
    sizeof (decl_specializations),
    &gt_ggc_m_P10spec_entry4htab,
    &gt_pch_n_P10spec_entry4htab
  },
  {
    &saved_access_scope,
    1,
    sizeof (saved_access_scope),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &current_tinst_level,
    1,
    sizeof (current_tinst_level),
    &gt_ggc_mx_tinst_level,
    &gt_pch_nx_tinst_level
  },
  {
    &saved_trees,
    1,
    sizeof (saved_trees),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &last_pending_template,
    1,
    sizeof (last_pending_template),
    &gt_ggc_mx_pending_template,
    &gt_pch_nx_pending_template
  },
  {
    &pending_templates,
    1,
    sizeof (pending_templates),
    &gt_ggc_mx_pending_template,
    &gt_pch_nx_pending_template
  },
  LAST_GGC_ROOT_TAB
};

