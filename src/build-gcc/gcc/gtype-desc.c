/* Type information for GCC.
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
#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "tm.h"
#include "hashtab.h"
#include "splay-tree.h"
#include "obstack.h"
#include "bitmap.h"
#include "input.h"
#include "tree.h"
#include "rtl.h"
#include "function.h"
#include "insn-config.h"
#include "expr.h"
#include "hard-reg-set.h"
#include "basic-block.h"
#include "cselib.h"
#include "insn-addr.h"
#include "optabs.h"
#include "libfuncs.h"
#include "debug.h"
#include "ggc.h"
#include "cgraph.h"
#include "tree-flow.h"
#include "reload.h"
#include "cpp-id-data.h"
#include "tree-chrec.h"
#include "except.h"
#include "output.h"
#include "gimple.h"
#include "cfgloop.h"
#include "target.h"
#include "ipa-prop.h"
#include "lto-streamer.h"
#include "target-globals.h"
#include "ipa-inline.h"
#include "dwarf2out.h"

/* See definition in function.h.  */
#undef cfun

void
gt_ggc_mx_vec_inline_summary_t_va_gc_ (void *x_p)
{
  vec<inline_summary_t,va_gc> * const x = (vec<inline_summary_t,va_gc> *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_mx (x);
    }
}

void
gt_ggc_mx (struct inline_summary& x_r ATTRIBUTE_UNUSED)
{
  struct inline_summary * ATTRIBUTE_UNUSED x = &x_r;
  gt_ggc_m_20vec_condition_va_gc_ ((*x).conds);
  gt_ggc_m_26vec_size_time_entry_va_gc_ ((*x).entry);
}

void
gt_ggc_mx_vec_size_time_entry_va_gc_ (void *x_p)
{
  vec<size_time_entry,va_gc> * const x = (vec<size_time_entry,va_gc> *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_mx (x);
    }
}

void
gt_ggc_mx (struct size_time_entry& x_r ATTRIBUTE_UNUSED)
{
  struct size_time_entry * ATTRIBUTE_UNUSED x = &x_r;
}

void
gt_ggc_mx_vec_condition_va_gc_ (void *x_p)
{
  vec<condition,va_gc> * const x = (vec<condition,va_gc> *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_mx (x);
    }
}

void
gt_ggc_mx (struct condition& x_r ATTRIBUTE_UNUSED)
{
  struct condition * ATTRIBUTE_UNUSED x = &x_r;
  gt_ggc_m_9tree_node ((*x).val);
}

void
gt_ggc_mx_lto_in_decl_state (void *x_p)
{
  struct lto_in_decl_state * const x = (struct lto_in_decl_state *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      {
        size_t i0;
        size_t l0 = (size_t)(LTO_N_DECL_STREAMS);
        for (i0 = 0; i0 != l0; i0++) {
          {
            size_t l1 = (size_t)(((*x).streams[i0]).size);
            if ((*x).streams[i0].trees != NULL) {
              size_t i1;
              for (i1 = 0; i1 != (size_t)(l1); i1++) {
                gt_ggc_m_9tree_node ((*x).streams[i0].trees[i1]);
              }
              ggc_mark ((*x).streams[i0].trees);
            }
          }
        }
      }
      gt_ggc_m_9tree_node ((*x).fn_decl);
    }
}

void
gt_ggc_mx_vec_ipa_edge_args_t_va_gc_ (void *x_p)
{
  vec<ipa_edge_args_t,va_gc> * const x = (vec<ipa_edge_args_t,va_gc> *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_mx (x);
    }
}

void
gt_ggc_mx (struct ipa_edge_args& x_r ATTRIBUTE_UNUSED)
{
  struct ipa_edge_args * ATTRIBUTE_UNUSED x = &x_r;
  gt_ggc_m_26vec_ipa_jump_func_t_va_gc_ ((*x).jump_functions);
}

void
gt_ggc_mx_vec_ipa_agg_replacement_value_p_va_gc_ (void *x_p)
{
  vec<ipa_agg_replacement_value_p,va_gc> * const x = (vec<ipa_agg_replacement_value_p,va_gc> *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_mx (x);
    }
}

void
gt_ggc_mx (struct ipa_agg_replacement_value *& x)
{
  if (x)
    gt_ggc_mx_ipa_agg_replacement_value ((void *) x);
}

void
gt_ggc_mx_vec_ipa_jump_func_t_va_gc_ (void *x_p)
{
  vec<ipa_jump_func_t,va_gc> * const x = (vec<ipa_jump_func_t,va_gc> *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_mx (x);
    }
}

void
gt_ggc_mx (struct ipa_jump_func& x_r ATTRIBUTE_UNUSED)
{
  struct ipa_jump_func * ATTRIBUTE_UNUSED x = &x_r;
  gt_ggc_m_28vec_ipa_agg_jf_item_t_va_gc_ ((*x).agg.items);
  switch (((*x)).type)
    {
    case IPA_JF_KNOWN_TYPE:
      gt_ggc_m_9tree_node ((*x).value.known_type.base_type);
      gt_ggc_m_9tree_node ((*x).value.known_type.component_type);
      break;
    case IPA_JF_CONST:
      gt_ggc_m_9tree_node ((*x).value.constant);
      break;
    case IPA_JF_PASS_THROUGH:
      gt_ggc_m_9tree_node ((*x).value.pass_through.operand);
      break;
    case IPA_JF_ANCESTOR:
      gt_ggc_m_9tree_node ((*x).value.ancestor.type);
      break;
    default:
      break;
    }
}

void
gt_ggc_mx_vec_ipa_agg_jf_item_t_va_gc_ (void *x_p)
{
  vec<ipa_agg_jf_item_t,va_gc> * const x = (vec<ipa_agg_jf_item_t,va_gc> *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_mx (x);
    }
}

void
gt_ggc_mx (struct ipa_agg_jf_item& x_r ATTRIBUTE_UNUSED)
{
  struct ipa_agg_jf_item * ATTRIBUTE_UNUSED x = &x_r;
  gt_ggc_m_9tree_node ((*x).value);
}

void
gt_ggc_mx_ssa_operand_memory_d (void *x_p)
{
  struct ssa_operand_memory_d * x = (struct ssa_operand_memory_d *)x_p;
  struct ssa_operand_memory_d * xlimit = x;
  while (ggc_test_and_set_mark (xlimit))
   xlimit = ((*xlimit).next);
  while (x != xlimit)
    {
      gt_ggc_m_20ssa_operand_memory_d ((*x).next);
      x = ((*x).next);
    }
}

void
gt_ggc_mx_vec_gimple_va_gc_ (void *x_p)
{
  vec<gimple,va_gc> * const x = (vec<gimple,va_gc> *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_mx (x);
    }
}

void
gt_ggc_mx (union gimple_statement_d *& x)
{
  if (x)
    gt_ggc_mx_gimple_statement_d ((void *) x);
}

void
gt_ggc_mx_tm_restart_node (void *x_p)
{
  struct tm_restart_node * const x = (struct tm_restart_node *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_18gimple_statement_d ((*x).stmt);
      gt_ggc_m_9tree_node ((*x).label_or_list);
    }
}

void
gt_ggc_mx_throw_stmt_node (void *x_p)
{
  struct throw_stmt_node * const x = (struct throw_stmt_node *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_18gimple_statement_d ((*x).stmt);
    }
}

void
gt_ggc_mx_vec_eh_landing_pad_va_gc_ (void *x_p)
{
  vec<eh_landing_pad,va_gc> * const x = (vec<eh_landing_pad,va_gc> *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_mx (x);
    }
}

void
gt_ggc_mx (struct eh_landing_pad_d *& x)
{
  if (x)
    gt_ggc_mx_eh_landing_pad_d ((void *) x);
}

void
gt_ggc_mx_vec_eh_region_va_gc_ (void *x_p)
{
  vec<eh_region,va_gc> * const x = (vec<eh_region,va_gc> *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_mx (x);
    }
}

void
gt_ggc_mx (struct eh_region_d *& x)
{
  if (x)
    gt_ggc_mx_eh_region_d ((void *) x);
}

void
gt_ggc_mx_eh_catch_d (void *x_p)
{
  struct eh_catch_d * const x = (struct eh_catch_d *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_10eh_catch_d ((*x).next_catch);
      gt_ggc_m_10eh_catch_d ((*x).prev_catch);
      gt_ggc_m_9tree_node ((*x).type_list);
      gt_ggc_m_9tree_node ((*x).filter_list);
      gt_ggc_m_9tree_node ((*x).label);
    }
}

void
gt_ggc_mx_eh_landing_pad_d (void *x_p)
{
  struct eh_landing_pad_d * const x = (struct eh_landing_pad_d *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_16eh_landing_pad_d ((*x).next_lp);
      gt_ggc_m_11eh_region_d ((*x).region);
      gt_ggc_m_9tree_node ((*x).post_landing_pad);
      gt_ggc_m_7rtx_def ((*x).landing_pad);
    }
}

void
gt_ggc_mx_eh_region_d (void *x_p)
{
  struct eh_region_d * const x = (struct eh_region_d *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_11eh_region_d ((*x).outer);
      gt_ggc_m_11eh_region_d ((*x).inner);
      gt_ggc_m_11eh_region_d ((*x).next_peer);
      switch ((*x).type)
        {
        case ERT_TRY:
          gt_ggc_m_10eh_catch_d ((*x).u.eh_try.first_catch);
          gt_ggc_m_10eh_catch_d ((*x).u.eh_try.last_catch);
          break;
        case ERT_ALLOWED_EXCEPTIONS:
          gt_ggc_m_9tree_node ((*x).u.allowed.type_list);
          gt_ggc_m_9tree_node ((*x).u.allowed.label);
          break;
        case ERT_MUST_NOT_THROW:
          gt_ggc_m_9tree_node ((*x).u.must_not_throw.failure_decl);
          break;
        default:
          break;
        }
      gt_ggc_m_16eh_landing_pad_d ((*x).landing_pads);
      gt_ggc_m_7rtx_def ((*x).exc_ptr_reg);
      gt_ggc_m_7rtx_def ((*x).filter_reg);
    }
}

void
gt_ggc_mx_vec_dw_cfi_ref_va_gc_ (void *x_p)
{
  vec<dw_cfi_ref,va_gc> * const x = (vec<dw_cfi_ref,va_gc> *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_mx (x);
    }
}

void
gt_ggc_mx (struct dw_cfi_struct *& x)
{
  if (x)
    gt_ggc_mx_dw_cfi_struct ((void *) x);
}

void
gt_ggc_mx_dw_loc_descr_struct (void *x_p)
{
  struct dw_loc_descr_struct * const x = (struct dw_loc_descr_struct *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_19dw_loc_descr_struct ((*x).dw_loc_next);
      gt_ggc_m_23addr_table_entry_struct ((*x).dw_loc_oprnd1.val_entry);
      switch (((*x).dw_loc_oprnd1).val_class)
        {
        case dw_val_class_addr:
          gt_ggc_m_7rtx_def ((*x).dw_loc_oprnd1.v.val_addr);
          break;
        case dw_val_class_offset:
          break;
        case dw_val_class_loc_list:
          gt_ggc_m_18dw_loc_list_struct ((*x).dw_loc_oprnd1.v.val_loc_list);
          break;
        case dw_val_class_loc:
          gt_ggc_m_19dw_loc_descr_struct ((*x).dw_loc_oprnd1.v.val_loc);
          break;
        default:
          break;
        case dw_val_class_unsigned_const:
          break;
        case dw_val_class_const_double:
          break;
        case dw_val_class_vec:
          gt_ggc_m_S ((*x).dw_loc_oprnd1.v.val_vec.array);
          break;
        case dw_val_class_die_ref:
          gt_ggc_m_10die_struct ((*x).dw_loc_oprnd1.v.val_die_ref.die);
          break;
        case dw_val_class_fde_ref:
          break;
        case dw_val_class_str:
          gt_ggc_m_20indirect_string_node ((*x).dw_loc_oprnd1.v.val_str);
          break;
        case dw_val_class_lbl_id:
          gt_ggc_m_S ((*x).dw_loc_oprnd1.v.val_lbl_id);
          break;
        case dw_val_class_flag:
          break;
        case dw_val_class_file:
          gt_ggc_m_15dwarf_file_data ((*x).dw_loc_oprnd1.v.val_file);
          break;
        case dw_val_class_data8:
          break;
        case dw_val_class_decl_ref:
          gt_ggc_m_9tree_node ((*x).dw_loc_oprnd1.v.val_decl_ref);
          break;
        case dw_val_class_vms_delta:
          gt_ggc_m_S ((*x).dw_loc_oprnd1.v.val_vms_delta.lbl1);
          gt_ggc_m_S ((*x).dw_loc_oprnd1.v.val_vms_delta.lbl2);
          break;
        }
      gt_ggc_m_23addr_table_entry_struct ((*x).dw_loc_oprnd2.val_entry);
      switch (((*x).dw_loc_oprnd2).val_class)
        {
        case dw_val_class_addr:
          gt_ggc_m_7rtx_def ((*x).dw_loc_oprnd2.v.val_addr);
          break;
        case dw_val_class_offset:
          break;
        case dw_val_class_loc_list:
          gt_ggc_m_18dw_loc_list_struct ((*x).dw_loc_oprnd2.v.val_loc_list);
          break;
        case dw_val_class_loc:
          gt_ggc_m_19dw_loc_descr_struct ((*x).dw_loc_oprnd2.v.val_loc);
          break;
        default:
          break;
        case dw_val_class_unsigned_const:
          break;
        case dw_val_class_const_double:
          break;
        case dw_val_class_vec:
          gt_ggc_m_S ((*x).dw_loc_oprnd2.v.val_vec.array);
          break;
        case dw_val_class_die_ref:
          gt_ggc_m_10die_struct ((*x).dw_loc_oprnd2.v.val_die_ref.die);
          break;
        case dw_val_class_fde_ref:
          break;
        case dw_val_class_str:
          gt_ggc_m_20indirect_string_node ((*x).dw_loc_oprnd2.v.val_str);
          break;
        case dw_val_class_lbl_id:
          gt_ggc_m_S ((*x).dw_loc_oprnd2.v.val_lbl_id);
          break;
        case dw_val_class_flag:
          break;
        case dw_val_class_file:
          gt_ggc_m_15dwarf_file_data ((*x).dw_loc_oprnd2.v.val_file);
          break;
        case dw_val_class_data8:
          break;
        case dw_val_class_decl_ref:
          gt_ggc_m_9tree_node ((*x).dw_loc_oprnd2.v.val_decl_ref);
          break;
        case dw_val_class_vms_delta:
          gt_ggc_m_S ((*x).dw_loc_oprnd2.v.val_vms_delta.lbl1);
          gt_ggc_m_S ((*x).dw_loc_oprnd2.v.val_vms_delta.lbl2);
          break;
        }
    }
}

void
gt_ggc_mx_dw_cfi_struct (void *x_p)
{
  struct dw_cfi_struct * const x = (struct dw_cfi_struct *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      switch (dw_cfi_oprnd1_desc (((*x)).dw_cfi_opc))
        {
        case dw_cfi_oprnd_reg_num:
          break;
        case dw_cfi_oprnd_offset:
          break;
        case dw_cfi_oprnd_addr:
          gt_ggc_m_S ((*x).dw_cfi_oprnd1.dw_cfi_addr);
          break;
        case dw_cfi_oprnd_loc:
          gt_ggc_m_19dw_loc_descr_struct ((*x).dw_cfi_oprnd1.dw_cfi_loc);
          break;
        default:
          break;
        }
      switch (dw_cfi_oprnd2_desc (((*x)).dw_cfi_opc))
        {
        case dw_cfi_oprnd_reg_num:
          break;
        case dw_cfi_oprnd_offset:
          break;
        case dw_cfi_oprnd_addr:
          gt_ggc_m_S ((*x).dw_cfi_oprnd2.dw_cfi_addr);
          break;
        case dw_cfi_oprnd_loc:
          gt_ggc_m_19dw_loc_descr_struct ((*x).dw_cfi_oprnd2.dw_cfi_loc);
          break;
        default:
          break;
        }
    }
}

void
gt_ggc_mx_ipa_agg_replacement_value (void *x_p)
{
  struct ipa_agg_replacement_value * const x = (struct ipa_agg_replacement_value *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_25ipa_agg_replacement_value ((*x).next);
      gt_ggc_m_9tree_node ((*x).value);
    }
}

void
gt_ggc_mx_constant_descriptor_tree (void *x_p)
{
  struct constant_descriptor_tree * const x = (struct constant_descriptor_tree *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_7rtx_def ((*x).rtl);
      gt_ggc_m_9tree_node ((*x).value);
    }
}

void
gt_ggc_mx_asm_node (void *x_p)
{
  struct asm_node * const x = (struct asm_node *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_8asm_node ((*x).next);
      gt_ggc_m_9tree_node ((*x).asm_str);
    }
}

void
gt_ggc_mx_cgraph_indirect_call_info (void *x_p)
{
  struct cgraph_indirect_call_info * const x = (struct cgraph_indirect_call_info *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_9tree_node ((*x).otr_type);
    }
}

void
gt_ggc_mx_cgraph_function_version_info (void *x_p)
{
  struct cgraph_function_version_info * const x = (struct cgraph_function_version_info *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_11cgraph_node ((*x).this_node);
      gt_ggc_m_28cgraph_function_version_info ((*x).prev);
      gt_ggc_m_28cgraph_function_version_info ((*x).next);
      gt_ggc_m_9tree_node ((*x).dispatcher_resolver);
    }
}

void
gt_ggc_mx_cgraph_edge (void *x_p)
{
  struct cgraph_edge * x = (struct cgraph_edge *)x_p;
  struct cgraph_edge * xlimit = x;
  while (ggc_test_and_set_mark (xlimit))
   xlimit = ((*xlimit).next_caller);
  if (x != xlimit)
    for (;;)
      {
        struct cgraph_edge * const xprev = ((*x).prev_caller);
        if (xprev == NULL) break;
        x = xprev;
        (void) ggc_test_and_set_mark (xprev);
      }
  while (x != xlimit)
    {
      gt_ggc_m_11cgraph_node ((*x).caller);
      gt_ggc_m_11cgraph_node ((*x).callee);
      gt_ggc_m_11cgraph_edge ((*x).prev_caller);
      gt_ggc_m_11cgraph_edge ((*x).next_caller);
      gt_ggc_m_11cgraph_edge ((*x).prev_callee);
      gt_ggc_m_11cgraph_edge ((*x).next_callee);
      gt_ggc_m_18gimple_statement_d ((*x).call_stmt);
      gt_ggc_m_25cgraph_indirect_call_info ((*x).indirect_info);
      x = ((*x).next_caller);
    }
}

void
gt_ggc_mx_vec_ipa_replace_map_p_va_gc_ (void *x_p)
{
  vec<ipa_replace_map_p,va_gc> * const x = (vec<ipa_replace_map_p,va_gc> *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_mx (x);
    }
}

void
gt_ggc_mx (struct ipa_replace_map *& x)
{
  if (x)
    gt_ggc_mx_ipa_replace_map ((void *) x);
}

void
gt_ggc_mx_ipa_replace_map (void *x_p)
{
  struct ipa_replace_map * const x = (struct ipa_replace_map *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_9tree_node ((*x).old_tree);
      gt_ggc_m_9tree_node ((*x).new_tree);
    }
}

void
gt_ggc_mx_lto_file_decl_data (void *x_p)
{
  struct lto_file_decl_data * const x = (struct lto_file_decl_data *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_17lto_in_decl_state ((*x).current_decl_state);
      gt_ggc_m_17lto_in_decl_state ((*x).global_decl_state);
      gt_ggc_m_P17lto_in_decl_state4htab ((*x).function_decl_states);
      gt_ggc_m_18lto_file_decl_data ((*x).next);
    }
}

void
gt_ggc_mx_vec_ipa_ref_t_va_gc_ (void *x_p)
{
  vec<ipa_ref_t,va_gc> * const x = (vec<ipa_ref_t,va_gc> *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_mx (x);
    }
}

void
gt_ggc_mx (struct ipa_ref& x_r ATTRIBUTE_UNUSED)
{
  struct ipa_ref * ATTRIBUTE_UNUSED x = &x_r;
  gt_ggc_m_15symtab_node_def ((*x).referring);
  gt_ggc_m_15symtab_node_def ((*x).referred);
  gt_ggc_m_18gimple_statement_d ((*x).stmt);
}

void
gt_ggc_mx_symtab_node_def (void *x_p)
{
  union symtab_node_def * x = (union symtab_node_def *)x_p;
  union symtab_node_def * xlimit = x;
  while (ggc_test_and_set_mark (xlimit))
   xlimit = ((*xlimit).symbol.next);
  if (x != xlimit)
    for (;;)
      {
        union symtab_node_def * const xprev = ((*x).symbol.previous);
        if (xprev == NULL) break;
        x = xprev;
        (void) ggc_test_and_set_mark (xprev);
      }
  while (x != xlimit)
    {
      switch (((*x)).symbol.type)
        {
        case SYMTAB_SYMBOL:
          gt_ggc_m_9tree_node ((*x).symbol.decl);
          gt_ggc_m_20vec_ipa_ref_t_va_gc_ ((*x).symbol.ref_list.references);
          gt_ggc_m_15symtab_node_def ((*x).symbol.same_comdat_group);
          gt_ggc_m_18lto_file_decl_data ((*x).symbol.lto_file_data);
          gt_ggc_m_15symtab_node_def ((*x).symbol.next);
          gt_ggc_m_15symtab_node_def ((*x).symbol.previous);
          gt_ggc_m_15symtab_node_def ((*x).symbol.next_sharing_asm_name);
          gt_ggc_m_15symtab_node_def ((*x).symbol.previous_sharing_asm_name);
          break;
        case SYMTAB_FUNCTION:
          gt_ggc_m_9tree_node ((*x).x_function.symbol.decl);
          gt_ggc_m_20vec_ipa_ref_t_va_gc_ ((*x).x_function.symbol.ref_list.references);
          gt_ggc_m_15symtab_node_def ((*x).x_function.symbol.same_comdat_group);
          gt_ggc_m_18lto_file_decl_data ((*x).x_function.symbol.lto_file_data);
          gt_ggc_m_15symtab_node_def ((*x).x_function.symbol.next);
          gt_ggc_m_15symtab_node_def ((*x).x_function.symbol.previous);
          gt_ggc_m_15symtab_node_def ((*x).x_function.symbol.next_sharing_asm_name);
          gt_ggc_m_15symtab_node_def ((*x).x_function.symbol.previous_sharing_asm_name);
          gt_ggc_m_11cgraph_edge ((*x).x_function.callees);
          gt_ggc_m_11cgraph_edge ((*x).x_function.callers);
          gt_ggc_m_11cgraph_edge ((*x).x_function.indirect_calls);
          {
            union symtab_node_def * const x0 =
              (symtab_node)((*x).x_function.origin);
            gt_ggc_m_15symtab_node_def (x0);
          }
          {
            union symtab_node_def * const x1 =
              (symtab_node)((*x).x_function.nested);
            gt_ggc_m_15symtab_node_def (x1);
          }
          {
            union symtab_node_def * const x2 =
              (symtab_node)((*x).x_function.next_nested);
            gt_ggc_m_15symtab_node_def (x2);
          }
          gt_ggc_m_11cgraph_node ((*x).x_function.next_sibling_clone);
          gt_ggc_m_11cgraph_node ((*x).x_function.prev_sibling_clone);
          gt_ggc_m_11cgraph_node ((*x).x_function.clones);
          gt_ggc_m_11cgraph_node ((*x).x_function.clone_of);
          gt_ggc_m_P11cgraph_edge4htab ((*x).x_function.call_site_hash);
          gt_ggc_m_9tree_node ((*x).x_function.former_clone_of);
          gt_ggc_m_11cgraph_node ((*x).x_function.global.inlined_to);
          gt_ggc_m_28vec_ipa_replace_map_p_va_gc_ ((*x).x_function.clone.tree_map);
          gt_ggc_m_15bitmap_head_def ((*x).x_function.clone.args_to_skip);
          gt_ggc_m_15bitmap_head_def ((*x).x_function.clone.combined_args_to_skip);
          gt_ggc_m_9tree_node ((*x).x_function.thunk.alias);
          break;
        case SYMTAB_VARIABLE:
          gt_ggc_m_9tree_node ((*x).x_variable.symbol.decl);
          gt_ggc_m_20vec_ipa_ref_t_va_gc_ ((*x).x_variable.symbol.ref_list.references);
          gt_ggc_m_15symtab_node_def ((*x).x_variable.symbol.same_comdat_group);
          gt_ggc_m_18lto_file_decl_data ((*x).x_variable.symbol.lto_file_data);
          gt_ggc_m_15symtab_node_def ((*x).x_variable.symbol.next);
          gt_ggc_m_15symtab_node_def ((*x).x_variable.symbol.previous);
          gt_ggc_m_15symtab_node_def ((*x).x_variable.symbol.next_sharing_asm_name);
          gt_ggc_m_15symtab_node_def ((*x).x_variable.symbol.previous_sharing_asm_name);
          gt_ggc_m_9tree_node ((*x).x_variable.alias_of);
          break;
        default:
          break;
        }
      x = ((*x).symbol.next);
    }
}

void
gt_ggc_mx_cgraph_node (void *x_p)
{
  struct cgraph_node * const x = (struct cgraph_node *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_9tree_node ((*x).symbol.decl);
      gt_ggc_m_20vec_ipa_ref_t_va_gc_ ((*x).symbol.ref_list.references);
      gt_ggc_m_15symtab_node_def ((*x).symbol.same_comdat_group);
      gt_ggc_m_18lto_file_decl_data ((*x).symbol.lto_file_data);
      gt_ggc_m_15symtab_node_def ((*x).symbol.next);
      gt_ggc_m_15symtab_node_def ((*x).symbol.previous);
      gt_ggc_m_15symtab_node_def ((*x).symbol.next_sharing_asm_name);
      gt_ggc_m_15symtab_node_def ((*x).symbol.previous_sharing_asm_name);
      gt_ggc_m_11cgraph_edge ((*x).callees);
      gt_ggc_m_11cgraph_edge ((*x).callers);
      gt_ggc_m_11cgraph_edge ((*x).indirect_calls);
      {
        union symtab_node_def * const x0 =
          (symtab_node)((*x).origin);
        gt_ggc_m_15symtab_node_def (x0);
      }
      {
        union symtab_node_def * const x1 =
          (symtab_node)((*x).nested);
        gt_ggc_m_15symtab_node_def (x1);
      }
      {
        union symtab_node_def * const x2 =
          (symtab_node)((*x).next_nested);
        gt_ggc_m_15symtab_node_def (x2);
      }
      gt_ggc_m_11cgraph_node ((*x).next_sibling_clone);
      gt_ggc_m_11cgraph_node ((*x).prev_sibling_clone);
      gt_ggc_m_11cgraph_node ((*x).clones);
      gt_ggc_m_11cgraph_node ((*x).clone_of);
      gt_ggc_m_P11cgraph_edge4htab ((*x).call_site_hash);
      gt_ggc_m_9tree_node ((*x).former_clone_of);
      gt_ggc_m_11cgraph_node ((*x).global.inlined_to);
      gt_ggc_m_28vec_ipa_replace_map_p_va_gc_ ((*x).clone.tree_map);
      gt_ggc_m_15bitmap_head_def ((*x).clone.args_to_skip);
      gt_ggc_m_15bitmap_head_def ((*x).clone.combined_args_to_skip);
      gt_ggc_m_9tree_node ((*x).thunk.alias);
    }
}

void
gt_ggc_mx_vec_basic_block_va_gc_ (void *x_p)
{
  vec<basic_block,va_gc> * const x = (vec<basic_block,va_gc> *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_mx (x);
    }
}

void
gt_ggc_mx (struct basic_block_def *& x)
{
  if (x)
    gt_ggc_mx_basic_block_def ((void *) x);
}

void
gt_ggc_mx_vec_edge_va_gc_ (void *x_p)
{
  vec<edge,va_gc> * const x = (vec<edge,va_gc> *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_mx (x);
    }
}

void
gt_ggc_mx (struct edge_def *& x)
{
  if (x)
    gt_ggc_mx_edge_def ((void *) x);
}

void
gt_ggc_mx_rtl_bb_info (void *x_p)
{
  struct rtl_bb_info * const x = (struct rtl_bb_info *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_7rtx_def ((*x).end_);
      gt_ggc_m_7rtx_def ((*x).header_);
      gt_ggc_m_7rtx_def ((*x).footer_);
    }
}

void
gt_ggc_mx_vec_loop_p_va_gc_ (void *x_p)
{
  vec<loop_p,va_gc> * const x = (vec<loop_p,va_gc> *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_mx (x);
    }
}

void
gt_ggc_mx (struct loop *& x)
{
  if (x)
    gt_ggc_mx_loop ((void *) x);
}

void
gt_ggc_mx_loop (void *x_p)
{
  struct loop * x = (struct loop *)x_p;
  struct loop * xlimit = x;
  while (ggc_test_and_set_mark (xlimit))
   xlimit = ((*xlimit).next);
  while (x != xlimit)
    {
      gt_ggc_m_15basic_block_def ((*x).header);
      gt_ggc_m_15basic_block_def ((*x).latch);
      gt_ggc_m_17vec_loop_p_va_gc_ ((*x).superloops);
      gt_ggc_m_4loop ((*x).inner);
      gt_ggc_m_4loop ((*x).next);
      gt_ggc_m_9tree_node ((*x).nb_iterations);
      gt_ggc_m_13nb_iter_bound ((*x).bounds);
      gt_ggc_m_9loop_exit ((*x).exits);
      x = ((*x).next);
    }
}

void
gt_ggc_mx_loop_exit (void *x_p)
{
  struct loop_exit * const x = (struct loop_exit *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_8edge_def ((*x).e);
      gt_ggc_m_9loop_exit ((*x).prev);
      gt_ggc_m_9loop_exit ((*x).next);
      gt_ggc_m_9loop_exit ((*x).next_e);
    }
}

void
gt_ggc_mx_nb_iter_bound (void *x_p)
{
  struct nb_iter_bound * x = (struct nb_iter_bound *)x_p;
  struct nb_iter_bound * xlimit = x;
  while (ggc_test_and_set_mark (xlimit))
   xlimit = ((*xlimit).next);
  while (x != xlimit)
    {
      gt_ggc_m_18gimple_statement_d ((*x).stmt);
      gt_ggc_m_13nb_iter_bound ((*x).next);
      x = ((*x).next);
    }
}

void
gt_ggc_mx_types_used_by_vars_entry (void *x_p)
{
  struct types_used_by_vars_entry * const x = (struct types_used_by_vars_entry *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_9tree_node ((*x).type);
      gt_ggc_m_9tree_node ((*x).var_decl);
    }
}

void
gt_ggc_mx_loops (void *x_p)
{
  struct loops * const x = (struct loops *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_17vec_loop_p_va_gc_ ((*x).larray);
      gt_ggc_m_P9loop_exit4htab ((*x).exits);
      gt_ggc_m_4loop ((*x).tree_root);
    }
}

void
gt_ggc_mx_control_flow_graph (void *x_p)
{
  struct control_flow_graph * const x = (struct control_flow_graph *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_15basic_block_def ((*x).x_entry_block_ptr);
      gt_ggc_m_15basic_block_def ((*x).x_exit_block_ptr);
      gt_ggc_m_22vec_basic_block_va_gc_ ((*x).x_basic_block_info);
      gt_ggc_m_22vec_basic_block_va_gc_ ((*x).x_label_to_block_map);
    }
}

void
gt_ggc_mx_eh_status (void *x_p)
{
  struct eh_status * const x = (struct eh_status *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_11eh_region_d ((*x).region_tree);
      gt_ggc_m_20vec_eh_region_va_gc_ ((*x).region_array);
      gt_ggc_m_25vec_eh_landing_pad_va_gc_ ((*x).lp_array);
      gt_ggc_m_P15throw_stmt_node4htab ((*x).throw_stmt_table);
      gt_ggc_m_15vec_tree_va_gc_ ((*x).ttype_data);
      switch (targetm.arm_eabi_unwinder)
        {
        case 1:
          gt_ggc_m_15vec_tree_va_gc_ ((*x).ehspec_data.arm_eabi);
          break;
        case 0:
          gt_ggc_m_16vec_uchar_va_gc_ ((*x).ehspec_data.other);
          break;
        default:
          break;
        }
    }
}

void
gt_ggc_mx_stack_usage (void *x_p)
{
  struct stack_usage * const x = (struct stack_usage *)x_p;
  if (ggc_test_and_set_mark (x))
    {
    }
}

void
gt_ggc_mx_vec_temp_slot_p_va_gc_ (void *x_p)
{
  vec<temp_slot_p,va_gc> * const x = (vec<temp_slot_p,va_gc> *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_mx (x);
    }
}

void
gt_ggc_mx (struct temp_slot *& x)
{
  if (x)
    gt_ggc_mx_temp_slot ((void *) x);
}

