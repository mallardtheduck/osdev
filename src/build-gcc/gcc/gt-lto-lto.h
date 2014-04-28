/* Type information for lto/lto.c.
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
gt_ggc_mx_gimple_type_leader_entry_s (void *x_p)
{
  struct gimple_type_leader_entry_s * const x = (struct gimple_type_leader_entry_s *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_9tree_node ((*x).type);
      gt_ggc_m_9tree_node ((*x).leader);
    }
}

void
gt_pch_nx_gimple_type_leader_entry_s (void *x_p)
{
  struct gimple_type_leader_entry_s * const x = (struct gimple_type_leader_entry_s *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_26gimple_type_leader_entry_s))
    {
      gt_pch_n_9tree_node ((*x).type);
      gt_pch_n_9tree_node ((*x).leader);
    }
}

void
gt_pch_p_26gimple_type_leader_entry_s (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct gimple_type_leader_entry_s * x ATTRIBUTE_UNUSED = (struct gimple_type_leader_entry_s *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).type), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).leader), cookie);
}

/* GC roots.  */

static void gt_ggc_ma_real_file_decl_data (void *);
static void
gt_ggc_ma_real_file_decl_data (ATTRIBUTE_UNUSED void *x_p)
{
  if (real_file_decl_data != NULL) {
    size_t i0;
    for (i0 = 0; i0 != (size_t)(real_file_count + 1); i0++) {
      gt_ggc_m_18lto_file_decl_data (real_file_decl_data[i0]);
    }
    ggc_mark (real_file_decl_data);
  }
}

static void gt_pch_pa_real_file_decl_data
    (void *, void *, gt_pointer_operator, void *);
static void gt_pch_pa_real_file_decl_data (ATTRIBUTE_UNUSED void *this_obj,
      ATTRIBUTE_UNUSED void *x_p,
      ATTRIBUTE_UNUSED gt_pointer_operator op,
      ATTRIBUTE_UNUSED void * cookie)
{
  if (real_file_decl_data != NULL) {
    size_t i0;
    for (i0 = 0; i0 != (size_t)(real_file_count + 1) && ((void *)real_file_decl_data == this_obj); i0++) {
      if ((void *)(real_file_decl_data) == this_obj)
        op (&(real_file_decl_data[i0]), cookie);
    }
    if ((void *)(&real_file_decl_data) == this_obj)
      op (&(real_file_decl_data), cookie);
  }
}

static void gt_pch_na_real_file_decl_data (void *);
static void
gt_pch_na_real_file_decl_data (ATTRIBUTE_UNUSED void *x_p)
{
  if (real_file_decl_data != NULL) {
    size_t i0;
    for (i0 = 0; i0 != (size_t)(real_file_count + 1); i0++) {
      gt_pch_n_18lto_file_decl_data (real_file_decl_data[i0]);
    }
    gt_pch_note_object (real_file_decl_data, &real_file_decl_data, gt_pch_pa_real_file_decl_data);
  }
}

static void gt_ggc_ma_all_file_decl_data (void *);
static void
gt_ggc_ma_all_file_decl_data (ATTRIBUTE_UNUSED void *x_p)
{
  if (all_file_decl_data != NULL) {
    size_t i0;
    for (i0 = 0; i0 != (size_t)(lto_stats.num_input_files + 1); i0++) {
      gt_ggc_m_18lto_file_decl_data (all_file_decl_data[i0]);
    }
    ggc_mark (all_file_decl_data);
  }
}

static void gt_pch_pa_all_file_decl_data
    (void *, void *, gt_pointer_operator, void *);
static void gt_pch_pa_all_file_decl_data (ATTRIBUTE_UNUSED void *this_obj,
      ATTRIBUTE_UNUSED void *x_p,
      ATTRIBUTE_UNUSED gt_pointer_operator op,
      ATTRIBUTE_UNUSED void * cookie)
{
  if (all_file_decl_data != NULL) {
    size_t i0;
    for (i0 = 0; i0 != (size_t)(lto_stats.num_input_files + 1) && ((void *)all_file_decl_data == this_obj); i0++) {
      if ((void *)(all_file_decl_data) == this_obj)
        op (&(all_file_decl_data[i0]), cookie);
    }
    if ((void *)(&all_file_decl_data) == this_obj)
      op (&(all_file_decl_data), cookie);
  }
}

static void gt_pch_na_all_file_decl_data (void *);
static void
gt_pch_na_all_file_decl_data (ATTRIBUTE_UNUSED void *x_p)
{
  if (all_file_decl_data != NULL) {
    size_t i0;
    for (i0 = 0; i0 != (size_t)(lto_stats.num_input_files + 1); i0++) {
      gt_pch_n_18lto_file_decl_data (all_file_decl_data[i0]);
    }
    gt_pch_note_object (all_file_decl_data, &all_file_decl_data, gt_pch_pa_all_file_decl_data);
  }
}

