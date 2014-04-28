/* Generated automatically by the program 'build/genpreds'
   from the machine description file '../../gcc-4.8.1/gcc/config/i386/i386.md'.  */

#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "tm.h"
#include "rtl.h"
#include "tree.h"
#include "tm_p.h"
#include "function.h"
#include "insn-config.h"
#include "recog.h"
#include "output.h"
#include "flags.h"
#include "hard-reg-set.h"
#include "resource.h"
#include "diagnostic-core.h"
#include "reload.h"
#include "regs.h"
#include "tm-constrs.h"

int
any_fp_register_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return ((GET_CODE (op) == REG) && (
#line 23 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
(ANY_FP_REGNO_P (REGNO (op))))) && (
(mode == VOIDmode || GET_MODE (op) == mode));
}

int
fp_register_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return ((GET_CODE (op) == REG) && (
#line 28 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
(STACK_REGNO_P (REGNO (op))))) && (
(mode == VOIDmode || GET_MODE (op) == mode));
}

int
register_and_not_any_fp_reg_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return ((GET_CODE (op) == REG) && (!(
#line 33 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
(ANY_FP_REGNO_P (REGNO (op)))))) && (
(mode == VOIDmode || GET_MODE (op) == mode));
}

int
register_and_not_fp_reg_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return ((GET_CODE (op) == REG) && (!(
#line 38 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
(STACK_REGNO_P (REGNO (op)))))) && (
(mode == VOIDmode || GET_MODE (op) == mode));
}

int
mmx_reg_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return ((GET_CODE (op) == REG) && (
#line 43 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
(MMX_REGNO_P (REGNO (op))))) && (
(mode == VOIDmode || GET_MODE (op) == mode));
}

int
sse_reg_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return ((GET_CODE (op) == REG) && (
#line 48 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
(SSE_REGNO_P (REGNO (op))))) && (
(mode == VOIDmode || GET_MODE (op) == mode));
}

static inline int
q_regs_operand_1 (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
#line 53 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
{
  if (GET_CODE (op) == SUBREG)
    op = SUBREG_REG (op);
  return ANY_QI_REG_P (op);
}

int
q_regs_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (register_operand (op, mode)) && (
(q_regs_operand_1 (op, mode)));
}

static inline int
ext_register_operand_1 (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
#line 62 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
{
  if ((!TARGET_64BIT || GET_MODE (op) != DImode)
      && GET_MODE (op) != SImode && GET_MODE (op) != HImode)
    return false;
  if (GET_CODE (op) == SUBREG)
    op = SUBREG_REG (op);

  /* Be careful to accept only registers having upper parts.  */
  return (REG_P (op)
	  && (REGNO (op) > LAST_VIRTUAL_REGISTER || REGNO (op) <= BX_REG));
}

int
ext_register_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (register_operand (op, mode)) && (
(ext_register_operand_1 (op, mode)));
}

int
ax_reg_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return ((GET_CODE (op) == REG) && (
#line 77 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
(REGNO (op) == AX_REG))) && (
(mode == VOIDmode || GET_MODE (op) == mode));
}

int
flags_reg_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return ((GET_CODE (op) == REG) && (
#line 82 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
(REGNO (op) == FLAGS_REG))) && (
(mode == VOIDmode || GET_MODE (op) == mode));
}

int
QIreg_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (
#line 86 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
(QI_REG_P (op))) && (
(mode == VOIDmode || GET_MODE (op) == mode));
}

int
ext_QIreg_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return ((GET_CODE (op) == REG) && ((
#line 92 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
(TARGET_64BIT)) && (
#line 93 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
(REGNO (op) > BX_REG)))) && (
(mode == VOIDmode || GET_MODE (op) == mode));
}

static inline int
x86_64_immediate_operand_1 (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
#line 98 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
{
  if (!TARGET_64BIT)
    return immediate_operand (op, mode);

  switch (GET_CODE (op))
    {
    case CONST_INT:
      /* CONST_DOUBLES never match, since HOST_BITS_PER_WIDE_INT is known
         to be at least 32 and this all acceptable constants are
	 represented as CONST_INT.  */
      if (HOST_BITS_PER_WIDE_INT == 32)
	return true;
      else
	{
	  HOST_WIDE_INT val = trunc_int_for_mode (INTVAL (op), DImode);
	  return trunc_int_for_mode (val, SImode) == val;
	}
      break;

    case SYMBOL_REF:
      /* For certain code models, the symbolic references are known to fit.
	 in CM_SMALL_PIC model we know it fits if it is local to the shared
	 library.  Don't count TLS SYMBOL_REFs here, since they should fit
	 only if inside of UNSPEC handled below.  */
      /* TLS symbols are not constant.  */
      if (SYMBOL_REF_TLS_MODEL (op))
	return false;
      return (ix86_cmodel == CM_SMALL || ix86_cmodel == CM_KERNEL
	      || (ix86_cmodel == CM_MEDIUM && !SYMBOL_REF_FAR_ADDR_P (op)));

    case LABEL_REF:
      /* For certain code models, the code is near as well.  */
      return (ix86_cmodel == CM_SMALL || ix86_cmodel == CM_MEDIUM
	      || ix86_cmodel == CM_KERNEL);

    case CONST:
      /* We also may accept the offsetted memory references in certain
	 special cases.  */
      if (GET_CODE (XEXP (op, 0)) == UNSPEC)
	switch (XINT (XEXP (op, 0), 1))
	  {
	  case UNSPEC_GOTPCREL:
	  case UNSPEC_DTPOFF:
	  case UNSPEC_GOTNTPOFF:
	  case UNSPEC_NTPOFF:
	    return true;
	  default:
	    break;
	  }

      if (GET_CODE (XEXP (op, 0)) == PLUS)
	{
	  rtx op1 = XEXP (XEXP (op, 0), 0);
	  rtx op2 = XEXP (XEXP (op, 0), 1);
	  HOST_WIDE_INT offset;

	  if (ix86_cmodel == CM_LARGE)
	    return false;
	  if (!CONST_INT_P (op2))
	    return false;
	  offset = trunc_int_for_mode (INTVAL (op2), DImode);
	  switch (GET_CODE (op1))
	    {
	    case SYMBOL_REF:
	      /* TLS symbols are not constant.  */
	      if (SYMBOL_REF_TLS_MODEL (op1))
		return false;
	      /* For CM_SMALL assume that latest object is 16MB before
		 end of 31bits boundary.  We may also accept pretty
		 large negative constants knowing that all objects are
		 in the positive half of address space.  */
	      if ((ix86_cmodel == CM_SMALL
		   || (ix86_cmodel == CM_MEDIUM
		       && !SYMBOL_REF_FAR_ADDR_P (op1)))
		  && offset < 16*1024*1024
		  && trunc_int_for_mode (offset, SImode) == offset)
		return true;
	      /* For CM_KERNEL we know that all object resist in the
		 negative half of 32bits address space.  We may not
		 accept negative offsets, since they may be just off
		 and we may accept pretty large positive ones.  */
	      if (ix86_cmodel == CM_KERNEL
		  && offset > 0
		  && trunc_int_for_mode (offset, SImode) == offset)
		return true;
	      break;

	    case LABEL_REF:
	      /* These conditions are similar to SYMBOL_REF ones, just the
		 constraints for code models differ.  */
	      if ((ix86_cmodel == CM_SMALL || ix86_cmodel == CM_MEDIUM)
		  && offset < 16*1024*1024
		  && trunc_int_for_mode (offset, SImode) == offset)
		return true;
	      if (ix86_cmodel == CM_KERNEL
		  && offset > 0
		  && trunc_int_for_mode (offset, SImode) == offset)
		return true;
	      break;

	    case UNSPEC:
	      switch (XINT (op1, 1))
		{
		case UNSPEC_DTPOFF:
		case UNSPEC_NTPOFF:
		  if (trunc_int_for_mode (offset, SImode) == offset)
		    return true;
		}
	      break;

	    default:
	      break;
	    }
	}
      break;

      default:
	gcc_unreachable ();
    }

  return false;
}

int
x86_64_immediate_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  switch (GET_CODE (op))
    {
    case CONST_INT:
    case SYMBOL_REF:
    case LABEL_REF:
    case CONST:
      break;
    default:
      return false;
    }
  return 
(x86_64_immediate_operand_1 (op, mode));
}