void
gt_ggc_mx_frame_space (void *x_p)
{
  struct frame_space * const x = (struct frame_space *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_11frame_space ((*x).next);
    }
}

void
gt_ggc_mx_dw_fde_struct (void *x_p)
{
  struct dw_fde_struct * const x = (struct dw_fde_struct *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_9tree_node ((*x).decl);
      gt_ggc_m_S ((*x).dw_fde_begin);
      gt_ggc_m_S ((*x).dw_fde_current_label);
      gt_ggc_m_S ((*x).dw_fde_end);
      gt_ggc_m_S ((*x).dw_fde_vms_end_prologue);
      gt_ggc_m_S ((*x).dw_fde_vms_begin_epilogue);
      gt_ggc_m_S ((*x).dw_fde_second_begin);
      gt_ggc_m_S ((*x).dw_fde_second_end);
      gt_ggc_m_21vec_dw_cfi_ref_va_gc_ ((*x).dw_fde_cfi);
    }
}

void
gt_ggc_mx_gimple_df (void *x_p)
{
  struct gimple_df * const x = (struct gimple_df *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_17vec_gimple_va_gc_ ((*x).modified_noreturn_calls);
      gt_ggc_m_15vec_tree_va_gc_ ((*x).ssa_names);
      gt_ggc_m_9tree_node ((*x).vop);
      gt_ggc_m_15bitmap_head_def ((*x).escaped.vars);
      gt_ggc_m_15vec_tree_va_gc_ ((*x).free_ssanames);
      gt_ggc_m_P9tree_node4htab ((*x).default_defs);
      gt_ggc_m_20ssa_operand_memory_d ((*x).ssa_operands.operand_memory);
      gt_ggc_m_P15tm_restart_node4htab ((*x).tm_restart);
    }
}

void
gt_ggc_mx_vec_call_site_record_va_gc_ (void *x_p)
{
  vec<call_site_record,va_gc> * const x = (vec<call_site_record,va_gc> *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_mx (x);
    }
}

void
gt_ggc_mx (struct call_site_record_d *& x)
{
  if (x)
    gt_ggc_mx_call_site_record_d ((void *) x);
}

void
gt_ggc_mx_vec_uchar_va_gc_ (void *x_p)
{
  vec<uchar,va_gc> * const x = (vec<uchar,va_gc> *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_mx (x);
    }
}

void
gt_ggc_mx_sequence_stack (void *x_p)
{
  struct sequence_stack * const x = (struct sequence_stack *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_7rtx_def ((*x).first);
      gt_ggc_m_7rtx_def ((*x).last);
      gt_ggc_m_14sequence_stack ((*x).next);
    }
}

void
gt_ggc_mx_libfunc_entry (void *x_p)
{
  struct libfunc_entry * const x = (struct libfunc_entry *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_7rtx_def ((*x).libfunc);
    }
}

void
gt_ggc_mx_tree_vec_map (void *x_p)
{
  struct tree_vec_map * const x = (struct tree_vec_map *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_9tree_node ((*x).base.from);
      gt_ggc_m_15vec_tree_va_gc_ ((*x).to);
    }
}

void
gt_ggc_mx_tree_priority_map (void *x_p)
{
  struct tree_priority_map * const x = (struct tree_priority_map *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_9tree_node ((*x).base.from);
    }
}

void
gt_ggc_mx_tree_int_map (void *x_p)
{
  struct tree_int_map * const x = (struct tree_int_map *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_9tree_node ((*x).base.from);
    }
}

void
gt_ggc_mx_tree_decl_map (void *x_p)
{
  struct tree_decl_map * const x = (struct tree_decl_map *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_9tree_node ((*x).base.from);
      gt_ggc_m_9tree_node ((*x).to);
    }
}

void
gt_ggc_mx_tree_map (void *x_p)
{
  struct tree_map * const x = (struct tree_map *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_9tree_node ((*x).base.from);
      gt_ggc_m_9tree_node ((*x).to);
    }
}

void
gt_ggc_mx_tree_statement_list_node (void *x_p)
{
  struct tree_statement_list_node * x = (struct tree_statement_list_node *)x_p;
  struct tree_statement_list_node * xlimit = x;
  while (ggc_test_and_set_mark (xlimit))
   xlimit = ((*xlimit).next);
  if (x != xlimit)
    for (;;)
      {
        struct tree_statement_list_node * const xprev = ((*x).prev);
        if (xprev == NULL) break;
        x = xprev;
        (void) ggc_test_and_set_mark (xprev);
      }
  while (x != xlimit)
    {
      gt_ggc_m_24tree_statement_list_node ((*x).prev);
      gt_ggc_m_24tree_statement_list_node ((*x).next);
      gt_ggc_m_9tree_node ((*x).stmt);
      x = ((*x).next);
    }
}

void
gt_ggc_mx_vec_tree_va_gc_ (void *x_p)
{
  vec<tree,va_gc> * const x = (vec<tree,va_gc> *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_mx (x);
    }
}

void
gt_ggc_mx (union tree_node *& x)
{
  if (x)
    gt_ggc_mx_lang_tree_node ((void *) x);
}

void
gt_ggc_mx_ptr_info_def (void *x_p)
{
  struct ptr_info_def * const x = (struct ptr_info_def *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_15bitmap_head_def ((*x).pt.vars);
    }
}

void
gt_ggc_mx_vec_constructor_elt_va_gc_ (void *x_p)
{
  vec<constructor_elt,va_gc> * const x = (vec<constructor_elt,va_gc> *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_mx (x);
    }
}

void
gt_ggc_mx (struct constructor_elt_d& x_r ATTRIBUTE_UNUSED)
{
  struct constructor_elt_d * ATTRIBUTE_UNUSED x = &x_r;
  gt_ggc_m_9tree_node ((*x).index);
  gt_ggc_m_9tree_node ((*x).value);
}

void
gt_ggc_mx_vec_alias_pair_va_gc_ (void *x_p)
{
  vec<alias_pair,va_gc> * const x = (vec<alias_pair,va_gc> *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_mx (x);
    }
}

void
gt_ggc_mx (struct alias_pair& x_r ATTRIBUTE_UNUSED)
{
  struct alias_pair * ATTRIBUTE_UNUSED x = &x_r;
  gt_ggc_m_9tree_node ((*x).decl);
  gt_ggc_m_9tree_node ((*x).target);
}

void
gt_ggc_mx_function (void *x_p)
{
  struct function * const x = (struct function *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_9eh_status ((*x).eh);
      gt_ggc_m_18control_flow_graph ((*x).cfg);
      gt_ggc_m_18gimple_statement_d ((*x).gimple_body);
      gt_ggc_m_9gimple_df ((*x).gimple_df);
      gt_ggc_m_5loops ((*x).x_current_loops);
      gt_ggc_m_11stack_usage ((*x).su);
      gt_ggc_m_9tree_node ((*x).decl);
      gt_ggc_m_9tree_node ((*x).static_chain_decl);
      gt_ggc_m_9tree_node ((*x).nonlocal_goto_save_area);
      gt_ggc_m_15vec_tree_va_gc_ ((*x).local_decls);
      gt_ggc_m_16machine_function ((*x).machine);
      gt_ggc_m_17language_function ((*x).language);
      gt_ggc_m_P9tree_node4htab ((*x).used_types_hash);
      gt_ggc_m_13dw_fde_struct ((*x).fde);
    }
}

void
gt_ggc_mx_fixed_value (void *x_p)
{
  struct fixed_value * const x = (struct fixed_value *)x_p;
  if (ggc_test_and_set_mark (x))
    {
    }
}

void
gt_ggc_mx_real_value (void *x_p)
{
  struct real_value * const x = (struct real_value *)x_p;
  if (ggc_test_and_set_mark (x))
    {
    }
}

void
gt_ggc_mx_vec_rtx_va_gc_ (void *x_p)
{
  vec<rtx,va_gc> * const x = (vec<rtx,va_gc> *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_mx (x);
    }
}

void
gt_ggc_mx (struct rtx_def *& x)
{
  if (x)
    gt_ggc_mx_rtx_def ((void *) x);
}

void
gt_ggc_mx_object_block (void *x_p)
{
  struct object_block * const x = (struct object_block *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_7section ((*x).sect);
      gt_ggc_m_14vec_rtx_va_gc_ ((*x).objects);
      gt_ggc_m_14vec_rtx_va_gc_ ((*x).anchors);
    }
}

void
gt_ggc_mx_reg_attrs (void *x_p)
{
  struct reg_attrs * const x = (struct reg_attrs *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_9tree_node ((*x).decl);
    }
}

void
gt_ggc_mx_mem_attrs (void *x_p)
{
  struct mem_attrs * const x = (struct mem_attrs *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_9tree_node ((*x).expr);
    }
}

void
gt_ggc_mx_bitmap_obstack (void *x_p)
{
  struct bitmap_obstack * const x = (struct bitmap_obstack *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_18bitmap_element_def ((*x).elements);
      gt_ggc_m_15bitmap_head_def ((*x).heads);
    }
}

void
gt_ggc_mx_bitmap_element_def (void *x_p)
{
  struct bitmap_element_def * x = (struct bitmap_element_def *)x_p;
  struct bitmap_element_def * xlimit = x;
  while (ggc_test_and_set_mark (xlimit))
   xlimit = ((*xlimit).next);
  if (x != xlimit)
    for (;;)
      {
        struct bitmap_element_def * const xprev = ((*x).prev);
        if (xprev == NULL) break;
        x = xprev;
        (void) ggc_test_and_set_mark (xprev);
      }
  while (x != xlimit)
    {
      gt_ggc_m_18bitmap_element_def ((*x).next);
      gt_ggc_m_18bitmap_element_def ((*x).prev);
      x = ((*x).next);
    }
}

void
gt_ggc_mx_machine_function (void *x_p)
{
  struct machine_function * const x = (struct machine_function *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_17stack_local_entry ((*x).stack_locals);
      gt_ggc_m_S ((*x).some_ld_name);
      gt_ggc_m_7rtx_def ((*x).split_stack_varargs_pointer);
      gt_ggc_m_7rtx_def ((*x).fs.cfa_reg);
    }
}

void
gt_ggc_mx_basic_block_def (void *x_p)
{
  struct basic_block_def * x = (struct basic_block_def *)x_p;
  struct basic_block_def * xlimit = x;
  while (ggc_test_and_set_mark (xlimit))
   xlimit = ((*xlimit).next_bb);
  if (x != xlimit)
    for (;;)
      {
        struct basic_block_def * const xprev = ((*x).prev_bb);
        if (xprev == NULL) break;
        x = xprev;
        (void) ggc_test_and_set_mark (xprev);
      }
  while (x != xlimit)
    {
      gt_ggc_m_15vec_edge_va_gc_ ((*x).preds);
      gt_ggc_m_15vec_edge_va_gc_ ((*x).succs);
      gt_ggc_m_4loop ((*x).loop_father);
      gt_ggc_m_15basic_block_def ((*x).prev_bb);
      gt_ggc_m_15basic_block_def ((*x).next_bb);
      switch (((((*x)).flags & BB_RTL) != 0))
        {
        case 0:
          gt_ggc_m_18gimple_statement_d ((*x).il.gimple.seq);
          gt_ggc_m_18gimple_statement_d ((*x).il.gimple.phi_nodes);
          break;
        case 1:
          gt_ggc_m_7rtx_def ((*x).il.x.head_);
          gt_ggc_m_11rtl_bb_info ((*x).il.x.rtl);
          break;
        default:
          break;
        }
      x = ((*x).next_bb);
    }
}

void
gt_ggc_mx_edge_def (void *x_p)
{
  struct edge_def * const x = (struct edge_def *)x_p;
  if (ggc_test_and_set_mark (x))
    {
    }
}

void
gt_ggc_mx_section (void *x_p)
{
  union section * const x = (union section *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      switch (SECTION_STYLE (&(((*x)))))
        {
        case SECTION_NAMED:
          gt_ggc_m_S ((*x).named.name);
          gt_ggc_m_9tree_node ((*x).named.decl);
          break;
        case SECTION_UNNAMED:
          gt_ggc_m_7section ((*x).unnamed.next);
          break;
        case SECTION_NOSWITCH:
          break;
        default:
          break;
        }
    }
}

void
gt_ggc_mx_gimple_statement_d (void *x_p)
{
  union gimple_statement_d * x = (union gimple_statement_d *)x_p;
  union gimple_statement_d * xlimit = x;
  while (ggc_test_and_set_mark (xlimit))
   xlimit = ((*xlimit).gsbase.next);
  while (x != xlimit)
    {
      switch (gimple_statement_structure (&((*x))))
        {
        case GSS_BASE:
          gt_ggc_m_15basic_block_def ((*x).gsbase.bb);
          gt_ggc_m_18gimple_statement_d ((*x).gsbase.next);
          break;
        case GSS_WITH_OPS:
          {
            size_t l0 = (size_t)(((*x).gsops).opbase.gsbase.num_ops);
            gt_ggc_m_15basic_block_def ((*x).gsops.opbase.gsbase.bb);
            gt_ggc_m_18gimple_statement_d ((*x).gsops.opbase.gsbase.next);
            {
              size_t i0;
              for (i0 = 0; i0 != l0; i0++) {
                gt_ggc_m_9tree_node ((*x).gsops.op[i0]);
              }
            }
          }
          break;
        case GSS_WITH_MEM_OPS_BASE:
          gt_ggc_m_15basic_block_def ((*x).gsmembase.opbase.gsbase.bb);
          gt_ggc_m_18gimple_statement_d ((*x).gsmembase.opbase.gsbase.next);
          break;
        case GSS_WITH_MEM_OPS:
          {
            size_t l1 = (size_t)(((*x).gsmem).membase.opbase.gsbase.num_ops);
            gt_ggc_m_15basic_block_def ((*x).gsmem.membase.opbase.gsbase.bb);
            gt_ggc_m_18gimple_statement_d ((*x).gsmem.membase.opbase.gsbase.next);
            {
              size_t i1;
              for (i1 = 0; i1 != l1; i1++) {
                gt_ggc_m_9tree_node ((*x).gsmem.op[i1]);
              }
            }
          }
          break;
        case GSS_CALL:
          {
            size_t l2 = (size_t)(((*x).gimple_call).membase.opbase.gsbase.num_ops);
            gt_ggc_m_15basic_block_def ((*x).gimple_call.membase.opbase.gsbase.bb);
            gt_ggc_m_18gimple_statement_d ((*x).gimple_call.membase.opbase.gsbase.next);
            gt_ggc_m_15bitmap_head_def ((*x).gimple_call.call_used.vars);
            gt_ggc_m_15bitmap_head_def ((*x).gimple_call.call_clobbered.vars);
            switch (((*x).gimple_call).membase.opbase.gsbase.subcode & GF_CALL_INTERNAL)
              {
              case 0:
                gt_ggc_m_9tree_node ((*x).gimple_call.u.fntype);
                break;
              case GF_CALL_INTERNAL:
                break;
              default:
                break;
              }
            {
              size_t i2;
              for (i2 = 0; i2 != l2; i2++) {
                gt_ggc_m_9tree_node ((*x).gimple_call.op[i2]);
              }
            }
          }
          break;
        case GSS_OMP:
          gt_ggc_m_15basic_block_def ((*x).omp.gsbase.bb);
          gt_ggc_m_18gimple_statement_d ((*x).omp.gsbase.next);
          gt_ggc_m_18gimple_statement_d ((*x).omp.body);
          break;
        case GSS_BIND:
          gt_ggc_m_15basic_block_def ((*x).gimple_bind.gsbase.bb);
          gt_ggc_m_18gimple_statement_d ((*x).gimple_bind.gsbase.next);
          gt_ggc_m_9tree_node ((*x).gimple_bind.vars);
          gt_ggc_m_9tree_node ((*x).gimple_bind.block);
          gt_ggc_m_18gimple_statement_d ((*x).gimple_bind.body);
          break;
        case GSS_CATCH:
          gt_ggc_m_15basic_block_def ((*x).gimple_catch.gsbase.bb);
          gt_ggc_m_18gimple_statement_d ((*x).gimple_catch.gsbase.next);
          gt_ggc_m_9tree_node ((*x).gimple_catch.types);
          gt_ggc_m_18gimple_statement_d ((*x).gimple_catch.handler);
          break;
        case GSS_EH_FILTER:
          gt_ggc_m_15basic_block_def ((*x).gimple_eh_filter.gsbase.bb);
          gt_ggc_m_18gimple_statement_d ((*x).gimple_eh_filter.gsbase.next);
          gt_ggc_m_9tree_node ((*x).gimple_eh_filter.types);
          gt_ggc_m_18gimple_statement_d ((*x).gimple_eh_filter.failure);
          break;
        case GSS_EH_MNT:
          gt_ggc_m_15basic_block_def ((*x).gimple_eh_mnt.gsbase.bb);
          gt_ggc_m_18gimple_statement_d ((*x).gimple_eh_mnt.gsbase.next);
          gt_ggc_m_9tree_node ((*x).gimple_eh_mnt.fndecl);
          break;
        case GSS_EH_ELSE:
          gt_ggc_m_15basic_block_def ((*x).gimple_eh_else.gsbase.bb);
          gt_ggc_m_18gimple_statement_d ((*x).gimple_eh_else.gsbase.next);
          gt_ggc_m_18gimple_statement_d ((*x).gimple_eh_else.n_body);
          gt_ggc_m_18gimple_statement_d ((*x).gimple_eh_else.e_body);
          break;
        case GSS_PHI:
          {
            size_t l3 = (size_t)(((*x).gimple_phi).nargs);
            gt_ggc_m_15basic_block_def ((*x).gimple_phi.gsbase.bb);
            gt_ggc_m_18gimple_statement_d ((*x).gimple_phi.gsbase.next);
            gt_ggc_m_9tree_node ((*x).gimple_phi.result);
            {
              size_t i3;
              for (i3 = 0; i3 != l3; i3++) {
                gt_ggc_m_9tree_node ((*x).gimple_phi.args[i3].def);
              }
            }
          }
          break;
        case GSS_EH_CTRL:
          gt_ggc_m_15basic_block_def ((*x).gimple_eh_ctrl.gsbase.bb);
          gt_ggc_m_18gimple_statement_d ((*x).gimple_eh_ctrl.gsbase.next);
          break;
        case GSS_TRY:
          gt_ggc_m_15basic_block_def ((*x).gimple_try.gsbase.bb);
          gt_ggc_m_18gimple_statement_d ((*x).gimple_try.gsbase.next);
          gt_ggc_m_18gimple_statement_d ((*x).gimple_try.eval);
          gt_ggc_m_18gimple_statement_d ((*x).gimple_try.cleanup);
          break;
        case GSS_WCE:
          gt_ggc_m_15basic_block_def ((*x).gimple_wce.gsbase.bb);
          gt_ggc_m_18gimple_statement_d ((*x).gimple_wce.gsbase.next);
          gt_ggc_m_18gimple_statement_d ((*x).gimple_wce.cleanup);
          break;
        case GSS_ASM:
          {
            size_t l4 = (size_t)(((*x).gimple_asm).membase.opbase.gsbase.num_ops);
            gt_ggc_m_15basic_block_def ((*x).gimple_asm.membase.opbase.gsbase.bb);
            gt_ggc_m_18gimple_statement_d ((*x).gimple_asm.membase.opbase.gsbase.next);
            gt_ggc_m_S ((*x).gimple_asm.string);
            {
              size_t i4;
              for (i4 = 0; i4 != l4; i4++) {
                gt_ggc_m_9tree_node ((*x).gimple_asm.op[i4]);
              }
            }
          }
          break;
        case GSS_OMP_CRITICAL:
          gt_ggc_m_15basic_block_def ((*x).gimple_omp_critical.omp.gsbase.bb);
          gt_ggc_m_18gimple_statement_d ((*x).gimple_omp_critical.omp.gsbase.next);
          gt_ggc_m_18gimple_statement_d ((*x).gimple_omp_critical.omp.body);
          gt_ggc_m_9tree_node ((*x).gimple_omp_critical.name);
          break;
        case GSS_OMP_FOR:
          {
            size_t l5 = (size_t)(((*x).gimple_omp_for).collapse);
            gt_ggc_m_15basic_block_def ((*x).gimple_omp_for.omp.gsbase.bb);
            gt_ggc_m_18gimple_statement_d ((*x).gimple_omp_for.omp.gsbase.next);
            gt_ggc_m_18gimple_statement_d ((*x).gimple_omp_for.omp.body);
            gt_ggc_m_9tree_node ((*x).gimple_omp_for.clauses);
            if ((*x).gimple_omp_for.iter != NULL) {
              size_t i5;
              for (i5 = 0; i5 != (size_t)(l5); i5++) {
                gt_ggc_m_9tree_node ((*x).gimple_omp_for.iter[i5].index);
                gt_ggc_m_9tree_node ((*x).gimple_omp_for.iter[i5].initial);
                gt_ggc_m_9tree_node ((*x).gimple_omp_for.iter[i5].final);
                gt_ggc_m_9tree_node ((*x).gimple_omp_for.iter[i5].incr);
              }
              ggc_mark ((*x).gimple_omp_for.iter);
            }
            gt_ggc_m_18gimple_statement_d ((*x).gimple_omp_for.pre_body);
          }
          break;
        case GSS_OMP_PARALLEL:
          gt_ggc_m_15basic_block_def ((*x).gimple_omp_parallel.omp.gsbase.bb);
          gt_ggc_m_18gimple_statement_d ((*x).gimple_omp_parallel.omp.gsbase.next);
          gt_ggc_m_18gimple_statement_d ((*x).gimple_omp_parallel.omp.body);
          gt_ggc_m_9tree_node ((*x).gimple_omp_parallel.clauses);
          gt_ggc_m_9tree_node ((*x).gimple_omp_parallel.child_fn);
          gt_ggc_m_9tree_node ((*x).gimple_omp_parallel.data_arg);
          break;
        case GSS_OMP_TASK:
          gt_ggc_m_15basic_block_def ((*x).gimple_omp_task.par.omp.gsbase.bb);
          gt_ggc_m_18gimple_statement_d ((*x).gimple_omp_task.par.omp.gsbase.next);
          gt_ggc_m_18gimple_statement_d ((*x).gimple_omp_task.par.omp.body);
          gt_ggc_m_9tree_node ((*x).gimple_omp_task.par.clauses);
          gt_ggc_m_9tree_node ((*x).gimple_omp_task.par.child_fn);
          gt_ggc_m_9tree_node ((*x).gimple_omp_task.par.data_arg);
          gt_ggc_m_9tree_node ((*x).gimple_omp_task.copy_fn);
          gt_ggc_m_9tree_node ((*x).gimple_omp_task.arg_size);
          gt_ggc_m_9tree_node ((*x).gimple_omp_task.arg_align);
          break;
        case GSS_OMP_SECTIONS:
          gt_ggc_m_15basic_block_def ((*x).gimple_omp_sections.omp.gsbase.bb);
          gt_ggc_m_18gimple_statement_d ((*x).gimple_omp_sections.omp.gsbase.next);
          gt_ggc_m_18gimple_statement_d ((*x).gimple_omp_sections.omp.body);
          gt_ggc_m_9tree_node ((*x).gimple_omp_sections.clauses);
          gt_ggc_m_9tree_node ((*x).gimple_omp_sections.control);
          break;
        case GSS_OMP_SINGLE:
          gt_ggc_m_15basic_block_def ((*x).gimple_omp_single.omp.gsbase.bb);
          gt_ggc_m_18gimple_statement_d ((*x).gimple_omp_single.omp.gsbase.next);
          gt_ggc_m_18gimple_statement_d ((*x).gimple_omp_single.omp.body);
          gt_ggc_m_9tree_node ((*x).gimple_omp_single.clauses);
          break;
        case GSS_OMP_CONTINUE:
          gt_ggc_m_15basic_block_def ((*x).gimple_omp_continue.gsbase.bb);
          gt_ggc_m_18gimple_statement_d ((*x).gimple_omp_continue.gsbase.next);
          gt_ggc_m_9tree_node ((*x).gimple_omp_continue.control_def);
          gt_ggc_m_9tree_node ((*x).gimple_omp_continue.control_use);
          break;
        case GSS_OMP_ATOMIC_LOAD:
          gt_ggc_m_15basic_block_def ((*x).gimple_omp_atomic_load.gsbase.bb);
          gt_ggc_m_18gimple_statement_d ((*x).gimple_omp_atomic_load.gsbase.next);
          gt_ggc_m_9tree_node ((*x).gimple_omp_atomic_load.rhs);
          gt_ggc_m_9tree_node ((*x).gimple_omp_atomic_load.lhs);
          break;
        case GSS_OMP_ATOMIC_STORE:
          gt_ggc_m_15basic_block_def ((*x).gimple_omp_atomic_store.gsbase.bb);
          gt_ggc_m_18gimple_statement_d ((*x).gimple_omp_atomic_store.gsbase.next);
          gt_ggc_m_9tree_node ((*x).gimple_omp_atomic_store.val);
          break;
        case GSS_TRANSACTION:
          gt_ggc_m_15basic_block_def ((*x).gimple_transaction.gsbase.opbase.gsbase.bb);
          gt_ggc_m_18gimple_statement_d ((*x).gimple_transaction.gsbase.opbase.gsbase.next);
          gt_ggc_m_18gimple_statement_d ((*x).gimple_transaction.body);
          gt_ggc_m_9tree_node ((*x).gimple_transaction.label);
          break;
        default:
          break;
        }
      x = ((*x).gsbase.next);
    }
}

void
gt_ggc_mx_rtvec_def (void *x_p)
{
  struct rtvec_def * const x = (struct rtvec_def *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      {
        size_t l0 = (size_t)(((*x)).num_elem);
        {
          size_t i0;
          for (i0 = 0; i0 != l0; i0++) {
            gt_ggc_m_7rtx_def ((*x).elem[i0]);
          }
        }
      }
    }
}

