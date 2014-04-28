/* Generated automatically by the program `genattrtab'
   from the machine description file `md'.  */

#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "tm.h"
#include "rtl.h"
#include "insn-attr.h"
#include "tm_p.h"
#include "insn-config.h"
#include "recog.h"
#include "regs.h"
#include "real.h"
#include "output.h"
#include "toplev.h"
#include "flags.h"
#include "function.h"

#define operands recog_data.operand

extern int internal_dfa_insn_code_btver2 (rtx);
extern int insn_default_latency_btver2 (rtx);
extern int internal_dfa_insn_code_btver1 (rtx);
extern int insn_default_latency_btver1 (rtx);
extern int internal_dfa_insn_code_bdver3 (rtx);
extern int insn_default_latency_bdver3 (rtx);
extern int internal_dfa_insn_code_bdver2 (rtx);
extern int insn_default_latency_bdver2 (rtx);
extern int internal_dfa_insn_code_bdver1 (rtx);
extern int insn_default_latency_bdver1 (rtx);
extern int internal_dfa_insn_code_amdfam10 (rtx);
extern int insn_default_latency_amdfam10 (rtx);
extern int internal_dfa_insn_code_generic64 (rtx);
extern int insn_default_latency_generic64 (rtx);
extern int internal_dfa_insn_code_atom (rtx);
extern int insn_default_latency_atom (rtx);
extern int internal_dfa_insn_code_corei7 (rtx);
extern int insn_default_latency_corei7 (rtx);
extern int internal_dfa_insn_code_core2 (rtx);
extern int insn_default_latency_core2 (rtx);
extern int internal_dfa_insn_code_k8 (rtx);
extern int insn_default_latency_k8 (rtx);
extern int internal_dfa_insn_code_athlon (rtx);
extern int insn_default_latency_athlon (rtx);
extern int internal_dfa_insn_code_k6 (rtx);
extern int insn_default_latency_k6 (rtx);
extern int internal_dfa_insn_code_geode (rtx);
extern int insn_default_latency_geode (rtx);
extern int internal_dfa_insn_code_pentiumpro (rtx);
extern int insn_default_latency_pentiumpro (rtx);
extern int internal_dfa_insn_code_pentium (rtx);
extern int insn_default_latency_pentium (rtx);
extern int internal_dfa_insn_code_none (rtx);
extern int insn_default_latency_none (rtx);

int (*internal_dfa_insn_code) (rtx);
int (*insn_default_latency) (rtx);

void
init_sched_attrs (void)
{
  if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_BTVER2)))))
    {
      internal_dfa_insn_code
        = internal_dfa_insn_code_btver2;
      insn_default_latency
        = insn_default_latency_btver2;
    }
  else if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_BTVER1)))))
    {
      internal_dfa_insn_code
        = internal_dfa_insn_code_btver1;
      insn_default_latency
        = insn_default_latency_btver1;
    }
  else if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_BDVER3)))))
    {
      internal_dfa_insn_code
        = internal_dfa_insn_code_bdver3;
      insn_default_latency
        = insn_default_latency_bdver3;
    }
  else if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_BDVER2)))))
    {
      internal_dfa_insn_code
        = internal_dfa_insn_code_bdver2;
      insn_default_latency
        = insn_default_latency_bdver2;
    }
  else if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_BDVER1)))))
    {
      internal_dfa_insn_code
        = internal_dfa_insn_code_bdver1;
      insn_default_latency
        = insn_default_latency_bdver1;
    }
  else if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_AMDFAM10)))))
    {
      internal_dfa_insn_code
        = internal_dfa_insn_code_amdfam10;
      insn_default_latency
        = insn_default_latency_amdfam10;
    }
  else if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_GENERIC64)))))
    {
      internal_dfa_insn_code
        = internal_dfa_insn_code_generic64;
      insn_default_latency
        = insn_default_latency_generic64;
    }
  else if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_ATOM)))))
    {
      internal_dfa_insn_code
        = internal_dfa_insn_code_atom;
      insn_default_latency
        = insn_default_latency_atom;
    }
  else if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_COREI7)))))
    {
      internal_dfa_insn_code
        = internal_dfa_insn_code_corei7;
      insn_default_latency
        = insn_default_latency_corei7;
    }
  else if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_CORE2)))))
    {
      internal_dfa_insn_code
        = internal_dfa_insn_code_core2;
      insn_default_latency
        = insn_default_latency_core2;
    }
  else if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_K8)))))
    {
      internal_dfa_insn_code
        = internal_dfa_insn_code_k8;
      insn_default_latency
        = insn_default_latency_k8;
    }
  else if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_ATHLON)))))
    {
      internal_dfa_insn_code
        = internal_dfa_insn_code_athlon;
      insn_default_latency
        = insn_default_latency_athlon;
    }
  else if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_K6)))))
    {
      internal_dfa_insn_code
        = internal_dfa_insn_code_k6;
      insn_default_latency
        = insn_default_latency_k6;
    }
  else if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_GEODE)))))
    {
      internal_dfa_insn_code
        = internal_dfa_insn_code_geode;
      insn_default_latency
        = insn_default_latency_geode;
    }
  else if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_PENTIUMPRO)))))
    {
      internal_dfa_insn_code
        = internal_dfa_insn_code_pentiumpro;
      insn_default_latency
        = insn_default_latency_pentiumpro;
    }
  else if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_PENTIUM)))))
    {
      internal_dfa_insn_code
        = internal_dfa_insn_code_pentium;
      insn_default_latency
        = insn_default_latency_pentium;
    }
  else if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_NONE)))))
    {
      internal_dfa_insn_code
        = internal_dfa_insn_code_none;
      insn_default_latency
        = insn_default_latency_none;
    }
  else
    gcc_unreachable ();
}

int
insn_current_length (rtx insn ATTRIBUTE_UNUSED)
{
  switch (recog_memoized (insn))
    {
    case 541:  /* jump */
      extract_insn_cached (insn);
      if ((((INSN_ADDRESSES_SET_P () ? INSN_ADDRESSES (INSN_UID (GET_CODE (operands[0]) == LABEL_REF ? XEXP (operands[0], 0) : operands[0])) : 0) - (insn_current_reference_address (insn))) >= (-126)) && (((INSN_ADDRESSES_SET_P () ? INSN_ADDRESSES (INSN_UID (GET_CODE (operands[0]) == LABEL_REF ? XEXP (operands[0], 0) : operands[0])) : 0) - (insn_current_reference_address (insn))) < (128)))
        {
	  return 2;
        }
      else
        {
	  return 5;
        }

    case 504:  /* *jcc_2 */
      extract_insn_cached (insn);
      if ((((INSN_ADDRESSES_SET_P () ? INSN_ADDRESSES (INSN_UID (GET_CODE (operands[0]) == LABEL_REF ? XEXP (operands[0], 0) : operands[0])) : 0) - (insn_current_reference_address (insn))) >= (-126)) && (((INSN_ADDRESSES_SET_P () ? INSN_ADDRESSES (INSN_UID (GET_CODE (operands[0]) == LABEL_REF ? XEXP (operands[0], 0) : operands[0])) : 0) - (insn_current_reference_address (insn))) < (128)))
        {
	  return 2;
        }
      else
        {
	  return 6;
        }

    case 503:  /* *jcc_1 */
      extract_insn_cached (insn);
      if ((((INSN_ADDRESSES_SET_P () ? INSN_ADDRESSES (INSN_UID (GET_CODE (operands[0]) == LABEL_REF ? XEXP (operands[0], 0) : operands[0])) : 0) - (insn_current_reference_address (insn))) >= (-126)) && (((INSN_ADDRESSES_SET_P () ? INSN_ADDRESSES (INSN_UID (GET_CODE (operands[0]) == LABEL_REF ? XEXP (operands[0], 0) : operands[0])) : 0) - (insn_current_reference_address (insn))) < (128)))
        {
	  return 2;
        }
      else
        {
	  return 6;
        }

    case -1:
      if (GET_CODE (PATTERN (insn)) != ASM_INPUT
          && asm_noperands (PATTERN (insn)) < 0)
        fatal_insn_not_found (insn);
    default:
      return 0;

    }
}

int
insn_variable_length_p (rtx insn ATTRIBUTE_UNUSED)
{
  switch (recog_memoized (insn))
    {
    case 541:  /* jump */
    case 504:  /* *jcc_2 */
    case 503:  /* *jcc_1 */
      return 1;

    case -1:
      if (GET_CODE (PATTERN (insn)) != ASM_INPUT
          && asm_noperands (PATTERN (insn)) < 0)
        fatal_insn_not_found (insn);
    default:
      return 0;

    }
}

int
insn_min_length (rtx insn ATTRIBUTE_UNUSED)
{
  enum attr_type cached_type ATTRIBUTE_UNUSED;
  enum attr_prefix cached_prefix ATTRIBUTE_UNUSED;

  switch (recog_memoized (insn))
    {
    case 868:  /* *vec_extractv2sf_1 */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 4)
        {
	  return 2 + get_attr_prefix_data16 (insn) + get_attr_length_address (insn);
        }
      else
        {
	  return get_attr_modrm (insn) + get_attr_prefix_0f (insn) + get_attr_prefix_rex (insn) + get_attr_prefix_extra (insn) + 1 + get_attr_prefix_rep (insn) + get_attr_prefix_data16 (insn) + get_attr_length_immediate (insn) + get_attr_length_address (insn);
        }

    case 778:  /* *movsfcc_1_387 */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return 2 + get_attr_prefix_data16 (insn) + get_attr_length_address (insn);
        }
      else
        {
	  return get_attr_modrm (insn) + get_attr_prefix_0f (insn) + get_attr_prefix_rex (insn) + get_attr_prefix_extra (insn) + 1 + get_attr_prefix_rep (insn) + get_attr_prefix_data16 (insn) + get_attr_length_immediate (insn) + get_attr_length_address (insn);
        }

    case 187:  /* *floatsidf2_vector_mixed */
    case 186:  /* *floatsisf2_vector_mixed */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return 2 + get_attr_prefix_data16 (insn) + get_attr_length_address (insn);
        }
      else
        {
	  return get_attr_modrm (insn) + get_attr_prefix_0f (insn) + get_attr_prefix_rex (insn) + get_attr_prefix_extra (insn) + 1 + get_attr_prefix_rep (insn) + get_attr_prefix_data16 (insn) + get_attr_length_immediate (insn) + get_attr_length_address (insn);
        }

    case 217:  /* *floatdixf2_i387_with_temp */
    case 216:  /* *floatdidf2_i387_with_temp */
    case 215:  /* *floatdisf2_i387_with_temp */
    case 214:  /* *floatsixf2_i387_with_temp */
    case 213:  /* *floatsidf2_i387_with_temp */
    case 212:  /* *floatsisf2_i387_with_temp */
    case 174:  /* *floathixf2_i387_with_temp */
    case 173:  /* *floathidf2_i387_with_temp */
    case 172:  /* *floathisf2_i387_with_temp */
    case 140:  /* *truncxfdf2_mixed */
    case 139:  /* *truncxfsf2_mixed */
    case 137:  /* *truncdfsf_i387 */
      extract_constrain_insn_cached (insn);
      if (which_alternative != 0)
        {
	  return 16 /* 0x10 */;
        }
      else
        {
	  return 2 + get_attr_prefix_data16 (insn) + get_attr_length_address (insn);
        }

    case 1877:  /* storedi_via_fpu */
    case 1876:  /* loaddi_via_fpu */
    case 776:  /* *movxfcc_1 */
    case 710:  /* fistsi2_with_temp */
    case 709:  /* fisthi2_with_temp */
    case 708:  /* fistsi2 */
    case 707:  /* fisthi2 */
    case 706:  /* *fistsi2_1 */
    case 705:  /* *fisthi2_1 */
    case 704:  /* fistdi2_with_temp */
    case 703:  /* fistdi2 */
    case 702:  /* *fistdi2_1 */
    case 701:  /* rintxf2 */
    case 698:  /* *fscalexf4_i387 */
    case 697:  /* *f2xm1xf2_i387 */
    case 696:  /* fxtract_extenddfxf3_i387 */
    case 695:  /* fxtract_extendsfxf3_i387 */
    case 694:  /* fxtractxf3_i387 */
    case 693:  /* fyl2xp1_extenddfxf3_i387 */
    case 692:  /* fyl2xp1_extendsfxf3_i387 */
    case 691:  /* fyl2xp1xf3_i387 */
    case 690:  /* fyl2x_extenddfxf3_i387 */
    case 689:  /* fyl2x_extendsfxf3_i387 */
    case 688:  /* fyl2xxf3_i387 */
    case 687:  /* fpatan_extenddfxf3_i387 */
    case 686:  /* fpatan_extendsfxf3_i387 */
    case 685:  /* *fpatanxf3_i387 */
    case 684:  /* fptan_extenddfxf4_i387 */
    case 683:  /* fptan_extendsfxf4_i387 */
    case 682:  /* fptanxf4_i387 */
    case 681:  /* sincos_extenddfxf3_i387 */
    case 680:  /* sincos_extendsfxf3_i387 */
    case 679:  /* sincosxf3 */
    case 678:  /* *cos_extenddfxf2_i387 */
    case 677:  /* *sin_extenddfxf2_i387 */
    case 676:  /* *cos_extendsfxf2_i387 */
    case 675:  /* *sin_extendsfxf2_i387 */
    case 674:  /* *cosxf2_i387 */
    case 673:  /* *sinxf2_i387 */
    case 672:  /* fprem1xf4_i387 */
    case 671:  /* fpremxf4_i387 */
    case 667:  /* sqrt_extenddfxf2_i387 */
    case 666:  /* sqrt_extendsfxf2_i387 */
    case 665:  /* sqrtxf2 */
    case 664:  /* truncxfdf2_i387_noop_unspec */
    case 663:  /* truncxfsf2_i387_noop_unspec */
    case 409:  /* *negextenddfxf2 */
    case 408:  /* *absextenddfxf2 */
    case 407:  /* *negextendsfxf2 */
    case 406:  /* *absextendsfxf2 */
    case 405:  /* *negextendsfdf2 */
    case 404:  /* *absextendsfdf2 */
    case 403:  /* *negxf2_1 */
    case 402:  /* *absxf2_1 */
    case 401:  /* *negdf2_1 */
    case 400:  /* *absdf2_1 */
    case 399:  /* *negsf2_1 */
    case 398:  /* *abssf2_1 */
    case 223:  /* *floatdixf2_i387 */
    case 222:  /* *floatdidf2_i387 */
    case 221:  /* *floatdisf2_i387 */
    case 220:  /* *floatsixf2_i387 */
    case 219:  /* *floatsidf2_i387 */
    case 218:  /* *floatsisf2_i387 */
    case 177:  /* *floathixf2_i387 */
    case 176:  /* *floathidf2_i387 */
    case 175:  /* *floathisf2_i387 */
    case 157:  /* fix_truncdi_i387_fisttp_with_temp */
    case 156:  /* fix_truncsi_i387_fisttp_with_temp */
    case 155:  /* fix_trunchi_i387_fisttp_with_temp */
    case 154:  /* fix_truncdi_i387_fisttp */
    case 153:  /* fix_truncsi_i387_fisttp */
    case 152:  /* fix_trunchi_i387_fisttp */
    case 151:  /* fix_truncdi_fisttp_i387_1 */
    case 150:  /* fix_truncsi_fisttp_i387_1 */
    case 149:  /* fix_trunchi_fisttp_i387_1 */
    case 144:  /* *truncxfdf2_i387 */
    case 143:  /* *truncxfsf2_i387 */
    case 142:  /* truncxfdf2_i387_noop */
    case 141:  /* truncxfsf2_i387_noop */
    case 138:  /* *truncdfsf2_i387_1 */
    case 135:  /* *truncdfsf_fast_i387 */
    case 132:  /* *extenddfxf2_i387 */
    case 131:  /* *extendsfxf2_i387 */
    case 130:  /* *extendsfdf2_i387 */
    case 116:  /* *swapdf */
    case 115:  /* *swapsf */
    case 114:  /* swapxf */
      return 2 + get_attr_prefix_data16 (insn) + get_attr_length_address (insn);

    case 1866:  /* *avx2_gatherdiv8sf_4 */
    case 1865:  /* *avx2_gatherdiv8sf_4 */
    case 1864:  /* *avx2_gatherdiv8si_4 */
    case 1863:  /* *avx2_gatherdiv8si_4 */
    case 1862:  /* *avx2_gatherdiv8sf_3 */
    case 1861:  /* *avx2_gatherdiv8sf_3 */
    case 1860:  /* *avx2_gatherdiv8si_3 */
    case 1859:  /* *avx2_gatherdiv8si_3 */
    case 1858:  /* *avx2_gatherdiv8sf_2 */
    case 1857:  /* *avx2_gatherdiv8sf_2 */
    case 1856:  /* *avx2_gatherdiv8si_2 */
    case 1855:  /* *avx2_gatherdiv8si_2 */
    case 1854:  /* *avx2_gatherdiv4sf_2 */
    case 1853:  /* *avx2_gatherdiv4sf_2 */
    case 1852:  /* *avx2_gatherdiv4si_2 */
    case 1851:  /* *avx2_gatherdiv4si_2 */
    case 1850:  /* *avx2_gatherdiv4df_2 */
    case 1849:  /* *avx2_gatherdiv4df_2 */
    case 1848:  /* *avx2_gatherdiv4di_2 */
    case 1847:  /* *avx2_gatherdiv4di_2 */
    case 1846:  /* *avx2_gatherdiv2df_2 */
    case 1845:  /* *avx2_gatherdiv2df_2 */
    case 1844:  /* *avx2_gatherdiv2di_2 */
    case 1843:  /* *avx2_gatherdiv2di_2 */
    case 1842:  /* *avx2_gatherdiv8sf */
    case 1841:  /* *avx2_gatherdiv8sf */
    case 1840:  /* *avx2_gatherdiv8si */
    case 1839:  /* *avx2_gatherdiv8si */
    case 1838:  /* *avx2_gatherdiv4sf */
    case 1837:  /* *avx2_gatherdiv4sf */
    case 1836:  /* *avx2_gatherdiv4si */
    case 1835:  /* *avx2_gatherdiv4si */
    case 1834:  /* *avx2_gatherdiv4df */
    case 1833:  /* *avx2_gatherdiv4df */
    case 1832:  /* *avx2_gatherdiv4di */
    case 1831:  /* *avx2_gatherdiv4di */
    case 1830:  /* *avx2_gatherdiv2df */
    case 1829:  /* *avx2_gatherdiv2df */
    case 1828:  /* *avx2_gatherdiv2di */
    case 1827:  /* *avx2_gatherdiv2di */
    case 1826:  /* *avx2_gathersiv8sf_2 */
    case 1825:  /* *avx2_gathersiv8sf_2 */
    case 1824:  /* *avx2_gathersiv8si_2 */
    case 1823:  /* *avx2_gathersiv8si_2 */
    case 1822:  /* *avx2_gathersiv4sf_2 */
    case 1821:  /* *avx2_gathersiv4sf_2 */
    case 1820:  /* *avx2_gathersiv4si_2 */
    case 1819:  /* *avx2_gathersiv4si_2 */
    case 1818:  /* *avx2_gathersiv4df_2 */
    case 1817:  /* *avx2_gathersiv4df_2 */
    case 1816:  /* *avx2_gathersiv4di_2 */
    case 1815:  /* *avx2_gathersiv4di_2 */
    case 1814:  /* *avx2_gathersiv2df_2 */
    case 1813:  /* *avx2_gathersiv2df_2 */
    case 1812:  /* *avx2_gathersiv2di_2 */
    case 1811:  /* *avx2_gathersiv2di_2 */
    case 1810:  /* *avx2_gathersiv8sf */
    case 1809:  /* *avx2_gathersiv8sf */
    case 1808:  /* *avx2_gathersiv8si */
    case 1807:  /* *avx2_gathersiv8si */
    case 1806:  /* *avx2_gathersiv4sf */
    case 1805:  /* *avx2_gathersiv4sf */
    case 1804:  /* *avx2_gathersiv4si */
    case 1803:  /* *avx2_gathersiv4si */
    case 1802:  /* *avx2_gathersiv4df */
    case 1801:  /* *avx2_gathersiv4df */
    case 1800:  /* *avx2_gathersiv4di */
    case 1799:  /* *avx2_gathersiv4di */
    case 1798:  /* *avx2_gathersiv2df */
    case 1797:  /* *avx2_gathersiv2df */
    case 1796:  /* *avx2_gathersiv2di */
    case 1795:  /* *avx2_gathersiv2di */
    case 1794:  /* vcvtps2ph256 */
    case 1793:  /* *vcvtps2ph_store */
    case 1792:  /* *vcvtps2ph */
    case 1791:  /* vcvtph2ps256 */
    case 1790:  /* *vcvtph2ps_load */
    case 1789:  /* vcvtph2ps */
    case 1788:  /* avx_vec_concatv4df */
    case 1787:  /* avx_vec_concatv8sf */
    case 1786:  /* avx_vec_concatv4di */
    case 1785:  /* avx_vec_concatv8si */
    case 1784:  /* avx_vec_concatv16hi */
    case 1783:  /* avx_vec_concatv32qi */
    case 1782:  /* avx2_lshrvv2di */
    case 1781:  /* avx2_ashlvv2di */
    case 1780:  /* avx2_lshrvv4di */
    case 1779:  /* avx2_ashlvv4di */
    case 1778:  /* avx2_lshrvv4si */
    case 1777:  /* avx2_ashlvv4si */
    case 1776:  /* avx2_lshrvv8si */
    case 1775:  /* avx2_ashlvv8si */
    case 1774:  /* avx2_ashrvv4si */
    case 1773:  /* avx2_ashrvv8si */
    case 1769:  /* avx2_maskstoreq256 */
    case 1768:  /* avx2_maskstored256 */
    case 1767:  /* avx2_maskstoreq */
    case 1766:  /* avx2_maskstored */
    case 1765:  /* avx_maskstorepd256 */
    case 1764:  /* avx_maskstoreps256 */
    case 1763:  /* avx_maskstorepd */
    case 1762:  /* avx_maskstoreps */
    case 1761:  /* avx2_maskloadq256 */
    case 1760:  /* avx2_maskloadd256 */
    case 1759:  /* avx2_maskloadq */
    case 1758:  /* avx2_maskloadd */
    case 1757:  /* avx_maskloadpd256 */
    case 1756:  /* avx_maskloadps256 */
    case 1755:  /* avx_maskloadpd */
    case 1754:  /* avx_maskloadps */
    case 1753:  /* vec_set_hi_v32qi */
    case 1752:  /* vec_set_lo_v32qi */
    case 1751:  /* vec_set_hi_v16hi */
    case 1750:  /* vec_set_lo_v16hi */
    case 1749:  /* vec_set_hi_v8sf */
    case 1748:  /* vec_set_hi_v8si */
    case 1747:  /* vec_set_lo_v8sf */
    case 1746:  /* vec_set_lo_v8si */
    case 1745:  /* vec_set_hi_v4df */
    case 1744:  /* vec_set_hi_v4di */
    case 1743:  /* vec_set_lo_v4df */
    case 1742:  /* vec_set_lo_v4di */
    case 1741:  /* avx2_vec_set_hi_v4di */
    case 1740:  /* avx2_vec_set_lo_v4di */
    case 1739:  /* *avx_vperm2f128v4df_nozero */
    case 1738:  /* *avx_vperm2f128v8sf_nozero */
    case 1737:  /* *avx_vperm2f128v8si_nozero */
    case 1736:  /* *avx_vperm2f128v4df_full */
    case 1735:  /* *avx_vperm2f128v8sf_full */
    case 1734:  /* *avx_vperm2f128v8si_full */
    case 1733:  /* avx_vpermilvarv2df3 */
    case 1732:  /* avx_vpermilvarv4df3 */
    case 1731:  /* avx_vpermilvarv4sf3 */
    case 1730:  /* avx_vpermilvarv8sf3 */
    case 1729:  /* *avx_vpermilpv2df */
    case 1728:  /* *avx_vpermilpv4df */
    case 1727:  /* *avx_vpermilpv4sf */
    case 1726:  /* *avx_vpermilpv8sf */
    case 1723:  /* *avx_vperm_broadcast_v4sf */
    case 1722:  /* avx_vbroadcastf128_v4df */
    case 1721:  /* avx_vbroadcastf128_v8sf */
    case 1720:  /* avx_vbroadcastf128_v4di */
    case 1719:  /* avx_vbroadcastf128_v8si */
    case 1718:  /* avx_vbroadcastf128_v16hi */
    case 1717:  /* avx_vbroadcastf128_v32qi */
    case 1716:  /* avx2_vbroadcasti128_v4di */
    case 1715:  /* avx2_vbroadcasti128_v8si */
    case 1714:  /* avx2_vbroadcasti128_v16hi */
    case 1713:  /* avx2_vbroadcasti128_v32qi */
    case 1712:  /* vec_dupv4df */
    case 1711:  /* vec_dupv4di */
    case 1710:  /* vec_dupv8sf */
    case 1709:  /* vec_dupv8si */
    case 1708:  /* avx2_vec_dupv4df */
    case 1707:  /* avx2_permv2ti */
    case 1706:  /* avx2_permv4df_1 */
    case 1705:  /* avx2_permv4di_1 */
    case 1704:  /* avx2_permvarv8sf */
    case 1703:  /* avx2_permvarv8si */
    case 1702:  /* avx2_pbroadcastv4di_1 */
    case 1701:  /* avx2_pbroadcastv8si_1 */
    case 1700:  /* avx2_pbroadcastv16hi_1 */
    case 1699:  /* avx2_pbroadcastv32qi_1 */
    case 1698:  /* avx2_pbroadcastv2di */
    case 1697:  /* avx2_pbroadcastv4di */
    case 1696:  /* avx2_pbroadcastv4si */
    case 1695:  /* avx2_pbroadcastv8si */
    case 1694:  /* avx2_pbroadcastv8hi */
    case 1693:  /* avx2_pbroadcastv16hi */
    case 1692:  /* avx2_pbroadcastv16qi */
    case 1691:  /* avx2_pbroadcastv32qi */
    case 1690:  /* avx_vzeroupper */
    case 1689:  /* *avx_vzeroall */
    case 1680:  /* xop_vpermil2v4df3 */
    case 1678:  /* xop_vpermil2v8sf3 */
    case 1659:  /* xop_frczv4df2 */
    case 1658:  /* xop_frczv8sf2 */
    case 1573:  /* avx_ptest256 */
    case 1572:  /* avx_vtestpd */
    case 1571:  /* avx_vtestpd256 */
    case 1570:  /* avx_vtestps */
    case 1569:  /* avx_vtestps256 */
    case 1566:  /* avx2_zero_extendv4siv4di2 */
    case 1565:  /* avx2_sign_extendv4siv4di2 */
    case 1562:  /* avx2_zero_extendv4hiv4di2 */
    case 1561:  /* avx2_sign_extendv4hiv4di2 */
    case 1558:  /* avx2_zero_extendv4qiv4di2 */
    case 1557:  /* avx2_sign_extendv4qiv4di2 */
    case 1554:  /* avx2_zero_extendv8hiv8si2 */
    case 1553:  /* avx2_sign_extendv8hiv8si2 */
    case 1550:  /* avx2_zero_extendv8qiv8si2 */
    case 1549:  /* avx2_sign_extendv8qiv8si2 */
    case 1546:  /* avx2_zero_extendv16qiv16hi2 */
    case 1545:  /* avx2_sign_extendv16qiv16hi2 */
    case 1543:  /* avx2_pblenddv4si */
    case 1542:  /* avx2_pblenddv8si */
    case 1541:  /* *avx2_pblendw */
    case 1536:  /* avx2_packusdw */
    case 1482:  /* avx2_pmaddubsw256 */
    case 1477:  /* avx2_phsubdv8si3 */
    case 1476:  /* avx2_phadddv8si3 */
    case 1467:  /* avx2_phsubswv16hi3 */
    case 1466:  /* avx2_phsubwv16hi3 */
    case 1465:  /* avx2_phaddswv16hi3 */
    case 1464:  /* avx2_phaddwv16hi3 */
    case 1455:  /* avx2_pmovmskb */
    case 1431:  /* avx2_pshufhw_1 */
    case 1429:  /* avx2_pshuflw_1 */
    case 1427:  /* avx2_pshufd_1 */
    case 1416:  /* avx2_interleave_lowv8si */
    case 1414:  /* avx2_interleave_highv8si */
    case 1412:  /* avx2_interleave_lowv16hi */
    case 1410:  /* avx2_interleave_highv16hi */
    case 1408:  /* avx2_interleave_lowv32qi */
    case 1406:  /* avx2_interleave_highv32qi */
    case 1364:  /* avx2_gtv4di3 */
    case 1363:  /* avx2_gtv8si3 */
    case 1362:  /* avx2_gtv16hi3 */
    case 1361:  /* avx2_gtv32qi3 */
    case 1355:  /* *avx2_eqv4di3 */
    case 1354:  /* *avx2_eqv8si3 */
    case 1353:  /* *avx2_eqv16hi3 */
    case 1352:  /* *avx2_eqv32qi3 */
    case 1339:  /* *avx2_uminv8si3 */
    case 1338:  /* *avx2_umaxv8si3 */
    case 1337:  /* *avx2_sminv8si3 */
    case 1336:  /* *avx2_smaxv8si3 */
    case 1335:  /* *avx2_uminv16hi3 */
    case 1334:  /* *avx2_umaxv16hi3 */
    case 1333:  /* *avx2_sminv16hi3 */
    case 1332:  /* *avx2_smaxv16hi3 */
    case 1331:  /* *avx2_uminv32qi3 */
    case 1330:  /* *avx2_umaxv32qi3 */
    case 1329:  /* *avx2_sminv32qi3 */
    case 1328:  /* *avx2_smaxv32qi3 */
    case 1304:  /* *avx2_pmaddwd */
    case 1302:  /* *vec_widen_smult_even_v8si */
    case 1300:  /* *vec_widen_umult_even_v8si */
    case 1249:  /* avx2_interleave_lowv4di */
    case 1247:  /* avx2_interleave_highv4di */
    case 1246:  /* avx_shufpd256_1 */
    case 1244:  /* *avx_unpcklpd256 */
    case 1242:  /* avx_unpckhpd256 */
    case 1241:  /* vec_extract_hi_v32qi */
    case 1239:  /* vec_extract_hi_v16hi */
    case 1237:  /* vec_extract_hi_v8sf */
    case 1236:  /* vec_extract_hi_v8si */
    case 1233:  /* vec_extract_hi_v4df */
    case 1232:  /* vec_extract_hi_v4di */
    case 1218:  /* avx2_vec_dupv8sf_1 */
    case 1217:  /* avx2_vec_dupv4sf */
    case 1216:  /* avx2_vec_dupv8sf */
    case 1208:  /* avx_shufps256_1 */
    case 1206:  /* avx_movsldup256 */
    case 1204:  /* avx_movshdup256 */
    case 1202:  /* avx_unpcklps256 */
    case 1200:  /* avx_unpckhps256 */
    case 1196:  /* *avx_cvtps2pd256_2 */
    case 1195:  /* avx_cvtps2pd256 */
    case 1193:  /* avx_cvtpd2ps256 */
    case 1189:  /* *avx_cvttpd2dq256_2 */
    case 1188:  /* fix_truncv4dfv4si2 */
    case 1186:  /* *avx_cvtpd2dq256_2 */
    case 1185:  /* avx_cvtpd2dq256 */
    case 1183:  /* avx_cvtdq2pd256_2 */
    case 1182:  /* floatv4siv4df2 */
    case 1173:  /* fix_truncv8sfv8si2 */
    case 1171:  /* avx_cvtps2dq256 */
    case 1144:  /* *fma_fmsubadd_v4df */
    case 1142:  /* *fma_fmsubadd_v8sf */
    case 1140:  /* *fma_fmaddsub_v4df */
    case 1138:  /* *fma_fmaddsub_v8sf */
    case 1137:  /* *fma_fnmsub_v4df */
    case 1136:  /* *fma_fnmsub_v8sf */
    case 1131:  /* *fma_fnmadd_v4df */
    case 1130:  /* *fma_fnmadd_v8sf */
    case 1125:  /* *fma_fmsub_v4df */
    case 1124:  /* *fma_fmsub_v8sf */
    case 1119:  /* *fma_fmadd_v4df */
    case 1118:  /* *fma_fmadd_v8sf */
    case 1071:  /* avx_vmcmpv2df3 */
    case 1070:  /* avx_vmcmpv4sf3 */
    case 1069:  /* avx_cmpv2df3 */
    case 1068:  /* avx_cmpv4df3 */
    case 1067:  /* avx_cmpv4sf3 */
    case 1066:  /* avx_cmpv8sf3 */
    case 1063:  /* avx_hsubv8sf3 */
    case 1062:  /* avx_haddv8sf3 */
    case 1057:  /* avx_hsubv4df3 */
    case 1056:  /* avx_haddv4df3 */
    case 1054:  /* avx_addsubv8sf3 */
    case 1052:  /* avx_addsubv4df3 */
    case 588:  /* bmi2_pext_si3 */
    case 587:  /* bmi2_pdep_si3 */
    case 586:  /* bmi2_bzhi_si3 */
    case 305:  /* *bmi2_umulsidi3_1 */
    case 75:  /* *movoi_internal_avx */
      return get_attr_length_vex (insn) + get_attr_length_immediate (insn) + get_attr_modrm (insn) + get_attr_length_address (insn);

    case -1:
      if (GET_CODE (PATTERN (insn)) != ASM_INPUT
          && asm_noperands (PATTERN (insn)) < 0)
        fatal_insn_not_found (insn);
      return 128 /* 0x80 */;

    case 1463:  /* sse3_monitor */
    case 1462:  /* sse3_mwait */
    case 835:  /* xtest_1 */
    case 834:  /* xabort */
    case 833:  /* xend */
    case 815:  /* rdtscp */
    case 563:  /* simple_return_pop_internal */
      return 3;

    case 832:  /* xbegin_1 */
    case 624:  /* *tls_dynamic_gnu2_lea_32 */
      return 6;

    case 826:  /* *lwp_lwpinssi3_1 */
    case 825:  /* *lwp_lwpvalsi3_1 */
      extract_constrain_insn_cached (insn);
      return 
#line 18005 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_address_default (insn) + 9);

    case 824:  /* lwp_slwpcbdi */
    case 823:  /* lwp_slwpcbsi */
    case 822:  /* *lwp_llwpcbdi1 */
    case 821:  /* *lwp_llwpcbsi1 */
    case 794:  /* allocate_stack_worker_probe_di */
    case 793:  /* allocate_stack_worker_probe_si */
      return 5;

    case 820:  /* xrstor */
    case 819:  /* xsaveopt */
    case 818:  /* xsave */
    case 817:  /* fxrstor */
    case 816:  /* fxsave */
      extract_constrain_insn_cached (insn);
      return 
#line 17891 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_address_default (insn) + 3);

    case 743:  /* cld */
    case 565:  /* nop */
    case 561:  /* simple_return_internal */
    case 48:  /* x86_sahf_1 */
      return 1;

    case 62:  /* *cmpiuxf_i387 */
    case 61:  /* *cmpiudf_i387 */
    case 60:  /* *cmpiusf_i387 */
    case 59:  /* *cmpixf_i387 */
    case 58:  /* *cmpidf_i387 */
    case 57:  /* *cmpisf_i387 */
    case 739:  /* fxamxf2_i387 */
    case 738:  /* fxamdf2_i387 */
    case 737:  /* fxamsf2_i387 */
    case 609:  /* bswaphi_lowpart */
      return 4;

    case 623:  /* *add_tp_di */
    case 622:  /* *add_tp_si */
    case 621:  /* *add_tp_x32_zext */
    case 620:  /* *add_tp_x32 */
    case 619:  /* *load_tp_di */
    case 618:  /* *load_tp_si */
    case 617:  /* *load_tp_x32_zext */
    case 616:  /* *load_tp_x32 */
      return 7;

    case 614:  /* *tls_local_dynamic_base_32_gnu */
      return 11 /* 0xb */;

    case 613:  /* *tls_global_dynamic_32_gnu */
    case 569:  /* set_got_labelled */
    case 568:  /* set_got */
      return 12 /* 0xc */;

    case 608:  /* *bswaphi_lowpart_1 */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return 2;
        }
      else
        {
	  return 4;
        }

    case 573:  /* split_stack_return */
      extract_insn_cached (insn);
      if (const0_operand (operands[0], SImode))
        {
	  return 1;
        }
      else
        {
	  return 3;
        }

    case 1905:  /* atomic_xorsi */
    case 1904:  /* atomic_orsi */
    case 1903:  /* atomic_andsi */
    case 1902:  /* atomic_xorhi */
    case 1901:  /* atomic_orhi */
    case 1900:  /* atomic_andhi */
    case 1899:  /* atomic_xorqi */
    case 1898:  /* atomic_orqi */
    case 1897:  /* atomic_andqi */
    case 1896:  /* atomic_subsi */
    case 1895:  /* atomic_subhi */
    case 1894:  /* atomic_subqi */
    case 1893:  /* atomic_addsi */
    case 1892:  /* atomic_addhi */
    case 1891:  /* atomic_addqi */
    case 1890:  /* atomic_exchangesi */
    case 1889:  /* atomic_exchangehi */
    case 1888:  /* atomic_exchangeqi */
    case 1887:  /* *atomic_fetch_add_cmpsi */
    case 1886:  /* *atomic_fetch_add_cmphi */
    case 1885:  /* *atomic_fetch_add_cmpqi */
    case 1884:  /* atomic_fetch_addsi */
    case 1883:  /* atomic_fetch_addhi */
    case 1882:  /* atomic_fetch_addqi */
    case 1881:  /* atomic_compare_and_swapdi_doubleword */
    case 1880:  /* atomic_compare_and_swapsi_1 */
    case 1879:  /* atomic_compare_and_swaphi_1 */
    case 1878:  /* atomic_compare_and_swapqi_1 */
    case 1875:  /* atomic_storedi_fpu */
    case 1874:  /* atomic_storesi_1 */
    case 1873:  /* atomic_storehi_1 */
    case 1872:  /* atomic_storeqi_1 */
    case 1871:  /* atomic_loaddi_fpu */
    case 1870:  /* mfence_nosse */
    case 1772:  /* avx_pd256_pd */
    case 1771:  /* avx_ps256_ps */
    case 1770:  /* avx_si256_si */
    case 1725:  /* *avx_vperm_broadcast_v4df */
    case 1724:  /* *avx_vperm_broadcast_v8sf */
    case 1436:  /* *sse2_storeq */
    case 1435:  /* *vec_ext_v4si_mem */
    case 1434:  /* sse2_stored */
    case 1240:  /* vec_extract_lo_v32qi */
    case 1238:  /* vec_extract_lo_v16hi */
    case 1235:  /* vec_extract_lo_v8sf */
    case 1234:  /* vec_extract_lo_v8si */
    case 1231:  /* vec_extract_lo_v4df */
    case 1230:  /* vec_extract_lo_v4di */
    case 1229:  /* *vec_extract_v4sf_mem */
    case 1227:  /* *vec_extractv4sf_0 */
    case 987:  /* *absnegv2df2 */
    case 986:  /* *absnegv4df2 */
    case 985:  /* *absnegv4sf2 */
    case 984:  /* *absnegv8sf2 */
    case 962:  /* movdi_to_sse */
    case 937:  /* *vec_extractv2si_0 */
    case 867:  /* *vec_extractv2sf_0 */
    case 830:  /* rdseedsi_1 */
    case 829:  /* rdseedhi_1 */
    case 828:  /* rdrandsi_1 */
    case 827:  /* rdrandhi_1 */
    case 809:  /* stack_tls_protect_test_di */
    case 808:  /* stack_tls_protect_test_si */
    case 807:  /* stack_protect_test_di */
    case 806:  /* stack_protect_test_si */
    case 805:  /* stack_tls_protect_set_di */
    case 804:  /* stack_tls_protect_set_si */
    case 803:  /* stack_protect_set_di */
    case 802:  /* stack_protect_set_si */
    case 798:  /* probe_stack_rangedi */
    case 797:  /* probe_stack_rangesi */
    case 796:  /* adjust_stack_and_probedi */
    case 795:  /* adjust_stack_and_probesi */
    case 741:  /* fxamdf2_i387_with_temp */
    case 740:  /* fxamsf2_i387_with_temp */
    case 736:  /* fistsi2_ceil_with_temp */
    case 735:  /* fistsi2_floor_with_temp */
    case 734:  /* fisthi2_ceil_with_temp */
    case 733:  /* fisthi2_floor_with_temp */
    case 732:  /* fistsi2_ceil */
    case 731:  /* fistsi2_floor */
    case 730:  /* fisthi2_ceil */
    case 729:  /* fisthi2_floor */
    case 728:  /* fistdi2_ceil_with_temp */
    case 727:  /* fistdi2_floor_with_temp */
    case 726:  /* fistdi2_ceil */
    case 725:  /* fistdi2_floor */
    case 724:  /* *fistdi2_ceil_1 */
    case 723:  /* *fistdi2_floor_1 */
    case 722:  /* *fistsi2_ceil_1 */
    case 721:  /* *fistsi2_floor_1 */
    case 720:  /* *fisthi2_ceil_1 */
    case 719:  /* *fisthi2_floor_1 */
    case 718:  /* frndintxf2_mask_pm_i387 */
    case 717:  /* frndintxf2_mask_pm */
    case 716:  /* frndintxf2_trunc_i387 */
    case 715:  /* frndintxf2_ceil_i387 */
    case 714:  /* frndintxf2_floor_i387 */
    case 713:  /* frndintxf2_trunc */
    case 712:  /* frndintxf2_ceil */
    case 711:  /* frndintxf2_floor */
    case 626:  /* *tls_dynamic_gnu2_combine_32 */
    case 615:  /* *tls_local_dynamic_32_once */
    case 611:  /* paritysi2_cmp */
    case 610:  /* paritydi2_cmp */
    case 574:  /* ffssi2_no_cmove */
    case 571:  /* eh_return_internal */
    case 540:  /* *jccxf_si_r_i387 */
    case 539:  /* *jccdf_si_r_i387 */
    case 538:  /* *jccsf_si_r_i387 */
    case 537:  /* *jccxf_hi_r_i387 */
    case 536:  /* *jccdf_hi_r_i387 */
    case 535:  /* *jccsf_hi_r_i387 */
    case 534:  /* *jccxf_si_i387 */
    case 533:  /* *jccdf_si_i387 */
    case 532:  /* *jccsf_si_i387 */
    case 531:  /* *jccxf_hi_i387 */
    case 530:  /* *jccdf_hi_i387 */
    case 529:  /* *jccsf_hi_i387 */
    case 528:  /* *jccuxf_r_i387 */
    case 527:  /* *jccudf_r_i387 */
    case 526:  /* *jccusf_r_i387 */
    case 525:  /* *jccuxf_i387 */
    case 524:  /* *jccudf_i387 */
    case 523:  /* *jccusf_i387 */
    case 522:  /* *jccdf_r_i387 */
    case 521:  /* *jccsf_r_i387 */
    case 520:  /* *jccdf_i387 */
    case 519:  /* *jccsf_i387 */
    case 518:  /* *jccxf_r_i387 */
    case 517:  /* *jccxf_i387 */
    case 516:  /* *jccxf_0_r_i387 */
    case 515:  /* *jccdf_0_r_i387 */
    case 514:  /* *jccsf_0_r_i387 */
    case 513:  /* *jccxf_0_i387 */
    case 512:  /* *jccdf_0_i387 */
    case 511:  /* *jccsf_0_i387 */
    case 510:  /* *jcc_btsi_mask_1 */
    case 509:  /* *jcc_btsi_1 */
    case 508:  /* *jcc_btdi_mask */
    case 507:  /* *jcc_btsi_mask */
    case 506:  /* *jcc_btdi */
    case 505:  /* *jcc_btsi */
    case 498:  /* *setcc_si_1_movzbl */
    case 497:  /* *setcc_si_1_and */
    case 483:  /* ix86_rotrdi3_doubleword */
    case 482:  /* ix86_rotldi3_doubleword */
    case 447:  /* *ashrdi3_doubleword */
    case 446:  /* *lshrdi3_doubleword */
    case 424:  /* *ashldi3_doubleword */
    case 415:  /* copysigntf3_var */
    case 414:  /* copysigndf3_var */
    case 413:  /* copysignsf3_var */
    case 412:  /* copysigntf3_const */
    case 411:  /* copysigndf3_const */
    case 410:  /* copysignsf3_const */
    case 397:  /* *absnegtf2_sse */
    case 396:  /* *absnegxf2_i387 */
    case 395:  /* *absnegdf2_i387 */
    case 394:  /* *absnegsf2_i387 */
    case 393:  /* *absnegdf2_sse */
    case 392:  /* *absnegsf2_sse */
    case 391:  /* *absnegdf2_mixed */
    case 390:  /* *absnegsf2_mixed */
    case 381:  /* *negti2_doubleword */
    case 380:  /* *negdi2_doubleword */
    case 331:  /* *testqi_ext_3 */
    case 320:  /* *udivmodsi4 */
    case 319:  /* *udivmodhi4 */
    case 318:  /* udivmodsi4_1 */
    case 314:  /* *divmodsi4 */
    case 313:  /* *divmodhi4 */
    case 312:  /* divmodsi4_1 */
    case 264:  /* *subti3_doubleword */
    case 263:  /* *subdi3_doubleword */
    case 232:  /* *addti3_doubleword */
    case 231:  /* *adddi3_doubleword */
    case 229:  /* *floatunssixf2_1 */
    case 228:  /* *floatunssidf2_1 */
    case 227:  /* *floatunssisf2_1 */
    case 226:  /* floatdixf2_i387_with_xmm */
    case 225:  /* floatdidf2_i387_with_xmm */
    case 224:  /* floatdisf2_i387_with_xmm */
    case 183:  /* *floatdixf2_1 */
    case 182:  /* *floatdidf2_1 */
    case 181:  /* *floatdisf2_1 */
    case 180:  /* *floatsixf2_1 */
    case 179:  /* *floatsidf2_1 */
    case 178:  /* *floatsisf2_1 */
    case 171:  /* *floathixf2_1 */
    case 170:  /* *floathidf2_1 */
    case 169:  /* *floathisf2_1 */
    case 166:  /* fix_truncsi_i387_with_temp */
    case 165:  /* fix_trunchi_i387_with_temp */
    case 164:  /* fix_truncsi_i387 */
    case 163:  /* fix_trunchi_i387 */
    case 162:  /* fix_truncdi_i387_with_temp */
    case 161:  /* fix_truncdi_i387 */
    case 160:  /* *fix_truncdi_i387_1 */
    case 159:  /* *fix_truncsi_i387_1 */
    case 158:  /* *fix_trunchi_i387_1 */
    case 146:  /* *fixuns_truncdf_1 */
    case 145:  /* *fixuns_truncsf_1 */
    case 124:  /* extendsidi2_1 */
    case 108:  /* *pushdf */
    case 107:  /* *pushxf_nointeger */
    case 106:  /* *pushxf */
    case 105:  /* *pushtf */
    case 63:  /* *pushdi2 */
    case 46:  /* *cmpxf_si_cc_i387 */
    case 45:  /* *cmpdf_si_cc_i387 */
    case 44:  /* *cmpsf_si_cc_i387 */
    case 43:  /* *cmpxf_hi_cc_i387 */
    case 42:  /* *cmpdf_hi_cc_i387 */
    case 41:  /* *cmpsf_hi_cc_i387 */
    case 40:  /* *cmpxf_si_i387 */
    case 39:  /* *cmpdf_si_i387 */
    case 38:  /* *cmpsf_si_i387 */
    case 37:  /* *cmpxf_hi_i387 */
    case 36:  /* *cmpdf_hi_i387 */
    case 35:  /* *cmpsf_hi_i387 */
    case 34:  /* *cmpuxf_cc_i387 */
    case 33:  /* *cmpudf_cc_i387 */
    case 32:  /* *cmpusf_cc_i387 */
    case 31:  /* *cmpuxf_i387 */
    case 30:  /* *cmpudf_i387 */
    case 29:  /* *cmpusf_i387 */
    case 28:  /* *cmpdf_cc_i387 */
    case 27:  /* *cmpsf_cc_i387 */
    case 26:  /* *cmpdf_i387 */
    case 25:  /* *cmpsf_i387 */
    case 24:  /* *cmpxf_cc_i387 */
    case 23:  /* *cmpxf_i387 */
    case 22:  /* *cmpxf_0_cc_i387 */
    case 21:  /* *cmpdf_0_cc_i387 */
    case 20:  /* *cmpsf_0_cc_i387 */
    case 19:  /* *cmpxf_0_i387 */
    case 18:  /* *cmpdf_0_i387 */
    case 17:  /* *cmpsf_0_i387 */
    case 567:  /* pad */
      return 16 /* 0x10 */;

    case 566:  /* nops */
      extract_constrain_insn_cached (insn);
      return 
#line 11775 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(INTVAL (operands[0]));

    case 560:  /* prologue_use */
    case 559:  /* *memory_blockage */
    case 558:  /* blockage */
      return 0;

    case 831:  /* *pause */
    case 814:  /* rdtsc */
    case 813:  /* rdpmc */
    case 799:  /* trap */
    case 625:  /* *tls_dynamic_gnu2_call_32 */
    case 612:  /* *parityhi2_cmp */
    case 562:  /* simple_return_internal_long */
    case 541:  /* jump */
    case 504:  /* *jcc_2 */
    case 503:  /* *jcc_1 */
      return 2;

    case 168:  /* x86_fldcw_1 */
    case 167:  /* x86_fnstcw_1 */
    case 47:  /* x86_fnstsw_1 */
      extract_constrain_insn_cached (insn);
      return 
#line 4691 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_address_default (insn) + 2);

    case 1688:  /* pclmulqdq */
    case 1687:  /* aeskeygenassist */
    case 1686:  /* aesimc */
    case 1685:  /* aesdeclast */
    case 1684:  /* aesdec */
    case 1683:  /* aesenclast */
    case 1682:  /* aesenc */
    case 1590:  /* sse4_2_pcmpistr_cconly */
    case 1589:  /* sse4_2_pcmpistrm */
    case 1588:  /* sse4_2_pcmpistri */
    case 1585:  /* sse4_2_pcmpestr_cconly */
    case 1584:  /* sse4_2_pcmpestrm */
    case 1583:  /* sse4_2_pcmpestri */
    case 1580:  /* sse4_1_roundsd */
    case 1579:  /* sse4_1_roundss */
    case 1578:  /* sse4_1_roundpd */
    case 1577:  /* avx_roundpd256 */
    case 1576:  /* sse4_1_roundps */
    case 1575:  /* avx_roundps256 */
    case 1574:  /* sse4_1_ptest */
    case 1568:  /* sse4_1_zero_extendv2siv2di2 */
    case 1567:  /* sse4_1_sign_extendv2siv2di2 */
    case 1564:  /* sse4_1_zero_extendv2hiv2di2 */
    case 1563:  /* sse4_1_sign_extendv2hiv2di2 */
    case 1560:  /* sse4_1_zero_extendv2qiv2di2 */
    case 1559:  /* sse4_1_sign_extendv2qiv2di2 */
    case 1556:  /* sse4_1_zero_extendv4hiv4si2 */
    case 1555:  /* sse4_1_sign_extendv4hiv4si2 */
    case 1552:  /* sse4_1_zero_extendv4qiv4si2 */
    case 1551:  /* sse4_1_sign_extendv4qiv4si2 */
    case 1548:  /* sse4_1_zero_extendv8qiv8hi2 */
    case 1547:  /* sse4_1_sign_extendv8qiv8hi2 */
    case 1544:  /* sse4_1_phminposuw */
    case 1540:  /* sse4_1_pblendw */
    case 1539:  /* sse4_1_pblendvb */
    case 1538:  /* avx2_pblendvb */
    case 1537:  /* sse4_1_packusdw */
    case 1535:  /* sse4_1_mpsadbw */
    case 1534:  /* avx2_mpsadbw */
    case 1533:  /* sse4_1_movntdqa */
    case 1532:  /* avx2_movntdqa */
    case 1531:  /* sse4_1_dppd */
    case 1530:  /* avx_dppd256 */
    case 1529:  /* sse4_1_dpps */
    case 1528:  /* avx_dpps256 */
    case 1527:  /* sse4_1_blendvpd */
    case 1526:  /* avx_blendvpd256 */
    case 1525:  /* sse4_1_blendvps */
    case 1524:  /* avx_blendvps256 */
    case 1523:  /* sse4_1_blendpd */
    case 1522:  /* avx_blendpd256 */
    case 1521:  /* sse4_1_blendps */
    case 1520:  /* avx_blendps256 */
    case 1508:  /* absv4si2 */
    case 1507:  /* absv8si2 */
    case 1506:  /* absv8hi2 */
    case 1505:  /* absv16hi2 */
    case 1504:  /* absv16qi2 */
    case 1503:  /* absv32qi2 */
    case 1501:  /* ssse3_palignrti */
    case 1500:  /* avx2_palignrv2ti */
    case 1496:  /* ssse3_psignv4si3 */
    case 1495:  /* avx2_psignv8si3 */
    case 1494:  /* ssse3_psignv8hi3 */
    case 1493:  /* avx2_psignv16hi3 */
    case 1492:  /* ssse3_psignv16qi3 */
    case 1491:  /* avx2_psignv32qi3 */
    case 1489:  /* ssse3_pshufbv16qi3 */
    case 1488:  /* avx2_pshufbv32qi3 */
    case 1486:  /* *ssse3_pmulhrswv8hi3 */
    case 1485:  /* *avx2_pmulhrswv16hi3 */
    case 1483:  /* ssse3_pmaddubsw128 */
    case 1479:  /* ssse3_phsubdv4si3 */
    case 1478:  /* ssse3_phadddv4si3 */
    case 1471:  /* ssse3_phsubswv8hi3 */
    case 1470:  /* ssse3_phsubwv8hi3 */
    case 1469:  /* ssse3_phaddswv8hi3 */
    case 1468:  /* ssse3_phaddwv8hi3 */
    case 1460:  /* sse_stmxcsr */
    case 1459:  /* sse_ldmxcsr */
    case 1458:  /* *sse2_maskmovdqu */
    case 1457:  /* *sse2_maskmovdqu */
    case 1456:  /* sse2_pmovmskb */
    case 1454:  /* sse2_movmskpd */
    case 1453:  /* avx_movmskpd256 */
    case 1452:  /* sse_movmskps */
    case 1451:  /* avx_movmskps256 */
    case 1450:  /* sse2_psadbw */
    case 1449:  /* avx2_psadbw */
    case 1448:  /* *sse2_uavgv8hi3 */
    case 1447:  /* *avx2_uavgv16hi3 */
    case 1446:  /* *sse2_uavgv16qi3 */
    case 1445:  /* *avx2_uavgv32qi3 */
    case 1444:  /* vec_concatv2di */
    case 1443:  /* *vec_concatv4si */
    case 1440:  /* *vec_concatv2si_sse4_1 */
    case 1439:  /* *vec_dupv2di */
    case 1438:  /* *vec_dupv4si */
    case 1437:  /* *vec_extractv2di_1 */
    case 1433:  /* sse2_loadld */
    case 1432:  /* sse2_pshufhw_1 */
    case 1430:  /* sse2_pshuflw_1 */
    case 1428:  /* sse2_pshufd_1 */
    case 1426:  /* *sse4_1_pextrd */
    case 1425:  /* *sse4_1_pextrw_memory */
    case 1424:  /* *sse2_pextrw_si */
    case 1423:  /* *sse4_1_pextrb_memory */
    case 1422:  /* *sse4_1_pextrb_si */
    case 1421:  /* sse4_1_pinsrq */
    case 1420:  /* sse4_1_pinsrd */
    case 1419:  /* sse2_pinsrw */
    case 1418:  /* sse4_1_pinsrb */
    case 1417:  /* vec_interleave_lowv4si */
    case 1415:  /* vec_interleave_highv4si */
    case 1413:  /* vec_interleave_lowv8hi */
    case 1411:  /* vec_interleave_highv8hi */
    case 1409:  /* vec_interleave_lowv16qi */
    case 1407:  /* vec_interleave_highv16qi */
    case 1405:  /* sse2_packuswb */
    case 1404:  /* avx2_packuswb */
    case 1403:  /* sse2_packssdw */
    case 1402:  /* avx2_packssdw */
    case 1401:  /* sse2_packsswb */
    case 1400:  /* avx2_packsswb */
    case 1399:  /* *xorv2di3 */
    case 1398:  /* *iorv2di3 */
    case 1397:  /* *andv2di3 */
    case 1396:  /* *xorv4di3 */
    case 1395:  /* *iorv4di3 */
    case 1394:  /* *andv4di3 */
    case 1393:  /* *xorv4si3 */
    case 1392:  /* *iorv4si3 */
    case 1391:  /* *andv4si3 */
    case 1390:  /* *xorv8si3 */
    case 1389:  /* *iorv8si3 */
    case 1388:  /* *andv8si3 */
    case 1387:  /* *xorv8hi3 */
    case 1386:  /* *iorv8hi3 */
    case 1385:  /* *andv8hi3 */
    case 1384:  /* *xorv16hi3 */
    case 1383:  /* *iorv16hi3 */
    case 1382:  /* *andv16hi3 */
    case 1381:  /* *xorv16qi3 */
    case 1380:  /* *iorv16qi3 */
    case 1379:  /* *andv16qi3 */
    case 1378:  /* *xorv32qi3 */
    case 1377:  /* *iorv32qi3 */
    case 1376:  /* *andv32qi3 */
    case 1375:  /* *andnotv2di3 */
    case 1374:  /* *andnotv4di3 */
    case 1373:  /* *andnotv4si3 */
    case 1372:  /* *andnotv8si3 */
    case 1371:  /* *andnotv8hi3 */
    case 1370:  /* *andnotv16hi3 */
    case 1369:  /* *andnotv16qi3 */
    case 1368:  /* *andnotv32qi3 */
    case 1367:  /* sse2_gtv4si3 */
    case 1366:  /* sse2_gtv8hi3 */
    case 1365:  /* sse2_gtv16qi3 */
    case 1360:  /* sse4_2_gtv2di3 */
    case 1359:  /* *sse2_eqv4si3 */
    case 1358:  /* *sse2_eqv8hi3 */
    case 1357:  /* *sse2_eqv16qi3 */
    case 1356:  /* *sse4_1_eqv2di3 */
    case 1351:  /* *uminv16qi3 */
    case 1350:  /* *umaxv16qi3 */
    case 1349:  /* *sse4_1_uminv4si3 */
    case 1348:  /* *sse4_1_umaxv4si3 */
    case 1347:  /* *sse4_1_uminv8hi3 */
    case 1346:  /* *sse4_1_umaxv8hi3 */
    case 1345:  /* *sminv8hi3 */
    case 1344:  /* *smaxv8hi3 */
    case 1343:  /* *sse4_1_sminv4si3 */
    case 1342:  /* *sse4_1_smaxv4si3 */
    case 1341:  /* *sse4_1_sminv16qi3 */
    case 1340:  /* *sse4_1_smaxv16qi3 */
    case 1327:  /* sse2_lshrv1ti3 */
    case 1326:  /* avx2_lshrv2ti3 */
    case 1325:  /* sse2_ashlv1ti3 */
    case 1324:  /* avx2_ashlv2ti3 */
    case 1323:  /* lshrv2di3 */
    case 1322:  /* ashlv2di3 */
    case 1321:  /* lshrv4di3 */
    case 1320:  /* ashlv4di3 */
    case 1319:  /* lshrv4si3 */
    case 1318:  /* ashlv4si3 */
    case 1317:  /* lshrv8si3 */
    case 1316:  /* ashlv8si3 */
    case 1315:  /* lshrv8hi3 */
    case 1314:  /* ashlv8hi3 */
    case 1313:  /* lshrv16hi3 */
    case 1312:  /* ashlv16hi3 */
    case 1311:  /* ashrv4si3 */
    case 1310:  /* ashrv8si3 */
    case 1309:  /* ashrv8hi3 */
    case 1308:  /* ashrv16hi3 */
    case 1307:  /* *sse4_1_mulv4si3 */
    case 1306:  /* *avx2_mulv8si3 */
    case 1305:  /* *sse2_pmaddwd */
    case 1303:  /* *sse4_1_mulv2siv2di3 */
    case 1301:  /* *vec_widen_umult_even_v4si */
    case 1299:  /* *umulv8hi3_highpart */
    case 1298:  /* *smulv8hi3_highpart */
    case 1297:  /* *umulv16hi3_highpart */
    case 1296:  /* *smulv16hi3_highpart */
    case 1295:  /* *mulv8hi3 */
    case 1294:  /* *mulv16hi3 */
    case 1293:  /* *sse2_ussubv8hi3 */
    case 1292:  /* *sse2_sssubv8hi3 */
    case 1291:  /* *sse2_usaddv8hi3 */
    case 1290:  /* *sse2_ssaddv8hi3 */
    case 1289:  /* *avx2_ussubv16hi3 */
    case 1288:  /* *avx2_sssubv16hi3 */
    case 1287:  /* *avx2_usaddv16hi3 */
    case 1286:  /* *avx2_ssaddv16hi3 */
    case 1285:  /* *sse2_ussubv16qi3 */
    case 1284:  /* *sse2_sssubv16qi3 */
    case 1283:  /* *sse2_usaddv16qi3 */
    case 1282:  /* *sse2_ssaddv16qi3 */
    case 1281:  /* *avx2_ussubv32qi3 */
    case 1280:  /* *avx2_sssubv32qi3 */
    case 1279:  /* *avx2_usaddv32qi3 */
    case 1278:  /* *avx2_ssaddv32qi3 */
    case 1277:  /* *subv2di3 */
    case 1276:  /* *addv2di3 */
    case 1275:  /* *subv4di3 */
    case 1274:  /* *addv4di3 */
    case 1273:  /* *subv4si3 */
    case 1272:  /* *addv4si3 */
    case 1271:  /* *subv8si3 */
    case 1270:  /* *addv8si3 */
    case 1269:  /* *subv8hi3 */
    case 1268:  /* *addv8hi3 */
    case 1267:  /* *subv16hi3 */
    case 1266:  /* *addv16hi3 */
    case 1265:  /* *subv16qi3 */
    case 1264:  /* *addv16qi3 */
    case 1263:  /* *subv32qi3 */
    case 1262:  /* *addv32qi3 */
    case 1261:  /* *vec_concatv2df */
    case 1260:  /* vec_dupv2df */
    case 1259:  /* sse2_movsd */
    case 1258:  /* sse2_loadlpd */
    case 1257:  /* sse2_loadhpd */
    case 1255:  /* sse2_storelpd */
    case 1253:  /* sse2_storehpd */
    case 1252:  /* sse2_shufpd_v2df */
    case 1251:  /* sse2_shufpd_v2di */
    case 1250:  /* vec_interleave_lowv2di */
    case 1248:  /* vec_interleave_highv2di */
    case 1245:  /* *vec_interleave_lowv2df */
    case 1243:  /* *vec_interleave_highv2df */
    case 1228:  /* *sse4_1_extractps */
    case 1226:  /* sse4_1_insertps */
    case 1225:  /* *vec_setv4sf_sse4_1 */
    case 1224:  /* vec_setv4sf_0 */
    case 1223:  /* vec_setv4si_0 */
    case 1222:  /* *vec_concatv4sf */
    case 1220:  /* *vec_concatv2sf_sse4_1 */
    case 1219:  /* vec_dupv4sf */
    case 1215:  /* sse_movss */
    case 1214:  /* sse_loadlps */
    case 1213:  /* sse_storelps */
    case 1212:  /* sse_loadhps */
    case 1211:  /* sse_storehps */
    case 1210:  /* sse_shufps_v4sf */
    case 1209:  /* sse_shufps_v4si */
    case 1207:  /* sse3_movsldup */
    case 1205:  /* sse3_movshdup */
    case 1203:  /* vec_interleave_lowv4sf */
    case 1201:  /* vec_interleave_highv4sf */
    case 1199:  /* sse_movlhps */
    case 1198:  /* sse_movhlps */
    case 1197:  /* sse2_cvtps2pd */
    case 1194:  /* *sse2_cvtpd2ps */
    case 1192:  /* sse2_cvtss2sd */
    case 1191:  /* sse2_cvtsd2ss */
    case 1190:  /* *sse2_cvttpd2dq */
    case 1187:  /* *sse2_cvtpd2dq */
    case 1184:  /* sse2_cvtdq2pd */
    case 1181:  /* sse2_cvttsd2si */
    case 1180:  /* sse2_cvtsd2si_2 */
    case 1179:  /* sse2_cvtsd2si */
    case 1178:  /* sse2_cvtsi2sd */
    case 1174:  /* fix_truncv4sfv4si2 */
    case 1172:  /* sse2_cvtps2dq */
    case 1170:  /* floatv4siv4sf2 */
    case 1169:  /* floatv8siv8sf2 */
    case 1168:  /* sse_cvttss2si */
    case 1167:  /* sse_cvtss2si_2 */
    case 1166:  /* sse_cvtss2si */
    case 1165:  /* sse_cvtsi2ss */
    case 1113:  /* *xortf3 */
    case 1112:  /* *iortf3 */
    case 1111:  /* *andtf3 */
    case 1110:  /* *xordf3 */
    case 1109:  /* *iordf3 */
    case 1108:  /* *anddf3 */
    case 1107:  /* *xorsf3 */
    case 1106:  /* *iorsf3 */
    case 1105:  /* *andsf3 */
    case 1104:  /* *andnottf3 */
    case 1103:  /* *andnotdf3 */
    case 1102:  /* *andnotsf3 */
    case 1101:  /* *xorv2df3 */
    case 1100:  /* *iorv2df3 */
    case 1099:  /* *andv2df3 */
    case 1098:  /* *xorv4df3 */
    case 1097:  /* *iorv4df3 */
    case 1096:  /* *andv4df3 */
    case 1095:  /* *xorv4sf3 */
    case 1094:  /* *iorv4sf3 */
    case 1093:  /* *andv4sf3 */
    case 1092:  /* *xorv8sf3 */
    case 1091:  /* *iorv8sf3 */
    case 1090:  /* *andv8sf3 */
    case 1089:  /* sse2_andnotv2df3 */
    case 1088:  /* avx_andnotv4df3 */
    case 1087:  /* sse_andnotv4sf3 */
    case 1086:  /* avx_andnotv8sf3 */
    case 1085:  /* sse2_ucomi */
    case 1084:  /* sse_ucomi */
    case 1083:  /* sse2_comi */
    case 1082:  /* sse_comi */
    case 1081:  /* sse2_vmmaskcmpv2df3 */
    case 1080:  /* sse_vmmaskcmpv4sf3 */
    case 1079:  /* sse2_maskcmpv2df3 */
    case 1078:  /* avx_maskcmpv4df3 */
    case 1077:  /* sse_maskcmpv4sf3 */
    case 1076:  /* avx_maskcmpv8sf3 */
    case 1075:  /* *sse2_maskcmpv2df3_comm */
    case 1074:  /* *avx_maskcmpv4df3_comm */
    case 1073:  /* *sse_maskcmpv4sf3_comm */
    case 1072:  /* *avx_maskcmpv8sf3_comm */
    case 1065:  /* sse3_hsubv4sf3 */
    case 1064:  /* sse3_haddv4sf3 */
    case 1061:  /* *sse3_hsubv2df3_low */
    case 1060:  /* *sse3_haddv2df3_low */
    case 1059:  /* sse3_hsubv2df3 */
    case 1058:  /* *sse3_haddv2df3 */
    case 1055:  /* sse3_addsubv4sf3 */
    case 1053:  /* sse3_addsubv2df3 */
    case 1051:  /* *ieee_smaxv2df3 */
    case 1050:  /* *ieee_smaxv4df3 */
    case 1049:  /* *ieee_smaxv4sf3 */
    case 1048:  /* *ieee_smaxv8sf3 */
    case 1047:  /* *ieee_sminv2df3 */
    case 1046:  /* *ieee_sminv4df3 */
    case 1045:  /* *ieee_sminv4sf3 */
    case 1044:  /* *ieee_sminv8sf3 */
    case 1043:  /* sse2_vmsminv2df3 */
    case 1042:  /* sse2_vmsmaxv2df3 */
    case 1041:  /* sse_vmsminv4sf3 */
    case 1040:  /* sse_vmsmaxv4sf3 */
    case 1039:  /* *sminv2df3 */
    case 1038:  /* *smaxv2df3 */
    case 1037:  /* *sminv4df3 */
    case 1036:  /* *smaxv4df3 */
    case 1035:  /* *sminv4sf3 */
    case 1034:  /* *smaxv4sf3 */
    case 1033:  /* *sminv8sf3 */
    case 1032:  /* *smaxv8sf3 */
    case 1031:  /* *sminv2df3_finite */
    case 1030:  /* *smaxv2df3_finite */
    case 1029:  /* *sminv4df3_finite */
    case 1028:  /* *smaxv4df3_finite */
    case 1027:  /* *sminv4sf3_finite */
    case 1026:  /* *smaxv4sf3_finite */
    case 1025:  /* *sminv8sf3_finite */
    case 1024:  /* *smaxv8sf3_finite */
    case 1023:  /* sse_vmrsqrtv4sf2 */
    case 1022:  /* sse_rsqrtv4sf2 */
    case 1021:  /* avx_rsqrtv8sf2 */
    case 1020:  /* sse2_vmsqrtv2df2 */
    case 1019:  /* sse_vmsqrtv4sf2 */
    case 1018:  /* sse2_sqrtv2df2 */
    case 1017:  /* avx_sqrtv4df2 */
    case 1016:  /* sse_sqrtv4sf2 */
    case 1015:  /* avx_sqrtv8sf2 */
    case 1014:  /* sse_vmrcpv4sf2 */
    case 1013:  /* sse_rcpv4sf2 */
    case 1012:  /* avx_rcpv8sf2 */
    case 1011:  /* sse2_vmdivv2df3 */
    case 1010:  /* sse_vmdivv4sf3 */
    case 1009:  /* sse2_divv2df3 */
    case 1008:  /* avx_divv4df3 */
    case 1007:  /* sse_divv4sf3 */
    case 1006:  /* avx_divv8sf3 */
    case 1005:  /* sse2_vmmulv2df3 */
    case 1004:  /* sse_vmmulv4sf3 */
    case 1003:  /* *mulv2df3 */
    case 1002:  /* *mulv4df3 */
    case 1001:  /* *mulv4sf3 */
    case 1000:  /* *mulv8sf3 */
    case 999:  /* sse2_vmsubv2df3 */
    case 998:  /* sse2_vmaddv2df3 */
    case 997:  /* sse_vmsubv4sf3 */
    case 996:  /* sse_vmaddv4sf3 */
    case 995:  /* *subv2df3 */
    case 994:  /* *addv2df3 */
    case 993:  /* *subv4df3 */
    case 992:  /* *addv4df3 */
    case 991:  /* *subv4sf3 */
    case 990:  /* *addv4sf3 */
    case 989:  /* *subv8sf3 */
    case 988:  /* *addv8sf3 */
    case 983:  /* sse2_movntv2di */
    case 982:  /* avx_movntv4di */
    case 981:  /* sse2_movntv2df */
    case 980:  /* avx_movntv4df */
    case 979:  /* sse_movntv4sf */
    case 978:  /* avx_movntv8sf */
    case 976:  /* sse3_lddqu */
    case 975:  /* avx_lddqu256 */
    case 974:  /* sse2_storedqu */
    case 973:  /* avx_storedqu256 */
    case 972:  /* sse2_loaddqu */
    case 971:  /* avx_loaddqu256 */
    case 970:  /* sse2_storeupd */
    case 969:  /* avx_storeupd256 */
    case 968:  /* sse_storeups */
    case 967:  /* avx_storeups256 */
    case 966:  /* sse2_loadupd */
    case 965:  /* avx_loadupd256 */
    case 964:  /* sse_loadups */
    case 963:  /* avx_loadups256 */
    case 961:  /* sse2_movq128 */
    case 960:  /* *movv2df_internal */
    case 959:  /* *movv4df_internal */
    case 958:  /* *movv4sf_internal */
    case 957:  /* *movv8sf_internal */
    case 956:  /* *movv1ti_internal */
    case 955:  /* *movv2ti_internal */
    case 954:  /* *movv2di_internal */
    case 953:  /* *movv4di_internal */
    case 952:  /* *movv4si_internal */
    case 951:  /* *movv8si_internal */
    case 950:  /* *movv8hi_internal */
    case 949:  /* *movv16hi_internal */
    case 948:  /* *movv16qi_internal */
    case 947:  /* *movv32qi_internal */
    case 840:  /* *movv2sf_internal */
    case 839:  /* *movv1di_internal */
    case 838:  /* *movv2si_internal */
    case 837:  /* *movv4hi_internal */
    case 836:  /* *movv8qi_internal */
    case 788:  /* *ieee_smindf3 */
    case 787:  /* *ieee_smaxdf3 */
    case 786:  /* *ieee_sminsf3 */
    case 785:  /* *ieee_smaxsf3 */
    case 784:  /* smindf3 */
    case 783:  /* smaxdf3 */
    case 782:  /* sminsf3 */
    case 781:  /* smaxsf3 */
    case 777:  /* *movdfcc_1 */
    case 742:  /* movmsk_df */
    case 700:  /* sse4_1_rounddf2 */
    case 699:  /* sse4_1_roundsf2 */
    case 670:  /* *sqrtdf2_sse */
    case 669:  /* *sqrtsf2_sse */
    case 668:  /* *rsqrtsf2_sse */
    case 662:  /* *fop_xf_6_i387 */
    case 661:  /* *fop_xf_6_i387 */
    case 660:  /* *fop_xf_5_i387 */
    case 659:  /* *fop_xf_5_i387 */
    case 658:  /* *fop_xf_4_i387 */
    case 657:  /* *fop_xf_4_i387 */
    case 656:  /* *fop_xf_3_i387 */
    case 655:  /* *fop_xf_3_i387 */
    case 654:  /* *fop_xf_2_i387 */
    case 653:  /* *fop_xf_2_i387 */
    case 652:  /* *fop_xf_1_i387 */
    case 651:  /* *fop_xf_comm_i387 */
    case 650:  /* *fop_df_6_i387 */
    case 649:  /* *fop_df_5_i387 */
    case 648:  /* *fop_df_4_i387 */
    case 647:  /* *fop_df_3_i387 */
    case 646:  /* *fop_sf_3_i387 */
    case 645:  /* *fop_df_3_i387 */
    case 644:  /* *fop_sf_3_i387 */
    case 643:  /* *fop_df_2_i387 */
    case 642:  /* *fop_sf_2_i387 */
    case 641:  /* *fop_df_2_i387 */
    case 640:  /* *fop_sf_2_i387 */
    case 639:  /* *fop_df_1_i387 */
    case 638:  /* *fop_sf_1_i387 */
    case 637:  /* *fop_df_1_sse */
    case 636:  /* *fop_sf_1_sse */
    case 635:  /* *rcpsf2_sse */
    case 634:  /* *fop_df_1_mixed */
    case 633:  /* *fop_sf_1_mixed */
    case 632:  /* *fop_df_comm_i387 */
    case 631:  /* *fop_sf_comm_i387 */
    case 630:  /* *fop_df_comm_sse */
    case 629:  /* *fop_sf_comm_sse */
    case 628:  /* *fop_df_comm_mixed */
    case 627:  /* *fop_sf_comm_mixed */
    case 502:  /* setcc_df_sse */
    case 501:  /* setcc_sf_sse */
    case 306:  /* *umulsidi3_1 */
    case 211:  /* *floatdidf2_sse_nointerunit */
    case 210:  /* *floatsidf2_sse_nointerunit */
    case 209:  /* *floatdisf2_sse_nointerunit */
    case 208:  /* *floatsisf2_sse_nointerunit */
    case 207:  /* *floatdidf2_sse_interunit */
    case 206:  /* *floatsidf2_sse_interunit */
    case 205:  /* *floatdisf2_sse_interunit */
    case 204:  /* *floatsisf2_sse_interunit */
    case 197:  /* *floatdidf2_mixed_nointerunit */
    case 196:  /* *floatsidf2_mixed_nointerunit */
    case 195:  /* *floatdisf2_mixed_nointerunit */
    case 194:  /* *floatsisf2_mixed_nointerunit */
    case 193:  /* *floatdidf2_mixed_interunit */
    case 192:  /* *floatsidf2_mixed_interunit */
    case 191:  /* *floatdisf2_mixed_interunit */
    case 190:  /* *floatsisf2_mixed_interunit */
    case 189:  /* *floatsidf2_mixed_with_temp */
    case 188:  /* *floatsisf2_mixed_with_temp */
    case 185:  /* *floatsidf2_vector_mixed_with_temp */
    case 184:  /* *floatsisf2_vector_mixed_with_temp */
    case 148:  /* fix_truncdfsi_sse */
    case 147:  /* fix_truncsfsi_sse */
    case 136:  /* *truncdfsf_mixed */
    case 134:  /* *truncdfsf_fast_sse */
    case 133:  /* *truncdfsf_fast_mixed */
    case 129:  /* *extendsfdf2_sse */
    case 128:  /* *extendsfdf2_mixed */
    case 117:  /* *zero_extendsidi2 */
    case 113:  /* *movsf_internal */
    case 112:  /* *movdf_internal */
    case 111:  /* *movxf_internal */
    case 110:  /* *movtf_internal_sse */
    case 109:  /* *pushsf */
    case 78:  /* *movsi_internal */
    case 77:  /* *movdi_internal */
    case 76:  /* *movti_internal_sse */
    case 56:  /* *cmpiudf_sse */
    case 55:  /* *cmpiusf_sse */
    case 54:  /* *cmpidf_sse */
    case 53:  /* *cmpisf_sse */
    case 52:  /* *cmpiudf_mixed */
    case 51:  /* *cmpiusf_mixed */
    case 50:  /* *cmpidf_mixed */
    case 49:  /* *cmpisf_mixed */
      extract_constrain_insn_cached (insn);
      if (((cached_type = get_attr_type (insn)) == TYPE_OTHER) || ((cached_type == TYPE_MULTI) || ((cached_type == TYPE_FISTP) || (cached_type == TYPE_FRNDINT))))
        {
	  return 16 /* 0x10 */;
        }
      else if (cached_type == TYPE_FCMP)
        {
	  return 4;
        }
      else if (get_attr_unit (insn) == UNIT_I387)
        {
	  return 2 + get_attr_prefix_data16 (insn) + get_attr_length_address (insn);
        }
      else if (((cached_prefix = get_attr_prefix (insn)) == PREFIX_VEX) || ((cached_prefix == PREFIX_MAYBE_VEX) && (
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX))))
        {
	  return get_attr_length_vex (insn) + get_attr_length_immediate (insn) + get_attr_modrm (insn) + get_attr_length_address (insn);
        }
      else
        {
	  return get_attr_modrm (insn) + get_attr_prefix_0f (insn) + get_attr_prefix_rex (insn) + get_attr_prefix_extra (insn) + 1 + get_attr_prefix_rep (insn) + get_attr_prefix_data16 (insn) + get_attr_length_immediate (insn) + get_attr_length_address (insn);
        }

    default:
      return get_attr_modrm (insn) + get_attr_prefix_0f (insn) + get_attr_prefix_rex (insn) + get_attr_prefix_extra (insn) + 1 + get_attr_prefix_rep (insn) + get_attr_prefix_data16 (insn) + get_attr_length_immediate (insn) + get_attr_length_address (insn);

    }
}

int
insn_default_length (rtx insn ATTRIBUTE_UNUSED)
{
  enum attr_type cached_type ATTRIBUTE_UNUSED;
  enum attr_prefix cached_prefix ATTRIBUTE_UNUSED;

  switch (recog_memoized (insn))
    {
    case 868:  /* *vec_extractv2sf_1 */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 4)
        {
	  return 2 + get_attr_prefix_data16 (insn) + get_attr_length_address (insn);
        }
      else
        {
	  return get_attr_modrm (insn) + get_attr_prefix_0f (insn) + get_attr_prefix_rex (insn) + get_attr_prefix_extra (insn) + 1 + get_attr_prefix_rep (insn) + get_attr_prefix_data16 (insn) + get_attr_length_immediate (insn) + get_attr_length_address (insn);
        }

    case 778:  /* *movsfcc_1_387 */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return 2 + get_attr_prefix_data16 (insn) + get_attr_length_address (insn);
        }
      else
        {
	  return get_attr_modrm (insn) + get_attr_prefix_0f (insn) + get_attr_prefix_rex (insn) + get_attr_prefix_extra (insn) + 1 + get_attr_prefix_rep (insn) + get_attr_prefix_data16 (insn) + get_attr_length_immediate (insn) + get_attr_length_address (insn);
        }

    case 187:  /* *floatsidf2_vector_mixed */
    case 186:  /* *floatsisf2_vector_mixed */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return 2 + get_attr_prefix_data16 (insn) + get_attr_length_address (insn);
        }
      else
        {
	  return get_attr_modrm (insn) + get_attr_prefix_0f (insn) + get_attr_prefix_rex (insn) + get_attr_prefix_extra (insn) + 1 + get_attr_prefix_rep (insn) + get_attr_prefix_data16 (insn) + get_attr_length_immediate (insn) + get_attr_length_address (insn);
        }

    case 217:  /* *floatdixf2_i387_with_temp */
    case 216:  /* *floatdidf2_i387_with_temp */
    case 215:  /* *floatdisf2_i387_with_temp */
    case 214:  /* *floatsixf2_i387_with_temp */
    case 213:  /* *floatsidf2_i387_with_temp */
    case 212:  /* *floatsisf2_i387_with_temp */
    case 174:  /* *floathixf2_i387_with_temp */
    case 173:  /* *floathidf2_i387_with_temp */
    case 172:  /* *floathisf2_i387_with_temp */
    case 140:  /* *truncxfdf2_mixed */
    case 139:  /* *truncxfsf2_mixed */
    case 137:  /* *truncdfsf_i387 */
      extract_constrain_insn_cached (insn);
      if (which_alternative != 0)
        {
	  return 16 /* 0x10 */;
        }
      else
        {
	  return 2 + get_attr_prefix_data16 (insn) + get_attr_length_address (insn);
        }

    case 1877:  /* storedi_via_fpu */
    case 1876:  /* loaddi_via_fpu */
    case 776:  /* *movxfcc_1 */
    case 710:  /* fistsi2_with_temp */
    case 709:  /* fisthi2_with_temp */
    case 708:  /* fistsi2 */
    case 707:  /* fisthi2 */
    case 706:  /* *fistsi2_1 */
    case 705:  /* *fisthi2_1 */
    case 704:  /* fistdi2_with_temp */
    case 703:  /* fistdi2 */
    case 702:  /* *fistdi2_1 */
    case 701:  /* rintxf2 */
    case 698:  /* *fscalexf4_i387 */
    case 697:  /* *f2xm1xf2_i387 */
    case 696:  /* fxtract_extenddfxf3_i387 */
    case 695:  /* fxtract_extendsfxf3_i387 */
    case 694:  /* fxtractxf3_i387 */
    case 693:  /* fyl2xp1_extenddfxf3_i387 */
    case 692:  /* fyl2xp1_extendsfxf3_i387 */
    case 691:  /* fyl2xp1xf3_i387 */
    case 690:  /* fyl2x_extenddfxf3_i387 */
    case 689:  /* fyl2x_extendsfxf3_i387 */
    case 688:  /* fyl2xxf3_i387 */
    case 687:  /* fpatan_extenddfxf3_i387 */
    case 686:  /* fpatan_extendsfxf3_i387 */
    case 685:  /* *fpatanxf3_i387 */
    case 684:  /* fptan_extenddfxf4_i387 */
    case 683:  /* fptan_extendsfxf4_i387 */
    case 682:  /* fptanxf4_i387 */
    case 681:  /* sincos_extenddfxf3_i387 */
    case 680:  /* sincos_extendsfxf3_i387 */
    case 679:  /* sincosxf3 */
    case 678:  /* *cos_extenddfxf2_i387 */
    case 677:  /* *sin_extenddfxf2_i387 */
    case 676:  /* *cos_extendsfxf2_i387 */
    case 675:  /* *sin_extendsfxf2_i387 */
    case 674:  /* *cosxf2_i387 */
    case 673:  /* *sinxf2_i387 */
    case 672:  /* fprem1xf4_i387 */
    case 671:  /* fpremxf4_i387 */
    case 667:  /* sqrt_extenddfxf2_i387 */
    case 666:  /* sqrt_extendsfxf2_i387 */
    case 665:  /* sqrtxf2 */
    case 664:  /* truncxfdf2_i387_noop_unspec */
    case 663:  /* truncxfsf2_i387_noop_unspec */
    case 409:  /* *negextenddfxf2 */
    case 408:  /* *absextenddfxf2 */
    case 407:  /* *negextendsfxf2 */
    case 406:  /* *absextendsfxf2 */
    case 405:  /* *negextendsfdf2 */
    case 404:  /* *absextendsfdf2 */
    case 403:  /* *negxf2_1 */
    case 402:  /* *absxf2_1 */
    case 401:  /* *negdf2_1 */
    case 400:  /* *absdf2_1 */
    case 399:  /* *negsf2_1 */
    case 398:  /* *abssf2_1 */
    case 223:  /* *floatdixf2_i387 */
    case 222:  /* *floatdidf2_i387 */
    case 221:  /* *floatdisf2_i387 */
    case 220:  /* *floatsixf2_i387 */
    case 219:  /* *floatsidf2_i387 */
    case 218:  /* *floatsisf2_i387 */
    case 177:  /* *floathixf2_i387 */
    case 176:  /* *floathidf2_i387 */
    case 175:  /* *floathisf2_i387 */
    case 157:  /* fix_truncdi_i387_fisttp_with_temp */
    case 156:  /* fix_truncsi_i387_fisttp_with_temp */
    case 155:  /* fix_trunchi_i387_fisttp_with_temp */
    case 154:  /* fix_truncdi_i387_fisttp */
    case 153:  /* fix_truncsi_i387_fisttp */
    case 152:  /* fix_trunchi_i387_fisttp */
    case 151:  /* fix_truncdi_fisttp_i387_1 */
    case 150:  /* fix_truncsi_fisttp_i387_1 */
    case 149:  /* fix_trunchi_fisttp_i387_1 */
    case 144:  /* *truncxfdf2_i387 */
    case 143:  /* *truncxfsf2_i387 */
    case 142:  /* truncxfdf2_i387_noop */
    case 141:  /* truncxfsf2_i387_noop */
    case 138:  /* *truncdfsf2_i387_1 */
    case 135:  /* *truncdfsf_fast_i387 */
    case 132:  /* *extenddfxf2_i387 */
    case 131:  /* *extendsfxf2_i387 */
    case 130:  /* *extendsfdf2_i387 */
    case 116:  /* *swapdf */
    case 115:  /* *swapsf */
    case 114:  /* swapxf */
      return 2 + get_attr_prefix_data16 (insn) + get_attr_length_address (insn);

    case 1866:  /* *avx2_gatherdiv8sf_4 */
    case 1865:  /* *avx2_gatherdiv8sf_4 */
    case 1864:  /* *avx2_gatherdiv8si_4 */
    case 1863:  /* *avx2_gatherdiv8si_4 */
    case 1862:  /* *avx2_gatherdiv8sf_3 */
    case 1861:  /* *avx2_gatherdiv8sf_3 */
    case 1860:  /* *avx2_gatherdiv8si_3 */
    case 1859:  /* *avx2_gatherdiv8si_3 */
    case 1858:  /* *avx2_gatherdiv8sf_2 */
    case 1857:  /* *avx2_gatherdiv8sf_2 */
    case 1856:  /* *avx2_gatherdiv8si_2 */
    case 1855:  /* *avx2_gatherdiv8si_2 */
    case 1854:  /* *avx2_gatherdiv4sf_2 */
    case 1853:  /* *avx2_gatherdiv4sf_2 */
    case 1852:  /* *avx2_gatherdiv4si_2 */
    case 1851:  /* *avx2_gatherdiv4si_2 */
    case 1850:  /* *avx2_gatherdiv4df_2 */
    case 1849:  /* *avx2_gatherdiv4df_2 */
    case 1848:  /* *avx2_gatherdiv4di_2 */
    case 1847:  /* *avx2_gatherdiv4di_2 */
    case 1846:  /* *avx2_gatherdiv2df_2 */
    case 1845:  /* *avx2_gatherdiv2df_2 */
    case 1844:  /* *avx2_gatherdiv2di_2 */
    case 1843:  /* *avx2_gatherdiv2di_2 */
    case 1842:  /* *avx2_gatherdiv8sf */
    case 1841:  /* *avx2_gatherdiv8sf */
    case 1840:  /* *avx2_gatherdiv8si */
    case 1839:  /* *avx2_gatherdiv8si */
    case 1838:  /* *avx2_gatherdiv4sf */
    case 1837:  /* *avx2_gatherdiv4sf */
    case 1836:  /* *avx2_gatherdiv4si */
    case 1835:  /* *avx2_gatherdiv4si */
    case 1834:  /* *avx2_gatherdiv4df */
    case 1833:  /* *avx2_gatherdiv4df */
    case 1832:  /* *avx2_gatherdiv4di */
    case 1831:  /* *avx2_gatherdiv4di */
    case 1830:  /* *avx2_gatherdiv2df */
    case 1829:  /* *avx2_gatherdiv2df */
    case 1828:  /* *avx2_gatherdiv2di */
    case 1827:  /* *avx2_gatherdiv2di */
    case 1826:  /* *avx2_gathersiv8sf_2 */
    case 1825:  /* *avx2_gathersiv8sf_2 */
    case 1824:  /* *avx2_gathersiv8si_2 */
    case 1823:  /* *avx2_gathersiv8si_2 */
    case 1822:  /* *avx2_gathersiv4sf_2 */
    case 1821:  /* *avx2_gathersiv4sf_2 */
    case 1820:  /* *avx2_gathersiv4si_2 */
    case 1819:  /* *avx2_gathersiv4si_2 */
    case 1818:  /* *avx2_gathersiv4df_2 */
    case 1817:  /* *avx2_gathersiv4df_2 */
    case 1816:  /* *avx2_gathersiv4di_2 */
    case 1815:  /* *avx2_gathersiv4di_2 */
    case 1814:  /* *avx2_gathersiv2df_2 */
    case 1813:  /* *avx2_gathersiv2df_2 */
    case 1812:  /* *avx2_gathersiv2di_2 */
    case 1811:  /* *avx2_gathersiv2di_2 */
    case 1810:  /* *avx2_gathersiv8sf */
    case 1809:  /* *avx2_gathersiv8sf */
    case 1808:  /* *avx2_gathersiv8si */
    case 1807:  /* *avx2_gathersiv8si */
    case 1806:  /* *avx2_gathersiv4sf */
    case 1805:  /* *avx2_gathersiv4sf */
    case 1804:  /* *avx2_gathersiv4si */
    case 1803:  /* *avx2_gathersiv4si */
    case 1802:  /* *avx2_gathersiv4df */
    case 1801:  /* *avx2_gathersiv4df */
    case 1800:  /* *avx2_gathersiv4di */
    case 1799:  /* *avx2_gathersiv4di */
    case 1798:  /* *avx2_gathersiv2df */
    case 1797:  /* *avx2_gathersiv2df */
    case 1796:  /* *avx2_gathersiv2di */
    case 1795:  /* *avx2_gathersiv2di */
    case 1794:  /* vcvtps2ph256 */
    case 1793:  /* *vcvtps2ph_store */
    case 1792:  /* *vcvtps2ph */
    case 1791:  /* vcvtph2ps256 */
    case 1790:  /* *vcvtph2ps_load */
    case 1789:  /* vcvtph2ps */
    case 1788:  /* avx_vec_concatv4df */
    case 1787:  /* avx_vec_concatv8sf */
    case 1786:  /* avx_vec_concatv4di */
    case 1785:  /* avx_vec_concatv8si */
    case 1784:  /* avx_vec_concatv16hi */
    case 1783:  /* avx_vec_concatv32qi */
    case 1782:  /* avx2_lshrvv2di */
    case 1781:  /* avx2_ashlvv2di */
    case 1780:  /* avx2_lshrvv4di */
    case 1779:  /* avx2_ashlvv4di */
    case 1778:  /* avx2_lshrvv4si */
    case 1777:  /* avx2_ashlvv4si */
    case 1776:  /* avx2_lshrvv8si */
    case 1775:  /* avx2_ashlvv8si */
    case 1774:  /* avx2_ashrvv4si */
    case 1773:  /* avx2_ashrvv8si */
    case 1769:  /* avx2_maskstoreq256 */
    case 1768:  /* avx2_maskstored256 */
    case 1767:  /* avx2_maskstoreq */
    case 1766:  /* avx2_maskstored */
    case 1765:  /* avx_maskstorepd256 */
    case 1764:  /* avx_maskstoreps256 */
    case 1763:  /* avx_maskstorepd */
    case 1762:  /* avx_maskstoreps */
    case 1761:  /* avx2_maskloadq256 */
    case 1760:  /* avx2_maskloadd256 */
    case 1759:  /* avx2_maskloadq */
    case 1758:  /* avx2_maskloadd */
    case 1757:  /* avx_maskloadpd256 */
    case 1756:  /* avx_maskloadps256 */
    case 1755:  /* avx_maskloadpd */
    case 1754:  /* avx_maskloadps */
    case 1753:  /* vec_set_hi_v32qi */
    case 1752:  /* vec_set_lo_v32qi */
    case 1751:  /* vec_set_hi_v16hi */
    case 1750:  /* vec_set_lo_v16hi */
    case 1749:  /* vec_set_hi_v8sf */
    case 1748:  /* vec_set_hi_v8si */
    case 1747:  /* vec_set_lo_v8sf */
    case 1746:  /* vec_set_lo_v8si */
    case 1745:  /* vec_set_hi_v4df */
    case 1744:  /* vec_set_hi_v4di */
    case 1743:  /* vec_set_lo_v4df */
    case 1742:  /* vec_set_lo_v4di */
    case 1741:  /* avx2_vec_set_hi_v4di */
    case 1740:  /* avx2_vec_set_lo_v4di */
    case 1739:  /* *avx_vperm2f128v4df_nozero */
    case 1738:  /* *avx_vperm2f128v8sf_nozero */
    case 1737:  /* *avx_vperm2f128v8si_nozero */
    case 1736:  /* *avx_vperm2f128v4df_full */
    case 1735:  /* *avx_vperm2f128v8sf_full */
    case 1734:  /* *avx_vperm2f128v8si_full */
    case 1733:  /* avx_vpermilvarv2df3 */
    case 1732:  /* avx_vpermilvarv4df3 */
    case 1731:  /* avx_vpermilvarv4sf3 */
    case 1730:  /* avx_vpermilvarv8sf3 */
    case 1729:  /* *avx_vpermilpv2df */
    case 1728:  /* *avx_vpermilpv4df */
    case 1727:  /* *avx_vpermilpv4sf */
    case 1726:  /* *avx_vpermilpv8sf */
    case 1723:  /* *avx_vperm_broadcast_v4sf */
    case 1722:  /* avx_vbroadcastf128_v4df */
    case 1721:  /* avx_vbroadcastf128_v8sf */
    case 1720:  /* avx_vbroadcastf128_v4di */
    case 1719:  /* avx_vbroadcastf128_v8si */
    case 1718:  /* avx_vbroadcastf128_v16hi */
    case 1717:  /* avx_vbroadcastf128_v32qi */
    case 1716:  /* avx2_vbroadcasti128_v4di */
    case 1715:  /* avx2_vbroadcasti128_v8si */
    case 1714:  /* avx2_vbroadcasti128_v16hi */
    case 1713:  /* avx2_vbroadcasti128_v32qi */
    case 1712:  /* vec_dupv4df */
    case 1711:  /* vec_dupv4di */
    case 1710:  /* vec_dupv8sf */
    case 1709:  /* vec_dupv8si */
    case 1708:  /* avx2_vec_dupv4df */
    case 1707:  /* avx2_permv2ti */
    case 1706:  /* avx2_permv4df_1 */
    case 1705:  /* avx2_permv4di_1 */
    case 1704:  /* avx2_permvarv8sf */
    case 1703:  /* avx2_permvarv8si */
    case 1702:  /* avx2_pbroadcastv4di_1 */
    case 1701:  /* avx2_pbroadcastv8si_1 */
    case 1700:  /* avx2_pbroadcastv16hi_1 */
    case 1699:  /* avx2_pbroadcastv32qi_1 */
    case 1698:  /* avx2_pbroadcastv2di */
    case 1697:  /* avx2_pbroadcastv4di */
    case 1696:  /* avx2_pbroadcastv4si */
    case 1695:  /* avx2_pbroadcastv8si */
    case 1694:  /* avx2_pbroadcastv8hi */
    case 1693:  /* avx2_pbroadcastv16hi */
    case 1692:  /* avx2_pbroadcastv16qi */
    case 1691:  /* avx2_pbroadcastv32qi */
    case 1690:  /* avx_vzeroupper */
    case 1689:  /* *avx_vzeroall */
    case 1680:  /* xop_vpermil2v4df3 */
    case 1678:  /* xop_vpermil2v8sf3 */
    case 1659:  /* xop_frczv4df2 */
    case 1658:  /* xop_frczv8sf2 */
    case 1573:  /* avx_ptest256 */
    case 1572:  /* avx_vtestpd */
    case 1571:  /* avx_vtestpd256 */
    case 1570:  /* avx_vtestps */
    case 1569:  /* avx_vtestps256 */
    case 1566:  /* avx2_zero_extendv4siv4di2 */
    case 1565:  /* avx2_sign_extendv4siv4di2 */
    case 1562:  /* avx2_zero_extendv4hiv4di2 */
    case 1561:  /* avx2_sign_extendv4hiv4di2 */
    case 1558:  /* avx2_zero_extendv4qiv4di2 */
    case 1557:  /* avx2_sign_extendv4qiv4di2 */
    case 1554:  /* avx2_zero_extendv8hiv8si2 */
    case 1553:  /* avx2_sign_extendv8hiv8si2 */
    case 1550:  /* avx2_zero_extendv8qiv8si2 */
    case 1549:  /* avx2_sign_extendv8qiv8si2 */
    case 1546:  /* avx2_zero_extendv16qiv16hi2 */
    case 1545:  /* avx2_sign_extendv16qiv16hi2 */
    case 1543:  /* avx2_pblenddv4si */
    case 1542:  /* avx2_pblenddv8si */
    case 1541:  /* *avx2_pblendw */
    case 1536:  /* avx2_packusdw */
    case 1482:  /* avx2_pmaddubsw256 */
    case 1477:  /* avx2_phsubdv8si3 */
    case 1476:  /* avx2_phadddv8si3 */
    case 1467:  /* avx2_phsubswv16hi3 */
    case 1466:  /* avx2_phsubwv16hi3 */
    case 1465:  /* avx2_phaddswv16hi3 */
    case 1464:  /* avx2_phaddwv16hi3 */
    case 1455:  /* avx2_pmovmskb */
    case 1431:  /* avx2_pshufhw_1 */
    case 1429:  /* avx2_pshuflw_1 */
    case 1427:  /* avx2_pshufd_1 */
    case 1416:  /* avx2_interleave_lowv8si */
    case 1414:  /* avx2_interleave_highv8si */
    case 1412:  /* avx2_interleave_lowv16hi */
    case 1410:  /* avx2_interleave_highv16hi */
    case 1408:  /* avx2_interleave_lowv32qi */
    case 1406:  /* avx2_interleave_highv32qi */
    case 1364:  /* avx2_gtv4di3 */
    case 1363:  /* avx2_gtv8si3 */
    case 1362:  /* avx2_gtv16hi3 */
    case 1361:  /* avx2_gtv32qi3 */
    case 1355:  /* *avx2_eqv4di3 */
    case 1354:  /* *avx2_eqv8si3 */
    case 1353:  /* *avx2_eqv16hi3 */
    case 1352:  /* *avx2_eqv32qi3 */
    case 1339:  /* *avx2_uminv8si3 */
    case 1338:  /* *avx2_umaxv8si3 */
    case 1337:  /* *avx2_sminv8si3 */
    case 1336:  /* *avx2_smaxv8si3 */
    case 1335:  /* *avx2_uminv16hi3 */
    case 1334:  /* *avx2_umaxv16hi3 */
    case 1333:  /* *avx2_sminv16hi3 */
    case 1332:  /* *avx2_smaxv16hi3 */
    case 1331:  /* *avx2_uminv32qi3 */
    case 1330:  /* *avx2_umaxv32qi3 */
    case 1329:  /* *avx2_sminv32qi3 */
    case 1328:  /* *avx2_smaxv32qi3 */
    case 1304:  /* *avx2_pmaddwd */
    case 1302:  /* *vec_widen_smult_even_v8si */
    case 1300:  /* *vec_widen_umult_even_v8si */
    case 1249:  /* avx2_interleave_lowv4di */
    case 1247:  /* avx2_interleave_highv4di */
    case 1246:  /* avx_shufpd256_1 */
    case 1244:  /* *avx_unpcklpd256 */
    case 1242:  /* avx_unpckhpd256 */
    case 1241:  /* vec_extract_hi_v32qi */
    case 1239:  /* vec_extract_hi_v16hi */
    case 1237:  /* vec_extract_hi_v8sf */
    case 1236:  /* vec_extract_hi_v8si */
    case 1233:  /* vec_extract_hi_v4df */
    case 1232:  /* vec_extract_hi_v4di */
    case 1218:  /* avx2_vec_dupv8sf_1 */
    case 1217:  /* avx2_vec_dupv4sf */
    case 1216:  /* avx2_vec_dupv8sf */
    case 1208:  /* avx_shufps256_1 */
    case 1206:  /* avx_movsldup256 */
    case 1204:  /* avx_movshdup256 */
    case 1202:  /* avx_unpcklps256 */
    case 1200:  /* avx_unpckhps256 */
    case 1196:  /* *avx_cvtps2pd256_2 */
    case 1195:  /* avx_cvtps2pd256 */
    case 1193:  /* avx_cvtpd2ps256 */
    case 1189:  /* *avx_cvttpd2dq256_2 */
    case 1188:  /* fix_truncv4dfv4si2 */
    case 1186:  /* *avx_cvtpd2dq256_2 */
    case 1185:  /* avx_cvtpd2dq256 */
    case 1183:  /* avx_cvtdq2pd256_2 */
    case 1182:  /* floatv4siv4df2 */
    case 1173:  /* fix_truncv8sfv8si2 */
    case 1171:  /* avx_cvtps2dq256 */
    case 1144:  /* *fma_fmsubadd_v4df */
    case 1142:  /* *fma_fmsubadd_v8sf */
    case 1140:  /* *fma_fmaddsub_v4df */
    case 1138:  /* *fma_fmaddsub_v8sf */
    case 1137:  /* *fma_fnmsub_v4df */
    case 1136:  /* *fma_fnmsub_v8sf */
    case 1131:  /* *fma_fnmadd_v4df */
    case 1130:  /* *fma_fnmadd_v8sf */
    case 1125:  /* *fma_fmsub_v4df */
    case 1124:  /* *fma_fmsub_v8sf */
    case 1119:  /* *fma_fmadd_v4df */
    case 1118:  /* *fma_fmadd_v8sf */
    case 1071:  /* avx_vmcmpv2df3 */
    case 1070:  /* avx_vmcmpv4sf3 */
    case 1069:  /* avx_cmpv2df3 */
    case 1068:  /* avx_cmpv4df3 */
    case 1067:  /* avx_cmpv4sf3 */
    case 1066:  /* avx_cmpv8sf3 */
    case 1063:  /* avx_hsubv8sf3 */
    case 1062:  /* avx_haddv8sf3 */
    case 1057:  /* avx_hsubv4df3 */
    case 1056:  /* avx_haddv4df3 */
    case 1054:  /* avx_addsubv8sf3 */
    case 1052:  /* avx_addsubv4df3 */
    case 588:  /* bmi2_pext_si3 */
    case 587:  /* bmi2_pdep_si3 */
    case 586:  /* bmi2_bzhi_si3 */
    case 305:  /* *bmi2_umulsidi3_1 */
    case 75:  /* *movoi_internal_avx */
      return get_attr_length_vex (insn) + get_attr_length_immediate (insn) + get_attr_modrm (insn) + get_attr_length_address (insn);

    case -1:
      if (GET_CODE (PATTERN (insn)) != ASM_INPUT
          && asm_noperands (PATTERN (insn)) < 0)
        fatal_insn_not_found (insn);
      return 128 /* 0x80 */;

    case 1463:  /* sse3_monitor */
    case 1462:  /* sse3_mwait */
    case 835:  /* xtest_1 */
    case 834:  /* xabort */
    case 833:  /* xend */
    case 815:  /* rdtscp */
    case 563:  /* simple_return_pop_internal */
      return 3;

    case 831:  /* *pause */
    case 814:  /* rdtsc */
    case 813:  /* rdpmc */
    case 799:  /* trap */
    case 625:  /* *tls_dynamic_gnu2_call_32 */
    case 612:  /* *parityhi2_cmp */
    case 562:  /* simple_return_internal_long */
      return 2;

    case 826:  /* *lwp_lwpinssi3_1 */
    case 825:  /* *lwp_lwpvalsi3_1 */
      extract_constrain_insn_cached (insn);
      return 
#line 18005 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_address_default (insn) + 9);

    case 820:  /* xrstor */
    case 819:  /* xsaveopt */
    case 818:  /* xsave */
    case 817:  /* fxrstor */
    case 816:  /* fxsave */
      extract_constrain_insn_cached (insn);
      return 
#line 17891 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_address_default (insn) + 3);

    case 743:  /* cld */
    case 565:  /* nop */
    case 561:  /* simple_return_internal */
    case 48:  /* x86_sahf_1 */
      return 1;

    case 62:  /* *cmpiuxf_i387 */
    case 61:  /* *cmpiudf_i387 */
    case 60:  /* *cmpiusf_i387 */
    case 59:  /* *cmpixf_i387 */
    case 58:  /* *cmpidf_i387 */
    case 57:  /* *cmpisf_i387 */
    case 739:  /* fxamxf2_i387 */
    case 738:  /* fxamdf2_i387 */
    case 737:  /* fxamsf2_i387 */
    case 609:  /* bswaphi_lowpart */
      return 4;

    case 623:  /* *add_tp_di */
    case 622:  /* *add_tp_si */
    case 621:  /* *add_tp_x32_zext */
    case 620:  /* *add_tp_x32 */
    case 619:  /* *load_tp_di */
    case 618:  /* *load_tp_si */
    case 617:  /* *load_tp_x32_zext */
    case 616:  /* *load_tp_x32 */
      return 7;

    case 614:  /* *tls_local_dynamic_base_32_gnu */
      return 11 /* 0xb */;

    case 613:  /* *tls_global_dynamic_32_gnu */
    case 569:  /* set_got_labelled */
    case 568:  /* set_got */
      return 12 /* 0xc */;

    case 608:  /* *bswaphi_lowpart_1 */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return 2;
        }
      else
        {
	  return 4;
        }

    case 573:  /* split_stack_return */
      extract_insn_cached (insn);
      if (const0_operand (operands[0], SImode))
        {
	  return 1;
        }
      else
        {
	  return 3;
        }

    case 1905:  /* atomic_xorsi */
    case 1904:  /* atomic_orsi */
    case 1903:  /* atomic_andsi */
    case 1902:  /* atomic_xorhi */
    case 1901:  /* atomic_orhi */
    case 1900:  /* atomic_andhi */
    case 1899:  /* atomic_xorqi */
    case 1898:  /* atomic_orqi */
    case 1897:  /* atomic_andqi */
    case 1896:  /* atomic_subsi */
    case 1895:  /* atomic_subhi */
    case 1894:  /* atomic_subqi */
    case 1893:  /* atomic_addsi */
    case 1892:  /* atomic_addhi */
    case 1891:  /* atomic_addqi */
    case 1890:  /* atomic_exchangesi */
    case 1889:  /* atomic_exchangehi */
    case 1888:  /* atomic_exchangeqi */
    case 1887:  /* *atomic_fetch_add_cmpsi */
    case 1886:  /* *atomic_fetch_add_cmphi */
    case 1885:  /* *atomic_fetch_add_cmpqi */
    case 1884:  /* atomic_fetch_addsi */
    case 1883:  /* atomic_fetch_addhi */
    case 1882:  /* atomic_fetch_addqi */
    case 1881:  /* atomic_compare_and_swapdi_doubleword */
    case 1880:  /* atomic_compare_and_swapsi_1 */
    case 1879:  /* atomic_compare_and_swaphi_1 */
    case 1878:  /* atomic_compare_and_swapqi_1 */
    case 1875:  /* atomic_storedi_fpu */
    case 1874:  /* atomic_storesi_1 */
    case 1873:  /* atomic_storehi_1 */
    case 1872:  /* atomic_storeqi_1 */
    case 1871:  /* atomic_loaddi_fpu */
    case 1870:  /* mfence_nosse */
    case 1772:  /* avx_pd256_pd */
    case 1771:  /* avx_ps256_ps */
    case 1770:  /* avx_si256_si */
    case 1725:  /* *avx_vperm_broadcast_v4df */
    case 1724:  /* *avx_vperm_broadcast_v8sf */
    case 1436:  /* *sse2_storeq */
    case 1435:  /* *vec_ext_v4si_mem */
    case 1434:  /* sse2_stored */
    case 1240:  /* vec_extract_lo_v32qi */
    case 1238:  /* vec_extract_lo_v16hi */
    case 1235:  /* vec_extract_lo_v8sf */
    case 1234:  /* vec_extract_lo_v8si */
    case 1231:  /* vec_extract_lo_v4df */
    case 1230:  /* vec_extract_lo_v4di */
    case 1229:  /* *vec_extract_v4sf_mem */
    case 1227:  /* *vec_extractv4sf_0 */
    case 987:  /* *absnegv2df2 */
    case 986:  /* *absnegv4df2 */
    case 985:  /* *absnegv4sf2 */
    case 984:  /* *absnegv8sf2 */
    case 962:  /* movdi_to_sse */
    case 937:  /* *vec_extractv2si_0 */
    case 867:  /* *vec_extractv2sf_0 */
    case 830:  /* rdseedsi_1 */
    case 829:  /* rdseedhi_1 */
    case 828:  /* rdrandsi_1 */
    case 827:  /* rdrandhi_1 */
    case 809:  /* stack_tls_protect_test_di */
    case 808:  /* stack_tls_protect_test_si */
    case 807:  /* stack_protect_test_di */
    case 806:  /* stack_protect_test_si */
    case 805:  /* stack_tls_protect_set_di */
    case 804:  /* stack_tls_protect_set_si */
    case 803:  /* stack_protect_set_di */
    case 802:  /* stack_protect_set_si */
    case 798:  /* probe_stack_rangedi */
    case 797:  /* probe_stack_rangesi */
    case 796:  /* adjust_stack_and_probedi */
    case 795:  /* adjust_stack_and_probesi */
    case 741:  /* fxamdf2_i387_with_temp */
    case 740:  /* fxamsf2_i387_with_temp */
    case 736:  /* fistsi2_ceil_with_temp */
    case 735:  /* fistsi2_floor_with_temp */
    case 734:  /* fisthi2_ceil_with_temp */
    case 733:  /* fisthi2_floor_with_temp */
    case 732:  /* fistsi2_ceil */
    case 731:  /* fistsi2_floor */
    case 730:  /* fisthi2_ceil */
    case 729:  /* fisthi2_floor */
    case 728:  /* fistdi2_ceil_with_temp */
    case 727:  /* fistdi2_floor_with_temp */
    case 726:  /* fistdi2_ceil */
    case 725:  /* fistdi2_floor */
    case 724:  /* *fistdi2_ceil_1 */
    case 723:  /* *fistdi2_floor_1 */
    case 722:  /* *fistsi2_ceil_1 */
    case 721:  /* *fistsi2_floor_1 */
    case 720:  /* *fisthi2_ceil_1 */
    case 719:  /* *fisthi2_floor_1 */
    case 718:  /* frndintxf2_mask_pm_i387 */
    case 717:  /* frndintxf2_mask_pm */
    case 716:  /* frndintxf2_trunc_i387 */
    case 715:  /* frndintxf2_ceil_i387 */
    case 714:  /* frndintxf2_floor_i387 */
    case 713:  /* frndintxf2_trunc */
    case 712:  /* frndintxf2_ceil */
    case 711:  /* frndintxf2_floor */
    case 626:  /* *tls_dynamic_gnu2_combine_32 */
    case 615:  /* *tls_local_dynamic_32_once */
    case 611:  /* paritysi2_cmp */
    case 610:  /* paritydi2_cmp */
    case 574:  /* ffssi2_no_cmove */
    case 571:  /* eh_return_internal */
    case 540:  /* *jccxf_si_r_i387 */
    case 539:  /* *jccdf_si_r_i387 */
    case 538:  /* *jccsf_si_r_i387 */
    case 537:  /* *jccxf_hi_r_i387 */
    case 536:  /* *jccdf_hi_r_i387 */
    case 535:  /* *jccsf_hi_r_i387 */
    case 534:  /* *jccxf_si_i387 */
    case 533:  /* *jccdf_si_i387 */
    case 532:  /* *jccsf_si_i387 */
    case 531:  /* *jccxf_hi_i387 */
    case 530:  /* *jccdf_hi_i387 */
    case 529:  /* *jccsf_hi_i387 */
    case 528:  /* *jccuxf_r_i387 */
    case 527:  /* *jccudf_r_i387 */
    case 526:  /* *jccusf_r_i387 */
    case 525:  /* *jccuxf_i387 */
    case 524:  /* *jccudf_i387 */
    case 523:  /* *jccusf_i387 */
    case 522:  /* *jccdf_r_i387 */
    case 521:  /* *jccsf_r_i387 */
    case 520:  /* *jccdf_i387 */
    case 519:  /* *jccsf_i387 */
    case 518:  /* *jccxf_r_i387 */
    case 517:  /* *jccxf_i387 */
    case 516:  /* *jccxf_0_r_i387 */
    case 515:  /* *jccdf_0_r_i387 */
    case 514:  /* *jccsf_0_r_i387 */
    case 513:  /* *jccxf_0_i387 */
    case 512:  /* *jccdf_0_i387 */
    case 511:  /* *jccsf_0_i387 */
    case 510:  /* *jcc_btsi_mask_1 */
    case 509:  /* *jcc_btsi_1 */
    case 508:  /* *jcc_btdi_mask */
    case 507:  /* *jcc_btsi_mask */
    case 506:  /* *jcc_btdi */
    case 505:  /* *jcc_btsi */
    case 498:  /* *setcc_si_1_movzbl */
    case 497:  /* *setcc_si_1_and */
    case 483:  /* ix86_rotrdi3_doubleword */
    case 482:  /* ix86_rotldi3_doubleword */
    case 447:  /* *ashrdi3_doubleword */
    case 446:  /* *lshrdi3_doubleword */
    case 424:  /* *ashldi3_doubleword */
    case 415:  /* copysigntf3_var */
    case 414:  /* copysigndf3_var */
    case 413:  /* copysignsf3_var */
    case 412:  /* copysigntf3_const */
    case 411:  /* copysigndf3_const */
    case 410:  /* copysignsf3_const */
    case 397:  /* *absnegtf2_sse */
    case 396:  /* *absnegxf2_i387 */
    case 395:  /* *absnegdf2_i387 */
    case 394:  /* *absnegsf2_i387 */
    case 393:  /* *absnegdf2_sse */
    case 392:  /* *absnegsf2_sse */
    case 391:  /* *absnegdf2_mixed */
    case 390:  /* *absnegsf2_mixed */
    case 381:  /* *negti2_doubleword */
    case 380:  /* *negdi2_doubleword */
    case 331:  /* *testqi_ext_3 */
    case 320:  /* *udivmodsi4 */
    case 319:  /* *udivmodhi4 */
    case 318:  /* udivmodsi4_1 */
    case 314:  /* *divmodsi4 */
    case 313:  /* *divmodhi4 */
    case 312:  /* divmodsi4_1 */
    case 264:  /* *subti3_doubleword */
    case 263:  /* *subdi3_doubleword */
    case 232:  /* *addti3_doubleword */
    case 231:  /* *adddi3_doubleword */
    case 229:  /* *floatunssixf2_1 */
    case 228:  /* *floatunssidf2_1 */
    case 227:  /* *floatunssisf2_1 */
    case 226:  /* floatdixf2_i387_with_xmm */
    case 225:  /* floatdidf2_i387_with_xmm */
    case 224:  /* floatdisf2_i387_with_xmm */
    case 183:  /* *floatdixf2_1 */
    case 182:  /* *floatdidf2_1 */
    case 181:  /* *floatdisf2_1 */
    case 180:  /* *floatsixf2_1 */
    case 179:  /* *floatsidf2_1 */
    case 178:  /* *floatsisf2_1 */
    case 171:  /* *floathixf2_1 */
    case 170:  /* *floathidf2_1 */
    case 169:  /* *floathisf2_1 */
    case 166:  /* fix_truncsi_i387_with_temp */
    case 165:  /* fix_trunchi_i387_with_temp */
    case 164:  /* fix_truncsi_i387 */
    case 163:  /* fix_trunchi_i387 */
    case 162:  /* fix_truncdi_i387_with_temp */
    case 161:  /* fix_truncdi_i387 */
    case 160:  /* *fix_truncdi_i387_1 */
    case 159:  /* *fix_truncsi_i387_1 */
    case 158:  /* *fix_trunchi_i387_1 */
    case 146:  /* *fixuns_truncdf_1 */
    case 145:  /* *fixuns_truncsf_1 */
    case 124:  /* extendsidi2_1 */
    case 108:  /* *pushdf */
    case 107:  /* *pushxf_nointeger */
    case 106:  /* *pushxf */
    case 105:  /* *pushtf */
    case 63:  /* *pushdi2 */
    case 46:  /* *cmpxf_si_cc_i387 */
    case 45:  /* *cmpdf_si_cc_i387 */
    case 44:  /* *cmpsf_si_cc_i387 */
    case 43:  /* *cmpxf_hi_cc_i387 */
    case 42:  /* *cmpdf_hi_cc_i387 */
    case 41:  /* *cmpsf_hi_cc_i387 */
    case 40:  /* *cmpxf_si_i387 */
    case 39:  /* *cmpdf_si_i387 */
    case 38:  /* *cmpsf_si_i387 */
    case 37:  /* *cmpxf_hi_i387 */
    case 36:  /* *cmpdf_hi_i387 */
    case 35:  /* *cmpsf_hi_i387 */
    case 34:  /* *cmpuxf_cc_i387 */
    case 33:  /* *cmpudf_cc_i387 */
    case 32:  /* *cmpusf_cc_i387 */
    case 31:  /* *cmpuxf_i387 */
    case 30:  /* *cmpudf_i387 */
    case 29:  /* *cmpusf_i387 */
    case 28:  /* *cmpdf_cc_i387 */
    case 27:  /* *cmpsf_cc_i387 */
    case 26:  /* *cmpdf_i387 */
    case 25:  /* *cmpsf_i387 */
    case 24:  /* *cmpxf_cc_i387 */
    case 23:  /* *cmpxf_i387 */
    case 22:  /* *cmpxf_0_cc_i387 */
    case 21:  /* *cmpdf_0_cc_i387 */
    case 20:  /* *cmpsf_0_cc_i387 */
    case 19:  /* *cmpxf_0_i387 */
    case 18:  /* *cmpdf_0_i387 */
    case 17:  /* *cmpsf_0_i387 */
    case 567:  /* pad */
      return 16 /* 0x10 */;

    case 566:  /* nops */
      extract_constrain_insn_cached (insn);
      return 
#line 11775 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(INTVAL (operands[0]));

    case 560:  /* prologue_use */
    case 559:  /* *memory_blockage */
    case 558:  /* blockage */
      return 0;

    case 824:  /* lwp_slwpcbdi */
    case 823:  /* lwp_slwpcbsi */
    case 822:  /* *lwp_llwpcbdi1 */
    case 821:  /* *lwp_llwpcbsi1 */
    case 794:  /* allocate_stack_worker_probe_di */
    case 793:  /* allocate_stack_worker_probe_si */
    case 541:  /* jump */
      return 5;

    case 832:  /* xbegin_1 */
    case 624:  /* *tls_dynamic_gnu2_lea_32 */
    case 504:  /* *jcc_2 */
    case 503:  /* *jcc_1 */
      return 6;

    case 168:  /* x86_fldcw_1 */
    case 167:  /* x86_fnstcw_1 */
    case 47:  /* x86_fnstsw_1 */
      extract_constrain_insn_cached (insn);
      return 
#line 4691 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_address_default (insn) + 2);

    case 1688:  /* pclmulqdq */
    case 1687:  /* aeskeygenassist */
    case 1686:  /* aesimc */
    case 1685:  /* aesdeclast */
    case 1684:  /* aesdec */
    case 1683:  /* aesenclast */
    case 1682:  /* aesenc */
    case 1590:  /* sse4_2_pcmpistr_cconly */
    case 1589:  /* sse4_2_pcmpistrm */
    case 1588:  /* sse4_2_pcmpistri */
    case 1585:  /* sse4_2_pcmpestr_cconly */
    case 1584:  /* sse4_2_pcmpestrm */
    case 1583:  /* sse4_2_pcmpestri */
    case 1580:  /* sse4_1_roundsd */
    case 1579:  /* sse4_1_roundss */
    case 1578:  /* sse4_1_roundpd */
    case 1577:  /* avx_roundpd256 */
    case 1576:  /* sse4_1_roundps */
    case 1575:  /* avx_roundps256 */
    case 1574:  /* sse4_1_ptest */
    case 1568:  /* sse4_1_zero_extendv2siv2di2 */
    case 1567:  /* sse4_1_sign_extendv2siv2di2 */
    case 1564:  /* sse4_1_zero_extendv2hiv2di2 */
    case 1563:  /* sse4_1_sign_extendv2hiv2di2 */
    case 1560:  /* sse4_1_zero_extendv2qiv2di2 */
    case 1559:  /* sse4_1_sign_extendv2qiv2di2 */
    case 1556:  /* sse4_1_zero_extendv4hiv4si2 */
    case 1555:  /* sse4_1_sign_extendv4hiv4si2 */
    case 1552:  /* sse4_1_zero_extendv4qiv4si2 */
    case 1551:  /* sse4_1_sign_extendv4qiv4si2 */
    case 1548:  /* sse4_1_zero_extendv8qiv8hi2 */
    case 1547:  /* sse4_1_sign_extendv8qiv8hi2 */
    case 1544:  /* sse4_1_phminposuw */
    case 1540:  /* sse4_1_pblendw */
    case 1539:  /* sse4_1_pblendvb */
    case 1538:  /* avx2_pblendvb */
    case 1537:  /* sse4_1_packusdw */
    case 1535:  /* sse4_1_mpsadbw */
    case 1534:  /* avx2_mpsadbw */
    case 1533:  /* sse4_1_movntdqa */
    case 1532:  /* avx2_movntdqa */
    case 1531:  /* sse4_1_dppd */
    case 1530:  /* avx_dppd256 */
    case 1529:  /* sse4_1_dpps */
    case 1528:  /* avx_dpps256 */
    case 1527:  /* sse4_1_blendvpd */
    case 1526:  /* avx_blendvpd256 */
    case 1525:  /* sse4_1_blendvps */
    case 1524:  /* avx_blendvps256 */
    case 1523:  /* sse4_1_blendpd */
    case 1522:  /* avx_blendpd256 */
    case 1521:  /* sse4_1_blendps */
    case 1520:  /* avx_blendps256 */
    case 1508:  /* absv4si2 */
    case 1507:  /* absv8si2 */
    case 1506:  /* absv8hi2 */
    case 1505:  /* absv16hi2 */
    case 1504:  /* absv16qi2 */
    case 1503:  /* absv32qi2 */
    case 1501:  /* ssse3_palignrti */
    case 1500:  /* avx2_palignrv2ti */
    case 1496:  /* ssse3_psignv4si3 */
    case 1495:  /* avx2_psignv8si3 */
    case 1494:  /* ssse3_psignv8hi3 */
    case 1493:  /* avx2_psignv16hi3 */
    case 1492:  /* ssse3_psignv16qi3 */
    case 1491:  /* avx2_psignv32qi3 */
    case 1489:  /* ssse3_pshufbv16qi3 */
    case 1488:  /* avx2_pshufbv32qi3 */
    case 1486:  /* *ssse3_pmulhrswv8hi3 */
    case 1485:  /* *avx2_pmulhrswv16hi3 */
    case 1483:  /* ssse3_pmaddubsw128 */
    case 1479:  /* ssse3_phsubdv4si3 */
    case 1478:  /* ssse3_phadddv4si3 */
    case 1471:  /* ssse3_phsubswv8hi3 */
    case 1470:  /* ssse3_phsubwv8hi3 */
    case 1469:  /* ssse3_phaddswv8hi3 */
    case 1468:  /* ssse3_phaddwv8hi3 */
    case 1460:  /* sse_stmxcsr */
    case 1459:  /* sse_ldmxcsr */
    case 1458:  /* *sse2_maskmovdqu */
    case 1457:  /* *sse2_maskmovdqu */
    case 1456:  /* sse2_pmovmskb */
    case 1454:  /* sse2_movmskpd */
    case 1453:  /* avx_movmskpd256 */
    case 1452:  /* sse_movmskps */
    case 1451:  /* avx_movmskps256 */
    case 1450:  /* sse2_psadbw */
    case 1449:  /* avx2_psadbw */
    case 1448:  /* *sse2_uavgv8hi3 */
    case 1447:  /* *avx2_uavgv16hi3 */
    case 1446:  /* *sse2_uavgv16qi3 */
    case 1445:  /* *avx2_uavgv32qi3 */
    case 1444:  /* vec_concatv2di */
    case 1443:  /* *vec_concatv4si */
    case 1440:  /* *vec_concatv2si_sse4_1 */
    case 1439:  /* *vec_dupv2di */
    case 1438:  /* *vec_dupv4si */
    case 1437:  /* *vec_extractv2di_1 */
    case 1433:  /* sse2_loadld */
    case 1432:  /* sse2_pshufhw_1 */
    case 1430:  /* sse2_pshuflw_1 */
    case 1428:  /* sse2_pshufd_1 */
    case 1426:  /* *sse4_1_pextrd */
    case 1425:  /* *sse4_1_pextrw_memory */
    case 1424:  /* *sse2_pextrw_si */
    case 1423:  /* *sse4_1_pextrb_memory */
    case 1422:  /* *sse4_1_pextrb_si */
    case 1421:  /* sse4_1_pinsrq */
    case 1420:  /* sse4_1_pinsrd */
    case 1419:  /* sse2_pinsrw */
    case 1418:  /* sse4_1_pinsrb */
    case 1417:  /* vec_interleave_lowv4si */
    case 1415:  /* vec_interleave_highv4si */
    case 1413:  /* vec_interleave_lowv8hi */
    case 1411:  /* vec_interleave_highv8hi */
    case 1409:  /* vec_interleave_lowv16qi */
    case 1407:  /* vec_interleave_highv16qi */
    case 1405:  /* sse2_packuswb */
    case 1404:  /* avx2_packuswb */
    case 1403:  /* sse2_packssdw */
    case 1402:  /* avx2_packssdw */
    case 1401:  /* sse2_packsswb */
    case 1400:  /* avx2_packsswb */
    case 1399:  /* *xorv2di3 */
    case 1398:  /* *iorv2di3 */
    case 1397:  /* *andv2di3 */
    case 1396:  /* *xorv4di3 */
    case 1395:  /* *iorv4di3 */
    case 1394:  /* *andv4di3 */
    case 1393:  /* *xorv4si3 */
    case 1392:  /* *iorv4si3 */
    case 1391:  /* *andv4si3 */
    case 1390:  /* *xorv8si3 */
    case 1389:  /* *iorv8si3 */
    case 1388:  /* *andv8si3 */
    case 1387:  /* *xorv8hi3 */
    case 1386:  /* *iorv8hi3 */
    case 1385:  /* *andv8hi3 */
    case 1384:  /* *xorv16hi3 */
    case 1383:  /* *iorv16hi3 */
    case 1382:  /* *andv16hi3 */
    case 1381:  /* *xorv16qi3 */
    case 1380:  /* *iorv16qi3 */
    case 1379:  /* *andv16qi3 */
    case 1378:  /* *xorv32qi3 */
    case 1377:  /* *iorv32qi3 */
    case 1376:  /* *andv32qi3 */
    case 1375:  /* *andnotv2di3 */
    case 1374:  /* *andnotv4di3 */
    case 1373:  /* *andnotv4si3 */
    case 1372:  /* *andnotv8si3 */
    case 1371:  /* *andnotv8hi3 */
    case 1370:  /* *andnotv16hi3 */
    case 1369:  /* *andnotv16qi3 */
    case 1368:  /* *andnotv32qi3 */
    case 1367:  /* sse2_gtv4si3 */
    case 1366:  /* sse2_gtv8hi3 */
    case 1365:  /* sse2_gtv16qi3 */
    case 1360:  /* sse4_2_gtv2di3 */
    case 1359:  /* *sse2_eqv4si3 */
    case 1358:  /* *sse2_eqv8hi3 */
    case 1357:  /* *sse2_eqv16qi3 */
    case 1356:  /* *sse4_1_eqv2di3 */
    case 1351:  /* *uminv16qi3 */
    case 1350:  /* *umaxv16qi3 */
    case 1349:  /* *sse4_1_uminv4si3 */
    case 1348:  /* *sse4_1_umaxv4si3 */
    case 1347:  /* *sse4_1_uminv8hi3 */
    case 1346:  /* *sse4_1_umaxv8hi3 */
    case 1345:  /* *sminv8hi3 */
    case 1344:  /* *smaxv8hi3 */
    case 1343:  /* *sse4_1_sminv4si3 */
    case 1342:  /* *sse4_1_smaxv4si3 */
    case 1341:  /* *sse4_1_sminv16qi3 */
    case 1340:  /* *sse4_1_smaxv16qi3 */
    case 1327:  /* sse2_lshrv1ti3 */
    case 1326:  /* avx2_lshrv2ti3 */
    case 1325:  /* sse2_ashlv1ti3 */
    case 1324:  /* avx2_ashlv2ti3 */
    case 1323:  /* lshrv2di3 */
    case 1322:  /* ashlv2di3 */
    case 1321:  /* lshrv4di3 */
    case 1320:  /* ashlv4di3 */
    case 1319:  /* lshrv4si3 */
    case 1318:  /* ashlv4si3 */
    case 1317:  /* lshrv8si3 */
    case 1316:  /* ashlv8si3 */
    case 1315:  /* lshrv8hi3 */
    case 1314:  /* ashlv8hi3 */
    case 1313:  /* lshrv16hi3 */
    case 1312:  /* ashlv16hi3 */
    case 1311:  /* ashrv4si3 */
    case 1310:  /* ashrv8si3 */
    case 1309:  /* ashrv8hi3 */
    case 1308:  /* ashrv16hi3 */
    case 1307:  /* *sse4_1_mulv4si3 */
    case 1306:  /* *avx2_mulv8si3 */
    case 1305:  /* *sse2_pmaddwd */
    case 1303:  /* *sse4_1_mulv2siv2di3 */
    case 1301:  /* *vec_widen_umult_even_v4si */
    case 1299:  /* *umulv8hi3_highpart */
    case 1298:  /* *smulv8hi3_highpart */
    case 1297:  /* *umulv16hi3_highpart */
    case 1296:  /* *smulv16hi3_highpart */
    case 1295:  /* *mulv8hi3 */
    case 1294:  /* *mulv16hi3 */
    case 1293:  /* *sse2_ussubv8hi3 */
    case 1292:  /* *sse2_sssubv8hi3 */
    case 1291:  /* *sse2_usaddv8hi3 */
    case 1290:  /* *sse2_ssaddv8hi3 */
    case 1289:  /* *avx2_ussubv16hi3 */
    case 1288:  /* *avx2_sssubv16hi3 */
    case 1287:  /* *avx2_usaddv16hi3 */
    case 1286:  /* *avx2_ssaddv16hi3 */
    case 1285:  /* *sse2_ussubv16qi3 */
    case 1284:  /* *sse2_sssubv16qi3 */
    case 1283:  /* *sse2_usaddv16qi3 */
    case 1282:  /* *sse2_ssaddv16qi3 */
    case 1281:  /* *avx2_ussubv32qi3 */
    case 1280:  /* *avx2_sssubv32qi3 */
    case 1279:  /* *avx2_usaddv32qi3 */
    case 1278:  /* *avx2_ssaddv32qi3 */
    case 1277:  /* *subv2di3 */
    case 1276:  /* *addv2di3 */
    case 1275:  /* *subv4di3 */
    case 1274:  /* *addv4di3 */
    case 1273:  /* *subv4si3 */
    case 1272:  /* *addv4si3 */
    case 1271:  /* *subv8si3 */
    case 1270:  /* *addv8si3 */
    case 1269:  /* *subv8hi3 */
    case 1268:  /* *addv8hi3 */
    case 1267:  /* *subv16hi3 */
    case 1266:  /* *addv16hi3 */
    case 1265:  /* *subv16qi3 */
    case 1264:  /* *addv16qi3 */
    case 1263:  /* *subv32qi3 */
    case 1262:  /* *addv32qi3 */
    case 1261:  /* *vec_concatv2df */
    case 1260:  /* vec_dupv2df */
    case 1259:  /* sse2_movsd */
    case 1258:  /* sse2_loadlpd */
    case 1257:  /* sse2_loadhpd */
    case 1255:  /* sse2_storelpd */
    case 1253:  /* sse2_storehpd */
    case 1252:  /* sse2_shufpd_v2df */
    case 1251:  /* sse2_shufpd_v2di */
    case 1250:  /* vec_interleave_lowv2di */
    case 1248:  /* vec_interleave_highv2di */
    case 1245:  /* *vec_interleave_lowv2df */
    case 1243:  /* *vec_interleave_highv2df */
    case 1228:  /* *sse4_1_extractps */
    case 1226:  /* sse4_1_insertps */
    case 1225:  /* *vec_setv4sf_sse4_1 */
    case 1224:  /* vec_setv4sf_0 */
    case 1223:  /* vec_setv4si_0 */
    case 1222:  /* *vec_concatv4sf */
    case 1220:  /* *vec_concatv2sf_sse4_1 */
    case 1219:  /* vec_dupv4sf */
    case 1215:  /* sse_movss */
    case 1214:  /* sse_loadlps */
    case 1213:  /* sse_storelps */
    case 1212:  /* sse_loadhps */
    case 1211:  /* sse_storehps */
    case 1210:  /* sse_shufps_v4sf */
    case 1209:  /* sse_shufps_v4si */
    case 1207:  /* sse3_movsldup */
    case 1205:  /* sse3_movshdup */
    case 1203:  /* vec_interleave_lowv4sf */
    case 1201:  /* vec_interleave_highv4sf */
    case 1199:  /* sse_movlhps */
    case 1198:  /* sse_movhlps */
    case 1197:  /* sse2_cvtps2pd */
    case 1194:  /* *sse2_cvtpd2ps */
    case 1192:  /* sse2_cvtss2sd */
    case 1191:  /* sse2_cvtsd2ss */
    case 1190:  /* *sse2_cvttpd2dq */
    case 1187:  /* *sse2_cvtpd2dq */
    case 1184:  /* sse2_cvtdq2pd */
    case 1181:  /* sse2_cvttsd2si */
    case 1180:  /* sse2_cvtsd2si_2 */
    case 1179:  /* sse2_cvtsd2si */
    case 1178:  /* sse2_cvtsi2sd */
    case 1174:  /* fix_truncv4sfv4si2 */
    case 1172:  /* sse2_cvtps2dq */
    case 1170:  /* floatv4siv4sf2 */
    case 1169:  /* floatv8siv8sf2 */
    case 1168:  /* sse_cvttss2si */
    case 1167:  /* sse_cvtss2si_2 */
    case 1166:  /* sse_cvtss2si */
    case 1165:  /* sse_cvtsi2ss */
    case 1113:  /* *xortf3 */
    case 1112:  /* *iortf3 */
    case 1111:  /* *andtf3 */
    case 1110:  /* *xordf3 */
    case 1109:  /* *iordf3 */
    case 1108:  /* *anddf3 */
    case 1107:  /* *xorsf3 */
    case 1106:  /* *iorsf3 */
    case 1105:  /* *andsf3 */
    case 1104:  /* *andnottf3 */
    case 1103:  /* *andnotdf3 */
    case 1102:  /* *andnotsf3 */
    case 1101:  /* *xorv2df3 */
    case 1100:  /* *iorv2df3 */
    case 1099:  /* *andv2df3 */
    case 1098:  /* *xorv4df3 */
    case 1097:  /* *iorv4df3 */
    case 1096:  /* *andv4df3 */
    case 1095:  /* *xorv4sf3 */
    case 1094:  /* *iorv4sf3 */
    case 1093:  /* *andv4sf3 */
    case 1092:  /* *xorv8sf3 */
    case 1091:  /* *iorv8sf3 */
    case 1090:  /* *andv8sf3 */
    case 1089:  /* sse2_andnotv2df3 */
    case 1088:  /* avx_andnotv4df3 */
    case 1087:  /* sse_andnotv4sf3 */
    case 1086:  /* avx_andnotv8sf3 */
    case 1085:  /* sse2_ucomi */
    case 1084:  /* sse_ucomi */
    case 1083:  /* sse2_comi */
    case 1082:  /* sse_comi */
    case 1081:  /* sse2_vmmaskcmpv2df3 */
    case 1080:  /* sse_vmmaskcmpv4sf3 */
    case 1079:  /* sse2_maskcmpv2df3 */
    case 1078:  /* avx_maskcmpv4df3 */
    case 1077:  /* sse_maskcmpv4sf3 */
    case 1076:  /* avx_maskcmpv8sf3 */
    case 1075:  /* *sse2_maskcmpv2df3_comm */
    case 1074:  /* *avx_maskcmpv4df3_comm */
    case 1073:  /* *sse_maskcmpv4sf3_comm */
    case 1072:  /* *avx_maskcmpv8sf3_comm */
    case 1065:  /* sse3_hsubv4sf3 */
    case 1064:  /* sse3_haddv4sf3 */
    case 1061:  /* *sse3_hsubv2df3_low */
    case 1060:  /* *sse3_haddv2df3_low */
    case 1059:  /* sse3_hsubv2df3 */
    case 1058:  /* *sse3_haddv2df3 */
    case 1055:  /* sse3_addsubv4sf3 */
    case 1053:  /* sse3_addsubv2df3 */
    case 1051:  /* *ieee_smaxv2df3 */
    case 1050:  /* *ieee_smaxv4df3 */
    case 1049:  /* *ieee_smaxv4sf3 */
    case 1048:  /* *ieee_smaxv8sf3 */
    case 1047:  /* *ieee_sminv2df3 */
    case 1046:  /* *ieee_sminv4df3 */
    case 1045:  /* *ieee_sminv4sf3 */
    case 1044:  /* *ieee_sminv8sf3 */
    case 1043:  /* sse2_vmsminv2df3 */
    case 1042:  /* sse2_vmsmaxv2df3 */
    case 1041:  /* sse_vmsminv4sf3 */
    case 1040:  /* sse_vmsmaxv4sf3 */
    case 1039:  /* *sminv2df3 */
    case 1038:  /* *smaxv2df3 */
    case 1037:  /* *sminv4df3 */
    case 1036:  /* *smaxv4df3 */
    case 1035:  /* *sminv4sf3 */
    case 1034:  /* *smaxv4sf3 */
    case 1033:  /* *sminv8sf3 */
    case 1032:  /* *smaxv8sf3 */
    case 1031:  /* *sminv2df3_finite */
    case 1030:  /* *smaxv2df3_finite */
    case 1029:  /* *sminv4df3_finite */
    case 1028:  /* *smaxv4df3_finite */
    case 1027:  /* *sminv4sf3_finite */
    case 1026:  /* *smaxv4sf3_finite */
    case 1025:  /* *sminv8sf3_finite */
    case 1024:  /* *smaxv8sf3_finite */
    case 1023:  /* sse_vmrsqrtv4sf2 */
    case 1022:  /* sse_rsqrtv4sf2 */
    case 1021:  /* avx_rsqrtv8sf2 */
    case 1020:  /* sse2_vmsqrtv2df2 */
    case 1019:  /* sse_vmsqrtv4sf2 */
    case 1018:  /* sse2_sqrtv2df2 */
    case 1017:  /* avx_sqrtv4df2 */
    case 1016:  /* sse_sqrtv4sf2 */
    case 1015:  /* avx_sqrtv8sf2 */
    case 1014:  /* sse_vmrcpv4sf2 */
    case 1013:  /* sse_rcpv4sf2 */
    case 1012:  /* avx_rcpv8sf2 */
    case 1011:  /* sse2_vmdivv2df3 */
    case 1010:  /* sse_vmdivv4sf3 */
    case 1009:  /* sse2_divv2df3 */
    case 1008:  /* avx_divv4df3 */
    case 1007:  /* sse_divv4sf3 */
    case 1006:  /* avx_divv8sf3 */
    case 1005:  /* sse2_vmmulv2df3 */
    case 1004:  /* sse_vmmulv4sf3 */
    case 1003:  /* *mulv2df3 */
    case 1002:  /* *mulv4df3 */
    case 1001:  /* *mulv4sf3 */
    case 1000:  /* *mulv8sf3 */
    case 999:  /* sse2_vmsubv2df3 */
    case 998:  /* sse2_vmaddv2df3 */
    case 997:  /* sse_vmsubv4sf3 */
    case 996:  /* sse_vmaddv4sf3 */
    case 995:  /* *subv2df3 */
    case 994:  /* *addv2df3 */
    case 993:  /* *subv4df3 */
    case 992:  /* *addv4df3 */
    case 991:  /* *subv4sf3 */
    case 990:  /* *addv4sf3 */
    case 989:  /* *subv8sf3 */
    case 988:  /* *addv8sf3 */
    case 983:  /* sse2_movntv2di */
    case 982:  /* avx_movntv4di */
    case 981:  /* sse2_movntv2df */
    case 980:  /* avx_movntv4df */
    case 979:  /* sse_movntv4sf */
    case 978:  /* avx_movntv8sf */
    case 976:  /* sse3_lddqu */
    case 975:  /* avx_lddqu256 */
    case 974:  /* sse2_storedqu */
    case 973:  /* avx_storedqu256 */
    case 972:  /* sse2_loaddqu */
    case 971:  /* avx_loaddqu256 */
    case 970:  /* sse2_storeupd */
    case 969:  /* avx_storeupd256 */
    case 968:  /* sse_storeups */
    case 967:  /* avx_storeups256 */
    case 966:  /* sse2_loadupd */
    case 965:  /* avx_loadupd256 */
    case 964:  /* sse_loadups */
    case 963:  /* avx_loadups256 */
    case 961:  /* sse2_movq128 */
    case 960:  /* *movv2df_internal */
    case 959:  /* *movv4df_internal */
    case 958:  /* *movv4sf_internal */
    case 957:  /* *movv8sf_internal */
    case 956:  /* *movv1ti_internal */
    case 955:  /* *movv2ti_internal */
    case 954:  /* *movv2di_internal */
    case 953:  /* *movv4di_internal */
    case 952:  /* *movv4si_internal */
    case 951:  /* *movv8si_internal */
    case 950:  /* *movv8hi_internal */
    case 949:  /* *movv16hi_internal */
    case 948:  /* *movv16qi_internal */
    case 947:  /* *movv32qi_internal */
    case 840:  /* *movv2sf_internal */
    case 839:  /* *movv1di_internal */
    case 838:  /* *movv2si_internal */
    case 837:  /* *movv4hi_internal */
    case 836:  /* *movv8qi_internal */
    case 788:  /* *ieee_smindf3 */
    case 787:  /* *ieee_smaxdf3 */
    case 786:  /* *ieee_sminsf3 */
    case 785:  /* *ieee_smaxsf3 */
    case 784:  /* smindf3 */
    case 783:  /* smaxdf3 */
    case 782:  /* sminsf3 */
    case 781:  /* smaxsf3 */
    case 777:  /* *movdfcc_1 */
    case 742:  /* movmsk_df */
    case 700:  /* sse4_1_rounddf2 */
    case 699:  /* sse4_1_roundsf2 */
    case 670:  /* *sqrtdf2_sse */
    case 669:  /* *sqrtsf2_sse */
    case 668:  /* *rsqrtsf2_sse */
    case 662:  /* *fop_xf_6_i387 */
    case 661:  /* *fop_xf_6_i387 */
    case 660:  /* *fop_xf_5_i387 */
    case 659:  /* *fop_xf_5_i387 */
    case 658:  /* *fop_xf_4_i387 */
    case 657:  /* *fop_xf_4_i387 */
    case 656:  /* *fop_xf_3_i387 */
    case 655:  /* *fop_xf_3_i387 */
    case 654:  /* *fop_xf_2_i387 */
    case 653:  /* *fop_xf_2_i387 */
    case 652:  /* *fop_xf_1_i387 */
    case 651:  /* *fop_xf_comm_i387 */
    case 650:  /* *fop_df_6_i387 */
    case 649:  /* *fop_df_5_i387 */
    case 648:  /* *fop_df_4_i387 */
    case 647:  /* *fop_df_3_i387 */
    case 646:  /* *fop_sf_3_i387 */
    case 645:  /* *fop_df_3_i387 */
    case 644:  /* *fop_sf_3_i387 */
    case 643:  /* *fop_df_2_i387 */
    case 642:  /* *fop_sf_2_i387 */
    case 641:  /* *fop_df_2_i387 */
    case 640:  /* *fop_sf_2_i387 */
    case 639:  /* *fop_df_1_i387 */
    case 638:  /* *fop_sf_1_i387 */
    case 637:  /* *fop_df_1_sse */
    case 636:  /* *fop_sf_1_sse */
    case 635:  /* *rcpsf2_sse */
    case 634:  /* *fop_df_1_mixed */
    case 633:  /* *fop_sf_1_mixed */
    case 632:  /* *fop_df_comm_i387 */
    case 631:  /* *fop_sf_comm_i387 */
    case 630:  /* *fop_df_comm_sse */
    case 629:  /* *fop_sf_comm_sse */
    case 628:  /* *fop_df_comm_mixed */
    case 627:  /* *fop_sf_comm_mixed */
    case 502:  /* setcc_df_sse */
    case 501:  /* setcc_sf_sse */
    case 306:  /* *umulsidi3_1 */
    case 211:  /* *floatdidf2_sse_nointerunit */
    case 210:  /* *floatsidf2_sse_nointerunit */
    case 209:  /* *floatdisf2_sse_nointerunit */
    case 208:  /* *floatsisf2_sse_nointerunit */
    case 207:  /* *floatdidf2_sse_interunit */
    case 206:  /* *floatsidf2_sse_interunit */
    case 205:  /* *floatdisf2_sse_interunit */
    case 204:  /* *floatsisf2_sse_interunit */
    case 197:  /* *floatdidf2_mixed_nointerunit */
    case 196:  /* *floatsidf2_mixed_nointerunit */
    case 195:  /* *floatdisf2_mixed_nointerunit */
    case 194:  /* *floatsisf2_mixed_nointerunit */
    case 193:  /* *floatdidf2_mixed_interunit */
    case 192:  /* *floatsidf2_mixed_interunit */
    case 191:  /* *floatdisf2_mixed_interunit */
    case 190:  /* *floatsisf2_mixed_interunit */
    case 189:  /* *floatsidf2_mixed_with_temp */
    case 188:  /* *floatsisf2_mixed_with_temp */
    case 185:  /* *floatsidf2_vector_mixed_with_temp */
    case 184:  /* *floatsisf2_vector_mixed_with_temp */
    case 148:  /* fix_truncdfsi_sse */
    case 147:  /* fix_truncsfsi_sse */
    case 136:  /* *truncdfsf_mixed */
    case 134:  /* *truncdfsf_fast_sse */
    case 133:  /* *truncdfsf_fast_mixed */
    case 129:  /* *extendsfdf2_sse */
    case 128:  /* *extendsfdf2_mixed */
    case 117:  /* *zero_extendsidi2 */
    case 113:  /* *movsf_internal */
    case 112:  /* *movdf_internal */
    case 111:  /* *movxf_internal */
    case 110:  /* *movtf_internal_sse */
    case 109:  /* *pushsf */
    case 78:  /* *movsi_internal */
    case 77:  /* *movdi_internal */
    case 76:  /* *movti_internal_sse */
    case 56:  /* *cmpiudf_sse */
    case 55:  /* *cmpiusf_sse */
    case 54:  /* *cmpidf_sse */
    case 53:  /* *cmpisf_sse */
    case 52:  /* *cmpiudf_mixed */
    case 51:  /* *cmpiusf_mixed */
    case 50:  /* *cmpidf_mixed */
    case 49:  /* *cmpisf_mixed */
      extract_constrain_insn_cached (insn);
      if (((cached_type = get_attr_type (insn)) == TYPE_OTHER) || ((cached_type == TYPE_MULTI) || ((cached_type == TYPE_FISTP) || (cached_type == TYPE_FRNDINT))))
        {
	  return 16 /* 0x10 */;
        }
      else if (cached_type == TYPE_FCMP)
        {
	  return 4;
        }
      else if (get_attr_unit (insn) == UNIT_I387)
        {
	  return 2 + get_attr_prefix_data16 (insn) + get_attr_length_address (insn);
        }
      else if (((cached_prefix = get_attr_prefix (insn)) == PREFIX_VEX) || ((cached_prefix == PREFIX_MAYBE_VEX) && (
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX))))
        {
	  return get_attr_length_vex (insn) + get_attr_length_immediate (insn) + get_attr_modrm (insn) + get_attr_length_address (insn);
        }
      else
        {
	  return get_attr_modrm (insn) + get_attr_prefix_0f (insn) + get_attr_prefix_rex (insn) + get_attr_prefix_extra (insn) + 1 + get_attr_prefix_rep (insn) + get_attr_prefix_data16 (insn) + get_attr_length_immediate (insn) + get_attr_length_address (insn);
        }

    default:
      return get_attr_modrm (insn) + get_attr_prefix_0f (insn) + get_attr_prefix_rex (insn) + get_attr_prefix_extra (insn) + 1 + get_attr_prefix_rep (insn) + get_attr_prefix_data16 (insn) + get_attr_length_immediate (insn) + get_attr_length_address (insn);

    }
}

int
bypass_p (rtx insn ATTRIBUTE_UNUSED)
{
  enum attr_memory cached_memory ATTRIBUTE_UNUSED;
  enum attr_type cached_type ATTRIBUTE_UNUSED;
  enum attr_use_carry cached_use_carry ATTRIBUTE_UNUSED;
  enum attr_mode cached_mode ATTRIBUTE_UNUSED;

  switch (recog_memoized (insn))
    {
    case 1258:  /* sse2_loadlpd */
      extract_constrain_insn_cached (insn);
      if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_ATOM)))) && ((which_alternative == 10) || ((which_alternative == 9) && (! (get_attr_memory (insn) == MEMORY_NONE)))))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 1257:  /* sse2_loadhpd */
      extract_constrain_insn_cached (insn);
      if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_ATOM)))) && ((which_alternative == 6) || ((which_alternative == 5) && (! (get_attr_memory (insn) == MEMORY_NONE)))))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 1255:  /* sse2_storelpd */
      extract_constrain_insn_cached (insn);
      if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_ATOM)))) && ((which_alternative == 4) || ((which_alternative == 3) && (! (get_attr_memory (insn) == MEMORY_NONE)))))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 1224:  /* vec_setv4sf_0 */
    case 1223:  /* vec_setv4si_0 */
      extract_constrain_insn_cached (insn);
      if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_ATOM)))) && ((which_alternative == 9) || ((which_alternative == 10) && (! (get_attr_memory (insn) == MEMORY_NONE)))))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 938:  /* *vec_extractv2si_1 */
      extract_constrain_insn_cached (insn);
      if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_ATOM)))) && (which_alternative == 6))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 1253:  /* sse2_storehpd */
    case 868:  /* *vec_extractv2sf_1 */
      extract_constrain_insn_cached (insn);
      if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_ATOM)))) && ((which_alternative == 5) || ((which_alternative == 4) && (! (get_attr_memory (insn) == MEMORY_NONE)))))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 778:  /* *movsfcc_1_387 */
      extract_constrain_insn_cached (insn);
      if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_ATOM)))) && (!((1 << which_alternative) & 0x3)))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 606:  /* *bswapsi2_movbe */
      extract_constrain_insn_cached (insn);
      if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_ATOM)))) && (which_alternative != 0))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 500:  /* *setcc_qi_slp */
    case 499:  /* *setcc_qi */
      if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_ATOM)))) && (! (get_attr_memory (insn) == MEMORY_STORE)))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 488:  /* *rotrdi3_1 */
    case 487:  /* *rotldi3_1 */
    case 486:  /* *rotrsi3_1 */
    case 485:  /* *rotlsi3_1 */
    case 455:  /* *ashrdi3_1 */
    case 454:  /* *lshrdi3_1 */
    case 453:  /* *ashrsi3_1 */
    case 452:  /* *lshrsi3_1 */
      extract_constrain_insn_cached (insn);
      if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_ATOM)))) && ((which_alternative == 0) && (get_attr_memory (insn) == MEMORY_NONE)))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 306:  /* *umulsidi3_1 */
      extract_constrain_insn_cached (insn);
      if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_ATOM)))) && (which_alternative == 1))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 217:  /* *floatdixf2_i387_with_temp */
    case 216:  /* *floatdidf2_i387_with_temp */
    case 215:  /* *floatdisf2_i387_with_temp */
    case 214:  /* *floatsixf2_i387_with_temp */
    case 213:  /* *floatsidf2_i387_with_temp */
    case 212:  /* *floatsisf2_i387_with_temp */
    case 197:  /* *floatdidf2_mixed_nointerunit */
    case 196:  /* *floatsidf2_mixed_nointerunit */
    case 195:  /* *floatdisf2_mixed_nointerunit */
    case 194:  /* *floatsisf2_mixed_nointerunit */
    case 193:  /* *floatdidf2_mixed_interunit */
    case 192:  /* *floatsidf2_mixed_interunit */
    case 191:  /* *floatdisf2_mixed_interunit */
    case 190:  /* *floatsisf2_mixed_interunit */
    case 189:  /* *floatsidf2_mixed_with_temp */
    case 188:  /* *floatsisf2_mixed_with_temp */
    case 187:  /* *floatsidf2_vector_mixed */
    case 186:  /* *floatsisf2_vector_mixed */
    case 185:  /* *floatsidf2_vector_mixed_with_temp */
    case 184:  /* *floatsisf2_vector_mixed_with_temp */
    case 174:  /* *floathixf2_i387_with_temp */
    case 173:  /* *floathidf2_i387_with_temp */
    case 172:  /* *floathisf2_i387_with_temp */
    case 140:  /* *truncxfdf2_mixed */
    case 139:  /* *truncxfsf2_mixed */
    case 137:  /* *truncdfsf_i387 */
    case 136:  /* *truncdfsf_mixed */
    case 133:  /* *truncdfsf_fast_mixed */
      extract_constrain_insn_cached (insn);
      if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_ATOM)))) && ((which_alternative == 0) && (! (get_attr_memory (insn) == MEMORY_NONE))))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 1877:  /* storedi_via_fpu */
    case 1876:  /* loaddi_via_fpu */
    case 664:  /* truncxfdf2_i387_noop_unspec */
    case 663:  /* truncxfsf2_i387_noop_unspec */
    case 223:  /* *floatdixf2_i387 */
    case 222:  /* *floatdidf2_i387 */
    case 221:  /* *floatdisf2_i387 */
    case 220:  /* *floatsixf2_i387 */
    case 219:  /* *floatsidf2_i387 */
    case 218:  /* *floatsisf2_i387 */
    case 177:  /* *floathixf2_i387 */
    case 176:  /* *floathidf2_i387 */
    case 175:  /* *floathisf2_i387 */
    case 144:  /* *truncxfdf2_i387 */
    case 143:  /* *truncxfsf2_i387 */
    case 142:  /* truncxfdf2_i387_noop */
    case 141:  /* truncxfsf2_i387_noop */
    case 138:  /* *truncdfsf2_i387_1 */
    case 135:  /* *truncdfsf_fast_i387 */
    case 132:  /* *extenddfxf2_i387 */
    case 131:  /* *extendsfxf2_i387 */
    case 130:  /* *extendsfdf2_i387 */
      if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_ATOM)))) && (! (get_attr_memory (insn) == MEMORY_NONE)))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 128:  /* *extendsfdf2_mixed */
      extract_constrain_insn_cached (insn);
      if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_ATOM)))) && ((((1 << which_alternative) & 0x3)) && (! (get_attr_memory (insn) == MEMORY_NONE))))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 113:  /* *movsf_internal */
      extract_constrain_insn_cached (insn);
      if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_ATOM)))) && ((((1 << which_alternative) & 0x18)) || ((((1 << which_alternative) & 0x7)) && (! (get_attr_memory (insn) == MEMORY_NONE)))))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 112:  /* *movdf_internal */
    case 111:  /* *movxf_internal */
      extract_constrain_insn_cached (insn);
      if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_ATOM)))) && ((((1 << which_alternative) & 0x7)) && (! (get_attr_memory (insn) == MEMORY_NONE))))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 109:  /* *pushsf */
      extract_constrain_insn_cached (insn);
      if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_PENTIUM)))) && ((which_alternative == 1) && (get_attr_memory (insn) == MEMORY_STORE)))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 78:  /* *movsi_internal */
      if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_ATOM)))) && (((cached_type = get_attr_type (insn)) == TYPE_IMOV) || (cached_type == TYPE_LEA)))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 792:  /* pro_epilogue_adjust_stack_di_sub */
    case 791:  /* pro_epilogue_adjust_stack_si_sub */
    case 775:  /* *movqicc_noc */
    case 774:  /* *movsicc_noc */
    case 773:  /* *movhicc_noc */
    case 772:  /* *x86_movsicc_0_m1_neg */
    case 771:  /* *x86_movsicc_0_m1_se */
    case 770:  /* *x86_movsicc_0_m1 */
    case 624:  /* *tls_dynamic_gnu2_lea_32 */
    case 623:  /* *add_tp_di */
    case 622:  /* *add_tp_si */
    case 621:  /* *add_tp_x32_zext */
    case 620:  /* *add_tp_x32 */
    case 619:  /* *load_tp_di */
    case 618:  /* *load_tp_si */
    case 617:  /* *load_tp_x32_zext */
    case 616:  /* *load_tp_x32 */
    case 600:  /* *bsrhi */
    case 599:  /* bsr */
    case 578:  /* ctzsi2 */
    case 577:  /* ctzhi2 */
    case 576:  /* *bsfsi_1 */
    case 575:  /* *tzcntsi_1 */
    case 570:  /* set_got_offset_rex64 */
    case 496:  /* *btdi */
    case 495:  /* *btsi */
    case 423:  /* *one_cmpldi2_2 */
    case 422:  /* *one_cmplsi2_2 */
    case 421:  /* *one_cmplhi2_2 */
    case 420:  /* *one_cmplqi2_2 */
    case 379:  /* *xorqi_cc_ext_1 */
    case 378:  /* *xorqi_ext_2 */
    case 377:  /* *iorqi_ext_2 */
    case 376:  /* *xorqi_ext_1 */
    case 375:  /* *iorqi_ext_1 */
    case 374:  /* *xorqi_ext_0 */
    case 373:  /* *iorqi_ext_0 */
    case 372:  /* *xordi_3 */
    case 371:  /* *iordi_3 */
    case 370:  /* *xorsi_3 */
    case 369:  /* *iorsi_3 */
    case 368:  /* *xorhi_3 */
    case 367:  /* *iorhi_3 */
    case 366:  /* *xorqi_3 */
    case 365:  /* *iorqi_3 */
    case 364:  /* *xorqi_2_slp */
    case 363:  /* *iorqi_2_slp */
    case 362:  /* *xordi_2 */
    case 361:  /* *iordi_2 */
    case 360:  /* *xorsi_2 */
    case 359:  /* *iorsi_2 */
    case 358:  /* *xorhi_2 */
    case 357:  /* *iorhi_2 */
    case 356:  /* *xorqi_2 */
    case 355:  /* *iorqi_2 */
    case 354:  /* *xorqi_1_slp */
    case 353:  /* *iorqi_1_slp */
    case 352:  /* *xorqi_1 */
    case 351:  /* *iorqi_1 */
    case 350:  /* *xordi_1 */
    case 349:  /* *iordi_1 */
    case 348:  /* *xorsi_1 */
    case 347:  /* *iorsi_1 */
    case 346:  /* *xorhi_1 */
    case 345:  /* *iorhi_1 */
    case 344:  /* *andqi_ext_2 */
    case 343:  /* *andqi_ext_1 */
    case 342:  /* *andqi_ext_0_cc */
    case 341:  /* andqi_ext_0 */
    case 340:  /* *andqi_2_slp */
    case 339:  /* *andsi_2 */
    case 338:  /* *andhi_2 */
    case 337:  /* *andqi_2 */
    case 336:  /* *andqi_2_maybe_si */
    case 335:  /* *andqi_1_slp */
    case 334:  /* *andqi_1 */
    case 311:  /* *umulsi3_highpart_1 */
    case 310:  /* *smulsi3_highpart_1 */
    case 307:  /* *mulsidi3_1 */
    case 302:  /* *mulsi3_1 */
    case 301:  /* *subdi3_cc_overflow */
    case 300:  /* *adddi3_cc_overflow */
    case 299:  /* *subsi3_cc_overflow */
    case 298:  /* *addsi3_cc_overflow */
    case 297:  /* *subhi3_cc_overflow */
    case 296:  /* *addhi3_cc_overflow */
    case 295:  /* *subqi3_cc_overflow */
    case 294:  /* *addqi3_cc_overflow */
    case 290:  /* *addsi3_cconly_overflow */
    case 289:  /* *addhi3_cconly_overflow */
    case 288:  /* *addqi3_cconly_overflow */
    case 287:  /* adcxdi3 */
    case 286:  /* adcxsi3 */
    case 285:  /* *subdi3_carry */
    case 284:  /* *adddi3_carry */
    case 283:  /* *subsi3_carry */
    case 282:  /* *addsi3_carry */
    case 281:  /* *subhi3_carry */
    case 280:  /* *addhi3_carry */
    case 279:  /* *subqi3_carry */
    case 278:  /* *addqi3_carry */
    case 277:  /* *subdi_3 */
    case 276:  /* *subsi_3 */
    case 275:  /* *subhi_3 */
    case 274:  /* *subqi_3 */
    case 273:  /* *subdi_2 */
    case 272:  /* *subsi_2 */
    case 271:  /* *subhi_2 */
    case 270:  /* *subqi_2 */
    case 269:  /* *subqi_1_slp */
    case 268:  /* *subdi_1 */
    case 267:  /* *subsi_1 */
    case 266:  /* *subhi_1 */
    case 265:  /* *subqi_1 */
    case 262:  /* *lea_general_4 */
    case 261:  /* *lea_general_4 */
    case 260:  /* *lea_general_3 */
    case 259:  /* *lea_general_2 */
    case 258:  /* *lea_general_1 */
    case 257:  /* *addqi_ext_2 */
    case 235:  /* addqi3_cc */
    case 234:  /* *adddi3_cc */
    case 233:  /* *addsi3_cc */
    case 230:  /* *leasi */
    case 122:  /* zero_extendqihi2_and */
    case 119:  /* zero_extendhisi2_and */
    case 118:  /* zero_extendqisi2_and */
    case 104:  /* *movqi_insv_2 */
    case 103:  /* *movsi_insv_1 */
    case 97:  /* *movstricthi_xor */
    case 96:  /* *movstrictqi_xor */
    case 95:  /* *movstricthi_1 */
    case 94:  /* *movstrictqi_1 */
    case 93:  /* *swaphi_2 */
    case 92:  /* *swapqi_2 */
    case 91:  /* *swaphi_1 */
    case 90:  /* *swapqi_1 */
    case 89:  /* swapsi */
    case 88:  /* *movabsdi_2 */
    case 87:  /* *movabssi_2 */
    case 86:  /* *movabshi_2 */
    case 85:  /* *movabsqi_2 */
    case 84:  /* *movabsdi_1 */
    case 83:  /* *movabssi_1 */
    case 82:  /* *movabshi_1 */
    case 81:  /* *movabsqi_1 */
    case 74:  /* *movsi_or */
    case 73:  /* *movsi_xor */
      if (((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_ATOM))))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 72:  /* *popdi1_epilogue */
    case 70:  /* *popdi1 */
      if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_PENTIUM)))) || (((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_ATOM)))))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 572:  /* leave */
    case 71:  /* *popsi1_epilogue */
    case 69:  /* *popsi1 */
      if (((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_PENTIUM))))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 68:  /* *pushdi2_prologue */
    case 67:  /* *pushsi2_prologue */
    case 66:  /* *pushhi2 */
    case 65:  /* *pushqi2 */
    case 64:  /* *pushsi2 */
      if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_PENTIUM)))) && (get_attr_memory (insn) == MEMORY_STORE))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 494:  /* *rotrqi3_1_slp */
    case 493:  /* *rotlqi3_1_slp */
    case 492:  /* *rotrhi3_1 */
    case 491:  /* *rotlhi3_1 */
    case 490:  /* *rotrqi3_1 */
    case 489:  /* *rotlqi3_1 */
    case 481:  /* *rotrdi3_mask */
    case 480:  /* *rotldi3_mask */
    case 479:  /* *rotrsi3_mask */
    case 478:  /* *rotlsi3_mask */
    case 477:  /* *ashrdi3_cconly */
    case 476:  /* *lshrdi3_cconly */
    case 475:  /* *ashrsi3_cconly */
    case 474:  /* *lshrsi3_cconly */
    case 473:  /* *ashrhi3_cconly */
    case 472:  /* *lshrhi3_cconly */
    case 471:  /* *ashrqi3_cconly */
    case 470:  /* *lshrqi3_cconly */
    case 469:  /* *ashrdi3_cmp */
    case 468:  /* *lshrdi3_cmp */
    case 467:  /* *ashrsi3_cmp */
    case 466:  /* *lshrsi3_cmp */
    case 465:  /* *ashrhi3_cmp */
    case 464:  /* *lshrhi3_cmp */
    case 463:  /* *ashrqi3_cmp */
    case 462:  /* *lshrqi3_cmp */
    case 461:  /* *ashrqi3_1_slp */
    case 460:  /* *lshrqi3_1_slp */
    case 459:  /* *ashrhi3_1 */
    case 458:  /* *lshrhi3_1 */
    case 457:  /* *ashrqi3_1 */
    case 456:  /* *lshrqi3_1 */
    case 445:  /* *ashrdi3_mask */
    case 444:  /* *lshrdi3_mask */
    case 443:  /* *ashrsi3_mask */
    case 442:  /* *lshrsi3_mask */
    case 427:  /* *ashldi3_mask */
    case 426:  /* *ashlsi3_mask */
    case 419:  /* *one_cmplqi2_1 */
    case 418:  /* *one_cmpldi2_1 */
    case 417:  /* *one_cmplsi2_1 */
    case 416:  /* *one_cmplhi2_1 */
    case 389:  /* *negdi2_cmpz */
    case 388:  /* *negsi2_cmpz */
    case 387:  /* *neghi2_cmpz */
    case 386:  /* *negqi2_cmpz */
    case 385:  /* *negdi2_1 */
    case 384:  /* *negsi2_1 */
    case 383:  /* *neghi2_1 */
    case 382:  /* *negqi2_1 */
    case 330:  /* *testqi_ext_2 */
    case 329:  /* *testqi_ext_1 */
    case 328:  /* *testqi_ext_0 */
    case 327:  /* *testsi_1 */
    case 326:  /* *testhi_1 */
    case 325:  /* *testqi_1 */
    case 324:  /* *testqi_1_maybe_si */
    case 293:  /* *subsi3_cconly_overflow */
    case 292:  /* *subhi3_cconly_overflow */
    case 291:  /* *subqi3_cconly_overflow */
    case 16:  /* *cmpqi_ext_4 */
    case 15:  /* *cmpqi_ext_3_insn */
    case 14:  /* *cmpqi_ext_2 */
    case 13:  /* *cmpqi_ext_1 */
    case 12:  /* *cmpdi_minus_1 */
    case 11:  /* *cmpsi_minus_1 */
    case 10:  /* *cmphi_minus_1 */
    case 9:  /* *cmpqi_minus_1 */
    case 8:  /* *cmpdi_1 */
    case 7:  /* *cmpsi_1 */
    case 6:  /* *cmphi_1 */
    case 5:  /* *cmpqi_1 */
      if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_ATOM)))) && (get_attr_memory (insn) == MEMORY_NONE))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 4:  /* *cmpdi_ccno_1 */
    case 3:  /* *cmpsi_ccno_1 */
    case 2:  /* *cmphi_ccno_1 */
    case 1:  /* *cmpqi_ccno_1 */
      extract_constrain_insn_cached (insn);
      if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_ATOM)))) && ((((1 << which_alternative) & 0x3)) && (get_attr_memory (insn) == MEMORY_NONE)))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case -1:
      if (GET_CODE (PATTERN (insn)) != ASM_INPUT
          && asm_noperands (PATTERN (insn)) < 0)
        fatal_insn_not_found (insn);
    case 79:  /* *movhi_internal */
    case 80:  /* *movqi_internal */
    case 98:  /* *movhi_extv_1 */
    case 99:  /* *movsi_extv_1 */
    case 100:  /* *movqi_extv_1 */
    case 101:  /* *movsi_extzv_1 */
    case 102:  /* *movqi_extzv_2 */
    case 120:  /* *zero_extendqisi2 */
    case 121:  /* *zero_extendhisi2 */
    case 123:  /* *zero_extendqihi2 */
    case 125:  /* extendhisi2 */
    case 126:  /* extendqisi2 */
    case 127:  /* extendqihi2 */
    case 236:  /* *addsi_1 */
    case 237:  /* *adddi_1 */
    case 238:  /* *addhi_1 */
    case 239:  /* *addqi_1 */
    case 240:  /* *addqi_1_slp */
    case 241:  /* *addqi_2 */
    case 242:  /* *addhi_2 */
    case 243:  /* *addsi_2 */
    case 244:  /* *adddi_2 */
    case 245:  /* *addqi_3 */
    case 246:  /* *addhi_3 */
    case 247:  /* *addsi_3 */
    case 248:  /* *adddi_3 */
    case 249:  /* *addqi_4 */
    case 250:  /* *addhi_4 */
    case 251:  /* *addsi_4 */
    case 252:  /* *addqi_5 */
    case 253:  /* *addhi_5 */
    case 254:  /* *addsi_5 */
    case 255:  /* *adddi_5 */
    case 256:  /* addqi_ext_1 */
    case 332:  /* *andsi_1 */
    case 333:  /* *andhi_1 */
    case 429:  /* *ashlsi3_1 */
    case 430:  /* *ashldi3_1 */
    case 431:  /* *ashlhi3_1 */
    case 432:  /* *ashlqi3_1 */
    case 433:  /* *ashlqi3_1_slp */
    case 434:  /* *ashlqi3_cmp */
    case 435:  /* *ashlhi3_cmp */
    case 436:  /* *ashlsi3_cmp */
    case 437:  /* *ashldi3_cmp */
    case 438:  /* *ashlqi3_cconly */
    case 439:  /* *ashlhi3_cconly */
    case 440:  /* *ashlsi3_cconly */
    case 441:  /* *ashldi3_cconly */
    case 449:  /* ashrsi3_cvt */
    case 789:  /* pro_epilogue_adjust_stack_si_add */
    case 790:  /* pro_epilogue_adjust_stack_di_add */
      extract_insn_cached (insn);
      if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_PENTIUM)))) && (((cached_type = get_attr_type (insn)) == TYPE_PUSH) && ((cached_memory = get_attr_memory (insn)) == MEMORY_STORE)))
        {
	  return 1;
        }
      else if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_PENTIUM)))) && (((cached_type = get_attr_type (insn)) == TYPE_POP) || (cached_type == TYPE_LEAVE)))
        {
	  return 1;
        }
      else if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_ATOM)))) && (((cached_type = get_attr_type (insn)) == TYPE_ALU) && (((cached_memory = get_attr_memory (insn)) == MEMORY_NONE) && ((cached_use_carry = get_attr_use_carry (insn)) == USE_CARRY_0))))
        {
	  return 1;
        }
      else if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_ATOM)))) && (((cached_type = get_attr_type (insn)) == TYPE_ALU) && ((! ((cached_memory = get_attr_memory (insn)) == MEMORY_NONE)) && ((cached_use_carry = get_attr_use_carry (insn)) == USE_CARRY_0))))
        {
	  return 1;
        }
      else if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_ATOM)))) && (((cached_type = get_attr_type (insn)) == TYPE_ALU) && (((cached_memory = get_attr_memory (insn)) == MEMORY_NONE) && ((cached_use_carry = get_attr_use_carry (insn)) == USE_CARRY_1))))
        {
	  return 1;
        }
      else if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_ATOM)))) && (((cached_type = get_attr_type (insn)) == TYPE_ALU) && ((! ((cached_memory = get_attr_memory (insn)) == MEMORY_NONE)) && ((cached_use_carry = get_attr_use_carry (insn)) == USE_CARRY_1))))
        {
	  return 1;
        }
      else if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_ATOM)))) && (((cached_type = get_attr_type (insn)) == TYPE_ALU1) && ((cached_memory = get_attr_memory (insn)) == MEMORY_NONE)))
        {
	  return 1;
        }
      else if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_ATOM)))) && (((cached_type = get_attr_type (insn)) == TYPE_ALU1) && (! ((cached_memory = get_attr_memory (insn)) == MEMORY_NONE))))
        {
	  return 1;
        }
      else if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_ATOM)))) && (((cached_type = get_attr_type (insn)) == TYPE_NEGNOT) && ((cached_memory = get_attr_memory (insn)) == MEMORY_NONE)))
        {
	  return 1;
        }
      else if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_ATOM)))) && (((cached_type = get_attr_type (insn)) == TYPE_IMOV) && ((cached_memory = get_attr_memory (insn)) == MEMORY_NONE)))
        {
	  return 1;
        }
      else if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_ATOM)))) && (((cached_type = get_attr_type (insn)) == TYPE_IMOV) && (! ((cached_memory = get_attr_memory (insn)) == MEMORY_NONE))))
        {
	  return 1;
        }
      else if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_ATOM)))) && (((cached_type = get_attr_type (insn)) == TYPE_IMOVX) && (((cached_memory = get_attr_memory (insn)) == MEMORY_NONE) && (((register_operand (operands[0], HImode)) && (general_operand (operands[1], HImode))) || ((register_operand (operands[0], SImode)) && (general_operand (operands[1], SImode)))))))
        {
	  return 1;
        }
      else if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_ATOM)))) && (((cached_type = get_attr_type (insn)) == TYPE_IMOVX) && ((! ((cached_memory = get_attr_memory (insn)) == MEMORY_NONE)) && (((register_operand (operands[0], HImode)) && (general_operand (operands[1], HImode))) || ((register_operand (operands[0], SImode)) && (general_operand (operands[1], SImode)))))))
        {
	  return 1;
        }
      else if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_ATOM)))) && (((cached_type = get_attr_type (insn)) == TYPE_IMOVX) && ((! ((cached_memory = get_attr_memory (insn)) == MEMORY_NONE)) && ((register_operand (operands[0], QImode)) || (((register_operand (operands[0], SImode)) && (! (general_operand (operands[1], SImode)))) || (register_operand (operands[0], DImode)))))))
        {
	  return 1;
        }
      else if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_ATOM)))) && (((cached_type = get_attr_type (insn)) == TYPE_LEA) && (! ((cached_mode = get_attr_mode (insn)) == MODE_HI))))
        {
	  return 1;
        }
      else if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_ATOM)))) && (((cached_type = get_attr_type (insn)) == TYPE_INCDEC) && ((cached_memory = get_attr_memory (insn)) == MEMORY_NONE)))
        {
	  return 1;
        }
      else if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_ATOM)))) && (((cached_type = get_attr_type (insn)) == TYPE_ISHIFT) && (((cached_memory = get_attr_memory (insn)) == MEMORY_NONE) && (get_attr_prefix_0f (insn) == 0))))
        {
	  return 1;
        }
      else if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_ATOM)))) && (((cached_type = get_attr_type (insn)) == TYPE_ISHIFT1) && ((cached_memory = get_attr_memory (insn)) == MEMORY_NONE)))
        {
	  return 1;
        }
      else if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_ATOM)))) && (((cached_type = get_attr_type (insn)) == TYPE_ROTATE) && ((cached_memory = get_attr_memory (insn)) == MEMORY_NONE)))
        {
	  return 1;
        }
      else if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_ATOM)))) && (((cached_type = get_attr_type (insn)) == TYPE_ROTATE1) && ((cached_memory = get_attr_memory (insn)) == MEMORY_NONE)))
        {
	  return 1;
        }
      else if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_ATOM)))) && (((cached_type = get_attr_type (insn)) == TYPE_IMUL) && (((cached_memory = get_attr_memory (insn)) == MEMORY_NONE) && ((cached_mode = get_attr_mode (insn)) == MODE_SI))))
        {
	  return 1;
        }
      else if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_ATOM)))) && (((cached_type = get_attr_type (insn)) == TYPE_IMUL) && ((! ((cached_memory = get_attr_memory (insn)) == MEMORY_NONE)) && ((cached_mode = get_attr_mode (insn)) == MODE_SI))))
        {
	  return 1;
        }
      else if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_ATOM)))) && (((cached_type = get_attr_type (insn)) == TYPE_ICMP) && ((cached_memory = get_attr_memory (insn)) == MEMORY_NONE)))
        {
	  return 1;
        }
      else if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_ATOM)))) && (((cached_type = get_attr_type (insn)) == TYPE_TEST) && ((cached_memory = get_attr_memory (insn)) == MEMORY_NONE)))
        {
	  return 1;
        }
      else if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_ATOM)))) && (((cached_type = get_attr_type (insn)) == TYPE_SETCC) && (! ((cached_memory = get_attr_memory (insn)) == MEMORY_STORE))))
        {
	  return 1;
        }
      else if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_ATOM)))) && (((cached_type = get_attr_type (insn)) == TYPE_ICMOV) && ((cached_memory = get_attr_memory (insn)) == MEMORY_NONE)))
        {
	  return 1;
        }
      else if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_ATOM)))) && (((cached_type = get_attr_type (insn)) == TYPE_ICMOV) && (! ((cached_memory = get_attr_memory (insn)) == MEMORY_NONE))))
        {
	  return 1;
        }
      else if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_ATOM)))) && (((cached_type = get_attr_type (insn)) == TYPE_POP) && ((cached_mode = get_attr_mode (insn)) == MODE_DI)))
        {
	  return 1;
        }
      else if ((((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_ATOM)))) && (((cached_type = get_attr_type (insn)) == TYPE_FMOV) && (! ((cached_memory = get_attr_memory (insn)) == MEMORY_NONE))))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    default:
      return 0;

    }
}

enum attr_atom_sse_attr
get_attr_atom_sse_attr (rtx insn ATTRIBUTE_UNUSED)
{
  switch (recog_memoized (insn))
    {
    case 1459:  /* sse_ldmxcsr */
    case 1460:  /* sse_stmxcsr */
      return ATOM_SSE_ATTR_MXCSR;

    case 669:  /* *sqrtsf2_sse */
    case 670:  /* *sqrtdf2_sse */
    case 1015:  /* avx_sqrtv8sf2 */
    case 1016:  /* sse_sqrtv4sf2 */
    case 1017:  /* avx_sqrtv4df2 */
    case 1018:  /* sse2_sqrtv2df2 */
    case 1019:  /* sse_vmsqrtv4sf2 */
    case 1020:  /* sse2_vmsqrtv2df2 */
      return ATOM_SSE_ATTR_SQRT;

    case 800:  /* *prefetch_sse */
      return ATOM_SSE_ATTR_PREFETCH;

    case 1461:  /* sse2_clflush */
    case 1868:  /* *sse_sfence */
    case 1869:  /* mfence_sse2 */
      return ATOM_SSE_ATTR_FENCE;

    case 1867:  /* *sse2_lfence */
      return ATOM_SSE_ATTR_LFENCE;

    case 635:  /* *rcpsf2_sse */
    case 668:  /* *rsqrtsf2_sse */
    case 1012:  /* avx_rcpv8sf2 */
    case 1013:  /* sse_rcpv4sf2 */
    case 1014:  /* sse_vmrcpv4sf2 */
      return ATOM_SSE_ATTR_RCP;

    case -1:
      if (GET_CODE (PATTERN (insn)) != ASM_INPUT
          && asm_noperands (PATTERN (insn)) < 0)
        fatal_insn_not_found (insn);
    default:
      return ATOM_SSE_ATTR_OTHER;

    }
}

enum attr_atom_unit
get_attr_atom_unit (rtx insn ATTRIBUTE_UNUSED)
{
  switch (recog_memoized (insn))
    {
    case 1053:  /* sse3_addsubv2df3 */
    case 1064:  /* sse3_haddv4sf3 */
    case 1065:  /* sse3_hsubv4sf3 */
    case 1468:  /* ssse3_phaddwv8hi3 */
    case 1469:  /* ssse3_phaddswv8hi3 */
    case 1470:  /* ssse3_phsubwv8hi3 */
    case 1471:  /* ssse3_phsubswv8hi3 */
    case 1472:  /* ssse3_phaddwv4hi3 */
    case 1473:  /* ssse3_phaddswv4hi3 */
    case 1474:  /* ssse3_phsubwv4hi3 */
    case 1475:  /* ssse3_phsubswv4hi3 */
    case 1478:  /* ssse3_phadddv4si3 */
    case 1479:  /* ssse3_phsubdv4si3 */
    case 1480:  /* ssse3_phadddv2si3 */
    case 1481:  /* ssse3_phsubdv2si3 */
      return ATOM_UNIT_COMPLEX;

    case 561:  /* simple_return_internal */
    case 562:  /* simple_return_internal_long */
    case 563:  /* simple_return_pop_internal */
    case 573:  /* split_stack_return */
      return ATOM_UNIT_JEU;

    case 1305:  /* *sse2_pmaddwd */
    case 1449:  /* avx2_psadbw */
    case 1450:  /* sse2_psadbw */
    case 1483:  /* ssse3_pmaddubsw128 */
    case 1484:  /* ssse3_pmaddubsw */
      return ATOM_UNIT_SIMUL;

    case 1326:  /* avx2_lshrv2ti3 */
    case 1327:  /* sse2_lshrv1ti3 */
    case 1500:  /* avx2_palignrv2ti */
    case 1501:  /* ssse3_palignrti */
    case 1502:  /* ssse3_palignrdi */
      return ATOM_UNIT_SISHUF;

    case -1:
      if (GET_CODE (PATTERN (insn)) != ASM_INPUT
          && asm_noperands (PATTERN (insn)) < 0)
        fatal_insn_not_found (insn);
    default:
      return ATOM_UNIT_OTHER;

    }
}

enum attr_amdfam10_decode
get_attr_amdfam10_decode (rtx insn ATTRIBUTE_UNUSED)
{
  switch (recog_memoized (insn))
    {
    case 189:  /* *floatsidf2_mixed_with_temp */
    case 188:  /* *floatsisf2_mixed_with_temp */
    case 185:  /* *floatsidf2_vector_mixed_with_temp */
    case 184:  /* *floatsisf2_vector_mixed_with_temp */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return AMDFAM10_DECODE_DIRECT;
        }
      else if (which_alternative == 2)
        {
	  return AMDFAM10_DECODE_VECTOR;
        }
      else
        {
	  return AMDFAM10_DECODE_DOUBLE;
        }

    case 190:  /* *floatsisf2_mixed_interunit */
    case 191:  /* *floatdisf2_mixed_interunit */
    case 192:  /* *floatsidf2_mixed_interunit */
    case 193:  /* *floatdidf2_mixed_interunit */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return AMDFAM10_DECODE_DIRECT;
        }
      else if (which_alternative == 1)
        {
	  return AMDFAM10_DECODE_VECTOR;
        }
      else
        {
	  return AMDFAM10_DECODE_DOUBLE;
        }

    case 199:  /* *floatsidf2_vector_sse_with_temp */
    case 198:  /* *floatsisf2_vector_sse_with_temp */
    case 202:  /* *floatsisf2_sse_with_temp */
    case 203:  /* *floatsidf2_sse_with_temp */
    case 204:  /* *floatsisf2_sse_interunit */
    case 205:  /* *floatdisf2_sse_interunit */
    case 206:  /* *floatsidf2_sse_interunit */
    case 207:  /* *floatdidf2_sse_interunit */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return AMDFAM10_DECODE_VECTOR;
        }
      else
        {
	  return AMDFAM10_DECODE_DOUBLE;
        }

    case 302:  /* *mulsi3_1 */
      extract_constrain_insn_cached (insn);
      if ((((1 << which_alternative) & 0x3)) && (memory_operand (operands[1], VOIDmode)))
        {
	  return AMDFAM10_DECODE_VECTOR;
        }
      else
        {
	  return AMDFAM10_DECODE_DIRECT;
        }

    case 303:  /* *mulhi3_1 */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return AMDFAM10_DECODE_VECTOR;
        }
      else
        {
	  return AMDFAM10_DECODE_DIRECT;
        }

    case 186:  /* *floatsisf2_vector_mixed */
    case 187:  /* *floatsidf2_vector_mixed */
    case 194:  /* *floatsisf2_mixed_nointerunit */
    case 195:  /* *floatdisf2_mixed_nointerunit */
    case 196:  /* *floatsidf2_mixed_nointerunit */
    case 197:  /* *floatdidf2_mixed_nointerunit */
    case 306:  /* *umulsidi3_1 */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return AMDFAM10_DECODE_DIRECT;
        }
      else
        {
	  return AMDFAM10_DECODE_DOUBLE;
        }

    case 1165:  /* sse_cvtsi2ss */
    case 1178:  /* sse2_cvtsi2sd */
    case 1191:  /* sse2_cvtsd2ss */
    case 1192:  /* sse2_cvtss2sd */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return AMDFAM10_DECODE_VECTOR;
        }
      else if (which_alternative == 1)
        {
	  return AMDFAM10_DECODE_DOUBLE;
        }
      else
        {
	  return AMDFAM10_DECODE_DIRECT;
        }

    case 89:  /* swapsi */
    case 90:  /* *swapqi_1 */
    case 91:  /* *swaphi_1 */
    case 147:  /* fix_truncsfsi_sse */
    case 148:  /* fix_truncdfsi_sse */
    case 200:  /* *floatsisf2_vector_sse */
    case 201:  /* *floatsidf2_vector_sse */
    case 208:  /* *floatsisf2_sse_nointerunit */
    case 209:  /* *floatdisf2_sse_nointerunit */
    case 210:  /* *floatsidf2_sse_nointerunit */
    case 211:  /* *floatdidf2_sse_nointerunit */
    case 307:  /* *mulsidi3_1 */
    case 310:  /* *smulsi3_highpart_1 */
    case 311:  /* *umulsi3_highpart_1 */
    case 1167:  /* sse_cvtss2si_2 */
    case 1168:  /* sse_cvttss2si */
    case 1180:  /* sse2_cvtsd2si_2 */
    case 1181:  /* sse2_cvttsd2si */
    case 1187:  /* *sse2_cvtpd2dq */
    case 1190:  /* *sse2_cvttpd2dq */
    case 1194:  /* *sse2_cvtpd2ps */
      return AMDFAM10_DECODE_DOUBLE;

    case 168:  /* x86_fldcw_1 */
    case 425:  /* x86_shld */
    case 448:  /* x86_shrd */
      return AMDFAM10_DECODE_VECTOR;

    case -1:
      if (GET_CODE (PATTERN (insn)) != ASM_INPUT
          && asm_noperands (PATTERN (insn)) < 0)
        fatal_insn_not_found (insn);
    default:
      return AMDFAM10_DECODE_DIRECT;

    }
}

enum attr_athlon_decode
get_attr_athlon_decode (rtx insn ATTRIBUTE_UNUSED)
{
  enum attr_memory cached_memory ATTRIBUTE_UNUSED;
  enum attr_type cached_type ATTRIBUTE_UNUSED;

  switch (recog_memoized (insn))
    {
    case 1191:  /* sse2_cvtsd2ss */
    case 1165:  /* sse_cvtsi2ss */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return ATHLON_DECODE_VECTOR;
        }
      else if (which_alternative == 1)
        {
	  return ATHLON_DECODE_DOUBLE;
        }
      else
        {
	  return ATHLON_DECODE_DIRECT;
        }

    case 840:  /* *movv2sf_internal */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0xc00))
        {
	  return ATHLON_DECODE_VECTOR;
        }
      else
        {
	  return ATHLON_DECODE_DIRECT;
        }

    case 839:  /* *movv1di_internal */
    case 838:  /* *movv2si_internal */
    case 837:  /* *movv4hi_internal */
    case 836:  /* *movv8qi_internal */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x6000))
        {
	  return ATHLON_DECODE_VECTOR;
        }
      else
        {
	  return ATHLON_DECODE_DIRECT;
        }

    case 306:  /* *umulsidi3_1 */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 1)
        {
	  if (((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_ATHLON))))
	    {
	      return ATHLON_DECODE_VECTOR;
	    }
	  else
	    {
	      return ATHLON_DECODE_DOUBLE;
	    }
        }
      else
        {
	  if (which_alternative != 0)
	    {
	      return ATHLON_DECODE_VECTOR;
	    }
	  else
	    {
	      return ATHLON_DECODE_DIRECT;
	    }
        }

    case 193:  /* *floatdidf2_mixed_interunit */
    case 192:  /* *floatsidf2_mixed_interunit */
    case 191:  /* *floatdisf2_mixed_interunit */
    case 190:  /* *floatsisf2_mixed_interunit */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return ATHLON_DECODE_DIRECT;
        }
      else if (which_alternative == 1)
        {
	  return ATHLON_DECODE_DOUBLE;
        }
      else
        {
	  return ATHLON_DECODE_DIRECT;
        }

    case 189:  /* *floatsidf2_mixed_with_temp */
    case 188:  /* *floatsisf2_mixed_with_temp */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  if (which_alternative == 1)
	    {
	      return ATHLON_DECODE_VECTOR;
	    }
	  else
	    {
	      return ATHLON_DECODE_DIRECT;
	    }
        }
      else if (which_alternative == 2)
        {
	  return ATHLON_DECODE_DOUBLE;
        }
      else
        {
	  return ATHLON_DECODE_DIRECT;
        }

    case 185:  /* *floatsidf2_vector_mixed_with_temp */
    case 184:  /* *floatsisf2_vector_mixed_with_temp */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  if (which_alternative == 1)
	    {
	      return ATHLON_DECODE_VECTOR;
	    }
	  else
	    {
	      return ATHLON_DECODE_DIRECT;
	    }
        }
      else if (which_alternative == 2)
        {
	  return ATHLON_DECODE_DOUBLE;
        }
      else if (which_alternative == 3)
        {
	  return ATHLON_DECODE_DIRECT;
        }
      else
        {
	  return ATHLON_DECODE_DOUBLE;
        }

    case 223:  /* *floatdixf2_i387 */
    case 220:  /* *floatsixf2_i387 */
    case 177:  /* *floathixf2_i387 */
      if (((cached_memory = get_attr_memory (insn)) == MEMORY_LOAD) || (cached_memory == MEMORY_STORE))
        {
	  return ATHLON_DECODE_VECTOR;
        }
      else
        {
	  return ATHLON_DECODE_DIRECT;
        }

    case 217:  /* *floatdixf2_i387_with_temp */
    case 214:  /* *floatsixf2_i387_with_temp */
    case 174:  /* *floathixf2_i387_with_temp */
      extract_constrain_insn_cached (insn);
      if ((which_alternative != 0) || ((which_alternative == 0) && (((cached_memory = get_attr_memory (insn)) == MEMORY_LOAD) || (cached_memory == MEMORY_STORE))))
        {
	  return ATHLON_DECODE_VECTOR;
        }
      else
        {
	  return ATHLON_DECODE_DIRECT;
        }

    case 1228:  /* *sse4_1_extractps */
    case 216:  /* *floatdidf2_i387_with_temp */
    case 215:  /* *floatdisf2_i387_with_temp */
    case 213:  /* *floatsidf2_i387_with_temp */
    case 212:  /* *floatsisf2_i387_with_temp */
    case 173:  /* *floathidf2_i387_with_temp */
    case 172:  /* *floathisf2_i387_with_temp */
    case 140:  /* *truncxfdf2_mixed */
    case 139:  /* *truncxfsf2_mixed */
    case 137:  /* *truncdfsf_i387 */
      extract_constrain_insn_cached (insn);
      if (which_alternative != 0)
        {
	  return ATHLON_DECODE_VECTOR;
        }
      else
        {
	  return ATHLON_DECODE_DIRECT;
        }

    case 136:  /* *truncdfsf_mixed */
      extract_constrain_insn_cached (insn);
      if (!((1 << which_alternative) & 0x3))
        {
	  return ATHLON_DECODE_VECTOR;
        }
      else
        {
	  return ATHLON_DECODE_DIRECT;
        }

    case 132:  /* *extenddfxf2_i387 */
    case 131:  /* *extendsfxf2_i387 */
    case 130:  /* *extendsfdf2_i387 */
      extract_constrain_insn_cached (insn);
      if ((which_alternative == 1) && (((cached_memory = get_attr_memory (insn)) == MEMORY_LOAD) || (cached_memory == MEMORY_STORE)))
        {
	  return ATHLON_DECODE_VECTOR;
        }
      else
        {
	  return ATHLON_DECODE_DIRECT;
        }

    case 128:  /* *extendsfdf2_mixed */
      extract_constrain_insn_cached (insn);
      if ((((cached_memory = get_attr_memory (insn)) == MEMORY_LOAD) || (cached_memory == MEMORY_STORE)) && (which_alternative == 1))
        {
	  return ATHLON_DECODE_VECTOR;
        }
      else
        {
	  return ATHLON_DECODE_DIRECT;
        }

    case 117:  /* *zero_extendsidi2 */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x7))
        {
	  return ATHLON_DECODE_VECTOR;
        }
      else
        {
	  return ATHLON_DECODE_DIRECT;
        }

    case 112:  /* *movdf_internal */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x18))
        {
	  return ATHLON_DECODE_VECTOR;
        }
      else
        {
	  return ATHLON_DECODE_DIRECT;
        }

    case 111:  /* *movxf_internal */
      extract_constrain_insn_cached (insn);
      if ((!((1 << which_alternative) & 0x7)) || ((((1 << which_alternative) & 0x7)) && (((cached_memory = get_attr_memory (insn)) == MEMORY_LOAD) || (cached_memory == MEMORY_STORE))))
        {
	  return ATHLON_DECODE_VECTOR;
        }
      else
        {
	  return ATHLON_DECODE_DIRECT;
        }

    case 109:  /* *pushsf */
      extract_constrain_insn_cached (insn);
      if ((which_alternative != 1) || ((which_alternative == 1) && (memory_operand (operands[1], VOIDmode))))
        {
	  return ATHLON_DECODE_VECTOR;
        }
      else
        {
	  return ATHLON_DECODE_DIRECT;
        }

    case 778:  /* *movsfcc_1_387 */
    case 77:  /* *movdi_internal */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return ATHLON_DECODE_VECTOR;
        }
      else
        {
	  return ATHLON_DECODE_DIRECT;
        }

    case 68:  /* *pushdi2_prologue */
    case 67:  /* *pushsi2_prologue */
    case 66:  /* *pushhi2 */
    case 65:  /* *pushqi2 */
    case 64:  /* *pushsi2 */
      extract_insn_cached (insn);
      if (memory_operand (operands[1], VOIDmode))
        {
	  return ATHLON_DECODE_VECTOR;
        }
      else
        {
	  return ATHLON_DECODE_DIRECT;
        }

    case 198:  /* *floatsisf2_vector_sse_with_temp */
    case 199:  /* *floatsidf2_vector_sse_with_temp */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return ATHLON_DECODE_DOUBLE;
        }
      else if (which_alternative == 1)
        {
	  return ATHLON_DECODE_DIRECT;
        }
      else
        {
	  return ATHLON_DECODE_DOUBLE;
        }

    case 1178:  /* sse2_cvtsi2sd */
    case 202:  /* *floatsisf2_sse_with_temp */
    case 203:  /* *floatsidf2_sse_with_temp */
    case 204:  /* *floatsisf2_sse_interunit */
    case 205:  /* *floatdisf2_sse_interunit */
    case 206:  /* *floatsidf2_sse_interunit */
    case 207:  /* *floatdidf2_sse_interunit */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return ATHLON_DECODE_DOUBLE;
        }
      else
        {
	  return ATHLON_DECODE_DIRECT;
        }

    case 302:  /* *mulsi3_1 */
      extract_constrain_insn_cached (insn);
      if (((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_ATHLON))))
        {
	  return ATHLON_DECODE_VECTOR;
        }
      else if (which_alternative == 1)
        {
	  return ATHLON_DECODE_VECTOR;
        }
      else if ((which_alternative == 2) && (memory_operand (operands[1], VOIDmode)))
        {
	  return ATHLON_DECODE_VECTOR;
        }
      else
        {
	  return ATHLON_DECODE_DIRECT;
        }

    case 303:  /* *mulhi3_1 */
      extract_constrain_insn_cached (insn);
      if (((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_ATHLON))))
        {
	  return ATHLON_DECODE_VECTOR;
        }
      else if (((1 << which_alternative) & 0x6))
        {
	  return ATHLON_DECODE_VECTOR;
        }
      else
        {
	  return ATHLON_DECODE_DIRECT;
        }

    case 304:  /* *mulqi3_1 */
    case 308:  /* *mulqihi3_1 */
    case 309:  /* *umulqihi3_1 */
      if (((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_ATHLON))))
        {
	  return ATHLON_DECODE_VECTOR;
        }
      else
        {
	  return ATHLON_DECODE_DIRECT;
        }

    case 307:  /* *mulsidi3_1 */
    case 310:  /* *smulsi3_highpart_1 */
    case 311:  /* *umulsi3_highpart_1 */
      if (((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_ATHLON))))
        {
	  return ATHLON_DECODE_VECTOR;
        }
      else
        {
	  return ATHLON_DECODE_DOUBLE;
        }

    case 147:  /* fix_truncsfsi_sse */
    case 148:  /* fix_truncdfsi_sse */
    case 1166:  /* sse_cvtss2si */
    case 1167:  /* sse_cvtss2si_2 */
    case 1168:  /* sse_cvttss2si */
    case 1179:  /* sse2_cvtsd2si */
    case 1180:  /* sse2_cvtsd2si_2 */
    case 1181:  /* sse2_cvttsd2si */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return ATHLON_DECODE_DOUBLE;
        }
      else
        {
	  return ATHLON_DECODE_VECTOR;
        }

    case -1:
      if (GET_CODE (PATTERN (insn)) != ASM_INPUT
          && asm_noperands (PATTERN (insn)) < 0)
        fatal_insn_not_found (insn);
      extract_insn_cached (insn);
      if (((cached_type = get_attr_type (insn)) == TYPE_CALL) || ((cached_type == TYPE_IMUL) || ((cached_type == TYPE_IDIV) || ((cached_type == TYPE_OTHER) || ((cached_type == TYPE_MULTI) || ((cached_type == TYPE_FCMOV) || ((cached_type == TYPE_FPSPC) || ((cached_type == TYPE_STR) || ((cached_type == TYPE_POP) || (cached_type == TYPE_LEAVE))))))))))
        {
	  return ATHLON_DECODE_VECTOR;
        }
      else if ((cached_type == TYPE_PUSH) && (memory_operand (operands[1], VOIDmode)))
        {
	  return ATHLON_DECODE_VECTOR;
        }
      else if ((cached_type == TYPE_FMOV) && ((((cached_memory = get_attr_memory (insn)) == MEMORY_LOAD) || (cached_memory == MEMORY_STORE)) && (get_attr_mode (insn) == MODE_XF)))
        {
	  return ATHLON_DECODE_VECTOR;
        }
      else
        {
	  return ATHLON_DECODE_DIRECT;
        }

    case 1197:  /* sse2_cvtps2pd */
      return ATHLON_DECODE_DOUBLE;

    case 1905:  /* atomic_xorsi */
    case 1904:  /* atomic_orsi */
    case 1903:  /* atomic_andsi */
    case 1902:  /* atomic_xorhi */
    case 1901:  /* atomic_orhi */
    case 1900:  /* atomic_andhi */
    case 1899:  /* atomic_xorqi */
    case 1898:  /* atomic_orqi */
    case 1897:  /* atomic_andqi */
    case 1896:  /* atomic_subsi */
    case 1895:  /* atomic_subhi */
    case 1894:  /* atomic_subqi */
    case 1893:  /* atomic_addsi */
    case 1892:  /* atomic_addhi */
    case 1891:  /* atomic_addqi */
    case 1890:  /* atomic_exchangesi */
    case 1889:  /* atomic_exchangehi */
    case 1888:  /* atomic_exchangeqi */
    case 1887:  /* *atomic_fetch_add_cmpsi */
    case 1886:  /* *atomic_fetch_add_cmphi */
    case 1885:  /* *atomic_fetch_add_cmpqi */
    case 1884:  /* atomic_fetch_addsi */
    case 1883:  /* atomic_fetch_addhi */
    case 1882:  /* atomic_fetch_addqi */
    case 1881:  /* atomic_compare_and_swapdi_doubleword */
    case 1880:  /* atomic_compare_and_swapsi_1 */
    case 1879:  /* atomic_compare_and_swaphi_1 */
    case 1878:  /* atomic_compare_and_swapqi_1 */
    case 1875:  /* atomic_storedi_fpu */
    case 1874:  /* atomic_storesi_1 */
    case 1873:  /* atomic_storehi_1 */
    case 1872:  /* atomic_storeqi_1 */
    case 1871:  /* atomic_loaddi_fpu */
    case 1870:  /* mfence_nosse */
    case 1772:  /* avx_pd256_pd */
    case 1771:  /* avx_ps256_ps */
    case 1770:  /* avx_si256_si */
    case 1725:  /* *avx_vperm_broadcast_v4df */
    case 1724:  /* *avx_vperm_broadcast_v8sf */
    case 1463:  /* sse3_monitor */
    case 1462:  /* sse3_mwait */
    case 1436:  /* *sse2_storeq */
    case 1435:  /* *vec_ext_v4si_mem */
    case 1434:  /* sse2_stored */
    case 1240:  /* vec_extract_lo_v32qi */
    case 1238:  /* vec_extract_lo_v16hi */
    case 1235:  /* vec_extract_lo_v8sf */
    case 1234:  /* vec_extract_lo_v8si */
    case 1231:  /* vec_extract_lo_v4df */
    case 1230:  /* vec_extract_lo_v4di */
    case 1229:  /* *vec_extract_v4sf_mem */
    case 1227:  /* *vec_extractv4sf_0 */
    case 987:  /* *absnegv2df2 */
    case 986:  /* *absnegv4df2 */
    case 985:  /* *absnegv4sf2 */
    case 984:  /* *absnegv8sf2 */
    case 962:  /* movdi_to_sse */
    case 937:  /* *vec_extractv2si_0 */
    case 867:  /* *vec_extractv2sf_0 */
    case 835:  /* xtest_1 */
    case 834:  /* xabort */
    case 833:  /* xend */
    case 832:  /* xbegin_1 */
    case 831:  /* *pause */
    case 830:  /* rdseedsi_1 */
    case 829:  /* rdseedhi_1 */
    case 828:  /* rdrandsi_1 */
    case 827:  /* rdrandhi_1 */
    case 820:  /* xrstor */
    case 819:  /* xsaveopt */
    case 818:  /* xsave */
    case 817:  /* fxrstor */
    case 816:  /* fxsave */
    case 815:  /* rdtscp */
    case 814:  /* rdtsc */
    case 813:  /* rdpmc */
    case 809:  /* stack_tls_protect_test_di */
    case 808:  /* stack_tls_protect_test_si */
    case 807:  /* stack_protect_test_di */
    case 806:  /* stack_protect_test_si */
    case 805:  /* stack_tls_protect_set_di */
    case 804:  /* stack_tls_protect_set_si */
    case 803:  /* stack_protect_set_di */
    case 802:  /* stack_protect_set_si */
    case 799:  /* trap */
    case 798:  /* probe_stack_rangedi */
    case 797:  /* probe_stack_rangesi */
    case 796:  /* adjust_stack_and_probedi */
    case 795:  /* adjust_stack_and_probesi */
    case 794:  /* allocate_stack_worker_probe_di */
    case 793:  /* allocate_stack_worker_probe_si */
    case 777:  /* *movdfcc_1 */
    case 776:  /* *movxfcc_1 */
    case 769:  /* *strlenqi_1 */
    case 768:  /* *strlenqi_1 */
    case 767:  /* *cmpstrnqi_1 */
    case 766:  /* *cmpstrnqi_1 */
    case 765:  /* *cmpstrnqi_nz_1 */
    case 764:  /* *cmpstrnqi_nz_1 */
    case 763:  /* *rep_stosqi */
    case 762:  /* *rep_stosqi */
    case 761:  /* *rep_stossi */
    case 760:  /* *rep_stossi */
    case 759:  /* *strsetqi_1 */
    case 758:  /* *strsetqi_1 */
    case 757:  /* *strsethi_1 */
    case 756:  /* *strsethi_1 */
    case 755:  /* *strsetsi_1 */
    case 754:  /* *strsetsi_1 */
    case 753:  /* *rep_movqi */
    case 752:  /* *rep_movqi */
    case 751:  /* *rep_movsi */
    case 750:  /* *rep_movsi */
    case 749:  /* *strmovqi_1 */
    case 748:  /* *strmovqi_1 */
    case 747:  /* *strmovhi_1 */
    case 746:  /* *strmovhi_1 */
    case 745:  /* *strmovsi_1 */
    case 744:  /* *strmovsi_1 */
    case 743:  /* cld */
    case 741:  /* fxamdf2_i387_with_temp */
    case 740:  /* fxamsf2_i387_with_temp */
    case 739:  /* fxamxf2_i387 */
    case 738:  /* fxamdf2_i387 */
    case 737:  /* fxamsf2_i387 */
    case 710:  /* fistsi2_with_temp */
    case 709:  /* fisthi2_with_temp */
    case 708:  /* fistsi2 */
    case 707:  /* fisthi2 */
    case 706:  /* *fistsi2_1 */
    case 705:  /* *fisthi2_1 */
    case 704:  /* fistdi2_with_temp */
    case 703:  /* fistdi2 */
    case 702:  /* *fistdi2_1 */
    case 701:  /* rintxf2 */
    case 698:  /* *fscalexf4_i387 */
    case 697:  /* *f2xm1xf2_i387 */
    case 696:  /* fxtract_extenddfxf3_i387 */
    case 695:  /* fxtract_extendsfxf3_i387 */
    case 694:  /* fxtractxf3_i387 */
    case 693:  /* fyl2xp1_extenddfxf3_i387 */
    case 692:  /* fyl2xp1_extendsfxf3_i387 */
    case 691:  /* fyl2xp1xf3_i387 */
    case 690:  /* fyl2x_extenddfxf3_i387 */
    case 689:  /* fyl2x_extendsfxf3_i387 */
    case 688:  /* fyl2xxf3_i387 */
    case 687:  /* fpatan_extenddfxf3_i387 */
    case 686:  /* fpatan_extendsfxf3_i387 */
    case 685:  /* *fpatanxf3_i387 */
    case 684:  /* fptan_extenddfxf4_i387 */
    case 683:  /* fptan_extendsfxf4_i387 */
    case 682:  /* fptanxf4_i387 */
    case 681:  /* sincos_extenddfxf3_i387 */
    case 680:  /* sincos_extendsfxf3_i387 */
    case 679:  /* sincosxf3 */
    case 678:  /* *cos_extenddfxf2_i387 */
    case 677:  /* *sin_extenddfxf2_i387 */
    case 676:  /* *cos_extendsfxf2_i387 */
    case 675:  /* *sin_extendsfxf2_i387 */
    case 674:  /* *cosxf2_i387 */
    case 673:  /* *sinxf2_i387 */
    case 672:  /* fprem1xf4_i387 */
    case 671:  /* fpremxf4_i387 */
    case 626:  /* *tls_dynamic_gnu2_combine_32 */
    case 625:  /* *tls_dynamic_gnu2_call_32 */
    case 615:  /* *tls_local_dynamic_32_once */
    case 614:  /* *tls_local_dynamic_base_32_gnu */
    case 613:  /* *tls_global_dynamic_32_gnu */
    case 612:  /* *parityhi2_cmp */
    case 611:  /* paritysi2_cmp */
    case 610:  /* paritydi2_cmp */
    case 609:  /* bswaphi_lowpart */
    case 608:  /* *bswaphi_lowpart_1 */
    case 574:  /* ffssi2_no_cmove */
    case 573:  /* split_stack_return */
    case 572:  /* leave */
    case 571:  /* eh_return_internal */
    case 569:  /* set_got_labelled */
    case 568:  /* set_got */
    case 567:  /* pad */
    case 566:  /* nops */
    case 565:  /* nop */
    case 563:  /* simple_return_pop_internal */
    case 562:  /* simple_return_internal_long */
    case 561:  /* simple_return_internal */
    case 560:  /* prologue_use */
    case 559:  /* *memory_blockage */
    case 558:  /* blockage */
    case 551:  /* *sibcall_pop */
    case 550:  /* *call_pop */
    case 549:  /* *sibcall */
    case 548:  /* *sibcall */
    case 547:  /* *call */
    case 546:  /* *call */
    case 540:  /* *jccxf_si_r_i387 */
    case 539:  /* *jccdf_si_r_i387 */
    case 538:  /* *jccsf_si_r_i387 */
    case 537:  /* *jccxf_hi_r_i387 */
    case 536:  /* *jccdf_hi_r_i387 */
    case 535:  /* *jccsf_hi_r_i387 */
    case 534:  /* *jccxf_si_i387 */
    case 533:  /* *jccdf_si_i387 */
    case 532:  /* *jccsf_si_i387 */
    case 531:  /* *jccxf_hi_i387 */
    case 530:  /* *jccdf_hi_i387 */
    case 529:  /* *jccsf_hi_i387 */
    case 528:  /* *jccuxf_r_i387 */
    case 527:  /* *jccudf_r_i387 */
    case 526:  /* *jccusf_r_i387 */
    case 525:  /* *jccuxf_i387 */
    case 524:  /* *jccudf_i387 */
    case 523:  /* *jccusf_i387 */
    case 522:  /* *jccdf_r_i387 */
    case 521:  /* *jccsf_r_i387 */
    case 520:  /* *jccdf_i387 */
    case 519:  /* *jccsf_i387 */
    case 518:  /* *jccxf_r_i387 */
    case 517:  /* *jccxf_i387 */
    case 516:  /* *jccxf_0_r_i387 */
    case 515:  /* *jccdf_0_r_i387 */
    case 514:  /* *jccsf_0_r_i387 */
    case 513:  /* *jccxf_0_i387 */
    case 512:  /* *jccdf_0_i387 */
    case 511:  /* *jccsf_0_i387 */
    case 510:  /* *jcc_btsi_mask_1 */
    case 509:  /* *jcc_btsi_1 */
    case 508:  /* *jcc_btdi_mask */
    case 507:  /* *jcc_btsi_mask */
    case 506:  /* *jcc_btdi */
    case 505:  /* *jcc_btsi */
    case 498:  /* *setcc_si_1_movzbl */
    case 497:  /* *setcc_si_1_and */
    case 483:  /* ix86_rotrdi3_doubleword */
    case 482:  /* ix86_rotldi3_doubleword */
    case 447:  /* *ashrdi3_doubleword */
    case 446:  /* *lshrdi3_doubleword */
    case 424:  /* *ashldi3_doubleword */
    case 415:  /* copysigntf3_var */
    case 414:  /* copysigndf3_var */
    case 413:  /* copysignsf3_var */
    case 412:  /* copysigntf3_const */
    case 411:  /* copysigndf3_const */
    case 410:  /* copysignsf3_const */
    case 397:  /* *absnegtf2_sse */
    case 396:  /* *absnegxf2_i387 */
    case 395:  /* *absnegdf2_i387 */
    case 394:  /* *absnegsf2_i387 */
    case 393:  /* *absnegdf2_sse */
    case 392:  /* *absnegsf2_sse */
    case 391:  /* *absnegdf2_mixed */
    case 390:  /* *absnegsf2_mixed */
    case 381:  /* *negti2_doubleword */
    case 380:  /* *negdi2_doubleword */
    case 331:  /* *testqi_ext_3 */
    case 323:  /* udivmodhiqi3 */
    case 322:  /* *udivmodsi4_noext */
    case 321:  /* *udivmodhi4_noext */
    case 320:  /* *udivmodsi4 */
    case 319:  /* *udivmodhi4 */
    case 318:  /* udivmodsi4_1 */
    case 317:  /* divmodhiqi3 */
    case 316:  /* *divmodsi4_noext */
    case 315:  /* *divmodhi4_noext */
    case 314:  /* *divmodsi4 */
    case 313:  /* *divmodhi4 */
    case 312:  /* divmodsi4_1 */
    case 264:  /* *subti3_doubleword */
    case 263:  /* *subdi3_doubleword */
    case 232:  /* *addti3_doubleword */
    case 231:  /* *adddi3_doubleword */
    case 229:  /* *floatunssixf2_1 */
    case 228:  /* *floatunssidf2_1 */
    case 227:  /* *floatunssisf2_1 */
    case 226:  /* floatdixf2_i387_with_xmm */
    case 225:  /* floatdidf2_i387_with_xmm */
    case 224:  /* floatdisf2_i387_with_xmm */
    case 183:  /* *floatdixf2_1 */
    case 182:  /* *floatdidf2_1 */
    case 181:  /* *floatdisf2_1 */
    case 180:  /* *floatsixf2_1 */
    case 179:  /* *floatsidf2_1 */
    case 178:  /* *floatsisf2_1 */
    case 171:  /* *floathixf2_1 */
    case 170:  /* *floathidf2_1 */
    case 169:  /* *floathisf2_1 */
    case 167:  /* x86_fnstcw_1 */
    case 146:  /* *fixuns_truncdf_1 */
    case 145:  /* *fixuns_truncsf_1 */
    case 124:  /* extendsidi2_1 */
    case 108:  /* *pushdf */
    case 107:  /* *pushxf_nointeger */
    case 106:  /* *pushxf */
    case 105:  /* *pushtf */
    case 72:  /* *popdi1_epilogue */
    case 71:  /* *popsi1_epilogue */
    case 70:  /* *popdi1 */
    case 69:  /* *popsi1 */
    case 63:  /* *pushdi2 */
    case 47:  /* x86_fnstsw_1 */
    case 46:  /* *cmpxf_si_cc_i387 */
    case 45:  /* *cmpdf_si_cc_i387 */
    case 44:  /* *cmpsf_si_cc_i387 */
    case 43:  /* *cmpxf_hi_cc_i387 */
    case 42:  /* *cmpdf_hi_cc_i387 */
    case 41:  /* *cmpsf_hi_cc_i387 */
    case 40:  /* *cmpxf_si_i387 */
    case 39:  /* *cmpdf_si_i387 */
    case 38:  /* *cmpsf_si_i387 */
    case 37:  /* *cmpxf_hi_i387 */
    case 36:  /* *cmpdf_hi_i387 */
    case 35:  /* *cmpsf_hi_i387 */
    case 34:  /* *cmpuxf_cc_i387 */
    case 33:  /* *cmpudf_cc_i387 */
    case 32:  /* *cmpusf_cc_i387 */
    case 31:  /* *cmpuxf_i387 */
    case 30:  /* *cmpudf_i387 */
    case 29:  /* *cmpusf_i387 */
    case 28:  /* *cmpdf_cc_i387 */
    case 27:  /* *cmpsf_cc_i387 */
    case 26:  /* *cmpdf_i387 */
    case 25:  /* *cmpsf_i387 */
    case 24:  /* *cmpxf_cc_i387 */
    case 23:  /* *cmpxf_i387 */
    case 22:  /* *cmpxf_0_cc_i387 */
    case 21:  /* *cmpdf_0_cc_i387 */
    case 20:  /* *cmpsf_0_cc_i387 */
    case 19:  /* *cmpxf_0_i387 */
    case 18:  /* *cmpdf_0_i387 */
    case 17:  /* *cmpsf_0_i387 */
    case 48:  /* x86_sahf_1 */
    case 49:  /* *cmpisf_mixed */
    case 50:  /* *cmpidf_mixed */
    case 51:  /* *cmpiusf_mixed */
    case 52:  /* *cmpiudf_mixed */
    case 53:  /* *cmpisf_sse */
    case 54:  /* *cmpidf_sse */
    case 55:  /* *cmpiusf_sse */
    case 56:  /* *cmpiudf_sse */
    case 57:  /* *cmpisf_i387 */
    case 58:  /* *cmpidf_i387 */
    case 59:  /* *cmpixf_i387 */
    case 60:  /* *cmpiusf_i387 */
    case 61:  /* *cmpiudf_i387 */
    case 62:  /* *cmpiuxf_i387 */
    case 89:  /* swapsi */
    case 90:  /* *swapqi_1 */
    case 91:  /* *swaphi_1 */
    case 92:  /* *swapqi_2 */
    case 93:  /* *swaphi_2 */
    case 168:  /* x86_fldcw_1 */
    case 425:  /* x86_shld */
    case 448:  /* x86_shrd */
    case 1187:  /* *sse2_cvtpd2dq */
    case 1190:  /* *sse2_cvttpd2dq */
    case 1194:  /* *sse2_cvtpd2ps */
      return ATHLON_DECODE_VECTOR;

    default:
      return ATHLON_DECODE_DIRECT;

    }
}

enum attr_btver2_sse_attr
get_attr_btver2_sse_attr (rtx insn ATTRIBUTE_UNUSED)
{
  switch (recog_memoized (insn))
    {
    case 1024:  /* *smaxv8sf3_finite */
    case 1025:  /* *sminv8sf3_finite */
    case 1026:  /* *smaxv4sf3_finite */
    case 1027:  /* *sminv4sf3_finite */
    case 1028:  /* *smaxv4df3_finite */
    case 1029:  /* *sminv4df3_finite */
    case 1030:  /* *smaxv2df3_finite */
    case 1031:  /* *sminv2df3_finite */
    case 1032:  /* *smaxv8sf3 */
    case 1033:  /* *sminv8sf3 */
    case 1034:  /* *smaxv4sf3 */
    case 1035:  /* *sminv4sf3 */
    case 1036:  /* *smaxv4df3 */
    case 1037:  /* *sminv4df3 */
    case 1038:  /* *smaxv2df3 */
    case 1039:  /* *sminv2df3 */
    case 1040:  /* sse_vmsmaxv4sf3 */
    case 1041:  /* sse_vmsminv4sf3 */
    case 1042:  /* sse2_vmsmaxv2df3 */
    case 1043:  /* sse2_vmsminv2df3 */
      return BTVER2_SSE_ATTR_MAXMIN;

    case 669:  /* *sqrtsf2_sse */
    case 670:  /* *sqrtdf2_sse */
    case 1015:  /* avx_sqrtv8sf2 */
    case 1016:  /* sse_sqrtv4sf2 */
    case 1017:  /* avx_sqrtv4df2 */
    case 1018:  /* sse2_sqrtv2df2 */
    case 1019:  /* sse_vmsqrtv4sf2 */
    case 1020:  /* sse2_vmsqrtv2df2 */
      return BTVER2_SSE_ATTR_SQRT;

    case 635:  /* *rcpsf2_sse */
    case 668:  /* *rsqrtsf2_sse */
    case 1012:  /* avx_rcpv8sf2 */
    case 1013:  /* sse_rcpv4sf2 */
    case 1014:  /* sse_vmrcpv4sf2 */
      return BTVER2_SSE_ATTR_RCP;

    case -1:
      if (GET_CODE (PATTERN (insn)) != ASM_INPUT
          && asm_noperands (PATTERN (insn)) < 0)
        fatal_insn_not_found (insn);
    default:
      return BTVER2_SSE_ATTR_OTHER;

    }
}

enum attr_btver2_decode
get_attr_btver2_decode (rtx insn ATTRIBUTE_UNUSED)
{
  switch (recog_memoized (insn))
    {
    case 581:  /* *bmi_andn_si */
    case 582:  /* bmi_bextr_si */
    case 1000:  /* *mulv8sf3 */
    case 1001:  /* *mulv4sf3 */
    case 1002:  /* *mulv4df3 */
    case 1003:  /* *mulv2df3 */
    case 1010:  /* sse_vmdivv4sf3 */
    case 1011:  /* sse2_vmdivv2df3 */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return BTVER2_DECODE_DIRECT;
        }
      else
        {
	  return BTVER2_DECODE_DOUBLE;
        }

    case 202:  /* *floatsisf2_sse_with_temp */
    case 203:  /* *floatsidf2_sse_with_temp */
    case 204:  /* *floatsisf2_sse_interunit */
    case 205:  /* *floatdisf2_sse_interunit */
    case 206:  /* *floatsidf2_sse_interunit */
    case 207:  /* *floatdidf2_sse_interunit */
    case 575:  /* *tzcntsi_1 */
    case 576:  /* *bsfsi_1 */
    case 583:  /* *bmi_blsi_si */
    case 584:  /* *bmi_blsmsk_si */
    case 585:  /* *bmi_blsr_si */
    case 1165:  /* sse_cvtsi2ss */
    case 1178:  /* sse2_cvtsi2sd */
    case 1179:  /* sse2_cvtsd2si */
    case 1181:  /* sse2_cvttsd2si */
    case 1191:  /* sse2_cvtsd2ss */
    case 1192:  /* sse2_cvtss2sd */
    case 1682:  /* aesenc */
    case 1683:  /* aesenclast */
    case 1684:  /* aesdec */
    case 1685:  /* aesdeclast */
    case 1791:  /* vcvtph2ps256 */
      return BTVER2_DECODE_DOUBLE;

    case 1186:  /* *avx_cvtpd2dq256_2 */
    case 1189:  /* *avx_cvttpd2dq256_2 */
    case 1193:  /* avx_cvtpd2ps256 */
    case 1306:  /* *avx2_mulv8si3 */
    case 1307:  /* *sse4_1_mulv4si3 */
    case 1488:  /* avx2_pshufbv32qi3 */
    case 1489:  /* ssse3_pshufbv16qi3 */
    case 1524:  /* avx_blendvps256 */
    case 1525:  /* sse4_1_blendvps */
    case 1526:  /* avx_blendvpd256 */
    case 1527:  /* sse4_1_blendvpd */
    case 1528:  /* avx_dpps256 */
    case 1529:  /* sse4_1_dpps */
    case 1530:  /* avx_dppd256 */
    case 1531:  /* sse4_1_dppd */
    case 1534:  /* avx2_mpsadbw */
    case 1535:  /* sse4_1_mpsadbw */
    case 1538:  /* avx2_pblendvb */
    case 1539:  /* sse4_1_pblendvb */
    case 1573:  /* avx_ptest256 */
    case 1583:  /* sse4_2_pcmpestri */
    case 1584:  /* sse4_2_pcmpestrm */
    case 1585:  /* sse4_2_pcmpestr_cconly */
    case 1588:  /* sse4_2_pcmpistri */
    case 1589:  /* sse4_2_pcmpistrm */
    case 1590:  /* sse4_2_pcmpistr_cconly */
    case 1689:  /* *avx_vzeroall */
    case 1690:  /* avx_vzeroupper */
    case 1730:  /* avx_vpermilvarv8sf3 */
    case 1731:  /* avx_vpermilvarv4sf3 */
    case 1732:  /* avx_vpermilvarv4df3 */
    case 1733:  /* avx_vpermilvarv2df3 */
    case 1754:  /* avx_maskloadps */
    case 1755:  /* avx_maskloadpd */
    case 1756:  /* avx_maskloadps256 */
    case 1757:  /* avx_maskloadpd256 */
    case 1758:  /* avx2_maskloadd */
    case 1759:  /* avx2_maskloadq */
    case 1760:  /* avx2_maskloadd256 */
    case 1761:  /* avx2_maskloadq256 */
    case 1762:  /* avx_maskstoreps */
    case 1763:  /* avx_maskstorepd */
    case 1764:  /* avx_maskstoreps256 */
    case 1765:  /* avx_maskstorepd256 */
    case 1766:  /* avx2_maskstored */
    case 1767:  /* avx2_maskstoreq */
    case 1768:  /* avx2_maskstored256 */
    case 1769:  /* avx2_maskstoreq256 */
    case 1794:  /* vcvtps2ph256 */
      return BTVER2_DECODE_VECTOR;

    case -1:
      if (GET_CODE (PATTERN (insn)) != ASM_INPUT
          && asm_noperands (PATTERN (insn)) < 0)
        fatal_insn_not_found (insn);
    default:
      return BTVER2_DECODE_DIRECT;

    }
}

enum attr_bdver1_decode
get_attr_bdver1_decode (rtx insn ATTRIBUTE_UNUSED)
{
  switch (recog_memoized (insn))
    {
    case 189:  /* *floatsidf2_mixed_with_temp */
    case 188:  /* *floatsisf2_mixed_with_temp */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return BDVER1_DECODE_DIRECT;
        }
      else if (which_alternative == 2)
        {
	  return BDVER1_DECODE_DOUBLE;
        }
      else
        {
	  return BDVER1_DECODE_DIRECT;
        }

    case 185:  /* *floatsidf2_vector_mixed_with_temp */
    case 184:  /* *floatsisf2_vector_mixed_with_temp */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return BDVER1_DECODE_DIRECT;
        }
      else if (which_alternative == 2)
        {
	  return BDVER1_DECODE_DOUBLE;
        }
      else if (which_alternative == 3)
        {
	  return BDVER1_DECODE_DIRECT;
        }
      else
        {
	  return BDVER1_DECODE_DOUBLE;
        }

    case 190:  /* *floatsisf2_mixed_interunit */
    case 191:  /* *floatdisf2_mixed_interunit */
    case 192:  /* *floatsidf2_mixed_interunit */
    case 193:  /* *floatdidf2_mixed_interunit */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return BDVER1_DECODE_DIRECT;
        }
      else if (which_alternative == 1)
        {
	  return BDVER1_DECODE_DOUBLE;
        }
      else
        {
	  return BDVER1_DECODE_DIRECT;
        }

    case 198:  /* *floatsisf2_vector_sse_with_temp */
    case 199:  /* *floatsidf2_vector_sse_with_temp */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return BDVER1_DECODE_DOUBLE;
        }
      else if (which_alternative == 1)
        {
	  return BDVER1_DECODE_DIRECT;
        }
      else
        {
	  return BDVER1_DECODE_DOUBLE;
        }

    case 1178:  /* sse2_cvtsi2sd */
    case 1165:  /* sse_cvtsi2ss */
    case 202:  /* *floatsisf2_sse_with_temp */
    case 203:  /* *floatsidf2_sse_with_temp */
    case 204:  /* *floatsisf2_sse_interunit */
    case 205:  /* *floatdisf2_sse_interunit */
    case 206:  /* *floatsidf2_sse_interunit */
    case 207:  /* *floatdidf2_sse_interunit */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return BDVER1_DECODE_DOUBLE;
        }
      else
        {
	  return BDVER1_DECODE_DIRECT;
        }

    case 49:  /* *cmpisf_mixed */
    case 50:  /* *cmpidf_mixed */
    case 51:  /* *cmpiusf_mixed */
    case 52:  /* *cmpiudf_mixed */
    case 53:  /* *cmpisf_sse */
    case 54:  /* *cmpidf_sse */
    case 55:  /* *cmpiusf_sse */
    case 56:  /* *cmpiudf_sse */
    case 57:  /* *cmpisf_i387 */
    case 58:  /* *cmpidf_i387 */
    case 59:  /* *cmpixf_i387 */
    case 60:  /* *cmpiusf_i387 */
    case 61:  /* *cmpiudf_i387 */
    case 62:  /* *cmpiuxf_i387 */
    case 89:  /* swapsi */
    case 90:  /* *swapqi_1 */
    case 91:  /* *swaphi_1 */
    case 147:  /* fix_truncsfsi_sse */
    case 148:  /* fix_truncdfsi_sse */
    case 303:  /* *mulhi3_1 */
    case 1166:  /* sse_cvtss2si */
    case 1167:  /* sse_cvtss2si_2 */
    case 1168:  /* sse_cvttss2si */
    case 1176:  /* sse2_cvtpd2pi */
    case 1177:  /* sse2_cvttpd2pi */
    case 1179:  /* sse2_cvtsd2si */
    case 1180:  /* sse2_cvtsd2si_2 */
    case 1181:  /* sse2_cvttsd2si */
    case 1187:  /* *sse2_cvtpd2dq */
    case 1190:  /* *sse2_cvttpd2dq */
    case 1194:  /* *sse2_cvtpd2ps */
    case 1197:  /* sse2_cvtps2pd */
      return BDVER1_DECODE_DOUBLE;

    case 167:  /* x86_fnstcw_1 */
    case 168:  /* x86_fldcw_1 */
    case 425:  /* x86_shld */
    case 448:  /* x86_shrd */
      return BDVER1_DECODE_VECTOR;

    case -1:
      if (GET_CODE (PATTERN (insn)) != ASM_INPUT
          && asm_noperands (PATTERN (insn)) < 0)
        fatal_insn_not_found (insn);
    default:
      return BDVER1_DECODE_DIRECT;

    }
}

int
get_attr_enabled (rtx insn ATTRIBUTE_UNUSED)
{
  enum attr_isa cached_isa ATTRIBUTE_UNUSED;

  switch (recog_memoized (insn))
    {
    case 1712:  /* vec_dupv4df */
    case 1711:  /* vec_dupv4di */
    case 1710:  /* vec_dupv8sf */
    case 1709:  /* vec_dupv8si */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 1)
        {
	  return 
#line 668 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX2);
        }
      else if (!((1 << which_alternative) & 0x3))
        {
	  return 
#line 669 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(!TARGET_AVX2);
        }
      else
        {
	  return 1;
        }

    case 1444:  /* vec_concatv2di */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return 
#line 659 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SSE2);
        }
      else if (which_alternative == 2)
        {
	  return 
#line 661 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SSE2 && !TARGET_AVX);
        }
      else if (!((1 << which_alternative) & 0x37))
        {
	  return 
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX);
        }
      else
        {
	  return 
#line 667 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(!TARGET_AVX);
        }

    case 1443:  /* *vec_concatv4si */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return 
#line 661 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SSE2 && !TARGET_AVX);
        }
      else if (!((1 << which_alternative) & 0xd))
        {
	  return 
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX);
        }
      else
        {
	  return 
#line 667 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(!TARGET_AVX);
        }

    case 1439:  /* *vec_dupv2di */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return 
#line 661 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SSE2 && !TARGET_AVX);
        }
      else if (which_alternative == 2)
        {
	  return 
#line 662 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SSE3);
        }
      else if (which_alternative == 1)
        {
	  return 
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX);
        }
      else
        {
	  return 
#line 667 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(!TARGET_AVX);
        }

    case 1438:  /* *vec_dupv4si */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return 
#line 659 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SSE2);
        }
      else if (which_alternative == 1)
        {
	  return 
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX);
        }
      else
        {
	  return 
#line 667 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(!TARGET_AVX);
        }

    case 1437:  /* *vec_extractv2di_1 */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 3)
        {
	  return 
#line 659 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SSE2);
        }
      else if (which_alternative == 1)
        {
	  return 
#line 661 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SSE2 && !TARGET_AVX);
        }
      else if (which_alternative == 2)
        {
	  return 
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX);
        }
      else if (!((1 << which_alternative) & 0xf))
        {
	  return 
#line 667 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(!TARGET_AVX);
        }
      else
        {
	  return 1;
        }

    case 1433:  /* sse2_loadld */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return 
#line 659 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SSE2);
        }
      else if (!((1 << which_alternative) & 0xf))
        {
	  return 
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX);
        }
      else if (((1 << which_alternative) & 0xc))
        {
	  return 
#line 667 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(!TARGET_AVX);
        }
      else
        {
	  return 1;
        }

    case 1302:  /* *vec_widen_smult_even_v8si */
      extract_constrain_insn_cached (insn);
      return 
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX);

    case 1261:  /* *vec_concatv2df */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 5)
        {
	  return 
#line 659 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SSE2);
        }
      else if (((1 << which_alternative) & 0x9))
        {
	  return 
#line 661 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SSE2 && !TARGET_AVX);
        }
      else if (which_alternative == 2)
        {
	  return 
#line 662 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SSE3);
        }
      else if (((1 << which_alternative) & 0x12))
        {
	  return 
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX);
        }
      else
        {
	  return 
#line 667 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(!TARGET_AVX);
        }

    case 1260:  /* vec_dupv2df */
      extract_constrain_insn_cached (insn);
      if (which_alternative != 0)
        {
	  return 
#line 662 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SSE3);
        }
      else
        {
	  return 
#line 667 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(!TARGET_AVX);
        }

    case 1259:  /* sse2_movsd */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x8a))
        {
	  return 
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX);
        }
      else if (((1 << which_alternative) & 0x65))
        {
	  return 
#line 667 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(!TARGET_AVX);
        }
      else
        {
	  return 1;
        }

    case 1258:  /* sse2_loadlpd */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x94))
        {
	  return 
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX);
        }
      else if (((1 << which_alternative) & 0x6a))
        {
	  return 
#line 667 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(!TARGET_AVX);
        }
      else
        {
	  return 1;
        }

    case 1253:  /* sse2_storehpd */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 2)
        {
	  return 
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX);
        }
      else if (which_alternative == 1)
        {
	  return 
#line 667 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(!TARGET_AVX);
        }
      else
        {
	  return 1;
        }

    case 1245:  /* *vec_interleave_lowv2df */
    case 1243:  /* *vec_interleave_highv2df */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 2)
        {
	  return 
#line 662 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SSE3);
        }
      else if (((1 << which_alternative) & 0x12))
        {
	  return 
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX);
        }
      else if (((1 << which_alternative) & 0x9))
        {
	  return 
#line 667 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(!TARGET_AVX);
        }
      else
        {
	  return 1;
        }

    case 1224:  /* vec_setv4sf_0 */
    case 1223:  /* vec_setv4si_0 */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x6))
        {
	  return 
#line 659 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SSE2);
        }
      else if (which_alternative == 0)
        {
	  return 
#line 663 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SSE4_1);
        }
      else if (which_alternative == 6)
        {
	  return 
#line 665 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SSE4_1 && !TARGET_AVX);
        }
      else if (((1 << which_alternative) & 0xa0))
        {
	  return 
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX);
        }
      else if (((1 << which_alternative) & 0x18))
        {
	  return 
#line 667 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(!TARGET_AVX);
        }
      else
        {
	  return 1;
        }

    case 1222:  /* *vec_concatv4sf */
      extract_constrain_insn_cached (insn);
      if (!((1 << which_alternative) & 0x5))
        {
	  return 
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX);
        }
      else
        {
	  return 
#line 667 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(!TARGET_AVX);
        }

    case 1219:  /* vec_dupv4sf */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return 
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX);
        }
      else
        {
	  return 
#line 667 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(!TARGET_AVX);
        }

    case 1440:  /* *vec_concatv2si_sse4_1 */
    case 1257:  /* sse2_loadhpd */
    case 1220:  /* *vec_concatv2sf_sse4_1 */
    case 1214:  /* sse_loadlps */
    case 1212:  /* sse_loadhps */
    case 1199:  /* sse_movlhps */
    case 1198:  /* sse_movhlps */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0xa))
        {
	  return 
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX);
        }
      else if (((1 << which_alternative) & 0x5))
        {
	  return 
#line 667 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(!TARGET_AVX);
        }
      else
        {
	  return 1;
        }

    case 1145:  /* *fma_fmsubadd_v2df */
    case 1144:  /* *fma_fmsubadd_v4df */
    case 1143:  /* *fma_fmsubadd_v4sf */
    case 1142:  /* *fma_fmsubadd_v8sf */
    case 1141:  /* *fma_fmaddsub_v2df */
    case 1140:  /* *fma_fmaddsub_v4df */
    case 1139:  /* *fma_fmaddsub_v4sf */
    case 1138:  /* *fma_fmaddsub_v8sf */
    case 1137:  /* *fma_fnmsub_v4df */
    case 1136:  /* *fma_fnmsub_v8sf */
    case 1135:  /* *fma_fnmsub_v2df */
    case 1134:  /* *fma_fnmsub_v4sf */
    case 1133:  /* *fma_fnmsub_df */
    case 1132:  /* *fma_fnmsub_sf */
    case 1131:  /* *fma_fnmadd_v4df */
    case 1130:  /* *fma_fnmadd_v8sf */
    case 1129:  /* *fma_fnmadd_v2df */
    case 1128:  /* *fma_fnmadd_v4sf */
    case 1127:  /* *fma_fnmadd_df */
    case 1126:  /* *fma_fnmadd_sf */
    case 1125:  /* *fma_fmsub_v4df */
    case 1124:  /* *fma_fmsub_v8sf */
    case 1123:  /* *fma_fmsub_v2df */
    case 1122:  /* *fma_fmsub_v4sf */
    case 1121:  /* *fma_fmsub_df */
    case 1120:  /* *fma_fmsub_sf */
    case 1119:  /* *fma_fmadd_v4df */
    case 1118:  /* *fma_fmadd_v8sf */
    case 1117:  /* *fma_fmadd_v2df */
    case 1116:  /* *fma_fmadd_v4sf */
    case 1115:  /* *fma_fmadd_df */
    case 1114:  /* *fma_fmadd_sf */
      extract_constrain_insn_cached (insn);
      if (!((1 << which_alternative) & 0x7))
        {
	  return 
#line 671 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_FMA4);
        }
      else
        {
	  return 
#line 672 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_FMA);
        }

    case 1421:  /* sse4_1_pinsrq */
    case 1420:  /* sse4_1_pinsrd */
    case 1419:  /* sse2_pinsrw */
    case 1418:  /* sse4_1_pinsrb */
    case 1192:  /* sse2_cvtss2sd */
    case 1191:  /* sse2_cvtsd2ss */
    case 1178:  /* sse2_cvtsi2sd */
    case 1165:  /* sse_cvtsi2ss */
    case 987:  /* *absnegv2df2 */
    case 986:  /* *absnegv4df2 */
    case 985:  /* *absnegv4sf2 */
    case 984:  /* *absnegv8sf2 */
      extract_constrain_insn_cached (insn);
      if (!((1 << which_alternative) & 0x3))
        {
	  return 
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX);
        }
      else
        {
	  return 
#line 667 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(!TARGET_AVX);
        }

    case 938:  /* *vec_extractv2si_1 */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x6))
        {
	  return 
#line 659 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SSE2);
        }
      else
        {
	  return 1;
        }

    case 840:  /* *movv2sf_internal */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x30))
        {
	  return 
#line 659 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SSE2);
        }
      else
        {
	  return 1;
        }

    case 839:  /* *movv1di_internal */
    case 838:  /* *movv2si_internal */
    case 837:  /* *movv4hi_internal */
    case 836:  /* *movv8qi_internal */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x1f0))
        {
	  return 
#line 659 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SSE2);
        }
      else if (((1 << which_alternative) & 0x1e00))
        {
	  return 
#line 667 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(!TARGET_AVX);
        }
      else
        {
	  return 1;
        }

    case 634:  /* *fop_df_1_mixed */
    case 633:  /* *fop_sf_1_mixed */
      extract_constrain_insn_cached (insn);
      if (!((1 << which_alternative) & 0x7))
        {
	  return 
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX);
        }
      else if (which_alternative == 2)
        {
	  return 
#line 667 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(!TARGET_AVX);
        }
      else
        {
	  return 1;
        }

    case 1228:  /* *sse4_1_extractps */
    case 628:  /* *fop_df_comm_mixed */
    case 627:  /* *fop_sf_comm_mixed */
      extract_constrain_insn_cached (insn);
      if (!((1 << which_alternative) & 0x3))
        {
	  return 
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX);
        }
      else if (which_alternative == 1)
        {
	  return 
#line 667 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(!TARGET_AVX);
        }
      else
        {
	  return 1;
        }

    case 1688:  /* pclmulqdq */
    case 1685:  /* aesdeclast */
    case 1684:  /* aesdec */
    case 1683:  /* aesenclast */
    case 1682:  /* aesenc */
    case 1580:  /* sse4_1_roundsd */
    case 1579:  /* sse4_1_roundss */
    case 1540:  /* sse4_1_pblendw */
    case 1539:  /* sse4_1_pblendvb */
    case 1538:  /* avx2_pblendvb */
    case 1537:  /* sse4_1_packusdw */
    case 1535:  /* sse4_1_mpsadbw */
    case 1534:  /* avx2_mpsadbw */
    case 1531:  /* sse4_1_dppd */
    case 1530:  /* avx_dppd256 */
    case 1529:  /* sse4_1_dpps */
    case 1528:  /* avx_dpps256 */
    case 1527:  /* sse4_1_blendvpd */
    case 1526:  /* avx_blendvpd256 */
    case 1525:  /* sse4_1_blendvps */
    case 1524:  /* avx_blendvps256 */
    case 1523:  /* sse4_1_blendpd */
    case 1522:  /* avx_blendpd256 */
    case 1521:  /* sse4_1_blendps */
    case 1520:  /* avx_blendps256 */
    case 1501:  /* ssse3_palignrti */
    case 1500:  /* avx2_palignrv2ti */
    case 1496:  /* ssse3_psignv4si3 */
    case 1495:  /* avx2_psignv8si3 */
    case 1494:  /* ssse3_psignv8hi3 */
    case 1493:  /* avx2_psignv16hi3 */
    case 1492:  /* ssse3_psignv16qi3 */
    case 1491:  /* avx2_psignv32qi3 */
    case 1489:  /* ssse3_pshufbv16qi3 */
    case 1488:  /* avx2_pshufbv32qi3 */
    case 1486:  /* *ssse3_pmulhrswv8hi3 */
    case 1485:  /* *avx2_pmulhrswv16hi3 */
    case 1483:  /* ssse3_pmaddubsw128 */
    case 1479:  /* ssse3_phsubdv4si3 */
    case 1478:  /* ssse3_phadddv4si3 */
    case 1471:  /* ssse3_phsubswv8hi3 */
    case 1470:  /* ssse3_phsubwv8hi3 */
    case 1469:  /* ssse3_phaddswv8hi3 */
    case 1468:  /* ssse3_phaddwv8hi3 */
    case 1450:  /* sse2_psadbw */
    case 1449:  /* avx2_psadbw */
    case 1448:  /* *sse2_uavgv8hi3 */
    case 1447:  /* *avx2_uavgv16hi3 */
    case 1446:  /* *sse2_uavgv16qi3 */
    case 1445:  /* *avx2_uavgv32qi3 */
    case 1417:  /* vec_interleave_lowv4si */
    case 1415:  /* vec_interleave_highv4si */
    case 1413:  /* vec_interleave_lowv8hi */
    case 1411:  /* vec_interleave_highv8hi */
    case 1409:  /* vec_interleave_lowv16qi */
    case 1407:  /* vec_interleave_highv16qi */
    case 1405:  /* sse2_packuswb */
    case 1404:  /* avx2_packuswb */
    case 1403:  /* sse2_packssdw */
    case 1402:  /* avx2_packssdw */
    case 1401:  /* sse2_packsswb */
    case 1400:  /* avx2_packsswb */
    case 1399:  /* *xorv2di3 */
    case 1398:  /* *iorv2di3 */
    case 1397:  /* *andv2di3 */
    case 1396:  /* *xorv4di3 */
    case 1395:  /* *iorv4di3 */
    case 1394:  /* *andv4di3 */
    case 1393:  /* *xorv4si3 */
    case 1392:  /* *iorv4si3 */
    case 1391:  /* *andv4si3 */
    case 1390:  /* *xorv8si3 */
    case 1389:  /* *iorv8si3 */
    case 1388:  /* *andv8si3 */
    case 1387:  /* *xorv8hi3 */
    case 1386:  /* *iorv8hi3 */
    case 1385:  /* *andv8hi3 */
    case 1384:  /* *xorv16hi3 */
    case 1383:  /* *iorv16hi3 */
    case 1382:  /* *andv16hi3 */
    case 1381:  /* *xorv16qi3 */
    case 1380:  /* *iorv16qi3 */
    case 1379:  /* *andv16qi3 */
    case 1378:  /* *xorv32qi3 */
    case 1377:  /* *iorv32qi3 */
    case 1376:  /* *andv32qi3 */
    case 1375:  /* *andnotv2di3 */
    case 1374:  /* *andnotv4di3 */
    case 1373:  /* *andnotv4si3 */
    case 1372:  /* *andnotv8si3 */
    case 1371:  /* *andnotv8hi3 */
    case 1370:  /* *andnotv16hi3 */
    case 1369:  /* *andnotv16qi3 */
    case 1368:  /* *andnotv32qi3 */
    case 1367:  /* sse2_gtv4si3 */
    case 1366:  /* sse2_gtv8hi3 */
    case 1365:  /* sse2_gtv16qi3 */
    case 1360:  /* sse4_2_gtv2di3 */
    case 1359:  /* *sse2_eqv4si3 */
    case 1358:  /* *sse2_eqv8hi3 */
    case 1357:  /* *sse2_eqv16qi3 */
    case 1356:  /* *sse4_1_eqv2di3 */
    case 1351:  /* *uminv16qi3 */
    case 1350:  /* *umaxv16qi3 */
    case 1349:  /* *sse4_1_uminv4si3 */
    case 1348:  /* *sse4_1_umaxv4si3 */
    case 1347:  /* *sse4_1_uminv8hi3 */
    case 1346:  /* *sse4_1_umaxv8hi3 */
    case 1345:  /* *sminv8hi3 */
    case 1344:  /* *smaxv8hi3 */
    case 1343:  /* *sse4_1_sminv4si3 */
    case 1342:  /* *sse4_1_smaxv4si3 */
    case 1341:  /* *sse4_1_sminv16qi3 */
    case 1340:  /* *sse4_1_smaxv16qi3 */
    case 1327:  /* sse2_lshrv1ti3 */
    case 1326:  /* avx2_lshrv2ti3 */
    case 1325:  /* sse2_ashlv1ti3 */
    case 1324:  /* avx2_ashlv2ti3 */
    case 1323:  /* lshrv2di3 */
    case 1322:  /* ashlv2di3 */
    case 1321:  /* lshrv4di3 */
    case 1320:  /* ashlv4di3 */
    case 1319:  /* lshrv4si3 */
    case 1318:  /* ashlv4si3 */
    case 1317:  /* lshrv8si3 */
    case 1316:  /* ashlv8si3 */
    case 1315:  /* lshrv8hi3 */
    case 1314:  /* ashlv8hi3 */
    case 1313:  /* lshrv16hi3 */
    case 1312:  /* ashlv16hi3 */
    case 1311:  /* ashrv4si3 */
    case 1310:  /* ashrv8si3 */
    case 1309:  /* ashrv8hi3 */
    case 1308:  /* ashrv16hi3 */
    case 1307:  /* *sse4_1_mulv4si3 */
    case 1306:  /* *avx2_mulv8si3 */
    case 1305:  /* *sse2_pmaddwd */
    case 1303:  /* *sse4_1_mulv2siv2di3 */
    case 1301:  /* *vec_widen_umult_even_v4si */
    case 1299:  /* *umulv8hi3_highpart */
    case 1298:  /* *smulv8hi3_highpart */
    case 1297:  /* *umulv16hi3_highpart */
    case 1296:  /* *smulv16hi3_highpart */
    case 1295:  /* *mulv8hi3 */
    case 1294:  /* *mulv16hi3 */
    case 1293:  /* *sse2_ussubv8hi3 */
    case 1292:  /* *sse2_sssubv8hi3 */
    case 1291:  /* *sse2_usaddv8hi3 */
    case 1290:  /* *sse2_ssaddv8hi3 */
    case 1289:  /* *avx2_ussubv16hi3 */
    case 1288:  /* *avx2_sssubv16hi3 */
    case 1287:  /* *avx2_usaddv16hi3 */
    case 1286:  /* *avx2_ssaddv16hi3 */
    case 1285:  /* *sse2_ussubv16qi3 */
    case 1284:  /* *sse2_sssubv16qi3 */
    case 1283:  /* *sse2_usaddv16qi3 */
    case 1282:  /* *sse2_ssaddv16qi3 */
    case 1281:  /* *avx2_ussubv32qi3 */
    case 1280:  /* *avx2_sssubv32qi3 */
    case 1279:  /* *avx2_usaddv32qi3 */
    case 1278:  /* *avx2_ssaddv32qi3 */
    case 1277:  /* *subv2di3 */
    case 1276:  /* *addv2di3 */
    case 1275:  /* *subv4di3 */
    case 1274:  /* *addv4di3 */
    case 1273:  /* *subv4si3 */
    case 1272:  /* *addv4si3 */
    case 1271:  /* *subv8si3 */
    case 1270:  /* *addv8si3 */
    case 1269:  /* *subv8hi3 */
    case 1268:  /* *addv8hi3 */
    case 1267:  /* *subv16hi3 */
    case 1266:  /* *addv16hi3 */
    case 1265:  /* *subv16qi3 */
    case 1264:  /* *addv16qi3 */
    case 1263:  /* *subv32qi3 */
    case 1262:  /* *addv32qi3 */
    case 1252:  /* sse2_shufpd_v2df */
    case 1251:  /* sse2_shufpd_v2di */
    case 1250:  /* vec_interleave_lowv2di */
    case 1248:  /* vec_interleave_highv2di */
    case 1226:  /* sse4_1_insertps */
    case 1225:  /* *vec_setv4sf_sse4_1 */
    case 1215:  /* sse_movss */
    case 1210:  /* sse_shufps_v4sf */
    case 1209:  /* sse_shufps_v4si */
    case 1203:  /* vec_interleave_lowv4sf */
    case 1201:  /* vec_interleave_highv4sf */
    case 1113:  /* *xortf3 */
    case 1112:  /* *iortf3 */
    case 1111:  /* *andtf3 */
    case 1110:  /* *xordf3 */
    case 1109:  /* *iordf3 */
    case 1108:  /* *anddf3 */
    case 1107:  /* *xorsf3 */
    case 1106:  /* *iorsf3 */
    case 1105:  /* *andsf3 */
    case 1104:  /* *andnottf3 */
    case 1103:  /* *andnotdf3 */
    case 1102:  /* *andnotsf3 */
    case 1101:  /* *xorv2df3 */
    case 1100:  /* *iorv2df3 */
    case 1099:  /* *andv2df3 */
    case 1098:  /* *xorv4df3 */
    case 1097:  /* *iorv4df3 */
    case 1096:  /* *andv4df3 */
    case 1095:  /* *xorv4sf3 */
    case 1094:  /* *iorv4sf3 */
    case 1093:  /* *andv4sf3 */
    case 1092:  /* *xorv8sf3 */
    case 1091:  /* *iorv8sf3 */
    case 1090:  /* *andv8sf3 */
    case 1089:  /* sse2_andnotv2df3 */
    case 1088:  /* avx_andnotv4df3 */
    case 1087:  /* sse_andnotv4sf3 */
    case 1086:  /* avx_andnotv8sf3 */
    case 1081:  /* sse2_vmmaskcmpv2df3 */
    case 1080:  /* sse_vmmaskcmpv4sf3 */
    case 1079:  /* sse2_maskcmpv2df3 */
    case 1078:  /* avx_maskcmpv4df3 */
    case 1077:  /* sse_maskcmpv4sf3 */
    case 1076:  /* avx_maskcmpv8sf3 */
    case 1075:  /* *sse2_maskcmpv2df3_comm */
    case 1074:  /* *avx_maskcmpv4df3_comm */
    case 1073:  /* *sse_maskcmpv4sf3_comm */
    case 1072:  /* *avx_maskcmpv8sf3_comm */
    case 1065:  /* sse3_hsubv4sf3 */
    case 1064:  /* sse3_haddv4sf3 */
    case 1061:  /* *sse3_hsubv2df3_low */
    case 1060:  /* *sse3_haddv2df3_low */
    case 1059:  /* sse3_hsubv2df3 */
    case 1058:  /* *sse3_haddv2df3 */
    case 1055:  /* sse3_addsubv4sf3 */
    case 1053:  /* sse3_addsubv2df3 */
    case 1051:  /* *ieee_smaxv2df3 */
    case 1050:  /* *ieee_smaxv4df3 */
    case 1049:  /* *ieee_smaxv4sf3 */
    case 1048:  /* *ieee_smaxv8sf3 */
    case 1047:  /* *ieee_sminv2df3 */
    case 1046:  /* *ieee_sminv4df3 */
    case 1045:  /* *ieee_sminv4sf3 */
    case 1044:  /* *ieee_sminv8sf3 */
    case 1043:  /* sse2_vmsminv2df3 */
    case 1042:  /* sse2_vmsmaxv2df3 */
    case 1041:  /* sse_vmsminv4sf3 */
    case 1040:  /* sse_vmsmaxv4sf3 */
    case 1039:  /* *sminv2df3 */
    case 1038:  /* *smaxv2df3 */
    case 1037:  /* *sminv4df3 */
    case 1036:  /* *smaxv4df3 */
    case 1035:  /* *sminv4sf3 */
    case 1034:  /* *smaxv4sf3 */
    case 1033:  /* *sminv8sf3 */
    case 1032:  /* *smaxv8sf3 */
    case 1031:  /* *sminv2df3_finite */
    case 1030:  /* *smaxv2df3_finite */
    case 1029:  /* *sminv4df3_finite */
    case 1028:  /* *smaxv4df3_finite */
    case 1027:  /* *sminv4sf3_finite */
    case 1026:  /* *smaxv4sf3_finite */
    case 1025:  /* *sminv8sf3_finite */
    case 1024:  /* *smaxv8sf3_finite */
    case 1023:  /* sse_vmrsqrtv4sf2 */
    case 1020:  /* sse2_vmsqrtv2df2 */
    case 1019:  /* sse_vmsqrtv4sf2 */
    case 1014:  /* sse_vmrcpv4sf2 */
    case 1011:  /* sse2_vmdivv2df3 */
    case 1010:  /* sse_vmdivv4sf3 */
    case 1009:  /* sse2_divv2df3 */
    case 1008:  /* avx_divv4df3 */
    case 1007:  /* sse_divv4sf3 */
    case 1006:  /* avx_divv8sf3 */
    case 1005:  /* sse2_vmmulv2df3 */
    case 1004:  /* sse_vmmulv4sf3 */
    case 1003:  /* *mulv2df3 */
    case 1002:  /* *mulv4df3 */
    case 1001:  /* *mulv4sf3 */
    case 1000:  /* *mulv8sf3 */
    case 999:  /* sse2_vmsubv2df3 */
    case 998:  /* sse2_vmaddv2df3 */
    case 997:  /* sse_vmsubv4sf3 */
    case 996:  /* sse_vmaddv4sf3 */
    case 995:  /* *subv2df3 */
    case 994:  /* *addv2df3 */
    case 993:  /* *subv4df3 */
    case 992:  /* *addv4df3 */
    case 991:  /* *subv4sf3 */
    case 990:  /* *addv4sf3 */
    case 989:  /* *subv8sf3 */
    case 988:  /* *addv8sf3 */
    case 788:  /* *ieee_smindf3 */
    case 787:  /* *ieee_smaxdf3 */
    case 786:  /* *ieee_sminsf3 */
    case 785:  /* *ieee_smaxsf3 */
    case 784:  /* smindf3 */
    case 783:  /* smaxdf3 */
    case 782:  /* sminsf3 */
    case 781:  /* smaxsf3 */
    case 637:  /* *fop_df_1_sse */
    case 636:  /* *fop_sf_1_sse */
    case 630:  /* *fop_df_comm_sse */
    case 629:  /* *fop_sf_comm_sse */
    case 502:  /* setcc_df_sse */
    case 501:  /* setcc_sf_sse */
      extract_constrain_insn_cached (insn);
      if (which_alternative != 0)
        {
	  return 
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX);
        }
      else
        {
	  return 
#line 667 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(!TARGET_AVX);
        }

    case 488:  /* *rotrdi3_1 */
    case 487:  /* *rotldi3_1 */
    case 486:  /* *rotrsi3_1 */
    case 485:  /* *rotlsi3_1 */
    case 455:  /* *ashrdi3_1 */
    case 454:  /* *lshrdi3_1 */
    case 453:  /* *ashrsi3_1 */
    case 452:  /* *lshrsi3_1 */
      extract_constrain_insn_cached (insn);
      if (which_alternative != 0)
        {
	  return 
#line 670 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_BMI2);
        }
      else
        {
	  return 1;
        }

    case 430:  /* *ashldi3_1 */
    case 429:  /* *ashlsi3_1 */
      extract_constrain_insn_cached (insn);
      if (!((1 << which_alternative) & 0x3))
        {
	  return 
#line 670 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_BMI2);
        }
      else
        {
	  return 1;
        }

    case 306:  /* *umulsidi3_1 */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return 
#line 670 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_BMI2);
        }
      else
        {
	  return 1;
        }

    case 140:  /* *truncxfdf2_mixed */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 2)
        {
	  return 
#line 659 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SSE2);
        }
      else
        {
	  return 1;
        }

    case 136:  /* *truncdfsf_mixed */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 1)
        {
	  return 
#line 659 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SSE2);
        }
      else
        {
	  return 1;
        }

    case 117:  /* *zero_extendsidi2 */
      extract_constrain_insn_cached (insn);
      if (!((1 << which_alternative) & 0x3f))
        {
	  return 
#line 659 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SSE2);
        }
      else
        {
	  return 1;
        }

    case 112:  /* *movdf_internal */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x1e0))
        {
	  return 
#line 659 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SSE2);
        }
      else
        {
	  return 1;
        }

    case 108:  /* *pushdf */
      extract_constrain_insn_cached (insn);
      if (!((1 << which_alternative) & 0x3))
        {
	  return 
#line 659 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SSE2);
        }
      else
        {
	  return 1;
        }

    case 77:  /* *movdi_internal */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x61e0))
        {
	  return 
#line 659 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SSE2);
        }
      else if (((1 << which_alternative) & 0x1e00))
        {
	  return 
#line 667 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(!TARGET_AVX);
        }
      else
        {
	  return 1;
        }

    case -1:
      if (GET_CODE (PATTERN (insn)) != ASM_INPUT
          && asm_noperands (PATTERN (insn)) < 0)
        fatal_insn_not_found (insn);
      extract_constrain_insn_cached (insn);
      if ((cached_isa = get_attr_isa (insn)) == ISA_SSE2)
        {
	  return 
#line 659 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SSE2);
        }
      else if (cached_isa == ISA_SSE2_NOAVX)
        {
	  return 
#line 661 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SSE2 && !TARGET_AVX);
        }
      else if (cached_isa == ISA_SSE3)
        {
	  return 
#line 662 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SSE3);
        }
      else if (cached_isa == ISA_SSE4)
        {
	  return 
#line 663 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SSE4_1);
        }
      else if (cached_isa == ISA_SSE4_NOAVX)
        {
	  return 
#line 665 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SSE4_1 && !TARGET_AVX);
        }
      else if (cached_isa == ISA_AVX)
        {
	  return 
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX);
        }
      else if (cached_isa == ISA_NOAVX)
        {
	  return 
#line 667 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(!TARGET_AVX);
        }
      else if (cached_isa == ISA_AVX2)
        {
	  return 
#line 668 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX2);
        }
      else if (cached_isa == ISA_NOAVX2)
        {
	  return 
#line 669 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(!TARGET_AVX2);
        }
      else if (cached_isa == ISA_BMI2)
        {
	  return 
#line 670 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_BMI2);
        }
      else if (cached_isa == ISA_FMA4)
        {
	  return 
#line 671 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_FMA4);
        }
      else if (cached_isa == ISA_FMA)
        {
	  return 
#line 672 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_FMA);
        }
      else
        {
	  return 1;
        }

    default:
      return 1;

    }
}

enum attr_fp_int_src
get_attr_fp_int_src (rtx insn ATTRIBUTE_UNUSED)
{
  switch (recog_memoized (insn))
    {
    case 35:  /* *cmpsf_hi_i387 */
    case 36:  /* *cmpdf_hi_i387 */
    case 37:  /* *cmpxf_hi_i387 */
    case 38:  /* *cmpsf_si_i387 */
    case 39:  /* *cmpdf_si_i387 */
    case 40:  /* *cmpxf_si_i387 */
    case 41:  /* *cmpsf_hi_cc_i387 */
    case 42:  /* *cmpdf_hi_cc_i387 */
    case 43:  /* *cmpxf_hi_cc_i387 */
    case 44:  /* *cmpsf_si_cc_i387 */
    case 45:  /* *cmpdf_si_cc_i387 */
    case 46:  /* *cmpxf_si_cc_i387 */
    case 172:  /* *floathisf2_i387_with_temp */
    case 173:  /* *floathidf2_i387_with_temp */
    case 174:  /* *floathixf2_i387_with_temp */
    case 175:  /* *floathisf2_i387 */
    case 176:  /* *floathidf2_i387 */
    case 177:  /* *floathixf2_i387 */
    case 184:  /* *floatsisf2_vector_mixed_with_temp */
    case 185:  /* *floatsidf2_vector_mixed_with_temp */
    case 186:  /* *floatsisf2_vector_mixed */
    case 187:  /* *floatsidf2_vector_mixed */
    case 188:  /* *floatsisf2_mixed_with_temp */
    case 189:  /* *floatsidf2_mixed_with_temp */
    case 190:  /* *floatsisf2_mixed_interunit */
    case 191:  /* *floatdisf2_mixed_interunit */
    case 192:  /* *floatsidf2_mixed_interunit */
    case 193:  /* *floatdidf2_mixed_interunit */
    case 194:  /* *floatsisf2_mixed_nointerunit */
    case 195:  /* *floatdisf2_mixed_nointerunit */
    case 196:  /* *floatsidf2_mixed_nointerunit */
    case 197:  /* *floatdidf2_mixed_nointerunit */
    case 198:  /* *floatsisf2_vector_sse_with_temp */
    case 199:  /* *floatsidf2_vector_sse_with_temp */
    case 200:  /* *floatsisf2_vector_sse */
    case 201:  /* *floatsidf2_vector_sse */
    case 202:  /* *floatsisf2_sse_with_temp */
    case 203:  /* *floatsidf2_sse_with_temp */
    case 204:  /* *floatsisf2_sse_interunit */
    case 205:  /* *floatdisf2_sse_interunit */
    case 206:  /* *floatsidf2_sse_interunit */
    case 207:  /* *floatdidf2_sse_interunit */
    case 208:  /* *floatsisf2_sse_nointerunit */
    case 209:  /* *floatdisf2_sse_nointerunit */
    case 210:  /* *floatsidf2_sse_nointerunit */
    case 211:  /* *floatdidf2_sse_nointerunit */
    case 212:  /* *floatsisf2_i387_with_temp */
    case 213:  /* *floatsidf2_i387_with_temp */
    case 214:  /* *floatsixf2_i387_with_temp */
    case 215:  /* *floatdisf2_i387_with_temp */
    case 216:  /* *floatdidf2_i387_with_temp */
    case 217:  /* *floatdixf2_i387_with_temp */
    case 218:  /* *floatsisf2_i387 */
    case 219:  /* *floatsidf2_i387 */
    case 220:  /* *floatsixf2_i387 */
    case 221:  /* *floatdisf2_i387 */
    case 222:  /* *floatdidf2_i387 */
    case 223:  /* *floatdixf2_i387 */
    case 224:  /* floatdisf2_i387_with_xmm */
    case 225:  /* floatdidf2_i387_with_xmm */
    case 226:  /* floatdixf2_i387_with_xmm */
    case 640:  /* *fop_sf_2_i387 */
    case 641:  /* *fop_df_2_i387 */
    case 642:  /* *fop_sf_2_i387 */
    case 643:  /* *fop_df_2_i387 */
    case 644:  /* *fop_sf_3_i387 */
    case 645:  /* *fop_df_3_i387 */
    case 646:  /* *fop_sf_3_i387 */
    case 647:  /* *fop_df_3_i387 */
    case 653:  /* *fop_xf_2_i387 */
    case 654:  /* *fop_xf_2_i387 */
    case 655:  /* *fop_xf_3_i387 */
    case 656:  /* *fop_xf_3_i387 */
    case 1876:  /* loaddi_via_fpu */
      return FP_INT_SRC_TRUE;

    case -1:
      if (GET_CODE (PATTERN (insn)) != ASM_INPUT
          && asm_noperands (PATTERN (insn)) < 0)
        fatal_insn_not_found (insn);
    default:
      return FP_INT_SRC_FALSE;

    }
}

enum attr_i7_domain
get_attr_i7_domain (rtx insn ATTRIBUTE_UNUSED)
{
  enum attr_mode cached_mode ATTRIBUTE_UNUSED;
  enum attr_type cached_type ATTRIBUTE_UNUSED;

  switch (recog_memoized (insn))
    {
    case 1443:  /* *vec_concatv4si */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 2)
        {
	  return I7_DOMAIN_FLOAT;
        }
      else
        {
	  return I7_DOMAIN_SIMD;
        }

    case 1438:  /* *vec_dupv4si */
      extract_constrain_insn_cached (insn);
      if (which_alternative != 0)
        {
	  return I7_DOMAIN_FLOAT;
        }
      else
        {
	  return I7_DOMAIN_SIMD;
        }

    case 1444:  /* vec_concatv2di */
    case 1437:  /* *vec_extractv2di_1 */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 4)
        {
	  return I7_DOMAIN_FLOAT;
        }
      else
        {
	  return I7_DOMAIN_SIMD;
        }

    case 1439:  /* *vec_dupv2di */
    case 1433:  /* sse2_loadld */
      extract_constrain_insn_cached (insn);
      if (!((1 << which_alternative) & 0x3))
        {
	  return I7_DOMAIN_FLOAT;
        }
      else
        {
	  return I7_DOMAIN_SIMD;
        }

    case 1261:  /* *vec_concatv2df */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x67))
        {
	  return I7_DOMAIN_FLOAT;
        }
      else
        {
	  return I7_DOMAIN_SIMD;
        }

    case 1259:  /* sse2_movsd */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x23))
        {
	  return I7_DOMAIN_FLOAT;
        }
      else
        {
	  return I7_DOMAIN_SIMD;
        }

    case 1258:  /* sse2_loadlpd */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 9)
        {
	  return I7_DOMAIN_FLOAT;
        }
      else if (!((1 << which_alternative) & 0x600))
        {
	  if (!((1 << which_alternative) & 0xde))
	    {
	      return I7_DOMAIN_FLOAT;
	    }
	  else
	    {
	      return I7_DOMAIN_SIMD;
	    }
        }
      else
        {
	  return I7_DOMAIN_INT;
        }

    case 1257:  /* sse2_loadhpd */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 5)
        {
	  return I7_DOMAIN_FLOAT;
        }
      else if (((1 << which_alternative) & 0x1f))
        {
	  if (!((1 << which_alternative) & 0x3))
	    {
	      return I7_DOMAIN_FLOAT;
	    }
	  else
	    {
	      return I7_DOMAIN_SIMD;
	    }
        }
      else
        {
	  return I7_DOMAIN_INT;
        }

    case 1255:  /* sse2_storelpd */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 3)
        {
	  return I7_DOMAIN_FLOAT;
        }
      else if (((1 << which_alternative) & 0x7))
        {
	  if (which_alternative != 0)
	    {
	      return I7_DOMAIN_FLOAT;
	    }
	  else
	    {
	      return I7_DOMAIN_SIMD;
	    }
        }
      else
        {
	  return I7_DOMAIN_INT;
        }

    case 1253:  /* sse2_storehpd */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 4)
        {
	  return I7_DOMAIN_FLOAT;
        }
      else if (((1 << which_alternative) & 0xf))
        {
	  if (!((1 << which_alternative) & 0x3))
	    {
	      return I7_DOMAIN_FLOAT;
	    }
	  else
	    {
	      return I7_DOMAIN_SIMD;
	    }
        }
      else
        {
	  return I7_DOMAIN_INT;
        }

    case 1245:  /* *vec_interleave_lowv2df */
    case 1243:  /* *vec_interleave_highv2df */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x7))
        {
	  return I7_DOMAIN_FLOAT;
        }
      else
        {
	  return I7_DOMAIN_SIMD;
        }

    case 1228:  /* *sse4_1_extractps */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return I7_DOMAIN_FLOAT;
        }
      else
        {
	  return I7_DOMAIN_INT;
        }

    case 1224:  /* vec_setv4sf_0 */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 10)
        {
	  return I7_DOMAIN_FLOAT;
        }
      else if (!((1 << which_alternative) & 0x600))
        {
	  if (((1 << which_alternative) & 0x3b))
	    {
	      return I7_DOMAIN_FLOAT;
	    }
	  else if (which_alternative == 2)
	    {
	      return I7_DOMAIN_INT;
	    }
	  else
	    {
	      return I7_DOMAIN_SIMD;
	    }
        }
      else
        {
	  return I7_DOMAIN_INT;
        }

    case 1223:  /* vec_setv4si_0 */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 10)
        {
	  return I7_DOMAIN_FLOAT;
        }
      else if (!((1 << which_alternative) & 0x600))
        {
	  if (((1 << which_alternative) & 0x39))
	    {
	      return I7_DOMAIN_FLOAT;
	    }
	  else if (((1 << which_alternative) & 0x6))
	    {
	      return I7_DOMAIN_INT;
	    }
	  else
	    {
	      return I7_DOMAIN_SIMD;
	    }
        }
      else
        {
	  return I7_DOMAIN_INT;
        }

    case 1442:  /* *vec_concatv2si_sse */
    case 1221:  /* *vec_concatv2sf_sse */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return I7_DOMAIN_FLOAT;
        }
      else
        {
	  return I7_DOMAIN_SIMD;
        }

    case 1220:  /* *vec_concatv2sf_sse4_1 */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x1f))
        {
	  return I7_DOMAIN_FLOAT;
        }
      else
        {
	  return I7_DOMAIN_SIMD;
        }

    case 1219:  /* vec_dupv4sf */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 1)
        {
	  return I7_DOMAIN_FLOAT;
        }
      else
        {
	  return I7_DOMAIN_INT;
        }

    case 1214:  /* sse_loadlps */
      extract_constrain_insn_cached (insn);
      if (!((1 << which_alternative) & 0x3))
        {
	  return I7_DOMAIN_SIMD;
        }
      else
        {
	  return I7_DOMAIN_INT;
        }

    case 1212:  /* sse_loadhps */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0xc))
        {
	  return I7_DOMAIN_FLOAT;
        }
      else
        {
	  return I7_DOMAIN_SIMD;
        }

    case 1256:  /* *vec_extractv2df_0_sse */
    case 1254:  /* *vec_extractv2df_1_sse */
    case 1213:  /* sse_storelps */
    case 1211:  /* sse_storehps */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 1)
        {
	  return I7_DOMAIN_FLOAT;
        }
      else
        {
	  return I7_DOMAIN_SIMD;
        }

    case 1222:  /* *vec_concatv4sf */
    case 1199:  /* sse_movlhps */
    case 1198:  /* sse_movhlps */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return I7_DOMAIN_FLOAT;
        }
      else
        {
	  return I7_DOMAIN_SIMD;
        }

    case 973:  /* avx_storedqu256 */
      extract_constrain_insn_cached (insn);
      if (((
#line 6498 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_PACKED_SINGLE_INSN_OPTIMAL)) || (
#line 707 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_TYPELESS_STORES))) || (get_attr_mode (insn) == MODE_V4SF))
        {
	  return I7_DOMAIN_FLOAT;
        }
      else
        {
	  return I7_DOMAIN_SIMD;
        }

    case 972:  /* sse2_loaddqu */
      extract_constrain_insn_cached (insn);
      if ((
#line 6498 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_PACKED_SINGLE_INSN_OPTIMAL)) || ((! (
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX))) && (
#line 6508 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(optimize_function_for_size_p (cfun)))))
        {
	  return I7_DOMAIN_FLOAT;
        }
      else
        {
	  return I7_DOMAIN_SIMD;
        }

    case 971:  /* avx_loaddqu256 */
      extract_constrain_insn_cached (insn);
      if ((
#line 6498 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_PACKED_SINGLE_INSN_OPTIMAL)) || (get_attr_mode (insn) == MODE_V4SF))
        {
	  return I7_DOMAIN_FLOAT;
        }
      else
        {
	  return I7_DOMAIN_SIMD;
        }

    case 969:  /* avx_storeupd256 */
      extract_constrain_insn_cached (insn);
      if (((cached_mode = get_attr_mode (insn)) == MODE_V4DF) || (((
#line 6498 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_PACKED_SINGLE_INSN_OPTIMAL)) || (
#line 707 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_TYPELESS_STORES))) || (cached_mode == MODE_V4SF)))
        {
	  return I7_DOMAIN_FLOAT;
        }
      else
        {
	  return I7_DOMAIN_SIMD;
        }

    case 1110:  /* *xordf3 */
    case 1109:  /* *iordf3 */
    case 1108:  /* *anddf3 */
    case 1103:  /* *andnotdf3 */
    case 1101:  /* *xorv2df3 */
    case 1100:  /* *iorv2df3 */
    case 1099:  /* *andv2df3 */
    case 1089:  /* sse2_andnotv2df3 */
    case 966:  /* sse2_loadupd */
      extract_constrain_insn_cached (insn);
      if ((get_attr_mode (insn) == MODE_V2DF) || ((
#line 6498 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_PACKED_SINGLE_INSN_OPTIMAL)) || ((! (
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX))) && (
#line 6508 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(optimize_function_for_size_p (cfun))))))
        {
	  return I7_DOMAIN_FLOAT;
        }
      else
        {
	  return I7_DOMAIN_SIMD;
        }

    case 1098:  /* *xorv4df3 */
    case 1097:  /* *iorv4df3 */
    case 1096:  /* *andv4df3 */
    case 1088:  /* avx_andnotv4df3 */
    case 965:  /* avx_loadupd256 */
      extract_constrain_insn_cached (insn);
      if (((cached_mode = get_attr_mode (insn)) == MODE_V4DF) || ((
#line 6498 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_PACKED_SINGLE_INSN_OPTIMAL)) || (cached_mode == MODE_V4SF)))
        {
	  return I7_DOMAIN_FLOAT;
        }
      else
        {
	  return I7_DOMAIN_SIMD;
        }

    case 1092:  /* *xorv8sf3 */
    case 1091:  /* *iorv8sf3 */
    case 1090:  /* *andv8sf3 */
    case 1086:  /* avx_andnotv8sf3 */
    case 963:  /* avx_loadups256 */
      extract_constrain_insn_cached (insn);
      if (((
#line 6498 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_PACKED_SINGLE_INSN_OPTIMAL)) || ((
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX)) || (! (
#line 6508 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(optimize_function_for_size_p (cfun)))))) || (get_attr_mode (insn) == MODE_V4SF))
        {
	  return I7_DOMAIN_FLOAT;
        }
      else
        {
	  return I7_DOMAIN_SIMD;
        }

    case 970:  /* sse2_storeupd */
    case 960:  /* *movv2df_internal */
      if (((cached_mode = get_attr_mode (insn)) == MODE_V2DF) || (cached_mode == MODE_V4SF))
        {
	  return I7_DOMAIN_FLOAT;
        }
      else
        {
	  return I7_DOMAIN_SIMD;
        }

    case 959:  /* *movv4df_internal */
      extract_constrain_insn_cached (insn);
      if (((cached_mode = get_attr_mode (insn)) == MODE_V4DF) || (((
#line 6498 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_PACKED_SINGLE_INSN_OPTIMAL)) || ((which_alternative == 2) && (
#line 707 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_TYPELESS_STORES)))) || (cached_mode == MODE_V4SF)))
        {
	  return I7_DOMAIN_FLOAT;
        }
      else
        {
	  return I7_DOMAIN_SIMD;
        }

    case 1399:  /* *xorv2di3 */
    case 1398:  /* *iorv2di3 */
    case 1397:  /* *andv2di3 */
    case 1396:  /* *xorv4di3 */
    case 1395:  /* *iorv4di3 */
    case 1394:  /* *andv4di3 */
    case 1393:  /* *xorv4si3 */
    case 1392:  /* *iorv4si3 */
    case 1391:  /* *andv4si3 */
    case 1390:  /* *xorv8si3 */
    case 1389:  /* *iorv8si3 */
    case 1388:  /* *andv8si3 */
    case 1387:  /* *xorv8hi3 */
    case 1386:  /* *iorv8hi3 */
    case 1385:  /* *andv8hi3 */
    case 1384:  /* *xorv16hi3 */
    case 1383:  /* *iorv16hi3 */
    case 1382:  /* *andv16hi3 */
    case 1381:  /* *xorv16qi3 */
    case 1380:  /* *iorv16qi3 */
    case 1379:  /* *andv16qi3 */
    case 1378:  /* *xorv32qi3 */
    case 1377:  /* *iorv32qi3 */
    case 1376:  /* *andv32qi3 */
    case 1375:  /* *andnotv2di3 */
    case 1374:  /* *andnotv4di3 */
    case 1373:  /* *andnotv4si3 */
    case 1372:  /* *andnotv8si3 */
    case 1371:  /* *andnotv8hi3 */
    case 1370:  /* *andnotv16hi3 */
    case 1369:  /* *andnotv16qi3 */
    case 1368:  /* *andnotv32qi3 */
    case 967:  /* avx_storeups256 */
    case 957:  /* *movv8sf_internal */
      if (((cached_mode = get_attr_mode (insn)) == MODE_V8SF) || (cached_mode == MODE_V4SF))
        {
	  return I7_DOMAIN_FLOAT;
        }
      else
        {
	  return I7_DOMAIN_SIMD;
        }

    case 955:  /* *movv2ti_internal */
    case 953:  /* *movv4di_internal */
    case 951:  /* *movv8si_internal */
    case 949:  /* *movv16hi_internal */
    case 947:  /* *movv32qi_internal */
      extract_constrain_insn_cached (insn);
      if (((
#line 6498 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_PACKED_SINGLE_INSN_OPTIMAL)) || ((which_alternative == 2) && (
#line 707 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_TYPELESS_STORES)))) || (get_attr_mode (insn) == MODE_V4SF))
        {
	  return I7_DOMAIN_FLOAT;
        }
      else
        {
	  return I7_DOMAIN_SIMD;
        }

    case 938:  /* *vec_extractv2si_1 */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x2e))
        {
	  if (which_alternative == 3)
	    {
	      return I7_DOMAIN_FLOAT;
	    }
	  else if (!((1 << which_alternative) & 0xf))
	    {
	      return I7_DOMAIN_INT;
	    }
	  else
	    {
	      return I7_DOMAIN_SIMD;
	    }
        }
      else if (((1 << which_alternative) & 0x11))
        {
	  return I7_DOMAIN_SIMD;
        }
      else
        {
	  return I7_DOMAIN_INT;
        }

    case 868:  /* *vec_extractv2sf_1 */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 4)
        {
	  return I7_DOMAIN_FLOAT;
        }
      else if (((1 << which_alternative) & 0xa))
        {
	  return I7_DOMAIN_FLOAT;
        }
      else if (((1 << which_alternative) & 0x5))
        {
	  return I7_DOMAIN_SIMD;
        }
      else
        {
	  return I7_DOMAIN_INT;
        }

    case 840:  /* *movv2sf_internal */
      extract_constrain_insn_cached (insn);
      if (!((1 << which_alternative) & 0xc0f))
        {
	  if (((1 << which_alternative) & 0xc0))
	    {
	      return I7_DOMAIN_FLOAT;
	    }
	  else
	    {
	      return I7_DOMAIN_SIMD;
	    }
        }
      else if (((1 << which_alternative) & 0xf))
        {
	  return I7_DOMAIN_SIMD;
        }
      else
        {
	  return I7_DOMAIN_INT;
        }

    case 839:  /* *movv1di_internal */
    case 838:  /* *movv2si_internal */
    case 837:  /* *movv4hi_internal */
    case 836:  /* *movv8qi_internal */
      extract_constrain_insn_cached (insn);
      if (!((1 << which_alternative) & 0x600f))
        {
	  if (((1 << which_alternative) & 0x600))
	    {
	      return I7_DOMAIN_FLOAT;
	    }
	  else
	    {
	      return I7_DOMAIN_SIMD;
	    }
        }
      else if (((1 << which_alternative) & 0xf))
        {
	  return I7_DOMAIN_SIMD;
        }
      else
        {
	  return I7_DOMAIN_INT;
        }

    case 662:  /* *fop_xf_6_i387 */
    case 661:  /* *fop_xf_6_i387 */
    case 660:  /* *fop_xf_5_i387 */
    case 659:  /* *fop_xf_5_i387 */
    case 658:  /* *fop_xf_4_i387 */
    case 657:  /* *fop_xf_4_i387 */
    case 656:  /* *fop_xf_3_i387 */
    case 655:  /* *fop_xf_3_i387 */
    case 654:  /* *fop_xf_2_i387 */
    case 653:  /* *fop_xf_2_i387 */
    case 652:  /* *fop_xf_1_i387 */
    case 650:  /* *fop_df_6_i387 */
    case 649:  /* *fop_df_5_i387 */
    case 648:  /* *fop_df_4_i387 */
    case 647:  /* *fop_df_3_i387 */
    case 646:  /* *fop_sf_3_i387 */
    case 645:  /* *fop_df_3_i387 */
    case 644:  /* *fop_sf_3_i387 */
    case 643:  /* *fop_df_2_i387 */
    case 642:  /* *fop_sf_2_i387 */
    case 641:  /* *fop_df_2_i387 */
    case 640:  /* *fop_sf_2_i387 */
    case 639:  /* *fop_df_1_i387 */
    case 638:  /* *fop_sf_1_i387 */
      if (((cached_type = get_attr_type (insn)) == TYPE_FOP) || ((cached_type == TYPE_FMUL) || (cached_type == TYPE_FDIV)))
        {
	  return I7_DOMAIN_FLOAT;
        }
      else
        {
	  return I7_DOMAIN_INT;
        }

    case 637:  /* *fop_df_1_sse */
    case 636:  /* *fop_sf_1_sse */
      if (((cached_type = get_attr_type (insn)) == TYPE_SSEADD) || ((cached_type == TYPE_SSEMUL) || (cached_type == TYPE_SSEDIV)))
        {
	  return I7_DOMAIN_FLOAT;
        }
      else
        {
	  return I7_DOMAIN_INT;
        }

    case 651:  /* *fop_xf_comm_i387 */
    case 632:  /* *fop_df_comm_i387 */
    case 631:  /* *fop_sf_comm_i387 */
      if (((cached_type = get_attr_type (insn)) == TYPE_FOP) || (cached_type == TYPE_FMUL))
        {
	  return I7_DOMAIN_FLOAT;
        }
      else
        {
	  return I7_DOMAIN_INT;
        }

    case 630:  /* *fop_df_comm_sse */
    case 629:  /* *fop_sf_comm_sse */
      if (((cached_type = get_attr_type (insn)) == TYPE_SSEADD) || (cached_type == TYPE_SSEMUL))
        {
	  return I7_DOMAIN_FLOAT;
        }
      else
        {
	  return I7_DOMAIN_INT;
        }

    case 189:  /* *floatsidf2_mixed_with_temp */
    case 188:  /* *floatsisf2_mixed_with_temp */
    case 185:  /* *floatsidf2_vector_mixed_with_temp */
    case 184:  /* *floatsisf2_vector_mixed_with_temp */
      extract_constrain_insn_cached (insn);
      if (which_alternative != 1)
        {
	  return I7_DOMAIN_FLOAT;
        }
      else
        {
	  return I7_DOMAIN_INT;
        }

    case 217:  /* *floatdixf2_i387_with_temp */
    case 216:  /* *floatdidf2_i387_with_temp */
    case 215:  /* *floatdisf2_i387_with_temp */
    case 214:  /* *floatsixf2_i387_with_temp */
    case 213:  /* *floatsidf2_i387_with_temp */
    case 212:  /* *floatsisf2_i387_with_temp */
    case 174:  /* *floathixf2_i387_with_temp */
    case 173:  /* *floathidf2_i387_with_temp */
    case 172:  /* *floathisf2_i387_with_temp */
    case 140:  /* *truncxfdf2_mixed */
    case 139:  /* *truncxfsf2_mixed */
    case 137:  /* *truncdfsf_i387 */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return I7_DOMAIN_FLOAT;
        }
      else
        {
	  return I7_DOMAIN_INT;
        }

    case 778:  /* *movsfcc_1_387 */
    case 777:  /* *movdfcc_1 */
    case 136:  /* *truncdfsf_mixed */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return I7_DOMAIN_FLOAT;
        }
      else
        {
	  return I7_DOMAIN_INT;
        }

    case 128:  /* *extendsfdf2_mixed */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return I7_DOMAIN_FLOAT;
        }
      else
        {
	  return I7_DOMAIN_FLOAT;
        }

    case 117:  /* *zero_extendsidi2 */
      extract_constrain_insn_cached (insn);
      if (!((1 << which_alternative) & 0x1f))
        {
	  return I7_DOMAIN_SIMD;
        }
      else if (((1 << which_alternative) & 0x18))
        {
	  return I7_DOMAIN_SIMD;
        }
      else
        {
	  return I7_DOMAIN_INT;
        }

    case 113:  /* *movsf_internal */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x7))
        {
	  return I7_DOMAIN_FLOAT;
        }
      else if (!((1 << which_alternative) & 0xce1f))
        {
	  if (((cached_mode = get_attr_mode (insn)) == MODE_V4SF) || (cached_mode == MODE_SF))
	    {
	      return I7_DOMAIN_FLOAT;
	    }
	  else
	    {
	      return I7_DOMAIN_SIMD;
	    }
        }
      else if (((1 << which_alternative) & 0xce00))
        {
	  return I7_DOMAIN_SIMD;
        }
      else
        {
	  return I7_DOMAIN_INT;
        }

    case 111:  /* *movxf_internal */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x7))
        {
	  return I7_DOMAIN_FLOAT;
        }
      else
        {
	  return I7_DOMAIN_INT;
        }

    case 78:  /* *movsi_internal */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0xfc0))
        {
	  if ((get_attr_mode (insn) == MODE_V4SF) || ((((1 << which_alternative) & 0xf00)) && (! (
#line 659 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SSE2)))))
	    {
	      return I7_DOMAIN_FLOAT;
	    }
	  else if (!((1 << which_alternative) & 0xcc))
	    {
	      return I7_DOMAIN_INT;
	    }
	  else
	    {
	      return I7_DOMAIN_SIMD;
	    }
        }
      else if (((1 << which_alternative) & 0x3c))
        {
	  return I7_DOMAIN_SIMD;
        }
      else
        {
	  return I7_DOMAIN_INT;
        }

    case 77:  /* *movdi_internal */
      extract_constrain_insn_cached (insn);
      if (!((1 << which_alternative) & 0x1f))
        {
	  if (get_attr_mode (insn) == MODE_V4SF)
	    {
	      return I7_DOMAIN_FLOAT;
	    }
	  else
	    {
	      return I7_DOMAIN_SIMD;
	    }
        }
      else if (((1 << which_alternative) & 0x1c))
        {
	  return I7_DOMAIN_SIMD;
        }
      else
        {
	  return I7_DOMAIN_INT;
        }

    case 1113:  /* *xortf3 */
    case 1112:  /* *iortf3 */
    case 1111:  /* *andtf3 */
    case 1104:  /* *andnottf3 */
    case 974:  /* sse2_storedqu */
    case 958:  /* *movv4sf_internal */
    case 956:  /* *movv1ti_internal */
    case 954:  /* *movv2di_internal */
    case 952:  /* *movv4si_internal */
    case 950:  /* *movv8hi_internal */
    case 948:  /* *movv16qi_internal */
    case 110:  /* *movtf_internal_sse */
    case 76:  /* *movti_internal_sse */
      if (get_attr_mode (insn) == MODE_V4SF)
        {
	  return I7_DOMAIN_FLOAT;
        }
      else
        {
	  return I7_DOMAIN_SIMD;
        }

    case 75:  /* *movoi_internal_avx */
      extract_constrain_insn_cached (insn);
      if ((
#line 6498 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_PACKED_SINGLE_INSN_OPTIMAL)) || ((which_alternative == 2) && (
#line 707 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_TYPELESS_STORES))))
        {
	  return I7_DOMAIN_FLOAT;
        }
      else
        {
	  return I7_DOMAIN_SIMD;
        }

    case -1:
      if (GET_CODE (PATTERN (insn)) != ASM_INPUT
          && asm_noperands (PATTERN (insn)) < 0)
        fatal_insn_not_found (insn);
    case 112:  /* *movdf_internal */
    case 627:  /* *fop_sf_comm_mixed */
    case 628:  /* *fop_df_comm_mixed */
    case 633:  /* *fop_sf_1_mixed */
    case 634:  /* *fop_df_1_mixed */
      if (((cached_type = get_attr_type (insn)) == TYPE_FMOV) || ((cached_type == TYPE_FOP) || ((cached_type == TYPE_FSGN) || ((cached_type == TYPE_FMUL) || ((cached_type == TYPE_FDIV) || ((cached_type == TYPE_FPSPC) || ((cached_type == TYPE_FCMOV) || ((cached_type == TYPE_FCMP) || ((cached_type == TYPE_FXCH) || ((cached_type == TYPE_FISTP) || ((cached_type == TYPE_FISTTP) || (cached_type == TYPE_FRNDINT))))))))))))
        {
	  return I7_DOMAIN_FLOAT;
        }
      else if ((cached_type == TYPE_SSELOG) || ((cached_type == TYPE_SSELOG1) || ((cached_type == TYPE_SSEIADD) || ((cached_type == TYPE_SSEIADD1) || ((cached_type == TYPE_SSEISHFT) || ((cached_type == TYPE_SSEISHFT1) || ((cached_type == TYPE_SSEIMUL) || ((cached_type == TYPE_SSE) || ((cached_type == TYPE_SSEMOV) || ((cached_type == TYPE_SSEADD) || ((cached_type == TYPE_SSEADD1) || ((cached_type == TYPE_SSEMUL) || ((cached_type == TYPE_SSECMP) || ((cached_type == TYPE_SSECOMI) || ((cached_type == TYPE_SSECVT) || ((cached_type == TYPE_SSECVT1) || ((cached_type == TYPE_SSEICVT) || ((cached_type == TYPE_SSEDIV) || ((cached_type == TYPE_SSEINS) || ((cached_type == TYPE_SSEMULADD) || (cached_type == TYPE_SSE4ARG)))))))))))))))))))))
        {
	  if (((cached_mode = get_attr_mode (insn)) == MODE_V4DF) || ((cached_mode == MODE_V8SF) || ((cached_mode == MODE_V2DF) || ((cached_mode == MODE_V4SF) || ((cached_mode == MODE_SF) || (cached_mode == MODE_DF))))))
	    {
	      return I7_DOMAIN_FLOAT;
	    }
	  else if (cached_mode == MODE_SI)
	    {
	      return I7_DOMAIN_INT;
	    }
	  else
	    {
	      return I7_DOMAIN_SIMD;
	    }
        }
      else if ((cached_type == TYPE_MMX) || ((cached_type == TYPE_MMXMOV) || ((cached_type == TYPE_MMXADD) || ((cached_type == TYPE_MMXMUL) || ((cached_type == TYPE_MMXCMP) || ((cached_type == TYPE_MMXCVT) || (cached_type == TYPE_MMXSHFT)))))))
        {
	  return I7_DOMAIN_SIMD;
        }
      else
        {
	  return I7_DOMAIN_INT;
        }

    case 1869:  /* mfence_sse2 */
    case 1868:  /* *sse_sfence */
    case 1867:  /* *sse2_lfence */
    case 1864:  /* *avx2_gatherdiv8si_4 */
    case 1863:  /* *avx2_gatherdiv8si_4 */
    case 1860:  /* *avx2_gatherdiv8si_3 */
    case 1859:  /* *avx2_gatherdiv8si_3 */
    case 1856:  /* *avx2_gatherdiv8si_2 */
    case 1855:  /* *avx2_gatherdiv8si_2 */
    case 1852:  /* *avx2_gatherdiv4si_2 */
    case 1851:  /* *avx2_gatherdiv4si_2 */
    case 1848:  /* *avx2_gatherdiv4di_2 */
    case 1847:  /* *avx2_gatherdiv4di_2 */
    case 1844:  /* *avx2_gatherdiv2di_2 */
    case 1843:  /* *avx2_gatherdiv2di_2 */
    case 1840:  /* *avx2_gatherdiv8si */
    case 1839:  /* *avx2_gatherdiv8si */
    case 1836:  /* *avx2_gatherdiv4si */
    case 1835:  /* *avx2_gatherdiv4si */
    case 1832:  /* *avx2_gatherdiv4di */
    case 1831:  /* *avx2_gatherdiv4di */
    case 1828:  /* *avx2_gatherdiv2di */
    case 1827:  /* *avx2_gatherdiv2di */
    case 1824:  /* *avx2_gathersiv8si_2 */
    case 1823:  /* *avx2_gathersiv8si_2 */
    case 1820:  /* *avx2_gathersiv4si_2 */
    case 1819:  /* *avx2_gathersiv4si_2 */
    case 1816:  /* *avx2_gathersiv4di_2 */
    case 1815:  /* *avx2_gathersiv4di_2 */
    case 1812:  /* *avx2_gathersiv2di_2 */
    case 1811:  /* *avx2_gathersiv2di_2 */
    case 1808:  /* *avx2_gathersiv8si */
    case 1807:  /* *avx2_gathersiv8si */
    case 1804:  /* *avx2_gathersiv4si */
    case 1803:  /* *avx2_gathersiv4si */
    case 1800:  /* *avx2_gathersiv4di */
    case 1799:  /* *avx2_gathersiv4di */
    case 1796:  /* *avx2_gathersiv2di */
    case 1795:  /* *avx2_gathersiv2di */
    case 1786:  /* avx_vec_concatv4di */
    case 1785:  /* avx_vec_concatv8si */
    case 1784:  /* avx_vec_concatv16hi */
    case 1783:  /* avx_vec_concatv32qi */
    case 1782:  /* avx2_lshrvv2di */
    case 1781:  /* avx2_ashlvv2di */
    case 1780:  /* avx2_lshrvv4di */
    case 1779:  /* avx2_ashlvv4di */
    case 1778:  /* avx2_lshrvv4si */
    case 1777:  /* avx2_ashlvv4si */
    case 1776:  /* avx2_lshrvv8si */
    case 1775:  /* avx2_ashlvv8si */
    case 1774:  /* avx2_ashrvv4si */
    case 1773:  /* avx2_ashrvv8si */
    case 1769:  /* avx2_maskstoreq256 */
    case 1768:  /* avx2_maskstored256 */
    case 1767:  /* avx2_maskstoreq */
    case 1766:  /* avx2_maskstored */
    case 1761:  /* avx2_maskloadq256 */
    case 1760:  /* avx2_maskloadd256 */
    case 1759:  /* avx2_maskloadq */
    case 1758:  /* avx2_maskloadd */
    case 1753:  /* vec_set_hi_v32qi */
    case 1752:  /* vec_set_lo_v32qi */
    case 1751:  /* vec_set_hi_v16hi */
    case 1750:  /* vec_set_lo_v16hi */
    case 1748:  /* vec_set_hi_v8si */
    case 1746:  /* vec_set_lo_v8si */
    case 1744:  /* vec_set_hi_v4di */
    case 1742:  /* vec_set_lo_v4di */
    case 1741:  /* avx2_vec_set_hi_v4di */
    case 1740:  /* avx2_vec_set_lo_v4di */
    case 1737:  /* *avx_vperm2f128v8si_nozero */
    case 1734:  /* *avx_vperm2f128v8si_full */
    case 1720:  /* avx_vbroadcastf128_v4di */
    case 1719:  /* avx_vbroadcastf128_v8si */
    case 1718:  /* avx_vbroadcastf128_v16hi */
    case 1717:  /* avx_vbroadcastf128_v32qi */
    case 1716:  /* avx2_vbroadcasti128_v4di */
    case 1715:  /* avx2_vbroadcasti128_v8si */
    case 1714:  /* avx2_vbroadcasti128_v16hi */
    case 1713:  /* avx2_vbroadcasti128_v32qi */
    case 1707:  /* avx2_permv2ti */
    case 1705:  /* avx2_permv4di_1 */
    case 1704:  /* avx2_permvarv8sf */
    case 1703:  /* avx2_permvarv8si */
    case 1702:  /* avx2_pbroadcastv4di_1 */
    case 1701:  /* avx2_pbroadcastv8si_1 */
    case 1700:  /* avx2_pbroadcastv16hi_1 */
    case 1699:  /* avx2_pbroadcastv32qi_1 */
    case 1698:  /* avx2_pbroadcastv2di */
    case 1697:  /* avx2_pbroadcastv4di */
    case 1696:  /* avx2_pbroadcastv4si */
    case 1695:  /* avx2_pbroadcastv8si */
    case 1694:  /* avx2_pbroadcastv8hi */
    case 1693:  /* avx2_pbroadcastv16hi */
    case 1692:  /* avx2_pbroadcastv16qi */
    case 1691:  /* avx2_pbroadcastv32qi */
    case 1690:  /* avx_vzeroupper */
    case 1689:  /* *avx_vzeroall */
    case 1688:  /* pclmulqdq */
    case 1687:  /* aeskeygenassist */
    case 1686:  /* aesimc */
    case 1685:  /* aesdeclast */
    case 1684:  /* aesdec */
    case 1683:  /* aesenclast */
    case 1682:  /* aesenc */
    case 1677:  /* xop_pcom_tfv2di3 */
    case 1676:  /* xop_pcom_tfv4si3 */
    case 1675:  /* xop_pcom_tfv8hi3 */
    case 1674:  /* xop_pcom_tfv16qi3 */
    case 1673:  /* xop_maskcmp_uns2v2di3 */
    case 1672:  /* xop_maskcmp_uns2v4si3 */
    case 1671:  /* xop_maskcmp_uns2v8hi3 */
    case 1670:  /* xop_maskcmp_uns2v16qi3 */
    case 1669:  /* xop_maskcmp_unsv2di3 */
    case 1668:  /* xop_maskcmp_unsv4si3 */
    case 1667:  /* xop_maskcmp_unsv8hi3 */
    case 1666:  /* xop_maskcmp_unsv16qi3 */
    case 1665:  /* xop_maskcmpv2di3 */
    case 1664:  /* xop_maskcmpv4si3 */
    case 1663:  /* xop_maskcmpv8hi3 */
    case 1662:  /* xop_maskcmpv16qi3 */
    case 1653:  /* xop_shlv2di3 */
    case 1652:  /* xop_shlv4si3 */
    case 1651:  /* xop_shlv8hi3 */
    case 1650:  /* xop_shlv16qi3 */
    case 1649:  /* xop_shav2di3 */
    case 1648:  /* xop_shav4si3 */
    case 1647:  /* xop_shav8hi3 */
    case 1646:  /* xop_shav16qi3 */
    case 1645:  /* xop_vrotlv2di3 */
    case 1644:  /* xop_vrotlv4si3 */
    case 1643:  /* xop_vrotlv8hi3 */
    case 1642:  /* xop_vrotlv16qi3 */
    case 1641:  /* xop_rotrv2di3 */
    case 1640:  /* xop_rotrv4si3 */
    case 1639:  /* xop_rotrv8hi3 */
    case 1638:  /* xop_rotrv16qi3 */
    case 1637:  /* xop_rotlv2di3 */
    case 1636:  /* xop_rotlv4si3 */
    case 1635:  /* xop_rotlv8hi3 */
    case 1634:  /* xop_rotlv16qi3 */
    case 1633:  /* xop_pperm_pack_v8hi_v16qi */
    case 1632:  /* xop_pperm_pack_v4si_v8hi */
    case 1631:  /* xop_pperm_pack_v2di_v4si */
    case 1630:  /* xop_pperm */
    case 1629:  /* xop_phsubdq */
    case 1628:  /* xop_phsubwd */
    case 1627:  /* xop_phsubbw */
    case 1626:  /* xop_phaddudq */
    case 1625:  /* xop_phadddq */
    case 1624:  /* xop_phadduwq */
    case 1623:  /* xop_phaddwq */
    case 1622:  /* xop_phadduwd */
    case 1621:  /* xop_phaddwd */
    case 1620:  /* xop_phaddubq */
    case 1619:  /* xop_phaddbq */
    case 1618:  /* xop_phaddubd */
    case 1617:  /* xop_phaddbd */
    case 1616:  /* xop_phaddubw */
    case 1615:  /* xop_phaddbw */
    case 1614:  /* xop_pcmov_v2df */
    case 1613:  /* xop_pcmov_v4df256 */
    case 1612:  /* xop_pcmov_v4sf */
    case 1611:  /* xop_pcmov_v8sf256 */
    case 1610:  /* xop_pcmov_v2di */
    case 1609:  /* xop_pcmov_v4di256 */
    case 1608:  /* xop_pcmov_v4si */
    case 1607:  /* xop_pcmov_v8si256 */
    case 1606:  /* xop_pcmov_v8hi */
    case 1605:  /* xop_pcmov_v16hi256 */
    case 1604:  /* xop_pcmov_v16qi */
    case 1603:  /* xop_pcmov_v32qi256 */
    case 1602:  /* xop_pmadcsswd */
    case 1601:  /* xop_pmadcswd */
    case 1600:  /* xop_pmacsswd */
    case 1599:  /* xop_pmacswd */
    case 1598:  /* xop_pmacssdqh */
    case 1597:  /* xop_pmacsdqh */
    case 1596:  /* xop_pmacssdql */
    case 1595:  /* xop_pmacsdql */
    case 1594:  /* xop_pmacssdd */
    case 1593:  /* xop_pmacsdd */
    case 1592:  /* xop_pmacssww */
    case 1591:  /* xop_pmacsww */
    case 1590:  /* sse4_2_pcmpistr_cconly */
    case 1589:  /* sse4_2_pcmpistrm */
    case 1588:  /* sse4_2_pcmpistri */
    case 1587:  /* *sse4_2_pcmpistr_unaligned */
    case 1586:  /* sse4_2_pcmpistr */
    case 1585:  /* sse4_2_pcmpestr_cconly */
    case 1584:  /* sse4_2_pcmpestrm */
    case 1583:  /* sse4_2_pcmpestri */
    case 1582:  /* *sse4_2_pcmpestr_unaligned */
    case 1581:  /* sse4_2_pcmpestr */
    case 1574:  /* sse4_1_ptest */
    case 1573:  /* avx_ptest256 */
    case 1568:  /* sse4_1_zero_extendv2siv2di2 */
    case 1567:  /* sse4_1_sign_extendv2siv2di2 */
    case 1566:  /* avx2_zero_extendv4siv4di2 */
    case 1565:  /* avx2_sign_extendv4siv4di2 */
    case 1564:  /* sse4_1_zero_extendv2hiv2di2 */
    case 1563:  /* sse4_1_sign_extendv2hiv2di2 */
    case 1562:  /* avx2_zero_extendv4hiv4di2 */
    case 1561:  /* avx2_sign_extendv4hiv4di2 */
    case 1560:  /* sse4_1_zero_extendv2qiv2di2 */
    case 1559:  /* sse4_1_sign_extendv2qiv2di2 */
    case 1558:  /* avx2_zero_extendv4qiv4di2 */
    case 1557:  /* avx2_sign_extendv4qiv4di2 */
    case 1556:  /* sse4_1_zero_extendv4hiv4si2 */
    case 1555:  /* sse4_1_sign_extendv4hiv4si2 */
    case 1554:  /* avx2_zero_extendv8hiv8si2 */
    case 1553:  /* avx2_sign_extendv8hiv8si2 */
    case 1552:  /* sse4_1_zero_extendv4qiv4si2 */
    case 1551:  /* sse4_1_sign_extendv4qiv4si2 */
    case 1550:  /* avx2_zero_extendv8qiv8si2 */
    case 1549:  /* avx2_sign_extendv8qiv8si2 */
    case 1548:  /* sse4_1_zero_extendv8qiv8hi2 */
    case 1547:  /* sse4_1_sign_extendv8qiv8hi2 */
    case 1546:  /* avx2_zero_extendv16qiv16hi2 */
    case 1545:  /* avx2_sign_extendv16qiv16hi2 */
    case 1544:  /* sse4_1_phminposuw */
    case 1543:  /* avx2_pblenddv4si */
    case 1542:  /* avx2_pblenddv8si */
    case 1541:  /* *avx2_pblendw */
    case 1540:  /* sse4_1_pblendw */
    case 1539:  /* sse4_1_pblendvb */
    case 1538:  /* avx2_pblendvb */
    case 1537:  /* sse4_1_packusdw */
    case 1536:  /* avx2_packusdw */
    case 1535:  /* sse4_1_mpsadbw */
    case 1534:  /* avx2_mpsadbw */
    case 1533:  /* sse4_1_movntdqa */
    case 1532:  /* avx2_movntdqa */
    case 1519:  /* sse4a_insertq */
    case 1518:  /* sse4a_insertqi */
    case 1517:  /* sse4a_extrq */
    case 1516:  /* sse4a_extrqi */
    case 1511:  /* absv2si2 */
    case 1510:  /* absv4hi2 */
    case 1509:  /* absv8qi2 */
    case 1508:  /* absv4si2 */
    case 1507:  /* absv8si2 */
    case 1506:  /* absv8hi2 */
    case 1505:  /* absv16hi2 */
    case 1504:  /* absv16qi2 */
    case 1503:  /* absv32qi2 */
    case 1502:  /* ssse3_palignrdi */
    case 1501:  /* ssse3_palignrti */
    case 1500:  /* avx2_palignrv2ti */
    case 1499:  /* ssse3_psignv2si3 */
    case 1498:  /* ssse3_psignv4hi3 */
    case 1497:  /* ssse3_psignv8qi3 */
    case 1496:  /* ssse3_psignv4si3 */
    case 1495:  /* avx2_psignv8si3 */
    case 1494:  /* ssse3_psignv8hi3 */
    case 1493:  /* avx2_psignv16hi3 */
    case 1492:  /* ssse3_psignv16qi3 */
    case 1491:  /* avx2_psignv32qi3 */
    case 1490:  /* ssse3_pshufbv8qi3 */
    case 1489:  /* ssse3_pshufbv16qi3 */
    case 1488:  /* avx2_pshufbv32qi3 */
    case 1487:  /* *ssse3_pmulhrswv4hi3 */
    case 1486:  /* *ssse3_pmulhrswv8hi3 */
    case 1485:  /* *avx2_pmulhrswv16hi3 */
    case 1484:  /* ssse3_pmaddubsw */
    case 1483:  /* ssse3_pmaddubsw128 */
    case 1482:  /* avx2_pmaddubsw256 */
    case 1481:  /* ssse3_phsubdv2si3 */
    case 1480:  /* ssse3_phadddv2si3 */
    case 1479:  /* ssse3_phsubdv4si3 */
    case 1478:  /* ssse3_phadddv4si3 */
    case 1477:  /* avx2_phsubdv8si3 */
    case 1476:  /* avx2_phadddv8si3 */
    case 1475:  /* ssse3_phsubswv4hi3 */
    case 1474:  /* ssse3_phsubwv4hi3 */
    case 1473:  /* ssse3_phaddswv4hi3 */
    case 1472:  /* ssse3_phaddwv4hi3 */
    case 1471:  /* ssse3_phsubswv8hi3 */
    case 1470:  /* ssse3_phsubwv8hi3 */
    case 1469:  /* ssse3_phaddswv8hi3 */
    case 1468:  /* ssse3_phaddwv8hi3 */
    case 1467:  /* avx2_phsubswv16hi3 */
    case 1466:  /* avx2_phsubwv16hi3 */
    case 1465:  /* avx2_phaddswv16hi3 */
    case 1464:  /* avx2_phaddwv16hi3 */
    case 1461:  /* sse2_clflush */
    case 1460:  /* sse_stmxcsr */
    case 1459:  /* sse_ldmxcsr */
    case 1458:  /* *sse2_maskmovdqu */
    case 1457:  /* *sse2_maskmovdqu */
    case 1455:  /* avx2_pmovmskb */
    case 1450:  /* sse2_psadbw */
    case 1449:  /* avx2_psadbw */
    case 1448:  /* *sse2_uavgv8hi3 */
    case 1447:  /* *avx2_uavgv16hi3 */
    case 1446:  /* *sse2_uavgv16qi3 */
    case 1445:  /* *avx2_uavgv32qi3 */
    case 1441:  /* *vec_concatv2si_sse2 */
    case 1440:  /* *vec_concatv2si_sse4_1 */
    case 1432:  /* sse2_pshufhw_1 */
    case 1431:  /* avx2_pshufhw_1 */
    case 1430:  /* sse2_pshuflw_1 */
    case 1429:  /* avx2_pshuflw_1 */
    case 1428:  /* sse2_pshufd_1 */
    case 1427:  /* avx2_pshufd_1 */
    case 1426:  /* *sse4_1_pextrd */
    case 1425:  /* *sse4_1_pextrw_memory */
    case 1424:  /* *sse2_pextrw_si */
    case 1423:  /* *sse4_1_pextrb_memory */
    case 1422:  /* *sse4_1_pextrb_si */
    case 1421:  /* sse4_1_pinsrq */
    case 1420:  /* sse4_1_pinsrd */
    case 1419:  /* sse2_pinsrw */
    case 1418:  /* sse4_1_pinsrb */
    case 1417:  /* vec_interleave_lowv4si */
    case 1416:  /* avx2_interleave_lowv8si */
    case 1415:  /* vec_interleave_highv4si */
    case 1414:  /* avx2_interleave_highv8si */
    case 1413:  /* vec_interleave_lowv8hi */
    case 1412:  /* avx2_interleave_lowv16hi */
    case 1411:  /* vec_interleave_highv8hi */
    case 1410:  /* avx2_interleave_highv16hi */
    case 1409:  /* vec_interleave_lowv16qi */
    case 1408:  /* avx2_interleave_lowv32qi */
    case 1407:  /* vec_interleave_highv16qi */
    case 1406:  /* avx2_interleave_highv32qi */
    case 1405:  /* sse2_packuswb */
    case 1404:  /* avx2_packuswb */
    case 1403:  /* sse2_packssdw */
    case 1402:  /* avx2_packssdw */
    case 1401:  /* sse2_packsswb */
    case 1400:  /* avx2_packsswb */
    case 1367:  /* sse2_gtv4si3 */
    case 1366:  /* sse2_gtv8hi3 */
    case 1365:  /* sse2_gtv16qi3 */
    case 1364:  /* avx2_gtv4di3 */
    case 1363:  /* avx2_gtv8si3 */
    case 1362:  /* avx2_gtv16hi3 */
    case 1361:  /* avx2_gtv32qi3 */
    case 1360:  /* sse4_2_gtv2di3 */
    case 1359:  /* *sse2_eqv4si3 */
    case 1358:  /* *sse2_eqv8hi3 */
    case 1357:  /* *sse2_eqv16qi3 */
    case 1356:  /* *sse4_1_eqv2di3 */
    case 1355:  /* *avx2_eqv4di3 */
    case 1354:  /* *avx2_eqv8si3 */
    case 1353:  /* *avx2_eqv16hi3 */
    case 1352:  /* *avx2_eqv32qi3 */
    case 1351:  /* *uminv16qi3 */
    case 1350:  /* *umaxv16qi3 */
    case 1349:  /* *sse4_1_uminv4si3 */
    case 1348:  /* *sse4_1_umaxv4si3 */
    case 1347:  /* *sse4_1_uminv8hi3 */
    case 1346:  /* *sse4_1_umaxv8hi3 */
    case 1345:  /* *sminv8hi3 */
    case 1344:  /* *smaxv8hi3 */
    case 1343:  /* *sse4_1_sminv4si3 */
    case 1342:  /* *sse4_1_smaxv4si3 */
    case 1341:  /* *sse4_1_sminv16qi3 */
    case 1340:  /* *sse4_1_smaxv16qi3 */
    case 1339:  /* *avx2_uminv8si3 */
    case 1338:  /* *avx2_umaxv8si3 */
    case 1337:  /* *avx2_sminv8si3 */
    case 1336:  /* *avx2_smaxv8si3 */
    case 1335:  /* *avx2_uminv16hi3 */
    case 1334:  /* *avx2_umaxv16hi3 */
    case 1333:  /* *avx2_sminv16hi3 */
    case 1332:  /* *avx2_smaxv16hi3 */
    case 1331:  /* *avx2_uminv32qi3 */
    case 1330:  /* *avx2_umaxv32qi3 */
    case 1329:  /* *avx2_sminv32qi3 */
    case 1328:  /* *avx2_smaxv32qi3 */
    case 1327:  /* sse2_lshrv1ti3 */
    case 1326:  /* avx2_lshrv2ti3 */
    case 1325:  /* sse2_ashlv1ti3 */
    case 1324:  /* avx2_ashlv2ti3 */
    case 1323:  /* lshrv2di3 */
    case 1322:  /* ashlv2di3 */
    case 1321:  /* lshrv4di3 */
    case 1320:  /* ashlv4di3 */
    case 1319:  /* lshrv4si3 */
    case 1318:  /* ashlv4si3 */
    case 1317:  /* lshrv8si3 */
    case 1316:  /* ashlv8si3 */
    case 1315:  /* lshrv8hi3 */
    case 1314:  /* ashlv8hi3 */
    case 1313:  /* lshrv16hi3 */
    case 1312:  /* ashlv16hi3 */
    case 1311:  /* ashrv4si3 */
    case 1310:  /* ashrv8si3 */
    case 1309:  /* ashrv8hi3 */
    case 1308:  /* ashrv16hi3 */
    case 1307:  /* *sse4_1_mulv4si3 */
    case 1306:  /* *avx2_mulv8si3 */
    case 1305:  /* *sse2_pmaddwd */
    case 1304:  /* *avx2_pmaddwd */
    case 1303:  /* *sse4_1_mulv2siv2di3 */
    case 1302:  /* *vec_widen_smult_even_v8si */
    case 1301:  /* *vec_widen_umult_even_v4si */
    case 1300:  /* *vec_widen_umult_even_v8si */
    case 1299:  /* *umulv8hi3_highpart */
    case 1298:  /* *smulv8hi3_highpart */
    case 1297:  /* *umulv16hi3_highpart */
    case 1296:  /* *smulv16hi3_highpart */
    case 1295:  /* *mulv8hi3 */
    case 1294:  /* *mulv16hi3 */
    case 1293:  /* *sse2_ussubv8hi3 */
    case 1292:  /* *sse2_sssubv8hi3 */
    case 1291:  /* *sse2_usaddv8hi3 */
    case 1290:  /* *sse2_ssaddv8hi3 */
    case 1289:  /* *avx2_ussubv16hi3 */
    case 1288:  /* *avx2_sssubv16hi3 */
    case 1287:  /* *avx2_usaddv16hi3 */
    case 1286:  /* *avx2_ssaddv16hi3 */
    case 1285:  /* *sse2_ussubv16qi3 */
    case 1284:  /* *sse2_sssubv16qi3 */
    case 1283:  /* *sse2_usaddv16qi3 */
    case 1282:  /* *sse2_ssaddv16qi3 */
    case 1281:  /* *avx2_ussubv32qi3 */
    case 1280:  /* *avx2_sssubv32qi3 */
    case 1279:  /* *avx2_usaddv32qi3 */
    case 1278:  /* *avx2_ssaddv32qi3 */
    case 1277:  /* *subv2di3 */
    case 1276:  /* *addv2di3 */
    case 1275:  /* *subv4di3 */
    case 1274:  /* *addv4di3 */
    case 1273:  /* *subv4si3 */
    case 1272:  /* *addv4si3 */
    case 1271:  /* *subv8si3 */
    case 1270:  /* *addv8si3 */
    case 1269:  /* *subv8hi3 */
    case 1268:  /* *addv8hi3 */
    case 1267:  /* *subv16hi3 */
    case 1266:  /* *addv16hi3 */
    case 1265:  /* *subv16qi3 */
    case 1264:  /* *addv16qi3 */
    case 1263:  /* *subv32qi3 */
    case 1262:  /* *addv32qi3 */
    case 1250:  /* vec_interleave_lowv2di */
    case 1249:  /* avx2_interleave_lowv4di */
    case 1248:  /* vec_interleave_highv2di */
    case 1247:  /* avx2_interleave_highv4di */
    case 1241:  /* vec_extract_hi_v32qi */
    case 1239:  /* vec_extract_hi_v16hi */
    case 1236:  /* vec_extract_hi_v8si */
    case 1232:  /* vec_extract_hi_v4di */
    case 1190:  /* *sse2_cvttpd2dq */
    case 1189:  /* *avx_cvttpd2dq256_2 */
    case 1188:  /* fix_truncv4dfv4si2 */
    case 1187:  /* *sse2_cvtpd2dq */
    case 1186:  /* *avx_cvtpd2dq256_2 */
    case 1185:  /* avx_cvtpd2dq256 */
    case 1177:  /* sse2_cvttpd2pi */
    case 1176:  /* sse2_cvtpd2pi */
    case 1174:  /* fix_truncv4sfv4si2 */
    case 1173:  /* fix_truncv8sfv8si2 */
    case 1172:  /* sse2_cvtps2dq */
    case 1171:  /* avx_cvtps2dq256 */
    case 1163:  /* sse_cvtps2pi */
    case 983:  /* sse2_movntv2di */
    case 982:  /* avx_movntv4di */
    case 976:  /* sse3_lddqu */
    case 975:  /* avx_lddqu256 */
    case 961:  /* sse2_movq128 */
    case 946:  /* *mmx_femms */
    case 945:  /* *mmx_emms */
    case 944:  /* *mmx_maskmovq */
    case 943:  /* *mmx_maskmovq */
    case 942:  /* mmx_pmovmskb */
    case 941:  /* mmx_psadbw */
    case 940:  /* *mmx_uavgv4hi3 */
    case 939:  /* *mmx_uavgv8qi3 */
    case 936:  /* *mmx_concatv2si */
    case 935:  /* *vec_dupv2si */
    case 934:  /* *vec_dupv4hi */
    case 933:  /* mmx_pswapdv2si2 */
    case 932:  /* mmx_pshufw_1 */
    case 931:  /* mmx_pextrw */
    case 930:  /* *mmx_pinsrw */
    case 929:  /* mmx_punpckldq */
    case 928:  /* mmx_punpckhdq */
    case 927:  /* mmx_punpcklwd */
    case 926:  /* mmx_punpckhwd */
    case 925:  /* mmx_punpcklbw */
    case 924:  /* mmx_punpckhbw */
    case 923:  /* mmx_packuswb */
    case 922:  /* mmx_packssdw */
    case 921:  /* mmx_packsswb */
    case 920:  /* *mmx_xorv2si3 */
    case 919:  /* *mmx_iorv2si3 */
    case 918:  /* *mmx_andv2si3 */
    case 917:  /* *mmx_xorv4hi3 */
    case 916:  /* *mmx_iorv4hi3 */
    case 915:  /* *mmx_andv4hi3 */
    case 914:  /* *mmx_xorv8qi3 */
    case 913:  /* *mmx_iorv8qi3 */
    case 912:  /* *mmx_andv8qi3 */
    case 911:  /* mmx_andnotv2si3 */
    case 910:  /* mmx_andnotv4hi3 */
    case 909:  /* mmx_andnotv8qi3 */
    case 908:  /* mmx_gtv2si3 */
    case 907:  /* mmx_gtv4hi3 */
    case 906:  /* mmx_gtv8qi3 */
    case 905:  /* *mmx_eqv2si3 */
    case 904:  /* *mmx_eqv4hi3 */
    case 903:  /* *mmx_eqv8qi3 */
    case 902:  /* mmx_lshrv1di3 */
    case 901:  /* mmx_ashlv1di3 */
    case 900:  /* mmx_lshrv2si3 */
    case 899:  /* mmx_ashlv2si3 */
    case 898:  /* mmx_lshrv4hi3 */
    case 897:  /* mmx_ashlv4hi3 */
    case 896:  /* mmx_ashrv2si3 */
    case 895:  /* mmx_ashrv4hi3 */
    case 894:  /* *mmx_uminv8qi3 */
    case 893:  /* *mmx_umaxv8qi3 */
    case 892:  /* *mmx_sminv4hi3 */
    case 891:  /* *mmx_smaxv4hi3 */
    case 890:  /* *sse2_umulv1siv1di3 */
    case 889:  /* *mmx_pmulhrwv4hi3 */
    case 888:  /* *mmx_pmaddwd */
    case 887:  /* *mmx_umulv4hi3_highpart */
    case 886:  /* *mmx_smulv4hi3_highpart */
    case 885:  /* *mmx_mulv4hi3 */
    case 884:  /* *mmx_ussubv4hi3 */
    case 883:  /* *mmx_sssubv4hi3 */
    case 882:  /* *mmx_usaddv4hi3 */
    case 881:  /* *mmx_ssaddv4hi3 */
    case 880:  /* *mmx_ussubv8qi3 */
    case 879:  /* *mmx_sssubv8qi3 */
    case 878:  /* *mmx_usaddv8qi3 */
    case 877:  /* *mmx_ssaddv8qi3 */
    case 876:  /* *mmx_subv1di3 */
    case 875:  /* *mmx_addv1di3 */
    case 874:  /* *mmx_subv2si3 */
    case 873:  /* *mmx_addv2si3 */
    case 872:  /* *mmx_subv4hi3 */
    case 871:  /* *mmx_addv4hi3 */
    case 870:  /* *mmx_subv8qi3 */
    case 869:  /* *mmx_addv8qi3 */
    case 866:  /* *mmx_concatv2sf */
    case 865:  /* *vec_dupv2sf */
    case 864:  /* mmx_pswapdv2sf2 */
    case 863:  /* mmx_floatv2si2 */
    case 862:  /* mmx_pi2fw */
    case 861:  /* mmx_pf2iw */
    case 860:  /* mmx_pf2id */
    case 859:  /* mmx_gev2sf3 */
    case 858:  /* mmx_gtv2sf3 */
    case 857:  /* *mmx_eqv2sf3 */
    case 856:  /* mmx_addsubv2sf3 */
    case 855:  /* mmx_hsubv2sf3 */
    case 854:  /* mmx_haddv2sf3 */
    case 853:  /* mmx_rsqit1v2sf3 */
    case 852:  /* mmx_rsqrtv2sf2 */
    case 851:  /* mmx_rcpit2v2sf3 */
    case 850:  /* mmx_rcpit1v2sf3 */
    case 849:  /* mmx_rcpv2sf2 */
    case 848:  /* *mmx_sminv2sf3 */
    case 847:  /* *mmx_smaxv2sf3 */
    case 846:  /* *mmx_sminv2sf3_finite */
    case 845:  /* *mmx_smaxv2sf3_finite */
    case 844:  /* *mmx_mulv2sf3 */
    case 843:  /* *mmx_subv2sf3 */
    case 842:  /* *mmx_addv2sf3 */
    case 841:  /* sse_movntq */
    case 801:  /* *prefetch_3dnow */
    case 800:  /* *prefetch_sse */
    case 780:  /* *xop_pcmov_df */
    case 779:  /* *xop_pcmov_sf */
      return I7_DOMAIN_SIMD;

    case 1877:  /* storedi_via_fpu */
    case 1876:  /* loaddi_via_fpu */
    case 1866:  /* *avx2_gatherdiv8sf_4 */
    case 1865:  /* *avx2_gatherdiv8sf_4 */
    case 1862:  /* *avx2_gatherdiv8sf_3 */
    case 1861:  /* *avx2_gatherdiv8sf_3 */
    case 1858:  /* *avx2_gatherdiv8sf_2 */
    case 1857:  /* *avx2_gatherdiv8sf_2 */
    case 1854:  /* *avx2_gatherdiv4sf_2 */
    case 1853:  /* *avx2_gatherdiv4sf_2 */
    case 1850:  /* *avx2_gatherdiv4df_2 */
    case 1849:  /* *avx2_gatherdiv4df_2 */
    case 1846:  /* *avx2_gatherdiv2df_2 */
    case 1845:  /* *avx2_gatherdiv2df_2 */
    case 1842:  /* *avx2_gatherdiv8sf */
    case 1841:  /* *avx2_gatherdiv8sf */
    case 1838:  /* *avx2_gatherdiv4sf */
    case 1837:  /* *avx2_gatherdiv4sf */
    case 1834:  /* *avx2_gatherdiv4df */
    case 1833:  /* *avx2_gatherdiv4df */
    case 1830:  /* *avx2_gatherdiv2df */
    case 1829:  /* *avx2_gatherdiv2df */
    case 1826:  /* *avx2_gathersiv8sf_2 */
    case 1825:  /* *avx2_gathersiv8sf_2 */
    case 1822:  /* *avx2_gathersiv4sf_2 */
    case 1821:  /* *avx2_gathersiv4sf_2 */
    case 1818:  /* *avx2_gathersiv4df_2 */
    case 1817:  /* *avx2_gathersiv4df_2 */
    case 1814:  /* *avx2_gathersiv2df_2 */
    case 1813:  /* *avx2_gathersiv2df_2 */
    case 1810:  /* *avx2_gathersiv8sf */
    case 1809:  /* *avx2_gathersiv8sf */
    case 1806:  /* *avx2_gathersiv4sf */
    case 1805:  /* *avx2_gathersiv4sf */
    case 1802:  /* *avx2_gathersiv4df */
    case 1801:  /* *avx2_gathersiv4df */
    case 1798:  /* *avx2_gathersiv2df */
    case 1797:  /* *avx2_gathersiv2df */
    case 1794:  /* vcvtps2ph256 */
    case 1793:  /* *vcvtps2ph_store */
    case 1792:  /* *vcvtps2ph */
    case 1791:  /* vcvtph2ps256 */
    case 1790:  /* *vcvtph2ps_load */
    case 1789:  /* vcvtph2ps */
    case 1788:  /* avx_vec_concatv4df */
    case 1787:  /* avx_vec_concatv8sf */
    case 1765:  /* avx_maskstorepd256 */
    case 1764:  /* avx_maskstoreps256 */
    case 1763:  /* avx_maskstorepd */
    case 1762:  /* avx_maskstoreps */
    case 1757:  /* avx_maskloadpd256 */
    case 1756:  /* avx_maskloadps256 */
    case 1755:  /* avx_maskloadpd */
    case 1754:  /* avx_maskloadps */
    case 1749:  /* vec_set_hi_v8sf */
    case 1747:  /* vec_set_lo_v8sf */
    case 1745:  /* vec_set_hi_v4df */
    case 1743:  /* vec_set_lo_v4df */
    case 1739:  /* *avx_vperm2f128v4df_nozero */
    case 1738:  /* *avx_vperm2f128v8sf_nozero */
    case 1736:  /* *avx_vperm2f128v4df_full */
    case 1735:  /* *avx_vperm2f128v8sf_full */
    case 1733:  /* avx_vpermilvarv2df3 */
    case 1732:  /* avx_vpermilvarv4df3 */
    case 1731:  /* avx_vpermilvarv4sf3 */
    case 1730:  /* avx_vpermilvarv8sf3 */
    case 1729:  /* *avx_vpermilpv2df */
    case 1728:  /* *avx_vpermilpv4df */
    case 1727:  /* *avx_vpermilpv4sf */
    case 1726:  /* *avx_vpermilpv8sf */
    case 1723:  /* *avx_vperm_broadcast_v4sf */
    case 1722:  /* avx_vbroadcastf128_v4df */
    case 1721:  /* avx_vbroadcastf128_v8sf */
    case 1712:  /* vec_dupv4df */
    case 1711:  /* vec_dupv4di */
    case 1710:  /* vec_dupv8sf */
    case 1709:  /* vec_dupv8si */
    case 1708:  /* avx2_vec_dupv4df */
    case 1706:  /* avx2_permv4df_1 */
    case 1681:  /* xop_vpermil2v2df3 */
    case 1680:  /* xop_vpermil2v4df3 */
    case 1679:  /* xop_vpermil2v4sf3 */
    case 1678:  /* xop_vpermil2v8sf3 */
    case 1661:  /* *xop_vmfrcz_v2df */
    case 1660:  /* *xop_vmfrcz_v4sf */
    case 1659:  /* xop_frczv4df2 */
    case 1658:  /* xop_frczv8sf2 */
    case 1657:  /* xop_frczv2df2 */
    case 1656:  /* xop_frczv4sf2 */
    case 1655:  /* xop_frczdf2 */
    case 1654:  /* xop_frczsf2 */
    case 1580:  /* sse4_1_roundsd */
    case 1579:  /* sse4_1_roundss */
    case 1578:  /* sse4_1_roundpd */
    case 1577:  /* avx_roundpd256 */
    case 1576:  /* sse4_1_roundps */
    case 1575:  /* avx_roundps256 */
    case 1572:  /* avx_vtestpd */
    case 1571:  /* avx_vtestpd256 */
    case 1570:  /* avx_vtestps */
    case 1569:  /* avx_vtestps256 */
    case 1531:  /* sse4_1_dppd */
    case 1530:  /* avx_dppd256 */
    case 1529:  /* sse4_1_dpps */
    case 1528:  /* avx_dpps256 */
    case 1527:  /* sse4_1_blendvpd */
    case 1526:  /* avx_blendvpd256 */
    case 1525:  /* sse4_1_blendvps */
    case 1524:  /* avx_blendvps256 */
    case 1523:  /* sse4_1_blendpd */
    case 1522:  /* avx_blendpd256 */
    case 1521:  /* sse4_1_blendps */
    case 1520:  /* avx_blendps256 */
    case 1515:  /* sse4a_vmmovntv2df */
    case 1514:  /* sse4a_vmmovntv4sf */
    case 1513:  /* sse4a_movntdf */
    case 1512:  /* sse4a_movntsf */
    case 1454:  /* sse2_movmskpd */
    case 1453:  /* avx_movmskpd256 */
    case 1452:  /* sse_movmskps */
    case 1451:  /* avx_movmskps256 */
    case 1260:  /* vec_dupv2df */
    case 1244:  /* *avx_unpcklpd256 */
    case 1242:  /* avx_unpckhpd256 */
    case 1237:  /* vec_extract_hi_v8sf */
    case 1233:  /* vec_extract_hi_v4df */
    case 1226:  /* sse4_1_insertps */
    case 1225:  /* *vec_setv4sf_sse4_1 */
    case 1218:  /* avx2_vec_dupv8sf_1 */
    case 1217:  /* avx2_vec_dupv4sf */
    case 1216:  /* avx2_vec_dupv8sf */
    case 1215:  /* sse_movss */
    case 1207:  /* sse3_movsldup */
    case 1206:  /* avx_movsldup256 */
    case 1205:  /* sse3_movshdup */
    case 1204:  /* avx_movshdup256 */
    case 1203:  /* vec_interleave_lowv4sf */
    case 1202:  /* avx_unpcklps256 */
    case 1201:  /* vec_interleave_highv4sf */
    case 1200:  /* avx_unpckhps256 */
    case 1197:  /* sse2_cvtps2pd */
    case 1196:  /* *avx_cvtps2pd256_2 */
    case 1195:  /* avx_cvtps2pd256 */
    case 1194:  /* *sse2_cvtpd2ps */
    case 1193:  /* avx_cvtpd2ps256 */
    case 1192:  /* sse2_cvtss2sd */
    case 1191:  /* sse2_cvtsd2ss */
    case 1184:  /* sse2_cvtdq2pd */
    case 1183:  /* avx_cvtdq2pd256_2 */
    case 1182:  /* floatv4siv4df2 */
    case 1178:  /* sse2_cvtsi2sd */
    case 1175:  /* sse2_cvtpi2pd */
    case 1170:  /* floatv4siv4sf2 */
    case 1169:  /* floatv8siv8sf2 */
    case 1165:  /* sse_cvtsi2ss */
    case 1164:  /* sse_cvttps2pi */
    case 1162:  /* sse_cvtpi2ps */
    case 1161:  /* *fma4i_vmfnmsub_v2df */
    case 1160:  /* *fma4i_vmfnmsub_v4sf */
    case 1159:  /* *fma4i_vmfnmadd_v2df */
    case 1158:  /* *fma4i_vmfnmadd_v4sf */
    case 1157:  /* *fma4i_vmfmsub_v2df */
    case 1156:  /* *fma4i_vmfmsub_v4sf */
    case 1155:  /* *fma4i_vmfmadd_v2df */
    case 1154:  /* *fma4i_vmfmadd_v4sf */
    case 1153:  /* *fmai_fnmsub_v2df */
    case 1152:  /* *fmai_fnmsub_v4sf */
    case 1151:  /* *fmai_fnmadd_v2df */
    case 1150:  /* *fmai_fnmadd_v4sf */
    case 1149:  /* *fmai_fmsub_v2df */
    case 1148:  /* *fmai_fmsub_v4sf */
    case 1147:  /* *fmai_fmadd_v2df */
    case 1146:  /* *fmai_fmadd_v4sf */
    case 1145:  /* *fma_fmsubadd_v2df */
    case 1144:  /* *fma_fmsubadd_v4df */
    case 1143:  /* *fma_fmsubadd_v4sf */
    case 1142:  /* *fma_fmsubadd_v8sf */
    case 1141:  /* *fma_fmaddsub_v2df */
    case 1140:  /* *fma_fmaddsub_v4df */
    case 1139:  /* *fma_fmaddsub_v4sf */
    case 1138:  /* *fma_fmaddsub_v8sf */
    case 1137:  /* *fma_fnmsub_v4df */
    case 1136:  /* *fma_fnmsub_v8sf */
    case 1135:  /* *fma_fnmsub_v2df */
    case 1134:  /* *fma_fnmsub_v4sf */
    case 1133:  /* *fma_fnmsub_df */
    case 1132:  /* *fma_fnmsub_sf */
    case 1131:  /* *fma_fnmadd_v4df */
    case 1130:  /* *fma_fnmadd_v8sf */
    case 1129:  /* *fma_fnmadd_v2df */
    case 1128:  /* *fma_fnmadd_v4sf */
    case 1127:  /* *fma_fnmadd_df */
    case 1126:  /* *fma_fnmadd_sf */
    case 1125:  /* *fma_fmsub_v4df */
    case 1124:  /* *fma_fmsub_v8sf */
    case 1123:  /* *fma_fmsub_v2df */
    case 1122:  /* *fma_fmsub_v4sf */
    case 1121:  /* *fma_fmsub_df */
    case 1120:  /* *fma_fmsub_sf */
    case 1119:  /* *fma_fmadd_v4df */
    case 1118:  /* *fma_fmadd_v8sf */
    case 1117:  /* *fma_fmadd_v2df */
    case 1116:  /* *fma_fmadd_v4sf */
    case 1115:  /* *fma_fmadd_df */
    case 1114:  /* *fma_fmadd_sf */
    case 1107:  /* *xorsf3 */
    case 1106:  /* *iorsf3 */
    case 1105:  /* *andsf3 */
    case 1102:  /* *andnotsf3 */
    case 1095:  /* *xorv4sf3 */
    case 1094:  /* *iorv4sf3 */
    case 1093:  /* *andv4sf3 */
    case 1087:  /* sse_andnotv4sf3 */
    case 1085:  /* sse2_ucomi */
    case 1084:  /* sse_ucomi */
    case 1083:  /* sse2_comi */
    case 1082:  /* sse_comi */
    case 1081:  /* sse2_vmmaskcmpv2df3 */
    case 1080:  /* sse_vmmaskcmpv4sf3 */
    case 1079:  /* sse2_maskcmpv2df3 */
    case 1078:  /* avx_maskcmpv4df3 */
    case 1077:  /* sse_maskcmpv4sf3 */
    case 1076:  /* avx_maskcmpv8sf3 */
    case 1075:  /* *sse2_maskcmpv2df3_comm */
    case 1074:  /* *avx_maskcmpv4df3_comm */
    case 1073:  /* *sse_maskcmpv4sf3_comm */
    case 1072:  /* *avx_maskcmpv8sf3_comm */
    case 1071:  /* avx_vmcmpv2df3 */
    case 1070:  /* avx_vmcmpv4sf3 */
    case 1069:  /* avx_cmpv2df3 */
    case 1068:  /* avx_cmpv4df3 */
    case 1067:  /* avx_cmpv4sf3 */
    case 1066:  /* avx_cmpv8sf3 */
    case 1065:  /* sse3_hsubv4sf3 */
    case 1064:  /* sse3_haddv4sf3 */
    case 1063:  /* avx_hsubv8sf3 */
    case 1062:  /* avx_haddv8sf3 */
    case 1061:  /* *sse3_hsubv2df3_low */
    case 1060:  /* *sse3_haddv2df3_low */
    case 1059:  /* sse3_hsubv2df3 */
    case 1058:  /* *sse3_haddv2df3 */
    case 1057:  /* avx_hsubv4df3 */
    case 1056:  /* avx_haddv4df3 */
    case 1055:  /* sse3_addsubv4sf3 */
    case 1054:  /* avx_addsubv8sf3 */
    case 1053:  /* sse3_addsubv2df3 */
    case 1052:  /* avx_addsubv4df3 */
    case 1051:  /* *ieee_smaxv2df3 */
    case 1050:  /* *ieee_smaxv4df3 */
    case 1049:  /* *ieee_smaxv4sf3 */
    case 1048:  /* *ieee_smaxv8sf3 */
    case 1047:  /* *ieee_sminv2df3 */
    case 1046:  /* *ieee_sminv4df3 */
    case 1045:  /* *ieee_sminv4sf3 */
    case 1044:  /* *ieee_sminv8sf3 */
    case 1043:  /* sse2_vmsminv2df3 */
    case 1042:  /* sse2_vmsmaxv2df3 */
    case 1041:  /* sse_vmsminv4sf3 */
    case 1040:  /* sse_vmsmaxv4sf3 */
    case 1039:  /* *sminv2df3 */
    case 1038:  /* *smaxv2df3 */
    case 1037:  /* *sminv4df3 */
    case 1036:  /* *smaxv4df3 */
    case 1035:  /* *sminv4sf3 */
    case 1034:  /* *smaxv4sf3 */
    case 1033:  /* *sminv8sf3 */
    case 1032:  /* *smaxv8sf3 */
    case 1031:  /* *sminv2df3_finite */
    case 1030:  /* *smaxv2df3_finite */
    case 1029:  /* *sminv4df3_finite */
    case 1028:  /* *smaxv4df3_finite */
    case 1027:  /* *sminv4sf3_finite */
    case 1026:  /* *smaxv4sf3_finite */
    case 1025:  /* *sminv8sf3_finite */
    case 1024:  /* *smaxv8sf3_finite */
    case 1023:  /* sse_vmrsqrtv4sf2 */
    case 1022:  /* sse_rsqrtv4sf2 */
    case 1021:  /* avx_rsqrtv8sf2 */
    case 1020:  /* sse2_vmsqrtv2df2 */
    case 1019:  /* sse_vmsqrtv4sf2 */
    case 1018:  /* sse2_sqrtv2df2 */
    case 1017:  /* avx_sqrtv4df2 */
    case 1016:  /* sse_sqrtv4sf2 */
    case 1015:  /* avx_sqrtv8sf2 */
    case 1014:  /* sse_vmrcpv4sf2 */
    case 1013:  /* sse_rcpv4sf2 */
    case 1012:  /* avx_rcpv8sf2 */
    case 1011:  /* sse2_vmdivv2df3 */
    case 1010:  /* sse_vmdivv4sf3 */
    case 1009:  /* sse2_divv2df3 */
    case 1008:  /* avx_divv4df3 */
    case 1007:  /* sse_divv4sf3 */
    case 1006:  /* avx_divv8sf3 */
    case 1005:  /* sse2_vmmulv2df3 */
    case 1004:  /* sse_vmmulv4sf3 */
    case 1003:  /* *mulv2df3 */
    case 1002:  /* *mulv4df3 */
    case 1001:  /* *mulv4sf3 */
    case 1000:  /* *mulv8sf3 */
    case 999:  /* sse2_vmsubv2df3 */
    case 998:  /* sse2_vmaddv2df3 */
    case 997:  /* sse_vmsubv4sf3 */
    case 996:  /* sse_vmaddv4sf3 */
    case 995:  /* *subv2df3 */
    case 994:  /* *addv2df3 */
    case 993:  /* *subv4df3 */
    case 992:  /* *addv4df3 */
    case 991:  /* *subv4sf3 */
    case 990:  /* *addv4sf3 */
    case 989:  /* *subv8sf3 */
    case 988:  /* *addv8sf3 */
    case 981:  /* sse2_movntv2df */
    case 980:  /* avx_movntv4df */
    case 979:  /* sse_movntv4sf */
    case 978:  /* avx_movntv8sf */
    case 968:  /* sse_storeups */
    case 964:  /* sse_loadups */
    case 788:  /* *ieee_smindf3 */
    case 787:  /* *ieee_smaxdf3 */
    case 786:  /* *ieee_sminsf3 */
    case 785:  /* *ieee_smaxsf3 */
    case 784:  /* smindf3 */
    case 783:  /* smaxdf3 */
    case 782:  /* sminsf3 */
    case 781:  /* smaxsf3 */
    case 776:  /* *movxfcc_1 */
    case 742:  /* movmsk_df */
    case 736:  /* fistsi2_ceil_with_temp */
    case 735:  /* fistsi2_floor_with_temp */
    case 734:  /* fisthi2_ceil_with_temp */
    case 733:  /* fisthi2_floor_with_temp */
    case 732:  /* fistsi2_ceil */
    case 731:  /* fistsi2_floor */
    case 730:  /* fisthi2_ceil */
    case 729:  /* fisthi2_floor */
    case 728:  /* fistdi2_ceil_with_temp */
    case 727:  /* fistdi2_floor_with_temp */
    case 726:  /* fistdi2_ceil */
    case 725:  /* fistdi2_floor */
    case 724:  /* *fistdi2_ceil_1 */
    case 723:  /* *fistdi2_floor_1 */
    case 722:  /* *fistsi2_ceil_1 */
    case 721:  /* *fistsi2_floor_1 */
    case 720:  /* *fisthi2_ceil_1 */
    case 719:  /* *fisthi2_floor_1 */
    case 718:  /* frndintxf2_mask_pm_i387 */
    case 717:  /* frndintxf2_mask_pm */
    case 716:  /* frndintxf2_trunc_i387 */
    case 715:  /* frndintxf2_ceil_i387 */
    case 714:  /* frndintxf2_floor_i387 */
    case 713:  /* frndintxf2_trunc */
    case 712:  /* frndintxf2_ceil */
    case 711:  /* frndintxf2_floor */
    case 710:  /* fistsi2_with_temp */
    case 709:  /* fisthi2_with_temp */
    case 708:  /* fistsi2 */
    case 707:  /* fisthi2 */
    case 706:  /* *fistsi2_1 */
    case 705:  /* *fisthi2_1 */
    case 704:  /* fistdi2_with_temp */
    case 703:  /* fistdi2 */
    case 702:  /* *fistdi2_1 */
    case 701:  /* rintxf2 */
    case 700:  /* sse4_1_rounddf2 */
    case 699:  /* sse4_1_roundsf2 */
    case 698:  /* *fscalexf4_i387 */
    case 697:  /* *f2xm1xf2_i387 */
    case 696:  /* fxtract_extenddfxf3_i387 */
    case 695:  /* fxtract_extendsfxf3_i387 */
    case 694:  /* fxtractxf3_i387 */
    case 693:  /* fyl2xp1_extenddfxf3_i387 */
    case 692:  /* fyl2xp1_extendsfxf3_i387 */
    case 691:  /* fyl2xp1xf3_i387 */
    case 690:  /* fyl2x_extenddfxf3_i387 */
    case 689:  /* fyl2x_extendsfxf3_i387 */
    case 688:  /* fyl2xxf3_i387 */
    case 687:  /* fpatan_extenddfxf3_i387 */
    case 686:  /* fpatan_extendsfxf3_i387 */
    case 685:  /* *fpatanxf3_i387 */
    case 684:  /* fptan_extenddfxf4_i387 */
    case 683:  /* fptan_extendsfxf4_i387 */
    case 682:  /* fptanxf4_i387 */
    case 681:  /* sincos_extenddfxf3_i387 */
    case 680:  /* sincos_extendsfxf3_i387 */
    case 679:  /* sincosxf3 */
    case 678:  /* *cos_extenddfxf2_i387 */
    case 677:  /* *sin_extenddfxf2_i387 */
    case 676:  /* *cos_extendsfxf2_i387 */
    case 675:  /* *sin_extendsfxf2_i387 */
    case 674:  /* *cosxf2_i387 */
    case 673:  /* *sinxf2_i387 */
    case 672:  /* fprem1xf4_i387 */
    case 671:  /* fpremxf4_i387 */
    case 670:  /* *sqrtdf2_sse */
    case 669:  /* *sqrtsf2_sse */
    case 668:  /* *rsqrtsf2_sse */
    case 667:  /* sqrt_extenddfxf2_i387 */
    case 666:  /* sqrt_extendsfxf2_i387 */
    case 665:  /* sqrtxf2 */
    case 664:  /* truncxfdf2_i387_noop_unspec */
    case 663:  /* truncxfsf2_i387_noop_unspec */
    case 635:  /* *rcpsf2_sse */
    case 502:  /* setcc_df_sse */
    case 501:  /* setcc_sf_sse */
    case 409:  /* *negextenddfxf2 */
    case 408:  /* *absextenddfxf2 */
    case 407:  /* *negextendsfxf2 */
    case 406:  /* *absextendsfxf2 */
    case 405:  /* *negextendsfdf2 */
    case 404:  /* *absextendsfdf2 */
    case 403:  /* *negxf2_1 */
    case 402:  /* *absxf2_1 */
    case 401:  /* *negdf2_1 */
    case 400:  /* *absdf2_1 */
    case 399:  /* *negsf2_1 */
    case 398:  /* *abssf2_1 */
    case 223:  /* *floatdixf2_i387 */
    case 222:  /* *floatdidf2_i387 */
    case 221:  /* *floatdisf2_i387 */
    case 220:  /* *floatsixf2_i387 */
    case 219:  /* *floatsidf2_i387 */
    case 218:  /* *floatsisf2_i387 */
    case 211:  /* *floatdidf2_sse_nointerunit */
    case 210:  /* *floatsidf2_sse_nointerunit */
    case 209:  /* *floatdisf2_sse_nointerunit */
    case 208:  /* *floatsisf2_sse_nointerunit */
    case 207:  /* *floatdidf2_sse_interunit */
    case 206:  /* *floatsidf2_sse_interunit */
    case 205:  /* *floatdisf2_sse_interunit */
    case 204:  /* *floatsisf2_sse_interunit */
    case 203:  /* *floatsidf2_sse_with_temp */
    case 202:  /* *floatsisf2_sse_with_temp */
    case 201:  /* *floatsidf2_vector_sse */
    case 200:  /* *floatsisf2_vector_sse */
    case 199:  /* *floatsidf2_vector_sse_with_temp */
    case 198:  /* *floatsisf2_vector_sse_with_temp */
    case 197:  /* *floatdidf2_mixed_nointerunit */
    case 196:  /* *floatsidf2_mixed_nointerunit */
    case 195:  /* *floatdisf2_mixed_nointerunit */
    case 194:  /* *floatsisf2_mixed_nointerunit */
    case 193:  /* *floatdidf2_mixed_interunit */
    case 192:  /* *floatsidf2_mixed_interunit */
    case 191:  /* *floatdisf2_mixed_interunit */
    case 190:  /* *floatsisf2_mixed_interunit */
    case 187:  /* *floatsidf2_vector_mixed */
    case 186:  /* *floatsisf2_vector_mixed */
    case 177:  /* *floathixf2_i387 */
    case 176:  /* *floathidf2_i387 */
    case 175:  /* *floathisf2_i387 */
    case 166:  /* fix_truncsi_i387_with_temp */
    case 165:  /* fix_trunchi_i387_with_temp */
    case 164:  /* fix_truncsi_i387 */
    case 163:  /* fix_trunchi_i387 */
    case 162:  /* fix_truncdi_i387_with_temp */
    case 161:  /* fix_truncdi_i387 */
    case 160:  /* *fix_truncdi_i387_1 */
    case 159:  /* *fix_truncsi_i387_1 */
    case 158:  /* *fix_trunchi_i387_1 */
    case 157:  /* fix_truncdi_i387_fisttp_with_temp */
    case 156:  /* fix_truncsi_i387_fisttp_with_temp */
    case 155:  /* fix_trunchi_i387_fisttp_with_temp */
    case 154:  /* fix_truncdi_i387_fisttp */
    case 153:  /* fix_truncsi_i387_fisttp */
    case 152:  /* fix_trunchi_i387_fisttp */
    case 151:  /* fix_truncdi_fisttp_i387_1 */
    case 150:  /* fix_truncsi_fisttp_i387_1 */
    case 149:  /* fix_trunchi_fisttp_i387_1 */
    case 148:  /* fix_truncdfsi_sse */
    case 147:  /* fix_truncsfsi_sse */
    case 144:  /* *truncxfdf2_i387 */
    case 143:  /* *truncxfsf2_i387 */
    case 142:  /* truncxfdf2_i387_noop */
    case 141:  /* truncxfsf2_i387_noop */
    case 138:  /* *truncdfsf2_i387_1 */
    case 135:  /* *truncdfsf_fast_i387 */
    case 134:  /* *truncdfsf_fast_sse */
    case 133:  /* *truncdfsf_fast_mixed */
    case 132:  /* *extenddfxf2_i387 */
    case 131:  /* *extendsfxf2_i387 */
    case 130:  /* *extendsfdf2_i387 */
    case 129:  /* *extendsfdf2_sse */
    case 116:  /* *swapdf */
    case 115:  /* *swapsf */
    case 114:  /* swapxf */
    case 62:  /* *cmpiuxf_i387 */
    case 61:  /* *cmpiudf_i387 */
    case 60:  /* *cmpiusf_i387 */
    case 59:  /* *cmpixf_i387 */
    case 58:  /* *cmpidf_i387 */
    case 57:  /* *cmpisf_i387 */
    case 56:  /* *cmpiudf_sse */
    case 55:  /* *cmpiusf_sse */
    case 54:  /* *cmpidf_sse */
    case 53:  /* *cmpisf_sse */
    case 52:  /* *cmpiudf_mixed */
    case 51:  /* *cmpiusf_mixed */
    case 50:  /* *cmpidf_mixed */
    case 49:  /* *cmpisf_mixed */
      return I7_DOMAIN_FLOAT;

    default:
      return I7_DOMAIN_INT;

    }
}

enum attr_isa
get_attr_isa (rtx insn ATTRIBUTE_UNUSED)
{
  switch (recog_memoized (insn))
    {
    case 1444:  /* vec_concatv2di */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return ISA_SSE2;
        }
      else if (which_alternative == 2)
        {
	  return ISA_SSE2_NOAVX;
        }
      else if (which_alternative == 3)
        {
	  return ISA_AVX;
        }
      else if (((1 << which_alternative) & 0x30))
        {
	  return ISA_NOAVX;
        }
      else
        {
	  return ISA_AVX;
        }

    case 1443:  /* *vec_concatv4si */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return ISA_SSE2_NOAVX;
        }
      else if (which_alternative == 1)
        {
	  return ISA_AVX;
        }
      else if (((1 << which_alternative) & 0xc))
        {
	  return ISA_NOAVX;
        }
      else
        {
	  return ISA_AVX;
        }

    case 1437:  /* *vec_extractv2di_1 */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return ISA_BASE;
        }
      else if (which_alternative == 1)
        {
	  return ISA_SSE2_NOAVX;
        }
      else if (which_alternative == 2)
        {
	  return ISA_AVX;
        }
      else if (which_alternative == 3)
        {
	  return ISA_SSE2;
        }
      else
        {
	  return ISA_NOAVX;
        }

    case 1433:  /* sse2_loadld */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return ISA_SSE2;
        }
      else if (which_alternative == 1)
        {
	  return ISA_BASE;
        }
      else if (((1 << which_alternative) & 0xc))
        {
	  return ISA_NOAVX;
        }
      else
        {
	  return ISA_AVX;
        }

    case 1261:  /* *vec_concatv2df */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return ISA_SSE2_NOAVX;
        }
      else if (which_alternative == 1)
        {
	  return ISA_AVX;
        }
      else if (which_alternative == 2)
        {
	  return ISA_SSE3;
        }
      else if (which_alternative == 3)
        {
	  return ISA_SSE2_NOAVX;
        }
      else if (which_alternative == 4)
        {
	  return ISA_AVX;
        }
      else if (which_alternative == 5)
        {
	  return ISA_SSE2;
        }
      else
        {
	  return ISA_NOAVX;
        }

    case 1259:  /* sse2_movsd */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return ISA_NOAVX;
        }
      else if (which_alternative == 1)
        {
	  return ISA_AVX;
        }
      else if (which_alternative == 2)
        {
	  return ISA_NOAVX;
        }
      else if (which_alternative == 3)
        {
	  return ISA_AVX;
        }
      else if (which_alternative == 4)
        {
	  return ISA_BASE;
        }
      else if (((1 << which_alternative) & 0x60))
        {
	  return ISA_NOAVX;
        }
      else if (which_alternative == 7)
        {
	  return ISA_AVX;
        }
      else
        {
	  return ISA_BASE;
        }

    case 1258:  /* sse2_loadlpd */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return ISA_BASE;
        }
      else if (which_alternative == 1)
        {
	  return ISA_NOAVX;
        }
      else if (which_alternative == 2)
        {
	  return ISA_AVX;
        }
      else if (which_alternative == 3)
        {
	  return ISA_NOAVX;
        }
      else if (which_alternative == 4)
        {
	  return ISA_AVX;
        }
      else if (((1 << which_alternative) & 0x60))
        {
	  return ISA_NOAVX;
        }
      else if (which_alternative == 7)
        {
	  return ISA_AVX;
        }
      else
        {
	  return ISA_BASE;
        }

    case 1253:  /* sse2_storehpd */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return ISA_BASE;
        }
      else if (which_alternative == 1)
        {
	  return ISA_NOAVX;
        }
      else if (which_alternative == 2)
        {
	  return ISA_AVX;
        }
      else
        {
	  return ISA_BASE;
        }

    case 1224:  /* vec_setv4sf_0 */
    case 1223:  /* vec_setv4si_0 */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return ISA_SSE4;
        }
      else if (((1 << which_alternative) & 0x6))
        {
	  return ISA_SSE2;
        }
      else if (((1 << which_alternative) & 0x18))
        {
	  return ISA_NOAVX;
        }
      else if (which_alternative == 5)
        {
	  return ISA_AVX;
        }
      else if (which_alternative == 6)
        {
	  return ISA_SSE4_NOAVX;
        }
      else if (which_alternative == 7)
        {
	  return ISA_AVX;
        }
      else
        {
	  return ISA_BASE;
        }

    case 1219:  /* vec_dupv4sf */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return ISA_AVX;
        }
      else
        {
	  return ISA_NOAVX;
        }

    case 1145:  /* *fma_fmsubadd_v2df */
    case 1144:  /* *fma_fmsubadd_v4df */
    case 1143:  /* *fma_fmsubadd_v4sf */
    case 1142:  /* *fma_fmsubadd_v8sf */
    case 1141:  /* *fma_fmaddsub_v2df */
    case 1140:  /* *fma_fmaddsub_v4df */
    case 1139:  /* *fma_fmaddsub_v4sf */
    case 1138:  /* *fma_fmaddsub_v8sf */
    case 1137:  /* *fma_fnmsub_v4df */
    case 1136:  /* *fma_fnmsub_v8sf */
    case 1135:  /* *fma_fnmsub_v2df */
    case 1134:  /* *fma_fnmsub_v4sf */
    case 1133:  /* *fma_fnmsub_df */
    case 1132:  /* *fma_fnmsub_sf */
    case 1131:  /* *fma_fnmadd_v4df */
    case 1130:  /* *fma_fnmadd_v8sf */
    case 1129:  /* *fma_fnmadd_v2df */
    case 1128:  /* *fma_fnmadd_v4sf */
    case 1127:  /* *fma_fnmadd_df */
    case 1126:  /* *fma_fnmadd_sf */
    case 1125:  /* *fma_fmsub_v4df */
    case 1124:  /* *fma_fmsub_v8sf */
    case 1123:  /* *fma_fmsub_v2df */
    case 1122:  /* *fma_fmsub_v4sf */
    case 1121:  /* *fma_fmsub_df */
    case 1120:  /* *fma_fmsub_sf */
    case 1119:  /* *fma_fmadd_v4df */
    case 1118:  /* *fma_fmadd_v8sf */
    case 1117:  /* *fma_fmadd_v2df */
    case 1116:  /* *fma_fmadd_v4sf */
    case 1115:  /* *fma_fmadd_df */
    case 1114:  /* *fma_fmadd_sf */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x7))
        {
	  return ISA_FMA;
        }
      else
        {
	  return ISA_FMA4;
        }

    case 1421:  /* sse4_1_pinsrq */
    case 1420:  /* sse4_1_pinsrd */
    case 1419:  /* sse2_pinsrw */
    case 1418:  /* sse4_1_pinsrb */
    case 1192:  /* sse2_cvtss2sd */
    case 1191:  /* sse2_cvtsd2ss */
    case 1178:  /* sse2_cvtsi2sd */
    case 1165:  /* sse_cvtsi2ss */
    case 987:  /* *absnegv2df2 */
    case 986:  /* *absnegv4df2 */
    case 985:  /* *absnegv4sf2 */
    case 984:  /* *absnegv8sf2 */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return ISA_NOAVX;
        }
      else
        {
	  return ISA_AVX;
        }

    case 634:  /* *fop_df_1_mixed */
    case 633:  /* *fop_sf_1_mixed */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return ISA_BASE;
        }
      else if (which_alternative == 2)
        {
	  return ISA_NOAVX;
        }
      else
        {
	  return ISA_AVX;
        }

    case 430:  /* *ashldi3_1 */
    case 429:  /* *ashlsi3_1 */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return ISA_BASE;
        }
      else
        {
	  return ISA_BMI2;
        }

    case 140:  /* *truncxfdf2_mixed */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return ISA_BASE;
        }
      else if (which_alternative == 2)
        {
	  return ISA_SSE2;
        }
      else
        {
	  return ISA_BASE;
        }

    case 136:  /* *truncdfsf_mixed */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return ISA_BASE;
        }
      else if (which_alternative == 1)
        {
	  return ISA_SSE2;
        }
      else
        {
	  return ISA_BASE;
        }

    case 117:  /* *zero_extendsidi2 */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3f))
        {
	  return ISA_BASE;
        }
      else
        {
	  return ISA_SSE2;
        }

    case 108:  /* *pushdf */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return ISA_BASE;
        }
      else
        {
	  return ISA_SSE2;
        }

    case 77:  /* *movdi_internal */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x61e0))
        {
	  return ISA_SSE2;
        }
      else if (((1 << which_alternative) & 0x1e00))
        {
	  return ISA_NOAVX;
        }
      else
        {
	  return ISA_BASE;
        }

    case 112:  /* *movdf_internal */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x1e0))
        {
	  return ISA_SSE2;
        }
      else
        {
	  return ISA_BASE;
        }

    case 306:  /* *umulsidi3_1 */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return ISA_BMI2;
        }
      else
        {
	  return ISA_BASE;
        }

    case 452:  /* *lshrsi3_1 */
    case 453:  /* *ashrsi3_1 */
    case 454:  /* *lshrdi3_1 */
    case 455:  /* *ashrdi3_1 */
    case 485:  /* *rotlsi3_1 */
    case 486:  /* *rotrsi3_1 */
    case 487:  /* *rotldi3_1 */
    case 488:  /* *rotrdi3_1 */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return ISA_BASE;
        }
      else
        {
	  return ISA_BMI2;
        }

    case 836:  /* *movv8qi_internal */
    case 837:  /* *movv4hi_internal */
    case 838:  /* *movv2si_internal */
    case 839:  /* *movv1di_internal */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x1f0))
        {
	  return ISA_SSE2;
        }
      else if (((1 << which_alternative) & 0x1e00))
        {
	  return ISA_NOAVX;
        }
      else
        {
	  return ISA_BASE;
        }

    case 840:  /* *movv2sf_internal */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x30))
        {
	  return ISA_SSE2;
        }
      else
        {
	  return ISA_BASE;
        }

    case 938:  /* *vec_extractv2si_1 */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x6))
        {
	  return ISA_SSE2;
        }
      else
        {
	  return ISA_BASE;
        }

    case 1440:  /* *vec_concatv2si_sse4_1 */
    case 1257:  /* sse2_loadhpd */
    case 1220:  /* *vec_concatv2sf_sse4_1 */
    case 1198:  /* sse_movhlps */
    case 1199:  /* sse_movlhps */
    case 1212:  /* sse_loadhps */
    case 1214:  /* sse_loadlps */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return ISA_NOAVX;
        }
      else if (which_alternative == 1)
        {
	  return ISA_AVX;
        }
      else if (which_alternative == 2)
        {
	  return ISA_NOAVX;
        }
      else if (which_alternative == 3)
        {
	  return ISA_AVX;
        }
      else
        {
	  return ISA_BASE;
        }

    case 1222:  /* *vec_concatv4sf */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return ISA_NOAVX;
        }
      else if (which_alternative == 1)
        {
	  return ISA_AVX;
        }
      else if (which_alternative == 2)
        {
	  return ISA_NOAVX;
        }
      else
        {
	  return ISA_AVX;
        }

    case 627:  /* *fop_sf_comm_mixed */
    case 628:  /* *fop_df_comm_mixed */
    case 1228:  /* *sse4_1_extractps */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return ISA_BASE;
        }
      else if (which_alternative == 1)
        {
	  return ISA_NOAVX;
        }
      else
        {
	  return ISA_AVX;
        }

    case 1243:  /* *vec_interleave_highv2df */
    case 1245:  /* *vec_interleave_lowv2df */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return ISA_NOAVX;
        }
      else if (which_alternative == 1)
        {
	  return ISA_AVX;
        }
      else if (which_alternative == 2)
        {
	  return ISA_SSE3;
        }
      else if (which_alternative == 3)
        {
	  return ISA_NOAVX;
        }
      else if (which_alternative == 4)
        {
	  return ISA_AVX;
        }
      else
        {
	  return ISA_BASE;
        }

    case 1260:  /* vec_dupv2df */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return ISA_NOAVX;
        }
      else
        {
	  return ISA_SSE3;
        }

    case 1438:  /* *vec_dupv4si */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return ISA_SSE2;
        }
      else if (which_alternative == 1)
        {
	  return ISA_AVX;
        }
      else
        {
	  return ISA_NOAVX;
        }

    case 1439:  /* *vec_dupv2di */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return ISA_SSE2_NOAVX;
        }
      else if (which_alternative == 1)
        {
	  return ISA_AVX;
        }
      else if (which_alternative == 2)
        {
	  return ISA_SSE3;
        }
      else
        {
	  return ISA_NOAVX;
        }

    case 501:  /* setcc_sf_sse */
    case 502:  /* setcc_df_sse */
    case 629:  /* *fop_sf_comm_sse */
    case 630:  /* *fop_df_comm_sse */
    case 636:  /* *fop_sf_1_sse */
    case 637:  /* *fop_df_1_sse */
    case 781:  /* smaxsf3 */
    case 782:  /* sminsf3 */
    case 783:  /* smaxdf3 */
    case 784:  /* smindf3 */
    case 785:  /* *ieee_smaxsf3 */
    case 786:  /* *ieee_sminsf3 */
    case 787:  /* *ieee_smaxdf3 */
    case 788:  /* *ieee_smindf3 */
    case 988:  /* *addv8sf3 */
    case 989:  /* *subv8sf3 */
    case 990:  /* *addv4sf3 */
    case 991:  /* *subv4sf3 */
    case 992:  /* *addv4df3 */
    case 993:  /* *subv4df3 */
    case 994:  /* *addv2df3 */
    case 995:  /* *subv2df3 */
    case 996:  /* sse_vmaddv4sf3 */
    case 997:  /* sse_vmsubv4sf3 */
    case 998:  /* sse2_vmaddv2df3 */
    case 999:  /* sse2_vmsubv2df3 */
    case 1000:  /* *mulv8sf3 */
    case 1001:  /* *mulv4sf3 */
    case 1002:  /* *mulv4df3 */
    case 1003:  /* *mulv2df3 */
    case 1004:  /* sse_vmmulv4sf3 */
    case 1005:  /* sse2_vmmulv2df3 */
    case 1006:  /* avx_divv8sf3 */
    case 1007:  /* sse_divv4sf3 */
    case 1008:  /* avx_divv4df3 */
    case 1009:  /* sse2_divv2df3 */
    case 1010:  /* sse_vmdivv4sf3 */
    case 1011:  /* sse2_vmdivv2df3 */
    case 1014:  /* sse_vmrcpv4sf2 */
    case 1019:  /* sse_vmsqrtv4sf2 */
    case 1020:  /* sse2_vmsqrtv2df2 */
    case 1023:  /* sse_vmrsqrtv4sf2 */
    case 1024:  /* *smaxv8sf3_finite */
    case 1025:  /* *sminv8sf3_finite */
    case 1026:  /* *smaxv4sf3_finite */
    case 1027:  /* *sminv4sf3_finite */
    case 1028:  /* *smaxv4df3_finite */
    case 1029:  /* *sminv4df3_finite */
    case 1030:  /* *smaxv2df3_finite */
    case 1031:  /* *sminv2df3_finite */
    case 1032:  /* *smaxv8sf3 */
    case 1033:  /* *sminv8sf3 */
    case 1034:  /* *smaxv4sf3 */
    case 1035:  /* *sminv4sf3 */
    case 1036:  /* *smaxv4df3 */
    case 1037:  /* *sminv4df3 */
    case 1038:  /* *smaxv2df3 */
    case 1039:  /* *sminv2df3 */
    case 1040:  /* sse_vmsmaxv4sf3 */
    case 1041:  /* sse_vmsminv4sf3 */
    case 1042:  /* sse2_vmsmaxv2df3 */
    case 1043:  /* sse2_vmsminv2df3 */
    case 1044:  /* *ieee_sminv8sf3 */
    case 1045:  /* *ieee_sminv4sf3 */
    case 1046:  /* *ieee_sminv4df3 */
    case 1047:  /* *ieee_sminv2df3 */
    case 1048:  /* *ieee_smaxv8sf3 */
    case 1049:  /* *ieee_smaxv4sf3 */
    case 1050:  /* *ieee_smaxv4df3 */
    case 1051:  /* *ieee_smaxv2df3 */
    case 1053:  /* sse3_addsubv2df3 */
    case 1055:  /* sse3_addsubv4sf3 */
    case 1058:  /* *sse3_haddv2df3 */
    case 1059:  /* sse3_hsubv2df3 */
    case 1060:  /* *sse3_haddv2df3_low */
    case 1061:  /* *sse3_hsubv2df3_low */
    case 1064:  /* sse3_haddv4sf3 */
    case 1065:  /* sse3_hsubv4sf3 */
    case 1072:  /* *avx_maskcmpv8sf3_comm */
    case 1073:  /* *sse_maskcmpv4sf3_comm */
    case 1074:  /* *avx_maskcmpv4df3_comm */
    case 1075:  /* *sse2_maskcmpv2df3_comm */
    case 1076:  /* avx_maskcmpv8sf3 */
    case 1077:  /* sse_maskcmpv4sf3 */
    case 1078:  /* avx_maskcmpv4df3 */
    case 1079:  /* sse2_maskcmpv2df3 */
    case 1080:  /* sse_vmmaskcmpv4sf3 */
    case 1081:  /* sse2_vmmaskcmpv2df3 */
    case 1086:  /* avx_andnotv8sf3 */
    case 1087:  /* sse_andnotv4sf3 */
    case 1088:  /* avx_andnotv4df3 */
    case 1089:  /* sse2_andnotv2df3 */
    case 1090:  /* *andv8sf3 */
    case 1091:  /* *iorv8sf3 */
    case 1092:  /* *xorv8sf3 */
    case 1093:  /* *andv4sf3 */
    case 1094:  /* *iorv4sf3 */
    case 1095:  /* *xorv4sf3 */
    case 1096:  /* *andv4df3 */
    case 1097:  /* *iorv4df3 */
    case 1098:  /* *xorv4df3 */
    case 1099:  /* *andv2df3 */
    case 1100:  /* *iorv2df3 */
    case 1101:  /* *xorv2df3 */
    case 1102:  /* *andnotsf3 */
    case 1103:  /* *andnotdf3 */
    case 1104:  /* *andnottf3 */
    case 1105:  /* *andsf3 */
    case 1106:  /* *iorsf3 */
    case 1107:  /* *xorsf3 */
    case 1108:  /* *anddf3 */
    case 1109:  /* *iordf3 */
    case 1110:  /* *xordf3 */
    case 1111:  /* *andtf3 */
    case 1112:  /* *iortf3 */
    case 1113:  /* *xortf3 */
    case 1201:  /* vec_interleave_highv4sf */
    case 1203:  /* vec_interleave_lowv4sf */
    case 1209:  /* sse_shufps_v4si */
    case 1210:  /* sse_shufps_v4sf */
    case 1215:  /* sse_movss */
    case 1225:  /* *vec_setv4sf_sse4_1 */
    case 1226:  /* sse4_1_insertps */
    case 1248:  /* vec_interleave_highv2di */
    case 1250:  /* vec_interleave_lowv2di */
    case 1251:  /* sse2_shufpd_v2di */
    case 1252:  /* sse2_shufpd_v2df */
    case 1262:  /* *addv32qi3 */
    case 1263:  /* *subv32qi3 */
    case 1264:  /* *addv16qi3 */
    case 1265:  /* *subv16qi3 */
    case 1266:  /* *addv16hi3 */
    case 1267:  /* *subv16hi3 */
    case 1268:  /* *addv8hi3 */
    case 1269:  /* *subv8hi3 */
    case 1270:  /* *addv8si3 */
    case 1271:  /* *subv8si3 */
    case 1272:  /* *addv4si3 */
    case 1273:  /* *subv4si3 */
    case 1274:  /* *addv4di3 */
    case 1275:  /* *subv4di3 */
    case 1276:  /* *addv2di3 */
    case 1277:  /* *subv2di3 */
    case 1278:  /* *avx2_ssaddv32qi3 */
    case 1279:  /* *avx2_usaddv32qi3 */
    case 1280:  /* *avx2_sssubv32qi3 */
    case 1281:  /* *avx2_ussubv32qi3 */
    case 1282:  /* *sse2_ssaddv16qi3 */
    case 1283:  /* *sse2_usaddv16qi3 */
    case 1284:  /* *sse2_sssubv16qi3 */
    case 1285:  /* *sse2_ussubv16qi3 */
    case 1286:  /* *avx2_ssaddv16hi3 */
    case 1287:  /* *avx2_usaddv16hi3 */
    case 1288:  /* *avx2_sssubv16hi3 */
    case 1289:  /* *avx2_ussubv16hi3 */
    case 1290:  /* *sse2_ssaddv8hi3 */
    case 1291:  /* *sse2_usaddv8hi3 */
    case 1292:  /* *sse2_sssubv8hi3 */
    case 1293:  /* *sse2_ussubv8hi3 */
    case 1294:  /* *mulv16hi3 */
    case 1295:  /* *mulv8hi3 */
    case 1296:  /* *smulv16hi3_highpart */
    case 1297:  /* *umulv16hi3_highpart */
    case 1298:  /* *smulv8hi3_highpart */
    case 1299:  /* *umulv8hi3_highpart */
    case 1301:  /* *vec_widen_umult_even_v4si */
    case 1303:  /* *sse4_1_mulv2siv2di3 */
    case 1305:  /* *sse2_pmaddwd */
    case 1306:  /* *avx2_mulv8si3 */
    case 1307:  /* *sse4_1_mulv4si3 */
    case 1308:  /* ashrv16hi3 */
    case 1309:  /* ashrv8hi3 */
    case 1310:  /* ashrv8si3 */
    case 1311:  /* ashrv4si3 */
    case 1312:  /* ashlv16hi3 */
    case 1313:  /* lshrv16hi3 */
    case 1314:  /* ashlv8hi3 */
    case 1315:  /* lshrv8hi3 */
    case 1316:  /* ashlv8si3 */
    case 1317:  /* lshrv8si3 */
    case 1318:  /* ashlv4si3 */
    case 1319:  /* lshrv4si3 */
    case 1320:  /* ashlv4di3 */
    case 1321:  /* lshrv4di3 */
    case 1322:  /* ashlv2di3 */
    case 1323:  /* lshrv2di3 */
    case 1324:  /* avx2_ashlv2ti3 */
    case 1325:  /* sse2_ashlv1ti3 */
    case 1326:  /* avx2_lshrv2ti3 */
    case 1327:  /* sse2_lshrv1ti3 */
    case 1340:  /* *sse4_1_smaxv16qi3 */
    case 1341:  /* *sse4_1_sminv16qi3 */
    case 1342:  /* *sse4_1_smaxv4si3 */
    case 1343:  /* *sse4_1_sminv4si3 */
    case 1344:  /* *smaxv8hi3 */
    case 1345:  /* *sminv8hi3 */
    case 1346:  /* *sse4_1_umaxv8hi3 */
    case 1347:  /* *sse4_1_uminv8hi3 */
    case 1348:  /* *sse4_1_umaxv4si3 */
    case 1349:  /* *sse4_1_uminv4si3 */
    case 1350:  /* *umaxv16qi3 */
    case 1351:  /* *uminv16qi3 */
    case 1356:  /* *sse4_1_eqv2di3 */
    case 1357:  /* *sse2_eqv16qi3 */
    case 1358:  /* *sse2_eqv8hi3 */
    case 1359:  /* *sse2_eqv4si3 */
    case 1360:  /* sse4_2_gtv2di3 */
    case 1365:  /* sse2_gtv16qi3 */
    case 1366:  /* sse2_gtv8hi3 */
    case 1367:  /* sse2_gtv4si3 */
    case 1368:  /* *andnotv32qi3 */
    case 1369:  /* *andnotv16qi3 */
    case 1370:  /* *andnotv16hi3 */
    case 1371:  /* *andnotv8hi3 */
    case 1372:  /* *andnotv8si3 */
    case 1373:  /* *andnotv4si3 */
    case 1374:  /* *andnotv4di3 */
    case 1375:  /* *andnotv2di3 */
    case 1376:  /* *andv32qi3 */
    case 1377:  /* *iorv32qi3 */
    case 1378:  /* *xorv32qi3 */
    case 1379:  /* *andv16qi3 */
    case 1380:  /* *iorv16qi3 */
    case 1381:  /* *xorv16qi3 */
    case 1382:  /* *andv16hi3 */
    case 1383:  /* *iorv16hi3 */
    case 1384:  /* *xorv16hi3 */
    case 1385:  /* *andv8hi3 */
    case 1386:  /* *iorv8hi3 */
    case 1387:  /* *xorv8hi3 */
    case 1388:  /* *andv8si3 */
    case 1389:  /* *iorv8si3 */
    case 1390:  /* *xorv8si3 */
    case 1391:  /* *andv4si3 */
    case 1392:  /* *iorv4si3 */
    case 1393:  /* *xorv4si3 */
    case 1394:  /* *andv4di3 */
    case 1395:  /* *iorv4di3 */
    case 1396:  /* *xorv4di3 */
    case 1397:  /* *andv2di3 */
    case 1398:  /* *iorv2di3 */
    case 1399:  /* *xorv2di3 */
    case 1400:  /* avx2_packsswb */
    case 1401:  /* sse2_packsswb */
    case 1402:  /* avx2_packssdw */
    case 1403:  /* sse2_packssdw */
    case 1404:  /* avx2_packuswb */
    case 1405:  /* sse2_packuswb */
    case 1407:  /* vec_interleave_highv16qi */
    case 1409:  /* vec_interleave_lowv16qi */
    case 1411:  /* vec_interleave_highv8hi */
    case 1413:  /* vec_interleave_lowv8hi */
    case 1415:  /* vec_interleave_highv4si */
    case 1417:  /* vec_interleave_lowv4si */
    case 1445:  /* *avx2_uavgv32qi3 */
    case 1446:  /* *sse2_uavgv16qi3 */
    case 1447:  /* *avx2_uavgv16hi3 */
    case 1448:  /* *sse2_uavgv8hi3 */
    case 1449:  /* avx2_psadbw */
    case 1450:  /* sse2_psadbw */
    case 1468:  /* ssse3_phaddwv8hi3 */
    case 1469:  /* ssse3_phaddswv8hi3 */
    case 1470:  /* ssse3_phsubwv8hi3 */
    case 1471:  /* ssse3_phsubswv8hi3 */
    case 1478:  /* ssse3_phadddv4si3 */
    case 1479:  /* ssse3_phsubdv4si3 */
    case 1483:  /* ssse3_pmaddubsw128 */
    case 1485:  /* *avx2_pmulhrswv16hi3 */
    case 1486:  /* *ssse3_pmulhrswv8hi3 */
    case 1488:  /* avx2_pshufbv32qi3 */
    case 1489:  /* ssse3_pshufbv16qi3 */
    case 1491:  /* avx2_psignv32qi3 */
    case 1492:  /* ssse3_psignv16qi3 */
    case 1493:  /* avx2_psignv16hi3 */
    case 1494:  /* ssse3_psignv8hi3 */
    case 1495:  /* avx2_psignv8si3 */
    case 1496:  /* ssse3_psignv4si3 */
    case 1500:  /* avx2_palignrv2ti */
    case 1501:  /* ssse3_palignrti */
    case 1520:  /* avx_blendps256 */
    case 1521:  /* sse4_1_blendps */
    case 1522:  /* avx_blendpd256 */
    case 1523:  /* sse4_1_blendpd */
    case 1524:  /* avx_blendvps256 */
    case 1525:  /* sse4_1_blendvps */
    case 1526:  /* avx_blendvpd256 */
    case 1527:  /* sse4_1_blendvpd */
    case 1528:  /* avx_dpps256 */
    case 1529:  /* sse4_1_dpps */
    case 1530:  /* avx_dppd256 */
    case 1531:  /* sse4_1_dppd */
    case 1534:  /* avx2_mpsadbw */
    case 1535:  /* sse4_1_mpsadbw */
    case 1537:  /* sse4_1_packusdw */
    case 1538:  /* avx2_pblendvb */
    case 1539:  /* sse4_1_pblendvb */
    case 1540:  /* sse4_1_pblendw */
    case 1579:  /* sse4_1_roundss */
    case 1580:  /* sse4_1_roundsd */
    case 1682:  /* aesenc */
    case 1683:  /* aesenclast */
    case 1684:  /* aesdec */
    case 1685:  /* aesdeclast */
    case 1688:  /* pclmulqdq */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return ISA_NOAVX;
        }
      else
        {
	  return ISA_AVX;
        }

    case 1709:  /* vec_dupv8si */
    case 1710:  /* vec_dupv8sf */
    case 1711:  /* vec_dupv4di */
    case 1712:  /* vec_dupv4df */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return ISA_BASE;
        }
      else if (which_alternative == 1)
        {
	  return ISA_AVX2;
        }
      else
        {
	  return ISA_NOAVX2;
        }

    case 1302:  /* *vec_widen_smult_even_v8si */
      return ISA_AVX;

    case -1:
      if (GET_CODE (PATTERN (insn)) != ASM_INPUT
          && asm_noperands (PATTERN (insn)) < 0)
        fatal_insn_not_found (insn);
    default:
      return ISA_BASE;

    }
}

enum attr_i387_cw
get_attr_i387_cw (rtx insn ATTRIBUTE_UNUSED)
{
  switch (recog_memoized (insn))
    {
    case 717:  /* frndintxf2_mask_pm */
    case 718:  /* frndintxf2_mask_pm_i387 */
      return I387_CW_MASK_PM;

    case 712:  /* frndintxf2_ceil */
    case 715:  /* frndintxf2_ceil_i387 */
    case 720:  /* *fisthi2_ceil_1 */
    case 722:  /* *fistsi2_ceil_1 */
    case 724:  /* *fistdi2_ceil_1 */
    case 726:  /* fistdi2_ceil */
    case 728:  /* fistdi2_ceil_with_temp */
    case 730:  /* fisthi2_ceil */
    case 732:  /* fistsi2_ceil */
    case 734:  /* fisthi2_ceil_with_temp */
    case 736:  /* fistsi2_ceil_with_temp */
      return I387_CW_CEIL;

    case 711:  /* frndintxf2_floor */
    case 714:  /* frndintxf2_floor_i387 */
    case 719:  /* *fisthi2_floor_1 */
    case 721:  /* *fistsi2_floor_1 */
    case 723:  /* *fistdi2_floor_1 */
    case 725:  /* fistdi2_floor */
    case 727:  /* fistdi2_floor_with_temp */
    case 729:  /* fisthi2_floor */
    case 731:  /* fistsi2_floor */
    case 733:  /* fisthi2_floor_with_temp */
    case 735:  /* fistsi2_floor_with_temp */
      return I387_CW_FLOOR;

    case 158:  /* *fix_trunchi_i387_1 */
    case 159:  /* *fix_truncsi_i387_1 */
    case 160:  /* *fix_truncdi_i387_1 */
    case 161:  /* fix_truncdi_i387 */
    case 162:  /* fix_truncdi_i387_with_temp */
    case 163:  /* fix_trunchi_i387 */
    case 164:  /* fix_truncsi_i387 */
    case 165:  /* fix_trunchi_i387_with_temp */
    case 166:  /* fix_truncsi_i387_with_temp */
    case 713:  /* frndintxf2_trunc */
    case 716:  /* frndintxf2_trunc_i387 */
      return I387_CW_TRUNC;

    case -1:
      if (GET_CODE (PATTERN (insn)) != ASM_INPUT
          && asm_noperands (PATTERN (insn)) < 0)
        fatal_insn_not_found (insn);
    default:
      return I387_CW_ANY;

    }
}

enum attr_imm_disp
get_attr_imm_disp (rtx insn ATTRIBUTE_UNUSED)
{
  enum attr_type cached_type ATTRIBUTE_UNUSED;

  switch (recog_memoized (insn))
    {
    case 840:  /* *movv2sf_internal */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0xc00))
        {
	  return IMM_DISP_UNKNOWN;
        }
      else
        {
	  return IMM_DISP_FALSE;
        }

    case 839:  /* *movv1di_internal */
    case 838:  /* *movv2si_internal */
    case 837:  /* *movv4hi_internal */
    case 836:  /* *movv8qi_internal */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x6000))
        {
	  return IMM_DISP_UNKNOWN;
        }
      else
        {
	  return IMM_DISP_FALSE;
        }

    case 792:  /* pro_epilogue_adjust_stack_di_sub */
    case 791:  /* pro_epilogue_adjust_stack_si_sub */
    case 492:  /* *rotrhi3_1 */
    case 491:  /* *rotlhi3_1 */
    case 490:  /* *rotrqi3_1 */
    case 489:  /* *rotlqi3_1 */
    case 488:  /* *rotrdi3_1 */
    case 487:  /* *rotldi3_1 */
    case 486:  /* *rotrsi3_1 */
    case 485:  /* *rotlsi3_1 */
    case 484:  /* *bmi2_rorxsi3_1 */
    case 481:  /* *rotrdi3_mask */
    case 480:  /* *rotldi3_mask */
    case 479:  /* *rotrsi3_mask */
    case 478:  /* *rotlsi3_mask */
    case 477:  /* *ashrdi3_cconly */
    case 476:  /* *lshrdi3_cconly */
    case 475:  /* *ashrsi3_cconly */
    case 474:  /* *lshrsi3_cconly */
    case 473:  /* *ashrhi3_cconly */
    case 472:  /* *lshrhi3_cconly */
    case 471:  /* *ashrqi3_cconly */
    case 470:  /* *lshrqi3_cconly */
    case 469:  /* *ashrdi3_cmp */
    case 468:  /* *lshrdi3_cmp */
    case 467:  /* *ashrsi3_cmp */
    case 466:  /* *lshrsi3_cmp */
    case 465:  /* *ashrhi3_cmp */
    case 464:  /* *lshrhi3_cmp */
    case 463:  /* *ashrqi3_cmp */
    case 462:  /* *lshrqi3_cmp */
    case 459:  /* *ashrhi3_1 */
    case 458:  /* *lshrhi3_1 */
    case 457:  /* *ashrqi3_1 */
    case 456:  /* *lshrqi3_1 */
    case 455:  /* *ashrdi3_1 */
    case 454:  /* *lshrdi3_1 */
    case 453:  /* *ashrsi3_1 */
    case 452:  /* *lshrsi3_1 */
    case 451:  /* *bmi2_ashrsi3_1 */
    case 450:  /* *bmi2_lshrsi3_1 */
    case 448:  /* x86_shrd */
    case 445:  /* *ashrdi3_mask */
    case 444:  /* *lshrdi3_mask */
    case 443:  /* *ashrsi3_mask */
    case 442:  /* *lshrsi3_mask */
    case 428:  /* *bmi2_ashlsi3_1 */
    case 427:  /* *ashldi3_mask */
    case 426:  /* *ashlsi3_mask */
    case 425:  /* x86_shld */
    case 379:  /* *xorqi_cc_ext_1 */
    case 378:  /* *xorqi_ext_2 */
    case 377:  /* *iorqi_ext_2 */
    case 376:  /* *xorqi_ext_1 */
    case 375:  /* *iorqi_ext_1 */
    case 374:  /* *xorqi_ext_0 */
    case 373:  /* *iorqi_ext_0 */
    case 372:  /* *xordi_3 */
    case 371:  /* *iordi_3 */
    case 370:  /* *xorsi_3 */
    case 369:  /* *iorsi_3 */
    case 368:  /* *xorhi_3 */
    case 367:  /* *iorhi_3 */
    case 366:  /* *xorqi_3 */
    case 365:  /* *iorqi_3 */
    case 362:  /* *xordi_2 */
    case 361:  /* *iordi_2 */
    case 360:  /* *xorsi_2 */
    case 359:  /* *iorsi_2 */
    case 358:  /* *xorhi_2 */
    case 357:  /* *iorhi_2 */
    case 356:  /* *xorqi_2 */
    case 355:  /* *iorqi_2 */
    case 352:  /* *xorqi_1 */
    case 351:  /* *iorqi_1 */
    case 350:  /* *xordi_1 */
    case 349:  /* *iordi_1 */
    case 348:  /* *xorsi_1 */
    case 347:  /* *iorsi_1 */
    case 346:  /* *xorhi_1 */
    case 345:  /* *iorhi_1 */
    case 344:  /* *andqi_ext_2 */
    case 343:  /* *andqi_ext_1 */
    case 342:  /* *andqi_ext_0_cc */
    case 341:  /* andqi_ext_0 */
    case 339:  /* *andsi_2 */
    case 338:  /* *andhi_2 */
    case 337:  /* *andqi_2 */
    case 336:  /* *andqi_2_maybe_si */
    case 334:  /* *andqi_1 */
    case 323:  /* udivmodhiqi3 */
    case 322:  /* *udivmodsi4_noext */
    case 321:  /* *udivmodhi4_noext */
    case 317:  /* divmodhiqi3 */
    case 316:  /* *divmodsi4_noext */
    case 315:  /* *divmodhi4_noext */
    case 311:  /* *umulsi3_highpart_1 */
    case 310:  /* *smulsi3_highpart_1 */
    case 309:  /* *umulqihi3_1 */
    case 308:  /* *mulqihi3_1 */
    case 307:  /* *mulsidi3_1 */
    case 304:  /* *mulqi3_1 */
    case 303:  /* *mulhi3_1 */
    case 302:  /* *mulsi3_1 */
    case 301:  /* *subdi3_cc_overflow */
    case 300:  /* *adddi3_cc_overflow */
    case 299:  /* *subsi3_cc_overflow */
    case 298:  /* *addsi3_cc_overflow */
    case 297:  /* *subhi3_cc_overflow */
    case 296:  /* *addhi3_cc_overflow */
    case 295:  /* *subqi3_cc_overflow */
    case 294:  /* *addqi3_cc_overflow */
    case 290:  /* *addsi3_cconly_overflow */
    case 289:  /* *addhi3_cconly_overflow */
    case 288:  /* *addqi3_cconly_overflow */
    case 287:  /* adcxdi3 */
    case 286:  /* adcxsi3 */
    case 285:  /* *subdi3_carry */
    case 284:  /* *adddi3_carry */
    case 283:  /* *subsi3_carry */
    case 282:  /* *addsi3_carry */
    case 281:  /* *subhi3_carry */
    case 280:  /* *addhi3_carry */
    case 279:  /* *subqi3_carry */
    case 278:  /* *addqi3_carry */
    case 277:  /* *subdi_3 */
    case 276:  /* *subsi_3 */
    case 275:  /* *subhi_3 */
    case 274:  /* *subqi_3 */
    case 273:  /* *subdi_2 */
    case 272:  /* *subsi_2 */
    case 271:  /* *subhi_2 */
    case 270:  /* *subqi_2 */
    case 268:  /* *subdi_1 */
    case 267:  /* *subsi_1 */
    case 266:  /* *subhi_1 */
    case 265:  /* *subqi_1 */
    case 257:  /* *addqi_ext_2 */
    case 235:  /* addqi3_cc */
    case 234:  /* *adddi3_cc */
    case 233:  /* *addsi3_cc */
      extract_insn_cached (insn);
      if ((memory_displacement_operand (operands[0], VOIDmode)) && (immediate_operand (operands[2], VOIDmode)))
        {
	  return IMM_DISP_TRUE;
        }
      else
        {
	  return IMM_DISP_FALSE;
        }

    case 189:  /* *floatsidf2_mixed_with_temp */
    case 188:  /* *floatsisf2_mixed_with_temp */
    case 185:  /* *floatsidf2_vector_mixed_with_temp */
    case 184:  /* *floatsisf2_vector_mixed_with_temp */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 1)
        {
	  return IMM_DISP_UNKNOWN;
        }
      else
        {
	  return IMM_DISP_FALSE;
        }

    case 1228:  /* *sse4_1_extractps */
    case 217:  /* *floatdixf2_i387_with_temp */
    case 216:  /* *floatdidf2_i387_with_temp */
    case 215:  /* *floatdisf2_i387_with_temp */
    case 214:  /* *floatsixf2_i387_with_temp */
    case 213:  /* *floatsidf2_i387_with_temp */
    case 212:  /* *floatsisf2_i387_with_temp */
    case 174:  /* *floathixf2_i387_with_temp */
    case 173:  /* *floathidf2_i387_with_temp */
    case 172:  /* *floathisf2_i387_with_temp */
    case 140:  /* *truncxfdf2_mixed */
    case 139:  /* *truncxfsf2_mixed */
    case 137:  /* *truncdfsf_i387 */
      extract_constrain_insn_cached (insn);
      if (which_alternative != 0)
        {
	  return IMM_DISP_UNKNOWN;
        }
      else
        {
	  return IMM_DISP_FALSE;
        }

    case 777:  /* *movdfcc_1 */
    case 136:  /* *truncdfsf_mixed */
      extract_constrain_insn_cached (insn);
      if (!((1 << which_alternative) & 0x3))
        {
	  return IMM_DISP_UNKNOWN;
        }
      else
        {
	  return IMM_DISP_FALSE;
        }

    case 117:  /* *zero_extendsidi2 */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x7))
        {
	  return IMM_DISP_UNKNOWN;
        }
      else
        {
	  return IMM_DISP_FALSE;
        }

    case 112:  /* *movdf_internal */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x18))
        {
	  return IMM_DISP_UNKNOWN;
        }
      else
        {
	  return IMM_DISP_FALSE;
        }

    case 111:  /* *movxf_internal */
      extract_constrain_insn_cached (insn);
      if (!((1 << which_alternative) & 0x7))
        {
	  return IMM_DISP_UNKNOWN;
        }
      else
        {
	  return IMM_DISP_FALSE;
        }

    case 109:  /* *pushsf */
      extract_constrain_insn_cached (insn);
      if (which_alternative != 1)
        {
	  return IMM_DISP_UNKNOWN;
        }
      else
        {
	  return IMM_DISP_FALSE;
        }

    case 77:  /* *movdi_internal */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return IMM_DISP_UNKNOWN;
        }
      else
        {
	  return IMM_DISP_FALSE;
        }

    case 600:  /* *bsrhi */
    case 599:  /* bsr */
    case 578:  /* ctzsi2 */
    case 577:  /* ctzhi2 */
    case 576:  /* *bsfsi_1 */
    case 575:  /* *tzcntsi_1 */
    case 570:  /* set_got_offset_rex64 */
    case 496:  /* *btdi */
    case 495:  /* *btsi */
    case 494:  /* *rotrqi3_1_slp */
    case 493:  /* *rotlqi3_1_slp */
    case 461:  /* *ashrqi3_1_slp */
    case 460:  /* *lshrqi3_1_slp */
    case 423:  /* *one_cmpldi2_2 */
    case 422:  /* *one_cmplsi2_2 */
    case 421:  /* *one_cmplhi2_2 */
    case 420:  /* *one_cmplqi2_2 */
    case 364:  /* *xorqi_2_slp */
    case 363:  /* *iorqi_2_slp */
    case 354:  /* *xorqi_1_slp */
    case 353:  /* *iorqi_1_slp */
    case 340:  /* *andqi_2_slp */
    case 335:  /* *andqi_1_slp */
    case 330:  /* *testqi_ext_2 */
    case 329:  /* *testqi_ext_1 */
    case 328:  /* *testqi_ext_0 */
    case 327:  /* *testsi_1 */
    case 326:  /* *testhi_1 */
    case 325:  /* *testqi_1 */
    case 324:  /* *testqi_1_maybe_si */
    case 293:  /* *subsi3_cconly_overflow */
    case 292:  /* *subhi3_cconly_overflow */
    case 291:  /* *subqi3_cconly_overflow */
    case 269:  /* *subqi_1_slp */
    case 122:  /* zero_extendqihi2_and */
    case 119:  /* zero_extendhisi2_and */
    case 118:  /* zero_extendqisi2_and */
    case 104:  /* *movqi_insv_2 */
    case 103:  /* *movsi_insv_1 */
    case 97:  /* *movstricthi_xor */
    case 96:  /* *movstrictqi_xor */
    case 95:  /* *movstricthi_1 */
    case 94:  /* *movstrictqi_1 */
    case 93:  /* *swaphi_2 */
    case 92:  /* *swapqi_2 */
    case 91:  /* *swaphi_1 */
    case 90:  /* *swapqi_1 */
    case 89:  /* swapsi */
    case 88:  /* *movabsdi_2 */
    case 87:  /* *movabssi_2 */
    case 86:  /* *movabshi_2 */
    case 85:  /* *movabsqi_2 */
    case 84:  /* *movabsdi_1 */
    case 83:  /* *movabssi_1 */
    case 82:  /* *movabshi_1 */
    case 81:  /* *movabsqi_1 */
    case 74:  /* *movsi_or */
    case 73:  /* *movsi_xor */
    case 16:  /* *cmpqi_ext_4 */
    case 15:  /* *cmpqi_ext_3_insn */
    case 14:  /* *cmpqi_ext_2 */
    case 13:  /* *cmpqi_ext_1 */
    case 12:  /* *cmpdi_minus_1 */
    case 11:  /* *cmpsi_minus_1 */
    case 10:  /* *cmphi_minus_1 */
    case 9:  /* *cmpqi_minus_1 */
    case 8:  /* *cmpdi_1 */
    case 7:  /* *cmpsi_1 */
    case 6:  /* *cmphi_1 */
    case 5:  /* *cmpqi_1 */
    case 4:  /* *cmpdi_ccno_1 */
    case 3:  /* *cmpsi_ccno_1 */
    case 2:  /* *cmphi_ccno_1 */
    case 1:  /* *cmpqi_ccno_1 */
      extract_insn_cached (insn);
      if ((memory_displacement_operand (operands[0], VOIDmode)) && (immediate_operand (operands[1], VOIDmode)))
        {
	  return IMM_DISP_TRUE;
        }
      else
        {
	  return IMM_DISP_FALSE;
        }

    case -1:
      if (GET_CODE (PATTERN (insn)) != ASM_INPUT
          && asm_noperands (PATTERN (insn)) < 0)
        fatal_insn_not_found (insn);
    case 78:  /* *movsi_internal */
    case 79:  /* *movhi_internal */
    case 80:  /* *movqi_internal */
    case 100:  /* *movqi_extv_1 */
    case 102:  /* *movqi_extzv_2 */
    case 113:  /* *movsf_internal */
    case 236:  /* *addsi_1 */
    case 237:  /* *adddi_1 */
    case 238:  /* *addhi_1 */
    case 239:  /* *addqi_1 */
    case 240:  /* *addqi_1_slp */
    case 241:  /* *addqi_2 */
    case 242:  /* *addhi_2 */
    case 243:  /* *addsi_2 */
    case 244:  /* *adddi_2 */
    case 245:  /* *addqi_3 */
    case 246:  /* *addhi_3 */
    case 247:  /* *addsi_3 */
    case 248:  /* *adddi_3 */
    case 249:  /* *addqi_4 */
    case 250:  /* *addhi_4 */
    case 251:  /* *addsi_4 */
    case 252:  /* *addqi_5 */
    case 253:  /* *addhi_5 */
    case 254:  /* *addsi_5 */
    case 255:  /* *adddi_5 */
    case 256:  /* addqi_ext_1 */
    case 306:  /* *umulsidi3_1 */
    case 332:  /* *andsi_1 */
    case 333:  /* *andhi_1 */
    case 429:  /* *ashlsi3_1 */
    case 430:  /* *ashldi3_1 */
    case 431:  /* *ashlhi3_1 */
    case 432:  /* *ashlqi3_1 */
    case 433:  /* *ashlqi3_1_slp */
    case 434:  /* *ashlqi3_cmp */
    case 435:  /* *ashlhi3_cmp */
    case 436:  /* *ashlsi3_cmp */
    case 437:  /* *ashldi3_cmp */
    case 438:  /* *ashlqi3_cconly */
    case 439:  /* *ashlhi3_cconly */
    case 440:  /* *ashlsi3_cconly */
    case 441:  /* *ashldi3_cconly */
    case 449:  /* ashrsi3_cvt */
    case 606:  /* *bswapsi2_movbe */
    case 789:  /* pro_epilogue_adjust_stack_si_add */
    case 790:  /* pro_epilogue_adjust_stack_di_add */
    case 868:  /* *vec_extractv2sf_1 */
    case 938:  /* *vec_extractv2si_1 */
    case 1223:  /* vec_setv4si_0 */
    case 1224:  /* vec_setv4sf_0 */
    case 1253:  /* sse2_storehpd */
    case 1255:  /* sse2_storelpd */
    case 1257:  /* sse2_loadhpd */
    case 1258:  /* sse2_loadlpd */
      extract_insn_cached (insn);
      if (((cached_type = get_attr_type (insn)) == TYPE_OTHER) || (cached_type == TYPE_MULTI))
        {
	  return IMM_DISP_UNKNOWN;
        }
      else if (((cached_type == TYPE_ICMP) || ((cached_type == TYPE_TEST) || ((cached_type == TYPE_IMOV) || ((cached_type == TYPE_ALU1) || ((cached_type == TYPE_ISHIFT1) || (cached_type == TYPE_ROTATE1)))))) && ((memory_displacement_operand (operands[0], VOIDmode)) && (immediate_operand (operands[1], VOIDmode))))
        {
	  return IMM_DISP_TRUE;
        }
      else if (((cached_type == TYPE_ALU) || ((cached_type == TYPE_ISHIFT) || ((cached_type == TYPE_ISHIFTX) || ((cached_type == TYPE_ROTATE) || ((cached_type == TYPE_ROTATEX) || ((cached_type == TYPE_IMUL) || (cached_type == TYPE_IDIV))))))) && ((memory_displacement_operand (operands[0], VOIDmode)) && (immediate_operand (operands[2], VOIDmode))))
        {
	  return IMM_DISP_TRUE;
        }
      else
        {
	  return IMM_DISP_FALSE;
        }

    case 1905:  /* atomic_xorsi */
    case 1904:  /* atomic_orsi */
    case 1903:  /* atomic_andsi */
    case 1902:  /* atomic_xorhi */
    case 1901:  /* atomic_orhi */
    case 1900:  /* atomic_andhi */
    case 1899:  /* atomic_xorqi */
    case 1898:  /* atomic_orqi */
    case 1897:  /* atomic_andqi */
    case 1896:  /* atomic_subsi */
    case 1895:  /* atomic_subhi */
    case 1894:  /* atomic_subqi */
    case 1893:  /* atomic_addsi */
    case 1892:  /* atomic_addhi */
    case 1891:  /* atomic_addqi */
    case 1890:  /* atomic_exchangesi */
    case 1889:  /* atomic_exchangehi */
    case 1888:  /* atomic_exchangeqi */
    case 1887:  /* *atomic_fetch_add_cmpsi */
    case 1886:  /* *atomic_fetch_add_cmphi */
    case 1885:  /* *atomic_fetch_add_cmpqi */
    case 1884:  /* atomic_fetch_addsi */
    case 1883:  /* atomic_fetch_addhi */
    case 1882:  /* atomic_fetch_addqi */
    case 1881:  /* atomic_compare_and_swapdi_doubleword */
    case 1880:  /* atomic_compare_and_swapsi_1 */
    case 1879:  /* atomic_compare_and_swaphi_1 */
    case 1878:  /* atomic_compare_and_swapqi_1 */
    case 1875:  /* atomic_storedi_fpu */
    case 1874:  /* atomic_storesi_1 */
    case 1873:  /* atomic_storehi_1 */
    case 1872:  /* atomic_storeqi_1 */
    case 1871:  /* atomic_loaddi_fpu */
    case 1870:  /* mfence_nosse */
    case 1772:  /* avx_pd256_pd */
    case 1771:  /* avx_ps256_ps */
    case 1770:  /* avx_si256_si */
    case 1725:  /* *avx_vperm_broadcast_v4df */
    case 1724:  /* *avx_vperm_broadcast_v8sf */
    case 1463:  /* sse3_monitor */
    case 1462:  /* sse3_mwait */
    case 1436:  /* *sse2_storeq */
    case 1435:  /* *vec_ext_v4si_mem */
    case 1434:  /* sse2_stored */
    case 1240:  /* vec_extract_lo_v32qi */
    case 1238:  /* vec_extract_lo_v16hi */
    case 1235:  /* vec_extract_lo_v8sf */
    case 1234:  /* vec_extract_lo_v8si */
    case 1231:  /* vec_extract_lo_v4df */
    case 1230:  /* vec_extract_lo_v4di */
    case 1229:  /* *vec_extract_v4sf_mem */
    case 1227:  /* *vec_extractv4sf_0 */
    case 987:  /* *absnegv2df2 */
    case 986:  /* *absnegv4df2 */
    case 985:  /* *absnegv4sf2 */
    case 984:  /* *absnegv8sf2 */
    case 962:  /* movdi_to_sse */
    case 937:  /* *vec_extractv2si_0 */
    case 867:  /* *vec_extractv2sf_0 */
    case 835:  /* xtest_1 */
    case 834:  /* xabort */
    case 833:  /* xend */
    case 832:  /* xbegin_1 */
    case 831:  /* *pause */
    case 830:  /* rdseedsi_1 */
    case 829:  /* rdseedhi_1 */
    case 828:  /* rdrandsi_1 */
    case 827:  /* rdrandhi_1 */
    case 820:  /* xrstor */
    case 819:  /* xsaveopt */
    case 818:  /* xsave */
    case 817:  /* fxrstor */
    case 816:  /* fxsave */
    case 815:  /* rdtscp */
    case 814:  /* rdtsc */
    case 813:  /* rdpmc */
    case 809:  /* stack_tls_protect_test_di */
    case 808:  /* stack_tls_protect_test_si */
    case 807:  /* stack_protect_test_di */
    case 806:  /* stack_protect_test_si */
    case 805:  /* stack_tls_protect_set_di */
    case 804:  /* stack_tls_protect_set_si */
    case 803:  /* stack_protect_set_di */
    case 802:  /* stack_protect_set_si */
    case 799:  /* trap */
    case 798:  /* probe_stack_rangedi */
    case 797:  /* probe_stack_rangesi */
    case 796:  /* adjust_stack_and_probedi */
    case 795:  /* adjust_stack_and_probesi */
    case 794:  /* allocate_stack_worker_probe_di */
    case 793:  /* allocate_stack_worker_probe_si */
    case 743:  /* cld */
    case 741:  /* fxamdf2_i387_with_temp */
    case 740:  /* fxamsf2_i387_with_temp */
    case 739:  /* fxamxf2_i387 */
    case 738:  /* fxamdf2_i387 */
    case 737:  /* fxamsf2_i387 */
    case 626:  /* *tls_dynamic_gnu2_combine_32 */
    case 615:  /* *tls_local_dynamic_32_once */
    case 614:  /* *tls_local_dynamic_base_32_gnu */
    case 613:  /* *tls_global_dynamic_32_gnu */
    case 612:  /* *parityhi2_cmp */
    case 611:  /* paritysi2_cmp */
    case 610:  /* paritydi2_cmp */
    case 609:  /* bswaphi_lowpart */
    case 608:  /* *bswaphi_lowpart_1 */
    case 574:  /* ffssi2_no_cmove */
    case 573:  /* split_stack_return */
    case 571:  /* eh_return_internal */
    case 569:  /* set_got_labelled */
    case 568:  /* set_got */
    case 567:  /* pad */
    case 566:  /* nops */
    case 565:  /* nop */
    case 563:  /* simple_return_pop_internal */
    case 562:  /* simple_return_internal_long */
    case 561:  /* simple_return_internal */
    case 560:  /* prologue_use */
    case 559:  /* *memory_blockage */
    case 558:  /* blockage */
    case 540:  /* *jccxf_si_r_i387 */
    case 539:  /* *jccdf_si_r_i387 */
    case 538:  /* *jccsf_si_r_i387 */
    case 537:  /* *jccxf_hi_r_i387 */
    case 536:  /* *jccdf_hi_r_i387 */
    case 535:  /* *jccsf_hi_r_i387 */
    case 534:  /* *jccxf_si_i387 */
    case 533:  /* *jccdf_si_i387 */
    case 532:  /* *jccsf_si_i387 */
    case 531:  /* *jccxf_hi_i387 */
    case 530:  /* *jccdf_hi_i387 */
    case 529:  /* *jccsf_hi_i387 */
    case 528:  /* *jccuxf_r_i387 */
    case 527:  /* *jccudf_r_i387 */
    case 526:  /* *jccusf_r_i387 */
    case 525:  /* *jccuxf_i387 */
    case 524:  /* *jccudf_i387 */
    case 523:  /* *jccusf_i387 */
    case 522:  /* *jccdf_r_i387 */
    case 521:  /* *jccsf_r_i387 */
    case 520:  /* *jccdf_i387 */
    case 519:  /* *jccsf_i387 */
    case 518:  /* *jccxf_r_i387 */
    case 517:  /* *jccxf_i387 */
    case 516:  /* *jccxf_0_r_i387 */
    case 515:  /* *jccdf_0_r_i387 */
    case 514:  /* *jccsf_0_r_i387 */
    case 513:  /* *jccxf_0_i387 */
    case 512:  /* *jccdf_0_i387 */
    case 511:  /* *jccsf_0_i387 */
    case 510:  /* *jcc_btsi_mask_1 */
    case 509:  /* *jcc_btsi_1 */
    case 508:  /* *jcc_btdi_mask */
    case 507:  /* *jcc_btsi_mask */
    case 506:  /* *jcc_btdi */
    case 505:  /* *jcc_btsi */
    case 498:  /* *setcc_si_1_movzbl */
    case 497:  /* *setcc_si_1_and */
    case 483:  /* ix86_rotrdi3_doubleword */
    case 482:  /* ix86_rotldi3_doubleword */
    case 447:  /* *ashrdi3_doubleword */
    case 446:  /* *lshrdi3_doubleword */
    case 424:  /* *ashldi3_doubleword */
    case 415:  /* copysigntf3_var */
    case 414:  /* copysigndf3_var */
    case 413:  /* copysignsf3_var */
    case 412:  /* copysigntf3_const */
    case 411:  /* copysigndf3_const */
    case 410:  /* copysignsf3_const */
    case 397:  /* *absnegtf2_sse */
    case 396:  /* *absnegxf2_i387 */
    case 395:  /* *absnegdf2_i387 */
    case 394:  /* *absnegsf2_i387 */
    case 393:  /* *absnegdf2_sse */
    case 392:  /* *absnegsf2_sse */
    case 391:  /* *absnegdf2_mixed */
    case 390:  /* *absnegsf2_mixed */
    case 381:  /* *negti2_doubleword */
    case 380:  /* *negdi2_doubleword */
    case 331:  /* *testqi_ext_3 */
    case 320:  /* *udivmodsi4 */
    case 319:  /* *udivmodhi4 */
    case 318:  /* udivmodsi4_1 */
    case 314:  /* *divmodsi4 */
    case 313:  /* *divmodhi4 */
    case 312:  /* divmodsi4_1 */
    case 264:  /* *subti3_doubleword */
    case 263:  /* *subdi3_doubleword */
    case 232:  /* *addti3_doubleword */
    case 231:  /* *adddi3_doubleword */
    case 229:  /* *floatunssixf2_1 */
    case 228:  /* *floatunssidf2_1 */
    case 227:  /* *floatunssisf2_1 */
    case 226:  /* floatdixf2_i387_with_xmm */
    case 225:  /* floatdidf2_i387_with_xmm */
    case 224:  /* floatdisf2_i387_with_xmm */
    case 183:  /* *floatdixf2_1 */
    case 182:  /* *floatdidf2_1 */
    case 181:  /* *floatdisf2_1 */
    case 180:  /* *floatsixf2_1 */
    case 179:  /* *floatsidf2_1 */
    case 178:  /* *floatsisf2_1 */
    case 171:  /* *floathixf2_1 */
    case 170:  /* *floathidf2_1 */
    case 169:  /* *floathisf2_1 */
    case 168:  /* x86_fldcw_1 */
    case 167:  /* x86_fnstcw_1 */
    case 146:  /* *fixuns_truncdf_1 */
    case 145:  /* *fixuns_truncsf_1 */
    case 124:  /* extendsidi2_1 */
    case 108:  /* *pushdf */
    case 107:  /* *pushxf_nointeger */
    case 106:  /* *pushxf */
    case 105:  /* *pushtf */
    case 63:  /* *pushdi2 */
    case 48:  /* x86_sahf_1 */
    case 47:  /* x86_fnstsw_1 */
    case 46:  /* *cmpxf_si_cc_i387 */
    case 45:  /* *cmpdf_si_cc_i387 */
    case 44:  /* *cmpsf_si_cc_i387 */
    case 43:  /* *cmpxf_hi_cc_i387 */
    case 42:  /* *cmpdf_hi_cc_i387 */
    case 41:  /* *cmpsf_hi_cc_i387 */
    case 40:  /* *cmpxf_si_i387 */
    case 39:  /* *cmpdf_si_i387 */
    case 38:  /* *cmpsf_si_i387 */
    case 37:  /* *cmpxf_hi_i387 */
    case 36:  /* *cmpdf_hi_i387 */
    case 35:  /* *cmpsf_hi_i387 */
    case 34:  /* *cmpuxf_cc_i387 */
    case 33:  /* *cmpudf_cc_i387 */
    case 32:  /* *cmpusf_cc_i387 */
    case 31:  /* *cmpuxf_i387 */
    case 30:  /* *cmpudf_i387 */
    case 29:  /* *cmpusf_i387 */
    case 28:  /* *cmpdf_cc_i387 */
    case 27:  /* *cmpsf_cc_i387 */
    case 26:  /* *cmpdf_i387 */
    case 25:  /* *cmpsf_i387 */
    case 24:  /* *cmpxf_cc_i387 */
    case 23:  /* *cmpxf_i387 */
    case 22:  /* *cmpxf_0_cc_i387 */
    case 21:  /* *cmpdf_0_cc_i387 */
    case 20:  /* *cmpsf_0_cc_i387 */
    case 19:  /* *cmpxf_0_i387 */
    case 18:  /* *cmpdf_0_i387 */
    case 17:  /* *cmpsf_0_i387 */
      return IMM_DISP_UNKNOWN;

    default:
      return IMM_DISP_FALSE;

    }
}

int
get_attr_length_vex (rtx insn ATTRIBUTE_UNUSED)
{
  switch (recog_memoized (insn))
    {
    case 1421:  /* sse4_1_pinsrq */
      extract_constrain_insn_cached (insn);
      if ((! (
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX))) && ((V2DImode) == (V8HImode)))
        {
	  return 
#line 482 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_vex_default (insn, true, false));
        }
      else
        {
	  return 
#line 485 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_vex_default (insn, false, false));
        }

    case 1420:  /* sse4_1_pinsrd */
      extract_constrain_insn_cached (insn);
      if ((! (
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX))) && ((V4SImode) == (V8HImode)))
        {
	  return 
#line 482 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_vex_default (insn, true, false));
        }
      else
        {
	  return 
#line 485 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_vex_default (insn, false, false));
        }

    case 1419:  /* sse2_pinsrw */
      extract_constrain_insn_cached (insn);
      if ((! (
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX))) && ((V8HImode) == (V8HImode)))
        {
	  return 
#line 482 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_vex_default (insn, true, false));
        }
      else
        {
	  return 
#line 485 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_vex_default (insn, false, false));
        }

    case 1418:  /* sse4_1_pinsrb */
      extract_constrain_insn_cached (insn);
      if ((! (
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX))) && ((V16QImode) == (V8HImode)))
        {
	  return 
#line 482 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_vex_default (insn, true, false));
        }
      else
        {
	  return 
#line 485 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_vex_default (insn, false, false));
        }

    case 1258:  /* sse2_loadlpd */
      extract_constrain_insn_cached (insn);
      if (!((1 << which_alternative) & 0x600))
        {
	  return 
#line 482 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_vex_default (insn, true, false));
        }
      else
        {
	  return 
#line 485 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_vex_default (insn, false, false));
        }

    case 1257:  /* sse2_loadhpd */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x1f))
        {
	  return 
#line 482 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_vex_default (insn, true, false));
        }
      else
        {
	  return 
#line 485 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_vex_default (insn, false, false));
        }

    case 1255:  /* sse2_storelpd */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x7))
        {
	  return 
#line 482 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_vex_default (insn, true, false));
        }
      else
        {
	  return 
#line 485 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_vex_default (insn, false, false));
        }

    case 1224:  /* vec_setv4sf_0 */
    case 1223:  /* vec_setv4si_0 */
      extract_constrain_insn_cached (insn);
      if (!((1 << which_alternative) & 0x6c0))
        {
	  return 
#line 482 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_vex_default (insn, true, false));
        }
      else
        {
	  return 
#line 485 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_vex_default (insn, false, false));
        }

    case 1220:  /* *vec_concatv2sf_sse4_1 */
      extract_constrain_insn_cached (insn);
      if (!((1 << which_alternative) & 0xc))
        {
	  return 
#line 482 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_vex_default (insn, true, false));
        }
      else
        {
	  return 
#line 485 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_vex_default (insn, false, false));
        }

    case 1438:  /* *vec_dupv4si */
    case 1219:  /* vec_dupv4sf */
      extract_constrain_insn_cached (insn);
      if (which_alternative != 1)
        {
	  return 
#line 482 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_vex_default (insn, true, false));
        }
      else
        {
	  return 
#line 485 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_vex_default (insn, false, false));
        }

    case 939:  /* *mmx_uavgv8qi3 */
      extract_constrain_insn_cached (insn);
      if ((
#line 1589 "../../gcc-4.8.1/gcc/config/i386/mmx.md"
(TARGET_SSE)) || (
#line 1590 "../../gcc-4.8.1/gcc/config/i386/mmx.md"
(TARGET_3DNOW_A)))
        {
	  return 
#line 482 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_vex_default (insn, true, false));
        }
      else
        {
	  return 
#line 485 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_vex_default (insn, false, false));
        }

    case 938:  /* *vec_extractv2si_1 */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3f))
        {
	  return 
#line 482 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_vex_default (insn, true, false));
        }
      else
        {
	  return 
#line 485 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_vex_default (insn, false, false));
        }

    case 1253:  /* sse2_storehpd */
    case 868:  /* *vec_extractv2sf_1 */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0xf))
        {
	  return 
#line 482 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_vex_default (insn, true, false));
        }
      else
        {
	  return 
#line 485 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_vex_default (insn, false, false));
        }

    case 840:  /* *movv2sf_internal */
      extract_constrain_insn_cached (insn);
      if (!((1 << which_alternative) & 0xc00))
        {
	  return 
#line 482 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_vex_default (insn, true, false));
        }
      else
        {
	  return 
#line 485 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_vex_default (insn, false, false));
        }

    case 839:  /* *movv1di_internal */
    case 838:  /* *movv2si_internal */
    case 837:  /* *movv4hi_internal */
    case 836:  /* *movv8qi_internal */
      extract_constrain_insn_cached (insn);
      if (!((1 << which_alternative) & 0x6000))
        {
	  return 
#line 482 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_vex_default (insn, true, false));
        }
      else
        {
	  return 
#line 485 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_vex_default (insn, false, false));
        }

    case 637:  /* *fop_df_1_sse */
    case 636:  /* *fop_sf_1_sse */
    case 634:  /* *fop_df_1_mixed */
    case 633:  /* *fop_sf_1_mixed */
    case 630:  /* *fop_df_comm_sse */
    case 629:  /* *fop_sf_comm_sse */
    case 628:  /* *fop_df_comm_mixed */
    case 627:  /* *fop_sf_comm_mixed */
      extract_constrain_insn_cached (insn);
      if (get_attr_unit (insn) == UNIT_SSE)
        {
	  return 
#line 482 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_vex_default (insn, true, false));
        }
      else
        {
	  return 
#line 485 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_vex_default (insn, false, false));
        }

    case 136:  /* *truncdfsf_mixed */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 1)
        {
	  return 
#line 482 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_vex_default (insn, true, false));
        }
      else
        {
	  return 
#line 485 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_vex_default (insn, false, false));
        }

    case 127:  /* extendqihi2 */
    case 125:  /* extendhisi2 */
      extract_constrain_insn_cached (insn);
      if (get_attr_prefix_0f (insn) == 1)
        {
	  return 
#line 482 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_vex_default (insn, true, false));
        }
      else
        {
	  return 
#line 485 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_vex_default (insn, false, false));
        }

    case 117:  /* *zero_extendsidi2 */
      extract_constrain_insn_cached (insn);
      if (!((1 << which_alternative) & 0x7))
        {
	  return 
#line 482 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_vex_default (insn, true, false));
        }
      else
        {
	  return 
#line 485 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_vex_default (insn, false, false));
        }

    case 113:  /* *movsf_internal */
    case 112:  /* *movdf_internal */
      extract_constrain_insn_cached (insn);
      if (!((1 << which_alternative) & 0x1f))
        {
	  return 
#line 482 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_vex_default (insn, true, false));
        }
      else
        {
	  return 
#line 485 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_vex_default (insn, false, false));
        }

    case 1351:  /* *uminv16qi3 */
    case 1350:  /* *umaxv16qi3 */
    case 1345:  /* *sminv8hi3 */
    case 1344:  /* *smaxv8hi3 */
    case 606:  /* *bswapsi2_movbe */
    case 105:  /* *pushtf */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return 
#line 482 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_vex_default (insn, true, false));
        }
      else
        {
	  return 
#line 485 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_vex_default (insn, false, false));
        }

    case 102:  /* *movqi_extzv_2 */
    case 100:  /* *movqi_extv_1 */
    case 80:  /* *movqi_internal */
    case 79:  /* *movhi_internal */
      extract_constrain_insn_cached (insn);
      if (get_attr_type (insn) == TYPE_IMOVX)
        {
	  return 
#line 482 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_vex_default (insn, true, false));
        }
      else
        {
	  return 
#line 485 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_vex_default (insn, false, false));
        }

    case 78:  /* *movsi_internal */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0xffc))
        {
	  return 
#line 482 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_vex_default (insn, true, false));
        }
      else
        {
	  return 
#line 485 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_vex_default (insn, false, false));
        }

    case 1440:  /* *vec_concatv2si_sse4_1 */
    case 778:  /* *movsfcc_1_387 */
    case 333:  /* *andhi_1 */
    case 332:  /* *andsi_1 */
    case 303:  /* *mulhi3_1 */
    case 302:  /* *mulsi3_1 */
    case 189:  /* *floatsidf2_mixed_with_temp */
    case 188:  /* *floatsisf2_mixed_with_temp */
    case 185:  /* *floatsidf2_vector_mixed_with_temp */
    case 184:  /* *floatsisf2_vector_mixed_with_temp */
    case 128:  /* *extendsfdf2_mixed */
    case 77:  /* *movdi_internal */
      extract_constrain_insn_cached (insn);
      if (!((1 << which_alternative) & 0x3))
        {
	  return 
#line 482 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_vex_default (insn, true, false));
        }
      else
        {
	  return 
#line 485 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_vex_default (insn, false, false));
        }

    case 1869:  /* mfence_sse2 */
    case 1868:  /* *sse_sfence */
    case 1867:  /* *sse2_lfence */
    case 1866:  /* *avx2_gatherdiv8sf_4 */
    case 1865:  /* *avx2_gatherdiv8sf_4 */
    case 1864:  /* *avx2_gatherdiv8si_4 */
    case 1863:  /* *avx2_gatherdiv8si_4 */
    case 1862:  /* *avx2_gatherdiv8sf_3 */
    case 1861:  /* *avx2_gatherdiv8sf_3 */
    case 1860:  /* *avx2_gatherdiv8si_3 */
    case 1859:  /* *avx2_gatherdiv8si_3 */
    case 1858:  /* *avx2_gatherdiv8sf_2 */
    case 1857:  /* *avx2_gatherdiv8sf_2 */
    case 1856:  /* *avx2_gatherdiv8si_2 */
    case 1855:  /* *avx2_gatherdiv8si_2 */
    case 1854:  /* *avx2_gatherdiv4sf_2 */
    case 1853:  /* *avx2_gatherdiv4sf_2 */
    case 1852:  /* *avx2_gatherdiv4si_2 */
    case 1851:  /* *avx2_gatherdiv4si_2 */
    case 1850:  /* *avx2_gatherdiv4df_2 */
    case 1849:  /* *avx2_gatherdiv4df_2 */
    case 1848:  /* *avx2_gatherdiv4di_2 */
    case 1847:  /* *avx2_gatherdiv4di_2 */
    case 1846:  /* *avx2_gatherdiv2df_2 */
    case 1845:  /* *avx2_gatherdiv2df_2 */
    case 1844:  /* *avx2_gatherdiv2di_2 */
    case 1843:  /* *avx2_gatherdiv2di_2 */
    case 1842:  /* *avx2_gatherdiv8sf */
    case 1841:  /* *avx2_gatherdiv8sf */
    case 1840:  /* *avx2_gatherdiv8si */
    case 1839:  /* *avx2_gatherdiv8si */
    case 1838:  /* *avx2_gatherdiv4sf */
    case 1837:  /* *avx2_gatherdiv4sf */
    case 1836:  /* *avx2_gatherdiv4si */
    case 1835:  /* *avx2_gatherdiv4si */
    case 1834:  /* *avx2_gatherdiv4df */
    case 1833:  /* *avx2_gatherdiv4df */
    case 1832:  /* *avx2_gatherdiv4di */
    case 1831:  /* *avx2_gatherdiv4di */
    case 1830:  /* *avx2_gatherdiv2df */
    case 1829:  /* *avx2_gatherdiv2df */
    case 1828:  /* *avx2_gatherdiv2di */
    case 1827:  /* *avx2_gatherdiv2di */
    case 1826:  /* *avx2_gathersiv8sf_2 */
    case 1825:  /* *avx2_gathersiv8sf_2 */
    case 1824:  /* *avx2_gathersiv8si_2 */
    case 1823:  /* *avx2_gathersiv8si_2 */
    case 1822:  /* *avx2_gathersiv4sf_2 */
    case 1821:  /* *avx2_gathersiv4sf_2 */
    case 1820:  /* *avx2_gathersiv4si_2 */
    case 1819:  /* *avx2_gathersiv4si_2 */
    case 1818:  /* *avx2_gathersiv4df_2 */
    case 1817:  /* *avx2_gathersiv4df_2 */
    case 1816:  /* *avx2_gathersiv4di_2 */
    case 1815:  /* *avx2_gathersiv4di_2 */
    case 1814:  /* *avx2_gathersiv2df_2 */
    case 1813:  /* *avx2_gathersiv2df_2 */
    case 1812:  /* *avx2_gathersiv2di_2 */
    case 1811:  /* *avx2_gathersiv2di_2 */
    case 1810:  /* *avx2_gathersiv8sf */
    case 1809:  /* *avx2_gathersiv8sf */
    case 1808:  /* *avx2_gathersiv8si */
    case 1807:  /* *avx2_gathersiv8si */
    case 1806:  /* *avx2_gathersiv4sf */
    case 1805:  /* *avx2_gathersiv4sf */
    case 1804:  /* *avx2_gathersiv4si */
    case 1803:  /* *avx2_gathersiv4si */
    case 1802:  /* *avx2_gathersiv4df */
    case 1801:  /* *avx2_gathersiv4df */
    case 1800:  /* *avx2_gathersiv4di */
    case 1799:  /* *avx2_gathersiv4di */
    case 1798:  /* *avx2_gathersiv2df */
    case 1797:  /* *avx2_gathersiv2df */
    case 1796:  /* *avx2_gathersiv2di */
    case 1795:  /* *avx2_gathersiv2di */
    case 1794:  /* vcvtps2ph256 */
    case 1793:  /* *vcvtps2ph_store */
    case 1792:  /* *vcvtps2ph */
    case 1791:  /* vcvtph2ps256 */
    case 1790:  /* *vcvtph2ps_load */
    case 1789:  /* vcvtph2ps */
    case 1782:  /* avx2_lshrvv2di */
    case 1781:  /* avx2_ashlvv2di */
    case 1780:  /* avx2_lshrvv4di */
    case 1779:  /* avx2_ashlvv4di */
    case 1778:  /* avx2_lshrvv4si */
    case 1777:  /* avx2_ashlvv4si */
    case 1776:  /* avx2_lshrvv8si */
    case 1775:  /* avx2_ashlvv8si */
    case 1774:  /* avx2_ashrvv4si */
    case 1773:  /* avx2_ashrvv8si */
    case 1708:  /* avx2_vec_dupv4df */
    case 1707:  /* avx2_permv2ti */
    case 1706:  /* avx2_permv4df_1 */
    case 1705:  /* avx2_permv4di_1 */
    case 1704:  /* avx2_permvarv8sf */
    case 1703:  /* avx2_permvarv8si */
    case 1690:  /* avx_vzeroupper */
    case 1689:  /* *avx_vzeroall */
    case 1641:  /* xop_rotrv2di3 */
    case 1640:  /* xop_rotrv4si3 */
    case 1639:  /* xop_rotrv8hi3 */
    case 1638:  /* xop_rotrv16qi3 */
    case 1637:  /* xop_rotlv2di3 */
    case 1636:  /* xop_rotlv4si3 */
    case 1635:  /* xop_rotlv8hi3 */
    case 1634:  /* xop_rotlv16qi3 */
    case 1519:  /* sse4a_insertq */
    case 1518:  /* sse4a_insertqi */
    case 1517:  /* sse4a_extrq */
    case 1516:  /* sse4a_extrqi */
    case 1515:  /* sse4a_vmmovntv2df */
    case 1514:  /* sse4a_vmmovntv4sf */
    case 1513:  /* sse4a_movntdf */
    case 1512:  /* sse4a_movntsf */
    case 1461:  /* sse2_clflush */
    case 1460:  /* sse_stmxcsr */
    case 1459:  /* sse_ldmxcsr */
    case 1456:  /* sse2_pmovmskb */
    case 1455:  /* avx2_pmovmskb */
    case 1454:  /* sse2_movmskpd */
    case 1453:  /* avx_movmskpd256 */
    case 1452:  /* sse_movmskps */
    case 1451:  /* avx_movmskps256 */
    case 1450:  /* sse2_psadbw */
    case 1449:  /* avx2_psadbw */
    case 1448:  /* *sse2_uavgv8hi3 */
    case 1447:  /* *avx2_uavgv16hi3 */
    case 1446:  /* *sse2_uavgv16qi3 */
    case 1445:  /* *avx2_uavgv32qi3 */
    case 1444:  /* vec_concatv2di */
    case 1443:  /* *vec_concatv4si */
    case 1442:  /* *vec_concatv2si_sse */
    case 1441:  /* *vec_concatv2si_sse2 */
    case 1439:  /* *vec_dupv2di */
    case 1437:  /* *vec_extractv2di_1 */
    case 1433:  /* sse2_loadld */
    case 1432:  /* sse2_pshufhw_1 */
    case 1431:  /* avx2_pshufhw_1 */
    case 1430:  /* sse2_pshuflw_1 */
    case 1429:  /* avx2_pshuflw_1 */
    case 1428:  /* sse2_pshufd_1 */
    case 1427:  /* avx2_pshufd_1 */
    case 1424:  /* *sse2_pextrw_si */
    case 1417:  /* vec_interleave_lowv4si */
    case 1416:  /* avx2_interleave_lowv8si */
    case 1415:  /* vec_interleave_highv4si */
    case 1414:  /* avx2_interleave_highv8si */
    case 1413:  /* vec_interleave_lowv8hi */
    case 1412:  /* avx2_interleave_lowv16hi */
    case 1411:  /* vec_interleave_highv8hi */
    case 1410:  /* avx2_interleave_highv16hi */
    case 1409:  /* vec_interleave_lowv16qi */
    case 1408:  /* avx2_interleave_lowv32qi */
    case 1407:  /* vec_interleave_highv16qi */
    case 1406:  /* avx2_interleave_highv32qi */
    case 1405:  /* sse2_packuswb */
    case 1404:  /* avx2_packuswb */
    case 1403:  /* sse2_packssdw */
    case 1402:  /* avx2_packssdw */
    case 1401:  /* sse2_packsswb */
    case 1400:  /* avx2_packsswb */
    case 1399:  /* *xorv2di3 */
    case 1398:  /* *iorv2di3 */
    case 1397:  /* *andv2di3 */
    case 1396:  /* *xorv4di3 */
    case 1395:  /* *iorv4di3 */
    case 1394:  /* *andv4di3 */
    case 1393:  /* *xorv4si3 */
    case 1392:  /* *iorv4si3 */
    case 1391:  /* *andv4si3 */
    case 1390:  /* *xorv8si3 */
    case 1389:  /* *iorv8si3 */
    case 1388:  /* *andv8si3 */
    case 1387:  /* *xorv8hi3 */
    case 1386:  /* *iorv8hi3 */
    case 1385:  /* *andv8hi3 */
    case 1384:  /* *xorv16hi3 */
    case 1383:  /* *iorv16hi3 */
    case 1382:  /* *andv16hi3 */
    case 1381:  /* *xorv16qi3 */
    case 1380:  /* *iorv16qi3 */
    case 1379:  /* *andv16qi3 */
    case 1378:  /* *xorv32qi3 */
    case 1377:  /* *iorv32qi3 */
    case 1376:  /* *andv32qi3 */
    case 1375:  /* *andnotv2di3 */
    case 1374:  /* *andnotv4di3 */
    case 1373:  /* *andnotv4si3 */
    case 1372:  /* *andnotv8si3 */
    case 1371:  /* *andnotv8hi3 */
    case 1370:  /* *andnotv16hi3 */
    case 1369:  /* *andnotv16qi3 */
    case 1368:  /* *andnotv32qi3 */
    case 1367:  /* sse2_gtv4si3 */
    case 1366:  /* sse2_gtv8hi3 */
    case 1365:  /* sse2_gtv16qi3 */
    case 1359:  /* *sse2_eqv4si3 */
    case 1358:  /* *sse2_eqv8hi3 */
    case 1357:  /* *sse2_eqv16qi3 */
    case 1327:  /* sse2_lshrv1ti3 */
    case 1326:  /* avx2_lshrv2ti3 */
    case 1325:  /* sse2_ashlv1ti3 */
    case 1324:  /* avx2_ashlv2ti3 */
    case 1323:  /* lshrv2di3 */
    case 1322:  /* ashlv2di3 */
    case 1321:  /* lshrv4di3 */
    case 1320:  /* ashlv4di3 */
    case 1319:  /* lshrv4si3 */
    case 1318:  /* ashlv4si3 */
    case 1317:  /* lshrv8si3 */
    case 1316:  /* ashlv8si3 */
    case 1315:  /* lshrv8hi3 */
    case 1314:  /* ashlv8hi3 */
    case 1313:  /* lshrv16hi3 */
    case 1312:  /* ashlv16hi3 */
    case 1311:  /* ashrv4si3 */
    case 1310:  /* ashrv8si3 */
    case 1309:  /* ashrv8hi3 */
    case 1308:  /* ashrv16hi3 */
    case 1305:  /* *sse2_pmaddwd */
    case 1304:  /* *avx2_pmaddwd */
    case 1301:  /* *vec_widen_umult_even_v4si */
    case 1300:  /* *vec_widen_umult_even_v8si */
    case 1299:  /* *umulv8hi3_highpart */
    case 1298:  /* *smulv8hi3_highpart */
    case 1297:  /* *umulv16hi3_highpart */
    case 1296:  /* *smulv16hi3_highpart */
    case 1295:  /* *mulv8hi3 */
    case 1294:  /* *mulv16hi3 */
    case 1293:  /* *sse2_ussubv8hi3 */
    case 1292:  /* *sse2_sssubv8hi3 */
    case 1291:  /* *sse2_usaddv8hi3 */
    case 1290:  /* *sse2_ssaddv8hi3 */
    case 1289:  /* *avx2_ussubv16hi3 */
    case 1288:  /* *avx2_sssubv16hi3 */
    case 1287:  /* *avx2_usaddv16hi3 */
    case 1286:  /* *avx2_ssaddv16hi3 */
    case 1285:  /* *sse2_ussubv16qi3 */
    case 1284:  /* *sse2_sssubv16qi3 */
    case 1283:  /* *sse2_usaddv16qi3 */
    case 1282:  /* *sse2_ssaddv16qi3 */
    case 1281:  /* *avx2_ussubv32qi3 */
    case 1280:  /* *avx2_sssubv32qi3 */
    case 1279:  /* *avx2_usaddv32qi3 */
    case 1278:  /* *avx2_ssaddv32qi3 */
    case 1277:  /* *subv2di3 */
    case 1276:  /* *addv2di3 */
    case 1275:  /* *subv4di3 */
    case 1274:  /* *addv4di3 */
    case 1273:  /* *subv4si3 */
    case 1272:  /* *addv4si3 */
    case 1271:  /* *subv8si3 */
    case 1270:  /* *addv8si3 */
    case 1269:  /* *subv8hi3 */
    case 1268:  /* *addv8hi3 */
    case 1267:  /* *subv16hi3 */
    case 1266:  /* *addv16hi3 */
    case 1265:  /* *subv16qi3 */
    case 1264:  /* *addv16qi3 */
    case 1263:  /* *subv32qi3 */
    case 1262:  /* *addv32qi3 */
    case 1261:  /* *vec_concatv2df */
    case 1260:  /* vec_dupv2df */
    case 1259:  /* sse2_movsd */
    case 1256:  /* *vec_extractv2df_0_sse */
    case 1254:  /* *vec_extractv2df_1_sse */
    case 1252:  /* sse2_shufpd_v2df */
    case 1251:  /* sse2_shufpd_v2di */
    case 1250:  /* vec_interleave_lowv2di */
    case 1249:  /* avx2_interleave_lowv4di */
    case 1248:  /* vec_interleave_highv2di */
    case 1247:  /* avx2_interleave_highv4di */
    case 1246:  /* avx_shufpd256_1 */
    case 1245:  /* *vec_interleave_lowv2df */
    case 1244:  /* *avx_unpcklpd256 */
    case 1243:  /* *vec_interleave_highv2df */
    case 1242:  /* avx_unpckhpd256 */
    case 1222:  /* *vec_concatv4sf */
    case 1221:  /* *vec_concatv2sf_sse */
    case 1218:  /* avx2_vec_dupv8sf_1 */
    case 1217:  /* avx2_vec_dupv4sf */
    case 1216:  /* avx2_vec_dupv8sf */
    case 1215:  /* sse_movss */
    case 1214:  /* sse_loadlps */
    case 1213:  /* sse_storelps */
    case 1212:  /* sse_loadhps */
    case 1211:  /* sse_storehps */
    case 1210:  /* sse_shufps_v4sf */
    case 1209:  /* sse_shufps_v4si */
    case 1208:  /* avx_shufps256_1 */
    case 1207:  /* sse3_movsldup */
    case 1206:  /* avx_movsldup256 */
    case 1205:  /* sse3_movshdup */
    case 1204:  /* avx_movshdup256 */
    case 1203:  /* vec_interleave_lowv4sf */
    case 1202:  /* avx_unpcklps256 */
    case 1201:  /* vec_interleave_highv4sf */
    case 1200:  /* avx_unpckhps256 */
    case 1199:  /* sse_movlhps */
    case 1198:  /* sse_movhlps */
    case 1197:  /* sse2_cvtps2pd */
    case 1196:  /* *avx_cvtps2pd256_2 */
    case 1195:  /* avx_cvtps2pd256 */
    case 1194:  /* *sse2_cvtpd2ps */
    case 1193:  /* avx_cvtpd2ps256 */
    case 1192:  /* sse2_cvtss2sd */
    case 1191:  /* sse2_cvtsd2ss */
    case 1190:  /* *sse2_cvttpd2dq */
    case 1189:  /* *avx_cvttpd2dq256_2 */
    case 1188:  /* fix_truncv4dfv4si2 */
    case 1187:  /* *sse2_cvtpd2dq */
    case 1186:  /* *avx_cvtpd2dq256_2 */
    case 1185:  /* avx_cvtpd2dq256 */
    case 1184:  /* sse2_cvtdq2pd */
    case 1183:  /* avx_cvtdq2pd256_2 */
    case 1182:  /* floatv4siv4df2 */
    case 1181:  /* sse2_cvttsd2si */
    case 1180:  /* sse2_cvtsd2si_2 */
    case 1179:  /* sse2_cvtsd2si */
    case 1178:  /* sse2_cvtsi2sd */
    case 1177:  /* sse2_cvttpd2pi */
    case 1176:  /* sse2_cvtpd2pi */
    case 1175:  /* sse2_cvtpi2pd */
    case 1174:  /* fix_truncv4sfv4si2 */
    case 1173:  /* fix_truncv8sfv8si2 */
    case 1172:  /* sse2_cvtps2dq */
    case 1171:  /* avx_cvtps2dq256 */
    case 1170:  /* floatv4siv4sf2 */
    case 1169:  /* floatv8siv8sf2 */
    case 1168:  /* sse_cvttss2si */
    case 1167:  /* sse_cvtss2si_2 */
    case 1166:  /* sse_cvtss2si */
    case 1165:  /* sse_cvtsi2ss */
    case 1164:  /* sse_cvttps2pi */
    case 1163:  /* sse_cvtps2pi */
    case 1162:  /* sse_cvtpi2ps */
    case 1113:  /* *xortf3 */
    case 1112:  /* *iortf3 */
    case 1111:  /* *andtf3 */
    case 1110:  /* *xordf3 */
    case 1109:  /* *iordf3 */
    case 1108:  /* *anddf3 */
    case 1107:  /* *xorsf3 */
    case 1106:  /* *iorsf3 */
    case 1105:  /* *andsf3 */
    case 1104:  /* *andnottf3 */
    case 1103:  /* *andnotdf3 */
    case 1102:  /* *andnotsf3 */
    case 1101:  /* *xorv2df3 */
    case 1100:  /* *iorv2df3 */
    case 1099:  /* *andv2df3 */
    case 1098:  /* *xorv4df3 */
    case 1097:  /* *iorv4df3 */
    case 1096:  /* *andv4df3 */
    case 1095:  /* *xorv4sf3 */
    case 1094:  /* *iorv4sf3 */
    case 1093:  /* *andv4sf3 */
    case 1092:  /* *xorv8sf3 */
    case 1091:  /* *iorv8sf3 */
    case 1090:  /* *andv8sf3 */
    case 1089:  /* sse2_andnotv2df3 */
    case 1088:  /* avx_andnotv4df3 */
    case 1087:  /* sse_andnotv4sf3 */
    case 1086:  /* avx_andnotv8sf3 */
    case 1085:  /* sse2_ucomi */
    case 1084:  /* sse_ucomi */
    case 1083:  /* sse2_comi */
    case 1082:  /* sse_comi */
    case 1081:  /* sse2_vmmaskcmpv2df3 */
    case 1080:  /* sse_vmmaskcmpv4sf3 */
    case 1079:  /* sse2_maskcmpv2df3 */
    case 1078:  /* avx_maskcmpv4df3 */
    case 1077:  /* sse_maskcmpv4sf3 */
    case 1076:  /* avx_maskcmpv8sf3 */
    case 1075:  /* *sse2_maskcmpv2df3_comm */
    case 1074:  /* *avx_maskcmpv4df3_comm */
    case 1073:  /* *sse_maskcmpv4sf3_comm */
    case 1072:  /* *avx_maskcmpv8sf3_comm */
    case 1071:  /* avx_vmcmpv2df3 */
    case 1070:  /* avx_vmcmpv4sf3 */
    case 1069:  /* avx_cmpv2df3 */
    case 1068:  /* avx_cmpv4df3 */
    case 1067:  /* avx_cmpv4sf3 */
    case 1066:  /* avx_cmpv8sf3 */
    case 1065:  /* sse3_hsubv4sf3 */
    case 1064:  /* sse3_haddv4sf3 */
    case 1063:  /* avx_hsubv8sf3 */
    case 1062:  /* avx_haddv8sf3 */
    case 1061:  /* *sse3_hsubv2df3_low */
    case 1060:  /* *sse3_haddv2df3_low */
    case 1059:  /* sse3_hsubv2df3 */
    case 1058:  /* *sse3_haddv2df3 */
    case 1057:  /* avx_hsubv4df3 */
    case 1056:  /* avx_haddv4df3 */
    case 1055:  /* sse3_addsubv4sf3 */
    case 1054:  /* avx_addsubv8sf3 */
    case 1053:  /* sse3_addsubv2df3 */
    case 1052:  /* avx_addsubv4df3 */
    case 1051:  /* *ieee_smaxv2df3 */
    case 1050:  /* *ieee_smaxv4df3 */
    case 1049:  /* *ieee_smaxv4sf3 */
    case 1048:  /* *ieee_smaxv8sf3 */
    case 1047:  /* *ieee_sminv2df3 */
    case 1046:  /* *ieee_sminv4df3 */
    case 1045:  /* *ieee_sminv4sf3 */
    case 1044:  /* *ieee_sminv8sf3 */
    case 1043:  /* sse2_vmsminv2df3 */
    case 1042:  /* sse2_vmsmaxv2df3 */
    case 1041:  /* sse_vmsminv4sf3 */
    case 1040:  /* sse_vmsmaxv4sf3 */
    case 1039:  /* *sminv2df3 */
    case 1038:  /* *smaxv2df3 */
    case 1037:  /* *sminv4df3 */
    case 1036:  /* *smaxv4df3 */
    case 1035:  /* *sminv4sf3 */
    case 1034:  /* *smaxv4sf3 */
    case 1033:  /* *sminv8sf3 */
    case 1032:  /* *smaxv8sf3 */
    case 1031:  /* *sminv2df3_finite */
    case 1030:  /* *smaxv2df3_finite */
    case 1029:  /* *sminv4df3_finite */
    case 1028:  /* *smaxv4df3_finite */
    case 1027:  /* *sminv4sf3_finite */
    case 1026:  /* *smaxv4sf3_finite */
    case 1025:  /* *sminv8sf3_finite */
    case 1024:  /* *smaxv8sf3_finite */
    case 1023:  /* sse_vmrsqrtv4sf2 */
    case 1022:  /* sse_rsqrtv4sf2 */
    case 1021:  /* avx_rsqrtv8sf2 */
    case 1020:  /* sse2_vmsqrtv2df2 */
    case 1019:  /* sse_vmsqrtv4sf2 */
    case 1018:  /* sse2_sqrtv2df2 */
    case 1017:  /* avx_sqrtv4df2 */
    case 1016:  /* sse_sqrtv4sf2 */
    case 1015:  /* avx_sqrtv8sf2 */
    case 1014:  /* sse_vmrcpv4sf2 */
    case 1013:  /* sse_rcpv4sf2 */
    case 1012:  /* avx_rcpv8sf2 */
    case 1011:  /* sse2_vmdivv2df3 */
    case 1010:  /* sse_vmdivv4sf3 */
    case 1009:  /* sse2_divv2df3 */
    case 1008:  /* avx_divv4df3 */
    case 1007:  /* sse_divv4sf3 */
    case 1006:  /* avx_divv8sf3 */
    case 1005:  /* sse2_vmmulv2df3 */
    case 1004:  /* sse_vmmulv4sf3 */
    case 1003:  /* *mulv2df3 */
    case 1002:  /* *mulv4df3 */
    case 1001:  /* *mulv4sf3 */
    case 1000:  /* *mulv8sf3 */
    case 999:  /* sse2_vmsubv2df3 */
    case 998:  /* sse2_vmaddv2df3 */
    case 997:  /* sse_vmsubv4sf3 */
    case 996:  /* sse_vmaddv4sf3 */
    case 995:  /* *subv2df3 */
    case 994:  /* *addv2df3 */
    case 993:  /* *subv4df3 */
    case 992:  /* *addv4df3 */
    case 991:  /* *subv4sf3 */
    case 990:  /* *addv4sf3 */
    case 989:  /* *subv8sf3 */
    case 988:  /* *addv8sf3 */
    case 983:  /* sse2_movntv2di */
    case 982:  /* avx_movntv4di */
    case 981:  /* sse2_movntv2df */
    case 980:  /* avx_movntv4df */
    case 979:  /* sse_movntv4sf */
    case 978:  /* avx_movntv8sf */
    case 977:  /* sse2_movntisi */
    case 976:  /* sse3_lddqu */
    case 975:  /* avx_lddqu256 */
    case 974:  /* sse2_storedqu */
    case 973:  /* avx_storedqu256 */
    case 972:  /* sse2_loaddqu */
    case 971:  /* avx_loaddqu256 */
    case 970:  /* sse2_storeupd */
    case 969:  /* avx_storeupd256 */
    case 968:  /* sse_storeups */
    case 967:  /* avx_storeups256 */
    case 966:  /* sse2_loadupd */
    case 965:  /* avx_loadupd256 */
    case 964:  /* sse_loadups */
    case 963:  /* avx_loadups256 */
    case 961:  /* sse2_movq128 */
    case 960:  /* *movv2df_internal */
    case 959:  /* *movv4df_internal */
    case 958:  /* *movv4sf_internal */
    case 957:  /* *movv8sf_internal */
    case 956:  /* *movv1ti_internal */
    case 955:  /* *movv2ti_internal */
    case 954:  /* *movv2di_internal */
    case 953:  /* *movv4di_internal */
    case 952:  /* *movv4si_internal */
    case 951:  /* *movv8si_internal */
    case 950:  /* *movv8hi_internal */
    case 949:  /* *movv16hi_internal */
    case 948:  /* *movv16qi_internal */
    case 947:  /* *movv32qi_internal */
    case 946:  /* *mmx_femms */
    case 945:  /* *mmx_emms */
    case 944:  /* *mmx_maskmovq */
    case 943:  /* *mmx_maskmovq */
    case 942:  /* mmx_pmovmskb */
    case 941:  /* mmx_psadbw */
    case 940:  /* *mmx_uavgv4hi3 */
    case 936:  /* *mmx_concatv2si */
    case 935:  /* *vec_dupv2si */
    case 934:  /* *vec_dupv4hi */
    case 932:  /* mmx_pshufw_1 */
    case 931:  /* mmx_pextrw */
    case 930:  /* *mmx_pinsrw */
    case 929:  /* mmx_punpckldq */
    case 928:  /* mmx_punpckhdq */
    case 927:  /* mmx_punpcklwd */
    case 926:  /* mmx_punpckhwd */
    case 925:  /* mmx_punpcklbw */
    case 924:  /* mmx_punpckhbw */
    case 923:  /* mmx_packuswb */
    case 922:  /* mmx_packssdw */
    case 921:  /* mmx_packsswb */
    case 920:  /* *mmx_xorv2si3 */
    case 919:  /* *mmx_iorv2si3 */
    case 918:  /* *mmx_andv2si3 */
    case 917:  /* *mmx_xorv4hi3 */
    case 916:  /* *mmx_iorv4hi3 */
    case 915:  /* *mmx_andv4hi3 */
    case 914:  /* *mmx_xorv8qi3 */
    case 913:  /* *mmx_iorv8qi3 */
    case 912:  /* *mmx_andv8qi3 */
    case 911:  /* mmx_andnotv2si3 */
    case 910:  /* mmx_andnotv4hi3 */
    case 909:  /* mmx_andnotv8qi3 */
    case 908:  /* mmx_gtv2si3 */
    case 907:  /* mmx_gtv4hi3 */
    case 906:  /* mmx_gtv8qi3 */
    case 905:  /* *mmx_eqv2si3 */
    case 904:  /* *mmx_eqv4hi3 */
    case 903:  /* *mmx_eqv8qi3 */
    case 902:  /* mmx_lshrv1di3 */
    case 901:  /* mmx_ashlv1di3 */
    case 900:  /* mmx_lshrv2si3 */
    case 899:  /* mmx_ashlv2si3 */
    case 898:  /* mmx_lshrv4hi3 */
    case 897:  /* mmx_ashlv4hi3 */
    case 896:  /* mmx_ashrv2si3 */
    case 895:  /* mmx_ashrv4hi3 */
    case 894:  /* *mmx_uminv8qi3 */
    case 893:  /* *mmx_umaxv8qi3 */
    case 892:  /* *mmx_sminv4hi3 */
    case 891:  /* *mmx_smaxv4hi3 */
    case 890:  /* *sse2_umulv1siv1di3 */
    case 888:  /* *mmx_pmaddwd */
    case 887:  /* *mmx_umulv4hi3_highpart */
    case 886:  /* *mmx_smulv4hi3_highpart */
    case 885:  /* *mmx_mulv4hi3 */
    case 884:  /* *mmx_ussubv4hi3 */
    case 883:  /* *mmx_sssubv4hi3 */
    case 882:  /* *mmx_usaddv4hi3 */
    case 881:  /* *mmx_ssaddv4hi3 */
    case 880:  /* *mmx_ussubv8qi3 */
    case 879:  /* *mmx_sssubv8qi3 */
    case 878:  /* *mmx_usaddv8qi3 */
    case 877:  /* *mmx_ssaddv8qi3 */
    case 876:  /* *mmx_subv1di3 */
    case 875:  /* *mmx_addv1di3 */
    case 874:  /* *mmx_subv2si3 */
    case 873:  /* *mmx_addv2si3 */
    case 872:  /* *mmx_subv4hi3 */
    case 871:  /* *mmx_addv4hi3 */
    case 870:  /* *mmx_subv8qi3 */
    case 869:  /* *mmx_addv8qi3 */
    case 866:  /* *mmx_concatv2sf */
    case 865:  /* *vec_dupv2sf */
    case 841:  /* sse_movntq */
    case 801:  /* *prefetch_3dnow */
    case 800:  /* *prefetch_sse */
    case 788:  /* *ieee_smindf3 */
    case 787:  /* *ieee_smaxdf3 */
    case 786:  /* *ieee_sminsf3 */
    case 785:  /* *ieee_smaxsf3 */
    case 784:  /* smindf3 */
    case 783:  /* smaxdf3 */
    case 782:  /* sminsf3 */
    case 781:  /* smaxsf3 */
    case 775:  /* *movqicc_noc */
    case 774:  /* *movsicc_noc */
    case 773:  /* *movhicc_noc */
    case 742:  /* movmsk_df */
    case 670:  /* *sqrtdf2_sse */
    case 669:  /* *sqrtsf2_sse */
    case 668:  /* *rsqrtsf2_sse */
    case 635:  /* *rcpsf2_sse */
    case 607:  /* *bswapsi2 */
    case 605:  /* *popcountdi2_cmp */
    case 604:  /* *popcountsi2_cmp */
    case 603:  /* *popcounthi2_cmp */
    case 602:  /* popcountsi2 */
    case 601:  /* popcounthi2 */
    case 600:  /* *bsrhi */
    case 599:  /* bsr */
    case 598:  /* *tbm_tzmsk_si */
    case 597:  /* *tbm_t1mskc_si */
    case 596:  /* *tbm_blsic_si */
    case 595:  /* *tbm_blsfill_si */
    case 594:  /* *tbm_blcs_si */
    case 593:  /* *tbm_blcmsk_si */
    case 592:  /* *tbm_blcic_si */
    case 591:  /* *tbm_blci_si */
    case 590:  /* *tbm_blcfill_si */
    case 589:  /* tbm_bextri_si */
    case 588:  /* bmi2_pext_si3 */
    case 587:  /* bmi2_pdep_si3 */
    case 586:  /* bmi2_bzhi_si3 */
    case 585:  /* *bmi_blsr_si */
    case 584:  /* *bmi_blsmsk_si */
    case 583:  /* *bmi_blsi_si */
    case 582:  /* bmi_bextr_si */
    case 581:  /* *bmi_andn_si */
    case 580:  /* clzsi2_lzcnt */
    case 579:  /* clzhi2_lzcnt */
    case 578:  /* ctzsi2 */
    case 577:  /* ctzhi2 */
    case 576:  /* *bsfsi_1 */
    case 575:  /* *tzcntsi_1 */
    case 502:  /* setcc_df_sse */
    case 501:  /* setcc_sf_sse */
    case 500:  /* *setcc_qi_slp */
    case 499:  /* *setcc_qi */
    case 496:  /* *btdi */
    case 495:  /* *btsi */
    case 448:  /* x86_shrd */
    case 425:  /* x86_shld */
    case 211:  /* *floatdidf2_sse_nointerunit */
    case 210:  /* *floatsidf2_sse_nointerunit */
    case 209:  /* *floatdisf2_sse_nointerunit */
    case 208:  /* *floatsisf2_sse_nointerunit */
    case 207:  /* *floatdidf2_sse_interunit */
    case 206:  /* *floatsidf2_sse_interunit */
    case 205:  /* *floatdisf2_sse_interunit */
    case 204:  /* *floatsisf2_sse_interunit */
    case 203:  /* *floatsidf2_sse_with_temp */
    case 202:  /* *floatsisf2_sse_with_temp */
    case 201:  /* *floatsidf2_vector_sse */
    case 200:  /* *floatsisf2_vector_sse */
    case 199:  /* *floatsidf2_vector_sse_with_temp */
    case 198:  /* *floatsisf2_vector_sse_with_temp */
    case 148:  /* fix_truncdfsi_sse */
    case 147:  /* fix_truncsfsi_sse */
    case 134:  /* *truncdfsf_fast_sse */
    case 129:  /* *extendsfdf2_sse */
    case 126:  /* extendqisi2 */
    case 123:  /* *zero_extendqihi2 */
    case 121:  /* *zero_extendhisi2 */
    case 120:  /* *zero_extendqisi2 */
    case 110:  /* *movtf_internal_sse */
    case 101:  /* *movsi_extzv_1 */
    case 99:  /* *movsi_extv_1 */
    case 98:  /* *movhi_extv_1 */
    case 76:  /* *movti_internal_sse */
    case 75:  /* *movoi_internal_avx */
    case 56:  /* *cmpiudf_sse */
    case 55:  /* *cmpiusf_sse */
    case 54:  /* *cmpidf_sse */
    case 53:  /* *cmpisf_sse */
      extract_constrain_insn_cached (insn);
      return 
#line 482 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_vex_default (insn, true, false));

    case 1788:  /* avx_vec_concatv4df */
    case 1787:  /* avx_vec_concatv8sf */
    case 1786:  /* avx_vec_concatv4di */
    case 1785:  /* avx_vec_concatv8si */
    case 1784:  /* avx_vec_concatv16hi */
    case 1783:  /* avx_vec_concatv32qi */
    case 1349:  /* *sse4_1_uminv4si3 */
    case 1348:  /* *sse4_1_umaxv4si3 */
    case 1347:  /* *sse4_1_uminv8hi3 */
    case 1346:  /* *sse4_1_umaxv8hi3 */
    case 1343:  /* *sse4_1_sminv4si3 */
    case 1342:  /* *sse4_1_smaxv4si3 */
    case 1341:  /* *sse4_1_sminv16qi3 */
    case 1340:  /* *sse4_1_smaxv16qi3 */
    case 197:  /* *floatdidf2_mixed_nointerunit */
    case 196:  /* *floatsidf2_mixed_nointerunit */
    case 195:  /* *floatdisf2_mixed_nointerunit */
    case 194:  /* *floatsisf2_mixed_nointerunit */
    case 193:  /* *floatdidf2_mixed_interunit */
    case 192:  /* *floatsidf2_mixed_interunit */
    case 191:  /* *floatdisf2_mixed_interunit */
    case 190:  /* *floatsisf2_mixed_interunit */
    case 187:  /* *floatsidf2_vector_mixed */
    case 186:  /* *floatsisf2_vector_mixed */
    case 133:  /* *truncdfsf_fast_mixed */
    case 52:  /* *cmpiudf_mixed */
    case 51:  /* *cmpiusf_mixed */
    case 50:  /* *cmpidf_mixed */
    case 49:  /* *cmpisf_mixed */
      extract_constrain_insn_cached (insn);
      if (which_alternative != 0)
        {
	  return 
#line 482 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_vex_default (insn, true, false));
        }
      else
        {
	  return 
#line 485 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_vex_default (insn, false, false));
        }

    case 1457:  /* *sse2_maskmovdqu */
    case 1458:  /* *sse2_maskmovdqu */
      extract_constrain_insn_cached (insn);
      return 
#line 7766 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(3 + REX_SSE_REGNO_P (REGNO (operands[2])));

    case -1:
      if (GET_CODE (PATTERN (insn)) != ASM_INPUT
          && asm_noperands (PATTERN (insn)) < 0)
        fatal_insn_not_found (insn);
      extract_constrain_insn_cached (insn);
      if ((get_attr_prefix_0f (insn) == 1) && (get_attr_prefix_extra (insn) == 0))
        {
	  if (get_attr_prefix_vex_w (insn) == 1)
	    {
	      return 
#line 481 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_vex_default (insn, true, true));
	    }
	  else
	    {
	      return 
#line 482 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_vex_default (insn, true, false));
	    }
        }
      else
        {
	  if (get_attr_prefix_vex_w (insn) == 1)
	    {
	      return 
#line 484 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_vex_default (insn, false, true));
	    }
	  else
	    {
	      return 
#line 485 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_vex_default (insn, false, false));
	    }
        }

    default:
      extract_constrain_insn_cached (insn);
      return 
#line 485 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_vex_default (insn, false, false));

    }
}

int
get_attr_length_address (rtx insn ATTRIBUTE_UNUSED)
{
  enum attr_type cached_type ATTRIBUTE_UNUSED;

  switch (recog_memoized (insn))
    {
    case 840:  /* *movv2sf_internal */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0xc00))
        {
	  return 0;
        }
      else
        {
	  return 
#line 403 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_address_default (insn));
        }

    case 839:  /* *movv1di_internal */
    case 838:  /* *movv2si_internal */
    case 837:  /* *movv4hi_internal */
    case 836:  /* *movv8qi_internal */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x6000))
        {
	  return 0;
        }
      else
        {
	  return 
#line 403 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_address_default (insn));
        }

    case 557:  /* *sibcall_value_pop */
    case 556:  /* *call_value_pop */
    case 555:  /* *sibcall_value */
    case 554:  /* *sibcall_value */
    case 553:  /* *call_value */
    case 552:  /* *call_value */
      extract_constrain_insn_cached (insn);
      if (constant_call_address_operand (operands[1], VOIDmode))
        {
	  return 0;
        }
      else
        {
	  return 
#line 403 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_address_default (insn));
        }

    case 551:  /* *sibcall_pop */
    case 550:  /* *call_pop */
    case 549:  /* *sibcall */
    case 548:  /* *sibcall */
    case 547:  /* *call */
    case 546:  /* *call */
      extract_constrain_insn_cached (insn);
      if (constant_call_address_operand (operands[0], VOIDmode))
        {
	  return 0;
        }
      else
        {
	  return 
#line 403 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_address_default (insn));
        }

    case 189:  /* *floatsidf2_mixed_with_temp */
    case 188:  /* *floatsisf2_mixed_with_temp */
    case 185:  /* *floatsidf2_vector_mixed_with_temp */
    case 184:  /* *floatsisf2_vector_mixed_with_temp */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 1)
        {
	  return 0;
        }
      else
        {
	  return 
#line 403 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_address_default (insn));
        }

    case 1228:  /* *sse4_1_extractps */
    case 217:  /* *floatdixf2_i387_with_temp */
    case 216:  /* *floatdidf2_i387_with_temp */
    case 215:  /* *floatdisf2_i387_with_temp */
    case 214:  /* *floatsixf2_i387_with_temp */
    case 213:  /* *floatsidf2_i387_with_temp */
    case 212:  /* *floatsisf2_i387_with_temp */
    case 174:  /* *floathixf2_i387_with_temp */
    case 173:  /* *floathidf2_i387_with_temp */
    case 172:  /* *floathisf2_i387_with_temp */
    case 140:  /* *truncxfdf2_mixed */
    case 139:  /* *truncxfsf2_mixed */
    case 137:  /* *truncdfsf_i387 */
      extract_constrain_insn_cached (insn);
      if (which_alternative != 0)
        {
	  return 0;
        }
      else
        {
	  return 
#line 403 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_address_default (insn));
        }

    case 777:  /* *movdfcc_1 */
    case 136:  /* *truncdfsf_mixed */
      extract_constrain_insn_cached (insn);
      if (!((1 << which_alternative) & 0x3))
        {
	  return 0;
        }
      else
        {
	  return 
#line 403 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_address_default (insn));
        }

    case 117:  /* *zero_extendsidi2 */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x7))
        {
	  return 0;
        }
      else
        {
	  return 
#line 403 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_address_default (insn));
        }

    case 112:  /* *movdf_internal */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x18))
        {
	  return 0;
        }
      else
        {
	  return 
#line 403 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_address_default (insn));
        }

    case 111:  /* *movxf_internal */
      extract_constrain_insn_cached (insn);
      if (!((1 << which_alternative) & 0x7))
        {
	  return 0;
        }
      else
        {
	  return 
#line 403 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_address_default (insn));
        }

    case 109:  /* *pushsf */
      extract_constrain_insn_cached (insn);
      if (which_alternative != 1)
        {
	  return 0;
        }
      else
        {
	  return 
#line 403 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_address_default (insn));
        }

    case 77:  /* *movdi_internal */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return 0;
        }
      else
        {
	  return 
#line 403 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_address_default (insn));
        }

    case 81:  /* *movabsqi_1 */
    case 82:  /* *movabshi_1 */
    case 83:  /* *movabssi_1 */
    case 84:  /* *movabsdi_1 */
    case 85:  /* *movabsqi_2 */
    case 86:  /* *movabshi_2 */
    case 87:  /* *movabssi_2 */
    case 88:  /* *movabsdi_2 */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return 8;
        }
      else
        {
	  return 0;
        }

    case 570:  /* set_got_offset_rex64 */
      return 8;

    case 624:  /* *tls_dynamic_gnu2_lea_32 */
      return 4;

    case 800:  /* *prefetch_sse */
    case 801:  /* *prefetch_3dnow */
      extract_constrain_insn_cached (insn);
      return 
#line 17596 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(memory_address_length (operands[0], false));

    case 1905:  /* atomic_xorsi */
    case 1904:  /* atomic_orsi */
    case 1903:  /* atomic_andsi */
    case 1902:  /* atomic_xorhi */
    case 1901:  /* atomic_orhi */
    case 1900:  /* atomic_andhi */
    case 1899:  /* atomic_xorqi */
    case 1898:  /* atomic_orqi */
    case 1897:  /* atomic_andqi */
    case 1896:  /* atomic_subsi */
    case 1895:  /* atomic_subhi */
    case 1894:  /* atomic_subqi */
    case 1893:  /* atomic_addsi */
    case 1892:  /* atomic_addhi */
    case 1891:  /* atomic_addqi */
    case 1890:  /* atomic_exchangesi */
    case 1889:  /* atomic_exchangehi */
    case 1888:  /* atomic_exchangeqi */
    case 1887:  /* *atomic_fetch_add_cmpsi */
    case 1886:  /* *atomic_fetch_add_cmphi */
    case 1885:  /* *atomic_fetch_add_cmpqi */
    case 1884:  /* atomic_fetch_addsi */
    case 1883:  /* atomic_fetch_addhi */
    case 1882:  /* atomic_fetch_addqi */
    case 1881:  /* atomic_compare_and_swapdi_doubleword */
    case 1880:  /* atomic_compare_and_swapsi_1 */
    case 1879:  /* atomic_compare_and_swaphi_1 */
    case 1878:  /* atomic_compare_and_swapqi_1 */
    case 1875:  /* atomic_storedi_fpu */
    case 1874:  /* atomic_storesi_1 */
    case 1873:  /* atomic_storehi_1 */
    case 1872:  /* atomic_storeqi_1 */
    case 1871:  /* atomic_loaddi_fpu */
    case 1870:  /* mfence_nosse */
    case 1772:  /* avx_pd256_pd */
    case 1771:  /* avx_ps256_ps */
    case 1770:  /* avx_si256_si */
    case 1725:  /* *avx_vperm_broadcast_v4df */
    case 1724:  /* *avx_vperm_broadcast_v8sf */
    case 1463:  /* sse3_monitor */
    case 1462:  /* sse3_mwait */
    case 1436:  /* *sse2_storeq */
    case 1435:  /* *vec_ext_v4si_mem */
    case 1434:  /* sse2_stored */
    case 1240:  /* vec_extract_lo_v32qi */
    case 1238:  /* vec_extract_lo_v16hi */
    case 1235:  /* vec_extract_lo_v8sf */
    case 1234:  /* vec_extract_lo_v8si */
    case 1231:  /* vec_extract_lo_v4df */
    case 1230:  /* vec_extract_lo_v4di */
    case 1229:  /* *vec_extract_v4sf_mem */
    case 1227:  /* *vec_extractv4sf_0 */
    case 987:  /* *absnegv2df2 */
    case 986:  /* *absnegv4df2 */
    case 985:  /* *absnegv4sf2 */
    case 984:  /* *absnegv8sf2 */
    case 962:  /* movdi_to_sse */
    case 937:  /* *vec_extractv2si_0 */
    case 867:  /* *vec_extractv2sf_0 */
    case 835:  /* xtest_1 */
    case 834:  /* xabort */
    case 833:  /* xend */
    case 832:  /* xbegin_1 */
    case 831:  /* *pause */
    case 830:  /* rdseedsi_1 */
    case 829:  /* rdseedhi_1 */
    case 828:  /* rdrandsi_1 */
    case 827:  /* rdrandhi_1 */
    case 820:  /* xrstor */
    case 819:  /* xsaveopt */
    case 818:  /* xsave */
    case 817:  /* fxrstor */
    case 816:  /* fxsave */
    case 815:  /* rdtscp */
    case 814:  /* rdtsc */
    case 813:  /* rdpmc */
    case 809:  /* stack_tls_protect_test_di */
    case 808:  /* stack_tls_protect_test_si */
    case 807:  /* stack_protect_test_di */
    case 806:  /* stack_protect_test_si */
    case 805:  /* stack_tls_protect_set_di */
    case 804:  /* stack_tls_protect_set_si */
    case 803:  /* stack_protect_set_di */
    case 802:  /* stack_protect_set_si */
    case 799:  /* trap */
    case 798:  /* probe_stack_rangedi */
    case 797:  /* probe_stack_rangesi */
    case 796:  /* adjust_stack_and_probedi */
    case 795:  /* adjust_stack_and_probesi */
    case 794:  /* allocate_stack_worker_probe_di */
    case 793:  /* allocate_stack_worker_probe_si */
    case 769:  /* *strlenqi_1 */
    case 768:  /* *strlenqi_1 */
    case 767:  /* *cmpstrnqi_1 */
    case 766:  /* *cmpstrnqi_1 */
    case 765:  /* *cmpstrnqi_nz_1 */
    case 764:  /* *cmpstrnqi_nz_1 */
    case 763:  /* *rep_stosqi */
    case 762:  /* *rep_stosqi */
    case 761:  /* *rep_stossi */
    case 760:  /* *rep_stossi */
    case 759:  /* *strsetqi_1 */
    case 758:  /* *strsetqi_1 */
    case 757:  /* *strsethi_1 */
    case 756:  /* *strsethi_1 */
    case 755:  /* *strsetsi_1 */
    case 754:  /* *strsetsi_1 */
    case 753:  /* *rep_movqi */
    case 752:  /* *rep_movqi */
    case 751:  /* *rep_movsi */
    case 750:  /* *rep_movsi */
    case 749:  /* *strmovqi_1 */
    case 748:  /* *strmovqi_1 */
    case 747:  /* *strmovhi_1 */
    case 746:  /* *strmovhi_1 */
    case 745:  /* *strmovsi_1 */
    case 744:  /* *strmovsi_1 */
    case 743:  /* cld */
    case 741:  /* fxamdf2_i387_with_temp */
    case 740:  /* fxamsf2_i387_with_temp */
    case 739:  /* fxamxf2_i387 */
    case 738:  /* fxamdf2_i387 */
    case 737:  /* fxamsf2_i387 */
    case 626:  /* *tls_dynamic_gnu2_combine_32 */
    case 615:  /* *tls_local_dynamic_32_once */
    case 614:  /* *tls_local_dynamic_base_32_gnu */
    case 613:  /* *tls_global_dynamic_32_gnu */
    case 612:  /* *parityhi2_cmp */
    case 611:  /* paritysi2_cmp */
    case 610:  /* paritydi2_cmp */
    case 609:  /* bswaphi_lowpart */
    case 608:  /* *bswaphi_lowpart_1 */
    case 574:  /* ffssi2_no_cmove */
    case 573:  /* split_stack_return */
    case 571:  /* eh_return_internal */
    case 569:  /* set_got_labelled */
    case 568:  /* set_got */
    case 567:  /* pad */
    case 566:  /* nops */
    case 565:  /* nop */
    case 563:  /* simple_return_pop_internal */
    case 562:  /* simple_return_internal_long */
    case 561:  /* simple_return_internal */
    case 560:  /* prologue_use */
    case 559:  /* *memory_blockage */
    case 558:  /* blockage */
    case 540:  /* *jccxf_si_r_i387 */
    case 539:  /* *jccdf_si_r_i387 */
    case 538:  /* *jccsf_si_r_i387 */
    case 537:  /* *jccxf_hi_r_i387 */
    case 536:  /* *jccdf_hi_r_i387 */
    case 535:  /* *jccsf_hi_r_i387 */
    case 534:  /* *jccxf_si_i387 */
    case 533:  /* *jccdf_si_i387 */
    case 532:  /* *jccsf_si_i387 */
    case 531:  /* *jccxf_hi_i387 */
    case 530:  /* *jccdf_hi_i387 */
    case 529:  /* *jccsf_hi_i387 */
    case 528:  /* *jccuxf_r_i387 */
    case 527:  /* *jccudf_r_i387 */
    case 526:  /* *jccusf_r_i387 */
    case 525:  /* *jccuxf_i387 */
    case 524:  /* *jccudf_i387 */
    case 523:  /* *jccusf_i387 */
    case 522:  /* *jccdf_r_i387 */
    case 521:  /* *jccsf_r_i387 */
    case 520:  /* *jccdf_i387 */
    case 519:  /* *jccsf_i387 */
    case 518:  /* *jccxf_r_i387 */
    case 517:  /* *jccxf_i387 */
    case 516:  /* *jccxf_0_r_i387 */
    case 515:  /* *jccdf_0_r_i387 */
    case 514:  /* *jccsf_0_r_i387 */
    case 513:  /* *jccxf_0_i387 */
    case 512:  /* *jccdf_0_i387 */
    case 511:  /* *jccsf_0_i387 */
    case 510:  /* *jcc_btsi_mask_1 */
    case 509:  /* *jcc_btsi_1 */
    case 508:  /* *jcc_btdi_mask */
    case 507:  /* *jcc_btsi_mask */
    case 506:  /* *jcc_btdi */
    case 505:  /* *jcc_btsi */
    case 498:  /* *setcc_si_1_movzbl */
    case 497:  /* *setcc_si_1_and */
    case 483:  /* ix86_rotrdi3_doubleword */
    case 482:  /* ix86_rotldi3_doubleword */
    case 447:  /* *ashrdi3_doubleword */
    case 446:  /* *lshrdi3_doubleword */
    case 424:  /* *ashldi3_doubleword */
    case 415:  /* copysigntf3_var */
    case 414:  /* copysigndf3_var */
    case 413:  /* copysignsf3_var */
    case 412:  /* copysigntf3_const */
    case 411:  /* copysigndf3_const */
    case 410:  /* copysignsf3_const */
    case 397:  /* *absnegtf2_sse */
    case 396:  /* *absnegxf2_i387 */
    case 395:  /* *absnegdf2_i387 */
    case 394:  /* *absnegsf2_i387 */
    case 393:  /* *absnegdf2_sse */
    case 392:  /* *absnegsf2_sse */
    case 391:  /* *absnegdf2_mixed */
    case 390:  /* *absnegsf2_mixed */
    case 381:  /* *negti2_doubleword */
    case 380:  /* *negdi2_doubleword */
    case 331:  /* *testqi_ext_3 */
    case 320:  /* *udivmodsi4 */
    case 319:  /* *udivmodhi4 */
    case 318:  /* udivmodsi4_1 */
    case 314:  /* *divmodsi4 */
    case 313:  /* *divmodhi4 */
    case 312:  /* divmodsi4_1 */
    case 264:  /* *subti3_doubleword */
    case 263:  /* *subdi3_doubleword */
    case 232:  /* *addti3_doubleword */
    case 231:  /* *adddi3_doubleword */
    case 229:  /* *floatunssixf2_1 */
    case 228:  /* *floatunssidf2_1 */
    case 227:  /* *floatunssisf2_1 */
    case 226:  /* floatdixf2_i387_with_xmm */
    case 225:  /* floatdidf2_i387_with_xmm */
    case 224:  /* floatdisf2_i387_with_xmm */
    case 183:  /* *floatdixf2_1 */
    case 182:  /* *floatdidf2_1 */
    case 181:  /* *floatdisf2_1 */
    case 180:  /* *floatsixf2_1 */
    case 179:  /* *floatsidf2_1 */
    case 178:  /* *floatsisf2_1 */
    case 171:  /* *floathixf2_1 */
    case 170:  /* *floathidf2_1 */
    case 169:  /* *floathisf2_1 */
    case 168:  /* x86_fldcw_1 */
    case 167:  /* x86_fnstcw_1 */
    case 146:  /* *fixuns_truncdf_1 */
    case 145:  /* *fixuns_truncsf_1 */
    case 124:  /* extendsidi2_1 */
    case 116:  /* *swapdf */
    case 115:  /* *swapsf */
    case 114:  /* swapxf */
    case 108:  /* *pushdf */
    case 107:  /* *pushxf_nointeger */
    case 106:  /* *pushxf */
    case 105:  /* *pushtf */
    case 63:  /* *pushdi2 */
    case 48:  /* x86_sahf_1 */
    case 47:  /* x86_fnstsw_1 */
    case 46:  /* *cmpxf_si_cc_i387 */
    case 45:  /* *cmpdf_si_cc_i387 */
    case 44:  /* *cmpsf_si_cc_i387 */
    case 43:  /* *cmpxf_hi_cc_i387 */
    case 42:  /* *cmpdf_hi_cc_i387 */
    case 41:  /* *cmpsf_hi_cc_i387 */
    case 40:  /* *cmpxf_si_i387 */
    case 39:  /* *cmpdf_si_i387 */
    case 38:  /* *cmpsf_si_i387 */
    case 37:  /* *cmpxf_hi_i387 */
    case 36:  /* *cmpdf_hi_i387 */
    case 35:  /* *cmpsf_hi_i387 */
    case 34:  /* *cmpuxf_cc_i387 */
    case 33:  /* *cmpudf_cc_i387 */
    case 32:  /* *cmpusf_cc_i387 */
    case 31:  /* *cmpuxf_i387 */
    case 30:  /* *cmpudf_i387 */
    case 29:  /* *cmpusf_i387 */
    case 28:  /* *cmpdf_cc_i387 */
    case 27:  /* *cmpsf_cc_i387 */
    case 26:  /* *cmpdf_i387 */
    case 25:  /* *cmpsf_i387 */
    case 24:  /* *cmpxf_cc_i387 */
    case 23:  /* *cmpxf_i387 */
    case 22:  /* *cmpxf_0_cc_i387 */
    case 21:  /* *cmpdf_0_cc_i387 */
    case 20:  /* *cmpsf_0_cc_i387 */
    case 19:  /* *cmpxf_0_i387 */
    case 18:  /* *cmpdf_0_i387 */
    case 17:  /* *cmpsf_0_i387 */
    case 625:  /* *tls_dynamic_gnu2_call_32 */
    case 1867:  /* *sse2_lfence */
    case 1868:  /* *sse_sfence */
    case 1869:  /* mfence_sse2 */
      return 0;

    case -1:
      if (GET_CODE (PATTERN (insn)) != ASM_INPUT
          && asm_noperands (PATTERN (insn)) < 0)
        fatal_insn_not_found (insn);
      extract_constrain_insn_cached (insn);
      if (((cached_type = get_attr_type (insn)) == TYPE_STR) || ((cached_type == TYPE_OTHER) || ((cached_type == TYPE_MULTI) || (cached_type == TYPE_FXCH))))
        {
	  return 0;
        }
      else if ((cached_type == TYPE_CALL) && (constant_call_address_operand (operands[0], VOIDmode)))
        {
	  return 0;
        }
      else if ((cached_type == TYPE_CALLV) && (constant_call_address_operand (operands[1], VOIDmode)))
        {
	  return 0;
        }
      else
        {
	  return 
#line 403 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_address_default (insn));
        }

    default:
      extract_constrain_insn_cached (insn);
      return 
#line 403 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_address_default (insn));

    }
}

int
get_attr_length_immediate (rtx insn ATTRIBUTE_UNUSED)
{
  enum attr_unit cached_unit ATTRIBUTE_UNUSED;
  enum attr_type cached_type ATTRIBUTE_UNUSED;

  switch (recog_memoized (insn))
    {
    case 1723:  /* *avx_vperm_broadcast_v4sf */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return 0;
        }
      else
        {
	  return 1;
        }

    case 1437:  /* *vec_extractv2di_1 */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return 0;
        }
      else if (((1 << which_alternative) & 0x6))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 1259:  /* sse2_movsd */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x1f))
        {
	  return 0;
        }
      else if (which_alternative == 5)
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 1258:  /* sse2_loadlpd */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x1f))
        {
	  return 0;
        }
      else if (which_alternative == 5)
        {
	  return 1;
        }
      else
        {
	  if (which_alternative != 10)
	    {
	      return 0;
	    }
	  else
	    {
	      return 
#line 375 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_immediate_default (insn, false));
	    }
        }

    case 1257:  /* sse2_loadhpd */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3f))
        {
	  return 0;
        }
      else
        {
	  return 
#line 375 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_immediate_default (insn, false));
        }

    case 1255:  /* sse2_storelpd */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0xf))
        {
	  return 0;
        }
      else
        {
	  return 
#line 375 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_immediate_default (insn, false));
        }

    case 1224:  /* vec_setv4sf_0 */
    case 1223:  /* vec_setv4si_0 */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3f))
        {
	  return 0;
        }
      else if (((1 << which_alternative) & 0xc0))
        {
	  return 1;
        }
      else
        {
	  if (which_alternative != 9)
	    {
	      return 0;
	    }
	  else
	    {
	      return 
#line 375 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_immediate_default (insn, false));
	    }
        }

    case 1220:  /* *vec_concatv2sf_sse4_1 */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return 0;
        }
      else if (((1 << which_alternative) & 0xc))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 1440:  /* *vec_concatv2si_sse4_1 */
    case 1214:  /* sse_loadlps */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 1788:  /* avx_vec_concatv4df */
    case 1787:  /* avx_vec_concatv8sf */
    case 1786:  /* avx_vec_concatv4di */
    case 1785:  /* avx_vec_concatv8si */
    case 1784:  /* avx_vec_concatv16hi */
    case 1783:  /* avx_vec_concatv32qi */
    case 1228:  /* *sse4_1_extractps */
    case 1081:  /* sse2_vmmaskcmpv2df3 */
    case 1080:  /* sse_vmmaskcmpv4sf3 */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 938:  /* *vec_extractv2si_1 */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return 0;
        }
      else if (which_alternative == 2)
        {
	  return 1;
        }
      else
        {
	  if (((1 << which_alternative) & 0x3f))
	    {
	      return 0;
	    }
	  else
	    {
	      return 
#line 375 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_immediate_default (insn, false));
	    }
        }

    case 1253:  /* sse2_storehpd */
    case 868:  /* *vec_extractv2sf_1 */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x1f))
        {
	  return 0;
        }
      else
        {
	  return 
#line 375 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_immediate_default (insn, false));
        }

    case 826:  /* *lwp_lwpinssi3_1 */
    case 825:  /* *lwp_lwpvalsi3_1 */
    case 824:  /* lwp_slwpcbdi */
    case 823:  /* lwp_slwpcbsi */
    case 822:  /* *lwp_llwpcbdi1 */
    case 821:  /* *lwp_llwpcbsi1 */
      extract_constrain_insn_cached (insn);
      return 
#line 389 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(/* Update immediate_length and other attributes! */
		      gcc_unreachable (),1);

    case 662:  /* *fop_xf_6_i387 */
    case 661:  /* *fop_xf_6_i387 */
    case 660:  /* *fop_xf_5_i387 */
    case 659:  /* *fop_xf_5_i387 */
    case 658:  /* *fop_xf_4_i387 */
    case 657:  /* *fop_xf_4_i387 */
    case 656:  /* *fop_xf_3_i387 */
    case 655:  /* *fop_xf_3_i387 */
    case 654:  /* *fop_xf_2_i387 */
    case 653:  /* *fop_xf_2_i387 */
    case 652:  /* *fop_xf_1_i387 */
    case 651:  /* *fop_xf_comm_i387 */
    case 650:  /* *fop_df_6_i387 */
    case 649:  /* *fop_df_5_i387 */
    case 648:  /* *fop_df_4_i387 */
    case 647:  /* *fop_df_3_i387 */
    case 646:  /* *fop_sf_3_i387 */
    case 645:  /* *fop_df_3_i387 */
    case 644:  /* *fop_sf_3_i387 */
    case 643:  /* *fop_df_2_i387 */
    case 642:  /* *fop_sf_2_i387 */
    case 641:  /* *fop_df_2_i387 */
    case 640:  /* *fop_sf_2_i387 */
    case 639:  /* *fop_df_1_i387 */
    case 638:  /* *fop_sf_1_i387 */
    case 632:  /* *fop_df_comm_i387 */
    case 631:  /* *fop_sf_comm_i387 */
      extract_constrain_insn_cached (insn);
      if (get_attr_unit (insn) == UNIT_I387)
        {
	  return 0;
        }
      else
        {
	  return 
#line 389 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(/* Update immediate_length and other attributes! */
		      gcc_unreachable (),1);
        }

    case 637:  /* *fop_df_1_sse */
    case 636:  /* *fop_sf_1_sse */
    case 630:  /* *fop_df_comm_sse */
    case 629:  /* *fop_sf_comm_sse */
      extract_constrain_insn_cached (insn);
      if (get_attr_unit (insn) == UNIT_SSE)
        {
	  return 0;
        }
      else
        {
	  return 
#line 389 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(/* Update immediate_length and other attributes! */
		      gcc_unreachable (),1);
        }

    case 634:  /* *fop_df_1_mixed */
    case 633:  /* *fop_sf_1_mixed */
    case 628:  /* *fop_df_comm_mixed */
    case 627:  /* *fop_sf_comm_mixed */
      extract_constrain_insn_cached (insn);
      if (((cached_unit = get_attr_unit (insn)) == UNIT_I387) || (cached_unit == UNIT_SSE))
        {
	  return 0;
        }
      else
        {
	  return 
#line 389 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(/* Update immediate_length and other attributes! */
		      gcc_unreachable (),1);
        }

    case 606:  /* *bswapsi2_movbe */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return 0;
        }
      else
        {
	  return 
#line 375 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_immediate_default (insn, false));
        }

    case 557:  /* *sibcall_value_pop */
    case 556:  /* *call_value_pop */
    case 555:  /* *sibcall_value */
    case 554:  /* *sibcall_value */
    case 553:  /* *call_value */
    case 552:  /* *call_value */
      extract_insn_cached (insn);
      if (constant_call_address_operand (operands[1], VOIDmode))
        {
	  return 4;
        }
      else
        {
	  return 0;
        }

    case 625:  /* *tls_dynamic_gnu2_call_32 */
    case 551:  /* *sibcall_pop */
    case 550:  /* *call_pop */
    case 549:  /* *sibcall */
    case 548:  /* *sibcall */
    case 547:  /* *call */
    case 546:  /* *call */
      extract_insn_cached (insn);
      if (constant_call_address_operand (operands[0], VOIDmode))
        {
	  return 4;
        }
      else
        {
	  return 0;
        }

    case 488:  /* *rotrdi3_1 */
    case 487:  /* *rotldi3_1 */
    case 486:  /* *rotrsi3_1 */
    case 485:  /* *rotlsi3_1 */
      extract_constrain_insn_cached (insn);
      if ((which_alternative == 0) && ((const1_operand (operands[2], VOIDmode)) && ((
#line 10376 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SHIFT1)) || (
#line 6508 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(optimize_function_for_size_p (cfun))))))
        {
	  return 0;
        }
      else
        {
	  return 
#line 373 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_immediate_default (insn, true));
        }

    case 494:  /* *rotrqi3_1_slp */
    case 493:  /* *rotlqi3_1_slp */
    case 461:  /* *ashrqi3_1_slp */
    case 460:  /* *lshrqi3_1_slp */
      extract_constrain_insn_cached (insn);
      if ((const1_operand (operands[1], VOIDmode)) && ((
#line 10376 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SHIFT1)) || (
#line 6508 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(optimize_function_for_size_p (cfun)))))
        {
	  return 0;
        }
      else
        {
	  return 
#line 373 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_immediate_default (insn, true));
        }

    case 492:  /* *rotrhi3_1 */
    case 491:  /* *rotlhi3_1 */
    case 490:  /* *rotrqi3_1 */
    case 489:  /* *rotlqi3_1 */
    case 477:  /* *ashrdi3_cconly */
    case 476:  /* *lshrdi3_cconly */
    case 475:  /* *ashrsi3_cconly */
    case 474:  /* *lshrsi3_cconly */
    case 473:  /* *ashrhi3_cconly */
    case 472:  /* *lshrhi3_cconly */
    case 471:  /* *ashrqi3_cconly */
    case 470:  /* *lshrqi3_cconly */
    case 469:  /* *ashrdi3_cmp */
    case 468:  /* *lshrdi3_cmp */
    case 467:  /* *ashrsi3_cmp */
    case 466:  /* *lshrsi3_cmp */
    case 465:  /* *ashrhi3_cmp */
    case 464:  /* *lshrhi3_cmp */
    case 463:  /* *ashrqi3_cmp */
    case 462:  /* *lshrqi3_cmp */
    case 459:  /* *ashrhi3_1 */
    case 458:  /* *lshrhi3_1 */
    case 457:  /* *ashrqi3_1 */
    case 456:  /* *lshrqi3_1 */
    case 455:  /* *ashrdi3_1 */
    case 454:  /* *lshrdi3_1 */
    case 453:  /* *ashrsi3_1 */
    case 452:  /* *lshrsi3_1 */
      extract_constrain_insn_cached (insn);
      if ((const1_operand (operands[2], VOIDmode)) && ((
#line 10376 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SHIFT1)) || (
#line 6508 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(optimize_function_for_size_p (cfun)))))
        {
	  return 0;
        }
      else
        {
	  return 
#line 373 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_immediate_default (insn, true));
        }

    case 449:  /* ashrsi3_cvt */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return 0;
        }
      else
        {
	  return 
#line 373 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_immediate_default (insn, true));
        }

    case 333:  /* *andhi_1 */
    case 332:  /* *andsi_1 */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return 
#line 373 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_immediate_default (insn, true));
        }
      else
        {
	  return 0;
        }

    case 306:  /* *umulsidi3_1 */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return 0;
        }
      else
        {
	  return 0;
        }

    case 256:  /* addqi_ext_1 */
      extract_constrain_insn_cached (insn);
      if ((cached_type = get_attr_type (insn)) == TYPE_INCDEC)
        {
	  return 0;
        }
      else if (cached_type == TYPE_ALU)
        {
	  return 
#line 373 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_immediate_default (insn, true));
        }
      else
        {
	  return 
#line 389 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(/* Update immediate_length and other attributes! */
		      gcc_unreachable (),1);
        }

    case 240:  /* *addqi_1_slp */
      extract_constrain_insn_cached (insn);
      if ((cached_type = get_attr_type (insn)) == TYPE_INCDEC)
        {
	  return 0;
        }
      else if (cached_type == TYPE_ALU1)
        {
	  return 
#line 373 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_immediate_default (insn, true));
        }
      else
        {
	  return 
#line 389 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(/* Update immediate_length and other attributes! */
		      gcc_unreachable (),1);
        }

    case 113:  /* *movsf_internal */
      extract_constrain_insn_cached (insn);
      if (!((1 << which_alternative) & 0x18))
        {
	  return 0;
        }
      else
        {
	  return 
#line 375 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_immediate_default (insn, false));
        }

    case 109:  /* *pushsf */
      extract_constrain_insn_cached (insn);
      if (which_alternative != 1)
        {
	  return 0;
        }
      else
        {
	  return 
#line 373 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_immediate_default (insn, true));
        }

    case 619:  /* *load_tp_di */
    case 618:  /* *load_tp_si */
    case 617:  /* *load_tp_x32_zext */
    case 616:  /* *load_tp_x32 */
    case 330:  /* *testqi_ext_2 */
    case 329:  /* *testqi_ext_1 */
    case 327:  /* *testsi_1 */
    case 326:  /* *testhi_1 */
    case 325:  /* *testqi_1 */
    case 324:  /* *testqi_1_maybe_si */
    case 104:  /* *movqi_insv_2 */
    case 103:  /* *movsi_insv_1 */
    case 95:  /* *movstricthi_1 */
    case 94:  /* *movstrictqi_1 */
    case 93:  /* *swaphi_2 */
    case 92:  /* *swapqi_2 */
    case 91:  /* *swaphi_1 */
    case 90:  /* *swapqi_1 */
    case 89:  /* swapsi */
      extract_constrain_insn_cached (insn);
      return 
#line 375 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_immediate_default (insn, false));

    case 84:  /* *movabsdi_1 */
    case 83:  /* *movabssi_1 */
    case 82:  /* *movabshi_1 */
    case 81:  /* *movabsqi_1 */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return 0;
        }
      else
        {
	  return 
#line 375 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_immediate_default (insn, false));
        }

    case 102:  /* *movqi_extzv_2 */
    case 100:  /* *movqi_extv_1 */
    case 80:  /* *movqi_internal */
    case 79:  /* *movhi_internal */
      extract_constrain_insn_cached (insn);
      if ((cached_type = get_attr_type (insn)) == TYPE_IMOVX)
        {
	  return 
#line 373 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_immediate_default (insn, true));
        }
      else if (cached_type == TYPE_IMOV)
        {
	  return 
#line 375 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_immediate_default (insn, false));
        }
      else
        {
	  return 
#line 389 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(/* Update immediate_length and other attributes! */
		      gcc_unreachable (),1);
        }

    case 78:  /* *movsi_internal */
      extract_constrain_insn_cached (insn);
      if (((cached_type = get_attr_type (insn)) == TYPE_LEA) || (((1 << which_alternative) & 0xffc)))
        {
	  return 0;
        }
      else if (cached_type == TYPE_IMOV)
        {
	  return 
#line 375 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_immediate_default (insn, false));
        }
      else
        {
	  return 
#line 389 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(/* Update immediate_length and other attributes! */
		      gcc_unreachable (),1);
        }

    case 792:  /* pro_epilogue_adjust_stack_di_sub */
    case 791:  /* pro_epilogue_adjust_stack_si_sub */
    case 623:  /* *add_tp_di */
    case 622:  /* *add_tp_si */
    case 621:  /* *add_tp_x32_zext */
    case 620:  /* *add_tp_x32 */
    case 600:  /* *bsrhi */
    case 599:  /* bsr */
    case 578:  /* ctzsi2 */
    case 577:  /* ctzhi2 */
    case 576:  /* *bsfsi_1 */
    case 575:  /* *tzcntsi_1 */
    case 496:  /* *btdi */
    case 495:  /* *btsi */
    case 484:  /* *bmi2_rorxsi3_1 */
    case 481:  /* *rotrdi3_mask */
    case 480:  /* *rotldi3_mask */
    case 479:  /* *rotrsi3_mask */
    case 478:  /* *rotlsi3_mask */
    case 451:  /* *bmi2_ashrsi3_1 */
    case 450:  /* *bmi2_lshrsi3_1 */
    case 448:  /* x86_shrd */
    case 445:  /* *ashrdi3_mask */
    case 444:  /* *lshrdi3_mask */
    case 443:  /* *ashrsi3_mask */
    case 442:  /* *lshrsi3_mask */
    case 428:  /* *bmi2_ashlsi3_1 */
    case 427:  /* *ashldi3_mask */
    case 426:  /* *ashlsi3_mask */
    case 425:  /* x86_shld */
    case 423:  /* *one_cmpldi2_2 */
    case 422:  /* *one_cmplsi2_2 */
    case 421:  /* *one_cmplhi2_2 */
    case 420:  /* *one_cmplqi2_2 */
    case 419:  /* *one_cmplqi2_1 */
    case 418:  /* *one_cmpldi2_1 */
    case 417:  /* *one_cmplsi2_1 */
    case 416:  /* *one_cmplhi2_1 */
    case 389:  /* *negdi2_cmpz */
    case 388:  /* *negsi2_cmpz */
    case 387:  /* *neghi2_cmpz */
    case 386:  /* *negqi2_cmpz */
    case 385:  /* *negdi2_1 */
    case 384:  /* *negsi2_1 */
    case 383:  /* *neghi2_1 */
    case 382:  /* *negqi2_1 */
    case 379:  /* *xorqi_cc_ext_1 */
    case 372:  /* *xordi_3 */
    case 371:  /* *iordi_3 */
    case 370:  /* *xorsi_3 */
    case 369:  /* *iorsi_3 */
    case 368:  /* *xorhi_3 */
    case 367:  /* *iorhi_3 */
    case 366:  /* *xorqi_3 */
    case 365:  /* *iorqi_3 */
    case 364:  /* *xorqi_2_slp */
    case 363:  /* *iorqi_2_slp */
    case 362:  /* *xordi_2 */
    case 361:  /* *iordi_2 */
    case 360:  /* *xorsi_2 */
    case 359:  /* *iorsi_2 */
    case 358:  /* *xorhi_2 */
    case 357:  /* *iorhi_2 */
    case 356:  /* *xorqi_2 */
    case 355:  /* *iorqi_2 */
    case 354:  /* *xorqi_1_slp */
    case 353:  /* *iorqi_1_slp */
    case 352:  /* *xorqi_1 */
    case 351:  /* *iorqi_1 */
    case 350:  /* *xordi_1 */
    case 349:  /* *iordi_1 */
    case 348:  /* *xorsi_1 */
    case 347:  /* *iorsi_1 */
    case 346:  /* *xorhi_1 */
    case 345:  /* *iorhi_1 */
    case 340:  /* *andqi_2_slp */
    case 339:  /* *andsi_2 */
    case 338:  /* *andhi_2 */
    case 337:  /* *andqi_2 */
    case 336:  /* *andqi_2_maybe_si */
    case 335:  /* *andqi_1_slp */
    case 334:  /* *andqi_1 */
    case 303:  /* *mulhi3_1 */
    case 302:  /* *mulsi3_1 */
    case 301:  /* *subdi3_cc_overflow */
    case 300:  /* *adddi3_cc_overflow */
    case 299:  /* *subsi3_cc_overflow */
    case 298:  /* *addsi3_cc_overflow */
    case 297:  /* *subhi3_cc_overflow */
    case 296:  /* *addhi3_cc_overflow */
    case 295:  /* *subqi3_cc_overflow */
    case 294:  /* *addqi3_cc_overflow */
    case 293:  /* *subsi3_cconly_overflow */
    case 292:  /* *subhi3_cconly_overflow */
    case 291:  /* *subqi3_cconly_overflow */
    case 290:  /* *addsi3_cconly_overflow */
    case 289:  /* *addhi3_cconly_overflow */
    case 288:  /* *addqi3_cconly_overflow */
    case 287:  /* adcxdi3 */
    case 286:  /* adcxsi3 */
    case 285:  /* *subdi3_carry */
    case 284:  /* *adddi3_carry */
    case 283:  /* *subsi3_carry */
    case 282:  /* *addsi3_carry */
    case 281:  /* *subhi3_carry */
    case 280:  /* *addhi3_carry */
    case 279:  /* *subqi3_carry */
    case 278:  /* *addqi3_carry */
    case 277:  /* *subdi_3 */
    case 276:  /* *subsi_3 */
    case 275:  /* *subhi_3 */
    case 274:  /* *subqi_3 */
    case 273:  /* *subdi_2 */
    case 272:  /* *subsi_2 */
    case 271:  /* *subhi_2 */
    case 270:  /* *subqi_2 */
    case 269:  /* *subqi_1_slp */
    case 268:  /* *subdi_1 */
    case 267:  /* *subsi_1 */
    case 266:  /* *subhi_1 */
    case 265:  /* *subqi_1 */
    case 257:  /* *addqi_ext_2 */
    case 235:  /* addqi3_cc */
    case 234:  /* *adddi3_cc */
    case 233:  /* *addsi3_cc */
    case 127:  /* extendqihi2 */
    case 126:  /* extendqisi2 */
    case 125:  /* extendhisi2 */
    case 123:  /* *zero_extendqihi2 */
    case 122:  /* zero_extendqihi2_and */
    case 121:  /* *zero_extendhisi2 */
    case 120:  /* *zero_extendqisi2 */
    case 119:  /* zero_extendhisi2_and */
    case 118:  /* zero_extendqisi2_and */
    case 101:  /* *movsi_extzv_1 */
    case 99:  /* *movsi_extv_1 */
    case 98:  /* *movhi_extv_1 */
    case 72:  /* *popdi1_epilogue */
    case 71:  /* *popsi1_epilogue */
    case 70:  /* *popdi1 */
    case 69:  /* *popsi1 */
    case 68:  /* *pushdi2_prologue */
    case 67:  /* *pushsi2_prologue */
    case 66:  /* *pushhi2 */
    case 65:  /* *pushqi2 */
    case 64:  /* *pushsi2 */
    case 16:  /* *cmpqi_ext_4 */
    case 15:  /* *cmpqi_ext_3_insn */
    case 13:  /* *cmpqi_ext_1 */
    case 12:  /* *cmpdi_minus_1 */
    case 11:  /* *cmpsi_minus_1 */
    case 10:  /* *cmphi_minus_1 */
    case 9:  /* *cmpqi_minus_1 */
    case 8:  /* *cmpdi_1 */
    case 7:  /* *cmpsi_1 */
    case 6:  /* *cmphi_1 */
    case 5:  /* *cmpqi_1 */
      extract_constrain_insn_cached (insn);
      return 
#line 373 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_immediate_default (insn, true));

    case 1722:  /* avx_vbroadcastf128_v4df */
    case 1721:  /* avx_vbroadcastf128_v8sf */
    case 1720:  /* avx_vbroadcastf128_v4di */
    case 1719:  /* avx_vbroadcastf128_v8si */
    case 1718:  /* avx_vbroadcastf128_v16hi */
    case 1717:  /* avx_vbroadcastf128_v32qi */
    case 1539:  /* sse4_1_pblendvb */
    case 1538:  /* avx2_pblendvb */
    case 1:  /* *cmpqi_ccno_1 */
    case 2:  /* *cmphi_ccno_1 */
    case 3:  /* *cmpsi_ccno_1 */
    case 4:  /* *cmpdi_ccno_1 */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return 0;
        }
      else
        {
	  return 1;
        }

    case 236:  /* *addsi_1 */
    case 237:  /* *adddi_1 */
    case 238:  /* *addhi_1 */
    case 239:  /* *addqi_1 */
    case 241:  /* *addqi_2 */
    case 242:  /* *addhi_2 */
    case 243:  /* *addsi_2 */
    case 244:  /* *adddi_2 */
    case 245:  /* *addqi_3 */
    case 246:  /* *addhi_3 */
    case 247:  /* *addsi_3 */
    case 248:  /* *adddi_3 */
    case 249:  /* *addqi_4 */
    case 250:  /* *addhi_4 */
    case 251:  /* *addsi_4 */
    case 252:  /* *addqi_5 */
    case 253:  /* *addhi_5 */
    case 254:  /* *addsi_5 */
    case 255:  /* *adddi_5 */
      extract_constrain_insn_cached (insn);
      if ((get_attr_type (insn) == TYPE_ALU) && (const128_operand (operands[2], VOIDmode)))
        {
	  return 1;
        }
      else
        {
	  if (((cached_type = get_attr_type (insn)) == TYPE_INCDEC) || ((cached_type == TYPE_SETCC) || ((cached_type == TYPE_ICMOV) || ((cached_type == TYPE_STR) || ((cached_type == TYPE_LEA) || ((cached_type == TYPE_OTHER) || ((cached_type == TYPE_MULTI) || ((cached_type == TYPE_IDIV) || ((cached_type == TYPE_LEAVE) || ((cached_type == TYPE_BITMANIP) || (cached_type == TYPE_IMULX)))))))))))
	    {
	      return 0;
	    }
	  else if (((cached_unit = get_attr_unit (insn)) == UNIT_I387) || ((cached_unit == UNIT_SSE) || (cached_unit == UNIT_MMX)))
	    {
	      return 0;
	    }
	  else if ((cached_type == TYPE_ALU) || ((cached_type == TYPE_ALU1) || ((cached_type == TYPE_NEGNOT) || ((cached_type == TYPE_IMOVX) || ((cached_type == TYPE_ISHIFT) || ((cached_type == TYPE_ISHIFTX) || ((cached_type == TYPE_ISHIFT1) || ((cached_type == TYPE_ROTATE) || ((cached_type == TYPE_ROTATEX) || ((cached_type == TYPE_ROTATE1) || ((cached_type == TYPE_IMUL) || ((cached_type == TYPE_ICMP) || ((cached_type == TYPE_PUSH) || (cached_type == TYPE_POP))))))))))))))
	    {
	      return 
#line 373 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_immediate_default (insn, true));
	    }
	  else if ((cached_type == TYPE_IMOV) || (cached_type == TYPE_TEST))
	    {
	      return 
#line 375 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_immediate_default (insn, false));
	    }
	  else if (cached_type == TYPE_CALL)
	    {
	      if (constant_call_address_operand (operands[0], VOIDmode))
	        {
		  return 4;
	        }
	      else
	        {
		  return 0;
	        }
	    }
	  else if (cached_type == TYPE_CALLV)
	    {
	      if (constant_call_address_operand (operands[1], VOIDmode))
	        {
		  return 4;
	        }
	      else
	        {
		  return 0;
	        }
	    }
	  else if (cached_type == TYPE_IBR)
	    {
	      return 1;
	    }
	  else
	    {
	      return 
#line 389 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(/* Update immediate_length and other attributes! */
		      gcc_unreachable (),1);
	    }
        }

    case 433:  /* *ashlqi3_1_slp */
      extract_constrain_insn_cached (insn);
      if (((cached_type = get_attr_type (insn)) == TYPE_ALU) || ((cached_type == TYPE_ISHIFT1) && ((const1_operand (operands[1], VOIDmode)) && ((
#line 10376 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SHIFT1)) || (
#line 6508 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(optimize_function_for_size_p (cfun)))))))
        {
	  return 0;
        }
      else
        {
	  if ((cached_type == TYPE_INCDEC) || ((cached_type == TYPE_SETCC) || ((cached_type == TYPE_ICMOV) || ((cached_type == TYPE_STR) || ((cached_type == TYPE_LEA) || ((cached_type == TYPE_OTHER) || ((cached_type == TYPE_MULTI) || ((cached_type == TYPE_IDIV) || ((cached_type == TYPE_LEAVE) || ((cached_type == TYPE_BITMANIP) || (cached_type == TYPE_IMULX)))))))))))
	    {
	      return 0;
	    }
	  else if ((cached_type == TYPE_ALU1) || ((cached_type == TYPE_NEGNOT) || ((cached_type == TYPE_IMOVX) || ((cached_type == TYPE_ISHIFT) || ((cached_type == TYPE_ISHIFT1) || ((cached_type == TYPE_ROTATE) || ((cached_type == TYPE_ROTATE1) || ((cached_type == TYPE_IMUL) || ((cached_type == TYPE_ICMP) || ((cached_type == TYPE_PUSH) || (cached_type == TYPE_POP)))))))))))
	    {
	      return 
#line 373 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_immediate_default (insn, true));
	    }
	  else if ((cached_type == TYPE_IMOV) || (cached_type == TYPE_TEST))
	    {
	      return 
#line 375 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_immediate_default (insn, false));
	    }
	  else if (cached_type == TYPE_CALL)
	    {
	      if (constant_call_address_operand (operands[0], VOIDmode))
	        {
		  return 4;
	        }
	      else
	        {
		  return 0;
	        }
	    }
	  else if (cached_type == TYPE_CALLV)
	    {
	      if (constant_call_address_operand (operands[1], VOIDmode))
	        {
		  return 4;
	        }
	      else
	        {
		  return 0;
	        }
	    }
	  else if (cached_type == TYPE_IBR)
	    {
	      return 1;
	    }
	  else
	    {
	      return 
#line 389 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(/* Update immediate_length and other attributes! */
		      gcc_unreachable (),1);
	    }
        }

    case 429:  /* *ashlsi3_1 */
    case 430:  /* *ashldi3_1 */
    case 431:  /* *ashlhi3_1 */
    case 432:  /* *ashlqi3_1 */
    case 434:  /* *ashlqi3_cmp */
    case 435:  /* *ashlhi3_cmp */
    case 436:  /* *ashlsi3_cmp */
    case 437:  /* *ashldi3_cmp */
    case 438:  /* *ashlqi3_cconly */
    case 439:  /* *ashlhi3_cconly */
    case 440:  /* *ashlsi3_cconly */
    case 441:  /* *ashldi3_cconly */
      extract_constrain_insn_cached (insn);
      if (((cached_type = get_attr_type (insn)) == TYPE_ALU) || ((cached_type == TYPE_ISHIFT) && ((const1_operand (operands[2], VOIDmode)) && ((
#line 10376 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SHIFT1)) || (
#line 6508 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(optimize_function_for_size_p (cfun)))))))
        {
	  return 0;
        }
      else
        {
	  if ((cached_type == TYPE_INCDEC) || ((cached_type == TYPE_SETCC) || ((cached_type == TYPE_ICMOV) || ((cached_type == TYPE_STR) || ((cached_type == TYPE_LEA) || ((cached_type == TYPE_OTHER) || ((cached_type == TYPE_MULTI) || ((cached_type == TYPE_IDIV) || ((cached_type == TYPE_LEAVE) || ((cached_type == TYPE_BITMANIP) || (cached_type == TYPE_IMULX)))))))))))
	    {
	      return 0;
	    }
	  else if (((cached_unit = get_attr_unit (insn)) == UNIT_I387) || ((cached_unit == UNIT_SSE) || (cached_unit == UNIT_MMX)))
	    {
	      return 0;
	    }
	  else if ((cached_type == TYPE_ALU1) || ((cached_type == TYPE_NEGNOT) || ((cached_type == TYPE_IMOVX) || ((cached_type == TYPE_ISHIFT) || ((cached_type == TYPE_ISHIFTX) || ((cached_type == TYPE_ISHIFT1) || ((cached_type == TYPE_ROTATE) || ((cached_type == TYPE_ROTATEX) || ((cached_type == TYPE_ROTATE1) || ((cached_type == TYPE_IMUL) || ((cached_type == TYPE_ICMP) || ((cached_type == TYPE_PUSH) || (cached_type == TYPE_POP)))))))))))))
	    {
	      return 
#line 373 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_immediate_default (insn, true));
	    }
	  else if ((cached_type == TYPE_IMOV) || (cached_type == TYPE_TEST))
	    {
	      return 
#line 375 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_immediate_default (insn, false));
	    }
	  else if (cached_type == TYPE_CALL)
	    {
	      if (constant_call_address_operand (operands[0], VOIDmode))
	        {
		  return 4;
	        }
	      else
	        {
		  return 0;
	        }
	    }
	  else if (cached_type == TYPE_CALLV)
	    {
	      if (constant_call_address_operand (operands[1], VOIDmode))
	        {
		  return 4;
	        }
	      else
	        {
		  return 0;
	        }
	    }
	  else if (cached_type == TYPE_IBR)
	    {
	      return 1;
	    }
	  else
	    {
	      return 
#line 389 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(/* Update immediate_length and other attributes! */
		      gcc_unreachable (),1);
	    }
        }

    case 573:  /* split_stack_return */
      extract_insn_cached (insn);
      if (const0_operand (operands[0], SImode))
        {
	  return 0;
        }
      else
        {
	  return 2;
        }

    case 789:  /* pro_epilogue_adjust_stack_si_add */
    case 790:  /* pro_epilogue_adjust_stack_di_add */
      extract_constrain_insn_cached (insn);
      if ((cached_type = get_attr_type (insn)) == TYPE_IMOV)
        {
	  return 0;
        }
      else if ((cached_type == TYPE_ALU) && (const128_operand (operands[2], VOIDmode)))
        {
	  return 1;
        }
      else
        {
	  if ((cached_type == TYPE_INCDEC) || ((cached_type == TYPE_SETCC) || ((cached_type == TYPE_ICMOV) || ((cached_type == TYPE_STR) || ((cached_type == TYPE_LEA) || ((cached_type == TYPE_OTHER) || ((cached_type == TYPE_MULTI) || ((cached_type == TYPE_IDIV) || ((cached_type == TYPE_LEAVE) || ((cached_type == TYPE_BITMANIP) || (cached_type == TYPE_IMULX)))))))))))
	    {
	      return 0;
	    }
	  else if (((cached_unit = get_attr_unit (insn)) == UNIT_I387) || ((cached_unit == UNIT_SSE) || (cached_unit == UNIT_MMX)))
	    {
	      return 0;
	    }
	  else if ((cached_type == TYPE_ALU) || ((cached_type == TYPE_ALU1) || ((cached_type == TYPE_NEGNOT) || ((cached_type == TYPE_IMOVX) || ((cached_type == TYPE_ISHIFT) || ((cached_type == TYPE_ISHIFTX) || ((cached_type == TYPE_ISHIFT1) || ((cached_type == TYPE_ROTATE) || ((cached_type == TYPE_ROTATEX) || ((cached_type == TYPE_ROTATE1) || ((cached_type == TYPE_IMUL) || ((cached_type == TYPE_ICMP) || ((cached_type == TYPE_PUSH) || (cached_type == TYPE_POP))))))))))))))
	    {
	      return 
#line 373 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_immediate_default (insn, true));
	    }
	  else if (cached_type == TYPE_TEST)
	    {
	      return 
#line 375 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_immediate_default (insn, false));
	    }
	  else if (cached_type == TYPE_CALL)
	    {
	      if (constant_call_address_operand (operands[0], VOIDmode))
	        {
		  return 4;
	        }
	      else
	        {
		  return 0;
	        }
	    }
	  else if (cached_type == TYPE_CALLV)
	    {
	      if (constant_call_address_operand (operands[1], VOIDmode))
	        {
		  return 4;
	        }
	      else
	        {
		  return 0;
	        }
	    }
	  else if (cached_type == TYPE_IBR)
	    {
	      return 1;
	    }
	  else
	    {
	      return 
#line 389 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(/* Update immediate_length and other attributes! */
		      gcc_unreachable (),1);
	    }
        }

    case 895:  /* mmx_ashrv4hi3 */
    case 896:  /* mmx_ashrv2si3 */
    case 897:  /* mmx_ashlv4hi3 */
    case 898:  /* mmx_lshrv4hi3 */
    case 899:  /* mmx_ashlv2si3 */
    case 900:  /* mmx_lshrv2si3 */
    case 901:  /* mmx_ashlv1di3 */
    case 902:  /* mmx_lshrv1di3 */
    case 1308:  /* ashrv16hi3 */
    case 1309:  /* ashrv8hi3 */
    case 1310:  /* ashrv8si3 */
    case 1311:  /* ashrv4si3 */
    case 1312:  /* ashlv16hi3 */
    case 1313:  /* lshrv16hi3 */
    case 1314:  /* ashlv8hi3 */
    case 1315:  /* lshrv8hi3 */
    case 1316:  /* ashlv8si3 */
    case 1317:  /* lshrv8si3 */
    case 1318:  /* ashlv4si3 */
    case 1319:  /* lshrv4si3 */
    case 1320:  /* ashlv4di3 */
    case 1321:  /* lshrv4di3 */
    case 1322:  /* ashlv2di3 */
    case 1323:  /* lshrv2di3 */
      extract_insn_cached (insn);
      if (const_int_operand (operands[2], VOIDmode))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 1219:  /* vec_dupv4sf */
    case 1438:  /* *vec_dupv4si */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return 1;
        }
      else if (which_alternative == 1)
        {
	  return 0;
        }
      else
        {
	  return 1;
        }

    case 563:  /* simple_return_pop_internal */
    case 1516:  /* sse4a_extrqi */
    case 1518:  /* sse4a_insertqi */
      return 2;

    case 541:  /* jump */
    case 504:  /* *jcc_2 */
    case 503:  /* *jcc_1 */
    case 74:  /* *movsi_or */
    case 328:  /* *testqi_ext_0 */
    case 341:  /* andqi_ext_0 */
    case 342:  /* *andqi_ext_0_cc */
    case 373:  /* *iorqi_ext_0 */
    case 374:  /* *xorqi_ext_0 */
    case 501:  /* setcc_sf_sse */
    case 502:  /* setcc_df_sse */
    case 930:  /* *mmx_pinsrw */
    case 931:  /* mmx_pextrw */
    case 932:  /* mmx_pshufw_1 */
    case 934:  /* *vec_dupv4hi */
    case 1066:  /* avx_cmpv8sf3 */
    case 1067:  /* avx_cmpv4sf3 */
    case 1068:  /* avx_cmpv4df3 */
    case 1069:  /* avx_cmpv2df3 */
    case 1070:  /* avx_vmcmpv4sf3 */
    case 1071:  /* avx_vmcmpv2df3 */
    case 1072:  /* *avx_maskcmpv8sf3_comm */
    case 1073:  /* *sse_maskcmpv4sf3_comm */
    case 1074:  /* *avx_maskcmpv4df3_comm */
    case 1075:  /* *sse2_maskcmpv2df3_comm */
    case 1076:  /* avx_maskcmpv8sf3 */
    case 1077:  /* sse_maskcmpv4sf3 */
    case 1078:  /* avx_maskcmpv4df3 */
    case 1079:  /* sse2_maskcmpv2df3 */
    case 1208:  /* avx_shufps256_1 */
    case 1209:  /* sse_shufps_v4si */
    case 1210:  /* sse_shufps_v4sf */
    case 1225:  /* *vec_setv4sf_sse4_1 */
    case 1226:  /* sse4_1_insertps */
    case 1232:  /* vec_extract_hi_v4di */
    case 1233:  /* vec_extract_hi_v4df */
    case 1236:  /* vec_extract_hi_v8si */
    case 1237:  /* vec_extract_hi_v8sf */
    case 1239:  /* vec_extract_hi_v16hi */
    case 1241:  /* vec_extract_hi_v32qi */
    case 1246:  /* avx_shufpd256_1 */
    case 1251:  /* sse2_shufpd_v2di */
    case 1252:  /* sse2_shufpd_v2df */
    case 1324:  /* avx2_ashlv2ti3 */
    case 1325:  /* sse2_ashlv1ti3 */
    case 1326:  /* avx2_lshrv2ti3 */
    case 1327:  /* sse2_lshrv1ti3 */
    case 1418:  /* sse4_1_pinsrb */
    case 1419:  /* sse2_pinsrw */
    case 1420:  /* sse4_1_pinsrd */
    case 1421:  /* sse4_1_pinsrq */
    case 1422:  /* *sse4_1_pextrb_si */
    case 1423:  /* *sse4_1_pextrb_memory */
    case 1424:  /* *sse2_pextrw_si */
    case 1425:  /* *sse4_1_pextrw_memory */
    case 1426:  /* *sse4_1_pextrd */
    case 1427:  /* avx2_pshufd_1 */
    case 1428:  /* sse2_pshufd_1 */
    case 1429:  /* avx2_pshuflw_1 */
    case 1430:  /* sse2_pshuflw_1 */
    case 1431:  /* avx2_pshufhw_1 */
    case 1432:  /* sse2_pshufhw_1 */
    case 1500:  /* avx2_palignrv2ti */
    case 1501:  /* ssse3_palignrti */
    case 1502:  /* ssse3_palignrdi */
    case 1520:  /* avx_blendps256 */
    case 1521:  /* sse4_1_blendps */
    case 1522:  /* avx_blendpd256 */
    case 1523:  /* sse4_1_blendpd */
    case 1524:  /* avx_blendvps256 */
    case 1525:  /* sse4_1_blendvps */
    case 1526:  /* avx_blendvpd256 */
    case 1527:  /* sse4_1_blendvpd */
    case 1528:  /* avx_dpps256 */
    case 1529:  /* sse4_1_dpps */
    case 1530:  /* avx_dppd256 */
    case 1531:  /* sse4_1_dppd */
    case 1534:  /* avx2_mpsadbw */
    case 1535:  /* sse4_1_mpsadbw */
    case 1540:  /* sse4_1_pblendw */
    case 1541:  /* *avx2_pblendw */
    case 1542:  /* avx2_pblenddv8si */
    case 1543:  /* avx2_pblenddv4si */
    case 1575:  /* avx_roundps256 */
    case 1576:  /* sse4_1_roundps */
    case 1577:  /* avx_roundpd256 */
    case 1578:  /* sse4_1_roundpd */
    case 1579:  /* sse4_1_roundss */
    case 1580:  /* sse4_1_roundsd */
    case 1581:  /* sse4_2_pcmpestr */
    case 1582:  /* *sse4_2_pcmpestr_unaligned */
    case 1583:  /* sse4_2_pcmpestri */
    case 1584:  /* sse4_2_pcmpestrm */
    case 1585:  /* sse4_2_pcmpestr_cconly */
    case 1586:  /* sse4_2_pcmpistr */
    case 1587:  /* *sse4_2_pcmpistr_unaligned */
    case 1588:  /* sse4_2_pcmpistri */
    case 1589:  /* sse4_2_pcmpistrm */
    case 1590:  /* sse4_2_pcmpistr_cconly */
    case 1634:  /* xop_rotlv16qi3 */
    case 1635:  /* xop_rotlv8hi3 */
    case 1636:  /* xop_rotlv4si3 */
    case 1637:  /* xop_rotlv2di3 */
    case 1638:  /* xop_rotrv16qi3 */
    case 1639:  /* xop_rotrv8hi3 */
    case 1640:  /* xop_rotrv4si3 */
    case 1641:  /* xop_rotrv2di3 */
    case 1662:  /* xop_maskcmpv16qi3 */
    case 1663:  /* xop_maskcmpv8hi3 */
    case 1664:  /* xop_maskcmpv4si3 */
    case 1665:  /* xop_maskcmpv2di3 */
    case 1666:  /* xop_maskcmp_unsv16qi3 */
    case 1667:  /* xop_maskcmp_unsv8hi3 */
    case 1668:  /* xop_maskcmp_unsv4si3 */
    case 1669:  /* xop_maskcmp_unsv2di3 */
    case 1670:  /* xop_maskcmp_uns2v16qi3 */
    case 1671:  /* xop_maskcmp_uns2v8hi3 */
    case 1672:  /* xop_maskcmp_uns2v4si3 */
    case 1673:  /* xop_maskcmp_uns2v2di3 */
    case 1674:  /* xop_pcom_tfv16qi3 */
    case 1675:  /* xop_pcom_tfv8hi3 */
    case 1676:  /* xop_pcom_tfv4si3 */
    case 1677:  /* xop_pcom_tfv2di3 */
    case 1678:  /* xop_vpermil2v8sf3 */
    case 1679:  /* xop_vpermil2v4sf3 */
    case 1680:  /* xop_vpermil2v4df3 */
    case 1681:  /* xop_vpermil2v2df3 */
    case 1687:  /* aeskeygenassist */
    case 1688:  /* pclmulqdq */
    case 1726:  /* *avx_vpermilpv8sf */
    case 1727:  /* *avx_vpermilpv4sf */
    case 1728:  /* *avx_vpermilpv4df */
    case 1729:  /* *avx_vpermilpv2df */
    case 1734:  /* *avx_vperm2f128v8si_full */
    case 1735:  /* *avx_vperm2f128v8sf_full */
    case 1736:  /* *avx_vperm2f128v4df_full */
    case 1737:  /* *avx_vperm2f128v8si_nozero */
    case 1738:  /* *avx_vperm2f128v8sf_nozero */
    case 1739:  /* *avx_vperm2f128v4df_nozero */
    case 1740:  /* avx2_vec_set_lo_v4di */
    case 1741:  /* avx2_vec_set_hi_v4di */
    case 1742:  /* vec_set_lo_v4di */
    case 1743:  /* vec_set_lo_v4df */
    case 1744:  /* vec_set_hi_v4di */
    case 1745:  /* vec_set_hi_v4df */
    case 1746:  /* vec_set_lo_v8si */
    case 1747:  /* vec_set_lo_v8sf */
    case 1748:  /* vec_set_hi_v8si */
    case 1749:  /* vec_set_hi_v8sf */
    case 1750:  /* vec_set_lo_v16hi */
    case 1751:  /* vec_set_hi_v16hi */
    case 1752:  /* vec_set_lo_v32qi */
    case 1753:  /* vec_set_hi_v32qi */
      return 1;

    case -1:
      if (GET_CODE (PATTERN (insn)) != ASM_INPUT
          && asm_noperands (PATTERN (insn)) < 0)
        fatal_insn_not_found (insn);
      extract_constrain_insn_cached (insn);
      if (((cached_type = get_attr_type (insn)) == TYPE_INCDEC) || ((cached_type == TYPE_SETCC) || ((cached_type == TYPE_ICMOV) || ((cached_type == TYPE_STR) || ((cached_type == TYPE_LEA) || ((cached_type == TYPE_OTHER) || ((cached_type == TYPE_MULTI) || ((cached_type == TYPE_IDIV) || ((cached_type == TYPE_LEAVE) || ((cached_type == TYPE_BITMANIP) || (cached_type == TYPE_IMULX)))))))))))
        {
	  return 0;
        }
      else if (((cached_unit = get_attr_unit (insn)) == UNIT_I387) || ((cached_unit == UNIT_SSE) || (cached_unit == UNIT_MMX)))
        {
	  return 0;
        }
      else if ((cached_type == TYPE_ALU) || ((cached_type == TYPE_ALU1) || ((cached_type == TYPE_NEGNOT) || ((cached_type == TYPE_IMOVX) || ((cached_type == TYPE_ISHIFT) || ((cached_type == TYPE_ISHIFTX) || ((cached_type == TYPE_ISHIFT1) || ((cached_type == TYPE_ROTATE) || ((cached_type == TYPE_ROTATEX) || ((cached_type == TYPE_ROTATE1) || ((cached_type == TYPE_IMUL) || ((cached_type == TYPE_ICMP) || ((cached_type == TYPE_PUSH) || (cached_type == TYPE_POP))))))))))))))
        {
	  return 
#line 373 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_immediate_default (insn, true));
        }
      else if ((cached_type == TYPE_IMOV) || (cached_type == TYPE_TEST))
        {
	  return 
#line 375 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_attr_length_immediate_default (insn, false));
        }
      else if (cached_type == TYPE_CALL)
        {
	  if (constant_call_address_operand (operands[0], VOIDmode))
	    {
	      return 4;
	    }
	  else
	    {
	      return 0;
	    }
        }
      else if (cached_type == TYPE_CALLV)
        {
	  if (constant_call_address_operand (operands[1], VOIDmode))
	    {
	      return 4;
	    }
	  else
	    {
	      return 0;
	    }
        }
      else if (cached_type == TYPE_IBR)
        {
	  return 1;
        }
      else
        {
	  return 
#line 389 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(/* Update immediate_length and other attributes! */
		      gcc_unreachable (),1);
        }

    default:
      return 0;

    }
}

enum attr_movu
get_attr_movu (rtx insn ATTRIBUTE_UNUSED)
{
  switch (recog_memoized (insn))
    {
    case 963:  /* avx_loadups256 */
    case 964:  /* sse_loadups */
    case 965:  /* avx_loadupd256 */
    case 966:  /* sse2_loadupd */
    case 967:  /* avx_storeups256 */
    case 968:  /* sse_storeups */
    case 969:  /* avx_storeupd256 */
    case 970:  /* sse2_storeupd */
    case 971:  /* avx_loaddqu256 */
    case 972:  /* sse2_loaddqu */
    case 973:  /* avx_storedqu256 */
    case 974:  /* sse2_storedqu */
    case 975:  /* avx_lddqu256 */
    case 976:  /* sse3_lddqu */
      return MOVU_1;

    case -1:
      if (GET_CODE (PATTERN (insn)) != ASM_INPUT
          && asm_noperands (PATTERN (insn)) < 0)
        fatal_insn_not_found (insn);
    default:
      return MOVU_0;

    }
}

enum attr_memory
get_attr_memory (rtx insn ATTRIBUTE_UNUSED)
{
  enum attr_type cached_type ATTRIBUTE_UNUSED;

  switch (recog_memoized (insn))
    {
    case 557:  /* *sibcall_value_pop */
    case 556:  /* *call_value_pop */
    case 555:  /* *sibcall_value */
    case 554:  /* *sibcall_value */
    case 553:  /* *call_value */
    case 552:  /* *call_value */
      extract_insn_cached (insn);
      if (constant_call_address_operand (operands[1], VOIDmode))
        {
	  return MEMORY_NONE;
        }
      else
        {
	  return MEMORY_LOAD;
        }

    case 625:  /* *tls_dynamic_gnu2_call_32 */
    case 551:  /* *sibcall_pop */
    case 550:  /* *call_pop */
    case 549:  /* *sibcall */
    case 548:  /* *sibcall */
    case 547:  /* *call */
    case 546:  /* *call */
      extract_insn_cached (insn);
      if (constant_call_address_operand (operands[0], VOIDmode))
        {
	  return MEMORY_NONE;
        }
      else
        {
	  return MEMORY_LOAD;
        }

    case 564:  /* simple_return_indirect_internal */
    case 545:  /* *tablejump_1 */
    case 544:  /* *tablejump_1 */
    case 543:  /* *indirect_jump */
    case 542:  /* *indirect_jump */
    case 541:  /* jump */
    case 504:  /* *jcc_2 */
    case 503:  /* *jcc_1 */
      extract_insn_cached (insn);
      if (memory_operand (operands[0], VOIDmode))
        {
	  return MEMORY_LOAD;
        }
      else
        {
	  return MEMORY_NONE;
        }

    case 500:  /* *setcc_qi_slp */
    case 499:  /* *setcc_qi */
      extract_insn_cached (insn);
      if (memory_operand (operands[0], VOIDmode))
        {
	  return MEMORY_STORE;
        }
      else
        {
	  return MEMORY_NONE;
        }

    case 72:  /* *popdi1_epilogue */
    case 71:  /* *popsi1_epilogue */
    case 70:  /* *popdi1 */
    case 69:  /* *popsi1 */
      extract_insn_cached (insn);
      if (memory_operand (operands[0], VOIDmode))
        {
	  return MEMORY_BOTH;
        }
      else
        {
	  return MEMORY_LOAD;
        }

    case 68:  /* *pushdi2_prologue */
    case 67:  /* *pushsi2_prologue */
    case 66:  /* *pushhi2 */
    case 65:  /* *pushqi2 */
    case 64:  /* *pushsi2 */
      extract_insn_cached (insn);
      if (memory_operand (operands[1], VOIDmode))
        {
	  return MEMORY_BOTH;
        }
      else
        {
	  return MEMORY_STORE;
        }

    case 1677:  /* xop_pcom_tfv2di3 */
    case 1676:  /* xop_pcom_tfv4si3 */
    case 1675:  /* xop_pcom_tfv8hi3 */
    case 1674:  /* xop_pcom_tfv16qi3 */
    case 1673:  /* xop_maskcmp_uns2v2di3 */
    case 1672:  /* xop_maskcmp_uns2v4si3 */
    case 1671:  /* xop_maskcmp_uns2v8hi3 */
    case 1670:  /* xop_maskcmp_uns2v16qi3 */
    case 1669:  /* xop_maskcmp_unsv2di3 */
    case 1668:  /* xop_maskcmp_unsv4si3 */
    case 1667:  /* xop_maskcmp_unsv8hi3 */
    case 1666:  /* xop_maskcmp_unsv16qi3 */
    case 1574:  /* sse4_1_ptest */
    case 1573:  /* avx_ptest256 */
    case 1572:  /* avx_vtestpd */
    case 1571:  /* avx_vtestpd256 */
    case 1570:  /* avx_vtestps */
    case 1569:  /* avx_vtestps256 */
    case 1367:  /* sse2_gtv4si3 */
    case 1366:  /* sse2_gtv8hi3 */
    case 1365:  /* sse2_gtv16qi3 */
    case 1364:  /* avx2_gtv4di3 */
    case 1363:  /* avx2_gtv8si3 */
    case 1362:  /* avx2_gtv16hi3 */
    case 1361:  /* avx2_gtv32qi3 */
    case 1360:  /* sse4_2_gtv2di3 */
    case 1359:  /* *sse2_eqv4si3 */
    case 1358:  /* *sse2_eqv8hi3 */
    case 1357:  /* *sse2_eqv16qi3 */
    case 1356:  /* *sse4_1_eqv2di3 */
    case 1355:  /* *avx2_eqv4di3 */
    case 1354:  /* *avx2_eqv8si3 */
    case 1353:  /* *avx2_eqv16hi3 */
    case 1352:  /* *avx2_eqv32qi3 */
    case 1085:  /* sse2_ucomi */
    case 1084:  /* sse_ucomi */
    case 1083:  /* sse2_comi */
    case 1082:  /* sse_comi */
    case 1081:  /* sse2_vmmaskcmpv2df3 */
    case 1080:  /* sse_vmmaskcmpv4sf3 */
    case 1079:  /* sse2_maskcmpv2df3 */
    case 1078:  /* avx_maskcmpv4df3 */
    case 1077:  /* sse_maskcmpv4sf3 */
    case 1076:  /* avx_maskcmpv8sf3 */
    case 1075:  /* *sse2_maskcmpv2df3_comm */
    case 1074:  /* *avx_maskcmpv4df3_comm */
    case 1073:  /* *sse_maskcmpv4sf3_comm */
    case 1072:  /* *avx_maskcmpv8sf3_comm */
    case 1071:  /* avx_vmcmpv2df3 */
    case 1070:  /* avx_vmcmpv4sf3 */
    case 1069:  /* avx_cmpv2df3 */
    case 1068:  /* avx_cmpv4df3 */
    case 1067:  /* avx_cmpv4sf3 */
    case 1066:  /* avx_cmpv8sf3 */
    case 908:  /* mmx_gtv2si3 */
    case 907:  /* mmx_gtv4hi3 */
    case 906:  /* mmx_gtv8qi3 */
    case 905:  /* *mmx_eqv2si3 */
    case 904:  /* *mmx_eqv4hi3 */
    case 903:  /* *mmx_eqv8qi3 */
    case 859:  /* mmx_gev2sf3 */
    case 858:  /* mmx_gtv2sf3 */
    case 857:  /* *mmx_eqv2sf3 */
    case 502:  /* setcc_df_sse */
    case 501:  /* setcc_sf_sse */
    case 330:  /* *testqi_ext_2 */
    case 329:  /* *testqi_ext_1 */
    case 328:  /* *testqi_ext_0 */
    case 327:  /* *testsi_1 */
    case 326:  /* *testhi_1 */
    case 325:  /* *testqi_1 */
    case 324:  /* *testqi_1_maybe_si */
    case 293:  /* *subsi3_cconly_overflow */
    case 292:  /* *subhi3_cconly_overflow */
    case 291:  /* *subqi3_cconly_overflow */
    case 62:  /* *cmpiuxf_i387 */
    case 61:  /* *cmpiudf_i387 */
    case 60:  /* *cmpiusf_i387 */
    case 59:  /* *cmpixf_i387 */
    case 58:  /* *cmpidf_i387 */
    case 57:  /* *cmpisf_i387 */
    case 56:  /* *cmpiudf_sse */
    case 55:  /* *cmpiusf_sse */
    case 54:  /* *cmpidf_sse */
    case 53:  /* *cmpisf_sse */
    case 52:  /* *cmpiudf_mixed */
    case 51:  /* *cmpiusf_mixed */
    case 50:  /* *cmpidf_mixed */
    case 49:  /* *cmpisf_mixed */
    case 16:  /* *cmpqi_ext_4 */
    case 15:  /* *cmpqi_ext_3_insn */
    case 14:  /* *cmpqi_ext_2 */
    case 13:  /* *cmpqi_ext_1 */
    case 12:  /* *cmpdi_minus_1 */
    case 11:  /* *cmpsi_minus_1 */
    case 10:  /* *cmphi_minus_1 */
    case 9:  /* *cmpqi_minus_1 */
    case 8:  /* *cmpdi_1 */
    case 7:  /* *cmpsi_1 */
    case 6:  /* *cmphi_1 */
    case 5:  /* *cmpqi_1 */
    case 4:  /* *cmpdi_ccno_1 */
    case 3:  /* *cmpsi_ccno_1 */
    case 2:  /* *cmphi_ccno_1 */
    case 1:  /* *cmpqi_ccno_1 */
      extract_insn_cached (insn);
      if ((memory_operand (operands[0], VOIDmode)) || (memory_operand (operands[1], VOIDmode)))
        {
	  return MEMORY_LOAD;
        }
      else
        {
	  return MEMORY_NONE;
        }

    case 240:  /* *addqi_1_slp */
      extract_insn_cached (insn);
      if (memory_operand (operands[1], VOIDmode))
        {
	  return MEMORY_LOAD;
        }
      else
        {
	  return MEMORY_NONE;
        }

    case 1232:  /* vec_extract_hi_v4di */
    case 1233:  /* vec_extract_hi_v4df */
    case 1236:  /* vec_extract_hi_v8si */
    case 1237:  /* vec_extract_hi_v8sf */
    case 1239:  /* vec_extract_hi_v16hi */
    case 1241:  /* vec_extract_hi_v32qi */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return MEMORY_NONE;
        }
      else
        {
	  return MEMORY_STORE;
        }

    case 1437:  /* *vec_extractv2di_1 */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  if (((cached_type = get_attr_type (insn)) == TYPE_OTHER) || ((cached_type == TYPE_MULTI) || ((cached_type == TYPE_STR) || (cached_type == TYPE_LWP))))
	    {
	      return MEMORY_UNKNOWN;
	    }
	  else if ((cached_type == TYPE_LEA) || ((cached_type == TYPE_FCMOV) || (cached_type == TYPE_FPSPC)))
	    {
	      return MEMORY_NONE;
	    }
	  else if ((cached_type == TYPE_FISTP) || (cached_type == TYPE_LEAVE))
	    {
	      return MEMORY_BOTH;
	    }
	  else if (cached_type == TYPE_FRNDINT)
	    {
	      return MEMORY_LOAD;
	    }
	  else if (cached_type == TYPE_PUSH)
	    {
	      if (memory_operand (operands[1], VOIDmode))
	        {
		  return MEMORY_BOTH;
	        }
	      else
	        {
		  return MEMORY_STORE;
	        }
	    }
	  else if (cached_type == TYPE_POP)
	    {
	      if (memory_operand (operands[0], VOIDmode))
	        {
		  return MEMORY_BOTH;
	        }
	      else
	        {
		  return MEMORY_LOAD;
	        }
	    }
	  else if (cached_type == TYPE_SETCC)
	    {
	      if (memory_operand (operands[0], VOIDmode))
	        {
		  return MEMORY_STORE;
	        }
	      else
	        {
		  return MEMORY_NONE;
	        }
	    }
	  else if ((cached_type == TYPE_ICMP) || ((cached_type == TYPE_TEST) || ((cached_type == TYPE_SSECMP) || ((cached_type == TYPE_SSECOMI) || ((cached_type == TYPE_MMXCMP) || (cached_type == TYPE_FCMP))))))
	    {
	      if ((memory_operand (operands[0], VOIDmode)) || (memory_operand (operands[1], VOIDmode)))
	        {
		  return MEMORY_LOAD;
	        }
	      else
	        {
		  return MEMORY_NONE;
	        }
	    }
	  else if (cached_type == TYPE_IBR)
	    {
	      if (memory_operand (operands[0], VOIDmode))
	        {
		  return MEMORY_LOAD;
	        }
	      else
	        {
		  return MEMORY_NONE;
	        }
	    }
	  else if (cached_type == TYPE_CALL)
	    {
	      if (constant_call_address_operand (operands[0], VOIDmode))
	        {
		  return MEMORY_NONE;
	        }
	      else
	        {
		  return MEMORY_LOAD;
	        }
	    }
	  else if (cached_type == TYPE_CALLV)
	    {
	      if (constant_call_address_operand (operands[1], VOIDmode))
	        {
		  return MEMORY_NONE;
	        }
	      else
	        {
		  return MEMORY_LOAD;
	        }
	    }
	  else if (((cached_type == TYPE_ALU1) || ((cached_type == TYPE_NEGNOT) || ((cached_type == TYPE_ISHIFT1) || ((cached_type == TYPE_SSELOG1) || (cached_type == TYPE_SSESHUF1))))) && (memory_operand (operands[1], VOIDmode)))
	    {
	      return MEMORY_BOTH;
	    }
	  else if ((memory_operand (operands[0], VOIDmode)) && (memory_operand (operands[1], VOIDmode)))
	    {
	      return MEMORY_BOTH;
	    }
	  else if (memory_operand (operands[0], VOIDmode))
	    {
	      return MEMORY_STORE;
	    }
	  else if (memory_operand (operands[1], VOIDmode))
	    {
	      return MEMORY_LOAD;
	    }
	  else if (((cached_type == TYPE_ICMOV) || ((cached_type == TYPE_SSEMULADD) || (cached_type == TYPE_SSE4ARG))) && (memory_operand (operands[3], VOIDmode)))
	    {
	      return MEMORY_LOAD;
	    }
	  else
	    {
	      return MEMORY_NONE;
	    }
        }
      else if (which_alternative == 1)
        {
	  return MEMORY_NONE;
        }
      else if (which_alternative == 2)
        {
	  return MEMORY_NONE;
        }
      else if (which_alternative == 3)
        {
	  if (((cached_type = get_attr_type (insn)) == TYPE_OTHER) || ((cached_type == TYPE_MULTI) || ((cached_type == TYPE_STR) || (cached_type == TYPE_LWP))))
	    {
	      return MEMORY_UNKNOWN;
	    }
	  else if ((cached_type == TYPE_LEA) || ((cached_type == TYPE_FCMOV) || (cached_type == TYPE_FPSPC)))
	    {
	      return MEMORY_NONE;
	    }
	  else if ((cached_type == TYPE_FISTP) || (cached_type == TYPE_LEAVE))
	    {
	      return MEMORY_BOTH;
	    }
	  else if (cached_type == TYPE_FRNDINT)
	    {
	      return MEMORY_LOAD;
	    }
	  else if (cached_type == TYPE_PUSH)
	    {
	      if (memory_operand (operands[1], VOIDmode))
	        {
		  return MEMORY_BOTH;
	        }
	      else
	        {
		  return MEMORY_STORE;
	        }
	    }
	  else if (cached_type == TYPE_POP)
	    {
	      if (memory_operand (operands[0], VOIDmode))
	        {
		  return MEMORY_BOTH;
	        }
	      else
	        {
		  return MEMORY_LOAD;
	        }
	    }
	  else if (cached_type == TYPE_SETCC)
	    {
	      if (memory_operand (operands[0], VOIDmode))
	        {
		  return MEMORY_STORE;
	        }
	      else
	        {
		  return MEMORY_NONE;
	        }
	    }
	  else if ((cached_type == TYPE_ICMP) || ((cached_type == TYPE_TEST) || ((cached_type == TYPE_SSECMP) || ((cached_type == TYPE_SSECOMI) || ((cached_type == TYPE_MMXCMP) || (cached_type == TYPE_FCMP))))))
	    {
	      if ((memory_operand (operands[0], VOIDmode)) || (memory_operand (operands[1], VOIDmode)))
	        {
		  return MEMORY_LOAD;
	        }
	      else
	        {
		  return MEMORY_NONE;
	        }
	    }
	  else if (cached_type == TYPE_IBR)
	    {
	      if (memory_operand (operands[0], VOIDmode))
	        {
		  return MEMORY_LOAD;
	        }
	      else
	        {
		  return MEMORY_NONE;
	        }
	    }
	  else if (cached_type == TYPE_CALL)
	    {
	      if (constant_call_address_operand (operands[0], VOIDmode))
	        {
		  return MEMORY_NONE;
	        }
	      else
	        {
		  return MEMORY_LOAD;
	        }
	    }
	  else if (cached_type == TYPE_CALLV)
	    {
	      if (constant_call_address_operand (operands[1], VOIDmode))
	        {
		  return MEMORY_NONE;
	        }
	      else
	        {
		  return MEMORY_LOAD;
	        }
	    }
	  else if (((cached_type == TYPE_ALU1) || ((cached_type == TYPE_NEGNOT) || ((cached_type == TYPE_ISHIFT1) || ((cached_type == TYPE_SSELOG1) || (cached_type == TYPE_SSESHUF1))))) && (memory_operand (operands[1], VOIDmode)))
	    {
	      return MEMORY_BOTH;
	    }
	  else if ((memory_operand (operands[0], VOIDmode)) && (memory_operand (operands[1], VOIDmode)))
	    {
	      return MEMORY_BOTH;
	    }
	  else if (memory_operand (operands[0], VOIDmode))
	    {
	      return MEMORY_STORE;
	    }
	  else if (memory_operand (operands[1], VOIDmode))
	    {
	      return MEMORY_LOAD;
	    }
	  else if (((cached_type == TYPE_ICMOV) || ((cached_type == TYPE_SSEMULADD) || (cached_type == TYPE_SSE4ARG))) && (memory_operand (operands[3], VOIDmode)))
	    {
	      return MEMORY_LOAD;
	    }
	  else
	    {
	      return MEMORY_NONE;
	    }
        }
      else if (which_alternative == 4)
        {
	  if (((cached_type = get_attr_type (insn)) == TYPE_OTHER) || ((cached_type == TYPE_MULTI) || ((cached_type == TYPE_STR) || (cached_type == TYPE_LWP))))
	    {
	      return MEMORY_UNKNOWN;
	    }
	  else if ((cached_type == TYPE_LEA) || ((cached_type == TYPE_FCMOV) || (cached_type == TYPE_FPSPC)))
	    {
	      return MEMORY_NONE;
	    }
	  else if ((cached_type == TYPE_FISTP) || (cached_type == TYPE_LEAVE))
	    {
	      return MEMORY_BOTH;
	    }
	  else if (cached_type == TYPE_FRNDINT)
	    {
	      return MEMORY_LOAD;
	    }
	  else if (cached_type == TYPE_PUSH)
	    {
	      if (memory_operand (operands[1], VOIDmode))
	        {
		  return MEMORY_BOTH;
	        }
	      else
	        {
		  return MEMORY_STORE;
	        }
	    }
	  else if (cached_type == TYPE_POP)
	    {
	      if (memory_operand (operands[0], VOIDmode))
	        {
		  return MEMORY_BOTH;
	        }
	      else
	        {
		  return MEMORY_LOAD;
	        }
	    }
	  else if (cached_type == TYPE_SETCC)
	    {
	      if (memory_operand (operands[0], VOIDmode))
	        {
		  return MEMORY_STORE;
	        }
	      else
	        {
		  return MEMORY_NONE;
	        }
	    }
	  else if ((cached_type == TYPE_ICMP) || ((cached_type == TYPE_TEST) || ((cached_type == TYPE_SSECMP) || ((cached_type == TYPE_SSECOMI) || ((cached_type == TYPE_MMXCMP) || (cached_type == TYPE_FCMP))))))
	    {
	      if ((memory_operand (operands[0], VOIDmode)) || (memory_operand (operands[1], VOIDmode)))
	        {
		  return MEMORY_LOAD;
	        }
	      else
	        {
		  return MEMORY_NONE;
	        }
	    }
	  else if (cached_type == TYPE_IBR)
	    {
	      if (memory_operand (operands[0], VOIDmode))
	        {
		  return MEMORY_LOAD;
	        }
	      else
	        {
		  return MEMORY_NONE;
	        }
	    }
	  else if (cached_type == TYPE_CALL)
	    {
	      if (constant_call_address_operand (operands[0], VOIDmode))
	        {
		  return MEMORY_NONE;
	        }
	      else
	        {
		  return MEMORY_LOAD;
	        }
	    }
	  else if (cached_type == TYPE_CALLV)
	    {
	      if (constant_call_address_operand (operands[1], VOIDmode))
	        {
		  return MEMORY_NONE;
	        }
	      else
	        {
		  return MEMORY_LOAD;
	        }
	    }
	  else if (((cached_type == TYPE_ALU1) || ((cached_type == TYPE_NEGNOT) || ((cached_type == TYPE_ISHIFT1) || ((cached_type == TYPE_SSELOG1) || (cached_type == TYPE_SSESHUF1))))) && (memory_operand (operands[1], VOIDmode)))
	    {
	      return MEMORY_BOTH;
	    }
	  else if ((memory_operand (operands[0], VOIDmode)) && (memory_operand (operands[1], VOIDmode)))
	    {
	      return MEMORY_BOTH;
	    }
	  else if (memory_operand (operands[0], VOIDmode))
	    {
	      return MEMORY_STORE;
	    }
	  else if (memory_operand (operands[1], VOIDmode))
	    {
	      return MEMORY_LOAD;
	    }
	  else if (((cached_type == TYPE_ICMOV) || ((cached_type == TYPE_SSEMULADD) || (cached_type == TYPE_SSE4ARG))) && (memory_operand (operands[3], VOIDmode)))
	    {
	      return MEMORY_LOAD;
	    }
	  else
	    {
	      return MEMORY_NONE;
	    }
        }
      else
        {
	  if (((cached_type = get_attr_type (insn)) == TYPE_OTHER) || ((cached_type == TYPE_MULTI) || ((cached_type == TYPE_STR) || (cached_type == TYPE_LWP))))
	    {
	      return MEMORY_UNKNOWN;
	    }
	  else if ((cached_type == TYPE_LEA) || ((cached_type == TYPE_FCMOV) || (cached_type == TYPE_FPSPC)))
	    {
	      return MEMORY_NONE;
	    }
	  else if ((cached_type == TYPE_FISTP) || (cached_type == TYPE_LEAVE))
	    {
	      return MEMORY_BOTH;
	    }
	  else if (cached_type == TYPE_FRNDINT)
	    {
	      return MEMORY_LOAD;
	    }
	  else if (cached_type == TYPE_PUSH)
	    {
	      if (memory_operand (operands[1], VOIDmode))
	        {
		  return MEMORY_BOTH;
	        }
	      else
	        {
		  return MEMORY_STORE;
	        }
	    }
	  else if (cached_type == TYPE_POP)
	    {
	      if (memory_operand (operands[0], VOIDmode))
	        {
		  return MEMORY_BOTH;
	        }
	      else
	        {
		  return MEMORY_LOAD;
	        }
	    }
	  else if (cached_type == TYPE_SETCC)
	    {
	      if (memory_operand (operands[0], VOIDmode))
	        {
		  return MEMORY_STORE;
	        }
	      else
	        {
		  return MEMORY_NONE;
	        }
	    }
	  else if ((cached_type == TYPE_ICMP) || ((cached_type == TYPE_TEST) || ((cached_type == TYPE_SSECMP) || ((cached_type == TYPE_SSECOMI) || ((cached_type == TYPE_MMXCMP) || (cached_type == TYPE_FCMP))))))
	    {
	      if ((memory_operand (operands[0], VOIDmode)) || (memory_operand (operands[1], VOIDmode)))
	        {
		  return MEMORY_LOAD;
	        }
	      else
	        {
		  return MEMORY_NONE;
	        }
	    }
	  else if (cached_type == TYPE_IBR)
	    {
	      if (memory_operand (operands[0], VOIDmode))
	        {
		  return MEMORY_LOAD;
	        }
	      else
	        {
		  return MEMORY_NONE;
	        }
	    }
	  else if (cached_type == TYPE_CALL)
	    {
	      if (constant_call_address_operand (operands[0], VOIDmode))
	        {
		  return MEMORY_NONE;
	        }
	      else
	        {
		  return MEMORY_LOAD;
	        }
	    }
	  else if (cached_type == TYPE_CALLV)
	    {
	      if (constant_call_address_operand (operands[1], VOIDmode))
	        {
		  return MEMORY_NONE;
	        }
	      else
	        {
		  return MEMORY_LOAD;
	        }
	    }
	  else if (((cached_type == TYPE_ALU1) || ((cached_type == TYPE_NEGNOT) || ((cached_type == TYPE_ISHIFT1) || ((cached_type == TYPE_SSELOG1) || (cached_type == TYPE_SSESHUF1))))) && (memory_operand (operands[1], VOIDmode)))
	    {
	      return MEMORY_BOTH;
	    }
	  else if ((memory_operand (operands[0], VOIDmode)) && (memory_operand (operands[1], VOIDmode)))
	    {
	      return MEMORY_BOTH;
	    }
	  else if (memory_operand (operands[0], VOIDmode))
	    {
	      return MEMORY_STORE;
	    }
	  else if (memory_operand (operands[1], VOIDmode))
	    {
	      return MEMORY_LOAD;
	    }
	  else if (((cached_type == TYPE_ICMOV) || ((cached_type == TYPE_SSEMULADD) || (cached_type == TYPE_SSE4ARG))) && (memory_operand (operands[3], VOIDmode)))
	    {
	      return MEMORY_LOAD;
	    }
	  else
	    {
	      return MEMORY_NONE;
	    }
        }

    case 1581:  /* sse4_2_pcmpestr */
    case 1583:  /* sse4_2_pcmpestri */
    case 1584:  /* sse4_2_pcmpestrm */
    case 1586:  /* sse4_2_pcmpistr */
    case 1588:  /* sse4_2_pcmpistri */
    case 1589:  /* sse4_2_pcmpistrm */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return MEMORY_NONE;
        }
      else
        {
	  return MEMORY_LOAD;
        }

    case 1585:  /* sse4_2_pcmpestr_cconly */
    case 1590:  /* sse4_2_pcmpistr_cconly */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return MEMORY_NONE;
        }
      else if (which_alternative == 1)
        {
	  return MEMORY_LOAD;
        }
      else if (which_alternative == 2)
        {
	  return MEMORY_NONE;
        }
      else
        {
	  return MEMORY_LOAD;
        }

    case 1905:  /* atomic_xorsi */
    case 1904:  /* atomic_orsi */
    case 1903:  /* atomic_andsi */
    case 1902:  /* atomic_xorhi */
    case 1901:  /* atomic_orhi */
    case 1900:  /* atomic_andhi */
    case 1899:  /* atomic_xorqi */
    case 1898:  /* atomic_orqi */
    case 1897:  /* atomic_andqi */
    case 1896:  /* atomic_subsi */
    case 1895:  /* atomic_subhi */
    case 1894:  /* atomic_subqi */
    case 1893:  /* atomic_addsi */
    case 1892:  /* atomic_addhi */
    case 1891:  /* atomic_addqi */
    case 1890:  /* atomic_exchangesi */
    case 1889:  /* atomic_exchangehi */
    case 1888:  /* atomic_exchangeqi */
    case 1887:  /* *atomic_fetch_add_cmpsi */
    case 1886:  /* *atomic_fetch_add_cmphi */
    case 1885:  /* *atomic_fetch_add_cmpqi */
    case 1884:  /* atomic_fetch_addsi */
    case 1883:  /* atomic_fetch_addhi */
    case 1882:  /* atomic_fetch_addqi */
    case 1881:  /* atomic_compare_and_swapdi_doubleword */
    case 1880:  /* atomic_compare_and_swapsi_1 */
    case 1879:  /* atomic_compare_and_swaphi_1 */
    case 1878:  /* atomic_compare_and_swapqi_1 */
    case 1875:  /* atomic_storedi_fpu */
    case 1874:  /* atomic_storesi_1 */
    case 1873:  /* atomic_storehi_1 */
    case 1872:  /* atomic_storeqi_1 */
    case 1871:  /* atomic_loaddi_fpu */
    case 1772:  /* avx_pd256_pd */
    case 1771:  /* avx_ps256_ps */
    case 1770:  /* avx_si256_si */
    case 1725:  /* *avx_vperm_broadcast_v4df */
    case 1724:  /* *avx_vperm_broadcast_v8sf */
    case 1463:  /* sse3_monitor */
    case 1462:  /* sse3_mwait */
    case 1436:  /* *sse2_storeq */
    case 1435:  /* *vec_ext_v4si_mem */
    case 1434:  /* sse2_stored */
    case 1240:  /* vec_extract_lo_v32qi */
    case 1238:  /* vec_extract_lo_v16hi */
    case 1235:  /* vec_extract_lo_v8sf */
    case 1234:  /* vec_extract_lo_v8si */
    case 1231:  /* vec_extract_lo_v4df */
    case 1230:  /* vec_extract_lo_v4di */
    case 1229:  /* *vec_extract_v4sf_mem */
    case 1227:  /* *vec_extractv4sf_0 */
    case 987:  /* *absnegv2df2 */
    case 986:  /* *absnegv4df2 */
    case 985:  /* *absnegv4sf2 */
    case 984:  /* *absnegv8sf2 */
    case 962:  /* movdi_to_sse */
    case 937:  /* *vec_extractv2si_0 */
    case 867:  /* *vec_extractv2sf_0 */
    case 835:  /* xtest_1 */
    case 834:  /* xabort */
    case 833:  /* xend */
    case 832:  /* xbegin_1 */
    case 830:  /* rdseedsi_1 */
    case 829:  /* rdseedhi_1 */
    case 828:  /* rdrandsi_1 */
    case 827:  /* rdrandhi_1 */
    case 826:  /* *lwp_lwpinssi3_1 */
    case 825:  /* *lwp_lwpvalsi3_1 */
    case 824:  /* lwp_slwpcbdi */
    case 823:  /* lwp_slwpcbsi */
    case 822:  /* *lwp_llwpcbdi1 */
    case 821:  /* *lwp_llwpcbsi1 */
    case 815:  /* rdtscp */
    case 814:  /* rdtsc */
    case 813:  /* rdpmc */
    case 809:  /* stack_tls_protect_test_di */
    case 808:  /* stack_tls_protect_test_si */
    case 807:  /* stack_protect_test_di */
    case 806:  /* stack_protect_test_si */
    case 805:  /* stack_tls_protect_set_di */
    case 804:  /* stack_tls_protect_set_si */
    case 803:  /* stack_protect_set_di */
    case 802:  /* stack_protect_set_si */
    case 799:  /* trap */
    case 798:  /* probe_stack_rangedi */
    case 797:  /* probe_stack_rangesi */
    case 796:  /* adjust_stack_and_probedi */
    case 795:  /* adjust_stack_and_probesi */
    case 794:  /* allocate_stack_worker_probe_di */
    case 793:  /* allocate_stack_worker_probe_si */
    case 769:  /* *strlenqi_1 */
    case 768:  /* *strlenqi_1 */
    case 767:  /* *cmpstrnqi_1 */
    case 766:  /* *cmpstrnqi_1 */
    case 765:  /* *cmpstrnqi_nz_1 */
    case 764:  /* *cmpstrnqi_nz_1 */
    case 743:  /* cld */
    case 741:  /* fxamdf2_i387_with_temp */
    case 740:  /* fxamsf2_i387_with_temp */
    case 739:  /* fxamxf2_i387 */
    case 738:  /* fxamdf2_i387 */
    case 737:  /* fxamsf2_i387 */
    case 626:  /* *tls_dynamic_gnu2_combine_32 */
    case 615:  /* *tls_local_dynamic_32_once */
    case 614:  /* *tls_local_dynamic_base_32_gnu */
    case 613:  /* *tls_global_dynamic_32_gnu */
    case 612:  /* *parityhi2_cmp */
    case 611:  /* paritysi2_cmp */
    case 610:  /* paritydi2_cmp */
    case 609:  /* bswaphi_lowpart */
    case 608:  /* *bswaphi_lowpart_1 */
    case 574:  /* ffssi2_no_cmove */
    case 573:  /* split_stack_return */
    case 571:  /* eh_return_internal */
    case 569:  /* set_got_labelled */
    case 568:  /* set_got */
    case 567:  /* pad */
    case 566:  /* nops */
    case 565:  /* nop */
    case 563:  /* simple_return_pop_internal */
    case 562:  /* simple_return_internal_long */
    case 561:  /* simple_return_internal */
    case 560:  /* prologue_use */
    case 559:  /* *memory_blockage */
    case 558:  /* blockage */
    case 540:  /* *jccxf_si_r_i387 */
    case 539:  /* *jccdf_si_r_i387 */
    case 538:  /* *jccsf_si_r_i387 */
    case 537:  /* *jccxf_hi_r_i387 */
    case 536:  /* *jccdf_hi_r_i387 */
    case 535:  /* *jccsf_hi_r_i387 */
    case 534:  /* *jccxf_si_i387 */
    case 533:  /* *jccdf_si_i387 */
    case 532:  /* *jccsf_si_i387 */
    case 531:  /* *jccxf_hi_i387 */
    case 530:  /* *jccdf_hi_i387 */
    case 529:  /* *jccsf_hi_i387 */
    case 528:  /* *jccuxf_r_i387 */
    case 527:  /* *jccudf_r_i387 */
    case 526:  /* *jccusf_r_i387 */
    case 525:  /* *jccuxf_i387 */
    case 524:  /* *jccudf_i387 */
    case 523:  /* *jccusf_i387 */
    case 522:  /* *jccdf_r_i387 */
    case 521:  /* *jccsf_r_i387 */
    case 520:  /* *jccdf_i387 */
    case 519:  /* *jccsf_i387 */
    case 518:  /* *jccxf_r_i387 */
    case 517:  /* *jccxf_i387 */
    case 516:  /* *jccxf_0_r_i387 */
    case 515:  /* *jccdf_0_r_i387 */
    case 514:  /* *jccsf_0_r_i387 */
    case 513:  /* *jccxf_0_i387 */
    case 512:  /* *jccdf_0_i387 */
    case 511:  /* *jccsf_0_i387 */
    case 510:  /* *jcc_btsi_mask_1 */
    case 509:  /* *jcc_btsi_1 */
    case 508:  /* *jcc_btdi_mask */
    case 507:  /* *jcc_btsi_mask */
    case 506:  /* *jcc_btdi */
    case 505:  /* *jcc_btsi */
    case 498:  /* *setcc_si_1_movzbl */
    case 497:  /* *setcc_si_1_and */
    case 483:  /* ix86_rotrdi3_doubleword */
    case 482:  /* ix86_rotldi3_doubleword */
    case 447:  /* *ashrdi3_doubleword */
    case 446:  /* *lshrdi3_doubleword */
    case 424:  /* *ashldi3_doubleword */
    case 415:  /* copysigntf3_var */
    case 414:  /* copysigndf3_var */
    case 413:  /* copysignsf3_var */
    case 412:  /* copysigntf3_const */
    case 411:  /* copysigndf3_const */
    case 410:  /* copysignsf3_const */
    case 397:  /* *absnegtf2_sse */
    case 396:  /* *absnegxf2_i387 */
    case 395:  /* *absnegdf2_i387 */
    case 394:  /* *absnegsf2_i387 */
    case 393:  /* *absnegdf2_sse */
    case 392:  /* *absnegsf2_sse */
    case 391:  /* *absnegdf2_mixed */
    case 390:  /* *absnegsf2_mixed */
    case 381:  /* *negti2_doubleword */
    case 380:  /* *negdi2_doubleword */
    case 331:  /* *testqi_ext_3 */
    case 320:  /* *udivmodsi4 */
    case 319:  /* *udivmodhi4 */
    case 318:  /* udivmodsi4_1 */
    case 314:  /* *divmodsi4 */
    case 313:  /* *divmodhi4 */
    case 312:  /* divmodsi4_1 */
    case 264:  /* *subti3_doubleword */
    case 263:  /* *subdi3_doubleword */
    case 232:  /* *addti3_doubleword */
    case 231:  /* *adddi3_doubleword */
    case 229:  /* *floatunssixf2_1 */
    case 228:  /* *floatunssidf2_1 */
    case 227:  /* *floatunssisf2_1 */
    case 226:  /* floatdixf2_i387_with_xmm */
    case 225:  /* floatdidf2_i387_with_xmm */
    case 224:  /* floatdisf2_i387_with_xmm */
    case 183:  /* *floatdixf2_1 */
    case 182:  /* *floatdidf2_1 */
    case 181:  /* *floatdisf2_1 */
    case 180:  /* *floatsixf2_1 */
    case 179:  /* *floatsidf2_1 */
    case 178:  /* *floatsisf2_1 */
    case 171:  /* *floathixf2_1 */
    case 170:  /* *floathidf2_1 */
    case 169:  /* *floathisf2_1 */
    case 168:  /* x86_fldcw_1 */
    case 167:  /* x86_fnstcw_1 */
    case 146:  /* *fixuns_truncdf_1 */
    case 145:  /* *fixuns_truncsf_1 */
    case 124:  /* extendsidi2_1 */
    case 108:  /* *pushdf */
    case 107:  /* *pushxf_nointeger */
    case 106:  /* *pushxf */
    case 105:  /* *pushtf */
    case 63:  /* *pushdi2 */
    case 48:  /* x86_sahf_1 */
    case 47:  /* x86_fnstsw_1 */
    case 46:  /* *cmpxf_si_cc_i387 */
    case 45:  /* *cmpdf_si_cc_i387 */
    case 44:  /* *cmpsf_si_cc_i387 */
    case 43:  /* *cmpxf_hi_cc_i387 */
    case 42:  /* *cmpdf_hi_cc_i387 */
    case 41:  /* *cmpsf_hi_cc_i387 */
    case 40:  /* *cmpxf_si_i387 */
    case 39:  /* *cmpdf_si_i387 */
    case 38:  /* *cmpsf_si_i387 */
    case 37:  /* *cmpxf_hi_i387 */
    case 36:  /* *cmpdf_hi_i387 */
    case 35:  /* *cmpsf_hi_i387 */
    case 34:  /* *cmpuxf_cc_i387 */
    case 33:  /* *cmpudf_cc_i387 */
    case 32:  /* *cmpusf_cc_i387 */
    case 31:  /* *cmpuxf_i387 */
    case 30:  /* *cmpudf_i387 */
    case 29:  /* *cmpusf_i387 */
    case 28:  /* *cmpdf_cc_i387 */
    case 27:  /* *cmpsf_cc_i387 */
    case 26:  /* *cmpdf_i387 */
    case 25:  /* *cmpsf_i387 */
    case 24:  /* *cmpxf_cc_i387 */
    case 23:  /* *cmpxf_i387 */
    case 22:  /* *cmpxf_0_cc_i387 */
    case 21:  /* *cmpdf_0_cc_i387 */
    case 20:  /* *cmpsf_0_cc_i387 */
    case 19:  /* *cmpxf_0_i387 */
    case 18:  /* *cmpdf_0_i387 */
    case 17:  /* *cmpsf_0_i387 */
    case 831:  /* *pause */
    case 1461:  /* sse2_clflush */
    case 1867:  /* *sse2_lfence */
    case 1868:  /* *sse_sfence */
    case 1869:  /* mfence_sse2 */
    case 1870:  /* mfence_nosse */
      return MEMORY_UNKNOWN;

    case 736:  /* fistsi2_ceil_with_temp */
    case 735:  /* fistsi2_floor_with_temp */
    case 734:  /* fisthi2_ceil_with_temp */
    case 733:  /* fisthi2_floor_with_temp */
    case 732:  /* fistsi2_ceil */
    case 731:  /* fistsi2_floor */
    case 730:  /* fisthi2_ceil */
    case 729:  /* fisthi2_floor */
    case 728:  /* fistdi2_ceil_with_temp */
    case 727:  /* fistdi2_floor_with_temp */
    case 726:  /* fistdi2_ceil */
    case 725:  /* fistdi2_floor */
    case 724:  /* *fistdi2_ceil_1 */
    case 723:  /* *fistdi2_floor_1 */
    case 722:  /* *fistsi2_ceil_1 */
    case 721:  /* *fistsi2_floor_1 */
    case 720:  /* *fisthi2_ceil_1 */
    case 719:  /* *fisthi2_floor_1 */
    case 572:  /* leave */
    case 166:  /* fix_truncsi_i387_with_temp */
    case 165:  /* fix_trunchi_i387_with_temp */
    case 164:  /* fix_truncsi_i387 */
    case 163:  /* fix_trunchi_i387 */
    case 162:  /* fix_truncdi_i387_with_temp */
    case 161:  /* fix_truncdi_i387 */
    case 160:  /* *fix_truncdi_i387_1 */
    case 159:  /* *fix_truncsi_i387_1 */
    case 158:  /* *fix_trunchi_i387_1 */
    case 744:  /* *strmovsi_1 */
    case 745:  /* *strmovsi_1 */
    case 746:  /* *strmovhi_1 */
    case 747:  /* *strmovhi_1 */
    case 748:  /* *strmovqi_1 */
    case 749:  /* *strmovqi_1 */
    case 750:  /* *rep_movsi */
    case 751:  /* *rep_movsi */
    case 752:  /* *rep_movqi */
    case 753:  /* *rep_movqi */
      return MEMORY_BOTH;

    case 81:  /* *movabsqi_1 */
    case 82:  /* *movabshi_1 */
    case 83:  /* *movabssi_1 */
    case 84:  /* *movabsdi_1 */
    case 754:  /* *strsetsi_1 */
    case 755:  /* *strsetsi_1 */
    case 756:  /* *strsethi_1 */
    case 757:  /* *strsethi_1 */
    case 758:  /* *strsetqi_1 */
    case 759:  /* *strsetqi_1 */
    case 760:  /* *rep_stossi */
    case 761:  /* *rep_stossi */
    case 762:  /* *rep_stosqi */
    case 763:  /* *rep_stosqi */
    case 816:  /* fxsave */
    case 818:  /* xsave */
    case 819:  /* xsaveopt */
    case 1460:  /* sse_stmxcsr */
      return MEMORY_STORE;

    case 718:  /* frndintxf2_mask_pm_i387 */
    case 717:  /* frndintxf2_mask_pm */
    case 716:  /* frndintxf2_trunc_i387 */
    case 715:  /* frndintxf2_ceil_i387 */
    case 714:  /* frndintxf2_floor_i387 */
    case 713:  /* frndintxf2_trunc */
    case 712:  /* frndintxf2_ceil */
    case 711:  /* frndintxf2_floor */
    case 85:  /* *movabsqi_2 */
    case 86:  /* *movabshi_2 */
    case 87:  /* *movabssi_2 */
    case 88:  /* *movabsdi_2 */
    case 616:  /* *load_tp_x32 */
    case 617:  /* *load_tp_x32_zext */
    case 618:  /* *load_tp_si */
    case 619:  /* *load_tp_di */
    case 620:  /* *add_tp_x32 */
    case 621:  /* *add_tp_x32_zext */
    case 622:  /* *add_tp_si */
    case 623:  /* *add_tp_di */
    case 817:  /* fxrstor */
    case 820:  /* xrstor */
    case 1459:  /* sse_ldmxcsr */
    case 1582:  /* *sse4_2_pcmpestr_unaligned */
    case 1587:  /* *sse4_2_pcmpistr_unaligned */
      return MEMORY_LOAD;

    case 776:  /* *movxfcc_1 */
    case 710:  /* fistsi2_with_temp */
    case 709:  /* fisthi2_with_temp */
    case 708:  /* fistsi2 */
    case 707:  /* fisthi2 */
    case 706:  /* *fistsi2_1 */
    case 705:  /* *fisthi2_1 */
    case 704:  /* fistdi2_with_temp */
    case 703:  /* fistdi2 */
    case 702:  /* *fistdi2_1 */
    case 701:  /* rintxf2 */
    case 698:  /* *fscalexf4_i387 */
    case 697:  /* *f2xm1xf2_i387 */
    case 696:  /* fxtract_extenddfxf3_i387 */
    case 695:  /* fxtract_extendsfxf3_i387 */
    case 694:  /* fxtractxf3_i387 */
    case 693:  /* fyl2xp1_extenddfxf3_i387 */
    case 692:  /* fyl2xp1_extendsfxf3_i387 */
    case 691:  /* fyl2xp1xf3_i387 */
    case 690:  /* fyl2x_extenddfxf3_i387 */
    case 689:  /* fyl2x_extendsfxf3_i387 */
    case 688:  /* fyl2xxf3_i387 */
    case 687:  /* fpatan_extenddfxf3_i387 */
    case 686:  /* fpatan_extendsfxf3_i387 */
    case 685:  /* *fpatanxf3_i387 */
    case 684:  /* fptan_extenddfxf4_i387 */
    case 683:  /* fptan_extendsfxf4_i387 */
    case 682:  /* fptanxf4_i387 */
    case 681:  /* sincos_extenddfxf3_i387 */
    case 680:  /* sincos_extendsfxf3_i387 */
    case 679:  /* sincosxf3 */
    case 678:  /* *cos_extenddfxf2_i387 */
    case 677:  /* *sin_extenddfxf2_i387 */
    case 676:  /* *cos_extendsfxf2_i387 */
    case 675:  /* *sin_extendsfxf2_i387 */
    case 674:  /* *cosxf2_i387 */
    case 673:  /* *sinxf2_i387 */
    case 672:  /* fprem1xf4_i387 */
    case 671:  /* fpremxf4_i387 */
    case 667:  /* sqrt_extenddfxf2_i387 */
    case 666:  /* sqrt_extendsfxf2_i387 */
    case 665:  /* sqrtxf2 */
    case 624:  /* *tls_dynamic_gnu2_lea_32 */
    case 262:  /* *lea_general_4 */
    case 261:  /* *lea_general_4 */
    case 260:  /* *lea_general_3 */
    case 259:  /* *lea_general_2 */
    case 258:  /* *lea_general_1 */
    case 230:  /* *leasi */
    case 770:  /* *x86_movsicc_0_m1 */
    case 771:  /* *x86_movsicc_0_m1_se */
    case 772:  /* *x86_movsicc_0_m1_neg */
    case 800:  /* *prefetch_sse */
    case 801:  /* *prefetch_3dnow */
    case 945:  /* *mmx_emms */
    case 946:  /* *mmx_femms */
    case 1689:  /* *avx_vzeroall */
    case 1690:  /* avx_vzeroupper */
      return MEMORY_NONE;

    case -1:
      if (GET_CODE (PATTERN (insn)) != ASM_INPUT
          && asm_noperands (PATTERN (insn)) < 0)
        fatal_insn_not_found (insn);
    default:
      extract_insn_cached (insn);
      if (((cached_type = get_attr_type (insn)) == TYPE_OTHER) || ((cached_type == TYPE_MULTI) || ((cached_type == TYPE_STR) || (cached_type == TYPE_LWP))))
        {
	  return MEMORY_UNKNOWN;
        }
      else if ((cached_type == TYPE_LEA) || ((cached_type == TYPE_FCMOV) || (cached_type == TYPE_FPSPC)))
        {
	  return MEMORY_NONE;
        }
      else if ((cached_type == TYPE_FISTP) || (cached_type == TYPE_LEAVE))
        {
	  return MEMORY_BOTH;
        }
      else if (cached_type == TYPE_FRNDINT)
        {
	  return MEMORY_LOAD;
        }
      else if (cached_type == TYPE_PUSH)
        {
	  if (memory_operand (operands[1], VOIDmode))
	    {
	      return MEMORY_BOTH;
	    }
	  else
	    {
	      return MEMORY_STORE;
	    }
        }
      else if (cached_type == TYPE_POP)
        {
	  if (memory_operand (operands[0], VOIDmode))
	    {
	      return MEMORY_BOTH;
	    }
	  else
	    {
	      return MEMORY_LOAD;
	    }
        }
      else if (cached_type == TYPE_SETCC)
        {
	  if (memory_operand (operands[0], VOIDmode))
	    {
	      return MEMORY_STORE;
	    }
	  else
	    {
	      return MEMORY_NONE;
	    }
        }
      else if ((cached_type == TYPE_ICMP) || ((cached_type == TYPE_TEST) || ((cached_type == TYPE_SSECMP) || ((cached_type == TYPE_SSECOMI) || ((cached_type == TYPE_MMXCMP) || (cached_type == TYPE_FCMP))))))
        {
	  if ((memory_operand (operands[0], VOIDmode)) || (memory_operand (operands[1], VOIDmode)))
	    {
	      return MEMORY_LOAD;
	    }
	  else
	    {
	      return MEMORY_NONE;
	    }
        }
      else if (cached_type == TYPE_IBR)
        {
	  if (memory_operand (operands[0], VOIDmode))
	    {
	      return MEMORY_LOAD;
	    }
	  else
	    {
	      return MEMORY_NONE;
	    }
        }
      else if (cached_type == TYPE_CALL)
        {
	  if (constant_call_address_operand (operands[0], VOIDmode))
	    {
	      return MEMORY_NONE;
	    }
	  else
	    {
	      return MEMORY_LOAD;
	    }
        }
      else if (cached_type == TYPE_CALLV)
        {
	  if (constant_call_address_operand (operands[1], VOIDmode))
	    {
	      return MEMORY_NONE;
	    }
	  else
	    {
	      return MEMORY_LOAD;
	    }
        }
      else if (((cached_type == TYPE_ALU1) || ((cached_type == TYPE_NEGNOT) || ((cached_type == TYPE_ISHIFT1) || ((cached_type == TYPE_SSELOG1) || (cached_type == TYPE_SSESHUF1))))) && (memory_operand (operands[1], VOIDmode)))
        {
	  return MEMORY_BOTH;
        }
      else if ((memory_operand (operands[0], VOIDmode)) && (memory_operand (operands[1], VOIDmode)))
        {
	  return MEMORY_BOTH;
        }
      else if (memory_operand (operands[0], VOIDmode))
        {
	  return MEMORY_STORE;
        }
      else if (memory_operand (operands[1], VOIDmode))
        {
	  return MEMORY_LOAD;
        }
      else if ((! ((cached_type == TYPE_ALU1) || ((cached_type == TYPE_NEGNOT) || ((cached_type == TYPE_ISHIFT1) || ((cached_type == TYPE_IMOV) || ((cached_type == TYPE_IMOVX) || ((cached_type == TYPE_ICMP) || ((cached_type == TYPE_TEST) || ((cached_type == TYPE_BITMANIP) || ((cached_type == TYPE_FMOV) || ((cached_type == TYPE_FCMP) || ((cached_type == TYPE_FSGN) || ((cached_type == TYPE_SSE) || ((cached_type == TYPE_SSEMOV) || ((cached_type == TYPE_SSECMP) || ((cached_type == TYPE_SSECOMI) || ((cached_type == TYPE_SSECVT) || ((cached_type == TYPE_SSECVT1) || ((cached_type == TYPE_SSEICVT) || ((cached_type == TYPE_SSELOG1) || ((cached_type == TYPE_SSESHUF1) || ((cached_type == TYPE_SSEADD1) || ((cached_type == TYPE_SSEIADD1) || ((cached_type == TYPE_MMX) || ((cached_type == TYPE_MMXMOV) || ((cached_type == TYPE_MMXCMP) || (cached_type == TYPE_MMXCVT))))))))))))))))))))))))))) && (memory_operand (operands[2], VOIDmode)))
        {
	  return MEMORY_LOAD;
        }
      else if (((cached_type == TYPE_ICMOV) || ((cached_type == TYPE_SSEMULADD) || (cached_type == TYPE_SSE4ARG))) && (memory_operand (operands[3], VOIDmode)))
        {
	  return MEMORY_LOAD;
        }
      else
        {
	  return MEMORY_NONE;
        }

    }
}

int
get_attr_modrm (rtx insn ATTRIBUTE_UNUSED)
{
  enum attr_type cached_type ATTRIBUTE_UNUSED;

  switch (recog_memoized (insn))
    {
    case 790:  /* pro_epilogue_adjust_stack_di_add */
      extract_constrain_insn_cached (insn);
      if (((which_alternative == 0) && (! (
#line 16519 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_OPT_AGU)))) && (ax_reg_operand (operands[0], VOIDmode)))
        {
	  return 
#line 521 "../../gcc-4.8.1/gcc/config/i386/i386.md"
((get_attr_length_immediate (insn) <= (get_attr_mode (insn) != MODE_QI)));
        }
      else
        {
	  return 1;
        }

    case 662:  /* *fop_xf_6_i387 */
    case 661:  /* *fop_xf_6_i387 */
    case 660:  /* *fop_xf_5_i387 */
    case 659:  /* *fop_xf_5_i387 */
    case 658:  /* *fop_xf_4_i387 */
    case 657:  /* *fop_xf_4_i387 */
    case 656:  /* *fop_xf_3_i387 */
    case 655:  /* *fop_xf_3_i387 */
    case 654:  /* *fop_xf_2_i387 */
    case 653:  /* *fop_xf_2_i387 */
    case 652:  /* *fop_xf_1_i387 */
    case 651:  /* *fop_xf_comm_i387 */
    case 650:  /* *fop_df_6_i387 */
    case 649:  /* *fop_df_5_i387 */
    case 648:  /* *fop_df_4_i387 */
    case 647:  /* *fop_df_3_i387 */
    case 646:  /* *fop_sf_3_i387 */
    case 645:  /* *fop_df_3_i387 */
    case 644:  /* *fop_sf_3_i387 */
    case 643:  /* *fop_df_2_i387 */
    case 642:  /* *fop_sf_2_i387 */
    case 641:  /* *fop_df_2_i387 */
    case 640:  /* *fop_sf_2_i387 */
    case 639:  /* *fop_df_1_i387 */
    case 638:  /* *fop_sf_1_i387 */
    case 634:  /* *fop_df_1_mixed */
    case 633:  /* *fop_sf_1_mixed */
    case 632:  /* *fop_df_comm_i387 */
    case 631:  /* *fop_sf_comm_i387 */
    case 628:  /* *fop_df_comm_mixed */
    case 627:  /* *fop_sf_comm_mixed */
      if (get_attr_unit (insn) == UNIT_I387)
        {
	  return 0;
        }
      else
        {
	  return 1;
        }

    case 557:  /* *sibcall_value_pop */
    case 556:  /* *call_value_pop */
    case 555:  /* *sibcall_value */
    case 554:  /* *sibcall_value */
    case 553:  /* *call_value */
    case 552:  /* *call_value */
      extract_insn_cached (insn);
      if (constant_call_address_operand (operands[1], VOIDmode))
        {
	  return 0;
        }
      else
        {
	  return 1;
        }

    case 625:  /* *tls_dynamic_gnu2_call_32 */
    case 551:  /* *sibcall_pop */
    case 550:  /* *call_pop */
    case 549:  /* *sibcall */
    case 548:  /* *sibcall */
    case 547:  /* *call */
    case 546:  /* *call */
      extract_insn_cached (insn);
      if (constant_call_address_operand (operands[0], VOIDmode))
        {
	  return 0;
        }
      else
        {
	  return 1;
        }

    case 441:  /* *ashldi3_cconly */
    case 440:  /* *ashlsi3_cconly */
    case 439:  /* *ashlhi3_cconly */
    case 438:  /* *ashlqi3_cconly */
    case 437:  /* *ashldi3_cmp */
    case 436:  /* *ashlsi3_cmp */
    case 435:  /* *ashlhi3_cmp */
    case 434:  /* *ashlqi3_cmp */
    case 433:  /* *ashlqi3_1_slp */
    case 432:  /* *ashlqi3_1 */
    case 431:  /* *ashlhi3_1 */
    case 430:  /* *ashldi3_1 */
    case 429:  /* *ashlsi3_1 */
      extract_constrain_insn_cached (insn);
      if ((get_attr_type (insn) == TYPE_ALU) && (ax_reg_operand (operands[0], VOIDmode)))
        {
	  return 
#line 521 "../../gcc-4.8.1/gcc/config/i386/i386.md"
((get_attr_length_immediate (insn) <= (get_attr_mode (insn) != MODE_QI)));
        }
      else
        {
	  return 1;
        }

    case 333:  /* *andhi_1 */
    case 332:  /* *andsi_1 */
      extract_constrain_insn_cached (insn);
      if ((((1 << which_alternative) & 0x3)) && (ax_reg_operand (operands[0], VOIDmode)))
        {
	  return 
#line 521 "../../gcc-4.8.1/gcc/config/i386/i386.md"
((get_attr_length_immediate (insn) <= (get_attr_mode (insn) != MODE_QI)));
        }
      else
        {
	  return 1;
        }

    case 136:  /* *truncdfsf_mixed */
      extract_constrain_insn_cached (insn);
      if (which_alternative != 1)
        {
	  return 0;
        }
      else
        {
	  return 1;
        }

    case 778:  /* *movsfcc_1_387 */
    case 777:  /* *movdfcc_1 */
    case 189:  /* *floatsidf2_mixed_with_temp */
    case 188:  /* *floatsisf2_mixed_with_temp */
    case 185:  /* *floatsidf2_vector_mixed_with_temp */
    case 184:  /* *floatsisf2_vector_mixed_with_temp */
    case 128:  /* *extendsfdf2_mixed */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return 0;
        }
      else
        {
	  return 1;
        }

    case 112:  /* *movdf_internal */
    case 111:  /* *movxf_internal */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x7))
        {
	  return 0;
        }
      else
        {
	  return 1;
        }

    case 109:  /* *pushsf */
      extract_constrain_insn_cached (insn);
      if ((which_alternative == 0) || ((which_alternative == 1) && (! (memory_operand (operands[1], VOIDmode)))))
        {
	  return 0;
        }
      else
        {
	  return 1;
        }

    case 72:  /* *popdi1_epilogue */
    case 71:  /* *popsi1_epilogue */
    case 70:  /* *popdi1 */
    case 69:  /* *popsi1 */
      extract_insn_cached (insn);
      if (! (memory_operand (operands[0], VOIDmode)))
        {
	  return 0;
        }
      else
        {
	  return 1;
        }

    case 68:  /* *pushdi2_prologue */
    case 67:  /* *pushsi2_prologue */
    case 66:  /* *pushhi2 */
    case 65:  /* *pushqi2 */
    case 64:  /* *pushsi2 */
      extract_insn_cached (insn);
      if (! (memory_operand (operands[1], VOIDmode)))
        {
	  return 0;
        }
      else
        {
	  return 1;
        }

    case 792:  /* pro_epilogue_adjust_stack_di_sub */
    case 791:  /* pro_epilogue_adjust_stack_si_sub */
    case 772:  /* *x86_movsicc_0_m1_neg */
    case 771:  /* *x86_movsicc_0_m1_se */
    case 770:  /* *x86_movsicc_0_m1 */
    case 600:  /* *bsrhi */
    case 599:  /* bsr */
    case 578:  /* ctzsi2 */
    case 577:  /* ctzhi2 */
    case 576:  /* *bsfsi_1 */
    case 575:  /* *tzcntsi_1 */
    case 496:  /* *btdi */
    case 495:  /* *btsi */
    case 423:  /* *one_cmpldi2_2 */
    case 422:  /* *one_cmplsi2_2 */
    case 421:  /* *one_cmplhi2_2 */
    case 420:  /* *one_cmplqi2_2 */
    case 378:  /* *xorqi_ext_2 */
    case 377:  /* *iorqi_ext_2 */
    case 376:  /* *xorqi_ext_1 */
    case 375:  /* *iorqi_ext_1 */
    case 372:  /* *xordi_3 */
    case 371:  /* *iordi_3 */
    case 370:  /* *xorsi_3 */
    case 369:  /* *iorsi_3 */
    case 368:  /* *xorhi_3 */
    case 367:  /* *iorhi_3 */
    case 366:  /* *xorqi_3 */
    case 365:  /* *iorqi_3 */
    case 364:  /* *xorqi_2_slp */
    case 363:  /* *iorqi_2_slp */
    case 362:  /* *xordi_2 */
    case 361:  /* *iordi_2 */
    case 360:  /* *xorsi_2 */
    case 359:  /* *iorsi_2 */
    case 358:  /* *xorhi_2 */
    case 357:  /* *iorhi_2 */
    case 356:  /* *xorqi_2 */
    case 355:  /* *iorqi_2 */
    case 354:  /* *xorqi_1_slp */
    case 353:  /* *iorqi_1_slp */
    case 352:  /* *xorqi_1 */
    case 351:  /* *iorqi_1 */
    case 350:  /* *xordi_1 */
    case 349:  /* *iordi_1 */
    case 348:  /* *xorsi_1 */
    case 347:  /* *iorsi_1 */
    case 346:  /* *xorhi_1 */
    case 345:  /* *iorhi_1 */
    case 344:  /* *andqi_ext_2 */
    case 343:  /* *andqi_ext_1 */
    case 340:  /* *andqi_2_slp */
    case 339:  /* *andsi_2 */
    case 338:  /* *andhi_2 */
    case 337:  /* *andqi_2 */
    case 336:  /* *andqi_2_maybe_si */
    case 335:  /* *andqi_1_slp */
    case 334:  /* *andqi_1 */
    case 330:  /* *testqi_ext_2 */
    case 329:  /* *testqi_ext_1 */
    case 301:  /* *subdi3_cc_overflow */
    case 300:  /* *adddi3_cc_overflow */
    case 299:  /* *subsi3_cc_overflow */
    case 298:  /* *addsi3_cc_overflow */
    case 297:  /* *subhi3_cc_overflow */
    case 296:  /* *addhi3_cc_overflow */
    case 295:  /* *subqi3_cc_overflow */
    case 294:  /* *addqi3_cc_overflow */
    case 293:  /* *subsi3_cconly_overflow */
    case 292:  /* *subhi3_cconly_overflow */
    case 291:  /* *subqi3_cconly_overflow */
    case 290:  /* *addsi3_cconly_overflow */
    case 289:  /* *addhi3_cconly_overflow */
    case 288:  /* *addqi3_cconly_overflow */
    case 287:  /* adcxdi3 */
    case 286:  /* adcxsi3 */
    case 285:  /* *subdi3_carry */
    case 284:  /* *adddi3_carry */
    case 283:  /* *subsi3_carry */
    case 282:  /* *addsi3_carry */
    case 281:  /* *subhi3_carry */
    case 280:  /* *addhi3_carry */
    case 279:  /* *subqi3_carry */
    case 278:  /* *addqi3_carry */
    case 277:  /* *subdi_3 */
    case 276:  /* *subsi_3 */
    case 275:  /* *subhi_3 */
    case 274:  /* *subqi_3 */
    case 273:  /* *subdi_2 */
    case 272:  /* *subsi_2 */
    case 271:  /* *subhi_2 */
    case 270:  /* *subqi_2 */
    case 269:  /* *subqi_1_slp */
    case 268:  /* *subdi_1 */
    case 267:  /* *subsi_1 */
    case 266:  /* *subhi_1 */
    case 265:  /* *subqi_1 */
    case 257:  /* *addqi_ext_2 */
    case 235:  /* addqi3_cc */
    case 234:  /* *adddi3_cc */
    case 233:  /* *addsi3_cc */
    case 122:  /* zero_extendqihi2_and */
    case 119:  /* zero_extendhisi2_and */
    case 118:  /* zero_extendqisi2_and */
    case 97:  /* *movstricthi_xor */
    case 96:  /* *movstrictqi_xor */
    case 74:  /* *movsi_or */
    case 73:  /* *movsi_xor */
    case 16:  /* *cmpqi_ext_4 */
    case 14:  /* *cmpqi_ext_2 */
    case 13:  /* *cmpqi_ext_1 */
    case 12:  /* *cmpdi_minus_1 */
    case 11:  /* *cmpsi_minus_1 */
    case 10:  /* *cmphi_minus_1 */
    case 9:  /* *cmpqi_minus_1 */
    case 8:  /* *cmpdi_1 */
    case 7:  /* *cmpsi_1 */
    case 6:  /* *cmphi_1 */
    case 5:  /* *cmpqi_1 */
    case 4:  /* *cmpdi_ccno_1 */
    case 3:  /* *cmpsi_ccno_1 */
    case 2:  /* *cmphi_ccno_1 */
    case 1:  /* *cmpqi_ccno_1 */
      extract_constrain_insn_cached (insn);
      if (ax_reg_operand (operands[0], VOIDmode))
        {
	  return 
#line 521 "../../gcc-4.8.1/gcc/config/i386/i386.md"
((get_attr_length_immediate (insn) <= (get_attr_mode (insn) != MODE_QI)));
        }
      else
        {
	  return 1;
        }

    case 81:  /* *movabsqi_1 */
    case 82:  /* *movabshi_1 */
    case 83:  /* *movabssi_1 */
    case 85:  /* *movabsqi_2 */
    case 86:  /* *movabshi_2 */
    case 87:  /* *movabssi_2 */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return 0;
        }
      else
        {
	  if (((cached_type = get_attr_type (insn)) == TYPE_STR) || (cached_type == TYPE_LEAVE))
	    {
	      return 0;
	    }
	  else if (get_attr_unit (insn) == UNIT_I387)
	    {
	      return 0;
	    }
	  else if ((cached_type == TYPE_INCDEC) && ((! (
#line 435 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_64BIT))) && ((register_operand (operands[1], SImode)) || (register_operand (operands[1], HImode)))))
	    {
	      return 0;
	    }
	  else if ((cached_type == TYPE_PUSH) && (! (memory_operand (operands[1], VOIDmode))))
	    {
	      return 0;
	    }
	  else if ((cached_type == TYPE_POP) && (! (memory_operand (operands[0], VOIDmode))))
	    {
	      return 0;
	    }
	  else if ((cached_type == TYPE_IMOV) && ((! (get_attr_mode (insn) == MODE_DI)) && (((register_operand (operands[0], VOIDmode)) && (immediate_operand (operands[1], VOIDmode))) || (((ax_reg_operand (operands[0], VOIDmode)) && (memory_displacement_only_operand (operands[1], VOIDmode))) || ((memory_displacement_only_operand (operands[0], VOIDmode)) && (ax_reg_operand (operands[1], VOIDmode)))))))
	    {
	      return 0;
	    }
	  else if ((cached_type == TYPE_CALL) && (constant_call_address_operand (operands[0], VOIDmode)))
	    {
	      return 0;
	    }
	  else if ((cached_type == TYPE_CALLV) && (constant_call_address_operand (operands[1], VOIDmode)))
	    {
	      return 0;
	    }
	  else if (((cached_type == TYPE_ALU) || ((cached_type == TYPE_ALU1) || ((cached_type == TYPE_ICMP) || (cached_type == TYPE_TEST)))) && (ax_reg_operand (operands[0], VOIDmode)))
	    {
	      return 
#line 521 "../../gcc-4.8.1/gcc/config/i386/i386.md"
((get_attr_length_immediate (insn) <= (get_attr_mode (insn) != MODE_QI)));
	    }
	  else
	    {
	      return 1;
	    }
        }

    case 125:  /* extendhisi2 */
    case 127:  /* extendqihi2 */
      if (get_attr_prefix_0f (insn) == 0)
        {
	  return 0;
        }
      else
        {
	  return 1;
        }

    case 606:  /* *bswapsi2_movbe */
    case 327:  /* *testsi_1 */
    case 326:  /* *testhi_1 */
    case 325:  /* *testqi_1 */
    case 324:  /* *testqi_1_maybe_si */
    case 197:  /* *floatdidf2_mixed_nointerunit */
    case 196:  /* *floatsidf2_mixed_nointerunit */
    case 195:  /* *floatdisf2_mixed_nointerunit */
    case 194:  /* *floatsisf2_mixed_nointerunit */
    case 193:  /* *floatdidf2_mixed_interunit */
    case 192:  /* *floatsidf2_mixed_interunit */
    case 191:  /* *floatdisf2_mixed_interunit */
    case 190:  /* *floatsisf2_mixed_interunit */
    case 187:  /* *floatsidf2_vector_mixed */
    case 186:  /* *floatsisf2_vector_mixed */
    case 133:  /* *truncdfsf_fast_mixed */
    case 108:  /* *pushdf */
    case 107:  /* *pushxf_nointeger */
    case 106:  /* *pushxf */
    case 88:  /* *movabsdi_2 */
    case 84:  /* *movabsdi_1 */
    case 52:  /* *cmpiudf_mixed */
    case 51:  /* *cmpiusf_mixed */
    case 50:  /* *cmpidf_mixed */
    case 49:  /* *cmpisf_mixed */
    case 449:  /* ashrsi3_cvt */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return 0;
        }
      else
        {
	  return 1;
        }

    case 1877:  /* storedi_via_fpu */
    case 1876:  /* loaddi_via_fpu */
    case 776:  /* *movxfcc_1 */
    case 769:  /* *strlenqi_1 */
    case 768:  /* *strlenqi_1 */
    case 767:  /* *cmpstrnqi_1 */
    case 766:  /* *cmpstrnqi_1 */
    case 765:  /* *cmpstrnqi_nz_1 */
    case 764:  /* *cmpstrnqi_nz_1 */
    case 763:  /* *rep_stosqi */
    case 762:  /* *rep_stosqi */
    case 761:  /* *rep_stossi */
    case 760:  /* *rep_stossi */
    case 759:  /* *strsetqi_1 */
    case 758:  /* *strsetqi_1 */
    case 757:  /* *strsethi_1 */
    case 756:  /* *strsethi_1 */
    case 755:  /* *strsetsi_1 */
    case 754:  /* *strsetsi_1 */
    case 753:  /* *rep_movqi */
    case 752:  /* *rep_movqi */
    case 751:  /* *rep_movsi */
    case 750:  /* *rep_movsi */
    case 749:  /* *strmovqi_1 */
    case 748:  /* *strmovqi_1 */
    case 747:  /* *strmovhi_1 */
    case 746:  /* *strmovhi_1 */
    case 745:  /* *strmovsi_1 */
    case 744:  /* *strmovsi_1 */
    case 741:  /* fxamdf2_i387_with_temp */
    case 740:  /* fxamsf2_i387_with_temp */
    case 739:  /* fxamxf2_i387 */
    case 738:  /* fxamdf2_i387 */
    case 737:  /* fxamsf2_i387 */
    case 736:  /* fistsi2_ceil_with_temp */
    case 735:  /* fistsi2_floor_with_temp */
    case 734:  /* fisthi2_ceil_with_temp */
    case 733:  /* fisthi2_floor_with_temp */
    case 732:  /* fistsi2_ceil */
    case 731:  /* fistsi2_floor */
    case 730:  /* fisthi2_ceil */
    case 729:  /* fisthi2_floor */
    case 728:  /* fistdi2_ceil_with_temp */
    case 727:  /* fistdi2_floor_with_temp */
    case 726:  /* fistdi2_ceil */
    case 725:  /* fistdi2_floor */
    case 724:  /* *fistdi2_ceil_1 */
    case 723:  /* *fistdi2_floor_1 */
    case 722:  /* *fistsi2_ceil_1 */
    case 721:  /* *fistsi2_floor_1 */
    case 720:  /* *fisthi2_ceil_1 */
    case 719:  /* *fisthi2_floor_1 */
    case 718:  /* frndintxf2_mask_pm_i387 */
    case 717:  /* frndintxf2_mask_pm */
    case 716:  /* frndintxf2_trunc_i387 */
    case 715:  /* frndintxf2_ceil_i387 */
    case 714:  /* frndintxf2_floor_i387 */
    case 713:  /* frndintxf2_trunc */
    case 712:  /* frndintxf2_ceil */
    case 711:  /* frndintxf2_floor */
    case 710:  /* fistsi2_with_temp */
    case 709:  /* fisthi2_with_temp */
    case 708:  /* fistsi2 */
    case 707:  /* fisthi2 */
    case 706:  /* *fistsi2_1 */
    case 705:  /* *fisthi2_1 */
    case 704:  /* fistdi2_with_temp */
    case 703:  /* fistdi2 */
    case 702:  /* *fistdi2_1 */
    case 701:  /* rintxf2 */
    case 698:  /* *fscalexf4_i387 */
    case 697:  /* *f2xm1xf2_i387 */
    case 696:  /* fxtract_extenddfxf3_i387 */
    case 695:  /* fxtract_extendsfxf3_i387 */
    case 694:  /* fxtractxf3_i387 */
    case 693:  /* fyl2xp1_extenddfxf3_i387 */
    case 692:  /* fyl2xp1_extendsfxf3_i387 */
    case 691:  /* fyl2xp1xf3_i387 */
    case 690:  /* fyl2x_extenddfxf3_i387 */
    case 689:  /* fyl2x_extendsfxf3_i387 */
    case 688:  /* fyl2xxf3_i387 */
    case 687:  /* fpatan_extenddfxf3_i387 */
    case 686:  /* fpatan_extendsfxf3_i387 */
    case 685:  /* *fpatanxf3_i387 */
    case 684:  /* fptan_extenddfxf4_i387 */
    case 683:  /* fptan_extendsfxf4_i387 */
    case 682:  /* fptanxf4_i387 */
    case 681:  /* sincos_extenddfxf3_i387 */
    case 680:  /* sincos_extendsfxf3_i387 */
    case 679:  /* sincosxf3 */
    case 678:  /* *cos_extenddfxf2_i387 */
    case 677:  /* *sin_extenddfxf2_i387 */
    case 676:  /* *cos_extendsfxf2_i387 */
    case 675:  /* *sin_extendsfxf2_i387 */
    case 674:  /* *cosxf2_i387 */
    case 673:  /* *sinxf2_i387 */
    case 672:  /* fprem1xf4_i387 */
    case 671:  /* fpremxf4_i387 */
    case 667:  /* sqrt_extenddfxf2_i387 */
    case 666:  /* sqrt_extendsfxf2_i387 */
    case 665:  /* sqrtxf2 */
    case 664:  /* truncxfdf2_i387_noop_unspec */
    case 663:  /* truncxfsf2_i387_noop_unspec */
    case 572:  /* leave */
    case 409:  /* *negextenddfxf2 */
    case 408:  /* *absextenddfxf2 */
    case 407:  /* *negextendsfxf2 */
    case 406:  /* *absextendsfxf2 */
    case 405:  /* *negextendsfdf2 */
    case 404:  /* *absextendsfdf2 */
    case 403:  /* *negxf2_1 */
    case 402:  /* *absxf2_1 */
    case 401:  /* *negdf2_1 */
    case 400:  /* *absdf2_1 */
    case 399:  /* *negsf2_1 */
    case 398:  /* *abssf2_1 */
    case 226:  /* floatdixf2_i387_with_xmm */
    case 225:  /* floatdidf2_i387_with_xmm */
    case 224:  /* floatdisf2_i387_with_xmm */
    case 223:  /* *floatdixf2_i387 */
    case 222:  /* *floatdidf2_i387 */
    case 221:  /* *floatdisf2_i387 */
    case 220:  /* *floatsixf2_i387 */
    case 219:  /* *floatsidf2_i387 */
    case 218:  /* *floatsisf2_i387 */
    case 217:  /* *floatdixf2_i387_with_temp */
    case 216:  /* *floatdidf2_i387_with_temp */
    case 215:  /* *floatdisf2_i387_with_temp */
    case 214:  /* *floatsixf2_i387_with_temp */
    case 213:  /* *floatsidf2_i387_with_temp */
    case 212:  /* *floatsisf2_i387_with_temp */
    case 177:  /* *floathixf2_i387 */
    case 176:  /* *floathidf2_i387 */
    case 175:  /* *floathisf2_i387 */
    case 174:  /* *floathixf2_i387_with_temp */
    case 173:  /* *floathidf2_i387_with_temp */
    case 172:  /* *floathisf2_i387_with_temp */
    case 168:  /* x86_fldcw_1 */
    case 167:  /* x86_fnstcw_1 */
    case 166:  /* fix_truncsi_i387_with_temp */
    case 165:  /* fix_trunchi_i387_with_temp */
    case 164:  /* fix_truncsi_i387 */
    case 163:  /* fix_trunchi_i387 */
    case 162:  /* fix_truncdi_i387_with_temp */
    case 161:  /* fix_truncdi_i387 */
    case 160:  /* *fix_truncdi_i387_1 */
    case 159:  /* *fix_truncsi_i387_1 */
    case 158:  /* *fix_trunchi_i387_1 */
    case 157:  /* fix_truncdi_i387_fisttp_with_temp */
    case 156:  /* fix_truncsi_i387_fisttp_with_temp */
    case 155:  /* fix_trunchi_i387_fisttp_with_temp */
    case 154:  /* fix_truncdi_i387_fisttp */
    case 153:  /* fix_truncsi_i387_fisttp */
    case 152:  /* fix_trunchi_i387_fisttp */
    case 151:  /* fix_truncdi_fisttp_i387_1 */
    case 150:  /* fix_truncsi_fisttp_i387_1 */
    case 149:  /* fix_trunchi_fisttp_i387_1 */
    case 144:  /* *truncxfdf2_i387 */
    case 143:  /* *truncxfsf2_i387 */
    case 142:  /* truncxfdf2_i387_noop */
    case 141:  /* truncxfsf2_i387_noop */
    case 140:  /* *truncxfdf2_mixed */
    case 139:  /* *truncxfsf2_mixed */
    case 138:  /* *truncdfsf2_i387_1 */
    case 137:  /* *truncdfsf_i387 */
    case 135:  /* *truncdfsf_fast_i387 */
    case 132:  /* *extenddfxf2_i387 */
    case 131:  /* *extendsfxf2_i387 */
    case 130:  /* *extendsfdf2_i387 */
    case 116:  /* *swapdf */
    case 115:  /* *swapsf */
    case 114:  /* swapxf */
    case 62:  /* *cmpiuxf_i387 */
    case 61:  /* *cmpiudf_i387 */
    case 60:  /* *cmpiusf_i387 */
    case 59:  /* *cmpixf_i387 */
    case 58:  /* *cmpidf_i387 */
    case 57:  /* *cmpisf_i387 */
    case 47:  /* x86_fnstsw_1 */
    case 46:  /* *cmpxf_si_cc_i387 */
    case 45:  /* *cmpdf_si_cc_i387 */
    case 44:  /* *cmpsf_si_cc_i387 */
    case 43:  /* *cmpxf_hi_cc_i387 */
    case 42:  /* *cmpdf_hi_cc_i387 */
    case 41:  /* *cmpsf_hi_cc_i387 */
    case 40:  /* *cmpxf_si_i387 */
    case 39:  /* *cmpdf_si_i387 */
    case 38:  /* *cmpsf_si_i387 */
    case 37:  /* *cmpxf_hi_i387 */
    case 36:  /* *cmpdf_hi_i387 */
    case 35:  /* *cmpsf_hi_i387 */
    case 34:  /* *cmpuxf_cc_i387 */
    case 33:  /* *cmpudf_cc_i387 */
    case 32:  /* *cmpusf_cc_i387 */
    case 31:  /* *cmpuxf_i387 */
    case 30:  /* *cmpudf_i387 */
    case 29:  /* *cmpusf_i387 */
    case 28:  /* *cmpdf_cc_i387 */
    case 27:  /* *cmpsf_cc_i387 */
    case 26:  /* *cmpdf_i387 */
    case 25:  /* *cmpsf_i387 */
    case 24:  /* *cmpxf_cc_i387 */
    case 23:  /* *cmpxf_i387 */
    case 22:  /* *cmpxf_0_cc_i387 */
    case 21:  /* *cmpdf_0_cc_i387 */
    case 20:  /* *cmpsf_0_cc_i387 */
    case 19:  /* *cmpxf_0_i387 */
    case 18:  /* *cmpdf_0_i387 */
    case 17:  /* *cmpsf_0_i387 */
    case 503:  /* *jcc_1 */
    case 504:  /* *jcc_2 */
    case 541:  /* jump */
    case 561:  /* simple_return_internal */
    case 562:  /* simple_return_internal_long */
    case 563:  /* simple_return_pop_internal */
    case 565:  /* nop */
    case 566:  /* nops */
    case 573:  /* split_stack_return */
    case 607:  /* *bswapsi2 */
    case 616:  /* *load_tp_x32 */
    case 617:  /* *load_tp_x32_zext */
    case 618:  /* *load_tp_si */
    case 619:  /* *load_tp_di */
    case 620:  /* *add_tp_x32 */
    case 621:  /* *add_tp_x32_zext */
    case 622:  /* *add_tp_si */
    case 623:  /* *add_tp_di */
    case 743:  /* cld */
    case 945:  /* *mmx_emms */
    case 946:  /* *mmx_femms */
    case 1689:  /* *avx_vzeroall */
    case 1690:  /* avx_vzeroupper */
      return 0;

    case -1:
      if (GET_CODE (PATTERN (insn)) != ASM_INPUT
          && asm_noperands (PATTERN (insn)) < 0)
        fatal_insn_not_found (insn);
    case 78:  /* *movsi_internal */
    case 79:  /* *movhi_internal */
    case 80:  /* *movqi_internal */
    case 89:  /* swapsi */
    case 90:  /* *swapqi_1 */
    case 91:  /* *swaphi_1 */
    case 92:  /* *swapqi_2 */
    case 93:  /* *swaphi_2 */
    case 94:  /* *movstrictqi_1 */
    case 95:  /* *movstricthi_1 */
    case 100:  /* *movqi_extv_1 */
    case 102:  /* *movqi_extzv_2 */
    case 103:  /* *movsi_insv_1 */
    case 104:  /* *movqi_insv_2 */
    case 113:  /* *movsf_internal */
    case 236:  /* *addsi_1 */
    case 237:  /* *adddi_1 */
    case 238:  /* *addhi_1 */
    case 239:  /* *addqi_1 */
    case 240:  /* *addqi_1_slp */
    case 241:  /* *addqi_2 */
    case 242:  /* *addhi_2 */
    case 243:  /* *addsi_2 */
    case 244:  /* *adddi_2 */
    case 245:  /* *addqi_3 */
    case 246:  /* *addhi_3 */
    case 247:  /* *addsi_3 */
    case 248:  /* *adddi_3 */
    case 249:  /* *addqi_4 */
    case 250:  /* *addhi_4 */
    case 251:  /* *addsi_4 */
    case 252:  /* *addqi_5 */
    case 253:  /* *addhi_5 */
    case 254:  /* *addsi_5 */
    case 255:  /* *adddi_5 */
    case 789:  /* pro_epilogue_adjust_stack_si_add */
    case 868:  /* *vec_extractv2sf_1 */
    case 938:  /* *vec_extractv2si_1 */
    case 1223:  /* vec_setv4si_0 */
    case 1224:  /* vec_setv4sf_0 */
    case 1253:  /* sse2_storehpd */
    case 1255:  /* sse2_storelpd */
    case 1257:  /* sse2_loadhpd */
    case 1258:  /* sse2_loadlpd */
      extract_constrain_insn_cached (insn);
      if (((cached_type = get_attr_type (insn)) == TYPE_STR) || (cached_type == TYPE_LEAVE))
        {
	  return 0;
        }
      else if (get_attr_unit (insn) == UNIT_I387)
        {
	  return 0;
        }
      else if ((cached_type == TYPE_INCDEC) && ((! (
#line 435 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_64BIT))) && ((register_operand (operands[1], SImode)) || (register_operand (operands[1], HImode)))))
        {
	  return 0;
        }
      else if ((cached_type == TYPE_PUSH) && (! (memory_operand (operands[1], VOIDmode))))
        {
	  return 0;
        }
      else if ((cached_type == TYPE_POP) && (! (memory_operand (operands[0], VOIDmode))))
        {
	  return 0;
        }
      else if ((cached_type == TYPE_IMOV) && ((! (get_attr_mode (insn) == MODE_DI)) && (((register_operand (operands[0], VOIDmode)) && (immediate_operand (operands[1], VOIDmode))) || (((ax_reg_operand (operands[0], VOIDmode)) && (memory_displacement_only_operand (operands[1], VOIDmode))) || ((memory_displacement_only_operand (operands[0], VOIDmode)) && (ax_reg_operand (operands[1], VOIDmode)))))))
        {
	  return 0;
        }
      else if ((cached_type == TYPE_CALL) && (constant_call_address_operand (operands[0], VOIDmode)))
        {
	  return 0;
        }
      else if ((cached_type == TYPE_CALLV) && (constant_call_address_operand (operands[1], VOIDmode)))
        {
	  return 0;
        }
      else if (((cached_type == TYPE_ALU) || ((cached_type == TYPE_ALU1) || ((cached_type == TYPE_ICMP) || (cached_type == TYPE_TEST)))) && (ax_reg_operand (operands[0], VOIDmode)))
        {
	  return 
#line 521 "../../gcc-4.8.1/gcc/config/i386/i386.md"
((get_attr_length_immediate (insn) <= (get_attr_mode (insn) != MODE_QI)));
        }
      else
        {
	  return 1;
        }

    default:
      return 1;

    }
}

enum attr_mode
get_attr_mode (rtx insn ATTRIBUTE_UNUSED)
{
  enum attr_type cached_type ATTRIBUTE_UNUSED;

  switch (recog_memoized (insn))
    {
    case 1444:  /* vec_concatv2di */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0xf))
        {
	  return MODE_TI;
        }
      else if (which_alternative == 4)
        {
	  return MODE_V4SF;
        }
      else
        {
	  return MODE_V2SF;
        }

    case 1443:  /* *vec_concatv4si */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return MODE_TI;
        }
      else if (which_alternative == 2)
        {
	  return MODE_V4SF;
        }
      else
        {
	  return MODE_V2SF;
        }

    case 1442:  /* *vec_concatv2si_sse */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return MODE_V4SF;
        }
      else
        {
	  return MODE_DI;
        }

    case 1441:  /* *vec_concatv2si_sse2 */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return MODE_TI;
        }
      else
        {
	  return MODE_DI;
        }

    case 1440:  /* *vec_concatv2si_sse4_1 */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x1f))
        {
	  return MODE_TI;
        }
      else
        {
	  return MODE_DI;
        }

    case 1439:  /* *vec_dupv2di */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return MODE_TI;
        }
      else if (which_alternative == 2)
        {
	  return MODE_DF;
        }
      else
        {
	  return MODE_V4SF;
        }

    case 1438:  /* *vec_dupv4si */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return MODE_TI;
        }
      else
        {
	  return MODE_V4SF;
        }

    case 1437:  /* *vec_extractv2di_1 */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return MODE_V2SF;
        }
      else if (((1 << which_alternative) & 0xe))
        {
	  return MODE_TI;
        }
      else if (which_alternative == 4)
        {
	  return MODE_V4SF;
        }
      else
        {
	  return MODE_V2SF;
        }

    case 1433:  /* sse2_loadld */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return MODE_TI;
        }
      else if (which_alternative == 2)
        {
	  return MODE_V4SF;
        }
      else
        {
	  return MODE_SF;
        }

    case 1261:  /* *vec_concatv2df */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return MODE_V2DF;
        }
      else if (which_alternative == 2)
        {
	  return MODE_DF;
        }
      else if (((1 << which_alternative) & 0x18))
        {
	  return MODE_V1DF;
        }
      else if (which_alternative == 5)
        {
	  return MODE_DF;
        }
      else if (which_alternative == 6)
        {
	  return MODE_V4SF;
        }
      else
        {
	  return MODE_V2SF;
        }

    case 1259:  /* sse2_movsd */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return MODE_DF;
        }
      else if (((1 << which_alternative) & 0x1c))
        {
	  return MODE_V1DF;
        }
      else if (which_alternative == 5)
        {
	  return MODE_V2DF;
        }
      else
        {
	  return MODE_V1DF;
        }

    case 1258:  /* sse2_loadlpd */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return MODE_DF;
        }
      else if (((1 << which_alternative) & 0x1e))
        {
	  return MODE_V1DF;
        }
      else if (which_alternative == 5)
        {
	  return MODE_V2DF;
        }
      else if (((1 << which_alternative) & 0xc0))
        {
	  return MODE_V1DF;
        }
      else
        {
	  return MODE_DF;
        }

    case 1257:  /* sse2_loadhpd */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return MODE_V1DF;
        }
      else if (((1 << which_alternative) & 0xc))
        {
	  return MODE_V2DF;
        }
      else
        {
	  return MODE_DF;
        }

    case 1255:  /* sse2_storelpd */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return MODE_V1DF;
        }
      else
        {
	  return MODE_DF;
        }

    case 1253:  /* sse2_storehpd */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return MODE_V1DF;
        }
      else if (which_alternative == 2)
        {
	  return MODE_V2DF;
        }
      else
        {
	  return MODE_DF;
        }

    case 1245:  /* *vec_interleave_lowv2df */
    case 1243:  /* *vec_interleave_highv2df */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return MODE_V2DF;
        }
      else if (which_alternative == 2)
        {
	  return MODE_DF;
        }
      else
        {
	  return MODE_V1DF;
        }

    case 1228:  /* *sse4_1_extractps */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return MODE_V4SF;
        }
      else
        {
	  return MODE_UNKNOWN;
        }

    case 1224:  /* vec_setv4sf_0 */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return MODE_SF;
        }
      else if (which_alternative == 2)
        {
	  return MODE_SI;
        }
      else if (((1 << which_alternative) & 0x38))
        {
	  return MODE_SF;
        }
      else if (((1 << which_alternative) & 0xc0))
        {
	  return MODE_TI;
        }
      else
        {
	  return MODE_UNKNOWN;
        }

    case 1223:  /* vec_setv4si_0 */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return MODE_SF;
        }
      else if (((1 << which_alternative) & 0x6))
        {
	  return MODE_SI;
        }
      else if (((1 << which_alternative) & 0x38))
        {
	  return MODE_SF;
        }
      else if (((1 << which_alternative) & 0xc0))
        {
	  return MODE_TI;
        }
      else
        {
	  return MODE_UNKNOWN;
        }

    case 1221:  /* *vec_concatv2sf_sse */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return MODE_V4SF;
        }
      else if (which_alternative == 1)
        {
	  return MODE_SF;
        }
      else
        {
	  return MODE_DI;
        }

    case 1220:  /* *vec_concatv2sf_sse4_1 */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0xf))
        {
	  return MODE_V4SF;
        }
      else if (which_alternative == 4)
        {
	  return MODE_SF;
        }
      else
        {
	  return MODE_DI;
        }

    case 1212:  /* sse_loadhps */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return MODE_V2SF;
        }
      else if (((1 << which_alternative) & 0xc))
        {
	  return MODE_V4SF;
        }
      else
        {
	  return MODE_V2SF;
        }

    case 1222:  /* *vec_concatv4sf */
    case 1214:  /* sse_loadlps */
    case 1199:  /* sse_movlhps */
    case 1198:  /* sse_movhlps */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return MODE_V4SF;
        }
      else
        {
	  return MODE_V2SF;
        }

    case 956:  /* *movv1ti_internal */
    case 954:  /* *movv2di_internal */
    case 952:  /* *movv4si_internal */
    case 950:  /* *movv8hi_internal */
    case 948:  /* *movv16qi_internal */
      extract_constrain_insn_cached (insn);
      if ((
#line 6498 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_PACKED_SINGLE_INSN_OPTIMAL)) || ((which_alternative == 2) && (
#line 707 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_TYPELESS_STORES))))
        {
	  return MODE_V4SF;
        }
      else if (
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX))
        {
	  return MODE_TI;
        }
      else if ((! (
#line 659 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SSE2))) || (
#line 6508 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(optimize_function_for_size_p (cfun))))
        {
	  return MODE_V4SF;
        }
      else
        {
	  return MODE_TI;
        }

    case 938:  /* *vec_extractv2si_1 */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return MODE_DI;
        }
      else if (((1 << which_alternative) & 0x6))
        {
	  return MODE_TI;
        }
      else if (which_alternative == 3)
        {
	  return MODE_V4SF;
        }
      else
        {
	  return MODE_SI;
        }

    case 868:  /* *vec_extractv2sf_1 */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return MODE_DI;
        }
      else if (which_alternative == 1)
        {
	  return MODE_V4SF;
        }
      else
        {
	  return MODE_SF;
        }

    case 840:  /* *movv2sf_internal */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3f))
        {
	  return MODE_DI;
        }
      else if (((1 << which_alternative) & 0xc0))
        {
	  return MODE_V4SF;
        }
      else if (((1 << which_alternative) & 0x300))
        {
	  return MODE_V2SF;
        }
      else
        {
	  return MODE_DI;
        }

    case 839:  /* *movv1di_internal */
    case 838:  /* *movv2si_internal */
    case 837:  /* *movv4hi_internal */
    case 836:  /* *movv8qi_internal */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3f))
        {
	  return MODE_DI;
        }
      else if (which_alternative == 6)
        {
	  return MODE_TI;
        }
      else if (((1 << which_alternative) & 0x180))
        {
	  return MODE_DI;
        }
      else if (((1 << which_alternative) & 0x600))
        {
	  return MODE_V4SF;
        }
      else if (((1 << which_alternative) & 0x1800))
        {
	  return MODE_V2SF;
        }
      else
        {
	  return MODE_DI;
        }

    case 778:  /* *movsfcc_1_387 */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return MODE_SF;
        }
      else
        {
	  return MODE_SI;
        }

    case 777:  /* *movdfcc_1 */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return MODE_DF;
        }
      else
        {
	  return MODE_DI;
        }

    case 352:  /* *xorqi_1 */
    case 351:  /* *iorqi_1 */
    case 336:  /* *andqi_2_maybe_si */
    case 334:  /* *andqi_1 */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return MODE_QI;
        }
      else
        {
	  return MODE_SI;
        }

    case 333:  /* *andhi_1 */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return MODE_HI;
        }
      else
        {
	  return MODE_SI;
        }

    case 324:  /* *testqi_1_maybe_si */
    case 239:  /* *addqi_1 */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x7))
        {
	  return MODE_QI;
        }
      else
        {
	  return MODE_SI;
        }

    case 238:  /* *addhi_1 */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x7))
        {
	  return MODE_HI;
        }
      else
        {
	  return MODE_SI;
        }

    case 199:  /* *floatsidf2_vector_sse_with_temp */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return MODE_DF;
        }
      else
        {
	  return MODE_V2DF;
        }

    case 1723:  /* *avx_vperm_broadcast_v4sf */
    case 198:  /* *floatsisf2_vector_sse_with_temp */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return MODE_SF;
        }
      else
        {
	  return MODE_V4SF;
        }

    case 185:  /* *floatsidf2_vector_mixed_with_temp */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0xf))
        {
	  return MODE_DF;
        }
      else
        {
	  return MODE_V2DF;
        }

    case 184:  /* *floatsisf2_vector_mixed_with_temp */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0xf))
        {
	  return MODE_SF;
        }
      else
        {
	  return MODE_V4SF;
        }

    case 117:  /* *zero_extendsidi2 */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x7))
        {
	  return MODE_SI;
        }
      else if (((1 << which_alternative) & 0x18))
        {
	  return MODE_DI;
        }
      else
        {
	  return MODE_TI;
        }

    case 111:  /* *movxf_internal */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x7))
        {
	  return MODE_XF;
        }
      else
        {
	  return MODE_SI;
        }

    case 105:  /* *pushtf */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return MODE_TF;
        }
      else
        {
	  return MODE_SI;
        }

    case 75:  /* *movoi_internal_avx */
      extract_constrain_insn_cached (insn);
      if (
#line 6498 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_PACKED_SINGLE_INSN_OPTIMAL))
        {
	  return MODE_V8SF;
        }
      else if ((which_alternative == 2) && (
#line 707 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_TYPELESS_STORES)))
        {
	  return MODE_V8SF;
        }
      else
        {
	  return MODE_OI;
        }

    case 76:  /* *movti_internal_sse */
      extract_constrain_insn_cached (insn);
      if (! (
#line 659 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SSE2)))
        {
	  return MODE_V4SF;
        }
      else if (
#line 6498 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_PACKED_SINGLE_INSN_OPTIMAL))
        {
	  return MODE_V4SF;
        }
      else if ((which_alternative == 2) && (
#line 707 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_TYPELESS_STORES)))
        {
	  return MODE_V4SF;
        }
      else if (
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX))
        {
	  return MODE_TI;
        }
      else if (
#line 6508 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(optimize_function_for_size_p (cfun)))
        {
	  return MODE_V4SF;
        }
      else
        {
	  return MODE_TI;
        }

    case 77:  /* *movdi_internal */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0xa00))
        {
	  return MODE_V4SF;
        }
      else if (((1 << which_alternative) & 0x1400))
        {
	  return MODE_V2SF;
        }
      else if (((1 << which_alternative) & 0xa0))
        {
	  if (
#line 6498 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_PACKED_SINGLE_INSN_OPTIMAL))
	    {
	      return MODE_V4SF;
	    }
	  else if (
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX))
	    {
	      return MODE_TI;
	    }
	  else if (
#line 6508 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(optimize_function_for_size_p (cfun)))
	    {
	      return MODE_V4SF;
	    }
	  else
	    {
	      return MODE_TI;
	    }
        }
      else
        {
	  return MODE_DI;
        }

    case 78:  /* *movsi_internal */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0xc))
        {
	  return MODE_DI;
        }
      else if (((1 << which_alternative) & 0xc0))
        {
	  if (
#line 6498 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_PACKED_SINGLE_INSN_OPTIMAL))
	    {
	      return MODE_V4SF;
	    }
	  else if (
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX))
	    {
	      return MODE_TI;
	    }
	  else if ((! (
#line 659 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SSE2))) || (
#line 6508 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(optimize_function_for_size_p (cfun))))
	    {
	      return MODE_V4SF;
	    }
	  else
	    {
	      return MODE_TI;
	    }
        }
      else if ((((1 << which_alternative) & 0xf00)) && (! (
#line 659 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SSE2))))
        {
	  return MODE_SF;
        }
      else
        {
	  return MODE_SI;
        }

    case 79:  /* *movhi_internal */
      extract_constrain_insn_cached (insn);
      if (get_attr_type (insn) == TYPE_IMOVX)
        {
	  return MODE_SI;
        }
      else if ((((1 << which_alternative) & 0x6)) && (aligned_operand (operands[1], HImode)))
        {
	  return MODE_SI;
        }
      else if ((which_alternative == 0) && ((! (
#line 2276 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_PARTIAL_REG_STALL))) || (! (
#line 2219 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_HIMODE_MATH)))))
        {
	  return MODE_SI;
        }
      else
        {
	  return MODE_HI;
        }

    case 80:  /* *movqi_internal */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x38))
        {
	  return MODE_SI;
        }
      else if (which_alternative == 6)
        {
	  return MODE_QI;
        }
      else if ((cached_type = get_attr_type (insn)) == TYPE_IMOVX)
        {
	  return MODE_SI;
        }
      else if ((cached_type == TYPE_IMOV) && ((((1 << which_alternative) & 0x3)) && ((
#line 2295 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_PARTIAL_REG_DEPENDENCY)) && ((! (
#line 6508 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(optimize_function_for_size_p (cfun)))) && (! (
#line 2276 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_PARTIAL_REG_STALL)))))))
        {
	  return MODE_SI;
        }
      else if ((cached_type == TYPE_IMOV) && ((((1 << which_alternative) & 0x3)) && ((
#line 2276 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_PARTIAL_REG_STALL)) && (! (
#line 2277 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_QIMODE_MATH))))))
        {
	  return MODE_SI;
        }
      else
        {
	  return MODE_QI;
        }

    case 100:  /* *movqi_extv_1 */
    case 102:  /* *movqi_extzv_2 */
      if (get_attr_type (insn) == TYPE_IMOVX)
        {
	  return MODE_SI;
        }
      else
        {
	  return MODE_QI;
        }

    case 106:  /* *pushxf */
    case 107:  /* *pushxf_nointeger */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return MODE_XF;
        }
      else
        {
	  return MODE_SI;
        }

    case 108:  /* *pushdf */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return MODE_DF;
        }
      else if (which_alternative == 1)
        {
	  return MODE_DI;
        }
      else
        {
	  return MODE_DF;
        }

    case 109:  /* *pushsf */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return MODE_SF;
        }
      else if (which_alternative == 1)
        {
	  return MODE_SI;
        }
      else
        {
	  return MODE_SF;
        }

    case 110:  /* *movtf_internal_sse */
      extract_constrain_insn_cached (insn);
      if (
#line 6498 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_PACKED_SINGLE_INSN_OPTIMAL))
        {
	  return MODE_V4SF;
        }
      else if ((which_alternative == 2) && (
#line 707 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_TYPELESS_STORES)))
        {
	  return MODE_V4SF;
        }
      else if (
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX))
        {
	  return MODE_TI;
        }
      else if ((! (
#line 659 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SSE2))) || (
#line 6508 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(optimize_function_for_size_p (cfun))))
        {
	  return MODE_V4SF;
        }
      else
        {
	  return MODE_TI;
        }

    case 112:  /* *movdf_internal */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x7))
        {
	  return MODE_DF;
        }
      else if (((1 << which_alternative) & 0x18))
        {
	  return MODE_SI;
        }
      else if (! (
#line 659 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SSE2)))
        {
	  if (((1 << which_alternative) & 0x660))
	    {
	      return MODE_V4SF;
	    }
	  else
	    {
	      return MODE_V2SF;
	    }
        }
      else if (((1 << which_alternative) & 0x220))
        {
	  if (
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX))
	    {
	      return MODE_V2DF;
	    }
	  else if (
#line 6508 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(optimize_function_for_size_p (cfun)))
	    {
	      return MODE_V4SF;
	    }
	  else if (
#line 494 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_LOAD0_BY_PXOR))
	    {
	      return MODE_TI;
	    }
	  else
	    {
	      return MODE_V2DF;
	    }
        }
      else if (((1 << which_alternative) & 0x440))
        {
	  if (
#line 6498 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_PACKED_SINGLE_INSN_OPTIMAL))
	    {
	      return MODE_V4SF;
	    }
	  else if (
#line 3324 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SSE_PARTIAL_REG_DEPENDENCY))
	    {
	      return MODE_V2DF;
	    }
	  else if (
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX))
	    {
	      return MODE_DF;
	    }
	  else if (
#line 6508 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(optimize_function_for_size_p (cfun)))
	    {
	      return MODE_V4SF;
	    }
	  else
	    {
	      return MODE_DF;
	    }
        }
      else if (((1 << which_alternative) & 0x880))
        {
	  if (
#line 3325 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SSE_SPLIT_REGS))
	    {
	      return MODE_V1DF;
	    }
	  else
	    {
	      return MODE_DF;
	    }
        }
      else
        {
	  return MODE_DF;
        }

    case 113:  /* *movsf_internal */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x618))
        {
	  return MODE_SI;
        }
      else if (which_alternative == 5)
        {
	  if (
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX))
	    {
	      return MODE_V4SF;
	    }
	  else if ((! (
#line 659 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SSE2))) || (
#line 6508 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(optimize_function_for_size_p (cfun))))
	    {
	      return MODE_V4SF;
	    }
	  else if (
#line 494 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_LOAD0_BY_PXOR))
	    {
	      return MODE_TI;
	    }
	  else
	    {
	      return MODE_V4SF;
	    }
        }
      else if (which_alternative == 6)
        {
	  if ((
#line 3324 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SSE_PARTIAL_REG_DEPENDENCY)) || (
#line 3325 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SSE_SPLIT_REGS)))
	    {
	      return MODE_V4SF;
	    }
	  else
	    {
	      return MODE_SF;
	    }
        }
      else if (which_alternative == 11)
        {
	  return MODE_DI;
        }
      else
        {
	  return MODE_SF;
        }

    case 128:  /* *extendsfdf2_mixed */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return MODE_SF;
        }
      else if (which_alternative == 1)
        {
	  return MODE_XF;
        }
      else
        {
	  return MODE_DF;
        }

    case 130:  /* *extendsfdf2_i387 */
    case 131:  /* *extendsfxf2_i387 */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return MODE_SF;
        }
      else
        {
	  return MODE_XF;
        }

    case 132:  /* *extenddfxf2_i387 */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return MODE_DF;
        }
      else
        {
	  return MODE_XF;
        }

    case 186:  /* *floatsisf2_vector_mixed */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return MODE_SF;
        }
      else
        {
	  return MODE_V4SF;
        }

    case 187:  /* *floatsidf2_vector_mixed */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return MODE_DF;
        }
      else
        {
	  return MODE_V2DF;
        }

    case 261:  /* *lea_general_4 */
    case 262:  /* *lea_general_4 */
      extract_insn_cached (insn);
      if (GET_MODE (operands[0]) == DImode)
        {
	  return MODE_DI;
        }
      else
        {
	  return MODE_SI;
        }

    case 432:  /* *ashlqi3_1 */
    case 419:  /* *one_cmplqi2_1 */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return MODE_QI;
        }
      else
        {
	  return MODE_SI;
        }

    case 431:  /* *ashlhi3_1 */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return MODE_HI;
        }
      else
        {
	  return MODE_SI;
        }

    case 608:  /* *bswaphi_lowpart_1 */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return MODE_QI;
        }
      else
        {
	  return MODE_HI;
        }

    case 947:  /* *movv32qi_internal */
    case 949:  /* *movv16hi_internal */
    case 951:  /* *movv8si_internal */
    case 953:  /* *movv4di_internal */
    case 955:  /* *movv2ti_internal */
      extract_constrain_insn_cached (insn);
      if (
#line 6498 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_PACKED_SINGLE_INSN_OPTIMAL))
        {
	  return MODE_V8SF;
        }
      else if ((which_alternative == 2) && (
#line 707 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_TYPELESS_STORES)))
        {
	  return MODE_V8SF;
        }
      else if (
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX))
        {
	  return MODE_OI;
        }
      else if ((! (
#line 659 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SSE2))) || (
#line 6508 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(optimize_function_for_size_p (cfun))))
        {
	  return MODE_V4SF;
        }
      else if ((which_alternative == 0) && (
#line 494 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_LOAD0_BY_PXOR)))
        {
	  return MODE_TI;
        }
      else
        {
	  return MODE_OI;
        }

    case 957:  /* *movv8sf_internal */
      extract_constrain_insn_cached (insn);
      if (
#line 6498 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_PACKED_SINGLE_INSN_OPTIMAL))
        {
	  return MODE_V8SF;
        }
      else if ((which_alternative == 2) && (
#line 707 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_TYPELESS_STORES)))
        {
	  return MODE_V8SF;
        }
      else if (
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX))
        {
	  return MODE_V8SF;
        }
      else if ((! (
#line 659 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SSE2))) || (
#line 6508 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(optimize_function_for_size_p (cfun))))
        {
	  return MODE_V4SF;
        }
      else if ((which_alternative == 0) && (
#line 494 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_LOAD0_BY_PXOR)))
        {
	  return MODE_TI;
        }
      else
        {
	  return MODE_V8SF;
        }

    case 958:  /* *movv4sf_internal */
      extract_constrain_insn_cached (insn);
      if (
#line 6498 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_PACKED_SINGLE_INSN_OPTIMAL))
        {
	  return MODE_V4SF;
        }
      else if ((which_alternative == 2) && (
#line 707 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_TYPELESS_STORES)))
        {
	  return MODE_V4SF;
        }
      else if (
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX))
        {
	  return MODE_V4SF;
        }
      else if ((! (
#line 659 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SSE2))) || (
#line 6508 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(optimize_function_for_size_p (cfun))))
        {
	  return MODE_V4SF;
        }
      else if ((which_alternative == 0) && (
#line 494 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_LOAD0_BY_PXOR)))
        {
	  return MODE_TI;
        }
      else
        {
	  return MODE_V4SF;
        }

    case 959:  /* *movv4df_internal */
      extract_constrain_insn_cached (insn);
      if (
#line 6498 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_PACKED_SINGLE_INSN_OPTIMAL))
        {
	  return MODE_V8SF;
        }
      else if ((which_alternative == 2) && (
#line 707 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_TYPELESS_STORES)))
        {
	  return MODE_V8SF;
        }
      else if (
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX))
        {
	  return MODE_V4DF;
        }
      else if ((! (
#line 659 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SSE2))) || (
#line 6508 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(optimize_function_for_size_p (cfun))))
        {
	  return MODE_V4SF;
        }
      else if ((which_alternative == 0) && (
#line 494 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_LOAD0_BY_PXOR)))
        {
	  return MODE_TI;
        }
      else
        {
	  return MODE_V4DF;
        }

    case 960:  /* *movv2df_internal */
      extract_constrain_insn_cached (insn);
      if (
#line 6498 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_PACKED_SINGLE_INSN_OPTIMAL))
        {
	  return MODE_V4SF;
        }
      else if ((which_alternative == 2) && (
#line 707 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_TYPELESS_STORES)))
        {
	  return MODE_V4SF;
        }
      else if (
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX))
        {
	  return MODE_V2DF;
        }
      else if ((! (
#line 659 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SSE2))) || (
#line 6508 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(optimize_function_for_size_p (cfun))))
        {
	  return MODE_V4SF;
        }
      else if ((which_alternative == 0) && (
#line 494 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_LOAD0_BY_PXOR)))
        {
	  return MODE_TI;
        }
      else
        {
	  return MODE_V2DF;
        }

    case 967:  /* avx_storeups256 */
      extract_constrain_insn_cached (insn);
      if ((
#line 6498 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_PACKED_SINGLE_INSN_OPTIMAL)) || (
#line 707 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_TYPELESS_STORES)))
        {
	  return MODE_V8SF;
        }
      else if (
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX))
        {
	  return MODE_V8SF;
        }
      else if (
#line 6508 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(optimize_function_for_size_p (cfun)))
        {
	  return MODE_V4SF;
        }
      else
        {
	  return MODE_V8SF;
        }

    case 969:  /* avx_storeupd256 */
      extract_constrain_insn_cached (insn);
      if ((
#line 6498 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_PACKED_SINGLE_INSN_OPTIMAL)) || (
#line 707 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_TYPELESS_STORES)))
        {
	  return MODE_V8SF;
        }
      else if (
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX))
        {
	  return MODE_V4DF;
        }
      else if (
#line 6508 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(optimize_function_for_size_p (cfun)))
        {
	  return MODE_V4SF;
        }
      else
        {
	  return MODE_V4DF;
        }

    case 970:  /* sse2_storeupd */
      extract_constrain_insn_cached (insn);
      if ((
#line 6498 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_PACKED_SINGLE_INSN_OPTIMAL)) || (
#line 707 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_TYPELESS_STORES)))
        {
	  return MODE_V4SF;
        }
      else if (
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX))
        {
	  return MODE_V2DF;
        }
      else if (
#line 6508 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(optimize_function_for_size_p (cfun)))
        {
	  return MODE_V4SF;
        }
      else
        {
	  return MODE_V2DF;
        }

    case 971:  /* avx_loaddqu256 */
      extract_constrain_insn_cached (insn);
      if (
#line 6498 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_PACKED_SINGLE_INSN_OPTIMAL))
        {
	  return MODE_V8SF;
        }
      else if (
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX))
        {
	  return MODE_OI;
        }
      else if (
#line 6508 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(optimize_function_for_size_p (cfun)))
        {
	  return MODE_V4SF;
        }
      else
        {
	  return MODE_OI;
        }

    case 972:  /* sse2_loaddqu */
      extract_constrain_insn_cached (insn);
      if (
#line 6498 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_PACKED_SINGLE_INSN_OPTIMAL))
        {
	  return MODE_V4SF;
        }
      else if (
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX))
        {
	  return MODE_TI;
        }
      else if (
#line 6508 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(optimize_function_for_size_p (cfun)))
        {
	  return MODE_V4SF;
        }
      else
        {
	  return MODE_TI;
        }

    case 973:  /* avx_storedqu256 */
      extract_constrain_insn_cached (insn);
      if ((
#line 6498 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_PACKED_SINGLE_INSN_OPTIMAL)) || (
#line 707 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_TYPELESS_STORES)))
        {
	  return MODE_V8SF;
        }
      else if (
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX))
        {
	  return MODE_OI;
        }
      else if (
#line 6508 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(optimize_function_for_size_p (cfun)))
        {
	  return MODE_V4SF;
        }
      else
        {
	  return MODE_OI;
        }

    case 974:  /* sse2_storedqu */
      extract_constrain_insn_cached (insn);
      if ((
#line 6498 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_PACKED_SINGLE_INSN_OPTIMAL)) || (
#line 707 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_TYPELESS_STORES)))
        {
	  return MODE_V4SF;
        }
      else if (
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX))
        {
	  return MODE_TI;
        }
      else if (
#line 6508 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(optimize_function_for_size_p (cfun)))
        {
	  return MODE_V4SF;
        }
      else
        {
	  return MODE_TI;
        }

    case 963:  /* avx_loadups256 */
    case 1086:  /* avx_andnotv8sf3 */
    case 1090:  /* *andv8sf3 */
    case 1091:  /* *iorv8sf3 */
    case 1092:  /* *xorv8sf3 */
      extract_constrain_insn_cached (insn);
      if (
#line 6498 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_PACKED_SINGLE_INSN_OPTIMAL))
        {
	  return MODE_V8SF;
        }
      else if (
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX))
        {
	  return MODE_V8SF;
        }
      else if (
#line 6508 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(optimize_function_for_size_p (cfun)))
        {
	  return MODE_V4SF;
        }
      else
        {
	  return MODE_V8SF;
        }

    case 965:  /* avx_loadupd256 */
    case 1088:  /* avx_andnotv4df3 */
    case 1096:  /* *andv4df3 */
    case 1097:  /* *iorv4df3 */
    case 1098:  /* *xorv4df3 */
      extract_constrain_insn_cached (insn);
      if (
#line 6498 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_PACKED_SINGLE_INSN_OPTIMAL))
        {
	  return MODE_V8SF;
        }
      else if (
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX))
        {
	  return MODE_V4DF;
        }
      else if (
#line 6508 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(optimize_function_for_size_p (cfun)))
        {
	  return MODE_V4SF;
        }
      else
        {
	  return MODE_V4DF;
        }

    case 966:  /* sse2_loadupd */
    case 1089:  /* sse2_andnotv2df3 */
    case 1099:  /* *andv2df3 */
    case 1100:  /* *iorv2df3 */
    case 1101:  /* *xorv2df3 */
    case 1103:  /* *andnotdf3 */
    case 1108:  /* *anddf3 */
    case 1109:  /* *iordf3 */
    case 1110:  /* *xordf3 */
      extract_constrain_insn_cached (insn);
      if (
#line 6498 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_PACKED_SINGLE_INSN_OPTIMAL))
        {
	  return MODE_V4SF;
        }
      else if (
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX))
        {
	  return MODE_V2DF;
        }
      else if (
#line 6508 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(optimize_function_for_size_p (cfun)))
        {
	  return MODE_V4SF;
        }
      else
        {
	  return MODE_V2DF;
        }

    case 1104:  /* *andnottf3 */
    case 1111:  /* *andtf3 */
    case 1112:  /* *iortf3 */
    case 1113:  /* *xortf3 */
      extract_constrain_insn_cached (insn);
      if (
#line 6498 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_PACKED_SINGLE_INSN_OPTIMAL))
        {
	  return MODE_V4SF;
        }
      else if (
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX))
        {
	  return MODE_TI;
        }
      else if ((! (
#line 659 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SSE2))) || (
#line 6508 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(optimize_function_for_size_p (cfun))))
        {
	  return MODE_V4SF;
        }
      else
        {
	  return MODE_TI;
        }

    case 1211:  /* sse_storehps */
    case 1213:  /* sse_storelps */
    case 1254:  /* *vec_extractv2df_1_sse */
    case 1256:  /* *vec_extractv2df_0_sse */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return MODE_V2SF;
        }
      else if (which_alternative == 1)
        {
	  return MODE_V4SF;
        }
      else
        {
	  return MODE_V2SF;
        }

    case 1260:  /* vec_dupv2df */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return MODE_V2DF;
        }
      else
        {
	  return MODE_DF;
        }

    case 1368:  /* *andnotv32qi3 */
    case 1376:  /* *andv32qi3 */
    case 1377:  /* *iorv32qi3 */
    case 1378:  /* *xorv32qi3 */
      extract_constrain_insn_cached (insn);
      if (
#line 6498 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_PACKED_SINGLE_INSN_OPTIMAL))
        {
	  return MODE_V8SF;
        }
      else if (
#line 668 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX2))
        {
	  return MODE_OI;
        }
      else if (
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX))
        {
	  if (
#line 6504 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(GET_MODE_SIZE (V32QImode) > 16))
	    {
	      return MODE_V8SF;
	    }
	  else
	    {
	      return MODE_OI;
	    }
        }
      else if ((! (
#line 659 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SSE2))) || (
#line 6508 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(optimize_function_for_size_p (cfun))))
        {
	  return MODE_V4SF;
        }
      else
        {
	  return MODE_OI;
        }

    case 1369:  /* *andnotv16qi3 */
    case 1379:  /* *andv16qi3 */
    case 1380:  /* *iorv16qi3 */
    case 1381:  /* *xorv16qi3 */
      extract_constrain_insn_cached (insn);
      if (
#line 6498 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_PACKED_SINGLE_INSN_OPTIMAL))
        {
	  return MODE_V4SF;
        }
      else if (
#line 668 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX2))
        {
	  return MODE_TI;
        }
      else if (
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX))
        {
	  if (
#line 6504 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(GET_MODE_SIZE (V16QImode) > 16))
	    {
	      return MODE_V8SF;
	    }
	  else
	    {
	      return MODE_TI;
	    }
        }
      else if ((! (
#line 659 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SSE2))) || (
#line 6508 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(optimize_function_for_size_p (cfun))))
        {
	  return MODE_V4SF;
        }
      else
        {
	  return MODE_TI;
        }

    case 1370:  /* *andnotv16hi3 */
    case 1382:  /* *andv16hi3 */
    case 1383:  /* *iorv16hi3 */
    case 1384:  /* *xorv16hi3 */
      extract_constrain_insn_cached (insn);
      if (
#line 6498 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_PACKED_SINGLE_INSN_OPTIMAL))
        {
	  return MODE_V8SF;
        }
      else if (
#line 668 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX2))
        {
	  return MODE_OI;
        }
      else if (
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX))
        {
	  if (
#line 6504 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(GET_MODE_SIZE (V16HImode) > 16))
	    {
	      return MODE_V8SF;
	    }
	  else
	    {
	      return MODE_OI;
	    }
        }
      else if ((! (
#line 659 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SSE2))) || (
#line 6508 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(optimize_function_for_size_p (cfun))))
        {
	  return MODE_V4SF;
        }
      else
        {
	  return MODE_OI;
        }

    case 1371:  /* *andnotv8hi3 */
    case 1385:  /* *andv8hi3 */
    case 1386:  /* *iorv8hi3 */
    case 1387:  /* *xorv8hi3 */
      extract_constrain_insn_cached (insn);
      if (
#line 6498 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_PACKED_SINGLE_INSN_OPTIMAL))
        {
	  return MODE_V4SF;
        }
      else if (
#line 668 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX2))
        {
	  return MODE_TI;
        }
      else if (
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX))
        {
	  if (
#line 6504 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(GET_MODE_SIZE (V8HImode) > 16))
	    {
	      return MODE_V8SF;
	    }
	  else
	    {
	      return MODE_TI;
	    }
        }
      else if ((! (
#line 659 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SSE2))) || (
#line 6508 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(optimize_function_for_size_p (cfun))))
        {
	  return MODE_V4SF;
        }
      else
        {
	  return MODE_TI;
        }

    case 1372:  /* *andnotv8si3 */
    case 1388:  /* *andv8si3 */
    case 1389:  /* *iorv8si3 */
    case 1390:  /* *xorv8si3 */
      extract_constrain_insn_cached (insn);
      if (
#line 6498 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_PACKED_SINGLE_INSN_OPTIMAL))
        {
	  return MODE_V8SF;
        }
      else if (
#line 668 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX2))
        {
	  return MODE_OI;
        }
      else if (
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX))
        {
	  if (
#line 6504 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(GET_MODE_SIZE (V8SImode) > 16))
	    {
	      return MODE_V8SF;
	    }
	  else
	    {
	      return MODE_OI;
	    }
        }
      else if ((! (
#line 659 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SSE2))) || (
#line 6508 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(optimize_function_for_size_p (cfun))))
        {
	  return MODE_V4SF;
        }
      else
        {
	  return MODE_OI;
        }

    case 1373:  /* *andnotv4si3 */
    case 1391:  /* *andv4si3 */
    case 1392:  /* *iorv4si3 */
    case 1393:  /* *xorv4si3 */
      extract_constrain_insn_cached (insn);
      if (
#line 6498 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_PACKED_SINGLE_INSN_OPTIMAL))
        {
	  return MODE_V4SF;
        }
      else if (
#line 668 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX2))
        {
	  return MODE_TI;
        }
      else if (
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX))
        {
	  if (
#line 6504 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(GET_MODE_SIZE (V4SImode) > 16))
	    {
	      return MODE_V8SF;
	    }
	  else
	    {
	      return MODE_TI;
	    }
        }
      else if ((! (
#line 659 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SSE2))) || (
#line 6508 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(optimize_function_for_size_p (cfun))))
        {
	  return MODE_V4SF;
        }
      else
        {
	  return MODE_TI;
        }

    case 1374:  /* *andnotv4di3 */
    case 1394:  /* *andv4di3 */
    case 1395:  /* *iorv4di3 */
    case 1396:  /* *xorv4di3 */
      extract_constrain_insn_cached (insn);
      if (
#line 6498 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_PACKED_SINGLE_INSN_OPTIMAL))
        {
	  return MODE_V8SF;
        }
      else if (
#line 668 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX2))
        {
	  return MODE_OI;
        }
      else if (
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX))
        {
	  if (
#line 6504 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(GET_MODE_SIZE (V4DImode) > 16))
	    {
	      return MODE_V8SF;
	    }
	  else
	    {
	      return MODE_OI;
	    }
        }
      else if ((! (
#line 659 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SSE2))) || (
#line 6508 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(optimize_function_for_size_p (cfun))))
        {
	  return MODE_V4SF;
        }
      else
        {
	  return MODE_OI;
        }

    case 1375:  /* *andnotv2di3 */
    case 1397:  /* *andv2di3 */
    case 1398:  /* *iorv2di3 */
    case 1399:  /* *xorv2di3 */
      extract_constrain_insn_cached (insn);
      if (
#line 6498 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(TARGET_SSE_PACKED_SINGLE_INSN_OPTIMAL))
        {
	  return MODE_V4SF;
        }
      else if (
#line 668 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX2))
        {
	  return MODE_TI;
        }
      else if (
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX))
        {
	  if (
#line 6504 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(GET_MODE_SIZE (V2DImode) > 16))
	    {
	      return MODE_V8SF;
	    }
	  else
	    {
	      return MODE_TI;
	    }
        }
      else if ((! (
#line 659 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SSE2))) || (
#line 6508 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(optimize_function_for_size_p (cfun))))
        {
	  return MODE_V4SF;
        }
      else
        {
	  return MODE_TI;
        }

    case 842:  /* *mmx_addv2sf3 */
    case 843:  /* *mmx_subv2sf3 */
    case 844:  /* *mmx_mulv2sf3 */
    case 845:  /* *mmx_smaxv2sf3_finite */
    case 846:  /* *mmx_sminv2sf3_finite */
    case 847:  /* *mmx_smaxv2sf3 */
    case 848:  /* *mmx_sminv2sf3 */
    case 849:  /* mmx_rcpv2sf2 */
    case 850:  /* mmx_rcpit1v2sf3 */
    case 851:  /* mmx_rcpit2v2sf3 */
    case 852:  /* mmx_rsqrtv2sf2 */
    case 853:  /* mmx_rsqit1v2sf3 */
    case 854:  /* mmx_haddv2sf3 */
    case 855:  /* mmx_hsubv2sf3 */
    case 856:  /* mmx_addsubv2sf3 */
    case 857:  /* *mmx_eqv2sf3 */
    case 858:  /* mmx_gtv2sf3 */
    case 859:  /* mmx_gev2sf3 */
    case 860:  /* mmx_pf2id */
    case 861:  /* mmx_pf2iw */
    case 862:  /* mmx_pi2fw */
    case 863:  /* mmx_floatv2si2 */
    case 864:  /* mmx_pswapdv2sf2 */
      return MODE_V2SF;

    case 981:  /* sse2_movntv2df */
    case 994:  /* *addv2df3 */
    case 995:  /* *subv2df3 */
    case 1003:  /* *mulv2df3 */
    case 1009:  /* sse2_divv2df3 */
    case 1018:  /* sse2_sqrtv2df2 */
    case 1030:  /* *smaxv2df3_finite */
    case 1031:  /* *sminv2df3_finite */
    case 1038:  /* *smaxv2df3 */
    case 1039:  /* *sminv2df3 */
    case 1047:  /* *ieee_sminv2df3 */
    case 1051:  /* *ieee_smaxv2df3 */
    case 1053:  /* sse3_addsubv2df3 */
    case 1058:  /* *sse3_haddv2df3 */
    case 1059:  /* sse3_hsubv2df3 */
    case 1060:  /* *sse3_haddv2df3_low */
    case 1061:  /* *sse3_hsubv2df3_low */
    case 1069:  /* avx_cmpv2df3 */
    case 1075:  /* *sse2_maskcmpv2df3_comm */
    case 1079:  /* sse2_maskcmpv2df3 */
    case 1117:  /* *fma_fmadd_v2df */
    case 1123:  /* *fma_fmsub_v2df */
    case 1129:  /* *fma_fnmadd_v2df */
    case 1135:  /* *fma_fnmsub_v2df */
    case 1141:  /* *fma_fmaddsub_v2df */
    case 1145:  /* *fma_fmsubadd_v2df */
    case 1147:  /* *fmai_fmadd_v2df */
    case 1149:  /* *fmai_fmsub_v2df */
    case 1151:  /* *fmai_fnmadd_v2df */
    case 1153:  /* *fmai_fnmsub_v2df */
    case 1155:  /* *fma4i_vmfmadd_v2df */
    case 1157:  /* *fma4i_vmfmsub_v2df */
    case 1159:  /* *fma4i_vmfnmadd_v2df */
    case 1161:  /* *fma4i_vmfnmsub_v2df */
    case 1175:  /* sse2_cvtpi2pd */
    case 1184:  /* sse2_cvtdq2pd */
    case 1197:  /* sse2_cvtps2pd */
    case 1251:  /* sse2_shufpd_v2di */
    case 1252:  /* sse2_shufpd_v2df */
    case 1454:  /* sse2_movmskpd */
    case 1523:  /* sse4_1_blendpd */
    case 1527:  /* sse4_1_blendvpd */
    case 1531:  /* sse4_1_dppd */
    case 1572:  /* avx_vtestpd */
    case 1578:  /* sse4_1_roundpd */
    case 1580:  /* sse4_1_roundsd */
    case 1657:  /* xop_frczv2df2 */
    case 1661:  /* *xop_vmfrcz_v2df */
    case 1681:  /* xop_vpermil2v2df3 */
    case 1729:  /* *avx_vpermilpv2df */
    case 1733:  /* avx_vpermilvarv2df3 */
    case 1755:  /* avx_maskloadpd */
    case 1763:  /* avx_maskstorepd */
    case 1797:  /* *avx2_gathersiv2df */
    case 1798:  /* *avx2_gathersiv2df */
    case 1813:  /* *avx2_gathersiv2df_2 */
    case 1814:  /* *avx2_gathersiv2df_2 */
    case 1829:  /* *avx2_gatherdiv2df */
    case 1830:  /* *avx2_gatherdiv2df */
    case 1845:  /* *avx2_gatherdiv2df_2 */
    case 1846:  /* *avx2_gatherdiv2df_2 */
      return MODE_V2DF;

    case 964:  /* sse_loadups */
    case 968:  /* sse_storeups */
    case 979:  /* sse_movntv4sf */
    case 990:  /* *addv4sf3 */
    case 991:  /* *subv4sf3 */
    case 1001:  /* *mulv4sf3 */
    case 1007:  /* sse_divv4sf3 */
    case 1013:  /* sse_rcpv4sf2 */
    case 1016:  /* sse_sqrtv4sf2 */
    case 1022:  /* sse_rsqrtv4sf2 */
    case 1026:  /* *smaxv4sf3_finite */
    case 1027:  /* *sminv4sf3_finite */
    case 1034:  /* *smaxv4sf3 */
    case 1035:  /* *sminv4sf3 */
    case 1045:  /* *ieee_sminv4sf3 */
    case 1049:  /* *ieee_smaxv4sf3 */
    case 1055:  /* sse3_addsubv4sf3 */
    case 1064:  /* sse3_haddv4sf3 */
    case 1065:  /* sse3_hsubv4sf3 */
    case 1067:  /* avx_cmpv4sf3 */
    case 1073:  /* *sse_maskcmpv4sf3_comm */
    case 1077:  /* sse_maskcmpv4sf3 */
    case 1087:  /* sse_andnotv4sf3 */
    case 1093:  /* *andv4sf3 */
    case 1094:  /* *iorv4sf3 */
    case 1095:  /* *xorv4sf3 */
    case 1102:  /* *andnotsf3 */
    case 1105:  /* *andsf3 */
    case 1106:  /* *iorsf3 */
    case 1107:  /* *xorsf3 */
    case 1116:  /* *fma_fmadd_v4sf */
    case 1122:  /* *fma_fmsub_v4sf */
    case 1128:  /* *fma_fnmadd_v4sf */
    case 1134:  /* *fma_fnmsub_v4sf */
    case 1139:  /* *fma_fmaddsub_v4sf */
    case 1143:  /* *fma_fmsubadd_v4sf */
    case 1146:  /* *fmai_fmadd_v4sf */
    case 1148:  /* *fmai_fmsub_v4sf */
    case 1150:  /* *fmai_fnmadd_v4sf */
    case 1152:  /* *fmai_fnmsub_v4sf */
    case 1154:  /* *fma4i_vmfmadd_v4sf */
    case 1156:  /* *fma4i_vmfmsub_v4sf */
    case 1158:  /* *fma4i_vmfnmadd_v4sf */
    case 1160:  /* *fma4i_vmfnmsub_v4sf */
    case 1162:  /* sse_cvtpi2ps */
    case 1170:  /* floatv4siv4sf2 */
    case 1193:  /* avx_cvtpd2ps256 */
    case 1194:  /* *sse2_cvtpd2ps */
    case 1201:  /* vec_interleave_highv4sf */
    case 1203:  /* vec_interleave_lowv4sf */
    case 1205:  /* sse3_movshdup */
    case 1207:  /* sse3_movsldup */
    case 1209:  /* sse_shufps_v4si */
    case 1210:  /* sse_shufps_v4sf */
    case 1217:  /* avx2_vec_dupv4sf */
    case 1219:  /* vec_dupv4sf */
    case 1225:  /* *vec_setv4sf_sse4_1 */
    case 1226:  /* sse4_1_insertps */
    case 1452:  /* sse_movmskps */
    case 1521:  /* sse4_1_blendps */
    case 1525:  /* sse4_1_blendvps */
    case 1529:  /* sse4_1_dpps */
    case 1570:  /* avx_vtestps */
    case 1576:  /* sse4_1_roundps */
    case 1579:  /* sse4_1_roundss */
    case 1656:  /* xop_frczv4sf2 */
    case 1660:  /* *xop_vmfrcz_v4sf */
    case 1679:  /* xop_vpermil2v4sf3 */
    case 1727:  /* *avx_vpermilpv4sf */
    case 1731:  /* avx_vpermilvarv4sf3 */
    case 1754:  /* avx_maskloadps */
    case 1762:  /* avx_maskstoreps */
    case 1789:  /* vcvtph2ps */
    case 1792:  /* *vcvtps2ph */
    case 1793:  /* *vcvtps2ph_store */
    case 1805:  /* *avx2_gathersiv4sf */
    case 1806:  /* *avx2_gathersiv4sf */
    case 1821:  /* *avx2_gathersiv4sf_2 */
    case 1822:  /* *avx2_gathersiv4sf_2 */
    case 1837:  /* *avx2_gatherdiv4sf */
    case 1838:  /* *avx2_gatherdiv4sf */
    case 1853:  /* *avx2_gatherdiv4sf_2 */
    case 1854:  /* *avx2_gatherdiv4sf_2 */
      return MODE_V4SF;

    case 980:  /* avx_movntv4df */
    case 992:  /* *addv4df3 */
    case 993:  /* *subv4df3 */
    case 1002:  /* *mulv4df3 */
    case 1008:  /* avx_divv4df3 */
    case 1017:  /* avx_sqrtv4df2 */
    case 1028:  /* *smaxv4df3_finite */
    case 1029:  /* *sminv4df3_finite */
    case 1036:  /* *smaxv4df3 */
    case 1037:  /* *sminv4df3 */
    case 1046:  /* *ieee_sminv4df3 */
    case 1050:  /* *ieee_smaxv4df3 */
    case 1052:  /* avx_addsubv4df3 */
    case 1056:  /* avx_haddv4df3 */
    case 1057:  /* avx_hsubv4df3 */
    case 1068:  /* avx_cmpv4df3 */
    case 1074:  /* *avx_maskcmpv4df3_comm */
    case 1078:  /* avx_maskcmpv4df3 */
    case 1119:  /* *fma_fmadd_v4df */
    case 1125:  /* *fma_fmsub_v4df */
    case 1131:  /* *fma_fnmadd_v4df */
    case 1137:  /* *fma_fnmsub_v4df */
    case 1140:  /* *fma_fmaddsub_v4df */
    case 1144:  /* *fma_fmsubadd_v4df */
    case 1182:  /* floatv4siv4df2 */
    case 1183:  /* avx_cvtdq2pd256_2 */
    case 1195:  /* avx_cvtps2pd256 */
    case 1196:  /* *avx_cvtps2pd256_2 */
    case 1233:  /* vec_extract_hi_v4df */
    case 1242:  /* avx_unpckhpd256 */
    case 1244:  /* *avx_unpcklpd256 */
    case 1246:  /* avx_shufpd256_1 */
    case 1453:  /* avx_movmskpd256 */
    case 1522:  /* avx_blendpd256 */
    case 1526:  /* avx_blendvpd256 */
    case 1530:  /* avx_dppd256 */
    case 1571:  /* avx_vtestpd256 */
    case 1577:  /* avx_roundpd256 */
    case 1659:  /* xop_frczv4df2 */
    case 1680:  /* xop_vpermil2v4df3 */
    case 1706:  /* avx2_permv4df_1 */
    case 1708:  /* avx2_vec_dupv4df */
    case 1722:  /* avx_vbroadcastf128_v4df */
    case 1728:  /* *avx_vpermilpv4df */
    case 1732:  /* avx_vpermilvarv4df3 */
    case 1736:  /* *avx_vperm2f128v4df_full */
    case 1739:  /* *avx_vperm2f128v4df_nozero */
    case 1743:  /* vec_set_lo_v4df */
    case 1745:  /* vec_set_hi_v4df */
    case 1757:  /* avx_maskloadpd256 */
    case 1765:  /* avx_maskstorepd256 */
    case 1788:  /* avx_vec_concatv4df */
    case 1801:  /* *avx2_gathersiv4df */
    case 1802:  /* *avx2_gathersiv4df */
    case 1817:  /* *avx2_gathersiv4df_2 */
    case 1818:  /* *avx2_gathersiv4df_2 */
    case 1833:  /* *avx2_gatherdiv4df */
    case 1834:  /* *avx2_gatherdiv4df */
    case 1849:  /* *avx2_gatherdiv4df_2 */
    case 1850:  /* *avx2_gatherdiv4df_2 */
      return MODE_V4DF;

    case 978:  /* avx_movntv8sf */
    case 988:  /* *addv8sf3 */
    case 989:  /* *subv8sf3 */
    case 1000:  /* *mulv8sf3 */
    case 1006:  /* avx_divv8sf3 */
    case 1012:  /* avx_rcpv8sf2 */
    case 1015:  /* avx_sqrtv8sf2 */
    case 1021:  /* avx_rsqrtv8sf2 */
    case 1024:  /* *smaxv8sf3_finite */
    case 1025:  /* *sminv8sf3_finite */
    case 1032:  /* *smaxv8sf3 */
    case 1033:  /* *sminv8sf3 */
    case 1044:  /* *ieee_sminv8sf3 */
    case 1048:  /* *ieee_smaxv8sf3 */
    case 1054:  /* avx_addsubv8sf3 */
    case 1062:  /* avx_haddv8sf3 */
    case 1063:  /* avx_hsubv8sf3 */
    case 1066:  /* avx_cmpv8sf3 */
    case 1072:  /* *avx_maskcmpv8sf3_comm */
    case 1076:  /* avx_maskcmpv8sf3 */
    case 1118:  /* *fma_fmadd_v8sf */
    case 1124:  /* *fma_fmsub_v8sf */
    case 1130:  /* *fma_fnmadd_v8sf */
    case 1136:  /* *fma_fnmsub_v8sf */
    case 1138:  /* *fma_fmaddsub_v8sf */
    case 1142:  /* *fma_fmsubadd_v8sf */
    case 1169:  /* floatv8siv8sf2 */
    case 1200:  /* avx_unpckhps256 */
    case 1202:  /* avx_unpcklps256 */
    case 1204:  /* avx_movshdup256 */
    case 1206:  /* avx_movsldup256 */
    case 1208:  /* avx_shufps256_1 */
    case 1216:  /* avx2_vec_dupv8sf */
    case 1218:  /* avx2_vec_dupv8sf_1 */
    case 1237:  /* vec_extract_hi_v8sf */
    case 1451:  /* avx_movmskps256 */
    case 1520:  /* avx_blendps256 */
    case 1524:  /* avx_blendvps256 */
    case 1528:  /* avx_dpps256 */
    case 1569:  /* avx_vtestps256 */
    case 1575:  /* avx_roundps256 */
    case 1658:  /* xop_frczv8sf2 */
    case 1678:  /* xop_vpermil2v8sf3 */
    case 1709:  /* vec_dupv8si */
    case 1710:  /* vec_dupv8sf */
    case 1711:  /* vec_dupv4di */
    case 1712:  /* vec_dupv4df */
    case 1721:  /* avx_vbroadcastf128_v8sf */
    case 1726:  /* *avx_vpermilpv8sf */
    case 1730:  /* avx_vpermilvarv8sf3 */
    case 1735:  /* *avx_vperm2f128v8sf_full */
    case 1738:  /* *avx_vperm2f128v8sf_nozero */
    case 1747:  /* vec_set_lo_v8sf */
    case 1749:  /* vec_set_hi_v8sf */
    case 1756:  /* avx_maskloadps256 */
    case 1764:  /* avx_maskstoreps256 */
    case 1787:  /* avx_vec_concatv8sf */
    case 1790:  /* *vcvtph2ps_load */
    case 1791:  /* vcvtph2ps256 */
    case 1794:  /* vcvtps2ph256 */
    case 1809:  /* *avx2_gathersiv8sf */
    case 1810:  /* *avx2_gathersiv8sf */
    case 1825:  /* *avx2_gathersiv8sf_2 */
    case 1826:  /* *avx2_gathersiv8sf_2 */
    case 1841:  /* *avx2_gatherdiv8sf */
    case 1842:  /* *avx2_gatherdiv8sf */
    case 1857:  /* *avx2_gatherdiv8sf_2 */
    case 1858:  /* *avx2_gatherdiv8sf_2 */
    case 1861:  /* *avx2_gatherdiv8sf_3 */
    case 1862:  /* *avx2_gatherdiv8sf_3 */
    case 1865:  /* *avx2_gatherdiv8sf_4 */
    case 1866:  /* *avx2_gatherdiv8sf_4 */
      return MODE_V8SF;

    case 19:  /* *cmpxf_0_i387 */
    case 22:  /* *cmpxf_0_cc_i387 */
    case 23:  /* *cmpxf_i387 */
    case 24:  /* *cmpxf_cc_i387 */
    case 31:  /* *cmpuxf_i387 */
    case 34:  /* *cmpuxf_cc_i387 */
    case 59:  /* *cmpixf_i387 */
    case 62:  /* *cmpiuxf_i387 */
    case 114:  /* swapxf */
    case 174:  /* *floathixf2_i387_with_temp */
    case 177:  /* *floathixf2_i387 */
    case 214:  /* *floatsixf2_i387_with_temp */
    case 217:  /* *floatdixf2_i387_with_temp */
    case 220:  /* *floatsixf2_i387 */
    case 223:  /* *floatdixf2_i387 */
    case 226:  /* floatdixf2_i387_with_xmm */
    case 229:  /* *floatunssixf2_1 */
    case 402:  /* *absxf2_1 */
    case 403:  /* *negxf2_1 */
    case 406:  /* *absextendsfxf2 */
    case 407:  /* *negextendsfxf2 */
    case 408:  /* *absextenddfxf2 */
    case 409:  /* *negextenddfxf2 */
    case 651:  /* *fop_xf_comm_i387 */
    case 652:  /* *fop_xf_1_i387 */
    case 665:  /* sqrtxf2 */
    case 666:  /* sqrt_extendsfxf2_i387 */
    case 667:  /* sqrt_extenddfxf2_i387 */
    case 671:  /* fpremxf4_i387 */
    case 672:  /* fprem1xf4_i387 */
    case 673:  /* *sinxf2_i387 */
    case 674:  /* *cosxf2_i387 */
    case 675:  /* *sin_extendsfxf2_i387 */
    case 676:  /* *cos_extendsfxf2_i387 */
    case 677:  /* *sin_extenddfxf2_i387 */
    case 678:  /* *cos_extenddfxf2_i387 */
    case 679:  /* sincosxf3 */
    case 680:  /* sincos_extendsfxf3_i387 */
    case 681:  /* sincos_extenddfxf3_i387 */
    case 682:  /* fptanxf4_i387 */
    case 683:  /* fptan_extendsfxf4_i387 */
    case 684:  /* fptan_extenddfxf4_i387 */
    case 685:  /* *fpatanxf3_i387 */
    case 686:  /* fpatan_extendsfxf3_i387 */
    case 687:  /* fpatan_extenddfxf3_i387 */
    case 688:  /* fyl2xxf3_i387 */
    case 689:  /* fyl2x_extendsfxf3_i387 */
    case 690:  /* fyl2x_extenddfxf3_i387 */
    case 691:  /* fyl2xp1xf3_i387 */
    case 692:  /* fyl2xp1_extendsfxf3_i387 */
    case 693:  /* fyl2xp1_extenddfxf3_i387 */
    case 694:  /* fxtractxf3_i387 */
    case 695:  /* fxtract_extendsfxf3_i387 */
    case 696:  /* fxtract_extenddfxf3_i387 */
    case 697:  /* *f2xm1xf2_i387 */
    case 698:  /* *fscalexf4_i387 */
    case 701:  /* rintxf2 */
    case 711:  /* frndintxf2_floor */
    case 712:  /* frndintxf2_ceil */
    case 713:  /* frndintxf2_trunc */
    case 714:  /* frndintxf2_floor_i387 */
    case 715:  /* frndintxf2_ceil_i387 */
    case 716:  /* frndintxf2_trunc_i387 */
    case 717:  /* frndintxf2_mask_pm */
    case 718:  /* frndintxf2_mask_pm_i387 */
    case 739:  /* fxamxf2_i387 */
    case 776:  /* *movxfcc_1 */
      return MODE_XF;

    case 18:  /* *cmpdf_0_i387 */
    case 21:  /* *cmpdf_0_cc_i387 */
    case 26:  /* *cmpdf_i387 */
    case 28:  /* *cmpdf_cc_i387 */
    case 30:  /* *cmpudf_i387 */
    case 33:  /* *cmpudf_cc_i387 */
    case 50:  /* *cmpidf_mixed */
    case 52:  /* *cmpiudf_mixed */
    case 54:  /* *cmpidf_sse */
    case 56:  /* *cmpiudf_sse */
    case 58:  /* *cmpidf_i387 */
    case 61:  /* *cmpiudf_i387 */
    case 116:  /* *swapdf */
    case 129:  /* *extendsfdf2_sse */
    case 140:  /* *truncxfdf2_mixed */
    case 142:  /* truncxfdf2_i387_noop */
    case 144:  /* *truncxfdf2_i387 */
    case 148:  /* fix_truncdfsi_sse */
    case 173:  /* *floathidf2_i387_with_temp */
    case 176:  /* *floathidf2_i387 */
    case 189:  /* *floatsidf2_mixed_with_temp */
    case 192:  /* *floatsidf2_mixed_interunit */
    case 193:  /* *floatdidf2_mixed_interunit */
    case 196:  /* *floatsidf2_mixed_nointerunit */
    case 197:  /* *floatdidf2_mixed_nointerunit */
    case 201:  /* *floatsidf2_vector_sse */
    case 203:  /* *floatsidf2_sse_with_temp */
    case 206:  /* *floatsidf2_sse_interunit */
    case 207:  /* *floatdidf2_sse_interunit */
    case 210:  /* *floatsidf2_sse_nointerunit */
    case 211:  /* *floatdidf2_sse_nointerunit */
    case 213:  /* *floatsidf2_i387_with_temp */
    case 216:  /* *floatdidf2_i387_with_temp */
    case 219:  /* *floatsidf2_i387 */
    case 222:  /* *floatdidf2_i387 */
    case 225:  /* floatdidf2_i387_with_xmm */
    case 228:  /* *floatunssidf2_1 */
    case 400:  /* *absdf2_1 */
    case 401:  /* *negdf2_1 */
    case 404:  /* *absextendsfdf2 */
    case 405:  /* *negextendsfdf2 */
    case 502:  /* setcc_df_sse */
    case 628:  /* *fop_df_comm_mixed */
    case 630:  /* *fop_df_comm_sse */
    case 632:  /* *fop_df_comm_i387 */
    case 634:  /* *fop_df_1_mixed */
    case 637:  /* *fop_df_1_sse */
    case 639:  /* *fop_df_1_i387 */
    case 658:  /* *fop_xf_4_i387 */
    case 660:  /* *fop_xf_5_i387 */
    case 662:  /* *fop_xf_6_i387 */
    case 664:  /* truncxfdf2_i387_noop_unspec */
    case 670:  /* *sqrtdf2_sse */
    case 700:  /* sse4_1_rounddf2 */
    case 738:  /* fxamdf2_i387 */
    case 741:  /* fxamdf2_i387_with_temp */
    case 742:  /* movmsk_df */
    case 783:  /* smaxdf3 */
    case 784:  /* smindf3 */
    case 787:  /* *ieee_smaxdf3 */
    case 788:  /* *ieee_smindf3 */
    case 998:  /* sse2_vmaddv2df3 */
    case 999:  /* sse2_vmsubv2df3 */
    case 1005:  /* sse2_vmmulv2df3 */
    case 1011:  /* sse2_vmdivv2df3 */
    case 1020:  /* sse2_vmsqrtv2df2 */
    case 1042:  /* sse2_vmsmaxv2df3 */
    case 1043:  /* sse2_vmsminv2df3 */
    case 1071:  /* avx_vmcmpv2df3 */
    case 1081:  /* sse2_vmmaskcmpv2df3 */
    case 1083:  /* sse2_comi */
    case 1085:  /* sse2_ucomi */
    case 1115:  /* *fma_fmadd_df */
    case 1121:  /* *fma_fmsub_df */
    case 1127:  /* *fma_fnmadd_df */
    case 1133:  /* *fma_fnmsub_df */
    case 1178:  /* sse2_cvtsi2sd */
    case 1192:  /* sse2_cvtss2sd */
    case 1513:  /* sse4a_movntdf */
    case 1515:  /* sse4a_vmmovntv2df */
    case 1655:  /* xop_frczdf2 */
    case 1876:  /* loaddi_via_fpu */
      return MODE_DF;

    case 17:  /* *cmpsf_0_i387 */
    case 20:  /* *cmpsf_0_cc_i387 */
    case 25:  /* *cmpsf_i387 */
    case 27:  /* *cmpsf_cc_i387 */
    case 29:  /* *cmpusf_i387 */
    case 32:  /* *cmpusf_cc_i387 */
    case 49:  /* *cmpisf_mixed */
    case 51:  /* *cmpiusf_mixed */
    case 53:  /* *cmpisf_sse */
    case 55:  /* *cmpiusf_sse */
    case 57:  /* *cmpisf_i387 */
    case 60:  /* *cmpiusf_i387 */
    case 115:  /* *swapsf */
    case 133:  /* *truncdfsf_fast_mixed */
    case 134:  /* *truncdfsf_fast_sse */
    case 135:  /* *truncdfsf_fast_i387 */
    case 136:  /* *truncdfsf_mixed */
    case 137:  /* *truncdfsf_i387 */
    case 138:  /* *truncdfsf2_i387_1 */
    case 139:  /* *truncxfsf2_mixed */
    case 141:  /* truncxfsf2_i387_noop */
    case 143:  /* *truncxfsf2_i387 */
    case 147:  /* fix_truncsfsi_sse */
    case 172:  /* *floathisf2_i387_with_temp */
    case 175:  /* *floathisf2_i387 */
    case 188:  /* *floatsisf2_mixed_with_temp */
    case 190:  /* *floatsisf2_mixed_interunit */
    case 191:  /* *floatdisf2_mixed_interunit */
    case 194:  /* *floatsisf2_mixed_nointerunit */
    case 195:  /* *floatdisf2_mixed_nointerunit */
    case 200:  /* *floatsisf2_vector_sse */
    case 202:  /* *floatsisf2_sse_with_temp */
    case 204:  /* *floatsisf2_sse_interunit */
    case 205:  /* *floatdisf2_sse_interunit */
    case 208:  /* *floatsisf2_sse_nointerunit */
    case 209:  /* *floatdisf2_sse_nointerunit */
    case 212:  /* *floatsisf2_i387_with_temp */
    case 215:  /* *floatdisf2_i387_with_temp */
    case 218:  /* *floatsisf2_i387 */
    case 221:  /* *floatdisf2_i387 */
    case 224:  /* floatdisf2_i387_with_xmm */
    case 227:  /* *floatunssisf2_1 */
    case 398:  /* *abssf2_1 */
    case 399:  /* *negsf2_1 */
    case 501:  /* setcc_sf_sse */
    case 627:  /* *fop_sf_comm_mixed */
    case 629:  /* *fop_sf_comm_sse */
    case 631:  /* *fop_sf_comm_i387 */
    case 633:  /* *fop_sf_1_mixed */
    case 635:  /* *rcpsf2_sse */
    case 636:  /* *fop_sf_1_sse */
    case 638:  /* *fop_sf_1_i387 */
    case 648:  /* *fop_df_4_i387 */
    case 649:  /* *fop_df_5_i387 */
    case 650:  /* *fop_df_6_i387 */
    case 657:  /* *fop_xf_4_i387 */
    case 659:  /* *fop_xf_5_i387 */
    case 661:  /* *fop_xf_6_i387 */
    case 663:  /* truncxfsf2_i387_noop_unspec */
    case 668:  /* *rsqrtsf2_sse */
    case 669:  /* *sqrtsf2_sse */
    case 699:  /* sse4_1_roundsf2 */
    case 737:  /* fxamsf2_i387 */
    case 740:  /* fxamsf2_i387_with_temp */
    case 781:  /* smaxsf3 */
    case 782:  /* sminsf3 */
    case 785:  /* *ieee_smaxsf3 */
    case 786:  /* *ieee_sminsf3 */
    case 996:  /* sse_vmaddv4sf3 */
    case 997:  /* sse_vmsubv4sf3 */
    case 1004:  /* sse_vmmulv4sf3 */
    case 1010:  /* sse_vmdivv4sf3 */
    case 1014:  /* sse_vmrcpv4sf2 */
    case 1019:  /* sse_vmsqrtv4sf2 */
    case 1023:  /* sse_vmrsqrtv4sf2 */
    case 1040:  /* sse_vmsmaxv4sf3 */
    case 1041:  /* sse_vmsminv4sf3 */
    case 1070:  /* avx_vmcmpv4sf3 */
    case 1080:  /* sse_vmmaskcmpv4sf3 */
    case 1082:  /* sse_comi */
    case 1084:  /* sse_ucomi */
    case 1114:  /* *fma_fmadd_sf */
    case 1120:  /* *fma_fmsub_sf */
    case 1126:  /* *fma_fnmadd_sf */
    case 1132:  /* *fma_fnmsub_sf */
    case 1164:  /* sse_cvttps2pi */
    case 1165:  /* sse_cvtsi2ss */
    case 1191:  /* sse2_cvtsd2ss */
    case 1215:  /* sse_movss */
    case 1512:  /* sse4a_movntsf */
    case 1514:  /* sse4a_vmmovntv4sf */
    case 1654:  /* xop_frczsf2 */
      return MODE_SF;

    case 975:  /* avx_lddqu256 */
    case 982:  /* avx_movntv4di */
    case 1171:  /* avx_cvtps2dq256 */
    case 1173:  /* fix_truncv8sfv8si2 */
    case 1185:  /* avx_cvtpd2dq256 */
    case 1186:  /* *avx_cvtpd2dq256_2 */
    case 1188:  /* fix_truncv4dfv4si2 */
    case 1189:  /* *avx_cvttpd2dq256_2 */
    case 1232:  /* vec_extract_hi_v4di */
    case 1236:  /* vec_extract_hi_v8si */
    case 1239:  /* vec_extract_hi_v16hi */
    case 1241:  /* vec_extract_hi_v32qi */
    case 1247:  /* avx2_interleave_highv4di */
    case 1249:  /* avx2_interleave_lowv4di */
    case 1262:  /* *addv32qi3 */
    case 1263:  /* *subv32qi3 */
    case 1266:  /* *addv16hi3 */
    case 1267:  /* *subv16hi3 */
    case 1270:  /* *addv8si3 */
    case 1271:  /* *subv8si3 */
    case 1274:  /* *addv4di3 */
    case 1275:  /* *subv4di3 */
    case 1294:  /* *mulv16hi3 */
    case 1296:  /* *smulv16hi3_highpart */
    case 1297:  /* *umulv16hi3_highpart */
    case 1300:  /* *vec_widen_umult_even_v8si */
    case 1302:  /* *vec_widen_smult_even_v8si */
    case 1304:  /* *avx2_pmaddwd */
    case 1306:  /* *avx2_mulv8si3 */
    case 1308:  /* ashrv16hi3 */
    case 1310:  /* ashrv8si3 */
    case 1312:  /* ashlv16hi3 */
    case 1313:  /* lshrv16hi3 */
    case 1316:  /* ashlv8si3 */
    case 1317:  /* lshrv8si3 */
    case 1320:  /* ashlv4di3 */
    case 1321:  /* lshrv4di3 */
    case 1324:  /* avx2_ashlv2ti3 */
    case 1326:  /* avx2_lshrv2ti3 */
    case 1328:  /* *avx2_smaxv32qi3 */
    case 1329:  /* *avx2_sminv32qi3 */
    case 1330:  /* *avx2_umaxv32qi3 */
    case 1331:  /* *avx2_uminv32qi3 */
    case 1332:  /* *avx2_smaxv16hi3 */
    case 1333:  /* *avx2_sminv16hi3 */
    case 1334:  /* *avx2_umaxv16hi3 */
    case 1335:  /* *avx2_uminv16hi3 */
    case 1336:  /* *avx2_smaxv8si3 */
    case 1337:  /* *avx2_sminv8si3 */
    case 1338:  /* *avx2_umaxv8si3 */
    case 1339:  /* *avx2_uminv8si3 */
    case 1352:  /* *avx2_eqv32qi3 */
    case 1353:  /* *avx2_eqv16hi3 */
    case 1354:  /* *avx2_eqv8si3 */
    case 1355:  /* *avx2_eqv4di3 */
    case 1361:  /* avx2_gtv32qi3 */
    case 1362:  /* avx2_gtv16hi3 */
    case 1363:  /* avx2_gtv8si3 */
    case 1364:  /* avx2_gtv4di3 */
    case 1400:  /* avx2_packsswb */
    case 1402:  /* avx2_packssdw */
    case 1404:  /* avx2_packuswb */
    case 1406:  /* avx2_interleave_highv32qi */
    case 1408:  /* avx2_interleave_lowv32qi */
    case 1410:  /* avx2_interleave_highv16hi */
    case 1412:  /* avx2_interleave_lowv16hi */
    case 1414:  /* avx2_interleave_highv8si */
    case 1416:  /* avx2_interleave_lowv8si */
    case 1427:  /* avx2_pshufd_1 */
    case 1429:  /* avx2_pshuflw_1 */
    case 1431:  /* avx2_pshufhw_1 */
    case 1445:  /* *avx2_uavgv32qi3 */
    case 1447:  /* *avx2_uavgv16hi3 */
    case 1449:  /* avx2_psadbw */
    case 1464:  /* avx2_phaddwv16hi3 */
    case 1465:  /* avx2_phaddswv16hi3 */
    case 1466:  /* avx2_phsubwv16hi3 */
    case 1467:  /* avx2_phsubswv16hi3 */
    case 1476:  /* avx2_phadddv8si3 */
    case 1477:  /* avx2_phsubdv8si3 */
    case 1482:  /* avx2_pmaddubsw256 */
    case 1485:  /* *avx2_pmulhrswv16hi3 */
    case 1488:  /* avx2_pshufbv32qi3 */
    case 1491:  /* avx2_psignv32qi3 */
    case 1493:  /* avx2_psignv16hi3 */
    case 1495:  /* avx2_psignv8si3 */
    case 1500:  /* avx2_palignrv2ti */
    case 1503:  /* absv32qi2 */
    case 1505:  /* absv16hi2 */
    case 1507:  /* absv8si2 */
    case 1532:  /* avx2_movntdqa */
    case 1534:  /* avx2_mpsadbw */
    case 1536:  /* avx2_packusdw */
    case 1538:  /* avx2_pblendvb */
    case 1541:  /* *avx2_pblendw */
    case 1542:  /* avx2_pblenddv8si */
    case 1545:  /* avx2_sign_extendv16qiv16hi2 */
    case 1546:  /* avx2_zero_extendv16qiv16hi2 */
    case 1549:  /* avx2_sign_extendv8qiv8si2 */
    case 1550:  /* avx2_zero_extendv8qiv8si2 */
    case 1553:  /* avx2_sign_extendv8hiv8si2 */
    case 1554:  /* avx2_zero_extendv8hiv8si2 */
    case 1557:  /* avx2_sign_extendv4qiv4di2 */
    case 1558:  /* avx2_zero_extendv4qiv4di2 */
    case 1561:  /* avx2_sign_extendv4hiv4di2 */
    case 1562:  /* avx2_zero_extendv4hiv4di2 */
    case 1565:  /* avx2_sign_extendv4siv4di2 */
    case 1566:  /* avx2_zero_extendv4siv4di2 */
    case 1573:  /* avx_ptest256 */
    case 1689:  /* *avx_vzeroall */
    case 1690:  /* avx_vzeroupper */
    case 1691:  /* avx2_pbroadcastv32qi */
    case 1693:  /* avx2_pbroadcastv16hi */
    case 1695:  /* avx2_pbroadcastv8si */
    case 1697:  /* avx2_pbroadcastv4di */
    case 1699:  /* avx2_pbroadcastv32qi_1 */
    case 1700:  /* avx2_pbroadcastv16hi_1 */
    case 1701:  /* avx2_pbroadcastv8si_1 */
    case 1702:  /* avx2_pbroadcastv4di_1 */
    case 1703:  /* avx2_permvarv8si */
    case 1704:  /* avx2_permvarv8sf */
    case 1705:  /* avx2_permv4di_1 */
    case 1707:  /* avx2_permv2ti */
    case 1713:  /* avx2_vbroadcasti128_v32qi */
    case 1714:  /* avx2_vbroadcasti128_v16hi */
    case 1715:  /* avx2_vbroadcasti128_v8si */
    case 1716:  /* avx2_vbroadcasti128_v4di */
    case 1717:  /* avx_vbroadcastf128_v32qi */
    case 1718:  /* avx_vbroadcastf128_v16hi */
    case 1719:  /* avx_vbroadcastf128_v8si */
    case 1720:  /* avx_vbroadcastf128_v4di */
    case 1734:  /* *avx_vperm2f128v8si_full */
    case 1737:  /* *avx_vperm2f128v8si_nozero */
    case 1740:  /* avx2_vec_set_lo_v4di */
    case 1741:  /* avx2_vec_set_hi_v4di */
    case 1742:  /* vec_set_lo_v4di */
    case 1744:  /* vec_set_hi_v4di */
    case 1746:  /* vec_set_lo_v8si */
    case 1748:  /* vec_set_hi_v8si */
    case 1750:  /* vec_set_lo_v16hi */
    case 1751:  /* vec_set_hi_v16hi */
    case 1752:  /* vec_set_lo_v32qi */
    case 1753:  /* vec_set_hi_v32qi */
    case 1760:  /* avx2_maskloadd256 */
    case 1761:  /* avx2_maskloadq256 */
    case 1768:  /* avx2_maskstored256 */
    case 1769:  /* avx2_maskstoreq256 */
    case 1773:  /* avx2_ashrvv8si */
    case 1775:  /* avx2_ashlvv8si */
    case 1776:  /* avx2_lshrvv8si */
    case 1779:  /* avx2_ashlvv4di */
    case 1780:  /* avx2_lshrvv4di */
    case 1783:  /* avx_vec_concatv32qi */
    case 1784:  /* avx_vec_concatv16hi */
    case 1785:  /* avx_vec_concatv8si */
    case 1786:  /* avx_vec_concatv4di */
    case 1799:  /* *avx2_gathersiv4di */
    case 1800:  /* *avx2_gathersiv4di */
    case 1807:  /* *avx2_gathersiv8si */
    case 1808:  /* *avx2_gathersiv8si */
    case 1815:  /* *avx2_gathersiv4di_2 */
    case 1816:  /* *avx2_gathersiv4di_2 */
    case 1823:  /* *avx2_gathersiv8si_2 */
    case 1824:  /* *avx2_gathersiv8si_2 */
    case 1831:  /* *avx2_gatherdiv4di */
    case 1832:  /* *avx2_gatherdiv4di */
    case 1839:  /* *avx2_gatherdiv8si */
    case 1840:  /* *avx2_gatherdiv8si */
    case 1847:  /* *avx2_gatherdiv4di_2 */
    case 1848:  /* *avx2_gatherdiv4di_2 */
    case 1855:  /* *avx2_gatherdiv8si_2 */
    case 1856:  /* *avx2_gatherdiv8si_2 */
    case 1859:  /* *avx2_gatherdiv8si_3 */
    case 1860:  /* *avx2_gatherdiv8si_3 */
    case 1863:  /* *avx2_gatherdiv8si_4 */
    case 1864:  /* *avx2_gatherdiv8si_4 */
      return MODE_OI;

    case 961:  /* sse2_movq128 */
    case 976:  /* sse3_lddqu */
    case 983:  /* sse2_movntv2di */
    case 1172:  /* sse2_cvtps2dq */
    case 1174:  /* fix_truncv4sfv4si2 */
    case 1177:  /* sse2_cvttpd2pi */
    case 1187:  /* *sse2_cvtpd2dq */
    case 1190:  /* *sse2_cvttpd2dq */
    case 1248:  /* vec_interleave_highv2di */
    case 1250:  /* vec_interleave_lowv2di */
    case 1264:  /* *addv16qi3 */
    case 1265:  /* *subv16qi3 */
    case 1268:  /* *addv8hi3 */
    case 1269:  /* *subv8hi3 */
    case 1272:  /* *addv4si3 */
    case 1273:  /* *subv4si3 */
    case 1276:  /* *addv2di3 */
    case 1277:  /* *subv2di3 */
    case 1278:  /* *avx2_ssaddv32qi3 */
    case 1279:  /* *avx2_usaddv32qi3 */
    case 1280:  /* *avx2_sssubv32qi3 */
    case 1281:  /* *avx2_ussubv32qi3 */
    case 1282:  /* *sse2_ssaddv16qi3 */
    case 1283:  /* *sse2_usaddv16qi3 */
    case 1284:  /* *sse2_sssubv16qi3 */
    case 1285:  /* *sse2_ussubv16qi3 */
    case 1286:  /* *avx2_ssaddv16hi3 */
    case 1287:  /* *avx2_usaddv16hi3 */
    case 1288:  /* *avx2_sssubv16hi3 */
    case 1289:  /* *avx2_ussubv16hi3 */
    case 1290:  /* *sse2_ssaddv8hi3 */
    case 1291:  /* *sse2_usaddv8hi3 */
    case 1292:  /* *sse2_sssubv8hi3 */
    case 1293:  /* *sse2_ussubv8hi3 */
    case 1295:  /* *mulv8hi3 */
    case 1298:  /* *smulv8hi3_highpart */
    case 1299:  /* *umulv8hi3_highpart */
    case 1301:  /* *vec_widen_umult_even_v4si */
    case 1303:  /* *sse4_1_mulv2siv2di3 */
    case 1305:  /* *sse2_pmaddwd */
    case 1307:  /* *sse4_1_mulv4si3 */
    case 1309:  /* ashrv8hi3 */
    case 1311:  /* ashrv4si3 */
    case 1314:  /* ashlv8hi3 */
    case 1315:  /* lshrv8hi3 */
    case 1318:  /* ashlv4si3 */
    case 1319:  /* lshrv4si3 */
    case 1322:  /* ashlv2di3 */
    case 1323:  /* lshrv2di3 */
    case 1325:  /* sse2_ashlv1ti3 */
    case 1327:  /* sse2_lshrv1ti3 */
    case 1340:  /* *sse4_1_smaxv16qi3 */
    case 1341:  /* *sse4_1_sminv16qi3 */
    case 1342:  /* *sse4_1_smaxv4si3 */
    case 1343:  /* *sse4_1_sminv4si3 */
    case 1344:  /* *smaxv8hi3 */
    case 1345:  /* *sminv8hi3 */
    case 1346:  /* *sse4_1_umaxv8hi3 */
    case 1347:  /* *sse4_1_uminv8hi3 */
    case 1348:  /* *sse4_1_umaxv4si3 */
    case 1349:  /* *sse4_1_uminv4si3 */
    case 1350:  /* *umaxv16qi3 */
    case 1351:  /* *uminv16qi3 */
    case 1356:  /* *sse4_1_eqv2di3 */
    case 1357:  /* *sse2_eqv16qi3 */
    case 1358:  /* *sse2_eqv8hi3 */
    case 1359:  /* *sse2_eqv4si3 */
    case 1360:  /* sse4_2_gtv2di3 */
    case 1365:  /* sse2_gtv16qi3 */
    case 1366:  /* sse2_gtv8hi3 */
    case 1367:  /* sse2_gtv4si3 */
    case 1401:  /* sse2_packsswb */
    case 1403:  /* sse2_packssdw */
    case 1405:  /* sse2_packuswb */
    case 1407:  /* vec_interleave_highv16qi */
    case 1409:  /* vec_interleave_lowv16qi */
    case 1411:  /* vec_interleave_highv8hi */
    case 1413:  /* vec_interleave_lowv8hi */
    case 1415:  /* vec_interleave_highv4si */
    case 1417:  /* vec_interleave_lowv4si */
    case 1418:  /* sse4_1_pinsrb */
    case 1419:  /* sse2_pinsrw */
    case 1420:  /* sse4_1_pinsrd */
    case 1421:  /* sse4_1_pinsrq */
    case 1422:  /* *sse4_1_pextrb_si */
    case 1423:  /* *sse4_1_pextrb_memory */
    case 1424:  /* *sse2_pextrw_si */
    case 1425:  /* *sse4_1_pextrw_memory */
    case 1426:  /* *sse4_1_pextrd */
    case 1428:  /* sse2_pshufd_1 */
    case 1430:  /* sse2_pshuflw_1 */
    case 1432:  /* sse2_pshufhw_1 */
    case 1446:  /* *sse2_uavgv16qi3 */
    case 1448:  /* *sse2_uavgv8hi3 */
    case 1450:  /* sse2_psadbw */
    case 1457:  /* *sse2_maskmovdqu */
    case 1458:  /* *sse2_maskmovdqu */
    case 1468:  /* ssse3_phaddwv8hi3 */
    case 1469:  /* ssse3_phaddswv8hi3 */
    case 1470:  /* ssse3_phsubwv8hi3 */
    case 1471:  /* ssse3_phsubswv8hi3 */
    case 1478:  /* ssse3_phadddv4si3 */
    case 1479:  /* ssse3_phsubdv4si3 */
    case 1483:  /* ssse3_pmaddubsw128 */
    case 1486:  /* *ssse3_pmulhrswv8hi3 */
    case 1489:  /* ssse3_pshufbv16qi3 */
    case 1492:  /* ssse3_psignv16qi3 */
    case 1494:  /* ssse3_psignv8hi3 */
    case 1496:  /* ssse3_psignv4si3 */
    case 1501:  /* ssse3_palignrti */
    case 1504:  /* absv16qi2 */
    case 1506:  /* absv8hi2 */
    case 1508:  /* absv4si2 */
    case 1516:  /* sse4a_extrqi */
    case 1517:  /* sse4a_extrq */
    case 1518:  /* sse4a_insertqi */
    case 1519:  /* sse4a_insertq */
    case 1533:  /* sse4_1_movntdqa */
    case 1535:  /* sse4_1_mpsadbw */
    case 1537:  /* sse4_1_packusdw */
    case 1539:  /* sse4_1_pblendvb */
    case 1540:  /* sse4_1_pblendw */
    case 1543:  /* avx2_pblenddv4si */
    case 1544:  /* sse4_1_phminposuw */
    case 1547:  /* sse4_1_sign_extendv8qiv8hi2 */
    case 1548:  /* sse4_1_zero_extendv8qiv8hi2 */
    case 1551:  /* sse4_1_sign_extendv4qiv4si2 */
    case 1552:  /* sse4_1_zero_extendv4qiv4si2 */
    case 1555:  /* sse4_1_sign_extendv4hiv4si2 */
    case 1556:  /* sse4_1_zero_extendv4hiv4si2 */
    case 1559:  /* sse4_1_sign_extendv2qiv2di2 */
    case 1560:  /* sse4_1_zero_extendv2qiv2di2 */
    case 1563:  /* sse4_1_sign_extendv2hiv2di2 */
    case 1564:  /* sse4_1_zero_extendv2hiv2di2 */
    case 1567:  /* sse4_1_sign_extendv2siv2di2 */
    case 1568:  /* sse4_1_zero_extendv2siv2di2 */
    case 1574:  /* sse4_1_ptest */
    case 1581:  /* sse4_2_pcmpestr */
    case 1582:  /* *sse4_2_pcmpestr_unaligned */
    case 1583:  /* sse4_2_pcmpestri */
    case 1584:  /* sse4_2_pcmpestrm */
    case 1585:  /* sse4_2_pcmpestr_cconly */
    case 1586:  /* sse4_2_pcmpistr */
    case 1587:  /* *sse4_2_pcmpistr_unaligned */
    case 1588:  /* sse4_2_pcmpistri */
    case 1589:  /* sse4_2_pcmpistrm */
    case 1590:  /* sse4_2_pcmpistr_cconly */
    case 1591:  /* xop_pmacsww */
    case 1592:  /* xop_pmacssww */
    case 1593:  /* xop_pmacsdd */
    case 1594:  /* xop_pmacssdd */
    case 1595:  /* xop_pmacsdql */
    case 1596:  /* xop_pmacssdql */
    case 1597:  /* xop_pmacsdqh */
    case 1598:  /* xop_pmacssdqh */
    case 1599:  /* xop_pmacswd */
    case 1600:  /* xop_pmacsswd */
    case 1601:  /* xop_pmadcswd */
    case 1602:  /* xop_pmadcsswd */
    case 1630:  /* xop_pperm */
    case 1631:  /* xop_pperm_pack_v2di_v4si */
    case 1632:  /* xop_pperm_pack_v4si_v8hi */
    case 1633:  /* xop_pperm_pack_v8hi_v16qi */
    case 1634:  /* xop_rotlv16qi3 */
    case 1635:  /* xop_rotlv8hi3 */
    case 1636:  /* xop_rotlv4si3 */
    case 1637:  /* xop_rotlv2di3 */
    case 1638:  /* xop_rotrv16qi3 */
    case 1639:  /* xop_rotrv8hi3 */
    case 1640:  /* xop_rotrv4si3 */
    case 1641:  /* xop_rotrv2di3 */
    case 1642:  /* xop_vrotlv16qi3 */
    case 1643:  /* xop_vrotlv8hi3 */
    case 1644:  /* xop_vrotlv4si3 */
    case 1645:  /* xop_vrotlv2di3 */
    case 1646:  /* xop_shav16qi3 */
    case 1647:  /* xop_shav8hi3 */
    case 1648:  /* xop_shav4si3 */
    case 1649:  /* xop_shav2di3 */
    case 1650:  /* xop_shlv16qi3 */
    case 1651:  /* xop_shlv8hi3 */
    case 1652:  /* xop_shlv4si3 */
    case 1653:  /* xop_shlv2di3 */
    case 1662:  /* xop_maskcmpv16qi3 */
    case 1663:  /* xop_maskcmpv8hi3 */
    case 1664:  /* xop_maskcmpv4si3 */
    case 1665:  /* xop_maskcmpv2di3 */
    case 1666:  /* xop_maskcmp_unsv16qi3 */
    case 1667:  /* xop_maskcmp_unsv8hi3 */
    case 1668:  /* xop_maskcmp_unsv4si3 */
    case 1669:  /* xop_maskcmp_unsv2di3 */
    case 1670:  /* xop_maskcmp_uns2v16qi3 */
    case 1671:  /* xop_maskcmp_uns2v8hi3 */
    case 1672:  /* xop_maskcmp_uns2v4si3 */
    case 1673:  /* xop_maskcmp_uns2v2di3 */
    case 1674:  /* xop_pcom_tfv16qi3 */
    case 1675:  /* xop_pcom_tfv8hi3 */
    case 1676:  /* xop_pcom_tfv4si3 */
    case 1677:  /* xop_pcom_tfv2di3 */
    case 1682:  /* aesenc */
    case 1683:  /* aesenclast */
    case 1684:  /* aesdec */
    case 1685:  /* aesdeclast */
    case 1686:  /* aesimc */
    case 1687:  /* aeskeygenassist */
    case 1688:  /* pclmulqdq */
    case 1692:  /* avx2_pbroadcastv16qi */
    case 1694:  /* avx2_pbroadcastv8hi */
    case 1696:  /* avx2_pbroadcastv4si */
    case 1698:  /* avx2_pbroadcastv2di */
    case 1758:  /* avx2_maskloadd */
    case 1759:  /* avx2_maskloadq */
    case 1766:  /* avx2_maskstored */
    case 1767:  /* avx2_maskstoreq */
    case 1774:  /* avx2_ashrvv4si */
    case 1777:  /* avx2_ashlvv4si */
    case 1778:  /* avx2_lshrvv4si */
    case 1781:  /* avx2_ashlvv2di */
    case 1782:  /* avx2_lshrvv2di */
    case 1795:  /* *avx2_gathersiv2di */
    case 1796:  /* *avx2_gathersiv2di */
    case 1803:  /* *avx2_gathersiv4si */
    case 1804:  /* *avx2_gathersiv4si */
    case 1811:  /* *avx2_gathersiv2di_2 */
    case 1812:  /* *avx2_gathersiv2di_2 */
    case 1819:  /* *avx2_gathersiv4si_2 */
    case 1820:  /* *avx2_gathersiv4si_2 */
    case 1827:  /* *avx2_gatherdiv2di */
    case 1828:  /* *avx2_gatherdiv2di */
    case 1835:  /* *avx2_gatherdiv4si */
    case 1836:  /* *avx2_gatherdiv4si */
    case 1843:  /* *avx2_gatherdiv2di_2 */
    case 1844:  /* *avx2_gatherdiv2di_2 */
    case 1851:  /* *avx2_gatherdiv4si_2 */
    case 1852:  /* *avx2_gatherdiv4si_2 */
      return MODE_TI;

    case 4:  /* *cmpdi_ccno_1 */
    case 8:  /* *cmpdi_1 */
    case 12:  /* *cmpdi_minus_1 */
    case 63:  /* *pushdi2 */
    case 68:  /* *pushdi2_prologue */
    case 70:  /* *popdi1 */
    case 72:  /* *popdi1_epilogue */
    case 84:  /* *movabsdi_1 */
    case 88:  /* *movabsdi_2 */
    case 151:  /* fix_truncdi_fisttp_i387_1 */
    case 154:  /* fix_truncdi_i387_fisttp */
    case 157:  /* fix_truncdi_i387_fisttp_with_temp */
    case 160:  /* *fix_truncdi_i387_1 */
    case 161:  /* fix_truncdi_i387 */
    case 162:  /* fix_truncdi_i387_with_temp */
    case 234:  /* *adddi3_cc */
    case 237:  /* *adddi_1 */
    case 244:  /* *adddi_2 */
    case 248:  /* *adddi_3 */
    case 255:  /* *adddi_5 */
    case 268:  /* *subdi_1 */
    case 273:  /* *subdi_2 */
    case 277:  /* *subdi_3 */
    case 284:  /* *adddi3_carry */
    case 285:  /* *subdi3_carry */
    case 287:  /* adcxdi3 */
    case 300:  /* *adddi3_cc_overflow */
    case 301:  /* *subdi3_cc_overflow */
    case 349:  /* *iordi_1 */
    case 350:  /* *xordi_1 */
    case 361:  /* *iordi_2 */
    case 362:  /* *xordi_2 */
    case 371:  /* *iordi_3 */
    case 372:  /* *xordi_3 */
    case 385:  /* *negdi2_1 */
    case 389:  /* *negdi2_cmpz */
    case 418:  /* *one_cmpldi2_1 */
    case 423:  /* *one_cmpldi2_2 */
    case 427:  /* *ashldi3_mask */
    case 430:  /* *ashldi3_1 */
    case 437:  /* *ashldi3_cmp */
    case 441:  /* *ashldi3_cconly */
    case 444:  /* *lshrdi3_mask */
    case 445:  /* *ashrdi3_mask */
    case 454:  /* *lshrdi3_1 */
    case 455:  /* *ashrdi3_1 */
    case 468:  /* *lshrdi3_cmp */
    case 469:  /* *ashrdi3_cmp */
    case 476:  /* *lshrdi3_cconly */
    case 477:  /* *ashrdi3_cconly */
    case 480:  /* *rotldi3_mask */
    case 481:  /* *rotrdi3_mask */
    case 487:  /* *rotldi3_1 */
    case 488:  /* *rotrdi3_1 */
    case 496:  /* *btdi */
    case 570:  /* set_got_offset_rex64 */
    case 605:  /* *popcountdi2_cmp */
    case 702:  /* *fistdi2_1 */
    case 703:  /* fistdi2 */
    case 704:  /* fistdi2_with_temp */
    case 723:  /* *fistdi2_floor_1 */
    case 724:  /* *fistdi2_ceil_1 */
    case 725:  /* fistdi2_floor */
    case 726:  /* fistdi2_ceil */
    case 727:  /* fistdi2_floor_with_temp */
    case 728:  /* fistdi2_ceil_with_temp */
    case 790:  /* pro_epilogue_adjust_stack_di_add */
    case 792:  /* pro_epilogue_adjust_stack_di_sub */
    case 822:  /* *lwp_llwpcbdi1 */
    case 824:  /* lwp_slwpcbdi */
    case 841:  /* sse_movntq */
    case 865:  /* *vec_dupv2sf */
    case 866:  /* *mmx_concatv2sf */
    case 869:  /* *mmx_addv8qi3 */
    case 870:  /* *mmx_subv8qi3 */
    case 871:  /* *mmx_addv4hi3 */
    case 872:  /* *mmx_subv4hi3 */
    case 873:  /* *mmx_addv2si3 */
    case 874:  /* *mmx_subv2si3 */
    case 875:  /* *mmx_addv1di3 */
    case 876:  /* *mmx_subv1di3 */
    case 877:  /* *mmx_ssaddv8qi3 */
    case 878:  /* *mmx_usaddv8qi3 */
    case 879:  /* *mmx_sssubv8qi3 */
    case 880:  /* *mmx_ussubv8qi3 */
    case 881:  /* *mmx_ssaddv4hi3 */
    case 882:  /* *mmx_usaddv4hi3 */
    case 883:  /* *mmx_sssubv4hi3 */
    case 884:  /* *mmx_ussubv4hi3 */
    case 885:  /* *mmx_mulv4hi3 */
    case 886:  /* *mmx_smulv4hi3_highpart */
    case 887:  /* *mmx_umulv4hi3_highpart */
    case 888:  /* *mmx_pmaddwd */
    case 889:  /* *mmx_pmulhrwv4hi3 */
    case 890:  /* *sse2_umulv1siv1di3 */
    case 891:  /* *mmx_smaxv4hi3 */
    case 892:  /* *mmx_sminv4hi3 */
    case 893:  /* *mmx_umaxv8qi3 */
    case 894:  /* *mmx_uminv8qi3 */
    case 895:  /* mmx_ashrv4hi3 */
    case 896:  /* mmx_ashrv2si3 */
    case 897:  /* mmx_ashlv4hi3 */
    case 898:  /* mmx_lshrv4hi3 */
    case 899:  /* mmx_ashlv2si3 */
    case 900:  /* mmx_lshrv2si3 */
    case 901:  /* mmx_ashlv1di3 */
    case 902:  /* mmx_lshrv1di3 */
    case 903:  /* *mmx_eqv8qi3 */
    case 904:  /* *mmx_eqv4hi3 */
    case 905:  /* *mmx_eqv2si3 */
    case 906:  /* mmx_gtv8qi3 */
    case 907:  /* mmx_gtv4hi3 */
    case 908:  /* mmx_gtv2si3 */
    case 909:  /* mmx_andnotv8qi3 */
    case 910:  /* mmx_andnotv4hi3 */
    case 911:  /* mmx_andnotv2si3 */
    case 912:  /* *mmx_andv8qi3 */
    case 913:  /* *mmx_iorv8qi3 */
    case 914:  /* *mmx_xorv8qi3 */
    case 915:  /* *mmx_andv4hi3 */
    case 916:  /* *mmx_iorv4hi3 */
    case 917:  /* *mmx_xorv4hi3 */
    case 918:  /* *mmx_andv2si3 */
    case 919:  /* *mmx_iorv2si3 */
    case 920:  /* *mmx_xorv2si3 */
    case 921:  /* mmx_packsswb */
    case 922:  /* mmx_packssdw */
    case 923:  /* mmx_packuswb */
    case 924:  /* mmx_punpckhbw */
    case 925:  /* mmx_punpcklbw */
    case 926:  /* mmx_punpckhwd */
    case 927:  /* mmx_punpcklwd */
    case 928:  /* mmx_punpckhdq */
    case 929:  /* mmx_punpckldq */
    case 930:  /* *mmx_pinsrw */
    case 931:  /* mmx_pextrw */
    case 932:  /* mmx_pshufw_1 */
    case 933:  /* mmx_pswapdv2si2 */
    case 934:  /* *vec_dupv4hi */
    case 935:  /* *vec_dupv2si */
    case 936:  /* *mmx_concatv2si */
    case 939:  /* *mmx_uavgv8qi3 */
    case 940:  /* *mmx_uavgv4hi3 */
    case 941:  /* mmx_psadbw */
    case 942:  /* mmx_pmovmskb */
    case 943:  /* *mmx_maskmovq */
    case 944:  /* *mmx_maskmovq */
    case 1163:  /* sse_cvtps2pi */
    case 1176:  /* sse2_cvtpd2pi */
    case 1455:  /* avx2_pmovmskb */
    case 1472:  /* ssse3_phaddwv4hi3 */
    case 1473:  /* ssse3_phaddswv4hi3 */
    case 1474:  /* ssse3_phsubwv4hi3 */
    case 1475:  /* ssse3_phsubswv4hi3 */
    case 1480:  /* ssse3_phadddv2si3 */
    case 1481:  /* ssse3_phsubdv2si3 */
    case 1484:  /* ssse3_pmaddubsw */
    case 1487:  /* *ssse3_pmulhrswv4hi3 */
    case 1490:  /* ssse3_pshufbv8qi3 */
    case 1497:  /* ssse3_psignv8qi3 */
    case 1498:  /* ssse3_psignv4hi3 */
    case 1499:  /* ssse3_psignv2si3 */
    case 1502:  /* ssse3_palignrdi */
    case 1509:  /* absv8qi2 */
    case 1510:  /* absv4hi2 */
    case 1511:  /* absv2si2 */
    case 1877:  /* storedi_via_fpu */
      return MODE_DI;

    case 3:  /* *cmpsi_ccno_1 */
    case 7:  /* *cmpsi_1 */
    case 11:  /* *cmpsi_minus_1 */
    case 38:  /* *cmpsf_si_i387 */
    case 39:  /* *cmpdf_si_i387 */
    case 40:  /* *cmpxf_si_i387 */
    case 44:  /* *cmpsf_si_cc_i387 */
    case 45:  /* *cmpdf_si_cc_i387 */
    case 46:  /* *cmpxf_si_cc_i387 */
    case 47:  /* x86_fnstsw_1 */
    case 48:  /* x86_sahf_1 */
    case 64:  /* *pushsi2 */
    case 65:  /* *pushqi2 */
    case 66:  /* *pushhi2 */
    case 67:  /* *pushsi2_prologue */
    case 69:  /* *popsi1 */
    case 71:  /* *popsi1_epilogue */
    case 73:  /* *movsi_xor */
    case 74:  /* *movsi_or */
    case 83:  /* *movabssi_1 */
    case 87:  /* *movabssi_2 */
    case 89:  /* swapsi */
    case 90:  /* *swapqi_1 */
    case 91:  /* *swaphi_1 */
    case 98:  /* *movhi_extv_1 */
    case 99:  /* *movsi_extv_1 */
    case 101:  /* *movsi_extzv_1 */
    case 118:  /* zero_extendqisi2_and */
    case 119:  /* zero_extendhisi2_and */
    case 120:  /* *zero_extendqisi2 */
    case 121:  /* *zero_extendhisi2 */
    case 122:  /* zero_extendqihi2_and */
    case 123:  /* *zero_extendqihi2 */
    case 125:  /* extendhisi2 */
    case 126:  /* extendqisi2 */
    case 150:  /* fix_truncsi_fisttp_i387_1 */
    case 153:  /* fix_truncsi_i387_fisttp */
    case 156:  /* fix_truncsi_i387_fisttp_with_temp */
    case 159:  /* *fix_truncsi_i387_1 */
    case 164:  /* fix_truncsi_i387 */
    case 166:  /* fix_truncsi_i387_with_temp */
    case 230:  /* *leasi */
    case 233:  /* *addsi3_cc */
    case 236:  /* *addsi_1 */
    case 243:  /* *addsi_2 */
    case 247:  /* *addsi_3 */
    case 251:  /* *addsi_4 */
    case 254:  /* *addsi_5 */
    case 258:  /* *lea_general_1 */
    case 259:  /* *lea_general_2 */
    case 260:  /* *lea_general_3 */
    case 267:  /* *subsi_1 */
    case 272:  /* *subsi_2 */
    case 276:  /* *subsi_3 */
    case 282:  /* *addsi3_carry */
    case 283:  /* *subsi3_carry */
    case 286:  /* adcxsi3 */
    case 290:  /* *addsi3_cconly_overflow */
    case 293:  /* *subsi3_cconly_overflow */
    case 298:  /* *addsi3_cc_overflow */
    case 299:  /* *subsi3_cc_overflow */
    case 302:  /* *mulsi3_1 */
    case 305:  /* *bmi2_umulsidi3_1 */
    case 306:  /* *umulsidi3_1 */
    case 307:  /* *mulsidi3_1 */
    case 310:  /* *smulsi3_highpart_1 */
    case 311:  /* *umulsi3_highpart_1 */
    case 312:  /* divmodsi4_1 */
    case 314:  /* *divmodsi4 */
    case 316:  /* *divmodsi4_noext */
    case 318:  /* udivmodsi4_1 */
    case 320:  /* *udivmodsi4 */
    case 322:  /* *udivmodsi4_noext */
    case 327:  /* *testsi_1 */
    case 332:  /* *andsi_1 */
    case 339:  /* *andsi_2 */
    case 347:  /* *iorsi_1 */
    case 348:  /* *xorsi_1 */
    case 359:  /* *iorsi_2 */
    case 360:  /* *xorsi_2 */
    case 369:  /* *iorsi_3 */
    case 370:  /* *xorsi_3 */
    case 384:  /* *negsi2_1 */
    case 388:  /* *negsi2_cmpz */
    case 417:  /* *one_cmplsi2_1 */
    case 422:  /* *one_cmplsi2_2 */
    case 425:  /* x86_shld */
    case 426:  /* *ashlsi3_mask */
    case 428:  /* *bmi2_ashlsi3_1 */
    case 429:  /* *ashlsi3_1 */
    case 436:  /* *ashlsi3_cmp */
    case 440:  /* *ashlsi3_cconly */
    case 442:  /* *lshrsi3_mask */
    case 443:  /* *ashrsi3_mask */
    case 448:  /* x86_shrd */
    case 449:  /* ashrsi3_cvt */
    case 450:  /* *bmi2_lshrsi3_1 */
    case 451:  /* *bmi2_ashrsi3_1 */
    case 452:  /* *lshrsi3_1 */
    case 453:  /* *ashrsi3_1 */
    case 466:  /* *lshrsi3_cmp */
    case 467:  /* *ashrsi3_cmp */
    case 474:  /* *lshrsi3_cconly */
    case 475:  /* *ashrsi3_cconly */
    case 478:  /* *rotlsi3_mask */
    case 479:  /* *rotrsi3_mask */
    case 484:  /* *bmi2_rorxsi3_1 */
    case 485:  /* *rotlsi3_1 */
    case 486:  /* *rotrsi3_1 */
    case 495:  /* *btsi */
    case 575:  /* *tzcntsi_1 */
    case 576:  /* *bsfsi_1 */
    case 578:  /* ctzsi2 */
    case 580:  /* clzsi2_lzcnt */
    case 581:  /* *bmi_andn_si */
    case 582:  /* bmi_bextr_si */
    case 583:  /* *bmi_blsi_si */
    case 584:  /* *bmi_blsmsk_si */
    case 585:  /* *bmi_blsr_si */
    case 586:  /* bmi2_bzhi_si3 */
    case 587:  /* bmi2_pdep_si3 */
    case 588:  /* bmi2_pext_si3 */
    case 589:  /* tbm_bextri_si */
    case 590:  /* *tbm_blcfill_si */
    case 591:  /* *tbm_blci_si */
    case 592:  /* *tbm_blcic_si */
    case 593:  /* *tbm_blcmsk_si */
    case 594:  /* *tbm_blcs_si */
    case 595:  /* *tbm_blsfill_si */
    case 596:  /* *tbm_blsic_si */
    case 597:  /* *tbm_t1mskc_si */
    case 598:  /* *tbm_tzmsk_si */
    case 599:  /* bsr */
    case 602:  /* popcountsi2 */
    case 604:  /* *popcountsi2_cmp */
    case 606:  /* *bswapsi2_movbe */
    case 607:  /* *bswapsi2 */
    case 624:  /* *tls_dynamic_gnu2_lea_32 */
    case 642:  /* *fop_sf_2_i387 */
    case 643:  /* *fop_df_2_i387 */
    case 646:  /* *fop_sf_3_i387 */
    case 647:  /* *fop_df_3_i387 */
    case 654:  /* *fop_xf_2_i387 */
    case 656:  /* *fop_xf_3_i387 */
    case 706:  /* *fistsi2_1 */
    case 708:  /* fistsi2 */
    case 710:  /* fistsi2_with_temp */
    case 721:  /* *fistsi2_floor_1 */
    case 722:  /* *fistsi2_ceil_1 */
    case 731:  /* fistsi2_floor */
    case 732:  /* fistsi2_ceil */
    case 735:  /* fistsi2_floor_with_temp */
    case 736:  /* fistsi2_ceil_with_temp */
    case 744:  /* *strmovsi_1 */
    case 745:  /* *strmovsi_1 */
    case 750:  /* *rep_movsi */
    case 751:  /* *rep_movsi */
    case 754:  /* *strsetsi_1 */
    case 755:  /* *strsetsi_1 */
    case 760:  /* *rep_stossi */
    case 761:  /* *rep_stossi */
    case 770:  /* *x86_movsicc_0_m1 */
    case 771:  /* *x86_movsicc_0_m1_se */
    case 772:  /* *x86_movsicc_0_m1_neg */
    case 774:  /* *movsicc_noc */
    case 789:  /* pro_epilogue_adjust_stack_si_add */
    case 791:  /* pro_epilogue_adjust_stack_si_sub */
    case 810:  /* sse4_2_crc32qi */
    case 811:  /* sse4_2_crc32hi */
    case 812:  /* sse4_2_crc32si */
    case 821:  /* *lwp_llwpcbsi1 */
    case 823:  /* lwp_slwpcbsi */
    case 825:  /* *lwp_lwpvalsi3_1 */
    case 826:  /* *lwp_lwpinssi3_1 */
    case 977:  /* sse2_movntisi */
    case 1166:  /* sse_cvtss2si */
    case 1167:  /* sse_cvtss2si_2 */
    case 1168:  /* sse_cvttss2si */
    case 1179:  /* sse2_cvtsd2si */
    case 1180:  /* sse2_cvtsd2si_2 */
    case 1181:  /* sse2_cvttsd2si */
    case 1456:  /* sse2_pmovmskb */
      return MODE_SI;

    case 2:  /* *cmphi_ccno_1 */
    case 6:  /* *cmphi_1 */
    case 10:  /* *cmphi_minus_1 */
    case 35:  /* *cmpsf_hi_i387 */
    case 36:  /* *cmpdf_hi_i387 */
    case 37:  /* *cmpxf_hi_i387 */
    case 41:  /* *cmpsf_hi_cc_i387 */
    case 42:  /* *cmpdf_hi_cc_i387 */
    case 43:  /* *cmpxf_hi_cc_i387 */
    case 82:  /* *movabshi_1 */
    case 86:  /* *movabshi_2 */
    case 93:  /* *swaphi_2 */
    case 95:  /* *movstricthi_1 */
    case 97:  /* *movstricthi_xor */
    case 127:  /* extendqihi2 */
    case 149:  /* fix_trunchi_fisttp_i387_1 */
    case 152:  /* fix_trunchi_i387_fisttp */
    case 155:  /* fix_trunchi_i387_fisttp_with_temp */
    case 158:  /* *fix_trunchi_i387_1 */
    case 163:  /* fix_trunchi_i387 */
    case 165:  /* fix_trunchi_i387_with_temp */
    case 167:  /* x86_fnstcw_1 */
    case 168:  /* x86_fldcw_1 */
    case 242:  /* *addhi_2 */
    case 246:  /* *addhi_3 */
    case 250:  /* *addhi_4 */
    case 253:  /* *addhi_5 */
    case 266:  /* *subhi_1 */
    case 271:  /* *subhi_2 */
    case 275:  /* *subhi_3 */
    case 280:  /* *addhi3_carry */
    case 281:  /* *subhi3_carry */
    case 289:  /* *addhi3_cconly_overflow */
    case 292:  /* *subhi3_cconly_overflow */
    case 296:  /* *addhi3_cc_overflow */
    case 297:  /* *subhi3_cc_overflow */
    case 303:  /* *mulhi3_1 */
    case 313:  /* *divmodhi4 */
    case 315:  /* *divmodhi4_noext */
    case 319:  /* *udivmodhi4 */
    case 321:  /* *udivmodhi4_noext */
    case 326:  /* *testhi_1 */
    case 338:  /* *andhi_2 */
    case 345:  /* *iorhi_1 */
    case 346:  /* *xorhi_1 */
    case 357:  /* *iorhi_2 */
    case 358:  /* *xorhi_2 */
    case 367:  /* *iorhi_3 */
    case 368:  /* *xorhi_3 */
    case 383:  /* *neghi2_1 */
    case 387:  /* *neghi2_cmpz */
    case 416:  /* *one_cmplhi2_1 */
    case 421:  /* *one_cmplhi2_2 */
    case 435:  /* *ashlhi3_cmp */
    case 439:  /* *ashlhi3_cconly */
    case 458:  /* *lshrhi3_1 */
    case 459:  /* *ashrhi3_1 */
    case 464:  /* *lshrhi3_cmp */
    case 465:  /* *ashrhi3_cmp */
    case 472:  /* *lshrhi3_cconly */
    case 473:  /* *ashrhi3_cconly */
    case 491:  /* *rotlhi3_1 */
    case 492:  /* *rotrhi3_1 */
    case 577:  /* ctzhi2 */
    case 579:  /* clzhi2_lzcnt */
    case 600:  /* *bsrhi */
    case 601:  /* popcounthi2 */
    case 603:  /* *popcounthi2_cmp */
    case 609:  /* bswaphi_lowpart */
    case 612:  /* *parityhi2_cmp */
    case 640:  /* *fop_sf_2_i387 */
    case 641:  /* *fop_df_2_i387 */
    case 644:  /* *fop_sf_3_i387 */
    case 645:  /* *fop_df_3_i387 */
    case 653:  /* *fop_xf_2_i387 */
    case 655:  /* *fop_xf_3_i387 */
    case 705:  /* *fisthi2_1 */
    case 707:  /* fisthi2 */
    case 709:  /* fisthi2_with_temp */
    case 719:  /* *fisthi2_floor_1 */
    case 720:  /* *fisthi2_ceil_1 */
    case 729:  /* fisthi2_floor */
    case 730:  /* fisthi2_ceil */
    case 733:  /* fisthi2_floor_with_temp */
    case 734:  /* fisthi2_ceil_with_temp */
    case 746:  /* *strmovhi_1 */
    case 747:  /* *strmovhi_1 */
    case 756:  /* *strsethi_1 */
    case 757:  /* *strsethi_1 */
    case 773:  /* *movhicc_noc */
      return MODE_HI;

    case 1:  /* *cmpqi_ccno_1 */
    case 5:  /* *cmpqi_1 */
    case 9:  /* *cmpqi_minus_1 */
    case 13:  /* *cmpqi_ext_1 */
    case 14:  /* *cmpqi_ext_2 */
    case 15:  /* *cmpqi_ext_3_insn */
    case 16:  /* *cmpqi_ext_4 */
    case 81:  /* *movabsqi_1 */
    case 85:  /* *movabsqi_2 */
    case 92:  /* *swapqi_2 */
    case 94:  /* *movstrictqi_1 */
    case 96:  /* *movstrictqi_xor */
    case 103:  /* *movsi_insv_1 */
    case 104:  /* *movqi_insv_2 */
    case 235:  /* addqi3_cc */
    case 240:  /* *addqi_1_slp */
    case 241:  /* *addqi_2 */
    case 245:  /* *addqi_3 */
    case 249:  /* *addqi_4 */
    case 252:  /* *addqi_5 */
    case 256:  /* addqi_ext_1 */
    case 257:  /* *addqi_ext_2 */
    case 265:  /* *subqi_1 */
    case 269:  /* *subqi_1_slp */
    case 270:  /* *subqi_2 */
    case 274:  /* *subqi_3 */
    case 278:  /* *addqi3_carry */
    case 279:  /* *subqi3_carry */
    case 288:  /* *addqi3_cconly_overflow */
    case 291:  /* *subqi3_cconly_overflow */
    case 294:  /* *addqi3_cc_overflow */
    case 295:  /* *subqi3_cc_overflow */
    case 304:  /* *mulqi3_1 */
    case 308:  /* *mulqihi3_1 */
    case 309:  /* *umulqihi3_1 */
    case 317:  /* divmodhiqi3 */
    case 323:  /* udivmodhiqi3 */
    case 325:  /* *testqi_1 */
    case 328:  /* *testqi_ext_0 */
    case 329:  /* *testqi_ext_1 */
    case 330:  /* *testqi_ext_2 */
    case 335:  /* *andqi_1_slp */
    case 337:  /* *andqi_2 */
    case 340:  /* *andqi_2_slp */
    case 341:  /* andqi_ext_0 */
    case 342:  /* *andqi_ext_0_cc */
    case 343:  /* *andqi_ext_1 */
    case 344:  /* *andqi_ext_2 */
    case 353:  /* *iorqi_1_slp */
    case 354:  /* *xorqi_1_slp */
    case 355:  /* *iorqi_2 */
    case 356:  /* *xorqi_2 */
    case 363:  /* *iorqi_2_slp */
    case 364:  /* *xorqi_2_slp */
    case 365:  /* *iorqi_3 */
    case 366:  /* *xorqi_3 */
    case 373:  /* *iorqi_ext_0 */
    case 374:  /* *xorqi_ext_0 */
    case 375:  /* *iorqi_ext_1 */
    case 376:  /* *xorqi_ext_1 */
    case 377:  /* *iorqi_ext_2 */
    case 378:  /* *xorqi_ext_2 */
    case 379:  /* *xorqi_cc_ext_1 */
    case 382:  /* *negqi2_1 */
    case 386:  /* *negqi2_cmpz */
    case 420:  /* *one_cmplqi2_2 */
    case 433:  /* *ashlqi3_1_slp */
    case 434:  /* *ashlqi3_cmp */
    case 438:  /* *ashlqi3_cconly */
    case 456:  /* *lshrqi3_1 */
    case 457:  /* *ashrqi3_1 */
    case 460:  /* *lshrqi3_1_slp */
    case 461:  /* *ashrqi3_1_slp */
    case 462:  /* *lshrqi3_cmp */
    case 463:  /* *ashrqi3_cmp */
    case 470:  /* *lshrqi3_cconly */
    case 471:  /* *ashrqi3_cconly */
    case 489:  /* *rotlqi3_1 */
    case 490:  /* *rotrqi3_1 */
    case 493:  /* *rotlqi3_1_slp */
    case 494:  /* *rotrqi3_1_slp */
    case 499:  /* *setcc_qi */
    case 500:  /* *setcc_qi_slp */
    case 748:  /* *strmovqi_1 */
    case 749:  /* *strmovqi_1 */
    case 752:  /* *rep_movqi */
    case 753:  /* *rep_movqi */
    case 758:  /* *strsetqi_1 */
    case 759:  /* *strsetqi_1 */
    case 762:  /* *rep_stosqi */
    case 763:  /* *rep_stosqi */
    case 764:  /* *cmpstrnqi_nz_1 */
    case 765:  /* *cmpstrnqi_nz_1 */
    case 766:  /* *cmpstrnqi_1 */
    case 767:  /* *cmpstrnqi_1 */
    case 768:  /* *strlenqi_1 */
    case 769:  /* *strlenqi_1 */
    case 775:  /* *movqicc_noc */
      return MODE_QI;

    case -1:
      if (GET_CODE (PATTERN (insn)) != ASM_INPUT
          && asm_noperands (PATTERN (insn)) < 0)
        fatal_insn_not_found (insn);
    default:
      return MODE_UNKNOWN;

    }
}

enum attr_pent_pair
get_attr_pent_pair (rtx insn ATTRIBUTE_UNUSED)
{
  enum attr_type cached_type ATTRIBUTE_UNUSED;

  switch (recog_memoized (insn))
    {
    case 1258:  /* sse2_loadlpd */
      extract_constrain_insn_cached (insn);
      if (get_attr_imm_disp (insn) == IMM_DISP_TRUE)
        {
	  return PENT_PAIR_NP;
        }
      else if (which_alternative == 10)
        {
	  return PENT_PAIR_UV;
        }
      else
        {
	  return PENT_PAIR_NP;
        }

    case 1257:  /* sse2_loadhpd */
      extract_constrain_insn_cached (insn);
      if (get_attr_imm_disp (insn) == IMM_DISP_TRUE)
        {
	  return PENT_PAIR_NP;
        }
      else if (!((1 << which_alternative) & 0x3f))
        {
	  return PENT_PAIR_UV;
        }
      else
        {
	  return PENT_PAIR_NP;
        }

    case 1255:  /* sse2_storelpd */
      extract_constrain_insn_cached (insn);
      if (get_attr_imm_disp (insn) == IMM_DISP_TRUE)
        {
	  return PENT_PAIR_NP;
        }
      else if (!((1 << which_alternative) & 0xf))
        {
	  return PENT_PAIR_UV;
        }
      else
        {
	  return PENT_PAIR_NP;
        }

    case 1253:  /* sse2_storehpd */
      extract_constrain_insn_cached (insn);
      if (get_attr_imm_disp (insn) == IMM_DISP_TRUE)
        {
	  return PENT_PAIR_NP;
        }
      else if (!((1 << which_alternative) & 0x1f))
        {
	  if (get_attr_pent_prefix (insn) == PENT_PREFIX_TRUE)
	    {
	      return PENT_PAIR_PU;
	    }
	  else
	    {
	      return PENT_PAIR_UV;
	    }
        }
      else
        {
	  return PENT_PAIR_NP;
        }

    case 1224:  /* vec_setv4sf_0 */
    case 1223:  /* vec_setv4si_0 */
      extract_constrain_insn_cached (insn);
      if (get_attr_imm_disp (insn) == IMM_DISP_TRUE)
        {
	  return PENT_PAIR_NP;
        }
      else if (which_alternative == 9)
        {
	  return PENT_PAIR_UV;
        }
      else
        {
	  return PENT_PAIR_NP;
        }

    case 938:  /* *vec_extractv2si_1 */
      extract_constrain_insn_cached (insn);
      if (get_attr_imm_disp (insn) == IMM_DISP_TRUE)
        {
	  return PENT_PAIR_NP;
        }
      else if (!((1 << which_alternative) & 0x3f))
        {
	  return PENT_PAIR_UV;
        }
      else
        {
	  return PENT_PAIR_NP;
        }

    case 868:  /* *vec_extractv2sf_1 */
      extract_constrain_insn_cached (insn);
      if (get_attr_imm_disp (insn) == IMM_DISP_TRUE)
        {
	  return PENT_PAIR_NP;
        }
      else if (!((1 << which_alternative) & 0x1f))
        {
	  return PENT_PAIR_UV;
        }
      else
        {
	  return PENT_PAIR_NP;
        }

    case 790:  /* pro_epilogue_adjust_stack_di_add */
    case 789:  /* pro_epilogue_adjust_stack_si_add */
      extract_constrain_insn_cached (insn);
      if (get_attr_imm_disp (insn) == IMM_DISP_TRUE)
        {
	  return PENT_PAIR_NP;
        }
      else if (((which_alternative == 0) && (! (
#line 16519 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_OPT_AGU)))) || (((cached_type = get_attr_type (insn)) == TYPE_IMOV) || (cached_type == TYPE_LEA)))
        {
	  return PENT_PAIR_UV;
        }
      else
        {
	  return PENT_PAIR_NP;
        }

    case 606:  /* *bswapsi2_movbe */
      extract_constrain_insn_cached (insn);
      if (get_attr_imm_disp (insn) == IMM_DISP_TRUE)
        {
	  return PENT_PAIR_NP;
        }
      else if (which_alternative != 0)
        {
	  return PENT_PAIR_PU;
        }
      else
        {
	  return PENT_PAIR_NP;
        }

    case 557:  /* *sibcall_value_pop */
    case 556:  /* *call_value_pop */
    case 555:  /* *sibcall_value */
    case 554:  /* *sibcall_value */
    case 553:  /* *call_value */
    case 552:  /* *call_value */
      extract_insn_cached (insn);
      if (constant_call_address_operand (operands[1], VOIDmode))
        {
	  return PENT_PAIR_PV;
        }
      else
        {
	  return PENT_PAIR_NP;
        }

    case 625:  /* *tls_dynamic_gnu2_call_32 */
    case 551:  /* *sibcall_pop */
    case 550:  /* *call_pop */
    case 549:  /* *sibcall */
    case 548:  /* *sibcall */
    case 547:  /* *call */
    case 546:  /* *call */
      extract_insn_cached (insn);
      if (constant_call_address_operand (operands[0], VOIDmode))
        {
	  return PENT_PAIR_PV;
        }
      else
        {
	  return PENT_PAIR_NP;
        }

    case 494:  /* *rotrqi3_1_slp */
    case 493:  /* *rotlqi3_1_slp */
      extract_insn_cached (insn);
      if (get_attr_imm_disp (insn) == IMM_DISP_TRUE)
        {
	  return PENT_PAIR_NP;
        }
      else if (const1_operand (operands[1], VOIDmode))
        {
	  return PENT_PAIR_PU;
        }
      else
        {
	  return PENT_PAIR_NP;
        }

    case 488:  /* *rotrdi3_1 */
    case 487:  /* *rotldi3_1 */
    case 486:  /* *rotrsi3_1 */
    case 485:  /* *rotlsi3_1 */
      extract_constrain_insn_cached (insn);
      if (get_attr_imm_disp (insn) == IMM_DISP_TRUE)
        {
	  return PENT_PAIR_NP;
        }
      else if ((which_alternative == 0) && (const1_operand (operands[2], VOIDmode)))
        {
	  return PENT_PAIR_PU;
        }
      else
        {
	  return PENT_PAIR_NP;
        }

    case 492:  /* *rotrhi3_1 */
    case 491:  /* *rotlhi3_1 */
    case 490:  /* *rotrqi3_1 */
    case 489:  /* *rotlqi3_1 */
    case 481:  /* *rotrdi3_mask */
    case 480:  /* *rotldi3_mask */
    case 479:  /* *rotrsi3_mask */
    case 478:  /* *rotlsi3_mask */
      extract_insn_cached (insn);
      if (get_attr_imm_disp (insn) == IMM_DISP_TRUE)
        {
	  return PENT_PAIR_NP;
        }
      else if (const1_operand (operands[2], VOIDmode))
        {
	  return PENT_PAIR_PU;
        }
      else
        {
	  return PENT_PAIR_NP;
        }

    case 461:  /* *ashrqi3_1_slp */
    case 460:  /* *lshrqi3_1_slp */
      extract_insn_cached (insn);
      if (get_attr_imm_disp (insn) == IMM_DISP_TRUE)
        {
	  return PENT_PAIR_NP;
        }
      else if (const_int_operand (operands[1], VOIDmode))
        {
	  return PENT_PAIR_PU;
        }
      else
        {
	  return PENT_PAIR_NP;
        }

    case 455:  /* *ashrdi3_1 */
    case 454:  /* *lshrdi3_1 */
    case 453:  /* *ashrsi3_1 */
    case 452:  /* *lshrsi3_1 */
      extract_constrain_insn_cached (insn);
      if (get_attr_imm_disp (insn) == IMM_DISP_TRUE)
        {
	  return PENT_PAIR_NP;
        }
      else if ((which_alternative == 0) && (const_int_operand (operands[2], VOIDmode)))
        {
	  return PENT_PAIR_PU;
        }
      else
        {
	  return PENT_PAIR_NP;
        }

    case 449:  /* ashrsi3_cvt */
      extract_constrain_insn_cached (insn);
      if (get_attr_imm_disp (insn) == IMM_DISP_TRUE)
        {
	  return PENT_PAIR_NP;
        }
      else if ((which_alternative == 1) && (const_int_operand (operands[2], VOIDmode)))
        {
	  return PENT_PAIR_PU;
        }
      else
        {
	  return PENT_PAIR_NP;
        }

    case 477:  /* *ashrdi3_cconly */
    case 476:  /* *lshrdi3_cconly */
    case 475:  /* *ashrsi3_cconly */
    case 474:  /* *lshrsi3_cconly */
    case 473:  /* *ashrhi3_cconly */
    case 472:  /* *lshrhi3_cconly */
    case 471:  /* *ashrqi3_cconly */
    case 470:  /* *lshrqi3_cconly */
    case 469:  /* *ashrdi3_cmp */
    case 468:  /* *lshrdi3_cmp */
    case 467:  /* *ashrsi3_cmp */
    case 466:  /* *lshrsi3_cmp */
    case 465:  /* *ashrhi3_cmp */
    case 464:  /* *lshrhi3_cmp */
    case 463:  /* *ashrqi3_cmp */
    case 462:  /* *lshrqi3_cmp */
    case 459:  /* *ashrhi3_1 */
    case 458:  /* *lshrhi3_1 */
    case 457:  /* *ashrqi3_1 */
    case 456:  /* *lshrqi3_1 */
    case 445:  /* *ashrdi3_mask */
    case 444:  /* *lshrdi3_mask */
    case 443:  /* *ashrsi3_mask */
    case 442:  /* *lshrsi3_mask */
    case 427:  /* *ashldi3_mask */
    case 426:  /* *ashlsi3_mask */
      extract_insn_cached (insn);
      if (get_attr_imm_disp (insn) == IMM_DISP_TRUE)
        {
	  return PENT_PAIR_NP;
        }
      else if (const_int_operand (operands[2], VOIDmode))
        {
	  return PENT_PAIR_PU;
        }
      else
        {
	  return PENT_PAIR_NP;
        }

    case 333:  /* *andhi_1 */
      extract_constrain_insn_cached (insn);
      if (get_attr_imm_disp (insn) == IMM_DISP_TRUE)
        {
	  return PENT_PAIR_NP;
        }
      else if (((1 << which_alternative) & 0x3))
        {
	  return PENT_PAIR_PU;
        }
      else
        {
	  return PENT_PAIR_NP;
        }

    case 332:  /* *andsi_1 */
      extract_constrain_insn_cached (insn);
      if (get_attr_imm_disp (insn) == IMM_DISP_TRUE)
        {
	  return PENT_PAIR_NP;
        }
      else if (((1 << which_alternative) & 0x3))
        {
	  return PENT_PAIR_UV;
        }
      else
        {
	  return PENT_PAIR_NP;
        }

    case 253:  /* *addhi_5 */
    case 250:  /* *addhi_4 */
    case 246:  /* *addhi_3 */
    case 242:  /* *addhi_2 */
      if (get_attr_imm_disp (insn) == IMM_DISP_TRUE)
        {
	  return PENT_PAIR_NP;
        }
      else if (((cached_type = get_attr_type (insn)) == TYPE_ALU) || (cached_type == TYPE_INCDEC))
        {
	  return PENT_PAIR_PU;
        }
      else
        {
	  return PENT_PAIR_NP;
        }

    case 256:  /* addqi_ext_1 */
    case 255:  /* *adddi_5 */
    case 254:  /* *addsi_5 */
    case 252:  /* *addqi_5 */
    case 251:  /* *addsi_4 */
    case 249:  /* *addqi_4 */
    case 248:  /* *adddi_3 */
    case 247:  /* *addsi_3 */
    case 245:  /* *addqi_3 */
    case 244:  /* *adddi_2 */
    case 243:  /* *addsi_2 */
    case 241:  /* *addqi_2 */
      if (get_attr_imm_disp (insn) == IMM_DISP_TRUE)
        {
	  return PENT_PAIR_NP;
        }
      else if (((cached_type = get_attr_type (insn)) == TYPE_ALU) || (cached_type == TYPE_INCDEC))
        {
	  return PENT_PAIR_UV;
        }
      else
        {
	  return PENT_PAIR_NP;
        }

    case 240:  /* *addqi_1_slp */
      if (get_attr_imm_disp (insn) == IMM_DISP_TRUE)
        {
	  return PENT_PAIR_NP;
        }
      else if (((cached_type = get_attr_type (insn)) == TYPE_ALU1) || (cached_type == TYPE_INCDEC))
        {
	  return PENT_PAIR_UV;
        }
      else
        {
	  return PENT_PAIR_NP;
        }

    case 239:  /* *addqi_1 */
      extract_constrain_insn_cached (insn);
      if (get_attr_imm_disp (insn) == IMM_DISP_TRUE)
        {
	  return PENT_PAIR_NP;
        }
      else if (((cached_type = get_attr_type (insn)) == TYPE_ALU) || ((which_alternative == 5) || (cached_type == TYPE_INCDEC)))
        {
	  return PENT_PAIR_UV;
        }
      else
        {
	  return PENT_PAIR_NP;
        }

    case 238:  /* *addhi_1 */
      extract_constrain_insn_cached (insn);
      if (get_attr_imm_disp (insn) == IMM_DISP_TRUE)
        {
	  return PENT_PAIR_NP;
        }
      else if (((cached_type = get_attr_type (insn)) == TYPE_ALU) || ((which_alternative == 3) || (cached_type == TYPE_INCDEC)))
        {
	  if (((1 << which_alternative) & 0x7))
	    {
	      return PENT_PAIR_PU;
	    }
	  else
	    {
	      return PENT_PAIR_UV;
	    }
        }
      else
        {
	  return PENT_PAIR_NP;
        }

    case 237:  /* *adddi_1 */
    case 236:  /* *addsi_1 */
      extract_constrain_insn_cached (insn);
      if (get_attr_imm_disp (insn) == IMM_DISP_TRUE)
        {
	  return PENT_PAIR_NP;
        }
      else if (((cached_type = get_attr_type (insn)) == TYPE_ALU) || ((which_alternative == 3) || (cached_type == TYPE_INCDEC)))
        {
	  return PENT_PAIR_UV;
        }
      else
        {
	  return PENT_PAIR_NP;
        }

    case 113:  /* *movsf_internal */
      extract_constrain_insn_cached (insn);
      if (get_attr_imm_disp (insn) == IMM_DISP_TRUE)
        {
	  return PENT_PAIR_NP;
        }
      else if (((1 << which_alternative) & 0x18))
        {
	  if (get_attr_pent_prefix (insn) == PENT_PREFIX_TRUE)
	    {
	      return PENT_PAIR_PU;
	    }
	  else
	    {
	      return PENT_PAIR_UV;
	    }
        }
      else
        {
	  return PENT_PAIR_NP;
        }

    case 109:  /* *pushsf */
      extract_constrain_insn_cached (insn);
      if ((which_alternative == 1) && (! (get_attr_memory (insn) == MEMORY_BOTH)))
        {
	  return PENT_PAIR_UV;
        }
      else
        {
	  return PENT_PAIR_NP;
        }

    case 102:  /* *movqi_extzv_2 */
    case 100:  /* *movqi_extv_1 */
    case 80:  /* *movqi_internal */
      if (get_attr_imm_disp (insn) == IMM_DISP_TRUE)
        {
	  return PENT_PAIR_NP;
        }
      else if (get_attr_type (insn) == TYPE_IMOV)
        {
	  return PENT_PAIR_UV;
        }
      else
        {
	  return PENT_PAIR_NP;
        }

    case 79:  /* *movhi_internal */
      if (get_attr_imm_disp (insn) == IMM_DISP_TRUE)
        {
	  return PENT_PAIR_NP;
        }
      else if (get_attr_type (insn) == TYPE_IMOV)
        {
	  if (get_attr_pent_prefix (insn) == PENT_PREFIX_TRUE)
	    {
	      return PENT_PAIR_PU;
	    }
	  else
	    {
	      return PENT_PAIR_UV;
	    }
        }
      else
        {
	  return PENT_PAIR_NP;
        }

    case 72:  /* *popdi1_epilogue */
    case 71:  /* *popsi1_epilogue */
    case 70:  /* *popdi1 */
    case 69:  /* *popsi1 */
    case 68:  /* *pushdi2_prologue */
    case 67:  /* *pushsi2_prologue */
    case 66:  /* *pushhi2 */
    case 65:  /* *pushqi2 */
    case 64:  /* *pushsi2 */
      if (! (get_attr_memory (insn) == MEMORY_BOTH))
        {
	  return PENT_PAIR_UV;
        }
      else
        {
	  return PENT_PAIR_NP;
        }

    case 600:  /* *bsrhi */
    case 599:  /* bsr */
    case 578:  /* ctzsi2 */
    case 577:  /* ctzhi2 */
    case 576:  /* *bsfsi_1 */
    case 575:  /* *tzcntsi_1 */
    case 496:  /* *btdi */
    case 495:  /* *btsi */
    case 421:  /* *one_cmplhi2_2 */
    case 368:  /* *xorhi_3 */
    case 367:  /* *iorhi_3 */
    case 358:  /* *xorhi_2 */
    case 357:  /* *iorhi_2 */
    case 346:  /* *xorhi_1 */
    case 345:  /* *iorhi_1 */
    case 338:  /* *andhi_2 */
    case 297:  /* *subhi3_cc_overflow */
    case 296:  /* *addhi3_cc_overflow */
    case 292:  /* *subhi3_cconly_overflow */
    case 289:  /* *addhi3_cconly_overflow */
    case 275:  /* *subhi_3 */
    case 271:  /* *subhi_2 */
    case 266:  /* *subhi_1 */
    case 97:  /* *movstricthi_xor */
    case 95:  /* *movstricthi_1 */
    case 86:  /* *movabshi_2 */
    case 82:  /* *movabshi_1 */
    case 10:  /* *cmphi_minus_1 */
    case 6:  /* *cmphi_1 */
    case 2:  /* *cmphi_ccno_1 */
      if (get_attr_imm_disp (insn) == IMM_DISP_TRUE)
        {
	  return PENT_PAIR_NP;
        }
      else
        {
	  return PENT_PAIR_PU;
        }

    case 792:  /* pro_epilogue_adjust_stack_di_sub */
    case 791:  /* pro_epilogue_adjust_stack_si_sub */
    case 570:  /* set_got_offset_rex64 */
    case 423:  /* *one_cmpldi2_2 */
    case 422:  /* *one_cmplsi2_2 */
    case 420:  /* *one_cmplqi2_2 */
    case 379:  /* *xorqi_cc_ext_1 */
    case 378:  /* *xorqi_ext_2 */
    case 377:  /* *iorqi_ext_2 */
    case 376:  /* *xorqi_ext_1 */
    case 375:  /* *iorqi_ext_1 */
    case 374:  /* *xorqi_ext_0 */
    case 373:  /* *iorqi_ext_0 */
    case 372:  /* *xordi_3 */
    case 371:  /* *iordi_3 */
    case 370:  /* *xorsi_3 */
    case 369:  /* *iorsi_3 */
    case 366:  /* *xorqi_3 */
    case 365:  /* *iorqi_3 */
    case 364:  /* *xorqi_2_slp */
    case 363:  /* *iorqi_2_slp */
    case 362:  /* *xordi_2 */
    case 361:  /* *iordi_2 */
    case 360:  /* *xorsi_2 */
    case 359:  /* *iorsi_2 */
    case 356:  /* *xorqi_2 */
    case 355:  /* *iorqi_2 */
    case 354:  /* *xorqi_1_slp */
    case 353:  /* *iorqi_1_slp */
    case 352:  /* *xorqi_1 */
    case 351:  /* *iorqi_1 */
    case 350:  /* *xordi_1 */
    case 349:  /* *iordi_1 */
    case 348:  /* *xorsi_1 */
    case 347:  /* *iorsi_1 */
    case 344:  /* *andqi_ext_2 */
    case 343:  /* *andqi_ext_1 */
    case 342:  /* *andqi_ext_0_cc */
    case 341:  /* andqi_ext_0 */
    case 340:  /* *andqi_2_slp */
    case 339:  /* *andsi_2 */
    case 337:  /* *andqi_2 */
    case 336:  /* *andqi_2_maybe_si */
    case 335:  /* *andqi_1_slp */
    case 334:  /* *andqi_1 */
    case 330:  /* *testqi_ext_2 */
    case 329:  /* *testqi_ext_1 */
    case 301:  /* *subdi3_cc_overflow */
    case 300:  /* *adddi3_cc_overflow */
    case 299:  /* *subsi3_cc_overflow */
    case 298:  /* *addsi3_cc_overflow */
    case 295:  /* *subqi3_cc_overflow */
    case 294:  /* *addqi3_cc_overflow */
    case 293:  /* *subsi3_cconly_overflow */
    case 291:  /* *subqi3_cconly_overflow */
    case 290:  /* *addsi3_cconly_overflow */
    case 288:  /* *addqi3_cconly_overflow */
    case 287:  /* adcxdi3 */
    case 286:  /* adcxsi3 */
    case 277:  /* *subdi_3 */
    case 276:  /* *subsi_3 */
    case 274:  /* *subqi_3 */
    case 273:  /* *subdi_2 */
    case 272:  /* *subsi_2 */
    case 270:  /* *subqi_2 */
    case 269:  /* *subqi_1_slp */
    case 268:  /* *subdi_1 */
    case 267:  /* *subsi_1 */
    case 265:  /* *subqi_1 */
    case 257:  /* *addqi_ext_2 */
    case 235:  /* addqi3_cc */
    case 234:  /* *adddi3_cc */
    case 233:  /* *addsi3_cc */
    case 122:  /* zero_extendqihi2_and */
    case 119:  /* zero_extendhisi2_and */
    case 118:  /* zero_extendqisi2_and */
    case 104:  /* *movqi_insv_2 */
    case 103:  /* *movsi_insv_1 */
    case 96:  /* *movstrictqi_xor */
    case 94:  /* *movstrictqi_1 */
    case 88:  /* *movabsdi_2 */
    case 87:  /* *movabssi_2 */
    case 85:  /* *movabsqi_2 */
    case 84:  /* *movabsdi_1 */
    case 83:  /* *movabssi_1 */
    case 81:  /* *movabsqi_1 */
    case 74:  /* *movsi_or */
    case 73:  /* *movsi_xor */
    case 16:  /* *cmpqi_ext_4 */
    case 15:  /* *cmpqi_ext_3_insn */
    case 14:  /* *cmpqi_ext_2 */
    case 13:  /* *cmpqi_ext_1 */
    case 12:  /* *cmpdi_minus_1 */
    case 11:  /* *cmpsi_minus_1 */
    case 9:  /* *cmpqi_minus_1 */
    case 8:  /* *cmpdi_1 */
    case 7:  /* *cmpsi_1 */
    case 5:  /* *cmpqi_1 */
    case 4:  /* *cmpdi_ccno_1 */
    case 3:  /* *cmpsi_ccno_1 */
    case 1:  /* *cmpqi_ccno_1 */
      if (get_attr_imm_disp (insn) == IMM_DISP_TRUE)
        {
	  return PENT_PAIR_NP;
        }
      else
        {
	  return PENT_PAIR_UV;
        }

    case 324:  /* *testqi_1_maybe_si */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return PENT_PAIR_UV;
        }
      else if (which_alternative == 1)
        {
	  return PENT_PAIR_NP;
        }
      else if (which_alternative == 2)
        {
	  return PENT_PAIR_UV;
        }
      else
        {
	  return PENT_PAIR_NP;
        }

    case 325:  /* *testqi_1 */
    case 326:  /* *testhi_1 */
    case 327:  /* *testsi_1 */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return PENT_PAIR_UV;
        }
      else if (which_alternative == 1)
        {
	  return PENT_PAIR_NP;
        }
      else
        {
	  return PENT_PAIR_UV;
        }

    case -1:
      if (GET_CODE (PATTERN (insn)) != ASM_INPUT
          && asm_noperands (PATTERN (insn)) < 0)
        fatal_insn_not_found (insn);
    case 78:  /* *movsi_internal */
    case 429:  /* *ashlsi3_1 */
    case 430:  /* *ashldi3_1 */
    case 431:  /* *ashlhi3_1 */
    case 432:  /* *ashlqi3_1 */
    case 433:  /* *ashlqi3_1_slp */
    case 434:  /* *ashlqi3_cmp */
    case 435:  /* *ashlhi3_cmp */
    case 436:  /* *ashlsi3_cmp */
    case 437:  /* *ashldi3_cmp */
    case 438:  /* *ashlqi3_cconly */
    case 439:  /* *ashlhi3_cconly */
    case 440:  /* *ashlsi3_cconly */
    case 441:  /* *ashldi3_cconly */
      extract_insn_cached (insn);
      if (get_attr_imm_disp (insn) == IMM_DISP_TRUE)
        {
	  return PENT_PAIR_NP;
        }
      else if ((((cached_type = get_attr_type (insn)) == TYPE_ALU1) || ((cached_type == TYPE_ALU) || ((cached_type == TYPE_IMOV) || ((cached_type == TYPE_ICMP) || ((cached_type == TYPE_TEST) || ((cached_type == TYPE_LEA) || (cached_type == TYPE_INCDEC))))))) || (((cached_type == TYPE_POP) || (cached_type == TYPE_PUSH)) && (! (get_attr_memory (insn) == MEMORY_BOTH))))
        {
	  if (get_attr_pent_prefix (insn) == PENT_PREFIX_TRUE)
	    {
	      return PENT_PAIR_PU;
	    }
	  else
	    {
	      return PENT_PAIR_UV;
	    }
        }
      else if (cached_type == TYPE_IBR)
        {
	  return PENT_PAIR_PV;
        }
      else if ((cached_type == TYPE_ISHIFT) && (const_int_operand (operands[2], VOIDmode)))
        {
	  return PENT_PAIR_PU;
        }
      else if ((cached_type == TYPE_ROTATE) && (const1_operand (operands[2], VOIDmode)))
        {
	  return PENT_PAIR_PU;
        }
      else if ((cached_type == TYPE_ISHIFT1) && (const_int_operand (operands[1], VOIDmode)))
        {
	  return PENT_PAIR_PU;
        }
      else if ((cached_type == TYPE_ROTATE1) && (const1_operand (operands[1], VOIDmode)))
        {
	  return PENT_PAIR_PU;
        }
      else if ((cached_type == TYPE_CALL) && (constant_call_address_operand (operands[0], VOIDmode)))
        {
	  return PENT_PAIR_PV;
        }
      else if ((cached_type == TYPE_CALLV) && (constant_call_address_operand (operands[1], VOIDmode)))
        {
	  return PENT_PAIR_PV;
        }
      else
        {
	  return PENT_PAIR_NP;
        }

    case 564:  /* simple_return_indirect_internal */
    case 545:  /* *tablejump_1 */
    case 544:  /* *tablejump_1 */
    case 543:  /* *indirect_jump */
    case 542:  /* *indirect_jump */
    case 541:  /* jump */
    case 504:  /* *jcc_2 */
    case 503:  /* *jcc_1 */
      return PENT_PAIR_PV;

    case 278:  /* *addqi3_carry */
    case 279:  /* *subqi3_carry */
    case 280:  /* *addhi3_carry */
    case 281:  /* *subhi3_carry */
    case 282:  /* *addsi3_carry */
    case 283:  /* *subsi3_carry */
    case 284:  /* *adddi3_carry */
    case 285:  /* *subdi3_carry */
    case 770:  /* *x86_movsicc_0_m1 */
    case 771:  /* *x86_movsicc_0_m1_se */
    case 772:  /* *x86_movsicc_0_m1_neg */
      return PENT_PAIR_PU;

    case 624:  /* *tls_dynamic_gnu2_lea_32 */
    case 623:  /* *add_tp_di */
    case 622:  /* *add_tp_si */
    case 621:  /* *add_tp_x32_zext */
    case 620:  /* *add_tp_x32 */
    case 619:  /* *load_tp_di */
    case 618:  /* *load_tp_si */
    case 617:  /* *load_tp_x32_zext */
    case 616:  /* *load_tp_x32 */
    case 262:  /* *lea_general_4 */
    case 261:  /* *lea_general_4 */
    case 260:  /* *lea_general_3 */
    case 259:  /* *lea_general_2 */
    case 258:  /* *lea_general_1 */
    case 230:  /* *leasi */
      return PENT_PAIR_UV;

    default:
      return PENT_PAIR_NP;

    }
}

enum attr_pent_prefix
get_attr_pent_prefix (rtx insn ATTRIBUTE_UNUSED)
{
  switch (recog_memoized (insn))
    {
    case 1257:  /* sse2_loadhpd */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x1f))
        {
	  return PENT_PREFIX_TRUE;
        }
      else
        {
	  return PENT_PREFIX_FALSE;
        }

    case 1253:  /* sse2_storehpd */
      extract_constrain_insn_cached (insn);
      if ((((1 << which_alternative) & 0xf)) || ((((which_alternative == 0) && (! (
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX)))) || (which_alternative == 2)) || (which_alternative == 3)))
        {
	  return PENT_PREFIX_TRUE;
        }
      else
        {
	  return PENT_PREFIX_FALSE;
        }

    case 1258:  /* sse2_loadlpd */
    case 1224:  /* vec_setv4sf_0 */
    case 1223:  /* vec_setv4si_0 */
      extract_constrain_insn_cached (insn);
      if (!((1 << which_alternative) & 0x600))
        {
	  return PENT_PREFIX_TRUE;
        }
      else
        {
	  return PENT_PREFIX_FALSE;
        }

    case 938:  /* *vec_extractv2si_1 */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3f))
        {
	  return PENT_PREFIX_TRUE;
        }
      else
        {
	  return PENT_PREFIX_FALSE;
        }

    case 868:  /* *vec_extractv2sf_1 */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0xf))
        {
	  return PENT_PREFIX_TRUE;
        }
      else
        {
	  return PENT_PREFIX_FALSE;
        }

    case 840:  /* *movv2sf_internal */
      extract_constrain_insn_cached (insn);
      if (!((1 << which_alternative) & 0xc00))
        {
	  return PENT_PREFIX_TRUE;
        }
      else
        {
	  return PENT_PREFIX_FALSE;
        }

    case 839:  /* *movv1di_internal */
    case 838:  /* *movv2si_internal */
    case 837:  /* *movv4hi_internal */
    case 836:  /* *movv8qi_internal */
      extract_constrain_insn_cached (insn);
      if ((!((1 << which_alternative) & 0x6000)) || ((((which_alternative == 8) && (! (
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX)))) || (which_alternative == 6)) || ((((1 << which_alternative) & 0x30)) || ((which_alternative == 7) && (! (
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX)))))))
        {
	  return PENT_PREFIX_TRUE;
        }
      else
        {
	  return PENT_PREFIX_FALSE;
        }

    case 637:  /* *fop_df_1_sse */
    case 636:  /* *fop_sf_1_sse */
    case 634:  /* *fop_df_1_mixed */
    case 633:  /* *fop_sf_1_mixed */
    case 630:  /* *fop_df_comm_sse */
    case 629:  /* *fop_sf_comm_sse */
    case 628:  /* *fop_df_comm_mixed */
    case 627:  /* *fop_sf_comm_mixed */
      if (get_attr_unit (insn) == UNIT_SSE)
        {
	  return PENT_PREFIX_TRUE;
        }
      else
        {
	  return PENT_PREFIX_FALSE;
        }

    case 1255:  /* sse2_storelpd */
    case 238:  /* *addhi_1 */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x7))
        {
	  return PENT_PREFIX_TRUE;
        }
      else
        {
	  return PENT_PREFIX_FALSE;
        }

    case 136:  /* *truncdfsf_mixed */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 1)
        {
	  return PENT_PREFIX_TRUE;
        }
      else
        {
	  return PENT_PREFIX_FALSE;
        }

    case 778:  /* *movsfcc_1_387 */
    case 332:  /* *andsi_1 */
    case 302:  /* *mulsi3_1 */
    case 189:  /* *floatsidf2_mixed_with_temp */
    case 188:  /* *floatsisf2_mixed_with_temp */
    case 185:  /* *floatsidf2_vector_mixed_with_temp */
    case 184:  /* *floatsisf2_vector_mixed_with_temp */
    case 128:  /* *extendsfdf2_mixed */
      extract_constrain_insn_cached (insn);
      if (!((1 << which_alternative) & 0x3))
        {
	  return PENT_PREFIX_TRUE;
        }
      else
        {
	  return PENT_PREFIX_FALSE;
        }

    case 125:  /* extendhisi2 */
      if (get_attr_prefix_0f (insn) == 1)
        {
	  return PENT_PREFIX_TRUE;
        }
      else
        {
	  return PENT_PREFIX_FALSE;
        }

    case 117:  /* *zero_extendsidi2 */
      extract_constrain_insn_cached (insn);
      if (!((1 << which_alternative) & 0x7))
        {
	  return PENT_PREFIX_TRUE;
        }
      else
        {
	  return PENT_PREFIX_FALSE;
        }

    case 113:  /* *movsf_internal */
    case 112:  /* *movdf_internal */
      extract_constrain_insn_cached (insn);
      if ((!((1 << which_alternative) & 0x1f)) || ((get_attr_prefix_data16 (insn) == 1) || (get_attr_prefix_rep (insn) == 1)))
        {
	  return PENT_PREFIX_TRUE;
        }
      else
        {
	  return PENT_PREFIX_FALSE;
        }

    case 1228:  /* *sse4_1_extractps */
    case 431:  /* *ashlhi3_1 */
    case 105:  /* *pushtf */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return PENT_PREFIX_TRUE;
        }
      else
        {
	  return PENT_PREFIX_FALSE;
        }

    case 102:  /* *movqi_extzv_2 */
    case 100:  /* *movqi_extv_1 */
    case 80:  /* *movqi_internal */
      if (get_attr_type (insn) == TYPE_IMOVX)
        {
	  return PENT_PREFIX_TRUE;
        }
      else
        {
	  return PENT_PREFIX_FALSE;
        }

    case 79:  /* *movhi_internal */
      if ((get_attr_type (insn) == TYPE_IMOVX) || (get_attr_mode (insn) == MODE_HI))
        {
	  return PENT_PREFIX_TRUE;
        }
      else
        {
	  return PENT_PREFIX_FALSE;
        }

    case 78:  /* *movsi_internal */
      extract_constrain_insn_cached (insn);
      if ((((1 << which_alternative) & 0xffc)) || ((get_attr_prefix_data16 (insn) == 1) || ((((1 << which_alternative) & 0xf00)) && (! (
#line 659 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SSE2))))))
        {
	  return PENT_PREFIX_TRUE;
        }
      else
        {
	  return PENT_PREFIX_FALSE;
        }

    case 77:  /* *movdi_internal */
      extract_constrain_insn_cached (insn);
      if ((!((1 << which_alternative) & 0x3)) || (get_attr_prefix_data16 (insn) == 1))
        {
	  return PENT_PREFIX_TRUE;
        }
      else
        {
	  return PENT_PREFIX_FALSE;
        }

    case 608:  /* *bswaphi_lowpart_1 */
    case 197:  /* *floatdidf2_mixed_nointerunit */
    case 196:  /* *floatsidf2_mixed_nointerunit */
    case 195:  /* *floatdisf2_mixed_nointerunit */
    case 194:  /* *floatsisf2_mixed_nointerunit */
    case 193:  /* *floatdidf2_mixed_interunit */
    case 192:  /* *floatsidf2_mixed_interunit */
    case 191:  /* *floatdisf2_mixed_interunit */
    case 190:  /* *floatsisf2_mixed_interunit */
    case 187:  /* *floatsidf2_vector_mixed */
    case 186:  /* *floatsisf2_vector_mixed */
    case 133:  /* *truncdfsf_fast_mixed */
    case 52:  /* *cmpiudf_mixed */
    case 51:  /* *cmpiusf_mixed */
    case 50:  /* *cmpidf_mixed */
    case 49:  /* *cmpisf_mixed */
      extract_constrain_insn_cached (insn);
      if (which_alternative != 0)
        {
	  return PENT_PREFIX_TRUE;
        }
      else
        {
	  return PENT_PREFIX_FALSE;
        }

    case -1:
      if (GET_CODE (PATTERN (insn)) != ASM_INPUT
          && asm_noperands (PATTERN (insn)) < 0)
        fatal_insn_not_found (insn);
      if ((get_attr_prefix_0f (insn) == 1) || ((get_attr_prefix_data16 (insn) == 1) || (get_attr_prefix_rep (insn) == 1)))
        {
	  return PENT_PREFIX_TRUE;
        }
      else
        {
	  return PENT_PREFIX_FALSE;
        }

    case 1905:  /* atomic_xorsi */
    case 1904:  /* atomic_orsi */
    case 1903:  /* atomic_andsi */
    case 1902:  /* atomic_xorhi */
    case 1901:  /* atomic_orhi */
    case 1900:  /* atomic_andhi */
    case 1899:  /* atomic_xorqi */
    case 1898:  /* atomic_orqi */
    case 1897:  /* atomic_andqi */
    case 1896:  /* atomic_subsi */
    case 1895:  /* atomic_subhi */
    case 1894:  /* atomic_subqi */
    case 1893:  /* atomic_addsi */
    case 1892:  /* atomic_addhi */
    case 1891:  /* atomic_addqi */
    case 1890:  /* atomic_exchangesi */
    case 1889:  /* atomic_exchangehi */
    case 1888:  /* atomic_exchangeqi */
    case 1887:  /* *atomic_fetch_add_cmpsi */
    case 1886:  /* *atomic_fetch_add_cmphi */
    case 1885:  /* *atomic_fetch_add_cmpqi */
    case 1884:  /* atomic_fetch_addsi */
    case 1883:  /* atomic_fetch_addhi */
    case 1882:  /* atomic_fetch_addqi */
    case 1881:  /* atomic_compare_and_swapdi_doubleword */
    case 1880:  /* atomic_compare_and_swapsi_1 */
    case 1879:  /* atomic_compare_and_swaphi_1 */
    case 1878:  /* atomic_compare_and_swapqi_1 */
    case 1877:  /* storedi_via_fpu */
    case 1876:  /* loaddi_via_fpu */
    case 1875:  /* atomic_storedi_fpu */
    case 1874:  /* atomic_storesi_1 */
    case 1873:  /* atomic_storehi_1 */
    case 1872:  /* atomic_storeqi_1 */
    case 1871:  /* atomic_loaddi_fpu */
    case 1870:  /* mfence_nosse */
    case 1772:  /* avx_pd256_pd */
    case 1771:  /* avx_ps256_ps */
    case 1770:  /* avx_si256_si */
    case 1725:  /* *avx_vperm_broadcast_v4df */
    case 1724:  /* *avx_vperm_broadcast_v8sf */
    case 1463:  /* sse3_monitor */
    case 1462:  /* sse3_mwait */
    case 1436:  /* *sse2_storeq */
    case 1435:  /* *vec_ext_v4si_mem */
    case 1434:  /* sse2_stored */
    case 1240:  /* vec_extract_lo_v32qi */
    case 1238:  /* vec_extract_lo_v16hi */
    case 1235:  /* vec_extract_lo_v8sf */
    case 1234:  /* vec_extract_lo_v8si */
    case 1231:  /* vec_extract_lo_v4df */
    case 1230:  /* vec_extract_lo_v4di */
    case 1229:  /* *vec_extract_v4sf_mem */
    case 1227:  /* *vec_extractv4sf_0 */
    case 987:  /* *absnegv2df2 */
    case 986:  /* *absnegv4df2 */
    case 985:  /* *absnegv4sf2 */
    case 984:  /* *absnegv8sf2 */
    case 962:  /* movdi_to_sse */
    case 937:  /* *vec_extractv2si_0 */
    case 867:  /* *vec_extractv2sf_0 */
    case 835:  /* xtest_1 */
    case 834:  /* xabort */
    case 833:  /* xend */
    case 832:  /* xbegin_1 */
    case 831:  /* *pause */
    case 830:  /* rdseedsi_1 */
    case 829:  /* rdseedhi_1 */
    case 828:  /* rdrandsi_1 */
    case 827:  /* rdrandhi_1 */
    case 826:  /* *lwp_lwpinssi3_1 */
    case 825:  /* *lwp_lwpvalsi3_1 */
    case 824:  /* lwp_slwpcbdi */
    case 823:  /* lwp_slwpcbsi */
    case 822:  /* *lwp_llwpcbdi1 */
    case 821:  /* *lwp_llwpcbsi1 */
    case 820:  /* xrstor */
    case 819:  /* xsaveopt */
    case 818:  /* xsave */
    case 817:  /* fxrstor */
    case 816:  /* fxsave */
    case 815:  /* rdtscp */
    case 814:  /* rdtsc */
    case 813:  /* rdpmc */
    case 809:  /* stack_tls_protect_test_di */
    case 808:  /* stack_tls_protect_test_si */
    case 807:  /* stack_protect_test_di */
    case 806:  /* stack_protect_test_si */
    case 805:  /* stack_tls_protect_set_di */
    case 804:  /* stack_tls_protect_set_si */
    case 803:  /* stack_protect_set_di */
    case 802:  /* stack_protect_set_si */
    case 799:  /* trap */
    case 798:  /* probe_stack_rangedi */
    case 797:  /* probe_stack_rangesi */
    case 796:  /* adjust_stack_and_probedi */
    case 795:  /* adjust_stack_and_probesi */
    case 794:  /* allocate_stack_worker_probe_di */
    case 793:  /* allocate_stack_worker_probe_si */
    case 792:  /* pro_epilogue_adjust_stack_di_sub */
    case 791:  /* pro_epilogue_adjust_stack_si_sub */
    case 790:  /* pro_epilogue_adjust_stack_di_add */
    case 789:  /* pro_epilogue_adjust_stack_si_add */
    case 777:  /* *movdfcc_1 */
    case 776:  /* *movxfcc_1 */
    case 772:  /* *x86_movsicc_0_m1_neg */
    case 771:  /* *x86_movsicc_0_m1_se */
    case 770:  /* *x86_movsicc_0_m1 */
    case 759:  /* *strsetqi_1 */
    case 758:  /* *strsetqi_1 */
    case 755:  /* *strsetsi_1 */
    case 754:  /* *strsetsi_1 */
    case 749:  /* *strmovqi_1 */
    case 748:  /* *strmovqi_1 */
    case 745:  /* *strmovsi_1 */
    case 744:  /* *strmovsi_1 */
    case 743:  /* cld */
    case 741:  /* fxamdf2_i387_with_temp */
    case 740:  /* fxamsf2_i387_with_temp */
    case 739:  /* fxamxf2_i387 */
    case 738:  /* fxamdf2_i387 */
    case 737:  /* fxamsf2_i387 */
    case 736:  /* fistsi2_ceil_with_temp */
    case 735:  /* fistsi2_floor_with_temp */
    case 732:  /* fistsi2_ceil */
    case 731:  /* fistsi2_floor */
    case 728:  /* fistdi2_ceil_with_temp */
    case 727:  /* fistdi2_floor_with_temp */
    case 726:  /* fistdi2_ceil */
    case 725:  /* fistdi2_floor */
    case 724:  /* *fistdi2_ceil_1 */
    case 723:  /* *fistdi2_floor_1 */
    case 722:  /* *fistsi2_ceil_1 */
    case 721:  /* *fistsi2_floor_1 */
    case 718:  /* frndintxf2_mask_pm_i387 */
    case 717:  /* frndintxf2_mask_pm */
    case 716:  /* frndintxf2_trunc_i387 */
    case 715:  /* frndintxf2_ceil_i387 */
    case 714:  /* frndintxf2_floor_i387 */
    case 713:  /* frndintxf2_trunc */
    case 712:  /* frndintxf2_ceil */
    case 711:  /* frndintxf2_floor */
    case 710:  /* fistsi2_with_temp */
    case 708:  /* fistsi2 */
    case 706:  /* *fistsi2_1 */
    case 704:  /* fistdi2_with_temp */
    case 703:  /* fistdi2 */
    case 702:  /* *fistdi2_1 */
    case 701:  /* rintxf2 */
    case 698:  /* *fscalexf4_i387 */
    case 697:  /* *f2xm1xf2_i387 */
    case 696:  /* fxtract_extenddfxf3_i387 */
    case 695:  /* fxtract_extendsfxf3_i387 */
    case 694:  /* fxtractxf3_i387 */
    case 693:  /* fyl2xp1_extenddfxf3_i387 */
    case 692:  /* fyl2xp1_extendsfxf3_i387 */
    case 691:  /* fyl2xp1xf3_i387 */
    case 690:  /* fyl2x_extenddfxf3_i387 */
    case 689:  /* fyl2x_extendsfxf3_i387 */
    case 688:  /* fyl2xxf3_i387 */
    case 687:  /* fpatan_extenddfxf3_i387 */
    case 686:  /* fpatan_extendsfxf3_i387 */
    case 685:  /* *fpatanxf3_i387 */
    case 684:  /* fptan_extenddfxf4_i387 */
    case 683:  /* fptan_extendsfxf4_i387 */
    case 682:  /* fptanxf4_i387 */
    case 681:  /* sincos_extenddfxf3_i387 */
    case 680:  /* sincos_extendsfxf3_i387 */
    case 679:  /* sincosxf3 */
    case 678:  /* *cos_extenddfxf2_i387 */
    case 677:  /* *sin_extenddfxf2_i387 */
    case 676:  /* *cos_extendsfxf2_i387 */
    case 675:  /* *sin_extendsfxf2_i387 */
    case 674:  /* *cosxf2_i387 */
    case 673:  /* *sinxf2_i387 */
    case 672:  /* fprem1xf4_i387 */
    case 671:  /* fpremxf4_i387 */
    case 667:  /* sqrt_extenddfxf2_i387 */
    case 666:  /* sqrt_extendsfxf2_i387 */
    case 665:  /* sqrtxf2 */
    case 664:  /* truncxfdf2_i387_noop_unspec */
    case 663:  /* truncxfsf2_i387_noop_unspec */
    case 662:  /* *fop_xf_6_i387 */
    case 661:  /* *fop_xf_6_i387 */
    case 660:  /* *fop_xf_5_i387 */
    case 659:  /* *fop_xf_5_i387 */
    case 658:  /* *fop_xf_4_i387 */
    case 657:  /* *fop_xf_4_i387 */
    case 656:  /* *fop_xf_3_i387 */
    case 654:  /* *fop_xf_2_i387 */
    case 652:  /* *fop_xf_1_i387 */
    case 651:  /* *fop_xf_comm_i387 */
    case 650:  /* *fop_df_6_i387 */
    case 649:  /* *fop_df_5_i387 */
    case 648:  /* *fop_df_4_i387 */
    case 647:  /* *fop_df_3_i387 */
    case 646:  /* *fop_sf_3_i387 */
    case 643:  /* *fop_df_2_i387 */
    case 642:  /* *fop_sf_2_i387 */
    case 639:  /* *fop_df_1_i387 */
    case 638:  /* *fop_sf_1_i387 */
    case 632:  /* *fop_df_comm_i387 */
    case 631:  /* *fop_sf_comm_i387 */
    case 626:  /* *tls_dynamic_gnu2_combine_32 */
    case 625:  /* *tls_dynamic_gnu2_call_32 */
    case 624:  /* *tls_dynamic_gnu2_lea_32 */
    case 623:  /* *add_tp_di */
    case 622:  /* *add_tp_si */
    case 621:  /* *add_tp_x32_zext */
    case 620:  /* *add_tp_x32 */
    case 619:  /* *load_tp_di */
    case 618:  /* *load_tp_si */
    case 617:  /* *load_tp_x32_zext */
    case 616:  /* *load_tp_x32 */
    case 615:  /* *tls_local_dynamic_32_once */
    case 614:  /* *tls_local_dynamic_base_32_gnu */
    case 613:  /* *tls_global_dynamic_32_gnu */
    case 611:  /* paritysi2_cmp */
    case 610:  /* paritydi2_cmp */
    case 574:  /* ffssi2_no_cmove */
    case 573:  /* split_stack_return */
    case 572:  /* leave */
    case 571:  /* eh_return_internal */
    case 570:  /* set_got_offset_rex64 */
    case 569:  /* set_got_labelled */
    case 568:  /* set_got */
    case 567:  /* pad */
    case 566:  /* nops */
    case 565:  /* nop */
    case 564:  /* simple_return_indirect_internal */
    case 563:  /* simple_return_pop_internal */
    case 561:  /* simple_return_internal */
    case 560:  /* prologue_use */
    case 559:  /* *memory_blockage */
    case 558:  /* blockage */
    case 557:  /* *sibcall_value_pop */
    case 556:  /* *call_value_pop */
    case 555:  /* *sibcall_value */
    case 554:  /* *sibcall_value */
    case 553:  /* *call_value */
    case 552:  /* *call_value */
    case 551:  /* *sibcall_pop */
    case 550:  /* *call_pop */
    case 549:  /* *sibcall */
    case 548:  /* *sibcall */
    case 547:  /* *call */
    case 546:  /* *call */
    case 545:  /* *tablejump_1 */
    case 544:  /* *tablejump_1 */
    case 543:  /* *indirect_jump */
    case 542:  /* *indirect_jump */
    case 541:  /* jump */
    case 540:  /* *jccxf_si_r_i387 */
    case 539:  /* *jccdf_si_r_i387 */
    case 538:  /* *jccsf_si_r_i387 */
    case 537:  /* *jccxf_hi_r_i387 */
    case 536:  /* *jccdf_hi_r_i387 */
    case 535:  /* *jccsf_hi_r_i387 */
    case 534:  /* *jccxf_si_i387 */
    case 533:  /* *jccdf_si_i387 */
    case 532:  /* *jccsf_si_i387 */
    case 531:  /* *jccxf_hi_i387 */
    case 530:  /* *jccdf_hi_i387 */
    case 529:  /* *jccsf_hi_i387 */
    case 528:  /* *jccuxf_r_i387 */
    case 527:  /* *jccudf_r_i387 */
    case 526:  /* *jccusf_r_i387 */
    case 525:  /* *jccuxf_i387 */
    case 524:  /* *jccudf_i387 */
    case 523:  /* *jccusf_i387 */
    case 522:  /* *jccdf_r_i387 */
    case 521:  /* *jccsf_r_i387 */
    case 520:  /* *jccdf_i387 */
    case 519:  /* *jccsf_i387 */
    case 518:  /* *jccxf_r_i387 */
    case 517:  /* *jccxf_i387 */
    case 516:  /* *jccxf_0_r_i387 */
    case 515:  /* *jccdf_0_r_i387 */
    case 514:  /* *jccsf_0_r_i387 */
    case 513:  /* *jccxf_0_i387 */
    case 512:  /* *jccdf_0_i387 */
    case 511:  /* *jccsf_0_i387 */
    case 510:  /* *jcc_btsi_mask_1 */
    case 509:  /* *jcc_btsi_1 */
    case 508:  /* *jcc_btdi_mask */
    case 507:  /* *jcc_btsi_mask */
    case 506:  /* *jcc_btdi */
    case 505:  /* *jcc_btsi */
    case 504:  /* *jcc_2 */
    case 503:  /* *jcc_1 */
    case 498:  /* *setcc_si_1_movzbl */
    case 497:  /* *setcc_si_1_and */
    case 494:  /* *rotrqi3_1_slp */
    case 493:  /* *rotlqi3_1_slp */
    case 490:  /* *rotrqi3_1 */
    case 489:  /* *rotlqi3_1 */
    case 488:  /* *rotrdi3_1 */
    case 487:  /* *rotldi3_1 */
    case 486:  /* *rotrsi3_1 */
    case 485:  /* *rotlsi3_1 */
    case 484:  /* *bmi2_rorxsi3_1 */
    case 483:  /* ix86_rotrdi3_doubleword */
    case 482:  /* ix86_rotldi3_doubleword */
    case 481:  /* *rotrdi3_mask */
    case 480:  /* *rotldi3_mask */
    case 479:  /* *rotrsi3_mask */
    case 478:  /* *rotlsi3_mask */
    case 477:  /* *ashrdi3_cconly */
    case 476:  /* *lshrdi3_cconly */
    case 475:  /* *ashrsi3_cconly */
    case 474:  /* *lshrsi3_cconly */
    case 471:  /* *ashrqi3_cconly */
    case 470:  /* *lshrqi3_cconly */
    case 469:  /* *ashrdi3_cmp */
    case 468:  /* *lshrdi3_cmp */
    case 467:  /* *ashrsi3_cmp */
    case 466:  /* *lshrsi3_cmp */
    case 463:  /* *ashrqi3_cmp */
    case 462:  /* *lshrqi3_cmp */
    case 461:  /* *ashrqi3_1_slp */
    case 460:  /* *lshrqi3_1_slp */
    case 457:  /* *ashrqi3_1 */
    case 456:  /* *lshrqi3_1 */
    case 455:  /* *ashrdi3_1 */
    case 454:  /* *lshrdi3_1 */
    case 453:  /* *ashrsi3_1 */
    case 452:  /* *lshrsi3_1 */
    case 451:  /* *bmi2_ashrsi3_1 */
    case 450:  /* *bmi2_lshrsi3_1 */
    case 449:  /* ashrsi3_cvt */
    case 447:  /* *ashrdi3_doubleword */
    case 446:  /* *lshrdi3_doubleword */
    case 445:  /* *ashrdi3_mask */
    case 444:  /* *lshrdi3_mask */
    case 443:  /* *ashrsi3_mask */
    case 442:  /* *lshrsi3_mask */
    case 441:  /* *ashldi3_cconly */
    case 440:  /* *ashlsi3_cconly */
    case 438:  /* *ashlqi3_cconly */
    case 437:  /* *ashldi3_cmp */
    case 436:  /* *ashlsi3_cmp */
    case 434:  /* *ashlqi3_cmp */
    case 433:  /* *ashlqi3_1_slp */
    case 432:  /* *ashlqi3_1 */
    case 430:  /* *ashldi3_1 */
    case 429:  /* *ashlsi3_1 */
    case 428:  /* *bmi2_ashlsi3_1 */
    case 427:  /* *ashldi3_mask */
    case 426:  /* *ashlsi3_mask */
    case 424:  /* *ashldi3_doubleword */
    case 423:  /* *one_cmpldi2_2 */
    case 422:  /* *one_cmplsi2_2 */
    case 420:  /* *one_cmplqi2_2 */
    case 419:  /* *one_cmplqi2_1 */
    case 418:  /* *one_cmpldi2_1 */
    case 417:  /* *one_cmplsi2_1 */
    case 415:  /* copysigntf3_var */
    case 414:  /* copysigndf3_var */
    case 413:  /* copysignsf3_var */
    case 412:  /* copysigntf3_const */
    case 411:  /* copysigndf3_const */
    case 410:  /* copysignsf3_const */
    case 409:  /* *negextenddfxf2 */
    case 408:  /* *absextenddfxf2 */
    case 407:  /* *negextendsfxf2 */
    case 406:  /* *absextendsfxf2 */
    case 405:  /* *negextendsfdf2 */
    case 404:  /* *absextendsfdf2 */
    case 403:  /* *negxf2_1 */
    case 402:  /* *absxf2_1 */
    case 401:  /* *negdf2_1 */
    case 400:  /* *absdf2_1 */
    case 399:  /* *negsf2_1 */
    case 398:  /* *abssf2_1 */
    case 397:  /* *absnegtf2_sse */
    case 396:  /* *absnegxf2_i387 */
    case 395:  /* *absnegdf2_i387 */
    case 394:  /* *absnegsf2_i387 */
    case 393:  /* *absnegdf2_sse */
    case 392:  /* *absnegsf2_sse */
    case 391:  /* *absnegdf2_mixed */
    case 390:  /* *absnegsf2_mixed */
    case 389:  /* *negdi2_cmpz */
    case 388:  /* *negsi2_cmpz */
    case 386:  /* *negqi2_cmpz */
    case 385:  /* *negdi2_1 */
    case 384:  /* *negsi2_1 */
    case 382:  /* *negqi2_1 */
    case 381:  /* *negti2_doubleword */
    case 380:  /* *negdi2_doubleword */
    case 379:  /* *xorqi_cc_ext_1 */
    case 378:  /* *xorqi_ext_2 */
    case 377:  /* *iorqi_ext_2 */
    case 376:  /* *xorqi_ext_1 */
    case 375:  /* *iorqi_ext_1 */
    case 374:  /* *xorqi_ext_0 */
    case 373:  /* *iorqi_ext_0 */
    case 372:  /* *xordi_3 */
    case 371:  /* *iordi_3 */
    case 370:  /* *xorsi_3 */
    case 369:  /* *iorsi_3 */
    case 366:  /* *xorqi_3 */
    case 365:  /* *iorqi_3 */
    case 364:  /* *xorqi_2_slp */
    case 363:  /* *iorqi_2_slp */
    case 362:  /* *xordi_2 */
    case 361:  /* *iordi_2 */
    case 360:  /* *xorsi_2 */
    case 359:  /* *iorsi_2 */
    case 356:  /* *xorqi_2 */
    case 355:  /* *iorqi_2 */
    case 354:  /* *xorqi_1_slp */
    case 353:  /* *iorqi_1_slp */
    case 352:  /* *xorqi_1 */
    case 351:  /* *iorqi_1 */
    case 350:  /* *xordi_1 */
    case 349:  /* *iordi_1 */
    case 348:  /* *xorsi_1 */
    case 347:  /* *iorsi_1 */
    case 344:  /* *andqi_ext_2 */
    case 343:  /* *andqi_ext_1 */
    case 342:  /* *andqi_ext_0_cc */
    case 341:  /* andqi_ext_0 */
    case 340:  /* *andqi_2_slp */
    case 339:  /* *andsi_2 */
    case 337:  /* *andqi_2 */
    case 336:  /* *andqi_2_maybe_si */
    case 335:  /* *andqi_1_slp */
    case 334:  /* *andqi_1 */
    case 331:  /* *testqi_ext_3 */
    case 330:  /* *testqi_ext_2 */
    case 329:  /* *testqi_ext_1 */
    case 328:  /* *testqi_ext_0 */
    case 327:  /* *testsi_1 */
    case 325:  /* *testqi_1 */
    case 324:  /* *testqi_1_maybe_si */
    case 323:  /* udivmodhiqi3 */
    case 322:  /* *udivmodsi4_noext */
    case 320:  /* *udivmodsi4 */
    case 318:  /* udivmodsi4_1 */
    case 317:  /* divmodhiqi3 */
    case 316:  /* *divmodsi4_noext */
    case 314:  /* *divmodsi4 */
    case 312:  /* divmodsi4_1 */
    case 311:  /* *umulsi3_highpart_1 */
    case 310:  /* *smulsi3_highpart_1 */
    case 309:  /* *umulqihi3_1 */
    case 308:  /* *mulqihi3_1 */
    case 307:  /* *mulsidi3_1 */
    case 306:  /* *umulsidi3_1 */
    case 305:  /* *bmi2_umulsidi3_1 */
    case 304:  /* *mulqi3_1 */
    case 301:  /* *subdi3_cc_overflow */
    case 300:  /* *adddi3_cc_overflow */
    case 299:  /* *subsi3_cc_overflow */
    case 298:  /* *addsi3_cc_overflow */
    case 295:  /* *subqi3_cc_overflow */
    case 294:  /* *addqi3_cc_overflow */
    case 293:  /* *subsi3_cconly_overflow */
    case 291:  /* *subqi3_cconly_overflow */
    case 290:  /* *addsi3_cconly_overflow */
    case 288:  /* *addqi3_cconly_overflow */
    case 287:  /* adcxdi3 */
    case 286:  /* adcxsi3 */
    case 285:  /* *subdi3_carry */
    case 284:  /* *adddi3_carry */
    case 283:  /* *subsi3_carry */
    case 282:  /* *addsi3_carry */
    case 279:  /* *subqi3_carry */
    case 278:  /* *addqi3_carry */
    case 277:  /* *subdi_3 */
    case 276:  /* *subsi_3 */
    case 274:  /* *subqi_3 */
    case 273:  /* *subdi_2 */
    case 272:  /* *subsi_2 */
    case 270:  /* *subqi_2 */
    case 269:  /* *subqi_1_slp */
    case 268:  /* *subdi_1 */
    case 267:  /* *subsi_1 */
    case 265:  /* *subqi_1 */
    case 264:  /* *subti3_doubleword */
    case 263:  /* *subdi3_doubleword */
    case 262:  /* *lea_general_4 */
    case 261:  /* *lea_general_4 */
    case 260:  /* *lea_general_3 */
    case 259:  /* *lea_general_2 */
    case 258:  /* *lea_general_1 */
    case 257:  /* *addqi_ext_2 */
    case 256:  /* addqi_ext_1 */
    case 255:  /* *adddi_5 */
    case 254:  /* *addsi_5 */
    case 252:  /* *addqi_5 */
    case 251:  /* *addsi_4 */
    case 249:  /* *addqi_4 */
    case 248:  /* *adddi_3 */
    case 247:  /* *addsi_3 */
    case 245:  /* *addqi_3 */
    case 244:  /* *adddi_2 */
    case 243:  /* *addsi_2 */
    case 241:  /* *addqi_2 */
    case 240:  /* *addqi_1_slp */
    case 239:  /* *addqi_1 */
    case 237:  /* *adddi_1 */
    case 236:  /* *addsi_1 */
    case 235:  /* addqi3_cc */
    case 234:  /* *adddi3_cc */
    case 233:  /* *addsi3_cc */
    case 232:  /* *addti3_doubleword */
    case 231:  /* *adddi3_doubleword */
    case 230:  /* *leasi */
    case 229:  /* *floatunssixf2_1 */
    case 228:  /* *floatunssidf2_1 */
    case 227:  /* *floatunssisf2_1 */
    case 226:  /* floatdixf2_i387_with_xmm */
    case 225:  /* floatdidf2_i387_with_xmm */
    case 224:  /* floatdisf2_i387_with_xmm */
    case 223:  /* *floatdixf2_i387 */
    case 222:  /* *floatdidf2_i387 */
    case 221:  /* *floatdisf2_i387 */
    case 220:  /* *floatsixf2_i387 */
    case 219:  /* *floatsidf2_i387 */
    case 218:  /* *floatsisf2_i387 */
    case 217:  /* *floatdixf2_i387_with_temp */
    case 216:  /* *floatdidf2_i387_with_temp */
    case 215:  /* *floatdisf2_i387_with_temp */
    case 214:  /* *floatsixf2_i387_with_temp */
    case 213:  /* *floatsidf2_i387_with_temp */
    case 212:  /* *floatsisf2_i387_with_temp */
    case 183:  /* *floatdixf2_1 */
    case 182:  /* *floatdidf2_1 */
    case 181:  /* *floatdisf2_1 */
    case 180:  /* *floatsixf2_1 */
    case 179:  /* *floatsidf2_1 */
    case 178:  /* *floatsisf2_1 */
    case 177:  /* *floathixf2_i387 */
    case 176:  /* *floathidf2_i387 */
    case 175:  /* *floathisf2_i387 */
    case 174:  /* *floathixf2_i387_with_temp */
    case 173:  /* *floathidf2_i387_with_temp */
    case 172:  /* *floathisf2_i387_with_temp */
    case 171:  /* *floathixf2_1 */
    case 170:  /* *floathidf2_1 */
    case 169:  /* *floathisf2_1 */
    case 166:  /* fix_truncsi_i387_with_temp */
    case 164:  /* fix_truncsi_i387 */
    case 162:  /* fix_truncdi_i387_with_temp */
    case 161:  /* fix_truncdi_i387 */
    case 160:  /* *fix_truncdi_i387_1 */
    case 159:  /* *fix_truncsi_i387_1 */
    case 157:  /* fix_truncdi_i387_fisttp_with_temp */
    case 156:  /* fix_truncsi_i387_fisttp_with_temp */
    case 154:  /* fix_truncdi_i387_fisttp */
    case 153:  /* fix_truncsi_i387_fisttp */
    case 151:  /* fix_truncdi_fisttp_i387_1 */
    case 150:  /* fix_truncsi_fisttp_i387_1 */
    case 146:  /* *fixuns_truncdf_1 */
    case 145:  /* *fixuns_truncsf_1 */
    case 144:  /* *truncxfdf2_i387 */
    case 143:  /* *truncxfsf2_i387 */
    case 142:  /* truncxfdf2_i387_noop */
    case 141:  /* truncxfsf2_i387_noop */
    case 140:  /* *truncxfdf2_mixed */
    case 139:  /* *truncxfsf2_mixed */
    case 138:  /* *truncdfsf2_i387_1 */
    case 137:  /* *truncdfsf_i387 */
    case 135:  /* *truncdfsf_fast_i387 */
    case 132:  /* *extenddfxf2_i387 */
    case 131:  /* *extendsfxf2_i387 */
    case 130:  /* *extendsfdf2_i387 */
    case 124:  /* extendsidi2_1 */
    case 122:  /* zero_extendqihi2_and */
    case 119:  /* zero_extendhisi2_and */
    case 118:  /* zero_extendqisi2_and */
    case 116:  /* *swapdf */
    case 115:  /* *swapsf */
    case 114:  /* swapxf */
    case 111:  /* *movxf_internal */
    case 109:  /* *pushsf */
    case 108:  /* *pushdf */
    case 107:  /* *pushxf_nointeger */
    case 106:  /* *pushxf */
    case 104:  /* *movqi_insv_2 */
    case 103:  /* *movsi_insv_1 */
    case 96:  /* *movstrictqi_xor */
    case 94:  /* *movstrictqi_1 */
    case 92:  /* *swapqi_2 */
    case 91:  /* *swaphi_1 */
    case 90:  /* *swapqi_1 */
    case 89:  /* swapsi */
    case 88:  /* *movabsdi_2 */
    case 87:  /* *movabssi_2 */
    case 85:  /* *movabsqi_2 */
    case 84:  /* *movabsdi_1 */
    case 83:  /* *movabssi_1 */
    case 81:  /* *movabsqi_1 */
    case 74:  /* *movsi_or */
    case 73:  /* *movsi_xor */
    case 72:  /* *popdi1_epilogue */
    case 71:  /* *popsi1_epilogue */
    case 70:  /* *popdi1 */
    case 69:  /* *popsi1 */
    case 68:  /* *pushdi2_prologue */
    case 67:  /* *pushsi2_prologue */
    case 66:  /* *pushhi2 */
    case 65:  /* *pushqi2 */
    case 64:  /* *pushsi2 */
    case 63:  /* *pushdi2 */
    case 62:  /* *cmpiuxf_i387 */
    case 61:  /* *cmpiudf_i387 */
    case 60:  /* *cmpiusf_i387 */
    case 59:  /* *cmpixf_i387 */
    case 58:  /* *cmpidf_i387 */
    case 57:  /* *cmpisf_i387 */
    case 48:  /* x86_sahf_1 */
    case 47:  /* x86_fnstsw_1 */
    case 46:  /* *cmpxf_si_cc_i387 */
    case 45:  /* *cmpdf_si_cc_i387 */
    case 44:  /* *cmpsf_si_cc_i387 */
    case 40:  /* *cmpxf_si_i387 */
    case 39:  /* *cmpdf_si_i387 */
    case 38:  /* *cmpsf_si_i387 */
    case 34:  /* *cmpuxf_cc_i387 */
    case 33:  /* *cmpudf_cc_i387 */
    case 32:  /* *cmpusf_cc_i387 */
    case 31:  /* *cmpuxf_i387 */
    case 30:  /* *cmpudf_i387 */
    case 29:  /* *cmpusf_i387 */
    case 28:  /* *cmpdf_cc_i387 */
    case 27:  /* *cmpsf_cc_i387 */
    case 26:  /* *cmpdf_i387 */
    case 25:  /* *cmpsf_i387 */
    case 24:  /* *cmpxf_cc_i387 */
    case 23:  /* *cmpxf_i387 */
    case 22:  /* *cmpxf_0_cc_i387 */
    case 21:  /* *cmpdf_0_cc_i387 */
    case 20:  /* *cmpsf_0_cc_i387 */
    case 19:  /* *cmpxf_0_i387 */
    case 18:  /* *cmpdf_0_i387 */
    case 17:  /* *cmpsf_0_i387 */
    case 16:  /* *cmpqi_ext_4 */
    case 15:  /* *cmpqi_ext_3_insn */
    case 14:  /* *cmpqi_ext_2 */
    case 13:  /* *cmpqi_ext_1 */
    case 12:  /* *cmpdi_minus_1 */
    case 11:  /* *cmpsi_minus_1 */
    case 9:  /* *cmpqi_minus_1 */
    case 8:  /* *cmpdi_1 */
    case 7:  /* *cmpsi_1 */
    case 5:  /* *cmpqi_1 */
    case 4:  /* *cmpdi_ccno_1 */
    case 3:  /* *cmpsi_ccno_1 */
    case 1:  /* *cmpqi_ccno_1 */
      return PENT_PREFIX_FALSE;

    default:
      return PENT_PREFIX_TRUE;

    }
}

int
get_attr_prefix_vex_w (rtx insn ATTRIBUTE_UNUSED)
{
  switch (recog_memoized (insn))
    {
    case -1:
      if (GET_CODE (PATTERN (insn)) != ASM_INPUT
          && asm_noperands (PATTERN (insn)) < 0)
        fatal_insn_not_found (insn);
    default:
      return 0;

    }
}

enum attr_prefix
get_attr_prefix (rtx insn ATTRIBUTE_UNUSED)
{
  enum attr_mode cached_mode ATTRIBUTE_UNUSED;

  switch (recog_memoized (insn))
    {
    case 1444:  /* vec_concatv2di */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return PREFIX_MAYBE_VEX;
        }
      else if (((1 << which_alternative) & 0x6))
        {
	  return PREFIX_ORIG;
        }
      else if (which_alternative == 3)
        {
	  return PREFIX_VEX;
        }
      else if (((1 << which_alternative) & 0x30))
        {
	  return PREFIX_ORIG;
        }
      else
        {
	  return PREFIX_VEX;
        }

    case 1443:  /* *vec_concatv4si */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return PREFIX_ORIG;
        }
      else if (which_alternative == 1)
        {
	  return PREFIX_VEX;
        }
      else if (((1 << which_alternative) & 0xc))
        {
	  return PREFIX_ORIG;
        }
      else
        {
	  return PREFIX_VEX;
        }

    case 1437:  /* *vec_extractv2di_1 */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return PREFIX_MAYBE_VEX;
        }
      else if (which_alternative == 1)
        {
	  return PREFIX_ORIG;
        }
      else if (which_alternative == 2)
        {
	  return PREFIX_VEX;
        }
      else if (which_alternative == 3)
        {
	  return PREFIX_MAYBE_VEX;
        }
      else
        {
	  return PREFIX_ORIG;
        }

    case 1433:  /* sse2_loadld */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return PREFIX_MAYBE_VEX;
        }
      else if (((1 << which_alternative) & 0xc))
        {
	  return PREFIX_ORIG;
        }
      else
        {
	  return PREFIX_VEX;
        }

    case 1261:  /* *vec_concatv2df */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return PREFIX_ORIG;
        }
      else if (which_alternative == 1)
        {
	  return PREFIX_VEX;
        }
      else if (which_alternative == 2)
        {
	  return PREFIX_MAYBE_VEX;
        }
      else if (which_alternative == 3)
        {
	  return PREFIX_ORIG;
        }
      else if (which_alternative == 4)
        {
	  return PREFIX_VEX;
        }
      else if (which_alternative == 5)
        {
	  return PREFIX_MAYBE_VEX;
        }
      else
        {
	  return PREFIX_ORIG;
        }

    case 1259:  /* sse2_movsd */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return PREFIX_ORIG;
        }
      else if (which_alternative == 1)
        {
	  return PREFIX_VEX;
        }
      else if (which_alternative == 2)
        {
	  return PREFIX_ORIG;
        }
      else if (which_alternative == 3)
        {
	  return PREFIX_VEX;
        }
      else if (which_alternative == 4)
        {
	  return PREFIX_MAYBE_VEX;
        }
      else if (((1 << which_alternative) & 0x60))
        {
	  return PREFIX_ORIG;
        }
      else if (which_alternative == 7)
        {
	  return PREFIX_VEX;
        }
      else
        {
	  return PREFIX_MAYBE_VEX;
        }

    case 1258:  /* sse2_loadlpd */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return PREFIX_MAYBE_VEX;
        }
      else if (which_alternative == 1)
        {
	  return PREFIX_ORIG;
        }
      else if (which_alternative == 2)
        {
	  return PREFIX_VEX;
        }
      else if (which_alternative == 3)
        {
	  return PREFIX_ORIG;
        }
      else if (which_alternative == 4)
        {
	  return PREFIX_VEX;
        }
      else if (((1 << which_alternative) & 0x60))
        {
	  return PREFIX_ORIG;
        }
      else if (which_alternative == 7)
        {
	  return PREFIX_VEX;
        }
      else
        {
	  return PREFIX_ORIG;
        }

    case 1257:  /* sse2_loadhpd */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return PREFIX_ORIG;
        }
      else if (which_alternative == 1)
        {
	  return PREFIX_VEX;
        }
      else if (which_alternative == 2)
        {
	  return PREFIX_ORIG;
        }
      else if (which_alternative == 3)
        {
	  return PREFIX_VEX;
        }
      else
        {
	  return PREFIX_ORIG;
        }

    case 1253:  /* sse2_storehpd */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return PREFIX_MAYBE_VEX;
        }
      else if (which_alternative == 1)
        {
	  return PREFIX_ORIG;
        }
      else if (which_alternative == 2)
        {
	  return PREFIX_VEX;
        }
      else
        {
	  return PREFIX_ORIG;
        }

    case 1228:  /* *sse4_1_extractps */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return PREFIX_MAYBE_VEX;
        }
      else
        {
	  return PREFIX_ORIG;
        }

    case 1224:  /* vec_setv4sf_0 */
    case 1223:  /* vec_setv4si_0 */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x7))
        {
	  return PREFIX_MAYBE_VEX;
        }
      else if (((1 << which_alternative) & 0x18))
        {
	  return PREFIX_ORIG;
        }
      else if (which_alternative == 5)
        {
	  return PREFIX_VEX;
        }
      else if (which_alternative == 6)
        {
	  return PREFIX_ORIG;
        }
      else if (which_alternative == 7)
        {
	  return PREFIX_VEX;
        }
      else
        {
	  return PREFIX_ORIG;
        }

    case 1440:  /* *vec_concatv2si_sse4_1 */
    case 1220:  /* *vec_concatv2sf_sse4_1 */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return PREFIX_ORIG;
        }
      else if (which_alternative == 1)
        {
	  return PREFIX_VEX;
        }
      else if (which_alternative == 2)
        {
	  return PREFIX_ORIG;
        }
      else if (which_alternative == 3)
        {
	  return PREFIX_VEX;
        }
      else if (which_alternative == 4)
        {
	  return PREFIX_MAYBE_VEX;
        }
      else
        {
	  return PREFIX_ORIG;
        }

    case 1219:  /* vec_dupv4sf */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return PREFIX_VEX;
        }
      else
        {
	  return PREFIX_ORIG;
        }

    case 634:  /* *fop_df_1_mixed */
    case 633:  /* *fop_sf_1_mixed */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x7))
        {
	  return PREFIX_ORIG;
        }
      else
        {
	  return PREFIX_VEX;
        }

    case 1421:  /* sse4_1_pinsrq */
    case 1420:  /* sse4_1_pinsrd */
    case 1419:  /* sse2_pinsrw */
    case 1418:  /* sse4_1_pinsrb */
    case 1192:  /* sse2_cvtss2sd */
    case 1191:  /* sse2_cvtsd2ss */
    case 1178:  /* sse2_cvtsi2sd */
    case 1165:  /* sse_cvtsi2ss */
    case 628:  /* *fop_df_comm_mixed */
    case 627:  /* *fop_sf_comm_mixed */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return PREFIX_ORIG;
        }
      else
        {
	  return PREFIX_VEX;
        }

    case 136:  /* *truncdfsf_mixed */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return PREFIX_ORIG;
        }
      else if (which_alternative == 1)
        {
	  return PREFIX_MAYBE_VEX;
        }
      else
        {
	  return PREFIX_ORIG;
        }

    case 128:  /* *extendsfdf2_mixed */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return PREFIX_ORIG;
        }
      else
        {
	  return PREFIX_MAYBE_VEX;
        }

    case 77:  /* *movdi_internal */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x1e0))
        {
	  return PREFIX_MAYBE_VEX;
        }
      else
        {
	  return PREFIX_ORIG;
        }

    case 78:  /* *movsi_internal */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3f))
        {
	  return PREFIX_ORIG;
        }
      else
        {
	  return PREFIX_MAYBE_VEX;
        }

    case 117:  /* *zero_extendsidi2 */
    case 112:  /* *movdf_internal */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x1f))
        {
	  return PREFIX_ORIG;
        }
      else
        {
	  return PREFIX_MAYBE_VEX;
        }

    case 113:  /* *movsf_internal */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x31e0))
        {
	  return PREFIX_MAYBE_VEX;
        }
      else
        {
	  return PREFIX_ORIG;
        }

    case 306:  /* *umulsidi3_1 */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return PREFIX_VEX;
        }
      else
        {
	  return PREFIX_ORIG;
        }

    case 836:  /* *movv8qi_internal */
    case 837:  /* *movv4hi_internal */
    case 838:  /* *movv2si_internal */
    case 839:  /* *movv1di_internal */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x1c0))
        {
	  return PREFIX_MAYBE_VEX;
        }
      else
        {
	  return PREFIX_ORIG;
        }

    case 840:  /* *movv2sf_internal */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3c0))
        {
	  return PREFIX_MAYBE_VEX;
        }
      else
        {
	  return PREFIX_ORIG;
        }

    case 1198:  /* sse_movhlps */
    case 1199:  /* sse_movlhps */
    case 1212:  /* sse_loadhps */
    case 1214:  /* sse_loadlps */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return PREFIX_ORIG;
        }
      else if (which_alternative == 1)
        {
	  return PREFIX_VEX;
        }
      else if (which_alternative == 2)
        {
	  return PREFIX_ORIG;
        }
      else if (which_alternative == 3)
        {
	  return PREFIX_VEX;
        }
      else
        {
	  return PREFIX_MAYBE_VEX;
        }

    case 1222:  /* *vec_concatv4sf */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return PREFIX_ORIG;
        }
      else if (which_alternative == 1)
        {
	  return PREFIX_VEX;
        }
      else if (which_alternative == 2)
        {
	  return PREFIX_ORIG;
        }
      else
        {
	  return PREFIX_VEX;
        }

    case 1243:  /* *vec_interleave_highv2df */
    case 1245:  /* *vec_interleave_lowv2df */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return PREFIX_ORIG;
        }
      else if (which_alternative == 1)
        {
	  return PREFIX_VEX;
        }
      else if (which_alternative == 2)
        {
	  return PREFIX_MAYBE_VEX;
        }
      else if (which_alternative == 3)
        {
	  return PREFIX_ORIG;
        }
      else if (which_alternative == 4)
        {
	  return PREFIX_VEX;
        }
      else
        {
	  return PREFIX_MAYBE_VEX;
        }

    case 193:  /* *floatdidf2_mixed_interunit */
    case 192:  /* *floatsidf2_mixed_interunit */
    case 191:  /* *floatdisf2_mixed_interunit */
    case 190:  /* *floatsisf2_mixed_interunit */
    case 49:  /* *cmpisf_mixed */
    case 50:  /* *cmpidf_mixed */
    case 51:  /* *cmpiusf_mixed */
    case 52:  /* *cmpiudf_mixed */
    case 133:  /* *truncdfsf_fast_mixed */
    case 194:  /* *floatsisf2_mixed_nointerunit */
    case 195:  /* *floatdisf2_mixed_nointerunit */
    case 196:  /* *floatsidf2_mixed_nointerunit */
    case 197:  /* *floatdidf2_mixed_nointerunit */
    case 1260:  /* vec_dupv2df */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return PREFIX_ORIG;
        }
      else
        {
	  return PREFIX_MAYBE_VEX;
        }

    case 1438:  /* *vec_dupv4si */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return PREFIX_MAYBE_VEX;
        }
      else if (which_alternative == 1)
        {
	  return PREFIX_VEX;
        }
      else
        {
	  return PREFIX_ORIG;
        }

    case 1439:  /* *vec_dupv2di */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return PREFIX_ORIG;
        }
      else if (which_alternative == 1)
        {
	  return PREFIX_VEX;
        }
      else if (which_alternative == 2)
        {
	  return PREFIX_MAYBE_VEX;
        }
      else
        {
	  return PREFIX_ORIG;
        }

    case 501:  /* setcc_sf_sse */
    case 502:  /* setcc_df_sse */
    case 629:  /* *fop_sf_comm_sse */
    case 630:  /* *fop_df_comm_sse */
    case 636:  /* *fop_sf_1_sse */
    case 637:  /* *fop_df_1_sse */
    case 781:  /* smaxsf3 */
    case 782:  /* sminsf3 */
    case 783:  /* smaxdf3 */
    case 784:  /* smindf3 */
    case 785:  /* *ieee_smaxsf3 */
    case 786:  /* *ieee_sminsf3 */
    case 787:  /* *ieee_smaxdf3 */
    case 788:  /* *ieee_smindf3 */
    case 988:  /* *addv8sf3 */
    case 989:  /* *subv8sf3 */
    case 990:  /* *addv4sf3 */
    case 991:  /* *subv4sf3 */
    case 992:  /* *addv4df3 */
    case 993:  /* *subv4df3 */
    case 994:  /* *addv2df3 */
    case 995:  /* *subv2df3 */
    case 996:  /* sse_vmaddv4sf3 */
    case 997:  /* sse_vmsubv4sf3 */
    case 998:  /* sse2_vmaddv2df3 */
    case 999:  /* sse2_vmsubv2df3 */
    case 1000:  /* *mulv8sf3 */
    case 1001:  /* *mulv4sf3 */
    case 1002:  /* *mulv4df3 */
    case 1003:  /* *mulv2df3 */
    case 1004:  /* sse_vmmulv4sf3 */
    case 1005:  /* sse2_vmmulv2df3 */
    case 1006:  /* avx_divv8sf3 */
    case 1007:  /* sse_divv4sf3 */
    case 1008:  /* avx_divv4df3 */
    case 1009:  /* sse2_divv2df3 */
    case 1010:  /* sse_vmdivv4sf3 */
    case 1011:  /* sse2_vmdivv2df3 */
    case 1014:  /* sse_vmrcpv4sf2 */
    case 1019:  /* sse_vmsqrtv4sf2 */
    case 1020:  /* sse2_vmsqrtv2df2 */
    case 1023:  /* sse_vmrsqrtv4sf2 */
    case 1024:  /* *smaxv8sf3_finite */
    case 1025:  /* *sminv8sf3_finite */
    case 1026:  /* *smaxv4sf3_finite */
    case 1027:  /* *sminv4sf3_finite */
    case 1028:  /* *smaxv4df3_finite */
    case 1029:  /* *sminv4df3_finite */
    case 1030:  /* *smaxv2df3_finite */
    case 1031:  /* *sminv2df3_finite */
    case 1032:  /* *smaxv8sf3 */
    case 1033:  /* *sminv8sf3 */
    case 1034:  /* *smaxv4sf3 */
    case 1035:  /* *sminv4sf3 */
    case 1036:  /* *smaxv4df3 */
    case 1037:  /* *sminv4df3 */
    case 1038:  /* *smaxv2df3 */
    case 1039:  /* *sminv2df3 */
    case 1040:  /* sse_vmsmaxv4sf3 */
    case 1041:  /* sse_vmsminv4sf3 */
    case 1042:  /* sse2_vmsmaxv2df3 */
    case 1043:  /* sse2_vmsminv2df3 */
    case 1044:  /* *ieee_sminv8sf3 */
    case 1045:  /* *ieee_sminv4sf3 */
    case 1046:  /* *ieee_sminv4df3 */
    case 1047:  /* *ieee_sminv2df3 */
    case 1048:  /* *ieee_smaxv8sf3 */
    case 1049:  /* *ieee_smaxv4sf3 */
    case 1050:  /* *ieee_smaxv4df3 */
    case 1051:  /* *ieee_smaxv2df3 */
    case 1053:  /* sse3_addsubv2df3 */
    case 1055:  /* sse3_addsubv4sf3 */
    case 1058:  /* *sse3_haddv2df3 */
    case 1059:  /* sse3_hsubv2df3 */
    case 1060:  /* *sse3_haddv2df3_low */
    case 1061:  /* *sse3_hsubv2df3_low */
    case 1064:  /* sse3_haddv4sf3 */
    case 1065:  /* sse3_hsubv4sf3 */
    case 1072:  /* *avx_maskcmpv8sf3_comm */
    case 1073:  /* *sse_maskcmpv4sf3_comm */
    case 1074:  /* *avx_maskcmpv4df3_comm */
    case 1075:  /* *sse2_maskcmpv2df3_comm */
    case 1076:  /* avx_maskcmpv8sf3 */
    case 1077:  /* sse_maskcmpv4sf3 */
    case 1078:  /* avx_maskcmpv4df3 */
    case 1079:  /* sse2_maskcmpv2df3 */
    case 1080:  /* sse_vmmaskcmpv4sf3 */
    case 1081:  /* sse2_vmmaskcmpv2df3 */
    case 1086:  /* avx_andnotv8sf3 */
    case 1087:  /* sse_andnotv4sf3 */
    case 1088:  /* avx_andnotv4df3 */
    case 1089:  /* sse2_andnotv2df3 */
    case 1090:  /* *andv8sf3 */
    case 1091:  /* *iorv8sf3 */
    case 1092:  /* *xorv8sf3 */
    case 1093:  /* *andv4sf3 */
    case 1094:  /* *iorv4sf3 */
    case 1095:  /* *xorv4sf3 */
    case 1096:  /* *andv4df3 */
    case 1097:  /* *iorv4df3 */
    case 1098:  /* *xorv4df3 */
    case 1099:  /* *andv2df3 */
    case 1100:  /* *iorv2df3 */
    case 1101:  /* *xorv2df3 */
    case 1102:  /* *andnotsf3 */
    case 1103:  /* *andnotdf3 */
    case 1104:  /* *andnottf3 */
    case 1105:  /* *andsf3 */
    case 1106:  /* *iorsf3 */
    case 1107:  /* *xorsf3 */
    case 1108:  /* *anddf3 */
    case 1109:  /* *iordf3 */
    case 1110:  /* *xordf3 */
    case 1111:  /* *andtf3 */
    case 1112:  /* *iortf3 */
    case 1113:  /* *xortf3 */
    case 1201:  /* vec_interleave_highv4sf */
    case 1203:  /* vec_interleave_lowv4sf */
    case 1209:  /* sse_shufps_v4si */
    case 1210:  /* sse_shufps_v4sf */
    case 1215:  /* sse_movss */
    case 1225:  /* *vec_setv4sf_sse4_1 */
    case 1226:  /* sse4_1_insertps */
    case 1248:  /* vec_interleave_highv2di */
    case 1250:  /* vec_interleave_lowv2di */
    case 1251:  /* sse2_shufpd_v2di */
    case 1252:  /* sse2_shufpd_v2df */
    case 1262:  /* *addv32qi3 */
    case 1263:  /* *subv32qi3 */
    case 1264:  /* *addv16qi3 */
    case 1265:  /* *subv16qi3 */
    case 1266:  /* *addv16hi3 */
    case 1267:  /* *subv16hi3 */
    case 1268:  /* *addv8hi3 */
    case 1269:  /* *subv8hi3 */
    case 1270:  /* *addv8si3 */
    case 1271:  /* *subv8si3 */
    case 1272:  /* *addv4si3 */
    case 1273:  /* *subv4si3 */
    case 1274:  /* *addv4di3 */
    case 1275:  /* *subv4di3 */
    case 1276:  /* *addv2di3 */
    case 1277:  /* *subv2di3 */
    case 1278:  /* *avx2_ssaddv32qi3 */
    case 1279:  /* *avx2_usaddv32qi3 */
    case 1280:  /* *avx2_sssubv32qi3 */
    case 1281:  /* *avx2_ussubv32qi3 */
    case 1282:  /* *sse2_ssaddv16qi3 */
    case 1283:  /* *sse2_usaddv16qi3 */
    case 1284:  /* *sse2_sssubv16qi3 */
    case 1285:  /* *sse2_ussubv16qi3 */
    case 1286:  /* *avx2_ssaddv16hi3 */
    case 1287:  /* *avx2_usaddv16hi3 */
    case 1288:  /* *avx2_sssubv16hi3 */
    case 1289:  /* *avx2_ussubv16hi3 */
    case 1290:  /* *sse2_ssaddv8hi3 */
    case 1291:  /* *sse2_usaddv8hi3 */
    case 1292:  /* *sse2_sssubv8hi3 */
    case 1293:  /* *sse2_ussubv8hi3 */
    case 1294:  /* *mulv16hi3 */
    case 1295:  /* *mulv8hi3 */
    case 1296:  /* *smulv16hi3_highpart */
    case 1297:  /* *umulv16hi3_highpart */
    case 1298:  /* *smulv8hi3_highpart */
    case 1299:  /* *umulv8hi3_highpart */
    case 1301:  /* *vec_widen_umult_even_v4si */
    case 1303:  /* *sse4_1_mulv2siv2di3 */
    case 1305:  /* *sse2_pmaddwd */
    case 1306:  /* *avx2_mulv8si3 */
    case 1307:  /* *sse4_1_mulv4si3 */
    case 1308:  /* ashrv16hi3 */
    case 1309:  /* ashrv8hi3 */
    case 1310:  /* ashrv8si3 */
    case 1311:  /* ashrv4si3 */
    case 1312:  /* ashlv16hi3 */
    case 1313:  /* lshrv16hi3 */
    case 1314:  /* ashlv8hi3 */
    case 1315:  /* lshrv8hi3 */
    case 1316:  /* ashlv8si3 */
    case 1317:  /* lshrv8si3 */
    case 1318:  /* ashlv4si3 */
    case 1319:  /* lshrv4si3 */
    case 1320:  /* ashlv4di3 */
    case 1321:  /* lshrv4di3 */
    case 1322:  /* ashlv2di3 */
    case 1323:  /* lshrv2di3 */
    case 1324:  /* avx2_ashlv2ti3 */
    case 1325:  /* sse2_ashlv1ti3 */
    case 1326:  /* avx2_lshrv2ti3 */
    case 1327:  /* sse2_lshrv1ti3 */
    case 1340:  /* *sse4_1_smaxv16qi3 */
    case 1341:  /* *sse4_1_sminv16qi3 */
    case 1342:  /* *sse4_1_smaxv4si3 */
    case 1343:  /* *sse4_1_sminv4si3 */
    case 1344:  /* *smaxv8hi3 */
    case 1345:  /* *sminv8hi3 */
    case 1346:  /* *sse4_1_umaxv8hi3 */
    case 1347:  /* *sse4_1_uminv8hi3 */
    case 1348:  /* *sse4_1_umaxv4si3 */
    case 1349:  /* *sse4_1_uminv4si3 */
    case 1350:  /* *umaxv16qi3 */
    case 1351:  /* *uminv16qi3 */
    case 1356:  /* *sse4_1_eqv2di3 */
    case 1357:  /* *sse2_eqv16qi3 */
    case 1358:  /* *sse2_eqv8hi3 */
    case 1359:  /* *sse2_eqv4si3 */
    case 1360:  /* sse4_2_gtv2di3 */
    case 1365:  /* sse2_gtv16qi3 */
    case 1366:  /* sse2_gtv8hi3 */
    case 1367:  /* sse2_gtv4si3 */
    case 1368:  /* *andnotv32qi3 */
    case 1369:  /* *andnotv16qi3 */
    case 1370:  /* *andnotv16hi3 */
    case 1371:  /* *andnotv8hi3 */
    case 1372:  /* *andnotv8si3 */
    case 1373:  /* *andnotv4si3 */
    case 1374:  /* *andnotv4di3 */
    case 1375:  /* *andnotv2di3 */
    case 1376:  /* *andv32qi3 */
    case 1377:  /* *iorv32qi3 */
    case 1378:  /* *xorv32qi3 */
    case 1379:  /* *andv16qi3 */
    case 1380:  /* *iorv16qi3 */
    case 1381:  /* *xorv16qi3 */
    case 1382:  /* *andv16hi3 */
    case 1383:  /* *iorv16hi3 */
    case 1384:  /* *xorv16hi3 */
    case 1385:  /* *andv8hi3 */
    case 1386:  /* *iorv8hi3 */
    case 1387:  /* *xorv8hi3 */
    case 1388:  /* *andv8si3 */
    case 1389:  /* *iorv8si3 */
    case 1390:  /* *xorv8si3 */
    case 1391:  /* *andv4si3 */
    case 1392:  /* *iorv4si3 */
    case 1393:  /* *xorv4si3 */
    case 1394:  /* *andv4di3 */
    case 1395:  /* *iorv4di3 */
    case 1396:  /* *xorv4di3 */
    case 1397:  /* *andv2di3 */
    case 1398:  /* *iorv2di3 */
    case 1399:  /* *xorv2di3 */
    case 1400:  /* avx2_packsswb */
    case 1401:  /* sse2_packsswb */
    case 1402:  /* avx2_packssdw */
    case 1403:  /* sse2_packssdw */
    case 1404:  /* avx2_packuswb */
    case 1405:  /* sse2_packuswb */
    case 1407:  /* vec_interleave_highv16qi */
    case 1409:  /* vec_interleave_lowv16qi */
    case 1411:  /* vec_interleave_highv8hi */
    case 1413:  /* vec_interleave_lowv8hi */
    case 1415:  /* vec_interleave_highv4si */
    case 1417:  /* vec_interleave_lowv4si */
    case 1445:  /* *avx2_uavgv32qi3 */
    case 1446:  /* *sse2_uavgv16qi3 */
    case 1447:  /* *avx2_uavgv16hi3 */
    case 1448:  /* *sse2_uavgv8hi3 */
    case 1449:  /* avx2_psadbw */
    case 1450:  /* sse2_psadbw */
    case 1468:  /* ssse3_phaddwv8hi3 */
    case 1469:  /* ssse3_phaddswv8hi3 */
    case 1470:  /* ssse3_phsubwv8hi3 */
    case 1471:  /* ssse3_phsubswv8hi3 */
    case 1478:  /* ssse3_phadddv4si3 */
    case 1479:  /* ssse3_phsubdv4si3 */
    case 1483:  /* ssse3_pmaddubsw128 */
    case 1485:  /* *avx2_pmulhrswv16hi3 */
    case 1486:  /* *ssse3_pmulhrswv8hi3 */
    case 1488:  /* avx2_pshufbv32qi3 */
    case 1489:  /* ssse3_pshufbv16qi3 */
    case 1491:  /* avx2_psignv32qi3 */
    case 1492:  /* ssse3_psignv16qi3 */
    case 1493:  /* avx2_psignv16hi3 */
    case 1494:  /* ssse3_psignv8hi3 */
    case 1495:  /* avx2_psignv8si3 */
    case 1496:  /* ssse3_psignv4si3 */
    case 1500:  /* avx2_palignrv2ti */
    case 1501:  /* ssse3_palignrti */
    case 1520:  /* avx_blendps256 */
    case 1521:  /* sse4_1_blendps */
    case 1522:  /* avx_blendpd256 */
    case 1523:  /* sse4_1_blendpd */
    case 1524:  /* avx_blendvps256 */
    case 1525:  /* sse4_1_blendvps */
    case 1526:  /* avx_blendvpd256 */
    case 1527:  /* sse4_1_blendvpd */
    case 1528:  /* avx_dpps256 */
    case 1529:  /* sse4_1_dpps */
    case 1530:  /* avx_dppd256 */
    case 1531:  /* sse4_1_dppd */
    case 1534:  /* avx2_mpsadbw */
    case 1535:  /* sse4_1_mpsadbw */
    case 1537:  /* sse4_1_packusdw */
    case 1538:  /* avx2_pblendvb */
    case 1539:  /* sse4_1_pblendvb */
    case 1540:  /* sse4_1_pblendw */
    case 1579:  /* sse4_1_roundss */
    case 1580:  /* sse4_1_roundsd */
    case 1682:  /* aesenc */
    case 1683:  /* aesenclast */
    case 1684:  /* aesdec */
    case 1685:  /* aesdeclast */
    case 1688:  /* pclmulqdq */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return PREFIX_ORIG;
        }
      else
        {
	  return PREFIX_VEX;
        }

    case -1:
      if (GET_CODE (PATTERN (insn)) != ASM_INPUT
          && asm_noperands (PATTERN (insn)) < 0)
        fatal_insn_not_found (insn);
      if (((cached_mode = get_attr_mode (insn)) == MODE_OI) || ((cached_mode == MODE_V8SF) || (cached_mode == MODE_V4DF)))
        {
	  return PREFIX_VEX;
        }
      else
        {
	  return PREFIX_ORIG;
        }

    case 53:  /* *cmpisf_sse */
    case 54:  /* *cmpidf_sse */
    case 55:  /* *cmpiusf_sse */
    case 56:  /* *cmpiudf_sse */
    case 76:  /* *movti_internal_sse */
    case 110:  /* *movtf_internal_sse */
    case 129:  /* *extendsfdf2_sse */
    case 134:  /* *truncdfsf_fast_sse */
    case 147:  /* fix_truncsfsi_sse */
    case 148:  /* fix_truncdfsi_sse */
    case 204:  /* *floatsisf2_sse_interunit */
    case 205:  /* *floatdisf2_sse_interunit */
    case 206:  /* *floatsidf2_sse_interunit */
    case 207:  /* *floatdidf2_sse_interunit */
    case 208:  /* *floatsisf2_sse_nointerunit */
    case 209:  /* *floatdisf2_sse_nointerunit */
    case 210:  /* *floatsidf2_sse_nointerunit */
    case 211:  /* *floatdidf2_sse_nointerunit */
    case 635:  /* *rcpsf2_sse */
    case 668:  /* *rsqrtsf2_sse */
    case 669:  /* *sqrtsf2_sse */
    case 670:  /* *sqrtdf2_sse */
    case 699:  /* sse4_1_roundsf2 */
    case 700:  /* sse4_1_rounddf2 */
    case 742:  /* movmsk_df */
    case 947:  /* *movv32qi_internal */
    case 948:  /* *movv16qi_internal */
    case 949:  /* *movv16hi_internal */
    case 950:  /* *movv8hi_internal */
    case 951:  /* *movv8si_internal */
    case 952:  /* *movv4si_internal */
    case 953:  /* *movv4di_internal */
    case 954:  /* *movv2di_internal */
    case 955:  /* *movv2ti_internal */
    case 956:  /* *movv1ti_internal */
    case 957:  /* *movv8sf_internal */
    case 958:  /* *movv4sf_internal */
    case 959:  /* *movv4df_internal */
    case 960:  /* *movv2df_internal */
    case 961:  /* sse2_movq128 */
    case 963:  /* avx_loadups256 */
    case 964:  /* sse_loadups */
    case 965:  /* avx_loadupd256 */
    case 966:  /* sse2_loadupd */
    case 967:  /* avx_storeups256 */
    case 968:  /* sse_storeups */
    case 969:  /* avx_storeupd256 */
    case 970:  /* sse2_storeupd */
    case 971:  /* avx_loaddqu256 */
    case 972:  /* sse2_loaddqu */
    case 973:  /* avx_storedqu256 */
    case 974:  /* sse2_storedqu */
    case 975:  /* avx_lddqu256 */
    case 976:  /* sse3_lddqu */
    case 978:  /* avx_movntv8sf */
    case 979:  /* sse_movntv4sf */
    case 980:  /* avx_movntv4df */
    case 981:  /* sse2_movntv2df */
    case 982:  /* avx_movntv4di */
    case 983:  /* sse2_movntv2di */
    case 1012:  /* avx_rcpv8sf2 */
    case 1013:  /* sse_rcpv4sf2 */
    case 1015:  /* avx_sqrtv8sf2 */
    case 1016:  /* sse_sqrtv4sf2 */
    case 1017:  /* avx_sqrtv4df2 */
    case 1018:  /* sse2_sqrtv2df2 */
    case 1021:  /* avx_rsqrtv8sf2 */
    case 1022:  /* sse_rsqrtv4sf2 */
    case 1082:  /* sse_comi */
    case 1083:  /* sse2_comi */
    case 1084:  /* sse_ucomi */
    case 1085:  /* sse2_ucomi */
    case 1166:  /* sse_cvtss2si */
    case 1167:  /* sse_cvtss2si_2 */
    case 1168:  /* sse_cvttss2si */
    case 1169:  /* floatv8siv8sf2 */
    case 1170:  /* floatv4siv4sf2 */
    case 1172:  /* sse2_cvtps2dq */
    case 1174:  /* fix_truncv4sfv4si2 */
    case 1179:  /* sse2_cvtsd2si */
    case 1180:  /* sse2_cvtsd2si_2 */
    case 1181:  /* sse2_cvttsd2si */
    case 1184:  /* sse2_cvtdq2pd */
    case 1187:  /* *sse2_cvtpd2dq */
    case 1190:  /* *sse2_cvttpd2dq */
    case 1194:  /* *sse2_cvtpd2ps */
    case 1197:  /* sse2_cvtps2pd */
    case 1205:  /* sse3_movshdup */
    case 1207:  /* sse3_movsldup */
    case 1211:  /* sse_storehps */
    case 1213:  /* sse_storelps */
    case 1255:  /* sse2_storelpd */
    case 1422:  /* *sse4_1_pextrb_si */
    case 1423:  /* *sse4_1_pextrb_memory */
    case 1424:  /* *sse2_pextrw_si */
    case 1425:  /* *sse4_1_pextrw_memory */
    case 1426:  /* *sse4_1_pextrd */
    case 1428:  /* sse2_pshufd_1 */
    case 1430:  /* sse2_pshuflw_1 */
    case 1432:  /* sse2_pshufhw_1 */
    case 1451:  /* avx_movmskps256 */
    case 1452:  /* sse_movmskps */
    case 1453:  /* avx_movmskpd256 */
    case 1454:  /* sse2_movmskpd */
    case 1456:  /* sse2_pmovmskb */
    case 1457:  /* *sse2_maskmovdqu */
    case 1458:  /* *sse2_maskmovdqu */
    case 1459:  /* sse_ldmxcsr */
    case 1460:  /* sse_stmxcsr */
    case 1503:  /* absv32qi2 */
    case 1504:  /* absv16qi2 */
    case 1505:  /* absv16hi2 */
    case 1506:  /* absv8hi2 */
    case 1507:  /* absv8si2 */
    case 1508:  /* absv4si2 */
    case 1532:  /* avx2_movntdqa */
    case 1533:  /* sse4_1_movntdqa */
    case 1544:  /* sse4_1_phminposuw */
    case 1547:  /* sse4_1_sign_extendv8qiv8hi2 */
    case 1548:  /* sse4_1_zero_extendv8qiv8hi2 */
    case 1551:  /* sse4_1_sign_extendv4qiv4si2 */
    case 1552:  /* sse4_1_zero_extendv4qiv4si2 */
    case 1555:  /* sse4_1_sign_extendv4hiv4si2 */
    case 1556:  /* sse4_1_zero_extendv4hiv4si2 */
    case 1559:  /* sse4_1_sign_extendv2qiv2di2 */
    case 1560:  /* sse4_1_zero_extendv2qiv2di2 */
    case 1563:  /* sse4_1_sign_extendv2hiv2di2 */
    case 1564:  /* sse4_1_zero_extendv2hiv2di2 */
    case 1567:  /* sse4_1_sign_extendv2siv2di2 */
    case 1568:  /* sse4_1_zero_extendv2siv2di2 */
    case 1574:  /* sse4_1_ptest */
    case 1575:  /* avx_roundps256 */
    case 1576:  /* sse4_1_roundps */
    case 1577:  /* avx_roundpd256 */
    case 1578:  /* sse4_1_roundpd */
    case 1583:  /* sse4_2_pcmpestri */
    case 1584:  /* sse4_2_pcmpestrm */
    case 1585:  /* sse4_2_pcmpestr_cconly */
    case 1588:  /* sse4_2_pcmpistri */
    case 1589:  /* sse4_2_pcmpistrm */
    case 1590:  /* sse4_2_pcmpistr_cconly */
    case 1686:  /* aesimc */
    case 1687:  /* aeskeygenassist */
      return PREFIX_MAYBE_VEX;

    case 1680:  /* xop_vpermil2v4df3 */
    case 1678:  /* xop_vpermil2v8sf3 */
    case 1659:  /* xop_frczv4df2 */
    case 1658:  /* xop_frczv8sf2 */
    case 1566:  /* avx2_zero_extendv4siv4di2 */
    case 1565:  /* avx2_sign_extendv4siv4di2 */
    case 1144:  /* *fma_fmsubadd_v4df */
    case 1142:  /* *fma_fmsubadd_v8sf */
    case 1140:  /* *fma_fmaddsub_v4df */
    case 1138:  /* *fma_fmaddsub_v8sf */
    case 1137:  /* *fma_fnmsub_v4df */
    case 1136:  /* *fma_fnmsub_v8sf */
    case 1131:  /* *fma_fnmadd_v4df */
    case 1130:  /* *fma_fnmadd_v8sf */
    case 1125:  /* *fma_fmsub_v4df */
    case 1124:  /* *fma_fmsub_v8sf */
    case 1119:  /* *fma_fmadd_v4df */
    case 1118:  /* *fma_fmadd_v8sf */
    case 75:  /* *movoi_internal_avx */
    case 305:  /* *bmi2_umulsidi3_1 */
    case 586:  /* bmi2_bzhi_si3 */
    case 587:  /* bmi2_pdep_si3 */
    case 588:  /* bmi2_pext_si3 */
    case 1052:  /* avx_addsubv4df3 */
    case 1054:  /* avx_addsubv8sf3 */
    case 1056:  /* avx_haddv4df3 */
    case 1057:  /* avx_hsubv4df3 */
    case 1062:  /* avx_haddv8sf3 */
    case 1063:  /* avx_hsubv8sf3 */
    case 1066:  /* avx_cmpv8sf3 */
    case 1067:  /* avx_cmpv4sf3 */
    case 1068:  /* avx_cmpv4df3 */
    case 1069:  /* avx_cmpv2df3 */
    case 1070:  /* avx_vmcmpv4sf3 */
    case 1071:  /* avx_vmcmpv2df3 */
    case 1171:  /* avx_cvtps2dq256 */
    case 1173:  /* fix_truncv8sfv8si2 */
    case 1182:  /* floatv4siv4df2 */
    case 1183:  /* avx_cvtdq2pd256_2 */
    case 1185:  /* avx_cvtpd2dq256 */
    case 1186:  /* *avx_cvtpd2dq256_2 */
    case 1188:  /* fix_truncv4dfv4si2 */
    case 1189:  /* *avx_cvttpd2dq256_2 */
    case 1193:  /* avx_cvtpd2ps256 */
    case 1195:  /* avx_cvtps2pd256 */
    case 1196:  /* *avx_cvtps2pd256_2 */
    case 1200:  /* avx_unpckhps256 */
    case 1202:  /* avx_unpcklps256 */
    case 1204:  /* avx_movshdup256 */
    case 1206:  /* avx_movsldup256 */
    case 1208:  /* avx_shufps256_1 */
    case 1216:  /* avx2_vec_dupv8sf */
    case 1217:  /* avx2_vec_dupv4sf */
    case 1218:  /* avx2_vec_dupv8sf_1 */
    case 1232:  /* vec_extract_hi_v4di */
    case 1233:  /* vec_extract_hi_v4df */
    case 1236:  /* vec_extract_hi_v8si */
    case 1237:  /* vec_extract_hi_v8sf */
    case 1239:  /* vec_extract_hi_v16hi */
    case 1241:  /* vec_extract_hi_v32qi */
    case 1242:  /* avx_unpckhpd256 */
    case 1244:  /* *avx_unpcklpd256 */
    case 1246:  /* avx_shufpd256_1 */
    case 1247:  /* avx2_interleave_highv4di */
    case 1249:  /* avx2_interleave_lowv4di */
    case 1300:  /* *vec_widen_umult_even_v8si */
    case 1302:  /* *vec_widen_smult_even_v8si */
    case 1304:  /* *avx2_pmaddwd */
    case 1328:  /* *avx2_smaxv32qi3 */
    case 1329:  /* *avx2_sminv32qi3 */
    case 1330:  /* *avx2_umaxv32qi3 */
    case 1331:  /* *avx2_uminv32qi3 */
    case 1332:  /* *avx2_smaxv16hi3 */
    case 1333:  /* *avx2_sminv16hi3 */
    case 1334:  /* *avx2_umaxv16hi3 */
    case 1335:  /* *avx2_uminv16hi3 */
    case 1336:  /* *avx2_smaxv8si3 */
    case 1337:  /* *avx2_sminv8si3 */
    case 1338:  /* *avx2_umaxv8si3 */
    case 1339:  /* *avx2_uminv8si3 */
    case 1352:  /* *avx2_eqv32qi3 */
    case 1353:  /* *avx2_eqv16hi3 */
    case 1354:  /* *avx2_eqv8si3 */
    case 1355:  /* *avx2_eqv4di3 */
    case 1361:  /* avx2_gtv32qi3 */
    case 1362:  /* avx2_gtv16hi3 */
    case 1363:  /* avx2_gtv8si3 */
    case 1364:  /* avx2_gtv4di3 */
    case 1406:  /* avx2_interleave_highv32qi */
    case 1408:  /* avx2_interleave_lowv32qi */
    case 1410:  /* avx2_interleave_highv16hi */
    case 1412:  /* avx2_interleave_lowv16hi */
    case 1414:  /* avx2_interleave_highv8si */
    case 1416:  /* avx2_interleave_lowv8si */
    case 1427:  /* avx2_pshufd_1 */
    case 1429:  /* avx2_pshuflw_1 */
    case 1431:  /* avx2_pshufhw_1 */
    case 1455:  /* avx2_pmovmskb */
    case 1464:  /* avx2_phaddwv16hi3 */
    case 1465:  /* avx2_phaddswv16hi3 */
    case 1466:  /* avx2_phsubwv16hi3 */
    case 1467:  /* avx2_phsubswv16hi3 */
    case 1476:  /* avx2_phadddv8si3 */
    case 1477:  /* avx2_phsubdv8si3 */
    case 1482:  /* avx2_pmaddubsw256 */
    case 1536:  /* avx2_packusdw */
    case 1541:  /* *avx2_pblendw */
    case 1542:  /* avx2_pblenddv8si */
    case 1543:  /* avx2_pblenddv4si */
    case 1545:  /* avx2_sign_extendv16qiv16hi2 */
    case 1546:  /* avx2_zero_extendv16qiv16hi2 */
    case 1549:  /* avx2_sign_extendv8qiv8si2 */
    case 1550:  /* avx2_zero_extendv8qiv8si2 */
    case 1553:  /* avx2_sign_extendv8hiv8si2 */
    case 1554:  /* avx2_zero_extendv8hiv8si2 */
    case 1557:  /* avx2_sign_extendv4qiv4di2 */
    case 1558:  /* avx2_zero_extendv4qiv4di2 */
    case 1561:  /* avx2_sign_extendv4hiv4di2 */
    case 1562:  /* avx2_zero_extendv4hiv4di2 */
    case 1569:  /* avx_vtestps256 */
    case 1570:  /* avx_vtestps */
    case 1571:  /* avx_vtestpd256 */
    case 1572:  /* avx_vtestpd */
    case 1573:  /* avx_ptest256 */
    case 1689:  /* *avx_vzeroall */
    case 1690:  /* avx_vzeroupper */
    case 1691:  /* avx2_pbroadcastv32qi */
    case 1692:  /* avx2_pbroadcastv16qi */
    case 1693:  /* avx2_pbroadcastv16hi */
    case 1694:  /* avx2_pbroadcastv8hi */
    case 1695:  /* avx2_pbroadcastv8si */
    case 1696:  /* avx2_pbroadcastv4si */
    case 1697:  /* avx2_pbroadcastv4di */
    case 1698:  /* avx2_pbroadcastv2di */
    case 1699:  /* avx2_pbroadcastv32qi_1 */
    case 1700:  /* avx2_pbroadcastv16hi_1 */
    case 1701:  /* avx2_pbroadcastv8si_1 */
    case 1702:  /* avx2_pbroadcastv4di_1 */
    case 1703:  /* avx2_permvarv8si */
    case 1704:  /* avx2_permvarv8sf */
    case 1705:  /* avx2_permv4di_1 */
    case 1706:  /* avx2_permv4df_1 */
    case 1707:  /* avx2_permv2ti */
    case 1708:  /* avx2_vec_dupv4df */
    case 1709:  /* vec_dupv8si */
    case 1710:  /* vec_dupv8sf */
    case 1711:  /* vec_dupv4di */
    case 1712:  /* vec_dupv4df */
    case 1713:  /* avx2_vbroadcasti128_v32qi */
    case 1714:  /* avx2_vbroadcasti128_v16hi */
    case 1715:  /* avx2_vbroadcasti128_v8si */
    case 1716:  /* avx2_vbroadcasti128_v4di */
    case 1717:  /* avx_vbroadcastf128_v32qi */
    case 1718:  /* avx_vbroadcastf128_v16hi */
    case 1719:  /* avx_vbroadcastf128_v8si */
    case 1720:  /* avx_vbroadcastf128_v4di */
    case 1721:  /* avx_vbroadcastf128_v8sf */
    case 1722:  /* avx_vbroadcastf128_v4df */
    case 1723:  /* *avx_vperm_broadcast_v4sf */
    case 1726:  /* *avx_vpermilpv8sf */
    case 1727:  /* *avx_vpermilpv4sf */
    case 1728:  /* *avx_vpermilpv4df */
    case 1729:  /* *avx_vpermilpv2df */
    case 1730:  /* avx_vpermilvarv8sf3 */
    case 1731:  /* avx_vpermilvarv4sf3 */
    case 1732:  /* avx_vpermilvarv4df3 */
    case 1733:  /* avx_vpermilvarv2df3 */
    case 1734:  /* *avx_vperm2f128v8si_full */
    case 1735:  /* *avx_vperm2f128v8sf_full */
    case 1736:  /* *avx_vperm2f128v4df_full */
    case 1737:  /* *avx_vperm2f128v8si_nozero */
    case 1738:  /* *avx_vperm2f128v8sf_nozero */
    case 1739:  /* *avx_vperm2f128v4df_nozero */
    case 1740:  /* avx2_vec_set_lo_v4di */
    case 1741:  /* avx2_vec_set_hi_v4di */
    case 1742:  /* vec_set_lo_v4di */
    case 1743:  /* vec_set_lo_v4df */
    case 1744:  /* vec_set_hi_v4di */
    case 1745:  /* vec_set_hi_v4df */
    case 1746:  /* vec_set_lo_v8si */
    case 1747:  /* vec_set_lo_v8sf */
    case 1748:  /* vec_set_hi_v8si */
    case 1749:  /* vec_set_hi_v8sf */
    case 1750:  /* vec_set_lo_v16hi */
    case 1751:  /* vec_set_hi_v16hi */
    case 1752:  /* vec_set_lo_v32qi */
    case 1753:  /* vec_set_hi_v32qi */
    case 1754:  /* avx_maskloadps */
    case 1755:  /* avx_maskloadpd */
    case 1756:  /* avx_maskloadps256 */
    case 1757:  /* avx_maskloadpd256 */
    case 1758:  /* avx2_maskloadd */
    case 1759:  /* avx2_maskloadq */
    case 1760:  /* avx2_maskloadd256 */
    case 1761:  /* avx2_maskloadq256 */
    case 1762:  /* avx_maskstoreps */
    case 1763:  /* avx_maskstorepd */
    case 1764:  /* avx_maskstoreps256 */
    case 1765:  /* avx_maskstorepd256 */
    case 1766:  /* avx2_maskstored */
    case 1767:  /* avx2_maskstoreq */
    case 1768:  /* avx2_maskstored256 */
    case 1769:  /* avx2_maskstoreq256 */
    case 1773:  /* avx2_ashrvv8si */
    case 1774:  /* avx2_ashrvv4si */
    case 1775:  /* avx2_ashlvv8si */
    case 1776:  /* avx2_lshrvv8si */
    case 1777:  /* avx2_ashlvv4si */
    case 1778:  /* avx2_lshrvv4si */
    case 1779:  /* avx2_ashlvv4di */
    case 1780:  /* avx2_lshrvv4di */
    case 1781:  /* avx2_ashlvv2di */
    case 1782:  /* avx2_lshrvv2di */
    case 1783:  /* avx_vec_concatv32qi */
    case 1784:  /* avx_vec_concatv16hi */
    case 1785:  /* avx_vec_concatv8si */
    case 1786:  /* avx_vec_concatv4di */
    case 1787:  /* avx_vec_concatv8sf */
    case 1788:  /* avx_vec_concatv4df */
    case 1789:  /* vcvtph2ps */
    case 1790:  /* *vcvtph2ps_load */
    case 1791:  /* vcvtph2ps256 */
    case 1792:  /* *vcvtps2ph */
    case 1793:  /* *vcvtps2ph_store */
    case 1794:  /* vcvtps2ph256 */
    case 1795:  /* *avx2_gathersiv2di */
    case 1796:  /* *avx2_gathersiv2di */
    case 1797:  /* *avx2_gathersiv2df */
    case 1798:  /* *avx2_gathersiv2df */
    case 1799:  /* *avx2_gathersiv4di */
    case 1800:  /* *avx2_gathersiv4di */
    case 1801:  /* *avx2_gathersiv4df */
    case 1802:  /* *avx2_gathersiv4df */
    case 1803:  /* *avx2_gathersiv4si */
    case 1804:  /* *avx2_gathersiv4si */
    case 1805:  /* *avx2_gathersiv4sf */
    case 1806:  /* *avx2_gathersiv4sf */
    case 1807:  /* *avx2_gathersiv8si */
    case 1808:  /* *avx2_gathersiv8si */
    case 1809:  /* *avx2_gathersiv8sf */
    case 1810:  /* *avx2_gathersiv8sf */
    case 1811:  /* *avx2_gathersiv2di_2 */
    case 1812:  /* *avx2_gathersiv2di_2 */
    case 1813:  /* *avx2_gathersiv2df_2 */
    case 1814:  /* *avx2_gathersiv2df_2 */
    case 1815:  /* *avx2_gathersiv4di_2 */
    case 1816:  /* *avx2_gathersiv4di_2 */
    case 1817:  /* *avx2_gathersiv4df_2 */
    case 1818:  /* *avx2_gathersiv4df_2 */
    case 1819:  /* *avx2_gathersiv4si_2 */
    case 1820:  /* *avx2_gathersiv4si_2 */
    case 1821:  /* *avx2_gathersiv4sf_2 */
    case 1822:  /* *avx2_gathersiv4sf_2 */
    case 1823:  /* *avx2_gathersiv8si_2 */
    case 1824:  /* *avx2_gathersiv8si_2 */
    case 1825:  /* *avx2_gathersiv8sf_2 */
    case 1826:  /* *avx2_gathersiv8sf_2 */
    case 1827:  /* *avx2_gatherdiv2di */
    case 1828:  /* *avx2_gatherdiv2di */
    case 1829:  /* *avx2_gatherdiv2df */
    case 1830:  /* *avx2_gatherdiv2df */
    case 1831:  /* *avx2_gatherdiv4di */
    case 1832:  /* *avx2_gatherdiv4di */
    case 1833:  /* *avx2_gatherdiv4df */
    case 1834:  /* *avx2_gatherdiv4df */
    case 1835:  /* *avx2_gatherdiv4si */
    case 1836:  /* *avx2_gatherdiv4si */
    case 1837:  /* *avx2_gatherdiv4sf */
    case 1838:  /* *avx2_gatherdiv4sf */
    case 1839:  /* *avx2_gatherdiv8si */
    case 1840:  /* *avx2_gatherdiv8si */
    case 1841:  /* *avx2_gatherdiv8sf */
    case 1842:  /* *avx2_gatherdiv8sf */
    case 1843:  /* *avx2_gatherdiv2di_2 */
    case 1844:  /* *avx2_gatherdiv2di_2 */
    case 1845:  /* *avx2_gatherdiv2df_2 */
    case 1846:  /* *avx2_gatherdiv2df_2 */
    case 1847:  /* *avx2_gatherdiv4di_2 */
    case 1848:  /* *avx2_gatherdiv4di_2 */
    case 1849:  /* *avx2_gatherdiv4df_2 */
    case 1850:  /* *avx2_gatherdiv4df_2 */
    case 1851:  /* *avx2_gatherdiv4si_2 */
    case 1852:  /* *avx2_gatherdiv4si_2 */
    case 1853:  /* *avx2_gatherdiv4sf_2 */
    case 1854:  /* *avx2_gatherdiv4sf_2 */
    case 1855:  /* *avx2_gatherdiv8si_2 */
    case 1856:  /* *avx2_gatherdiv8si_2 */
    case 1857:  /* *avx2_gatherdiv8sf_2 */
    case 1858:  /* *avx2_gatherdiv8sf_2 */
    case 1859:  /* *avx2_gatherdiv8si_3 */
    case 1860:  /* *avx2_gatherdiv8si_3 */
    case 1861:  /* *avx2_gatherdiv8sf_3 */
    case 1862:  /* *avx2_gatherdiv8sf_3 */
    case 1863:  /* *avx2_gatherdiv8si_4 */
    case 1864:  /* *avx2_gatherdiv8si_4 */
    case 1865:  /* *avx2_gatherdiv8sf_4 */
    case 1866:  /* *avx2_gatherdiv8sf_4 */
      return PREFIX_VEX;

    default:
      return PREFIX_ORIG;

    }
}

int
get_attr_prefix_extra (rtx insn ATTRIBUTE_UNUSED)
{
  enum attr_type cached_type ATTRIBUTE_UNUSED;

  switch (recog_memoized (insn))
    {
    case 1440:  /* *vec_concatv2si_sse4_1 */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 1421:  /* sse4_1_pinsrq */
      extract_constrain_insn_cached (insn);
      if ((! (
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX))) && ((V2DImode) == (V8HImode)))
        {
	  return 0;
        }
      else
        {
	  return 1;
        }

    case 1420:  /* sse4_1_pinsrd */
      extract_constrain_insn_cached (insn);
      if ((! (
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX))) && ((V4SImode) == (V8HImode)))
        {
	  return 0;
        }
      else
        {
	  return 1;
        }

    case 1419:  /* sse2_pinsrw */
      extract_constrain_insn_cached (insn);
      if ((! (
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX))) && ((V8HImode) == (V8HImode)))
        {
	  return 0;
        }
      else
        {
	  return 1;
        }

    case 1418:  /* sse4_1_pinsrb */
      extract_constrain_insn_cached (insn);
      if ((! (
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX))) && ((V16QImode) == (V8HImode)))
        {
	  return 0;
        }
      else
        {
	  return 1;
        }

    case 1788:  /* avx_vec_concatv4df */
    case 1787:  /* avx_vec_concatv8sf */
    case 1786:  /* avx_vec_concatv4di */
    case 1785:  /* avx_vec_concatv8si */
    case 1784:  /* avx_vec_concatv16hi */
    case 1783:  /* avx_vec_concatv32qi */
    case 1349:  /* *sse4_1_uminv4si3 */
    case 1348:  /* *sse4_1_umaxv4si3 */
    case 1347:  /* *sse4_1_uminv8hi3 */
    case 1346:  /* *sse4_1_umaxv8hi3 */
    case 1343:  /* *sse4_1_sminv4si3 */
    case 1342:  /* *sse4_1_smaxv4si3 */
    case 1341:  /* *sse4_1_sminv16qi3 */
    case 1340:  /* *sse4_1_smaxv16qi3 */
    case 1228:  /* *sse4_1_extractps */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 1224:  /* vec_setv4sf_0 */
    case 1223:  /* vec_setv4si_0 */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3f))
        {
	  return 0;
        }
      else if (((1 << which_alternative) & 0xc0))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 1220:  /* *vec_concatv2sf_sse4_1 */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return 0;
        }
      else if (((1 << which_alternative) & 0xc))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 1438:  /* *vec_dupv4si */
    case 1219:  /* vec_dupv4sf */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return 0;
        }
      else if (which_alternative == 1)
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 939:  /* *mmx_uavgv8qi3 */
      extract_constrain_insn_cached (insn);
      if ((! (
#line 1589 "../../gcc-4.8.1/gcc/config/i386/mmx.md"
(TARGET_SSE))) && (! (
#line 1590 "../../gcc-4.8.1/gcc/config/i386/mmx.md"
(TARGET_3DNOW_A))))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 1351:  /* *uminv16qi3 */
    case 1350:  /* *umaxv16qi3 */
    case 1345:  /* *sminv8hi3 */
    case 1344:  /* *smaxv8hi3 */
    case 606:  /* *bswapsi2_movbe */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return 0;
        }
      else
        {
	  return 1;
        }

    case 1681:  /* xop_vpermil2v2df3 */
    case 1680:  /* xop_vpermil2v4df3 */
    case 1679:  /* xop_vpermil2v4sf3 */
    case 1678:  /* xop_vpermil2v8sf3 */
    case 1633:  /* xop_pperm_pack_v8hi_v16qi */
    case 1632:  /* xop_pperm_pack_v4si_v8hi */
    case 1631:  /* xop_pperm_pack_v2di_v4si */
    case 1630:  /* xop_pperm */
    case 1614:  /* xop_pcmov_v2df */
    case 1613:  /* xop_pcmov_v4df256 */
    case 1612:  /* xop_pcmov_v4sf */
    case 1611:  /* xop_pcmov_v8sf256 */
    case 1610:  /* xop_pcmov_v2di */
    case 1609:  /* xop_pcmov_v4di256 */
    case 1608:  /* xop_pcmov_v4si */
    case 1607:  /* xop_pcmov_v8si256 */
    case 1606:  /* xop_pcmov_v8hi */
    case 1605:  /* xop_pcmov_v16hi256 */
    case 1604:  /* xop_pcmov_v16qi */
    case 1603:  /* xop_pcmov_v32qi256 */
    case 1602:  /* xop_pmadcsswd */
    case 1601:  /* xop_pmadcswd */
    case 1600:  /* xop_pmacsswd */
    case 1599:  /* xop_pmacswd */
    case 1598:  /* xop_pmacssdqh */
    case 1597:  /* xop_pmacsdqh */
    case 1596:  /* xop_pmacssdql */
    case 1595:  /* xop_pmacsdql */
    case 1594:  /* xop_pmacssdd */
    case 1593:  /* xop_pmacsdd */
    case 1592:  /* xop_pmacssww */
    case 1591:  /* xop_pmacsww */
    case 1161:  /* *fma4i_vmfnmsub_v2df */
    case 1160:  /* *fma4i_vmfnmsub_v4sf */
    case 1159:  /* *fma4i_vmfnmadd_v2df */
    case 1158:  /* *fma4i_vmfnmadd_v4sf */
    case 1157:  /* *fma4i_vmfmsub_v2df */
    case 1156:  /* *fma4i_vmfmsub_v4sf */
    case 1155:  /* *fma4i_vmfmadd_v2df */
    case 1154:  /* *fma4i_vmfmadd_v4sf */
    case 1153:  /* *fmai_fnmsub_v2df */
    case 1152:  /* *fmai_fnmsub_v4sf */
    case 1151:  /* *fmai_fnmadd_v2df */
    case 1150:  /* *fmai_fnmadd_v4sf */
    case 1149:  /* *fmai_fmsub_v2df */
    case 1148:  /* *fmai_fmsub_v4sf */
    case 1147:  /* *fmai_fmadd_v2df */
    case 1146:  /* *fmai_fmadd_v4sf */
    case 1145:  /* *fma_fmsubadd_v2df */
    case 1144:  /* *fma_fmsubadd_v4df */
    case 1143:  /* *fma_fmsubadd_v4sf */
    case 1142:  /* *fma_fmsubadd_v8sf */
    case 1141:  /* *fma_fmaddsub_v2df */
    case 1140:  /* *fma_fmaddsub_v4df */
    case 1139:  /* *fma_fmaddsub_v4sf */
    case 1138:  /* *fma_fmaddsub_v8sf */
    case 1137:  /* *fma_fnmsub_v4df */
    case 1136:  /* *fma_fnmsub_v8sf */
    case 1135:  /* *fma_fnmsub_v2df */
    case 1134:  /* *fma_fnmsub_v4sf */
    case 1133:  /* *fma_fnmsub_df */
    case 1132:  /* *fma_fnmsub_sf */
    case 1131:  /* *fma_fnmadd_v4df */
    case 1130:  /* *fma_fnmadd_v8sf */
    case 1129:  /* *fma_fnmadd_v2df */
    case 1128:  /* *fma_fnmadd_v4sf */
    case 1127:  /* *fma_fnmadd_df */
    case 1126:  /* *fma_fnmadd_sf */
    case 1125:  /* *fma_fmsub_v4df */
    case 1124:  /* *fma_fmsub_v8sf */
    case 1123:  /* *fma_fmsub_v2df */
    case 1122:  /* *fma_fmsub_v4sf */
    case 1121:  /* *fma_fmsub_df */
    case 1120:  /* *fma_fmsub_sf */
    case 1119:  /* *fma_fmadd_v4df */
    case 1118:  /* *fma_fmadd_v8sf */
    case 1117:  /* *fma_fmadd_v2df */
    case 1116:  /* *fma_fmadd_v4sf */
    case 1115:  /* *fma_fmadd_df */
    case 1114:  /* *fma_fmadd_sf */
    case 780:  /* *xop_pcmov_df */
    case 779:  /* *xop_pcmov_sf */
    case 1642:  /* xop_vrotlv16qi3 */
    case 1643:  /* xop_vrotlv8hi3 */
    case 1644:  /* xop_vrotlv4si3 */
    case 1645:  /* xop_vrotlv2di3 */
    case 1646:  /* xop_shav16qi3 */
    case 1647:  /* xop_shav8hi3 */
    case 1648:  /* xop_shav4si3 */
    case 1649:  /* xop_shav2di3 */
    case 1650:  /* xop_shlv16qi3 */
    case 1651:  /* xop_shlv8hi3 */
    case 1652:  /* xop_shlv4si3 */
    case 1653:  /* xop_shlv2di3 */
    case 1662:  /* xop_maskcmpv16qi3 */
    case 1663:  /* xop_maskcmpv8hi3 */
    case 1664:  /* xop_maskcmpv4si3 */
    case 1665:  /* xop_maskcmpv2di3 */
    case 1666:  /* xop_maskcmp_unsv16qi3 */
    case 1667:  /* xop_maskcmp_unsv8hi3 */
    case 1668:  /* xop_maskcmp_unsv4si3 */
    case 1669:  /* xop_maskcmp_unsv2di3 */
    case 1670:  /* xop_maskcmp_uns2v16qi3 */
    case 1671:  /* xop_maskcmp_uns2v8hi3 */
    case 1672:  /* xop_maskcmp_uns2v4si3 */
    case 1673:  /* xop_maskcmp_uns2v2di3 */
    case 1674:  /* xop_pcom_tfv16qi3 */
    case 1675:  /* xop_pcom_tfv8hi3 */
    case 1676:  /* xop_pcom_tfv4si3 */
    case 1677:  /* xop_pcom_tfv2di3 */
      return 2;

    case 1661:  /* *xop_vmfrcz_v2df */
    case 1660:  /* *xop_vmfrcz_v4sf */
    case 1659:  /* xop_frczv4df2 */
    case 1658:  /* xop_frczv8sf2 */
    case 1657:  /* xop_frczv2df2 */
    case 1656:  /* xop_frczv4sf2 */
    case 1655:  /* xop_frczdf2 */
    case 1654:  /* xop_frczsf2 */
    case 1629:  /* xop_phsubdq */
    case 1628:  /* xop_phsubwd */
    case 1627:  /* xop_phsubbw */
    case 1626:  /* xop_phaddudq */
    case 1625:  /* xop_phadddq */
    case 1624:  /* xop_phadduwq */
    case 1623:  /* xop_phaddwq */
    case 1622:  /* xop_phadduwd */
    case 1621:  /* xop_phaddwd */
    case 1620:  /* xop_phaddubq */
    case 1619:  /* xop_phaddbq */
    case 1618:  /* xop_phaddubd */
    case 1617:  /* xop_phaddbd */
    case 1616:  /* xop_phaddubw */
    case 1615:  /* xop_phaddbw */
    case 699:  /* sse4_1_roundsf2 */
    case 700:  /* sse4_1_rounddf2 */
    case 810:  /* sse4_2_crc32qi */
    case 811:  /* sse4_2_crc32hi */
    case 812:  /* sse4_2_crc32si */
    case 827:  /* rdrandhi_1 */
    case 828:  /* rdrandsi_1 */
    case 829:  /* rdseedhi_1 */
    case 830:  /* rdseedsi_1 */
    case 842:  /* *mmx_addv2sf3 */
    case 843:  /* *mmx_subv2sf3 */
    case 844:  /* *mmx_mulv2sf3 */
    case 845:  /* *mmx_smaxv2sf3_finite */
    case 846:  /* *mmx_sminv2sf3_finite */
    case 847:  /* *mmx_smaxv2sf3 */
    case 848:  /* *mmx_sminv2sf3 */
    case 849:  /* mmx_rcpv2sf2 */
    case 850:  /* mmx_rcpit1v2sf3 */
    case 851:  /* mmx_rcpit2v2sf3 */
    case 852:  /* mmx_rsqrtv2sf2 */
    case 853:  /* mmx_rsqit1v2sf3 */
    case 854:  /* mmx_haddv2sf3 */
    case 855:  /* mmx_hsubv2sf3 */
    case 856:  /* mmx_addsubv2sf3 */
    case 857:  /* *mmx_eqv2sf3 */
    case 858:  /* mmx_gtv2sf3 */
    case 859:  /* mmx_gev2sf3 */
    case 860:  /* mmx_pf2id */
    case 861:  /* mmx_pf2iw */
    case 862:  /* mmx_pi2fw */
    case 863:  /* mmx_floatv2si2 */
    case 864:  /* mmx_pswapdv2sf2 */
    case 889:  /* *mmx_pmulhrwv4hi3 */
    case 933:  /* mmx_pswapdv2si2 */
    case 1225:  /* *vec_setv4sf_sse4_1 */
    case 1226:  /* sse4_1_insertps */
    case 1232:  /* vec_extract_hi_v4di */
    case 1233:  /* vec_extract_hi_v4df */
    case 1236:  /* vec_extract_hi_v8si */
    case 1237:  /* vec_extract_hi_v8sf */
    case 1239:  /* vec_extract_hi_v16hi */
    case 1241:  /* vec_extract_hi_v32qi */
    case 1302:  /* *vec_widen_smult_even_v8si */
    case 1303:  /* *sse4_1_mulv2siv2di3 */
    case 1306:  /* *avx2_mulv8si3 */
    case 1307:  /* *sse4_1_mulv4si3 */
    case 1328:  /* *avx2_smaxv32qi3 */
    case 1329:  /* *avx2_sminv32qi3 */
    case 1330:  /* *avx2_umaxv32qi3 */
    case 1331:  /* *avx2_uminv32qi3 */
    case 1332:  /* *avx2_smaxv16hi3 */
    case 1333:  /* *avx2_sminv16hi3 */
    case 1334:  /* *avx2_umaxv16hi3 */
    case 1335:  /* *avx2_uminv16hi3 */
    case 1336:  /* *avx2_smaxv8si3 */
    case 1337:  /* *avx2_sminv8si3 */
    case 1338:  /* *avx2_umaxv8si3 */
    case 1339:  /* *avx2_uminv8si3 */
    case 1352:  /* *avx2_eqv32qi3 */
    case 1353:  /* *avx2_eqv16hi3 */
    case 1354:  /* *avx2_eqv8si3 */
    case 1355:  /* *avx2_eqv4di3 */
    case 1356:  /* *sse4_1_eqv2di3 */
    case 1360:  /* sse4_2_gtv2di3 */
    case 1361:  /* avx2_gtv32qi3 */
    case 1362:  /* avx2_gtv16hi3 */
    case 1363:  /* avx2_gtv8si3 */
    case 1364:  /* avx2_gtv4di3 */
    case 1422:  /* *sse4_1_pextrb_si */
    case 1423:  /* *sse4_1_pextrb_memory */
    case 1425:  /* *sse4_1_pextrw_memory */
    case 1426:  /* *sse4_1_pextrd */
    case 1464:  /* avx2_phaddwv16hi3 */
    case 1465:  /* avx2_phaddswv16hi3 */
    case 1466:  /* avx2_phsubwv16hi3 */
    case 1467:  /* avx2_phsubswv16hi3 */
    case 1468:  /* ssse3_phaddwv8hi3 */
    case 1469:  /* ssse3_phaddswv8hi3 */
    case 1470:  /* ssse3_phsubwv8hi3 */
    case 1471:  /* ssse3_phsubswv8hi3 */
    case 1472:  /* ssse3_phaddwv4hi3 */
    case 1473:  /* ssse3_phaddswv4hi3 */
    case 1474:  /* ssse3_phsubwv4hi3 */
    case 1475:  /* ssse3_phsubswv4hi3 */
    case 1476:  /* avx2_phadddv8si3 */
    case 1477:  /* avx2_phsubdv8si3 */
    case 1478:  /* ssse3_phadddv4si3 */
    case 1479:  /* ssse3_phsubdv4si3 */
    case 1480:  /* ssse3_phadddv2si3 */
    case 1481:  /* ssse3_phsubdv2si3 */
    case 1482:  /* avx2_pmaddubsw256 */
    case 1483:  /* ssse3_pmaddubsw128 */
    case 1484:  /* ssse3_pmaddubsw */
    case 1485:  /* *avx2_pmulhrswv16hi3 */
    case 1486:  /* *ssse3_pmulhrswv8hi3 */
    case 1487:  /* *ssse3_pmulhrswv4hi3 */
    case 1488:  /* avx2_pshufbv32qi3 */
    case 1489:  /* ssse3_pshufbv16qi3 */
    case 1490:  /* ssse3_pshufbv8qi3 */
    case 1491:  /* avx2_psignv32qi3 */
    case 1492:  /* ssse3_psignv16qi3 */
    case 1493:  /* avx2_psignv16hi3 */
    case 1494:  /* ssse3_psignv8hi3 */
    case 1495:  /* avx2_psignv8si3 */
    case 1496:  /* ssse3_psignv4si3 */
    case 1497:  /* ssse3_psignv8qi3 */
    case 1498:  /* ssse3_psignv4hi3 */
    case 1499:  /* ssse3_psignv2si3 */
    case 1500:  /* avx2_palignrv2ti */
    case 1501:  /* ssse3_palignrti */
    case 1502:  /* ssse3_palignrdi */
    case 1503:  /* absv32qi2 */
    case 1504:  /* absv16qi2 */
    case 1505:  /* absv16hi2 */
    case 1506:  /* absv8hi2 */
    case 1507:  /* absv8si2 */
    case 1508:  /* absv4si2 */
    case 1509:  /* absv8qi2 */
    case 1510:  /* absv4hi2 */
    case 1511:  /* absv2si2 */
    case 1520:  /* avx_blendps256 */
    case 1521:  /* sse4_1_blendps */
    case 1522:  /* avx_blendpd256 */
    case 1523:  /* sse4_1_blendpd */
    case 1524:  /* avx_blendvps256 */
    case 1525:  /* sse4_1_blendvps */
    case 1526:  /* avx_blendvpd256 */
    case 1527:  /* sse4_1_blendvpd */
    case 1528:  /* avx_dpps256 */
    case 1529:  /* sse4_1_dpps */
    case 1530:  /* avx_dppd256 */
    case 1531:  /* sse4_1_dppd */
    case 1532:  /* avx2_movntdqa */
    case 1533:  /* sse4_1_movntdqa */
    case 1534:  /* avx2_mpsadbw */
    case 1535:  /* sse4_1_mpsadbw */
    case 1536:  /* avx2_packusdw */
    case 1537:  /* sse4_1_packusdw */
    case 1538:  /* avx2_pblendvb */
    case 1539:  /* sse4_1_pblendvb */
    case 1540:  /* sse4_1_pblendw */
    case 1541:  /* *avx2_pblendw */
    case 1542:  /* avx2_pblenddv8si */
    case 1543:  /* avx2_pblenddv4si */
    case 1544:  /* sse4_1_phminposuw */
    case 1545:  /* avx2_sign_extendv16qiv16hi2 */
    case 1546:  /* avx2_zero_extendv16qiv16hi2 */
    case 1547:  /* sse4_1_sign_extendv8qiv8hi2 */
    case 1548:  /* sse4_1_zero_extendv8qiv8hi2 */
    case 1549:  /* avx2_sign_extendv8qiv8si2 */
    case 1550:  /* avx2_zero_extendv8qiv8si2 */
    case 1551:  /* sse4_1_sign_extendv4qiv4si2 */
    case 1552:  /* sse4_1_zero_extendv4qiv4si2 */
    case 1553:  /* avx2_sign_extendv8hiv8si2 */
    case 1554:  /* avx2_zero_extendv8hiv8si2 */
    case 1555:  /* sse4_1_sign_extendv4hiv4si2 */
    case 1556:  /* sse4_1_zero_extendv4hiv4si2 */
    case 1557:  /* avx2_sign_extendv4qiv4di2 */
    case 1558:  /* avx2_zero_extendv4qiv4di2 */
    case 1559:  /* sse4_1_sign_extendv2qiv2di2 */
    case 1560:  /* sse4_1_zero_extendv2qiv2di2 */
    case 1561:  /* avx2_sign_extendv4hiv4di2 */
    case 1562:  /* avx2_zero_extendv4hiv4di2 */
    case 1563:  /* sse4_1_sign_extendv2hiv2di2 */
    case 1564:  /* sse4_1_zero_extendv2hiv2di2 */
    case 1565:  /* avx2_sign_extendv4siv4di2 */
    case 1566:  /* avx2_zero_extendv4siv4di2 */
    case 1567:  /* sse4_1_sign_extendv2siv2di2 */
    case 1568:  /* sse4_1_zero_extendv2siv2di2 */
    case 1569:  /* avx_vtestps256 */
    case 1570:  /* avx_vtestps */
    case 1571:  /* avx_vtestpd256 */
    case 1572:  /* avx_vtestpd */
    case 1573:  /* avx_ptest256 */
    case 1574:  /* sse4_1_ptest */
    case 1575:  /* avx_roundps256 */
    case 1576:  /* sse4_1_roundps */
    case 1577:  /* avx_roundpd256 */
    case 1578:  /* sse4_1_roundpd */
    case 1579:  /* sse4_1_roundss */
    case 1580:  /* sse4_1_roundsd */
    case 1581:  /* sse4_2_pcmpestr */
    case 1582:  /* *sse4_2_pcmpestr_unaligned */
    case 1583:  /* sse4_2_pcmpestri */
    case 1584:  /* sse4_2_pcmpestrm */
    case 1585:  /* sse4_2_pcmpestr_cconly */
    case 1586:  /* sse4_2_pcmpistr */
    case 1587:  /* *sse4_2_pcmpistr_unaligned */
    case 1588:  /* sse4_2_pcmpistri */
    case 1589:  /* sse4_2_pcmpistrm */
    case 1590:  /* sse4_2_pcmpistr_cconly */
    case 1682:  /* aesenc */
    case 1683:  /* aesenclast */
    case 1684:  /* aesdec */
    case 1685:  /* aesdeclast */
    case 1686:  /* aesimc */
    case 1687:  /* aeskeygenassist */
    case 1688:  /* pclmulqdq */
    case 1691:  /* avx2_pbroadcastv32qi */
    case 1692:  /* avx2_pbroadcastv16qi */
    case 1693:  /* avx2_pbroadcastv16hi */
    case 1694:  /* avx2_pbroadcastv8hi */
    case 1695:  /* avx2_pbroadcastv8si */
    case 1696:  /* avx2_pbroadcastv4si */
    case 1697:  /* avx2_pbroadcastv4di */
    case 1698:  /* avx2_pbroadcastv2di */
    case 1699:  /* avx2_pbroadcastv32qi_1 */
    case 1700:  /* avx2_pbroadcastv16hi_1 */
    case 1701:  /* avx2_pbroadcastv8si_1 */
    case 1702:  /* avx2_pbroadcastv4di_1 */
    case 1709:  /* vec_dupv8si */
    case 1710:  /* vec_dupv8sf */
    case 1711:  /* vec_dupv4di */
    case 1712:  /* vec_dupv4df */
    case 1713:  /* avx2_vbroadcasti128_v32qi */
    case 1714:  /* avx2_vbroadcasti128_v16hi */
    case 1715:  /* avx2_vbroadcasti128_v8si */
    case 1716:  /* avx2_vbroadcasti128_v4di */
    case 1717:  /* avx_vbroadcastf128_v32qi */
    case 1718:  /* avx_vbroadcastf128_v16hi */
    case 1719:  /* avx_vbroadcastf128_v8si */
    case 1720:  /* avx_vbroadcastf128_v4di */
    case 1721:  /* avx_vbroadcastf128_v8sf */
    case 1722:  /* avx_vbroadcastf128_v4df */
    case 1723:  /* *avx_vperm_broadcast_v4sf */
    case 1726:  /* *avx_vpermilpv8sf */
    case 1727:  /* *avx_vpermilpv4sf */
    case 1728:  /* *avx_vpermilpv4df */
    case 1729:  /* *avx_vpermilpv2df */
    case 1730:  /* avx_vpermilvarv8sf3 */
    case 1731:  /* avx_vpermilvarv4sf3 */
    case 1732:  /* avx_vpermilvarv4df3 */
    case 1733:  /* avx_vpermilvarv2df3 */
    case 1734:  /* *avx_vperm2f128v8si_full */
    case 1735:  /* *avx_vperm2f128v8sf_full */
    case 1736:  /* *avx_vperm2f128v4df_full */
    case 1737:  /* *avx_vperm2f128v8si_nozero */
    case 1738:  /* *avx_vperm2f128v8sf_nozero */
    case 1739:  /* *avx_vperm2f128v4df_nozero */
    case 1740:  /* avx2_vec_set_lo_v4di */
    case 1741:  /* avx2_vec_set_hi_v4di */
    case 1742:  /* vec_set_lo_v4di */
    case 1743:  /* vec_set_lo_v4df */
    case 1744:  /* vec_set_hi_v4di */
    case 1745:  /* vec_set_hi_v4df */
    case 1746:  /* vec_set_lo_v8si */
    case 1747:  /* vec_set_lo_v8sf */
    case 1748:  /* vec_set_hi_v8si */
    case 1749:  /* vec_set_hi_v8sf */
    case 1750:  /* vec_set_lo_v16hi */
    case 1751:  /* vec_set_hi_v16hi */
    case 1752:  /* vec_set_lo_v32qi */
    case 1753:  /* vec_set_hi_v32qi */
    case 1754:  /* avx_maskloadps */
    case 1755:  /* avx_maskloadpd */
    case 1756:  /* avx_maskloadps256 */
    case 1757:  /* avx_maskloadpd256 */
    case 1758:  /* avx2_maskloadd */
    case 1759:  /* avx2_maskloadq */
    case 1760:  /* avx2_maskloadd256 */
    case 1761:  /* avx2_maskloadq256 */
    case 1762:  /* avx_maskstoreps */
    case 1763:  /* avx_maskstorepd */
    case 1764:  /* avx_maskstoreps256 */
    case 1765:  /* avx_maskstorepd256 */
    case 1766:  /* avx2_maskstored */
    case 1767:  /* avx2_maskstoreq */
    case 1768:  /* avx2_maskstored256 */
    case 1769:  /* avx2_maskstoreq256 */
      return 1;

    case -1:
      if (GET_CODE (PATTERN (insn)) != ASM_INPUT
          && asm_noperands (PATTERN (insn)) < 0)
        fatal_insn_not_found (insn);
      if (((cached_type = get_attr_type (insn)) == TYPE_SSEMULADD) || (cached_type == TYPE_SSE4ARG))
        {
	  return 2;
        }
      else if ((cached_type == TYPE_SSEIADD1) || (cached_type == TYPE_SSECVT1))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    default:
      return 0;

    }
}

int
get_attr_prefix_rex (rtx insn ATTRIBUTE_UNUSED)
{
  enum attr_mode cached_mode ATTRIBUTE_UNUSED;

  switch (recog_memoized (insn))
    {
    case 1421:  /* sse4_1_pinsrq */
      extract_constrain_insn_cached (insn);
      if ((! (
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX))) && ((V2DImode) == (V2DImode)))
        {
	  return 1;
        }
      else
        {
	  if (! (
#line 435 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_64BIT)))
	    {
	      return 0;
	    }
	  else if (
#line 444 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(x86_extended_reg_mentioned_p (insn)))
	    {
	      return 1;
	    }
	  else
	    {
	      return 0;
	    }
        }

    case 1420:  /* sse4_1_pinsrd */
      extract_constrain_insn_cached (insn);
      if ((! (
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX))) && ((V4SImode) == (V2DImode)))
        {
	  return 1;
        }
      else
        {
	  if (! (
#line 435 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_64BIT)))
	    {
	      return 0;
	    }
	  else if (
#line 444 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(x86_extended_reg_mentioned_p (insn)))
	    {
	      return 1;
	    }
	  else
	    {
	      return 0;
	    }
        }

    case 1419:  /* sse2_pinsrw */
      extract_constrain_insn_cached (insn);
      if ((! (
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX))) && ((V8HImode) == (V2DImode)))
        {
	  return 1;
        }
      else
        {
	  if (! (
#line 435 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_64BIT)))
	    {
	      return 0;
	    }
	  else if (
#line 444 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(x86_extended_reg_mentioned_p (insn)))
	    {
	      return 1;
	    }
	  else
	    {
	      return 0;
	    }
        }

    case 1418:  /* sse4_1_pinsrb */
      extract_constrain_insn_cached (insn);
      if ((! (
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX))) && ((V16QImode) == (V2DImode)))
        {
	  return 1;
        }
      else
        {
	  if (! (
#line 435 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_64BIT)))
	    {
	      return 0;
	    }
	  else if (
#line 444 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(x86_extended_reg_mentioned_p (insn)))
	    {
	      return 1;
	    }
	  else
	    {
	      return 0;
	    }
        }

    case 840:  /* *movv2sf_internal */
      extract_constrain_insn_cached (insn);
      if (! (
#line 435 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_64BIT)))
        {
	  return 0;
        }
      else if ((!((1 << which_alternative) & 0x3ff)) || (
#line 444 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(x86_extended_reg_mentioned_p (insn))))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 839:  /* *movv1di_internal */
    case 838:  /* *movv2si_internal */
    case 837:  /* *movv4hi_internal */
    case 836:  /* *movv8qi_internal */
      extract_constrain_insn_cached (insn);
      if (! (
#line 435 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_64BIT)))
        {
	  return 0;
        }
      else if ((!((1 << which_alternative) & 0x1e7f)) || (
#line 444 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(x86_extended_reg_mentioned_p (insn))))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 812:  /* sse4_2_crc32si */
    case 811:  /* sse4_2_crc32hi */
    case 810:  /* sse4_2_crc32qi */
      extract_constrain_insn_cached (insn);
      if (ext_QIreg_operand (operands[2], QImode))
        {
	  return 1;
        }
      else
        {
	  if (! (
#line 435 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_64BIT)))
	    {
	      return 0;
	    }
	  else if (
#line 444 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(x86_extended_reg_mentioned_p (insn)))
	    {
	      return 1;
	    }
	  else
	    {
	      return 0;
	    }
        }

    case 777:  /* *movdfcc_1 */
      extract_constrain_insn_cached (insn);
      if (! (
#line 435 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_64BIT)))
        {
	  return 0;
        }
      else if ((!((1 << which_alternative) & 0x3)) || (
#line 444 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(x86_extended_reg_mentioned_p (insn))))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 769:  /* *strlenqi_1 */
    case 767:  /* *cmpstrnqi_1 */
    case 765:  /* *cmpstrnqi_nz_1 */
    case 763:  /* *rep_stosqi */
    case 759:  /* *strsetqi_1 */
    case 749:  /* *strmovqi_1 */
      extract_constrain_insn_cached (insn);
      if (
#line 15990 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(DImode == DImode))
        {
	  return 0;
        }
      else
        {
	  if (! (
#line 435 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_64BIT)))
	    {
	      return 0;
	    }
	  else if ((
#line 442 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(x86_extended_QIreg_mentioned_p (insn))) || (
#line 444 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(x86_extended_reg_mentioned_p (insn))))
	    {
	      return 1;
	    }
	  else
	    {
	      return 0;
	    }
        }

    case 768:  /* *strlenqi_1 */
    case 766:  /* *cmpstrnqi_1 */
    case 764:  /* *cmpstrnqi_nz_1 */
    case 762:  /* *rep_stosqi */
    case 758:  /* *strsetqi_1 */
    case 748:  /* *strmovqi_1 */
      extract_constrain_insn_cached (insn);
      if (
#line 15990 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(SImode == DImode))
        {
	  return 0;
        }
      else
        {
	  if (! (
#line 435 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_64BIT)))
	    {
	      return 0;
	    }
	  else if ((
#line 442 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(x86_extended_QIreg_mentioned_p (insn))) || (
#line 444 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(x86_extended_reg_mentioned_p (insn))))
	    {
	      return 1;
	    }
	  else
	    {
	      return 0;
	    }
        }

    case 449:  /* ashrsi3_cvt */
      extract_constrain_insn_cached (insn);
      if (! (
#line 435 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_64BIT)))
        {
	  return 0;
        }
      else if ((
#line 444 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(x86_extended_reg_mentioned_p (insn))) || ((which_alternative == 0) && (ext_QIreg_operand (operands[1], QImode))))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 608:  /* *bswaphi_lowpart_1 */
    case 432:  /* *ashlqi3_1 */
    case 419:  /* *one_cmplqi2_1 */
      extract_constrain_insn_cached (insn);
      if (! (
#line 435 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_64BIT)))
        {
	  return 0;
        }
      else if (((which_alternative == 0) && (
#line 442 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(x86_extended_QIreg_mentioned_p (insn)))) || (
#line 444 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(x86_extended_reg_mentioned_p (insn))))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 352:  /* *xorqi_1 */
    case 351:  /* *iorqi_1 */
    case 336:  /* *andqi_2_maybe_si */
    case 334:  /* *andqi_1 */
      extract_constrain_insn_cached (insn);
      if (! (
#line 435 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_64BIT)))
        {
	  return 0;
        }
      else if (((((1 << which_alternative) & 0x3)) && (
#line 442 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(x86_extended_QIreg_mentioned_p (insn)))) || (
#line 444 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(x86_extended_reg_mentioned_p (insn))))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 262:  /* *lea_general_4 */
    case 261:  /* *lea_general_4 */
      extract_constrain_insn_cached (insn);
      if (! (
#line 435 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_64BIT)))
        {
	  return 0;
        }
      else if ((GET_MODE (operands[0]) == DImode) || (
#line 444 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(x86_extended_reg_mentioned_p (insn))))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 324:  /* *testqi_1_maybe_si */
    case 239:  /* *addqi_1 */
      extract_constrain_insn_cached (insn);
      if (! (
#line 435 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_64BIT)))
        {
	  return 0;
        }
      else if (((((1 << which_alternative) & 0x7)) && (
#line 442 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(x86_extended_QIreg_mentioned_p (insn)))) || (
#line 444 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(x86_extended_reg_mentioned_p (insn))))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 211:  /* *floatdidf2_sse_nointerunit */
    case 209:  /* *floatdisf2_sse_nointerunit */
    case 207:  /* *floatdidf2_sse_interunit */
    case 205:  /* *floatdisf2_sse_interunit */
      extract_constrain_insn_cached (insn);
      if (
#line 15990 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(DImode == DImode))
        {
	  return 1;
        }
      else
        {
	  if (! (
#line 435 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_64BIT)))
	    {
	      return 0;
	    }
	  else if (
#line 444 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(x86_extended_reg_mentioned_p (insn)))
	    {
	      return 1;
	    }
	  else
	    {
	      return 0;
	    }
        }

    case 197:  /* *floatdidf2_mixed_nointerunit */
    case 195:  /* *floatdisf2_mixed_nointerunit */
      extract_constrain_insn_cached (insn);
      if ((which_alternative == 1) && (
#line 15990 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(DImode == DImode)))
        {
	  return 1;
        }
      else
        {
	  if (! (
#line 435 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_64BIT)))
	    {
	      return 0;
	    }
	  else if (
#line 444 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(x86_extended_reg_mentioned_p (insn)))
	    {
	      return 1;
	    }
	  else
	    {
	      return 0;
	    }
        }

    case 196:  /* *floatsidf2_mixed_nointerunit */
    case 194:  /* *floatsisf2_mixed_nointerunit */
      extract_constrain_insn_cached (insn);
      if ((which_alternative == 1) && (
#line 15990 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(SImode == DImode)))
        {
	  return 1;
        }
      else
        {
	  if (! (
#line 435 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_64BIT)))
	    {
	      return 0;
	    }
	  else if (
#line 444 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(x86_extended_reg_mentioned_p (insn)))
	    {
	      return 1;
	    }
	  else
	    {
	      return 0;
	    }
        }

    case 193:  /* *floatdidf2_mixed_interunit */
    case 191:  /* *floatdisf2_mixed_interunit */
      extract_constrain_insn_cached (insn);
      if ((which_alternative != 0) && (
#line 15990 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(DImode == DImode)))
        {
	  return 1;
        }
      else
        {
	  if (! (
#line 435 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_64BIT)))
	    {
	      return 0;
	    }
	  else if (
#line 444 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(x86_extended_reg_mentioned_p (insn)))
	    {
	      return 1;
	    }
	  else
	    {
	      return 0;
	    }
        }

    case 192:  /* *floatsidf2_mixed_interunit */
    case 190:  /* *floatsisf2_mixed_interunit */
      extract_constrain_insn_cached (insn);
      if ((which_alternative != 0) && (
#line 15990 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(SImode == DImode)))
        {
	  return 1;
        }
      else
        {
	  if (! (
#line 435 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_64BIT)))
	    {
	      return 0;
	    }
	  else if (
#line 444 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(x86_extended_reg_mentioned_p (insn)))
	    {
	      return 1;
	    }
	  else
	    {
	      return 0;
	    }
        }

    case 210:  /* *floatsidf2_sse_nointerunit */
    case 208:  /* *floatsisf2_sse_nointerunit */
    case 206:  /* *floatsidf2_sse_interunit */
    case 204:  /* *floatsisf2_sse_interunit */
    case 148:  /* fix_truncdfsi_sse */
    case 147:  /* fix_truncsfsi_sse */
      extract_constrain_insn_cached (insn);
      if (
#line 15990 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(SImode == DImode))
        {
	  return 1;
        }
      else
        {
	  if (! (
#line 435 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_64BIT)))
	    {
	      return 0;
	    }
	  else if (
#line 444 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(x86_extended_reg_mentioned_p (insn)))
	    {
	      return 1;
	    }
	  else
	    {
	      return 0;
	    }
        }

    case 108:  /* *pushdf */
      extract_constrain_insn_cached (insn);
      if (! (
#line 435 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_64BIT)))
        {
	  return 0;
        }
      else if ((which_alternative == 1) || (
#line 444 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(x86_extended_reg_mentioned_p (insn))))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 127:  /* extendqihi2 */
    case 126:  /* extendqisi2 */
    case 125:  /* extendhisi2 */
    case 123:  /* *zero_extendqihi2 */
    case 121:  /* *zero_extendhisi2 */
    case 120:  /* *zero_extendqisi2 */
    case 101:  /* *movsi_extzv_1 */
    case 99:  /* *movsi_extv_1 */
    case 98:  /* *movhi_extv_1 */
      extract_constrain_insn_cached (insn);
      if (! (
#line 435 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_64BIT)))
        {
	  return 0;
        }
      else if ((
#line 444 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(x86_extended_reg_mentioned_p (insn))) || (ext_QIreg_operand (operands[1], QImode)))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 79:  /* *movhi_internal */
      extract_constrain_insn_cached (insn);
      if (! (
#line 435 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_64BIT)))
        {
	  return 0;
        }
      else if ((
#line 444 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(x86_extended_reg_mentioned_p (insn))) || ((get_attr_type (insn) == TYPE_IMOVX) && (ext_QIreg_operand (operands[1], QImode))))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 77:  /* *movdi_internal */
      extract_constrain_insn_cached (insn);
      if (! (
#line 435 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_64BIT)))
        {
	  return 0;
        }
      else if ((!((1 << which_alternative) & 0x1ebc)) || (
#line 444 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(x86_extended_reg_mentioned_p (insn))))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 1877:  /* storedi_via_fpu */
    case 1455:  /* avx2_pmovmskb */
    case 824:  /* lwp_slwpcbdi */
    case 822:  /* *lwp_llwpcbdi1 */
    case 792:  /* pro_epilogue_adjust_stack_di_sub */
    case 790:  /* pro_epilogue_adjust_stack_di_add */
    case 728:  /* fistdi2_ceil_with_temp */
    case 727:  /* fistdi2_floor_with_temp */
    case 726:  /* fistdi2_ceil */
    case 725:  /* fistdi2_floor */
    case 724:  /* *fistdi2_ceil_1 */
    case 723:  /* *fistdi2_floor_1 */
    case 704:  /* fistdi2_with_temp */
    case 703:  /* fistdi2 */
    case 702:  /* *fistdi2_1 */
    case 605:  /* *popcountdi2_cmp */
    case 570:  /* set_got_offset_rex64 */
    case 496:  /* *btdi */
    case 488:  /* *rotrdi3_1 */
    case 487:  /* *rotldi3_1 */
    case 481:  /* *rotrdi3_mask */
    case 480:  /* *rotldi3_mask */
    case 477:  /* *ashrdi3_cconly */
    case 476:  /* *lshrdi3_cconly */
    case 469:  /* *ashrdi3_cmp */
    case 468:  /* *lshrdi3_cmp */
    case 455:  /* *ashrdi3_1 */
    case 454:  /* *lshrdi3_1 */
    case 445:  /* *ashrdi3_mask */
    case 444:  /* *lshrdi3_mask */
    case 441:  /* *ashldi3_cconly */
    case 437:  /* *ashldi3_cmp */
    case 430:  /* *ashldi3_1 */
    case 427:  /* *ashldi3_mask */
    case 423:  /* *one_cmpldi2_2 */
    case 418:  /* *one_cmpldi2_1 */
    case 389:  /* *negdi2_cmpz */
    case 385:  /* *negdi2_1 */
    case 372:  /* *xordi_3 */
    case 371:  /* *iordi_3 */
    case 362:  /* *xordi_2 */
    case 361:  /* *iordi_2 */
    case 350:  /* *xordi_1 */
    case 349:  /* *iordi_1 */
    case 301:  /* *subdi3_cc_overflow */
    case 300:  /* *adddi3_cc_overflow */
    case 287:  /* adcxdi3 */
    case 285:  /* *subdi3_carry */
    case 284:  /* *adddi3_carry */
    case 277:  /* *subdi_3 */
    case 273:  /* *subdi_2 */
    case 268:  /* *subdi_1 */
    case 255:  /* *adddi_5 */
    case 248:  /* *adddi_3 */
    case 244:  /* *adddi_2 */
    case 237:  /* *adddi_1 */
    case 234:  /* *adddi3_cc */
    case 162:  /* fix_truncdi_i387_with_temp */
    case 161:  /* fix_truncdi_i387 */
    case 160:  /* *fix_truncdi_i387_1 */
    case 157:  /* fix_truncdi_i387_fisttp_with_temp */
    case 154:  /* fix_truncdi_i387_fisttp */
    case 151:  /* fix_truncdi_fisttp_i387_1 */
    case 88:  /* *movabsdi_2 */
    case 84:  /* *movabsdi_1 */
    case 63:  /* *pushdi2 */
    case 12:  /* *cmpdi_minus_1 */
    case 8:  /* *cmpdi_1 */
    case 4:  /* *cmpdi_ccno_1 */
      extract_constrain_insn_cached (insn);
      if (! (
#line 435 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_64BIT)))
        {
	  return 0;
        }
      else
        {
	  return 1;
        }

    case 775:  /* *movqicc_noc */
    case 753:  /* *rep_movqi */
    case 752:  /* *rep_movqi */
    case 500:  /* *setcc_qi_slp */
    case 499:  /* *setcc_qi */
    case 494:  /* *rotrqi3_1_slp */
    case 493:  /* *rotlqi3_1_slp */
    case 490:  /* *rotrqi3_1 */
    case 489:  /* *rotlqi3_1 */
    case 471:  /* *ashrqi3_cconly */
    case 470:  /* *lshrqi3_cconly */
    case 463:  /* *ashrqi3_cmp */
    case 462:  /* *lshrqi3_cmp */
    case 461:  /* *ashrqi3_1_slp */
    case 460:  /* *lshrqi3_1_slp */
    case 457:  /* *ashrqi3_1 */
    case 456:  /* *lshrqi3_1 */
    case 438:  /* *ashlqi3_cconly */
    case 434:  /* *ashlqi3_cmp */
    case 433:  /* *ashlqi3_1_slp */
    case 420:  /* *one_cmplqi2_2 */
    case 386:  /* *negqi2_cmpz */
    case 382:  /* *negqi2_1 */
    case 379:  /* *xorqi_cc_ext_1 */
    case 378:  /* *xorqi_ext_2 */
    case 377:  /* *iorqi_ext_2 */
    case 376:  /* *xorqi_ext_1 */
    case 375:  /* *iorqi_ext_1 */
    case 374:  /* *xorqi_ext_0 */
    case 373:  /* *iorqi_ext_0 */
    case 366:  /* *xorqi_3 */
    case 365:  /* *iorqi_3 */
    case 364:  /* *xorqi_2_slp */
    case 363:  /* *iorqi_2_slp */
    case 356:  /* *xorqi_2 */
    case 355:  /* *iorqi_2 */
    case 354:  /* *xorqi_1_slp */
    case 353:  /* *iorqi_1_slp */
    case 344:  /* *andqi_ext_2 */
    case 343:  /* *andqi_ext_1 */
    case 342:  /* *andqi_ext_0_cc */
    case 341:  /* andqi_ext_0 */
    case 340:  /* *andqi_2_slp */
    case 337:  /* *andqi_2 */
    case 335:  /* *andqi_1_slp */
    case 330:  /* *testqi_ext_2 */
    case 329:  /* *testqi_ext_1 */
    case 328:  /* *testqi_ext_0 */
    case 325:  /* *testqi_1 */
    case 323:  /* udivmodhiqi3 */
    case 317:  /* divmodhiqi3 */
    case 309:  /* *umulqihi3_1 */
    case 308:  /* *mulqihi3_1 */
    case 304:  /* *mulqi3_1 */
    case 295:  /* *subqi3_cc_overflow */
    case 294:  /* *addqi3_cc_overflow */
    case 291:  /* *subqi3_cconly_overflow */
    case 288:  /* *addqi3_cconly_overflow */
    case 279:  /* *subqi3_carry */
    case 278:  /* *addqi3_carry */
    case 274:  /* *subqi_3 */
    case 270:  /* *subqi_2 */
    case 269:  /* *subqi_1_slp */
    case 265:  /* *subqi_1 */
    case 257:  /* *addqi_ext_2 */
    case 256:  /* addqi_ext_1 */
    case 252:  /* *addqi_5 */
    case 249:  /* *addqi_4 */
    case 245:  /* *addqi_3 */
    case 241:  /* *addqi_2 */
    case 240:  /* *addqi_1_slp */
    case 235:  /* addqi3_cc */
    case 104:  /* *movqi_insv_2 */
    case 103:  /* *movsi_insv_1 */
    case 96:  /* *movstrictqi_xor */
    case 94:  /* *movstrictqi_1 */
    case 92:  /* *swapqi_2 */
    case 85:  /* *movabsqi_2 */
    case 81:  /* *movabsqi_1 */
    case 16:  /* *cmpqi_ext_4 */
    case 15:  /* *cmpqi_ext_3_insn */
    case 14:  /* *cmpqi_ext_2 */
    case 13:  /* *cmpqi_ext_1 */
    case 9:  /* *cmpqi_minus_1 */
    case 5:  /* *cmpqi_1 */
    case 1:  /* *cmpqi_ccno_1 */
      extract_constrain_insn_cached (insn);
      if (! (
#line 435 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_64BIT)))
        {
	  return 0;
        }
      else if ((
#line 442 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(x86_extended_QIreg_mentioned_p (insn))) || (
#line 444 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(x86_extended_reg_mentioned_p (insn))))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 332:  /* *andsi_1 */
      extract_constrain_insn_cached (insn);
      if ((get_attr_type (insn) == TYPE_IMOVX) && ((
#line 7838 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(INTVAL (operands[2]) == 0xff)) && (ext_QIreg_operand (operands[1], VOIDmode))))
        {
	  return 1;
        }
      else
        {
	  if (! (
#line 435 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_64BIT)))
	    {
	      return 0;
	    }
	  else if (
#line 444 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(x86_extended_reg_mentioned_p (insn)))
	    {
	      return 1;
	    }
	  else if ((get_attr_type (insn) == TYPE_IMOVX) && (ext_QIreg_operand (operands[1], QImode)))
	    {
	      return 1;
	    }
	  else
	    {
	      return 0;
	    }
        }

    case 333:  /* *andhi_1 */
      extract_constrain_insn_cached (insn);
      if ((get_attr_type (insn) == TYPE_IMOVX) && (ext_QIreg_operand (operands[1], VOIDmode)))
        {
	  return 1;
        }
      else
        {
	  if (! (
#line 435 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_64BIT)))
	    {
	      return 0;
	    }
	  else if (
#line 444 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(x86_extended_reg_mentioned_p (insn)))
	    {
	      return 1;
	    }
	  else if ((get_attr_type (insn) == TYPE_IMOVX) && (ext_QIreg_operand (operands[1], QImode)))
	    {
	      return 1;
	    }
	  else
	    {
	      return 0;
	    }
        }

    case 1472:  /* ssse3_phaddwv4hi3 */
    case 1473:  /* ssse3_phaddswv4hi3 */
    case 1474:  /* ssse3_phsubwv4hi3 */
    case 1475:  /* ssse3_phsubswv4hi3 */
    case 1480:  /* ssse3_phadddv2si3 */
    case 1481:  /* ssse3_phsubdv2si3 */
    case 1484:  /* ssse3_pmaddubsw */
    case 1487:  /* *ssse3_pmulhrswv4hi3 */
    case 1490:  /* ssse3_pshufbv8qi3 */
    case 1497:  /* ssse3_psignv8qi3 */
    case 1498:  /* ssse3_psignv4hi3 */
    case 1499:  /* ssse3_psignv2si3 */
    case 1502:  /* ssse3_palignrdi */
    case 1509:  /* absv8qi2 */
    case 1510:  /* absv4hi2 */
    case 1511:  /* absv2si2 */
      extract_constrain_insn_cached (insn);
      return 
#line 444 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(x86_extended_reg_mentioned_p (insn));

    case -1:
      if (GET_CODE (PATTERN (insn)) != ASM_INPUT
          && asm_noperands (PATTERN (insn)) < 0)
        fatal_insn_not_found (insn);
    case 80:  /* *movqi_internal */
    case 100:  /* *movqi_extv_1 */
    case 102:  /* *movqi_extzv_2 */
      extract_constrain_insn_cached (insn);
      if (! (
#line 435 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_64BIT)))
        {
	  return 0;
        }
      else if (((cached_mode = get_attr_mode (insn)) == MODE_DI) && ((! ((get_attr_type (insn) == TYPE_PUSH) || ((get_attr_type (insn) == TYPE_POP) || ((get_attr_type (insn) == TYPE_CALL) || ((get_attr_type (insn) == TYPE_CALLV) || ((get_attr_type (insn) == TYPE_LEAVE) || (get_attr_type (insn) == TYPE_IBR))))))) && (! (get_attr_unit (insn) == UNIT_MMX))))
        {
	  return 1;
        }
      else if ((cached_mode == MODE_QI) && (
#line 442 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(x86_extended_QIreg_mentioned_p (insn))))
        {
	  return 1;
        }
      else if (
#line 444 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(x86_extended_reg_mentioned_p (insn)))
        {
	  return 1;
        }
      else if ((get_attr_type (insn) == TYPE_IMOVX) && (ext_QIreg_operand (operands[1], QImode)))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    default:
      extract_constrain_insn_cached (insn);
      if (! (
#line 435 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_64BIT)))
        {
	  return 0;
        }
      else if (
#line 444 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(x86_extended_reg_mentioned_p (insn)))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    }
}

int
get_attr_prefix_0f (rtx insn ATTRIBUTE_UNUSED)
{
  enum attr_unit cached_unit ATTRIBUTE_UNUSED;
  enum attr_type cached_type ATTRIBUTE_UNUSED;

  switch (recog_memoized (insn))
    {
    case 1257:  /* sse2_loadhpd */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x1f))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 1255:  /* sse2_storelpd */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x7))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 1258:  /* sse2_loadlpd */
    case 1224:  /* vec_setv4sf_0 */
    case 1223:  /* vec_setv4si_0 */
      extract_constrain_insn_cached (insn);
      if (!((1 << which_alternative) & 0x600))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 938:  /* *vec_extractv2si_1 */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3f))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 1253:  /* sse2_storehpd */
    case 868:  /* *vec_extractv2sf_1 */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0xf))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 840:  /* *movv2sf_internal */
      extract_constrain_insn_cached (insn);
      if (!((1 << which_alternative) & 0xc00))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 839:  /* *movv1di_internal */
    case 838:  /* *movv2si_internal */
    case 837:  /* *movv4hi_internal */
    case 836:  /* *movv8qi_internal */
      extract_constrain_insn_cached (insn);
      if (!((1 << which_alternative) & 0x6000))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 637:  /* *fop_df_1_sse */
    case 636:  /* *fop_sf_1_sse */
    case 634:  /* *fop_df_1_mixed */
    case 633:  /* *fop_sf_1_mixed */
    case 630:  /* *fop_df_comm_sse */
    case 629:  /* *fop_sf_comm_sse */
    case 628:  /* *fop_df_comm_mixed */
    case 627:  /* *fop_sf_comm_mixed */
      if (get_attr_unit (insn) == UNIT_SSE)
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 606:  /* *bswapsi2_movbe */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return 1;
        }
      else
        {
	  return 1;
        }

    case 449:  /* ashrsi3_cvt */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return 0;
        }
      else
        {
	  return 0;
        }

    case 303:  /* *mulhi3_1 */
    case 302:  /* *mulsi3_1 */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return 0;
        }
      else
        {
	  return 1;
        }

    case 136:  /* *truncdfsf_mixed */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 1)
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 117:  /* *zero_extendsidi2 */
      extract_constrain_insn_cached (insn);
      if (!((1 << which_alternative) & 0x7))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 113:  /* *movsf_internal */
    case 112:  /* *movdf_internal */
      extract_constrain_insn_cached (insn);
      if (!((1 << which_alternative) & 0x1f))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 1228:  /* *sse4_1_extractps */
    case 105:  /* *pushtf */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 102:  /* *movqi_extzv_2 */
    case 100:  /* *movqi_extv_1 */
    case 80:  /* *movqi_internal */
    case 79:  /* *movhi_internal */
      if (get_attr_type (insn) == TYPE_IMOVX)
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 78:  /* *movsi_internal */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0xffc))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 778:  /* *movsfcc_1_387 */
    case 333:  /* *andhi_1 */
    case 332:  /* *andsi_1 */
    case 189:  /* *floatsidf2_mixed_with_temp */
    case 188:  /* *floatsisf2_mixed_with_temp */
    case 185:  /* *floatsidf2_vector_mixed_with_temp */
    case 184:  /* *floatsisf2_vector_mixed_with_temp */
    case 128:  /* *extendsfdf2_mixed */
    case 77:  /* *movdi_internal */
      extract_constrain_insn_cached (insn);
      if (!((1 << which_alternative) & 0x3))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 197:  /* *floatdidf2_mixed_nointerunit */
    case 196:  /* *floatsidf2_mixed_nointerunit */
    case 195:  /* *floatdisf2_mixed_nointerunit */
    case 194:  /* *floatsisf2_mixed_nointerunit */
    case 193:  /* *floatdidf2_mixed_interunit */
    case 192:  /* *floatsidf2_mixed_interunit */
    case 191:  /* *floatdisf2_mixed_interunit */
    case 190:  /* *floatsisf2_mixed_interunit */
    case 187:  /* *floatsidf2_vector_mixed */
    case 186:  /* *floatsisf2_vector_mixed */
    case 133:  /* *truncdfsf_fast_mixed */
    case 52:  /* *cmpiudf_mixed */
    case 51:  /* *cmpiusf_mixed */
    case 50:  /* *cmpidf_mixed */
    case 49:  /* *cmpisf_mixed */
      extract_constrain_insn_cached (insn);
      if (which_alternative != 0)
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 1905:  /* atomic_xorsi */
    case 1904:  /* atomic_orsi */
    case 1903:  /* atomic_andsi */
    case 1902:  /* atomic_xorhi */
    case 1901:  /* atomic_orhi */
    case 1900:  /* atomic_andhi */
    case 1899:  /* atomic_xorqi */
    case 1898:  /* atomic_orqi */
    case 1897:  /* atomic_andqi */
    case 1896:  /* atomic_subsi */
    case 1895:  /* atomic_subhi */
    case 1894:  /* atomic_subqi */
    case 1893:  /* atomic_addsi */
    case 1892:  /* atomic_addhi */
    case 1891:  /* atomic_addqi */
    case 1890:  /* atomic_exchangesi */
    case 1889:  /* atomic_exchangehi */
    case 1888:  /* atomic_exchangeqi */
    case 1887:  /* *atomic_fetch_add_cmpsi */
    case 1886:  /* *atomic_fetch_add_cmphi */
    case 1885:  /* *atomic_fetch_add_cmpqi */
    case 1884:  /* atomic_fetch_addsi */
    case 1883:  /* atomic_fetch_addhi */
    case 1882:  /* atomic_fetch_addqi */
    case 1881:  /* atomic_compare_and_swapdi_doubleword */
    case 1880:  /* atomic_compare_and_swapsi_1 */
    case 1879:  /* atomic_compare_and_swaphi_1 */
    case 1878:  /* atomic_compare_and_swapqi_1 */
    case 1877:  /* storedi_via_fpu */
    case 1876:  /* loaddi_via_fpu */
    case 1875:  /* atomic_storedi_fpu */
    case 1874:  /* atomic_storesi_1 */
    case 1873:  /* atomic_storehi_1 */
    case 1872:  /* atomic_storeqi_1 */
    case 1871:  /* atomic_loaddi_fpu */
    case 1870:  /* mfence_nosse */
    case 1772:  /* avx_pd256_pd */
    case 1771:  /* avx_ps256_ps */
    case 1770:  /* avx_si256_si */
    case 1725:  /* *avx_vperm_broadcast_v4df */
    case 1724:  /* *avx_vperm_broadcast_v8sf */
    case 1463:  /* sse3_monitor */
    case 1462:  /* sse3_mwait */
    case 1436:  /* *sse2_storeq */
    case 1435:  /* *vec_ext_v4si_mem */
    case 1434:  /* sse2_stored */
    case 1240:  /* vec_extract_lo_v32qi */
    case 1238:  /* vec_extract_lo_v16hi */
    case 1235:  /* vec_extract_lo_v8sf */
    case 1234:  /* vec_extract_lo_v8si */
    case 1231:  /* vec_extract_lo_v4df */
    case 1230:  /* vec_extract_lo_v4di */
    case 1229:  /* *vec_extract_v4sf_mem */
    case 1227:  /* *vec_extractv4sf_0 */
    case 987:  /* *absnegv2df2 */
    case 986:  /* *absnegv4df2 */
    case 985:  /* *absnegv4sf2 */
    case 984:  /* *absnegv8sf2 */
    case 962:  /* movdi_to_sse */
    case 937:  /* *vec_extractv2si_0 */
    case 867:  /* *vec_extractv2sf_0 */
    case 835:  /* xtest_1 */
    case 834:  /* xabort */
    case 833:  /* xend */
    case 832:  /* xbegin_1 */
    case 831:  /* *pause */
    case 830:  /* rdseedsi_1 */
    case 829:  /* rdseedhi_1 */
    case 828:  /* rdrandsi_1 */
    case 827:  /* rdrandhi_1 */
    case 826:  /* *lwp_lwpinssi3_1 */
    case 825:  /* *lwp_lwpvalsi3_1 */
    case 824:  /* lwp_slwpcbdi */
    case 823:  /* lwp_slwpcbsi */
    case 822:  /* *lwp_llwpcbdi1 */
    case 821:  /* *lwp_llwpcbsi1 */
    case 820:  /* xrstor */
    case 819:  /* xsaveopt */
    case 818:  /* xsave */
    case 817:  /* fxrstor */
    case 816:  /* fxsave */
    case 815:  /* rdtscp */
    case 814:  /* rdtsc */
    case 813:  /* rdpmc */
    case 809:  /* stack_tls_protect_test_di */
    case 808:  /* stack_tls_protect_test_si */
    case 807:  /* stack_protect_test_di */
    case 806:  /* stack_protect_test_si */
    case 805:  /* stack_tls_protect_set_di */
    case 804:  /* stack_tls_protect_set_si */
    case 803:  /* stack_protect_set_di */
    case 802:  /* stack_protect_set_si */
    case 799:  /* trap */
    case 798:  /* probe_stack_rangedi */
    case 797:  /* probe_stack_rangesi */
    case 796:  /* adjust_stack_and_probedi */
    case 795:  /* adjust_stack_and_probesi */
    case 794:  /* allocate_stack_worker_probe_di */
    case 793:  /* allocate_stack_worker_probe_si */
    case 792:  /* pro_epilogue_adjust_stack_di_sub */
    case 791:  /* pro_epilogue_adjust_stack_si_sub */
    case 790:  /* pro_epilogue_adjust_stack_di_add */
    case 789:  /* pro_epilogue_adjust_stack_si_add */
    case 777:  /* *movdfcc_1 */
    case 776:  /* *movxfcc_1 */
    case 772:  /* *x86_movsicc_0_m1_neg */
    case 771:  /* *x86_movsicc_0_m1_se */
    case 770:  /* *x86_movsicc_0_m1 */
    case 769:  /* *strlenqi_1 */
    case 768:  /* *strlenqi_1 */
    case 767:  /* *cmpstrnqi_1 */
    case 766:  /* *cmpstrnqi_1 */
    case 765:  /* *cmpstrnqi_nz_1 */
    case 764:  /* *cmpstrnqi_nz_1 */
    case 763:  /* *rep_stosqi */
    case 762:  /* *rep_stosqi */
    case 761:  /* *rep_stossi */
    case 760:  /* *rep_stossi */
    case 759:  /* *strsetqi_1 */
    case 758:  /* *strsetqi_1 */
    case 757:  /* *strsethi_1 */
    case 756:  /* *strsethi_1 */
    case 755:  /* *strsetsi_1 */
    case 754:  /* *strsetsi_1 */
    case 753:  /* *rep_movqi */
    case 752:  /* *rep_movqi */
    case 751:  /* *rep_movsi */
    case 750:  /* *rep_movsi */
    case 749:  /* *strmovqi_1 */
    case 748:  /* *strmovqi_1 */
    case 747:  /* *strmovhi_1 */
    case 746:  /* *strmovhi_1 */
    case 745:  /* *strmovsi_1 */
    case 744:  /* *strmovsi_1 */
    case 743:  /* cld */
    case 741:  /* fxamdf2_i387_with_temp */
    case 740:  /* fxamsf2_i387_with_temp */
    case 739:  /* fxamxf2_i387 */
    case 738:  /* fxamdf2_i387 */
    case 737:  /* fxamsf2_i387 */
    case 736:  /* fistsi2_ceil_with_temp */
    case 735:  /* fistsi2_floor_with_temp */
    case 734:  /* fisthi2_ceil_with_temp */
    case 733:  /* fisthi2_floor_with_temp */
    case 732:  /* fistsi2_ceil */
    case 731:  /* fistsi2_floor */
    case 730:  /* fisthi2_ceil */
    case 729:  /* fisthi2_floor */
    case 728:  /* fistdi2_ceil_with_temp */
    case 727:  /* fistdi2_floor_with_temp */
    case 726:  /* fistdi2_ceil */
    case 725:  /* fistdi2_floor */
    case 724:  /* *fistdi2_ceil_1 */
    case 723:  /* *fistdi2_floor_1 */
    case 722:  /* *fistsi2_ceil_1 */
    case 721:  /* *fistsi2_floor_1 */
    case 720:  /* *fisthi2_ceil_1 */
    case 719:  /* *fisthi2_floor_1 */
    case 718:  /* frndintxf2_mask_pm_i387 */
    case 717:  /* frndintxf2_mask_pm */
    case 716:  /* frndintxf2_trunc_i387 */
    case 715:  /* frndintxf2_ceil_i387 */
    case 714:  /* frndintxf2_floor_i387 */
    case 713:  /* frndintxf2_trunc */
    case 712:  /* frndintxf2_ceil */
    case 711:  /* frndintxf2_floor */
    case 710:  /* fistsi2_with_temp */
    case 709:  /* fisthi2_with_temp */
    case 708:  /* fistsi2 */
    case 707:  /* fisthi2 */
    case 706:  /* *fistsi2_1 */
    case 705:  /* *fisthi2_1 */
    case 704:  /* fistdi2_with_temp */
    case 703:  /* fistdi2 */
    case 702:  /* *fistdi2_1 */
    case 701:  /* rintxf2 */
    case 698:  /* *fscalexf4_i387 */
    case 697:  /* *f2xm1xf2_i387 */
    case 696:  /* fxtract_extenddfxf3_i387 */
    case 695:  /* fxtract_extendsfxf3_i387 */
    case 694:  /* fxtractxf3_i387 */
    case 693:  /* fyl2xp1_extenddfxf3_i387 */
    case 692:  /* fyl2xp1_extendsfxf3_i387 */
    case 691:  /* fyl2xp1xf3_i387 */
    case 690:  /* fyl2x_extenddfxf3_i387 */
    case 689:  /* fyl2x_extendsfxf3_i387 */
    case 688:  /* fyl2xxf3_i387 */
    case 687:  /* fpatan_extenddfxf3_i387 */
    case 686:  /* fpatan_extendsfxf3_i387 */
    case 685:  /* *fpatanxf3_i387 */
    case 684:  /* fptan_extenddfxf4_i387 */
    case 683:  /* fptan_extendsfxf4_i387 */
    case 682:  /* fptanxf4_i387 */
    case 681:  /* sincos_extenddfxf3_i387 */
    case 680:  /* sincos_extendsfxf3_i387 */
    case 679:  /* sincosxf3 */
    case 678:  /* *cos_extenddfxf2_i387 */
    case 677:  /* *sin_extenddfxf2_i387 */
    case 676:  /* *cos_extendsfxf2_i387 */
    case 675:  /* *sin_extendsfxf2_i387 */
    case 674:  /* *cosxf2_i387 */
    case 673:  /* *sinxf2_i387 */
    case 672:  /* fprem1xf4_i387 */
    case 671:  /* fpremxf4_i387 */
    case 667:  /* sqrt_extenddfxf2_i387 */
    case 666:  /* sqrt_extendsfxf2_i387 */
    case 665:  /* sqrtxf2 */
    case 664:  /* truncxfdf2_i387_noop_unspec */
    case 663:  /* truncxfsf2_i387_noop_unspec */
    case 662:  /* *fop_xf_6_i387 */
    case 661:  /* *fop_xf_6_i387 */
    case 660:  /* *fop_xf_5_i387 */
    case 659:  /* *fop_xf_5_i387 */
    case 658:  /* *fop_xf_4_i387 */
    case 657:  /* *fop_xf_4_i387 */
    case 656:  /* *fop_xf_3_i387 */
    case 655:  /* *fop_xf_3_i387 */
    case 654:  /* *fop_xf_2_i387 */
    case 653:  /* *fop_xf_2_i387 */
    case 652:  /* *fop_xf_1_i387 */
    case 651:  /* *fop_xf_comm_i387 */
    case 650:  /* *fop_df_6_i387 */
    case 649:  /* *fop_df_5_i387 */
    case 648:  /* *fop_df_4_i387 */
    case 647:  /* *fop_df_3_i387 */
    case 646:  /* *fop_sf_3_i387 */
    case 645:  /* *fop_df_3_i387 */
    case 644:  /* *fop_sf_3_i387 */
    case 643:  /* *fop_df_2_i387 */
    case 642:  /* *fop_sf_2_i387 */
    case 641:  /* *fop_df_2_i387 */
    case 640:  /* *fop_sf_2_i387 */
    case 639:  /* *fop_df_1_i387 */
    case 638:  /* *fop_sf_1_i387 */
    case 632:  /* *fop_df_comm_i387 */
    case 631:  /* *fop_sf_comm_i387 */
    case 626:  /* *tls_dynamic_gnu2_combine_32 */
    case 625:  /* *tls_dynamic_gnu2_call_32 */
    case 624:  /* *tls_dynamic_gnu2_lea_32 */
    case 623:  /* *add_tp_di */
    case 622:  /* *add_tp_si */
    case 621:  /* *add_tp_x32_zext */
    case 620:  /* *add_tp_x32 */
    case 619:  /* *load_tp_di */
    case 618:  /* *load_tp_si */
    case 617:  /* *load_tp_x32_zext */
    case 616:  /* *load_tp_x32 */
    case 615:  /* *tls_local_dynamic_32_once */
    case 614:  /* *tls_local_dynamic_base_32_gnu */
    case 613:  /* *tls_global_dynamic_32_gnu */
    case 612:  /* *parityhi2_cmp */
    case 611:  /* paritysi2_cmp */
    case 610:  /* paritydi2_cmp */
    case 609:  /* bswaphi_lowpart */
    case 608:  /* *bswaphi_lowpart_1 */
    case 574:  /* ffssi2_no_cmove */
    case 573:  /* split_stack_return */
    case 572:  /* leave */
    case 571:  /* eh_return_internal */
    case 570:  /* set_got_offset_rex64 */
    case 569:  /* set_got_labelled */
    case 568:  /* set_got */
    case 567:  /* pad */
    case 566:  /* nops */
    case 565:  /* nop */
    case 564:  /* simple_return_indirect_internal */
    case 563:  /* simple_return_pop_internal */
    case 562:  /* simple_return_internal_long */
    case 561:  /* simple_return_internal */
    case 560:  /* prologue_use */
    case 559:  /* *memory_blockage */
    case 558:  /* blockage */
    case 557:  /* *sibcall_value_pop */
    case 556:  /* *call_value_pop */
    case 555:  /* *sibcall_value */
    case 554:  /* *sibcall_value */
    case 553:  /* *call_value */
    case 552:  /* *call_value */
    case 551:  /* *sibcall_pop */
    case 550:  /* *call_pop */
    case 549:  /* *sibcall */
    case 548:  /* *sibcall */
    case 547:  /* *call */
    case 546:  /* *call */
    case 545:  /* *tablejump_1 */
    case 544:  /* *tablejump_1 */
    case 543:  /* *indirect_jump */
    case 542:  /* *indirect_jump */
    case 541:  /* jump */
    case 540:  /* *jccxf_si_r_i387 */
    case 539:  /* *jccdf_si_r_i387 */
    case 538:  /* *jccsf_si_r_i387 */
    case 537:  /* *jccxf_hi_r_i387 */
    case 536:  /* *jccdf_hi_r_i387 */
    case 535:  /* *jccsf_hi_r_i387 */
    case 534:  /* *jccxf_si_i387 */
    case 533:  /* *jccdf_si_i387 */
    case 532:  /* *jccsf_si_i387 */
    case 531:  /* *jccxf_hi_i387 */
    case 530:  /* *jccdf_hi_i387 */
    case 529:  /* *jccsf_hi_i387 */
    case 528:  /* *jccuxf_r_i387 */
    case 527:  /* *jccudf_r_i387 */
    case 526:  /* *jccusf_r_i387 */
    case 525:  /* *jccuxf_i387 */
    case 524:  /* *jccudf_i387 */
    case 523:  /* *jccusf_i387 */
    case 522:  /* *jccdf_r_i387 */
    case 521:  /* *jccsf_r_i387 */
    case 520:  /* *jccdf_i387 */
    case 519:  /* *jccsf_i387 */
    case 518:  /* *jccxf_r_i387 */
    case 517:  /* *jccxf_i387 */
    case 516:  /* *jccxf_0_r_i387 */
    case 515:  /* *jccdf_0_r_i387 */
    case 514:  /* *jccsf_0_r_i387 */
    case 513:  /* *jccxf_0_i387 */
    case 512:  /* *jccdf_0_i387 */
    case 511:  /* *jccsf_0_i387 */
    case 510:  /* *jcc_btsi_mask_1 */
    case 509:  /* *jcc_btsi_1 */
    case 508:  /* *jcc_btdi_mask */
    case 507:  /* *jcc_btsi_mask */
    case 506:  /* *jcc_btdi */
    case 505:  /* *jcc_btsi */
    case 504:  /* *jcc_2 */
    case 503:  /* *jcc_1 */
    case 498:  /* *setcc_si_1_movzbl */
    case 497:  /* *setcc_si_1_and */
    case 494:  /* *rotrqi3_1_slp */
    case 493:  /* *rotlqi3_1_slp */
    case 492:  /* *rotrhi3_1 */
    case 491:  /* *rotlhi3_1 */
    case 490:  /* *rotrqi3_1 */
    case 489:  /* *rotlqi3_1 */
    case 488:  /* *rotrdi3_1 */
    case 487:  /* *rotldi3_1 */
    case 486:  /* *rotrsi3_1 */
    case 485:  /* *rotlsi3_1 */
    case 484:  /* *bmi2_rorxsi3_1 */
    case 483:  /* ix86_rotrdi3_doubleword */
    case 482:  /* ix86_rotldi3_doubleword */
    case 481:  /* *rotrdi3_mask */
    case 480:  /* *rotldi3_mask */
    case 479:  /* *rotrsi3_mask */
    case 478:  /* *rotlsi3_mask */
    case 477:  /* *ashrdi3_cconly */
    case 476:  /* *lshrdi3_cconly */
    case 475:  /* *ashrsi3_cconly */
    case 474:  /* *lshrsi3_cconly */
    case 473:  /* *ashrhi3_cconly */
    case 472:  /* *lshrhi3_cconly */
    case 471:  /* *ashrqi3_cconly */
    case 470:  /* *lshrqi3_cconly */
    case 469:  /* *ashrdi3_cmp */
    case 468:  /* *lshrdi3_cmp */
    case 467:  /* *ashrsi3_cmp */
    case 466:  /* *lshrsi3_cmp */
    case 465:  /* *ashrhi3_cmp */
    case 464:  /* *lshrhi3_cmp */
    case 463:  /* *ashrqi3_cmp */
    case 462:  /* *lshrqi3_cmp */
    case 461:  /* *ashrqi3_1_slp */
    case 460:  /* *lshrqi3_1_slp */
    case 459:  /* *ashrhi3_1 */
    case 458:  /* *lshrhi3_1 */
    case 457:  /* *ashrqi3_1 */
    case 456:  /* *lshrqi3_1 */
    case 455:  /* *ashrdi3_1 */
    case 454:  /* *lshrdi3_1 */
    case 453:  /* *ashrsi3_1 */
    case 452:  /* *lshrsi3_1 */
    case 451:  /* *bmi2_ashrsi3_1 */
    case 450:  /* *bmi2_lshrsi3_1 */
    case 447:  /* *ashrdi3_doubleword */
    case 446:  /* *lshrdi3_doubleword */
    case 445:  /* *ashrdi3_mask */
    case 444:  /* *lshrdi3_mask */
    case 443:  /* *ashrsi3_mask */
    case 442:  /* *lshrsi3_mask */
    case 441:  /* *ashldi3_cconly */
    case 440:  /* *ashlsi3_cconly */
    case 439:  /* *ashlhi3_cconly */
    case 438:  /* *ashlqi3_cconly */
    case 437:  /* *ashldi3_cmp */
    case 436:  /* *ashlsi3_cmp */
    case 435:  /* *ashlhi3_cmp */
    case 434:  /* *ashlqi3_cmp */
    case 433:  /* *ashlqi3_1_slp */
    case 432:  /* *ashlqi3_1 */
    case 431:  /* *ashlhi3_1 */
    case 430:  /* *ashldi3_1 */
    case 429:  /* *ashlsi3_1 */
    case 428:  /* *bmi2_ashlsi3_1 */
    case 427:  /* *ashldi3_mask */
    case 426:  /* *ashlsi3_mask */
    case 424:  /* *ashldi3_doubleword */
    case 423:  /* *one_cmpldi2_2 */
    case 422:  /* *one_cmplsi2_2 */
    case 421:  /* *one_cmplhi2_2 */
    case 420:  /* *one_cmplqi2_2 */
    case 419:  /* *one_cmplqi2_1 */
    case 418:  /* *one_cmpldi2_1 */
    case 417:  /* *one_cmplsi2_1 */
    case 416:  /* *one_cmplhi2_1 */
    case 415:  /* copysigntf3_var */
    case 414:  /* copysigndf3_var */
    case 413:  /* copysignsf3_var */
    case 412:  /* copysigntf3_const */
    case 411:  /* copysigndf3_const */
    case 410:  /* copysignsf3_const */
    case 409:  /* *negextenddfxf2 */
    case 408:  /* *absextenddfxf2 */
    case 407:  /* *negextendsfxf2 */
    case 406:  /* *absextendsfxf2 */
    case 405:  /* *negextendsfdf2 */
    case 404:  /* *absextendsfdf2 */
    case 403:  /* *negxf2_1 */
    case 402:  /* *absxf2_1 */
    case 401:  /* *negdf2_1 */
    case 400:  /* *absdf2_1 */
    case 399:  /* *negsf2_1 */
    case 398:  /* *abssf2_1 */
    case 397:  /* *absnegtf2_sse */
    case 396:  /* *absnegxf2_i387 */
    case 395:  /* *absnegdf2_i387 */
    case 394:  /* *absnegsf2_i387 */
    case 393:  /* *absnegdf2_sse */
    case 392:  /* *absnegsf2_sse */
    case 391:  /* *absnegdf2_mixed */
    case 390:  /* *absnegsf2_mixed */
    case 389:  /* *negdi2_cmpz */
    case 388:  /* *negsi2_cmpz */
    case 387:  /* *neghi2_cmpz */
    case 386:  /* *negqi2_cmpz */
    case 385:  /* *negdi2_1 */
    case 384:  /* *negsi2_1 */
    case 383:  /* *neghi2_1 */
    case 382:  /* *negqi2_1 */
    case 381:  /* *negti2_doubleword */
    case 380:  /* *negdi2_doubleword */
    case 379:  /* *xorqi_cc_ext_1 */
    case 378:  /* *xorqi_ext_2 */
    case 377:  /* *iorqi_ext_2 */
    case 376:  /* *xorqi_ext_1 */
    case 375:  /* *iorqi_ext_1 */
    case 374:  /* *xorqi_ext_0 */
    case 373:  /* *iorqi_ext_0 */
    case 372:  /* *xordi_3 */
    case 371:  /* *iordi_3 */
    case 370:  /* *xorsi_3 */
    case 369:  /* *iorsi_3 */
    case 368:  /* *xorhi_3 */
    case 367:  /* *iorhi_3 */
    case 366:  /* *xorqi_3 */
    case 365:  /* *iorqi_3 */
    case 364:  /* *xorqi_2_slp */
    case 363:  /* *iorqi_2_slp */
    case 362:  /* *xordi_2 */
    case 361:  /* *iordi_2 */
    case 360:  /* *xorsi_2 */
    case 359:  /* *iorsi_2 */
    case 358:  /* *xorhi_2 */
    case 357:  /* *iorhi_2 */
    case 356:  /* *xorqi_2 */
    case 355:  /* *iorqi_2 */
    case 354:  /* *xorqi_1_slp */
    case 353:  /* *iorqi_1_slp */
    case 352:  /* *xorqi_1 */
    case 351:  /* *iorqi_1 */
    case 350:  /* *xordi_1 */
    case 349:  /* *iordi_1 */
    case 348:  /* *xorsi_1 */
    case 347:  /* *iorsi_1 */
    case 346:  /* *xorhi_1 */
    case 345:  /* *iorhi_1 */
    case 344:  /* *andqi_ext_2 */
    case 343:  /* *andqi_ext_1 */
    case 342:  /* *andqi_ext_0_cc */
    case 341:  /* andqi_ext_0 */
    case 340:  /* *andqi_2_slp */
    case 339:  /* *andsi_2 */
    case 338:  /* *andhi_2 */
    case 337:  /* *andqi_2 */
    case 336:  /* *andqi_2_maybe_si */
    case 335:  /* *andqi_1_slp */
    case 334:  /* *andqi_1 */
    case 331:  /* *testqi_ext_3 */
    case 330:  /* *testqi_ext_2 */
    case 329:  /* *testqi_ext_1 */
    case 328:  /* *testqi_ext_0 */
    case 327:  /* *testsi_1 */
    case 326:  /* *testhi_1 */
    case 325:  /* *testqi_1 */
    case 324:  /* *testqi_1_maybe_si */
    case 323:  /* udivmodhiqi3 */
    case 322:  /* *udivmodsi4_noext */
    case 321:  /* *udivmodhi4_noext */
    case 320:  /* *udivmodsi4 */
    case 319:  /* *udivmodhi4 */
    case 318:  /* udivmodsi4_1 */
    case 317:  /* divmodhiqi3 */
    case 316:  /* *divmodsi4_noext */
    case 315:  /* *divmodhi4_noext */
    case 314:  /* *divmodsi4 */
    case 313:  /* *divmodhi4 */
    case 312:  /* divmodsi4_1 */
    case 311:  /* *umulsi3_highpart_1 */
    case 310:  /* *smulsi3_highpart_1 */
    case 309:  /* *umulqihi3_1 */
    case 308:  /* *mulqihi3_1 */
    case 307:  /* *mulsidi3_1 */
    case 306:  /* *umulsidi3_1 */
    case 305:  /* *bmi2_umulsidi3_1 */
    case 304:  /* *mulqi3_1 */
    case 301:  /* *subdi3_cc_overflow */
    case 300:  /* *adddi3_cc_overflow */
    case 299:  /* *subsi3_cc_overflow */
    case 298:  /* *addsi3_cc_overflow */
    case 297:  /* *subhi3_cc_overflow */
    case 296:  /* *addhi3_cc_overflow */
    case 295:  /* *subqi3_cc_overflow */
    case 294:  /* *addqi3_cc_overflow */
    case 293:  /* *subsi3_cconly_overflow */
    case 292:  /* *subhi3_cconly_overflow */
    case 291:  /* *subqi3_cconly_overflow */
    case 290:  /* *addsi3_cconly_overflow */
    case 289:  /* *addhi3_cconly_overflow */
    case 288:  /* *addqi3_cconly_overflow */
    case 287:  /* adcxdi3 */
    case 286:  /* adcxsi3 */
    case 285:  /* *subdi3_carry */
    case 284:  /* *adddi3_carry */
    case 283:  /* *subsi3_carry */
    case 282:  /* *addsi3_carry */
    case 281:  /* *subhi3_carry */
    case 280:  /* *addhi3_carry */
    case 279:  /* *subqi3_carry */
    case 278:  /* *addqi3_carry */
    case 277:  /* *subdi_3 */
    case 276:  /* *subsi_3 */
    case 275:  /* *subhi_3 */
    case 274:  /* *subqi_3 */
    case 273:  /* *subdi_2 */
    case 272:  /* *subsi_2 */
    case 271:  /* *subhi_2 */
    case 270:  /* *subqi_2 */
    case 269:  /* *subqi_1_slp */
    case 268:  /* *subdi_1 */
    case 267:  /* *subsi_1 */
    case 266:  /* *subhi_1 */
    case 265:  /* *subqi_1 */
    case 264:  /* *subti3_doubleword */
    case 263:  /* *subdi3_doubleword */
    case 262:  /* *lea_general_4 */
    case 261:  /* *lea_general_4 */
    case 260:  /* *lea_general_3 */
    case 259:  /* *lea_general_2 */
    case 258:  /* *lea_general_1 */
    case 257:  /* *addqi_ext_2 */
    case 256:  /* addqi_ext_1 */
    case 255:  /* *adddi_5 */
    case 254:  /* *addsi_5 */
    case 253:  /* *addhi_5 */
    case 252:  /* *addqi_5 */
    case 251:  /* *addsi_4 */
    case 250:  /* *addhi_4 */
    case 249:  /* *addqi_4 */
    case 248:  /* *adddi_3 */
    case 247:  /* *addsi_3 */
    case 246:  /* *addhi_3 */
    case 245:  /* *addqi_3 */
    case 244:  /* *adddi_2 */
    case 243:  /* *addsi_2 */
    case 242:  /* *addhi_2 */
    case 241:  /* *addqi_2 */
    case 240:  /* *addqi_1_slp */
    case 239:  /* *addqi_1 */
    case 238:  /* *addhi_1 */
    case 237:  /* *adddi_1 */
    case 236:  /* *addsi_1 */
    case 235:  /* addqi3_cc */
    case 234:  /* *adddi3_cc */
    case 233:  /* *addsi3_cc */
    case 232:  /* *addti3_doubleword */
    case 231:  /* *adddi3_doubleword */
    case 230:  /* *leasi */
    case 229:  /* *floatunssixf2_1 */
    case 228:  /* *floatunssidf2_1 */
    case 227:  /* *floatunssisf2_1 */
    case 226:  /* floatdixf2_i387_with_xmm */
    case 225:  /* floatdidf2_i387_with_xmm */
    case 224:  /* floatdisf2_i387_with_xmm */
    case 223:  /* *floatdixf2_i387 */
    case 222:  /* *floatdidf2_i387 */
    case 221:  /* *floatdisf2_i387 */
    case 220:  /* *floatsixf2_i387 */
    case 219:  /* *floatsidf2_i387 */
    case 218:  /* *floatsisf2_i387 */
    case 217:  /* *floatdixf2_i387_with_temp */
    case 216:  /* *floatdidf2_i387_with_temp */
    case 215:  /* *floatdisf2_i387_with_temp */
    case 214:  /* *floatsixf2_i387_with_temp */
    case 213:  /* *floatsidf2_i387_with_temp */
    case 212:  /* *floatsisf2_i387_with_temp */
    case 183:  /* *floatdixf2_1 */
    case 182:  /* *floatdidf2_1 */
    case 181:  /* *floatdisf2_1 */
    case 180:  /* *floatsixf2_1 */
    case 179:  /* *floatsidf2_1 */
    case 178:  /* *floatsisf2_1 */
    case 177:  /* *floathixf2_i387 */
    case 176:  /* *floathidf2_i387 */
    case 175:  /* *floathisf2_i387 */
    case 174:  /* *floathixf2_i387_with_temp */
    case 173:  /* *floathidf2_i387_with_temp */
    case 172:  /* *floathisf2_i387_with_temp */
    case 171:  /* *floathixf2_1 */
    case 170:  /* *floathidf2_1 */
    case 169:  /* *floathisf2_1 */
    case 168:  /* x86_fldcw_1 */
    case 167:  /* x86_fnstcw_1 */
    case 166:  /* fix_truncsi_i387_with_temp */
    case 165:  /* fix_trunchi_i387_with_temp */
    case 164:  /* fix_truncsi_i387 */
    case 163:  /* fix_trunchi_i387 */
    case 162:  /* fix_truncdi_i387_with_temp */
    case 161:  /* fix_truncdi_i387 */
    case 160:  /* *fix_truncdi_i387_1 */
    case 159:  /* *fix_truncsi_i387_1 */
    case 158:  /* *fix_trunchi_i387_1 */
    case 157:  /* fix_truncdi_i387_fisttp_with_temp */
    case 156:  /* fix_truncsi_i387_fisttp_with_temp */
    case 155:  /* fix_trunchi_i387_fisttp_with_temp */
    case 154:  /* fix_truncdi_i387_fisttp */
    case 153:  /* fix_truncsi_i387_fisttp */
    case 152:  /* fix_trunchi_i387_fisttp */
    case 151:  /* fix_truncdi_fisttp_i387_1 */
    case 150:  /* fix_truncsi_fisttp_i387_1 */
    case 149:  /* fix_trunchi_fisttp_i387_1 */
    case 146:  /* *fixuns_truncdf_1 */
    case 145:  /* *fixuns_truncsf_1 */
    case 144:  /* *truncxfdf2_i387 */
    case 143:  /* *truncxfsf2_i387 */
    case 142:  /* truncxfdf2_i387_noop */
    case 141:  /* truncxfsf2_i387_noop */
    case 140:  /* *truncxfdf2_mixed */
    case 139:  /* *truncxfsf2_mixed */
    case 138:  /* *truncdfsf2_i387_1 */
    case 137:  /* *truncdfsf_i387 */
    case 135:  /* *truncdfsf_fast_i387 */
    case 132:  /* *extenddfxf2_i387 */
    case 131:  /* *extendsfxf2_i387 */
    case 130:  /* *extendsfdf2_i387 */
    case 124:  /* extendsidi2_1 */
    case 122:  /* zero_extendqihi2_and */
    case 119:  /* zero_extendhisi2_and */
    case 118:  /* zero_extendqisi2_and */
    case 116:  /* *swapdf */
    case 115:  /* *swapsf */
    case 114:  /* swapxf */
    case 111:  /* *movxf_internal */
    case 109:  /* *pushsf */
    case 108:  /* *pushdf */
    case 107:  /* *pushxf_nointeger */
    case 106:  /* *pushxf */
    case 104:  /* *movqi_insv_2 */
    case 103:  /* *movsi_insv_1 */
    case 97:  /* *movstricthi_xor */
    case 96:  /* *movstrictqi_xor */
    case 95:  /* *movstricthi_1 */
    case 94:  /* *movstrictqi_1 */
    case 93:  /* *swaphi_2 */
    case 92:  /* *swapqi_2 */
    case 91:  /* *swaphi_1 */
    case 90:  /* *swapqi_1 */
    case 89:  /* swapsi */
    case 88:  /* *movabsdi_2 */
    case 87:  /* *movabssi_2 */
    case 86:  /* *movabshi_2 */
    case 85:  /* *movabsqi_2 */
    case 84:  /* *movabsdi_1 */
    case 83:  /* *movabssi_1 */
    case 82:  /* *movabshi_1 */
    case 81:  /* *movabsqi_1 */
    case 74:  /* *movsi_or */
    case 73:  /* *movsi_xor */
    case 72:  /* *popdi1_epilogue */
    case 71:  /* *popsi1_epilogue */
    case 70:  /* *popdi1 */
    case 69:  /* *popsi1 */
    case 68:  /* *pushdi2_prologue */
    case 67:  /* *pushsi2_prologue */
    case 66:  /* *pushhi2 */
    case 65:  /* *pushqi2 */
    case 64:  /* *pushsi2 */
    case 63:  /* *pushdi2 */
    case 62:  /* *cmpiuxf_i387 */
    case 61:  /* *cmpiudf_i387 */
    case 60:  /* *cmpiusf_i387 */
    case 59:  /* *cmpixf_i387 */
    case 58:  /* *cmpidf_i387 */
    case 57:  /* *cmpisf_i387 */
    case 48:  /* x86_sahf_1 */
    case 47:  /* x86_fnstsw_1 */
    case 46:  /* *cmpxf_si_cc_i387 */
    case 45:  /* *cmpdf_si_cc_i387 */
    case 44:  /* *cmpsf_si_cc_i387 */
    case 43:  /* *cmpxf_hi_cc_i387 */
    case 42:  /* *cmpdf_hi_cc_i387 */
    case 41:  /* *cmpsf_hi_cc_i387 */
    case 40:  /* *cmpxf_si_i387 */
    case 39:  /* *cmpdf_si_i387 */
    case 38:  /* *cmpsf_si_i387 */
    case 37:  /* *cmpxf_hi_i387 */
    case 36:  /* *cmpdf_hi_i387 */
    case 35:  /* *cmpsf_hi_i387 */
    case 34:  /* *cmpuxf_cc_i387 */
    case 33:  /* *cmpudf_cc_i387 */
    case 32:  /* *cmpusf_cc_i387 */
    case 31:  /* *cmpuxf_i387 */
    case 30:  /* *cmpudf_i387 */
    case 29:  /* *cmpusf_i387 */
    case 28:  /* *cmpdf_cc_i387 */
    case 27:  /* *cmpsf_cc_i387 */
    case 26:  /* *cmpdf_i387 */
    case 25:  /* *cmpsf_i387 */
    case 24:  /* *cmpxf_cc_i387 */
    case 23:  /* *cmpxf_i387 */
    case 22:  /* *cmpxf_0_cc_i387 */
    case 21:  /* *cmpdf_0_cc_i387 */
    case 20:  /* *cmpsf_0_cc_i387 */
    case 19:  /* *cmpxf_0_i387 */
    case 18:  /* *cmpdf_0_i387 */
    case 17:  /* *cmpsf_0_i387 */
    case 16:  /* *cmpqi_ext_4 */
    case 15:  /* *cmpqi_ext_3_insn */
    case 14:  /* *cmpqi_ext_2 */
    case 13:  /* *cmpqi_ext_1 */
    case 12:  /* *cmpdi_minus_1 */
    case 11:  /* *cmpsi_minus_1 */
    case 10:  /* *cmphi_minus_1 */
    case 9:  /* *cmpqi_minus_1 */
    case 8:  /* *cmpdi_1 */
    case 7:  /* *cmpsi_1 */
    case 6:  /* *cmphi_1 */
    case 5:  /* *cmpqi_1 */
    case 4:  /* *cmpdi_ccno_1 */
    case 3:  /* *cmpsi_ccno_1 */
    case 2:  /* *cmphi_ccno_1 */
    case 1:  /* *cmpqi_ccno_1 */
      return 0;

    case 125:  /* extendhisi2 */
    case 127:  /* extendqihi2 */
      extract_constrain_insn_cached (insn);
      if ((! (((
#line 327 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(ix86_schedule)) == (
(CPU_K6))))) && (which_alternative == 0))
        {
	  return 0;
        }
      else
        {
	  return 1;
        }

    case -1:
      if (GET_CODE (PATTERN (insn)) != ASM_INPUT
          && asm_noperands (PATTERN (insn)) < 0)
        fatal_insn_not_found (insn);
      if ((((cached_type = get_attr_type (insn)) == TYPE_IMOVX) || ((cached_type == TYPE_SETCC) || ((cached_type == TYPE_ICMOV) || (cached_type == TYPE_BITMANIP)))) || (((cached_unit = get_attr_unit (insn)) == UNIT_SSE) || (cached_unit == UNIT_MMX)))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    default:
      return 1;

    }
}

int
get_attr_prefix_rep (rtx insn ATTRIBUTE_UNUSED)
{
  enum attr_mode cached_mode ATTRIBUTE_UNUSED;
  enum attr_type cached_type ATTRIBUTE_UNUSED;

  switch (recog_memoized (insn))
    {
    case 1433:  /* sse2_loadld */
      extract_constrain_insn_cached (insn);
      if (!((1 << which_alternative) & 0x7))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 1261:  /* *vec_concatv2df */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x24))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 1258:  /* sse2_loadlpd */
      extract_constrain_insn_cached (insn);
      if (!((1 << which_alternative) & 0x6fe))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 1255:  /* sse2_storelpd */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x6))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 1439:  /* *vec_dupv2di */
    case 1245:  /* *vec_interleave_lowv2df */
    case 1243:  /* *vec_interleave_highv2df */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 2)
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 1224:  /* vec_setv4sf_0 */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3b))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 1223:  /* vec_setv4si_0 */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x39))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 1257:  /* sse2_loadhpd */
    case 1220:  /* *vec_concatv2sf_sse4_1 */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 4)
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 1065:  /* sse3_hsubv4sf3 */
    case 1064:  /* sse3_haddv4sf3 */
    case 1055:  /* sse3_addsubv4sf3 */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 1174:  /* fix_truncv4sfv4si2 */
    case 976:  /* sse3_lddqu */
    case 975:  /* avx_lddqu256 */
      extract_constrain_insn_cached (insn);
      if (
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX))
        {
	  return 0;
        }
      else
        {
	  return 1;
        }

    case 1253:  /* sse2_storehpd */
    case 868:  /* *vec_extractv2sf_1 */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 3)
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 840:  /* *movv2sf_internal */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x30))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 839:  /* *movv1di_internal */
    case 838:  /* *movv2si_internal */
    case 837:  /* *movv4hi_internal */
    case 836:  /* *movv8qi_internal */
      extract_constrain_insn_cached (insn);
      if ((((1 << which_alternative) & 0x30)) || ((which_alternative == 7) && (! (
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX)))))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 637:  /* *fop_df_1_sse */
    case 636:  /* *fop_sf_1_sse */
    case 634:  /* *fop_df_1_mixed */
    case 633:  /* *fop_sf_1_mixed */
    case 630:  /* *fop_df_comm_sse */
    case 629:  /* *fop_sf_comm_sse */
    case 628:  /* *fop_df_comm_mixed */
    case 627:  /* *fop_sf_comm_mixed */
      if (get_attr_unit (insn) == UNIT_SSE)
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 1723:  /* *avx_vperm_broadcast_v4sf */
    case 1259:  /* sse2_movsd */
    case 199:  /* *floatsidf2_vector_sse_with_temp */
    case 198:  /* *floatsisf2_vector_sse_with_temp */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 185:  /* *floatsidf2_vector_mixed_with_temp */
    case 184:  /* *floatsisf2_vector_mixed_with_temp */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0xc))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 1221:  /* *vec_concatv2sf_sse */
    case 136:  /* *truncdfsf_mixed */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 1)
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 1260:  /* vec_dupv2df */
    case 197:  /* *floatdidf2_mixed_nointerunit */
    case 196:  /* *floatsidf2_mixed_nointerunit */
    case 195:  /* *floatdisf2_mixed_nointerunit */
    case 194:  /* *floatsisf2_mixed_nointerunit */
    case 193:  /* *floatdidf2_mixed_interunit */
    case 192:  /* *floatsidf2_mixed_interunit */
    case 191:  /* *floatdisf2_mixed_interunit */
    case 190:  /* *floatsisf2_mixed_interunit */
    case 133:  /* *truncdfsf_fast_mixed */
      extract_constrain_insn_cached (insn);
      if (which_alternative != 0)
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 189:  /* *floatsidf2_mixed_with_temp */
    case 188:  /* *floatsisf2_mixed_with_temp */
    case 128:  /* *extendsfdf2_mixed */
      extract_constrain_insn_cached (insn);
      if (!((1 << which_alternative) & 0x3))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 113:  /* *movsf_internal */
      extract_constrain_insn_cached (insn);
      if ((!((1 << which_alternative) & 0xce1f)) && (get_attr_mode (insn) == MODE_SF))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 112:  /* *movdf_internal */
      extract_constrain_insn_cached (insn);
      if ((!((1 << which_alternative) & 0x1f)) && (get_attr_mode (insn) == MODE_DF))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 78:  /* *movsi_internal */
      extract_constrain_insn_cached (insn);
      if ((((1 << which_alternative) & 0xf00)) && (! (
#line 659 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SSE2))))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 52:  /* *cmpiudf_mixed */
    case 51:  /* *cmpiusf_mixed */
    case 50:  /* *cmpidf_mixed */
    case 49:  /* *cmpisf_mixed */
      extract_constrain_insn_cached (insn);
      if (which_alternative != 0)
        {
	  return 0;
        }
      else
        {
	  return 0;
        }

    case 577:  /* ctzhi2 */
    case 578:  /* ctzsi2 */
      extract_constrain_insn_cached (insn);
      if ((
#line 12070 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_BMI)) || ((! (
#line 6508 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(optimize_function_for_size_p (cfun)))) && (
#line 12072 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_GENERIC))))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 1515:  /* sse4a_vmmovntv2df */
    case 1514:  /* sse4a_vmmovntv4sf */
    case 1513:  /* sse4a_movntdf */
    case 1512:  /* sse4a_movntsf */
    case 1215:  /* sse_movss */
    case 1192:  /* sse2_cvtss2sd */
    case 1191:  /* sse2_cvtsd2ss */
    case 1178:  /* sse2_cvtsi2sd */
    case 1165:  /* sse_cvtsi2ss */
    case 1081:  /* sse2_vmmaskcmpv2df3 */
    case 1080:  /* sse_vmmaskcmpv4sf3 */
    case 1071:  /* avx_vmcmpv2df3 */
    case 1070:  /* avx_vmcmpv4sf3 */
    case 1043:  /* sse2_vmsminv2df3 */
    case 1042:  /* sse2_vmsmaxv2df3 */
    case 1041:  /* sse_vmsminv4sf3 */
    case 1040:  /* sse_vmsmaxv4sf3 */
    case 1023:  /* sse_vmrsqrtv4sf2 */
    case 1020:  /* sse2_vmsqrtv2df2 */
    case 1019:  /* sse_vmsqrtv4sf2 */
    case 1014:  /* sse_vmrcpv4sf2 */
    case 1011:  /* sse2_vmdivv2df3 */
    case 1010:  /* sse_vmdivv4sf3 */
    case 1005:  /* sse2_vmmulv2df3 */
    case 1004:  /* sse_vmmulv4sf3 */
    case 999:  /* sse2_vmsubv2df3 */
    case 998:  /* sse2_vmaddv2df3 */
    case 997:  /* sse_vmsubv4sf3 */
    case 996:  /* sse_vmaddv4sf3 */
    case 788:  /* *ieee_smindf3 */
    case 787:  /* *ieee_smaxdf3 */
    case 786:  /* *ieee_sminsf3 */
    case 785:  /* *ieee_smaxsf3 */
    case 784:  /* smindf3 */
    case 783:  /* smaxdf3 */
    case 782:  /* sminsf3 */
    case 781:  /* smaxsf3 */
    case 742:  /* movmsk_df */
    case 700:  /* sse4_1_rounddf2 */
    case 699:  /* sse4_1_roundsf2 */
    case 670:  /* *sqrtdf2_sse */
    case 669:  /* *sqrtsf2_sse */
    case 668:  /* *rsqrtsf2_sse */
    case 635:  /* *rcpsf2_sse */
    case 502:  /* setcc_df_sse */
    case 501:  /* setcc_sf_sse */
    case 211:  /* *floatdidf2_sse_nointerunit */
    case 210:  /* *floatsidf2_sse_nointerunit */
    case 209:  /* *floatdisf2_sse_nointerunit */
    case 208:  /* *floatsisf2_sse_nointerunit */
    case 207:  /* *floatdidf2_sse_interunit */
    case 206:  /* *floatsidf2_sse_interunit */
    case 205:  /* *floatdisf2_sse_interunit */
    case 204:  /* *floatsisf2_sse_interunit */
    case 203:  /* *floatsidf2_sse_with_temp */
    case 202:  /* *floatsisf2_sse_with_temp */
    case 201:  /* *floatsidf2_vector_sse */
    case 200:  /* *floatsisf2_vector_sse */
    case 148:  /* fix_truncdfsi_sse */
    case 147:  /* fix_truncsfsi_sse */
    case 134:  /* *truncdfsf_fast_sse */
    case 129:  /* *extendsfdf2_sse */
    case 562:  /* simple_return_internal_long */
    case 575:  /* *tzcntsi_1 */
    case 579:  /* clzhi2_lzcnt */
    case 580:  /* clzsi2_lzcnt */
    case 601:  /* popcounthi2 */
    case 602:  /* popcountsi2 */
    case 603:  /* *popcounthi2_cmp */
    case 604:  /* *popcountsi2_cmp */
    case 605:  /* *popcountdi2_cmp */
    case 750:  /* *rep_movsi */
    case 751:  /* *rep_movsi */
    case 752:  /* *rep_movqi */
    case 753:  /* *rep_movqi */
    case 760:  /* *rep_stossi */
    case 761:  /* *rep_stossi */
    case 762:  /* *rep_stosqi */
    case 763:  /* *rep_stosqi */
    case 764:  /* *cmpstrnqi_nz_1 */
    case 765:  /* *cmpstrnqi_nz_1 */
    case 766:  /* *cmpstrnqi_1 */
    case 767:  /* *cmpstrnqi_1 */
    case 768:  /* *strlenqi_1 */
    case 769:  /* *strlenqi_1 */
    case 810:  /* sse4_2_crc32qi */
    case 811:  /* sse4_2_crc32hi */
    case 812:  /* sse4_2_crc32si */
    case 1166:  /* sse_cvtss2si */
    case 1167:  /* sse_cvtss2si_2 */
    case 1168:  /* sse_cvttss2si */
    case 1179:  /* sse2_cvtsd2si */
    case 1180:  /* sse2_cvtsd2si_2 */
    case 1181:  /* sse2_cvttsd2si */
    case 1187:  /* *sse2_cvtpd2dq */
    case 1205:  /* sse3_movshdup */
    case 1207:  /* sse3_movsldup */
    case 1430:  /* sse2_pshuflw_1 */
    case 1432:  /* sse2_pshufhw_1 */
    case 1518:  /* sse4a_insertqi */
    case 1519:  /* sse4a_insertq */
      return 1;

    case -1:
      if (GET_CODE (PATTERN (insn)) != ASM_INPUT
          && asm_noperands (PATTERN (insn)) < 0)
        fatal_insn_not_found (insn);
      if (((cached_type = get_attr_type (insn)) == TYPE_SSEMULADD) || ((cached_type == TYPE_SSE4ARG) || ((cached_type == TYPE_SSEIADD1) || (cached_type == TYPE_SSECVT1))))
        {
	  return 0;
        }
      else if ((get_attr_unit (insn) == UNIT_SSE) && (((cached_mode = get_attr_mode (insn)) == MODE_SF) || (cached_mode == MODE_DF)))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    default:
      return 0;

    }
}

int
get_attr_prefix_data16 (rtx insn ATTRIBUTE_UNUSED)
{
  enum attr_mode cached_mode ATTRIBUTE_UNUSED;
  enum attr_type cached_type ATTRIBUTE_UNUSED;

  switch (recog_memoized (insn))
    {
    case 1444:  /* vec_concatv2di */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0xf))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 1440:  /* *vec_concatv2si_sse4_1 */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x1f))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 1437:  /* *vec_extractv2di_1 */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0xe))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 1261:  /* *vec_concatv2df */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x7))
        {
	  if (((1 << which_alternative) & 0x3))
	    {
	      return 1;
	    }
	  else
	    {
	      return 0;
	    }
        }
      else if (which_alternative == 3)
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 1259:  /* sse2_movsd */
      extract_constrain_insn_cached (insn);
      if ((((1 << which_alternative) & 0x14)) && (! (
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX))))
        {
	  return 1;
        }
      else
        {
	  if (which_alternative == 5)
	    {
	      return 1;
	    }
	  else
	    {
	      return 0;
	    }
        }

    case 1258:  /* sse2_loadlpd */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return 0;
        }
      else if (which_alternative == 1)
        {
	  return 1;
        }
      else if (((1 << which_alternative) & 0x3c))
        {
	  if (which_alternative == 5)
	    {
	      return 1;
	    }
	  else
	    {
	      return 0;
	    }
        }
      else if (which_alternative == 6)
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 1257:  /* sse2_loadhpd */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return 1;
        }
      else
        {
	  if (((1 << which_alternative) & 0xc))
	    {
	      return 1;
	    }
	  else
	    {
	      return 0;
	    }
        }

    case 1253:  /* sse2_storehpd */
      extract_constrain_insn_cached (insn);
      if ((which_alternative == 0) && (! (
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX))))
        {
	  return 1;
        }
      else
        {
	  if (which_alternative == 2)
	    {
	      return 1;
	    }
	  else
	    {
	      return 0;
	    }
        }

    case 1245:  /* *vec_interleave_lowv2df */
    case 1243:  /* *vec_interleave_highv2df */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x7))
        {
	  if (((1 << which_alternative) & 0x3))
	    {
	      return 1;
	    }
	  else
	    {
	      return 0;
	    }
        }
      else if (which_alternative == 3)
        {
	  return 1;
        }
      else if (which_alternative == 4)
        {
	  return 0;
        }
      else
        {
	  return 1;
        }

    case 1224:  /* vec_setv4sf_0 */
    case 1223:  /* vec_setv4si_0 */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0xc0))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 1220:  /* *vec_concatv2sf_sse4_1 */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return 0;
        }
      else if (which_alternative == 2)
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 1175:  /* sse2_cvtpi2pd */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return 1;
        }
      else
        {
	  return 1;
        }

    case 1399:  /* *xorv2di3 */
    case 1398:  /* *iorv2di3 */
    case 1397:  /* *andv2di3 */
    case 1393:  /* *xorv4si3 */
    case 1392:  /* *iorv4si3 */
    case 1391:  /* *andv4si3 */
    case 1387:  /* *xorv8hi3 */
    case 1386:  /* *iorv8hi3 */
    case 1385:  /* *andv8hi3 */
    case 1381:  /* *xorv16qi3 */
    case 1380:  /* *iorv16qi3 */
    case 1379:  /* *andv16qi3 */
    case 1375:  /* *andnotv2di3 */
    case 1373:  /* *andnotv4si3 */
    case 1371:  /* *andnotv8hi3 */
    case 1369:  /* *andnotv16qi3 */
    case 1113:  /* *xortf3 */
    case 1112:  /* *iortf3 */
    case 1111:  /* *andtf3 */
    case 1104:  /* *andnottf3 */
      extract_constrain_insn_cached (insn);
      if ((which_alternative == 0) && (get_attr_mode (insn) == MODE_TI))
        {
	  return 1;
        }
      else
        {
	  if (get_attr_mode (insn) == MODE_TI)
	    {
	      return 1;
	    }
	  else
	    {
	      return 0;
	    }
        }

    case 976:  /* sse3_lddqu */
      extract_constrain_insn_cached (insn);
      if (
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 974:  /* sse2_storedqu */
    case 972:  /* sse2_loaddqu */
      extract_constrain_insn_cached (insn);
      if (
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX))
        {
	  if (get_attr_mode (insn) == MODE_TI)
	    {
	      return 1;
	    }
	  else
	    {
	      return 0;
	    }
        }
      else
        {
	  return 1;
        }

    case 1577:  /* avx_roundpd256 */
    case 1576:  /* sse4_1_roundps */
    case 1575:  /* avx_roundps256 */
    case 982:  /* avx_movntv4di */
    case 973:  /* avx_storedqu256 */
    case 971:  /* avx_loaddqu256 */
      extract_constrain_insn_cached (insn);
      if (
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX))
        {
	  return 0;
        }
      else
        {
	  return 1;
        }

    case 1110:  /* *xordf3 */
    case 1109:  /* *iordf3 */
    case 1108:  /* *anddf3 */
    case 1103:  /* *andnotdf3 */
    case 1101:  /* *xorv2df3 */
    case 1100:  /* *iorv2df3 */
    case 1099:  /* *andv2df3 */
    case 1089:  /* sse2_andnotv2df3 */
    case 970:  /* sse2_storeupd */
    case 966:  /* sse2_loadupd */
      if (get_attr_mode (insn) == MODE_V2DF)
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 960:  /* *movv2df_internal */
      if (((cached_mode = get_attr_mode (insn)) == MODE_V2DF) || (cached_mode == MODE_TI))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 938:  /* *vec_extractv2si_1 */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x6))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 839:  /* *movv1di_internal */
    case 838:  /* *movv2si_internal */
    case 837:  /* *movv4hi_internal */
    case 836:  /* *movv8qi_internal */
      extract_constrain_insn_cached (insn);
      if ((which_alternative == 8) && (! (
#line 540 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_AVX))))
        {
	  return 1;
        }
      else
        {
	  if (which_alternative == 6)
	    {
	      return 1;
	    }
	  else
	    {
	      return 0;
	    }
        }

    case 812:  /* sse4_2_crc32si */
    case 811:  /* sse4_2_crc32hi */
    case 810:  /* sse4_2_crc32qi */
      extract_insn_cached (insn);
      if (GET_MODE (operands[2]) == HImode)
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 1579:  /* sse4_1_roundss */
    case 1530:  /* avx_dppd256 */
    case 1529:  /* sse4_1_dpps */
    case 1528:  /* avx_dpps256 */
    case 1526:  /* avx_blendvpd256 */
    case 1525:  /* sse4_1_blendvps */
    case 1524:  /* avx_blendvps256 */
    case 1522:  /* avx_blendpd256 */
    case 1521:  /* sse4_1_blendps */
    case 1520:  /* avx_blendps256 */
    case 1500:  /* avx2_palignrv2ti */
    case 1495:  /* avx2_psignv8si3 */
    case 1493:  /* avx2_psignv16hi3 */
    case 1491:  /* avx2_psignv32qi3 */
    case 1488:  /* avx2_pshufbv32qi3 */
    case 1485:  /* *avx2_pmulhrswv16hi3 */
    case 1449:  /* avx2_psadbw */
    case 1447:  /* *avx2_uavgv16hi3 */
    case 1445:  /* *avx2_uavgv32qi3 */
    case 1438:  /* *vec_dupv4si */
    case 1404:  /* avx2_packuswb */
    case 1402:  /* avx2_packssdw */
    case 1400:  /* avx2_packsswb */
    case 1326:  /* avx2_lshrv2ti3 */
    case 1324:  /* avx2_ashlv2ti3 */
    case 1321:  /* lshrv4di3 */
    case 1320:  /* ashlv4di3 */
    case 1317:  /* lshrv8si3 */
    case 1316:  /* ashlv8si3 */
    case 1313:  /* lshrv16hi3 */
    case 1312:  /* ashlv16hi3 */
    case 1310:  /* ashrv8si3 */
    case 1308:  /* ashrv16hi3 */
    case 1297:  /* *umulv16hi3_highpart */
    case 1296:  /* *smulv16hi3_highpart */
    case 1294:  /* *mulv16hi3 */
    case 1275:  /* *subv4di3 */
    case 1274:  /* *addv4di3 */
    case 1271:  /* *subv8si3 */
    case 1270:  /* *addv8si3 */
    case 1267:  /* *subv16hi3 */
    case 1266:  /* *addv16hi3 */
    case 1263:  /* *subv32qi3 */
    case 1262:  /* *addv32qi3 */
    case 1260:  /* vec_dupv2df */
    case 1255:  /* sse2_storelpd */
    case 1228:  /* *sse4_1_extractps */
    case 1226:  /* sse4_1_insertps */
    case 1225:  /* *vec_setv4sf_sse4_1 */
    case 431:  /* *ashlhi3_1 */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 1443:  /* *vec_concatv4si */
    case 1441:  /* *vec_concatv2si_sse2 */
    case 1439:  /* *vec_dupv2di */
    case 1433:  /* sse2_loadld */
    case 333:  /* *andhi_1 */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 238:  /* *addhi_1 */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x7))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 199:  /* *floatsidf2_vector_sse_with_temp */
      extract_constrain_insn_cached (insn);
      if (!((1 << which_alternative) & 0x3))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 608:  /* *bswaphi_lowpart_1 */
    case 187:  /* *floatsidf2_vector_mixed */
      extract_constrain_insn_cached (insn);
      if (which_alternative != 0)
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 185:  /* *floatsidf2_vector_mixed_with_temp */
      extract_constrain_insn_cached (insn);
      if (!((1 << which_alternative) & 0xf))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 117:  /* *zero_extendsidi2 */
      extract_constrain_insn_cached (insn);
      if (!((1 << which_alternative) & 0x1f))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 113:  /* *movsf_internal */
      extract_constrain_insn_cached (insn);
      if ((!((1 << which_alternative) & 0xce1f)) && (get_attr_mode (insn) == MODE_TI))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 112:  /* *movdf_internal */
      extract_constrain_insn_cached (insn);
      if ((
#line 659 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SSE2)) && ((((1 << which_alternative) & 0x880)) && (
#line 3325 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SSE_SPLIT_REGS))))
        {
	  return 1;
        }
      else
        {
	  if ((!((1 << which_alternative) & 0x1f)) && (((cached_mode = get_attr_mode (insn)) == MODE_V2DF) || (cached_mode == MODE_TI)))
	    {
	      return 1;
	    }
	  else
	    {
	      return 0;
	    }
        }

    case 79:  /* *movhi_internal */
      if (get_attr_mode (insn) == MODE_HI)
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 78:  /* *movsi_internal */
      extract_constrain_insn_cached (insn);
      if ((((1 << which_alternative) & 0xf80)) && ((!((1 << which_alternative) & 0xcc)) && ((!((1 << which_alternative) & 0xf00)) || (
#line 659 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_SSE2)))))
        {
	  return 1;
        }
      else
        {
	  if ((((1 << which_alternative) & 0xfc0)) && (get_attr_mode (insn) == MODE_TI))
	    {
	      return 1;
	    }
	  else
	    {
	      return 0;
	    }
        }

    case 77:  /* *movdi_internal */
      extract_constrain_insn_cached (insn);
      if ((!((1 << which_alternative) & 0x1f)) && (get_attr_mode (insn) == MODE_TI))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 959:  /* *movv4df_internal */
    case 958:  /* *movv4sf_internal */
    case 957:  /* *movv8sf_internal */
    case 956:  /* *movv1ti_internal */
    case 955:  /* *movv2ti_internal */
    case 954:  /* *movv2di_internal */
    case 953:  /* *movv4di_internal */
    case 952:  /* *movv4si_internal */
    case 951:  /* *movv8si_internal */
    case 950:  /* *movv8hi_internal */
    case 949:  /* *movv16hi_internal */
    case 948:  /* *movv16qi_internal */
    case 947:  /* *movv32qi_internal */
    case 110:  /* *movtf_internal_sse */
    case 76:  /* *movti_internal_sse */
      if (get_attr_mode (insn) == MODE_TI)
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    case 52:  /* *cmpiudf_mixed */
    case 50:  /* *cmpidf_mixed */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return 0;
        }
      else
        {
	  return 1;
        }

    case 1852:  /* *avx2_gatherdiv4si_2 */
    case 1851:  /* *avx2_gatherdiv4si_2 */
    case 1846:  /* *avx2_gatherdiv2df_2 */
    case 1845:  /* *avx2_gatherdiv2df_2 */
    case 1844:  /* *avx2_gatherdiv2di_2 */
    case 1843:  /* *avx2_gatherdiv2di_2 */
    case 1836:  /* *avx2_gatherdiv4si */
    case 1835:  /* *avx2_gatherdiv4si */
    case 1830:  /* *avx2_gatherdiv2df */
    case 1829:  /* *avx2_gatherdiv2df */
    case 1828:  /* *avx2_gatherdiv2di */
    case 1827:  /* *avx2_gatherdiv2di */
    case 1820:  /* *avx2_gathersiv4si_2 */
    case 1819:  /* *avx2_gathersiv4si_2 */
    case 1814:  /* *avx2_gathersiv2df_2 */
    case 1813:  /* *avx2_gathersiv2df_2 */
    case 1812:  /* *avx2_gathersiv2di_2 */
    case 1811:  /* *avx2_gathersiv2di_2 */
    case 1804:  /* *avx2_gathersiv4si */
    case 1803:  /* *avx2_gathersiv4si */
    case 1798:  /* *avx2_gathersiv2df */
    case 1797:  /* *avx2_gathersiv2df */
    case 1796:  /* *avx2_gathersiv2di */
    case 1795:  /* *avx2_gathersiv2di */
    case 1782:  /* avx2_lshrvv2di */
    case 1781:  /* avx2_ashlvv2di */
    case 1778:  /* avx2_lshrvv4si */
    case 1777:  /* avx2_ashlvv4si */
    case 1774:  /* avx2_ashrvv4si */
    case 1767:  /* avx2_maskstoreq */
    case 1766:  /* avx2_maskstored */
    case 1763:  /* avx_maskstorepd */
    case 1759:  /* avx2_maskloadq */
    case 1758:  /* avx2_maskloadd */
    case 1755:  /* avx_maskloadpd */
    case 1733:  /* avx_vpermilvarv2df3 */
    case 1729:  /* *avx_vpermilpv2df */
    case 1698:  /* avx2_pbroadcastv2di */
    case 1696:  /* avx2_pbroadcastv4si */
    case 1694:  /* avx2_pbroadcastv8hi */
    case 1692:  /* avx2_pbroadcastv16qi */
    case 1688:  /* pclmulqdq */
    case 1687:  /* aeskeygenassist */
    case 1686:  /* aesimc */
    case 1685:  /* aesdeclast */
    case 1684:  /* aesdec */
    case 1683:  /* aesenclast */
    case 1682:  /* aesenc */
    case 1641:  /* xop_rotrv2di3 */
    case 1640:  /* xop_rotrv4si3 */
    case 1639:  /* xop_rotrv8hi3 */
    case 1638:  /* xop_rotrv16qi3 */
    case 1637:  /* xop_rotlv2di3 */
    case 1636:  /* xop_rotlv4si3 */
    case 1635:  /* xop_rotlv8hi3 */
    case 1634:  /* xop_rotlv16qi3 */
    case 1580:  /* sse4_1_roundsd */
    case 1578:  /* sse4_1_roundpd */
    case 1574:  /* sse4_1_ptest */
    case 1572:  /* avx_vtestpd */
    case 1568:  /* sse4_1_zero_extendv2siv2di2 */
    case 1567:  /* sse4_1_sign_extendv2siv2di2 */
    case 1564:  /* sse4_1_zero_extendv2hiv2di2 */
    case 1563:  /* sse4_1_sign_extendv2hiv2di2 */
    case 1560:  /* sse4_1_zero_extendv2qiv2di2 */
    case 1559:  /* sse4_1_sign_extendv2qiv2di2 */
    case 1556:  /* sse4_1_zero_extendv4hiv4si2 */
    case 1555:  /* sse4_1_sign_extendv4hiv4si2 */
    case 1552:  /* sse4_1_zero_extendv4qiv4si2 */
    case 1551:  /* sse4_1_sign_extendv4qiv4si2 */
    case 1548:  /* sse4_1_zero_extendv8qiv8hi2 */
    case 1547:  /* sse4_1_sign_extendv8qiv8hi2 */
    case 1544:  /* sse4_1_phminposuw */
    case 1543:  /* avx2_pblenddv4si */
    case 1540:  /* sse4_1_pblendw */
    case 1539:  /* sse4_1_pblendvb */
    case 1537:  /* sse4_1_packusdw */
    case 1535:  /* sse4_1_mpsadbw */
    case 1533:  /* sse4_1_movntdqa */
    case 1531:  /* sse4_1_dppd */
    case 1527:  /* sse4_1_blendvpd */
    case 1523:  /* sse4_1_blendpd */
    case 1501:  /* ssse3_palignrti */
    case 1496:  /* ssse3_psignv4si3 */
    case 1494:  /* ssse3_psignv8hi3 */
    case 1492:  /* ssse3_psignv16qi3 */
    case 1489:  /* ssse3_pshufbv16qi3 */
    case 1486:  /* *ssse3_pmulhrswv8hi3 */
    case 1483:  /* ssse3_pmaddubsw128 */
    case 1479:  /* ssse3_phsubdv4si3 */
    case 1478:  /* ssse3_phadddv4si3 */
    case 1471:  /* ssse3_phsubswv8hi3 */
    case 1470:  /* ssse3_phsubwv8hi3 */
    case 1469:  /* ssse3_phaddswv8hi3 */
    case 1468:  /* ssse3_phaddwv8hi3 */
    case 1454:  /* sse2_movmskpd */
    case 1450:  /* sse2_psadbw */
    case 1448:  /* *sse2_uavgv8hi3 */
    case 1446:  /* *sse2_uavgv16qi3 */
    case 1426:  /* *sse4_1_pextrd */
    case 1425:  /* *sse4_1_pextrw_memory */
    case 1423:  /* *sse4_1_pextrb_memory */
    case 1422:  /* *sse4_1_pextrb_si */
    case 1421:  /* sse4_1_pinsrq */
    case 1420:  /* sse4_1_pinsrd */
    case 1419:  /* sse2_pinsrw */
    case 1418:  /* sse4_1_pinsrb */
    case 1417:  /* vec_interleave_lowv4si */
    case 1415:  /* vec_interleave_highv4si */
    case 1413:  /* vec_interleave_lowv8hi */
    case 1411:  /* vec_interleave_highv8hi */
    case 1409:  /* vec_interleave_lowv16qi */
    case 1407:  /* vec_interleave_highv16qi */
    case 1405:  /* sse2_packuswb */
    case 1403:  /* sse2_packssdw */
    case 1401:  /* sse2_packsswb */
    case 1367:  /* sse2_gtv4si3 */
    case 1366:  /* sse2_gtv8hi3 */
    case 1365:  /* sse2_gtv16qi3 */
    case 1360:  /* sse4_2_gtv2di3 */
    case 1359:  /* *sse2_eqv4si3 */
    case 1358:  /* *sse2_eqv8hi3 */
    case 1357:  /* *sse2_eqv16qi3 */
    case 1356:  /* *sse4_1_eqv2di3 */
    case 1351:  /* *uminv16qi3 */
    case 1350:  /* *umaxv16qi3 */
    case 1349:  /* *sse4_1_uminv4si3 */
    case 1348:  /* *sse4_1_umaxv4si3 */
    case 1347:  /* *sse4_1_uminv8hi3 */
    case 1346:  /* *sse4_1_umaxv8hi3 */
    case 1345:  /* *sminv8hi3 */
    case 1344:  /* *smaxv8hi3 */
    case 1343:  /* *sse4_1_sminv4si3 */
    case 1342:  /* *sse4_1_smaxv4si3 */
    case 1341:  /* *sse4_1_sminv16qi3 */
    case 1340:  /* *sse4_1_smaxv16qi3 */
    case 1327:  /* sse2_lshrv1ti3 */
    case 1325:  /* sse2_ashlv1ti3 */
    case 1323:  /* lshrv2di3 */
    case 1322:  /* ashlv2di3 */
    case 1319:  /* lshrv4si3 */
    case 1318:  /* ashlv4si3 */
    case 1315:  /* lshrv8hi3 */
    case 1314:  /* ashlv8hi3 */
    case 1311:  /* ashrv4si3 */
    case 1309:  /* ashrv8hi3 */
    case 1307:  /* *sse4_1_mulv4si3 */
    case 1305:  /* *sse2_pmaddwd */
    case 1303:  /* *sse4_1_mulv2siv2di3 */
    case 1301:  /* *vec_widen_umult_even_v4si */
    case 1299:  /* *umulv8hi3_highpart */
    case 1298:  /* *smulv8hi3_highpart */
    case 1295:  /* *mulv8hi3 */
    case 1293:  /* *sse2_ussubv8hi3 */
    case 1292:  /* *sse2_sssubv8hi3 */
    case 1291:  /* *sse2_usaddv8hi3 */
    case 1290:  /* *sse2_ssaddv8hi3 */
    case 1289:  /* *avx2_ussubv16hi3 */
    case 1288:  /* *avx2_sssubv16hi3 */
    case 1287:  /* *avx2_usaddv16hi3 */
    case 1286:  /* *avx2_ssaddv16hi3 */
    case 1285:  /* *sse2_ussubv16qi3 */
    case 1284:  /* *sse2_sssubv16qi3 */
    case 1283:  /* *sse2_usaddv16qi3 */
    case 1282:  /* *sse2_ssaddv16qi3 */
    case 1281:  /* *avx2_ussubv32qi3 */
    case 1280:  /* *avx2_sssubv32qi3 */
    case 1279:  /* *avx2_usaddv32qi3 */
    case 1278:  /* *avx2_ssaddv32qi3 */
    case 1277:  /* *subv2di3 */
    case 1276:  /* *addv2di3 */
    case 1273:  /* *subv4si3 */
    case 1272:  /* *addv4si3 */
    case 1269:  /* *subv8hi3 */
    case 1268:  /* *addv8hi3 */
    case 1265:  /* *subv16qi3 */
    case 1264:  /* *addv16qi3 */
    case 1252:  /* sse2_shufpd_v2df */
    case 1251:  /* sse2_shufpd_v2di */
    case 1250:  /* vec_interleave_lowv2di */
    case 1248:  /* vec_interleave_highv2di */
    case 1190:  /* *sse2_cvttpd2dq */
    case 1184:  /* sse2_cvtdq2pd */
    case 1172:  /* sse2_cvtps2dq */
    case 1085:  /* sse2_ucomi */
    case 1083:  /* sse2_comi */
    case 1079:  /* sse2_maskcmpv2df3 */
    case 1075:  /* *sse2_maskcmpv2df3_comm */
    case 1069:  /* avx_cmpv2df3 */
    case 1061:  /* *sse3_hsubv2df3_low */
    case 1060:  /* *sse3_haddv2df3_low */
    case 1059:  /* sse3_hsubv2df3 */
    case 1058:  /* *sse3_haddv2df3 */
    case 1053:  /* sse3_addsubv2df3 */
    case 1051:  /* *ieee_smaxv2df3 */
    case 1047:  /* *ieee_sminv2df3 */
    case 1039:  /* *sminv2df3 */
    case 1038:  /* *smaxv2df3 */
    case 1031:  /* *sminv2df3_finite */
    case 1030:  /* *smaxv2df3_finite */
    case 1018:  /* sse2_sqrtv2df2 */
    case 1009:  /* sse2_divv2df3 */
    case 1003:  /* *mulv2df3 */
    case 995:  /* *subv2df3 */
    case 994:  /* *addv2df3 */
    case 983:  /* sse2_movntv2di */
    case 981:  /* sse2_movntv2df */
    case 961:  /* sse2_movq128 */
    case 773:  /* *movhicc_noc */
    case 757:  /* *strsethi_1 */
    case 756:  /* *strsethi_1 */
    case 747:  /* *strmovhi_1 */
    case 746:  /* *strmovhi_1 */
    case 734:  /* fisthi2_ceil_with_temp */
    case 733:  /* fisthi2_floor_with_temp */
    case 730:  /* fisthi2_ceil */
    case 729:  /* fisthi2_floor */
    case 720:  /* *fisthi2_ceil_1 */
    case 719:  /* *fisthi2_floor_1 */
    case 709:  /* fisthi2_with_temp */
    case 707:  /* fisthi2 */
    case 705:  /* *fisthi2_1 */
    case 655:  /* *fop_xf_3_i387 */
    case 653:  /* *fop_xf_2_i387 */
    case 645:  /* *fop_df_3_i387 */
    case 644:  /* *fop_sf_3_i387 */
    case 641:  /* *fop_df_2_i387 */
    case 640:  /* *fop_sf_2_i387 */
    case 612:  /* *parityhi2_cmp */
    case 609:  /* bswaphi_lowpart */
    case 603:  /* *popcounthi2_cmp */
    case 601:  /* popcounthi2 */
    case 600:  /* *bsrhi */
    case 579:  /* clzhi2_lzcnt */
    case 577:  /* ctzhi2 */
    case 492:  /* *rotrhi3_1 */
    case 491:  /* *rotlhi3_1 */
    case 473:  /* *ashrhi3_cconly */
    case 472:  /* *lshrhi3_cconly */
    case 465:  /* *ashrhi3_cmp */
    case 464:  /* *lshrhi3_cmp */
    case 459:  /* *ashrhi3_1 */
    case 458:  /* *lshrhi3_1 */
    case 439:  /* *ashlhi3_cconly */
    case 435:  /* *ashlhi3_cmp */
    case 421:  /* *one_cmplhi2_2 */
    case 416:  /* *one_cmplhi2_1 */
    case 387:  /* *neghi2_cmpz */
    case 383:  /* *neghi2_1 */
    case 368:  /* *xorhi_3 */
    case 367:  /* *iorhi_3 */
    case 358:  /* *xorhi_2 */
    case 357:  /* *iorhi_2 */
    case 346:  /* *xorhi_1 */
    case 345:  /* *iorhi_1 */
    case 338:  /* *andhi_2 */
    case 326:  /* *testhi_1 */
    case 321:  /* *udivmodhi4_noext */
    case 319:  /* *udivmodhi4 */
    case 315:  /* *divmodhi4_noext */
    case 313:  /* *divmodhi4 */
    case 303:  /* *mulhi3_1 */
    case 297:  /* *subhi3_cc_overflow */
    case 296:  /* *addhi3_cc_overflow */
    case 292:  /* *subhi3_cconly_overflow */
    case 289:  /* *addhi3_cconly_overflow */
    case 281:  /* *subhi3_carry */
    case 280:  /* *addhi3_carry */
    case 275:  /* *subhi_3 */
    case 271:  /* *subhi_2 */
    case 266:  /* *subhi_1 */
    case 253:  /* *addhi_5 */
    case 250:  /* *addhi_4 */
    case 246:  /* *addhi_3 */
    case 242:  /* *addhi_2 */
    case 168:  /* x86_fldcw_1 */
    case 167:  /* x86_fnstcw_1 */
    case 165:  /* fix_trunchi_i387_with_temp */
    case 163:  /* fix_trunchi_i387 */
    case 158:  /* *fix_trunchi_i387_1 */
    case 155:  /* fix_trunchi_i387_fisttp_with_temp */
    case 152:  /* fix_trunchi_i387_fisttp */
    case 149:  /* fix_trunchi_fisttp_i387_1 */
    case 127:  /* extendqihi2 */
    case 97:  /* *movstricthi_xor */
    case 95:  /* *movstricthi_1 */
    case 93:  /* *swaphi_2 */
    case 86:  /* *movabshi_2 */
    case 82:  /* *movabshi_1 */
    case 56:  /* *cmpiudf_sse */
    case 54:  /* *cmpidf_sse */
    case 43:  /* *cmpxf_hi_cc_i387 */
    case 42:  /* *cmpdf_hi_cc_i387 */
    case 41:  /* *cmpsf_hi_cc_i387 */
    case 37:  /* *cmpxf_hi_i387 */
    case 36:  /* *cmpdf_hi_i387 */
    case 35:  /* *cmpsf_hi_i387 */
    case 10:  /* *cmphi_minus_1 */
    case 6:  /* *cmphi_1 */
    case 2:  /* *cmphi_ccno_1 */
    case 1176:  /* sse2_cvtpd2pi */
    case 1177:  /* sse2_cvttpd2pi */
    case 1194:  /* *sse2_cvtpd2ps */
    case 1424:  /* *sse2_pextrw_si */
    case 1428:  /* sse2_pshufd_1 */
    case 1456:  /* sse2_pmovmskb */
    case 1457:  /* *sse2_maskmovdqu */
    case 1458:  /* *sse2_maskmovdqu */
    case 1503:  /* absv32qi2 */
    case 1504:  /* absv16qi2 */
    case 1505:  /* absv16hi2 */
    case 1506:  /* absv8hi2 */
    case 1507:  /* absv8si2 */
    case 1508:  /* absv4si2 */
    case 1516:  /* sse4a_extrqi */
    case 1517:  /* sse4a_extrq */
    case 1581:  /* sse4_2_pcmpestr */
    case 1582:  /* *sse4_2_pcmpestr_unaligned */
    case 1583:  /* sse4_2_pcmpestri */
    case 1584:  /* sse4_2_pcmpestrm */
    case 1585:  /* sse4_2_pcmpestr_cconly */
    case 1586:  /* sse4_2_pcmpistr */
    case 1587:  /* *sse4_2_pcmpistr_unaligned */
    case 1588:  /* sse4_2_pcmpistri */
    case 1589:  /* sse4_2_pcmpistrm */
    case 1590:  /* sse4_2_pcmpistr_cconly */
      return 1;

    case -1:
      if (GET_CODE (PATTERN (insn)) != ASM_INPUT
          && asm_noperands (PATTERN (insn)) < 0)
        fatal_insn_not_found (insn);
      if (((cached_type = get_attr_type (insn)) == TYPE_SSEMULADD) || ((cached_type == TYPE_SSE4ARG) || ((cached_type == TYPE_SSEIADD1) || (cached_type == TYPE_SSECVT1))))
        {
	  return 0;
        }
      else if ((cached_mode = get_attr_mode (insn)) == MODE_HI)
        {
	  return 1;
        }
      else if ((get_attr_unit (insn) == UNIT_SSE) && ((cached_mode == MODE_V2DF) || (cached_mode == MODE_TI)))
        {
	  return 1;
        }
      else
        {
	  return 0;
        }

    default:
      return 0;

    }
}

enum attr_type
get_attr_type (rtx insn ATTRIBUTE_UNUSED)
{
  switch (recog_memoized (insn))
    {
    case 1723:  /* *avx_vperm_broadcast_v4sf */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return TYPE_SSEMOV;
        }
      else
        {
	  return TYPE_SSELOG1;
        }

    case 1722:  /* avx_vbroadcastf128_v4df */
    case 1721:  /* avx_vbroadcastf128_v8sf */
    case 1720:  /* avx_vbroadcastf128_v4di */
    case 1719:  /* avx_vbroadcastf128_v8si */
    case 1718:  /* avx_vbroadcastf128_v16hi */
    case 1717:  /* avx_vbroadcastf128_v32qi */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return TYPE_SSEMOV;
        }
      else
        {
	  return TYPE_SSELOG1;
        }

    case 1444:  /* vec_concatv2di */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return TYPE_SSEMOV;
        }
      else if (((1 << which_alternative) & 0xc))
        {
	  return TYPE_SSELOG;
        }
      else
        {
	  return TYPE_SSEMOV;
        }

    case 1443:  /* *vec_concatv4si */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return TYPE_SSELOG;
        }
      else
        {
	  return TYPE_SSEMOV;
        }

    case 1439:  /* *vec_dupv2di */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x7))
        {
	  return TYPE_SSELOG1;
        }
      else
        {
	  return TYPE_SSEMOV;
        }

    case 1437:  /* *vec_extractv2di_1 */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return TYPE_SSEMOV;
        }
      else if (((1 << which_alternative) & 0x6))
        {
	  return TYPE_SSEISHFT1;
        }
      else
        {
	  return TYPE_SSEMOV;
        }

    case 1257:  /* sse2_loadhpd */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return TYPE_SSEMOV;
        }
      else if (((1 << which_alternative) & 0xc))
        {
	  return TYPE_SSELOG;
        }
      else if (which_alternative == 4)
        {
	  return TYPE_SSEMOV;
        }
      else if (which_alternative == 5)
        {
	  return TYPE_FMOV;
        }
      else
        {
	  return TYPE_IMOV;
        }

    case 1255:  /* sse2_storelpd */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x7))
        {
	  return TYPE_SSEMOV;
        }
      else if (which_alternative == 3)
        {
	  return TYPE_FMOV;
        }
      else
        {
	  return TYPE_IMOV;
        }

    case 1253:  /* sse2_storehpd */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return TYPE_SSEMOV;
        }
      else if (((1 << which_alternative) & 0x6))
        {
	  return TYPE_SSELOG1;
        }
      else if (which_alternative == 3)
        {
	  return TYPE_SSEMOV;
        }
      else if (which_alternative == 4)
        {
	  return TYPE_FMOV;
        }
      else
        {
	  return TYPE_IMOV;
        }

    case 1228:  /* *sse4_1_extractps */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return TYPE_SSELOG;
        }
      else
        {
	  return TYPE_OTHER;
        }

    case 1440:  /* *vec_concatv2si_sse4_1 */
    case 1220:  /* *vec_concatv2sf_sse4_1 */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0xf))
        {
	  return TYPE_SSELOG;
        }
      else if (which_alternative == 4)
        {
	  return TYPE_SSEMOV;
        }
      else if (which_alternative == 5)
        {
	  return TYPE_MMXCVT;
        }
      else
        {
	  return TYPE_MMXMOV;
        }

    case 1214:  /* sse_loadlps */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return TYPE_SSESHUF;
        }
      else
        {
	  return TYPE_SSEMOV;
        }

    case 938:  /* *vec_extractv2si_1 */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return TYPE_MMXCVT;
        }
      else if (((1 << which_alternative) & 0xe))
        {
	  return TYPE_SSELOG1;
        }
      else if (which_alternative == 4)
        {
	  return TYPE_MMXMOV;
        }
      else if (which_alternative == 5)
        {
	  return TYPE_SSEMOV;
        }
      else
        {
	  return TYPE_IMOV;
        }

    case 778:  /* *movsfcc_1_387 */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return TYPE_FCMOV;
        }
      else
        {
	  return TYPE_ICMOV;
        }

    case 777:  /* *movdfcc_1 */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return TYPE_FCMOV;
        }
      else
        {
	  return TYPE_MULTI;
        }

    case 606:  /* *bswapsi2_movbe */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return TYPE_BITMANIP;
        }
      else
        {
	  return TYPE_IMOV;
        }

    case 333:  /* *andhi_1 */
    case 332:  /* *andsi_1 */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return TYPE_ALU;
        }
      else
        {
	  return TYPE_IMOVX;
        }

    case 189:  /* *floatsidf2_mixed_with_temp */
    case 188:  /* *floatsisf2_mixed_with_temp */
    case 185:  /* *floatsidf2_vector_mixed_with_temp */
    case 184:  /* *floatsisf2_vector_mixed_with_temp */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return TYPE_FMOV;
        }
      else if (which_alternative == 1)
        {
	  return TYPE_MULTI;
        }
      else
        {
	  return TYPE_SSEICVT;
        }

    case 136:  /* *truncdfsf_mixed */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return TYPE_FMOV;
        }
      else if (which_alternative == 1)
        {
	  return TYPE_SSECVT;
        }
      else
        {
	  return TYPE_MULTI;
        }

    case 128:  /* *extendsfdf2_mixed */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return TYPE_FMOV;
        }
      else
        {
	  return TYPE_SSECVT;
        }

    case 117:  /* *zero_extendsidi2 */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x7))
        {
	  return TYPE_MULTI;
        }
      else if (((1 << which_alternative) & 0x18))
        {
	  return TYPE_MMXMOV;
        }
      else
        {
	  return TYPE_SSEMOV;
        }

    case 111:  /* *movxf_internal */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x7))
        {
	  return TYPE_FMOV;
        }
      else
        {
	  return TYPE_MULTI;
        }

    case 960:  /* *movv2df_internal */
    case 959:  /* *movv4df_internal */
    case 958:  /* *movv4sf_internal */
    case 957:  /* *movv8sf_internal */
    case 956:  /* *movv1ti_internal */
    case 955:  /* *movv2ti_internal */
    case 954:  /* *movv2di_internal */
    case 953:  /* *movv4di_internal */
    case 952:  /* *movv4si_internal */
    case 951:  /* *movv8si_internal */
    case 950:  /* *movv8hi_internal */
    case 949:  /* *movv16hi_internal */
    case 948:  /* *movv16qi_internal */
    case 947:  /* *movv32qi_internal */
    case 110:  /* *movtf_internal_sse */
    case 76:  /* *movti_internal_sse */
    case 75:  /* *movoi_internal_avx */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return TYPE_SSELOG1;
        }
      else
        {
	  return TYPE_SSEMOV;
        }

    case 1:  /* *cmpqi_ccno_1 */
    case 2:  /* *cmphi_ccno_1 */
    case 3:  /* *cmpsi_ccno_1 */
    case 4:  /* *cmpdi_ccno_1 */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return TYPE_TEST;
        }
      else
        {
	  return TYPE_ICMP;
        }

    case 49:  /* *cmpisf_mixed */
    case 50:  /* *cmpidf_mixed */
    case 51:  /* *cmpiusf_mixed */
    case 52:  /* *cmpiudf_mixed */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return TYPE_FCMP;
        }
      else
        {
	  return TYPE_SSECOMI;
        }

    case 77:  /* *movdi_internal */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return TYPE_MULTI;
        }
      else if (which_alternative == 2)
        {
	  return TYPE_MMX;
        }
      else if (((1 << which_alternative) & 0x18))
        {
	  return TYPE_MMXMOV;
        }
      else if (((1 << which_alternative) & 0x220))
        {
	  return TYPE_SSELOG1;
        }
      else if (((1 << which_alternative) & 0x6000))
        {
	  return TYPE_SSECVT;
        }
      else
        {
	  return TYPE_SSEMOV;
        }

    case 78:  /* *movsi_internal */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 2)
        {
	  return TYPE_MMX;
        }
      else if (((1 << which_alternative) & 0x38))
        {
	  return TYPE_MMXMOV;
        }
      else if (which_alternative == 6)
        {
	  return TYPE_SSELOG1;
        }
      else if (((1 << which_alternative) & 0xf80))
        {
	  return TYPE_SSEMOV;
        }
      else if (pic_32bit_operand (operands[1], VOIDmode))
        {
	  return TYPE_LEA;
        }
      else
        {
	  return TYPE_IMOV;
        }

    case 79:  /* *movhi_internal */
      extract_constrain_insn_cached (insn);
      if (
#line 6508 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(optimize_function_for_size_p (cfun)))
        {
	  return TYPE_IMOV;
        }
      else if ((which_alternative == 0) && ((! (
#line 2276 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_PARTIAL_REG_STALL))) || (! (
#line 2219 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_HIMODE_MATH)))))
        {
	  return TYPE_IMOV;
        }
      else if ((((1 << which_alternative) & 0x6)) && (aligned_operand (operands[1], HImode)))
        {
	  return TYPE_IMOV;
        }
      else if ((
#line 2532 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_MOVX)) && (((1 << which_alternative) & 0x5)))
        {
	  return TYPE_IMOVX;
        }
      else
        {
	  return TYPE_IMOV;
        }

    case 80:  /* *movqi_internal */
      extract_constrain_insn_cached (insn);
      if ((which_alternative == 5) && (! (aligned_operand (operands[1], QImode))))
        {
	  return TYPE_IMOVX;
        }
      else if (
#line 6508 "../../gcc-4.8.1/gcc/config/i386/sse.md"
(optimize_function_for_size_p (cfun)))
        {
	  return TYPE_IMOV;
        }
      else if ((which_alternative == 3) && ((! (
#line 2276 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_PARTIAL_REG_STALL))) || (! (
#line 2277 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_QIMODE_MATH)))))
        {
	  return TYPE_IMOV;
        }
      else if (((1 << which_alternative) & 0x28))
        {
	  return TYPE_IMOVX;
        }
      else if ((
#line 2532 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_MOVX)) && (which_alternative == 2))
        {
	  return TYPE_IMOVX;
        }
      else
        {
	  return TYPE_IMOV;
        }

    case 100:  /* *movqi_extv_1 */
    case 102:  /* *movqi_extzv_2 */
      extract_constrain_insn_cached (insn);
      if ((register_operand (operands[0], QImode)) && ((! (QIreg_operand (operands[0], QImode))) || (
#line 2532 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_MOVX))))
        {
	  return TYPE_IMOVX;
        }
      else
        {
	  return TYPE_IMOV;
        }

    case 109:  /* *pushsf */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return TYPE_MULTI;
        }
      else if (which_alternative == 1)
        {
	  return TYPE_PUSH;
        }
      else
        {
	  return TYPE_MULTI;
        }

    case 112:  /* *movdf_internal */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x7))
        {
	  return TYPE_FMOV;
        }
      else if (((1 << which_alternative) & 0x18))
        {
	  return TYPE_MULTI;
        }
      else if (((1 << which_alternative) & 0x220))
        {
	  return TYPE_SSELOG1;
        }
      else
        {
	  return TYPE_SSEMOV;
        }

    case 113:  /* *movsf_internal */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x7))
        {
	  return TYPE_FMOV;
        }
      else if (((1 << which_alternative) & 0x18))
        {
	  return TYPE_IMOV;
        }
      else if (which_alternative == 5)
        {
	  return TYPE_SSELOG1;
        }
      else if (((1 << which_alternative) & 0xce00))
        {
	  return TYPE_MMXMOV;
        }
      else
        {
	  return TYPE_SSEMOV;
        }

    case 133:  /* *truncdfsf_fast_mixed */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return TYPE_FMOV;
        }
      else
        {
	  return TYPE_SSECVT;
        }

    case 193:  /* *floatdidf2_mixed_interunit */
    case 192:  /* *floatsidf2_mixed_interunit */
    case 191:  /* *floatdisf2_mixed_interunit */
    case 190:  /* *floatsisf2_mixed_interunit */
    case 186:  /* *floatsisf2_vector_mixed */
    case 187:  /* *floatsidf2_vector_mixed */
    case 194:  /* *floatsisf2_mixed_nointerunit */
    case 195:  /* *floatdisf2_mixed_nointerunit */
    case 196:  /* *floatsidf2_mixed_nointerunit */
    case 197:  /* *floatdidf2_mixed_nointerunit */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return TYPE_FMOV;
        }
      else
        {
	  return TYPE_SSEICVT;
        }

    case 140:  /* *truncxfdf2_mixed */
    case 139:  /* *truncxfsf2_mixed */
    case 137:  /* *truncdfsf_i387 */
    case 172:  /* *floathisf2_i387_with_temp */
    case 173:  /* *floathidf2_i387_with_temp */
    case 174:  /* *floathixf2_i387_with_temp */
    case 212:  /* *floatsisf2_i387_with_temp */
    case 213:  /* *floatsidf2_i387_with_temp */
    case 214:  /* *floatsixf2_i387_with_temp */
    case 215:  /* *floatdisf2_i387_with_temp */
    case 216:  /* *floatdidf2_i387_with_temp */
    case 217:  /* *floatdixf2_i387_with_temp */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return TYPE_FMOV;
        }
      else
        {
	  return TYPE_MULTI;
        }

    case 236:  /* *addsi_1 */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 3)
        {
	  return TYPE_LEA;
        }
      else if (incdec_operand (operands[2], SImode))
        {
	  return TYPE_INCDEC;
        }
      else
        {
	  return TYPE_ALU;
        }

    case 237:  /* *adddi_1 */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 3)
        {
	  return TYPE_LEA;
        }
      else if (incdec_operand (operands[2], DImode))
        {
	  return TYPE_INCDEC;
        }
      else
        {
	  return TYPE_ALU;
        }

    case 238:  /* *addhi_1 */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 3)
        {
	  return TYPE_LEA;
        }
      else if (incdec_operand (operands[2], HImode))
        {
	  return TYPE_INCDEC;
        }
      else
        {
	  return TYPE_ALU;
        }

    case 239:  /* *addqi_1 */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 5)
        {
	  return TYPE_LEA;
        }
      else if (incdec_operand (operands[2], QImode))
        {
	  return TYPE_INCDEC;
        }
      else
        {
	  return TYPE_ALU;
        }

    case 240:  /* *addqi_1_slp */
      extract_insn_cached (insn);
      if (incdec_operand (operands[1], QImode))
        {
	  return TYPE_INCDEC;
        }
      else
        {
	  return TYPE_ALU1;
        }

    case 242:  /* *addhi_2 */
    case 246:  /* *addhi_3 */
    case 250:  /* *addhi_4 */
    case 253:  /* *addhi_5 */
      extract_insn_cached (insn);
      if (incdec_operand (operands[2], HImode))
        {
	  return TYPE_INCDEC;
        }
      else
        {
	  return TYPE_ALU;
        }

    case 243:  /* *addsi_2 */
    case 247:  /* *addsi_3 */
    case 251:  /* *addsi_4 */
    case 254:  /* *addsi_5 */
      extract_insn_cached (insn);
      if (incdec_operand (operands[2], SImode))
        {
	  return TYPE_INCDEC;
        }
      else
        {
	  return TYPE_ALU;
        }

    case 244:  /* *adddi_2 */
    case 248:  /* *adddi_3 */
    case 255:  /* *adddi_5 */
      extract_insn_cached (insn);
      if (incdec_operand (operands[2], DImode))
        {
	  return TYPE_INCDEC;
        }
      else
        {
	  return TYPE_ALU;
        }

    case 241:  /* *addqi_2 */
    case 245:  /* *addqi_3 */
    case 249:  /* *addqi_4 */
    case 252:  /* *addqi_5 */
    case 256:  /* addqi_ext_1 */
      extract_insn_cached (insn);
      if (incdec_operand (operands[2], QImode))
        {
	  return TYPE_INCDEC;
        }
      else
        {
	  return TYPE_ALU;
        }

    case 306:  /* *umulsidi3_1 */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return TYPE_IMULX;
        }
      else
        {
	  return TYPE_IMUL;
        }

    case 429:  /* *ashlsi3_1 */
    case 430:  /* *ashldi3_1 */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 1)
        {
	  return TYPE_LEA;
        }
      else if (which_alternative == 2)
        {
	  return TYPE_ISHIFTX;
        }
      else if (((
#line 9641 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_DOUBLE_WITH_ADD)) && (register_operand (operands[0], VOIDmode))) && (const1_operand (operands[2], VOIDmode)))
        {
	  return TYPE_ALU;
        }
      else
        {
	  return TYPE_ISHIFT;
        }

    case 431:  /* *ashlhi3_1 */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 1)
        {
	  return TYPE_LEA;
        }
      else if (((
#line 9641 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_DOUBLE_WITH_ADD)) && (register_operand (operands[0], VOIDmode))) && (const1_operand (operands[2], VOIDmode)))
        {
	  return TYPE_ALU;
        }
      else
        {
	  return TYPE_ISHIFT;
        }

    case 432:  /* *ashlqi3_1 */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 2)
        {
	  return TYPE_LEA;
        }
      else if (((
#line 9641 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_DOUBLE_WITH_ADD)) && (register_operand (operands[0], VOIDmode))) && (const1_operand (operands[2], VOIDmode)))
        {
	  return TYPE_ALU;
        }
      else
        {
	  return TYPE_ISHIFT;
        }

    case 433:  /* *ashlqi3_1_slp */
      extract_constrain_insn_cached (insn);
      if (((
#line 9641 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_DOUBLE_WITH_ADD)) && (register_operand (operands[0], VOIDmode))) && (const1_operand (operands[1], VOIDmode)))
        {
	  return TYPE_ALU;
        }
      else
        {
	  return TYPE_ISHIFT1;
        }

    case 434:  /* *ashlqi3_cmp */
    case 435:  /* *ashlhi3_cmp */
    case 436:  /* *ashlsi3_cmp */
    case 437:  /* *ashldi3_cmp */
    case 438:  /* *ashlqi3_cconly */
    case 439:  /* *ashlhi3_cconly */
    case 440:  /* *ashlsi3_cconly */
    case 441:  /* *ashldi3_cconly */
      extract_constrain_insn_cached (insn);
      if (((
#line 9641 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_DOUBLE_WITH_ADD)) && (register_operand (operands[0], VOIDmode))) && (const1_operand (operands[2], VOIDmode)))
        {
	  return TYPE_ALU;
        }
      else
        {
	  return TYPE_ISHIFT;
        }

    case 449:  /* ashrsi3_cvt */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return TYPE_IMOVX;
        }
      else
        {
	  return TYPE_ISHIFT;
        }

    case 452:  /* *lshrsi3_1 */
    case 453:  /* *ashrsi3_1 */
    case 454:  /* *lshrdi3_1 */
    case 455:  /* *ashrdi3_1 */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return TYPE_ISHIFT;
        }
      else
        {
	  return TYPE_ISHIFTX;
        }

    case 485:  /* *rotlsi3_1 */
    case 486:  /* *rotrsi3_1 */
    case 487:  /* *rotldi3_1 */
    case 488:  /* *rotrdi3_1 */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return TYPE_ROTATE;
        }
      else
        {
	  return TYPE_ROTATEX;
        }

    case 627:  /* *fop_sf_comm_mixed */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x6))
        {
	  if (mult_operator (operands[3], SFmode))
	    {
	      return TYPE_SSEMUL;
	    }
	  else
	    {
	      return TYPE_SSEADD;
	    }
        }
      else
        {
	  if (mult_operator (operands[3], SFmode))
	    {
	      return TYPE_FMUL;
	    }
	  else
	    {
	      return TYPE_FOP;
	    }
        }

    case 628:  /* *fop_df_comm_mixed */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x6))
        {
	  if (mult_operator (operands[3], DFmode))
	    {
	      return TYPE_SSEMUL;
	    }
	  else
	    {
	      return TYPE_SSEADD;
	    }
        }
      else
        {
	  if (mult_operator (operands[3], DFmode))
	    {
	      return TYPE_FMUL;
	    }
	  else
	    {
	      return TYPE_FOP;
	    }
        }

    case 629:  /* *fop_sf_comm_sse */
      extract_insn_cached (insn);
      if (mult_operator (operands[3], SFmode))
        {
	  return TYPE_SSEMUL;
        }
      else
        {
	  return TYPE_SSEADD;
        }

    case 630:  /* *fop_df_comm_sse */
      extract_insn_cached (insn);
      if (mult_operator (operands[3], DFmode))
        {
	  return TYPE_SSEMUL;
        }
      else
        {
	  return TYPE_SSEADD;
        }

    case 631:  /* *fop_sf_comm_i387 */
      extract_insn_cached (insn);
      if (mult_operator (operands[3], SFmode))
        {
	  return TYPE_FMUL;
        }
      else
        {
	  return TYPE_FOP;
        }

    case 632:  /* *fop_df_comm_i387 */
      extract_insn_cached (insn);
      if (mult_operator (operands[3], DFmode))
        {
	  return TYPE_FMUL;
        }
      else
        {
	  return TYPE_FOP;
        }

    case 633:  /* *fop_sf_1_mixed */
      extract_constrain_insn_cached (insn);
      if ((((1 << which_alternative) & 0xc)) && (mult_operator (operands[3], SFmode)))
        {
	  return TYPE_SSEMUL;
        }
      else if ((((1 << which_alternative) & 0xc)) && (div_operator (operands[3], SFmode)))
        {
	  return TYPE_SSEDIV;
        }
      else if (((1 << which_alternative) & 0xc))
        {
	  return TYPE_SSEADD;
        }
      else if (mult_operator (operands[3], SFmode))
        {
	  return TYPE_FMUL;
        }
      else if (div_operator (operands[3], SFmode))
        {
	  return TYPE_FDIV;
        }
      else
        {
	  return TYPE_FOP;
        }

    case 634:  /* *fop_df_1_mixed */
      extract_constrain_insn_cached (insn);
      if ((((1 << which_alternative) & 0xc)) && (mult_operator (operands[3], DFmode)))
        {
	  return TYPE_SSEMUL;
        }
      else if ((((1 << which_alternative) & 0xc)) && (div_operator (operands[3], DFmode)))
        {
	  return TYPE_SSEDIV;
        }
      else if (((1 << which_alternative) & 0xc))
        {
	  return TYPE_SSEADD;
        }
      else if (mult_operator (operands[3], DFmode))
        {
	  return TYPE_FMUL;
        }
      else if (div_operator (operands[3], DFmode))
        {
	  return TYPE_FDIV;
        }
      else
        {
	  return TYPE_FOP;
        }

    case 636:  /* *fop_sf_1_sse */
      extract_insn_cached (insn);
      if (mult_operator (operands[3], SFmode))
        {
	  return TYPE_SSEMUL;
        }
      else if (div_operator (operands[3], SFmode))
        {
	  return TYPE_SSEDIV;
        }
      else
        {
	  return TYPE_SSEADD;
        }

    case 637:  /* *fop_df_1_sse */
      extract_insn_cached (insn);
      if (mult_operator (operands[3], DFmode))
        {
	  return TYPE_SSEMUL;
        }
      else if (div_operator (operands[3], DFmode))
        {
	  return TYPE_SSEDIV;
        }
      else
        {
	  return TYPE_SSEADD;
        }

    case 638:  /* *fop_sf_1_i387 */
    case 640:  /* *fop_sf_2_i387 */
    case 642:  /* *fop_sf_2_i387 */
    case 644:  /* *fop_sf_3_i387 */
    case 646:  /* *fop_sf_3_i387 */
      extract_insn_cached (insn);
      if (mult_operator (operands[3], SFmode))
        {
	  return TYPE_FMUL;
        }
      else if (div_operator (operands[3], SFmode))
        {
	  return TYPE_FDIV;
        }
      else
        {
	  return TYPE_FOP;
        }

    case 639:  /* *fop_df_1_i387 */
    case 641:  /* *fop_df_2_i387 */
    case 643:  /* *fop_df_2_i387 */
    case 645:  /* *fop_df_3_i387 */
    case 647:  /* *fop_df_3_i387 */
    case 648:  /* *fop_df_4_i387 */
    case 649:  /* *fop_df_5_i387 */
    case 650:  /* *fop_df_6_i387 */
      extract_insn_cached (insn);
      if (mult_operator (operands[3], DFmode))
        {
	  return TYPE_FMUL;
        }
      else if (div_operator (operands[3], DFmode))
        {
	  return TYPE_FDIV;
        }
      else
        {
	  return TYPE_FOP;
        }

    case 651:  /* *fop_xf_comm_i387 */
      extract_insn_cached (insn);
      if (mult_operator (operands[3], XFmode))
        {
	  return TYPE_FMUL;
        }
      else
        {
	  return TYPE_FOP;
        }

    case 652:  /* *fop_xf_1_i387 */
    case 653:  /* *fop_xf_2_i387 */
    case 654:  /* *fop_xf_2_i387 */
    case 655:  /* *fop_xf_3_i387 */
    case 656:  /* *fop_xf_3_i387 */
    case 657:  /* *fop_xf_4_i387 */
    case 658:  /* *fop_xf_4_i387 */
    case 659:  /* *fop_xf_5_i387 */
    case 660:  /* *fop_xf_5_i387 */
    case 661:  /* *fop_xf_6_i387 */
    case 662:  /* *fop_xf_6_i387 */
      extract_insn_cached (insn);
      if (mult_operator (operands[3], XFmode))
        {
	  return TYPE_FMUL;
        }
      else if (div_operator (operands[3], XFmode))
        {
	  return TYPE_FDIV;
        }
      else
        {
	  return TYPE_FOP;
        }

    case 789:  /* pro_epilogue_adjust_stack_si_add */
      extract_constrain_insn_cached (insn);
      if ((which_alternative == 0) && (! (
#line 16519 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_OPT_AGU))))
        {
	  return TYPE_ALU;
        }
      else if (const0_operand (operands[2], SImode))
        {
	  return TYPE_IMOV;
        }
      else
        {
	  return TYPE_LEA;
        }

    case 790:  /* pro_epilogue_adjust_stack_di_add */
      extract_constrain_insn_cached (insn);
      if ((which_alternative == 0) && (! (
#line 16519 "../../gcc-4.8.1/gcc/config/i386/i386.md"
(TARGET_OPT_AGU))))
        {
	  return TYPE_ALU;
        }
      else if (const0_operand (operands[2], DImode))
        {
	  return TYPE_IMOV;
        }
      else
        {
	  return TYPE_LEA;
        }

    case 836:  /* *movv8qi_internal */
    case 837:  /* *movv4hi_internal */
    case 838:  /* *movv2si_internal */
    case 839:  /* *movv1di_internal */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return TYPE_MMX;
        }
      else if (((1 << which_alternative) & 0xe))
        {
	  return TYPE_MMXMOV;
        }
      else if (((1 << which_alternative) & 0x30))
        {
	  return TYPE_SSECVT;
        }
      else if (((1 << which_alternative) & 0x240))
        {
	  return TYPE_SSELOG1;
        }
      else if (((1 << which_alternative) & 0x6000))
        {
	  return TYPE_MULTI;
        }
      else
        {
	  return TYPE_SSEMOV;
        }

    case 840:  /* *movv2sf_internal */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return TYPE_MMX;
        }
      else if (((1 << which_alternative) & 0xe))
        {
	  return TYPE_MMXMOV;
        }
      else if (((1 << which_alternative) & 0x30))
        {
	  return TYPE_SSECVT;
        }
      else if (which_alternative == 6)
        {
	  return TYPE_SSELOG1;
        }
      else if (((1 << which_alternative) & 0xc00))
        {
	  return TYPE_MULTI;
        }
      else
        {
	  return TYPE_SSEMOV;
        }

    case 868:  /* *vec_extractv2sf_1 */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return TYPE_MMXCVT;
        }
      else if (which_alternative == 1)
        {
	  return TYPE_SSELOG1;
        }
      else if (which_alternative == 2)
        {
	  return TYPE_MMXMOV;
        }
      else if (which_alternative == 3)
        {
	  return TYPE_SSEMOV;
        }
      else if (which_alternative == 4)
        {
	  return TYPE_FMOV;
        }
      else
        {
	  return TYPE_IMOV;
        }

    case 866:  /* *mmx_concatv2sf */
    case 936:  /* *mmx_concatv2si */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return TYPE_MMXCVT;
        }
      else
        {
	  return TYPE_MMXMOV;
        }

    case 1219:  /* vec_dupv4sf */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return TYPE_SSESHUF1;
        }
      else if (which_alternative == 1)
        {
	  return TYPE_SSEMOV;
        }
      else
        {
	  return TYPE_SSESHUF1;
        }

    case 1223:  /* vec_setv4si_0 */
    case 1224:  /* vec_setv4sf_0 */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0xc1))
        {
	  return TYPE_SSELOG;
        }
      else if (which_alternative == 9)
        {
	  return TYPE_IMOV;
        }
      else if (which_alternative == 10)
        {
	  return TYPE_FMOV;
        }
      else
        {
	  return TYPE_SSEMOV;
        }

    case 1258:  /* sse2_loadlpd */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 5)
        {
	  return TYPE_SSELOG;
        }
      else if (which_alternative == 9)
        {
	  return TYPE_FMOV;
        }
      else if (which_alternative == 10)
        {
	  return TYPE_IMOV;
        }
      else
        {
	  return TYPE_SSEMOV;
        }

    case 1259:  /* sse2_movsd */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 5)
        {
	  return TYPE_SSELOG;
        }
      else
        {
	  return TYPE_SSEMOV;
        }

    case 1245:  /* *vec_interleave_lowv2df */
    case 1243:  /* *vec_interleave_highv2df */
    case 1261:  /* *vec_concatv2df */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x7))
        {
	  return TYPE_SSELOG;
        }
      else
        {
	  return TYPE_SSEMOV;
        }

    case 1438:  /* *vec_dupv4si */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return TYPE_SSELOG1;
        }
      else if (which_alternative == 1)
        {
	  return TYPE_SSEMOV;
        }
      else
        {
	  return TYPE_SSELOG1;
        }

    case 1221:  /* *vec_concatv2sf_sse */
    case 1441:  /* *vec_concatv2si_sse2 */
    case 1442:  /* *vec_concatv2si_sse */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return TYPE_SSELOG;
        }
      else if (which_alternative == 1)
        {
	  return TYPE_SSEMOV;
        }
      else if (which_alternative == 2)
        {
	  return TYPE_MMXCVT;
        }
      else
        {
	  return TYPE_MMXMOV;
        }

    case 1783:  /* avx_vec_concatv32qi */
    case 1784:  /* avx_vec_concatv16hi */
    case 1785:  /* avx_vec_concatv8si */
    case 1786:  /* avx_vec_concatv4di */
    case 1787:  /* avx_vec_concatv8sf */
    case 1788:  /* avx_vec_concatv4df */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return TYPE_SSELOG;
        }
      else
        {
	  return TYPE_SSEMOV;
        }

    case 895:  /* mmx_ashrv4hi3 */
    case 896:  /* mmx_ashrv2si3 */
    case 897:  /* mmx_ashlv4hi3 */
    case 898:  /* mmx_lshrv4hi3 */
    case 899:  /* mmx_ashlv2si3 */
    case 900:  /* mmx_lshrv2si3 */
    case 901:  /* mmx_ashlv1di3 */
    case 902:  /* mmx_lshrv1di3 */
    case 921:  /* mmx_packsswb */
    case 922:  /* mmx_packssdw */
    case 923:  /* mmx_packuswb */
    case 939:  /* *mmx_uavgv8qi3 */
    case 940:  /* *mmx_uavgv4hi3 */
    case 941:  /* mmx_psadbw */
      return TYPE_MMXSHFT;

    case 860:  /* mmx_pf2id */
    case 861:  /* mmx_pf2iw */
    case 862:  /* mmx_pi2fw */
    case 863:  /* mmx_floatv2si2 */
    case 864:  /* mmx_pswapdv2sf2 */
    case 865:  /* *vec_dupv2sf */
    case 924:  /* mmx_punpckhbw */
    case 925:  /* mmx_punpcklbw */
    case 926:  /* mmx_punpckhwd */
    case 927:  /* mmx_punpcklwd */
    case 928:  /* mmx_punpckhdq */
    case 929:  /* mmx_punpckldq */
    case 930:  /* *mmx_pinsrw */
    case 931:  /* mmx_pextrw */
    case 932:  /* mmx_pshufw_1 */
    case 933:  /* mmx_pswapdv2si2 */
    case 934:  /* *vec_dupv4hi */
    case 935:  /* *vec_dupv2si */
    case 942:  /* mmx_pmovmskb */
    case 943:  /* *mmx_maskmovq */
    case 944:  /* *mmx_maskmovq */
      return TYPE_MMXCVT;

    case 857:  /* *mmx_eqv2sf3 */
    case 858:  /* mmx_gtv2sf3 */
    case 859:  /* mmx_gev2sf3 */
    case 903:  /* *mmx_eqv8qi3 */
    case 904:  /* *mmx_eqv4hi3 */
    case 905:  /* *mmx_eqv2si3 */
    case 906:  /* mmx_gtv8qi3 */
    case 907:  /* mmx_gtv4hi3 */
    case 908:  /* mmx_gtv2si3 */
      return TYPE_MMXCMP;

    case 844:  /* *mmx_mulv2sf3 */
    case 885:  /* *mmx_mulv4hi3 */
    case 886:  /* *mmx_smulv4hi3_highpart */
    case 887:  /* *mmx_umulv4hi3_highpart */
    case 888:  /* *mmx_pmaddwd */
    case 889:  /* *mmx_pmulhrwv4hi3 */
    case 890:  /* *sse2_umulv1siv1di3 */
      return TYPE_MMXMUL;

    case 842:  /* *mmx_addv2sf3 */
    case 843:  /* *mmx_subv2sf3 */
    case 845:  /* *mmx_smaxv2sf3_finite */
    case 846:  /* *mmx_sminv2sf3_finite */
    case 847:  /* *mmx_smaxv2sf3 */
    case 848:  /* *mmx_sminv2sf3 */
    case 854:  /* mmx_haddv2sf3 */
    case 855:  /* mmx_hsubv2sf3 */
    case 856:  /* mmx_addsubv2sf3 */
    case 869:  /* *mmx_addv8qi3 */
    case 870:  /* *mmx_subv8qi3 */
    case 871:  /* *mmx_addv4hi3 */
    case 872:  /* *mmx_subv4hi3 */
    case 873:  /* *mmx_addv2si3 */
    case 874:  /* *mmx_subv2si3 */
    case 875:  /* *mmx_addv1di3 */
    case 876:  /* *mmx_subv1di3 */
    case 877:  /* *mmx_ssaddv8qi3 */
    case 878:  /* *mmx_usaddv8qi3 */
    case 879:  /* *mmx_sssubv8qi3 */
    case 880:  /* *mmx_ussubv8qi3 */
    case 881:  /* *mmx_ssaddv4hi3 */
    case 882:  /* *mmx_usaddv4hi3 */
    case 883:  /* *mmx_sssubv4hi3 */
    case 884:  /* *mmx_ussubv4hi3 */
    case 891:  /* *mmx_smaxv4hi3 */
    case 892:  /* *mmx_sminv4hi3 */
    case 893:  /* *mmx_umaxv8qi3 */
    case 894:  /* *mmx_uminv8qi3 */
    case 909:  /* mmx_andnotv8qi3 */
    case 910:  /* mmx_andnotv4hi3 */
    case 911:  /* mmx_andnotv2si3 */
    case 912:  /* *mmx_andv8qi3 */
    case 913:  /* *mmx_iorv8qi3 */
    case 914:  /* *mmx_xorv8qi3 */
    case 915:  /* *mmx_andv4hi3 */
    case 916:  /* *mmx_iorv4hi3 */
    case 917:  /* *mmx_xorv4hi3 */
    case 918:  /* *mmx_andv2si3 */
    case 919:  /* *mmx_iorv2si3 */
    case 920:  /* *mmx_xorv2si3 */
      return TYPE_MMXADD;

    case 841:  /* sse_movntq */
      return TYPE_MMXMOV;

    case 801:  /* *prefetch_3dnow */
    case 849:  /* mmx_rcpv2sf2 */
    case 850:  /* mmx_rcpit1v2sf3 */
    case 851:  /* mmx_rcpit2v2sf3 */
    case 852:  /* mmx_rsqrtv2sf2 */
    case 853:  /* mmx_rsqit1v2sf3 */
    case 945:  /* *mmx_emms */
    case 946:  /* *mmx_femms */
      return TYPE_MMX;

    case 821:  /* *lwp_llwpcbsi1 */
    case 822:  /* *lwp_llwpcbdi1 */
    case 823:  /* lwp_slwpcbsi */
    case 824:  /* lwp_slwpcbdi */
    case 825:  /* *lwp_lwpvalsi3_1 */
    case 826:  /* *lwp_lwpinssi3_1 */
      return TYPE_LWP;

    case 779:  /* *xop_pcmov_sf */
    case 780:  /* *xop_pcmov_df */
    case 1603:  /* xop_pcmov_v32qi256 */
    case 1604:  /* xop_pcmov_v16qi */
    case 1605:  /* xop_pcmov_v16hi256 */
    case 1606:  /* xop_pcmov_v8hi */
    case 1607:  /* xop_pcmov_v8si256 */
    case 1608:  /* xop_pcmov_v4si */
    case 1609:  /* xop_pcmov_v4di256 */
    case 1610:  /* xop_pcmov_v2di */
    case 1611:  /* xop_pcmov_v8sf256 */
    case 1612:  /* xop_pcmov_v4sf */
    case 1613:  /* xop_pcmov_v4df256 */
    case 1614:  /* xop_pcmov_v2df */
    case 1630:  /* xop_pperm */
    case 1631:  /* xop_pperm_pack_v2di_v4si */
    case 1632:  /* xop_pperm_pack_v4si_v8hi */
    case 1633:  /* xop_pperm_pack_v8hi_v16qi */
    case 1662:  /* xop_maskcmpv16qi3 */
    case 1663:  /* xop_maskcmpv8hi3 */
    case 1664:  /* xop_maskcmpv4si3 */
    case 1665:  /* xop_maskcmpv2di3 */
    case 1678:  /* xop_vpermil2v8sf3 */
    case 1679:  /* xop_vpermil2v4sf3 */
    case 1680:  /* xop_vpermil2v4df3 */
    case 1681:  /* xop_vpermil2v2df3 */
      return TYPE_SSE4ARG;

    case 1114:  /* *fma_fmadd_sf */
    case 1115:  /* *fma_fmadd_df */
    case 1116:  /* *fma_fmadd_v4sf */
    case 1117:  /* *fma_fmadd_v2df */
    case 1118:  /* *fma_fmadd_v8sf */
    case 1119:  /* *fma_fmadd_v4df */
    case 1120:  /* *fma_fmsub_sf */
    case 1121:  /* *fma_fmsub_df */
    case 1122:  /* *fma_fmsub_v4sf */
    case 1123:  /* *fma_fmsub_v2df */
    case 1124:  /* *fma_fmsub_v8sf */
    case 1125:  /* *fma_fmsub_v4df */
    case 1126:  /* *fma_fnmadd_sf */
    case 1127:  /* *fma_fnmadd_df */
    case 1128:  /* *fma_fnmadd_v4sf */
    case 1129:  /* *fma_fnmadd_v2df */
    case 1130:  /* *fma_fnmadd_v8sf */
    case 1131:  /* *fma_fnmadd_v4df */
    case 1132:  /* *fma_fnmsub_sf */
    case 1133:  /* *fma_fnmsub_df */
    case 1134:  /* *fma_fnmsub_v4sf */
    case 1135:  /* *fma_fnmsub_v2df */
    case 1136:  /* *fma_fnmsub_v8sf */
    case 1137:  /* *fma_fnmsub_v4df */
    case 1138:  /* *fma_fmaddsub_v8sf */
    case 1139:  /* *fma_fmaddsub_v4sf */
    case 1140:  /* *fma_fmaddsub_v4df */
    case 1141:  /* *fma_fmaddsub_v2df */
    case 1142:  /* *fma_fmsubadd_v8sf */
    case 1143:  /* *fma_fmsubadd_v4sf */
    case 1144:  /* *fma_fmsubadd_v4df */
    case 1145:  /* *fma_fmsubadd_v2df */
    case 1146:  /* *fmai_fmadd_v4sf */
    case 1147:  /* *fmai_fmadd_v2df */
    case 1148:  /* *fmai_fmsub_v4sf */
    case 1149:  /* *fmai_fmsub_v2df */
    case 1150:  /* *fmai_fnmadd_v4sf */
    case 1151:  /* *fmai_fnmadd_v2df */
    case 1152:  /* *fmai_fnmsub_v4sf */
    case 1153:  /* *fmai_fnmsub_v2df */
    case 1154:  /* *fma4i_vmfmadd_v4sf */
    case 1155:  /* *fma4i_vmfmadd_v2df */
    case 1156:  /* *fma4i_vmfmsub_v4sf */
    case 1157:  /* *fma4i_vmfmsub_v2df */
    case 1158:  /* *fma4i_vmfnmadd_v4sf */
    case 1159:  /* *fma4i_vmfnmadd_v2df */
    case 1160:  /* *fma4i_vmfnmsub_v4sf */
    case 1161:  /* *fma4i_vmfnmsub_v2df */
    case 1591:  /* xop_pmacsww */
    case 1592:  /* xop_pmacssww */
    case 1593:  /* xop_pmacsdd */
    case 1594:  /* xop_pmacssdd */
    case 1595:  /* xop_pmacsdql */
    case 1596:  /* xop_pmacssdql */
    case 1597:  /* xop_pmacsdqh */
    case 1598:  /* xop_pmacssdqh */
    case 1599:  /* xop_pmacswd */
    case 1600:  /* xop_pmacsswd */
    case 1601:  /* xop_pmadcswd */
    case 1602:  /* xop_pmadcsswd */
      return TYPE_SSEMULADD;

    case 1518:  /* sse4a_insertqi */
    case 1519:  /* sse4a_insertq */
      return TYPE_SSEINS;

    case 1006:  /* avx_divv8sf3 */
    case 1007:  /* sse_divv4sf3 */
    case 1008:  /* avx_divv4df3 */
    case 1009:  /* sse2_divv2df3 */
    case 1010:  /* sse_vmdivv4sf3 */
    case 1011:  /* sse2_vmdivv2df3 */
      return TYPE_SSEDIV;

    case 1208:  /* avx_shufps256_1 */
    case 1209:  /* sse_shufps_v4si */
    case 1210:  /* sse_shufps_v4sf */
    case 1246:  /* avx_shufpd256_1 */
    case 1251:  /* sse2_shufpd_v2di */
    case 1252:  /* sse2_shufpd_v2df */
      return TYPE_SSESHUF;

    case 147:  /* fix_truncsfsi_sse */
    case 148:  /* fix_truncdfsi_sse */
    case 198:  /* *floatsisf2_vector_sse_with_temp */
    case 199:  /* *floatsidf2_vector_sse_with_temp */
    case 200:  /* *floatsisf2_vector_sse */
    case 201:  /* *floatsidf2_vector_sse */
    case 202:  /* *floatsisf2_sse_with_temp */
    case 203:  /* *floatsidf2_sse_with_temp */
    case 204:  /* *floatsisf2_sse_interunit */
    case 205:  /* *floatdisf2_sse_interunit */
    case 206:  /* *floatsidf2_sse_interunit */
    case 207:  /* *floatdidf2_sse_interunit */
    case 208:  /* *floatsisf2_sse_nointerunit */
    case 209:  /* *floatdisf2_sse_nointerunit */
    case 210:  /* *floatsidf2_sse_nointerunit */
    case 211:  /* *floatdidf2_sse_nointerunit */
    case 1165:  /* sse_cvtsi2ss */
    case 1166:  /* sse_cvtss2si */
    case 1167:  /* sse_cvtss2si_2 */
    case 1168:  /* sse_cvttss2si */
    case 1178:  /* sse2_cvtsi2sd */
    case 1179:  /* sse2_cvtsd2si */
    case 1180:  /* sse2_cvtsd2si_2 */
    case 1181:  /* sse2_cvttsd2si */
      return TYPE_SSEICVT;

    case 1654:  /* xop_frczsf2 */
    case 1655:  /* xop_frczdf2 */
    case 1656:  /* xop_frczv4sf2 */
    case 1657:  /* xop_frczv2df2 */
    case 1658:  /* xop_frczv8sf2 */
    case 1659:  /* xop_frczv4df2 */
    case 1660:  /* *xop_vmfrcz_v4sf */
    case 1661:  /* *xop_vmfrcz_v2df */
      return TYPE_SSECVT1;

    case 129:  /* *extendsfdf2_sse */
    case 134:  /* *truncdfsf_fast_sse */
    case 699:  /* sse4_1_roundsf2 */
    case 700:  /* sse4_1_rounddf2 */
    case 982:  /* avx_movntv4di */
    case 983:  /* sse2_movntv2di */
    case 1162:  /* sse_cvtpi2ps */
    case 1163:  /* sse_cvtps2pi */
    case 1164:  /* sse_cvttps2pi */
    case 1169:  /* floatv8siv8sf2 */
    case 1170:  /* floatv4siv4sf2 */
    case 1171:  /* avx_cvtps2dq256 */
    case 1172:  /* sse2_cvtps2dq */
    case 1173:  /* fix_truncv8sfv8si2 */
    case 1174:  /* fix_truncv4sfv4si2 */
    case 1175:  /* sse2_cvtpi2pd */
    case 1176:  /* sse2_cvtpd2pi */
    case 1177:  /* sse2_cvttpd2pi */
    case 1182:  /* floatv4siv4df2 */
    case 1183:  /* avx_cvtdq2pd256_2 */
    case 1184:  /* sse2_cvtdq2pd */
    case 1185:  /* avx_cvtpd2dq256 */
    case 1186:  /* *avx_cvtpd2dq256_2 */
    case 1187:  /* *sse2_cvtpd2dq */
    case 1188:  /* fix_truncv4dfv4si2 */
    case 1189:  /* *avx_cvttpd2dq256_2 */
    case 1190:  /* *sse2_cvttpd2dq */
    case 1191:  /* sse2_cvtsd2ss */
    case 1192:  /* sse2_cvtss2sd */
    case 1193:  /* avx_cvtpd2ps256 */
    case 1194:  /* *sse2_cvtpd2ps */
    case 1195:  /* avx_cvtps2pd256 */
    case 1196:  /* *avx_cvtps2pd256_2 */
    case 1197:  /* sse2_cvtps2pd */
    case 1575:  /* avx_roundps256 */
    case 1576:  /* sse4_1_roundps */
    case 1577:  /* avx_roundpd256 */
    case 1578:  /* sse4_1_roundpd */
    case 1579:  /* sse4_1_roundss */
    case 1580:  /* sse4_1_roundsd */
    case 1789:  /* vcvtph2ps */
    case 1790:  /* *vcvtph2ps_load */
    case 1791:  /* vcvtph2ps256 */
    case 1792:  /* *vcvtps2ph */
    case 1793:  /* *vcvtps2ph_store */
    case 1794:  /* vcvtps2ph256 */
      return TYPE_SSECVT;

    case 53:  /* *cmpisf_sse */
    case 54:  /* *cmpidf_sse */
    case 55:  /* *cmpiusf_sse */
    case 56:  /* *cmpiudf_sse */
    case 1082:  /* sse_comi */
    case 1083:  /* sse2_comi */
    case 1084:  /* sse_ucomi */
    case 1085:  /* sse2_ucomi */
    case 1569:  /* avx_vtestps256 */
    case 1570:  /* avx_vtestps */
    case 1571:  /* avx_vtestpd256 */
    case 1572:  /* avx_vtestpd */
    case 1573:  /* avx_ptest256 */
    case 1574:  /* sse4_1_ptest */
      return TYPE_SSECOMI;

    case 501:  /* setcc_sf_sse */
    case 502:  /* setcc_df_sse */
    case 1066:  /* avx_cmpv8sf3 */
    case 1067:  /* avx_cmpv4sf3 */
    case 1068:  /* avx_cmpv4df3 */
    case 1069:  /* avx_cmpv2df3 */
    case 1070:  /* avx_vmcmpv4sf3 */
    case 1071:  /* avx_vmcmpv2df3 */
    case 1072:  /* *avx_maskcmpv8sf3_comm */
    case 1073:  /* *sse_maskcmpv4sf3_comm */
    case 1074:  /* *avx_maskcmpv4df3_comm */
    case 1075:  /* *sse2_maskcmpv2df3_comm */
    case 1076:  /* avx_maskcmpv8sf3 */
    case 1077:  /* sse_maskcmpv4sf3 */
    case 1078:  /* avx_maskcmpv4df3 */
    case 1079:  /* sse2_maskcmpv2df3 */
    case 1080:  /* sse_vmmaskcmpv4sf3 */
    case 1081:  /* sse2_vmmaskcmpv2df3 */
    case 1352:  /* *avx2_eqv32qi3 */
    case 1353:  /* *avx2_eqv16hi3 */
    case 1354:  /* *avx2_eqv8si3 */
    case 1355:  /* *avx2_eqv4di3 */
    case 1356:  /* *sse4_1_eqv2di3 */
    case 1357:  /* *sse2_eqv16qi3 */
    case 1358:  /* *sse2_eqv8hi3 */
    case 1359:  /* *sse2_eqv4si3 */
    case 1360:  /* sse4_2_gtv2di3 */
    case 1361:  /* avx2_gtv32qi3 */
    case 1362:  /* avx2_gtv16hi3 */
    case 1363:  /* avx2_gtv8si3 */
    case 1364:  /* avx2_gtv4di3 */
    case 1365:  /* sse2_gtv16qi3 */
    case 1366:  /* sse2_gtv8hi3 */
    case 1367:  /* sse2_gtv4si3 */
    case 1666:  /* xop_maskcmp_unsv16qi3 */
    case 1667:  /* xop_maskcmp_unsv8hi3 */
    case 1668:  /* xop_maskcmp_unsv4si3 */
    case 1669:  /* xop_maskcmp_unsv2di3 */
    case 1670:  /* xop_maskcmp_uns2v16qi3 */
    case 1671:  /* xop_maskcmp_uns2v8hi3 */
    case 1672:  /* xop_maskcmp_uns2v4si3 */
    case 1673:  /* xop_maskcmp_uns2v2di3 */
    case 1674:  /* xop_pcom_tfv16qi3 */
    case 1675:  /* xop_pcom_tfv8hi3 */
    case 1676:  /* xop_pcom_tfv4si3 */
    case 1677:  /* xop_pcom_tfv2di3 */
      return TYPE_SSECMP;

    case 1000:  /* *mulv8sf3 */
    case 1001:  /* *mulv4sf3 */
    case 1002:  /* *mulv4df3 */
    case 1003:  /* *mulv2df3 */
    case 1004:  /* sse_vmmulv4sf3 */
    case 1005:  /* sse2_vmmulv2df3 */
    case 1528:  /* avx_dpps256 */
    case 1529:  /* sse4_1_dpps */
    case 1530:  /* avx_dppd256 */
    case 1531:  /* sse4_1_dppd */
      return TYPE_SSEMUL;

    case 1060:  /* *sse3_haddv2df3_low */
    case 1061:  /* *sse3_hsubv2df3_low */
      return TYPE_SSEADD1;

    case 781:  /* smaxsf3 */
    case 782:  /* sminsf3 */
    case 783:  /* smaxdf3 */
    case 784:  /* smindf3 */
    case 785:  /* *ieee_smaxsf3 */
    case 786:  /* *ieee_sminsf3 */
    case 787:  /* *ieee_smaxdf3 */
    case 788:  /* *ieee_smindf3 */
    case 988:  /* *addv8sf3 */
    case 989:  /* *subv8sf3 */
    case 990:  /* *addv4sf3 */
    case 991:  /* *subv4sf3 */
    case 992:  /* *addv4df3 */
    case 993:  /* *subv4df3 */
    case 994:  /* *addv2df3 */
    case 995:  /* *subv2df3 */
    case 996:  /* sse_vmaddv4sf3 */
    case 997:  /* sse_vmsubv4sf3 */
    case 998:  /* sse2_vmaddv2df3 */
    case 999:  /* sse2_vmsubv2df3 */
    case 1024:  /* *smaxv8sf3_finite */
    case 1025:  /* *sminv8sf3_finite */
    case 1026:  /* *smaxv4sf3_finite */
    case 1027:  /* *sminv4sf3_finite */
    case 1028:  /* *smaxv4df3_finite */
    case 1029:  /* *sminv4df3_finite */
    case 1030:  /* *smaxv2df3_finite */
    case 1031:  /* *sminv2df3_finite */
    case 1032:  /* *smaxv8sf3 */
    case 1033:  /* *sminv8sf3 */
    case 1034:  /* *smaxv4sf3 */
    case 1035:  /* *sminv4sf3 */
    case 1036:  /* *smaxv4df3 */
    case 1037:  /* *sminv4df3 */
    case 1038:  /* *smaxv2df3 */
    case 1039:  /* *sminv2df3 */
    case 1044:  /* *ieee_sminv8sf3 */
    case 1045:  /* *ieee_sminv4sf3 */
    case 1046:  /* *ieee_sminv4df3 */
    case 1047:  /* *ieee_sminv2df3 */
    case 1048:  /* *ieee_smaxv8sf3 */
    case 1049:  /* *ieee_smaxv4sf3 */
    case 1050:  /* *ieee_smaxv4df3 */
    case 1051:  /* *ieee_smaxv2df3 */
    case 1052:  /* avx_addsubv4df3 */
    case 1053:  /* sse3_addsubv2df3 */
    case 1054:  /* avx_addsubv8sf3 */
    case 1055:  /* sse3_addsubv4sf3 */
    case 1056:  /* avx_haddv4df3 */
    case 1057:  /* avx_hsubv4df3 */
    case 1058:  /* *sse3_haddv2df3 */
    case 1059:  /* sse3_hsubv2df3 */
    case 1062:  /* avx_haddv8sf3 */
    case 1063:  /* avx_hsubv8sf3 */
    case 1064:  /* sse3_haddv4sf3 */
    case 1065:  /* sse3_hsubv4sf3 */
      return TYPE_SSEADD;

    case 635:  /* *rcpsf2_sse */
    case 668:  /* *rsqrtsf2_sse */
    case 669:  /* *sqrtsf2_sse */
    case 670:  /* *sqrtdf2_sse */
    case 800:  /* *prefetch_sse */
    case 1012:  /* avx_rcpv8sf2 */
    case 1013:  /* sse_rcpv4sf2 */
    case 1014:  /* sse_vmrcpv4sf2 */
    case 1015:  /* avx_sqrtv8sf2 */
    case 1016:  /* sse_sqrtv4sf2 */
    case 1017:  /* avx_sqrtv4df2 */
    case 1018:  /* sse2_sqrtv2df2 */
    case 1019:  /* sse_vmsqrtv4sf2 */
    case 1020:  /* sse2_vmsqrtv2df2 */
    case 1021:  /* avx_rsqrtv8sf2 */
    case 1022:  /* sse_rsqrtv4sf2 */
    case 1023:  /* sse_vmrsqrtv4sf2 */
    case 1040:  /* sse_vmsmaxv4sf3 */
    case 1041:  /* sse_vmsminv4sf3 */
    case 1042:  /* sse2_vmsmaxv2df3 */
    case 1043:  /* sse2_vmsminv2df3 */
    case 1204:  /* avx_movshdup256 */
    case 1205:  /* sse3_movshdup */
    case 1206:  /* avx_movsldup256 */
    case 1207:  /* sse3_movsldup */
    case 1459:  /* sse_ldmxcsr */
    case 1460:  /* sse_stmxcsr */
    case 1461:  /* sse2_clflush */
    case 1516:  /* sse4a_extrqi */
    case 1517:  /* sse4a_extrq */
    case 1689:  /* *avx_vzeroall */
    case 1690:  /* avx_vzeroupper */
    case 1867:  /* *sse2_lfence */
    case 1868:  /* *sse_sfence */
    case 1869:  /* mfence_sse2 */
      return TYPE_SSE;

    case 1294:  /* *mulv16hi3 */
    case 1295:  /* *mulv8hi3 */
    case 1296:  /* *smulv16hi3_highpart */
    case 1297:  /* *umulv16hi3_highpart */
    case 1298:  /* *smulv8hi3_highpart */
    case 1299:  /* *umulv8hi3_highpart */
    case 1300:  /* *vec_widen_umult_even_v8si */
    case 1301:  /* *vec_widen_umult_even_v4si */
    case 1302:  /* *vec_widen_smult_even_v8si */
    case 1303:  /* *sse4_1_mulv2siv2di3 */
    case 1306:  /* *avx2_mulv8si3 */
    case 1307:  /* *sse4_1_mulv4si3 */
    case 1485:  /* *avx2_pmulhrswv16hi3 */
    case 1486:  /* *ssse3_pmulhrswv8hi3 */
    case 1487:  /* *ssse3_pmulhrswv4hi3 */
      return TYPE_SSEIMUL;

    case 1308:  /* ashrv16hi3 */
    case 1309:  /* ashrv8hi3 */
    case 1310:  /* ashrv8si3 */
    case 1311:  /* ashrv4si3 */
    case 1312:  /* ashlv16hi3 */
    case 1313:  /* lshrv16hi3 */
    case 1314:  /* ashlv8hi3 */
    case 1315:  /* lshrv8hi3 */
    case 1316:  /* ashlv8si3 */
    case 1317:  /* lshrv8si3 */
    case 1318:  /* ashlv4si3 */
    case 1319:  /* lshrv4si3 */
    case 1320:  /* ashlv4di3 */
    case 1321:  /* lshrv4di3 */
    case 1322:  /* ashlv2di3 */
    case 1323:  /* lshrv2di3 */
    case 1324:  /* avx2_ashlv2ti3 */
    case 1325:  /* sse2_ashlv1ti3 */
    case 1326:  /* avx2_lshrv2ti3 */
    case 1327:  /* sse2_lshrv1ti3 */
    case 1500:  /* avx2_palignrv2ti */
    case 1501:  /* ssse3_palignrti */
    case 1502:  /* ssse3_palignrdi */
    case 1634:  /* xop_rotlv16qi3 */
    case 1635:  /* xop_rotlv8hi3 */
    case 1636:  /* xop_rotlv4si3 */
    case 1637:  /* xop_rotlv2di3 */
    case 1638:  /* xop_rotrv16qi3 */
    case 1639:  /* xop_rotrv8hi3 */
    case 1640:  /* xop_rotrv4si3 */
    case 1641:  /* xop_rotrv2di3 */
    case 1642:  /* xop_vrotlv16qi3 */
    case 1643:  /* xop_vrotlv8hi3 */
    case 1644:  /* xop_vrotlv4si3 */
    case 1645:  /* xop_vrotlv2di3 */
    case 1646:  /* xop_shav16qi3 */
    case 1647:  /* xop_shav8hi3 */
    case 1648:  /* xop_shav4si3 */
    case 1649:  /* xop_shav2di3 */
    case 1650:  /* xop_shlv16qi3 */
    case 1651:  /* xop_shlv8hi3 */
    case 1652:  /* xop_shlv4si3 */
    case 1653:  /* xop_shlv2di3 */
    case 1773:  /* avx2_ashrvv8si */
    case 1774:  /* avx2_ashrvv4si */
    case 1775:  /* avx2_ashlvv8si */
    case 1776:  /* avx2_lshrvv8si */
    case 1777:  /* avx2_ashlvv4si */
    case 1778:  /* avx2_lshrvv4si */
    case 1779:  /* avx2_ashlvv4di */
    case 1780:  /* avx2_lshrvv4di */
    case 1781:  /* avx2_ashlvv2di */
    case 1782:  /* avx2_lshrvv2di */
      return TYPE_SSEISHFT;

    case 1615:  /* xop_phaddbw */
    case 1616:  /* xop_phaddubw */
    case 1617:  /* xop_phaddbd */
    case 1618:  /* xop_phaddubd */
    case 1619:  /* xop_phaddbq */
    case 1620:  /* xop_phaddubq */
    case 1621:  /* xop_phaddwd */
    case 1622:  /* xop_phadduwd */
    case 1623:  /* xop_phaddwq */
    case 1624:  /* xop_phadduwq */
    case 1625:  /* xop_phadddq */
    case 1626:  /* xop_phaddudq */
    case 1627:  /* xop_phsubbw */
    case 1628:  /* xop_phsubwd */
    case 1629:  /* xop_phsubdq */
      return TYPE_SSEIADD1;

    case 1262:  /* *addv32qi3 */
    case 1263:  /* *subv32qi3 */
    case 1264:  /* *addv16qi3 */
    case 1265:  /* *subv16qi3 */
    case 1266:  /* *addv16hi3 */
    case 1267:  /* *subv16hi3 */
    case 1268:  /* *addv8hi3 */
    case 1269:  /* *subv8hi3 */
    case 1270:  /* *addv8si3 */
    case 1271:  /* *subv8si3 */
    case 1272:  /* *addv4si3 */
    case 1273:  /* *subv4si3 */
    case 1274:  /* *addv4di3 */
    case 1275:  /* *subv4di3 */
    case 1276:  /* *addv2di3 */
    case 1277:  /* *subv2di3 */
    case 1278:  /* *avx2_ssaddv32qi3 */
    case 1279:  /* *avx2_usaddv32qi3 */
    case 1280:  /* *avx2_sssubv32qi3 */
    case 1281:  /* *avx2_ussubv32qi3 */
    case 1282:  /* *sse2_ssaddv16qi3 */
    case 1283:  /* *sse2_usaddv16qi3 */
    case 1284:  /* *sse2_sssubv16qi3 */
    case 1285:  /* *sse2_ussubv16qi3 */
    case 1286:  /* *avx2_ssaddv16hi3 */
    case 1287:  /* *avx2_usaddv16hi3 */
    case 1288:  /* *avx2_sssubv16hi3 */
    case 1289:  /* *avx2_ussubv16hi3 */
    case 1290:  /* *sse2_ssaddv8hi3 */
    case 1291:  /* *sse2_usaddv8hi3 */
    case 1292:  /* *sse2_sssubv8hi3 */
    case 1293:  /* *sse2_ussubv8hi3 */
    case 1304:  /* *avx2_pmaddwd */
    case 1305:  /* *sse2_pmaddwd */
    case 1328:  /* *avx2_smaxv32qi3 */
    case 1329:  /* *avx2_sminv32qi3 */
    case 1330:  /* *avx2_umaxv32qi3 */
    case 1331:  /* *avx2_uminv32qi3 */
    case 1332:  /* *avx2_smaxv16hi3 */
    case 1333:  /* *avx2_sminv16hi3 */
    case 1334:  /* *avx2_umaxv16hi3 */
    case 1335:  /* *avx2_uminv16hi3 */
    case 1336:  /* *avx2_smaxv8si3 */
    case 1337:  /* *avx2_sminv8si3 */
    case 1338:  /* *avx2_umaxv8si3 */
    case 1339:  /* *avx2_uminv8si3 */
    case 1340:  /* *sse4_1_smaxv16qi3 */
    case 1341:  /* *sse4_1_sminv16qi3 */
    case 1342:  /* *sse4_1_smaxv4si3 */
    case 1343:  /* *sse4_1_sminv4si3 */
    case 1344:  /* *smaxv8hi3 */
    case 1345:  /* *sminv8hi3 */
    case 1346:  /* *sse4_1_umaxv8hi3 */
    case 1347:  /* *sse4_1_uminv8hi3 */
    case 1348:  /* *sse4_1_umaxv4si3 */
    case 1349:  /* *sse4_1_uminv4si3 */
    case 1350:  /* *umaxv16qi3 */
    case 1351:  /* *uminv16qi3 */
    case 1445:  /* *avx2_uavgv32qi3 */
    case 1446:  /* *sse2_uavgv16qi3 */
    case 1447:  /* *avx2_uavgv16hi3 */
    case 1448:  /* *sse2_uavgv8hi3 */
    case 1449:  /* avx2_psadbw */
    case 1450:  /* sse2_psadbw */
    case 1464:  /* avx2_phaddwv16hi3 */
    case 1465:  /* avx2_phaddswv16hi3 */
    case 1466:  /* avx2_phsubwv16hi3 */
    case 1467:  /* avx2_phsubswv16hi3 */
    case 1468:  /* ssse3_phaddwv8hi3 */
    case 1469:  /* ssse3_phaddswv8hi3 */
    case 1470:  /* ssse3_phsubwv8hi3 */
    case 1471:  /* ssse3_phsubswv8hi3 */
    case 1472:  /* ssse3_phaddwv4hi3 */
    case 1473:  /* ssse3_phaddswv4hi3 */
    case 1474:  /* ssse3_phsubwv4hi3 */
    case 1475:  /* ssse3_phsubswv4hi3 */
    case 1476:  /* avx2_phadddv8si3 */
    case 1477:  /* avx2_phsubdv8si3 */
    case 1478:  /* ssse3_phadddv4si3 */
    case 1479:  /* ssse3_phsubdv4si3 */
    case 1480:  /* ssse3_phadddv2si3 */
    case 1481:  /* ssse3_phsubdv2si3 */
    case 1482:  /* avx2_pmaddubsw256 */
    case 1483:  /* ssse3_pmaddubsw128 */
    case 1484:  /* ssse3_pmaddubsw */
      return TYPE_SSEIADD;

    case 810:  /* sse4_2_crc32qi */
    case 811:  /* sse4_2_crc32hi */
    case 812:  /* sse4_2_crc32si */
    case 1216:  /* avx2_vec_dupv8sf */
    case 1217:  /* avx2_vec_dupv4sf */
    case 1218:  /* avx2_vec_dupv8sf_1 */
    case 1260:  /* vec_dupv2df */
    case 1427:  /* avx2_pshufd_1 */
    case 1428:  /* sse2_pshufd_1 */
    case 1488:  /* avx2_pshufbv32qi3 */
    case 1489:  /* ssse3_pshufbv16qi3 */
    case 1490:  /* ssse3_pshufbv8qi3 */
    case 1491:  /* avx2_psignv32qi3 */
    case 1492:  /* ssse3_psignv16qi3 */
    case 1493:  /* avx2_psignv16hi3 */
    case 1494:  /* ssse3_psignv8hi3 */
    case 1495:  /* avx2_psignv8si3 */
    case 1496:  /* ssse3_psignv4si3 */
    case 1497:  /* ssse3_psignv8qi3 */
    case 1498:  /* ssse3_psignv4hi3 */
    case 1499:  /* ssse3_psignv2si3 */
    case 1503:  /* absv32qi2 */
    case 1504:  /* absv16qi2 */
    case 1505:  /* absv16hi2 */
    case 1506:  /* absv8hi2 */
    case 1507:  /* absv8si2 */
    case 1508:  /* absv4si2 */
    case 1509:  /* absv8qi2 */
    case 1510:  /* absv4hi2 */
    case 1511:  /* absv2si2 */
    case 1534:  /* avx2_mpsadbw */
    case 1535:  /* sse4_1_mpsadbw */
    case 1544:  /* sse4_1_phminposuw */
    case 1682:  /* aesenc */
    case 1683:  /* aesenclast */
    case 1684:  /* aesdec */
    case 1685:  /* aesdeclast */
    case 1686:  /* aesimc */
    case 1687:  /* aeskeygenassist */
    case 1688:  /* pclmulqdq */
    case 1708:  /* avx2_vec_dupv4df */
    case 1754:  /* avx_maskloadps */
    case 1755:  /* avx_maskloadpd */
    case 1756:  /* avx_maskloadps256 */
    case 1757:  /* avx_maskloadpd256 */
    case 1758:  /* avx2_maskloadd */
    case 1759:  /* avx2_maskloadq */
    case 1760:  /* avx2_maskloadd256 */
    case 1761:  /* avx2_maskloadq256 */
    case 1762:  /* avx_maskstoreps */
    case 1763:  /* avx_maskstorepd */
    case 1764:  /* avx_maskstoreps256 */
    case 1765:  /* avx_maskstorepd256 */
    case 1766:  /* avx2_maskstored */
    case 1767:  /* avx2_maskstoreq */
    case 1768:  /* avx2_maskstored256 */
    case 1769:  /* avx2_maskstoreq256 */
      return TYPE_SSELOG1;

    case 1086:  /* avx_andnotv8sf3 */
    case 1087:  /* sse_andnotv4sf3 */
    case 1088:  /* avx_andnotv4df3 */
    case 1089:  /* sse2_andnotv2df3 */
    case 1090:  /* *andv8sf3 */
    case 1091:  /* *iorv8sf3 */
    case 1092:  /* *xorv8sf3 */
    case 1093:  /* *andv4sf3 */
    case 1094:  /* *iorv4sf3 */
    case 1095:  /* *xorv4sf3 */
    case 1096:  /* *andv4df3 */
    case 1097:  /* *iorv4df3 */
    case 1098:  /* *xorv4df3 */
    case 1099:  /* *andv2df3 */
    case 1100:  /* *iorv2df3 */
    case 1101:  /* *xorv2df3 */
    case 1102:  /* *andnotsf3 */
    case 1103:  /* *andnotdf3 */
    case 1104:  /* *andnottf3 */
    case 1105:  /* *andsf3 */
    case 1106:  /* *iorsf3 */
    case 1107:  /* *xorsf3 */
    case 1108:  /* *anddf3 */
    case 1109:  /* *iordf3 */
    case 1110:  /* *xordf3 */
    case 1111:  /* *andtf3 */
    case 1112:  /* *iortf3 */
    case 1113:  /* *xortf3 */
    case 1200:  /* avx_unpckhps256 */
    case 1201:  /* vec_interleave_highv4sf */
    case 1202:  /* avx_unpcklps256 */
    case 1203:  /* vec_interleave_lowv4sf */
    case 1225:  /* *vec_setv4sf_sse4_1 */
    case 1226:  /* sse4_1_insertps */
    case 1232:  /* vec_extract_hi_v4di */
    case 1233:  /* vec_extract_hi_v4df */
    case 1236:  /* vec_extract_hi_v8si */
    case 1237:  /* vec_extract_hi_v8sf */
    case 1239:  /* vec_extract_hi_v16hi */
    case 1241:  /* vec_extract_hi_v32qi */
    case 1242:  /* avx_unpckhpd256 */
    case 1244:  /* *avx_unpcklpd256 */
    case 1247:  /* avx2_interleave_highv4di */
    case 1248:  /* vec_interleave_highv2di */
    case 1249:  /* avx2_interleave_lowv4di */
    case 1250:  /* vec_interleave_lowv2di */
    case 1368:  /* *andnotv32qi3 */
    case 1369:  /* *andnotv16qi3 */
    case 1370:  /* *andnotv16hi3 */
    case 1371:  /* *andnotv8hi3 */
    case 1372:  /* *andnotv8si3 */
    case 1373:  /* *andnotv4si3 */
    case 1374:  /* *andnotv4di3 */
    case 1375:  /* *andnotv2di3 */
    case 1376:  /* *andv32qi3 */
    case 1377:  /* *iorv32qi3 */
    case 1378:  /* *xorv32qi3 */
    case 1379:  /* *andv16qi3 */
    case 1380:  /* *iorv16qi3 */
    case 1381:  /* *xorv16qi3 */
    case 1382:  /* *andv16hi3 */
    case 1383:  /* *iorv16hi3 */
    case 1384:  /* *xorv16hi3 */
    case 1385:  /* *andv8hi3 */
    case 1386:  /* *iorv8hi3 */
    case 1387:  /* *xorv8hi3 */
    case 1388:  /* *andv8si3 */
    case 1389:  /* *iorv8si3 */
    case 1390:  /* *xorv8si3 */
    case 1391:  /* *andv4si3 */
    case 1392:  /* *iorv4si3 */
    case 1393:  /* *xorv4si3 */
    case 1394:  /* *andv4di3 */
    case 1395:  /* *iorv4di3 */
    case 1396:  /* *xorv4di3 */
    case 1397:  /* *andv2di3 */
    case 1398:  /* *iorv2di3 */
    case 1399:  /* *xorv2di3 */
    case 1400:  /* avx2_packsswb */
    case 1401:  /* sse2_packsswb */
    case 1402:  /* avx2_packssdw */
    case 1403:  /* sse2_packssdw */
    case 1404:  /* avx2_packuswb */
    case 1405:  /* sse2_packuswb */
    case 1406:  /* avx2_interleave_highv32qi */
    case 1407:  /* vec_interleave_highv16qi */
    case 1408:  /* avx2_interleave_lowv32qi */
    case 1409:  /* vec_interleave_lowv16qi */
    case 1410:  /* avx2_interleave_highv16hi */
    case 1411:  /* vec_interleave_highv8hi */
    case 1412:  /* avx2_interleave_lowv16hi */
    case 1413:  /* vec_interleave_lowv8hi */
    case 1414:  /* avx2_interleave_highv8si */
    case 1415:  /* vec_interleave_highv4si */
    case 1416:  /* avx2_interleave_lowv8si */
    case 1417:  /* vec_interleave_lowv4si */
    case 1418:  /* sse4_1_pinsrb */
    case 1419:  /* sse2_pinsrw */
    case 1420:  /* sse4_1_pinsrd */
    case 1421:  /* sse4_1_pinsrq */
    case 1422:  /* *sse4_1_pextrb_si */
    case 1423:  /* *sse4_1_pextrb_memory */
    case 1424:  /* *sse2_pextrw_si */
    case 1425:  /* *sse4_1_pextrw_memory */
    case 1426:  /* *sse4_1_pextrd */
    case 1429:  /* avx2_pshuflw_1 */
    case 1430:  /* sse2_pshuflw_1 */
    case 1431:  /* avx2_pshufhw_1 */
    case 1432:  /* sse2_pshufhw_1 */
    case 1536:  /* avx2_packusdw */
    case 1537:  /* sse4_1_packusdw */
    case 1581:  /* sse4_2_pcmpestr */
    case 1582:  /* *sse4_2_pcmpestr_unaligned */
    case 1583:  /* sse4_2_pcmpestri */
    case 1584:  /* sse4_2_pcmpestrm */
    case 1585:  /* sse4_2_pcmpestr_cconly */
    case 1586:  /* sse4_2_pcmpistr */
    case 1587:  /* *sse4_2_pcmpistr_unaligned */
    case 1588:  /* sse4_2_pcmpistri */
    case 1589:  /* sse4_2_pcmpistrm */
    case 1590:  /* sse4_2_pcmpistr_cconly */
    case 1703:  /* avx2_permvarv8si */
    case 1704:  /* avx2_permvarv8sf */
    case 1705:  /* avx2_permv4di_1 */
    case 1706:  /* avx2_permv4df_1 */
    case 1707:  /* avx2_permv2ti */
    case 1726:  /* *avx_vpermilpv8sf */
    case 1727:  /* *avx_vpermilpv4sf */
    case 1728:  /* *avx_vpermilpv4df */
    case 1729:  /* *avx_vpermilpv2df */
    case 1730:  /* avx_vpermilvarv8sf3 */
    case 1731:  /* avx_vpermilvarv4sf3 */
    case 1732:  /* avx_vpermilvarv4df3 */
    case 1733:  /* avx_vpermilvarv2df3 */
    case 1734:  /* *avx_vperm2f128v8si_full */
    case 1735:  /* *avx_vperm2f128v8sf_full */
    case 1736:  /* *avx_vperm2f128v4df_full */
    case 1737:  /* *avx_vperm2f128v8si_nozero */
    case 1738:  /* *avx_vperm2f128v8sf_nozero */
    case 1739:  /* *avx_vperm2f128v4df_nozero */
    case 1740:  /* avx2_vec_set_lo_v4di */
    case 1741:  /* avx2_vec_set_hi_v4di */
    case 1742:  /* vec_set_lo_v4di */
    case 1743:  /* vec_set_lo_v4df */
    case 1744:  /* vec_set_hi_v4di */
    case 1745:  /* vec_set_hi_v4df */
    case 1746:  /* vec_set_lo_v8si */
    case 1747:  /* vec_set_lo_v8sf */
    case 1748:  /* vec_set_hi_v8si */
    case 1749:  /* vec_set_hi_v8sf */
    case 1750:  /* vec_set_lo_v16hi */
    case 1751:  /* vec_set_hi_v16hi */
    case 1752:  /* vec_set_lo_v32qi */
    case 1753:  /* vec_set_hi_v32qi */
      return TYPE_SSELOG;

    case 711:  /* frndintxf2_floor */
    case 712:  /* frndintxf2_ceil */
    case 713:  /* frndintxf2_trunc */
    case 714:  /* frndintxf2_floor_i387 */
    case 715:  /* frndintxf2_ceil_i387 */
    case 716:  /* frndintxf2_trunc_i387 */
    case 717:  /* frndintxf2_mask_pm */
    case 718:  /* frndintxf2_mask_pm_i387 */
      return TYPE_FRNDINT;

    case 149:  /* fix_trunchi_fisttp_i387_1 */
    case 150:  /* fix_truncsi_fisttp_i387_1 */
    case 151:  /* fix_truncdi_fisttp_i387_1 */
    case 152:  /* fix_trunchi_i387_fisttp */
    case 153:  /* fix_truncsi_i387_fisttp */
    case 154:  /* fix_truncdi_i387_fisttp */
    case 155:  /* fix_trunchi_i387_fisttp_with_temp */
    case 156:  /* fix_truncsi_i387_fisttp_with_temp */
    case 157:  /* fix_truncdi_i387_fisttp_with_temp */
      return TYPE_FISTTP;

    case 158:  /* *fix_trunchi_i387_1 */
    case 159:  /* *fix_truncsi_i387_1 */
    case 160:  /* *fix_truncdi_i387_1 */
    case 161:  /* fix_truncdi_i387 */
    case 162:  /* fix_truncdi_i387_with_temp */
    case 163:  /* fix_trunchi_i387 */
    case 164:  /* fix_truncsi_i387 */
    case 165:  /* fix_trunchi_i387_with_temp */
    case 166:  /* fix_truncsi_i387_with_temp */
    case 719:  /* *fisthi2_floor_1 */
    case 720:  /* *fisthi2_ceil_1 */
    case 721:  /* *fistsi2_floor_1 */
    case 722:  /* *fistsi2_ceil_1 */
    case 723:  /* *fistdi2_floor_1 */
    case 724:  /* *fistdi2_ceil_1 */
    case 725:  /* fistdi2_floor */
    case 726:  /* fistdi2_ceil */
    case 727:  /* fistdi2_floor_with_temp */
    case 728:  /* fistdi2_ceil_with_temp */
    case 729:  /* fisthi2_floor */
    case 730:  /* fisthi2_ceil */
    case 731:  /* fistsi2_floor */
    case 732:  /* fistsi2_ceil */
    case 733:  /* fisthi2_floor_with_temp */
    case 734:  /* fisthi2_ceil_with_temp */
    case 735:  /* fistsi2_floor_with_temp */
    case 736:  /* fistsi2_ceil_with_temp */
      return TYPE_FISTP;

    case 114:  /* swapxf */
    case 115:  /* *swapsf */
    case 116:  /* *swapdf */
      return TYPE_FXCH;

    case 57:  /* *cmpisf_i387 */
    case 58:  /* *cmpidf_i387 */
    case 59:  /* *cmpixf_i387 */
    case 60:  /* *cmpiusf_i387 */
    case 61:  /* *cmpiudf_i387 */
    case 62:  /* *cmpiuxf_i387 */
      return TYPE_FCMP;

    case 776:  /* *movxfcc_1 */
      return TYPE_FCMOV;

    case 665:  /* sqrtxf2 */
    case 666:  /* sqrt_extendsfxf2_i387 */
    case 667:  /* sqrt_extenddfxf2_i387 */
    case 671:  /* fpremxf4_i387 */
    case 672:  /* fprem1xf4_i387 */
    case 673:  /* *sinxf2_i387 */
    case 674:  /* *cosxf2_i387 */
    case 675:  /* *sin_extendsfxf2_i387 */
    case 676:  /* *cos_extendsfxf2_i387 */
    case 677:  /* *sin_extenddfxf2_i387 */
    case 678:  /* *cos_extenddfxf2_i387 */
    case 679:  /* sincosxf3 */
    case 680:  /* sincos_extendsfxf3_i387 */
    case 681:  /* sincos_extenddfxf3_i387 */
    case 682:  /* fptanxf4_i387 */
    case 683:  /* fptan_extendsfxf4_i387 */
    case 684:  /* fptan_extenddfxf4_i387 */
    case 685:  /* *fpatanxf3_i387 */
    case 686:  /* fpatan_extendsfxf3_i387 */
    case 687:  /* fpatan_extenddfxf3_i387 */
    case 688:  /* fyl2xxf3_i387 */
    case 689:  /* fyl2x_extendsfxf3_i387 */
    case 690:  /* fyl2x_extenddfxf3_i387 */
    case 691:  /* fyl2xp1xf3_i387 */
    case 692:  /* fyl2xp1_extendsfxf3_i387 */
    case 693:  /* fyl2xp1_extenddfxf3_i387 */
    case 694:  /* fxtractxf3_i387 */
    case 695:  /* fxtract_extendsfxf3_i387 */
    case 696:  /* fxtract_extenddfxf3_i387 */
    case 697:  /* *f2xm1xf2_i387 */
    case 698:  /* *fscalexf4_i387 */
    case 701:  /* rintxf2 */
    case 702:  /* *fistdi2_1 */
    case 703:  /* fistdi2 */
    case 704:  /* fistdi2_with_temp */
    case 705:  /* *fisthi2_1 */
    case 706:  /* *fistsi2_1 */
    case 707:  /* fisthi2 */
    case 708:  /* fistsi2 */
    case 709:  /* fisthi2_with_temp */
    case 710:  /* fistsi2_with_temp */
      return TYPE_FPSPC;

    case 398:  /* *abssf2_1 */
    case 399:  /* *negsf2_1 */
    case 400:  /* *absdf2_1 */
    case 401:  /* *negdf2_1 */
    case 402:  /* *absxf2_1 */
    case 403:  /* *negxf2_1 */
    case 404:  /* *absextendsfdf2 */
    case 405:  /* *negextendsfdf2 */
    case 406:  /* *absextendsfxf2 */
    case 407:  /* *negextendsfxf2 */
    case 408:  /* *absextenddfxf2 */
    case 409:  /* *negextenddfxf2 */
      return TYPE_FSGN;

    case 130:  /* *extendsfdf2_i387 */
    case 131:  /* *extendsfxf2_i387 */
    case 132:  /* *extenddfxf2_i387 */
    case 135:  /* *truncdfsf_fast_i387 */
    case 138:  /* *truncdfsf2_i387_1 */
    case 141:  /* truncxfsf2_i387_noop */
    case 142:  /* truncxfdf2_i387_noop */
    case 143:  /* *truncxfsf2_i387 */
    case 144:  /* *truncxfdf2_i387 */
    case 175:  /* *floathisf2_i387 */
    case 176:  /* *floathidf2_i387 */
    case 177:  /* *floathixf2_i387 */
    case 218:  /* *floatsisf2_i387 */
    case 219:  /* *floatsidf2_i387 */
    case 220:  /* *floatsixf2_i387 */
    case 221:  /* *floatdisf2_i387 */
    case 222:  /* *floatdidf2_i387 */
    case 223:  /* *floatdixf2_i387 */
    case 663:  /* truncxfsf2_i387_noop_unspec */
    case 664:  /* truncxfdf2_i387_noop_unspec */
    case 1876:  /* loaddi_via_fpu */
    case 1877:  /* storedi_via_fpu */
      return TYPE_FMOV;

    case 579:  /* clzhi2_lzcnt */
    case 580:  /* clzsi2_lzcnt */
    case 581:  /* *bmi_andn_si */
    case 582:  /* bmi_bextr_si */
    case 583:  /* *bmi_blsi_si */
    case 584:  /* *bmi_blsmsk_si */
    case 585:  /* *bmi_blsr_si */
    case 586:  /* bmi2_bzhi_si3 */
    case 587:  /* bmi2_pdep_si3 */
    case 588:  /* bmi2_pext_si3 */
    case 589:  /* tbm_bextri_si */
    case 590:  /* *tbm_blcfill_si */
    case 591:  /* *tbm_blci_si */
    case 592:  /* *tbm_blcic_si */
    case 593:  /* *tbm_blcmsk_si */
    case 594:  /* *tbm_blcs_si */
    case 595:  /* *tbm_blsfill_si */
    case 596:  /* *tbm_blsic_si */
    case 597:  /* *tbm_t1mskc_si */
    case 598:  /* *tbm_tzmsk_si */
    case 601:  /* popcounthi2 */
    case 602:  /* popcountsi2 */
    case 603:  /* *popcounthi2_cmp */
    case 604:  /* *popcountsi2_cmp */
    case 605:  /* *popcountdi2_cmp */
    case 607:  /* *bswapsi2 */
      return TYPE_BITMANIP;

    case 744:  /* *strmovsi_1 */
    case 745:  /* *strmovsi_1 */
    case 746:  /* *strmovhi_1 */
    case 747:  /* *strmovhi_1 */
    case 748:  /* *strmovqi_1 */
    case 749:  /* *strmovqi_1 */
    case 750:  /* *rep_movsi */
    case 751:  /* *rep_movsi */
    case 752:  /* *rep_movqi */
    case 753:  /* *rep_movqi */
    case 754:  /* *strsetsi_1 */
    case 755:  /* *strsetsi_1 */
    case 756:  /* *strsethi_1 */
    case 757:  /* *strsethi_1 */
    case 758:  /* *strsetqi_1 */
    case 759:  /* *strsetqi_1 */
    case 760:  /* *rep_stossi */
    case 761:  /* *rep_stossi */
    case 762:  /* *rep_stosqi */
    case 763:  /* *rep_stosqi */
    case 764:  /* *cmpstrnqi_nz_1 */
    case 765:  /* *cmpstrnqi_nz_1 */
    case 766:  /* *cmpstrnqi_1 */
    case 767:  /* *cmpstrnqi_1 */
    case 768:  /* *strlenqi_1 */
    case 769:  /* *strlenqi_1 */
      return TYPE_STR;

    case 572:  /* leave */
      return TYPE_LEAVE;

    case 552:  /* *call_value */
    case 553:  /* *call_value */
    case 554:  /* *sibcall_value */
    case 555:  /* *sibcall_value */
    case 556:  /* *call_value_pop */
    case 557:  /* *sibcall_value_pop */
      return TYPE_CALLV;

    case 546:  /* *call */
    case 547:  /* *call */
    case 548:  /* *sibcall */
    case 549:  /* *sibcall */
    case 550:  /* *call_pop */
    case 551:  /* *sibcall_pop */
    case 625:  /* *tls_dynamic_gnu2_call_32 */
      return TYPE_CALL;

    case 69:  /* *popsi1 */
    case 70:  /* *popdi1 */
    case 71:  /* *popsi1_epilogue */
    case 72:  /* *popdi1_epilogue */
      return TYPE_POP;

    case 64:  /* *pushsi2 */
    case 65:  /* *pushqi2 */
    case 66:  /* *pushhi2 */
    case 67:  /* *pushsi2_prologue */
    case 68:  /* *pushdi2_prologue */
      return TYPE_PUSH;

    case 773:  /* *movhicc_noc */
    case 774:  /* *movsicc_noc */
    case 775:  /* *movqicc_noc */
      return TYPE_ICMOV;

    case 499:  /* *setcc_qi */
    case 500:  /* *setcc_qi_slp */
      return TYPE_SETCC;

    case 503:  /* *jcc_1 */
    case 504:  /* *jcc_2 */
    case 541:  /* jump */
    case 542:  /* *indirect_jump */
    case 543:  /* *indirect_jump */
    case 544:  /* *tablejump_1 */
    case 545:  /* *tablejump_1 */
    case 564:  /* simple_return_indirect_internal */
      return TYPE_IBR;

    case 14:  /* *cmpqi_ext_2 */
    case 324:  /* *testqi_1_maybe_si */
    case 325:  /* *testqi_1 */
    case 326:  /* *testhi_1 */
    case 327:  /* *testsi_1 */
    case 328:  /* *testqi_ext_0 */
    case 329:  /* *testqi_ext_1 */
    case 330:  /* *testqi_ext_2 */
      return TYPE_TEST;

    case 5:  /* *cmpqi_1 */
    case 6:  /* *cmphi_1 */
    case 7:  /* *cmpsi_1 */
    case 8:  /* *cmpdi_1 */
    case 9:  /* *cmpqi_minus_1 */
    case 10:  /* *cmphi_minus_1 */
    case 11:  /* *cmpsi_minus_1 */
    case 12:  /* *cmpdi_minus_1 */
    case 13:  /* *cmpqi_ext_1 */
    case 15:  /* *cmpqi_ext_3_insn */
    case 16:  /* *cmpqi_ext_4 */
    case 291:  /* *subqi3_cconly_overflow */
    case 292:  /* *subhi3_cconly_overflow */
    case 293:  /* *subsi3_cconly_overflow */
      return TYPE_ICMP;

    case 315:  /* *divmodhi4_noext */
    case 316:  /* *divmodsi4_noext */
    case 317:  /* divmodhiqi3 */
    case 321:  /* *udivmodhi4_noext */
    case 322:  /* *udivmodsi4_noext */
    case 323:  /* udivmodhiqi3 */
      return TYPE_IDIV;

    case 305:  /* *bmi2_umulsidi3_1 */
      return TYPE_IMULX;

    case 302:  /* *mulsi3_1 */
    case 303:  /* *mulhi3_1 */
    case 304:  /* *mulqi3_1 */
    case 307:  /* *mulsidi3_1 */
    case 308:  /* *mulqihi3_1 */
    case 309:  /* *umulqihi3_1 */
    case 310:  /* *smulsi3_highpart_1 */
    case 311:  /* *umulsi3_highpart_1 */
      return TYPE_IMUL;

    case 493:  /* *rotlqi3_1_slp */
    case 494:  /* *rotrqi3_1_slp */
      return TYPE_ROTATE1;

    case 484:  /* *bmi2_rorxsi3_1 */
      return TYPE_ROTATEX;

    case 478:  /* *rotlsi3_mask */
    case 479:  /* *rotrsi3_mask */
    case 480:  /* *rotldi3_mask */
    case 481:  /* *rotrdi3_mask */
    case 489:  /* *rotlqi3_1 */
    case 490:  /* *rotrqi3_1 */
    case 491:  /* *rotlhi3_1 */
    case 492:  /* *rotrhi3_1 */
      return TYPE_ROTATE;

    case 460:  /* *lshrqi3_1_slp */
    case 461:  /* *ashrqi3_1_slp */
      return TYPE_ISHIFT1;

    case 428:  /* *bmi2_ashlsi3_1 */
    case 450:  /* *bmi2_lshrsi3_1 */
    case 451:  /* *bmi2_ashrsi3_1 */
      return TYPE_ISHIFTX;

    case 425:  /* x86_shld */
    case 426:  /* *ashlsi3_mask */
    case 427:  /* *ashldi3_mask */
    case 442:  /* *lshrsi3_mask */
    case 443:  /* *ashrsi3_mask */
    case 444:  /* *lshrdi3_mask */
    case 445:  /* *ashrdi3_mask */
    case 448:  /* x86_shrd */
    case 456:  /* *lshrqi3_1 */
    case 457:  /* *ashrqi3_1 */
    case 458:  /* *lshrhi3_1 */
    case 459:  /* *ashrhi3_1 */
    case 462:  /* *lshrqi3_cmp */
    case 463:  /* *ashrqi3_cmp */
    case 464:  /* *lshrhi3_cmp */
    case 465:  /* *ashrhi3_cmp */
    case 466:  /* *lshrsi3_cmp */
    case 467:  /* *ashrsi3_cmp */
    case 468:  /* *lshrdi3_cmp */
    case 469:  /* *ashrdi3_cmp */
    case 470:  /* *lshrqi3_cconly */
    case 471:  /* *ashrqi3_cconly */
    case 472:  /* *lshrhi3_cconly */
    case 473:  /* *ashrhi3_cconly */
    case 474:  /* *lshrsi3_cconly */
    case 475:  /* *ashrsi3_cconly */
    case 476:  /* *lshrdi3_cconly */
    case 477:  /* *ashrdi3_cconly */
      return TYPE_ISHIFT;

    case 230:  /* *leasi */
    case 258:  /* *lea_general_1 */
    case 259:  /* *lea_general_2 */
    case 260:  /* *lea_general_3 */
    case 261:  /* *lea_general_4 */
    case 262:  /* *lea_general_4 */
    case 624:  /* *tls_dynamic_gnu2_lea_32 */
      return TYPE_LEA;

    case 98:  /* *movhi_extv_1 */
    case 99:  /* *movsi_extv_1 */
    case 101:  /* *movsi_extzv_1 */
    case 120:  /* *zero_extendqisi2 */
    case 121:  /* *zero_extendhisi2 */
    case 123:  /* *zero_extendqihi2 */
    case 125:  /* extendhisi2 */
    case 126:  /* extendqisi2 */
    case 127:  /* extendqihi2 */
      return TYPE_IMOVX;

    case 81:  /* *movabsqi_1 */
    case 82:  /* *movabshi_1 */
    case 83:  /* *movabssi_1 */
    case 84:  /* *movabsdi_1 */
    case 85:  /* *movabsqi_2 */
    case 86:  /* *movabshi_2 */
    case 87:  /* *movabssi_2 */
    case 88:  /* *movabsdi_2 */
    case 89:  /* swapsi */
    case 90:  /* *swapqi_1 */
    case 91:  /* *swaphi_1 */
    case 92:  /* *swapqi_2 */
    case 93:  /* *swaphi_2 */
    case 94:  /* *movstrictqi_1 */
    case 95:  /* *movstricthi_1 */
    case 103:  /* *movsi_insv_1 */
    case 104:  /* *movqi_insv_2 */
    case 570:  /* set_got_offset_rex64 */
    case 616:  /* *load_tp_x32 */
    case 617:  /* *load_tp_x32_zext */
    case 618:  /* *load_tp_si */
    case 619:  /* *load_tp_di */
      return TYPE_IMOV;

    case 382:  /* *negqi2_1 */
    case 383:  /* *neghi2_1 */
    case 384:  /* *negsi2_1 */
    case 385:  /* *negdi2_1 */
    case 386:  /* *negqi2_cmpz */
    case 387:  /* *neghi2_cmpz */
    case 388:  /* *negsi2_cmpz */
    case 389:  /* *negdi2_cmpz */
    case 416:  /* *one_cmplhi2_1 */
    case 417:  /* *one_cmplsi2_1 */
    case 418:  /* *one_cmpldi2_1 */
    case 419:  /* *one_cmplqi2_1 */
      return TYPE_NEGNOT;

    case 73:  /* *movsi_xor */
    case 74:  /* *movsi_or */
    case 96:  /* *movstrictqi_xor */
    case 97:  /* *movstricthi_xor */
    case 118:  /* zero_extendqisi2_and */
    case 119:  /* zero_extendhisi2_and */
    case 122:  /* zero_extendqihi2_and */
    case 269:  /* *subqi_1_slp */
    case 335:  /* *andqi_1_slp */
    case 340:  /* *andqi_2_slp */
    case 353:  /* *iorqi_1_slp */
    case 354:  /* *xorqi_1_slp */
    case 363:  /* *iorqi_2_slp */
    case 364:  /* *xorqi_2_slp */
    case 420:  /* *one_cmplqi2_2 */
    case 421:  /* *one_cmplhi2_2 */
    case 422:  /* *one_cmplsi2_2 */
    case 423:  /* *one_cmpldi2_2 */
    case 495:  /* *btsi */
    case 496:  /* *btdi */
    case 575:  /* *tzcntsi_1 */
    case 576:  /* *bsfsi_1 */
    case 577:  /* ctzhi2 */
    case 578:  /* ctzsi2 */
    case 599:  /* bsr */
    case 600:  /* *bsrhi */
      return TYPE_ALU1;

    case 233:  /* *addsi3_cc */
    case 234:  /* *adddi3_cc */
    case 235:  /* addqi3_cc */
    case 257:  /* *addqi_ext_2 */
    case 265:  /* *subqi_1 */
    case 266:  /* *subhi_1 */
    case 267:  /* *subsi_1 */
    case 268:  /* *subdi_1 */
    case 270:  /* *subqi_2 */
    case 271:  /* *subhi_2 */
    case 272:  /* *subsi_2 */
    case 273:  /* *subdi_2 */
    case 274:  /* *subqi_3 */
    case 275:  /* *subhi_3 */
    case 276:  /* *subsi_3 */
    case 277:  /* *subdi_3 */
    case 278:  /* *addqi3_carry */
    case 279:  /* *subqi3_carry */
    case 280:  /* *addhi3_carry */
    case 281:  /* *subhi3_carry */
    case 282:  /* *addsi3_carry */
    case 283:  /* *subsi3_carry */
    case 284:  /* *adddi3_carry */
    case 285:  /* *subdi3_carry */
    case 286:  /* adcxsi3 */
    case 287:  /* adcxdi3 */
    case 288:  /* *addqi3_cconly_overflow */
    case 289:  /* *addhi3_cconly_overflow */
    case 290:  /* *addsi3_cconly_overflow */
    case 294:  /* *addqi3_cc_overflow */
    case 295:  /* *subqi3_cc_overflow */
    case 296:  /* *addhi3_cc_overflow */
    case 297:  /* *subhi3_cc_overflow */
    case 298:  /* *addsi3_cc_overflow */
    case 299:  /* *subsi3_cc_overflow */
    case 300:  /* *adddi3_cc_overflow */
    case 301:  /* *subdi3_cc_overflow */
    case 334:  /* *andqi_1 */
    case 336:  /* *andqi_2_maybe_si */
    case 337:  /* *andqi_2 */
    case 338:  /* *andhi_2 */
    case 339:  /* *andsi_2 */
    case 341:  /* andqi_ext_0 */
    case 342:  /* *andqi_ext_0_cc */
    case 343:  /* *andqi_ext_1 */
    case 344:  /* *andqi_ext_2 */
    case 345:  /* *iorhi_1 */
    case 346:  /* *xorhi_1 */
    case 347:  /* *iorsi_1 */
    case 348:  /* *xorsi_1 */
    case 349:  /* *iordi_1 */
    case 350:  /* *xordi_1 */
    case 351:  /* *iorqi_1 */
    case 352:  /* *xorqi_1 */
    case 355:  /* *iorqi_2 */
    case 356:  /* *xorqi_2 */
    case 357:  /* *iorhi_2 */
    case 358:  /* *xorhi_2 */
    case 359:  /* *iorsi_2 */
    case 360:  /* *xorsi_2 */
    case 361:  /* *iordi_2 */
    case 362:  /* *xordi_2 */
    case 365:  /* *iorqi_3 */
    case 366:  /* *xorqi_3 */
    case 367:  /* *iorhi_3 */
    case 368:  /* *xorhi_3 */
    case 369:  /* *iorsi_3 */
    case 370:  /* *xorsi_3 */
    case 371:  /* *iordi_3 */
    case 372:  /* *xordi_3 */
    case 373:  /* *iorqi_ext_0 */
    case 374:  /* *xorqi_ext_0 */
    case 375:  /* *iorqi_ext_1 */
    case 376:  /* *xorqi_ext_1 */
    case 377:  /* *iorqi_ext_2 */
    case 378:  /* *xorqi_ext_2 */
    case 379:  /* *xorqi_cc_ext_1 */
    case 620:  /* *add_tp_x32 */
    case 621:  /* *add_tp_x32_zext */
    case 622:  /* *add_tp_si */
    case 623:  /* *add_tp_di */
    case 770:  /* *x86_movsicc_0_m1 */
    case 771:  /* *x86_movsicc_0_m1_se */
    case 772:  /* *x86_movsicc_0_m1_neg */
    case 791:  /* pro_epilogue_adjust_stack_si_sub */
    case 792:  /* pro_epilogue_adjust_stack_di_sub */
      return TYPE_ALU;

    case -1:
      if (GET_CODE (PATTERN (insn)) != ASM_INPUT
          && asm_noperands (PATTERN (insn)) < 0)
        fatal_insn_not_found (insn);
    case 17:  /* *cmpsf_0_i387 */
    case 18:  /* *cmpdf_0_i387 */
    case 19:  /* *cmpxf_0_i387 */
    case 20:  /* *cmpsf_0_cc_i387 */
    case 21:  /* *cmpdf_0_cc_i387 */
    case 22:  /* *cmpxf_0_cc_i387 */
    case 23:  /* *cmpxf_i387 */
    case 24:  /* *cmpxf_cc_i387 */
    case 25:  /* *cmpsf_i387 */
    case 26:  /* *cmpdf_i387 */
    case 27:  /* *cmpsf_cc_i387 */
    case 28:  /* *cmpdf_cc_i387 */
    case 29:  /* *cmpusf_i387 */
    case 30:  /* *cmpudf_i387 */
    case 31:  /* *cmpuxf_i387 */
    case 32:  /* *cmpusf_cc_i387 */
    case 33:  /* *cmpudf_cc_i387 */
    case 34:  /* *cmpuxf_cc_i387 */
    case 35:  /* *cmpsf_hi_i387 */
    case 36:  /* *cmpdf_hi_i387 */
    case 37:  /* *cmpxf_hi_i387 */
    case 38:  /* *cmpsf_si_i387 */
    case 39:  /* *cmpdf_si_i387 */
    case 40:  /* *cmpxf_si_i387 */
    case 41:  /* *cmpsf_hi_cc_i387 */
    case 42:  /* *cmpdf_hi_cc_i387 */
    case 43:  /* *cmpxf_hi_cc_i387 */
    case 44:  /* *cmpsf_si_cc_i387 */
    case 45:  /* *cmpdf_si_cc_i387 */
    case 46:  /* *cmpxf_si_cc_i387 */
    case 63:  /* *pushdi2 */
    case 105:  /* *pushtf */
    case 106:  /* *pushxf */
    case 107:  /* *pushxf_nointeger */
    case 108:  /* *pushdf */
    case 224:  /* floatdisf2_i387_with_xmm */
    case 225:  /* floatdidf2_i387_with_xmm */
    case 226:  /* floatdixf2_i387_with_xmm */
    case 227:  /* *floatunssisf2_1 */
    case 228:  /* *floatunssidf2_1 */
    case 229:  /* *floatunssixf2_1 */
    case 312:  /* divmodsi4_1 */
    case 313:  /* *divmodhi4 */
    case 314:  /* *divmodsi4 */
    case 318:  /* udivmodsi4_1 */
    case 319:  /* *udivmodhi4 */
    case 320:  /* *udivmodsi4 */
    case 424:  /* *ashldi3_doubleword */
    case 446:  /* *lshrdi3_doubleword */
    case 447:  /* *ashrdi3_doubleword */
    case 568:  /* set_got */
    case 569:  /* set_got_labelled */
    case 613:  /* *tls_global_dynamic_32_gnu */
    case 614:  /* *tls_local_dynamic_base_32_gnu */
    case 737:  /* fxamsf2_i387 */
    case 738:  /* fxamdf2_i387 */
    case 739:  /* fxamxf2_i387 */
    case 740:  /* fxamsf2_i387_with_temp */
    case 741:  /* fxamdf2_i387_with_temp */
    case 793:  /* allocate_stack_worker_probe_si */
    case 794:  /* allocate_stack_worker_probe_di */
    case 795:  /* adjust_stack_and_probesi */
    case 796:  /* adjust_stack_and_probedi */
    case 797:  /* probe_stack_rangesi */
    case 798:  /* probe_stack_rangedi */
    case 802:  /* stack_protect_set_si */
    case 803:  /* stack_protect_set_di */
    case 804:  /* stack_tls_protect_set_si */
    case 805:  /* stack_tls_protect_set_di */
    case 806:  /* stack_protect_test_si */
    case 807:  /* stack_protect_test_di */
    case 808:  /* stack_tls_protect_test_si */
    case 809:  /* stack_tls_protect_test_di */
      return TYPE_MULTI;

    case 47:  /* x86_fnstsw_1 */
    case 48:  /* x86_sahf_1 */
    case 124:  /* extendsidi2_1 */
    case 145:  /* *fixuns_truncsf_1 */
    case 146:  /* *fixuns_truncdf_1 */
    case 167:  /* x86_fnstcw_1 */
    case 168:  /* x86_fldcw_1 */
    case 169:  /* *floathisf2_1 */
    case 170:  /* *floathidf2_1 */
    case 171:  /* *floathixf2_1 */
    case 178:  /* *floatsisf2_1 */
    case 179:  /* *floatsidf2_1 */
    case 180:  /* *floatsixf2_1 */
    case 181:  /* *floatdisf2_1 */
    case 182:  /* *floatdidf2_1 */
    case 183:  /* *floatdixf2_1 */
    case 231:  /* *adddi3_doubleword */
    case 232:  /* *addti3_doubleword */
    case 263:  /* *subdi3_doubleword */
    case 264:  /* *subti3_doubleword */
    case 331:  /* *testqi_ext_3 */
    case 380:  /* *negdi2_doubleword */
    case 381:  /* *negti2_doubleword */
    case 390:  /* *absnegsf2_mixed */
    case 391:  /* *absnegdf2_mixed */
    case 392:  /* *absnegsf2_sse */
    case 393:  /* *absnegdf2_sse */
    case 394:  /* *absnegsf2_i387 */
    case 395:  /* *absnegdf2_i387 */
    case 396:  /* *absnegxf2_i387 */
    case 397:  /* *absnegtf2_sse */
    case 410:  /* copysignsf3_const */
    case 411:  /* copysigndf3_const */
    case 412:  /* copysigntf3_const */
    case 413:  /* copysignsf3_var */
    case 414:  /* copysigndf3_var */
    case 415:  /* copysigntf3_var */
    case 482:  /* ix86_rotldi3_doubleword */
    case 483:  /* ix86_rotrdi3_doubleword */
    case 497:  /* *setcc_si_1_and */
    case 498:  /* *setcc_si_1_movzbl */
    case 505:  /* *jcc_btsi */
    case 506:  /* *jcc_btdi */
    case 507:  /* *jcc_btsi_mask */
    case 508:  /* *jcc_btdi_mask */
    case 509:  /* *jcc_btsi_1 */
    case 510:  /* *jcc_btsi_mask_1 */
    case 511:  /* *jccsf_0_i387 */
    case 512:  /* *jccdf_0_i387 */
    case 513:  /* *jccxf_0_i387 */
    case 514:  /* *jccsf_0_r_i387 */
    case 515:  /* *jccdf_0_r_i387 */
    case 516:  /* *jccxf_0_r_i387 */
    case 517:  /* *jccxf_i387 */
    case 518:  /* *jccxf_r_i387 */
    case 519:  /* *jccsf_i387 */
    case 520:  /* *jccdf_i387 */
    case 521:  /* *jccsf_r_i387 */
    case 522:  /* *jccdf_r_i387 */
    case 523:  /* *jccusf_i387 */
    case 524:  /* *jccudf_i387 */
    case 525:  /* *jccuxf_i387 */
    case 526:  /* *jccusf_r_i387 */
    case 527:  /* *jccudf_r_i387 */
    case 528:  /* *jccuxf_r_i387 */
    case 529:  /* *jccsf_hi_i387 */
    case 530:  /* *jccdf_hi_i387 */
    case 531:  /* *jccxf_hi_i387 */
    case 532:  /* *jccsf_si_i387 */
    case 533:  /* *jccdf_si_i387 */
    case 534:  /* *jccxf_si_i387 */
    case 535:  /* *jccsf_hi_r_i387 */
    case 536:  /* *jccdf_hi_r_i387 */
    case 537:  /* *jccxf_hi_r_i387 */
    case 538:  /* *jccsf_si_r_i387 */
    case 539:  /* *jccdf_si_r_i387 */
    case 540:  /* *jccxf_si_r_i387 */
    case 558:  /* blockage */
    case 559:  /* *memory_blockage */
    case 560:  /* prologue_use */
    case 561:  /* simple_return_internal */
    case 562:  /* simple_return_internal_long */
    case 563:  /* simple_return_pop_internal */
    case 565:  /* nop */
    case 566:  /* nops */
    case 567:  /* pad */
    case 571:  /* eh_return_internal */
    case 573:  /* split_stack_return */
    case 574:  /* ffssi2_no_cmove */
    case 608:  /* *bswaphi_lowpart_1 */
    case 609:  /* bswaphi_lowpart */
    case 610:  /* paritydi2_cmp */
    case 611:  /* paritysi2_cmp */
    case 612:  /* *parityhi2_cmp */
    case 615:  /* *tls_local_dynamic_32_once */
    case 626:  /* *tls_dynamic_gnu2_combine_32 */
    case 743:  /* cld */
    case 799:  /* trap */
    case 813:  /* rdpmc */
    case 814:  /* rdtsc */
    case 815:  /* rdtscp */
    case 816:  /* fxsave */
    case 817:  /* fxrstor */
    case 818:  /* xsave */
    case 819:  /* xsaveopt */
    case 820:  /* xrstor */
    case 827:  /* rdrandhi_1 */
    case 828:  /* rdrandsi_1 */
    case 829:  /* rdseedhi_1 */
    case 830:  /* rdseedsi_1 */
    case 831:  /* *pause */
    case 832:  /* xbegin_1 */
    case 833:  /* xend */
    case 834:  /* xabort */
    case 835:  /* xtest_1 */
    case 867:  /* *vec_extractv2sf_0 */
    case 937:  /* *vec_extractv2si_0 */
    case 962:  /* movdi_to_sse */
    case 984:  /* *absnegv8sf2 */
    case 985:  /* *absnegv4sf2 */
    case 986:  /* *absnegv4df2 */
    case 987:  /* *absnegv2df2 */
    case 1227:  /* *vec_extractv4sf_0 */
    case 1229:  /* *vec_extract_v4sf_mem */
    case 1230:  /* vec_extract_lo_v4di */
    case 1231:  /* vec_extract_lo_v4df */
    case 1234:  /* vec_extract_lo_v8si */
    case 1235:  /* vec_extract_lo_v8sf */
    case 1238:  /* vec_extract_lo_v16hi */
    case 1240:  /* vec_extract_lo_v32qi */
    case 1434:  /* sse2_stored */
    case 1435:  /* *vec_ext_v4si_mem */
    case 1436:  /* *sse2_storeq */
    case 1462:  /* sse3_mwait */
    case 1463:  /* sse3_monitor */
    case 1724:  /* *avx_vperm_broadcast_v8sf */
    case 1725:  /* *avx_vperm_broadcast_v4df */
    case 1770:  /* avx_si256_si */
    case 1771:  /* avx_ps256_ps */
    case 1772:  /* avx_pd256_pd */
    case 1870:  /* mfence_nosse */
    case 1871:  /* atomic_loaddi_fpu */
    case 1872:  /* atomic_storeqi_1 */
    case 1873:  /* atomic_storehi_1 */
    case 1874:  /* atomic_storesi_1 */
    case 1875:  /* atomic_storedi_fpu */
    case 1878:  /* atomic_compare_and_swapqi_1 */
    case 1879:  /* atomic_compare_and_swaphi_1 */
    case 1880:  /* atomic_compare_and_swapsi_1 */
    case 1881:  /* atomic_compare_and_swapdi_doubleword */
    case 1882:  /* atomic_fetch_addqi */
    case 1883:  /* atomic_fetch_addhi */
    case 1884:  /* atomic_fetch_addsi */
    case 1885:  /* *atomic_fetch_add_cmpqi */
    case 1886:  /* *atomic_fetch_add_cmphi */
    case 1887:  /* *atomic_fetch_add_cmpsi */
    case 1888:  /* atomic_exchangeqi */
    case 1889:  /* atomic_exchangehi */
    case 1890:  /* atomic_exchangesi */
    case 1891:  /* atomic_addqi */
    case 1892:  /* atomic_addhi */
    case 1893:  /* atomic_addsi */
    case 1894:  /* atomic_subqi */
    case 1895:  /* atomic_subhi */
    case 1896:  /* atomic_subsi */
    case 1897:  /* atomic_andqi */
    case 1898:  /* atomic_orqi */
    case 1899:  /* atomic_xorqi */
    case 1900:  /* atomic_andhi */
    case 1901:  /* atomic_orhi */
    case 1902:  /* atomic_xorhi */
    case 1903:  /* atomic_andsi */
    case 1904:  /* atomic_orsi */
    case 1905:  /* atomic_xorsi */
      return TYPE_OTHER;

    default:
      return TYPE_SSEMOV;

    }
}

enum attr_use_carry
get_attr_use_carry (rtx insn ATTRIBUTE_UNUSED)
{
  switch (recog_memoized (insn))
    {
    case 278:  /* *addqi3_carry */
    case 279:  /* *subqi3_carry */
    case 280:  /* *addhi3_carry */
    case 281:  /* *subhi3_carry */
    case 282:  /* *addsi3_carry */
    case 283:  /* *subsi3_carry */
    case 284:  /* *adddi3_carry */
    case 285:  /* *subdi3_carry */
    case 286:  /* adcxsi3 */
    case 287:  /* adcxdi3 */
    case 770:  /* *x86_movsicc_0_m1 */
    case 771:  /* *x86_movsicc_0_m1_se */
    case 772:  /* *x86_movsicc_0_m1_neg */
      return USE_CARRY_1;

    case -1:
      if (GET_CODE (PATTERN (insn)) != ASM_INPUT
          && asm_noperands (PATTERN (insn)) < 0)
        fatal_insn_not_found (insn);
    default:
      return USE_CARRY_0;

    }
}

enum attr_unit
get_attr_unit (rtx insn ATTRIBUTE_UNUSED)
{
  enum attr_type cached_type ATTRIBUTE_UNUSED;

  switch (recog_memoized (insn))
    {
    case 1258:  /* sse2_loadlpd */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 9)
        {
	  return UNIT_I387;
        }
      else if (!((1 << which_alternative) & 0x600))
        {
	  return UNIT_SSE;
        }
      else
        {
	  return UNIT_INTEGER;
        }

    case 1257:  /* sse2_loadhpd */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 5)
        {
	  return UNIT_I387;
        }
      else if (((1 << which_alternative) & 0x1f))
        {
	  return UNIT_SSE;
        }
      else
        {
	  return UNIT_INTEGER;
        }

    case 1255:  /* sse2_storelpd */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 3)
        {
	  return UNIT_I387;
        }
      else if (((1 << which_alternative) & 0x7))
        {
	  return UNIT_SSE;
        }
      else
        {
	  return UNIT_INTEGER;
        }

    case 1253:  /* sse2_storehpd */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 4)
        {
	  return UNIT_I387;
        }
      else if (((1 << which_alternative) & 0xf))
        {
	  return UNIT_SSE;
        }
      else
        {
	  return UNIT_INTEGER;
        }

    case 1228:  /* *sse4_1_extractps */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return UNIT_SSE;
        }
      else
        {
	  return UNIT_UNKNOWN;
        }

    case 1224:  /* vec_setv4sf_0 */
    case 1223:  /* vec_setv4si_0 */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 10)
        {
	  return UNIT_I387;
        }
      else if (!((1 << which_alternative) & 0x600))
        {
	  return UNIT_SSE;
        }
      else
        {
	  return UNIT_INTEGER;
        }

    case 1442:  /* *vec_concatv2si_sse */
    case 1441:  /* *vec_concatv2si_sse2 */
    case 1221:  /* *vec_concatv2sf_sse */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return UNIT_SSE;
        }
      else
        {
	  return UNIT_MMX;
        }

    case 1440:  /* *vec_concatv2si_sse4_1 */
    case 1220:  /* *vec_concatv2sf_sse4_1 */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x1f))
        {
	  return UNIT_SSE;
        }
      else
        {
	  return UNIT_MMX;
        }

    case 1175:  /* sse2_cvtpi2pd */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return UNIT_MMX;
        }
      else
        {
	  return UNIT_SSE;
        }

    case 938:  /* *vec_extractv2si_1 */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x2e))
        {
	  return UNIT_SSE;
        }
      else if (((1 << which_alternative) & 0x11))
        {
	  return UNIT_MMX;
        }
      else
        {
	  return UNIT_INTEGER;
        }

    case 868:  /* *vec_extractv2sf_1 */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 4)
        {
	  return UNIT_I387;
        }
      else if (((1 << which_alternative) & 0xa))
        {
	  return UNIT_SSE;
        }
      else if (((1 << which_alternative) & 0x5))
        {
	  return UNIT_MMX;
        }
      else
        {
	  return UNIT_INTEGER;
        }

    case 840:  /* *movv2sf_internal */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x30))
        {
	  return UNIT_MMX;
        }
      else
        {
	  if (!((1 << which_alternative) & 0xc0f))
	    {
	      return UNIT_SSE;
	    }
	  else if (((1 << which_alternative) & 0xf))
	    {
	      return UNIT_MMX;
	    }
	  else
	    {
	      return UNIT_INTEGER;
	    }
        }

    case 839:  /* *movv1di_internal */
    case 838:  /* *movv2si_internal */
    case 837:  /* *movv4hi_internal */
    case 836:  /* *movv8qi_internal */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x30))
        {
	  return UNIT_MMX;
        }
      else
        {
	  if (!((1 << which_alternative) & 0x600f))
	    {
	      return UNIT_SSE;
	    }
	  else if (((1 << which_alternative) & 0xf))
	    {
	      return UNIT_MMX;
	    }
	  else
	    {
	      return UNIT_INTEGER;
	    }
        }

    case 778:  /* *movsfcc_1_387 */
    case 777:  /* *movdfcc_1 */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return UNIT_I387;
        }
      else
        {
	  return UNIT_INTEGER;
        }

    case 662:  /* *fop_xf_6_i387 */
    case 661:  /* *fop_xf_6_i387 */
    case 660:  /* *fop_xf_5_i387 */
    case 659:  /* *fop_xf_5_i387 */
    case 658:  /* *fop_xf_4_i387 */
    case 657:  /* *fop_xf_4_i387 */
    case 656:  /* *fop_xf_3_i387 */
    case 655:  /* *fop_xf_3_i387 */
    case 654:  /* *fop_xf_2_i387 */
    case 653:  /* *fop_xf_2_i387 */
    case 652:  /* *fop_xf_1_i387 */
    case 650:  /* *fop_df_6_i387 */
    case 649:  /* *fop_df_5_i387 */
    case 648:  /* *fop_df_4_i387 */
    case 647:  /* *fop_df_3_i387 */
    case 646:  /* *fop_sf_3_i387 */
    case 645:  /* *fop_df_3_i387 */
    case 644:  /* *fop_sf_3_i387 */
    case 643:  /* *fop_df_2_i387 */
    case 642:  /* *fop_sf_2_i387 */
    case 641:  /* *fop_df_2_i387 */
    case 640:  /* *fop_sf_2_i387 */
    case 639:  /* *fop_df_1_i387 */
    case 638:  /* *fop_sf_1_i387 */
      if (((cached_type = get_attr_type (insn)) == TYPE_FOP) || ((cached_type == TYPE_FMUL) || (cached_type == TYPE_FDIV)))
        {
	  return UNIT_I387;
        }
      else
        {
	  return UNIT_INTEGER;
        }

    case 637:  /* *fop_df_1_sse */
    case 636:  /* *fop_sf_1_sse */
      if (((cached_type = get_attr_type (insn)) == TYPE_SSEADD) || ((cached_type == TYPE_SSEMUL) || (cached_type == TYPE_SSEDIV)))
        {
	  return UNIT_SSE;
        }
      else
        {
	  return UNIT_INTEGER;
        }

    case 651:  /* *fop_xf_comm_i387 */
    case 632:  /* *fop_df_comm_i387 */
    case 631:  /* *fop_sf_comm_i387 */
      if (((cached_type = get_attr_type (insn)) == TYPE_FOP) || (cached_type == TYPE_FMUL))
        {
	  return UNIT_I387;
        }
      else
        {
	  return UNIT_INTEGER;
        }

    case 630:  /* *fop_df_comm_sse */
    case 629:  /* *fop_sf_comm_sse */
      if (((cached_type = get_attr_type (insn)) == TYPE_SSEADD) || (cached_type == TYPE_SSEMUL))
        {
	  return UNIT_SSE;
        }
      else
        {
	  return UNIT_INTEGER;
        }

    case 193:  /* *floatdidf2_mixed_interunit */
    case 192:  /* *floatsidf2_mixed_interunit */
    case 191:  /* *floatdisf2_mixed_interunit */
    case 190:  /* *floatsisf2_mixed_interunit */
    case 187:  /* *floatsidf2_vector_mixed */
    case 186:  /* *floatsisf2_vector_mixed */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return UNIT_I387;
        }
      else
        {
	  return UNIT_SSE;
        }

    case 189:  /* *floatsidf2_mixed_with_temp */
    case 188:  /* *floatsisf2_mixed_with_temp */
    case 185:  /* *floatsidf2_vector_mixed_with_temp */
    case 184:  /* *floatsisf2_vector_mixed_with_temp */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return UNIT_I387;
        }
      else if (which_alternative == 1)
        {
	  return UNIT_I387;
        }
      else
        {
	  return UNIT_SSE;
        }

    case 217:  /* *floatdixf2_i387_with_temp */
    case 216:  /* *floatdidf2_i387_with_temp */
    case 215:  /* *floatdisf2_i387_with_temp */
    case 214:  /* *floatsixf2_i387_with_temp */
    case 213:  /* *floatsidf2_i387_with_temp */
    case 212:  /* *floatsisf2_i387_with_temp */
    case 174:  /* *floathixf2_i387_with_temp */
    case 173:  /* *floathidf2_i387_with_temp */
    case 172:  /* *floathisf2_i387_with_temp */
    case 140:  /* *truncxfdf2_mixed */
    case 139:  /* *truncxfsf2_mixed */
    case 137:  /* *truncdfsf_i387 */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return UNIT_I387;
        }
      else
        {
	  return UNIT_I387;
        }

    case 136:  /* *truncdfsf_mixed */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  if (which_alternative == 0)
	    {
	      return UNIT_I387;
	    }
	  else
	    {
	      return UNIT_SSE;
	    }
        }
      else
        {
	  return UNIT_I387;
        }

    case 128:  /* *extendsfdf2_mixed */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x3))
        {
	  return UNIT_I387;
        }
      else
        {
	  return UNIT_SSE;
        }

    case 117:  /* *zero_extendsidi2 */
      extract_constrain_insn_cached (insn);
      if (!((1 << which_alternative) & 0x1f))
        {
	  return UNIT_SSE;
        }
      else if (((1 << which_alternative) & 0x18))
        {
	  return UNIT_MMX;
        }
      else
        {
	  return UNIT_INTEGER;
        }

    case 113:  /* *movsf_internal */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x7))
        {
	  return UNIT_I387;
        }
      else if (!((1 << which_alternative) & 0xce1f))
        {
	  return UNIT_SSE;
        }
      else if (((1 << which_alternative) & 0xce00))
        {
	  return UNIT_MMX;
        }
      else
        {
	  return UNIT_INTEGER;
        }

    case 112:  /* *movdf_internal */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x7))
        {
	  return UNIT_I387;
        }
      else if (!((1 << which_alternative) & 0x1f))
        {
	  return UNIT_SSE;
        }
      else
        {
	  return UNIT_INTEGER;
        }

    case 111:  /* *movxf_internal */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0x7))
        {
	  return UNIT_I387;
        }
      else
        {
	  return UNIT_INTEGER;
        }

    case 109:  /* *pushsf */
    case 108:  /* *pushdf */
    case 107:  /* *pushxf_nointeger */
    case 106:  /* *pushxf */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return UNIT_I387;
        }
      else
        {
	  return UNIT_INTEGER;
        }

    case 105:  /* *pushtf */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return UNIT_SSE;
        }
      else
        {
	  return UNIT_INTEGER;
        }

    case 78:  /* *movsi_internal */
      extract_constrain_insn_cached (insn);
      if (((1 << which_alternative) & 0xfc0))
        {
	  return UNIT_SSE;
        }
      else if (((1 << which_alternative) & 0x3c))
        {
	  return UNIT_MMX;
        }
      else
        {
	  return UNIT_INTEGER;
        }

    case 77:  /* *movdi_internal */
      extract_constrain_insn_cached (insn);
      if (!((1 << which_alternative) & 0x1f))
        {
	  return UNIT_SSE;
        }
      else if (((1 << which_alternative) & 0x1c))
        {
	  return UNIT_MMX;
        }
      else
        {
	  return UNIT_INTEGER;
        }

    case 197:  /* *floatdidf2_mixed_nointerunit */
    case 196:  /* *floatsidf2_mixed_nointerunit */
    case 195:  /* *floatdisf2_mixed_nointerunit */
    case 194:  /* *floatsisf2_mixed_nointerunit */
    case 133:  /* *truncdfsf_fast_mixed */
    case 52:  /* *cmpiudf_mixed */
    case 51:  /* *cmpiusf_mixed */
    case 50:  /* *cmpidf_mixed */
    case 49:  /* *cmpisf_mixed */
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return UNIT_I387;
        }
      else
        {
	  return UNIT_SSE;
        }

    case -1:
      if (GET_CODE (PATTERN (insn)) != ASM_INPUT
          && asm_noperands (PATTERN (insn)) < 0)
        fatal_insn_not_found (insn);
    case 627:  /* *fop_sf_comm_mixed */
    case 628:  /* *fop_df_comm_mixed */
    case 633:  /* *fop_sf_1_mixed */
    case 634:  /* *fop_df_1_mixed */
      if (((cached_type = get_attr_type (insn)) == TYPE_FMOV) || ((cached_type == TYPE_FOP) || ((cached_type == TYPE_FSGN) || ((cached_type == TYPE_FMUL) || ((cached_type == TYPE_FDIV) || ((cached_type == TYPE_FPSPC) || ((cached_type == TYPE_FCMOV) || ((cached_type == TYPE_FCMP) || ((cached_type == TYPE_FXCH) || ((cached_type == TYPE_FISTP) || ((cached_type == TYPE_FISTTP) || (cached_type == TYPE_FRNDINT))))))))))))
        {
	  return UNIT_I387;
        }
      else if ((cached_type == TYPE_SSELOG) || ((cached_type == TYPE_SSELOG1) || ((cached_type == TYPE_SSEIADD) || ((cached_type == TYPE_SSEIADD1) || ((cached_type == TYPE_SSEISHFT) || ((cached_type == TYPE_SSEISHFT1) || ((cached_type == TYPE_SSEIMUL) || ((cached_type == TYPE_SSE) || ((cached_type == TYPE_SSEMOV) || ((cached_type == TYPE_SSEADD) || ((cached_type == TYPE_SSEADD1) || ((cached_type == TYPE_SSEMUL) || ((cached_type == TYPE_SSECMP) || ((cached_type == TYPE_SSECOMI) || ((cached_type == TYPE_SSECVT) || ((cached_type == TYPE_SSESHUF) || ((cached_type == TYPE_SSESHUF1) || ((cached_type == TYPE_SSECVT1) || ((cached_type == TYPE_SSEICVT) || ((cached_type == TYPE_SSEDIV) || ((cached_type == TYPE_SSEINS) || ((cached_type == TYPE_SSEMULADD) || (cached_type == TYPE_SSE4ARG)))))))))))))))))))))))
        {
	  return UNIT_SSE;
        }
      else if ((cached_type == TYPE_MMX) || ((cached_type == TYPE_MMXMOV) || ((cached_type == TYPE_MMXADD) || ((cached_type == TYPE_MMXMUL) || ((cached_type == TYPE_MMXCMP) || ((cached_type == TYPE_MMXCVT) || (cached_type == TYPE_MMXSHFT)))))))
        {
	  return UNIT_MMX;
        }
      else if (cached_type == TYPE_OTHER)
        {
	  return UNIT_UNKNOWN;
        }
      else
        {
	  return UNIT_INTEGER;
        }

    case 1905:  /* atomic_xorsi */
    case 1904:  /* atomic_orsi */
    case 1903:  /* atomic_andsi */
    case 1902:  /* atomic_xorhi */
    case 1901:  /* atomic_orhi */
    case 1900:  /* atomic_andhi */
    case 1899:  /* atomic_xorqi */
    case 1898:  /* atomic_orqi */
    case 1897:  /* atomic_andqi */
    case 1896:  /* atomic_subsi */
    case 1895:  /* atomic_subhi */
    case 1894:  /* atomic_subqi */
    case 1893:  /* atomic_addsi */
    case 1892:  /* atomic_addhi */
    case 1891:  /* atomic_addqi */
    case 1890:  /* atomic_exchangesi */
    case 1889:  /* atomic_exchangehi */
    case 1888:  /* atomic_exchangeqi */
    case 1887:  /* *atomic_fetch_add_cmpsi */
    case 1886:  /* *atomic_fetch_add_cmphi */
    case 1885:  /* *atomic_fetch_add_cmpqi */
    case 1884:  /* atomic_fetch_addsi */
    case 1883:  /* atomic_fetch_addhi */
    case 1882:  /* atomic_fetch_addqi */
    case 1881:  /* atomic_compare_and_swapdi_doubleword */
    case 1880:  /* atomic_compare_and_swapsi_1 */
    case 1879:  /* atomic_compare_and_swaphi_1 */
    case 1878:  /* atomic_compare_and_swapqi_1 */
    case 1875:  /* atomic_storedi_fpu */
    case 1874:  /* atomic_storesi_1 */
    case 1873:  /* atomic_storehi_1 */
    case 1872:  /* atomic_storeqi_1 */
    case 1871:  /* atomic_loaddi_fpu */
    case 1870:  /* mfence_nosse */
    case 1772:  /* avx_pd256_pd */
    case 1771:  /* avx_ps256_ps */
    case 1770:  /* avx_si256_si */
    case 1725:  /* *avx_vperm_broadcast_v4df */
    case 1724:  /* *avx_vperm_broadcast_v8sf */
    case 1463:  /* sse3_monitor */
    case 1462:  /* sse3_mwait */
    case 1436:  /* *sse2_storeq */
    case 1435:  /* *vec_ext_v4si_mem */
    case 1434:  /* sse2_stored */
    case 1240:  /* vec_extract_lo_v32qi */
    case 1238:  /* vec_extract_lo_v16hi */
    case 1235:  /* vec_extract_lo_v8sf */
    case 1234:  /* vec_extract_lo_v8si */
    case 1231:  /* vec_extract_lo_v4df */
    case 1230:  /* vec_extract_lo_v4di */
    case 1229:  /* *vec_extract_v4sf_mem */
    case 1227:  /* *vec_extractv4sf_0 */
    case 987:  /* *absnegv2df2 */
    case 986:  /* *absnegv4df2 */
    case 985:  /* *absnegv4sf2 */
    case 984:  /* *absnegv8sf2 */
    case 962:  /* movdi_to_sse */
    case 937:  /* *vec_extractv2si_0 */
    case 867:  /* *vec_extractv2sf_0 */
    case 835:  /* xtest_1 */
    case 834:  /* xabort */
    case 833:  /* xend */
    case 832:  /* xbegin_1 */
    case 831:  /* *pause */
    case 830:  /* rdseedsi_1 */
    case 829:  /* rdseedhi_1 */
    case 828:  /* rdrandsi_1 */
    case 827:  /* rdrandhi_1 */
    case 820:  /* xrstor */
    case 819:  /* xsaveopt */
    case 818:  /* xsave */
    case 817:  /* fxrstor */
    case 816:  /* fxsave */
    case 815:  /* rdtscp */
    case 814:  /* rdtsc */
    case 813:  /* rdpmc */
    case 799:  /* trap */
    case 743:  /* cld */
    case 626:  /* *tls_dynamic_gnu2_combine_32 */
    case 615:  /* *tls_local_dynamic_32_once */
    case 612:  /* *parityhi2_cmp */
    case 611:  /* paritysi2_cmp */
    case 610:  /* paritydi2_cmp */
    case 609:  /* bswaphi_lowpart */
    case 608:  /* *bswaphi_lowpart_1 */
    case 574:  /* ffssi2_no_cmove */
    case 573:  /* split_stack_return */
    case 571:  /* eh_return_internal */
    case 567:  /* pad */
    case 566:  /* nops */
    case 565:  /* nop */
    case 563:  /* simple_return_pop_internal */
    case 562:  /* simple_return_internal_long */
    case 561:  /* simple_return_internal */
    case 560:  /* prologue_use */
    case 559:  /* *memory_blockage */
    case 558:  /* blockage */
    case 540:  /* *jccxf_si_r_i387 */
    case 539:  /* *jccdf_si_r_i387 */
    case 538:  /* *jccsf_si_r_i387 */
    case 537:  /* *jccxf_hi_r_i387 */
    case 536:  /* *jccdf_hi_r_i387 */
    case 535:  /* *jccsf_hi_r_i387 */
    case 534:  /* *jccxf_si_i387 */
    case 533:  /* *jccdf_si_i387 */
    case 532:  /* *jccsf_si_i387 */
    case 531:  /* *jccxf_hi_i387 */
    case 530:  /* *jccdf_hi_i387 */
    case 529:  /* *jccsf_hi_i387 */
    case 528:  /* *jccuxf_r_i387 */
    case 527:  /* *jccudf_r_i387 */
    case 526:  /* *jccusf_r_i387 */
    case 525:  /* *jccuxf_i387 */
    case 524:  /* *jccudf_i387 */
    case 523:  /* *jccusf_i387 */
    case 522:  /* *jccdf_r_i387 */
    case 521:  /* *jccsf_r_i387 */
    case 520:  /* *jccdf_i387 */
    case 519:  /* *jccsf_i387 */
    case 518:  /* *jccxf_r_i387 */
    case 517:  /* *jccxf_i387 */
    case 516:  /* *jccxf_0_r_i387 */
    case 515:  /* *jccdf_0_r_i387 */
    case 514:  /* *jccsf_0_r_i387 */
    case 513:  /* *jccxf_0_i387 */
    case 512:  /* *jccdf_0_i387 */
    case 511:  /* *jccsf_0_i387 */
    case 510:  /* *jcc_btsi_mask_1 */
    case 509:  /* *jcc_btsi_1 */
    case 508:  /* *jcc_btdi_mask */
    case 507:  /* *jcc_btsi_mask */
    case 506:  /* *jcc_btdi */
    case 505:  /* *jcc_btsi */
    case 498:  /* *setcc_si_1_movzbl */
    case 497:  /* *setcc_si_1_and */
    case 483:  /* ix86_rotrdi3_doubleword */
    case 482:  /* ix86_rotldi3_doubleword */
    case 415:  /* copysigntf3_var */
    case 414:  /* copysigndf3_var */
    case 413:  /* copysignsf3_var */
    case 412:  /* copysigntf3_const */
    case 411:  /* copysigndf3_const */
    case 410:  /* copysignsf3_const */
    case 397:  /* *absnegtf2_sse */
    case 396:  /* *absnegxf2_i387 */
    case 395:  /* *absnegdf2_i387 */
    case 394:  /* *absnegsf2_i387 */
    case 393:  /* *absnegdf2_sse */
    case 392:  /* *absnegsf2_sse */
    case 391:  /* *absnegdf2_mixed */
    case 390:  /* *absnegsf2_mixed */
    case 381:  /* *negti2_doubleword */
    case 380:  /* *negdi2_doubleword */
    case 331:  /* *testqi_ext_3 */
    case 264:  /* *subti3_doubleword */
    case 263:  /* *subdi3_doubleword */
    case 232:  /* *addti3_doubleword */
    case 231:  /* *adddi3_doubleword */
    case 183:  /* *floatdixf2_1 */
    case 182:  /* *floatdidf2_1 */
    case 181:  /* *floatdisf2_1 */
    case 180:  /* *floatsixf2_1 */
    case 179:  /* *floatsidf2_1 */
    case 178:  /* *floatsisf2_1 */
    case 171:  /* *floathixf2_1 */
    case 170:  /* *floathidf2_1 */
    case 169:  /* *floathisf2_1 */
    case 146:  /* *fixuns_truncdf_1 */
    case 145:  /* *fixuns_truncsf_1 */
    case 124:  /* extendsidi2_1 */
    case 48:  /* x86_sahf_1 */
      return UNIT_UNKNOWN;

    case 946:  /* *mmx_femms */
    case 945:  /* *mmx_emms */
    case 944:  /* *mmx_maskmovq */
    case 943:  /* *mmx_maskmovq */
    case 942:  /* mmx_pmovmskb */
    case 941:  /* mmx_psadbw */
    case 940:  /* *mmx_uavgv4hi3 */
    case 939:  /* *mmx_uavgv8qi3 */
    case 936:  /* *mmx_concatv2si */
    case 935:  /* *vec_dupv2si */
    case 934:  /* *vec_dupv4hi */
    case 933:  /* mmx_pswapdv2si2 */
    case 932:  /* mmx_pshufw_1 */
    case 931:  /* mmx_pextrw */
    case 930:  /* *mmx_pinsrw */
    case 929:  /* mmx_punpckldq */
    case 928:  /* mmx_punpckhdq */
    case 927:  /* mmx_punpcklwd */
    case 926:  /* mmx_punpckhwd */
    case 925:  /* mmx_punpcklbw */
    case 924:  /* mmx_punpckhbw */
    case 923:  /* mmx_packuswb */
    case 922:  /* mmx_packssdw */
    case 921:  /* mmx_packsswb */
    case 920:  /* *mmx_xorv2si3 */
    case 919:  /* *mmx_iorv2si3 */
    case 918:  /* *mmx_andv2si3 */
    case 917:  /* *mmx_xorv4hi3 */
    case 916:  /* *mmx_iorv4hi3 */
    case 915:  /* *mmx_andv4hi3 */
    case 914:  /* *mmx_xorv8qi3 */
    case 913:  /* *mmx_iorv8qi3 */
    case 912:  /* *mmx_andv8qi3 */
    case 911:  /* mmx_andnotv2si3 */
    case 910:  /* mmx_andnotv4hi3 */
    case 909:  /* mmx_andnotv8qi3 */
    case 908:  /* mmx_gtv2si3 */
    case 907:  /* mmx_gtv4hi3 */
    case 906:  /* mmx_gtv8qi3 */
    case 905:  /* *mmx_eqv2si3 */
    case 904:  /* *mmx_eqv4hi3 */
    case 903:  /* *mmx_eqv8qi3 */
    case 902:  /* mmx_lshrv1di3 */
    case 901:  /* mmx_ashlv1di3 */
    case 900:  /* mmx_lshrv2si3 */
    case 899:  /* mmx_ashlv2si3 */
    case 898:  /* mmx_lshrv4hi3 */
    case 897:  /* mmx_ashlv4hi3 */
    case 896:  /* mmx_ashrv2si3 */
    case 895:  /* mmx_ashrv4hi3 */
    case 894:  /* *mmx_uminv8qi3 */
    case 893:  /* *mmx_umaxv8qi3 */
    case 892:  /* *mmx_sminv4hi3 */
    case 891:  /* *mmx_smaxv4hi3 */
    case 890:  /* *sse2_umulv1siv1di3 */
    case 889:  /* *mmx_pmulhrwv4hi3 */
    case 888:  /* *mmx_pmaddwd */
    case 887:  /* *mmx_umulv4hi3_highpart */
    case 886:  /* *mmx_smulv4hi3_highpart */
    case 885:  /* *mmx_mulv4hi3 */
    case 884:  /* *mmx_ussubv4hi3 */
    case 883:  /* *mmx_sssubv4hi3 */
    case 882:  /* *mmx_usaddv4hi3 */
    case 881:  /* *mmx_ssaddv4hi3 */
    case 880:  /* *mmx_ussubv8qi3 */
    case 879:  /* *mmx_sssubv8qi3 */
    case 878:  /* *mmx_usaddv8qi3 */
    case 877:  /* *mmx_ssaddv8qi3 */
    case 876:  /* *mmx_subv1di3 */
    case 875:  /* *mmx_addv1di3 */
    case 874:  /* *mmx_subv2si3 */
    case 873:  /* *mmx_addv2si3 */
    case 872:  /* *mmx_subv4hi3 */
    case 871:  /* *mmx_addv4hi3 */
    case 870:  /* *mmx_subv8qi3 */
    case 869:  /* *mmx_addv8qi3 */
    case 866:  /* *mmx_concatv2sf */
    case 865:  /* *vec_dupv2sf */
    case 864:  /* mmx_pswapdv2sf2 */
    case 863:  /* mmx_floatv2si2 */
    case 862:  /* mmx_pi2fw */
    case 861:  /* mmx_pf2iw */
    case 860:  /* mmx_pf2id */
    case 859:  /* mmx_gev2sf3 */
    case 858:  /* mmx_gtv2sf3 */
    case 857:  /* *mmx_eqv2sf3 */
    case 856:  /* mmx_addsubv2sf3 */
    case 855:  /* mmx_hsubv2sf3 */
    case 854:  /* mmx_haddv2sf3 */
    case 853:  /* mmx_rsqit1v2sf3 */
    case 852:  /* mmx_rsqrtv2sf2 */
    case 851:  /* mmx_rcpit2v2sf3 */
    case 850:  /* mmx_rcpit1v2sf3 */
    case 849:  /* mmx_rcpv2sf2 */
    case 848:  /* *mmx_sminv2sf3 */
    case 847:  /* *mmx_smaxv2sf3 */
    case 846:  /* *mmx_sminv2sf3_finite */
    case 845:  /* *mmx_smaxv2sf3_finite */
    case 844:  /* *mmx_mulv2sf3 */
    case 843:  /* *mmx_subv2sf3 */
    case 842:  /* *mmx_addv2sf3 */
    case 841:  /* sse_movntq */
    case 801:  /* *prefetch_3dnow */
    case 1163:  /* sse_cvtps2pi */
    case 1164:  /* sse_cvttps2pi */
    case 1176:  /* sse2_cvtpd2pi */
    case 1177:  /* sse2_cvttpd2pi */
      return UNIT_MMX;

    case 1877:  /* storedi_via_fpu */
    case 1876:  /* loaddi_via_fpu */
    case 776:  /* *movxfcc_1 */
    case 736:  /* fistsi2_ceil_with_temp */
    case 735:  /* fistsi2_floor_with_temp */
    case 734:  /* fisthi2_ceil_with_temp */
    case 733:  /* fisthi2_floor_with_temp */
    case 732:  /* fistsi2_ceil */
    case 731:  /* fistsi2_floor */
    case 730:  /* fisthi2_ceil */
    case 729:  /* fisthi2_floor */
    case 728:  /* fistdi2_ceil_with_temp */
    case 727:  /* fistdi2_floor_with_temp */
    case 726:  /* fistdi2_ceil */
    case 725:  /* fistdi2_floor */
    case 724:  /* *fistdi2_ceil_1 */
    case 723:  /* *fistdi2_floor_1 */
    case 722:  /* *fistsi2_ceil_1 */
    case 721:  /* *fistsi2_floor_1 */
    case 720:  /* *fisthi2_ceil_1 */
    case 719:  /* *fisthi2_floor_1 */
    case 718:  /* frndintxf2_mask_pm_i387 */
    case 717:  /* frndintxf2_mask_pm */
    case 716:  /* frndintxf2_trunc_i387 */
    case 715:  /* frndintxf2_ceil_i387 */
    case 714:  /* frndintxf2_floor_i387 */
    case 713:  /* frndintxf2_trunc */
    case 712:  /* frndintxf2_ceil */
    case 711:  /* frndintxf2_floor */
    case 710:  /* fistsi2_with_temp */
    case 709:  /* fisthi2_with_temp */
    case 708:  /* fistsi2 */
    case 707:  /* fisthi2 */
    case 706:  /* *fistsi2_1 */
    case 705:  /* *fisthi2_1 */
    case 704:  /* fistdi2_with_temp */
    case 703:  /* fistdi2 */
    case 702:  /* *fistdi2_1 */
    case 701:  /* rintxf2 */
    case 698:  /* *fscalexf4_i387 */
    case 697:  /* *f2xm1xf2_i387 */
    case 696:  /* fxtract_extenddfxf3_i387 */
    case 695:  /* fxtract_extendsfxf3_i387 */
    case 694:  /* fxtractxf3_i387 */
    case 693:  /* fyl2xp1_extenddfxf3_i387 */
    case 692:  /* fyl2xp1_extendsfxf3_i387 */
    case 691:  /* fyl2xp1xf3_i387 */
    case 690:  /* fyl2x_extenddfxf3_i387 */
    case 689:  /* fyl2x_extendsfxf3_i387 */
    case 688:  /* fyl2xxf3_i387 */
    case 687:  /* fpatan_extenddfxf3_i387 */
    case 686:  /* fpatan_extendsfxf3_i387 */
    case 685:  /* *fpatanxf3_i387 */
    case 684:  /* fptan_extenddfxf4_i387 */
    case 683:  /* fptan_extendsfxf4_i387 */
    case 682:  /* fptanxf4_i387 */
    case 681:  /* sincos_extenddfxf3_i387 */
    case 680:  /* sincos_extendsfxf3_i387 */
    case 679:  /* sincosxf3 */
    case 678:  /* *cos_extenddfxf2_i387 */
    case 677:  /* *sin_extenddfxf2_i387 */
    case 676:  /* *cos_extendsfxf2_i387 */
    case 675:  /* *sin_extendsfxf2_i387 */
    case 674:  /* *cosxf2_i387 */
    case 673:  /* *sinxf2_i387 */
    case 672:  /* fprem1xf4_i387 */
    case 671:  /* fpremxf4_i387 */
    case 667:  /* sqrt_extenddfxf2_i387 */
    case 666:  /* sqrt_extendsfxf2_i387 */
    case 665:  /* sqrtxf2 */
    case 664:  /* truncxfdf2_i387_noop_unspec */
    case 663:  /* truncxfsf2_i387_noop_unspec */
    case 409:  /* *negextenddfxf2 */
    case 408:  /* *absextenddfxf2 */
    case 407:  /* *negextendsfxf2 */
    case 406:  /* *absextendsfxf2 */
    case 405:  /* *negextendsfdf2 */
    case 404:  /* *absextendsfdf2 */
    case 403:  /* *negxf2_1 */
    case 402:  /* *absxf2_1 */
    case 401:  /* *negdf2_1 */
    case 400:  /* *absdf2_1 */
    case 399:  /* *negsf2_1 */
    case 398:  /* *abssf2_1 */
    case 223:  /* *floatdixf2_i387 */
    case 222:  /* *floatdidf2_i387 */
    case 221:  /* *floatdisf2_i387 */
    case 220:  /* *floatsixf2_i387 */
    case 219:  /* *floatsidf2_i387 */
    case 218:  /* *floatsisf2_i387 */
    case 177:  /* *floathixf2_i387 */
    case 176:  /* *floathidf2_i387 */
    case 175:  /* *floathisf2_i387 */
    case 166:  /* fix_truncsi_i387_with_temp */
    case 165:  /* fix_trunchi_i387_with_temp */
    case 164:  /* fix_truncsi_i387 */
    case 163:  /* fix_trunchi_i387 */
    case 162:  /* fix_truncdi_i387_with_temp */
    case 161:  /* fix_truncdi_i387 */
    case 160:  /* *fix_truncdi_i387_1 */
    case 159:  /* *fix_truncsi_i387_1 */
    case 158:  /* *fix_trunchi_i387_1 */
    case 157:  /* fix_truncdi_i387_fisttp_with_temp */
    case 156:  /* fix_truncsi_i387_fisttp_with_temp */
    case 155:  /* fix_trunchi_i387_fisttp_with_temp */
    case 154:  /* fix_truncdi_i387_fisttp */
    case 153:  /* fix_truncsi_i387_fisttp */
    case 152:  /* fix_trunchi_i387_fisttp */
    case 151:  /* fix_truncdi_fisttp_i387_1 */
    case 150:  /* fix_truncsi_fisttp_i387_1 */
    case 149:  /* fix_trunchi_fisttp_i387_1 */
    case 144:  /* *truncxfdf2_i387 */
    case 143:  /* *truncxfsf2_i387 */
    case 142:  /* truncxfdf2_i387_noop */
    case 141:  /* truncxfsf2_i387_noop */
    case 138:  /* *truncdfsf2_i387_1 */
    case 135:  /* *truncdfsf_fast_i387 */
    case 132:  /* *extenddfxf2_i387 */
    case 131:  /* *extendsfxf2_i387 */
    case 130:  /* *extendsfdf2_i387 */
    case 116:  /* *swapdf */
    case 115:  /* *swapsf */
    case 114:  /* swapxf */
    case 62:  /* *cmpiuxf_i387 */
    case 61:  /* *cmpiudf_i387 */
    case 60:  /* *cmpiusf_i387 */
    case 59:  /* *cmpixf_i387 */
    case 58:  /* *cmpidf_i387 */
    case 57:  /* *cmpisf_i387 */
    case 17:  /* *cmpsf_0_i387 */
    case 18:  /* *cmpdf_0_i387 */
    case 19:  /* *cmpxf_0_i387 */
    case 20:  /* *cmpsf_0_cc_i387 */
    case 21:  /* *cmpdf_0_cc_i387 */
    case 22:  /* *cmpxf_0_cc_i387 */
    case 23:  /* *cmpxf_i387 */
    case 24:  /* *cmpxf_cc_i387 */
    case 25:  /* *cmpsf_i387 */
    case 26:  /* *cmpdf_i387 */
    case 27:  /* *cmpsf_cc_i387 */
    case 28:  /* *cmpdf_cc_i387 */
    case 29:  /* *cmpusf_i387 */
    case 30:  /* *cmpudf_i387 */
    case 31:  /* *cmpuxf_i387 */
    case 32:  /* *cmpusf_cc_i387 */
    case 33:  /* *cmpudf_cc_i387 */
    case 34:  /* *cmpuxf_cc_i387 */
    case 35:  /* *cmpsf_hi_i387 */
    case 36:  /* *cmpdf_hi_i387 */
    case 37:  /* *cmpxf_hi_i387 */
    case 38:  /* *cmpsf_si_i387 */
    case 39:  /* *cmpdf_si_i387 */
    case 40:  /* *cmpxf_si_i387 */
    case 41:  /* *cmpsf_hi_cc_i387 */
    case 42:  /* *cmpdf_hi_cc_i387 */
    case 43:  /* *cmpxf_hi_cc_i387 */
    case 44:  /* *cmpsf_si_cc_i387 */
    case 45:  /* *cmpdf_si_cc_i387 */
    case 46:  /* *cmpxf_si_cc_i387 */
    case 47:  /* x86_fnstsw_1 */
    case 167:  /* x86_fnstcw_1 */
    case 168:  /* x86_fldcw_1 */
    case 224:  /* floatdisf2_i387_with_xmm */
    case 225:  /* floatdidf2_i387_with_xmm */
    case 226:  /* floatdixf2_i387_with_xmm */
    case 737:  /* fxamsf2_i387 */
    case 738:  /* fxamdf2_i387 */
    case 739:  /* fxamxf2_i387 */
    case 740:  /* fxamsf2_i387_with_temp */
    case 741:  /* fxamdf2_i387_with_temp */
      return UNIT_I387;

    case 826:  /* *lwp_lwpinssi3_1 */
    case 825:  /* *lwp_lwpvalsi3_1 */
    case 824:  /* lwp_slwpcbdi */
    case 823:  /* lwp_slwpcbsi */
    case 822:  /* *lwp_llwpcbdi1 */
    case 821:  /* *lwp_llwpcbsi1 */
    case 809:  /* stack_tls_protect_test_di */
    case 808:  /* stack_tls_protect_test_si */
    case 807:  /* stack_protect_test_di */
    case 806:  /* stack_protect_test_si */
    case 805:  /* stack_tls_protect_set_di */
    case 804:  /* stack_tls_protect_set_si */
    case 803:  /* stack_protect_set_di */
    case 802:  /* stack_protect_set_si */
    case 798:  /* probe_stack_rangedi */
    case 797:  /* probe_stack_rangesi */
    case 796:  /* adjust_stack_and_probedi */
    case 795:  /* adjust_stack_and_probesi */
    case 794:  /* allocate_stack_worker_probe_di */
    case 793:  /* allocate_stack_worker_probe_si */
    case 792:  /* pro_epilogue_adjust_stack_di_sub */
    case 791:  /* pro_epilogue_adjust_stack_si_sub */
    case 790:  /* pro_epilogue_adjust_stack_di_add */
    case 789:  /* pro_epilogue_adjust_stack_si_add */
    case 775:  /* *movqicc_noc */
    case 774:  /* *movsicc_noc */
    case 773:  /* *movhicc_noc */
    case 772:  /* *x86_movsicc_0_m1_neg */
    case 771:  /* *x86_movsicc_0_m1_se */
    case 770:  /* *x86_movsicc_0_m1 */
    case 769:  /* *strlenqi_1 */
    case 768:  /* *strlenqi_1 */
    case 767:  /* *cmpstrnqi_1 */
    case 766:  /* *cmpstrnqi_1 */
    case 765:  /* *cmpstrnqi_nz_1 */
    case 764:  /* *cmpstrnqi_nz_1 */
    case 763:  /* *rep_stosqi */
    case 762:  /* *rep_stosqi */
    case 761:  /* *rep_stossi */
    case 760:  /* *rep_stossi */
    case 759:  /* *strsetqi_1 */
    case 758:  /* *strsetqi_1 */
    case 757:  /* *strsethi_1 */
    case 756:  /* *strsethi_1 */
    case 755:  /* *strsetsi_1 */
    case 754:  /* *strsetsi_1 */
    case 753:  /* *rep_movqi */
    case 752:  /* *rep_movqi */
    case 751:  /* *rep_movsi */
    case 750:  /* *rep_movsi */
    case 749:  /* *strmovqi_1 */
    case 748:  /* *strmovqi_1 */
    case 747:  /* *strmovhi_1 */
    case 746:  /* *strmovhi_1 */
    case 745:  /* *strmovsi_1 */
    case 744:  /* *strmovsi_1 */
    case 625:  /* *tls_dynamic_gnu2_call_32 */
    case 624:  /* *tls_dynamic_gnu2_lea_32 */
    case 623:  /* *add_tp_di */
    case 622:  /* *add_tp_si */
    case 621:  /* *add_tp_x32_zext */
    case 620:  /* *add_tp_x32 */
    case 619:  /* *load_tp_di */
    case 618:  /* *load_tp_si */
    case 617:  /* *load_tp_x32_zext */
    case 616:  /* *load_tp_x32 */
    case 614:  /* *tls_local_dynamic_base_32_gnu */
    case 613:  /* *tls_global_dynamic_32_gnu */
    case 607:  /* *bswapsi2 */
    case 606:  /* *bswapsi2_movbe */
    case 605:  /* *popcountdi2_cmp */
    case 604:  /* *popcountsi2_cmp */
    case 603:  /* *popcounthi2_cmp */
    case 602:  /* popcountsi2 */
    case 601:  /* popcounthi2 */
    case 600:  /* *bsrhi */
    case 599:  /* bsr */
    case 598:  /* *tbm_tzmsk_si */
    case 597:  /* *tbm_t1mskc_si */
    case 596:  /* *tbm_blsic_si */
    case 595:  /* *tbm_blsfill_si */
    case 594:  /* *tbm_blcs_si */
    case 593:  /* *tbm_blcmsk_si */
    case 592:  /* *tbm_blcic_si */
    case 591:  /* *tbm_blci_si */
    case 590:  /* *tbm_blcfill_si */
    case 589:  /* tbm_bextri_si */
    case 588:  /* bmi2_pext_si3 */
    case 587:  /* bmi2_pdep_si3 */
    case 586:  /* bmi2_bzhi_si3 */
    case 585:  /* *bmi_blsr_si */
    case 584:  /* *bmi_blsmsk_si */
    case 583:  /* *bmi_blsi_si */
    case 582:  /* bmi_bextr_si */
    case 581:  /* *bmi_andn_si */
    case 580:  /* clzsi2_lzcnt */
    case 579:  /* clzhi2_lzcnt */
    case 578:  /* ctzsi2 */
    case 577:  /* ctzhi2 */
    case 576:  /* *bsfsi_1 */
    case 575:  /* *tzcntsi_1 */
    case 572:  /* leave */
    case 570:  /* set_got_offset_rex64 */
    case 569:  /* set_got_labelled */
    case 568:  /* set_got */
    case 564:  /* simple_return_indirect_internal */
    case 557:  /* *sibcall_value_pop */
    case 556:  /* *call_value_pop */
    case 555:  /* *sibcall_value */
    case 554:  /* *sibcall_value */
    case 553:  /* *call_value */
    case 552:  /* *call_value */
    case 551:  /* *sibcall_pop */
    case 550:  /* *call_pop */
    case 549:  /* *sibcall */
    case 548:  /* *sibcall */
    case 547:  /* *call */
    case 546:  /* *call */
    case 545:  /* *tablejump_1 */
    case 544:  /* *tablejump_1 */
    case 543:  /* *indirect_jump */
    case 542:  /* *indirect_jump */
    case 541:  /* jump */
    case 504:  /* *jcc_2 */
    case 503:  /* *jcc_1 */
    case 500:  /* *setcc_qi_slp */
    case 499:  /* *setcc_qi */
    case 496:  /* *btdi */
    case 495:  /* *btsi */
    case 494:  /* *rotrqi3_1_slp */
    case 493:  /* *rotlqi3_1_slp */
    case 492:  /* *rotrhi3_1 */
    case 491:  /* *rotlhi3_1 */
    case 490:  /* *rotrqi3_1 */
    case 489:  /* *rotlqi3_1 */
    case 488:  /* *rotrdi3_1 */
    case 487:  /* *rotldi3_1 */
    case 486:  /* *rotrsi3_1 */
    case 485:  /* *rotlsi3_1 */
    case 484:  /* *bmi2_rorxsi3_1 */
    case 481:  /* *rotrdi3_mask */
    case 480:  /* *rotldi3_mask */
    case 479:  /* *rotrsi3_mask */
    case 478:  /* *rotlsi3_mask */
    case 477:  /* *ashrdi3_cconly */
    case 476:  /* *lshrdi3_cconly */
    case 475:  /* *ashrsi3_cconly */
    case 474:  /* *lshrsi3_cconly */
    case 473:  /* *ashrhi3_cconly */
    case 472:  /* *lshrhi3_cconly */
    case 471:  /* *ashrqi3_cconly */
    case 470:  /* *lshrqi3_cconly */
    case 469:  /* *ashrdi3_cmp */
    case 468:  /* *lshrdi3_cmp */
    case 467:  /* *ashrsi3_cmp */
    case 466:  /* *lshrsi3_cmp */
    case 465:  /* *ashrhi3_cmp */
    case 464:  /* *lshrhi3_cmp */
    case 463:  /* *ashrqi3_cmp */
    case 462:  /* *lshrqi3_cmp */
    case 461:  /* *ashrqi3_1_slp */
    case 460:  /* *lshrqi3_1_slp */
    case 459:  /* *ashrhi3_1 */
    case 458:  /* *lshrhi3_1 */
    case 457:  /* *ashrqi3_1 */
    case 456:  /* *lshrqi3_1 */
    case 455:  /* *ashrdi3_1 */
    case 454:  /* *lshrdi3_1 */
    case 453:  /* *ashrsi3_1 */
    case 452:  /* *lshrsi3_1 */
    case 451:  /* *bmi2_ashrsi3_1 */
    case 450:  /* *bmi2_lshrsi3_1 */
    case 449:  /* ashrsi3_cvt */
    case 448:  /* x86_shrd */
    case 447:  /* *ashrdi3_doubleword */
    case 446:  /* *lshrdi3_doubleword */
    case 445:  /* *ashrdi3_mask */
    case 444:  /* *lshrdi3_mask */
    case 443:  /* *ashrsi3_mask */
    case 442:  /* *lshrsi3_mask */
    case 441:  /* *ashldi3_cconly */
    case 440:  /* *ashlsi3_cconly */
    case 439:  /* *ashlhi3_cconly */
    case 438:  /* *ashlqi3_cconly */
    case 437:  /* *ashldi3_cmp */
    case 436:  /* *ashlsi3_cmp */
    case 435:  /* *ashlhi3_cmp */
    case 434:  /* *ashlqi3_cmp */
    case 433:  /* *ashlqi3_1_slp */
    case 432:  /* *ashlqi3_1 */
    case 431:  /* *ashlhi3_1 */
    case 430:  /* *ashldi3_1 */
    case 429:  /* *ashlsi3_1 */
    case 428:  /* *bmi2_ashlsi3_1 */
    case 427:  /* *ashldi3_mask */
    case 426:  /* *ashlsi3_mask */
    case 425:  /* x86_shld */
    case 424:  /* *ashldi3_doubleword */
    case 423:  /* *one_cmpldi2_2 */
    case 422:  /* *one_cmplsi2_2 */
    case 421:  /* *one_cmplhi2_2 */
    case 420:  /* *one_cmplqi2_2 */
    case 419:  /* *one_cmplqi2_1 */
    case 418:  /* *one_cmpldi2_1 */
    case 417:  /* *one_cmplsi2_1 */
    case 416:  /* *one_cmplhi2_1 */
    case 389:  /* *negdi2_cmpz */
    case 388:  /* *negsi2_cmpz */
    case 387:  /* *neghi2_cmpz */
    case 386:  /* *negqi2_cmpz */
    case 385:  /* *negdi2_1 */
    case 384:  /* *negsi2_1 */
    case 383:  /* *neghi2_1 */
    case 382:  /* *negqi2_1 */
    case 379:  /* *xorqi_cc_ext_1 */
    case 378:  /* *xorqi_ext_2 */
    case 377:  /* *iorqi_ext_2 */
    case 376:  /* *xorqi_ext_1 */
    case 375:  /* *iorqi_ext_1 */
    case 374:  /* *xorqi_ext_0 */
    case 373:  /* *iorqi_ext_0 */
    case 372:  /* *xordi_3 */
    case 371:  /* *iordi_3 */
    case 370:  /* *xorsi_3 */
    case 369:  /* *iorsi_3 */
    case 368:  /* *xorhi_3 */
    case 367:  /* *iorhi_3 */
    case 366:  /* *xorqi_3 */
    case 365:  /* *iorqi_3 */
    case 364:  /* *xorqi_2_slp */
    case 363:  /* *iorqi_2_slp */
    case 362:  /* *xordi_2 */
    case 361:  /* *iordi_2 */
    case 360:  /* *xorsi_2 */
    case 359:  /* *iorsi_2 */
    case 358:  /* *xorhi_2 */
    case 357:  /* *iorhi_2 */
    case 356:  /* *xorqi_2 */
    case 355:  /* *iorqi_2 */
    case 354:  /* *xorqi_1_slp */
    case 353:  /* *iorqi_1_slp */
    case 352:  /* *xorqi_1 */
    case 351:  /* *iorqi_1 */
    case 350:  /* *xordi_1 */
    case 349:  /* *iordi_1 */
    case 348:  /* *xorsi_1 */
    case 347:  /* *iorsi_1 */
    case 346:  /* *xorhi_1 */
    case 345:  /* *iorhi_1 */
    case 344:  /* *andqi_ext_2 */
    case 343:  /* *andqi_ext_1 */
    case 342:  /* *andqi_ext_0_cc */
    case 341:  /* andqi_ext_0 */
    case 340:  /* *andqi_2_slp */
    case 339:  /* *andsi_2 */
    case 338:  /* *andhi_2 */
    case 337:  /* *andqi_2 */
    case 336:  /* *andqi_2_maybe_si */
    case 335:  /* *andqi_1_slp */
    case 334:  /* *andqi_1 */
    case 333:  /* *andhi_1 */
    case 332:  /* *andsi_1 */
    case 330:  /* *testqi_ext_2 */
    case 329:  /* *testqi_ext_1 */
    case 328:  /* *testqi_ext_0 */
    case 327:  /* *testsi_1 */
    case 326:  /* *testhi_1 */
    case 325:  /* *testqi_1 */
    case 324:  /* *testqi_1_maybe_si */
    case 323:  /* udivmodhiqi3 */
    case 322:  /* *udivmodsi4_noext */
    case 321:  /* *udivmodhi4_noext */
    case 320:  /* *udivmodsi4 */
    case 319:  /* *udivmodhi4 */
    case 318:  /* udivmodsi4_1 */
    case 317:  /* divmodhiqi3 */
    case 316:  /* *divmodsi4_noext */
    case 315:  /* *divmodhi4_noext */
    case 314:  /* *divmodsi4 */
    case 313:  /* *divmodhi4 */
    case 312:  /* divmodsi4_1 */
    case 311:  /* *umulsi3_highpart_1 */
    case 310:  /* *smulsi3_highpart_1 */
    case 309:  /* *umulqihi3_1 */
    case 308:  /* *mulqihi3_1 */
    case 307:  /* *mulsidi3_1 */
    case 306:  /* *umulsidi3_1 */
    case 305:  /* *bmi2_umulsidi3_1 */
    case 304:  /* *mulqi3_1 */
    case 303:  /* *mulhi3_1 */
    case 302:  /* *mulsi3_1 */
    case 301:  /* *subdi3_cc_overflow */
    case 300:  /* *adddi3_cc_overflow */
    case 299:  /* *subsi3_cc_overflow */
    case 298:  /* *addsi3_cc_overflow */
    case 297:  /* *subhi3_cc_overflow */
    case 296:  /* *addhi3_cc_overflow */
    case 295:  /* *subqi3_cc_overflow */
    case 294:  /* *addqi3_cc_overflow */
    case 293:  /* *subsi3_cconly_overflow */
    case 292:  /* *subhi3_cconly_overflow */
    case 291:  /* *subqi3_cconly_overflow */
    case 290:  /* *addsi3_cconly_overflow */
    case 289:  /* *addhi3_cconly_overflow */
    case 288:  /* *addqi3_cconly_overflow */
    case 287:  /* adcxdi3 */
    case 286:  /* adcxsi3 */
    case 285:  /* *subdi3_carry */
    case 284:  /* *adddi3_carry */
    case 283:  /* *subsi3_carry */
    case 282:  /* *addsi3_carry */
    case 281:  /* *subhi3_carry */
    case 280:  /* *addhi3_carry */
    case 279:  /* *subqi3_carry */
    case 278:  /* *addqi3_carry */
    case 277:  /* *subdi_3 */
    case 276:  /* *subsi_3 */
    case 275:  /* *subhi_3 */
    case 274:  /* *subqi_3 */
    case 273:  /* *subdi_2 */
    case 272:  /* *subsi_2 */
    case 271:  /* *subhi_2 */
    case 270:  /* *subqi_2 */
    case 269:  /* *subqi_1_slp */
    case 268:  /* *subdi_1 */
    case 267:  /* *subsi_1 */
    case 266:  /* *subhi_1 */
    case 265:  /* *subqi_1 */
    case 262:  /* *lea_general_4 */
    case 261:  /* *lea_general_4 */
    case 260:  /* *lea_general_3 */
    case 259:  /* *lea_general_2 */
    case 258:  /* *lea_general_1 */
    case 257:  /* *addqi_ext_2 */
    case 256:  /* addqi_ext_1 */
    case 255:  /* *adddi_5 */
    case 254:  /* *addsi_5 */
    case 253:  /* *addhi_5 */
    case 252:  /* *addqi_5 */
    case 251:  /* *addsi_4 */
    case 250:  /* *addhi_4 */
    case 249:  /* *addqi_4 */
    case 248:  /* *adddi_3 */
    case 247:  /* *addsi_3 */
    case 246:  /* *addhi_3 */
    case 245:  /* *addqi_3 */
    case 244:  /* *adddi_2 */
    case 243:  /* *addsi_2 */
    case 242:  /* *addhi_2 */
    case 241:  /* *addqi_2 */
    case 240:  /* *addqi_1_slp */
    case 239:  /* *addqi_1 */
    case 238:  /* *addhi_1 */
    case 237:  /* *adddi_1 */
    case 236:  /* *addsi_1 */
    case 235:  /* addqi3_cc */
    case 234:  /* *adddi3_cc */
    case 233:  /* *addsi3_cc */
    case 230:  /* *leasi */
    case 229:  /* *floatunssixf2_1 */
    case 228:  /* *floatunssidf2_1 */
    case 227:  /* *floatunssisf2_1 */
    case 127:  /* extendqihi2 */
    case 126:  /* extendqisi2 */
    case 125:  /* extendhisi2 */
    case 123:  /* *zero_extendqihi2 */
    case 122:  /* zero_extendqihi2_and */
    case 121:  /* *zero_extendhisi2 */
    case 120:  /* *zero_extendqisi2 */
    case 119:  /* zero_extendhisi2_and */
    case 118:  /* zero_extendqisi2_and */
    case 104:  /* *movqi_insv_2 */
    case 103:  /* *movsi_insv_1 */
    case 102:  /* *movqi_extzv_2 */
    case 101:  /* *movsi_extzv_1 */
    case 100:  /* *movqi_extv_1 */
    case 99:  /* *movsi_extv_1 */
    case 98:  /* *movhi_extv_1 */
    case 97:  /* *movstricthi_xor */
    case 96:  /* *movstrictqi_xor */
    case 95:  /* *movstricthi_1 */
    case 94:  /* *movstrictqi_1 */
    case 93:  /* *swaphi_2 */
    case 92:  /* *swapqi_2 */
    case 91:  /* *swaphi_1 */
    case 90:  /* *swapqi_1 */
    case 89:  /* swapsi */
    case 88:  /* *movabsdi_2 */
    case 87:  /* *movabssi_2 */
    case 86:  /* *movabshi_2 */
    case 85:  /* *movabsqi_2 */
    case 84:  /* *movabsdi_1 */
    case 83:  /* *movabssi_1 */
    case 82:  /* *movabshi_1 */
    case 81:  /* *movabsqi_1 */
    case 80:  /* *movqi_internal */
    case 79:  /* *movhi_internal */
    case 74:  /* *movsi_or */
    case 73:  /* *movsi_xor */
    case 72:  /* *popdi1_epilogue */
    case 71:  /* *popsi1_epilogue */
    case 70:  /* *popdi1 */
    case 69:  /* *popsi1 */
    case 68:  /* *pushdi2_prologue */
    case 67:  /* *pushsi2_prologue */
    case 66:  /* *pushhi2 */
    case 65:  /* *pushqi2 */
    case 64:  /* *pushsi2 */
    case 63:  /* *pushdi2 */
    case 16:  /* *cmpqi_ext_4 */
    case 15:  /* *cmpqi_ext_3_insn */
    case 14:  /* *cmpqi_ext_2 */
    case 13:  /* *cmpqi_ext_1 */
    case 12:  /* *cmpdi_minus_1 */
    case 11:  /* *cmpsi_minus_1 */
    case 10:  /* *cmphi_minus_1 */
    case 9:  /* *cmpqi_minus_1 */
    case 8:  /* *cmpdi_1 */
    case 7:  /* *cmpsi_1 */
    case 6:  /* *cmphi_1 */
    case 5:  /* *cmpqi_1 */
    case 4:  /* *cmpdi_ccno_1 */
    case 3:  /* *cmpsi_ccno_1 */
    case 2:  /* *cmphi_ccno_1 */
    case 1:  /* *cmpqi_ccno_1 */
      return UNIT_INTEGER;

    default:
      return UNIT_SSE;

    }
}

EXPORTED_CONST int length_unit_log = 0;
