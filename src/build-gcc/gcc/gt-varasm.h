/* Type information for varasm.c.
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
gt_ggc_mx_rtx_constant_pool (void *x_p)
{
  struct rtx_constant_pool * const x = (struct rtx_constant_pool *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_23constant_descriptor_rtx ((*x).first);
      gt_ggc_m_23constant_descriptor_rtx ((*x).last);
      gt_ggc_m_P23constant_descriptor_rtx4htab ((*x).const_rtx_htab);
    }
}

void
gt_ggc_mx_constant_descriptor_rtx (void *x_p)
{
  struct constant_descriptor_rtx * x = (struct constant_descriptor_rtx *)x_p;
  struct constant_descriptor_rtx * xlimit = x;
  while (ggc_test_and_set_mark (xlimit))
   xlimit = ((*xlimit).next);
  while (x != xlimit)
    {
      gt_ggc_m_23constant_descriptor_rtx ((*x).next);
      gt_ggc_m_7rtx_def ((*x).mem);
      gt_ggc_m_7rtx_def ((*x).sym);
      gt_ggc_m_7rtx_def ((*x).constant);
      x = ((*x).next);
    }
}

void
gt_ggc_m_P23constant_descriptor_rtx4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      {
        size_t l0 = (size_t)(((*x)).size);
        if ((*x).entries != NULL) {
          size_t i0;
          for (i0 = 0; i0 != (size_t)(l0); i0++) {
            gt_ggc_m_23constant_descriptor_rtx ((*x).entries[i0]);
          }
          ggc_mark ((*x).entries);
        }
      }
    }
}

void
gt_pch_nx_rtx_constant_pool (void *x_p)
{
  struct rtx_constant_pool * const x = (struct rtx_constant_pool *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_17rtx_constant_pool))
    {
      gt_pch_n_23constant_descriptor_rtx ((*x).first);
      gt_pch_n_23constant_descriptor_rtx ((*x).last);
      gt_pch_n_P23constant_descriptor_rtx4htab ((*x).const_rtx_htab);
    }
}

void
gt_pch_nx_constant_descriptor_rtx (void *x_p)
{
  struct constant_descriptor_rtx * x = (struct constant_descriptor_rtx *)x_p;
  struct constant_descriptor_rtx * xlimit = x;
  while (gt_pch_note_object (xlimit, xlimit, gt_pch_p_23constant_descriptor_rtx))
   xlimit = ((*xlimit).next);
  while (x != xlimit)
    {
      gt_pch_n_23constant_descriptor_rtx ((*x).next);
      gt_pch_n_7rtx_def ((*x).mem);
      gt_pch_n_7rtx_def ((*x).sym);
      gt_pch_n_7rtx_def ((*x).constant);
      x = ((*x).next);
    }
}

void
gt_pch_n_P23constant_descriptor_rtx4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_P23constant_descriptor_rtx4htab))
    {
      {
        size_t l0 = (size_t)(((*x)).size);
        if ((*x).entries != NULL) {
          size_t i0;
          for (i0 = 0; i0 != (size_t)(l0); i0++) {
            gt_pch_n_23constant_descriptor_rtx ((*x).entries[i0]);
          }
          gt_pch_note_object ((*x).entries, x, gt_pch_p_P23constant_descriptor_rtx4htab);
        }
      }
    }
}

void
gt_pch_p_17rtx_constant_pool (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct rtx_constant_pool * x ATTRIBUTE_UNUSED = (struct rtx_constant_pool *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).first), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).last), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).const_rtx_htab), cookie);
}

void
gt_pch_p_23constant_descriptor_rtx (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct constant_descriptor_rtx * x ATTRIBUTE_UNUSED = (struct constant_descriptor_rtx *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).next), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).mem), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).sym), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).constant), cookie);
}

void
gt_pch_p_P23constant_descriptor_rtx4htab (ATTRIBUTE_UNUSED void *this_obj,
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

EXPORTED_CONST struct ggc_root_tab gt_ggc_r_gt_varasm_h[] = {
  {
    &elf_fini_array_section,
    1,
    sizeof (elf_fini_array_section),
    &gt_ggc_mx_section,
    &gt_pch_nx_section
  },
  {
    &elf_init_array_section,
    1,
    sizeof (elf_init_array_section),
    &gt_ggc_mx_section,
    &gt_pch_nx_section
  },
  {
    &weakref_targets,
    1,
    sizeof (weakref_targets),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &const_desc_htab,
    1,
    sizeof (const_desc_htab),
    &gt_ggc_m_P24constant_descriptor_tree4htab,
    &gt_pch_n_P24constant_descriptor_tree4htab
  },
  {
    &initial_trampoline,
    1,
    sizeof (initial_trampoline),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &weak_decls,
    1,
    sizeof (weak_decls),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &pending_assemble_externals,
    1,
    sizeof (pending_assemble_externals),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &shared_constant_pool,
    1,
    sizeof (shared_constant_pool),
    &gt_ggc_mx_rtx_constant_pool,
    &gt_pch_nx_rtx_constant_pool
  },
  {
    &object_block_htab,
    1,
    sizeof (object_block_htab),
    &gt_ggc_m_P12object_block4htab,
    &gt_pch_n_P12object_block4htab
  },
  {
    &section_htab,
    1,
    sizeof (section_htab),
    &gt_ggc_m_P7section4htab,
    &gt_pch_n_P7section4htab
  },
  {
    &unnamed_sections,
    1,
    sizeof (unnamed_sections),
    &gt_ggc_mx_section,
    &gt_pch_nx_section
  },
  {
    &weak_global_object_name,
    1,
    sizeof (weak_global_object_name),
    (gt_pointer_walker) &gt_ggc_m_S,
    (gt_pointer_walker) &gt_pch_n_S
  },
  {
    &first_global_object_name,
    1,
    sizeof (first_global_object_name),
    (gt_pointer_walker) &gt_ggc_m_S,
    (gt_pointer_walker) &gt_pch_n_S
  },
  LAST_GGC_ROOT_TAB
};

EXPORTED_CONST struct ggc_cache_tab gt_ggc_rc_gt_varasm_h[] = {
  {
    &tm_clone_hash,
    1,
    sizeof (tm_clone_hash),
    &gt_ggc_mx_tree_map,
    &gt_pch_nx_tree_map,
    &tree_map_marked_p
  },
  LAST_GGC_CACHE_TAB
};

EXPORTED_CONST struct ggc_root_tab gt_pch_rc_gt_varasm_h[] = {
  {
    &tm_clone_hash,
    1,
    sizeof (tm_clone_hash),
    &gt_ggc_m_P8tree_map4htab,
    &gt_pch_n_P8tree_map4htab
  },
  LAST_GGC_ROOT_TAB
};

EXPORTED_CONST struct ggc_root_tab gt_pch_rs_gt_varasm_h[] = {
  { &anchor_labelno, 1, sizeof (anchor_labelno), NULL, NULL },
  { &const_labelno, 1, sizeof (const_labelno), NULL, NULL },
  LAST_GGC_ROOT_TAB
};