void
gt_ggc_mx_rtx_def (void *x_p)
{
  struct rtx_def * x = (struct rtx_def *)x_p;
  struct rtx_def * xlimit = x;
  while (ggc_test_and_set_mark (xlimit))
   xlimit = (RTX_NEXT (&(*xlimit)));
  if (x != xlimit)
    for (;;)
      {
        struct rtx_def * const xprev = (RTX_PREV (&(*x)));
        if (xprev == NULL) break;
        x = xprev;
        (void) ggc_test_and_set_mark (xprev);
      }
  while (x != xlimit)
    {
      switch (GET_CODE (&(*x)))
        {
        case DEBUG_PARAMETER_REF:
          gt_ggc_m_9tree_node ((*x).u.fld[0].rt_tree);
          break;
        case ENTRY_VALUE:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case DEBUG_IMPLICIT_PTR:
          gt_ggc_m_9tree_node ((*x).u.fld[0].rt_tree);
          break;
        case VAR_LOCATION:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_9tree_node ((*x).u.fld[0].rt_tree);
          break;
        case FMA:
          gt_ggc_m_7rtx_def ((*x).u.fld[2].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case US_TRUNCATE:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SS_TRUNCATE:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case US_MINUS:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case US_ASHIFT:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SS_ASHIFT:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SS_ABS:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case US_NEG:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SS_NEG:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SS_MINUS:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case US_PLUS:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SS_PLUS:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case VEC_DUPLICATE:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case VEC_CONCAT:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case VEC_SELECT:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case VEC_MERGE:
          gt_ggc_m_7rtx_def ((*x).u.fld[2].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case LO_SUM:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case HIGH:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case ZERO_EXTRACT:
          gt_ggc_m_7rtx_def ((*x).u.fld[2].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SIGN_EXTRACT:
          gt_ggc_m_7rtx_def ((*x).u.fld[2].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case PARITY:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case POPCOUNT:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case CTZ:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case CLZ:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case CLRSB:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case FFS:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case BSWAP:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SQRT:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case ABS:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case UNSIGNED_SAT_FRACT:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SAT_FRACT:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case UNSIGNED_FRACT_CONVERT:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case FRACT_CONVERT:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case UNSIGNED_FIX:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case UNSIGNED_FLOAT:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case FIX:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case FLOAT:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case FLOAT_TRUNCATE:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case FLOAT_EXTEND:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case TRUNCATE:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case ZERO_EXTEND:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SIGN_EXTEND:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case LTGT:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case UNLT:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case UNLE:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case UNGT:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case UNGE:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case UNEQ:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case ORDERED:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case UNORDERED:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case LTU:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case LEU:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case GTU:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case GEU:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case LT:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case LE:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case GT:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case GE:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case EQ:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case NE:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case POST_MODIFY:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case PRE_MODIFY:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case POST_INC:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case POST_DEC:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case PRE_INC:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case PRE_DEC:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case UMAX:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case UMIN:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SMAX:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SMIN:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case ROTATERT:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case LSHIFTRT:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case ASHIFTRT:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case ROTATE:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case ASHIFT:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case NOT:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case XOR:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case IOR:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case AND:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case UMOD:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case UDIV:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case MOD:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case US_DIV:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SS_DIV:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case DIV:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case US_MULT:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SS_MULT:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case MULT:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case NEG:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case MINUS:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case PLUS:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case COMPARE:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case IF_THEN_ELSE:
          gt_ggc_m_7rtx_def ((*x).u.fld[2].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case CC0:
          break;
        case SYMBOL_REF:
          switch (SYMBOL_REF_HAS_BLOCK_INFO_P (&(*x)))
            {
            case 1:
              gt_ggc_m_12object_block ((*x).u.block_sym.block);
              break;
            default:
              break;
            }
          switch (CONSTANT_POOL_ADDRESS_P (&(*x)))
            {
            case 1:
              gt_ggc_m_23constant_descriptor_rtx ((*x).u.fld[2].rt_constant);
              break;
            default:
              gt_ggc_m_9tree_node ((*x).u.fld[2].rt_tree);
              break;
            }
          gt_ggc_m_S ((*x).u.fld[0].rt_str);
          break;
        case LABEL_REF:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case MEM:
          gt_ggc_m_9mem_attrs ((*x).u.fld[1].rt_mem);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case CONCATN:
          gt_ggc_m_9rtvec_def ((*x).u.fld[0].rt_rtvec);
          break;
        case CONCAT:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case STRICT_LOW_PART:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SUBREG:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SCRATCH:
          break;
        case REG:
          gt_ggc_m_9reg_attrs ((*x).u.fld[2].rt_reg);
          break;
        case PC:
          break;
        case CONST:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case CONST_STRING:
          gt_ggc_m_S ((*x).u.fld[0].rt_str);
          break;
        case CONST_VECTOR:
          gt_ggc_m_9rtvec_def ((*x).u.fld[0].rt_rtvec);
          break;
        case CONST_DOUBLE:
          break;
        case CONST_FIXED:
          break;
        case CONST_INT:
          break;
        case TRAP_IF:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case EH_RETURN:
          break;
        case SIMPLE_RETURN:
          break;
        case RETURN:
          break;
        case CALL:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case CLOBBER:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case USE:
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SET:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case PREFETCH:
          gt_ggc_m_7rtx_def ((*x).u.fld[2].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case ADDR_DIFF_VEC:
          gt_ggc_m_7rtx_def ((*x).u.fld[3].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[2].rt_rtx);
          gt_ggc_m_9rtvec_def ((*x).u.fld[1].rt_rtvec);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case ADDR_VEC:
          gt_ggc_m_9rtvec_def ((*x).u.fld[0].rt_rtvec);
          break;
        case UNSPEC_VOLATILE:
          gt_ggc_m_9rtvec_def ((*x).u.fld[0].rt_rtvec);
          break;
        case UNSPEC:
          gt_ggc_m_9rtvec_def ((*x).u.fld[0].rt_rtvec);
          break;
        case ASM_OPERANDS:
          gt_ggc_m_9rtvec_def ((*x).u.fld[5].rt_rtvec);
          gt_ggc_m_9rtvec_def ((*x).u.fld[4].rt_rtvec);
          gt_ggc_m_9rtvec_def ((*x).u.fld[3].rt_rtvec);
          gt_ggc_m_S ((*x).u.fld[1].rt_str);
          gt_ggc_m_S ((*x).u.fld[0].rt_str);
          break;
        case ASM_INPUT:
          gt_ggc_m_S ((*x).u.fld[0].rt_str);
          break;
        case PARALLEL:
          gt_ggc_m_9rtvec_def ((*x).u.fld[0].rt_rtvec);
          break;
        case COND_EXEC:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case NOTE:
          switch (NOTE_KIND (&(*x)))
            {
            default:
              gt_ggc_m_S ((*x).u.fld[4].rt_str);
              break;
            case NOTE_INSN_CFI_LABEL:
              break;
            case NOTE_INSN_CFI:
              break;
            case NOTE_INSN_SWITCH_TEXT_SECTIONS:
              break;
            case NOTE_INSN_BASIC_BLOCK:
              break;
            case NOTE_INSN_CALL_ARG_LOCATION:
              gt_ggc_m_7rtx_def ((*x).u.fld[4].rt_rtx);
              break;
            case NOTE_INSN_VAR_LOCATION:
              gt_ggc_m_7rtx_def ((*x).u.fld[4].rt_rtx);
              break;
            case NOTE_INSN_EH_REGION_END:
              break;
            case NOTE_INSN_EH_REGION_BEG:
              break;
            case NOTE_INSN_EPILOGUE_BEG:
              break;
            case NOTE_INSN_PROLOGUE_END:
              break;
            case NOTE_INSN_FUNCTION_BEG:
              break;
            case NOTE_INSN_BLOCK_END:
              gt_ggc_m_9tree_node ((*x).u.fld[4].rt_tree);
              break;
            case NOTE_INSN_BLOCK_BEG:
              gt_ggc_m_9tree_node ((*x).u.fld[4].rt_tree);
              break;
            case NOTE_INSN_DELETED_DEBUG_LABEL:
              gt_ggc_m_S ((*x).u.fld[4].rt_str);
              break;
            case NOTE_INSN_DELETED_LABEL:
              gt_ggc_m_S ((*x).u.fld[4].rt_str);
              break;
            case NOTE_INSN_DELETED:
              break;
            }
          gt_ggc_m_15basic_block_def ((*x).u.fld[3].rt_bb);
          gt_ggc_m_7rtx_def ((*x).u.fld[2].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          break;
        case CODE_LABEL:
          gt_ggc_m_S ((*x).u.fld[7].rt_str);
          gt_ggc_m_7rtx_def ((*x).u.fld[4].rt_rtx);
          gt_ggc_m_15basic_block_def ((*x).u.fld[3].rt_bb);
          gt_ggc_m_7rtx_def ((*x).u.fld[2].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          break;
        case BARRIER:
          gt_ggc_m_7rtx_def ((*x).u.fld[2].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          break;
        case CALL_INSN:
          gt_ggc_m_7rtx_def ((*x).u.fld[8].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[7].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[4].rt_rtx);
          gt_ggc_m_15basic_block_def ((*x).u.fld[3].rt_bb);
          gt_ggc_m_7rtx_def ((*x).u.fld[2].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          break;
        case JUMP_INSN:
          gt_ggc_m_7rtx_def ((*x).u.fld[8].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[7].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[4].rt_rtx);
          gt_ggc_m_15basic_block_def ((*x).u.fld[3].rt_bb);
          gt_ggc_m_7rtx_def ((*x).u.fld[2].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          break;
        case INSN:
          gt_ggc_m_7rtx_def ((*x).u.fld[7].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[4].rt_rtx);
          gt_ggc_m_15basic_block_def ((*x).u.fld[3].rt_bb);
          gt_ggc_m_7rtx_def ((*x).u.fld[2].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          break;
        case DEBUG_INSN:
          gt_ggc_m_7rtx_def ((*x).u.fld[7].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[4].rt_rtx);
          gt_ggc_m_15basic_block_def ((*x).u.fld[3].rt_bb);
          gt_ggc_m_7rtx_def ((*x).u.fld[2].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          break;
        case ADDRESS:
          break;
        case SEQUENCE:
          gt_ggc_m_9rtvec_def ((*x).u.fld[0].rt_rtvec);
          break;
        case INSN_LIST:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case EXPR_LIST:
          gt_ggc_m_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_ggc_m_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case DEBUG_EXPR:
          gt_ggc_m_9tree_node ((*x).u.fld[0].rt_tree);
          break;
        case VALUE:
          break;
        case UNKNOWN:
          break;
        default:
          break;
        }
      x = (RTX_NEXT (&(*x)));
    }
}

void
gt_ggc_mx_bitmap_head_def (void *x_p)
{
  struct bitmap_head_def * const x = (struct bitmap_head_def *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_18bitmap_element_def ((*x).first);
      gt_ggc_m_14bitmap_obstack ((*x).obstack);
    }
}

void
gt_ggc_mx_answer (void *x_p)
{
  struct answer * const x = (struct answer *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      {
        size_t l0 = (size_t)(((*x)).count);
        gt_ggc_m_6answer ((*x).next);
        {
          size_t i0;
          for (i0 = 0; i0 != l0; i0++) {
            switch (cpp_token_val_index (&((*x).first[i0])))
              {
              case CPP_TOKEN_FLD_NODE:
                {
                  union tree_node * const x1 =
                    ((*x).first[i0].val.node.node) ? HT_IDENT_TO_GCC_IDENT (HT_NODE (((*x).first[i0].val.node.node))) : NULL;
                  gt_ggc_m_9tree_node (x1);
                }
                break;
              case CPP_TOKEN_FLD_SOURCE:
                gt_ggc_m_9cpp_token ((*x).first[i0].val.source);
                break;
              case CPP_TOKEN_FLD_STR:
                gt_ggc_m_S ((*x).first[i0].val.str.text);
                break;
              case CPP_TOKEN_FLD_ARG_NO:
                break;
              case CPP_TOKEN_FLD_TOKEN_NO:
                break;
              case CPP_TOKEN_FLD_PRAGMA:
                break;
              default:
                break;
              }
          }
        }
      }
    }
}

void
gt_ggc_mx_cpp_macro (void *x_p)
{
  struct cpp_macro * const x = (struct cpp_macro *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      {
        size_t l0 = (size_t)(((*x)).paramc);
        if ((*x).params != NULL) {
          size_t i0;
          for (i0 = 0; i0 != (size_t)(l0); i0++) {
            {
              union tree_node * const x1 =
                ((*x).params[i0]) ? HT_IDENT_TO_GCC_IDENT (HT_NODE (((*x).params[i0]))) : NULL;
              gt_ggc_m_9tree_node (x1);
            }
          }
          ggc_mark ((*x).params);
        }
        switch (((*x)).traditional)
          {
          case 0:
            if ((*x).exp.tokens != NULL) {
              size_t i2;
              for (i2 = 0; i2 != (size_t)((*x).count); i2++) {
                switch (cpp_token_val_index (&((*x).exp.tokens[i2])))
                  {
                  case CPP_TOKEN_FLD_NODE:
                    {
                      union tree_node * const x3 =
                        ((*x).exp.tokens[i2].val.node.node) ? HT_IDENT_TO_GCC_IDENT (HT_NODE (((*x).exp.tokens[i2].val.node.node))) : NULL;
                      gt_ggc_m_9tree_node (x3);
                    }
                    break;
                  case CPP_TOKEN_FLD_SOURCE:
                    gt_ggc_m_9cpp_token ((*x).exp.tokens[i2].val.source);
                    break;
                  case CPP_TOKEN_FLD_STR:
                    gt_ggc_m_S ((*x).exp.tokens[i2].val.str.text);
                    break;
                  case CPP_TOKEN_FLD_ARG_NO:
                    break;
                  case CPP_TOKEN_FLD_TOKEN_NO:
                    break;
                  case CPP_TOKEN_FLD_PRAGMA:
                    break;
                  default:
                    break;
                  }
              }
              ggc_mark ((*x).exp.tokens);
            }
            break;
          case 1:
            gt_ggc_m_S ((*x).exp.text);
            break;
          default:
            break;
          }
      }
    }
}

void
gt_ggc_mx_cpp_token (void *x_p)
{
  struct cpp_token * const x = (struct cpp_token *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      switch (cpp_token_val_index (&((*x))))
        {
        case CPP_TOKEN_FLD_NODE:
          {
            union tree_node * const x0 =
              ((*x).val.node.node) ? HT_IDENT_TO_GCC_IDENT (HT_NODE (((*x).val.node.node))) : NULL;
            gt_ggc_m_9tree_node (x0);
          }
          break;
        case CPP_TOKEN_FLD_SOURCE:
          gt_ggc_m_9cpp_token ((*x).val.source);
          break;
        case CPP_TOKEN_FLD_STR:
          gt_ggc_m_S ((*x).val.str.text);
          break;
        case CPP_TOKEN_FLD_ARG_NO:
          break;
        case CPP_TOKEN_FLD_TOKEN_NO:
          break;
        case CPP_TOKEN_FLD_PRAGMA:
          break;
        default:
          break;
        }
    }
}

void
gt_ggc_mx_line_maps (void *x_p)
{
  struct line_maps * const x = (struct line_maps *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      {
        size_t l0 = (size_t)(((*x).info_ordinary).used);
        if ((*x).info_ordinary.maps != NULL) {
          size_t i0;
          for (i0 = 0; i0 != (size_t)(l0); i0++) {
            switch (((*x).info_ordinary.maps[i0]).reason == LC_ENTER_MACRO)
              {
              case 0:
                gt_ggc_m_S ((*x).info_ordinary.maps[i0].d.ordinary.to_file);
                break;
              case 1:
                {
                  union tree_node * const x1 =
                    ((*x).info_ordinary.maps[i0].d.macro.macro) ? HT_IDENT_TO_GCC_IDENT (HT_NODE (((*x).info_ordinary.maps[i0].d.macro.macro))) : NULL;
                  gt_ggc_m_9tree_node (x1);
                }
                if ((*x).info_ordinary.maps[i0].d.macro.macro_locations != NULL) {
                  ggc_mark ((*x).info_ordinary.maps[i0].d.macro.macro_locations);
                }
                break;
              default:
                break;
              }
          }
          ggc_mark ((*x).info_ordinary.maps);
        }
      }
      {
        size_t l2 = (size_t)(((*x).info_macro).used);
        if ((*x).info_macro.maps != NULL) {
          size_t i2;
          for (i2 = 0; i2 != (size_t)(l2); i2++) {
            switch (((*x).info_macro.maps[i2]).reason == LC_ENTER_MACRO)
              {
              case 0:
                gt_ggc_m_S ((*x).info_macro.maps[i2].d.ordinary.to_file);
                break;
              case 1:
                {
                  union tree_node * const x3 =
                    ((*x).info_macro.maps[i2].d.macro.macro) ? HT_IDENT_TO_GCC_IDENT (HT_NODE (((*x).info_macro.maps[i2].d.macro.macro))) : NULL;
                  gt_ggc_m_9tree_node (x3);
                }
                if ((*x).info_macro.maps[i2].d.macro.macro_locations != NULL) {
                  ggc_mark ((*x).info_macro.maps[i2].d.macro.macro_locations);
                }
                break;
              default:
                break;
              }
          }
          ggc_mark ((*x).info_macro.maps);
        }
      }
      {
        size_t l4 = (size_t)(((*x).location_adhoc_data_map).allocated);
        if ((*x).location_adhoc_data_map.data != NULL) {
          size_t i4;
          for (i4 = 0; i4 != (size_t)(l4); i4++) {
          }
          ggc_mark ((*x).location_adhoc_data_map.data);
        }
      }
    }
}

void
gt_ggc_m_II17splay_tree_node_s (void *x_p)
{
  struct splay_tree_node_s * const x = (struct splay_tree_node_s *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_II17splay_tree_node_s ((*x).left);
      gt_ggc_m_II17splay_tree_node_s ((*x).right);
    }
}

void
gt_ggc_m_SP9tree_node17splay_tree_node_s (void *x_p)
{
  struct splay_tree_node_s * const x = (struct splay_tree_node_s *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_S ((void *)(*x).key);
      gt_ggc_m_9tree_node ((void *)(*x).value);
      gt_ggc_m_SP9tree_node17splay_tree_node_s ((*x).left);
      gt_ggc_m_SP9tree_node17splay_tree_node_s ((*x).right);
    }
}

void
gt_ggc_m_P9tree_nodeP9tree_node17splay_tree_node_s (void *x_p)
{
  struct splay_tree_node_s * const x = (struct splay_tree_node_s *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_9tree_node ((void *)(*x).key);
      gt_ggc_m_9tree_node ((void *)(*x).value);
      gt_ggc_m_P9tree_nodeP9tree_node17splay_tree_node_s ((*x).left);
      gt_ggc_m_P9tree_nodeP9tree_node17splay_tree_node_s ((*x).right);
    }
}

void
gt_ggc_m_P17lto_in_decl_state4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      {
        size_t l0 = (size_t)(((*x)).size);
        if ((*x).entries != NULL) {
          size_t i0;
          for (i0 = 0; i0 != (size_t)(l0); i0++) {
            gt_ggc_m_17lto_in_decl_state ((*x).entries[i0]);
          }
          ggc_mark ((*x).entries);
        }
      }
    }
}

void
gt_ggc_m_P9tree_nodeP9tree_node12splay_tree_s (void *x_p)
{
  struct splay_tree_s * const x = (struct splay_tree_s *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_P9tree_nodeP9tree_node17splay_tree_node_s ((*x).root);
    }
}

void
gt_ggc_m_P15tm_restart_node4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      {
        size_t l0 = (size_t)(((*x)).size);
        if ((*x).entries != NULL) {
          size_t i0;
          for (i0 = 0; i0 != (size_t)(l0); i0++) {
            gt_ggc_m_15tm_restart_node ((*x).entries[i0]);
          }
          ggc_mark ((*x).entries);
        }
      }
    }
}

void
gt_ggc_m_P12tree_int_map4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      {
        size_t l0 = (size_t)(((*x)).size);
        if ((*x).entries != NULL) {
          size_t i0;
          for (i0 = 0; i0 != (size_t)(l0); i0++) {
            gt_ggc_m_12tree_int_map ((*x).entries[i0]);
          }
          ggc_mark ((*x).entries);
        }
      }
    }
}

void
gt_ggc_m_P8tree_map4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      {
        size_t l0 = (size_t)(((*x)).size);
        if ((*x).entries != NULL) {
          size_t i0;
          for (i0 = 0; i0 != (size_t)(l0); i0++) {
            gt_ggc_m_8tree_map ((*x).entries[i0]);
          }
          ggc_mark ((*x).entries);
        }
      }
    }
}

void
gt_ggc_m_P24constant_descriptor_tree4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      {
        size_t l0 = (size_t)(((*x)).size);
        if ((*x).entries != NULL) {
          size_t i0;
          for (i0 = 0; i0 != (size_t)(l0); i0++) {
            gt_ggc_m_24constant_descriptor_tree ((*x).entries[i0]);
          }
          ggc_mark ((*x).entries);
        }
      }
    }
}

void
gt_ggc_m_P12object_block4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      {
        size_t l0 = (size_t)(((*x)).size);
        if ((*x).entries != NULL) {
          size_t i0;
          for (i0 = 0; i0 != (size_t)(l0); i0++) {
            gt_ggc_m_12object_block ((*x).entries[i0]);
          }
          ggc_mark ((*x).entries);
        }
      }
    }
}

void
gt_ggc_m_P7section4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      {
        size_t l0 = (size_t)(((*x)).size);
        if ((*x).entries != NULL) {
          size_t i0;
          for (i0 = 0; i0 != (size_t)(l0); i0++) {
            gt_ggc_m_7section ((*x).entries[i0]);
          }
          ggc_mark ((*x).entries);
        }
      }
    }
}

void
gt_ggc_m_P17tree_priority_map4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      {
        size_t l0 = (size_t)(((*x)).size);
        if ((*x).entries != NULL) {
          size_t i0;
          for (i0 = 0; i0 != (size_t)(l0); i0++) {
            gt_ggc_m_17tree_priority_map ((*x).entries[i0]);
          }
          ggc_mark ((*x).entries);
        }
      }
    }
}

void
gt_ggc_m_P12tree_vec_map4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      {
        size_t l0 = (size_t)(((*x)).size);
        if ((*x).entries != NULL) {
          size_t i0;
          for (i0 = 0; i0 != (size_t)(l0); i0++) {
            gt_ggc_m_12tree_vec_map ((*x).entries[i0]);
          }
          ggc_mark ((*x).entries);
        }
      }
    }
}

void
gt_ggc_m_P13tree_decl_map4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      {
        size_t l0 = (size_t)(((*x)).size);
        if ((*x).entries != NULL) {
          size_t i0;
          for (i0 = 0; i0 != (size_t)(l0); i0++) {
            gt_ggc_m_13tree_decl_map ((*x).entries[i0]);
          }
          ggc_mark ((*x).entries);
        }
      }
    }
}

void
gt_ggc_m_P15throw_stmt_node4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      {
        size_t l0 = (size_t)(((*x)).size);
        if ((*x).entries != NULL) {
          size_t i0;
          for (i0 = 0; i0 != (size_t)(l0); i0++) {
            gt_ggc_m_15throw_stmt_node ((*x).entries[i0]);
          }
          ggc_mark ((*x).entries);
        }
      }
    }
}

void
gt_ggc_m_P9reg_attrs4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      {
        size_t l0 = (size_t)(((*x)).size);
        if ((*x).entries != NULL) {
          size_t i0;
          for (i0 = 0; i0 != (size_t)(l0); i0++) {
            gt_ggc_m_9reg_attrs ((*x).entries[i0]);
          }
          ggc_mark ((*x).entries);
        }
      }
    }
}

void
gt_ggc_m_P9mem_attrs4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      {
        size_t l0 = (size_t)(((*x)).size);
        if ((*x).entries != NULL) {
          size_t i0;
          for (i0 = 0; i0 != (size_t)(l0); i0++) {
            gt_ggc_m_9mem_attrs ((*x).entries[i0]);
          }
          ggc_mark ((*x).entries);
        }
      }
    }
}

void
gt_ggc_m_P7rtx_def4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      {
        size_t l0 = (size_t)(((*x)).size);
        if ((*x).entries != NULL) {
          size_t i0;
          for (i0 = 0; i0 != (size_t)(l0); i0++) {
            gt_ggc_m_7rtx_def ((*x).entries[i0]);
          }
          ggc_mark ((*x).entries);
        }
      }
    }
}

void
gt_ggc_m_SP9tree_node12splay_tree_s (void *x_p)
{
  struct splay_tree_s * const x = (struct splay_tree_s *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_SP9tree_node17splay_tree_node_s ((*x).root);
    }
}

void
gt_ggc_m_II12splay_tree_s (void *x_p)
{
  struct splay_tree_s * const x = (struct splay_tree_s *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_II17splay_tree_node_s ((*x).root);
    }
}

void
gt_ggc_m_P15symtab_node_def4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      {
        size_t l0 = (size_t)(((*x)).size);
        if ((*x).entries != NULL) {
          size_t i0;
          for (i0 = 0; i0 != (size_t)(l0); i0++) {
            gt_ggc_m_15symtab_node_def ((*x).entries[i0]);
          }
          ggc_mark ((*x).entries);
        }
      }
    }
}

void
gt_ggc_m_P11cgraph_edge4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      {
        size_t l0 = (size_t)(((*x)).size);
        if ((*x).entries != NULL) {
          size_t i0;
          for (i0 = 0; i0 != (size_t)(l0); i0++) {
            gt_ggc_m_11cgraph_edge ((*x).entries[i0]);
          }
          ggc_mark ((*x).entries);
        }
      }
    }
}

void
gt_ggc_m_P9loop_exit4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      {
        size_t l0 = (size_t)(((*x)).size);
        if ((*x).entries != NULL) {
          size_t i0;
          for (i0 = 0; i0 != (size_t)(l0); i0++) {
            gt_ggc_m_9loop_exit ((*x).entries[i0]);
          }
          ggc_mark ((*x).entries);
        }
      }
    }
}

void
gt_ggc_m_P24types_used_by_vars_entry4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      {
        size_t l0 = (size_t)(((*x)).size);
        if ((*x).entries != NULL) {
          size_t i0;
          for (i0 = 0; i0 != (size_t)(l0); i0++) {
            gt_ggc_m_24types_used_by_vars_entry ((*x).entries[i0]);
          }
          ggc_mark ((*x).entries);
        }
      }
    }
}

void
gt_ggc_m_P9tree_node4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      {
        size_t l0 = (size_t)(((*x)).size);
        if ((*x).entries != NULL) {
          size_t i0;
          for (i0 = 0; i0 != (size_t)(l0); i0++) {
            gt_ggc_m_9tree_node ((*x).entries[i0]);
          }
          ggc_mark ((*x).entries);
        }
      }
    }
}

void
gt_ggc_m_P13libfunc_entry4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      {
        size_t l0 = (size_t)(((*x)).size);
        if ((*x).entries != NULL) {
          size_t i0;
          for (i0 = 0; i0 != (size_t)(l0); i0++) {
            gt_ggc_m_13libfunc_entry ((*x).entries[i0]);
          }
          ggc_mark ((*x).entries);
        }
      }
    }
}

void
gt_pch_nx_vec_inline_summary_t_va_gc_ (void *x_p)
{
  vec<inline_summary_t,va_gc> * const x = (vec<inline_summary_t,va_gc> *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_27vec_inline_summary_t_va_gc_))
    {
      gt_pch_nx (x);
    }
}

void
gt_pch_nx (struct inline_summary& x_r ATTRIBUTE_UNUSED)
{
  struct inline_summary * ATTRIBUTE_UNUSED x = &x_r;
  gt_pch_n_20vec_condition_va_gc_ ((*x).conds);
  gt_pch_n_26vec_size_time_entry_va_gc_ ((*x).entry);
}

void
gt_pch_nx_vec_size_time_entry_va_gc_ (void *x_p)
{
  vec<size_time_entry,va_gc> * const x = (vec<size_time_entry,va_gc> *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_26vec_size_time_entry_va_gc_))
    {
      gt_pch_nx (x);
    }
}

void
gt_pch_nx (struct size_time_entry& x_r ATTRIBUTE_UNUSED)
{
  struct size_time_entry * ATTRIBUTE_UNUSED x = &x_r;
}

void
gt_pch_nx_vec_condition_va_gc_ (void *x_p)
{
  vec<condition,va_gc> * const x = (vec<condition,va_gc> *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_20vec_condition_va_gc_))
    {
      gt_pch_nx (x);
    }
}

void
gt_pch_nx (struct condition& x_r ATTRIBUTE_UNUSED)
{
  struct condition * ATTRIBUTE_UNUSED x = &x_r;
  gt_pch_n_9tree_node ((*x).val);
}

void
gt_pch_nx_lto_in_decl_state (void *x_p)
{
  struct lto_in_decl_state * const x = (struct lto_in_decl_state *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_17lto_in_decl_state))
    {
      {
        size_t i0;
        size_t l0 = (size_t)(LTO_N_DECL_STREAMS);
        for (i0 = 0; i0 != l0; i0++) {
          {
            size_t l1 = (size_t)(((*x).streams[i0]).size);
            if ((*x).streams[i0].trees != NULL) {
              size_t i1;
              for (i1 = 0; i1 != (size_t)(l1); i1++) {
                gt_pch_n_9tree_node ((*x).streams[i0].trees[i1]);
              }
              gt_pch_note_object ((*x).streams[i0].trees, x, gt_pch_p_17lto_in_decl_state);
            }
          }
        }
      }
      gt_pch_n_9tree_node ((*x).fn_decl);
    }
}

void
gt_pch_nx_vec_ipa_edge_args_t_va_gc_ (void *x_p)
{
  vec<ipa_edge_args_t,va_gc> * const x = (vec<ipa_edge_args_t,va_gc> *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_26vec_ipa_edge_args_t_va_gc_))
    {
      gt_pch_nx (x);
    }
}

void
gt_pch_nx (struct ipa_edge_args& x_r ATTRIBUTE_UNUSED)
{
  struct ipa_edge_args * ATTRIBUTE_UNUSED x = &x_r;
  gt_pch_n_26vec_ipa_jump_func_t_va_gc_ ((*x).jump_functions);
}

void
gt_pch_nx_vec_ipa_agg_replacement_value_p_va_gc_ (void *x_p)
{
  vec<ipa_agg_replacement_value_p,va_gc> * const x = (vec<ipa_agg_replacement_value_p,va_gc> *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_38vec_ipa_agg_replacement_value_p_va_gc_))
    {
      gt_pch_nx (x);
    }
}

void
gt_pch_nx (struct ipa_agg_replacement_value *& x)
{
  if (x)
    gt_pch_nx_ipa_agg_replacement_value ((void *) x);
}

void
gt_pch_nx_vec_ipa_jump_func_t_va_gc_ (void *x_p)
{
  vec<ipa_jump_func_t,va_gc> * const x = (vec<ipa_jump_func_t,va_gc> *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_26vec_ipa_jump_func_t_va_gc_))
    {
      gt_pch_nx (x);
    }
}

void
gt_pch_nx (struct ipa_jump_func& x_r ATTRIBUTE_UNUSED)
{
  struct ipa_jump_func * ATTRIBUTE_UNUSED x = &x_r;
  gt_pch_n_28vec_ipa_agg_jf_item_t_va_gc_ ((*x).agg.items);
  switch (((*x)).type)
    {
    case IPA_JF_KNOWN_TYPE:
      gt_pch_n_9tree_node ((*x).value.known_type.base_type);
      gt_pch_n_9tree_node ((*x).value.known_type.component_type);
      break;
    case IPA_JF_CONST:
      gt_pch_n_9tree_node ((*x).value.constant);
      break;
    case IPA_JF_PASS_THROUGH:
      gt_pch_n_9tree_node ((*x).value.pass_through.operand);
      break;
    case IPA_JF_ANCESTOR:
      gt_pch_n_9tree_node ((*x).value.ancestor.type);
      break;
    default:
      break;
    }
}

void
gt_pch_nx_vec_ipa_agg_jf_item_t_va_gc_ (void *x_p)
{
  vec<ipa_agg_jf_item_t,va_gc> * const x = (vec<ipa_agg_jf_item_t,va_gc> *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_28vec_ipa_agg_jf_item_t_va_gc_))
    {
      gt_pch_nx (x);
    }
}

void
gt_pch_nx (struct ipa_agg_jf_item& x_r ATTRIBUTE_UNUSED)
{
  struct ipa_agg_jf_item * ATTRIBUTE_UNUSED x = &x_r;
  gt_pch_n_9tree_node ((*x).value);
}

void
gt_pch_nx_ssa_operand_memory_d (void *x_p)
{
  struct ssa_operand_memory_d * x = (struct ssa_operand_memory_d *)x_p;
  struct ssa_operand_memory_d * xlimit = x;
  while (gt_pch_note_object (xlimit, xlimit, gt_pch_p_20ssa_operand_memory_d))
   xlimit = ((*xlimit).next);
  while (x != xlimit)
    {
      gt_pch_n_20ssa_operand_memory_d ((*x).next);
      x = ((*x).next);
    }
}

void
gt_pch_nx_vec_gimple_va_gc_ (void *x_p)
{
  vec<gimple,va_gc> * const x = (vec<gimple,va_gc> *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_17vec_gimple_va_gc_))
    {
      gt_pch_nx (x);
    }
}

void
gt_pch_nx (union gimple_statement_d *& x)
{
  if (x)
    gt_pch_nx_gimple_statement_d ((void *) x);
}

void
gt_pch_nx_tm_restart_node (void *x_p)
{
  struct tm_restart_node * const x = (struct tm_restart_node *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_15tm_restart_node))
    {
      gt_pch_n_18gimple_statement_d ((*x).stmt);
      gt_pch_n_9tree_node ((*x).label_or_list);
    }
}

void
gt_pch_nx_throw_stmt_node (void *x_p)
{
  struct throw_stmt_node * const x = (struct throw_stmt_node *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_15throw_stmt_node))
    {
      gt_pch_n_18gimple_statement_d ((*x).stmt);
    }
}

void
gt_pch_nx_vec_eh_landing_pad_va_gc_ (void *x_p)
{
  vec<eh_landing_pad,va_gc> * const x = (vec<eh_landing_pad,va_gc> *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_25vec_eh_landing_pad_va_gc_))
    {
      gt_pch_nx (x);
    }
}

void
gt_pch_nx (struct eh_landing_pad_d *& x)
{
  if (x)
    gt_pch_nx_eh_landing_pad_d ((void *) x);
}

void
gt_pch_nx_vec_eh_region_va_gc_ (void *x_p)
{
  vec<eh_region,va_gc> * const x = (vec<eh_region,va_gc> *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_20vec_eh_region_va_gc_))
    {
      gt_pch_nx (x);
    }
}

void
gt_pch_nx (struct eh_region_d *& x)
{
  if (x)
    gt_pch_nx_eh_region_d ((void *) x);
}

void
gt_pch_nx_eh_catch_d (void *x_p)
{
  struct eh_catch_d * const x = (struct eh_catch_d *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_10eh_catch_d))
    {
      gt_pch_n_10eh_catch_d ((*x).next_catch);
      gt_pch_n_10eh_catch_d ((*x).prev_catch);
      gt_pch_n_9tree_node ((*x).type_list);
      gt_pch_n_9tree_node ((*x).filter_list);
      gt_pch_n_9tree_node ((*x).label);
    }
}

void
gt_pch_nx_eh_landing_pad_d (void *x_p)
{
  struct eh_landing_pad_d * const x = (struct eh_landing_pad_d *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_16eh_landing_pad_d))
    {
      gt_pch_n_16eh_landing_pad_d ((*x).next_lp);
      gt_pch_n_11eh_region_d ((*x).region);
      gt_pch_n_9tree_node ((*x).post_landing_pad);
      gt_pch_n_7rtx_def ((*x).landing_pad);
    }
}

void
gt_pch_nx_eh_region_d (void *x_p)
{
  struct eh_region_d * const x = (struct eh_region_d *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_11eh_region_d))
    {
      gt_pch_n_11eh_region_d ((*x).outer);
      gt_pch_n_11eh_region_d ((*x).inner);
      gt_pch_n_11eh_region_d ((*x).next_peer);
      switch ((*x).type)
        {
        case ERT_TRY:
          gt_pch_n_10eh_catch_d ((*x).u.eh_try.first_catch);
          gt_pch_n_10eh_catch_d ((*x).u.eh_try.last_catch);
          break;
        case ERT_ALLOWED_EXCEPTIONS:
          gt_pch_n_9tree_node ((*x).u.allowed.type_list);
          gt_pch_n_9tree_node ((*x).u.allowed.label);
          break;
        case ERT_MUST_NOT_THROW:
          gt_pch_n_9tree_node ((*x).u.must_not_throw.failure_decl);
          break;
        default:
          break;
        }
      gt_pch_n_16eh_landing_pad_d ((*x).landing_pads);
      gt_pch_n_7rtx_def ((*x).exc_ptr_reg);
      gt_pch_n_7rtx_def ((*x).filter_reg);
    }
}

void
gt_pch_nx_vec_dw_cfi_ref_va_gc_ (void *x_p)
{
  vec<dw_cfi_ref,va_gc> * const x = (vec<dw_cfi_ref,va_gc> *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_21vec_dw_cfi_ref_va_gc_))
    {
      gt_pch_nx (x);
    }
}

void
gt_pch_nx (struct dw_cfi_struct *& x)
{
  if (x)
    gt_pch_nx_dw_cfi_struct ((void *) x);
}

void
gt_pch_nx_dw_loc_descr_struct (void *x_p)
{
  struct dw_loc_descr_struct * const x = (struct dw_loc_descr_struct *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_19dw_loc_descr_struct))
    {
      gt_pch_n_19dw_loc_descr_struct ((*x).dw_loc_next);
      gt_pch_n_23addr_table_entry_struct ((*x).dw_loc_oprnd1.val_entry);
      switch (((*x).dw_loc_oprnd1).val_class)
        {
        case dw_val_class_addr:
          gt_pch_n_7rtx_def ((*x).dw_loc_oprnd1.v.val_addr);
          break;
        case dw_val_class_offset:
          break;
        case dw_val_class_loc_list:
          gt_pch_n_18dw_loc_list_struct ((*x).dw_loc_oprnd1.v.val_loc_list);
          break;
        case dw_val_class_loc:
          gt_pch_n_19dw_loc_descr_struct ((*x).dw_loc_oprnd1.v.val_loc);
          break;
        default:
          break;
        case dw_val_class_unsigned_const:
          break;
        case dw_val_class_const_double:
          break;
        case dw_val_class_vec:
          gt_pch_n_S ((*x).dw_loc_oprnd1.v.val_vec.array);
          break;
        case dw_val_class_die_ref:
          gt_pch_n_10die_struct ((*x).dw_loc_oprnd1.v.val_die_ref.die);
          break;
        case dw_val_class_fde_ref:
          break;
        case dw_val_class_str:
          gt_pch_n_20indirect_string_node ((*x).dw_loc_oprnd1.v.val_str);
          break;
        case dw_val_class_lbl_id:
          gt_pch_n_S ((*x).dw_loc_oprnd1.v.val_lbl_id);
          break;
        case dw_val_class_flag:
          break;
        case dw_val_class_file:
          gt_pch_n_15dwarf_file_data ((*x).dw_loc_oprnd1.v.val_file);
          break;
        case dw_val_class_data8:
          break;
        case dw_val_class_decl_ref:
          gt_pch_n_9tree_node ((*x).dw_loc_oprnd1.v.val_decl_ref);
          break;
        case dw_val_class_vms_delta:
          gt_pch_n_S ((*x).dw_loc_oprnd1.v.val_vms_delta.lbl1);
          gt_pch_n_S ((*x).dw_loc_oprnd1.v.val_vms_delta.lbl2);
          break;
        }
      gt_pch_n_23addr_table_entry_struct ((*x).dw_loc_oprnd2.val_entry);
      switch (((*x).dw_loc_oprnd2).val_class)
        {
        case dw_val_class_addr:
          gt_pch_n_7rtx_def ((*x).dw_loc_oprnd2.v.val_addr);
          break;
        case dw_val_class_offset:
          break;
        case dw_val_class_loc_list:
          gt_pch_n_18dw_loc_list_struct ((*x).dw_loc_oprnd2.v.val_loc_list);
          break;
        case dw_val_class_loc:
          gt_pch_n_19dw_loc_descr_struct ((*x).dw_loc_oprnd2.v.val_loc);
          break;
        default:
          break;
        case dw_val_class_unsigned_const:
          break;
        case dw_val_class_const_double:
          break;
        case dw_val_class_vec:
          gt_pch_n_S ((*x).dw_loc_oprnd2.v.val_vec.array);
          break;
        case dw_val_class_die_ref:
          gt_pch_n_10die_struct ((*x).dw_loc_oprnd2.v.val_die_ref.die);
          break;
        case dw_val_class_fde_ref:
          break;
        case dw_val_class_str:
          gt_pch_n_20indirect_string_node ((*x).dw_loc_oprnd2.v.val_str);
          break;
        case dw_val_class_lbl_id:
          gt_pch_n_S ((*x).dw_loc_oprnd2.v.val_lbl_id);
          break;
        case dw_val_class_flag:
          break;
        case dw_val_class_file:
          gt_pch_n_15dwarf_file_data ((*x).dw_loc_oprnd2.v.val_file);
          break;
        case dw_val_class_data8:
          break;
        case dw_val_class_decl_ref:
          gt_pch_n_9tree_node ((*x).dw_loc_oprnd2.v.val_decl_ref);
          break;
        case dw_val_class_vms_delta:
          gt_pch_n_S ((*x).dw_loc_oprnd2.v.val_vms_delta.lbl1);
          gt_pch_n_S ((*x).dw_loc_oprnd2.v.val_vms_delta.lbl2);
          break;
        }
    }
}