static inline int
x86_64_zext_immediate_operand_1 (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
#line 224 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
{
  switch (GET_CODE (op))
    {
    case CONST_DOUBLE:
      if (HOST_BITS_PER_WIDE_INT == 32)
	return (GET_MODE (op) == VOIDmode && !CONST_DOUBLE_HIGH (op));
      else
	return false;

    case CONST_INT:
      if (HOST_BITS_PER_WIDE_INT == 32)
	return INTVAL (op) >= 0;
      else
	return !(INTVAL (op) & ~(HOST_WIDE_INT) 0xffffffff);

    case SYMBOL_REF:
      /* For certain code models, the symbolic references are known to fit.  */
      /* TLS symbols are not constant.  */
      if (SYMBOL_REF_TLS_MODEL (op))
	return false;
      return (ix86_cmodel == CM_SMALL
	      || (ix86_cmodel == CM_MEDIUM
		  && !SYMBOL_REF_FAR_ADDR_P (op)));

    case LABEL_REF:
      /* For certain code models, the code is near as well.  */
      return ix86_cmodel == CM_SMALL || ix86_cmodel == CM_MEDIUM;

    case CONST:
      /* We also may accept the offsetted memory references in certain
	 special cases.  */
      if (GET_CODE (XEXP (op, 0)) == PLUS)
	{
	  rtx op1 = XEXP (XEXP (op, 0), 0);
	  rtx op2 = XEXP (XEXP (op, 0), 1);

	  if (ix86_cmodel == CM_LARGE)
	    return false;
	  switch (GET_CODE (op1))
	    {
	    case SYMBOL_REF:
	      /* TLS symbols are not constant.  */
	      if (SYMBOL_REF_TLS_MODEL (op1))
		return false;
	      /* For small code model we may accept pretty large positive
		 offsets, since one bit is available for free.  Negative
		 offsets are limited by the size of NULL pointer area
		 specified by the ABI.  */
	      if ((ix86_cmodel == CM_SMALL
		   || (ix86_cmodel == CM_MEDIUM
		       && !SYMBOL_REF_FAR_ADDR_P (op1)))
		  && CONST_INT_P (op2)
		  && trunc_int_for_mode (INTVAL (op2), DImode) > -0x10000
		  && trunc_int_for_mode (INTVAL (op2), SImode) == INTVAL (op2))
		return true;
	      /* ??? For the kernel, we may accept adjustment of
		 -0x10000000, since we know that it will just convert
		 negative address space to positive, but perhaps this
		 is not worthwhile.  */
	      break;

	    case LABEL_REF:
	      /* These conditions are similar to SYMBOL_REF ones, just the
		 constraints for code models differ.  */
	      if ((ix86_cmodel == CM_SMALL || ix86_cmodel == CM_MEDIUM)
		  && CONST_INT_P (op2)
		  && trunc_int_for_mode (INTVAL (op2), DImode) > -0x10000
		  && trunc_int_for_mode (INTVAL (op2), SImode) == INTVAL (op2))
		return true;
	      break;

	    default:
	      return false;
	    }
	}
      break;

    default:
      gcc_unreachable ();
    }
  return false;
}

int
x86_64_zext_immediate_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  switch (GET_CODE (op))
    {
    case CONST_DOUBLE:
    case CONST_INT:
    case SYMBOL_REF:
    case LABEL_REF:
    case CONST:
      break;
    default:
      return false;
    }
  return 
(x86_64_zext_immediate_operand_1 (op, mode));
}

int
x86_64_general_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (
#line 309 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
(TARGET_64BIT)) ? ((nonimmediate_operand (op, mode)) || (x86_64_immediate_operand (op, mode))) : (general_operand (op, mode));
}

int
x86_64_zext_general_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (
#line 318 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
(TARGET_64BIT)) ? ((nonimmediate_operand (op, mode)) || ((x86_64_zext_immediate_operand (op, mode)) && (
#line 321 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
(GET_MODE (op) != VOIDmode)))) : (general_operand (op, mode));
}

int
x86_64_szext_general_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (
#line 327 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
(TARGET_64BIT)) ? ((nonimmediate_operand (op, mode)) || ((x86_64_immediate_operand (op, mode)) || (x86_64_zext_immediate_operand (op, mode)))) : (general_operand (op, mode));
}

int
x86_64_nonmemory_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (
#line 335 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
(TARGET_64BIT)) ? ((register_operand (op, mode)) || (x86_64_immediate_operand (op, mode))) : (nonmemory_operand (op, mode));
}

int
x86_64_szext_nonmemory_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (
#line 342 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
(TARGET_64BIT)) ? ((register_operand (op, mode)) || ((x86_64_immediate_operand (op, mode)) || (x86_64_zext_immediate_operand (op, mode)))) : (nonmemory_operand (op, mode));
}

static inline int
pic_32bit_operand_1 (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
#line 352 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
{
  if (!flag_pic)
    return false;

  /* Rule out relocations that translate into 64bit constants.  */
  if (TARGET_64BIT && GET_CODE (op) == CONST)
    {
      op = XEXP (op, 0);
      if (GET_CODE (op) == PLUS && CONST_INT_P (XEXP (op, 1)))
	op = XEXP (op, 0);
      if (GET_CODE (op) == UNSPEC
	  && (XINT (op, 1) == UNSPEC_GOTOFF
	      || XINT (op, 1) == UNSPEC_GOT))
	return false;
    }

  return symbolic_operand (op, mode);
}

int
pic_32bit_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  switch (GET_CODE (op))
    {
    case CONST:
    case SYMBOL_REF:
    case LABEL_REF:
      break;
    default:
      return false;
    }
  return (
(pic_32bit_operand_1 (op, mode))) && (
(mode == VOIDmode || GET_MODE (op) == mode));
}

