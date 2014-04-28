/* Type information for fortran.
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
gt_ggc_mx_module_htab_entry (void *x_p)
{
  struct module_htab_entry * const x = (struct module_htab_entry *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_S ((*x).name);
      gt_ggc_m_9tree_node ((*x).namespace_decl);
      gt_ggc_m_P9tree_node4htab ((*x).decls);
    }
}

void
gt_ggc_mx_lang_decl (void *x_p)
{
  struct lang_decl * const x = (struct lang_decl *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_9tree_node ((*x).saved_descriptor);
      gt_ggc_m_9tree_node ((*x).stringlen);
      gt_ggc_m_9tree_node ((*x).addr);
      gt_ggc_m_9tree_node ((*x).span);
      gt_ggc_m_9tree_node ((*x).token);
      gt_ggc_m_9tree_node ((*x).caf_offset);
    }
}

void
gt_ggc_mx_lang_type (void *x_p)
{
  struct lang_type * const x = (struct lang_type *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      {
        size_t i0;
        size_t l0 = (size_t)(GFC_MAX_DIMENSIONS);
        for (i0 = 0; i0 != l0; i0++) {
          gt_ggc_m_9tree_node ((*x).lbound[i0]);
        }
      }
      {
        size_t i1;
        size_t l1 = (size_t)(GFC_MAX_DIMENSIONS);
        for (i1 = 0; i1 != l1; i1++) {
          gt_ggc_m_9tree_node ((*x).ubound[i1]);
        }
      }
      {
        size_t i2;
        size_t l2 = (size_t)(GFC_MAX_DIMENSIONS);
        for (i2 = 0; i2 != l2; i2++) {
          gt_ggc_m_9tree_node ((*x).stride[i2]);
        }
      }
      gt_ggc_m_9tree_node ((*x).size);
      gt_ggc_m_9tree_node ((*x).offset);
      gt_ggc_m_9tree_node ((*x).dtype);
      gt_ggc_m_9tree_node ((*x).dataptr_type);
      gt_ggc_m_9tree_node ((*x).span);
      {
        size_t i3;
        size_t l3 = (size_t)(2);
        for (i3 = 0; i3 != l3; i3++) {
          gt_ggc_m_9tree_node ((*x).base_decl[i3]);
        }
      }
      gt_ggc_m_9tree_node ((*x).nonrestricted_type);
      gt_ggc_m_9tree_node ((*x).caf_token);
      gt_ggc_m_9tree_node ((*x).caf_offset);
    }
}

void
gt_ggc_m_P17module_htab_entry4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      {
        size_t l0 = (size_t)(((*x)).size);
        if ((*x).entries != NULL) {
          size_t i0;
          for (i0 = 0; i0 != (size_t)(l0); i0++) {
            gt_ggc_m_17module_htab_entry ((*x).entries[i0]);
          }
          ggc_mark ((*x).entries);
        }
      }
    }
}

void
gt_pch_nx_module_htab_entry (void *x_p)
{
  struct module_htab_entry * const x = (struct module_htab_entry *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_17module_htab_entry))
    {
      gt_pch_n_S ((*x).name);
      gt_pch_n_9tree_node ((*x).namespace_decl);
      gt_pch_n_P9tree_node4htab ((*x).decls);
    }
}

void
gt_pch_nx_lang_decl (void *x_p)
{
  struct lang_decl * const x = (struct lang_decl *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_9lang_decl))
    {
      gt_pch_n_9tree_node ((*x).saved_descriptor);
      gt_pch_n_9tree_node ((*x).stringlen);
      gt_pch_n_9tree_node ((*x).addr);
      gt_pch_n_9tree_node ((*x).span);
      gt_pch_n_9tree_node ((*x).token);
      gt_pch_n_9tree_node ((*x).caf_offset);
    }
}

void
gt_pch_nx_lang_type (void *x_p)
{
  struct lang_type * const x = (struct lang_type *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_9lang_type))
    {
      {
        size_t i0;
        size_t l0 = (size_t)(GFC_MAX_DIMENSIONS);
        for (i0 = 0; i0 != l0; i0++) {
          gt_pch_n_9tree_node ((*x).lbound[i0]);
        }
      }
      {
        size_t i1;
        size_t l1 = (size_t)(GFC_MAX_DIMENSIONS);
        for (i1 = 0; i1 != l1; i1++) {
          gt_pch_n_9tree_node ((*x).ubound[i1]);
        }
      }
      {
        size_t i2;
        size_t l2 = (size_t)(GFC_MAX_DIMENSIONS);
        for (i2 = 0; i2 != l2; i2++) {
          gt_pch_n_9tree_node ((*x).stride[i2]);
        }
      }
      gt_pch_n_9tree_node ((*x).size);
      gt_pch_n_9tree_node ((*x).offset);
      gt_pch_n_9tree_node ((*x).dtype);
      gt_pch_n_9tree_node ((*x).dataptr_type);
      gt_pch_n_9tree_node ((*x).span);
      {
        size_t i3;
        size_t l3 = (size_t)(2);
        for (i3 = 0; i3 != l3; i3++) {
          gt_pch_n_9tree_node ((*x).base_decl[i3]);
        }
      }
      gt_pch_n_9tree_node ((*x).nonrestricted_type);
      gt_pch_n_9tree_node ((*x).caf_token);
      gt_pch_n_9tree_node ((*x).caf_offset);
    }
}

void
gt_pch_n_P17module_htab_entry4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_P17module_htab_entry4htab))
    {
      {
        size_t l0 = (size_t)(((*x)).size);
        if ((*x).entries != NULL) {
          size_t i0;
          for (i0 = 0; i0 != (size_t)(l0); i0++) {
            gt_pch_n_17module_htab_entry ((*x).entries[i0]);
          }
          gt_pch_note_object ((*x).entries, x, gt_pch_p_P17module_htab_entry4htab);
        }
      }
    }
}

void
gt_pch_p_17module_htab_entry (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct module_htab_entry * x ATTRIBUTE_UNUSED = (struct module_htab_entry *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).name), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).namespace_decl), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).decls), cookie);
}

void
gt_pch_p_9lang_decl (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct lang_decl * x ATTRIBUTE_UNUSED = (struct lang_decl *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).saved_descriptor), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).stringlen), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).addr), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).span), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).token), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).caf_offset), cookie);
}

void
gt_pch_p_9lang_type (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct lang_type * x ATTRIBUTE_UNUSED = (struct lang_type *)x_p;
  {
    size_t i0;
    size_t l0 = (size_t)(GFC_MAX_DIMENSIONS);
    for (i0 = 0; i0 != l0; i0++) {
      if ((void *)(x) == this_obj)
        op (&((*x).lbound[i0]), cookie);
    }
  }
  {
    size_t i1;
    size_t l1 = (size_t)(GFC_MAX_DIMENSIONS);
    for (i1 = 0; i1 != l1; i1++) {
      if ((void *)(x) == this_obj)
        op (&((*x).ubound[i1]), cookie);
    }
  }
  {
    size_t i2;
    size_t l2 = (size_t)(GFC_MAX_DIMENSIONS);
    for (i2 = 0; i2 != l2; i2++) {
      if ((void *)(x) == this_obj)
        op (&((*x).stride[i2]), cookie);
    }
  }
  if ((void *)(x) == this_obj)
    op (&((*x).size), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).offset), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).dtype), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).dataptr_type), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).span), cookie);
  {
    size_t i3;
    size_t l3 = (size_t)(2);
    for (i3 = 0; i3 != l3; i3++) {
      if ((void *)(x) == this_obj)
        op (&((*x).base_decl[i3]), cookie);
    }
  }
  if ((void *)(x) == this_obj)
    op (&((*x).nonrestricted_type), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).caf_token), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).caf_offset), cookie);
}

void
gt_pch_p_P17module_htab_entry4htab (ATTRIBUTE_UNUSED void *this_obj,
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

EXPORTED_CONST struct ggc_root_tab gt_ggc_r_gtype_fortran_h[] = {
  {
    &gfc_rank_cst[0],
    1 * (GFC_MAX_DIMENSIONS + 1),
    sizeof (gfc_rank_cst[0]),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_sr_kind,
    1,
    sizeof (gfor_fndecl_sr_kind),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_si_kind,
    1,
    sizeof (gfor_fndecl_si_kind),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_sc_kind,
    1,
    sizeof (gfor_fndecl_sc_kind),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_iargc,
    1,
    sizeof (gfor_fndecl_iargc),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_size1,
    1,
    sizeof (gfor_fndecl_size1),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_size0,
    1,
    sizeof (gfor_fndecl_size0),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_convert_char4_to_char1,
    1,
    sizeof (gfor_fndecl_convert_char4_to_char1),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_convert_char1_to_char4,
    1,
    sizeof (gfor_fndecl_convert_char1_to_char4),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_select_string_char4,
    1,
    sizeof (gfor_fndecl_select_string_char4),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_adjustr_char4,
    1,
    sizeof (gfor_fndecl_adjustr_char4),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_adjustl_char4,
    1,
    sizeof (gfor_fndecl_adjustl_char4),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_string_minmax_char4,
    1,
    sizeof (gfor_fndecl_string_minmax_char4),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_string_trim_char4,
    1,
    sizeof (gfor_fndecl_string_trim_char4),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_string_verify_char4,
    1,
    sizeof (gfor_fndecl_string_verify_char4),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_string_scan_char4,
    1,
    sizeof (gfor_fndecl_string_scan_char4),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_string_index_char4,
    1,
    sizeof (gfor_fndecl_string_index_char4),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_string_len_trim_char4,
    1,
    sizeof (gfor_fndecl_string_len_trim_char4),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_concat_string_char4,
    1,
    sizeof (gfor_fndecl_concat_string_char4),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_compare_string_char4,
    1,
    sizeof (gfor_fndecl_compare_string_char4),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_select_string,
    1,
    sizeof (gfor_fndecl_select_string),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_adjustr,
    1,
    sizeof (gfor_fndecl_adjustr),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_adjustl,
    1,
    sizeof (gfor_fndecl_adjustl),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_string_minmax,
    1,
    sizeof (gfor_fndecl_string_minmax),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_string_trim,
    1,
    sizeof (gfor_fndecl_string_trim),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_string_verify,
    1,
    sizeof (gfor_fndecl_string_verify),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_string_scan,
    1,
    sizeof (gfor_fndecl_string_scan),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_string_index,
    1,
    sizeof (gfor_fndecl_string_index),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_string_len_trim,
    1,
    sizeof (gfor_fndecl_string_len_trim),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_concat_string,
    1,
    sizeof (gfor_fndecl_concat_string),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_compare_string,
    1,
    sizeof (gfor_fndecl_compare_string),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_zgemm,
    1,
    sizeof (gfor_fndecl_zgemm),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_cgemm,
    1,
    sizeof (gfor_fndecl_cgemm),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_dgemm,
    1,
    sizeof (gfor_fndecl_dgemm),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_sgemm,
    1,
    sizeof (gfor_fndecl_sgemm),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_math_ishftc16,
    1,
    sizeof (gfor_fndecl_math_ishftc16),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_math_ishftc8,
    1,
    sizeof (gfor_fndecl_math_ishftc8),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_math_ishftc4,
    1,
    sizeof (gfor_fndecl_math_ishftc4),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_math_powi[0][0].integer,
    1 * (4) * (3),
    sizeof (gfor_fndecl_math_powi[0][0]),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_math_powi[0][0].real,
    1 * (4) * (3),
    sizeof (gfor_fndecl_math_powi[0][0]),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_math_powi[0][0].cmplx,
    1 * (4) * (3),
    sizeof (gfor_fndecl_math_powi[0][0]),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfort_gvar_caf_this_image,
    1,
    sizeof (gfort_gvar_caf_this_image),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfort_gvar_caf_num_images,
    1,
    sizeof (gfort_gvar_caf_num_images),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_caf_error_stop_str,
    1,
    sizeof (gfor_fndecl_caf_error_stop_str),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_caf_error_stop,
    1,
    sizeof (gfor_fndecl_caf_error_stop),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_caf_sync_images,
    1,
    sizeof (gfor_fndecl_caf_sync_images),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_caf_sync_all,
    1,
    sizeof (gfor_fndecl_caf_sync_all),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_caf_end_critical,
    1,
    sizeof (gfor_fndecl_caf_end_critical),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_caf_critical,
    1,
    sizeof (gfor_fndecl_caf_critical),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_caf_deregister,
    1,
    sizeof (gfor_fndecl_caf_deregister),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_caf_register,
    1,
    sizeof (gfor_fndecl_caf_register),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_caf_finalize,
    1,
    sizeof (gfor_fndecl_caf_finalize),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_caf_init,
    1,
    sizeof (gfor_fndecl_caf_init),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_associated,
    1,
    sizeof (gfor_fndecl_associated),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_in_unpack,
    1,
    sizeof (gfor_fndecl_in_unpack),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_in_pack,
    1,
    sizeof (gfor_fndecl_in_pack),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_fdate,
    1,
    sizeof (gfor_fndecl_fdate),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_ctime,
    1,
    sizeof (gfor_fndecl_ctime),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_ttynam,
    1,
    sizeof (gfor_fndecl_ttynam),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_set_options,
    1,
    sizeof (gfor_fndecl_set_options),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_set_fpe,
    1,
    sizeof (gfor_fndecl_set_fpe),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_generate_error,
    1,
    sizeof (gfor_fndecl_generate_error),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_os_error,
    1,
    sizeof (gfor_fndecl_os_error),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_runtime_warning_at,
    1,
    sizeof (gfor_fndecl_runtime_warning_at),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_runtime_error_at,
    1,
    sizeof (gfor_fndecl_runtime_error_at),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_runtime_error,
    1,
    sizeof (gfor_fndecl_runtime_error),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_error_stop_string,
    1,
    sizeof (gfor_fndecl_error_stop_string),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_error_stop_numeric,
    1,
    sizeof (gfor_fndecl_error_stop_numeric),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_stop_string,
    1,
    sizeof (gfor_fndecl_stop_string),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_stop_numeric_f08,
    1,
    sizeof (gfor_fndecl_stop_numeric_f08),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_stop_numeric,
    1,
    sizeof (gfor_fndecl_stop_numeric),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_pause_string,
    1,
    sizeof (gfor_fndecl_pause_string),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfor_fndecl_pause_numeric,
    1,
    sizeof (gfor_fndecl_pause_numeric),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfc_static_ctors,
    1,
    sizeof (gfc_static_ctors),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfc_charlen_type_node,
    1,
    sizeof (gfc_charlen_type_node),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &complex_float128_type_node,
    1,
    sizeof (complex_float128_type_node),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &float128_type_node,
    1,
    sizeof (float128_type_node),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &pchar_type_node,
    1,
    sizeof (pchar_type_node),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &prvoid_type_node,
    1,
    sizeof (prvoid_type_node),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &pvoid_type_node,
    1,
    sizeof (pvoid_type_node),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &ppvoid_type_node,
    1,
    sizeof (ppvoid_type_node),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfc_character1_type_node,
    1,
    sizeof (gfc_character1_type_node),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfc_array_range_type,
    1,
    sizeof (gfc_array_range_type),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gfc_array_index_type,
    1,
    sizeof (gfc_array_index_type),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  LAST_GGC_ROOT_TAB
};

extern const struct ggc_root_tab gt_ggc_r_gt_coverage_h[];
extern const struct ggc_root_tab gt_ggc_r_gt_caller_save_h[];
extern const struct ggc_root_tab gt_ggc_r_gt_symtab_h[];
extern const struct ggc_root_tab gt_ggc_r_gt_alias_h[];
extern const struct ggc_root_tab gt_ggc_r_gt_cselib_h[];
extern const struct ggc_root_tab gt_ggc_r_gt_cgraph_h[];
extern const struct ggc_root_tab gt_ggc_r_gt_dbxout_h[];
extern const struct ggc_root_tab gt_ggc_r_gt_dwarf2asm_h[];
extern const struct ggc_root_tab gt_ggc_r_gt_dwarf2cfi_h[];
extern const struct ggc_root_tab gt_ggc_r_gt_dwarf2out_h[];
extern const struct ggc_root_tab gt_ggc_r_gt_tree_vect_generic_h[];
extern const struct ggc_root_tab gt_ggc_r_gt_dojump_h[];
extern const struct ggc_root_tab gt_ggc_r_gt_emit_rtl_h[];
extern const struct ggc_root_tab gt_ggc_r_gt_explow_h[];
extern const struct ggc_root_tab gt_ggc_r_gt_expr_h[];
extern const struct ggc_root_tab gt_ggc_r_gt_function_h[];
extern const struct ggc_root_tab gt_ggc_r_gt_except_h[];
extern const struct ggc_root_tab gt_ggc_r_gt_gcse_h[];
extern const struct ggc_root_tab gt_ggc_r_gt_godump_h[];
extern const struct ggc_root_tab gt_ggc_r_gt_optabs_h[];
extern const struct ggc_root_tab gt_ggc_r_gt_cfgrtl_h[];
extern const struct ggc_root_tab gt_ggc_r_gt_sdbout_h[];
extern const struct ggc_root_tab gt_ggc_r_gt_stor_layout_h[];
extern const struct ggc_root_tab gt_ggc_r_gt_stringpool_h[];
extern const struct ggc_root_tab gt_ggc_r_gt_tree_h[];
extern const struct ggc_root_tab gt_ggc_r_gt_varasm_h[];
extern const struct ggc_root_tab gt_ggc_r_gt_tree_mudflap_h[];
extern const struct ggc_root_tab gt_ggc_r_gt_tree_ssa_address_h[];
extern const struct ggc_root_tab gt_ggc_r_gt_gimplify_h[];
extern const struct ggc_root_tab gt_ggc_r_gt_tree_scalar_evolution_h[];
extern const struct ggc_root_tab gt_ggc_r_gt_tree_profile_h[];
extern const struct ggc_root_tab gt_ggc_r_gt_tree_nested_h[];
extern const struct ggc_root_tab gt_ggc_r_gt_tree_parloops_h[];
extern const struct ggc_root_tab gt_ggc_r_gt_omp_low_h[];
extern const struct ggc_root_tab gt_ggc_r_gt_targhooks_h[];
extern const struct ggc_root_tab gt_ggc_r_gt_i386_h[];
extern const struct ggc_root_tab gt_ggc_r_gt_passes_h[];
extern const struct ggc_root_tab gt_ggc_r_gt_cgraphunit_h[];
extern const struct ggc_root_tab gt_ggc_r_gt_cgraphclones_h[];
extern const struct ggc_root_tab gt_ggc_r_gt_tree_ssa_propagate_h[];
extern const struct ggc_root_tab gt_ggc_r_gtype_desc_c[];
extern const struct ggc_root_tab gt_ggc_r_gt_asan_h[];
extern const struct ggc_root_tab gt_ggc_r_gt_fortran_f95_lang_h[];
extern const struct ggc_root_tab gt_ggc_r_gt_fortran_trans_decl_h[];
extern const struct ggc_root_tab gt_ggc_r_gt_fortran_trans_intrinsic_h[];
extern const struct ggc_root_tab gt_ggc_r_gt_fortran_trans_io_h[];
extern const struct ggc_root_tab gt_ggc_r_gt_fortran_trans_stmt_h[];
extern const struct ggc_root_tab gt_ggc_r_gt_fortran_trans_types_h[];
extern const struct ggc_root_tab gt_ggc_r_gtype_fortran_h[];
EXPORTED_CONST struct ggc_root_tab * const gt_ggc_rtab[] = {
  gt_ggc_r_gt_coverage_h,
  gt_ggc_r_gt_caller_save_h,
  gt_ggc_r_gt_symtab_h,
  gt_ggc_r_gt_alias_h,
  gt_ggc_r_gt_cselib_h,
  gt_ggc_r_gt_cgraph_h,
  gt_ggc_r_gt_dbxout_h,
  gt_ggc_r_gt_dwarf2asm_h,
  gt_ggc_r_gt_dwarf2cfi_h,
  gt_ggc_r_gt_dwarf2out_h,
  gt_ggc_r_gt_tree_vect_generic_h,
  gt_ggc_r_gt_dojump_h,
  gt_ggc_r_gt_emit_rtl_h,
  gt_ggc_r_gt_explow_h,
  gt_ggc_r_gt_expr_h,
  gt_ggc_r_gt_function_h,
  gt_ggc_r_gt_except_h,
  gt_ggc_r_gt_gcse_h,
  gt_ggc_r_gt_godump_h,
  gt_ggc_r_gt_optabs_h,
  gt_ggc_r_gt_cfgrtl_h,
  gt_ggc_r_gt_sdbout_h,
  gt_ggc_r_gt_stor_layout_h,
  gt_ggc_r_gt_stringpool_h,
  gt_ggc_r_gt_tree_h,
  gt_ggc_r_gt_varasm_h,
  gt_ggc_r_gt_tree_mudflap_h,
  gt_ggc_r_gt_tree_ssa_address_h,
  gt_ggc_r_gt_gimplify_h,
  gt_ggc_r_gt_tree_scalar_evolution_h,
  gt_ggc_r_gt_tree_profile_h,
  gt_ggc_r_gt_tree_nested_h,
  gt_ggc_r_gt_tree_parloops_h,
  gt_ggc_r_gt_omp_low_h,
  gt_ggc_r_gt_targhooks_h,
  gt_ggc_r_gt_i386_h,
  gt_ggc_r_gt_passes_h,
  gt_ggc_r_gt_cgraphunit_h,
  gt_ggc_r_gt_cgraphclones_h,
  gt_ggc_r_gt_tree_ssa_propagate_h,
  gt_ggc_r_gtype_desc_c,
  gt_ggc_r_gt_asan_h,
  gt_ggc_r_gt_fortran_f95_lang_h,
  gt_ggc_r_gt_fortran_trans_decl_h,
  gt_ggc_r_gt_fortran_trans_intrinsic_h,
  gt_ggc_r_gt_fortran_trans_io_h,
  gt_ggc_r_gt_fortran_trans_stmt_h,
  gt_ggc_r_gt_fortran_trans_types_h,
  gt_ggc_r_gtype_fortran_h,
  NULL
};
extern const struct ggc_root_tab gt_ggc_rd_gt_alias_h[];
extern const struct ggc_root_tab gt_ggc_rd_gt_bitmap_h[];
extern const struct ggc_root_tab gt_ggc_rd_gt_emit_rtl_h[];
extern const struct ggc_root_tab gt_ggc_rd_gt_lists_h[];
extern const struct ggc_root_tab gt_ggc_rd_gt_tree_iterator_h[];
extern const struct ggc_root_tab gt_ggc_rd_gt_tree_phinodes_h[];
EXPORTED_CONST struct ggc_root_tab * const gt_ggc_deletable_rtab[] = {
  gt_ggc_rd_gt_alias_h,
  gt_ggc_rd_gt_bitmap_h,
  gt_ggc_rd_gt_emit_rtl_h,
  gt_ggc_rd_gt_lists_h,
  gt_ggc_rd_gt_tree_iterator_h,
  gt_ggc_rd_gt_tree_phinodes_h,
  NULL
};
extern const struct ggc_cache_tab gt_ggc_rc_gt_emit_rtl_h[];
extern const struct ggc_cache_tab gt_ggc_rc_gt_function_h[];
extern const struct ggc_cache_tab gt_ggc_rc_gt_tree_h[];
extern const struct ggc_cache_tab gt_ggc_rc_gt_varasm_h[];
extern const struct ggc_cache_tab gt_ggc_rc_gt_gimple_h[];
extern const struct ggc_cache_tab gt_ggc_rc_gt_i386_h[];
extern const struct ggc_cache_tab gt_ggc_rc_gt_trans_mem_h[];
EXPORTED_CONST struct ggc_cache_tab * const gt_ggc_cache_rtab[] = {
  gt_ggc_rc_gt_emit_rtl_h,
  gt_ggc_rc_gt_function_h,
  gt_ggc_rc_gt_tree_h,
  gt_ggc_rc_gt_varasm_h,
  gt_ggc_rc_gt_gimple_h,
  gt_ggc_rc_gt_i386_h,
  gt_ggc_rc_gt_trans_mem_h,
  NULL
};
extern const struct ggc_root_tab gt_pch_rc_gt_emit_rtl_h[];
extern const struct ggc_root_tab gt_pch_rc_gt_function_h[];
extern const struct ggc_root_tab gt_pch_rc_gt_tree_h[];
extern const struct ggc_root_tab gt_pch_rc_gt_varasm_h[];
extern const struct ggc_root_tab gt_pch_rc_gt_gimple_h[];
extern const struct ggc_root_tab gt_pch_rc_gt_i386_h[];
extern const struct ggc_root_tab gt_pch_rc_gt_trans_mem_h[];
EXPORTED_CONST struct ggc_root_tab * const gt_pch_cache_rtab[] = {
  gt_pch_rc_gt_emit_rtl_h,
  gt_pch_rc_gt_function_h,
  gt_pch_rc_gt_tree_h,
  gt_pch_rc_gt_varasm_h,
  gt_pch_rc_gt_gimple_h,
  gt_pch_rc_gt_i386_h,
  gt_pch_rc_gt_trans_mem_h,
  NULL
};
EXPORTED_CONST struct ggc_root_tab gt_pch_rs_gtype_fortran_h[] = {
  { &gfor_fndecl_math_powi, 1, sizeof (gfor_fndecl_math_powi), NULL, NULL },
  LAST_GGC_ROOT_TAB
};

extern const struct ggc_root_tab gt_pch_rs_gt_alias_h[];
extern const struct ggc_root_tab gt_pch_rs_gt_dbxout_h[];
extern const struct ggc_root_tab gt_pch_rs_gt_dwarf2asm_h[];
extern const struct ggc_root_tab gt_pch_rs_gt_dwarf2cfi_h[];
extern const struct ggc_root_tab gt_pch_rs_gt_dwarf2out_h[];
extern const struct ggc_root_tab gt_pch_rs_gt_tree_vect_generic_h[];
extern const struct ggc_root_tab gt_pch_rs_gt_emit_rtl_h[];
extern const struct ggc_root_tab gt_pch_rs_gt_function_h[];
extern const struct ggc_root_tab gt_pch_rs_gt_except_h[];
extern const struct ggc_root_tab gt_pch_rs_gt_sdbout_h[];
extern const struct ggc_root_tab gt_pch_rs_gt_tree_h[];
extern const struct ggc_root_tab gt_pch_rs_gt_varasm_h[];
extern const struct ggc_root_tab gt_pch_rs_gt_gimplify_h[];
extern const struct ggc_root_tab gt_pch_rs_gt_omp_low_h[];
extern const struct ggc_root_tab gt_pch_rs_gt_cgraphclones_h[];
extern const struct ggc_root_tab gt_pch_rs_gtype_desc_c[];
extern const struct ggc_root_tab gt_pch_rs_gt_fortran_trans_intrinsic_h[];
extern const struct ggc_root_tab gt_pch_rs_gt_fortran_trans_io_h[];
extern const struct ggc_root_tab gt_pch_rs_gtype_fortran_h[];
EXPORTED_CONST struct ggc_root_tab * const gt_pch_scalar_rtab[] = {
  gt_pch_rs_gt_alias_h,
  gt_pch_rs_gt_dbxout_h,
  gt_pch_rs_gt_dwarf2asm_h,
  gt_pch_rs_gt_dwarf2cfi_h,
  gt_pch_rs_gt_dwarf2out_h,
  gt_pch_rs_gt_tree_vect_generic_h,
  gt_pch_rs_gt_emit_rtl_h,
  gt_pch_rs_gt_function_h,
  gt_pch_rs_gt_except_h,
  gt_pch_rs_gt_sdbout_h,
  gt_pch_rs_gt_tree_h,
  gt_pch_rs_gt_varasm_h,
  gt_pch_rs_gt_gimplify_h,
  gt_pch_rs_gt_omp_low_h,
  gt_pch_rs_gt_cgraphclones_h,
  gt_pch_rs_gtype_desc_c,
  gt_pch_rs_gt_fortran_trans_intrinsic_h,
  gt_pch_rs_gt_fortran_trans_io_h,
  gt_pch_rs_gtype_fortran_h,
  NULL
};