void
gt_pch_nx_dw_cfi_struct (void *x_p)
{
  struct dw_cfi_struct * const x = (struct dw_cfi_struct *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_13dw_cfi_struct))
    {
      switch (dw_cfi_oprnd1_desc (((*x)).dw_cfi_opc))
        {
        case dw_cfi_oprnd_reg_num:
          break;
        case dw_cfi_oprnd_offset:
          break;
        case dw_cfi_oprnd_addr:
          gt_pch_n_S ((*x).dw_cfi_oprnd1.dw_cfi_addr);
          break;
        case dw_cfi_oprnd_loc:
          gt_pch_n_19dw_loc_descr_struct ((*x).dw_cfi_oprnd1.dw_cfi_loc);
          break;
        default:
          break;
        }
      switch (dw_cfi_oprnd2_desc (((*x)).dw_cfi_opc))
        {
        case dw_cfi_oprnd_reg_num:
          break;
        case dw_cfi_oprnd_offset:
          break;
        case dw_cfi_oprnd_addr:
          gt_pch_n_S ((*x).dw_cfi_oprnd2.dw_cfi_addr);
          break;
        case dw_cfi_oprnd_loc:
          gt_pch_n_19dw_loc_descr_struct ((*x).dw_cfi_oprnd2.dw_cfi_loc);
          break;
        default:
          break;
        }
    }
}

void
gt_pch_nx_ipa_agg_replacement_value (void *x_p)
{
  struct ipa_agg_replacement_value * const x = (struct ipa_agg_replacement_value *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_25ipa_agg_replacement_value))
    {
      gt_pch_n_25ipa_agg_replacement_value ((*x).next);
      gt_pch_n_9tree_node ((*x).value);
    }
}

void
gt_pch_nx_constant_descriptor_tree (void *x_p)
{
  struct constant_descriptor_tree * const x = (struct constant_descriptor_tree *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_24constant_descriptor_tree))
    {
      gt_pch_n_7rtx_def ((*x).rtl);
      gt_pch_n_9tree_node ((*x).value);
    }
}

void
gt_pch_nx_asm_node (void *x_p)
{
  struct asm_node * const x = (struct asm_node *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_8asm_node))
    {
      gt_pch_n_8asm_node ((*x).next);
      gt_pch_n_9tree_node ((*x).asm_str);
    }
}

void
gt_pch_nx_cgraph_indirect_call_info (void *x_p)
{
  struct cgraph_indirect_call_info * const x = (struct cgraph_indirect_call_info *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_25cgraph_indirect_call_info))
    {
      gt_pch_n_9tree_node ((*x).otr_type);
    }
}

void
gt_pch_nx_cgraph_function_version_info (void *x_p)
{
  struct cgraph_function_version_info * const x = (struct cgraph_function_version_info *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_28cgraph_function_version_info))
    {
      gt_pch_n_11cgraph_node ((*x).this_node);
      gt_pch_n_28cgraph_function_version_info ((*x).prev);
      gt_pch_n_28cgraph_function_version_info ((*x).next);
      gt_pch_n_9tree_node ((*x).dispatcher_resolver);
    }
}

void
gt_pch_nx_cgraph_edge (void *x_p)
{
  struct cgraph_edge * x = (struct cgraph_edge *)x_p;
  struct cgraph_edge * xlimit = x;
  while (gt_pch_note_object (xlimit, xlimit, gt_pch_p_11cgraph_edge))
   xlimit = ((*xlimit).next_caller);
  if (x != xlimit)
    for (;;)
      {
        struct cgraph_edge * const xprev = ((*x).prev_caller);
        if (xprev == NULL) break;
        x = xprev;
        (void) gt_pch_note_object (xprev, xprev, gt_pch_p_11cgraph_edge);
      }
  while (x != xlimit)
    {
      gt_pch_n_11cgraph_node ((*x).caller);
      gt_pch_n_11cgraph_node ((*x).callee);
      gt_pch_n_11cgraph_edge ((*x).prev_caller);
      gt_pch_n_11cgraph_edge ((*x).next_caller);
      gt_pch_n_11cgraph_edge ((*x).prev_callee);
      gt_pch_n_11cgraph_edge ((*x).next_callee);
      gt_pch_n_18gimple_statement_d ((*x).call_stmt);
      gt_pch_n_25cgraph_indirect_call_info ((*x).indirect_info);
      x = ((*x).next_caller);
    }
}

void
gt_pch_nx_vec_ipa_replace_map_p_va_gc_ (void *x_p)
{
  vec<ipa_replace_map_p,va_gc> * const x = (vec<ipa_replace_map_p,va_gc> *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_28vec_ipa_replace_map_p_va_gc_))
    {
      gt_pch_nx (x);
    }
}

void
gt_pch_nx (struct ipa_replace_map *& x)
{
  if (x)
    gt_pch_nx_ipa_replace_map ((void *) x);
}

void
gt_pch_nx_ipa_replace_map (void *x_p)
{
  struct ipa_replace_map * const x = (struct ipa_replace_map *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_15ipa_replace_map))
    {
      gt_pch_n_9tree_node ((*x).old_tree);
      gt_pch_n_9tree_node ((*x).new_tree);
    }
}

void
gt_pch_nx_lto_file_decl_data (void *x_p)
{
  struct lto_file_decl_data * const x = (struct lto_file_decl_data *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_18lto_file_decl_data))
    {
      gt_pch_n_17lto_in_decl_state ((*x).current_decl_state);
      gt_pch_n_17lto_in_decl_state ((*x).global_decl_state);
      gt_pch_n_P17lto_in_decl_state4htab ((*x).function_decl_states);
      gt_pch_n_18lto_file_decl_data ((*x).next);
    }
}

void
gt_pch_nx_vec_ipa_ref_t_va_gc_ (void *x_p)
{
  vec<ipa_ref_t,va_gc> * const x = (vec<ipa_ref_t,va_gc> *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_20vec_ipa_ref_t_va_gc_))
    {
      gt_pch_nx (x);
    }
}

void
gt_pch_nx (struct ipa_ref& x_r ATTRIBUTE_UNUSED)
{
  struct ipa_ref * ATTRIBUTE_UNUSED x = &x_r;
  gt_pch_n_15symtab_node_def ((*x).referring);
  gt_pch_n_15symtab_node_def ((*x).referred);
  gt_pch_n_18gimple_statement_d ((*x).stmt);
}

void
gt_pch_nx_symtab_node_def (void *x_p)
{
  union symtab_node_def * x = (union symtab_node_def *)x_p;
  union symtab_node_def * xlimit = x;
  while (gt_pch_note_object (xlimit, xlimit, gt_pch_p_15symtab_node_def))
   xlimit = ((*xlimit).symbol.next);
  if (x != xlimit)
    for (;;)
      {
        union symtab_node_def * const xprev = ((*x).symbol.previous);
        if (xprev == NULL) break;
        x = xprev;
        (void) gt_pch_note_object (xprev, xprev, gt_pch_p_15symtab_node_def);
      }
  while (x != xlimit)
    {
      switch (((*x)).symbol.type)
        {
        case SYMTAB_SYMBOL:
          gt_pch_n_9tree_node ((*x).symbol.decl);
          gt_pch_n_20vec_ipa_ref_t_va_gc_ ((*x).symbol.ref_list.references);
          gt_pch_n_15symtab_node_def ((*x).symbol.same_comdat_group);
          gt_pch_n_18lto_file_decl_data ((*x).symbol.lto_file_data);
          gt_pch_n_15symtab_node_def ((*x).symbol.next);
          gt_pch_n_15symtab_node_def ((*x).symbol.previous);
          gt_pch_n_15symtab_node_def ((*x).symbol.next_sharing_asm_name);
          gt_pch_n_15symtab_node_def ((*x).symbol.previous_sharing_asm_name);
          break;
        case SYMTAB_FUNCTION:
          gt_pch_n_9tree_node ((*x).x_function.symbol.decl);
          gt_pch_n_20vec_ipa_ref_t_va_gc_ ((*x).x_function.symbol.ref_list.references);
          gt_pch_n_15symtab_node_def ((*x).x_function.symbol.same_comdat_group);
          gt_pch_n_18lto_file_decl_data ((*x).x_function.symbol.lto_file_data);
          gt_pch_n_15symtab_node_def ((*x).x_function.symbol.next);
          gt_pch_n_15symtab_node_def ((*x).x_function.symbol.previous);
          gt_pch_n_15symtab_node_def ((*x).x_function.symbol.next_sharing_asm_name);
          gt_pch_n_15symtab_node_def ((*x).x_function.symbol.previous_sharing_asm_name);
          gt_pch_n_11cgraph_edge ((*x).x_function.callees);
          gt_pch_n_11cgraph_edge ((*x).x_function.callers);
          gt_pch_n_11cgraph_edge ((*x).x_function.indirect_calls);
          {
            union symtab_node_def * const x0 =
              (symtab_node)((*x).x_function.origin);
            gt_pch_n_15symtab_node_def (x0);
          }
          {
            union symtab_node_def * const x1 =
              (symtab_node)((*x).x_function.nested);
            gt_pch_n_15symtab_node_def (x1);
          }
          {
            union symtab_node_def * const x2 =
              (symtab_node)((*x).x_function.next_nested);
            gt_pch_n_15symtab_node_def (x2);
          }
          gt_pch_n_11cgraph_node ((*x).x_function.next_sibling_clone);
          gt_pch_n_11cgraph_node ((*x).x_function.prev_sibling_clone);
          gt_pch_n_11cgraph_node ((*x).x_function.clones);
          gt_pch_n_11cgraph_node ((*x).x_function.clone_of);
          gt_pch_n_P11cgraph_edge4htab ((*x).x_function.call_site_hash);
          gt_pch_n_9tree_node ((*x).x_function.former_clone_of);
          gt_pch_n_11cgraph_node ((*x).x_function.global.inlined_to);
          gt_pch_n_28vec_ipa_replace_map_p_va_gc_ ((*x).x_function.clone.tree_map);
          gt_pch_n_15bitmap_head_def ((*x).x_function.clone.args_to_skip);
          gt_pch_n_15bitmap_head_def ((*x).x_function.clone.combined_args_to_skip);
          gt_pch_n_9tree_node ((*x).x_function.thunk.alias);
          break;
        case SYMTAB_VARIABLE:
          gt_pch_n_9tree_node ((*x).x_variable.symbol.decl);
          gt_pch_n_20vec_ipa_ref_t_va_gc_ ((*x).x_variable.symbol.ref_list.references);
          gt_pch_n_15symtab_node_def ((*x).x_variable.symbol.same_comdat_group);
          gt_pch_n_18lto_file_decl_data ((*x).x_variable.symbol.lto_file_data);
          gt_pch_n_15symtab_node_def ((*x).x_variable.symbol.next);
          gt_pch_n_15symtab_node_def ((*x).x_variable.symbol.previous);
          gt_pch_n_15symtab_node_def ((*x).x_variable.symbol.next_sharing_asm_name);
          gt_pch_n_15symtab_node_def ((*x).x_variable.symbol.previous_sharing_asm_name);
          gt_pch_n_9tree_node ((*x).x_variable.alias_of);
          break;
        default:
          break;
        }
      x = ((*x).symbol.next);
    }
}

void
gt_pch_nx_cgraph_node (void *x_p)
{
  struct cgraph_node * const x = (struct cgraph_node *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_11cgraph_node))
    {
      gt_pch_n_9tree_node ((*x).symbol.decl);
      gt_pch_n_20vec_ipa_ref_t_va_gc_ ((*x).symbol.ref_list.references);
      gt_pch_n_15symtab_node_def ((*x).symbol.same_comdat_group);
      gt_pch_n_18lto_file_decl_data ((*x).symbol.lto_file_data);
      gt_pch_n_15symtab_node_def ((*x).symbol.next);
      gt_pch_n_15symtab_node_def ((*x).symbol.previous);
      gt_pch_n_15symtab_node_def ((*x).symbol.next_sharing_asm_name);
      gt_pch_n_15symtab_node_def ((*x).symbol.previous_sharing_asm_name);
      gt_pch_n_11cgraph_edge ((*x).callees);
      gt_pch_n_11cgraph_edge ((*x).callers);
      gt_pch_n_11cgraph_edge ((*x).indirect_calls);
      {
        union symtab_node_def * const x0 =
          (symtab_node)((*x).origin);
        gt_pch_n_15symtab_node_def (x0);
      }
      {
        union symtab_node_def * const x1 =
          (symtab_node)((*x).nested);
        gt_pch_n_15symtab_node_def (x1);
      }
      {
        union symtab_node_def * const x2 =
          (symtab_node)((*x).next_nested);
        gt_pch_n_15symtab_node_def (x2);
      }
      gt_pch_n_11cgraph_node ((*x).next_sibling_clone);
      gt_pch_n_11cgraph_node ((*x).prev_sibling_clone);
      gt_pch_n_11cgraph_node ((*x).clones);
      gt_pch_n_11cgraph_node ((*x).clone_of);
      gt_pch_n_P11cgraph_edge4htab ((*x).call_site_hash);
      gt_pch_n_9tree_node ((*x).former_clone_of);
      gt_pch_n_11cgraph_node ((*x).global.inlined_to);
      gt_pch_n_28vec_ipa_replace_map_p_va_gc_ ((*x).clone.tree_map);
      gt_pch_n_15bitmap_head_def ((*x).clone.args_to_skip);
      gt_pch_n_15bitmap_head_def ((*x).clone.combined_args_to_skip);
      gt_pch_n_9tree_node ((*x).thunk.alias);
    }
}

void
gt_pch_nx_vec_basic_block_va_gc_ (void *x_p)
{
  vec<basic_block,va_gc> * const x = (vec<basic_block,va_gc> *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_22vec_basic_block_va_gc_))
    {
      gt_pch_nx (x);
    }
}

void
gt_pch_nx (struct basic_block_def *& x)
{
  if (x)
    gt_pch_nx_basic_block_def ((void *) x);
}

void
gt_pch_nx_vec_edge_va_gc_ (void *x_p)
{
  vec<edge,va_gc> * const x = (vec<edge,va_gc> *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_15vec_edge_va_gc_))
    {
      gt_pch_nx (x);
    }
}

void
gt_pch_nx (struct edge_def *& x)
{
  if (x)
    gt_pch_nx_edge_def ((void *) x);
}

void
gt_pch_nx_rtl_bb_info (void *x_p)
{
  struct rtl_bb_info * const x = (struct rtl_bb_info *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_11rtl_bb_info))
    {
      gt_pch_n_7rtx_def ((*x).end_);
      gt_pch_n_7rtx_def ((*x).header_);
      gt_pch_n_7rtx_def ((*x).footer_);
    }
}

void
gt_pch_nx_vec_loop_p_va_gc_ (void *x_p)
{
  vec<loop_p,va_gc> * const x = (vec<loop_p,va_gc> *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_17vec_loop_p_va_gc_))
    {
      gt_pch_nx (x);
    }
}

void
gt_pch_nx (struct loop *& x)
{
  if (x)
    gt_pch_nx_loop ((void *) x);
}

void
gt_pch_nx_loop (void *x_p)
{
  struct loop * x = (struct loop *)x_p;
  struct loop * xlimit = x;
  while (gt_pch_note_object (xlimit, xlimit, gt_pch_p_4loop))
   xlimit = ((*xlimit).next);
  while (x != xlimit)
    {
      gt_pch_n_15basic_block_def ((*x).header);
      gt_pch_n_15basic_block_def ((*x).latch);
      gt_pch_n_17vec_loop_p_va_gc_ ((*x).superloops);
      gt_pch_n_4loop ((*x).inner);
      gt_pch_n_4loop ((*x).next);
      gt_pch_n_9tree_node ((*x).nb_iterations);
      gt_pch_n_13nb_iter_bound ((*x).bounds);
      gt_pch_n_9loop_exit ((*x).exits);
      x = ((*x).next);
    }
}

void
gt_pch_nx_loop_exit (void *x_p)
{
  struct loop_exit * const x = (struct loop_exit *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_9loop_exit))
    {
      gt_pch_n_8edge_def ((*x).e);
      gt_pch_n_9loop_exit ((*x).prev);
      gt_pch_n_9loop_exit ((*x).next);
      gt_pch_n_9loop_exit ((*x).next_e);
    }
}

void
gt_pch_nx_nb_iter_bound (void *x_p)
{
  struct nb_iter_bound * x = (struct nb_iter_bound *)x_p;
  struct nb_iter_bound * xlimit = x;
  while (gt_pch_note_object (xlimit, xlimit, gt_pch_p_13nb_iter_bound))
   xlimit = ((*xlimit).next);
  while (x != xlimit)
    {
      gt_pch_n_18gimple_statement_d ((*x).stmt);
      gt_pch_n_13nb_iter_bound ((*x).next);
      x = ((*x).next);
    }
}

void
gt_pch_nx_types_used_by_vars_entry (void *x_p)
{
  struct types_used_by_vars_entry * const x = (struct types_used_by_vars_entry *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_24types_used_by_vars_entry))
    {
      gt_pch_n_9tree_node ((*x).type);
      gt_pch_n_9tree_node ((*x).var_decl);
    }
}

void
gt_pch_nx_loops (void *x_p)
{
  struct loops * const x = (struct loops *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_5loops))
    {
      gt_pch_n_17vec_loop_p_va_gc_ ((*x).larray);
      gt_pch_n_P9loop_exit4htab ((*x).exits);
      gt_pch_n_4loop ((*x).tree_root);
    }
}

void
gt_pch_nx_control_flow_graph (void *x_p)
{
  struct control_flow_graph * const x = (struct control_flow_graph *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_18control_flow_graph))
    {
      gt_pch_n_15basic_block_def ((*x).x_entry_block_ptr);
      gt_pch_n_15basic_block_def ((*x).x_exit_block_ptr);
      gt_pch_n_22vec_basic_block_va_gc_ ((*x).x_basic_block_info);
      gt_pch_n_22vec_basic_block_va_gc_ ((*x).x_label_to_block_map);
    }
}

void
gt_pch_nx_eh_status (void *x_p)
{
  struct eh_status * const x = (struct eh_status *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_9eh_status))
    {
      gt_pch_n_11eh_region_d ((*x).region_tree);
      gt_pch_n_20vec_eh_region_va_gc_ ((*x).region_array);
      gt_pch_n_25vec_eh_landing_pad_va_gc_ ((*x).lp_array);
      gt_pch_n_P15throw_stmt_node4htab ((*x).throw_stmt_table);
      gt_pch_n_15vec_tree_va_gc_ ((*x).ttype_data);
      switch (targetm.arm_eabi_unwinder)
        {
        case 1:
          gt_pch_n_15vec_tree_va_gc_ ((*x).ehspec_data.arm_eabi);
          break;
        case 0:
          gt_pch_n_16vec_uchar_va_gc_ ((*x).ehspec_data.other);
          break;
        default:
          break;
        }
    }
}

void
gt_pch_nx_stack_usage (void *x_p)
{
  struct stack_usage * const x = (struct stack_usage *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_11stack_usage))
    {
    }
}

void
gt_pch_nx_vec_temp_slot_p_va_gc_ (void *x_p)
{
  vec<temp_slot_p,va_gc> * const x = (vec<temp_slot_p,va_gc> *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_22vec_temp_slot_p_va_gc_))
    {
      gt_pch_nx (x);
    }
}

void
gt_pch_nx (struct temp_slot *& x)
{
  if (x)
    gt_pch_nx_temp_slot ((void *) x);
}

void
gt_pch_nx_frame_space (void *x_p)
{
  struct frame_space * const x = (struct frame_space *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_11frame_space))
    {
      gt_pch_n_11frame_space ((*x).next);
    }
}

void
gt_pch_nx_dw_fde_struct (void *x_p)
{
  struct dw_fde_struct * const x = (struct dw_fde_struct *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_13dw_fde_struct))
    {
      gt_pch_n_9tree_node ((*x).decl);
      gt_pch_n_S ((*x).dw_fde_begin);
      gt_pch_n_S ((*x).dw_fde_current_label);
      gt_pch_n_S ((*x).dw_fde_end);
      gt_pch_n_S ((*x).dw_fde_vms_end_prologue);
      gt_pch_n_S ((*x).dw_fde_vms_begin_epilogue);
      gt_pch_n_S ((*x).dw_fde_second_begin);
      gt_pch_n_S ((*x).dw_fde_second_end);
      gt_pch_n_21vec_dw_cfi_ref_va_gc_ ((*x).dw_fde_cfi);
    }
}

void
gt_pch_nx_gimple_df (void *x_p)
{
  struct gimple_df * const x = (struct gimple_df *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_9gimple_df))
    {
      gt_pch_n_17vec_gimple_va_gc_ ((*x).modified_noreturn_calls);
      gt_pch_n_15vec_tree_va_gc_ ((*x).ssa_names);
      gt_pch_n_9tree_node ((*x).vop);
      gt_pch_n_15bitmap_head_def ((*x).escaped.vars);
      gt_pch_n_15vec_tree_va_gc_ ((*x).free_ssanames);
      gt_pch_n_P9tree_node4htab ((*x).default_defs);
      gt_pch_n_20ssa_operand_memory_d ((*x).ssa_operands.operand_memory);
      gt_pch_n_P15tm_restart_node4htab ((*x).tm_restart);
    }
}

void
gt_pch_nx_vec_call_site_record_va_gc_ (void *x_p)
{
  vec<call_site_record,va_gc> * const x = (vec<call_site_record,va_gc> *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_27vec_call_site_record_va_gc_))
    {
      gt_pch_nx (x);
    }
}

void
gt_pch_nx (struct call_site_record_d *& x)
{
  if (x)
    gt_pch_nx_call_site_record_d ((void *) x);
}

void
gt_pch_nx_vec_uchar_va_gc_ (void *x_p)
{
  vec<uchar,va_gc> * const x = (vec<uchar,va_gc> *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_16vec_uchar_va_gc_))
    {
      gt_pch_nx (x);
    }
}

void
gt_pch_nx_sequence_stack (void *x_p)
{
  struct sequence_stack * const x = (struct sequence_stack *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_14sequence_stack))
    {
      gt_pch_n_7rtx_def ((*x).first);
      gt_pch_n_7rtx_def ((*x).last);
      gt_pch_n_14sequence_stack ((*x).next);
    }
}

void
gt_pch_nx_libfunc_entry (void *x_p)
{
  struct libfunc_entry * const x = (struct libfunc_entry *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_13libfunc_entry))
    {
      gt_pch_n_7rtx_def ((*x).libfunc);
    }
}

void
gt_pch_nx_tree_vec_map (void *x_p)
{
  struct tree_vec_map * const x = (struct tree_vec_map *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_12tree_vec_map))
    {
      gt_pch_n_9tree_node ((*x).base.from);
      gt_pch_n_15vec_tree_va_gc_ ((*x).to);
    }
}

void
gt_pch_nx_tree_priority_map (void *x_p)
{
  struct tree_priority_map * const x = (struct tree_priority_map *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_17tree_priority_map))
    {
      gt_pch_n_9tree_node ((*x).base.from);
    }
}

void
gt_pch_nx_tree_int_map (void *x_p)
{
  struct tree_int_map * const x = (struct tree_int_map *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_12tree_int_map))
    {
      gt_pch_n_9tree_node ((*x).base.from);
    }
}

void
gt_pch_nx_tree_decl_map (void *x_p)
{
  struct tree_decl_map * const x = (struct tree_decl_map *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_13tree_decl_map))
    {
      gt_pch_n_9tree_node ((*x).base.from);
      gt_pch_n_9tree_node ((*x).to);
    }
}

void
gt_pch_nx_tree_map (void *x_p)
{
  struct tree_map * const x = (struct tree_map *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_8tree_map))
    {
      gt_pch_n_9tree_node ((*x).base.from);
      gt_pch_n_9tree_node ((*x).to);
    }
}

void
gt_pch_nx_tree_statement_list_node (void *x_p)
{
  struct tree_statement_list_node * x = (struct tree_statement_list_node *)x_p;
  struct tree_statement_list_node * xlimit = x;
  while (gt_pch_note_object (xlimit, xlimit, gt_pch_p_24tree_statement_list_node))
   xlimit = ((*xlimit).next);
  if (x != xlimit)
    for (;;)
      {
        struct tree_statement_list_node * const xprev = ((*x).prev);
        if (xprev == NULL) break;
        x = xprev;
        (void) gt_pch_note_object (xprev, xprev, gt_pch_p_24tree_statement_list_node);
      }
  while (x != xlimit)
    {
      gt_pch_n_24tree_statement_list_node ((*x).prev);
      gt_pch_n_24tree_statement_list_node ((*x).next);
      gt_pch_n_9tree_node ((*x).stmt);
      x = ((*x).next);
    }
}

void
gt_pch_nx_vec_tree_va_gc_ (void *x_p)
{
  vec<tree,va_gc> * const x = (vec<tree,va_gc> *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_15vec_tree_va_gc_))
    {
      gt_pch_nx (x);
    }
}

void
gt_pch_nx (union tree_node *& x)
{
  if (x)
    gt_pch_nx_lang_tree_node ((void *) x);
}

void
gt_pch_nx_ptr_info_def (void *x_p)
{
  struct ptr_info_def * const x = (struct ptr_info_def *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_12ptr_info_def))
    {
      gt_pch_n_15bitmap_head_def ((*x).pt.vars);
    }
}

void
gt_pch_nx_vec_constructor_elt_va_gc_ (void *x_p)
{
  vec<constructor_elt,va_gc> * const x = (vec<constructor_elt,va_gc> *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_26vec_constructor_elt_va_gc_))
    {
      gt_pch_nx (x);
    }
}

void
gt_pch_nx (struct constructor_elt_d& x_r ATTRIBUTE_UNUSED)
{
  struct constructor_elt_d * ATTRIBUTE_UNUSED x = &x_r;
  gt_pch_n_9tree_node ((*x).index);
  gt_pch_n_9tree_node ((*x).value);
}

void
gt_pch_nx_vec_alias_pair_va_gc_ (void *x_p)
{
  vec<alias_pair,va_gc> * const x = (vec<alias_pair,va_gc> *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_21vec_alias_pair_va_gc_))
    {
      gt_pch_nx (x);
    }
}

void
gt_pch_nx (struct alias_pair& x_r ATTRIBUTE_UNUSED)
{
  struct alias_pair * ATTRIBUTE_UNUSED x = &x_r;
  gt_pch_n_9tree_node ((*x).decl);
  gt_pch_n_9tree_node ((*x).target);
}

void
gt_pch_nx_function (void *x_p)
{
  struct function * const x = (struct function *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_8function))
    {
      gt_pch_n_9eh_status ((*x).eh);
      gt_pch_n_18control_flow_graph ((*x).cfg);
      gt_pch_n_18gimple_statement_d ((*x).gimple_body);
      gt_pch_n_9gimple_df ((*x).gimple_df);
      gt_pch_n_5loops ((*x).x_current_loops);
      gt_pch_n_11stack_usage ((*x).su);
      gt_pch_n_9tree_node ((*x).decl);
      gt_pch_n_9tree_node ((*x).static_chain_decl);
      gt_pch_n_9tree_node ((*x).nonlocal_goto_save_area);
      gt_pch_n_15vec_tree_va_gc_ ((*x).local_decls);
      gt_pch_n_16machine_function ((*x).machine);
      gt_pch_n_17language_function ((*x).language);
      gt_pch_n_P9tree_node4htab ((*x).used_types_hash);
      gt_pch_n_13dw_fde_struct ((*x).fde);
    }
}

void
gt_pch_nx_fixed_value (void *x_p)
{
  struct fixed_value * const x = (struct fixed_value *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_11fixed_value))
    {
    }
}

void
gt_pch_nx_real_value (void *x_p)
{
  struct real_value * const x = (struct real_value *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_10real_value))
    {
    }
}

void
gt_pch_nx_vec_rtx_va_gc_ (void *x_p)
{
  vec<rtx,va_gc> * const x = (vec<rtx,va_gc> *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_14vec_rtx_va_gc_))
    {
      gt_pch_nx (x);
    }
}

void
gt_pch_nx (struct rtx_def *& x)
{
  if (x)
    gt_pch_nx_rtx_def ((void *) x);
}

void
gt_pch_nx_object_block (void *x_p)
{
  struct object_block * const x = (struct object_block *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_12object_block))
    {
      gt_pch_n_7section ((*x).sect);
      gt_pch_n_14vec_rtx_va_gc_ ((*x).objects);
      gt_pch_n_14vec_rtx_va_gc_ ((*x).anchors);
    }
}

void
gt_pch_nx_reg_attrs (void *x_p)
{
  struct reg_attrs * const x = (struct reg_attrs *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_9reg_attrs))
    {
      gt_pch_n_9tree_node ((*x).decl);
    }
}

void
gt_pch_nx_mem_attrs (void *x_p)
{
  struct mem_attrs * const x = (struct mem_attrs *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_9mem_attrs))
    {
      gt_pch_n_9tree_node ((*x).expr);
    }
}

void
gt_pch_nx_bitmap_obstack (void *x_p)
{
  struct bitmap_obstack * const x = (struct bitmap_obstack *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_14bitmap_obstack))
    {
      gt_pch_n_18bitmap_element_def ((*x).elements);
      gt_pch_n_15bitmap_head_def ((*x).heads);
    }
}

void
gt_pch_nx_bitmap_element_def (void *x_p)
{
  struct bitmap_element_def * x = (struct bitmap_element_def *)x_p;
  struct bitmap_element_def * xlimit = x;
  while (gt_pch_note_object (xlimit, xlimit, gt_pch_p_18bitmap_element_def))
   xlimit = ((*xlimit).next);
  if (x != xlimit)
    for (;;)
      {
        struct bitmap_element_def * const xprev = ((*x).prev);
        if (xprev == NULL) break;
        x = xprev;
        (void) gt_pch_note_object (xprev, xprev, gt_pch_p_18bitmap_element_def);
      }
  while (x != xlimit)
    {
      gt_pch_n_18bitmap_element_def ((*x).next);
      gt_pch_n_18bitmap_element_def ((*x).prev);
      x = ((*x).next);
    }
}

void
gt_pch_nx_machine_function (void *x_p)
{
  struct machine_function * const x = (struct machine_function *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_16machine_function))
    {
      gt_pch_n_17stack_local_entry ((*x).stack_locals);
      gt_pch_n_S ((*x).some_ld_name);
      gt_pch_n_7rtx_def ((*x).split_stack_varargs_pointer);
      gt_pch_n_7rtx_def ((*x).fs.cfa_reg);
    }
}

void
gt_pch_nx_basic_block_def (void *x_p)
{
  struct basic_block_def * x = (struct basic_block_def *)x_p;
  struct basic_block_def * xlimit = x;
  while (gt_pch_note_object (xlimit, xlimit, gt_pch_p_15basic_block_def))
   xlimit = ((*xlimit).next_bb);
  if (x != xlimit)
    for (;;)
      {
        struct basic_block_def * const xprev = ((*x).prev_bb);
        if (xprev == NULL) break;
        x = xprev;
        (void) gt_pch_note_object (xprev, xprev, gt_pch_p_15basic_block_def);
      }
  while (x != xlimit)
    {
      gt_pch_n_15vec_edge_va_gc_ ((*x).preds);
      gt_pch_n_15vec_edge_va_gc_ ((*x).succs);
      gt_pch_n_4loop ((*x).loop_father);
      gt_pch_n_15basic_block_def ((*x).prev_bb);
      gt_pch_n_15basic_block_def ((*x).next_bb);
      switch (((((*x)).flags & BB_RTL) != 0))
        {
        case 0:
          gt_pch_n_18gimple_statement_d ((*x).il.gimple.seq);
          gt_pch_n_18gimple_statement_d ((*x).il.gimple.phi_nodes);
          break;
        case 1:
          gt_pch_n_7rtx_def ((*x).il.x.head_);
          gt_pch_n_11rtl_bb_info ((*x).il.x.rtl);
          break;
        default:
          break;
        }
      x = ((*x).next_bb);
    }
}