int
x86_64_movabs_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (nonmemory_operand (op, mode)) && (!(pic_32bit_operand (op, mode)));
}

static inline int
symbolic_operand_1 (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
#line 380 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
{
  switch (GET_CODE (op))
    {
    case SYMBOL_REF:
    case LABEL_REF:
      return true;

    case CONST:
      op = XEXP (op, 0);
      if (GET_CODE (op) == SYMBOL_REF
	  || GET_CODE (op) == LABEL_REF
	  || (GET_CODE (op) == UNSPEC
	      && (XINT (op, 1) == UNSPEC_GOT
		  || XINT (op, 1) == UNSPEC_GOTOFF
		  || XINT (op, 1) == UNSPEC_PCREL
		  || XINT (op, 1) == UNSPEC_GOTPCREL)))
	return true;
      if (GET_CODE (op) != PLUS
	  || !CONST_INT_P (XEXP (op, 1)))
	return false;

      op = XEXP (op, 0);
      if (GET_CODE (op) == SYMBOL_REF
	  || GET_CODE (op) == LABEL_REF)
	return true;
      /* Only @GOTOFF gets offsets.  */
      if (GET_CODE (op) != UNSPEC
	  || XINT (op, 1) != UNSPEC_GOTOFF)
	return false;

      op = XVECEXP (op, 0, 0);
      if (GET_CODE (op) == SYMBOL_REF
	  || GET_CODE (op) == LABEL_REF)
	return true;
      return false;

    default:
      gcc_unreachable ();
    }
}

int
symbolic_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  switch (GET_CODE (op))
    {
    case SYMBOL_REF:
    case LABEL_REF:
    case CONST:
      break;
    default:
      return false;
    }
  return (
(symbolic_operand_1 (op, mode))) && (
(mode == VOIDmode || GET_MODE (op) == mode));
}

static inline int
local_symbolic_operand_1 (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
#line 424 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
{
  if (GET_CODE (op) == CONST
      && GET_CODE (XEXP (op, 0)) == PLUS
      && CONST_INT_P (XEXP (XEXP (op, 0), 1)))
    op = XEXP (XEXP (op, 0), 0);

  if (GET_CODE (op) == LABEL_REF)
    return true;

  if (GET_CODE (op) != SYMBOL_REF)
    return false;

  if (SYMBOL_REF_TLS_MODEL (op))
    return false;

  if (SYMBOL_REF_LOCAL_P (op))
    return true;

  /* There is, however, a not insubstantial body of code in the rest of
     the compiler that assumes it can just stick the results of
     ASM_GENERATE_INTERNAL_LABEL in a symbol_ref and have done.  */
  /* ??? This is a hack.  Should update the body of the compiler to
     always create a DECL an invoke targetm.encode_section_info.  */
  if (strncmp (XSTR (op, 0), internal_label_prefix,
	       internal_label_prefix_len) == 0)
    return true;

  return false;
}

int
local_symbolic_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  switch (GET_CODE (op))
    {
    case CONST:
    case LABEL_REF:
    case SYMBOL_REF:
      break;
    default:
      return false;
    }
  return (
(local_symbolic_operand_1 (op, mode))) && (
(mode == VOIDmode || GET_MODE (op) == mode));
}

int
gotoff_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (!(
#line 463 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
(TARGET_VXWORKS_RTP))) && (local_symbolic_operand (op, mode));
}

int
tls_symbolic_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (GET_CODE (op) == SYMBOL_REF) && (
#line 469 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
(SYMBOL_REF_TLS_MODEL (op)));
}

int
tls_modbase_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (GET_CODE (op) == SYMBOL_REF) && (
#line 473 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
(op == ix86_tls_module_base ()));
}

static inline int
constant_call_address_operand_1 (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
#line 478 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
{
  if (ix86_cmodel == CM_LARGE || ix86_cmodel == CM_LARGE_PIC)
    return false;
  if (TARGET_DLLIMPORT_DECL_ATTRIBUTES && SYMBOL_REF_DLLIMPORT_P (op))
    return false;
  return true;
}

int
constant_call_address_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return ((GET_CODE (op) == SYMBOL_REF) && (
(constant_call_address_operand_1 (op, mode)))) && (
(mode == VOIDmode || GET_MODE (op) == mode));
}

static inline int
call_register_no_elim_operand_1 (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
#line 492 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
{
  if (GET_CODE (op) == SUBREG)
    op = SUBREG_REG (op);

  if (!TARGET_64BIT && op == stack_pointer_rtx)
    return false;

  return register_no_elim_operand (op, mode);
}

int
call_register_no_elim_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (register_operand (op, mode)) && (
(call_register_no_elim_operand_1 (op, mode)));
}

static inline int
register_no_elim_operand_1 (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
#line 506 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
{
  if (GET_CODE (op) == SUBREG)
    op = SUBREG_REG (op);
  return !(op == arg_pointer_rtx
	   || op == frame_pointer_rtx
	   || IN_RANGE (REGNO (op),
			FIRST_PSEUDO_REGISTER, LAST_VIRTUAL_REGISTER));
}

int
register_no_elim_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (register_operand (op, mode)) && (
(register_no_elim_operand_1 (op, mode)));
}

static inline int
index_register_operand_1 (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
#line 519 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
{
  if (GET_CODE (op) == SUBREG)
    op = SUBREG_REG (op);
  if (reload_in_progress || reload_completed)
    return REG_OK_FOR_INDEX_STRICT_P (op);
  else
    return REG_OK_FOR_INDEX_NONSTRICT_P (op);
}

int
index_register_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (register_operand (op, mode)) && (
(index_register_operand_1 (op, mode)));
}

int
general_no_elim_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (GET_CODE (op) == REG || GET_CODE (op) == SUBREG) ? (register_no_elim_operand (op, mode)) : (general_operand (op, mode));
}

int
nonmemory_no_elim_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (register_no_elim_operand (op, mode)) || (immediate_operand (op, mode));
}

int
indirect_branch_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (register_operand (op, mode)) || ((!(
#line 543 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
(TARGET_X32))) && (memory_operand (op, mode)));
}

int
call_insn_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (
#line 549 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
(constant_call_address_operand
		     (op, mode == VOIDmode ? mode : Pmode))) || ((call_register_no_elim_operand (op, mode)) || ((!(
#line 552 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
(TARGET_X32))) && (memory_operand (op, mode))));
}

int
sibcall_insn_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (
#line 557 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
(constant_call_address_operand
		     (op, mode == VOIDmode ? mode : Pmode))) || (register_no_elim_operand (op, mode));
}

