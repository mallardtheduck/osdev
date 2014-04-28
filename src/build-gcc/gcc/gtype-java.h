/* Type information for java.
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
gt_ggc_mx_vec_method_entry_va_gc_ (void *x_p)
{
  vec<method_entry,va_gc> * const x = (vec<method_entry,va_gc> *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_mx (x);
    }
}

void
gt_ggc_mx (struct method_entry_d& x_r ATTRIBUTE_UNUSED)
{
  struct method_entry_d * ATTRIBUTE_UNUSED x = &x_r;
  gt_ggc_m_9tree_node ((*x).method);
  gt_ggc_m_9tree_node ((*x).special);
}

void
gt_ggc_mx_type_assertion (void *x_p)
{
  struct type_assertion * const x = (struct type_assertion *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_9tree_node ((*x).op1);
      gt_ggc_m_9tree_node ((*x).op2);
    }
}

void
gt_ggc_mx_treetreehash_entry (void *x_p)
{
  struct treetreehash_entry * const x = (struct treetreehash_entry *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_9tree_node ((*x).key);
      gt_ggc_m_9tree_node ((*x).value);
    }
}

void
gt_ggc_mx_CPool (void *x_p)
{
  struct CPool * const x = (struct CPool *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      {
        size_t l0 = (size_t)(((*x)).count);
        if ((*x).tags != NULL) {
          ggc_mark ((*x).tags);
        }
        if ((*x).data != NULL) {
          size_t i0;
          for (i0 = 0; i0 != (size_t)(l0); i0++) {
            switch (cpool_entry_is_tree (((*x)).tags[i0]))
              {
              case 0:
                break;
              case 1:
                gt_ggc_m_9tree_node ((*x).data[i0].t);
                break;
              default:
                break;
              }
          }
          ggc_mark ((*x).data);
        }
      }
    }
}

void
gt_ggc_mx_JCF (void *x_p)
{
  struct JCF * const x = (struct JCF *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_S ((*x).filename);
      gt_ggc_m_S ((*x).classname);
      {
        size_t l0 = (size_t)(((*x).cpool).count);
        if ((*x).cpool.tags != NULL) {
          ggc_mark ((*x).cpool.tags);
        }
        if ((*x).cpool.data != NULL) {
          size_t i0;
          for (i0 = 0; i0 != (size_t)(l0); i0++) {
            switch (cpool_entry_is_tree (((*x).cpool).tags[i0]))
              {
              case 0:
                break;
              case 1:
                gt_ggc_m_9tree_node ((*x).cpool.data[i0].t);
                break;
              default:
                break;
              }
          }
          ggc_mark ((*x).cpool.data);
        }
      }
      {
        size_t l1 = (size_t)(((*x).bootstrap_methods).count);
        if ((*x).bootstrap_methods.methods != NULL) {
          size_t i1;
          for (i1 = 0; i1 != (size_t)(l1); i1++) {
            if ((*x).bootstrap_methods.methods[i1].bootstrap_arguments != NULL) {
              ggc_mark ((*x).bootstrap_methods.methods[i1].bootstrap_arguments);
            }
          }
          ggc_mark ((*x).bootstrap_methods.methods);
        }
      }
    }
}

void
gt_ggc_mx_lang_tree_node (void *x_p)
{
  union lang_tree_node * x = (union lang_tree_node *)x_p;
  union lang_tree_node * xlimit = x;
  while (ggc_test_and_set_mark (xlimit))
   xlimit = (CODE_CONTAINS_STRUCT (TREE_CODE (&(*xlimit).generic), TS_COMMON) ? ((union lang_tree_node *) TREE_CHAIN (&(*xlimit).generic)) : NULL);
  while (x != xlimit)
    {
      switch (TREE_CODE (&((*x)).generic) == IDENTIFIER_NODE)
        {
        case 0:
          switch (tree_node_structure (&((*x).generic)))
            {
            case TS_BASE:
              break;
            case TS_TYPED:
              gt_ggc_m_9tree_node ((*x).generic.typed.type);
              break;
            case TS_COMMON:
              gt_ggc_m_9tree_node ((*x).generic.common.typed.type);
              gt_ggc_m_9tree_node ((*x).generic.common.chain);
              break;
            case TS_INT_CST:
              gt_ggc_m_9tree_node ((*x).generic.int_cst.typed.type);
              break;
            case TS_REAL_CST:
              gt_ggc_m_9tree_node ((*x).generic.real_cst.typed.type);
              gt_ggc_m_10real_value ((*x).generic.real_cst.real_cst_ptr);
              break;
            case TS_FIXED_CST:
              gt_ggc_m_9tree_node ((*x).generic.fixed_cst.typed.type);
              gt_ggc_m_11fixed_value ((*x).generic.fixed_cst.fixed_cst_ptr);
              break;
            case TS_VECTOR:
              {
                size_t l0 = (size_t)(TYPE_VECTOR_SUBPARTS (TREE_TYPE ((tree)&((*x).generic.vector))));
                gt_ggc_m_9tree_node ((*x).generic.vector.typed.type);
                {
                  size_t i0;
                  for (i0 = 0; i0 != l0; i0++) {
                    gt_ggc_m_9tree_node ((*x).generic.vector.elts[i0]);
                  }
                }
              }
              break;
            case TS_STRING:
              gt_ggc_m_9tree_node ((*x).generic.string.typed.type);
              break;
            case TS_COMPLEX:
              gt_ggc_m_9tree_node ((*x).generic.complex.typed.type);
              gt_ggc_m_9tree_node ((*x).generic.complex.real);
              gt_ggc_m_9tree_node ((*x).generic.complex.imag);
              break;
            case TS_IDENTIFIER:
              gt_ggc_m_9tree_node ((*x).generic.identifier.common.typed.type);
              gt_ggc_m_9tree_node ((*x).generic.identifier.common.chain);
              gt_ggc_m_S ((*x).generic.identifier.id.str);
              break;
            case TS_DECL_MINIMAL:
              gt_ggc_m_9tree_node ((*x).generic.decl_minimal.common.typed.type);
              gt_ggc_m_9tree_node ((*x).generic.decl_minimal.common.chain);
              gt_ggc_m_9tree_node ((*x).generic.decl_minimal.name);
              gt_ggc_m_9tree_node ((*x).generic.decl_minimal.context);
              break;
            case TS_DECL_COMMON:
              gt_ggc_m_9tree_node ((*x).generic.decl_common.common.common.typed.type);
              gt_ggc_m_9tree_node ((*x).generic.decl_common.common.common.chain);
              gt_ggc_m_9tree_node ((*x).generic.decl_common.common.name);
              gt_ggc_m_9tree_node ((*x).generic.decl_common.common.context);
              gt_ggc_m_9tree_node ((*x).generic.decl_common.size);
              gt_ggc_m_9tree_node ((*x).generic.decl_common.size_unit);
              gt_ggc_m_9tree_node ((*x).generic.decl_common.initial);
              gt_ggc_m_9tree_node ((*x).generic.decl_common.attributes);
              gt_ggc_m_9tree_node ((*x).generic.decl_common.abstract_origin);
              gt_ggc_m_9lang_decl ((*x).generic.decl_common.lang_specific);
              break;
            case TS_DECL_WRTL:
              gt_ggc_m_9tree_node ((*x).generic.decl_with_rtl.common.common.common.typed.type);
              gt_ggc_m_9tree_node ((*x).generic.decl_with_rtl.common.common.common.chain);
              gt_ggc_m_9tree_node ((*x).generic.decl_with_rtl.common.common.name);
              gt_ggc_m_9tree_node ((*x).generic.decl_with_rtl.common.common.context);
              gt_ggc_m_9tree_node ((*x).generic.decl_with_rtl.common.size);
              gt_ggc_m_9tree_node ((*x).generic.decl_with_rtl.common.size_unit);
              gt_ggc_m_9tree_node ((*x).generic.decl_with_rtl.common.initial);
              gt_ggc_m_9tree_node ((*x).generic.decl_with_rtl.common.attributes);
              gt_ggc_m_9tree_node ((*x).generic.decl_with_rtl.common.abstract_origin);
              gt_ggc_m_9lang_decl ((*x).generic.decl_with_rtl.common.lang_specific);
              gt_ggc_m_7rtx_def ((*x).generic.decl_with_rtl.rtl);
              break;
            case TS_DECL_NON_COMMON:
              gt_ggc_m_9tree_node ((*x).generic.decl_non_common.common.common.common.common.common.typed.type);
              gt_ggc_m_9tree_node ((*x).generic.decl_non_common.common.common.common.common.common.chain);
              gt_ggc_m_9tree_node ((*x).generic.decl_non_common.common.common.common.common.name);
              gt_ggc_m_9tree_node ((*x).generic.decl_non_common.common.common.common.common.context);
              gt_ggc_m_9tree_node ((*x).generic.decl_non_common.common.common.common.size);
              gt_ggc_m_9tree_node ((*x).generic.decl_non_common.common.common.common.size_unit);
              gt_ggc_m_9tree_node ((*x).generic.decl_non_common.common.common.common.initial);
              gt_ggc_m_9tree_node ((*x).generic.decl_non_common.common.common.common.attributes);
              gt_ggc_m_9tree_node ((*x).generic.decl_non_common.common.common.common.abstract_origin);
              gt_ggc_m_9lang_decl ((*x).generic.decl_non_common.common.common.common.lang_specific);
              gt_ggc_m_7rtx_def ((*x).generic.decl_non_common.common.common.rtl);
              gt_ggc_m_9tree_node ((*x).generic.decl_non_common.common.assembler_name);
              gt_ggc_m_9tree_node ((*x).generic.decl_non_common.common.section_name);
              gt_ggc_m_9tree_node ((*x).generic.decl_non_common.common.comdat_group);
              gt_ggc_m_9tree_node ((*x).generic.decl_non_common.saved_tree);
              gt_ggc_m_9tree_node ((*x).generic.decl_non_common.arguments);
              gt_ggc_m_9tree_node ((*x).generic.decl_non_common.result);
              gt_ggc_m_9tree_node ((*x).generic.decl_non_common.vindex);
              break;
            case TS_PARM_DECL:
              gt_ggc_m_9tree_node ((*x).generic.parm_decl.common.common.common.common.typed.type);
              gt_ggc_m_9tree_node ((*x).generic.parm_decl.common.common.common.common.chain);
              gt_ggc_m_9tree_node ((*x).generic.parm_decl.common.common.common.name);
              gt_ggc_m_9tree_node ((*x).generic.parm_decl.common.common.common.context);
              gt_ggc_m_9tree_node ((*x).generic.parm_decl.common.common.size);
              gt_ggc_m_9tree_node ((*x).generic.parm_decl.common.common.size_unit);
              gt_ggc_m_9tree_node ((*x).generic.parm_decl.common.common.initial);
              gt_ggc_m_9tree_node ((*x).generic.parm_decl.common.common.attributes);
              gt_ggc_m_9tree_node ((*x).generic.parm_decl.common.common.abstract_origin);
              gt_ggc_m_9lang_decl ((*x).generic.parm_decl.common.common.lang_specific);
              gt_ggc_m_7rtx_def ((*x).generic.parm_decl.common.rtl);
              gt_ggc_m_7rtx_def ((*x).generic.parm_decl.incoming_rtl);
              break;
            case TS_DECL_WITH_VIS:
              gt_ggc_m_9tree_node ((*x).generic.decl_with_vis.common.common.common.common.typed.type);
              gt_ggc_m_9tree_node ((*x).generic.decl_with_vis.common.common.common.common.chain);
              gt_ggc_m_9tree_node ((*x).generic.decl_with_vis.common.common.common.name);
              gt_ggc_m_9tree_node ((*x).generic.decl_with_vis.common.common.common.context);
              gt_ggc_m_9tree_node ((*x).generic.decl_with_vis.common.common.size);
              gt_ggc_m_9tree_node ((*x).generic.decl_with_vis.common.common.size_unit);
              gt_ggc_m_9tree_node ((*x).generic.decl_with_vis.common.common.initial);
              gt_ggc_m_9tree_node ((*x).generic.decl_with_vis.common.common.attributes);
              gt_ggc_m_9tree_node ((*x).generic.decl_with_vis.common.common.abstract_origin);
              gt_ggc_m_9lang_decl ((*x).generic.decl_with_vis.common.common.lang_specific);
              gt_ggc_m_7rtx_def ((*x).generic.decl_with_vis.common.rtl);
              gt_ggc_m_9tree_node ((*x).generic.decl_with_vis.assembler_name);
              gt_ggc_m_9tree_node ((*x).generic.decl_with_vis.section_name);
              gt_ggc_m_9tree_node ((*x).generic.decl_with_vis.comdat_group);
              break;
            case TS_VAR_DECL:
              gt_ggc_m_9tree_node ((*x).generic.var_decl.common.common.common.common.common.typed.type);
              gt_ggc_m_9tree_node ((*x).generic.var_decl.common.common.common.common.common.chain);
              gt_ggc_m_9tree_node ((*x).generic.var_decl.common.common.common.common.name);
              gt_ggc_m_9tree_node ((*x).generic.var_decl.common.common.common.common.context);
              gt_ggc_m_9tree_node ((*x).generic.var_decl.common.common.common.size);
              gt_ggc_m_9tree_node ((*x).generic.var_decl.common.common.common.size_unit);
              gt_ggc_m_9tree_node ((*x).generic.var_decl.common.common.common.initial);
              gt_ggc_m_9tree_node ((*x).generic.var_decl.common.common.common.attributes);
              gt_ggc_m_9tree_node ((*x).generic.var_decl.common.common.common.abstract_origin);
              gt_ggc_m_9lang_decl ((*x).generic.var_decl.common.common.common.lang_specific);
              gt_ggc_m_7rtx_def ((*x).generic.var_decl.common.common.rtl);
              gt_ggc_m_9tree_node ((*x).generic.var_decl.common.assembler_name);
              gt_ggc_m_9tree_node ((*x).generic.var_decl.common.section_name);
              gt_ggc_m_9tree_node ((*x).generic.var_decl.common.comdat_group);
              break;
            case TS_FIELD_DECL:
              gt_ggc_m_9tree_node ((*x).generic.field_decl.common.common.common.typed.type);
              gt_ggc_m_9tree_node ((*x).generic.field_decl.common.common.common.chain);
              gt_ggc_m_9tree_node ((*x).generic.field_decl.common.common.name);
              gt_ggc_m_9tree_node ((*x).generic.field_decl.common.common.context);
              gt_ggc_m_9tree_node ((*x).generic.field_decl.common.size);
              gt_ggc_m_9tree_node ((*x).generic.field_decl.common.size_unit);
              gt_ggc_m_9tree_node ((*x).generic.field_decl.common.initial);
              gt_ggc_m_9tree_node ((*x).generic.field_decl.common.attributes);
              gt_ggc_m_9tree_node ((*x).generic.field_decl.common.abstract_origin);
              gt_ggc_m_9lang_decl ((*x).generic.field_decl.common.lang_specific);
              gt_ggc_m_9tree_node ((*x).generic.field_decl.offset);
              gt_ggc_m_9tree_node ((*x).generic.field_decl.bit_field_type);
              gt_ggc_m_9tree_node ((*x).generic.field_decl.qualifier);
              gt_ggc_m_9tree_node ((*x).generic.field_decl.bit_offset);
              gt_ggc_m_9tree_node ((*x).generic.field_decl.fcontext);
              break;
            case TS_LABEL_DECL:
              gt_ggc_m_9tree_node ((*x).generic.label_decl.common.common.common.common.typed.type);
              gt_ggc_m_9tree_node ((*x).generic.label_decl.common.common.common.common.chain);
              gt_ggc_m_9tree_node ((*x).generic.label_decl.common.common.common.name);
              gt_ggc_m_9tree_node ((*x).generic.label_decl.common.common.common.context);
              gt_ggc_m_9tree_node ((*x).generic.label_decl.common.common.size);
              gt_ggc_m_9tree_node ((*x).generic.label_decl.common.common.size_unit);
              gt_ggc_m_9tree_node ((*x).generic.label_decl.common.common.initial);
              gt_ggc_m_9tree_node ((*x).generic.label_decl.common.common.attributes);
              gt_ggc_m_9tree_node ((*x).generic.label_decl.common.common.abstract_origin);
              gt_ggc_m_9lang_decl ((*x).generic.label_decl.common.common.lang_specific);
              gt_ggc_m_7rtx_def ((*x).generic.label_decl.common.rtl);
              break;
            case TS_RESULT_DECL:
              gt_ggc_m_9tree_node ((*x).generic.result_decl.common.common.common.common.typed.type);
              gt_ggc_m_9tree_node ((*x).generic.result_decl.common.common.common.common.chain);
              gt_ggc_m_9tree_node ((*x).generic.result_decl.common.common.common.name);
              gt_ggc_m_9tree_node ((*x).generic.result_decl.common.common.common.context);
              gt_ggc_m_9tree_node ((*x).generic.result_decl.common.common.size);
              gt_ggc_m_9tree_node ((*x).generic.result_decl.common.common.size_unit);
              gt_ggc_m_9tree_node ((*x).generic.result_decl.common.common.initial);
              gt_ggc_m_9tree_node ((*x).generic.result_decl.common.common.attributes);
              gt_ggc_m_9tree_node ((*x).generic.result_decl.common.common.abstract_origin);
              gt_ggc_m_9lang_decl ((*x).generic.result_decl.common.common.lang_specific);
              gt_ggc_m_7rtx_def ((*x).generic.result_decl.common.rtl);
              break;
            case TS_CONST_DECL:
              gt_ggc_m_9tree_node ((*x).generic.const_decl.common.common.common.typed.type);
              gt_ggc_m_9tree_node ((*x).generic.const_decl.common.common.common.chain);
              gt_ggc_m_9tree_node ((*x).generic.const_decl.common.common.name);
              gt_ggc_m_9tree_node ((*x).generic.const_decl.common.common.context);
              gt_ggc_m_9tree_node ((*x).generic.const_decl.common.size);
              gt_ggc_m_9tree_node ((*x).generic.const_decl.common.size_unit);
              gt_ggc_m_9tree_node ((*x).generic.const_decl.common.initial);
              gt_ggc_m_9tree_node ((*x).generic.const_decl.common.attributes);
              gt_ggc_m_9tree_node ((*x).generic.const_decl.common.abstract_origin);
              gt_ggc_m_9lang_decl ((*x).generic.const_decl.common.lang_specific);
              break;
            case TS_TYPE_DECL:
              gt_ggc_m_9tree_node ((*x).generic.type_decl.common.common.common.common.common.common.typed.type);
              gt_ggc_m_9tree_node ((*x).generic.type_decl.common.common.common.common.common.common.chain);
              gt_ggc_m_9tree_node ((*x).generic.type_decl.common.common.common.common.common.name);
              gt_ggc_m_9tree_node ((*x).generic.type_decl.common.common.common.common.common.context);
              gt_ggc_m_9tree_node ((*x).generic.type_decl.common.common.common.common.size);
              gt_ggc_m_9tree_node ((*x).generic.type_decl.common.common.common.common.size_unit);
              gt_ggc_m_9tree_node ((*x).generic.type_decl.common.common.common.common.initial);
              gt_ggc_m_9tree_node ((*x).generic.type_decl.common.common.common.common.attributes);
              gt_ggc_m_9tree_node ((*x).generic.type_decl.common.common.common.common.abstract_origin);
              gt_ggc_m_9lang_decl ((*x).generic.type_decl.common.common.common.common.lang_specific);
              gt_ggc_m_7rtx_def ((*x).generic.type_decl.common.common.common.rtl);
              gt_ggc_m_9tree_node ((*x).generic.type_decl.common.common.assembler_name);
              gt_ggc_m_9tree_node ((*x).generic.type_decl.common.common.section_name);
              gt_ggc_m_9tree_node ((*x).generic.type_decl.common.common.comdat_group);
              gt_ggc_m_9tree_node ((*x).generic.type_decl.common.saved_tree);
              gt_ggc_m_9tree_node ((*x).generic.type_decl.common.arguments);
              gt_ggc_m_9tree_node ((*x).generic.type_decl.common.result);
              gt_ggc_m_9tree_node ((*x).generic.type_decl.common.vindex);
              break;
            case TS_FUNCTION_DECL:
              gt_ggc_m_9tree_node ((*x).generic.function_decl.common.common.common.common.common.common.typed.type);
              gt_ggc_m_9tree_node ((*x).generic.function_decl.common.common.common.common.common.common.chain);
              gt_ggc_m_9tree_node ((*x).generic.function_decl.common.common.common.common.common.name);
              gt_ggc_m_9tree_node ((*x).generic.function_decl.common.common.common.common.common.context);
              gt_ggc_m_9tree_node ((*x).generic.function_decl.common.common.common.common.size);
              gt_ggc_m_9tree_node ((*x).generic.function_decl.common.common.common.common.size_unit);
              gt_ggc_m_9tree_node ((*x).generic.function_decl.common.common.common.common.initial);
              gt_ggc_m_9tree_node ((*x).generic.function_decl.common.common.common.common.attributes);
              gt_ggc_m_9tree_node ((*x).generic.function_decl.common.common.common.common.abstract_origin);
              gt_ggc_m_9lang_decl ((*x).generic.function_decl.common.common.common.common.lang_specific);
              gt_ggc_m_7rtx_def ((*x).generic.function_decl.common.common.common.rtl);
              gt_ggc_m_9tree_node ((*x).generic.function_decl.common.common.assembler_name);
              gt_ggc_m_9tree_node ((*x).generic.function_decl.common.common.section_name);
              gt_ggc_m_9tree_node ((*x).generic.function_decl.common.common.comdat_group);
              gt_ggc_m_9tree_node ((*x).generic.function_decl.common.saved_tree);
              gt_ggc_m_9tree_node ((*x).generic.function_decl.common.arguments);
              gt_ggc_m_9tree_node ((*x).generic.function_decl.common.result);
              gt_ggc_m_9tree_node ((*x).generic.function_decl.common.vindex);
              gt_ggc_m_8function ((*x).generic.function_decl.f);
              gt_ggc_m_9tree_node ((*x).generic.function_decl.personality);
              gt_ggc_m_9tree_node ((*x).generic.function_decl.function_specific_target);
              gt_ggc_m_9tree_node ((*x).generic.function_decl.function_specific_optimization);
              break;
            case TS_TRANSLATION_UNIT_DECL:
              gt_ggc_m_9tree_node ((*x).generic.translation_unit_decl.common.common.common.typed.type);
              gt_ggc_m_9tree_node ((*x).generic.translation_unit_decl.common.common.common.chain);
              gt_ggc_m_9tree_node ((*x).generic.translation_unit_decl.common.common.name);
              gt_ggc_m_9tree_node ((*x).generic.translation_unit_decl.common.common.context);
              gt_ggc_m_9tree_node ((*x).generic.translation_unit_decl.common.size);
              gt_ggc_m_9tree_node ((*x).generic.translation_unit_decl.common.size_unit);
              gt_ggc_m_9tree_node ((*x).generic.translation_unit_decl.common.initial);
              gt_ggc_m_9tree_node ((*x).generic.translation_unit_decl.common.attributes);
              gt_ggc_m_9tree_node ((*x).generic.translation_unit_decl.common.abstract_origin);
              gt_ggc_m_9lang_decl ((*x).generic.translation_unit_decl.common.lang_specific);
              break;
            case TS_TYPE_COMMON:
              gt_ggc_m_9tree_node ((*x).generic.type_common.common.typed.type);
              gt_ggc_m_9tree_node ((*x).generic.type_common.common.chain);
              gt_ggc_m_9tree_node ((*x).generic.type_common.size);
              gt_ggc_m_9tree_node ((*x).generic.type_common.size_unit);
              gt_ggc_m_9tree_node ((*x).generic.type_common.attributes);
              gt_ggc_m_9tree_node ((*x).generic.type_common.pointer_to);
              gt_ggc_m_9tree_node ((*x).generic.type_common.reference_to);
              switch (debug_hooks->tree_type_symtab_field)
                {
                case TYPE_SYMTAB_IS_ADDRESS:
                  break;
                case TYPE_SYMTAB_IS_POINTER:
                  gt_ggc_m_S ((*x).generic.type_common.symtab.pointer);
                  break;
                case TYPE_SYMTAB_IS_DIE:
                  gt_ggc_m_10die_struct ((*x).generic.type_common.symtab.die);
                  break;
                default:
                  break;
                }
              gt_ggc_m_9tree_node ((*x).generic.type_common.name);
              gt_ggc_m_9tree_node ((*x).generic.type_common.next_variant);
              gt_ggc_m_9tree_node ((*x).generic.type_common.main_variant);
              gt_ggc_m_9tree_node ((*x).generic.type_common.context);
              gt_ggc_m_9tree_node ((*x).generic.type_common.canonical);
              break;
            case TS_TYPE_WITH_LANG_SPECIFIC:
              gt_ggc_m_9tree_node ((*x).generic.type_with_lang_specific.common.common.typed.type);
              gt_ggc_m_9tree_node ((*x).generic.type_with_lang_specific.common.common.chain);
              gt_ggc_m_9tree_node ((*x).generic.type_with_lang_specific.common.size);
              gt_ggc_m_9tree_node ((*x).generic.type_with_lang_specific.common.size_unit);
              gt_ggc_m_9tree_node ((*x).generic.type_with_lang_specific.common.attributes);
              gt_ggc_m_9tree_node ((*x).generic.type_with_lang_specific.common.pointer_to);
              gt_ggc_m_9tree_node ((*x).generic.type_with_lang_specific.common.reference_to);
              switch (debug_hooks->tree_type_symtab_field)
                {
                case TYPE_SYMTAB_IS_ADDRESS:
                  break;
                case TYPE_SYMTAB_IS_POINTER:
                  gt_ggc_m_S ((*x).generic.type_with_lang_specific.common.symtab.pointer);
                  break;
                case TYPE_SYMTAB_IS_DIE:
                  gt_ggc_m_10die_struct ((*x).generic.type_with_lang_specific.common.symtab.die);
                  break;
                default:
                  break;
                }
              gt_ggc_m_9tree_node ((*x).generic.type_with_lang_specific.common.name);
              gt_ggc_m_9tree_node ((*x).generic.type_with_lang_specific.common.next_variant);
              gt_ggc_m_9tree_node ((*x).generic.type_with_lang_specific.common.main_variant);
              gt_ggc_m_9tree_node ((*x).generic.type_with_lang_specific.common.context);
              gt_ggc_m_9tree_node ((*x).generic.type_with_lang_specific.common.canonical);
              gt_ggc_m_9lang_type ((*x).generic.type_with_lang_specific.lang_specific);
              break;
            case TS_TYPE_NON_COMMON:
              gt_ggc_m_9tree_node ((*x).generic.type_non_common.with_lang_specific.common.common.typed.type);
              gt_ggc_m_9tree_node ((*x).generic.type_non_common.with_lang_specific.common.common.chain);
              gt_ggc_m_9tree_node ((*x).generic.type_non_common.with_lang_specific.common.size);
              gt_ggc_m_9tree_node ((*x).generic.type_non_common.with_lang_specific.common.size_unit);
              gt_ggc_m_9tree_node ((*x).generic.type_non_common.with_lang_specific.common.attributes);
              gt_ggc_m_9tree_node ((*x).generic.type_non_common.with_lang_specific.common.pointer_to);
              gt_ggc_m_9tree_node ((*x).generic.type_non_common.with_lang_specific.common.reference_to);
              switch (debug_hooks->tree_type_symtab_field)
                {
                case TYPE_SYMTAB_IS_ADDRESS:
                  break;
                case TYPE_SYMTAB_IS_POINTER:
                  gt_ggc_m_S ((*x).generic.type_non_common.with_lang_specific.common.symtab.pointer);
                  break;
                case TYPE_SYMTAB_IS_DIE:
                  gt_ggc_m_10die_struct ((*x).generic.type_non_common.with_lang_specific.common.symtab.die);
                  break;
                default:
                  break;
                }
              gt_ggc_m_9tree_node ((*x).generic.type_non_common.with_lang_specific.common.name);
              gt_ggc_m_9tree_node ((*x).generic.type_non_common.with_lang_specific.common.next_variant);
              gt_ggc_m_9tree_node ((*x).generic.type_non_common.with_lang_specific.common.main_variant);
              gt_ggc_m_9tree_node ((*x).generic.type_non_common.with_lang_specific.common.context);
              gt_ggc_m_9tree_node ((*x).generic.type_non_common.with_lang_specific.common.canonical);
              gt_ggc_m_9lang_type ((*x).generic.type_non_common.with_lang_specific.lang_specific);
              gt_ggc_m_9tree_node ((*x).generic.type_non_common.values);
              gt_ggc_m_9tree_node ((*x).generic.type_non_common.minval);
              gt_ggc_m_9tree_node ((*x).generic.type_non_common.maxval);
              gt_ggc_m_9tree_node ((*x).generic.type_non_common.binfo);
              break;
            case TS_LIST:
              gt_ggc_m_9tree_node ((*x).generic.list.common.typed.type);
              gt_ggc_m_9tree_node ((*x).generic.list.common.chain);
              gt_ggc_m_9tree_node ((*x).generic.list.purpose);
              gt_ggc_m_9tree_node ((*x).generic.list.value);
              break;
            case TS_VEC:
              {
                size_t l1 = (size_t)(TREE_VEC_LENGTH ((tree)&((*x).generic.vec)));
                gt_ggc_m_9tree_node ((*x).generic.vec.common.typed.type);
                gt_ggc_m_9tree_node ((*x).generic.vec.common.chain);
                {
                  size_t i1;
                  for (i1 = 0; i1 != l1; i1++) {
                    gt_ggc_m_9tree_node ((*x).generic.vec.a[i1]);
                  }
                }
              }
              break;
            case TS_EXP:
              gt_ggc_m_9tree_node ((*x).generic.exp.typed.type);
              switch (TREE_CODE ((tree) &(*x)))
                {
                default:
                  {
                    size_t i2;
                    size_t l2 = (size_t)(TREE_OPERAND_LENGTH ((tree) &(*x)));
                    for (i2 = 0; i2 != l2; i2++) {
                      gt_ggc_m_9tree_node ((*x).generic.exp.operands[i2]);
                    }
                  }
                  break;
                }
              break;
            case TS_SSA_NAME:
              gt_ggc_m_9tree_node ((*x).generic.ssa_name.typed.type);
              gt_ggc_m_9tree_node ((*x).generic.ssa_name.var);
              gt_ggc_m_18gimple_statement_d ((*x).generic.ssa_name.def_stmt);
              gt_ggc_m_12ptr_info_def ((*x).generic.ssa_name.ptr_info);
              break;
            case TS_BLOCK:
              gt_ggc_m_9tree_node ((*x).generic.block.chain);
              gt_ggc_m_9tree_node ((*x).generic.block.vars);
              gt_ggc_m_15vec_tree_va_gc_ ((*x).generic.block.nonlocalized_vars);
              gt_ggc_m_9tree_node ((*x).generic.block.subblocks);
              gt_ggc_m_9tree_node ((*x).generic.block.supercontext);
              gt_ggc_m_9tree_node ((*x).generic.block.abstract_origin);
              gt_ggc_m_9tree_node ((*x).generic.block.fragment_origin);
              gt_ggc_m_9tree_node ((*x).generic.block.fragment_chain);
              break;
            case TS_BINFO:
              gt_ggc_m_9tree_node ((*x).generic.binfo.common.typed.type);
              gt_ggc_m_9tree_node ((*x).generic.binfo.common.chain);
              gt_ggc_m_9tree_node ((*x).generic.binfo.offset);
              gt_ggc_m_9tree_node ((*x).generic.binfo.vtable);
              gt_ggc_m_9tree_node ((*x).generic.binfo.virtuals);
              gt_ggc_m_9tree_node ((*x).generic.binfo.vptr_field);
              gt_ggc_m_15vec_tree_va_gc_ ((*x).generic.binfo.base_accesses);
              gt_ggc_m_9tree_node ((*x).generic.binfo.inheritance);
              gt_ggc_m_9tree_node ((*x).generic.binfo.vtt_subvtt);
              gt_ggc_m_9tree_node ((*x).generic.binfo.vtt_vptr);
              gt_ggc_mx (&((*x).generic.binfo.base_binfos));
              break;
            case TS_STATEMENT_LIST:
              gt_ggc_m_9tree_node ((*x).generic.stmt_list.typed.type);
              gt_ggc_m_24tree_statement_list_node ((*x).generic.stmt_list.head);
              gt_ggc_m_24tree_statement_list_node ((*x).generic.stmt_list.tail);
              break;
            case TS_CONSTRUCTOR:
              gt_ggc_m_9tree_node ((*x).generic.constructor.typed.type);
              gt_ggc_m_26vec_constructor_elt_va_gc_ ((*x).generic.constructor.elts);
              break;
            case TS_OMP_CLAUSE:
              {
                size_t l3 = (size_t)(omp_clause_num_ops[OMP_CLAUSE_CODE ((tree)&((*x).generic.omp_clause))]);
                gt_ggc_m_9tree_node ((*x).generic.omp_clause.common.typed.type);
                gt_ggc_m_9tree_node ((*x).generic.omp_clause.common.chain);
                gt_ggc_m_18gimple_statement_d ((*x).generic.omp_clause.gimple_reduction_init);
                gt_ggc_m_18gimple_statement_d ((*x).generic.omp_clause.gimple_reduction_merge);
                {
                  size_t i3;
                  for (i3 = 0; i3 != l3; i3++) {
                    gt_ggc_m_9tree_node ((*x).generic.omp_clause.ops[i3]);
                  }
                }
              }
              break;
            case TS_OPTIMIZATION:
              gt_ggc_m_9tree_node ((*x).generic.optimization.common.typed.type);
              gt_ggc_m_9tree_node ((*x).generic.optimization.common.chain);
              gt_ggc_m_S ((*x).generic.optimization.optabs);
              break;
            case TS_TARGET_OPTION:
              gt_ggc_m_9tree_node ((*x).generic.target_option.common.typed.type);
              gt_ggc_m_9tree_node ((*x).generic.target_option.common.chain);
              break;
            default:
              break;
            }
          break;
        case 1:
          gt_ggc_m_9tree_node ((*x).identifier.ignore.common.typed.type);
          gt_ggc_m_9tree_node ((*x).identifier.ignore.common.chain);
          gt_ggc_m_S ((*x).identifier.ignore.id.str);
          gt_ggc_m_9tree_node ((*x).identifier.global_value);
          gt_ggc_m_9tree_node ((*x).identifier.local_value);
          gt_ggc_m_9tree_node ((*x).identifier.utf8_ref);
          break;
        default:
          break;
        }
      x = (CODE_CONTAINS_STRUCT (TREE_CODE (&(*x).generic), TS_COMMON) ? ((union lang_tree_node *) TREE_CHAIN (&(*x).generic)) : NULL);
    }
}

void
gt_ggc_mx_lang_decl (void *x_p)
{
  struct lang_decl * const x = (struct lang_decl *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      switch ((*x).desc)
        {
        case LANG_DECL_FUNC:
          gt_ggc_m_15vec_tree_va_gc_ ((*x).u.f.throws_list);
          gt_ggc_m_9tree_node ((*x).u.f.exc_obj);
          gt_ggc_m_P18treetreehash_entry4htab ((*x).u.f.init_test_table);
          gt_ggc_m_P9tree_node4htab ((*x).u.f.ict);
          break;
        case LANG_DECL_VAR:
          gt_ggc_m_9tree_node ((*x).u.v.slot_chain);
          gt_ggc_m_9tree_node ((*x).u.v.owner);
          break;
        default:
          break;
        }
    }
}

void
gt_ggc_mx_lang_type (void *x_p)
{
  struct lang_type * const x = (struct lang_type *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_9tree_node ((*x).signature);
      gt_ggc_m_3JCF ((*x).jcf);
      gt_ggc_m_5CPool ((*x).cpool);
      gt_ggc_m_9tree_node ((*x).cpool_data_ref);
      gt_ggc_m_9tree_node ((*x).package_list);
      gt_ggc_m_23vec_method_entry_va_gc_ ((*x).otable_methods);
      gt_ggc_m_9tree_node ((*x).otable_decl);
      gt_ggc_m_9tree_node ((*x).otable_syms_decl);
      gt_ggc_m_23vec_method_entry_va_gc_ ((*x).atable_methods);
      gt_ggc_m_9tree_node ((*x).atable_decl);
      gt_ggc_m_9tree_node ((*x).atable_syms_decl);
      gt_ggc_m_23vec_method_entry_va_gc_ ((*x).itable_methods);
      gt_ggc_m_9tree_node ((*x).itable_decl);
      gt_ggc_m_9tree_node ((*x).itable_syms_decl);
      gt_ggc_m_9tree_node ((*x).ctable_decl);
      gt_ggc_m_26vec_constructor_elt_va_gc_ ((*x).catch_classes);
      gt_ggc_m_P18treetreehash_entry4htab ((*x).type_to_runtime_map);
      gt_ggc_m_P14type_assertion4htab ((*x).type_assertions);
      gt_ggc_m_9tree_node ((*x).package);
    }
}

void
gt_ggc_m_P14type_assertion4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      {
        size_t l0 = (size_t)(((*x)).size);
        if ((*x).entries != NULL) {
          size_t i0;
          for (i0 = 0; i0 != (size_t)(l0); i0++) {
            gt_ggc_m_14type_assertion ((*x).entries[i0]);
          }
          ggc_mark ((*x).entries);
        }
      }
    }
}

void
gt_ggc_m_P18treetreehash_entry4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      {
        size_t l0 = (size_t)(((*x)).size);
        if ((*x).entries != NULL) {
          size_t i0;
          for (i0 = 0; i0 != (size_t)(l0); i0++) {
            gt_ggc_m_18treetreehash_entry ((*x).entries[i0]);
          }
          ggc_mark ((*x).entries);
        }
      }
    }
}

void
gt_pch_nx_vec_method_entry_va_gc_ (void *x_p)
{
  vec<method_entry,va_gc> * const x = (vec<method_entry,va_gc> *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_23vec_method_entry_va_gc_))
    {
      gt_pch_nx (x);
    }
}

void
gt_pch_nx (struct method_entry_d& x_r ATTRIBUTE_UNUSED)
{
  struct method_entry_d * ATTRIBUTE_UNUSED x = &x_r;
  gt_pch_n_9tree_node ((*x).method);
  gt_pch_n_9tree_node ((*x).special);
}

void
gt_pch_nx_type_assertion (void *x_p)
{
  struct type_assertion * const x = (struct type_assertion *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_14type_assertion))
    {
      gt_pch_n_9tree_node ((*x).op1);
      gt_pch_n_9tree_node ((*x).op2);
    }
}

void
gt_pch_nx_treetreehash_entry (void *x_p)
{
  struct treetreehash_entry * const x = (struct treetreehash_entry *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_18treetreehash_entry))
    {
      gt_pch_n_9tree_node ((*x).key);
      gt_pch_n_9tree_node ((*x).value);
    }
}

void
gt_pch_nx_CPool (void *x_p)
{
  struct CPool * const x = (struct CPool *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_5CPool))
    {
      {
        size_t l0 = (size_t)(((*x)).count);
        if ((*x).tags != NULL) {
          gt_pch_note_object ((*x).tags, x, gt_pch_p_5CPool);
        }
        if ((*x).data != NULL) {
          size_t i0;
          for (i0 = 0; i0 != (size_t)(l0); i0++) {
            switch (cpool_entry_is_tree (((*x)).tags[i0]))
              {
              case 0:
                break;
              case 1:
                gt_pch_n_9tree_node ((*x).data[i0].t);
                break;
              default:
                break;
              }
          }
          gt_pch_note_object ((*x).data, x, gt_pch_p_5CPool);
        }
      }
    }
}

void
gt_pch_nx_JCF (void *x_p)
{
  struct JCF * const x = (struct JCF *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_3JCF))
    {
      gt_pch_n_S ((*x).filename);
      gt_pch_n_S ((*x).classname);
      {
        size_t l0 = (size_t)(((*x).cpool).count);
        if ((*x).cpool.tags != NULL) {
          gt_pch_note_object ((*x).cpool.tags, x, gt_pch_p_3JCF);
        }
        if ((*x).cpool.data != NULL) {
          size_t i0;
          for (i0 = 0; i0 != (size_t)(l0); i0++) {
            switch (cpool_entry_is_tree (((*x).cpool).tags[i0]))
              {
              case 0:
                break;
              case 1:
                gt_pch_n_9tree_node ((*x).cpool.data[i0].t);
                break;
              default:
                break;
              }
          }
          gt_pch_note_object ((*x).cpool.data, x, gt_pch_p_3JCF);
        }
      }
      {
        size_t l1 = (size_t)(((*x).bootstrap_methods).count);
        if ((*x).bootstrap_methods.methods != NULL) {
          size_t i1;
          for (i1 = 0; i1 != (size_t)(l1); i1++) {
            if ((*x).bootstrap_methods.methods[i1].bootstrap_arguments != NULL) {
              gt_pch_note_object ((*x).bootstrap_methods.methods[i1].bootstrap_arguments, x, gt_pch_p_3JCF);
            }
          }
          gt_pch_note_object ((*x).bootstrap_methods.methods, x, gt_pch_p_3JCF);
        }
      }
    }
}

void
gt_pch_nx_lang_tree_node (void *x_p)
{
  union lang_tree_node * x = (union lang_tree_node *)x_p;
  union lang_tree_node * xlimit = x;
  while (gt_pch_note_object (xlimit, xlimit, gt_pch_p_14lang_tree_node))
   xlimit = (CODE_CONTAINS_STRUCT (TREE_CODE (&(*xlimit).generic), TS_COMMON) ? ((union lang_tree_node *) TREE_CHAIN (&(*xlimit).generic)) : NULL);
  while (x != xlimit)
    {
      switch (TREE_CODE (&((*x)).generic) == IDENTIFIER_NODE)
        {
        case 0:
          switch (tree_node_structure (&((*x).generic)))
            {
            case TS_BASE:
              break;
            case TS_TYPED:
              gt_pch_n_9tree_node ((*x).generic.typed.type);
              break;
            case TS_COMMON:
              gt_pch_n_9tree_node ((*x).generic.common.typed.type);
              gt_pch_n_9tree_node ((*x).generic.common.chain);
              break;
            case TS_INT_CST:
              gt_pch_n_9tree_node ((*x).generic.int_cst.typed.type);
              break;
            case TS_REAL_CST:
              gt_pch_n_9tree_node ((*x).generic.real_cst.typed.type);
              gt_pch_n_10real_value ((*x).generic.real_cst.real_cst_ptr);
              break;
            case TS_FIXED_CST:
              gt_pch_n_9tree_node ((*x).generic.fixed_cst.typed.type);
              gt_pch_n_11fixed_value ((*x).generic.fixed_cst.fixed_cst_ptr);
              break;
            case TS_VECTOR:
              {
                size_t l0 = (size_t)(TYPE_VECTOR_SUBPARTS (TREE_TYPE ((tree)&((*x).generic.vector))));
                gt_pch_n_9tree_node ((*x).generic.vector.typed.type);
                {
                  size_t i0;
                  for (i0 = 0; i0 != l0; i0++) {
                    gt_pch_n_9tree_node ((*x).generic.vector.elts[i0]);
                  }
                }
              }
              break;
            case TS_STRING:
              gt_pch_n_9tree_node ((*x).generic.string.typed.type);
              break;
            case TS_COMPLEX:
              gt_pch_n_9tree_node ((*x).generic.complex.typed.type);
              gt_pch_n_9tree_node ((*x).generic.complex.real);
              gt_pch_n_9tree_node ((*x).generic.complex.imag);
              break;
            case TS_IDENTIFIER:
              gt_pch_n_9tree_node ((*x).generic.identifier.common.typed.type);
              gt_pch_n_9tree_node ((*x).generic.identifier.common.chain);
              gt_pch_n_S ((*x).generic.identifier.id.str);
              break;
            case TS_DECL_MINIMAL:
              gt_pch_n_9tree_node ((*x).generic.decl_minimal.common.typed.type);
              gt_pch_n_9tree_node ((*x).generic.decl_minimal.common.chain);
              gt_pch_n_9tree_node ((*x).generic.decl_minimal.name);
              gt_pch_n_9tree_node ((*x).generic.decl_minimal.context);
              break;
            case TS_DECL_COMMON:
              gt_pch_n_9tree_node ((*x).generic.decl_common.common.common.typed.type);
              gt_pch_n_9tree_node ((*x).generic.decl_common.common.common.chain);
              gt_pch_n_9tree_node ((*x).generic.decl_common.common.name);
              gt_pch_n_9tree_node ((*x).generic.decl_common.common.context);
              gt_pch_n_9tree_node ((*x).generic.decl_common.size);
              gt_pch_n_9tree_node ((*x).generic.decl_common.size_unit);
              gt_pch_n_9tree_node ((*x).generic.decl_common.initial);
              gt_pch_n_9tree_node ((*x).generic.decl_common.attributes);
              gt_pch_n_9tree_node ((*x).generic.decl_common.abstract_origin);
              gt_pch_n_9lang_decl ((*x).generic.decl_common.lang_specific);
              break;
            case TS_DECL_WRTL:
              gt_pch_n_9tree_node ((*x).generic.decl_with_rtl.common.common.common.typed.type);
              gt_pch_n_9tree_node ((*x).generic.decl_with_rtl.common.common.common.chain);
              gt_pch_n_9tree_node ((*x).generic.decl_with_rtl.common.common.name);
              gt_pch_n_9tree_node ((*x).generic.decl_with_rtl.common.common.context);
              gt_pch_n_9tree_node ((*x).generic.decl_with_rtl.common.size);
              gt_pch_n_9tree_node ((*x).generic.decl_with_rtl.common.size_unit);
              gt_pch_n_9tree_node ((*x).generic.decl_with_rtl.common.initial);
              gt_pch_n_9tree_node ((*x).generic.decl_with_rtl.common.attributes);
              gt_pch_n_9tree_node ((*x).generic.decl_with_rtl.common.abstract_origin);
              gt_pch_n_9lang_decl ((*x).generic.decl_with_rtl.common.lang_specific);
              gt_pch_n_7rtx_def ((*x).generic.decl_with_rtl.rtl);
              break;
            case TS_DECL_NON_COMMON:
              gt_pch_n_9tree_node ((*x).generic.decl_non_common.common.common.common.common.common.typed.type);
              gt_pch_n_9tree_node ((*x).generic.decl_non_common.common.common.common.common.common.chain);
              gt_pch_n_9tree_node ((*x).generic.decl_non_common.common.common.common.common.name);
              gt_pch_n_9tree_node ((*x).generic.decl_non_common.common.common.common.common.context);
              gt_pch_n_9tree_node ((*x).generic.decl_non_common.common.common.common.size);
              gt_pch_n_9tree_node ((*x).generic.decl_non_common.common.common.common.size_unit);
              gt_pch_n_9tree_node ((*x).generic.decl_non_common.common.common.common.initial);
              gt_pch_n_9tree_node ((*x).generic.decl_non_common.common.common.common.attributes);
              gt_pch_n_9tree_node ((*x).generic.decl_non_common.common.common.common.abstract_origin);
              gt_pch_n_9lang_decl ((*x).generic.decl_non_common.common.common.common.lang_specific);
              gt_pch_n_7rtx_def ((*x).generic.decl_non_common.common.common.rtl);
              gt_pch_n_9tree_node ((*x).generic.decl_non_common.common.assembler_name);
              gt_pch_n_9tree_node ((*x).generic.decl_non_common.common.section_name);
              gt_pch_n_9tree_node ((*x).generic.decl_non_common.common.comdat_group);
              gt_pch_n_9tree_node ((*x).generic.decl_non_common.saved_tree);
              gt_pch_n_9tree_node ((*x).generic.decl_non_common.arguments);
              gt_pch_n_9tree_node ((*x).generic.decl_non_common.result);
              gt_pch_n_9tree_node ((*x).generic.decl_non_common.vindex);
              break;
            case TS_PARM_DECL:
              gt_pch_n_9tree_node ((*x).generic.parm_decl.common.common.common.common.typed.type);
              gt_pch_n_9tree_node ((*x).generic.parm_decl.common.common.common.common.chain);
              gt_pch_n_9tree_node ((*x).generic.parm_decl.common.common.common.name);
              gt_pch_n_9tree_node ((*x).generic.parm_decl.common.common.common.context);
              gt_pch_n_9tree_node ((*x).generic.parm_decl.common.common.size);
              gt_pch_n_9tree_node ((*x).generic.parm_decl.common.common.size_unit);
              gt_pch_n_9tree_node ((*x).generic.parm_decl.common.common.initial);
              gt_pch_n_9tree_node ((*x).generic.parm_decl.common.common.attributes);
              gt_pch_n_9tree_node ((*x).generic.parm_decl.common.common.abstract_origin);
              gt_pch_n_9lang_decl ((*x).generic.parm_decl.common.common.lang_specific);
              gt_pch_n_7rtx_def ((*x).generic.parm_decl.common.rtl);
              gt_pch_n_7rtx_def ((*x).generic.parm_decl.incoming_rtl);
              break;
            case TS_DECL_WITH_VIS:
              gt_pch_n_9tree_node ((*x).generic.decl_with_vis.common.common.common.common.typed.type);
              gt_pch_n_9tree_node ((*x).generic.decl_with_vis.common.common.common.common.chain);
              gt_pch_n_9tree_node ((*x).generic.decl_with_vis.common.common.common.name);
              gt_pch_n_9tree_node ((*x).generic.decl_with_vis.common.common.common.context);
              gt_pch_n_9tree_node ((*x).generic.decl_with_vis.common.common.size);
              gt_pch_n_9tree_node ((*x).generic.decl_with_vis.common.common.size_unit);
              gt_pch_n_9tree_node ((*x).generic.decl_with_vis.common.common.initial);
              gt_pch_n_9tree_node ((*x).generic.decl_with_vis.common.common.attributes);
              gt_pch_n_9tree_node ((*x).generic.decl_with_vis.common.common.abstract_origin);
              gt_pch_n_9lang_decl ((*x).generic.decl_with_vis.common.common.lang_specific);
              gt_pch_n_7rtx_def ((*x).generic.decl_with_vis.common.rtl);
              gt_pch_n_9tree_node ((*x).generic.decl_with_vis.assembler_name);
              gt_pch_n_9tree_node ((*x).generic.decl_with_vis.section_name);
              gt_pch_n_9tree_node ((*x).generic.decl_with_vis.comdat_group);
              break;
            case TS_VAR_DECL:
              gt_pch_n_9tree_node ((*x).generic.var_decl.common.common.common.common.common.typed.type);
              gt_pch_n_9tree_node ((*x).generic.var_decl.common.common.common.common.common.chain);
              gt_pch_n_9tree_node ((*x).generic.var_decl.common.common.common.common.name);
              gt_pch_n_9tree_node ((*x).generic.var_decl.common.common.common.common.context);
              gt_pch_n_9tree_node ((*x).generic.var_decl.common.common.common.size);
              gt_pch_n_9tree_node ((*x).generic.var_decl.common.common.common.size_unit);
              gt_pch_n_9tree_node ((*x).generic.var_decl.common.common.common.initial);
              gt_pch_n_9tree_node ((*x).generic.var_decl.common.common.common.attributes);
              gt_pch_n_9tree_node ((*x).generic.var_decl.common.common.common.abstract_origin);
              gt_pch_n_9lang_decl ((*x).generic.var_decl.common.common.common.lang_specific);
              gt_pch_n_7rtx_def ((*x).generic.var_decl.common.common.rtl);
              gt_pch_n_9tree_node ((*x).generic.var_decl.common.assembler_name);
              gt_pch_n_9tree_node ((*x).generic.var_decl.common.section_name);
              gt_pch_n_9tree_node ((*x).generic.var_decl.common.comdat_group);
              break;
            case TS_FIELD_DECL:
              gt_pch_n_9tree_node ((*x).generic.field_decl.common.common.common.typed.type);
              gt_pch_n_9tree_node ((*x).generic.field_decl.common.common.common.chain);
              gt_pch_n_9tree_node ((*x).generic.field_decl.common.common.name);
              gt_pch_n_9tree_node ((*x).generic.field_decl.common.common.context);
              gt_pch_n_9tree_node ((*x).generic.field_decl.common.size);
              gt_pch_n_9tree_node ((*x).generic.field_decl.common.size_unit);
              gt_pch_n_9tree_node ((*x).generic.field_decl.common.initial);
              gt_pch_n_9tree_node ((*x).generic.field_decl.common.attributes);
              gt_pch_n_9tree_node ((*x).generic.field_decl.common.abstract_origin);
              gt_pch_n_9lang_decl ((*x).generic.field_decl.common.lang_specific);
              gt_pch_n_9tree_node ((*x).generic.field_decl.offset);
              gt_pch_n_9tree_node ((*x).generic.field_decl.bit_field_type);
              gt_pch_n_9tree_node ((*x).generic.field_decl.qualifier);
              gt_pch_n_9tree_node ((*x).generic.field_decl.bit_offset);
              gt_pch_n_9tree_node ((*x).generic.field_decl.fcontext);
              break;
            case TS_LABEL_DECL:
              gt_pch_n_9tree_node ((*x).generic.label_decl.common.common.common.common.typed.type);
              gt_pch_n_9tree_node ((*x).generic.label_decl.common.common.common.common.chain);
              gt_pch_n_9tree_node ((*x).generic.label_decl.common.common.common.name);
              gt_pch_n_9tree_node ((*x).generic.label_decl.common.common.common.context);
              gt_pch_n_9tree_node ((*x).generic.label_decl.common.common.size);
              gt_pch_n_9tree_node ((*x).generic.label_decl.common.common.size_unit);
              gt_pch_n_9tree_node ((*x).generic.label_decl.common.common.initial);
              gt_pch_n_9tree_node ((*x).generic.label_decl.common.common.attributes);
              gt_pch_n_9tree_node ((*x).generic.label_decl.common.common.abstract_origin);
              gt_pch_n_9lang_decl ((*x).generic.label_decl.common.common.lang_specific);
              gt_pch_n_7rtx_def ((*x).generic.label_decl.common.rtl);
              break;
            case TS_RESULT_DECL:
              gt_pch_n_9tree_node ((*x).generic.result_decl.common.common.common.common.typed.type);
              gt_pch_n_9tree_node ((*x).generic.result_decl.common.common.common.common.chain);
              gt_pch_n_9tree_node ((*x).generic.result_decl.common.common.common.name);
              gt_pch_n_9tree_node ((*x).generic.result_decl.common.common.common.context);
              gt_pch_n_9tree_node ((*x).generic.result_decl.common.common.size);
              gt_pch_n_9tree_node ((*x).generic.result_decl.common.common.size_unit);
              gt_pch_n_9tree_node ((*x).generic.result_decl.common.common.initial);
              gt_pch_n_9tree_node ((*x).generic.result_decl.common.common.attributes);
              gt_pch_n_9tree_node ((*x).generic.result_decl.common.common.abstract_origin);
              gt_pch_n_9lang_decl ((*x).generic.result_decl.common.common.lang_specific);
              gt_pch_n_7rtx_def ((*x).generic.result_decl.common.rtl);
              break;
            case TS_CONST_DECL:
              gt_pch_n_9tree_node ((*x).generic.const_decl.common.common.common.typed.type);
              gt_pch_n_9tree_node ((*x).generic.const_decl.common.common.common.chain);
              gt_pch_n_9tree_node ((*x).generic.const_decl.common.common.name);
              gt_pch_n_9tree_node ((*x).generic.const_decl.common.common.context);
              gt_pch_n_9tree_node ((*x).generic.const_decl.common.size);
              gt_pch_n_9tree_node ((*x).generic.const_decl.common.size_unit);
              gt_pch_n_9tree_node ((*x).generic.const_decl.common.initial);
              gt_pch_n_9tree_node ((*x).generic.const_decl.common.attributes);
              gt_pch_n_9tree_node ((*x).generic.const_decl.common.abstract_origin);
              gt_pch_n_9lang_decl ((*x).generic.const_decl.common.lang_specific);
              break;
            case TS_TYPE_DECL:
              gt_pch_n_9tree_node ((*x).generic.type_decl.common.common.common.common.common.common.typed.type);
              gt_pch_n_9tree_node ((*x).generic.type_decl.common.common.common.common.common.common.chain);
              gt_pch_n_9tree_node ((*x).generic.type_decl.common.common.common.common.common.name);
              gt_pch_n_9tree_node ((*x).generic.type_decl.common.common.common.common.common.context);
              gt_pch_n_9tree_node ((*x).generic.type_decl.common.common.common.common.size);
              gt_pch_n_9tree_node ((*x).generic.type_decl.common.common.common.common.size_unit);
              gt_pch_n_9tree_node ((*x).generic.type_decl.common.common.common.common.initial);
              gt_pch_n_9tree_node ((*x).generic.type_decl.common.common.common.common.attributes);
              gt_pch_n_9tree_node ((*x).generic.type_decl.common.common.common.common.abstract_origin);
              gt_pch_n_9lang_decl ((*x).generic.type_decl.common.common.common.common.lang_specific);
              gt_pch_n_7rtx_def ((*x).generic.type_decl.common.common.common.rtl);
              gt_pch_n_9tree_node ((*x).generic.type_decl.common.common.assembler_name);
              gt_pch_n_9tree_node ((*x).generic.type_decl.common.common.section_name);
              gt_pch_n_9tree_node ((*x).generic.type_decl.common.common.comdat_group);
              gt_pch_n_9tree_node ((*x).generic.type_decl.common.saved_tree);
              gt_pch_n_9tree_node ((*x).generic.type_decl.common.arguments);
              gt_pch_n_9tree_node ((*x).generic.type_decl.common.result);
              gt_pch_n_9tree_node ((*x).generic.type_decl.common.vindex);
              break;
            case TS_FUNCTION_DECL:
              gt_pch_n_9tree_node ((*x).generic.function_decl.common.common.common.common.common.common.typed.type);
              gt_pch_n_9tree_node ((*x).generic.function_decl.common.common.common.common.common.common.chain);
              gt_pch_n_9tree_node ((*x).generic.function_decl.common.common.common.common.common.name);
              gt_pch_n_9tree_node ((*x).generic.function_decl.common.common.common.common.common.context);
              gt_pch_n_9tree_node ((*x).generic.function_decl.common.common.common.common.size);
              gt_pch_n_9tree_node ((*x).generic.function_decl.common.common.common.common.size_unit);
              gt_pch_n_9tree_node ((*x).generic.function_decl.common.common.common.common.initial);
              gt_pch_n_9tree_node ((*x).generic.function_decl.common.common.common.common.attributes);
              gt_pch_n_9tree_node ((*x).generic.function_decl.common.common.common.common.abstract_origin);
              gt_pch_n_9lang_decl ((*x).generic.function_decl.common.common.common.common.lang_specific);
              gt_pch_n_7rtx_def ((*x).generic.function_decl.common.common.common.rtl);
              gt_pch_n_9tree_node ((*x).generic.function_decl.common.common.assembler_name);
              gt_pch_n_9tree_node ((*x).generic.function_decl.common.common.section_name);
              gt_pch_n_9tree_node ((*x).generic.function_decl.common.common.comdat_group);
              gt_pch_n_9tree_node ((*x).generic.function_decl.common.saved_tree);
              gt_pch_n_9tree_node ((*x).generic.function_decl.common.arguments);
              gt_pch_n_9tree_node ((*x).generic.function_decl.common.result);
              gt_pch_n_9tree_node ((*x).generic.function_decl.common.vindex);
              gt_pch_n_8function ((*x).generic.function_decl.f);
              gt_pch_n_9tree_node ((*x).generic.function_decl.personality);
              gt_pch_n_9tree_node ((*x).generic.function_decl.function_specific_target);
              gt_pch_n_9tree_node ((*x).generic.function_decl.function_specific_optimization);
              break;
            case TS_TRANSLATION_UNIT_DECL:
              gt_pch_n_9tree_node ((*x).generic.translation_unit_decl.common.common.common.typed.type);
              gt_pch_n_9tree_node ((*x).generic.translation_unit_decl.common.common.common.chain);
              gt_pch_n_9tree_node ((*x).generic.translation_unit_decl.common.common.name);
              gt_pch_n_9tree_node ((*x).generic.translation_unit_decl.common.common.context);
              gt_pch_n_9tree_node ((*x).generic.translation_unit_decl.common.size);
              gt_pch_n_9tree_node ((*x).generic.translation_unit_decl.common.size_unit);
              gt_pch_n_9tree_node ((*x).generic.translation_unit_decl.common.initial);
              gt_pch_n_9tree_node ((*x).generic.translation_unit_decl.common.attributes);
              gt_pch_n_9tree_node ((*x).generic.translation_unit_decl.common.abstract_origin);
              gt_pch_n_9lang_decl ((*x).generic.translation_unit_decl.common.lang_specific);
              break;
            case TS_TYPE_COMMON:
              gt_pch_n_9tree_node ((*x).generic.type_common.common.typed.type);
              gt_pch_n_9tree_node ((*x).generic.type_common.common.chain);
              gt_pch_n_9tree_node ((*x).generic.type_common.size);
              gt_pch_n_9tree_node ((*x).generic.type_common.size_unit);
              gt_pch_n_9tree_node ((*x).generic.type_common.attributes);
              gt_pch_n_9tree_node ((*x).generic.type_common.pointer_to);
              gt_pch_n_9tree_node ((*x).generic.type_common.reference_to);
              switch (debug_hooks->tree_type_symtab_field)
                {
                case TYPE_SYMTAB_IS_ADDRESS:
                  break;
                case TYPE_SYMTAB_IS_POINTER:
                  gt_pch_n_S ((*x).generic.type_common.symtab.pointer);
                  break;
                case TYPE_SYMTAB_IS_DIE:
                  gt_pch_n_10die_struct ((*x).generic.type_common.symtab.die);
                  break;
                default:
                  break;
                }
              gt_pch_n_9tree_node ((*x).generic.type_common.name);
              gt_pch_n_9tree_node ((*x).generic.type_common.next_variant);
              gt_pch_n_9tree_node ((*x).generic.type_common.main_variant);
              gt_pch_n_9tree_node ((*x).generic.type_common.context);
              gt_pch_n_9tree_node ((*x).generic.type_common.canonical);
              break;
            case TS_TYPE_WITH_LANG_SPECIFIC:
              gt_pch_n_9tree_node ((*x).generic.type_with_lang_specific.common.common.typed.type);
              gt_pch_n_9tree_node ((*x).generic.type_with_lang_specific.common.common.chain);
              gt_pch_n_9tree_node ((*x).generic.type_with_lang_specific.common.size);
              gt_pch_n_9tree_node ((*x).generic.type_with_lang_specific.common.size_unit);
              gt_pch_n_9tree_node ((*x).generic.type_with_lang_specific.common.attributes);
              gt_pch_n_9tree_node ((*x).generic.type_with_lang_specific.common.pointer_to);
              gt_pch_n_9tree_node ((*x).generic.type_with_lang_specific.common.reference_to);
              switch (debug_hooks->tree_type_symtab_field)
                {
                case TYPE_SYMTAB_IS_ADDRESS:
                  break;
                case TYPE_SYMTAB_IS_POINTER:
                  gt_pch_n_S ((*x).generic.type_with_lang_specific.common.symtab.pointer);
                  break;
                case TYPE_SYMTAB_IS_DIE:
                  gt_pch_n_10die_struct ((*x).generic.type_with_lang_specific.common.symtab.die);
                  break;
                default:
                  break;
                }
              gt_pch_n_9tree_node ((*x).generic.type_with_lang_specific.common.name);
              gt_pch_n_9tree_node ((*x).generic.type_with_lang_specific.common.next_variant);
              gt_pch_n_9tree_node ((*x).generic.type_with_lang_specific.common.main_variant);
              gt_pch_n_9tree_node ((*x).generic.type_with_lang_specific.common.context);
              gt_pch_n_9tree_node ((*x).generic.type_with_lang_specific.common.canonical);
              gt_pch_n_9lang_type ((*x).generic.type_with_lang_specific.lang_specific);
              break;
            case TS_TYPE_NON_COMMON:
              gt_pch_n_9tree_node ((*x).generic.type_non_common.with_lang_specific.common.common.typed.type);
              gt_pch_n_9tree_node ((*x).generic.type_non_common.with_lang_specific.common.common.chain);
              gt_pch_n_9tree_node ((*x).generic.type_non_common.with_lang_specific.common.size);
              gt_pch_n_9tree_node ((*x).generic.type_non_common.with_lang_specific.common.size_unit);
              gt_pch_n_9tree_node ((*x).generic.type_non_common.with_lang_specific.common.attributes);
              gt_pch_n_9tree_node ((*x).generic.type_non_common.with_lang_specific.common.pointer_to);
              gt_pch_n_9tree_node ((*x).generic.type_non_common.with_lang_specific.common.reference_to);
              switch (debug_hooks->tree_type_symtab_field)
                {
                case TYPE_SYMTAB_IS_ADDRESS:
                  break;
                case TYPE_SYMTAB_IS_POINTER:
                  gt_pch_n_S ((*x).generic.type_non_common.with_lang_specific.common.symtab.pointer);
                  break;
                case TYPE_SYMTAB_IS_DIE:
                  gt_pch_n_10die_struct ((*x).generic.type_non_common.with_lang_specific.common.symtab.die);
                  break;
                default:
                  break;
                }
              gt_pch_n_9tree_node ((*x).generic.type_non_common.with_lang_specific.common.name);
              gt_pch_n_9tree_node ((*x).generic.type_non_common.with_lang_specific.common.next_variant);
              gt_pch_n_9tree_node ((*x).generic.type_non_common.with_lang_specific.common.main_variant);
              gt_pch_n_9tree_node ((*x).generic.type_non_common.with_lang_specific.common.context);
              gt_pch_n_9tree_node ((*x).generic.type_non_common.with_lang_specific.common.canonical);
              gt_pch_n_9lang_type ((*x).generic.type_non_common.with_lang_specific.lang_specific);
              gt_pch_n_9tree_node ((*x).generic.type_non_common.values);
              gt_pch_n_9tree_node ((*x).generic.type_non_common.minval);
              gt_pch_n_9tree_node ((*x).generic.type_non_common.maxval);
              gt_pch_n_9tree_node ((*x).generic.type_non_common.binfo);
              break;
            case TS_LIST:
              gt_pch_n_9tree_node ((*x).generic.list.common.typed.type);
              gt_pch_n_9tree_node ((*x).generic.list.common.chain);
              gt_pch_n_9tree_node ((*x).generic.list.purpose);
              gt_pch_n_9tree_node ((*x).generic.list.value);
              break;
            case TS_VEC:
              {
                size_t l1 = (size_t)(TREE_VEC_LENGTH ((tree)&((*x).generic.vec)));
                gt_pch_n_9tree_node ((*x).generic.vec.common.typed.type);
                gt_pch_n_9tree_node ((*x).generic.vec.common.chain);
                {
                  size_t i1;
                  for (i1 = 0; i1 != l1; i1++) {
                    gt_pch_n_9tree_node ((*x).generic.vec.a[i1]);
                  }
                }
              }
              break;
            case TS_EXP:
              gt_pch_n_9tree_node ((*x).generic.exp.typed.type);
              switch (TREE_CODE ((tree) &(*x)))
                {
                default:
                  {
                    size_t i2;
                    size_t l2 = (size_t)(TREE_OPERAND_LENGTH ((tree) &(*x)));
                    for (i2 = 0; i2 != l2; i2++) {
                      gt_pch_n_9tree_node ((*x).generic.exp.operands[i2]);
                    }
                  }
                  break;
                }
              break;
            case TS_SSA_NAME:
              gt_pch_n_9tree_node ((*x).generic.ssa_name.typed.type);
              gt_pch_n_9tree_node ((*x).generic.ssa_name.var);
              gt_pch_n_18gimple_statement_d ((*x).generic.ssa_name.def_stmt);
              gt_pch_n_12ptr_info_def ((*x).generic.ssa_name.ptr_info);
              break;
            case TS_BLOCK:
              gt_pch_n_9tree_node ((*x).generic.block.chain);
              gt_pch_n_9tree_node ((*x).generic.block.vars);
              gt_pch_n_15vec_tree_va_gc_ ((*x).generic.block.nonlocalized_vars);
              gt_pch_n_9tree_node ((*x).generic.block.subblocks);
              gt_pch_n_9tree_node ((*x).generic.block.supercontext);
              gt_pch_n_9tree_node ((*x).generic.block.abstract_origin);
              gt_pch_n_9tree_node ((*x).generic.block.fragment_origin);
              gt_pch_n_9tree_node ((*x).generic.block.fragment_chain);
              break;
            case TS_BINFO:
              gt_pch_n_9tree_node ((*x).generic.binfo.common.typed.type);
              gt_pch_n_9tree_node ((*x).generic.binfo.common.chain);
              gt_pch_n_9tree_node ((*x).generic.binfo.offset);
              gt_pch_n_9tree_node ((*x).generic.binfo.vtable);
              gt_pch_n_9tree_node ((*x).generic.binfo.virtuals);
              gt_pch_n_9tree_node ((*x).generic.binfo.vptr_field);
              gt_pch_n_15vec_tree_va_gc_ ((*x).generic.binfo.base_accesses);
              gt_pch_n_9tree_node ((*x).generic.binfo.inheritance);
              gt_pch_n_9tree_node ((*x).generic.binfo.vtt_subvtt);
              gt_pch_n_9tree_node ((*x).generic.binfo.vtt_vptr);
              gt_pch_nx (&((*x).generic.binfo.base_binfos));
              break;
            case TS_STATEMENT_LIST:
              gt_pch_n_9tree_node ((*x).generic.stmt_list.typed.type);
              gt_pch_n_24tree_statement_list_node ((*x).generic.stmt_list.head);
              gt_pch_n_24tree_statement_list_node ((*x).generic.stmt_list.tail);
              break;
            case TS_CONSTRUCTOR:
              gt_pch_n_9tree_node ((*x).generic.constructor.typed.type);
              gt_pch_n_26vec_constructor_elt_va_gc_ ((*x).generic.constructor.elts);
              break;
            case TS_OMP_CLAUSE:
              {
                size_t l3 = (size_t)(omp_clause_num_ops[OMP_CLAUSE_CODE ((tree)&((*x).generic.omp_clause))]);
                gt_pch_n_9tree_node ((*x).generic.omp_clause.common.typed.type);
                gt_pch_n_9tree_node ((*x).generic.omp_clause.common.chain);
                gt_pch_n_18gimple_statement_d ((*x).generic.omp_clause.gimple_reduction_init);
                gt_pch_n_18gimple_statement_d ((*x).generic.omp_clause.gimple_reduction_merge);
                {
                  size_t i3;
                  for (i3 = 0; i3 != l3; i3++) {
                    gt_pch_n_9tree_node ((*x).generic.omp_clause.ops[i3]);
                  }
                }
              }
              break;
            case TS_OPTIMIZATION:
              gt_pch_n_9tree_node ((*x).generic.optimization.common.typed.type);
              gt_pch_n_9tree_node ((*x).generic.optimization.common.chain);
              gt_pch_n_S ((*x).generic.optimization.optabs);
              break;
            case TS_TARGET_OPTION:
              gt_pch_n_9tree_node ((*x).generic.target_option.common.typed.type);
              gt_pch_n_9tree_node ((*x).generic.target_option.common.chain);
              break;
            default:
              break;
            }
          break;
        case 1:
          gt_pch_n_9tree_node ((*x).identifier.ignore.common.typed.type);
          gt_pch_n_9tree_node ((*x).identifier.ignore.common.chain);
          gt_pch_n_S ((*x).identifier.ignore.id.str);
          gt_pch_n_9tree_node ((*x).identifier.global_value);
          gt_pch_n_9tree_node ((*x).identifier.local_value);
          gt_pch_n_9tree_node ((*x).identifier.utf8_ref);
          break;
        default:
          break;
        }
      x = (CODE_CONTAINS_STRUCT (TREE_CODE (&(*x).generic), TS_COMMON) ? ((union lang_tree_node *) TREE_CHAIN (&(*x).generic)) : NULL);
    }
}

void
gt_pch_nx_lang_decl (void *x_p)
{
  struct lang_decl * const x = (struct lang_decl *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_9lang_decl))
    {
      switch ((*x).desc)
        {
        case LANG_DECL_FUNC:
          gt_pch_n_15vec_tree_va_gc_ ((*x).u.f.throws_list);
          gt_pch_n_9tree_node ((*x).u.f.exc_obj);
          gt_pch_n_P18treetreehash_entry4htab ((*x).u.f.init_test_table);
          gt_pch_n_P9tree_node4htab ((*x).u.f.ict);
          break;
        case LANG_DECL_VAR:
          gt_pch_n_9tree_node ((*x).u.v.slot_chain);
          gt_pch_n_9tree_node ((*x).u.v.owner);
          break;
        default:
          break;
        }
    }
}

void
gt_pch_nx_lang_type (void *x_p)
{
  struct lang_type * const x = (struct lang_type *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_9lang_type))
    {
      gt_pch_n_9tree_node ((*x).signature);
      gt_pch_n_3JCF ((*x).jcf);
      gt_pch_n_5CPool ((*x).cpool);
      gt_pch_n_9tree_node ((*x).cpool_data_ref);
      gt_pch_n_9tree_node ((*x).package_list);
      gt_pch_n_23vec_method_entry_va_gc_ ((*x).otable_methods);
      gt_pch_n_9tree_node ((*x).otable_decl);
      gt_pch_n_9tree_node ((*x).otable_syms_decl);
      gt_pch_n_23vec_method_entry_va_gc_ ((*x).atable_methods);
      gt_pch_n_9tree_node ((*x).atable_decl);
      gt_pch_n_9tree_node ((*x).atable_syms_decl);
      gt_pch_n_23vec_method_entry_va_gc_ ((*x).itable_methods);
      gt_pch_n_9tree_node ((*x).itable_decl);
      gt_pch_n_9tree_node ((*x).itable_syms_decl);
      gt_pch_n_9tree_node ((*x).ctable_decl);
      gt_pch_n_26vec_constructor_elt_va_gc_ ((*x).catch_classes);
      gt_pch_n_P18treetreehash_entry4htab ((*x).type_to_runtime_map);
      gt_pch_n_P14type_assertion4htab ((*x).type_assertions);
      gt_pch_n_9tree_node ((*x).package);
    }
}

void
gt_pch_n_P14type_assertion4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_P14type_assertion4htab))
    {
      {
        size_t l0 = (size_t)(((*x)).size);
        if ((*x).entries != NULL) {
          size_t i0;
          for (i0 = 0; i0 != (size_t)(l0); i0++) {
            gt_pch_n_14type_assertion ((*x).entries[i0]);
          }
          gt_pch_note_object ((*x).entries, x, gt_pch_p_P14type_assertion4htab);
        }
      }
    }
}

void
gt_pch_n_P18treetreehash_entry4htab (void *x_p)
{
  struct htab * const x = (struct htab *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_P18treetreehash_entry4htab))
    {
      {
        size_t l0 = (size_t)(((*x)).size);
        if ((*x).entries != NULL) {
          size_t i0;
          for (i0 = 0; i0 != (size_t)(l0); i0++) {
            gt_pch_n_18treetreehash_entry ((*x).entries[i0]);
          }
          gt_pch_note_object ((*x).entries, x, gt_pch_p_P18treetreehash_entry4htab);
        }
      }
    }
}

void
gt_pch_p_23vec_method_entry_va_gc_ (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct vec<method_entry,va_gc> * x ATTRIBUTE_UNUSED = (struct vec<method_entry,va_gc> *)x_p;
  if ((void *)(x) == this_obj)
    gt_pch_nx (&((*x)), op, cookie);
}

void
gt_pch_nx (struct method_entry_d* x ATTRIBUTE_UNUSED,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
    op (&((*x).method), cookie);
    op (&((*x).special), cookie);
}

void
gt_pch_p_14type_assertion (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct type_assertion * x ATTRIBUTE_UNUSED = (struct type_assertion *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).op1), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).op2), cookie);
}

void
gt_pch_p_18treetreehash_entry (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct treetreehash_entry * x ATTRIBUTE_UNUSED = (struct treetreehash_entry *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).key), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).value), cookie);
}

void
gt_pch_p_5CPool (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct CPool * x ATTRIBUTE_UNUSED = (struct CPool *)x_p;
  {
    size_t l0 = (size_t)(((*x)).count);
    if ((*x).tags != NULL) {
      if ((void *)(x) == this_obj)
        op (&((*x).tags), cookie);
    }
    if ((*x).data != NULL) {
      size_t i0;
      for (i0 = 0; i0 != (size_t)(l0) && ((void *)(*x).data == this_obj); i0++) {
        switch (cpool_entry_is_tree (((*x)).tags[i0]))
          {
          case 0:
            break;
          case 1:
            if ((void *)((*x).data) == this_obj)
              op (&((*x).data[i0].t), cookie);
            break;
          default:
            break;
          }
      }
      if ((void *)(x) == this_obj)
        op (&((*x).data), cookie);
    }
  }
}

void
gt_pch_p_3JCF (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct JCF * x ATTRIBUTE_UNUSED = (struct JCF *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).filename), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).classname), cookie);
  {
    size_t l0 = (size_t)(((*x).cpool).count);
    if ((*x).cpool.tags != NULL) {
      if ((void *)(x) == this_obj)
        op (&((*x).cpool.tags), cookie);
    }
    if ((*x).cpool.data != NULL) {
      size_t i0;
      for (i0 = 0; i0 != (size_t)(l0) && ((void *)(*x).cpool.data == this_obj); i0++) {
        switch (cpool_entry_is_tree (((*x).cpool).tags[i0]))
          {
          case 0:
            break;
          case 1:
            if ((void *)((*x).cpool.data) == this_obj)
              op (&((*x).cpool.data[i0].t), cookie);
            break;
          default:
            break;
          }
      }
      if ((void *)(x) == this_obj)
        op (&((*x).cpool.data), cookie);
    }
  }
  {
    size_t l1 = (size_t)(((*x).bootstrap_methods).count);
    if ((*x).bootstrap_methods.methods != NULL) {
      size_t i1;
      for (i1 = 0; i1 != (size_t)(l1) && ((void *)(*x).bootstrap_methods.methods == this_obj); i1++) {
        if ((*x).bootstrap_methods.methods[i1].bootstrap_arguments != NULL) {
          if ((void *)((*x).bootstrap_methods.methods) == this_obj)
            op (&((*x).bootstrap_methods.methods[i1].bootstrap_arguments), cookie);
        }
      }
      if ((void *)(x) == this_obj)
        op (&((*x).bootstrap_methods.methods), cookie);
    }
  }
}

void
gt_pch_p_14lang_tree_node (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  union lang_tree_node * x ATTRIBUTE_UNUSED = (union lang_tree_node *)x_p;
  switch (TREE_CODE (&((*x)).generic) == IDENTIFIER_NODE)
    {
    case 0:
      switch (tree_node_structure (&((*x).generic)))
        {
        case TS_BASE:
          break;
        case TS_TYPED:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.typed.type), cookie);
          break;
        case TS_COMMON:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.common.typed.type), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.common.chain), cookie);
          break;
        case TS_INT_CST:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.int_cst.typed.type), cookie);
          break;
        case TS_REAL_CST:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.real_cst.typed.type), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.real_cst.real_cst_ptr), cookie);
          break;
        case TS_FIXED_CST:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.fixed_cst.typed.type), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.fixed_cst.fixed_cst_ptr), cookie);
          break;
        case TS_VECTOR:
          {
            size_t l0 = (size_t)(TYPE_VECTOR_SUBPARTS (TREE_TYPE ((tree)&((*x).generic.vector))));
            if ((void *)(x) == this_obj)
              op (&((*x).generic.vector.typed.type), cookie);
            {
              size_t i0;
              for (i0 = 0; i0 != l0; i0++) {
                if ((void *)(x) == this_obj)
                  op (&((*x).generic.vector.elts[i0]), cookie);
              }
            }
          }
          break;
        case TS_STRING:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.string.typed.type), cookie);
          break;
        case TS_COMPLEX:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.complex.typed.type), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.complex.real), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.complex.imag), cookie);
          break;
        case TS_IDENTIFIER:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.identifier.common.typed.type), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.identifier.common.chain), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.identifier.id.str), cookie);
          break;
        case TS_DECL_MINIMAL:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_minimal.common.typed.type), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_minimal.common.chain), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_minimal.name), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_minimal.context), cookie);
          break;
        case TS_DECL_COMMON:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_common.common.common.typed.type), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_common.common.common.chain), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_common.common.name), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_common.common.context), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_common.size), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_common.size_unit), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_common.initial), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_common.attributes), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_common.abstract_origin), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_common.lang_specific), cookie);
          break;
        case TS_DECL_WRTL:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_with_rtl.common.common.common.typed.type), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_with_rtl.common.common.common.chain), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_with_rtl.common.common.name), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_with_rtl.common.common.context), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_with_rtl.common.size), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_with_rtl.common.size_unit), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_with_rtl.common.initial), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_with_rtl.common.attributes), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_with_rtl.common.abstract_origin), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_with_rtl.common.lang_specific), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_with_rtl.rtl), cookie);
          break;
        case TS_DECL_NON_COMMON:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_non_common.common.common.common.common.common.typed.type), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_non_common.common.common.common.common.common.chain), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_non_common.common.common.common.common.name), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_non_common.common.common.common.common.context), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_non_common.common.common.common.size), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_non_common.common.common.common.size_unit), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_non_common.common.common.common.initial), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_non_common.common.common.common.attributes), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_non_common.common.common.common.abstract_origin), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_non_common.common.common.common.lang_specific), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_non_common.common.common.rtl), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_non_common.common.assembler_name), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_non_common.common.section_name), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_non_common.common.comdat_group), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_non_common.saved_tree), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_non_common.arguments), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_non_common.result), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_non_common.vindex), cookie);
          break;
        case TS_PARM_DECL:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.parm_decl.common.common.common.common.typed.type), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.parm_decl.common.common.common.common.chain), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.parm_decl.common.common.common.name), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.parm_decl.common.common.common.context), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.parm_decl.common.common.size), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.parm_decl.common.common.size_unit), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.parm_decl.common.common.initial), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.parm_decl.common.common.attributes), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.parm_decl.common.common.abstract_origin), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.parm_decl.common.common.lang_specific), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.parm_decl.common.rtl), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.parm_decl.incoming_rtl), cookie);
          break;
        case TS_DECL_WITH_VIS:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_with_vis.common.common.common.common.typed.type), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_with_vis.common.common.common.common.chain), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_with_vis.common.common.common.name), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_with_vis.common.common.common.context), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_with_vis.common.common.size), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_with_vis.common.common.size_unit), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_with_vis.common.common.initial), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_with_vis.common.common.attributes), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_with_vis.common.common.abstract_origin), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_with_vis.common.common.lang_specific), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_with_vis.common.rtl), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_with_vis.assembler_name), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_with_vis.section_name), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.decl_with_vis.comdat_group), cookie);
          break;
        case TS_VAR_DECL:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.var_decl.common.common.common.common.common.typed.type), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.var_decl.common.common.common.common.common.chain), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.var_decl.common.common.common.common.name), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.var_decl.common.common.common.common.context), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.var_decl.common.common.common.size), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.var_decl.common.common.common.size_unit), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.var_decl.common.common.common.initial), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.var_decl.common.common.common.attributes), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.var_decl.common.common.common.abstract_origin), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.var_decl.common.common.common.lang_specific), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.var_decl.common.common.rtl), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.var_decl.common.assembler_name), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.var_decl.common.section_name), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.var_decl.common.comdat_group), cookie);
          break;
        case TS_FIELD_DECL:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.field_decl.common.common.common.typed.type), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.field_decl.common.common.common.chain), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.field_decl.common.common.name), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.field_decl.common.common.context), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.field_decl.common.size), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.field_decl.common.size_unit), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.field_decl.common.initial), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.field_decl.common.attributes), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.field_decl.common.abstract_origin), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.field_decl.common.lang_specific), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.field_decl.offset), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.field_decl.bit_field_type), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.field_decl.qualifier), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.field_decl.bit_offset), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.field_decl.fcontext), cookie);
          break;
        case TS_LABEL_DECL:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.label_decl.common.common.common.common.typed.type), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.label_decl.common.common.common.common.chain), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.label_decl.common.common.common.name), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.label_decl.common.common.common.context), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.label_decl.common.common.size), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.label_decl.common.common.size_unit), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.label_decl.common.common.initial), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.label_decl.common.common.attributes), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.label_decl.common.common.abstract_origin), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.label_decl.common.common.lang_specific), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.label_decl.common.rtl), cookie);
          break;
        case TS_RESULT_DECL:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.result_decl.common.common.common.common.typed.type), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.result_decl.common.common.common.common.chain), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.result_decl.common.common.common.name), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.result_decl.common.common.common.context), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.result_decl.common.common.size), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.result_decl.common.common.size_unit), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.result_decl.common.common.initial), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.result_decl.common.common.attributes), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.result_decl.common.common.abstract_origin), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.result_decl.common.common.lang_specific), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.result_decl.common.rtl), cookie);
          break;
        case TS_CONST_DECL:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.const_decl.common.common.common.typed.type), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.const_decl.common.common.common.chain), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.const_decl.common.common.name), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.const_decl.common.common.context), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.const_decl.common.size), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.const_decl.common.size_unit), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.const_decl.common.initial), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.const_decl.common.attributes), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.const_decl.common.abstract_origin), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.const_decl.common.lang_specific), cookie);
          break;
        case TS_TYPE_DECL:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_decl.common.common.common.common.common.common.typed.type), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_decl.common.common.common.common.common.common.chain), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_decl.common.common.common.common.common.name), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_decl.common.common.common.common.common.context), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_decl.common.common.common.common.size), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_decl.common.common.common.common.size_unit), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_decl.common.common.common.common.initial), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_decl.common.common.common.common.attributes), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_decl.common.common.common.common.abstract_origin), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_decl.common.common.common.common.lang_specific), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_decl.common.common.common.rtl), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_decl.common.common.assembler_name), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_decl.common.common.section_name), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_decl.common.common.comdat_group), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_decl.common.saved_tree), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_decl.common.arguments), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_decl.common.result), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_decl.common.vindex), cookie);
          break;
        case TS_FUNCTION_DECL:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.function_decl.common.common.common.common.common.common.typed.type), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.function_decl.common.common.common.common.common.common.chain), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.function_decl.common.common.common.common.common.name), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.function_decl.common.common.common.common.common.context), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.function_decl.common.common.common.common.size), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.function_decl.common.common.common.common.size_unit), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.function_decl.common.common.common.common.initial), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.function_decl.common.common.common.common.attributes), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.function_decl.common.common.common.common.abstract_origin), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.function_decl.common.common.common.common.lang_specific), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.function_decl.common.common.common.rtl), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.function_decl.common.common.assembler_name), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.function_decl.common.common.section_name), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.function_decl.common.common.comdat_group), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.function_decl.common.saved_tree), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.function_decl.common.arguments), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.function_decl.common.result), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.function_decl.common.vindex), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.function_decl.f), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.function_decl.personality), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.function_decl.function_specific_target), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.function_decl.function_specific_optimization), cookie);
          break;
        case TS_TRANSLATION_UNIT_DECL:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.translation_unit_decl.common.common.common.typed.type), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.translation_unit_decl.common.common.common.chain), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.translation_unit_decl.common.common.name), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.translation_unit_decl.common.common.context), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.translation_unit_decl.common.size), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.translation_unit_decl.common.size_unit), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.translation_unit_decl.common.initial), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.translation_unit_decl.common.attributes), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.translation_unit_decl.common.abstract_origin), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.translation_unit_decl.common.lang_specific), cookie);
          break;
        case TS_TYPE_COMMON:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_common.common.typed.type), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_common.common.chain), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_common.size), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_common.size_unit), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_common.attributes), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_common.pointer_to), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_common.reference_to), cookie);
          switch (debug_hooks->tree_type_symtab_field)
            {
            case TYPE_SYMTAB_IS_ADDRESS:
              break;
            case TYPE_SYMTAB_IS_POINTER:
              if ((void *)(x) == this_obj)
                op (&((*x).generic.type_common.symtab.pointer), cookie);
              break;
            case TYPE_SYMTAB_IS_DIE:
              if ((void *)(x) == this_obj)
                op (&((*x).generic.type_common.symtab.die), cookie);
              break;
            default:
              break;
            }
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_common.name), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_common.next_variant), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_common.main_variant), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_common.context), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_common.canonical), cookie);
          break;
        case TS_TYPE_WITH_LANG_SPECIFIC:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_with_lang_specific.common.common.typed.type), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_with_lang_specific.common.common.chain), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_with_lang_specific.common.size), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_with_lang_specific.common.size_unit), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_with_lang_specific.common.attributes), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_with_lang_specific.common.pointer_to), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_with_lang_specific.common.reference_to), cookie);
          switch (debug_hooks->tree_type_symtab_field)
            {
            case TYPE_SYMTAB_IS_ADDRESS:
              break;
            case TYPE_SYMTAB_IS_POINTER:
              if ((void *)(x) == this_obj)
                op (&((*x).generic.type_with_lang_specific.common.symtab.pointer), cookie);
              break;
            case TYPE_SYMTAB_IS_DIE:
              if ((void *)(x) == this_obj)
                op (&((*x).generic.type_with_lang_specific.common.symtab.die), cookie);
              break;
            default:
              break;
            }
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_with_lang_specific.common.name), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_with_lang_specific.common.next_variant), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_with_lang_specific.common.main_variant), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_with_lang_specific.common.context), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_with_lang_specific.common.canonical), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_with_lang_specific.lang_specific), cookie);
          break;
        case TS_TYPE_NON_COMMON:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_non_common.with_lang_specific.common.common.typed.type), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_non_common.with_lang_specific.common.common.chain), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_non_common.with_lang_specific.common.size), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_non_common.with_lang_specific.common.size_unit), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_non_common.with_lang_specific.common.attributes), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_non_common.with_lang_specific.common.pointer_to), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_non_common.with_lang_specific.common.reference_to), cookie);
          switch (debug_hooks->tree_type_symtab_field)
            {
            case TYPE_SYMTAB_IS_ADDRESS:
              break;
            case TYPE_SYMTAB_IS_POINTER:
              if ((void *)(x) == this_obj)
                op (&((*x).generic.type_non_common.with_lang_specific.common.symtab.pointer), cookie);
              break;
            case TYPE_SYMTAB_IS_DIE:
              if ((void *)(x) == this_obj)
                op (&((*x).generic.type_non_common.with_lang_specific.common.symtab.die), cookie);
              break;
            default:
              break;
            }
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_non_common.with_lang_specific.common.name), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_non_common.with_lang_specific.common.next_variant), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_non_common.with_lang_specific.common.main_variant), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_non_common.with_lang_specific.common.context), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_non_common.with_lang_specific.common.canonical), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_non_common.with_lang_specific.lang_specific), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_non_common.values), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_non_common.minval), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_non_common.maxval), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.type_non_common.binfo), cookie);
          break;
        case TS_LIST:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.list.common.typed.type), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.list.common.chain), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.list.purpose), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.list.value), cookie);
          break;
        case TS_VEC:
          {
            size_t l1 = (size_t)(TREE_VEC_LENGTH ((tree)&((*x).generic.vec)));
            if ((void *)(x) == this_obj)
              op (&((*x).generic.vec.common.typed.type), cookie);
            if ((void *)(x) == this_obj)
              op (&((*x).generic.vec.common.chain), cookie);
            {
              size_t i1;
              for (i1 = 0; i1 != l1; i1++) {
                if ((void *)(x) == this_obj)
                  op (&((*x).generic.vec.a[i1]), cookie);
              }
            }
          }
          break;
        case TS_EXP:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.exp.typed.type), cookie);
          switch (TREE_CODE ((tree) &(*x)))
            {
            default:
              {
                size_t i2;
                size_t l2 = (size_t)(TREE_OPERAND_LENGTH ((tree) &(*x)));
                for (i2 = 0; i2 != l2; i2++) {
                  if ((void *)(x) == this_obj)
                    op (&((*x).generic.exp.operands[i2]), cookie);
                }
              }
              break;
            }
          break;
        case TS_SSA_NAME:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.ssa_name.typed.type), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.ssa_name.var), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.ssa_name.def_stmt), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.ssa_name.ptr_info), cookie);
          break;
        case TS_BLOCK:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.block.chain), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.block.vars), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.block.nonlocalized_vars), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.block.subblocks), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.block.supercontext), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.block.abstract_origin), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.block.fragment_origin), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.block.fragment_chain), cookie);
          break;
        case TS_BINFO:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.binfo.common.typed.type), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.binfo.common.chain), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.binfo.offset), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.binfo.vtable), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.binfo.virtuals), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.binfo.vptr_field), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.binfo.base_accesses), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.binfo.inheritance), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.binfo.vtt_subvtt), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.binfo.vtt_vptr), cookie);
          if ((void *)(x) == this_obj)
            gt_pch_nx (&((*x).generic.binfo.base_binfos), op, cookie);
          break;
        case TS_STATEMENT_LIST:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.stmt_list.typed.type), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.stmt_list.head), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.stmt_list.tail), cookie);
          break;
        case TS_CONSTRUCTOR:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.constructor.typed.type), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.constructor.elts), cookie);
          break;
        case TS_OMP_CLAUSE:
          {
            size_t l3 = (size_t)(omp_clause_num_ops[OMP_CLAUSE_CODE ((tree)&((*x).generic.omp_clause))]);
            if ((void *)(x) == this_obj)
              op (&((*x).generic.omp_clause.common.typed.type), cookie);
            if ((void *)(x) == this_obj)
              op (&((*x).generic.omp_clause.common.chain), cookie);
            if ((void *)(x) == this_obj)
              op (&((*x).generic.omp_clause.gimple_reduction_init), cookie);
            if ((void *)(x) == this_obj)
              op (&((*x).generic.omp_clause.gimple_reduction_merge), cookie);
            {
              size_t i3;
              for (i3 = 0; i3 != l3; i3++) {
                if ((void *)(x) == this_obj)
                  op (&((*x).generic.omp_clause.ops[i3]), cookie);
              }
            }
          }
          break;
        case TS_OPTIMIZATION:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.optimization.common.typed.type), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.optimization.common.chain), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.optimization.optabs), cookie);
          break;
        case TS_TARGET_OPTION:
          if ((void *)(x) == this_obj)
            op (&((*x).generic.target_option.common.typed.type), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).generic.target_option.common.chain), cookie);
          break;
        default:
          break;
        }
      break;
    case 1:
      if ((void *)(x) == this_obj)
        op (&((*x).identifier.ignore.common.typed.type), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).identifier.ignore.common.chain), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).identifier.ignore.id.str), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).identifier.global_value), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).identifier.local_value), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).identifier.utf8_ref), cookie);
      break;
    default:
      break;
    }
}

void
gt_pch_p_9lang_decl (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct lang_decl * x ATTRIBUTE_UNUSED = (struct lang_decl *)x_p;
  switch ((*x).desc)
    {
    case LANG_DECL_FUNC:
      if ((void *)(x) == this_obj)
        op (&((*x).u.f.throws_list), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.f.exc_obj), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.f.init_test_table), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.f.ict), cookie);
      break;
    case LANG_DECL_VAR:
      if ((void *)(x) == this_obj)
        op (&((*x).u.v.slot_chain), cookie);
      if ((void *)(x) == this_obj)
        op (&((*x).u.v.owner), cookie);
      break;
    default:
      break;
    }
}

void
gt_pch_p_9lang_type (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct lang_type * x ATTRIBUTE_UNUSED = (struct lang_type *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).signature), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).jcf), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).cpool), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).cpool_data_ref), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).package_list), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).otable_methods), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).otable_decl), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).otable_syms_decl), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).atable_methods), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).atable_decl), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).atable_syms_decl), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).itable_methods), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).itable_decl), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).itable_syms_decl), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).ctable_decl), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).catch_classes), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).type_to_runtime_map), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).type_assertions), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).package), cookie);
}

void
gt_pch_p_P14type_assertion4htab (ATTRIBUTE_UNUSED void *this_obj,
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
gt_pch_p_P18treetreehash_entry4htab (ATTRIBUTE_UNUSED void *this_obj,
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

EXPORTED_CONST struct ggc_root_tab gt_ggc_r_gtype_java_h[] = {
  {
    &pending_static_fields,
    1,
    sizeof (pending_static_fields),
    &gt_ggc_mx_vec_tree_va_gc_,
    &gt_pch_nx_vec_tree_va_gc_
  },
  {
    &soft_resolvepoolentry_node,
    1,
    sizeof (soft_resolvepoolentry_node),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &java_global_trees[0],
    1 * (JTI_MAX),
    sizeof (java_global_trees[0]),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &constants_data_field_decl_node,
    1,
    sizeof (constants_data_field_decl_node),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &constants_field_decl_node,
    1,
    sizeof (constants_field_decl_node),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &gcj_abi_version,
    1,
    sizeof (gcj_abi_version),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &java_io_serializable_identifier_node,
    1,
    sizeof (java_io_serializable_identifier_node),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &java_lang_cloneable_identifier_node,
    1,
    sizeof (java_lang_cloneable_identifier_node),
    &gt_ggc_mx_tree_node,
    &gt_pch_nx_tree_node
  },
  {
    &current_jcf,
    1,
    sizeof (current_jcf),
    &gt_ggc_mx_JCF,
    &gt_pch_nx_JCF
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
extern const struct ggc_root_tab gt_ggc_r_gtype_java_h[];
extern const struct ggc_root_tab gt_ggc_r_gt_java_builtins_h[];
extern const struct ggc_root_tab gt_ggc_r_gt_java_class_h[];
extern const struct ggc_root_tab gt_ggc_r_gt_java_constants_h[];
extern const struct ggc_root_tab gt_ggc_r_gt_java_decl_h[];
extern const struct ggc_root_tab gt_ggc_r_gt_java_expr_h[];
extern const struct ggc_root_tab gt_ggc_r_gt_java_jcf_parse_h[];
extern const struct ggc_root_tab gt_ggc_r_gt_java_lang_h[];
extern const struct ggc_root_tab gt_ggc_r_gt_java_mangle_h[];
extern const struct ggc_root_tab gt_ggc_r_gt_java_resource_h[];
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
  gt_ggc_r_gtype_java_h,
  gt_ggc_r_gt_java_builtins_h,
  gt_ggc_r_gt_java_class_h,
  gt_ggc_r_gt_java_constants_h,
  gt_ggc_r_gt_java_decl_h,
  gt_ggc_r_gt_java_expr_h,
  gt_ggc_r_gt_java_jcf_parse_h,
  gt_ggc_r_gt_java_lang_h,
  gt_ggc_r_gt_java_mangle_h,
  gt_ggc_r_gt_java_resource_h,
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
extern const struct ggc_root_tab gt_pch_rs_gt_java_builtins_h[];
extern const struct ggc_root_tab gt_pch_rs_gt_java_class_h[];
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
  gt_pch_rs_gt_java_builtins_h,
  gt_pch_rs_gt_java_class_h,
  NULL
};