void
gt_pch_nx_edge_def (void *x_p)
{
  struct edge_def * const x = (struct edge_def *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_8edge_def))
    {
    }
}

void
gt_pch_nx_section (void *x_p)
{
  union section * const x = (union section *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_7section))
    {
      switch (SECTION_STYLE (&(((*x)))))
        {
        case SECTION_NAMED:
          gt_pch_n_S ((*x).named.name);
          gt_pch_n_9tree_node ((*x).named.decl);
          break;
        case SECTION_UNNAMED:
          gt_pch_n_7section ((*x).unnamed.next);
          break;
        case SECTION_NOSWITCH:
          break;
        default:
          break;
        }
    }
}

void
gt_pch_nx_gimple_statement_d (void *x_p)
{
  union gimple_statement_d * x = (union gimple_statement_d *)x_p;
  union gimple_statement_d * xlimit = x;
  while (gt_pch_note_object (xlimit, xlimit, gt_pch_p_18gimple_statement_d))
   xlimit = ((*xlimit).gsbase.next);
  while (x != xlimit)
    {
      switch (gimple_statement_structure (&((*x))))
        {
        case GSS_BASE:
          gt_pch_n_15basic_block_def ((*x).gsbase.bb);
          gt_pch_n_18gimple_statement_d ((*x).gsbase.next);
          break;
        case GSS_WITH_OPS:
          {
            size_t l0 = (size_t)(((*x).gsops).opbase.gsbase.num_ops);
            gt_pch_n_15basic_block_def ((*x).gsops.opbase.gsbase.bb);
            gt_pch_n_18gimple_statement_d ((*x).gsops.opbase.gsbase.next);
            {
              size_t i0;
              for (i0 = 0; i0 != l0; i0++) {
                gt_pch_n_9tree_node ((*x).gsops.op[i0]);
              }
            }
          }
          break;
        case GSS_WITH_MEM_OPS_BASE:
          gt_pch_n_15basic_block_def ((*x).gsmembase.opbase.gsbase.bb);
          gt_pch_n_18gimple_statement_d ((*x).gsmembase.opbase.gsbase.next);
          break;
        case GSS_WITH_MEM_OPS:
          {
            size_t l1 = (size_t)(((*x).gsmem).membase.opbase.gsbase.num_ops);
            gt_pch_n_15basic_block_def ((*x).gsmem.membase.opbase.gsbase.bb);
            gt_pch_n_18gimple_statement_d ((*x).gsmem.membase.opbase.gsbase.next);
            {
              size_t i1;
              for (i1 = 0; i1 != l1; i1++) {
                gt_pch_n_9tree_node ((*x).gsmem.op[i1]);
              }
            }
          }
          break;
        case GSS_CALL:
          {
            size_t l2 = (size_t)(((*x).gimple_call).membase.opbase.gsbase.num_ops);
            gt_pch_n_15basic_block_def ((*x).gimple_call.membase.opbase.gsbase.bb);
            gt_pch_n_18gimple_statement_d ((*x).gimple_call.membase.opbase.gsbase.next);
            gt_pch_n_15bitmap_head_def ((*x).gimple_call.call_used.vars);
            gt_pch_n_15bitmap_head_def ((*x).gimple_call.call_clobbered.vars);
            switch (((*x).gimple_call).membase.opbase.gsbase.subcode & GF_CALL_INTERNAL)
              {
              case 0:
                gt_pch_n_9tree_node ((*x).gimple_call.u.fntype);
                break;
              case GF_CALL_INTERNAL:
                break;
              default:
                break;
              }
            {
              size_t i2;
              for (i2 = 0; i2 != l2; i2++) {
                gt_pch_n_9tree_node ((*x).gimple_call.op[i2]);
              }
            }
          }
          break;
        case GSS_OMP:
          gt_pch_n_15basic_block_def ((*x).omp.gsbase.bb);
          gt_pch_n_18gimple_statement_d ((*x).omp.gsbase.next);
          gt_pch_n_18gimple_statement_d ((*x).omp.body);
          break;
        case GSS_BIND:
          gt_pch_n_15basic_block_def ((*x).gimple_bind.gsbase.bb);
          gt_pch_n_18gimple_statement_d ((*x).gimple_bind.gsbase.next);
          gt_pch_n_9tree_node ((*x).gimple_bind.vars);
          gt_pch_n_9tree_node ((*x).gimple_bind.block);
          gt_pch_n_18gimple_statement_d ((*x).gimple_bind.body);
          break;
        case GSS_CATCH:
          gt_pch_n_15basic_block_def ((*x).gimple_catch.gsbase.bb);
          gt_pch_n_18gimple_statement_d ((*x).gimple_catch.gsbase.next);
          gt_pch_n_9tree_node ((*x).gimple_catch.types);
          gt_pch_n_18gimple_statement_d ((*x).gimple_catch.handler);
          break;
        case GSS_EH_FILTER:
          gt_pch_n_15basic_block_def ((*x).gimple_eh_filter.gsbase.bb);
          gt_pch_n_18gimple_statement_d ((*x).gimple_eh_filter.gsbase.next);
          gt_pch_n_9tree_node ((*x).gimple_eh_filter.types);
          gt_pch_n_18gimple_statement_d ((*x).gimple_eh_filter.failure);
          break;
        case GSS_EH_MNT:
          gt_pch_n_15basic_block_def ((*x).gimple_eh_mnt.gsbase.bb);
          gt_pch_n_18gimple_statement_d ((*x).gimple_eh_mnt.gsbase.next);
          gt_pch_n_9tree_node ((*x).gimple_eh_mnt.fndecl);
          break;
        case GSS_EH_ELSE:
          gt_pch_n_15basic_block_def ((*x).gimple_eh_else.gsbase.bb);
          gt_pch_n_18gimple_statement_d ((*x).gimple_eh_else.gsbase.next);
          gt_pch_n_18gimple_statement_d ((*x).gimple_eh_else.n_body);
          gt_pch_n_18gimple_statement_d ((*x).gimple_eh_else.e_body);
          break;
        case GSS_PHI:
          {
            size_t l3 = (size_t)(((*x).gimple_phi).nargs);
            gt_pch_n_15basic_block_def ((*x).gimple_phi.gsbase.bb);
            gt_pch_n_18gimple_statement_d ((*x).gimple_phi.gsbase.next);
            gt_pch_n_9tree_node ((*x).gimple_phi.result);
            {
              size_t i3;
              for (i3 = 0; i3 != l3; i3++) {
                gt_pch_n_9tree_node ((*x).gimple_phi.args[i3].def);
              }
            }
          }
          break;
        case GSS_EH_CTRL:
          gt_pch_n_15basic_block_def ((*x).gimple_eh_ctrl.gsbase.bb);
          gt_pch_n_18gimple_statement_d ((*x).gimple_eh_ctrl.gsbase.next);
          break;
        case GSS_TRY:
          gt_pch_n_15basic_block_def ((*x).gimple_try.gsbase.bb);
          gt_pch_n_18gimple_statement_d ((*x).gimple_try.gsbase.next);
          gt_pch_n_18gimple_statement_d ((*x).gimple_try.eval);
          gt_pch_n_18gimple_statement_d ((*x).gimple_try.cleanup);
          break;
        case GSS_WCE:
          gt_pch_n_15basic_block_def ((*x).gimple_wce.gsbase.bb);
          gt_pch_n_18gimple_statement_d ((*x).gimple_wce.gsbase.next);
          gt_pch_n_18gimple_statement_d ((*x).gimple_wce.cleanup);
          break;
        case GSS_ASM:
          {
            size_t l4 = (size_t)(((*x).gimple_asm).membase.opbase.gsbase.num_ops);
            gt_pch_n_15basic_block_def ((*x).gimple_asm.membase.opbase.gsbase.bb);
            gt_pch_n_18gimple_statement_d ((*x).gimple_asm.membase.opbase.gsbase.next);
            gt_pch_n_S ((*x).gimple_asm.string);
            {
              size_t i4;
              for (i4 = 0; i4 != l4; i4++) {
                gt_pch_n_9tree_node ((*x).gimple_asm.op[i4]);
              }
            }
          }
          break;
        case GSS_OMP_CRITICAL:
          gt_pch_n_15basic_block_def ((*x).gimple_omp_critical.omp.gsbase.bb);
          gt_pch_n_18gimple_statement_d ((*x).gimple_omp_critical.omp.gsbase.next);
          gt_pch_n_18gimple_statement_d ((*x).gimple_omp_critical.omp.body);
          gt_pch_n_9tree_node ((*x).gimple_omp_critical.name);
          break;
        case GSS_OMP_FOR:
          {
            size_t l5 = (size_t)(((*x).gimple_omp_for).collapse);
            gt_pch_n_15basic_block_def ((*x).gimple_omp_for.omp.gsbase.bb);
            gt_pch_n_18gimple_statement_d ((*x).gimple_omp_for.omp.gsbase.next);
            gt_pch_n_18gimple_statement_d ((*x).gimple_omp_for.omp.body);
            gt_pch_n_9tree_node ((*x).gimple_omp_for.clauses);
            if ((*x).gimple_omp_for.iter != NULL) {
              size_t i5;
              for (i5 = 0; i5 != (size_t)(l5); i5++) {
                gt_pch_n_9tree_node ((*x).gimple_omp_for.iter[i5].index);
                gt_pch_n_9tree_node ((*x).gimple_omp_for.iter[i5].initial);
                gt_pch_n_9tree_node ((*x).gimple_omp_for.iter[i5].final);
                gt_pch_n_9tree_node ((*x).gimple_omp_for.iter[i5].incr);
              }
              gt_pch_note_object ((*x).gimple_omp_for.iter, x, gt_pch_p_18gimple_statement_d);
            }
            gt_pch_n_18gimple_statement_d ((*x).gimple_omp_for.pre_body);
          }
          break;
        case GSS_OMP_PARALLEL:
          gt_pch_n_15basic_block_def ((*x).gimple_omp_parallel.omp.gsbase.bb);
          gt_pch_n_18gimple_statement_d ((*x).gimple_omp_parallel.omp.gsbase.next);
          gt_pch_n_18gimple_statement_d ((*x).gimple_omp_parallel.omp.body);
          gt_pch_n_9tree_node ((*x).gimple_omp_parallel.clauses);
          gt_pch_n_9tree_node ((*x).gimple_omp_parallel.child_fn);
          gt_pch_n_9tree_node ((*x).gimple_omp_parallel.data_arg);
          break;
        case GSS_OMP_TASK:
          gt_pch_n_15basic_block_def ((*x).gimple_omp_task.par.omp.gsbase.bb);
          gt_pch_n_18gimple_statement_d ((*x).gimple_omp_task.par.omp.gsbase.next);
          gt_pch_n_18gimple_statement_d ((*x).gimple_omp_task.par.omp.body);
          gt_pch_n_9tree_node ((*x).gimple_omp_task.par.clauses);
          gt_pch_n_9tree_node ((*x).gimple_omp_task.par.child_fn);
          gt_pch_n_9tree_node ((*x).gimple_omp_task.par.data_arg);
          gt_pch_n_9tree_node ((*x).gimple_omp_task.copy_fn);
          gt_pch_n_9tree_node ((*x).gimple_omp_task.arg_size);
          gt_pch_n_9tree_node ((*x).gimple_omp_task.arg_align);
          break;
        case GSS_OMP_SECTIONS:
          gt_pch_n_15basic_block_def ((*x).gimple_omp_sections.omp.gsbase.bb);
          gt_pch_n_18gimple_statement_d ((*x).gimple_omp_sections.omp.gsbase.next);
          gt_pch_n_18gimple_statement_d ((*x).gimple_omp_sections.omp.body);
          gt_pch_n_9tree_node ((*x).gimple_omp_sections.clauses);
          gt_pch_n_9tree_node ((*x).gimple_omp_sections.control);
          break;
        case GSS_OMP_SINGLE:
          gt_pch_n_15basic_block_def ((*x).gimple_omp_single.omp.gsbase.bb);
          gt_pch_n_18gimple_statement_d ((*x).gimple_omp_single.omp.gsbase.next);
          gt_pch_n_18gimple_statement_d ((*x).gimple_omp_single.omp.body);
          gt_pch_n_9tree_node ((*x).gimple_omp_single.clauses);
          break;
        case GSS_OMP_CONTINUE:
          gt_pch_n_15basic_block_def ((*x).gimple_omp_continue.gsbase.bb);
          gt_pch_n_18gimple_statement_d ((*x).gimple_omp_continue.gsbase.next);
          gt_pch_n_9tree_node ((*x).gimple_omp_continue.control_def);
          gt_pch_n_9tree_node ((*x).gimple_omp_continue.control_use);
          break;
        case GSS_OMP_ATOMIC_LOAD:
          gt_pch_n_15basic_block_def ((*x).gimple_omp_atomic_load.gsbase.bb);
          gt_pch_n_18gimple_statement_d ((*x).gimple_omp_atomic_load.gsbase.next);
          gt_pch_n_9tree_node ((*x).gimple_omp_atomic_load.rhs);
          gt_pch_n_9tree_node ((*x).gimple_omp_atomic_load.lhs);
          break;
        case GSS_OMP_ATOMIC_STORE:
          gt_pch_n_15basic_block_def ((*x).gimple_omp_atomic_store.gsbase.bb);
          gt_pch_n_18gimple_statement_d ((*x).gimple_omp_atomic_store.gsbase.next);
          gt_pch_n_9tree_node ((*x).gimple_omp_atomic_store.val);
          break;
        case GSS_TRANSACTION:
          gt_pch_n_15basic_block_def ((*x).gimple_transaction.gsbase.opbase.gsbase.bb);
          gt_pch_n_18gimple_statement_d ((*x).gimple_transaction.gsbase.opbase.gsbase.next);
          gt_pch_n_18gimple_statement_d ((*x).gimple_transaction.body);
          gt_pch_n_9tree_node ((*x).gimple_transaction.label);
          break;
        default:
          break;
        }
      x = ((*x).gsbase.next);
    }
}

void
gt_pch_nx_rtvec_def (void *x_p)
{
  struct rtvec_def * const x = (struct rtvec_def *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_9rtvec_def))
    {
      {
        size_t l0 = (size_t)(((*x)).num_elem);
        {
          size_t i0;
          for (i0 = 0; i0 != l0; i0++) {
            gt_pch_n_7rtx_def ((*x).elem[i0]);
          }
        }
      }
    }
}

void
gt_pch_nx_rtx_def (void *x_p)
{
  struct rtx_def * x = (struct rtx_def *)x_p;
  struct rtx_def * xlimit = x;
  while (gt_pch_note_object (xlimit, xlimit, gt_pch_p_7rtx_def))
   xlimit = (RTX_NEXT (&(*xlimit)));
  if (x != xlimit)
    for (;;)
      {
        struct rtx_def * const xprev = (RTX_PREV (&(*x)));
        if (xprev == NULL) break;
        x = xprev;
        (void) gt_pch_note_object (xprev, xprev, gt_pch_p_7rtx_def);
      }
  while (x != xlimit)
    {
      switch (GET_CODE (&(*x)))
        {
        case DEBUG_PARAMETER_REF:
          gt_pch_n_9tree_node ((*x).u.fld[0].rt_tree);
          break;
        case ENTRY_VALUE:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case DEBUG_IMPLICIT_PTR:
          gt_pch_n_9tree_node ((*x).u.fld[0].rt_tree);
          break;
        case VAR_LOCATION:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_9tree_node ((*x).u.fld[0].rt_tree);
          break;
        case FMA:
          gt_pch_n_7rtx_def ((*x).u.fld[2].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case US_TRUNCATE:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SS_TRUNCATE:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case US_MINUS:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case US_ASHIFT:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SS_ASHIFT:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SS_ABS:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case US_NEG:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SS_NEG:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SS_MINUS:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case US_PLUS:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SS_PLUS:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case VEC_DUPLICATE:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case VEC_CONCAT:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case VEC_SELECT:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case VEC_MERGE:
          gt_pch_n_7rtx_def ((*x).u.fld[2].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case LO_SUM:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case HIGH:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case ZERO_EXTRACT:
          gt_pch_n_7rtx_def ((*x).u.fld[2].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SIGN_EXTRACT:
          gt_pch_n_7rtx_def ((*x).u.fld[2].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case PARITY:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case POPCOUNT:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case CTZ:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case CLZ:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case CLRSB:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case FFS:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case BSWAP:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SQRT:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case ABS:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case UNSIGNED_SAT_FRACT:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SAT_FRACT:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case UNSIGNED_FRACT_CONVERT:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case FRACT_CONVERT:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case UNSIGNED_FIX:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case UNSIGNED_FLOAT:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case FIX:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case FLOAT:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case FLOAT_TRUNCATE:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case FLOAT_EXTEND:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case TRUNCATE:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case ZERO_EXTEND:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SIGN_EXTEND:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case LTGT:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case UNLT:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case UNLE:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case UNGT:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case UNGE:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case UNEQ:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case ORDERED:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case UNORDERED:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case LTU:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case LEU:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case GTU:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case GEU:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case LT:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case LE:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case GT:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case GE:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case EQ:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case NE:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case POST_MODIFY:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case PRE_MODIFY:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case POST_INC:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case POST_DEC:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case PRE_INC:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case PRE_DEC:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case UMAX:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case UMIN:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SMAX:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SMIN:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case ROTATERT:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case LSHIFTRT:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case ASHIFTRT:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case ROTATE:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case ASHIFT:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case NOT:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case XOR:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case IOR:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case AND:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case UMOD:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case UDIV:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case MOD:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case US_DIV:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SS_DIV:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case DIV:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case US_MULT:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SS_MULT:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case MULT:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case NEG:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case MINUS:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case PLUS:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case COMPARE:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case IF_THEN_ELSE:
          gt_pch_n_7rtx_def ((*x).u.fld[2].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case CC0:
          break;
        case SYMBOL_REF:
          switch (SYMBOL_REF_HAS_BLOCK_INFO_P (&(*x)))
            {
            case 1:
              gt_pch_n_12object_block ((*x).u.block_sym.block);
              break;
            default:
              break;
            }
          switch (CONSTANT_POOL_ADDRESS_P (&(*x)))
            {
            case 1:
              gt_pch_n_23constant_descriptor_rtx ((*x).u.fld[2].rt_constant);
              break;
            default:
              gt_pch_n_9tree_node ((*x).u.fld[2].rt_tree);
              break;
            }
          gt_pch_n_S ((*x).u.fld[0].rt_str);
          break;
        case LABEL_REF:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case MEM:
          gt_pch_n_9mem_attrs ((*x).u.fld[1].rt_mem);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case CONCATN:
          gt_pch_n_9rtvec_def ((*x).u.fld[0].rt_rtvec);
          break;
        case CONCAT:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case STRICT_LOW_PART:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SUBREG:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SCRATCH:
          break;
        case REG:
          gt_pch_n_9reg_attrs ((*x).u.fld[2].rt_reg);
          break;
        case PC:
          break;
        case CONST:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case CONST_STRING:
          gt_pch_n_S ((*x).u.fld[0].rt_str);
          break;
        case CONST_VECTOR:
          gt_pch_n_9rtvec_def ((*x).u.fld[0].rt_rtvec);
          break;
        case CONST_DOUBLE:
          break;
        case CONST_FIXED:
          break;
        case CONST_INT:
          break;
        case TRAP_IF:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case EH_RETURN:
          break;
        case SIMPLE_RETURN:
          break;
        case RETURN:
          break;
        case CALL:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case CLOBBER:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case USE:
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case SET:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case PREFETCH:
          gt_pch_n_7rtx_def ((*x).u.fld[2].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case ADDR_DIFF_VEC:
          gt_pch_n_7rtx_def ((*x).u.fld[3].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[2].rt_rtx);
          gt_pch_n_9rtvec_def ((*x).u.fld[1].rt_rtvec);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case ADDR_VEC:
          gt_pch_n_9rtvec_def ((*x).u.fld[0].rt_rtvec);
          break;
        case UNSPEC_VOLATILE:
          gt_pch_n_9rtvec_def ((*x).u.fld[0].rt_rtvec);
          break;
        case UNSPEC:
          gt_pch_n_9rtvec_def ((*x).u.fld[0].rt_rtvec);
          break;
        case ASM_OPERANDS:
          gt_pch_n_9rtvec_def ((*x).u.fld[5].rt_rtvec);
          gt_pch_n_9rtvec_def ((*x).u.fld[4].rt_rtvec);
          gt_pch_n_9rtvec_def ((*x).u.fld[3].rt_rtvec);
          gt_pch_n_S ((*x).u.fld[1].rt_str);
          gt_pch_n_S ((*x).u.fld[0].rt_str);
          break;
        case ASM_INPUT:
          gt_pch_n_S ((*x).u.fld[0].rt_str);
          break;
        case PARALLEL:
          gt_pch_n_9rtvec_def ((*x).u.fld[0].rt_rtvec);
          break;
        case COND_EXEC:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case NOTE:
          switch (NOTE_KIND (&(*x)))
            {
            default:
              gt_pch_n_S ((*x).u.fld[4].rt_str);
              break;
            case NOTE_INSN_CFI_LABEL:
              break;
            case NOTE_INSN_CFI:
              break;
            case NOTE_INSN_SWITCH_TEXT_SECTIONS:
              break;
            case NOTE_INSN_BASIC_BLOCK:
              break;
            case NOTE_INSN_CALL_ARG_LOCATION:
              gt_pch_n_7rtx_def ((*x).u.fld[4].rt_rtx);
              break;
            case NOTE_INSN_VAR_LOCATION:
              gt_pch_n_7rtx_def ((*x).u.fld[4].rt_rtx);
              break;
            case NOTE_INSN_EH_REGION_END:
              break;
            case NOTE_INSN_EH_REGION_BEG:
              break;
            case NOTE_INSN_EPILOGUE_BEG:
              break;
            case NOTE_INSN_PROLOGUE_END:
              break;
            case NOTE_INSN_FUNCTION_BEG:
              break;
            case NOTE_INSN_BLOCK_END:
              gt_pch_n_9tree_node ((*x).u.fld[4].rt_tree);
              break;
            case NOTE_INSN_BLOCK_BEG:
              gt_pch_n_9tree_node ((*x).u.fld[4].rt_tree);
              break;
            case NOTE_INSN_DELETED_DEBUG_LABEL:
              gt_pch_n_S ((*x).u.fld[4].rt_str);
              break;
            case NOTE_INSN_DELETED_LABEL:
              gt_pch_n_S ((*x).u.fld[4].rt_str);
              break;
            case NOTE_INSN_DELETED:
              break;
            }
          gt_pch_n_15basic_block_def ((*x).u.fld[3].rt_bb);
          gt_pch_n_7rtx_def ((*x).u.fld[2].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          break;
        case CODE_LABEL:
          gt_pch_n_S ((*x).u.fld[7].rt_str);
          gt_pch_n_7rtx_def ((*x).u.fld[4].rt_rtx);
          gt_pch_n_15basic_block_def ((*x).u.fld[3].rt_bb);
          gt_pch_n_7rtx_def ((*x).u.fld[2].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          break;
        case BARRIER:
          gt_pch_n_7rtx_def ((*x).u.fld[2].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          break;
        case CALL_INSN:
          gt_pch_n_7rtx_def ((*x).u.fld[8].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[7].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[4].rt_rtx);
          gt_pch_n_15basic_block_def ((*x).u.fld[3].rt_bb);
          gt_pch_n_7rtx_def ((*x).u.fld[2].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          break;
        case JUMP_INSN:
          gt_pch_n_7rtx_def ((*x).u.fld[8].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[7].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[4].rt_rtx);
          gt_pch_n_15basic_block_def ((*x).u.fld[3].rt_bb);
          gt_pch_n_7rtx_def ((*x).u.fld[2].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          break;
        case INSN:
          gt_pch_n_7rtx_def ((*x).u.fld[7].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[4].rt_rtx);
          gt_pch_n_15basic_block_def ((*x).u.fld[3].rt_bb);
          gt_pch_n_7rtx_def ((*x).u.fld[2].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          break;
        case DEBUG_INSN:
          gt_pch_n_7rtx_def ((*x).u.fld[7].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[4].rt_rtx);
          gt_pch_n_15basic_block_def ((*x).u.fld[3].rt_bb);
          gt_pch_n_7rtx_def ((*x).u.fld[2].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          break;
        case ADDRESS:
          break;
        case SEQUENCE:
          gt_pch_n_9rtvec_def ((*x).u.fld[0].rt_rtvec);
          break;
        case INSN_LIST:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case EXPR_LIST:
          gt_pch_n_7rtx_def ((*x).u.fld[1].rt_rtx);
          gt_pch_n_7rtx_def ((*x).u.fld[0].rt_rtx);
          break;
        case DEBUG_EXPR:
          gt_pch_n_9tree_node ((*x).u.fld[0].rt_tree);
          break;
        case VALUE:
          break;
        case UNKNOWN:
          break;
        default:
          break;
        }
      x = (RTX_NEXT (&(*x)));
    }
}

void
gt_pch_nx_bitmap_head_def (void *x_p)
{
  struct bitmap_head_def * const x = (struct bitmap_head_def *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_15bitmap_head_def))
    {
      gt_pch_n_18bitmap_element_def ((*x).first);
      gt_pch_n_14bitmap_obstack ((*x).obstack);
    }
}

void
gt_pch_nx_answer (void *x_p)
{
  struct answer * const x = (struct answer *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_6answer))
    {
      {
        size_t l0 = (size_t)(((*x)).count);
        gt_pch_n_6answer ((*x).next);
        {
          size_t i0;
          for (i0 = 0; i0 != l0; i0++) {
            switch (cpp_token_val_index (&((*x).first[i0])))
              {
              case CPP_TOKEN_FLD_NODE:
                {
                  union tree_node * const x1 =
                    ((*x).first[i0].val.node.node) ? HT_IDENT_TO_GCC_IDENT (HT_NODE (((*x).first[i0].val.node.node))) : NULL;
                  gt_pch_n_9tree_node (x1);
                }
                break;
              case CPP_TOKEN_FLD_SOURCE:
                gt_pch_n_9cpp_token ((*x).first[i0].val.source);
                break;
              case CPP_TOKEN_FLD_STR:
                gt_pch_n_S ((*x).first[i0].val.str.text);
                break;
              case CPP_TOKEN_FLD_ARG_NO:
                break;
              case CPP_TOKEN_FLD_TOKEN_NO:
                break;
              case CPP_TOKEN_FLD_PRAGMA:
                break;
              default:
                break;
              }
          }
        }
      }
    }
}

void
gt_pch_nx_cpp_macro (void *x_p)
{
  struct cpp_macro * const x = (struct cpp_macro *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_9cpp_macro))
    {
      {
        size_t l0 = (size_t)(((*x)).paramc);
        if ((*x).params != NULL) {
          size_t i0;
          for (i0 = 0; i0 != (size_t)(l0); i0++) {
            {
              union tree_node * const x1 =
                ((*x).params[i0]) ? HT_IDENT_TO_GCC_IDENT (HT_NODE (((*x).params[i0]))) : NULL;
              gt_pch_n_9tree_node (x1);
            }
          }
          gt_pch_note_object ((*x).params, x, gt_pch_p_9cpp_macro);
        }
        switch (((*x)).traditional)
          {
          case 0:
            if ((*x).exp.tokens != NULL) {
              size_t i2;
              for (i2 = 0; i2 != (size_t)((*x).count); i2++) {
                switch (cpp_token_val_index (&((*x).exp.tokens[i2])))
                  {
                  case CPP_TOKEN_FLD_NODE:
                    {
                      union tree_node * const x3 =
                        ((*x).exp.tokens[i2].val.node.node) ? HT_IDENT_TO_GCC_IDENT (HT_NODE (((*x).exp.tokens[i2].val.node.node))) : NULL;
                      gt_pch_n_9tree_node (x3);
                    }
                    break;
                  case CPP_TOKEN_FLD_SOURCE:
                    gt_pch_n_9cpp_token ((*x).exp.tokens[i2].val.source);
                    break;
                  case CPP_TOKEN_FLD_STR:
                    gt_pch_n_S ((*x).exp.tokens[i2].val.str.text);
                    break;
                  case CPP_TOKEN_FLD_ARG_NO:
                    break;
                  case CPP_TOKEN_FLD_TOKEN_NO:
                    break;
                  case CPP_TOKEN_FLD_PRAGMA:
                    break;
                  default:
                    break;
                  }
              }
              gt_pch_note_object ((*x).exp.tokens, x, gt_pch_p_9cpp_macro);
            }
            break;
          case 1:
            gt_pch_n_S ((*x).exp.text);
            break;
          default:
            break;
          }
      }
    }
}

void
gt_pch_nx_cpp_token (void *x_p)
{
  struct cpp_token * const x = (struct cpp_token *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_9cpp_token))
    {
      switch (cpp_token_val_index (&((*x))))
        {
        case CPP_TOKEN_FLD_NODE:
          {
            union tree_node * const x0 =
              ((*x).val.node.node) ? HT_IDENT_TO_GCC_IDENT (HT_NODE (((*x).val.node.node))) : NULL;
            gt_pch_n_9tree_node (x0);
          }
          break;
        case CPP_TOKEN_FLD_SOURCE:
          gt_pch_n_9cpp_token ((*x).val.source);
          break;
        case CPP_TOKEN_FLD_STR:
          gt_pch_n_S ((*x).val.str.text);
          break;
        case CPP_TOKEN_FLD_ARG_NO:
          break;
        case CPP_TOKEN_FLD_TOKEN_NO:
          break;
        case CPP_TOKEN_FLD_PRAGMA:
          break;
        default:
          break;
        }
    }
}

void
gt_pch_nx_line_maps (void *x_p)
{
  struct line_maps * const x = (struct line_maps *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_9line_maps))
    {
      {
        size_t l0 = (size_t)(((*x).info_ordinary).used);
        if ((*x).info_ordinary.maps != NULL) {
          size_t i0;
          for (i0 = 0; i0 != (size_t)(l0); i0++) {
            switch (((*x).info_ordinary.maps[i0]).reason == LC_ENTER_MACRO)
              {
              case 0:
                gt_pch_n_S ((*x).info_ordinary.maps[i0].d.ordinary.to_file);
                break;
              case 1:
                {
                  union tree_node * const x1 =
                    ((*x).info_ordinary.maps[i0].d.macro.macro) ? HT_IDENT_TO_GCC_IDENT (HT_NODE (((*x).info_ordinary.maps[i0].d.macro.macro))) : NULL;
                  gt_pch_n_9tree_node (x1);
                }
                if ((*x).info_ordinary.maps[i0].d.macro.macro_locations != NULL) {
                  gt_pch_note_object ((*x).info_ordinary.maps[i0].d.macro.macro_locations, x, gt_pch_p_9line_maps);
                }
                break;
              default:
                break;
              }
          }
          gt_pch_note_object ((*x).info_ordinary.maps, x, gt_pch_p_9line_maps);
        }
      }
      {
        size_t l2 = (size_t)(((*x).info_macro).used);
        if ((*x).info_macro.maps != NULL) {
          size_t i2;
          for (i2 = 0; i2 != (size_t)(l2); i2++) {
            switch (((*x).info_macro.maps[i2]).reason == LC_ENTER_MACRO)
              {
              case 0:
                gt_pch_n_S ((*x).info_macro.maps[i2].d.ordinary.to_file);
                break;
              case 1:
                {
                  union tree_node * const x3 =
                    ((*x).info_macro.maps[i2].d.macro.macro) ? HT_IDENT_TO_GCC_IDENT (HT_NODE (((*x).info_macro.maps[i2].d.macro.macro))) : NULL;
                  gt_pch_n_9tree_node (x3);
                }
                if ((*x).info_macro.maps[i2].d.macro.macro_locations != NULL) {
                  gt_pch_note_object ((*x).info_macro.maps[i2].d.macro.macro_locations, x, gt_pch_p_9line_maps);
                }
                break;
              default:
                break;
              }
          }
          gt_pch_note_object ((*x).info_macro.maps, x, gt_pch_p_9line_maps);
        }
      }
      {
        size_t l4 = (size_t)(((*x).location_adhoc_data_map).allocated);
        if ((*x).location_adhoc_data_map.data != NULL) {
          size_t i4;
          for (i4 = 0; i4 != (size_t)(l4); i4++) {
          }
          gt_pch_note_object ((*x).location_adhoc_data_map.data, x, gt_pch_p_9line_maps);
        }
      }
    }
}

void
gt_pch_n_II17splay_tree_node_s (void *x_p)
{
  struct splay_tree_node_s * const x = (struct splay_tree_node_s *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_II17splay_tree_node_s))
    {
      gt_pch_n_II17splay_tree_node_s ((*x).left);
      gt_pch_n_II17splay_tree_node_s ((*x).right);
    }
}

void
gt_pch_n_SP9tree_node17splay_tree_node_s (void *x_p)
{
  struct splay_tree_node_s * const x = (struct splay_tree_node_s *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_SP9tree_node17splay_tree_node_s))
    {
      gt_pch_n_S ((void *)(*x).key);
      gt_pch_n_9tree_node ((void *)(*x).value);
      gt_pch_n_SP9tree_node17splay_tree_node_s ((*x).left);
      gt_pch_n_SP9tree_node17splay_tree_node_s ((*x).right);
    }
}

void
gt_pch_n_P9tree_nodeP9tree_node17splay_tree_node_s (void *x_p)
{
  struct splay_tree_node_s * const x = (struct splay_tree_node_s *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_P9tree_nodeP9tree_node17splay_tree_node_s))
    {
      gt_pch_n_9tree_node ((void *)(*x).key);
      gt_pch_n_9tree_node ((void *)(*x).value);
      gt_pch_n_P9tree_nodeP9tree_node17splay_tree_node_s ((*x).left);
      gt_pch_n_P9tree_nodeP9tree_node17splay_tree_node_s ((*x).right);
    }
}

void
gt_pch_n_P17lto_in_decl_state4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_P17lto_in_decl_state4htab))
    {
      {
        size_t l0 = (size_t)(((*x)).size);
        if ((*x).entries != NULL) {
          size_t i0;
          for (i0 = 0; i0 != (size_t)(l0); i0++) {
            gt_pch_n_17lto_in_decl_state ((*x).entries[i0]);
          }
          gt_pch_note_object ((*x).entries, x, gt_pch_p_P17lto_in_decl_state4htab);
        }
      }
    }
}

void
gt_pch_n_P9tree_nodeP9tree_node12splay_tree_s (void *x_p)
{
  struct splay_tree_s * const x = (struct splay_tree_s *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_P9tree_nodeP9tree_node12splay_tree_s))
    {
      gt_pch_n_P9tree_nodeP9tree_node17splay_tree_node_s ((*x).root);
    }
}

void
gt_pch_n_P15tm_restart_node4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_P15tm_restart_node4htab))
    {
      {
        size_t l0 = (size_t)(((*x)).size);
        if ((*x).entries != NULL) {
          size_t i0;
          for (i0 = 0; i0 != (size_t)(l0); i0++) {
            gt_pch_n_15tm_restart_node ((*x).entries[i0]);
          }
          gt_pch_note_object ((*x).entries, x, gt_pch_p_P15tm_restart_node4htab);
        }
      }
    }
}