static inline int
const0_operand_1 (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
#line 564 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
{
  if (mode == VOIDmode)
    mode = GET_MODE (op);
  return op == CONST0_RTX (mode);
}

int
const0_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  switch (GET_CODE (op))
    {
    case CONST_INT:
    case CONST_DOUBLE:
    case CONST_VECTOR:
      break;
    default:
      return false;
    }
  return 
(const0_operand_1 (op, mode));
}

static inline int
const1_operand_1 (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
#line 573 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
{
  if (mode == VOIDmode)
    mode = GET_MODE (op);
  return op == CONST1_RTX (mode);
}

int
const1_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  switch (GET_CODE (op))
    {
    case CONST_INT:
    case CONST_DOUBLE:
    case CONST_VECTOR:
      break;
    default:
      return false;
    }
  return 
(const1_operand_1 (op, mode));
}

int
const8_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (GET_CODE (op) == CONST_INT) && (
#line 582 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
(INTVAL (op) == 8));
}

int
const128_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (GET_CODE (op) == CONST_INT) && (
#line 587 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
(INTVAL (op) == 128));
}

int
const_32bit_mask (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (GET_CODE (op) == CONST_INT) && (
#line 592 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
(trunc_int_for_mode (INTVAL (op), DImode)
		    == (HOST_WIDE_INT) 0xffffffff));
}

static inline int
const248_operand_1 (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
#line 598 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
{
  HOST_WIDE_INT i = INTVAL (op);
  return i == 2 || i == 4 || i == 8;
}

int
const248_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (GET_CODE (op) == CONST_INT) && (
(const248_operand_1 (op, mode)));
}

static inline int
const1248_operand_1 (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
#line 606 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
{
  HOST_WIDE_INT i = INTVAL (op);
  return i == 1 || i == 2 || i == 4 || i == 8;
}

int
const1248_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (GET_CODE (op) == CONST_INT) && (
(const1248_operand_1 (op, mode)));
}

static inline int
const359_operand_1 (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
#line 614 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
{
  HOST_WIDE_INT i = INTVAL (op);
  return i == 3 || i == 5 || i == 9;
}

int
const359_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (GET_CODE (op) == CONST_INT) && (
(const359_operand_1 (op, mode)));
}

int
const_0_to_1_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (GET_CODE (op) == CONST_INT) && ((
#line 622 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
(op == const0_rtx)) || (
#line 623 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
(op == const1_rtx)));
}

int
const_0_to_3_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (GET_CODE (op) == CONST_INT) && (
#line 628 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
(IN_RANGE (INTVAL (op), 0, 3)));
}

int
const_0_to_7_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (GET_CODE (op) == CONST_INT) && (
#line 633 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
(IN_RANGE (INTVAL (op), 0, 7)));
}

int
const_0_to_15_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (GET_CODE (op) == CONST_INT) && (
#line 638 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
(IN_RANGE (INTVAL (op), 0, 15)));
}

int
const_0_to_31_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (GET_CODE (op) == CONST_INT) && (
#line 643 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
(IN_RANGE (INTVAL (op), 0, 31)));
}

int
const_0_to_63_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (GET_CODE (op) == CONST_INT) && (
#line 648 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
(IN_RANGE (INTVAL (op), 0, 63)));
}

int
const_0_to_255_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (GET_CODE (op) == CONST_INT) && (
#line 653 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
(IN_RANGE (INTVAL (op), 0, 255)));
}

static inline int
const_0_to_255_mul_8_operand_1 (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
#line 658 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
{
  unsigned HOST_WIDE_INT val = INTVAL (op);
  return val <= 255*8 && val % 8 == 0;
}

int
const_0_to_255_mul_8_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (GET_CODE (op) == CONST_INT) && (
(const_0_to_255_mul_8_operand_1 (op, mode)));
}

int
const_1_to_31_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (GET_CODE (op) == CONST_INT) && (
#line 667 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
(IN_RANGE (INTVAL (op), 1, 31)));
}

int
const_1_to_63_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (GET_CODE (op) == CONST_INT) && (
#line 673 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
(IN_RANGE (INTVAL (op), 1, 63)));
}

int
const_2_to_3_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (GET_CODE (op) == CONST_INT) && (
#line 678 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
(IN_RANGE (INTVAL (op), 2, 3)));
}

int
const_4_to_5_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (GET_CODE (op) == CONST_INT) && (
#line 683 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
(IN_RANGE (INTVAL (op), 4, 5)));
}

int
const_4_to_7_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (GET_CODE (op) == CONST_INT) && (
#line 688 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
(IN_RANGE (INTVAL (op), 4, 7)));
}

int
const_6_to_7_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (GET_CODE (op) == CONST_INT) && (
#line 693 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
(IN_RANGE (INTVAL (op), 6, 7)));
}

int
const_8_to_11_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (GET_CODE (op) == CONST_INT) && (
#line 698 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
(IN_RANGE (INTVAL (op), 8, 11)));
}

int
const_12_to_15_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (GET_CODE (op) == CONST_INT) && (
#line 703 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
(IN_RANGE (INTVAL (op), 12, 15)));
}

static inline int
incdec_operand_1 (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
#line 708 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
{
  /* On Pentium4, the inc and dec operations causes extra dependency on flag
     registers, since carry flag is not set.  */
  if (!TARGET_USE_INCDEC && !optimize_insn_for_size_p ())
    return false;
  return op == const1_rtx || op == constm1_rtx;
}

int
incdec_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (GET_CODE (op) == CONST_INT) && (
(incdec_operand_1 (op, mode)));
}

int
reg_or_pm1_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (register_operand (op, mode)) || ((GET_CODE (op) == CONST_INT) && ((
#line 720 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
(op == const1_rtx)) || (
#line 721 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
(op == constm1_rtx))));
}

int
shiftdi_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (
#line 725 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
(TARGET_64BIT)) ? (nonimmediate_operand (op, mode)) : (register_operand (op, mode));
}

int
ashldi_input_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (
#line 730 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
(TARGET_64BIT)) ? (nonimmediate_operand (op, mode)) : (reg_or_pm1_operand (op, mode));
}

static inline int
zero_extended_scalar_load_operand_1 (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
#line 738 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
{
  unsigned n_elts;
  op = maybe_get_pool_constant (op);

  if (!(op && GET_CODE (op) == CONST_VECTOR))
    return false;

  n_elts = CONST_VECTOR_NUNITS (op);

  for (n_elts--; n_elts > 0; n_elts--)
    {
      rtx elt = CONST_VECTOR_ELT (op, n_elts);
      if (elt != CONST0_RTX (GET_MODE_INNER (GET_MODE (op))))
	return false;
    }
  return true;
}

int
zero_extended_scalar_load_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return ((GET_CODE (op) == MEM) && (
(zero_extended_scalar_load_operand_1 (op, mode)))) && (
(mode == VOIDmode || GET_MODE (op) == mode));
}