static void gt_ggc_ma_gimple_type_leader (void *);
static void
gt_ggc_ma_gimple_type_leader (ATTRIBUTE_UNUSED void *x_p)
{
  if (gimple_type_leader != NULL) {
    size_t i0;
    for (i0 = 0; i0 != (size_t)(GIMPLE_TYPE_LEADER_SIZE); i0++) {
      gt_ggc_m_9tree_node (gimple_type_leader[i0].type);
      gt_ggc_m_9tree_node (gimple_type_leader[i0].leader);
    }
    ggc_mark (gimple_type_leader);
  }
}

static void gt_pch_pa_gimple_type_leader
    (void *, void *, gt_pointer_operator, void *);
static void gt_pch_pa_gimple_type_leader (ATTRIBUTE_UNUSED void *this_obj,
      ATTRIBUTE_UNUSED void *x_p,
      ATTRIBUTE_UNUSED gt_pointer_operator op,
      ATTRIBUTE_UNUSED void * cookie)
{
  if (gimple_type_leader != NULL) {
    size_t i0;
    for (i0 = 0; i0 != (size_t)(GIMPLE_TYPE_LEADER_SIZE) && ((void *)gimple_type_leader == this_obj); i0++) {
      if ((void *)(gimple_type_leader) == this_obj)
        op (&(gimple_type_leader[i0].type), cookie);
      if ((void *)(gimple_type_leader) == this_obj)
        op (&(gimple_type_leader[i0].leader), cookie);
    }
    if ((void *)(&gimple_type_leader) == this_obj)
      op (&(gimple_type_leader), cookie);
  }
}

static void gt_pch_na_gimple_type_leader (void *);
static void
gt_pch_na_gimple_type_leader (ATTRIBUTE_UNUSED void *x_p)
{
  if (gimple_type_leader != NULL) {
    size_t i0;
    for (i0 = 0; i0 != (size_t)(GIMPLE_TYPE_LEADER_SIZE); i0++) {
      gt_pch_n_9tree_node (gimple_type_leader[i0].type);
      gt_pch_n_9tree_node (gimple_type_leader[i0].leader);
    }
    gt_pch_note_object (gimple_type_leader, &gimple_type_leader, gt_pch_pa_gimple_type_leader);
  }
}

EXPORTED_CONST struct ggc_root_tab gt_ggc_r_gt_lto_lto_h[] = {
  {
    &lto_eh_personality_decl,
    1,
    sizeof (lto_eh_personality_decl),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &real_file_decl_data,
    1,
    sizeof (real_file_decl_data),
    &gt_ggc_ma_real_file_decl_data,
    &gt_pch_na_real_file_decl_data
  },
  {
    &all_file_decl_data,
    1,
    sizeof (all_file_decl_data),
    &gt_ggc_ma_all_file_decl_data,
    &gt_pch_na_all_file_decl_data
  },
  {
    &gimple_type_leader,
    1,
    sizeof (gimple_type_leader),
    &gt_ggc_ma_gimple_type_leader,
    &gt_pch_na_gimple_type_leader
  },
  {
    &first_personality_decl,
    1,
    sizeof (first_personality_decl),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  LAST_GGC_ROOT_TAB
};

EXPORTED_CONST struct ggc_cache_tab gt_ggc_rc_gt_lto_lto_h[] = {
  {
    &tree_with_vars,
    1,
    sizeof (tree_with_vars),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node,
    &ggc_marked_p
  },
  {
    &type_hash_cache,
    1,
    sizeof (type_hash_cache),
    &gt_ggc_mx_tree_int_map,
    &gt_pch_nx_tree_int_map,
    &tree_int_map_marked_p
  },
  {
    &gimple_types,
    1,
    sizeof (gimple_types),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node,
    &ggc_marked_p
  },
  LAST_GGC_CACHE_TAB
};

EXPORTED_CONST struct ggc_root_tab gt_pch_rc_gt_lto_lto_h[] = {
  {
    &tree_with_vars,
    1,
    sizeof (tree_with_vars),
    &gt_ggc_m_P9tree_node4htab,
    &gt_pch_n_P9tree_node4htab
  },
  {
    &type_hash_cache,
    1,
    sizeof (type_hash_cache),
    &gt_ggc_m_P12tree_int_map4htab,
    &gt_pch_n_P12tree_int_map4htab
  },
  {
    &gimple_types,
    1,
    sizeof (gimple_types),
    &gt_ggc_m_P9tree_node4htab,
    &gt_pch_n_P9tree_node4htab
  },
  LAST_GGC_ROOT_TAB
};