void
gt_pch_n_P12tree_int_map4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_P12tree_int_map4htab))
    {
      {
        size_t l0 = (size_t)(((*x)).size);
        if ((*x).entries != NULL) {
          size_t i0;
          for (i0 = 0; i0 != (size_t)(l0); i0++) {
            gt_pch_n_12tree_int_map ((*x).entries[i0]);
          }
          gt_pch_note_object ((*x).entries, x, gt_pch_p_P12tree_int_map4htab);
        }
      }
    }
}

void
gt_pch_n_P8tree_map4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_P8tree_map4htab))
    {
      {
        size_t l0 = (size_t)(((*x)).size);
        if ((*x).entries != NULL) {
          size_t i0;
          for (i0 = 0; i0 != (size_t)(l0); i0++) {
            gt_pch_n_8tree_map ((*x).entries[i0]);
          }
          gt_pch_note_object ((*x).entries, x, gt_pch_p_P8tree_map4htab);
        }
      }
    }
}

void
gt_pch_n_P24constant_descriptor_tree4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_P24constant_descriptor_tree4htab))
    {
      {
        size_t l0 = (size_t)(((*x)).size);
        if ((*x).entries != NULL) {
          size_t i0;
          for (i0 = 0; i0 != (size_t)(l0); i0++) {
            gt_pch_n_24constant_descriptor_tree ((*x).entries[i0]);
          }
          gt_pch_note_object ((*x).entries, x, gt_pch_p_P24constant_descriptor_tree4htab);
        }
      }
    }
}

void
gt_pch_n_P12object_block4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_P12object_block4htab))
    {
      {
        size_t l0 = (size_t)(((*x)).size);
        if ((*x).entries != NULL) {
          size_t i0;
          for (i0 = 0; i0 != (size_t)(l0); i0++) {
            gt_pch_n_12object_block ((*x).entries[i0]);
          }
          gt_pch_note_object ((*x).entries, x, gt_pch_p_P12object_block4htab);
        }
      }
    }
}

void
gt_pch_n_P7section4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_P7section4htab))
    {
      {
        size_t l0 = (size_t)(((*x)).size);
        if ((*x).entries != NULL) {
          size_t i0;
          for (i0 = 0; i0 != (size_t)(l0); i0++) {
            gt_pch_n_7section ((*x).entries[i0]);
          }
          gt_pch_note_object ((*x).entries, x, gt_pch_p_P7section4htab);
        }
      }
    }
}

void
gt_pch_n_P17tree_priority_map4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_P17tree_priority_map4htab))
    {
      {
        size_t l0 = (size_t)(((*x)).size);
        if ((*x).entries != NULL) {
          size_t i0;
          for (i0 = 0; i0 != (size_t)(l0); i0++) {
            gt_pch_n_17tree_priority_map ((*x).entries[i0]);
          }
          gt_pch_note_object ((*x).entries, x, gt_pch_p_P17tree_priority_map4htab);
        }
      }
    }
}

void
gt_pch_n_P12tree_vec_map4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_P12tree_vec_map4htab))
    {
      {
        size_t l0 = (size_t)(((*x)).size);
        if ((*x).entries != NULL) {
          size_t i0;
          for (i0 = 0; i0 != (size_t)(l0); i0++) {
            gt_pch_n_12tree_vec_map ((*x).entries[i0]);
          }
          gt_pch_note_object ((*x).entries, x, gt_pch_p_P12tree_vec_map4htab);
        }
      }
    }
}

void
gt_pch_n_P13tree_decl_map4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_P13tree_decl_map4htab))
    {
      {
        size_t l0 = (size_t)(((*x)).size);
        if ((*x).entries != NULL) {
          size_t i0;
          for (i0 = 0; i0 != (size_t)(l0); i0++) {
            gt_pch_n_13tree_decl_map ((*x).entries[i0]);
          }
          gt_pch_note_object ((*x).entries, x, gt_pch_p_P13tree_decl_map4htab);
        }
      }
    }
}

void
gt_pch_n_P15throw_stmt_node4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_P15throw_stmt_node4htab))
    {
      {
        size_t l0 = (size_t)(((*x)).size);
        if ((*x).entries != NULL) {
          size_t i0;
          for (i0 = 0; i0 != (size_t)(l0); i0++) {
            gt_pch_n_15throw_stmt_node ((*x).entries[i0]);
          }
          gt_pch_note_object ((*x).entries, x, gt_pch_p_P15throw_stmt_node4htab);
        }
      }
    }
}

void
gt_pch_n_P9reg_attrs4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_P9reg_attrs4htab))
    {
      {
        size_t l0 = (size_t)(((*x)).size);
        if ((*x).entries != NULL) {
          size_t i0;
          for (i0 = 0; i0 != (size_t)(l0); i0++) {
            gt_pch_n_9reg_attrs ((*x).entries[i0]);
          }
          gt_pch_note_object ((*x).entries, x, gt_pch_p_P9reg_attrs4htab);
        }
      }
    }
}

void
gt_pch_n_P9mem_attrs4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_P9mem_attrs4htab))
    {
      {
        size_t l0 = (size_t)(((*x)).size);
        if ((*x).entries != NULL) {
          size_t i0;
          for (i0 = 0; i0 != (size_t)(l0); i0++) {
            gt_pch_n_9mem_attrs ((*x).entries[i0]);
          }
          gt_pch_note_object ((*x).entries, x, gt_pch_p_P9mem_attrs4htab);
        }
      }
    }
}

void
gt_pch_n_P7rtx_def4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_P7rtx_def4htab))
    {
      {
        size_t l0 = (size_t)(((*x)).size);
        if ((*x).entries != NULL) {
          size_t i0;
          for (i0 = 0; i0 != (size_t)(l0); i0++) {
            gt_pch_n_7rtx_def ((*x).entries[i0]);
          }
          gt_pch_note_object ((*x).entries, x, gt_pch_p_P7rtx_def4htab);
        }
      }
    }
}

void
gt_pch_n_SP9tree_node12splay_tree_s (void *x_p)
{
  struct splay_tree_s * const x = (struct splay_tree_s *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_SP9tree_node12splay_tree_s))
    {
      gt_pch_n_SP9tree_node17splay_tree_node_s ((*x).root);
    }
}

void
gt_pch_n_II12splay_tree_s (void *x_p)
{
  struct splay_tree_s * const x = (struct splay_tree_s *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_II12splay_tree_s))
    {
      gt_pch_n_II17splay_tree_node_s ((*x).root);
    }
}

void
gt_pch_n_P15symtab_node_def4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_P15symtab_node_def4htab))
    {
      {
        size_t l0 = (size_t)(((*x)).size);
        if ((*x).entries != NULL) {
          size_t i0;
          for (i0 = 0; i0 != (size_t)(l0); i0++) {
            gt_pch_n_15symtab_node_def ((*x).entries[i0]);
          }
          gt_pch_note_object ((*x).entries, x, gt_pch_p_P15symtab_node_def4htab);
        }
      }
    }
}

void
gt_pch_n_P11cgraph_edge4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_P11cgraph_edge4htab))
    {
      {
        size_t l0 = (size_t)(((*x)).size);
        if ((*x).entries != NULL) {
          size_t i0;
          for (i0 = 0; i0 != (size_t)(l0); i0++) {
            gt_pch_n_11cgraph_edge ((*x).entries[i0]);
          }
          gt_pch_note_object ((*x).entries, x, gt_pch_p_P11cgraph_edge4htab);
        }
      }
    }
}

void
gt_pch_n_P9loop_exit4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_P9loop_exit4htab))
    {
      {
        size_t l0 = (size_t)(((*x)).size);
        if ((*x).entries != NULL) {
          size_t i0;
          for (i0 = 0; i0 != (size_t)(l0); i0++) {
            gt_pch_n_9loop_exit ((*x).entries[i0]);
          }
          gt_pch_note_object ((*x).entries, x, gt_pch_p_P9loop_exit4htab);
        }
      }
    }
}

void
gt_pch_n_P24types_used_by_vars_entry4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_P24types_used_by_vars_entry4htab))
    {
      {
        size_t l0 = (size_t)(((*x)).size);
        if ((*x).entries != NULL) {
          size_t i0;
          for (i0 = 0; i0 != (size_t)(l0); i0++) {
            gt_pch_n_24types_used_by_vars_entry ((*x).entries[i0]);
          }
          gt_pch_note_object ((*x).entries, x, gt_pch_p_P24types_used_by_vars_entry4htab);
        }
      }
    }
}

void
gt_pch_n_P9tree_node4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_P9tree_node4htab))
    {
      {
        size_t l0 = (size_t)(((*x)).size);
        if ((*x).entries != NULL) {
          size_t i0;
          for (i0 = 0; i0 != (size_t)(l0); i0++) {
            gt_pch_n_9tree_node ((*x).entries[i0]);
          }
          gt_pch_note_object ((*x).entries, x, gt_pch_p_P9tree_node4htab);
        }
      }
    }
}

void
gt_pch_n_P13libfunc_entry4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_P13libfunc_entry4htab))
    {
      {
        size_t l0 = (size_t)(((*x)).size);
        if ((*x).entries != NULL) {
          size_t i0;
          for (i0 = 0; i0 != (size_t)(l0); i0++) {
            gt_pch_n_13libfunc_entry ((*x).entries[i0]);
          }
          gt_pch_note_object ((*x).entries, x, gt_pch_p_P13libfunc_entry4htab);
        }
      }
    }
}

void
gt_pch_p_27vec_inline_summary_t_va_gc_ (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct vec<inline_summary_t,va_gc> * x ATTRIBUTE_UNUSED = (struct vec<inline_summary_t,va_gc> *)x_p;
  if ((void *)(x) == this_obj)
    gt_pch_nx (&((*x)), op, cookie);
}

void
gt_pch_nx (struct inline_summary* x ATTRIBUTE_UNUSED,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
    op (&((*x).conds), cookie);
    op (&((*x).entry), cookie);
}

void
gt_pch_p_26vec_size_time_entry_va_gc_ (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct vec<size_time_entry,va_gc> * x ATTRIBUTE_UNUSED = (struct vec<size_time_entry,va_gc> *)x_p;
  if ((void *)(x) == this_obj)
    gt_pch_nx (&((*x)), op, cookie);
}

void
gt_pch_nx (struct size_time_entry* x ATTRIBUTE_UNUSED,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
}

void
gt_pch_p_20vec_condition_va_gc_ (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct vec<condition,va_gc> * x ATTRIBUTE_UNUSED = (struct vec<condition,va_gc> *)x_p;
  if ((void *)(x) == this_obj)
    gt_pch_nx (&((*x)), op, cookie);
}

void
gt_pch_nx (struct condition* x ATTRIBUTE_UNUSED,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
    op (&((*x).val), cookie);
}

void
gt_pch_p_17lto_in_decl_state (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct lto_in_decl_state * x ATTRIBUTE_UNUSED = (struct lto_in_decl_state *)x_p;
  {
    size_t i0;
    size_t l0 = (size_t)(LTO_N_DECL_STREAMS);
    for (i0 = 0; i0 != l0; i0++) {
      {
        size_t l1 = (size_t)(((*x).streams[i0]).size);
        if ((*x).streams[i0].trees != NULL) {
          size_t i1;
          for (i1 = 0; i1 != (size_t)(l1) && ((void *)(*x).streams[i0].trees == this_obj); i1++) {
            if ((void *)((*x).streams[i0].trees) == this_obj)
              op (&((*x).streams[i0].trees[i1]), cookie);
          }
          if ((void *)(x) == this_obj)
            op (&((*x).streams[i0].trees), cookie);
        }
      }
    }
  }
  if ((void *)(x) == this_obj)
    op (&((*x).fn_decl), cookie);
}

void
gt_pch_p_26vec_ipa_edge_args_t_va_gc_ (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct vec<ipa_edge_args_t,va_gc> * x ATTRIBUTE_UNUSED = (struct vec<ipa_edge_args_t,va_gc> *)x_p;
  if ((void *)(x) == this_obj)
    gt_pch_nx (&((*x)), op, cookie);
}

void
gt_pch_nx (struct ipa_edge_args* x ATTRIBUTE_UNUSED,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
    op (&((*x).jump_functions), cookie);
}

void
gt_pch_p_38vec_ipa_agg_replacement_value_p_va_gc_ (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct vec<ipa_agg_replacement_value_p,va_gc> * x ATTRIBUTE_UNUSED = (struct vec<ipa_agg_replacement_value_p,va_gc> *)x_p;
  if ((void *)(x) == this_obj)
    gt_pch_nx (&((*x)), op, cookie);
}

void
gt_pch_p_26vec_ipa_jump_func_t_va_gc_ (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct vec<ipa_jump_func_t,va_gc> * x ATTRIBUTE_UNUSED = (struct vec<ipa_jump_func_t,va_gc> *)x_p;
  if ((void *)(x) == this_obj)
    gt_pch_nx (&((*x)), op, cookie);
}

void
gt_pch_nx (struct ipa_jump_func* x ATTRIBUTE_UNUSED,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
    op (&((*x).agg.items), cookie);
  switch (((*x)).type)
    {
    case IPA_JF_KNOWN_TYPE:
        op (&((*x).value.known_type.base_type), cookie);
        op (&((*x).value.known_type.component_type), cookie);
      break;
    case IPA_JF_CONST:
        op (&((*x).value.constant), cookie);
      break;
    case IPA_JF_PASS_THROUGH:
        op (&((*x).value.pass_through.operand), cookie);
      break;
    case IPA_JF_ANCESTOR:
        op (&((*x).value.ancestor.type), cookie);
      break;
    default:
      break;
    }
}

void
gt_pch_p_28vec_ipa_agg_jf_item_t_va_gc_ (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct vec<ipa_agg_jf_item_t,va_gc> * x ATTRIBUTE_UNUSED = (struct vec<ipa_agg_jf_item_t,va_gc> *)x_p;
  if ((void *)(x) == this_obj)
    gt_pch_nx (&((*x)), op, cookie);
}

void
gt_pch_nx (struct ipa_agg_jf_item* x ATTRIBUTE_UNUSED,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
    op (&((*x).value), cookie);
}

void
gt_pch_p_20ssa_operand_memory_d (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct ssa_operand_memory_d * x ATTRIBUTE_UNUSED = (struct ssa_operand_memory_d *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).next), cookie);
}

void
gt_pch_p_17vec_gimple_va_gc_ (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct vec<gimple,va_gc> * x ATTRIBUTE_UNUSED = (struct vec<gimple,va_gc> *)x_p;
  if ((void *)(x) == this_obj)
    gt_pch_nx (&((*x)), op, cookie);
}

void
gt_pch_p_15tm_restart_node (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct tm_restart_node * x ATTRIBUTE_UNUSED = (struct tm_restart_node *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).stmt), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).label_or_list), cookie);
}

void
gt_pch_p_15throw_stmt_node (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct throw_stmt_node * x ATTRIBUTE_UNUSED = (struct throw_stmt_node *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).stmt), cookie);
}

void
gt_pch_p_25vec_eh_landing_pad_va_gc_ (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct vec<eh_landing_pad,va_gc> * x ATTRIBUTE_UNUSED = (struct vec<eh_landing_pad,va_gc> *)x_p;
  if ((void *)(x) == this_obj)
    gt_pch_nx (&((*x)), op, cookie);
}

void
gt_pch_p_20vec_eh_region_va_gc_ (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct vec<eh_region,va_gc> * x ATTRIBUTE_UNUSED = (struct vec<eh_region,va_gc> *)x_p;
  if ((void *)(x) == this_obj)
    gt_pch_nx (&((*x)), op, cookie);
}

void
gt_pch_p_10eh_catch_d (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct eh_catch_d * x ATTRIBUTE_UNUSED = (struct eh_catch_d *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).next_catch), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).prev_catch), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).type_list), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).filter_list), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).label), cookie);
}

void
gt_pch_p_16eh_landing_pad_d (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct eh_landing_pad_d * x ATTRIBUTE_UNUSED = (struct eh_landing_pad_d *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).next_lp), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).region), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).post_landing_pad), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).landing_pad), cookie);
}

void
gt_pch_p_11eh_region_d (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct eh_region_d * x ATTRIBUTE_UNUSED = (struct eh_region_d *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).outer), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).inner), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).next_peer), cookie);
  switch ((*x).type)
    {
    case ERT_TRY:
      if ((void *)(x) == this_obj)
        op (&((*x).u.eh_try.first_catch), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.eh_try.last_catch), cookie);
      break;
    case ERT_ALLOWED_EXCEPTIONS:
      if ((void *)(x) == this_obj)
        op (&((*x).u.allowed.type_list), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.allowed.label), cookie);
      break;
    case ERT_MUST_NOT_THROW:
      if ((void *)(x) == this_obj)
        op (&((*x).u.must_not_throw.failure_decl), cookie);
      break;
    default:
      break;
    }
  if ((void *)(x) == this_obj)
    op (&((*x).landing_pads), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).exc_ptr_reg), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).filter_reg), cookie);
}

void
gt_pch_p_21vec_dw_cfi_ref_va_gc_ (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct vec<dw_cfi_ref,va_gc> * x ATTRIBUTE_UNUSED = (struct vec<dw_cfi_ref,va_gc> *)x_p;
  if ((void *)(x) == this_obj)
    gt_pch_nx (&((*x)), op, cookie);
}

void
gt_pch_p_19dw_loc_descr_struct (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct dw_loc_descr_struct * x ATTRIBUTE_UNUSED = (struct dw_loc_descr_struct *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).dw_loc_next), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).dw_loc_oprnd1.val_entry), cookie);
  switch (((*x).dw_loc_oprnd1).val_class)
    {
    case dw_val_class_addr:
      if ((void *)(x) == this_obj)
        op (&((*x).dw_loc_oprnd1.v.val_addr), cookie);
      break;
    case dw_val_class_offset:
      break;
    case dw_val_class_loc_list:
      if ((void *)(x) == this_obj)
        op (&((*x).dw_loc_oprnd1.v.val_loc_list), cookie);
      break;
    case dw_val_class_loc:
      if ((void *)(x) == this_obj)
        op (&((*x).dw_loc_oprnd1.v.val_loc), cookie);
      break;
    default:
      break;
    case dw_val_class_unsigned_const:
      break;
    case dw_val_class_const_double:
      break;
    case dw_val_class_vec:
      if ((void *)(x) == this_obj)
        op (&((*x).dw_loc_oprnd1.v.val_vec.array), cookie);
      break;
    case dw_val_class_die_ref:
      if ((void *)(x) == this_obj)
        op (&((*x).dw_loc_oprnd1.v.val_die_ref.die), cookie);
      break;
    case dw_val_class_fde_ref:
      break;
    case dw_val_class_str:
      if ((void *)(x) == this_obj)
        op (&((*x).dw_loc_oprnd1.v.val_str), cookie);
      break;
    case dw_val_class_lbl_id:
      if ((void *)(x) == this_obj)
        op (&((*x).dw_loc_oprnd1.v.val_lbl_id), cookie);
      break;
    case dw_val_class_flag:
      break;
    case dw_val_class_file:
      if ((void *)(x) == this_obj)
        op (&((*x).dw_loc_oprnd1.v.val_file), cookie);
      break;
    case dw_val_class_data8:
      break;
    case dw_val_class_decl_ref:
      if ((void *)(x) == this_obj)
        op (&((*x).dw_loc_oprnd1.v.val_decl_ref), cookie);
      break;
    case dw_val_class_vms_delta:
      if ((void *)(x) == this_obj)
        op (&((*x).dw_loc_oprnd1.v.val_vms_delta.lbl1), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).dw_loc_oprnd1.v.val_vms_delta.lbl2), cookie);
      break;
    }
  if ((void *)(x) == this_obj)
    op (&((*x).dw_loc_oprnd2.val_entry), cookie);
  switch (((*x).dw_loc_oprnd2).val_class)
    {
    case dw_val_class_addr:
      if ((void *)(x) == this_obj)
        op (&((*x).dw_loc_oprnd2.v.val_addr), cookie);
      break;
    case dw_val_class_offset:
      break;
    case dw_val_class_loc_list:
      if ((void *)(x) == this_obj)
        op (&((*x).dw_loc_oprnd2.v.val_loc_list), cookie);
      break;
    case dw_val_class_loc:
      if ((void *)(x) == this_obj)
        op (&((*x).dw_loc_oprnd2.v.val_loc), cookie);
      break;
    default:
      break;
    case dw_val_class_unsigned_const:
      break;
    case dw_val_class_const_double:
      break;
    case dw_val_class_vec:
      if ((void *)(x) == this_obj)
        op (&((*x).dw_loc_oprnd2.v.val_vec.array), cookie);
      break;
    case dw_val_class_die_ref:
      if ((void *)(x) == this_obj)
        op (&((*x).dw_loc_oprnd2.v.val_die_ref.die), cookie);
      break;
    case dw_val_class_fde_ref:
      break;
    case dw_val_class_str:
      if ((void *)(x) == this_obj)
        op (&((*x).dw_loc_oprnd2.v.val_str), cookie);
      break;
    case dw_val_class_lbl_id:
      if ((void *)(x) == this_obj)
        op (&((*x).dw_loc_oprnd2.v.val_lbl_id), cookie);
      break;
    case dw_val_class_flag:
      break;
    case dw_val_class_file:
      if ((void *)(x) == this_obj)
        op (&((*x).dw_loc_oprnd2.v.val_file), cookie);
      break;
    case dw_val_class_data8:
      break;
    case dw_val_class_decl_ref:
      if ((void *)(x) == this_obj)
        op (&((*x).dw_loc_oprnd2.v.val_decl_ref), cookie);
      break;
    case dw_val_class_vms_delta:
      if ((void *)(x) == this_obj)
        op (&((*x).dw_loc_oprnd2.v.val_vms_delta.lbl1), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).dw_loc_oprnd2.v.val_vms_delta.lbl2), cookie);
      break;
    }
}

void
gt_pch_p_13dw_cfi_struct (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct dw_cfi_struct * x ATTRIBUTE_UNUSED = (struct dw_cfi_struct *)x_p;
  switch (dw_cfi_oprnd1_desc (((*x)).dw_cfi_opc))
    {
    case dw_cfi_oprnd_reg_num:
      break;
    case dw_cfi_oprnd_offset:
      break;
    case dw_cfi_oprnd_addr:
      if ((void *)(x) == this_obj)
        op (&((*x).dw_cfi_oprnd1.dw_cfi_addr), cookie);
      break;
    case dw_cfi_oprnd_loc:
      if ((void *)(x) == this_obj)
        op (&((*x).dw_cfi_oprnd1.dw_cfi_loc), cookie);
      break;
    default:
      break;
    }
  switch (dw_cfi_oprnd2_desc (((*x)).dw_cfi_opc))
    {
    case dw_cfi_oprnd_reg_num:
      break;
    case dw_cfi_oprnd_offset:
      break;
    case dw_cfi_oprnd_addr:
      if ((void *)(x) == this_obj)
        op (&((*x).dw_cfi_oprnd2.dw_cfi_addr), cookie);
      break;
    case dw_cfi_oprnd_loc:
      if ((void *)(x) == this_obj)
        op (&((*x).dw_cfi_oprnd2.dw_cfi_loc), cookie);
      break;
    default:
      break;
    }
}

void
gt_pch_p_25ipa_agg_replacement_value (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct ipa_agg_replacement_value * x ATTRIBUTE_UNUSED = (struct ipa_agg_replacement_value *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).next), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).value), cookie);
}

void
gt_pch_p_24constant_descriptor_tree (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct constant_descriptor_tree * x ATTRIBUTE_UNUSED = (struct constant_descriptor_tree *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).rtl), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).value), cookie);
}

void
gt_pch_p_8asm_node (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct asm_node * x ATTRIBUTE_UNUSED = (struct asm_node *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).next), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).asm_str), cookie);
}

void
gt_pch_p_25cgraph_indirect_call_info (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct cgraph_indirect_call_info * x ATTRIBUTE_UNUSED = (struct cgraph_indirect_call_info *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).otr_type), cookie);
}

void
gt_pch_p_28cgraph_function_version_info (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct cgraph_function_version_info * x ATTRIBUTE_UNUSED = (struct cgraph_function_version_info *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).this_node), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).prev), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).next), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).dispatcher_resolver), cookie);
}

void
gt_pch_p_11cgraph_edge (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct cgraph_edge * x ATTRIBUTE_UNUSED = (struct cgraph_edge *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).caller), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).callee), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).prev_caller), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).next_caller), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).prev_callee), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).next_callee), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).call_stmt), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).indirect_info), cookie);
}

void
gt_pch_p_28vec_ipa_replace_map_p_va_gc_ (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct vec<ipa_replace_map_p,va_gc> * x ATTRIBUTE_UNUSED = (struct vec<ipa_replace_map_p,va_gc> *)x_p;
  if ((void *)(x) == this_obj)
    gt_pch_nx (&((*x)), op, cookie);
}

void
gt_pch_p_15ipa_replace_map (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct ipa_replace_map * x ATTRIBUTE_UNUSED = (struct ipa_replace_map *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).old_tree), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).new_tree), cookie);
}

void
gt_pch_p_18lto_file_decl_data (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct lto_file_decl_data * x ATTRIBUTE_UNUSED = (struct lto_file_decl_data *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).current_decl_state), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).global_decl_state), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).function_decl_states), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).next), cookie);
}

void
gt_pch_p_20vec_ipa_ref_t_va_gc_ (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct vec<ipa_ref_t,va_gc> * x ATTRIBUTE_UNUSED = (struct vec<ipa_ref_t,va_gc> *)x_p;
  if ((void *)(x) == this_obj)
    gt_pch_nx (&((*x)), op, cookie);
}

void
gt_pch_nx (struct ipa_ref* x ATTRIBUTE_UNUSED,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
    op (&((*x).referring), cookie);
    op (&((*x).referred), cookie);
    op (&((*x).stmt), cookie);
}

void
gt_pch_p_15symtab_node_def (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  union symtab_node_def * x ATTRIBUTE_UNUSED = (union symtab_node_def *)x_p;
  switch (((*x)).symbol.type)
    {
    case SYMTAB_SYMBOL:
      if ((void *)(x) == this_obj)
        op (&((*x).symbol.decl), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).symbol.ref_list.references), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).symbol.same_comdat_group), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).symbol.lto_file_data), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).symbol.next), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).symbol.previous), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).symbol.next_sharing_asm_name), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).symbol.previous_sharing_asm_name), cookie);
      break;
    case SYMTAB_FUNCTION:
      if ((void *)(x) == this_obj)
        op (&((*x).x_function.symbol.decl), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).x_function.symbol.ref_list.references), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).x_function.symbol.same_comdat_group), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).x_function.symbol.lto_file_data), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).x_function.symbol.next), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).x_function.symbol.previous), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).x_function.symbol.next_sharing_asm_name), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).x_function.symbol.previous_sharing_asm_name), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).x_function.callees), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).x_function.callers), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).x_function.indirect_calls), cookie);
      {
        union symtab_node_def * x0 =
          (symtab_node)((*x).x_function.origin);
        if ((void *)(x) == this_obj)
          op (&(x0), cookie);
        (*x).x_function.origin = (struct cgraph_node *)((x0));
      }
      {
        union symtab_node_def * x1 =
          (symtab_node)((*x).x_function.nested);
        if ((void *)(x) == this_obj)
          op (&(x1), cookie);
        (*x).x_function.nested = (struct cgraph_node *)((x1));
      }
      {
        union symtab_node_def * x2 =
          (symtab_node)((*x).x_function.next_nested);
        if ((void *)(x) == this_obj)
          op (&(x2), cookie);
        (*x).x_function.next_nested = (struct cgraph_node *)((x2));
      }
      if ((void *)(x) == this_obj)
        op (&((*x).x_function.next_sibling_clone), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).x_function.prev_sibling_clone), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).x_function.clones), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).x_function.clone_of), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).x_function.call_site_hash), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).x_function.former_clone_of), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).x_function.global.inlined_to), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).x_function.clone.tree_map), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).x_function.clone.args_to_skip), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).x_function.clone.combined_args_to_skip), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).x_function.thunk.alias), cookie);
      break;
    case SYMTAB_VARIABLE:
      if ((void *)(x) == this_obj)
        op (&((*x).x_variable.symbol.decl), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).x_variable.symbol.ref_list.references), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).x_variable.symbol.same_comdat_group), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).x_variable.symbol.lto_file_data), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).x_variable.symbol.next), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).x_variable.symbol.previous), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).x_variable.symbol.next_sharing_asm_name), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).x_variable.symbol.previous_sharing_asm_name), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).x_variable.alias_of), cookie);
      break;
    default:
      break;
    }
}

void
gt_pch_p_11cgraph_node (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct cgraph_node * x ATTRIBUTE_UNUSED = (struct cgraph_node *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).symbol.decl), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).symbol.ref_list.references), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).symbol.same_comdat_group), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).symbol.lto_file_data), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).symbol.next), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).symbol.previous), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).symbol.next_sharing_asm_name), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).symbol.previous_sharing_asm_name), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).callees), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).callers), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).indirect_calls), cookie);
  {
    union symtab_node_def * x0 =
      (symtab_node)((*x).origin);
    if ((void *)(x) == this_obj)
      op (&(x0), cookie);
    (*x).origin = (struct cgraph_node *)((x0));
  }
  {
    union symtab_node_def * x1 =
      (symtab_node)((*x).nested);
    if ((void *)(x) == this_obj)
      op (&(x1), cookie);
    (*x).nested = (struct cgraph_node *)((x1));
  }
  {
    union symtab_node_def * x2 =
      (symtab_node)((*x).next_nested);
    if ((void *)(x) == this_obj)
      op (&(x2), cookie);
    (*x).next_nested = (struct cgraph_node *)((x2));
  }
  if ((void *)(x) == this_obj)
    op (&((*x).next_sibling_clone), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).prev_sibling_clone), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).clones), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).clone_of), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).call_site_hash), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).former_clone_of), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).global.inlined_to), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).clone.tree_map), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).clone.args_to_skip), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).clone.combined_args_to_skip), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).thunk.alias), cookie);
}

void
gt_pch_p_22vec_basic_block_va_gc_ (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct vec<basic_block,va_gc> * x ATTRIBUTE_UNUSED = (struct vec<basic_block,va_gc> *)x_p;
  if ((void *)(x) == this_obj)
    gt_pch_nx (&((*x)), op, cookie);
}