static inline int
vector_all_ones_operand_1 (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
#line 759 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
{
  int nunits = GET_MODE_NUNITS (mode);

  if (GET_CODE (op) == CONST_VECTOR
      && CONST_VECTOR_NUNITS (op) == nunits)
    {
      int i;
      for (i = 0; i < nunits; ++i)
        {
          rtx x = CONST_VECTOR_ELT (op, i);
          if (x != constm1_rtx)
            return false;
        }
      return true;
    }

  return false;
}

int
vector_all_ones_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return ((GET_CODE (op) == CONST_VECTOR) && (
(vector_all_ones_operand_1 (op, mode)))) && (
(mode == VOIDmode || GET_MODE (op) == mode));
}

int
vector_move_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (nonimmediate_operand (op, mode)) || (const0_operand (op, mode));
}

int
nonimmediate_or_const_vector_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (nonimmediate_operand (op, mode)) || ((GET_CODE (op) == CONST_VECTOR) && (
(mode == VOIDmode || GET_MODE (op) == mode)));
}

static inline int
nonimmediate_or_sse_const_operand_1 (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
#line 792 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
{
  if (nonimmediate_operand (op, mode))
    return true;
  if (standard_sse_constant_p (op) > 0)
    return true;
  return false;
}

int
nonimmediate_or_sse_const_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (general_operand (op, mode)) && (
(nonimmediate_or_sse_const_operand_1 (op, mode)));
}

int
reg_or_0_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (register_operand (op, mode)) || (const0_operand (op, mode));
}

static inline int
lea_address_operand_1 (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
#line 810 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
{
  struct ix86_address parts;
  int ok;

  ok = ix86_decompose_address (op, &parts);
  gcc_assert (ok);
  return parts.seg == SEG_DEFAULT;
}

int
lea_address_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (address_operand (op, mode)) && (
(lea_address_operand_1 (op, mode)));
}

int
SImode_address_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  switch (GET_CODE (op))
    {
    case SUBREG:
    case ZERO_EXTEND:
    case AND:
      break;
    default:
      return false;
    }
  return 
(mode == VOIDmode || GET_MODE (op) == mode);
}

static inline int
vsib_address_operand_1 (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
#line 827 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
{
  struct ix86_address parts;
  int ok;
  rtx disp;

  ok = ix86_decompose_address (op, &parts);
  gcc_assert (ok);
  if (parts.index || parts.seg != SEG_DEFAULT)
    return false;

  /* VSIB addressing doesn't support (%rip).  */
  if (parts.disp && GET_CODE (parts.disp) == CONST)
    {
      disp = XEXP (parts.disp, 0);
      if (GET_CODE (disp) == PLUS)
	disp = XEXP (disp, 0);
      if (GET_CODE (disp) == UNSPEC)
	switch (XINT (disp, 1))
	  {
	  case UNSPEC_GOTPCREL:
	  case UNSPEC_PCREL:
	  case UNSPEC_GOTNTPOFF:
	    return false;
	  }
    }

  return true;
}

int
vsib_address_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return ((address_operand (op, mode)) && (
(vsib_address_operand_1 (op, mode)))) && (
(mode == VOIDmode || GET_MODE (op) == mode));
}

int
vsib_mem_operator (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (GET_CODE (op) == MEM) && (
(mode == VOIDmode || GET_MODE (op) == mode));
}

static inline int
aligned_operand_1 (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
#line 862 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
{
  struct ix86_address parts;
  int ok;

  /* Registers and immediate operands are always "aligned".  */
  if (!MEM_P (op))
    return true;

  /* All patterns using aligned_operand on memory operands ends up
     in promoting memory operand to 64bit and thus causing memory mismatch.  */
  if (TARGET_MEMORY_MISMATCH_STALL && !optimize_insn_for_size_p ())
    return false;

  /* Don't even try to do any aligned optimizations with volatiles.  */
  if (MEM_VOLATILE_P (op))
    return false;

  if (MEM_ALIGN (op) >= 32)
    return true;

  op = XEXP (op, 0);

  /* Pushes and pops are only valid on the stack pointer.  */
  if (GET_CODE (op) == PRE_DEC
      || GET_CODE (op) == POST_INC)
    return true;

  /* Decode the address.  */
  ok = ix86_decompose_address (op, &parts);
  gcc_assert (ok);

  if (parts.base && GET_CODE (parts.base) == SUBREG)
    parts.base = SUBREG_REG (parts.base);
  if (parts.index && GET_CODE (parts.index) == SUBREG)
    parts.index = SUBREG_REG (parts.index);

  /* Look for some component that isn't known to be aligned.  */
  if (parts.index)
    {
      if (REGNO_POINTER_ALIGN (REGNO (parts.index)) * parts.scale < 32)
	return false;
    }
  if (parts.base)
    {
      if (REGNO_POINTER_ALIGN (REGNO (parts.base)) < 32)
	return false;
    }
  if (parts.disp)
    {
      if (!CONST_INT_P (parts.disp)
	  || (INTVAL (parts.disp) & 3))
	return false;
    }

  /* Didn't find one -- this must be an aligned address.  */
  return true;
}

int
aligned_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (general_operand (op, mode)) && (
(aligned_operand_1 (op, mode)));
}

static inline int
memory_displacement_operand_1 (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
#line 923 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
{
  struct ix86_address parts;
  int ok;

  ok = ix86_decompose_address (XEXP (op, 0), &parts);
  gcc_assert (ok);
  return parts.disp != NULL_RTX;
}

int
memory_displacement_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (memory_operand (op, mode)) && (
(memory_displacement_operand_1 (op, mode)));
}

static inline int
memory_displacement_only_operand_1 (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
#line 935 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
{
  struct ix86_address parts;
  int ok;

  if (TARGET_64BIT)
    return false;

  ok = ix86_decompose_address (XEXP (op, 0), &parts);
  gcc_assert (ok);

  if (parts.base || parts.index)
    return false;

  return parts.disp != NULL_RTX;
}

int
memory_displacement_only_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (memory_operand (op, mode)) && (
(memory_displacement_only_operand_1 (op, mode)));
}

static inline int
cmpxchg8b_pic_memory_operand_1 (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
#line 955 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
{
  struct ix86_address parts;
  int ok;

  if (TARGET_64BIT || !flag_pic)
    return true;

  ok = ix86_decompose_address (XEXP (op, 0), &parts);
  gcc_assert (ok);

  if (parts.base && GET_CODE (parts.base) == SUBREG)
    parts.base = SUBREG_REG (parts.base);
  if (parts.index && GET_CODE (parts.index) == SUBREG)
    parts.index = SUBREG_REG (parts.index);

  if (parts.base == NULL_RTX
      || parts.base == arg_pointer_rtx
      || parts.base == frame_pointer_rtx
      || parts.base == hard_frame_pointer_rtx
      || parts.base == stack_pointer_rtx)
    return true;

  if (parts.index == NULL_RTX
      || parts.index == arg_pointer_rtx
      || parts.index == frame_pointer_rtx
      || parts.index == hard_frame_pointer_rtx
      || parts.index == stack_pointer_rtx)
    return true;

  return false;
}

int
cmpxchg8b_pic_memory_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (memory_operand (op, mode)) && (
(cmpxchg8b_pic_memory_operand_1 (op, mode)));
}