void
gt_pch_p_15vec_edge_va_gc_ (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct vec<edge,va_gc> * x ATTRIBUTE_UNUSED = (struct vec<edge,va_gc> *)x_p;
  if ((void *)(x) == this_obj)
    gt_pch_nx (&((*x)), op, cookie);
}

void
gt_pch_p_11rtl_bb_info (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct rtl_bb_info * x ATTRIBUTE_UNUSED = (struct rtl_bb_info *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).end_), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).header_), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).footer_), cookie);
}

void
gt_pch_p_17vec_loop_p_va_gc_ (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct vec<loop_p,va_gc> * x ATTRIBUTE_UNUSED = (struct vec<loop_p,va_gc> *)x_p;
  if ((void *)(x) == this_obj)
    gt_pch_nx (&((*x)), op, cookie);
}

void
gt_pch_p_4loop (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct loop * x ATTRIBUTE_UNUSED = (struct loop *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).header), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).latch), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).superloops), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).inner), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).next), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).nb_iterations), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).bounds), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).exits), cookie);
}

void
gt_pch_p_9loop_exit (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct loop_exit * x ATTRIBUTE_UNUSED = (struct loop_exit *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).e), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).prev), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).next), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).next_e), cookie);
}

void
gt_pch_p_13nb_iter_bound (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct nb_iter_bound * x ATTRIBUTE_UNUSED = (struct nb_iter_bound *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).stmt), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).next), cookie);
}

void
gt_pch_p_24types_used_by_vars_entry (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct types_used_by_vars_entry * x ATTRIBUTE_UNUSED = (struct types_used_by_vars_entry *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).type), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).var_decl), cookie);
}

void
gt_pch_p_5loops (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct loops * x ATTRIBUTE_UNUSED = (struct loops *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).larray), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).exits), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).tree_root), cookie);
}

void
gt_pch_p_18control_flow_graph (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct control_flow_graph * x ATTRIBUTE_UNUSED = (struct control_flow_graph *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).x_entry_block_ptr), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).x_exit_block_ptr), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).x_basic_block_info), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).x_label_to_block_map), cookie);
}

void
gt_pch_p_9eh_status (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct eh_status * x ATTRIBUTE_UNUSED = (struct eh_status *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).region_tree), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).region_array), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).lp_array), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).throw_stmt_table), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).ttype_data), cookie);
  switch (targetm.arm_eabi_unwinder)
    {
    case 1:
      if ((void *)(x) == this_obj)
        op (&((*x).ehspec_data.arm_eabi), cookie);
      break;
    case 0:
      if ((void *)(x) == this_obj)
        op (&((*x).ehspec_data.other), cookie);
      break;
    default:
      break;
    }
}

void
gt_pch_p_11stack_usage (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct stack_usage * x ATTRIBUTE_UNUSED = (struct stack_usage *)x_p;
}

void
gt_pch_p_22vec_temp_slot_p_va_gc_ (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct vec<temp_slot_p,va_gc> * x ATTRIBUTE_UNUSED = (struct vec<temp_slot_p,va_gc> *)x_p;
  if ((void *)(x) == this_obj)
    gt_pch_nx (&((*x)), op, cookie);
}

void
gt_pch_p_11frame_space (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct frame_space * x ATTRIBUTE_UNUSED = (struct frame_space *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).next), cookie);
}

void
gt_pch_p_13dw_fde_struct (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct dw_fde_struct * x ATTRIBUTE_UNUSED = (struct dw_fde_struct *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).decl), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).dw_fde_begin), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).dw_fde_current_label), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).dw_fde_end), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).dw_fde_vms_end_prologue), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).dw_fde_vms_begin_epilogue), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).dw_fde_second_begin), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).dw_fde_second_end), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).dw_fde_cfi), cookie);
}

void
gt_pch_p_9gimple_df (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct gimple_df * x ATTRIBUTE_UNUSED = (struct gimple_df *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).modified_noreturn_calls), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).ssa_names), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).vop), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).escaped.vars), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).free_ssanames), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).default_defs), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).ssa_operands.operand_memory), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).tm_restart), cookie);
}

void
gt_pch_p_27vec_call_site_record_va_gc_ (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct vec<call_site_record,va_gc> * x ATTRIBUTE_UNUSED = (struct vec<call_site_record,va_gc> *)x_p;
  if ((void *)(x) == this_obj)
    gt_pch_nx (&((*x)), op, cookie);
}

void
gt_pch_p_16vec_uchar_va_gc_ (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct vec<uchar,va_gc> * x ATTRIBUTE_UNUSED = (struct vec<uchar,va_gc> *)x_p;
  if ((void *)(x) == this_obj)
    gt_pch_nx (&((*x)), op, cookie);
}

void
gt_pch_p_14sequence_stack (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct sequence_stack * x ATTRIBUTE_UNUSED = (struct sequence_stack *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).first), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).last), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).next), cookie);
}

void
gt_pch_p_13libfunc_entry (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct libfunc_entry * x ATTRIBUTE_UNUSED = (struct libfunc_entry *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).libfunc), cookie);
}

void
gt_pch_p_12tree_vec_map (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct tree_vec_map * x ATTRIBUTE_UNUSED = (struct tree_vec_map *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).base.from), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).to), cookie);
}

void
gt_pch_p_17tree_priority_map (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct tree_priority_map * x ATTRIBUTE_UNUSED = (struct tree_priority_map *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).base.from), cookie);
}

void
gt_pch_p_12tree_int_map (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct tree_int_map * x ATTRIBUTE_UNUSED = (struct tree_int_map *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).base.from), cookie);
}

void
gt_pch_p_13tree_decl_map (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct tree_decl_map * x ATTRIBUTE_UNUSED = (struct tree_decl_map *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).base.from), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).to), cookie);
}

void
gt_pch_p_8tree_map (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct tree_map * x ATTRIBUTE_UNUSED = (struct tree_map *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).base.from), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).to), cookie);
}

void
gt_pch_p_24tree_statement_list_node (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct tree_statement_list_node * x ATTRIBUTE_UNUSED = (struct tree_statement_list_node *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).prev), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).next), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).stmt), cookie);
}

void
gt_pch_p_15vec_tree_va_gc_ (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct vec<tree,va_gc> * x ATTRIBUTE_UNUSED = (struct vec<tree,va_gc> *)x_p;
  if ((void *)(x) == this_obj)
    gt_pch_nx (&((*x)), op, cookie);
}

void
gt_pch_p_12ptr_info_def (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct ptr_info_def * x ATTRIBUTE_UNUSED = (struct ptr_info_def *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).pt.vars), cookie);
}

void
gt_pch_p_26vec_constructor_elt_va_gc_ (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct vec<constructor_elt,va_gc> * x ATTRIBUTE_UNUSED = (struct vec<constructor_elt,va_gc> *)x_p;
  if ((void *)(x) == this_obj)
    gt_pch_nx (&((*x)), op, cookie);
}

void
gt_pch_nx (struct constructor_elt_d* x ATTRIBUTE_UNUSED,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
    op (&((*x).index), cookie);
    op (&((*x).value), cookie);
}

void
gt_pch_p_21vec_alias_pair_va_gc_ (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct vec<alias_pair,va_gc> * x ATTRIBUTE_UNUSED = (struct vec<alias_pair,va_gc> *)x_p;
  if ((void *)(x) == this_obj)
    gt_pch_nx (&((*x)), op, cookie);
}

void
gt_pch_nx (struct alias_pair* x ATTRIBUTE_UNUSED,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
    op (&((*x).decl), cookie);
    op (&((*x).target), cookie);
}

void
gt_pch_p_8function (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct function * x ATTRIBUTE_UNUSED = (struct function *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).eh), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).cfg), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).gimple_body), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).gimple_df), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).x_current_loops), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).su), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).decl), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).static_chain_decl), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).nonlocal_goto_save_area), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).local_decls), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).machine), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).language), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).used_types_hash), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).fde), cookie);
}

void
gt_pch_p_11fixed_value (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct fixed_value * x ATTRIBUTE_UNUSED = (struct fixed_value *)x_p;
}

void
gt_pch_p_10real_value (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct real_value * x ATTRIBUTE_UNUSED = (struct real_value *)x_p;
}

void
gt_pch_p_14vec_rtx_va_gc_ (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct vec<rtx,va_gc> * x ATTRIBUTE_UNUSED = (struct vec<rtx,va_gc> *)x_p;
  if ((void *)(x) == this_obj)
    gt_pch_nx (&((*x)), op, cookie);
}

void
gt_pch_p_12object_block (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct object_block * x ATTRIBUTE_UNUSED = (struct object_block *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).sect), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).objects), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).anchors), cookie);
}

void
gt_pch_p_9reg_attrs (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct reg_attrs * x ATTRIBUTE_UNUSED = (struct reg_attrs *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).decl), cookie);
}

void
gt_pch_p_9mem_attrs (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct mem_attrs * x ATTRIBUTE_UNUSED = (struct mem_attrs *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).expr), cookie);
}

void
gt_pch_p_14bitmap_obstack (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct bitmap_obstack * x ATTRIBUTE_UNUSED = (struct bitmap_obstack *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).elements), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).heads), cookie);
}

void
gt_pch_p_18bitmap_element_def (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct bitmap_element_def * x ATTRIBUTE_UNUSED = (struct bitmap_element_def *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).next), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).prev), cookie);
}

void
gt_pch_p_16machine_function (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct machine_function * x ATTRIBUTE_UNUSED = (struct machine_function *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).stack_locals), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).some_ld_name), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).split_stack_varargs_pointer), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).fs.cfa_reg), cookie);
}

void
gt_pch_p_15basic_block_def (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct basic_block_def * x ATTRIBUTE_UNUSED = (struct basic_block_def *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).preds), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).succs), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).loop_father), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).prev_bb), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).next_bb), cookie);
  switch (((((*x)).flags & BB_RTL) != 0))
    {
    case 0:
      if ((void *)(x) == this_obj)
        op (&((*x).il.gimple.seq), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).il.gimple.phi_nodes), cookie);
      break;
    case 1:
      if ((void *)(x) == this_obj)
        op (&((*x).il.x.head_), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).il.x.rtl), cookie);
      break;
    default:
      break;
    }
}

void
gt_pch_p_8edge_def (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct edge_def * x ATTRIBUTE_UNUSED = (struct edge_def *)x_p;
}

void
gt_pch_p_7section (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  union section * x ATTRIBUTE_UNUSED = (union section *)x_p;
  switch (SECTION_STYLE (&(((*x)))))
    {
    case SECTION_NAMED:
      if ((void *)(x) == this_obj)
        op (&((*x).named.name), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).named.decl), cookie);
      break;
    case SECTION_UNNAMED:
      if ((void *)(x) == this_obj)
        op (&((*x).unnamed.next), cookie);
      break;
    case SECTION_NOSWITCH:
      break;
    default:
      break;
    }
}

void
gt_pch_p_18gimple_statement_d (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  union gimple_statement_d * x ATTRIBUTE_UNUSED = (union gimple_statement_d *)x_p;
  switch (gimple_statement_structure (&((*x))))
    {
    case GSS_BASE:
      if ((void *)(x) == this_obj)
        op (&((*x).gsbase.bb), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gsbase.next), cookie);
      break;
    case GSS_WITH_OPS:
      {
        size_t l0 = (size_t)(((*x).gsops).opbase.gsbase.num_ops);
        if ((void *)(x) == this_obj)
          op (&((*x).gsops.opbase.gsbase.bb), cookie);
        if ((void *)(x) == this_obj)
          op (&((*x).gsops.opbase.gsbase.next), cookie);
        {
          size_t i0;
          for (i0 = 0; i0 != l0; i0++) {
            if ((void *)(x) == this_obj)
              op (&((*x).gsops.op[i0]), cookie);
          }
        }
      }
      break;
    case GSS_WITH_MEM_OPS_BASE:
      if ((void *)(x) == this_obj)
        op (&((*x).gsmembase.opbase.gsbase.bb), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gsmembase.opbase.gsbase.next), cookie);
      break;
    case GSS_WITH_MEM_OPS:
      {
        size_t l1 = (size_t)(((*x).gsmem).membase.opbase.gsbase.num_ops);
        if ((void *)(x) == this_obj)
          op (&((*x).gsmem.membase.opbase.gsbase.bb), cookie);
        if ((void *)(x) == this_obj)
          op (&((*x).gsmem.membase.opbase.gsbase.next), cookie);
        {
          size_t i1;
          for (i1 = 0; i1 != l1; i1++) {
            if ((void *)(x) == this_obj)
              op (&((*x).gsmem.op[i1]), cookie);
          }
        }
      }
      break;
    case GSS_CALL:
      {
        size_t l2 = (size_t)(((*x).gimple_call).membase.opbase.gsbase.num_ops);
        if ((void *)(x) == this_obj)
          op (&((*x).gimple_call.membase.opbase.gsbase.bb), cookie);
        if ((void *)(x) == this_obj)
          op (&((*x).gimple_call.membase.opbase.gsbase.next), cookie);
        if ((void *)(x) == this_obj)
          op (&((*x).gimple_call.call_used.vars), cookie);
        if ((void *)(x) == this_obj)
          op (&((*x).gimple_call.call_clobbered.vars), cookie);
        switch (((*x).gimple_call).membase.opbase.gsbase.subcode & GF_CALL_INTERNAL)
          {
          case 0:
            if ((void *)(x) == this_obj)
              op (&((*x).gimple_call.u.fntype), cookie);
            break;
          case GF_CALL_INTERNAL:
            break;
          default:
            break;
          }
        {
          size_t i2;
          for (i2 = 0; i2 != l2; i2++) {
            if ((void *)(x) == this_obj)
              op (&((*x).gimple_call.op[i2]), cookie);
          }
        }
      }
      break;
    case GSS_OMP:
      if ((void *)(x) == this_obj)
        op (&((*x).omp.gsbase.bb), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).omp.gsbase.next), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).omp.body), cookie);
      break;
    case GSS_BIND:
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_bind.gsbase.bb), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_bind.gsbase.next), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_bind.vars), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_bind.block), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_bind.body), cookie);
      break;
    case GSS_CATCH:
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_catch.gsbase.bb), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_catch.gsbase.next), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_catch.types), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_catch.handler), cookie);
      break;
    case GSS_EH_FILTER:
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_eh_filter.gsbase.bb), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_eh_filter.gsbase.next), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_eh_filter.types), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_eh_filter.failure), cookie);
      break;
    case GSS_EH_MNT:
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_eh_mnt.gsbase.bb), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_eh_mnt.gsbase.next), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_eh_mnt.fndecl), cookie);
      break;
    case GSS_EH_ELSE:
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_eh_else.gsbase.bb), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_eh_else.gsbase.next), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_eh_else.n_body), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_eh_else.e_body), cookie);
      break;
    case GSS_PHI:
      {
        size_t l3 = (size_t)(((*x).gimple_phi).nargs);
        if ((void *)(x) == this_obj)
          op (&((*x).gimple_phi.gsbase.bb), cookie);
        if ((void *)(x) == this_obj)
          op (&((*x).gimple_phi.gsbase.next), cookie);
        if ((void *)(x) == this_obj)
          op (&((*x).gimple_phi.result), cookie);
        {
          size_t i3;
          for (i3 = 0; i3 != l3; i3++) {
            if ((void *)(x) == this_obj)
              op (&((*x).gimple_phi.args[i3].def), cookie);
          }
        }
      }
      break;
    case GSS_EH_CTRL:
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_eh_ctrl.gsbase.bb), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_eh_ctrl.gsbase.next), cookie);
      break;
    case GSS_TRY:
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_try.gsbase.bb), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_try.gsbase.next), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_try.eval), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_try.cleanup), cookie);
      break;
    case GSS_WCE:
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_wce.gsbase.bb), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_wce.gsbase.next), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_wce.cleanup), cookie);
      break;
    case GSS_ASM:
      {
        size_t l4 = (size_t)(((*x).gimple_asm).membase.opbase.gsbase.num_ops);
        if ((void *)(x) == this_obj)
          op (&((*x).gimple_asm.membase.opbase.gsbase.bb), cookie);
        if ((void *)(x) == this_obj)
          op (&((*x).gimple_asm.membase.opbase.gsbase.next), cookie);
        if ((void *)(x) == this_obj)
          op (&((*x).gimple_asm.string), cookie);
        {
          size_t i4;
          for (i4 = 0; i4 != l4; i4++) {
            if ((void *)(x) == this_obj)
              op (&((*x).gimple_asm.op[i4]), cookie);
          }
        }
      }
      break;
    case GSS_OMP_CRITICAL:
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_critical.omp.gsbase.bb), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_critical.omp.gsbase.next), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_critical.omp.body), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_critical.name), cookie);
      break;
    case GSS_OMP_FOR:
      {
        size_t l5 = (size_t)(((*x).gimple_omp_for).collapse);
        if ((void *)(x) == this_obj)
          op (&((*x).gimple_omp_for.omp.gsbase.bb), cookie);
        if ((void *)(x) == this_obj)
          op (&((*x).gimple_omp_for.omp.gsbase.next), cookie);
        if ((void *)(x) == this_obj)
          op (&((*x).gimple_omp_for.omp.body), cookie);
        if ((void *)(x) == this_obj)
          op (&((*x).gimple_omp_for.clauses), cookie);
        if ((*x).gimple_omp_for.iter != NULL) {
          size_t i5;
          for (i5 = 0; i5 != (size_t)(l5) && ((void *)(*x).gimple_omp_for.iter == this_obj); i5++) {
            if ((void *)((*x).gimple_omp_for.iter) == this_obj)
              op (&((*x).gimple_omp_for.iter[i5].index), cookie);
            if ((void *)((*x).gimple_omp_for.iter) == this_obj)
              op (&((*x).gimple_omp_for.iter[i5].initial), cookie);
            if ((void *)((*x).gimple_omp_for.iter) == this_obj)
              op (&((*x).gimple_omp_for.iter[i5].final), cookie);
            if ((void *)((*x).gimple_omp_for.iter) == this_obj)
              op (&((*x).gimple_omp_for.iter[i5].incr), cookie);
          }
          if ((void *)(x) == this_obj)
            op (&((*x).gimple_omp_for.iter), cookie);
        }
        if ((void *)(x) == this_obj)
          op (&((*x).gimple_omp_for.pre_body), cookie);
      }
      break;
    case GSS_OMP_PARALLEL:
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_parallel.omp.gsbase.bb), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_parallel.omp.gsbase.next), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_parallel.omp.body), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_parallel.clauses), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_parallel.child_fn), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_parallel.data_arg), cookie);
      break;
    case GSS_OMP_TASK:
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_task.par.omp.gsbase.bb), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_task.par.omp.gsbase.next), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_task.par.omp.body), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_task.par.clauses), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_task.par.child_fn), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_task.par.data_arg), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_task.copy_fn), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_task.arg_size), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_task.arg_align), cookie);
      break;
    case GSS_OMP_SECTIONS:
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_sections.omp.gsbase.bb), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_sections.omp.gsbase.next), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_sections.omp.body), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_sections.clauses), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_sections.control), cookie);
      break;
    case GSS_OMP_SINGLE:
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_single.omp.gsbase.bb), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_single.omp.gsbase.next), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_single.omp.body), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_single.clauses), cookie);
      break;
    case GSS_OMP_CONTINUE:
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_continue.gsbase.bb), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_continue.gsbase.next), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_continue.control_def), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_continue.control_use), cookie);
      break;
    case GSS_OMP_ATOMIC_LOAD:
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_atomic_load.gsbase.bb), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_atomic_load.gsbase.next), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_atomic_load.rhs), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_atomic_load.lhs), cookie);
      break;
    case GSS_OMP_ATOMIC_STORE:
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_atomic_store.gsbase.bb), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_atomic_store.gsbase.next), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_omp_atomic_store.val), cookie);
      break;
    case GSS_TRANSACTION:
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_transaction.gsbase.opbase.gsbase.bb), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_transaction.gsbase.opbase.gsbase.next), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_transaction.body), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).gimple_transaction.label), cookie);
      break;
    default:
      break;
    }
}

void
gt_pch_p_9rtvec_def (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct rtvec_def * x ATTRIBUTE_UNUSED = (struct rtvec_def *)x_p;
  {
    size_t l0 = (size_t)(((*x)).num_elem);
    {
      size_t i0;
      for (i0 = 0; i0 != l0; i0++) {
        if ((void *)(x) == this_obj)
          op (&((*x).elem[i0]), cookie);
      }
    }
  }
}

void
gt_pch_p_7rtx_def (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct rtx_def * x ATTRIBUTE_UNUSED = (struct rtx_def *)x_p;
  switch (GET_CODE (&(*x)))
    {
    case DEBUG_PARAMETER_REF:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_tree), cookie);
      break;
    case ENTRY_VALUE:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case DEBUG_IMPLICIT_PTR:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_tree), cookie);
      break;
    case VAR_LOCATION:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_tree), cookie);
      break;
    case FMA:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[2].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case US_TRUNCATE:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case SS_TRUNCATE:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case US_MINUS:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case US_ASHIFT:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case SS_ASHIFT:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case SS_ABS:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case US_NEG:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case SS_NEG:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case SS_MINUS:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case US_PLUS:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case SS_PLUS:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case VEC_DUPLICATE:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case VEC_CONCAT:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case VEC_SELECT:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case VEC_MERGE:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[2].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case LO_SUM:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case HIGH:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case ZERO_EXTRACT:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[2].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case SIGN_EXTRACT:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[2].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case PARITY:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case POPCOUNT:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case CTZ:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case CLZ:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case CLRSB:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case FFS:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case BSWAP:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case SQRT:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case ABS:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case UNSIGNED_SAT_FRACT:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case SAT_FRACT:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case UNSIGNED_FRACT_CONVERT:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case FRACT_CONVERT:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case UNSIGNED_FIX:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case UNSIGNED_FLOAT:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case FIX:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case FLOAT:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case FLOAT_TRUNCATE:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case FLOAT_EXTEND:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case TRUNCATE:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case ZERO_EXTEND:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case SIGN_EXTEND:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case LTGT:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case UNLT:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case UNLE:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case UNGT:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case UNGE:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case UNEQ:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case ORDERED:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case UNORDERED:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case LTU:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case LEU:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case GTU:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case GEU:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case LT:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case LE:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case GT:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case GE:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case EQ:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case NE:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case POST_MODIFY:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case PRE_MODIFY:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case POST_INC:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case POST_DEC:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case PRE_INC:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case PRE_DEC:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case UMAX:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case UMIN:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case SMAX:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case SMIN:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case ROTATERT:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case LSHIFTRT:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case ASHIFTRT:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case ROTATE:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case ASHIFT:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case NOT:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case XOR:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case IOR:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case AND:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case UMOD:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case UDIV:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case MOD:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case US_DIV:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case SS_DIV:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case DIV:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case US_MULT:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case SS_MULT:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case MULT:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case NEG:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case MINUS:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case PLUS:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case COMPARE:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case IF_THEN_ELSE:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[2].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case CC0:
      break;
    case SYMBOL_REF:
      switch (SYMBOL_REF_HAS_BLOCK_INFO_P (&(*x)))
        {
        case 1:
          if ((void *)(x) == this_obj)
            op (&((*x).u.block_sym.block), cookie);
          break;
        default:
          break;
        }
      switch (CONSTANT_POOL_ADDRESS_P (&(*x)))
        {
        case 1:
          if ((void *)(x) == this_obj)
            op (&((*x).u.fld[2].rt_constant), cookie);
          break;
        default:
          if ((void *)(x) == this_obj)
            op (&((*x).u.fld[2].rt_tree), cookie);
          break;
        }
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_str), cookie);
      break;
    case LABEL_REF:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case MEM:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_mem), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case CONCATN:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtvec), cookie);
      break;
    case CONCAT:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case STRICT_LOW_PART:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case SUBREG:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case SCRATCH:
      break;
    case REG:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[2].rt_reg), cookie);
      break;
    case PC:
      break;
    case CONST:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case CONST_STRING:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_str), cookie);
      break;
    case CONST_VECTOR:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtvec), cookie);
      break;
    case CONST_DOUBLE:
      break;
    case CONST_FIXED:
      break;
    case CONST_INT:
      break;
    case TRAP_IF:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case EH_RETURN:
      break;
    case SIMPLE_RETURN:
      break;
    case RETURN:
      break;
    case CALL:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case CLOBBER:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case USE:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case SET:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case PREFETCH:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[2].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case ADDR_DIFF_VEC:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[3].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[2].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtvec), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case ADDR_VEC:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtvec), cookie);
      break;
    case UNSPEC_VOLATILE:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtvec), cookie);
      break;
    case UNSPEC:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtvec), cookie);
      break;
    case ASM_OPERANDS:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[5].rt_rtvec), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[4].rt_rtvec), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[3].rt_rtvec), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_str), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_str), cookie);
      break;
    case ASM_INPUT:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_str), cookie);
      break;
    case PARALLEL:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtvec), cookie);
      break;
    case COND_EXEC:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case NOTE:
      switch (NOTE_KIND (&(*x)))
        {
        default:
          if ((void *)(x) == this_obj)
            op (&((*x).u.fld[4].rt_str), cookie);
          break;
        case NOTE_INSN_CFI_LABEL:
          break;
        case NOTE_INSN_CFI:
          break;
        case NOTE_INSN_SWITCH_TEXT_SECTIONS:
          break;
        case NOTE_INSN_BASIC_BLOCK:
          break;
        case NOTE_INSN_CALL_ARG_LOCATION:
          if ((void *)(x) == this_obj)
            op (&((*x).u.fld[4].rt_rtx), cookie);
          break;
        case NOTE_INSN_VAR_LOCATION:
          if ((void *)(x) == this_obj)
            op (&((*x).u.fld[4].rt_rtx), cookie);
          break;
        case NOTE_INSN_EH_REGION_END:
          break;
        case NOTE_INSN_EH_REGION_BEG:
          break;
        case NOTE_INSN_EPILOGUE_BEG:
          break;
        case NOTE_INSN_PROLOGUE_END:
          break;
        case NOTE_INSN_FUNCTION_BEG:
          break;
        case NOTE_INSN_BLOCK_END:
          if ((void *)(x) == this_obj)
            op (&((*x).u.fld[4].rt_tree), cookie);
          break;
        case NOTE_INSN_BLOCK_BEG:
          if ((void *)(x) == this_obj)
            op (&((*x).u.fld[4].rt_tree), cookie);
          break;
        case NOTE_INSN_DELETED_DEBUG_LABEL:
          if ((void *)(x) == this_obj)
            op (&((*x).u.fld[4].rt_str), cookie);
          break;
        case NOTE_INSN_DELETED_LABEL:
          if ((void *)(x) == this_obj)
            op (&((*x).u.fld[4].rt_str), cookie);
          break;
        case NOTE_INSN_DELETED:
          break;
        }
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[3].rt_bb), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[2].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      break;
    case CODE_LABEL:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[7].rt_str), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[4].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[3].rt_bb), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[2].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      break;
    case BARRIER:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[2].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      break;
    case CALL_INSN:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[8].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[7].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[4].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[3].rt_bb), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[2].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      break;
    case JUMP_INSN:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[8].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[7].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[4].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[3].rt_bb), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[2].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      break;
    case INSN:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[7].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[4].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[3].rt_bb), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[2].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      break;
    case DEBUG_INSN:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[7].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[4].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[3].rt_bb), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[2].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      break;
    case ADDRESS:
      break;
    case SEQUENCE:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtvec), cookie);
      break;
    case INSN_LIST:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case EXPR_LIST:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[1].rt_rtx), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_rtx), cookie);
      break;
    case DEBUG_EXPR:
      if ((void *)(x) == this_obj)
        op (&((*x).u.fld[0].rt_tree), cookie);
      break;
    case VALUE:
      break;
    case UNKNOWN:
      break;
    default:
      break;
    }
}

void
gt_pch_p_15bitmap_head_def (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct bitmap_head_def * x ATTRIBUTE_UNUSED = (struct bitmap_head_def *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).first), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).obstack), cookie);
}

void
gt_pch_p_6answer (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct answer * x ATTRIBUTE_UNUSED = (struct answer *)x_p;
  {
    size_t l0 = (size_t)(((*x)).count);
    if ((void *)(x) == this_obj)
      op (&((*x).next), cookie);
    {
      size_t i0;
      for (i0 = 0; i0 != l0; i0++) {
        switch (cpp_token_val_index (&((*x).first[i0])))
          {
          case CPP_TOKEN_FLD_NODE:
            {
              union tree_node * x1 =
                ((*x).first[i0].val.node.node) ? HT_IDENT_TO_GCC_IDENT (HT_NODE (((*x).first[i0].val.node.node))) : NULL;
              if ((void *)(x) == this_obj)
                op (&(x1), cookie);
              (*x).first[i0].val.node.node = (x1) ? CPP_HASHNODE (GCC_IDENT_TO_HT_IDENT ((x1))) : NULL;
            }
            break;
          case CPP_TOKEN_FLD_SOURCE:
            if ((void *)(x) == this_obj)
              op (&((*x).first[i0].val.source), cookie);
            break;
          case CPP_TOKEN_FLD_STR:
            if ((void *)(x) == this_obj)
              op (&((*x).first[i0].val.str.text), cookie);
            break;
          case CPP_TOKEN_FLD_ARG_NO:
            break;
          case CPP_TOKEN_FLD_TOKEN_NO:
            break;
          case CPP_TOKEN_FLD_PRAGMA:
            break;
          default:
            break;
          }
      }
    }
  }
}

void
gt_pch_p_9cpp_macro (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct cpp_macro * x ATTRIBUTE_UNUSED = (struct cpp_macro *)x_p;
  {
    size_t l0 = (size_t)(((*x)).paramc);
    if ((*x).params != NULL) {
      size_t i0;
      for (i0 = 0; i0 != (size_t)(l0) && ((void *)(*x).params == this_obj); i0++) {
        {
          union tree_node * x1 =
            ((*x).params[i0]) ? HT_IDENT_TO_GCC_IDENT (HT_NODE (((*x).params[i0]))) : NULL;
          if ((void *)((*x).params) == this_obj)
            op (&(x1), cookie);
          (*x).params[i0] = (x1) ? CPP_HASHNODE (GCC_IDENT_TO_HT_IDENT ((x1))) : NULL;
        }
      }
      if ((void *)(x) == this_obj)
        op (&((*x).params), cookie);
    }
    switch (((*x)).traditional)
      {
      case 0:
        if ((*x).exp.tokens != NULL) {
          size_t i2;
          for (i2 = 0; i2 != (size_t)((*x).count) && ((void *)(*x).exp.tokens == this_obj); i2++) {
            switch (cpp_token_val_index (&((*x).exp.tokens[i2])))
              {
              case CPP_TOKEN_FLD_NODE:
                {
                  union tree_node * x3 =
                    ((*x).exp.tokens[i2].val.node.node) ? HT_IDENT_TO_GCC_IDENT (HT_NODE (((*x).exp.tokens[i2].val.node.node))) : NULL;
                  if ((void *)((*x).exp.tokens) == this_obj)
                    op (&(x3), cookie);
                  (*x).exp.tokens[i2].val.node.node = (x3) ? CPP_HASHNODE (GCC_IDENT_TO_HT_IDENT ((x3))) : NULL;
                }
                break;
              case CPP_TOKEN_FLD_SOURCE:
                if ((void *)((*x).exp.tokens) == this_obj)
                  op (&((*x).exp.tokens[i2].val.source), cookie);
                break;
              case CPP_TOKEN_FLD_STR:
                if ((void *)((*x).exp.tokens) == this_obj)
                  op (&((*x).exp.tokens[i2].val.str.text), cookie);
                break;
              case CPP_TOKEN_FLD_ARG_NO:
                break;
              case CPP_TOKEN_FLD_TOKEN_NO:
                break;
              case CPP_TOKEN_FLD_PRAGMA:
                break;
              default:
                break;
              }
          }
          if ((void *)(x) == this_obj)
            op (&((*x).exp.tokens), cookie);
        }
        break;
      case 1:
        if ((void *)(x) == this_obj)
          op (&((*x).exp.text), cookie);
        break;
      default:
        break;
      }
  }
}

void
gt_pch_p_9cpp_token (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct cpp_token * x ATTRIBUTE_UNUSED = (struct cpp_token *)x_p;
  switch (cpp_token_val_index (&((*x))))
    {
    case CPP_TOKEN_FLD_NODE:
      {
        union tree_node * x0 =
          ((*x).val.node.node) ? HT_IDENT_TO_GCC_IDENT (HT_NODE (((*x).val.node.node))) : NULL;
        if ((void *)(x) == this_obj)
          op (&(x0), cookie);
        (*x).val.node.node = (x0) ? CPP_HASHNODE (GCC_IDENT_TO_HT_IDENT ((x0))) : NULL;
      }
      break;
    case CPP_TOKEN_FLD_SOURCE:
      if ((void *)(x) == this_obj)
        op (&((*x).val.source), cookie);
      break;
    case CPP_TOKEN_FLD_STR:
      if ((void *)(x) == this_obj)
        op (&((*x).val.str.text), cookie);
      break;
    case CPP_TOKEN_FLD_ARG_NO:
      break;
    case CPP_TOKEN_FLD_TOKEN_NO:
      break;
    case CPP_TOKEN_FLD_PRAGMA:
      break;
    default:
      break;
    }
}

void
gt_pch_p_9line_maps (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct line_maps * x ATTRIBUTE_UNUSED = (struct line_maps *)x_p;
  {
    size_t l0 = (size_t)(((*x).info_ordinary).used);
    if ((*x).info_ordinary.maps != NULL) {
      size_t i0;
      for (i0 = 0; i0 != (size_t)(l0) && ((void *)(*x).info_ordinary.maps == this_obj); i0++) {
        switch (((*x).info_ordinary.maps[i0]).reason == LC_ENTER_MACRO)
          {
          case 0:
            if ((void *)((*x).info_ordinary.maps) == this_obj)
              op (&((*x).info_ordinary.maps[i0].d.ordinary.to_file), cookie);
            break;
          case 1:
            {
              union tree_node * x1 =
                ((*x).info_ordinary.maps[i0].d.macro.macro) ? HT_IDENT_TO_GCC_IDENT (HT_NODE (((*x).info_ordinary.maps[i0].d.macro.macro))) : NULL;
              if ((void *)((*x).info_ordinary.maps) == this_obj)
                op (&(x1), cookie);
              (*x).info_ordinary.maps[i0].d.macro.macro = (x1) ? CPP_HASHNODE (GCC_IDENT_TO_HT_IDENT ((x1))) : NULL;
            }
            if ((*x).info_ordinary.maps[i0].d.macro.macro_locations != NULL) {
              if ((void *)((*x).info_ordinary.maps) == this_obj)
                op (&((*x).info_ordinary.maps[i0].d.macro.macro_locations), cookie);
            }
            break;
          default:
            break;
          }
      }
      if ((void *)(x) == this_obj)
        op (&((*x).info_ordinary.maps), cookie);
    }
  }
  {
    size_t l2 = (size_t)(((*x).info_macro).used);
    if ((*x).info_macro.maps != NULL) {
      size_t i2;
      for (i2 = 0; i2 != (size_t)(l2) && ((void *)(*x).info_macro.maps == this_obj); i2++) {
        switch (((*x).info_macro.maps[i2]).reason == LC_ENTER_MACRO)
          {
          case 0:
            if ((void *)((*x).info_macro.maps) == this_obj)
              op (&((*x).info_macro.maps[i2].d.ordinary.to_file), cookie);
            break;
          case 1:
            {
              union tree_node * x3 =
                ((*x).info_macro.maps[i2].d.macro.macro) ? HT_IDENT_TO_GCC_IDENT (HT_NODE (((*x).info_macro.maps[i2].d.macro.macro))) : NULL;
              if ((void *)((*x).info_macro.maps) == this_obj)
                op (&(x3), cookie);
              (*x).info_macro.maps[i2].d.macro.macro = (x3) ? CPP_HASHNODE (GCC_IDENT_TO_HT_IDENT ((x3))) : NULL;
            }
            if ((*x).info_macro.maps[i2].d.macro.macro_locations != NULL) {
              if ((void *)((*x).info_macro.maps) == this_obj)
                op (&((*x).info_macro.maps[i2].d.macro.macro_locations), cookie);
            }
            break;
          default:
            break;
          }
      }
      if ((void *)(x) == this_obj)
        op (&((*x).info_macro.maps), cookie);
    }
  }
  {
    size_t l4 = (size_t)(((*x).location_adhoc_data_map).allocated);
    if ((*x).location_adhoc_data_map.data != NULL) {
      size_t i4;
      for (i4 = 0; i4 != (size_t)(l4) && ((void *)(*x).location_adhoc_data_map.data == this_obj); i4++) {
      }
      if ((void *)(x) == this_obj)
        op (&((*x).location_adhoc_data_map.data), cookie);
    }
  }
}

void
gt_pch_p_II17splay_tree_node_s (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct splay_tree_node_s * x ATTRIBUTE_UNUSED = (struct splay_tree_node_s *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).left), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).right), cookie);
}

void
gt_pch_p_SP9tree_node17splay_tree_node_s (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct splay_tree_node_s * x ATTRIBUTE_UNUSED = (struct splay_tree_node_s *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).key), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).value), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).left), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).right), cookie);
}

void
gt_pch_p_P9tree_nodeP9tree_node17splay_tree_node_s (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct splay_tree_node_s * x ATTRIBUTE_UNUSED = (struct splay_tree_node_s *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).key), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).value), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).left), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).right), cookie);
}

void
gt_pch_p_P17lto_in_decl_state4htab (ATTRIBUTE_UNUSED void *this_obj,
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

void
gt_pch_p_P9tree_nodeP9tree_node12splay_tree_s (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct splay_tree_s * x ATTRIBUTE_UNUSED = (struct splay_tree_s *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).root), cookie);
}

void
gt_pch_p_P15tm_restart_node4htab (ATTRIBUTE_UNUSED void *this_obj,
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

void
gt_pch_p_P12tree_int_map4htab (ATTRIBUTE_UNUSED void *this_obj,
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

void
gt_pch_p_P8tree_map4htab (ATTRIBUTE_UNUSED void *this_obj,
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

void
gt_pch_p_P24constant_descriptor_tree4htab (ATTRIBUTE_UNUSED void *this_obj,
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

void
gt_pch_p_P12object_block4htab (ATTRIBUTE_UNUSED void *this_obj,
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

void
gt_pch_p_P7section4htab (ATTRIBUTE_UNUSED void *this_obj,
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

void
gt_pch_p_P17tree_priority_map4htab (ATTRIBUTE_UNUSED void *this_obj,
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

void
gt_pch_p_P12tree_vec_map4htab (ATTRIBUTE_UNUSED void *this_obj,
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

void
gt_pch_p_P13tree_decl_map4htab (ATTRIBUTE_UNUSED void *this_obj,
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

void
gt_pch_p_P15throw_stmt_node4htab (ATTRIBUTE_UNUSED void *this_obj,
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

void
gt_pch_p_P9reg_attrs4htab (ATTRIBUTE_UNUSED void *this_obj,
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

void
gt_pch_p_P9mem_attrs4htab (ATTRIBUTE_UNUSED void *this_obj,
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

void
gt_pch_p_P7rtx_def4htab (ATTRIBUTE_UNUSED void *this_obj,
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

void
gt_pch_p_SP9tree_node12splay_tree_s (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct splay_tree_s * x ATTRIBUTE_UNUSED = (struct splay_tree_s *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).root), cookie);
}

void
gt_pch_p_II12splay_tree_s (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct splay_tree_s * x ATTRIBUTE_UNUSED = (struct splay_tree_s *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).root), cookie);
}

void
gt_pch_p_P15symtab_node_def4htab (ATTRIBUTE_UNUSED void *this_obj,
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

void
gt_pch_p_P11cgraph_edge4htab (ATTRIBUTE_UNUSED void *this_obj,
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

void
gt_pch_p_P9loop_exit4htab (ATTRIBUTE_UNUSED void *this_obj,
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

void
gt_pch_p_P24types_used_by_vars_entry4htab (ATTRIBUTE_UNUSED void *this_obj,
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

void
gt_pch_p_P9tree_node4htab (ATTRIBUTE_UNUSED void *this_obj,
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

void
gt_pch_p_P13libfunc_entry4htab (ATTRIBUTE_UNUSED void *this_obj,
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
void * ggc_alloc_splay_tree_scalar_scalar_splay_tree_node_s (int sz, void * nl)
{
  return ggc_splay_alloc (sz, nl);
}

void * ggc_alloc_splay_tree_str_tree_node_splay_tree_node_s (int sz, void * nl)
{
  return ggc_splay_alloc (sz, nl);
}

void * ggc_alloc_splay_tree_tree_node_tree_node_splay_tree_node_s (int sz, void * nl)
{
  return ggc_splay_alloc (sz, nl);
}

void * ggc_alloc_splay_tree_string_descriptor_htab (int sz, void * nl)
{
  return ggc_splay_alloc (sz, nl);
}

void * ggc_alloc_splay_tree_type_assertion_htab (int sz, void * nl)
{
  return ggc_splay_alloc (sz, nl);
}

void * ggc_alloc_splay_tree_treetreehash_entry_htab (int sz, void * nl)
{
  return ggc_splay_alloc (sz, nl);
}

void * ggc_alloc_splay_tree_module_htab_entry_htab (int sz, void * nl)
{
  return ggc_splay_alloc (sz, nl);
}

void * ggc_alloc_splay_tree_pending_abstract_type_htab (int sz, void * nl)
{
  return ggc_splay_alloc (sz, nl);
}

void * ggc_alloc_splay_tree_constexpr_call_htab (int sz, void * nl)
{
  return ggc_splay_alloc (sz, nl);
}

void * ggc_alloc_splay_tree_constexpr_fundef_htab (int sz, void * nl)
{
  return ggc_splay_alloc (sz, nl);
}

void * ggc_alloc_splay_tree_spec_entry_htab (int sz, void * nl)
{
  return ggc_splay_alloc (sz, nl);
}

void * ggc_alloc_splay_tree_cxx_int_tree_map_htab (int sz, void * nl)
{
  return ggc_splay_alloc (sz, nl);
}

void * ggc_alloc_splay_tree_named_label_entry_htab (int sz, void * nl)
{
  return ggc_splay_alloc (sz, nl);
}

void * ggc_alloc_splay_tree_pad_type_hash_htab (int sz, void * nl)
{
  return ggc_splay_alloc (sz, nl);
}

void * ggc_alloc_splay_tree_lto_in_decl_state_htab (int sz, void * nl)
{
  return ggc_splay_alloc (sz, nl);
}

void * ggc_alloc_splay_tree_tree_node_tree_node_splay_tree_s (int sz, void * nl)
{
  return ggc_splay_alloc (sz, nl);
}

void * ggc_alloc_splay_tree_scev_info_str_htab (int sz, void * nl)
{
  return ggc_splay_alloc (sz, nl);
}

void * ggc_alloc_splay_tree_tm_restart_node_htab (int sz, void * nl)
{
  return ggc_splay_alloc (sz, nl);
}

void * ggc_alloc_splay_tree_tree_int_map_htab (int sz, void * nl)
{
  return ggc_splay_alloc (sz, nl);
}

void * ggc_alloc_splay_tree_tree_map_htab (int sz, void * nl)
{
  return ggc_splay_alloc (sz, nl);
}

void * ggc_alloc_splay_tree_constant_descriptor_rtx_htab (int sz, void * nl)
{
  return ggc_splay_alloc (sz, nl);
}

void * ggc_alloc_splay_tree_constant_descriptor_tree_htab (int sz, void * nl)
{
  return ggc_splay_alloc (sz, nl);
}

void * ggc_alloc_splay_tree_object_block_htab (int sz, void * nl)
{
  return ggc_splay_alloc (sz, nl);
}

void * ggc_alloc_splay_tree_section_htab (int sz, void * nl)
{
  return ggc_splay_alloc (sz, nl);
}

void * ggc_alloc_splay_tree_tree_priority_map_htab (int sz, void * nl)
{
  return ggc_splay_alloc (sz, nl);
}

void * ggc_alloc_splay_tree_tree_vec_map_htab (int sz, void * nl)
{
  return ggc_splay_alloc (sz, nl);
}

void * ggc_alloc_splay_tree_tree_decl_map_htab (int sz, void * nl)
{
  return ggc_splay_alloc (sz, nl);
}

void * ggc_alloc_splay_tree_type_hash_htab (int sz, void * nl)
{
  return ggc_splay_alloc (sz, nl);
}

void * ggc_alloc_splay_tree_temp_slot_address_entry_htab (int sz, void * nl)
{
  return ggc_splay_alloc (sz, nl);
}

void * ggc_alloc_splay_tree_throw_stmt_node_htab (int sz, void * nl)
{
  return ggc_splay_alloc (sz, nl);
}

void * ggc_alloc_splay_tree_reg_attrs_htab (int sz, void * nl)
{
  return ggc_splay_alloc (sz, nl);
}

void * ggc_alloc_splay_tree_mem_attrs_htab (int sz, void * nl)
{
  return ggc_splay_alloc (sz, nl);
}

void * ggc_alloc_splay_tree_rtx_def_htab (int sz, void * nl)
{
  return ggc_splay_alloc (sz, nl);
}

void * ggc_alloc_splay_tree_addr_table_entry_struct_htab (int sz, void * nl)
{
  return ggc_splay_alloc (sz, nl);
}

void * ggc_alloc_splay_tree_cached_dw_loc_list_def_htab (int sz, void * nl)
{
  return ggc_splay_alloc (sz, nl);
}

void * ggc_alloc_splay_tree_var_loc_list_def_htab (int sz, void * nl)
{
  return ggc_splay_alloc (sz, nl);
}

void * ggc_alloc_splay_tree_die_struct_htab (int sz, void * nl)
{
  return ggc_splay_alloc (sz, nl);
}

void * ggc_alloc_splay_tree_dwarf_file_data_htab (int sz, void * nl)
{
  return ggc_splay_alloc (sz, nl);
}

void * ggc_alloc_splay_tree_indirect_string_node_htab (int sz, void * nl)
{
  return ggc_splay_alloc (sz, nl);
}

void * ggc_alloc_splay_tree_str_tree_node_splay_tree_s (int sz, void * nl)
{
  return ggc_splay_alloc (sz, nl);
}

void * ggc_alloc_splay_tree_scalar_scalar_splay_tree_s (int sz, void * nl)
{
  return ggc_splay_alloc (sz, nl);
}

void * ggc_alloc_splay_tree_symtab_node_def_htab (int sz, void * nl)
{
  return ggc_splay_alloc (sz, nl);
}

void * ggc_alloc_splay_tree_cgraph_edge_htab (int sz, void * nl)
{
  return ggc_splay_alloc (sz, nl);
}

void * ggc_alloc_splay_tree_loop_exit_htab (int sz, void * nl)
{
  return ggc_splay_alloc (sz, nl);
}

void * ggc_alloc_splay_tree_types_used_by_vars_entry_htab (int sz, void * nl)
{
  return ggc_splay_alloc (sz, nl);
}

void * ggc_alloc_splay_tree_tree_node_htab (int sz, void * nl)
{
  return ggc_splay_alloc (sz, nl);
}

void * ggc_alloc_splay_tree_libfunc_entry_htab (int sz, void * nl)
{
  return ggc_splay_alloc (sz, nl);
}


/* GC roots.  */

static void gt_ggc_ma_regno_reg_rtx (void *);
static void
gt_ggc_ma_regno_reg_rtx (ATTRIBUTE_UNUSED void *x_p)
{
  if (regno_reg_rtx != NULL) {
    size_t i0;
    for (i0 = 0; i0 != (size_t)(crtl->emit.x_reg_rtx_no); i0++) {
      gt_ggc_m_7rtx_def (regno_reg_rtx[i0]);
    }
    ggc_mark (regno_reg_rtx);
  }
}

static void gt_pch_pa_regno_reg_rtx
    (void *, void *, gt_pointer_operator, void *);
static void gt_pch_pa_regno_reg_rtx (ATTRIBUTE_UNUSED void *this_obj,
      ATTRIBUTE_UNUSED void *x_p,
      ATTRIBUTE_UNUSED gt_pointer_operator op,
      ATTRIBUTE_UNUSED void * cookie)
{
  if (regno_reg_rtx != NULL) {
    size_t i0;
    for (i0 = 0; i0 != (size_t)(crtl->emit.x_reg_rtx_no) && ((void *)regno_reg_rtx == this_obj); i0++) {
      if ((void *)(regno_reg_rtx) == this_obj)
        op (&(regno_reg_rtx[i0]), cookie);
    }
    if ((void *)(&regno_reg_rtx) == this_obj)
      op (&(regno_reg_rtx), cookie);
  }
}

static void gt_pch_na_regno_reg_rtx (void *);
static void
gt_pch_na_regno_reg_rtx (ATTRIBUTE_UNUSED void *x_p)
{
  if (regno_reg_rtx != NULL) {
    size_t i0;
    for (i0 = 0; i0 != (size_t)(crtl->emit.x_reg_rtx_no); i0++) {
      gt_pch_n_7rtx_def (regno_reg_rtx[i0]);
    }
    gt_pch_note_object (regno_reg_rtx, &regno_reg_rtx, gt_pch_pa_regno_reg_rtx);
  }
}

EXPORTED_CONST struct ggc_root_tab gt_ggc_r_gtype_desc_c[] = {
  {
    &inline_summary_vec,
    1,
    sizeof (inline_summary_vec),
    &gt_ggc_mx_vec_inline_summary_t_va_gc_,
    &gt_pch_nx_vec_inline_summary_t_va_gc_
  },
  {
    &lto_global_var_decls,
    1,
    sizeof (lto_global_var_decls),
    &gt_ggc_mx_vec_tree_va_gc_,
    &gt_pch_nx_vec_tree_va_gc_
  },
  {
    &ipa_edge_args_vector,
    1,
    sizeof (ipa_edge_args_vector),
    &gt_ggc_mx_vec_ipa_edge_args_t_va_gc_,
    &gt_pch_nx_vec_ipa_edge_args_t_va_gc_
  },
  {
    &ipa_node_agg_replacements,
    1,
    sizeof (ipa_node_agg_replacements),
    &gt_ggc_mx_vec_ipa_agg_replacement_value_p_va_gc_,
    &gt_pch_nx_vec_ipa_agg_replacement_value_p_va_gc_
  },
  {
    &ipa_escaped_pt.vars,
    1,
    sizeof (ipa_escaped_pt.vars),
    &gt_ggc_mx_bitmap_head_def,
    &gt_pch_nx_bitmap_head_def
  },
  {
    &chrec_known,
    1,
    sizeof (chrec_known),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &chrec_dont_know,
    1,
    sizeof (chrec_dont_know),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &block_clear_fn,
    1,
    sizeof (block_clear_fn),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &cie_cfi_vec,
    1,
    sizeof (cie_cfi_vec),
    &gt_ggc_mx_vec_dw_cfi_ref_va_gc_,
    &gt_pch_nx_vec_dw_cfi_ref_va_gc_
  },
  {
    &asm_nodes,
    1,
    sizeof (asm_nodes),
    &gt_ggc_mx_asm_node,
    &gt_pch_nx_asm_node
  },
  {
    &symtab_nodes,
    1,
    sizeof (symtab_nodes),
    &gt_ggc_mx_symtab_node_def,
    &gt_pch_nx_symtab_node_def
  },
  {
    &in_section,
    1,
    sizeof (in_section),
    &gt_ggc_mx_section,
    &gt_pch_nx_section
  },
  {
    &bss_noswitch_section,
    1,
    sizeof (bss_noswitch_section),
    &gt_ggc_mx_section,
    &gt_pch_nx_section
  },
  {
    &lcomm_section,
    1,
    sizeof (lcomm_section),
    &gt_ggc_mx_section,
    &gt_pch_nx_section
  },
  {
    &comm_section,
    1,
    sizeof (comm_section),
    &gt_ggc_mx_section,
    &gt_pch_nx_section
  },
  {
    &tls_comm_section,
    1,
    sizeof (tls_comm_section),
    &gt_ggc_mx_section,
    &gt_pch_nx_section
  },
  {
    &eh_frame_section,
    1,
    sizeof (eh_frame_section),
    &gt_ggc_mx_section,
    &gt_pch_nx_section
  },
  {
    &exception_section,
    1,
    sizeof (exception_section),
    &gt_ggc_mx_section,
    &gt_pch_nx_section
  },
  {
    &sbss_section,
    1,
    sizeof (sbss_section),
    &gt_ggc_mx_section,
    &gt_pch_nx_section
  },
  {
    &bss_section,
    1,
    sizeof (bss_section),
    &gt_ggc_mx_section,
    &gt_pch_nx_section
  },
  {
    &dtors_section,
    1,
    sizeof (dtors_section),
    &gt_ggc_mx_section,
    &gt_pch_nx_section
  },
  {
    &ctors_section,
    1,
    sizeof (ctors_section),
    &gt_ggc_mx_section,
    &gt_pch_nx_section
  },
  {
    &sdata_section,
    1,
    sizeof (sdata_section),
    &gt_ggc_mx_section,
    &gt_pch_nx_section
  },
  {
    &readonly_data_section,
    1,
    sizeof (readonly_data_section),
    &gt_ggc_mx_section,
    &gt_pch_nx_section
  },
  {
    &data_section,
    1,
    sizeof (data_section),
    &gt_ggc_mx_section,
    &gt_pch_nx_section
  },
  {
    &text_section,
    1,
    sizeof (text_section),
    &gt_ggc_mx_section,
    &gt_pch_nx_section
  },
  {
    &types_used_by_cur_var_decl,
    1,
    sizeof (types_used_by_cur_var_decl),
    &gt_ggc_mx_vec_tree_va_gc_,
    &gt_pch_nx_vec_tree_va_gc_
  },
  {
    &types_used_by_vars_hash,
    1,
    sizeof (types_used_by_vars_hash),
    &gt_ggc_m_P24types_used_by_vars_entry4htab,
    &gt_pch_n_P24types_used_by_vars_entry4htab
  },
  {
    &cfun,
    1,
    sizeof (cfun),
    &gt_ggc_mx_function,
    &gt_pch_nx_function
  },
  {
    &x_rtl.expr.x_saveregs_value,
    1,
    sizeof (x_rtl.expr.x_saveregs_value),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &x_rtl.expr.x_apply_args_value,
    1,
    sizeof (x_rtl.expr.x_apply_args_value),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &x_rtl.expr.x_forced_labels,
    1,
    sizeof (x_rtl.expr.x_forced_labels),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &x_rtl.emit.x_first_insn,
    1,
    sizeof (x_rtl.emit.x_first_insn),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &x_rtl.emit.x_last_insn,
    1,
    sizeof (x_rtl.emit.x_last_insn),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &x_rtl.emit.sequence_stack,
    1,
    sizeof (x_rtl.emit.sequence_stack),
    &gt_ggc_mx_sequence_stack,
    &gt_pch_nx_sequence_stack
  },
  {
    &x_rtl.varasm.pool,
    1,
    sizeof (x_rtl.varasm.pool),
    &gt_ggc_mx_rtx_constant_pool,
    &gt_pch_nx_rtx_constant_pool
  },
  {
    &x_rtl.args.arg_offset_rtx,
    1,
    sizeof (x_rtl.args.arg_offset_rtx),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &x_rtl.args.internal_arg_pointer,
    1,
    sizeof (x_rtl.args.internal_arg_pointer),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &x_rtl.subsections.hot_section_label,
    1,
    sizeof (x_rtl.subsections.hot_section_label),
    (gt_pointer_walker) &gt_ggc_m_S,
    (gt_pointer_walker) &gt_pch_n_S
  },
  {
    &x_rtl.subsections.cold_section_label,
    1,
    sizeof (x_rtl.subsections.cold_section_label),
    (gt_pointer_walker) &gt_ggc_m_S,
    (gt_pointer_walker) &gt_pch_n_S
  },
  {
    &x_rtl.subsections.hot_section_end_label,
    1,
    sizeof (x_rtl.subsections.hot_section_end_label),
    (gt_pointer_walker) &gt_ggc_m_S,
    (gt_pointer_walker) &gt_pch_n_S
  },
  {
    &x_rtl.subsections.cold_section_end_label,
    1,
    sizeof (x_rtl.subsections.cold_section_end_label),
    (gt_pointer_walker) &gt_ggc_m_S,
    (gt_pointer_walker) &gt_pch_n_S
  },
  {
    &x_rtl.eh.ehr_stackadj,
    1,
    sizeof (x_rtl.eh.ehr_stackadj),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &x_rtl.eh.ehr_handler,
    1,
    sizeof (x_rtl.eh.ehr_handler),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &x_rtl.eh.ehr_label,
    1,
    sizeof (x_rtl.eh.ehr_label),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &x_rtl.eh.sjlj_fc,
    1,
    sizeof (x_rtl.eh.sjlj_fc),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &x_rtl.eh.sjlj_exit_after,
    1,
    sizeof (x_rtl.eh.sjlj_exit_after),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &x_rtl.eh.action_record_data,
    1,
    sizeof (x_rtl.eh.action_record_data),
    &gt_ggc_mx_vec_uchar_va_gc_,
    &gt_pch_nx_vec_uchar_va_gc_
  },
  {
    &x_rtl.eh.call_site_record_v[0],
    1 * (2),
    sizeof (x_rtl.eh.call_site_record_v[0]),
    &gt_ggc_mx_vec_call_site_record_va_gc_,
    &gt_pch_nx_vec_call_site_record_va_gc_
  },
  {
    &x_rtl.return_rtx,
    1,
    sizeof (x_rtl.return_rtx),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &x_rtl.hard_reg_initial_vals,
    1,
    sizeof (x_rtl.hard_reg_initial_vals),
    &gt_ggc_mx_initial_value_struct,
    &gt_pch_nx_initial_value_struct
  },
  {
    &x_rtl.stack_protect_guard,
    1,
    sizeof (x_rtl.stack_protect_guard),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &x_rtl.x_nonlocal_goto_handler_labels,
    1,
    sizeof (x_rtl.x_nonlocal_goto_handler_labels),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &x_rtl.x_return_label,
    1,
    sizeof (x_rtl.x_return_label),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &x_rtl.x_naked_return_label,
    1,
    sizeof (x_rtl.x_naked_return_label),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &x_rtl.x_stack_slot_list,
    1,
    sizeof (x_rtl.x_stack_slot_list),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &x_rtl.frame_space_list,
    1,
    sizeof (x_rtl.frame_space_list),
    &gt_ggc_mx_frame_space,
    &gt_pch_nx_frame_space
  },
  {
    &x_rtl.x_stack_check_probe_note,
    1,
    sizeof (x_rtl.x_stack_check_probe_note),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &x_rtl.x_arg_pointer_save_area,
    1,
    sizeof (x_rtl.x_arg_pointer_save_area),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &x_rtl.drap_reg,
    1,
    sizeof (x_rtl.drap_reg),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &x_rtl.x_parm_birth_insn,
    1,
    sizeof (x_rtl.x_parm_birth_insn),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &x_rtl.x_used_temp_slots,
    1,
    sizeof (x_rtl.x_used_temp_slots),
    &gt_ggc_mx_vec_temp_slot_p_va_gc_,
    &gt_pch_nx_vec_temp_slot_p_va_gc_
  },
  {
    &x_rtl.x_avail_temp_slots,
    1,
    sizeof (x_rtl.x_avail_temp_slots),
    &gt_ggc_mx_temp_slot,
    &gt_pch_nx_temp_slot
  },
  {
    &regno_reg_rtx,
    1,
    sizeof (regno_reg_rtx),
    &gt_ggc_ma_regno_reg_rtx,
    &gt_pch_na_regno_reg_rtx
  },
  {
    &default_target_libfuncs.x_libfunc_table[0],
    1 * (LTI_MAX),
    sizeof (default_target_libfuncs.x_libfunc_table[0]),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &default_target_libfuncs.x_libfunc_hash,
    1,
    sizeof (default_target_libfuncs.x_libfunc_hash),
    &gt_ggc_m_P13libfunc_entry4htab,
    &gt_pch_n_P13libfunc_entry4htab
  },
  {
    &builtin_info.decl[0],
    1 * ((int)END_BUILTINS),
    sizeof (builtin_info.decl[0]),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &current_function_func_begin_label,
    1,
    sizeof (current_function_func_begin_label),
    (gt_pointer_walker) &gt_ggc_m_S,
    (gt_pointer_walker) &gt_pch_n_S
  },
  {
    &current_function_decl,
    1,
    sizeof (current_function_decl),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &sizetype_tab[0],
    1 * ((int) stk_type_kind_last),
    sizeof (sizetype_tab[0]),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &integer_types[0],
    1 * (itk_none),
    sizeof (integer_types[0]),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &global_trees[0],
    1 * (TI_MAX),
    sizeof (global_trees[0]),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &all_translation_units,
    1,
    sizeof (all_translation_units),
    &gt_ggc_mx_vec_tree_va_gc_,
    &gt_pch_nx_vec_tree_va_gc_
  },
  {
    &alias_pairs,
    1,
    sizeof (alias_pairs),
    &gt_ggc_mx_vec_alias_pair_va_gc_,
    &gt_pch_nx_vec_alias_pair_va_gc_
  },
  {
    &stack_limit_rtx,
    1,
    sizeof (stack_limit_rtx),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &default_target_rtl.x_global_rtl[0],
    1 * (GR_MAX),
    sizeof (default_target_rtl.x_global_rtl[0]),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &default_target_rtl.x_pic_offset_table_rtx,
    1,
    sizeof (default_target_rtl.x_pic_offset_table_rtx),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &default_target_rtl.x_return_address_pointer_rtx,
    1,
    sizeof (default_target_rtl.x_return_address_pointer_rtx),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &default_target_rtl.x_initial_regno_reg_rtx[0],
    1 * (FIRST_PSEUDO_REGISTER),
    sizeof (default_target_rtl.x_initial_regno_reg_rtx[0]),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &default_target_rtl.x_top_of_stack[0],
    1 * (MAX_MACHINE_MODE),
    sizeof (default_target_rtl.x_top_of_stack[0]),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &default_target_rtl.x_static_reg_base_value[0],
    1 * (FIRST_PSEUDO_REGISTER),
    sizeof (default_target_rtl.x_static_reg_base_value[0]),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &default_target_rtl.x_mode_mem_attrs[0],
    1 * ((int) MAX_MACHINE_MODE),
    sizeof (default_target_rtl.x_mode_mem_attrs[0]),
    &gt_ggc_mx_mem_attrs,
    &gt_pch_nx_mem_attrs
  },
  {
    &simple_return_rtx,
    1,
    sizeof (simple_return_rtx),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &ret_rtx,
    1,
    sizeof (ret_rtx),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &cc0_rtx,
    1,
    sizeof (cc0_rtx),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &pc_rtx,
    1,
    sizeof (pc_rtx),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &const_tiny_rtx[0][0],
    1 * (4) * ((int) MAX_MACHINE_MODE),
    sizeof (const_tiny_rtx[0][0]),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &const_true_rtx,
    1,
    sizeof (const_true_rtx),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &const_int_rtx[0],
    1 * (MAX_SAVED_CONST_INT * 2 + 1),
    sizeof (const_int_rtx[0]),
    &gt_ggc_mx_rtx_def,
    &gt_pch_nx_rtx_def
  },
  {
    &line_table,
    1,
    sizeof (line_table),
    &gt_ggc_mx_line_maps,
    &gt_pch_nx_line_maps
  },
  LAST_GGC_ROOT_TAB
};

EXPORTED_CONST struct ggc_root_tab gt_pch_rs_gtype_desc_c[] = {
  { &ipa_escaped_pt, 1, sizeof (ipa_escaped_pt), NULL, NULL },
  { &symtab_order, 1, sizeof (symtab_order), NULL, NULL },
  { &cgraph_edge_max_uid, 1, sizeof (cgraph_edge_max_uid), NULL, NULL },
  { &cgraph_max_uid, 1, sizeof (cgraph_max_uid), NULL, NULL },
  { &cgraph_n_nodes, 1, sizeof (cgraph_n_nodes), NULL, NULL },
  { &in_cold_section_p, 1, sizeof (in_cold_section_p), NULL, NULL },
  { &x_rtl, 1, sizeof (x_rtl), NULL, NULL },
  { &default_target_libfuncs, 1, sizeof (default_target_libfuncs), NULL, NULL },
  { &builtin_info, 1, sizeof (builtin_info), NULL, NULL },
  { &default_target_rtl, 1, sizeof (default_target_rtl), NULL, NULL },
  LAST_GGC_ROOT_TAB
};


/* Used to implement the RTX_NEXT macro.  */
EXPORTED_CONST unsigned char rtx_next[NUM_RTX_CODE] = {
  0,
  0,
  0,
  RTX_HDR_SIZE + 1 * sizeof (rtunion),
  RTX_HDR_SIZE + 1 * sizeof (rtunion),
  0,
  0,
  RTX_HDR_SIZE + 2 * sizeof (rtunion),
  RTX_HDR_SIZE + 2 * sizeof (rtunion),
  RTX_HDR_SIZE + 2 * sizeof (rtunion),
  RTX_HDR_SIZE + 2 * sizeof (rtunion),
  RTX_HDR_SIZE + 2 * sizeof (rtunion),
  RTX_HDR_SIZE + 2 * sizeof (rtunion),
  RTX_HDR_SIZE + 2 * sizeof (rtunion),
  RTX_HDR_SIZE + 1 * sizeof (rtunion),
  0,
  0,
  0,
  0,
  0,
  0,
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 1 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  0,
  0,
  0,
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  0,
  0,
  0,
  0,
  0,
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  0,
  0,
  0,
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  0,
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  0,
  0,
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 0 * sizeof (rtunion),
  RTX_HDR_SIZE + 1 * sizeof (rtunion),
  0,
  0,
  0,
};