int
long_memory_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (memory_operand (op, mode)) && (
#line 992 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
(memory_address_length (op, false)));
}

static inline int
fcmov_comparison_operator_1 (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
#line 997 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
{
  enum machine_mode inmode = GET_MODE (XEXP (op, 0));
  enum rtx_code code = GET_CODE (op);

  if (inmode == CCFPmode || inmode == CCFPUmode)
    {
      if (!ix86_trivial_fp_comparison_operator (op, mode))
	return false;
      code = ix86_fp_compare_code_to_integer (code);
    }
  /* i387 supports just limited amount of conditional codes.  */
  switch (code)
    {
    case LTU: case GTU: case LEU: case GEU:
      if (inmode == CCmode || inmode == CCFPmode || inmode == CCFPUmode
	  || inmode == CCCmode)
	return true;
      return false;
    case ORDERED: case UNORDERED:
    case EQ: case NE:
      return true;
    default:
      return false;
    }
}

int
fcmov_comparison_operator (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (comparison_operator (op, mode)) && (
(fcmov_comparison_operator_1 (op, mode)));
}

int
sse_comparison_operator (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return ((GET_CODE (op) == EQ || GET_CODE (op) == NE || GET_CODE (op) == LT || GET_CODE (op) == LE || GET_CODE (op) == UNORDERED || GET_CODE (op) == UNGE || GET_CODE (op) == UNGT || GET_CODE (op) == ORDERED) || ((
#line 1029 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
(TARGET_AVX)) && (GET_CODE (op) == GE || GET_CODE (op) == GT || GET_CODE (op) == UNEQ || GET_CODE (op) == UNLE || GET_CODE (op) == UNLT || GET_CODE (op) == LTGT))) && (
(mode == VOIDmode || GET_MODE (op) == mode));
}

int
ix86_comparison_int_operator (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  switch (GET_CODE (op))
    {
    case NE:
    case EQ:
    case GE:
    case GT:
    case LE:
    case LT:
      break;
    default:
      return false;
    }
  return 
(mode == VOIDmode || GET_MODE (op) == mode);
}

int
ix86_comparison_uns_operator (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  switch (GET_CODE (op))
    {
    case NE:
    case EQ:
    case GEU:
    case GTU:
    case LEU:
    case LTU:
      break;
    default:
      return false;
    }
  return 
(mode == VOIDmode || GET_MODE (op) == mode);
}

int
bt_comparison_operator (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  switch (GET_CODE (op))
    {
    case NE:
    case EQ:
      break;
    default:
      return false;
    }
  return 
(mode == VOIDmode || GET_MODE (op) == mode);
}

static inline int
ix86_comparison_operator_1 (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
#line 1044 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
{
  enum machine_mode inmode = GET_MODE (XEXP (op, 0));
  enum rtx_code code = GET_CODE (op);

  if (inmode == CCFPmode || inmode == CCFPUmode)
    return ix86_trivial_fp_comparison_operator (op, mode);

  switch (code)
    {
    case EQ: case NE:
      return true;
    case LT: case GE:
      if (inmode == CCmode || inmode == CCGCmode
	  || inmode == CCGOCmode || inmode == CCNOmode)
	return true;
      return false;
    case LTU: case GTU: case LEU: case GEU:
      if (inmode == CCmode || inmode == CCCmode)
	return true;
      return false;
    case ORDERED: case UNORDERED:
      if (inmode == CCmode)
	return true;
      return false;
    case GT: case LE:
      if (inmode == CCmode || inmode == CCGCmode || inmode == CCNOmode)
	return true;
      return false;
    default:
      return false;
    }
}

int
ix86_comparison_operator (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (comparison_operator (op, mode)) && (
(ix86_comparison_operator_1 (op, mode)));
}

static inline int
ix86_carry_flag_operator_1 (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
#line 1081 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
{
  enum machine_mode inmode = GET_MODE (XEXP (op, 0));
  enum rtx_code code = GET_CODE (op);

  if (inmode == CCFPmode || inmode == CCFPUmode)
    {
      if (!ix86_trivial_fp_comparison_operator (op, mode))
	return false;
      code = ix86_fp_compare_code_to_integer (code);
    }
  else if (inmode == CCCmode)
   return code == LTU || code == GTU;
  else if (inmode != CCmode)
    return false;

  return code == LTU;
}

int
ix86_carry_flag_operator (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  switch (GET_CODE (op))
    {
    case LTU:
    case LT:
    case UNLT:
    case GTU:
    case GT:
    case UNGT:
    case LE:
    case UNLE:
    case GE:
    case UNGE:
    case LTGT:
    case UNEQ:
      break;
    default:
      return false;
    }
  return (
(ix86_carry_flag_operator_1 (op, mode))) && (
(mode == VOIDmode || GET_MODE (op) == mode));
}

int
ix86_trivial_fp_comparison_operator (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  switch (GET_CODE (op))
    {
    case GT:
    case GE:
    case UNLT:
    case UNLE:
    case UNEQ:
    case LTGT:
    case ORDERED:
    case UNORDERED:
      break;
    default:
      return false;
    }
  return 
(mode == VOIDmode || GET_MODE (op) == mode);
}

int
ix86_fp_comparison_operator (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (
#line 1107 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
(ix86_fp_comparison_strategy (GET_CODE (op))
                             == IX86_FPCMP_ARITH)) ? (comparison_operator (op, mode)) : (ix86_trivial_fp_comparison_operator (op, mode));
}

static inline int
ix86_swapped_fp_comparison_operator_1 (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
#line 1115 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
{
  enum rtx_code code = GET_CODE (op);
  bool ret;

  PUT_CODE (op, swap_condition (code));
  ret = ix86_fp_comparison_operator (op, mode);
  PUT_CODE (op, code);
  return ret;
}

int
ix86_swapped_fp_comparison_operator (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (comparison_operator (op, mode)) && (
(ix86_swapped_fp_comparison_operator_1 (op, mode)));
}

int
cmp_fp_expander_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (GET_CODE (op) == CONST_DOUBLE) || (general_operand (op, mode));
}

int
binary_fp_operator (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  switch (GET_CODE (op))
    {
    case PLUS:
    case MINUS:
    case MULT:
    case DIV:
      break;
    default:
      return false;
    }
  return 
(mode == VOIDmode || GET_MODE (op) == mode);
}

int
mult_operator (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (GET_CODE (op) == MULT) && (
(mode == VOIDmode || GET_MODE (op) == mode));
}

int
div_operator (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (GET_CODE (op) == DIV) && (
(mode == VOIDmode || GET_MODE (op) == mode));
}

int
plusminuslogic_operator (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  switch (GET_CODE (op))
    {
    case PLUS:
    case MINUS:
    case AND:
    case IOR:
    case XOR:
      break;
    default:
      return false;
    }
  return 
(mode == VOIDmode || GET_MODE (op) == mode);
}

int
float_operator (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (GET_CODE (op) == FLOAT) && (
(mode == VOIDmode || GET_MODE (op) == mode));
}

int
arith_or_logical_operator (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  switch (GET_CODE (op))
    {
    case PLUS:
    case MULT:
    case AND:
    case IOR:
    case XOR:
    case SMIN:
    case SMAX:
    case UMIN:
    case UMAX:
    case COMPARE:
    case MINUS:
    case DIV:
    case MOD:
    case UDIV:
    case UMOD:
    case ASHIFT:
    case ROTATE:
    case ASHIFTRT:
    case LSHIFTRT:
    case ROTATERT:
      break;
    default:
      return false;
    }
  return 
(mode == VOIDmode || GET_MODE (op) == mode);
}

int
commutative_operator (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  switch (GET_CODE (op))
    {
    case PLUS:
    case MULT:
    case AND:
    case IOR:
    case XOR:
    case SMIN:
    case SMAX:
    case UMIN:
    case UMAX:
      break;
    default:
      return false;
    }
  return 
(mode == VOIDmode || GET_MODE (op) == mode);
}

int
promotable_binary_operator (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return ((GET_CODE (op) == PLUS || GET_CODE (op) == MINUS || GET_CODE (op) == AND || GET_CODE (op) == IOR || GET_CODE (op) == XOR || GET_CODE (op) == ASHIFT) || ((GET_CODE (op) == MULT) && (
#line 1165 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
(TARGET_TUNE_PROMOTE_HIMODE_IMUL)))) && (
(mode == VOIDmode || GET_MODE (op) == mode));
}

int
compare_operator (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (GET_CODE (op) == COMPARE) && (
(mode == VOIDmode || GET_MODE (op) == mode));
}

int
absneg_operator (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  switch (GET_CODE (op))
    {
    case ABS:
    case NEG:
      break;
    default:
      return false;
    }
  return 
(mode == VOIDmode || GET_MODE (op) == mode);
}

int
misaligned_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return ((GET_CODE (op) == MEM) && (
#line 1176 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
(MEM_ALIGN (op) < GET_MODE_ALIGNMENT (mode)))) && (
(mode == VOIDmode || GET_MODE (op) == mode));
}

static inline int
emms_operation_1 (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
#line 1181 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
{
  unsigned i;

  if (XVECLEN (op, 0) != 17)
    return false;

  for (i = 0; i < 8; i++)
    {
      rtx elt = XVECEXP (op, 0, i+1);

      if (GET_CODE (elt) != CLOBBER
	  || GET_CODE (SET_DEST (elt)) != REG
	  || GET_MODE (SET_DEST (elt)) != XFmode
	  || REGNO (SET_DEST (elt)) != FIRST_STACK_REG + i)
        return false;

      elt = XVECEXP (op, 0, i+9);

      if (GET_CODE (elt) != CLOBBER
	  || GET_CODE (SET_DEST (elt)) != REG
	  || GET_MODE (SET_DEST (elt)) != DImode
	  || REGNO (SET_DEST (elt)) != FIRST_MMX_REG + i)
	return false;
    }
  return true;
}

int
emms_operation (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return ((GET_CODE (op) == PARALLEL) && (
(emms_operation_1 (op, mode)))) && (
(mode == VOIDmode || GET_MODE (op) == mode));
}

static inline int
vzeroall_operation_1 (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
#line 1211 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
{
  unsigned i, nregs = TARGET_64BIT ? 16 : 8;

  if ((unsigned) XVECLEN (op, 0) != 1 + nregs)
    return false;

  for (i = 0; i < nregs; i++)
    {
      rtx elt = XVECEXP (op, 0, i+1);

      if (GET_CODE (elt) != SET
	  || GET_CODE (SET_DEST (elt)) != REG
	  || GET_MODE (SET_DEST (elt)) != V8SImode
	  || REGNO (SET_DEST (elt)) != SSE_REGNO (i)
	  || SET_SRC (elt) != CONST0_RTX (V8SImode))
	return false;
    }
  return true;
}

int
vzeroall_operation (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return ((GET_CODE (op) == PARALLEL) && (
(vzeroall_operation_1 (op, mode)))) && (
(mode == VOIDmode || GET_MODE (op) == mode));
}

int
vzeroupper_operation (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return ((GET_CODE (op) == UNSPEC_VOLATILE) && (
#line 1234 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
(XINT (op, 1) == UNSPECV_VZEROUPPER))) && (
(mode == VOIDmode || GET_MODE (op) == mode));
}

static inline int
avx_vbroadcast_operand_1 (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
#line 1241 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
{
  rtx elt = XVECEXP (op, 0, 0);
  int i, nelt = XVECLEN (op, 0);

  /* Don't bother checking there are the right number of operands,
     merely that they're all identical.  */
  for (i = 1; i < nelt; ++i)
    if (XVECEXP (op, 0, i) != elt)
      return false;
  return true;
}

int
avx_vbroadcast_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (((GET_CODE (op) == PARALLEL) && (GET_CODE (XVECEXP (op, 0, 0)) == CONST_INT)) && (
(avx_vbroadcast_operand_1 (op, mode)))) && (
(mode == VOIDmode || GET_MODE (op) == mode));
}

static inline int
avx2_pblendw_operand_1 (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
#line 1256 "../../gcc-4.8.1/gcc/config/i386/predicates.md"
{
  HOST_WIDE_INT val = INTVAL (op);
  HOST_WIDE_INT low = val & 0xff;
  return val == ((low << 8) | low);
}

int
avx2_pblendw_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (GET_CODE (op) == CONST_INT) && (
(avx2_pblendw_operand_1 (op, mode)));
}

enum constraint_num
lookup_constraint (const char *str)
{
  switch (str[0])
    {
    case 'A':
      return CONSTRAINT_A;
    case 'C':
      return CONSTRAINT_C;
    case 'D':
      return CONSTRAINT_D;
    case 'G':
      return CONSTRAINT_G;
    case 'I':
      return CONSTRAINT_I;
    case 'J':
      return CONSTRAINT_J;
    case 'K':
      return CONSTRAINT_K;
    case 'L':
      return CONSTRAINT_L;
    case 'M':
      return CONSTRAINT_M;
    case 'N':
      return CONSTRAINT_N;
    case 'O':
      return CONSTRAINT_O;
    case 'Q':
      return CONSTRAINT_Q;
    case 'R':
      return CONSTRAINT_R;
    case 'S':
      return CONSTRAINT_S;
    case 'U':
      return CONSTRAINT_U;
    case 'W':
      if (!strncmp (str + 1, "z", 1))
        return CONSTRAINT_Wz;
      break;
    case 'Y':
      if (!strncmp (str + 1, "i", 1))
        return CONSTRAINT_Yi;
      if (!strncmp (str + 1, "m", 1))
        return CONSTRAINT_Ym;
      if (!strncmp (str + 1, "p", 1))
        return CONSTRAINT_Yp;
      if (!strncmp (str + 1, "a", 1))
        return CONSTRAINT_Ya;
      if (!strncmp (str + 1, "d", 1))
        return CONSTRAINT_Yd;
      if (!strncmp (str + 1, "x", 1))
        return CONSTRAINT_Yx;
      if (!strncmp (str + 1, "f", 1))
        return CONSTRAINT_Yf;
      if (!strncmp (str + 1, "z", 1))
        return CONSTRAINT_Yz;
      break;
    case 'Z':
      return CONSTRAINT_Z;
    case 'a':
      return CONSTRAINT_a;
    case 'b':
      return CONSTRAINT_b;
    case 'c':
      return CONSTRAINT_c;
    case 'd':
      return CONSTRAINT_d;
    case 'e':
      return CONSTRAINT_e;
    case 'f':
      return CONSTRAINT_f;
    case 'l':
      return CONSTRAINT_l;
    case 'q':
      return CONSTRAINT_q;
    case 't':
      return CONSTRAINT_t;
    case 'u':
      return CONSTRAINT_u;
    case 'w':
      return CONSTRAINT_w;
    case 'x':
      return CONSTRAINT_x;
    case 'y':
      return CONSTRAINT_y;
    case 'z':
      return CONSTRAINT_z;
    default: break;
    }
  return CONSTRAINT__UNKNOWN;
}

enum reg_class
regclass_for_constraint (enum constraint_num c)
{
  switch (c)
    {
    case CONSTRAINT_R: return LEGACY_REGS;
    case CONSTRAINT_q: return TARGET_64BIT ? GENERAL_REGS : Q_REGS;
    case CONSTRAINT_Q: return Q_REGS;
    case CONSTRAINT_l: return INDEX_REGS;
    case CONSTRAINT_a: return AREG;
    case CONSTRAINT_b: return BREG;
    case CONSTRAINT_c: return CREG;
    case CONSTRAINT_d: return DREG;
    case CONSTRAINT_S: return SIREG;
    case CONSTRAINT_D: return DIREG;
    case CONSTRAINT_A: return AD_REGS;
    case CONSTRAINT_U: return CLOBBERED_REGS;
    case CONSTRAINT_f: return TARGET_80387 || TARGET_FLOAT_RETURNS_IN_80387 ? FLOAT_REGS : NO_REGS;
    case CONSTRAINT_t: return TARGET_80387 || TARGET_FLOAT_RETURNS_IN_80387 ? FP_TOP_REG : NO_REGS;
    case CONSTRAINT_u: return TARGET_80387 || TARGET_FLOAT_RETURNS_IN_80387 ? FP_SECOND_REG : NO_REGS;
    case CONSTRAINT_y: return TARGET_MMX ? MMX_REGS : NO_REGS;
    case CONSTRAINT_x: return TARGET_SSE ? SSE_REGS : NO_REGS;
    case CONSTRAINT_Yz: return TARGET_SSE ? SSE_FIRST_REG : NO_REGS;
    case CONSTRAINT_Yi: return TARGET_SSE2 && TARGET_INTER_UNIT_MOVES ? SSE_REGS : NO_REGS;
    case CONSTRAINT_Ym: return TARGET_MMX && TARGET_INTER_UNIT_MOVES ? MMX_REGS : NO_REGS;
    case CONSTRAINT_Yp: return TARGET_PARTIAL_REG_STALL ? NO_REGS : GENERAL_REGS;
    case CONSTRAINT_Ya: return TARGET_ZERO_EXTEND_WITH_AND && optimize_function_for_speed_p (cfun)
  ? NO_REGS : GENERAL_REGS;
    case CONSTRAINT_Yd: return (TARGET_64BIT
   || (TARGET_INTEGER_DFMODE_MOVES && optimize_function_for_speed_p (cfun)))
  ? GENERAL_REGS : NO_REGS;
    case CONSTRAINT_Yx: return optimize_function_for_speed_p (cfun) ? GENERAL_REGS : NO_REGS;
    case CONSTRAINT_Yf: return (ix86_fpmath & FPMATH_387) ? FLOAT_REGS : NO_REGS;
    default: break;
    }
  return NO_REGS;
}

bool
constraint_satisfied_p (rtx op, enum constraint_num c)
{
  switch (c)
    {
    case CONSTRAINT_z: return satisfies_constraint_z (op);
    case CONSTRAINT_w: return satisfies_constraint_w (op);
    case CONSTRAINT_I: return satisfies_constraint_I (op);
    case CONSTRAINT_J: return satisfies_constraint_J (op);
    case CONSTRAINT_K: return satisfies_constraint_K (op);
    case CONSTRAINT_L: return satisfies_constraint_L (op);
    case CONSTRAINT_M: return satisfies_constraint_M (op);
    case CONSTRAINT_N: return satisfies_constraint_N (op);
    case CONSTRAINT_O: return satisfies_constraint_O (op);
    case CONSTRAINT_G: return satisfies_constraint_G (op);
    case CONSTRAINT_C: return satisfies_constraint_C (op);
    case CONSTRAINT_e: return satisfies_constraint_e (op);
    case CONSTRAINT_Wz: return satisfies_constraint_Wz (op);
    case CONSTRAINT_Z: return satisfies_constraint_Z (op);
    default: break;
    }
  return false;
}

bool
insn_const_int_ok_for_constraint (HOST_WIDE_INT ival, enum constraint_num c)
{
  switch (c)
    {
    case CONSTRAINT_I:
      return 
#line 145 "../../gcc-4.8.1/gcc/config/i386/constraints.md"
(IN_RANGE (ival, 0, 31));

    case CONSTRAINT_J:
      return 
#line 150 "../../gcc-4.8.1/gcc/config/i386/constraints.md"
(IN_RANGE (ival, 0, 63));

    case CONSTRAINT_K:
      return 
#line 155 "../../gcc-4.8.1/gcc/config/i386/constraints.md"
(IN_RANGE (ival, -128, 127));

    case CONSTRAINT_L:
      return 
#line 161 "../../gcc-4.8.1/gcc/config/i386/constraints.md"
(ival == 0xff || ival == 0xffff
		    || ival == (HOST_WIDE_INT) 0xffffffff);

    case CONSTRAINT_M:
      return 
#line 167 "../../gcc-4.8.1/gcc/config/i386/constraints.md"
(IN_RANGE (ival, 0, 3));

    case CONSTRAINT_N:
      return 
#line 173 "../../gcc-4.8.1/gcc/config/i386/constraints.md"
(IN_RANGE (ival, 0, 255));

    case CONSTRAINT_O:
      return 
#line 178 "../../gcc-4.8.1/gcc/config/i386/constraints.md"
(IN_RANGE (ival, 0, 127));

    default: break;
    }
  return false;
}

