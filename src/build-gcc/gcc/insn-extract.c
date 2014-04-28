/* Generated automatically by the program `genextract'
   from the machine description file `md'.  */

#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "tm.h"
#include "rtl.h"
#include "insn-config.h"
#include "recog.h"
#include "diagnostic-core.h"

/* This variable is used as the "location" of any missing operand
   whose numbers are skipped by a given pattern.  */
static rtx junk ATTRIBUTE_UNUSED;

void
insn_extract (rtx insn)
{
  rtx *ro = recog_data.operand;
  rtx **ro_loc = recog_data.operand_loc;
  rtx pat = PATTERN (insn);
  int i ATTRIBUTE_UNUSED; /* only for peepholes */

#ifdef ENABLE_CHECKING
  memset (ro, 0xab, sizeof (*ro) * MAX_RECOG_OPERANDS);
  memset (ro_loc, 0xab, sizeof (*ro_loc) * MAX_RECOG_OPERANDS);
#endif

  switch (INSN_CODE (insn))
    {
    default:
      /* Control reaches here if insn_extract has been called with an
         unrecognizable insn (code -1), or an insn whose INSN_CODE
         corresponds to a DEFINE_EXPAND in the machine description;
         either way, a bug.  */
      if (INSN_CODE (insn) < 0)
        fatal_insn ("unrecognizable insn:", insn);
      else
        fatal_insn ("insn with invalid code number:", insn);

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
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0), 1));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 1));
      recog_data.dup_loc[0] = &XEXP (XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0), 0);
      recog_data.dup_num[0] = 0;
      break;

    case 1890:  /* atomic_exchangesi */
    case 1889:  /* atomic_exchangehi */
    case 1888:  /* atomic_exchangeqi */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      ro[2] = *(ro_loc[2] = &XEXP (XVECEXP (pat, 0, 1), 1));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 1));
      recog_data.dup_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0);
      recog_data.dup_num[0] = 1;
      break;

    case 1887:  /* *atomic_fetch_add_cmpsi */
    case 1886:  /* *atomic_fetch_add_cmphi */
    case 1885:  /* *atomic_fetch_add_cmpqi */
      ro[0] = *(ro_loc[0] = &XVECEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 1));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0, 1));
      recog_data.dup_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0);
      recog_data.dup_num[0] = 0;
      recog_data.dup_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0);
      recog_data.dup_num[1] = 0;
      break;

    case 1884:  /* atomic_fetch_addsi */
    case 1883:  /* atomic_fetch_addhi */
    case 1882:  /* atomic_fetch_addqi */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 1));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 1));
      recog_data.dup_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0);
      recog_data.dup_num[0] = 1;
      recog_data.dup_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0);
      recog_data.dup_num[1] = 1;
      break;

    case 1881:  /* atomic_compare_and_swapdi_doubleword */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 1));
      ro[4] = *(ro_loc[4] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 2));
      ro[5] = *(ro_loc[5] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 3));
      ro[6] = *(ro_loc[6] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 4));
      ro[7] = *(ro_loc[7] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 5));
      ro[8] = *(ro_loc[8] = &XEXP (XVECEXP (pat, 0, 4), 0));
      recog_data.dup_loc[0] = &XEXP (XVECEXP (pat, 0, 2), 0);
      recog_data.dup_num[0] = 2;
      break;

    case 1880:  /* atomic_compare_and_swapsi_1 */
    case 1879:  /* atomic_compare_and_swaphi_1 */
    case 1878:  /* atomic_compare_and_swapqi_1 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 1));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 2));
      ro[4] = *(ro_loc[4] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 3));
      recog_data.dup_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0);
      recog_data.dup_num[0] = 1;
      break;

    case 1870:  /* mfence_nosse */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      recog_data.dup_loc[0] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0);
      recog_data.dup_num[0] = 0;
      break;

    case 1866:  /* *avx2_gatherdiv8sf_4 */
    case 1865:  /* *avx2_gatherdiv8sf_4 */
    case 1864:  /* *avx2_gatherdiv8si_4 */
    case 1863:  /* *avx2_gatherdiv8si_4 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0, 1), 0), 0, 0));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XVECEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0, 1), 0), 0, 1));
      ro[4] = *(ro_loc[4] = &XVECEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0, 3));
      ro[5] = *(ro_loc[5] = &XVECEXP (XEXP (XVECEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0, 1), 0), 0, 2));
      ro[6] = *(ro_loc[6] = &XVECEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0, 1));
      break;

    case 1862:  /* *avx2_gatherdiv8sf_3 */
    case 1861:  /* *avx2_gatherdiv8sf_3 */
    case 1860:  /* *avx2_gatherdiv8si_3 */
    case 1859:  /* *avx2_gatherdiv8si_3 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0, 0));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XVECEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0, 1), 0), 0, 0));
      ro[4] = *(ro_loc[4] = &XVECEXP (XEXP (XVECEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0, 1), 0), 0, 1));
      ro[5] = *(ro_loc[5] = &XVECEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0, 3));
      ro[6] = *(ro_loc[6] = &XVECEXP (XEXP (XVECEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0, 1), 0), 0, 2));
      ro[7] = *(ro_loc[7] = &XVECEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0, 1));
      break;

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
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 1), 0), 0, 0));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 1), 0), 0, 1));
      ro[4] = *(ro_loc[4] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 3));
      ro[5] = *(ro_loc[5] = &XVECEXP (XEXP (XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 1), 0), 0, 2));
      ro[6] = *(ro_loc[6] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 1));
      break;

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
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 1), 0), 0, 0));
      ro[4] = *(ro_loc[4] = &XVECEXP (XEXP (XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 1), 0), 0, 1));
      ro[5] = *(ro_loc[5] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 3));
      ro[6] = *(ro_loc[6] = &XVECEXP (XEXP (XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 1), 0), 0, 2));
      ro[7] = *(ro_loc[7] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 1));
      break;

    case 1792:  /* *vcvtps2ph */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (XEXP (pat, 1), 0), 0, 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XEXP (pat, 1), 0), 0, 1));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (pat, 1), 1));
      break;

    case 1769:  /* avx2_maskstoreq256 */
    case 1768:  /* avx2_maskstored256 */
    case 1767:  /* avx2_maskstoreq */
    case 1766:  /* avx2_maskstored */
    case 1765:  /* avx_maskstorepd256 */
    case 1764:  /* avx_maskstoreps256 */
    case 1763:  /* avx_maskstorepd */
    case 1762:  /* avx_maskstoreps */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (pat, 1), 0, 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (pat, 1), 0, 1));
      recog_data.dup_loc[0] = &XVECEXP (XEXP (pat, 1), 0, 2);
      recog_data.dup_num[0] = 0;
      break;

    case 1761:  /* avx2_maskloadq256 */
    case 1760:  /* avx2_maskloadd256 */
    case 1759:  /* avx2_maskloadq */
    case 1758:  /* avx2_maskloadd */
    case 1757:  /* avx_maskloadpd256 */
    case 1756:  /* avx_maskloadps256 */
    case 1755:  /* avx_maskloadpd */
    case 1754:  /* avx_maskloadps */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (pat, 1), 0, 1));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (pat, 1), 0, 0));
      break;

    case 1739:  /* *avx_vperm2f128v4df_nozero */
    case 1738:  /* *avx_vperm2f128v8sf_nozero */
    case 1737:  /* *avx_vperm2f128v8si_nozero */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (pat, 1), 0), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (pat, 1), 1));
      ro[4] = *(ro_loc[4] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 0));
      break;

    case 1729:  /* *avx_vpermilpv2df */
    case 1728:  /* *avx_vpermilpv4df */
    case 1727:  /* *avx_vpermilpv4sf */
    case 1726:  /* *avx_vpermilpv8sf */
    case 1725:  /* *avx_vperm_broadcast_v4df */
    case 1724:  /* *avx_vperm_broadcast_v8sf */
    case 1723:  /* *avx_vperm_broadcast_v4sf */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (pat, 1), 1));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 0));
      break;

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
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 1), 0));
      recog_data.dup_loc[0] = &XEXP (XEXP (pat, 1), 1);
      recog_data.dup_num[0] = 1;
      break;

    case 1673:  /* xop_maskcmp_uns2v2di3 */
    case 1672:  /* xop_maskcmp_uns2v4si3 */
    case 1671:  /* xop_maskcmp_uns2v8hi3 */
    case 1670:  /* xop_maskcmp_uns2v16qi3 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (pat, 1), 0, 0));
      ro[2] = *(ro_loc[2] = &XEXP (XVECEXP (XEXP (pat, 1), 0, 0), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (XEXP (pat, 1), 0, 0), 1));
      break;

    case 1669:  /* xop_maskcmp_unsv2di3 */
    case 1668:  /* xop_maskcmp_unsv4si3 */
    case 1667:  /* xop_maskcmp_unsv8hi3 */
    case 1666:  /* xop_maskcmp_unsv16qi3 */
    case 1665:  /* xop_maskcmpv2di3 */
    case 1664:  /* xop_maskcmpv4si3 */
    case 1663:  /* xop_maskcmpv8hi3 */
    case 1662:  /* xop_maskcmpv16qi3 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (pat, 1));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (pat, 1), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (pat, 1), 1));
      break;

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
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      recog_data.dup_loc[0] = &XEXP (XEXP (XEXP (pat, 1), 1), 1);
      recog_data.dup_num[0] = 2;
      recog_data.dup_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 2), 0);
      recog_data.dup_num[1] = 1;
      recog_data.dup_loc[2] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 2), 1), 0);
      recog_data.dup_num[2] = 2;
      break;

    case 1633:  /* xop_pperm_pack_v8hi_v16qi */
    case 1632:  /* xop_pperm_pack_v4si_v8hi */
    case 1631:  /* xop_pperm_pack_v2di_v4si */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (pat, 0, 1), 0));
      break;

    case 1620:  /* xop_phaddubq */
    case 1619:  /* xop_phaddbq */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0), 0), 0));
      recog_data.dup_loc[0] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 1), 0), 0);
      recog_data.dup_num[0] = 1;
      recog_data.dup_loc[1] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 1), 0), 0), 0);
      recog_data.dup_num[1] = 1;
      recog_data.dup_loc[2] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 1), 1), 0), 0);
      recog_data.dup_num[2] = 1;
      recog_data.dup_loc[3] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 0), 0), 0), 0);
      recog_data.dup_num[3] = 1;
      recog_data.dup_loc[4] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 0), 1), 0), 0);
      recog_data.dup_num[4] = 1;
      recog_data.dup_loc[5] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 1), 0), 0), 0);
      recog_data.dup_num[5] = 1;
      recog_data.dup_loc[6] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 1), 1), 0), 0);
      recog_data.dup_num[6] = 1;
      break;

    case 1624:  /* xop_phadduwq */
    case 1623:  /* xop_phaddwq */
    case 1618:  /* xop_phaddubd */
    case 1617:  /* xop_phaddbd */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0), 0));
      recog_data.dup_loc[0] = &XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 1), 0), 0);
      recog_data.dup_num[0] = 1;
      recog_data.dup_loc[1] = &XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 0), 0), 0);
      recog_data.dup_num[1] = 1;
      recog_data.dup_loc[2] = &XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 1), 0), 0);
      recog_data.dup_num[2] = 1;
      break;

    case 1629:  /* xop_phsubdq */
    case 1628:  /* xop_phsubwd */
    case 1627:  /* xop_phsubbw */
    case 1626:  /* xop_phaddudq */
    case 1625:  /* xop_phadddq */
    case 1622:  /* xop_phadduwd */
    case 1621:  /* xop_phaddwd */
    case 1616:  /* xop_phaddubw */
    case 1615:  /* xop_phaddbw */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0));
      recog_data.dup_loc[0] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 0), 0);
      recog_data.dup_num[0] = 1;
      break;

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
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 1), 1));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (pat, 1), 2));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (pat, 1), 0));
      break;

    case 1602:  /* xop_pmadcsswd */
    case 1601:  /* xop_pmadcswd */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 1), 0), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (pat, 1), 1));
      recog_data.dup_loc[0] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 1), 0), 0), 0);
      recog_data.dup_num[0] = 1;
      recog_data.dup_loc[1] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 1), 1), 0), 0);
      recog_data.dup_num[1] = 2;
      break;

    case 1600:  /* xop_pmacsswd */
    case 1599:  /* xop_pmacswd */
    case 1598:  /* xop_pmacssdqh */
    case 1597:  /* xop_pmacsdqh */
    case 1596:  /* xop_pmacssdql */
    case 1595:  /* xop_pmacsdql */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 1), 0), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (pat, 1), 1));
      break;

    case 1590:  /* sse4_2_pcmpistr_cconly */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 2), 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 1));
      ro[4] = *(ro_loc[4] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 2));
      break;

    case 1589:  /* sse4_2_pcmpistrm */
    case 1588:  /* sse4_2_pcmpistri */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 1));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 2));
      recog_data.dup_loc[0] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 2);
      recog_data.dup_num[0] = 3;
      recog_data.dup_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 1);
      recog_data.dup_num[1] = 2;
      recog_data.dup_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 0);
      recog_data.dup_num[2] = 1;
      break;

    case 1587:  /* *sse4_2_pcmpistr_unaligned */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      ro[3] = *(ro_loc[3] = &XVECEXP (XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 1), 0, 0));
      ro[4] = *(ro_loc[4] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 2));
      recog_data.dup_loc[0] = &XVECEXP (XEXP (XVECEXP (pat, 0, 2), 1), 0, 2);
      recog_data.dup_num[0] = 4;
      recog_data.dup_loc[1] = &XVECEXP (XVECEXP (XEXP (XVECEXP (pat, 0, 2), 1), 0, 1), 0, 0);
      recog_data.dup_num[1] = 3;
      recog_data.dup_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 2), 1), 0, 0);
      recog_data.dup_num[2] = 2;
      recog_data.dup_loc[3] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 2);
      recog_data.dup_num[3] = 4;
      recog_data.dup_loc[4] = &XVECEXP (XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 1), 0, 0);
      recog_data.dup_num[4] = 3;
      recog_data.dup_loc[5] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 0);
      recog_data.dup_num[5] = 2;
      break;

    case 1586:  /* sse4_2_pcmpistr */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 1));
      ro[4] = *(ro_loc[4] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 2));
      recog_data.dup_loc[0] = &XVECEXP (XEXP (XVECEXP (pat, 0, 2), 1), 0, 2);
      recog_data.dup_num[0] = 4;
      recog_data.dup_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 2), 1), 0, 1);
      recog_data.dup_num[1] = 3;
      recog_data.dup_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 2), 1), 0, 0);
      recog_data.dup_num[2] = 2;
      recog_data.dup_loc[3] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 2);
      recog_data.dup_num[3] = 4;
      recog_data.dup_loc[4] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 1);
      recog_data.dup_num[4] = 3;
      recog_data.dup_loc[5] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 0);
      recog_data.dup_num[5] = 2;
      break;

    case 1585:  /* sse4_2_pcmpestr_cconly */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 2), 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 1));
      ro[4] = *(ro_loc[4] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 2));
      ro[5] = *(ro_loc[5] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 3));
      ro[6] = *(ro_loc[6] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 4));
      break;

    case 1584:  /* sse4_2_pcmpestrm */
    case 1583:  /* sse4_2_pcmpestri */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 1));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 2));
      ro[4] = *(ro_loc[4] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 3));
      ro[5] = *(ro_loc[5] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 4));
      recog_data.dup_loc[0] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 4);
      recog_data.dup_num[0] = 5;
      recog_data.dup_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 3);
      recog_data.dup_num[1] = 4;
      recog_data.dup_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 2);
      recog_data.dup_num[2] = 3;
      recog_data.dup_loc[3] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 1);
      recog_data.dup_num[3] = 2;
      recog_data.dup_loc[4] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 0);
      recog_data.dup_num[4] = 1;
      break;

    case 1582:  /* *sse4_2_pcmpestr_unaligned */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 1));
      ro[4] = *(ro_loc[4] = &XVECEXP (XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 2), 0, 0));
      ro[5] = *(ro_loc[5] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 3));
      ro[6] = *(ro_loc[6] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 4));
      recog_data.dup_loc[0] = &XVECEXP (XEXP (XVECEXP (pat, 0, 2), 1), 0, 4);
      recog_data.dup_num[0] = 6;
      recog_data.dup_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 2), 1), 0, 3);
      recog_data.dup_num[1] = 5;
      recog_data.dup_loc[2] = &XVECEXP (XVECEXP (XEXP (XVECEXP (pat, 0, 2), 1), 0, 2), 0, 0);
      recog_data.dup_num[2] = 4;
      recog_data.dup_loc[3] = &XVECEXP (XEXP (XVECEXP (pat, 0, 2), 1), 0, 1);
      recog_data.dup_num[3] = 3;
      recog_data.dup_loc[4] = &XVECEXP (XEXP (XVECEXP (pat, 0, 2), 1), 0, 0);
      recog_data.dup_num[4] = 2;
      recog_data.dup_loc[5] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 4);
      recog_data.dup_num[5] = 6;
      recog_data.dup_loc[6] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 3);
      recog_data.dup_num[6] = 5;
      recog_data.dup_loc[7] = &XVECEXP (XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 2), 0, 0);
      recog_data.dup_num[7] = 4;
      recog_data.dup_loc[8] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 1);
      recog_data.dup_num[8] = 3;
      recog_data.dup_loc[9] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 0);
      recog_data.dup_num[9] = 2;
      break;

    case 1581:  /* sse4_2_pcmpestr */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 1));
      ro[4] = *(ro_loc[4] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 2));
      ro[5] = *(ro_loc[5] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 3));
      ro[6] = *(ro_loc[6] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 4));
      recog_data.dup_loc[0] = &XVECEXP (XEXP (XVECEXP (pat, 0, 2), 1), 0, 4);
      recog_data.dup_num[0] = 6;
      recog_data.dup_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 2), 1), 0, 3);
      recog_data.dup_num[1] = 5;
      recog_data.dup_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 2), 1), 0, 2);
      recog_data.dup_num[2] = 4;
      recog_data.dup_loc[3] = &XVECEXP (XEXP (XVECEXP (pat, 0, 2), 1), 0, 1);
      recog_data.dup_num[3] = 3;
      recog_data.dup_loc[4] = &XVECEXP (XEXP (XVECEXP (pat, 0, 2), 1), 0, 0);
      recog_data.dup_num[4] = 2;
      recog_data.dup_loc[5] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 4);
      recog_data.dup_num[5] = 6;
      recog_data.dup_loc[6] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 3);
      recog_data.dup_num[6] = 5;
      recog_data.dup_loc[7] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 2);
      recog_data.dup_num[7] = 4;
      recog_data.dup_loc[8] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 1);
      recog_data.dup_num[8] = 3;
      recog_data.dup_loc[9] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 0);
      recog_data.dup_num[9] = 2;
      break;

    case 1580:  /* sse4_1_roundsd */
    case 1579:  /* sse4_1_roundss */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 1), 1));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XEXP (pat, 1), 0), 0, 0));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XEXP (pat, 1), 0), 0, 1));
      break;

    case 1574:  /* sse4_1_ptest */
    case 1573:  /* avx_ptest256 */
    case 1572:  /* avx_vtestpd */
    case 1571:  /* avx_vtestpd256 */
    case 1570:  /* avx_vtestps */
    case 1569:  /* avx_vtestps256 */
      ro[0] = *(ro_loc[0] = &XVECEXP (XEXP (pat, 1), 0, 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (pat, 1), 0, 1));
      break;

    case 1543:  /* avx2_pblenddv4si */
    case 1542:  /* avx2_pblenddv8si */
    case 1541:  /* *avx2_pblendw */
    case 1540:  /* sse4_1_pblendw */
    case 1523:  /* sse4_1_blendpd */
    case 1522:  /* avx_blendpd256 */
    case 1521:  /* sse4_1_blendps */
    case 1520:  /* avx_blendps256 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 1), 1));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (pat, 1), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (pat, 1), 2));
      break;

    case 1681:  /* xop_vpermil2v2df3 */
    case 1680:  /* xop_vpermil2v4df3 */
    case 1679:  /* xop_vpermil2v4sf3 */
    case 1678:  /* xop_vpermil2v8sf3 */
    case 1518:  /* sse4a_insertqi */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (pat, 1), 0, 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (pat, 1), 0, 1));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (pat, 1), 0, 2));
      ro[4] = *(ro_loc[4] = &XVECEXP (XEXP (pat, 1), 0, 3));
      break;

    case 1487:  /* *ssse3_pmulhrswv4hi3 */
    case 1486:  /* *ssse3_pmulhrswv8hi3 */
    case 1485:  /* *avx2_pmulhrswv16hi3 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0), 0), 1), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 1));
      break;

    case 1477:  /* avx2_phsubdv8si3 */
    case 1476:  /* avx2_phadddv8si3 */
    case 1471:  /* ssse3_phsubswv8hi3 */
    case 1470:  /* ssse3_phsubwv8hi3 */
    case 1469:  /* ssse3_phaddswv8hi3 */
    case 1468:  /* ssse3_phaddwv8hi3 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 0), 0), 0), 0));
      recog_data.dup_loc[0] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0), 1), 0);
      recog_data.dup_num[0] = 1;
      recog_data.dup_loc[1] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 1), 0), 0);
      recog_data.dup_num[1] = 1;
      recog_data.dup_loc[2] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 1), 1), 0);
      recog_data.dup_num[2] = 1;
      recog_data.dup_loc[3] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 1), 0), 0), 0);
      recog_data.dup_num[3] = 1;
      recog_data.dup_loc[4] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 1), 0), 1), 0);
      recog_data.dup_num[4] = 1;
      recog_data.dup_loc[5] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 1), 1), 0), 0);
      recog_data.dup_num[5] = 1;
      recog_data.dup_loc[6] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 1), 1), 1), 0);
      recog_data.dup_num[6] = 1;
      recog_data.dup_loc[7] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 0), 0), 1), 0);
      recog_data.dup_num[7] = 2;
      recog_data.dup_loc[8] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 0), 1), 0), 0);
      recog_data.dup_num[8] = 2;
      recog_data.dup_loc[9] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 0), 1), 1), 0);
      recog_data.dup_num[9] = 2;
      recog_data.dup_loc[10] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 1), 0), 0), 0);
      recog_data.dup_num[10] = 2;
      recog_data.dup_loc[11] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 1), 0), 1), 0);
      recog_data.dup_num[11] = 2;
      recog_data.dup_loc[12] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 1), 1), 0), 0);
      recog_data.dup_num[12] = 2;
      recog_data.dup_loc[13] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 1), 1), 1), 0);
      recog_data.dup_num[13] = 2;
      break;

    case 1467:  /* avx2_phsubswv16hi3 */
    case 1466:  /* avx2_phsubwv16hi3 */
    case 1465:  /* avx2_phaddswv16hi3 */
    case 1464:  /* avx2_phaddwv16hi3 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 0), 0), 0), 0), 0));
      recog_data.dup_loc[0] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0), 0), 1), 0);
      recog_data.dup_num[0] = 1;
      recog_data.dup_loc[1] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0), 1), 0), 0);
      recog_data.dup_num[1] = 1;
      recog_data.dup_loc[2] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0), 1), 1), 0);
      recog_data.dup_num[2] = 1;
      recog_data.dup_loc[3] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 1), 0), 0), 0);
      recog_data.dup_num[3] = 1;
      recog_data.dup_loc[4] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 1), 0), 1), 0);
      recog_data.dup_num[4] = 1;
      recog_data.dup_loc[5] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 1), 1), 0), 0);
      recog_data.dup_num[5] = 1;
      recog_data.dup_loc[6] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 1), 1), 1), 0);
      recog_data.dup_num[6] = 1;
      recog_data.dup_loc[7] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 1), 0), 0), 0), 0);
      recog_data.dup_num[7] = 1;
      recog_data.dup_loc[8] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 1), 0), 0), 1), 0);
      recog_data.dup_num[8] = 1;
      recog_data.dup_loc[9] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 1), 0), 1), 0), 0);
      recog_data.dup_num[9] = 1;
      recog_data.dup_loc[10] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 1), 0), 1), 1), 0);
      recog_data.dup_num[10] = 1;
      recog_data.dup_loc[11] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 1), 1), 0), 0), 0);
      recog_data.dup_num[11] = 1;
      recog_data.dup_loc[12] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 1), 1), 0), 1), 0);
      recog_data.dup_num[12] = 1;
      recog_data.dup_loc[13] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 1), 1), 1), 0), 0);
      recog_data.dup_num[13] = 1;
      recog_data.dup_loc[14] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 1), 1), 1), 1), 0);
      recog_data.dup_num[14] = 1;
      recog_data.dup_loc[15] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 0), 0), 0), 1), 0);
      recog_data.dup_num[15] = 2;
      recog_data.dup_loc[16] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 0), 0), 1), 0), 0);
      recog_data.dup_num[16] = 2;
      recog_data.dup_loc[17] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 0), 0), 1), 1), 0);
      recog_data.dup_num[17] = 2;
      recog_data.dup_loc[18] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 0), 1), 0), 0), 0);
      recog_data.dup_num[18] = 2;
      recog_data.dup_loc[19] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 0), 1), 0), 1), 0);
      recog_data.dup_num[19] = 2;
      recog_data.dup_loc[20] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 0), 1), 1), 0), 0);
      recog_data.dup_num[20] = 2;
      recog_data.dup_loc[21] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 0), 1), 1), 1), 0);
      recog_data.dup_num[21] = 2;
      recog_data.dup_loc[22] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 1), 0), 0), 0), 0);
      recog_data.dup_num[22] = 2;
      recog_data.dup_loc[23] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 1), 0), 0), 1), 0);
      recog_data.dup_num[23] = 2;
      recog_data.dup_loc[24] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 1), 0), 1), 0), 0);
      recog_data.dup_num[24] = 2;
      recog_data.dup_loc[25] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 1), 0), 1), 1), 0);
      recog_data.dup_num[25] = 2;
      recog_data.dup_loc[26] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 1), 1), 0), 0), 0);
      recog_data.dup_num[26] = 2;
      recog_data.dup_loc[27] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 1), 1), 0), 1), 0);
      recog_data.dup_num[27] = 2;
      recog_data.dup_loc[28] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 1), 1), 1), 0), 0);
      recog_data.dup_num[28] = 2;
      recog_data.dup_loc[29] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 1), 1), 1), 1), 0);
      recog_data.dup_num[29] = 2;
      break;

    case 1448:  /* *sse2_uavgv8hi3 */
    case 1447:  /* *avx2_uavgv16hi3 */
    case 1446:  /* *sse2_uavgv16qi3 */
    case 1445:  /* *avx2_uavgv32qi3 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0), 1), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 1));
      break;

    case 1432:  /* sse2_pshufhw_1 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 1), 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 4));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 5));
      ro[4] = *(ro_loc[4] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 6));
      ro[5] = *(ro_loc[5] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 7));
      break;

    case 1431:  /* avx2_pshufhw_1 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 1), 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 4));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 5));
      ro[4] = *(ro_loc[4] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 6));
      ro[5] = *(ro_loc[5] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 7));
      ro[6] = *(ro_loc[6] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 12));
      ro[7] = *(ro_loc[7] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 13));
      ro[8] = *(ro_loc[8] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 14));
      ro[9] = *(ro_loc[9] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 15));
      break;

    case 1429:  /* avx2_pshuflw_1 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 1), 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 0));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 1));
      ro[4] = *(ro_loc[4] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 2));
      ro[5] = *(ro_loc[5] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 3));
      ro[6] = *(ro_loc[6] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 8));
      ro[7] = *(ro_loc[7] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 9));
      ro[8] = *(ro_loc[8] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 10));
      ro[9] = *(ro_loc[9] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 11));
      break;

    case 1427:  /* avx2_pshufd_1 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 1), 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 0));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 1));
      ro[4] = *(ro_loc[4] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 2));
      ro[5] = *(ro_loc[5] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 3));
      ro[6] = *(ro_loc[6] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 4));
      ro[7] = *(ro_loc[7] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 5));
      ro[8] = *(ro_loc[8] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 6));
      ro[9] = *(ro_loc[9] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 7));
      break;

    case 1252:  /* sse2_shufpd_v2df */
    case 1251:  /* sse2_shufpd_v2di */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (pat, 1), 0), 1));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 0));
      ro[4] = *(ro_loc[4] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 1));
      break;

    case 1435:  /* *vec_ext_v4si_mem */
    case 1426:  /* *sse4_1_pextrd */
    case 1425:  /* *sse4_1_pextrw_memory */
    case 1423:  /* *sse4_1_pextrb_memory */
    case 1229:  /* *vec_extract_v4sf_mem */
    case 1228:  /* *sse4_1_extractps */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 1), 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 0));
      break;

    case 1226:  /* sse4_1_insertps */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (pat, 1), 0, 1));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (pat, 1), 0, 0));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (pat, 1), 0, 2));
      break;

    case 1433:  /* sse2_loadld */
    case 1224:  /* vec_setv4sf_0 */
    case 1223:  /* vec_setv4si_0 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 1), 1));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      break;

    case 1259:  /* sse2_movsd */
    case 1215:  /* sse_movss */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 1), 1));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (pat, 1), 0));
      break;

    case 1752:  /* vec_set_lo_v32qi */
    case 1750:  /* vec_set_lo_v16hi */
    case 1747:  /* vec_set_lo_v8sf */
    case 1746:  /* vec_set_lo_v8si */
    case 1743:  /* vec_set_lo_v4df */
    case 1742:  /* vec_set_lo_v4di */
    case 1740:  /* avx2_vec_set_lo_v4di */
    case 1258:  /* sse2_loadlpd */
    case 1214:  /* sse_loadlps */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (pat, 1), 0));
      break;

    case 1246:  /* avx_shufpd256_1 */
    case 1210:  /* sse_shufps_v4sf */
    case 1209:  /* sse_shufps_v4si */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (pat, 1), 0), 1));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 0));
      ro[4] = *(ro_loc[4] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 1));
      ro[5] = *(ro_loc[5] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 2));
      ro[6] = *(ro_loc[6] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 3));
      break;

    case 1208:  /* avx_shufps256_1 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (pat, 1), 0), 1));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 0));
      ro[4] = *(ro_loc[4] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 1));
      ro[5] = *(ro_loc[5] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 2));
      ro[6] = *(ro_loc[6] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 3));
      ro[7] = *(ro_loc[7] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 4));
      ro[8] = *(ro_loc[8] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 5));
      ro[9] = *(ro_loc[9] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 6));
      ro[10] = *(ro_loc[10] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 7));
      break;

    case 1207:  /* sse3_movsldup */
    case 1206:  /* avx_movsldup256 */
    case 1205:  /* sse3_movshdup */
    case 1204:  /* avx_movshdup256 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      recog_data.dup_loc[0] = &XEXP (XEXP (XEXP (pat, 1), 0), 1);
      recog_data.dup_num[0] = 1;
      break;

    case 1789:  /* vcvtph2ps */
    case 1163:  /* sse_cvtps2pi */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (XEXP (pat, 1), 0), 0, 0));
      break;

    case 1192:  /* sse2_cvtss2sd */
    case 1191:  /* sse2_cvtsd2ss */
    case 1178:  /* sse2_cvtsi2sd */
    case 1165:  /* sse_cvtsi2ss */
    case 1162:  /* sse_cvtpi2ps */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 1), 1));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0));
      break;

    case 1161:  /* *fma4i_vmfnmsub_v2df */
    case 1160:  /* *fma4i_vmfnmsub_v4sf */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (pat, 1), 0), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 2), 0));
      ro[4] = *(ro_loc[4] = &XEXP (XEXP (pat, 1), 1));
      break;

    case 1159:  /* *fma4i_vmfnmadd_v2df */
    case 1158:  /* *fma4i_vmfnmadd_v4sf */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (pat, 1), 0), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XEXP (pat, 1), 0), 2));
      ro[4] = *(ro_loc[4] = &XEXP (XEXP (pat, 1), 1));
      break;

    case 1157:  /* *fma4i_vmfmsub_v2df */
    case 1156:  /* *fma4i_vmfmsub_v4sf */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (pat, 1), 0), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 2), 0));
      ro[4] = *(ro_loc[4] = &XEXP (XEXP (pat, 1), 1));
      break;

    case 1155:  /* *fma4i_vmfmadd_v2df */
    case 1154:  /* *fma4i_vmfmadd_v4sf */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (pat, 1), 0), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XEXP (pat, 1), 0), 2));
      ro[4] = *(ro_loc[4] = &XEXP (XEXP (pat, 1), 1));
      break;

    case 1153:  /* *fmai_fnmsub_v2df */
    case 1152:  /* *fmai_fnmsub_v4sf */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 0), 1));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 2), 0));
      recog_data.dup_loc[0] = &XEXP (XEXP (pat, 1), 1);
      recog_data.dup_num[0] = 1;
      break;

    case 1151:  /* *fmai_fnmadd_v2df */
    case 1150:  /* *fmai_fnmadd_v4sf */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 0), 1));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XEXP (pat, 1), 0), 2));
      recog_data.dup_loc[0] = &XEXP (XEXP (pat, 1), 1);
      recog_data.dup_num[0] = 1;
      break;

    case 1149:  /* *fmai_fmsub_v2df */
    case 1148:  /* *fmai_fmsub_v4sf */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (pat, 1), 0), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 2), 0));
      recog_data.dup_loc[0] = &XEXP (XEXP (pat, 1), 1);
      recog_data.dup_num[0] = 1;
      break;

    case 1147:  /* *fmai_fmadd_v2df */
    case 1146:  /* *fmai_fmadd_v4sf */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (pat, 1), 0), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XEXP (pat, 1), 0), 2));
      recog_data.dup_loc[0] = &XEXP (XEXP (pat, 1), 1);
      recog_data.dup_num[0] = 1;
      break;

    case 1145:  /* *fma_fmsubadd_v2df */
    case 1144:  /* *fma_fmsubadd_v4df */
    case 1143:  /* *fma_fmsubadd_v4sf */
    case 1142:  /* *fma_fmsubadd_v8sf */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (pat, 1), 0, 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (pat, 1), 0, 1));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (XEXP (pat, 1), 0, 2), 0));
      break;

    case 1137:  /* *fma_fnmsub_v4df */
    case 1136:  /* *fma_fnmsub_v8sf */
    case 1135:  /* *fma_fnmsub_v2df */
    case 1134:  /* *fma_fnmsub_v4sf */
    case 1133:  /* *fma_fnmsub_df */
    case 1132:  /* *fma_fnmsub_sf */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (pat, 1), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XEXP (pat, 1), 2), 0));
      break;

    case 1131:  /* *fma_fnmadd_v4df */
    case 1130:  /* *fma_fnmadd_v8sf */
    case 1129:  /* *fma_fnmadd_v2df */
    case 1128:  /* *fma_fnmadd_v4sf */
    case 1127:  /* *fma_fnmadd_df */
    case 1126:  /* *fma_fnmadd_sf */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (pat, 1), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (pat, 1), 2));
      break;

    case 1125:  /* *fma_fmsub_v4df */
    case 1124:  /* *fma_fmsub_v8sf */
    case 1123:  /* *fma_fmsub_v2df */
    case 1122:  /* *fma_fmsub_v4sf */
    case 1121:  /* *fma_fmsub_df */
    case 1120:  /* *fma_fmsub_sf */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (pat, 1), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XEXP (pat, 1), 2), 0));
      break;

    case 1085:  /* sse2_ucomi */
    case 1084:  /* sse_ucomi */
    case 1083:  /* sse2_comi */
    case 1082:  /* sse_comi */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 1), 0));
      break;

    case 1081:  /* sse2_vmmaskcmpv2df3 */
    case 1080:  /* sse_vmmaskcmpv4sf3 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (pat, 1), 0), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (pat, 1), 0));
      recog_data.dup_loc[0] = &XEXP (XEXP (pat, 1), 1);
      recog_data.dup_num[0] = 1;
      break;

    case 1071:  /* avx_vmcmpv2df3 */
    case 1070:  /* avx_vmcmpv4sf3 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (XEXP (pat, 1), 0), 0, 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XEXP (pat, 1), 0), 0, 1));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XEXP (pat, 1), 0), 0, 2));
      recog_data.dup_loc[0] = &XEXP (XEXP (pat, 1), 1);
      recog_data.dup_num[0] = 1;
      break;

    case 1479:  /* ssse3_phsubdv4si3 */
    case 1478:  /* ssse3_phadddv4si3 */
    case 1475:  /* ssse3_phsubswv4hi3 */
    case 1474:  /* ssse3_phsubwv4hi3 */
    case 1473:  /* ssse3_phaddswv4hi3 */
    case 1472:  /* ssse3_phaddwv4hi3 */
    case 1065:  /* sse3_hsubv4sf3 */
    case 1064:  /* sse3_haddv4sf3 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 0), 0), 0));
      recog_data.dup_loc[0] = &XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 1), 0);
      recog_data.dup_num[0] = 1;
      recog_data.dup_loc[1] = &XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 1), 0), 0);
      recog_data.dup_num[1] = 1;
      recog_data.dup_loc[2] = &XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 1), 1), 0);
      recog_data.dup_num[2] = 1;
      recog_data.dup_loc[3] = &XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 0), 1), 0);
      recog_data.dup_num[3] = 2;
      recog_data.dup_loc[4] = &XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 1), 0), 0);
      recog_data.dup_num[4] = 2;
      recog_data.dup_loc[5] = &XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 1), 1), 0);
      recog_data.dup_num[5] = 2;
      break;

    case 1063:  /* avx_hsubv8sf3 */
    case 1062:  /* avx_haddv8sf3 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 1), 0), 0), 0));
      recog_data.dup_loc[0] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0), 1), 0);
      recog_data.dup_num[0] = 1;
      recog_data.dup_loc[1] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 1), 0), 0);
      recog_data.dup_num[1] = 1;
      recog_data.dup_loc[2] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 1), 1), 0);
      recog_data.dup_num[2] = 1;
      recog_data.dup_loc[3] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 1), 0), 1), 0);
      recog_data.dup_num[3] = 2;
      recog_data.dup_loc[4] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 1), 1), 0), 0);
      recog_data.dup_num[4] = 2;
      recog_data.dup_loc[5] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 1), 1), 1), 0);
      recog_data.dup_num[5] = 2;
      recog_data.dup_loc[6] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 0), 0), 0), 0);
      recog_data.dup_num[6] = 1;
      recog_data.dup_loc[7] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 0), 0), 1), 0);
      recog_data.dup_num[7] = 1;
      recog_data.dup_loc[8] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 0), 1), 0), 0);
      recog_data.dup_num[8] = 1;
      recog_data.dup_loc[9] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 0), 1), 1), 0);
      recog_data.dup_num[9] = 1;
      recog_data.dup_loc[10] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 1), 0), 0), 0);
      recog_data.dup_num[10] = 2;
      recog_data.dup_loc[11] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 1), 0), 1), 0);
      recog_data.dup_num[11] = 2;
      recog_data.dup_loc[12] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 1), 1), 0), 0);
      recog_data.dup_num[12] = 2;
      recog_data.dup_loc[13] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 1), 1), 1), 0);
      recog_data.dup_num[13] = 2;
      break;

    case 1061:  /* *sse3_hsubv2df3_low */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      recog_data.dup_loc[0] = &XEXP (XEXP (XEXP (pat, 1), 1), 0);
      recog_data.dup_num[0] = 1;
      break;

    case 1060:  /* *sse3_haddv2df3_low */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XEXP (XEXP (pat, 1), 0), 1), 0, 0));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XEXP (XEXP (pat, 1), 1), 1), 0, 0));
      recog_data.dup_loc[0] = &XEXP (XEXP (XEXP (pat, 1), 1), 0);
      recog_data.dup_num[0] = 1;
      break;

    case 1058:  /* *sse3_haddv2df3 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 0), 0));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 1), 0, 0));
      ro[4] = *(ro_loc[4] = &XVECEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 1), 1), 0, 0));
      ro[5] = *(ro_loc[5] = &XVECEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 0), 1), 0, 0));
      ro[6] = *(ro_loc[6] = &XVECEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 1), 1), 0, 0));
      recog_data.dup_loc[0] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 1), 0);
      recog_data.dup_num[0] = 1;
      recog_data.dup_loc[1] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 1), 0);
      recog_data.dup_num[1] = 2;
      break;

    case 1057:  /* avx_hsubv4df3 */
    case 1056:  /* avx_haddv4df3 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 1), 0), 0));
      recog_data.dup_loc[0] = &XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 1), 0);
      recog_data.dup_num[0] = 1;
      recog_data.dup_loc[1] = &XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 1), 1), 0);
      recog_data.dup_num[1] = 2;
      recog_data.dup_loc[2] = &XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 0), 0), 0);
      recog_data.dup_num[2] = 1;
      recog_data.dup_loc[3] = &XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 0), 1), 0);
      recog_data.dup_num[3] = 1;
      recog_data.dup_loc[4] = &XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 1), 0), 0);
      recog_data.dup_num[4] = 2;
      recog_data.dup_loc[5] = &XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 1), 1), 0);
      recog_data.dup_num[5] = 2;
      break;

    case 1661:  /* *xop_vmfrcz_v2df */
    case 1660:  /* *xop_vmfrcz_v4sf */
    case 1187:  /* *sse2_cvtpd2dq */
    case 1186:  /* *avx_cvtpd2dq256_2 */
    case 1023:  /* sse_vmrsqrtv4sf2 */
    case 1014:  /* sse_vmrcpv4sf2 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (XEXP (pat, 1), 0), 0, 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (pat, 1), 1));
      break;

    case 1043:  /* sse2_vmsminv2df3 */
    case 1042:  /* sse2_vmsmaxv2df3 */
    case 1041:  /* sse_vmsminv4sf3 */
    case 1040:  /* sse_vmsmaxv4sf3 */
    case 1011:  /* sse2_vmdivv2df3 */
    case 1010:  /* sse_vmdivv4sf3 */
    case 1005:  /* sse2_vmmulv2df3 */
    case 1004:  /* sse_vmmulv4sf3 */
    case 999:  /* sse2_vmsubv2df3 */
    case 998:  /* sse2_vmaddv2df3 */
    case 997:  /* sse_vmsubv4sf3 */
    case 996:  /* sse_vmaddv4sf3 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (pat, 1), 0), 1));
      recog_data.dup_loc[0] = &XEXP (XEXP (pat, 1), 1);
      recog_data.dup_num[0] = 1;
      break;

    case 1689:  /* *avx_vzeroall */
    case 946:  /* *mmx_femms */
    case 945:  /* *mmx_emms */
      ro[0] = *(ro_loc[0] = &PATTERN (insn));
      break;

    case 1458:  /* *sse2_maskmovdqu */
    case 1457:  /* *sse2_maskmovdqu */
    case 944:  /* *mmx_maskmovq */
    case 943:  /* *mmx_maskmovq */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (pat, 0), 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (pat, 1), 0, 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (pat, 1), 0, 1));
      recog_data.dup_loc[0] = &XEXP (XVECEXP (XEXP (pat, 1), 0, 2), 0);
      recog_data.dup_num[0] = 0;
      break;

    case 1706:  /* avx2_permv4df_1 */
    case 1705:  /* avx2_permv4di_1 */
    case 1430:  /* sse2_pshuflw_1 */
    case 1428:  /* sse2_pshufd_1 */
    case 932:  /* mmx_pshufw_1 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 1), 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 0));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 1));
      ro[4] = *(ro_loc[4] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 2));
      ro[5] = *(ro_loc[5] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 3));
      break;

    case 1424:  /* *sse2_pextrw_si */
    case 1422:  /* *sse4_1_pextrb_si */
    case 931:  /* mmx_pextrw */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XEXP (XEXP (pat, 1), 0), 1), 0, 0));
      break;

    case 1421:  /* sse4_1_pinsrq */
    case 1420:  /* sse4_1_pinsrd */
    case 1419:  /* sse2_pinsrw */
    case 1418:  /* sse4_1_pinsrb */
    case 1225:  /* *vec_setv4sf_sse4_1 */
    case 930:  /* *mmx_pinsrw */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 1), 1));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (pat, 1), 2));
      break;

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
    case 1250:  /* vec_interleave_lowv2di */
    case 1249:  /* avx2_interleave_lowv4di */
    case 1248:  /* vec_interleave_highv2di */
    case 1247:  /* avx2_interleave_highv4di */
    case 1245:  /* *vec_interleave_lowv2df */
    case 1244:  /* *avx_unpcklpd256 */
    case 1243:  /* *vec_interleave_highv2df */
    case 1242:  /* avx_unpckhpd256 */
    case 1203:  /* vec_interleave_lowv4sf */
    case 1202:  /* avx_unpcklps256 */
    case 1201:  /* vec_interleave_highv4sf */
    case 1200:  /* avx_unpckhps256 */
    case 1199:  /* sse_movlhps */
    case 1198:  /* sse_movhlps */
    case 929:  /* mmx_punpckldq */
    case 928:  /* mmx_punpckhdq */
    case 927:  /* mmx_punpcklwd */
    case 926:  /* mmx_punpckhwd */
    case 925:  /* mmx_punpcklbw */
    case 924:  /* mmx_punpckhbw */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (pat, 1), 0), 1));
      break;

    case 1537:  /* sse4_1_packusdw */
    case 1536:  /* avx2_packusdw */
    case 1405:  /* sse2_packuswb */
    case 1404:  /* avx2_packuswb */
    case 1403:  /* sse2_packssdw */
    case 1402:  /* avx2_packssdw */
    case 1401:  /* sse2_packsswb */
    case 1400:  /* avx2_packsswb */
    case 923:  /* mmx_packuswb */
    case 922:  /* mmx_packssdw */
    case 921:  /* mmx_packsswb */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (pat, 1), 1), 0));
      break;

    case 1303:  /* *sse4_1_mulv2siv2di3 */
    case 1302:  /* *vec_widen_smult_even_v8si */
    case 1301:  /* *vec_widen_umult_even_v4si */
    case 1300:  /* *vec_widen_umult_even_v8si */
    case 890:  /* *sse2_umulv1siv1di3 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 0), 0));
      break;

    case 940:  /* *mmx_uavgv4hi3 */
    case 939:  /* *mmx_uavgv8qi3 */
    case 889:  /* *mmx_pmulhrwv4hi3 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0), 1), 0));
      break;

    case 1484:  /* ssse3_pmaddubsw */
    case 1483:  /* ssse3_pmaddubsw128 */
    case 1482:  /* avx2_pmaddubsw256 */
    case 1305:  /* *sse2_pmaddwd */
    case 1304:  /* *avx2_pmaddwd */
    case 888:  /* *mmx_pmaddwd */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 1), 0), 0));
      recog_data.dup_loc[0] = &XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 0), 0), 0);
      recog_data.dup_num[0] = 1;
      recog_data.dup_loc[1] = &XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 1), 0), 0);
      recog_data.dup_num[1] = 2;
      break;

    case 1299:  /* *umulv8hi3_highpart */
    case 1298:  /* *smulv8hi3_highpart */
    case 1297:  /* *umulv16hi3_highpart */
    case 1296:  /* *smulv16hi3_highpart */
    case 887:  /* *mmx_umulv4hi3_highpart */
    case 886:  /* *mmx_smulv4hi3_highpart */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 1), 0));
      break;

    case 862:  /* mmx_pi2fw */
    case 861:  /* mmx_pf2iw */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0));
      break;

    case 1055:  /* sse3_addsubv4sf3 */
    case 1054:  /* avx_addsubv8sf3 */
    case 1053:  /* sse3_addsubv2df3 */
    case 1052:  /* avx_addsubv4df3 */
    case 856:  /* mmx_addsubv2sf3 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (pat, 1), 0), 1));
      recog_data.dup_loc[0] = &XEXP (XEXP (XEXP (pat, 1), 1), 0);
      recog_data.dup_num[0] = 1;
      recog_data.dup_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 1), 1);
      recog_data.dup_num[1] = 2;
      break;

    case 1481:  /* ssse3_phsubdv2si3 */
    case 1480:  /* ssse3_phadddv2si3 */
    case 1059:  /* sse3_hsubv2df3 */
    case 855:  /* mmx_hsubv2sf3 */
    case 854:  /* mmx_haddv2sf3 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 0), 0));
      recog_data.dup_loc[0] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 1), 0);
      recog_data.dup_num[0] = 1;
      recog_data.dup_loc[1] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 1), 0);
      recog_data.dup_num[1] = 2;
      break;

    case 832:  /* xbegin_1 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1), 0));
      recog_data.dup_loc[0] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 0);
      recog_data.dup_num[0] = 0;
      break;

    case 826:  /* *lwp_lwpinssi3_1 */
      ro[0] = *(ro_loc[0] = &XVECEXP (XEXP (pat, 1), 0, 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (pat, 1), 0, 1));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (pat, 1), 0, 2));
      break;

    case 1463:  /* sse3_monitor */
    case 825:  /* *lwp_lwpvalsi3_1 */
      ro[0] = *(ro_loc[0] = &XVECEXP (pat, 0, 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (pat, 0, 1));
      ro[2] = *(ro_loc[2] = &XVECEXP (pat, 0, 2));
      break;

    case 1462:  /* sse3_mwait */
    case 820:  /* xrstor */
      ro[0] = *(ro_loc[0] = &XVECEXP (pat, 0, 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (pat, 0, 1));
      break;

    case 815:  /* rdtscp */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 1), 0));
      break;

    case 800:  /* *prefetch_sse */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (pat, 2));
      break;

    case 796:  /* adjust_stack_and_probedi */
    case 795:  /* adjust_stack_and_probesi */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 1));
      break;

    case 1119:  /* *fma_fmadd_v4df */
    case 1118:  /* *fma_fmadd_v8sf */
    case 1117:  /* *fma_fmadd_v2df */
    case 1116:  /* *fma_fmadd_v4sf */
    case 1115:  /* *fma_fmadd_df */
    case 1114:  /* *fma_fmadd_sf */
    case 780:  /* *xop_pcmov_df */
    case 779:  /* *xop_pcmov_sf */
    case 778:  /* *movsfcc_1_387 */
    case 777:  /* *movdfcc_1 */
    case 776:  /* *movxfcc_1 */
    case 775:  /* *movqicc_noc */
    case 774:  /* *movsicc_noc */
    case 773:  /* *movhicc_noc */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (pat, 1), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (pat, 1), 2));
      break;

    case 769:  /* *strlenqi_1 */
    case 768:  /* *strlenqi_1 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 1));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 2));
      ro[4] = *(ro_loc[4] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 3));
      ro[5] = *(ro_loc[5] = &XEXP (XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0), 0));
      break;

    case 767:  /* *cmpstrnqi_1 */
    case 766:  /* *cmpstrnqi_1 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 3), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 4), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XVECEXP (pat, 0, 5), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[4] = *(ro_loc[4] = &XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1), 0), 0));
      ro[5] = *(ro_loc[5] = &XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1), 1), 0));
      ro[6] = *(ro_loc[6] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0));
      break;

    case 765:  /* *cmpstrnqi_nz_1 */
    case 764:  /* *cmpstrnqi_nz_1 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 3), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 4), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XVECEXP (pat, 0, 5), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (pat, 0, 2), 0));
      ro[4] = *(ro_loc[4] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0));
      ro[5] = *(ro_loc[5] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1), 0));
      ro[6] = *(ro_loc[6] = &XEXP (XVECEXP (pat, 0, 1), 0));
      break;

    case 763:  /* *rep_stosqi */
    case 762:  /* *rep_stosqi */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XVECEXP (pat, 0, 3), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0));
      ro[4] = *(ro_loc[4] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 1));
      recog_data.dup_loc[0] = &XEXP (XVECEXP (pat, 0, 4), 0);
      recog_data.dup_num[0] = 4;
      recog_data.dup_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 2), 0), 0);
      recog_data.dup_num[1] = 3;
      break;

    case 761:  /* *rep_stossi */
    case 760:  /* *rep_stossi */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XVECEXP (pat, 0, 3), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 1));
      ro[4] = *(ro_loc[4] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0), 0));
      recog_data.dup_loc[0] = &XEXP (XVECEXP (pat, 0, 4), 0);
      recog_data.dup_num[0] = 4;
      recog_data.dup_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 2), 0), 0);
      recog_data.dup_num[1] = 3;
      break;

    case 759:  /* *strsetqi_1 */
    case 758:  /* *strsetqi_1 */
    case 757:  /* *strsethi_1 */
    case 756:  /* *strsethi_1 */
    case 755:  /* *strsetsi_1 */
    case 754:  /* *strsetsi_1 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XVECEXP (pat, 0, 0), 1));
      recog_data.dup_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0);
      recog_data.dup_num[0] = 1;
      break;

    case 753:  /* *rep_movqi */
    case 752:  /* *rep_movqi */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 2), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0));
      ro[4] = *(ro_loc[4] = &XEXP (XEXP (XVECEXP (pat, 0, 2), 1), 0));
      ro[5] = *(ro_loc[5] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 1));
      recog_data.dup_loc[0] = &XEXP (XVECEXP (pat, 0, 4), 0);
      recog_data.dup_num[0] = 5;
      recog_data.dup_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 3), 0), 0);
      recog_data.dup_num[1] = 3;
      recog_data.dup_loc[2] = &XEXP (XEXP (XVECEXP (pat, 0, 3), 1), 0);
      recog_data.dup_num[2] = 4;
      recog_data.dup_loc[3] = &XEXP (XEXP (XVECEXP (pat, 0, 2), 1), 1);
      recog_data.dup_num[3] = 5;
      break;

    case 751:  /* *rep_movsi */
    case 750:  /* *rep_movsi */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 2), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 1));
      ro[4] = *(ro_loc[4] = &XEXP (XEXP (XVECEXP (pat, 0, 2), 1), 1));
      ro[5] = *(ro_loc[5] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0), 0));
      recog_data.dup_loc[0] = &XEXP (XVECEXP (pat, 0, 4), 0);
      recog_data.dup_num[0] = 5;
      recog_data.dup_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 3), 0), 0);
      recog_data.dup_num[1] = 3;
      recog_data.dup_loc[2] = &XEXP (XEXP (XVECEXP (pat, 0, 3), 1), 0);
      recog_data.dup_num[2] = 4;
      recog_data.dup_loc[3] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 2), 1), 0), 0);
      recog_data.dup_num[3] = 5;
      break;

    case 749:  /* *strmovqi_1 */
    case 748:  /* *strmovqi_1 */
    case 747:  /* *strmovhi_1 */
    case 746:  /* *strmovhi_1 */
    case 745:  /* *strmovsi_1 */
    case 744:  /* *strmovsi_1 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 2), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 0), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      recog_data.dup_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 2), 1), 0);
      recog_data.dup_num[0] = 3;
      recog_data.dup_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0);
      recog_data.dup_num[1] = 2;
      break;

    case 728:  /* fistdi2_ceil_with_temp */
    case 727:  /* fistdi2_floor_with_temp */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      ro[2] = *(ro_loc[2] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (pat, 0, 2), 0));
      ro[4] = *(ro_loc[4] = &XEXP (XVECEXP (pat, 0, 3), 0));
      ro[5] = *(ro_loc[5] = &XEXP (XVECEXP (pat, 0, 4), 0));
      break;

    case 736:  /* fistsi2_ceil_with_temp */
    case 735:  /* fistsi2_floor_with_temp */
    case 734:  /* fisthi2_ceil_with_temp */
    case 733:  /* fisthi2_floor_with_temp */
    case 726:  /* fistdi2_ceil */
    case 725:  /* fistdi2_floor */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      ro[2] = *(ro_loc[2] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (pat, 0, 2), 0));
      ro[4] = *(ro_loc[4] = &XEXP (XVECEXP (pat, 0, 3), 0));
      break;

    case 794:  /* allocate_stack_worker_probe_di */
    case 793:  /* allocate_stack_worker_probe_si */
    case 724:  /* *fistdi2_ceil_1 */
    case 723:  /* *fistdi2_floor_1 */
    case 722:  /* *fistsi2_ceil_1 */
    case 721:  /* *fistsi2_floor_1 */
    case 720:  /* *fisthi2_ceil_1 */
    case 719:  /* *fisthi2_floor_1 */
    case 717:  /* frndintxf2_mask_pm */
    case 713:  /* frndintxf2_trunc */
    case 712:  /* frndintxf2_ceil */
    case 711:  /* frndintxf2_floor */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      break;

    case 1875:  /* atomic_storedi_fpu */
    case 1871:  /* atomic_loaddi_fpu */
    case 732:  /* fistsi2_ceil */
    case 731:  /* fistsi2_floor */
    case 730:  /* fisthi2_ceil */
    case 729:  /* fisthi2_floor */
    case 718:  /* frndintxf2_mask_pm_i387 */
    case 716:  /* frndintxf2_trunc_i387 */
    case 715:  /* frndintxf2_ceil_i387 */
    case 714:  /* frndintxf2_floor_i387 */
    case 704:  /* fistdi2_with_temp */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      ro[2] = *(ro_loc[2] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (pat, 0, 2), 0));
      break;

    case 805:  /* stack_tls_protect_set_di */
    case 804:  /* stack_tls_protect_set_si */
    case 803:  /* stack_protect_set_di */
    case 802:  /* stack_protect_set_si */
    case 710:  /* fistsi2_with_temp */
    case 709:  /* fisthi2_with_temp */
    case 703:  /* fistdi2 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      ro[2] = *(ro_loc[2] = &XEXP (XVECEXP (pat, 0, 1), 0));
      break;

    case 698:  /* *fscalexf4_i387 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 1));
      recog_data.dup_loc[0] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 1);
      recog_data.dup_num[0] = 3;
      recog_data.dup_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 0);
      recog_data.dup_num[1] = 2;
      break;

    case 693:  /* fyl2xp1_extenddfxf3_i387 */
    case 692:  /* fyl2xp1_extendsfxf3_i387 */
    case 690:  /* fyl2x_extenddfxf3_i387 */
    case 689:  /* fyl2x_extendsfxf3_i387 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0), 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 1));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (pat, 0, 1), 0));
      break;

    case 687:  /* fpatan_extenddfxf3_i387 */
    case 686:  /* fpatan_extendsfxf3_i387 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 1), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (pat, 0, 1), 0));
      break;

    case 809:  /* stack_tls_protect_test_di */
    case 808:  /* stack_tls_protect_test_si */
    case 807:  /* stack_protect_test_di */
    case 806:  /* stack_protect_test_si */
    case 691:  /* fyl2xp1xf3_i387 */
    case 688:  /* fyl2xxf3_i387 */
    case 685:  /* *fpatanxf3_i387 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 1));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (pat, 0, 1), 0));
      break;

    case 684:  /* fptan_extenddfxf4_i387 */
    case 683:  /* fptan_extendsfxf4_i387 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 0), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (pat, 0, 0), 1));
      break;

    case 682:  /* fptanxf4_i387 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 0));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (pat, 0, 0), 1));
      break;

    case 696:  /* fxtract_extenddfxf3_i387 */
    case 695:  /* fxtract_extendsfxf3_i387 */
    case 681:  /* sincos_extenddfxf3_i387 */
    case 680:  /* sincos_extendsfxf3_i387 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0), 0));
      recog_data.dup_loc[0] = &XEXP (XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 0), 0);
      recog_data.dup_num[0] = 2;
      break;

    case 694:  /* fxtractxf3_i387 */
    case 679:  /* sincosxf3 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      recog_data.dup_loc[0] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 0);
      recog_data.dup_num[0] = 2;
      break;

    case 672:  /* fprem1xf4_i387 */
    case 671:  /* fpremxf4_i387 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 1));
      recog_data.dup_loc[0] = &XVECEXP (XEXP (XVECEXP (pat, 0, 2), 1), 0, 1);
      recog_data.dup_num[0] = 3;
      recog_data.dup_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 2), 1), 0, 0);
      recog_data.dup_num[1] = 2;
      recog_data.dup_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 1);
      recog_data.dup_num[2] = 3;
      recog_data.dup_loc[3] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 0);
      recog_data.dup_num[3] = 2;
      break;

    case 662:  /* *fop_xf_6_i387 */
    case 661:  /* *fop_xf_6_i387 */
    case 650:  /* *fop_df_6_i387 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (pat, 1), 1), 0));
      ro[3] = *(ro_loc[3] = &XEXP (pat, 1));
      break;

    case 660:  /* *fop_xf_5_i387 */
    case 659:  /* *fop_xf_5_i387 */
    case 656:  /* *fop_xf_3_i387 */
    case 655:  /* *fop_xf_3_i387 */
    case 649:  /* *fop_df_5_i387 */
    case 647:  /* *fop_df_3_i387 */
    case 646:  /* *fop_sf_3_i387 */
    case 645:  /* *fop_df_3_i387 */
    case 644:  /* *fop_sf_3_i387 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (pat, 1), 1), 0));
      ro[3] = *(ro_loc[3] = &XEXP (pat, 1));
      break;

    case 658:  /* *fop_xf_4_i387 */
    case 657:  /* *fop_xf_4_i387 */
    case 654:  /* *fop_xf_2_i387 */
    case 653:  /* *fop_xf_2_i387 */
    case 648:  /* *fop_df_4_i387 */
    case 643:  /* *fop_df_2_i387 */
    case 642:  /* *fop_sf_2_i387 */
    case 641:  /* *fop_df_2_i387 */
    case 640:  /* *fop_sf_2_i387 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (pat, 1), 1));
      ro[3] = *(ro_loc[3] = &XEXP (pat, 1));
      break;

    case 1877:  /* storedi_via_fpu */
    case 1876:  /* loaddi_via_fpu */
    case 1791:  /* vcvtph2ps256 */
    case 1790:  /* *vcvtph2ps_load */
    case 1772:  /* avx_pd256_pd */
    case 1771:  /* avx_ps256_ps */
    case 1770:  /* avx_si256_si */
    case 1686:  /* aesimc */
    case 1659:  /* xop_frczv4df2 */
    case 1658:  /* xop_frczv8sf2 */
    case 1657:  /* xop_frczv2df2 */
    case 1656:  /* xop_frczv4sf2 */
    case 1655:  /* xop_frczdf2 */
    case 1654:  /* xop_frczsf2 */
    case 1544:  /* sse4_1_phminposuw */
    case 1533:  /* sse4_1_movntdqa */
    case 1532:  /* avx2_movntdqa */
    case 1513:  /* sse4a_movntdf */
    case 1512:  /* sse4a_movntsf */
    case 1456:  /* sse2_pmovmskb */
    case 1455:  /* avx2_pmovmskb */
    case 1454:  /* sse2_movmskpd */
    case 1453:  /* avx_movmskpd256 */
    case 1452:  /* sse_movmskps */
    case 1451:  /* avx_movmskps256 */
    case 1185:  /* avx_cvtpd2dq256 */
    case 1180:  /* sse2_cvtsd2si_2 */
    case 1176:  /* sse2_cvtpd2pi */
    case 1172:  /* sse2_cvtps2dq */
    case 1171:  /* avx_cvtps2dq256 */
    case 1167:  /* sse_cvtss2si_2 */
    case 1022:  /* sse_rsqrtv4sf2 */
    case 1021:  /* avx_rsqrtv8sf2 */
    case 1013:  /* sse_rcpv4sf2 */
    case 1012:  /* avx_rcpv8sf2 */
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
    case 942:  /* mmx_pmovmskb */
    case 852:  /* mmx_rsqrtv2sf2 */
    case 849:  /* mmx_rcpv2sf2 */
    case 841:  /* sse_movntq */
    case 819:  /* xsaveopt */
    case 818:  /* xsave */
    case 813:  /* rdpmc */
    case 742:  /* movmsk_df */
    case 741:  /* fxamdf2_i387_with_temp */
    case 740:  /* fxamsf2_i387_with_temp */
    case 739:  /* fxamxf2_i387 */
    case 738:  /* fxamdf2_i387 */
    case 737:  /* fxamsf2_i387 */
    case 708:  /* fistsi2 */
    case 707:  /* fisthi2 */
    case 706:  /* *fistsi2_1 */
    case 705:  /* *fisthi2_1 */
    case 702:  /* *fistdi2_1 */
    case 701:  /* rintxf2 */
    case 697:  /* *f2xm1xf2_i387 */
    case 674:  /* *cosxf2_i387 */
    case 673:  /* *sinxf2_i387 */
    case 668:  /* *rsqrtsf2_sse */
    case 664:  /* truncxfdf2_i387_noop_unspec */
    case 663:  /* truncxfsf2_i387_noop_unspec */
    case 635:  /* *rcpsf2_sse */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (pat, 1), 0, 0));
      break;

    case 626:  /* *tls_dynamic_gnu2_combine_32 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1), 0), 0, 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0, 2));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0, 0));
      ro[4] = *(ro_loc[4] = &XVECEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0, 1));
      break;

    case 625:  /* *tls_dynamic_gnu2_call_32 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 1));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 2));
      break;

    case 624:  /* *tls_dynamic_gnu2_lea_32 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 1), 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XEXP (XEXP (pat, 1), 1), 0), 0, 0));
      break;

    case 621:  /* *add_tp_x32_zext */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 1));
      break;

    case 623:  /* *add_tp_di */
    case 622:  /* *add_tp_si */
    case 620:  /* *add_tp_x32 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1));
      break;

    case 615:  /* *tls_local_dynamic_32_once */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0, 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0, 1));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1), 0), 0, 0));
      ro[4] = *(ro_loc[4] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[5] = *(ro_loc[5] = &XEXP (XVECEXP (pat, 0, 2), 0));
      break;

    case 614:  /* *tls_local_dynamic_base_32_gnu */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 1));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[4] = *(ro_loc[4] = &XEXP (XVECEXP (pat, 0, 2), 0));
      break;

    case 613:  /* *tls_global_dynamic_32_gnu */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 1));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 2));
      ro[4] = *(ro_loc[4] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[5] = *(ro_loc[5] = &XEXP (XVECEXP (pat, 0, 2), 0));
      break;

    case 612:  /* *parityhi2_cmp */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      break;

    case 611:  /* paritysi2_cmp */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 2), 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      break;

    case 610:  /* paritydi2_cmp */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 2), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XVECEXP (pat, 0, 3), 0));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      break;

    case 609:  /* bswaphi_lowpart */
    case 608:  /* *bswaphi_lowpart_1 */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 0), 0));
      recog_data.dup_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0);
      recog_data.dup_num[0] = 0;
      break;

    case 600:  /* *bsrhi */
    case 599:  /* bsr */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1), 0));
      break;

    case 598:  /* *tbm_tzmsk_si */
    case 597:  /* *tbm_t1mskc_si */
    case 596:  /* *tbm_blsic_si */
    case 592:  /* *tbm_blcic_si */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0));
      recog_data.dup_loc[0] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1), 0);
      recog_data.dup_num[0] = 1;
      break;

    case 591:  /* *tbm_blci_si */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0), 0));
      recog_data.dup_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1);
      recog_data.dup_num[0] = 1;
      break;

    case 589:  /* tbm_bextri_si */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 2));
      break;

    case 1874:  /* atomic_storesi_1 */
    case 1873:  /* atomic_storehi_1 */
    case 1872:  /* atomic_storeqi_1 */
    case 1794:  /* vcvtps2ph256 */
    case 1793:  /* *vcvtps2ph_store */
    case 1733:  /* avx_vpermilvarv2df3 */
    case 1732:  /* avx_vpermilvarv4df3 */
    case 1731:  /* avx_vpermilvarv4sf3 */
    case 1730:  /* avx_vpermilvarv8sf3 */
    case 1704:  /* avx2_permvarv8sf */
    case 1703:  /* avx2_permvarv8si */
    case 1687:  /* aeskeygenassist */
    case 1685:  /* aesdeclast */
    case 1684:  /* aesdec */
    case 1683:  /* aesenclast */
    case 1682:  /* aesenc */
    case 1578:  /* sse4_1_roundpd */
    case 1577:  /* avx_roundpd256 */
    case 1576:  /* sse4_1_roundps */
    case 1575:  /* avx_roundps256 */
    case 1519:  /* sse4a_insertq */
    case 1517:  /* sse4a_extrq */
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
    case 1450:  /* sse2_psadbw */
    case 1449:  /* avx2_psadbw */
    case 1051:  /* *ieee_smaxv2df3 */
    case 1050:  /* *ieee_smaxv4df3 */
    case 1049:  /* *ieee_smaxv4sf3 */
    case 1048:  /* *ieee_smaxv8sf3 */
    case 1047:  /* *ieee_sminv2df3 */
    case 1046:  /* *ieee_sminv4df3 */
    case 1045:  /* *ieee_sminv4sf3 */
    case 1044:  /* *ieee_sminv8sf3 */
    case 941:  /* mmx_psadbw */
    case 853:  /* mmx_rsqit1v2sf3 */
    case 851:  /* mmx_rcpit2v2sf3 */
    case 850:  /* mmx_rcpit1v2sf3 */
    case 812:  /* sse4_2_crc32si */
    case 811:  /* sse4_2_crc32hi */
    case 810:  /* sse4_2_crc32qi */
    case 788:  /* *ieee_smindf3 */
    case 787:  /* *ieee_smaxdf3 */
    case 786:  /* *ieee_sminsf3 */
    case 785:  /* *ieee_smaxsf3 */
    case 700:  /* sse4_1_rounddf2 */
    case 699:  /* sse4_1_roundsf2 */
    case 588:  /* bmi2_pext_si3 */
    case 587:  /* bmi2_pdep_si3 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (pat, 1), 0, 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (pat, 1), 0, 1));
      break;

    case 586:  /* bmi2_bzhi_si3 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1), 1));
      break;

    case 595:  /* *tbm_blsfill_si */
    case 594:  /* *tbm_blcs_si */
    case 593:  /* *tbm_blcmsk_si */
    case 590:  /* *tbm_blcfill_si */
    case 585:  /* *bmi_blsr_si */
    case 584:  /* *bmi_blsmsk_si */
    case 583:  /* *bmi_blsi_si */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0));
      recog_data.dup_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1);
      recog_data.dup_num[0] = 1;
      break;

    case 798:  /* probe_stack_rangedi */
    case 797:  /* probe_stack_rangesi */
    case 582:  /* bmi_bextr_si */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 1));
      break;

    case 581:  /* *bmi_andn_si */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1));
      break;

    case 576:  /* *bsfsi_1 */
    case 575:  /* *tzcntsi_1 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      recog_data.dup_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0);
      recog_data.dup_num[0] = 1;
      break;

    case 1515:  /* sse4a_vmmovntv2df */
    case 1514:  /* sse4a_vmmovntv4sf */
    case 1179:  /* sse2_cvtsd2si */
    case 1166:  /* sse_cvtss2si */
    case 678:  /* *cos_extenddfxf2_i387 */
    case 677:  /* *sin_extenddfxf2_i387 */
    case 676:  /* *cos_extendsfxf2_i387 */
    case 675:  /* *sin_extendsfxf2_i387 */
    case 570:  /* set_got_offset_rex64 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (XEXP (pat, 1), 0, 0), 0));
      break;

    case 569:  /* set_got_labelled */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0), 0));
      break;

    case 830:  /* rdseedsi_1 */
    case 829:  /* rdseedhi_1 */
    case 828:  /* rdrandsi_1 */
    case 827:  /* rdrandhi_1 */
    case 568:  /* set_got */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      break;

    case 564:  /* simple_return_indirect_internal */
    case 563:  /* simple_return_pop_internal */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0));
      break;

    case 1461:  /* sse2_clflush */
    case 1459:  /* sse_ldmxcsr */
    case 834:  /* xabort */
    case 822:  /* *lwp_llwpcbdi1 */
    case 821:  /* *lwp_llwpcbsi1 */
    case 817:  /* fxrstor */
    case 573:  /* split_stack_return */
    case 567:  /* pad */
    case 566:  /* nops */
    case 560:  /* prologue_use */
      ro[0] = *(ro_loc[0] = &XVECEXP (pat, 0, 0));
      break;

    case 1869:  /* mfence_sse2 */
    case 1868:  /* *sse_sfence */
    case 1867:  /* *sse2_lfence */
    case 831:  /* *pause */
    case 559:  /* *memory_blockage */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      recog_data.dup_loc[0] = &XVECEXP (XEXP (pat, 1), 0, 0);
      recog_data.dup_num[0] = 0;
      break;

    case 1690:  /* avx_vzeroupper */
    case 835:  /* xtest_1 */
    case 833:  /* xend */
    case 799:  /* trap */
    case 743:  /* cld */
    case 572:  /* leave */
    case 571:  /* eh_return_internal */
    case 565:  /* nop */
    case 562:  /* simple_return_internal_long */
    case 561:  /* simple_return_internal */
    case 558:  /* blockage */
      break;

    case 557:  /* *sibcall_value_pop */
    case 556:  /* *call_value_pop */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 1));
      break;

    case 1753:  /* vec_set_hi_v32qi */
    case 1751:  /* vec_set_hi_v16hi */
    case 1749:  /* vec_set_hi_v8sf */
    case 1748:  /* vec_set_hi_v8si */
    case 1745:  /* vec_set_hi_v4df */
    case 1744:  /* vec_set_hi_v4di */
    case 1741:  /* avx2_vec_set_hi_v4di */
    case 1375:  /* *andnotv2di3 */
    case 1374:  /* *andnotv4di3 */
    case 1373:  /* *andnotv4si3 */
    case 1372:  /* *andnotv8si3 */
    case 1371:  /* *andnotv8hi3 */
    case 1370:  /* *andnotv16hi3 */
    case 1369:  /* *andnotv16qi3 */
    case 1368:  /* *andnotv32qi3 */
    case 1257:  /* sse2_loadhpd */
    case 1212:  /* sse_loadhps */
    case 1194:  /* *sse2_cvtpd2ps */
    case 1190:  /* *sse2_cvttpd2dq */
    case 1189:  /* *avx_cvttpd2dq256_2 */
    case 1104:  /* *andnottf3 */
    case 1103:  /* *andnotdf3 */
    case 1102:  /* *andnotsf3 */
    case 1089:  /* sse2_andnotv2df3 */
    case 1088:  /* avx_andnotv4df3 */
    case 1087:  /* sse_andnotv4sf3 */
    case 1086:  /* avx_andnotv8sf3 */
    case 1020:  /* sse2_vmsqrtv2df2 */
    case 1019:  /* sse_vmsqrtv4sf2 */
    case 911:  /* mmx_andnotv2si3 */
    case 910:  /* mmx_andnotv4hi3 */
    case 909:  /* mmx_andnotv8qi3 */
    case 555:  /* *sibcall_value */
    case 554:  /* *sibcall_value */
    case 553:  /* *call_value */
    case 552:  /* *call_value */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (pat, 1), 1));
      break;

    case 551:  /* *sibcall_pop */
    case 550:  /* *call_pop */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 0), 1));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 1));
      break;

    case 545:  /* *tablejump_1 */
    case 544:  /* *tablejump_1 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 1));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 0), 0));
      break;

    case 543:  /* *indirect_jump */
    case 542:  /* *indirect_jump */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 1));
      break;

    case 541:  /* jump */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (pat, 1), 0));
      break;

    case 540:  /* *jccxf_si_r_i387 */
    case 539:  /* *jccdf_si_r_i387 */
    case 538:  /* *jccsf_si_r_i387 */
    case 537:  /* *jccxf_hi_r_i387 */
    case 536:  /* *jccdf_hi_r_i387 */
    case 535:  /* *jccsf_hi_r_i387 */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 1));
      ro[4] = *(ro_loc[4] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 2), 0));
      ro[5] = *(ro_loc[5] = &XEXP (XVECEXP (pat, 0, 3), 0));
      break;

    case 534:  /* *jccxf_si_i387 */
    case 533:  /* *jccdf_si_i387 */
    case 532:  /* *jccsf_si_i387 */
    case 531:  /* *jccxf_hi_i387 */
    case 530:  /* *jccdf_hi_i387 */
    case 529:  /* *jccsf_hi_i387 */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 1));
      ro[4] = *(ro_loc[4] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1), 0));
      ro[5] = *(ro_loc[5] = &XEXP (XVECEXP (pat, 0, 3), 0));
      break;

    case 528:  /* *jccuxf_r_i387 */
    case 527:  /* *jccudf_r_i387 */
    case 526:  /* *jccusf_r_i387 */
    case 522:  /* *jccdf_r_i387 */
    case 521:  /* *jccsf_r_i387 */
    case 518:  /* *jccxf_r_i387 */
    case 516:  /* *jccxf_0_r_i387 */
    case 515:  /* *jccdf_0_r_i387 */
    case 514:  /* *jccsf_0_r_i387 */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 2), 0));
      ro[4] = *(ro_loc[4] = &XEXP (XVECEXP (pat, 0, 3), 0));
      break;

    case 525:  /* *jccuxf_i387 */
    case 524:  /* *jccudf_i387 */
    case 523:  /* *jccusf_i387 */
    case 520:  /* *jccdf_i387 */
    case 519:  /* *jccsf_i387 */
    case 517:  /* *jccxf_i387 */
    case 513:  /* *jccxf_0_i387 */
    case 512:  /* *jccdf_0_i387 */
    case 511:  /* *jccsf_0_i387 */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1), 0));
      ro[4] = *(ro_loc[4] = &XEXP (XVECEXP (pat, 0, 3), 0));
      break;

    case 510:  /* *jcc_btsi_mask_1 */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0), 0), 1), 0), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0), 0), 1), 0), 1));
      ro[4] = *(ro_loc[4] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1), 0));
      break;

    case 509:  /* *jcc_btsi_1 */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0), 0), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1), 0));
      break;

    case 508:  /* *jcc_btdi_mask */
    case 507:  /* *jcc_btsi_mask */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0), 2), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0), 2), 1));
      ro[4] = *(ro_loc[4] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1), 0));
      break;

    case 506:  /* *jcc_btdi */
    case 505:  /* *jcc_btsi */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0), 2), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1), 0));
      break;

    case 504:  /* *jcc_2 */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XEXP (pat, 1), 2), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 1), 0));
      break;

    case 503:  /* *jcc_1 */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XEXP (pat, 1), 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 1), 0));
      break;

    case 1079:  /* sse2_maskcmpv2df3 */
    case 1078:  /* avx_maskcmpv4df3 */
    case 1077:  /* sse_maskcmpv4sf3 */
    case 1076:  /* avx_maskcmpv8sf3 */
    case 1075:  /* *sse2_maskcmpv2df3_comm */
    case 1074:  /* *avx_maskcmpv4df3_comm */
    case 1073:  /* *sse_maskcmpv4sf3_comm */
    case 1072:  /* *avx_maskcmpv8sf3_comm */
    case 652:  /* *fop_xf_1_i387 */
    case 651:  /* *fop_xf_comm_i387 */
    case 639:  /* *fop_df_1_i387 */
    case 638:  /* *fop_sf_1_i387 */
    case 637:  /* *fop_df_1_sse */
    case 636:  /* *fop_sf_1_sse */
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
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (pat, 1), 1));
      ro[3] = *(ro_loc[3] = &XEXP (pat, 1));
      break;

    case 496:  /* *btdi */
    case 495:  /* *btsi */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 0), 2));
      break;

    case 483:  /* ix86_rotrdi3_doubleword */
    case 482:  /* ix86_rotldi3_doubleword */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (pat, 0, 2), 0));
      break;

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
    case 1641:  /* xop_rotrv2di3 */
    case 1640:  /* xop_rotrv4si3 */
    case 1639:  /* xop_rotrv8hi3 */
    case 1638:  /* xop_rotrv16qi3 */
    case 1637:  /* xop_rotlv2di3 */
    case 1636:  /* xop_rotlv4si3 */
    case 1635:  /* xop_rotlv8hi3 */
    case 1634:  /* xop_rotlv16qi3 */
    case 1444:  /* vec_concatv2di */
    case 1443:  /* *vec_concatv4si */
    case 1442:  /* *vec_concatv2si_sse */
    case 1441:  /* *vec_concatv2si_sse2 */
    case 1440:  /* *vec_concatv2si_sse4_1 */
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
    case 1222:  /* *vec_concatv4sf */
    case 1221:  /* *vec_concatv2sf_sse */
    case 1220:  /* *vec_concatv2sf_sse4_1 */
    case 1113:  /* *xortf3 */
    case 1112:  /* *iortf3 */
    case 1111:  /* *andtf3 */
    case 1110:  /* *xordf3 */
    case 1109:  /* *iordf3 */
    case 1108:  /* *anddf3 */
    case 1107:  /* *xorsf3 */
    case 1106:  /* *iorsf3 */
    case 1105:  /* *andsf3 */
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
    case 1009:  /* sse2_divv2df3 */
    case 1008:  /* avx_divv4df3 */
    case 1007:  /* sse_divv4sf3 */
    case 1006:  /* avx_divv8sf3 */
    case 1003:  /* *mulv2df3 */
    case 1002:  /* *mulv4df3 */
    case 1001:  /* *mulv4sf3 */
    case 1000:  /* *mulv8sf3 */
    case 995:  /* *subv2df3 */
    case 994:  /* *addv2df3 */
    case 993:  /* *subv4df3 */
    case 992:  /* *addv4df3 */
    case 991:  /* *subv4sf3 */
    case 990:  /* *addv4sf3 */
    case 989:  /* *subv8sf3 */
    case 988:  /* *addv8sf3 */
    case 936:  /* *mmx_concatv2si */
    case 920:  /* *mmx_xorv2si3 */
    case 919:  /* *mmx_iorv2si3 */
    case 918:  /* *mmx_andv2si3 */
    case 917:  /* *mmx_xorv4hi3 */
    case 916:  /* *mmx_iorv4hi3 */
    case 915:  /* *mmx_andv4hi3 */
    case 914:  /* *mmx_xorv8qi3 */
    case 913:  /* *mmx_iorv8qi3 */
    case 912:  /* *mmx_andv8qi3 */
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
    case 859:  /* mmx_gev2sf3 */
    case 858:  /* mmx_gtv2sf3 */
    case 857:  /* *mmx_eqv2sf3 */
    case 848:  /* *mmx_sminv2sf3 */
    case 847:  /* *mmx_smaxv2sf3 */
    case 846:  /* *mmx_sminv2sf3_finite */
    case 845:  /* *mmx_smaxv2sf3_finite */
    case 844:  /* *mmx_mulv2sf3 */
    case 843:  /* *mmx_subv2sf3 */
    case 842:  /* *mmx_addv2sf3 */
    case 784:  /* smindf3 */
    case 783:  /* smaxdf3 */
    case 782:  /* sminsf3 */
    case 781:  /* smaxsf3 */
    case 484:  /* *bmi2_rorxsi3_1 */
    case 451:  /* *bmi2_ashrsi3_1 */
    case 450:  /* *bmi2_lshrsi3_1 */
    case 428:  /* *bmi2_ashlsi3_1 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (pat, 1), 1));
      break;

    case 481:  /* *rotrdi3_mask */
    case 480:  /* *rotldi3_mask */
    case 479:  /* *rotrsi3_mask */
    case 478:  /* *rotlsi3_mask */
    case 445:  /* *ashrdi3_mask */
    case 444:  /* *lshrdi3_mask */
    case 443:  /* *ashrsi3_mask */
    case 442:  /* *lshrsi3_mask */
    case 427:  /* *ashldi3_mask */
    case 426:  /* *ashlsi3_mask */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1), 0), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1), 0), 1));
      break;

    case 448:  /* x86_shrd */
    case 425:  /* x86_shld */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 1));
      recog_data.dup_loc[0] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0);
      recog_data.dup_num[0] = 0;
      recog_data.dup_loc[1] = &XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1), 1), 1);
      recog_data.dup_num[1] = 2;
      break;

    case 415:  /* copysigntf3_var */
    case 414:  /* copysigndf3_var */
    case 413:  /* copysignsf3_var */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 1));
      ro[4] = *(ro_loc[4] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 2));
      ro[5] = *(ro_loc[5] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 3));
      break;

    case 1736:  /* *avx_vperm2f128v4df_full */
    case 1735:  /* *avx_vperm2f128v8sf_full */
    case 1734:  /* *avx_vperm2f128v8si_full */
    case 1707:  /* avx2_permv2ti */
    case 1688:  /* pclmulqdq */
    case 1677:  /* xop_pcom_tfv2di3 */
    case 1676:  /* xop_pcom_tfv4si3 */
    case 1675:  /* xop_pcom_tfv8hi3 */
    case 1674:  /* xop_pcom_tfv16qi3 */
    case 1630:  /* xop_pperm */
    case 1539:  /* sse4_1_pblendvb */
    case 1538:  /* avx2_pblendvb */
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
    case 1516:  /* sse4a_extrqi */
    case 1502:  /* ssse3_palignrdi */
    case 1501:  /* ssse3_palignrti */
    case 1500:  /* avx2_palignrv2ti */
    case 1141:  /* *fma_fmaddsub_v2df */
    case 1140:  /* *fma_fmaddsub_v4df */
    case 1139:  /* *fma_fmaddsub_v4sf */
    case 1138:  /* *fma_fmaddsub_v8sf */
    case 1069:  /* avx_cmpv2df3 */
    case 1068:  /* avx_cmpv4df3 */
    case 1067:  /* avx_cmpv4sf3 */
    case 1066:  /* avx_cmpv8sf3 */
    case 412:  /* copysigntf3_const */
    case 411:  /* copysigndf3_const */
    case 410:  /* copysignsf3_const */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (pat, 1), 0, 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (pat, 1), 0, 1));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (pat, 1), 0, 2));
      break;

    case 987:  /* *absnegv2df2 */
    case 986:  /* *absnegv4df2 */
    case 985:  /* *absnegv4sf2 */
    case 984:  /* *absnegv8sf2 */
    case 397:  /* *absnegtf2_sse */
    case 396:  /* *absnegxf2_i387 */
    case 395:  /* *absnegdf2_i387 */
    case 394:  /* *absnegsf2_i387 */
    case 393:  /* *absnegdf2_sse */
    case 392:  /* *absnegsf2_sse */
    case 391:  /* *absnegdf2_mixed */
    case 390:  /* *absnegsf2_mixed */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (pat, 0, 0), 1));
      break;

    case 605:  /* *popcountdi2_cmp */
    case 604:  /* *popcountsi2_cmp */
    case 603:  /* *popcounthi2_cmp */
    case 423:  /* *one_cmpldi2_2 */
    case 422:  /* *one_cmplsi2_2 */
    case 421:  /* *one_cmplhi2_2 */
    case 420:  /* *one_cmplqi2_2 */
    case 389:  /* *negdi2_cmpz */
    case 388:  /* *negsi2_cmpz */
    case 387:  /* *neghi2_cmpz */
    case 386:  /* *negqi2_cmpz */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0));
      recog_data.dup_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0);
      recog_data.dup_num[0] = 1;
      break;

    case 379:  /* *xorqi_cc_ext_1 */
    case 342:  /* *andqi_ext_0_cc */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 1));
      recog_data.dup_loc[0] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0), 0);
      recog_data.dup_num[0] = 1;
      recog_data.dup_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 1);
      recog_data.dup_num[1] = 2;
      break;

    case 364:  /* *xorqi_2_slp */
    case 363:  /* *iorqi_2_slp */
    case 340:  /* *andqi_2_slp */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 1));
      recog_data.dup_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 0), 0);
      recog_data.dup_num[0] = 0;
      recog_data.dup_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0);
      recog_data.dup_num[1] = 0;
      recog_data.dup_loc[2] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 1);
      recog_data.dup_num[2] = 1;
      break;

    case 331:  /* *testqi_ext_3 */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 0), 1));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (pat, 1), 0), 2));
      break;

    case 330:  /* *testqi_ext_2 */
    case 329:  /* *testqi_ext_1 */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 1), 0));
      break;

    case 328:  /* *testqi_ext_0 */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 0), 1));
      break;

    case 323:  /* udivmodhiqi3 */
    case 317:  /* divmodhiqi3 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0), 0), 0), 1), 0));
      recog_data.dup_loc[0] = &XEXP (XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1), 0), 0), 0);
      recog_data.dup_num[0] = 1;
      recog_data.dup_loc[1] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1), 0), 0), 1), 0);
      recog_data.dup_num[1] = 2;
      break;

    case 322:  /* *udivmodsi4_noext */
    case 321:  /* *udivmodhi4_noext */
    case 316:  /* *divmodsi4_noext */
    case 315:  /* *divmodhi4_noext */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1));
      ro[4] = *(ro_loc[4] = &XEXP (XVECEXP (pat, 0, 2), 0));
      recog_data.dup_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0);
      recog_data.dup_num[0] = 2;
      recog_data.dup_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 1);
      recog_data.dup_num[1] = 3;
      break;

    case 320:  /* *udivmodsi4 */
    case 319:  /* *udivmodhi4 */
    case 318:  /* udivmodsi4_1 */
    case 314:  /* *divmodsi4 */
    case 313:  /* *divmodhi4 */
    case 312:  /* divmodsi4_1 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1));
      recog_data.dup_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0);
      recog_data.dup_num[0] = 2;
      recog_data.dup_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 1);
      recog_data.dup_num[1] = 3;
      break;

    case 311:  /* *umulsi3_highpart_1 */
    case 310:  /* *smulsi3_highpart_1 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0), 1), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (pat, 0, 1), 0));
      break;

    case 309:  /* *umulqihi3_1 */
    case 308:  /* *mulqihi3_1 */
    case 307:  /* *mulsidi3_1 */
    case 306:  /* *umulsidi3_1 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1), 0));
      break;

    case 305:  /* *bmi2_umulsidi3_1 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1));
      recog_data.dup_loc[0] = &XEXP (XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0), 0), 0), 0);
      recog_data.dup_num[0] = 2;
      recog_data.dup_loc[1] = &XEXP (XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0), 0), 1), 0);
      recog_data.dup_num[1] = 3;
      break;

    case 301:  /* *subdi3_cc_overflow */
    case 300:  /* *adddi3_cc_overflow */
    case 299:  /* *subsi3_cc_overflow */
    case 298:  /* *addsi3_cc_overflow */
    case 297:  /* *subhi3_cc_overflow */
    case 296:  /* *addhi3_cc_overflow */
    case 295:  /* *subqi3_cc_overflow */
    case 294:  /* *addqi3_cc_overflow */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 1));
      recog_data.dup_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0);
      recog_data.dup_num[0] = 1;
      recog_data.dup_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 1);
      recog_data.dup_num[1] = 2;
      recog_data.dup_loc[2] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1);
      recog_data.dup_num[2] = 1;
      break;

    case 293:  /* *subsi3_cconly_overflow */
    case 292:  /* *subhi3_cconly_overflow */
    case 291:  /* *subqi3_cconly_overflow */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 0), 1));
      recog_data.dup_loc[0] = &XEXP (XEXP (pat, 1), 1);
      recog_data.dup_num[0] = 0;
      break;

    case 290:  /* *addsi3_cconly_overflow */
    case 289:  /* *addhi3_cconly_overflow */
    case 288:  /* *addqi3_cconly_overflow */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 1));
      recog_data.dup_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1);
      recog_data.dup_num[0] = 1;
      break;

    case 287:  /* adcxdi3 */
    case 286:  /* adcxsi3 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 1), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 1), 0), 0));
      ro[4] = *(ro_loc[4] = &XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 1), 0));
      recog_data.dup_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0);
      recog_data.dup_num[0] = 1;
      recog_data.dup_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 1), 0);
      recog_data.dup_num[1] = 4;
      recog_data.dup_loc[2] = &XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 1), 0), 0);
      recog_data.dup_num[2] = 3;
      recog_data.dup_loc[3] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 1), 1);
      recog_data.dup_num[3] = 2;
      break;

    case 285:  /* *subdi3_carry */
    case 284:  /* *adddi3_carry */
    case 283:  /* *subsi3_carry */
    case 282:  /* *addsi3_carry */
    case 281:  /* *subhi3_carry */
    case 280:  /* *addhi3_carry */
    case 279:  /* *subqi3_carry */
    case 278:  /* *addqi3_carry */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1), 0));
      break;

    case 277:  /* *subdi_3 */
    case 276:  /* *subsi_3 */
    case 275:  /* *subhi_3 */
    case 274:  /* *subqi_3 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1));
      recog_data.dup_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0);
      recog_data.dup_num[0] = 1;
      recog_data.dup_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 1);
      recog_data.dup_num[1] = 2;
      break;

    case 260:  /* *lea_general_3 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XEXP (pat, 1), 0), 1));
      ro[4] = *(ro_loc[4] = &XEXP (XEXP (pat, 1), 1));
      break;

    case 1594:  /* xop_pmacssdd */
    case 1593:  /* xop_pmacsdd */
    case 1592:  /* xop_pmacssww */
    case 1591:  /* xop_pmacsww */
    case 262:  /* *lea_general_4 */
    case 261:  /* *lea_general_4 */
    case 259:  /* *lea_general_2 */
    case 258:  /* *lea_general_1 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (pat, 1), 0), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (pat, 1), 1));
      break;

    case 378:  /* *xorqi_ext_2 */
    case 377:  /* *iorqi_ext_2 */
    case 376:  /* *xorqi_ext_1 */
    case 375:  /* *iorqi_ext_1 */
    case 344:  /* *andqi_ext_2 */
    case 343:  /* *andqi_ext_1 */
    case 257:  /* *addqi_ext_2 */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1), 0));
      break;

    case 374:  /* *xorqi_ext_0 */
    case 373:  /* *iorqi_ext_0 */
    case 341:  /* andqi_ext_0 */
    case 256:  /* addqi_ext_1 */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1));
      break;

    case 477:  /* *ashrdi3_cconly */
    case 476:  /* *lshrdi3_cconly */
    case 475:  /* *ashrsi3_cconly */
    case 474:  /* *lshrsi3_cconly */
    case 473:  /* *ashrhi3_cconly */
    case 472:  /* *lshrhi3_cconly */
    case 471:  /* *ashrqi3_cconly */
    case 470:  /* *lshrqi3_cconly */
    case 441:  /* *ashldi3_cconly */
    case 440:  /* *ashlsi3_cconly */
    case 439:  /* *ashlhi3_cconly */
    case 438:  /* *ashlqi3_cconly */
    case 372:  /* *xordi_3 */
    case 371:  /* *iordi_3 */
    case 370:  /* *xorsi_3 */
    case 369:  /* *iorsi_3 */
    case 368:  /* *xorhi_3 */
    case 367:  /* *iorhi_3 */
    case 366:  /* *xorqi_3 */
    case 365:  /* *iorqi_3 */
    case 255:  /* *adddi_5 */
    case 254:  /* *addsi_5 */
    case 253:  /* *addhi_5 */
    case 252:  /* *addqi_5 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 1));
      break;

    case 248:  /* *adddi_3 */
    case 247:  /* *addsi_3 */
    case 246:  /* *addhi_3 */
    case 245:  /* *addqi_3 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0));
      break;

    case 469:  /* *ashrdi3_cmp */
    case 468:  /* *lshrdi3_cmp */
    case 467:  /* *ashrsi3_cmp */
    case 466:  /* *lshrsi3_cmp */
    case 465:  /* *ashrhi3_cmp */
    case 464:  /* *lshrhi3_cmp */
    case 463:  /* *ashrqi3_cmp */
    case 462:  /* *lshrqi3_cmp */
    case 437:  /* *ashldi3_cmp */
    case 436:  /* *ashlsi3_cmp */
    case 435:  /* *ashlhi3_cmp */
    case 434:  /* *ashlqi3_cmp */
    case 362:  /* *xordi_2 */
    case 361:  /* *iordi_2 */
    case 360:  /* *xorsi_2 */
    case 359:  /* *iorsi_2 */
    case 358:  /* *xorhi_2 */
    case 357:  /* *iorhi_2 */
    case 356:  /* *xorqi_2 */
    case 355:  /* *iorqi_2 */
    case 339:  /* *andsi_2 */
    case 338:  /* *andhi_2 */
    case 337:  /* *andqi_2 */
    case 336:  /* *andqi_2_maybe_si */
    case 273:  /* *subdi_2 */
    case 272:  /* *subsi_2 */
    case 271:  /* *subhi_2 */
    case 270:  /* *subqi_2 */
    case 244:  /* *adddi_2 */
    case 243:  /* *addsi_2 */
    case 242:  /* *addhi_2 */
    case 241:  /* *addqi_2 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 1));
      recog_data.dup_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0);
      recog_data.dup_num[0] = 1;
      recog_data.dup_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 1);
      recog_data.dup_num[1] = 2;
      break;

    case 494:  /* *rotrqi3_1_slp */
    case 493:  /* *rotlqi3_1_slp */
    case 461:  /* *ashrqi3_1_slp */
    case 460:  /* *lshrqi3_1_slp */
    case 433:  /* *ashlqi3_1_slp */
    case 354:  /* *xorqi_1_slp */
    case 353:  /* *iorqi_1_slp */
    case 335:  /* *andqi_1_slp */
    case 269:  /* *subqi_1_slp */
    case 240:  /* *addqi_1_slp */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1));
      recog_data.dup_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0);
      recog_data.dup_num[0] = 0;
      break;

    case 235:  /* addqi3_cc */
    case 234:  /* *adddi3_cc */
    case 233:  /* *addsi3_cc */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 1));
      recog_data.dup_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0);
      recog_data.dup_num[0] = 1;
      recog_data.dup_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 1);
      recog_data.dup_num[1] = 2;
      break;

    case 792:  /* pro_epilogue_adjust_stack_di_sub */
    case 791:  /* pro_epilogue_adjust_stack_si_sub */
    case 790:  /* pro_epilogue_adjust_stack_di_add */
    case 789:  /* pro_epilogue_adjust_stack_si_add */
    case 492:  /* *rotrhi3_1 */
    case 491:  /* *rotlhi3_1 */
    case 490:  /* *rotrqi3_1 */
    case 489:  /* *rotlqi3_1 */
    case 488:  /* *rotrdi3_1 */
    case 487:  /* *rotldi3_1 */
    case 486:  /* *rotrsi3_1 */
    case 485:  /* *rotlsi3_1 */
    case 459:  /* *ashrhi3_1 */
    case 458:  /* *lshrhi3_1 */
    case 457:  /* *ashrqi3_1 */
    case 456:  /* *lshrqi3_1 */
    case 455:  /* *ashrdi3_1 */
    case 454:  /* *lshrdi3_1 */
    case 453:  /* *ashrsi3_1 */
    case 452:  /* *lshrsi3_1 */
    case 449:  /* ashrsi3_cvt */
    case 447:  /* *ashrdi3_doubleword */
    case 446:  /* *lshrdi3_doubleword */
    case 432:  /* *ashlqi3_1 */
    case 431:  /* *ashlhi3_1 */
    case 430:  /* *ashldi3_1 */
    case 429:  /* *ashlsi3_1 */
    case 424:  /* *ashldi3_doubleword */
    case 352:  /* *xorqi_1 */
    case 351:  /* *iorqi_1 */
    case 350:  /* *xordi_1 */
    case 349:  /* *iordi_1 */
    case 348:  /* *xorsi_1 */
    case 347:  /* *iorsi_1 */
    case 346:  /* *xorhi_1 */
    case 345:  /* *iorhi_1 */
    case 334:  /* *andqi_1 */
    case 333:  /* *andhi_1 */
    case 332:  /* *andsi_1 */
    case 304:  /* *mulqi3_1 */
    case 303:  /* *mulhi3_1 */
    case 302:  /* *mulsi3_1 */
    case 268:  /* *subdi_1 */
    case 267:  /* *subsi_1 */
    case 266:  /* *subhi_1 */
    case 265:  /* *subqi_1 */
    case 264:  /* *subti3_doubleword */
    case 263:  /* *subdi3_doubleword */
    case 239:  /* *addqi_1 */
    case 238:  /* *addhi_1 */
    case 237:  /* *adddi_1 */
    case 236:  /* *addsi_1 */
    case 232:  /* *addti3_doubleword */
    case 231:  /* *adddi3_doubleword */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1));
      break;

    case 226:  /* floatdixf2_i387_with_xmm */
    case 225:  /* floatdidf2_i387_with_xmm */
    case 224:  /* floatdisf2_i387_with_xmm */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XVECEXP (pat, 0, 3), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[4] = *(ro_loc[4] = &XEXP (XVECEXP (pat, 0, 2), 0));
      break;

    case 162:  /* fix_truncdi_i387_with_temp */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (pat, 0, 2), 0));
      ro[4] = *(ro_loc[4] = &XEXP (XVECEXP (pat, 0, 3), 0));
      ro[5] = *(ro_loc[5] = &XEXP (XVECEXP (pat, 0, 4), 0));
      break;

    case 166:  /* fix_truncsi_i387_with_temp */
    case 165:  /* fix_trunchi_i387_with_temp */
    case 161:  /* fix_truncdi_i387 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (pat, 0, 2), 0));
      ro[4] = *(ro_loc[4] = &XEXP (XVECEXP (pat, 0, 3), 0));
      break;

    case 229:  /* *floatunssixf2_1 */
    case 228:  /* *floatunssidf2_1 */
    case 227:  /* *floatunssisf2_1 */
    case 164:  /* fix_truncsi_i387 */
    case 163:  /* fix_trunchi_i387 */
    case 157:  /* fix_truncdi_i387_fisttp_with_temp */
    case 156:  /* fix_truncsi_i387_fisttp_with_temp */
    case 155:  /* fix_trunchi_i387_fisttp_with_temp */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (pat, 0, 2), 0));
      break;

    case 146:  /* *fixuns_truncdf_1 */
    case 145:  /* *fixuns_truncsf_1 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 2), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XVECEXP (pat, 0, 3), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[4] = *(ro_loc[4] = &XEXP (XVECEXP (pat, 0, 1), 0));
      break;

    case 962:  /* movdi_to_sse */
    case 574:  /* ffssi2_no_cmove */
    case 217:  /* *floatdixf2_i387_with_temp */
    case 216:  /* *floatdidf2_i387_with_temp */
    case 215:  /* *floatdisf2_i387_with_temp */
    case 214:  /* *floatsixf2_i387_with_temp */
    case 213:  /* *floatsidf2_i387_with_temp */
    case 212:  /* *floatsisf2_i387_with_temp */
    case 203:  /* *floatsidf2_sse_with_temp */
    case 202:  /* *floatsisf2_sse_with_temp */
    case 199:  /* *floatsidf2_vector_sse_with_temp */
    case 198:  /* *floatsisf2_vector_sse_with_temp */
    case 189:  /* *floatsidf2_mixed_with_temp */
    case 188:  /* *floatsisf2_mixed_with_temp */
    case 185:  /* *floatsidf2_vector_mixed_with_temp */
    case 184:  /* *floatsisf2_vector_mixed_with_temp */
    case 174:  /* *floathixf2_i387_with_temp */
    case 173:  /* *floathidf2_i387_with_temp */
    case 172:  /* *floathisf2_i387_with_temp */
    case 154:  /* fix_truncdi_i387_fisttp */
    case 153:  /* fix_truncsi_i387_fisttp */
    case 152:  /* fix_trunchi_i387_fisttp */
    case 140:  /* *truncxfdf2_mixed */
    case 139:  /* *truncxfsf2_mixed */
    case 137:  /* *truncdfsf_i387 */
    case 136:  /* *truncdfsf_mixed */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XVECEXP (pat, 0, 1), 0));
      break;

    case 124:  /* extendsidi2_1 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XVECEXP (pat, 0, 2), 0));
      break;

    case 772:  /* *x86_movsicc_0_m1_neg */
    case 771:  /* *x86_movsicc_0_m1_se */
    case 770:  /* *x86_movsicc_0_m1 */
    case 602:  /* popcountsi2 */
    case 601:  /* popcounthi2 */
    case 580:  /* clzsi2_lzcnt */
    case 579:  /* clzhi2_lzcnt */
    case 578:  /* ctzsi2 */
    case 577:  /* ctzhi2 */
    case 385:  /* *negdi2_1 */
    case 384:  /* *negsi2_1 */
    case 383:  /* *neghi2_1 */
    case 382:  /* *negqi2_1 */
    case 381:  /* *negti2_doubleword */
    case 380:  /* *negdi2_doubleword */
    case 160:  /* *fix_truncdi_i387_1 */
    case 159:  /* *fix_truncsi_i387_1 */
    case 158:  /* *fix_trunchi_i387_1 */
    case 122:  /* zero_extendqihi2_and */
    case 119:  /* zero_extendhisi2_and */
    case 118:  /* zero_extendqisi2_and */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      break;

    case 104:  /* *movqi_insv_2 */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (pat, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 1), 0));
      break;

    case 1708:  /* avx2_vec_dupv4df */
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
    case 1568:  /* sse4_1_zero_extendv2siv2di2 */
    case 1567:  /* sse4_1_sign_extendv2siv2di2 */
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
    case 1552:  /* sse4_1_zero_extendv4qiv4si2 */
    case 1551:  /* sse4_1_sign_extendv4qiv4si2 */
    case 1550:  /* avx2_zero_extendv8qiv8si2 */
    case 1549:  /* avx2_sign_extendv8qiv8si2 */
    case 1548:  /* sse4_1_zero_extendv8qiv8hi2 */
    case 1547:  /* sse4_1_sign_extendv8qiv8hi2 */
    case 1218:  /* avx2_vec_dupv8sf_1 */
    case 1217:  /* avx2_vec_dupv4sf */
    case 1216:  /* avx2_vec_dupv8sf */
    case 1197:  /* sse2_cvtps2pd */
    case 1196:  /* *avx_cvtps2pd256_2 */
    case 1184:  /* sse2_cvtdq2pd */
    case 1183:  /* avx_cvtdq2pd256_2 */
    case 1181:  /* sse2_cvttsd2si */
    case 1168:  /* sse_cvttss2si */
    case 1164:  /* sse_cvttps2pi */
    case 961:  /* sse2_movq128 */
    case 934:  /* *vec_dupv4hi */
    case 667:  /* sqrt_extenddfxf2_i387 */
    case 666:  /* sqrt_extendsfxf2_i387 */
    case 409:  /* *negextenddfxf2 */
    case 408:  /* *absextenddfxf2 */
    case 407:  /* *negextendsfxf2 */
    case 406:  /* *absextendsfxf2 */
    case 405:  /* *negextendsfdf2 */
    case 404:  /* *absextendsfdf2 */
    case 102:  /* *movqi_extzv_2 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      break;

    case 97:  /* *movstricthi_xor */
    case 96:  /* *movstrictqi_xor */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 0), 1));
      break;

    case 116:  /* *swapdf */
    case 115:  /* *swapsf */
    case 114:  /* swapxf */
    case 93:  /* *swaphi_2 */
    case 92:  /* *swapqi_2 */
    case 91:  /* *swaphi_1 */
    case 90:  /* *swapqi_1 */
    case 89:  /* swapsi */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 0), 1));
      recog_data.dup_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0);
      recog_data.dup_num[0] = 1;
      recog_data.dup_loc[1] = &XEXP (XVECEXP (pat, 0, 1), 1);
      recog_data.dup_num[1] = 0;
      break;

    case 1712:  /* vec_dupv4df */
    case 1711:  /* vec_dupv4di */
    case 1710:  /* vec_dupv8sf */
    case 1709:  /* vec_dupv8si */
    case 1566:  /* avx2_zero_extendv4siv4di2 */
    case 1565:  /* avx2_sign_extendv4siv4di2 */
    case 1554:  /* avx2_zero_extendv8hiv8si2 */
    case 1553:  /* avx2_sign_extendv8hiv8si2 */
    case 1546:  /* avx2_zero_extendv16qiv16hi2 */
    case 1545:  /* avx2_sign_extendv16qiv16hi2 */
    case 1511:  /* absv2si2 */
    case 1510:  /* absv4hi2 */
    case 1509:  /* absv8qi2 */
    case 1508:  /* absv4si2 */
    case 1507:  /* absv8si2 */
    case 1506:  /* absv8hi2 */
    case 1505:  /* absv16hi2 */
    case 1504:  /* absv16qi2 */
    case 1503:  /* absv32qi2 */
    case 1439:  /* *vec_dupv2di */
    case 1438:  /* *vec_dupv4si */
    case 1437:  /* *vec_extractv2di_1 */
    case 1436:  /* *sse2_storeq */
    case 1434:  /* sse2_stored */
    case 1260:  /* vec_dupv2df */
    case 1256:  /* *vec_extractv2df_0_sse */
    case 1255:  /* sse2_storelpd */
    case 1254:  /* *vec_extractv2df_1_sse */
    case 1253:  /* sse2_storehpd */
    case 1241:  /* vec_extract_hi_v32qi */
    case 1240:  /* vec_extract_lo_v32qi */
    case 1239:  /* vec_extract_hi_v16hi */
    case 1238:  /* vec_extract_lo_v16hi */
    case 1237:  /* vec_extract_hi_v8sf */
    case 1236:  /* vec_extract_hi_v8si */
    case 1235:  /* vec_extract_lo_v8sf */
    case 1234:  /* vec_extract_lo_v8si */
    case 1233:  /* vec_extract_hi_v4df */
    case 1232:  /* vec_extract_hi_v4di */
    case 1231:  /* vec_extract_lo_v4df */
    case 1230:  /* vec_extract_lo_v4di */
    case 1227:  /* *vec_extractv4sf_0 */
    case 1219:  /* vec_dupv4sf */
    case 1213:  /* sse_storelps */
    case 1211:  /* sse_storehps */
    case 1195:  /* avx_cvtps2pd256 */
    case 1193:  /* avx_cvtpd2ps256 */
    case 1188:  /* fix_truncv4dfv4si2 */
    case 1182:  /* floatv4siv4df2 */
    case 1177:  /* sse2_cvttpd2pi */
    case 1175:  /* sse2_cvtpi2pd */
    case 1174:  /* fix_truncv4sfv4si2 */
    case 1173:  /* fix_truncv8sfv8si2 */
    case 1170:  /* floatv4siv4sf2 */
    case 1169:  /* floatv8siv8sf2 */
    case 1018:  /* sse2_sqrtv2df2 */
    case 1017:  /* avx_sqrtv4df2 */
    case 1016:  /* sse_sqrtv4sf2 */
    case 1015:  /* avx_sqrtv8sf2 */
    case 938:  /* *vec_extractv2si_1 */
    case 937:  /* *vec_extractv2si_0 */
    case 935:  /* *vec_dupv2si */
    case 933:  /* mmx_pswapdv2si2 */
    case 868:  /* *vec_extractv2sf_1 */
    case 867:  /* *vec_extractv2sf_0 */
    case 865:  /* *vec_dupv2sf */
    case 864:  /* mmx_pswapdv2sf2 */
    case 863:  /* mmx_floatv2si2 */
    case 860:  /* mmx_pf2id */
    case 670:  /* *sqrtdf2_sse */
    case 669:  /* *sqrtsf2_sse */
    case 665:  /* sqrtxf2 */
    case 607:  /* *bswapsi2 */
    case 606:  /* *bswapsi2_movbe */
    case 419:  /* *one_cmplqi2_1 */
    case 418:  /* *one_cmpldi2_1 */
    case 417:  /* *one_cmplsi2_1 */
    case 416:  /* *one_cmplhi2_1 */
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
    case 201:  /* *floatsidf2_vector_sse */
    case 200:  /* *floatsisf2_vector_sse */
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
    case 183:  /* *floatdixf2_1 */
    case 182:  /* *floatdidf2_1 */
    case 181:  /* *floatdisf2_1 */
    case 180:  /* *floatsixf2_1 */
    case 179:  /* *floatsidf2_1 */
    case 178:  /* *floatsisf2_1 */
    case 177:  /* *floathixf2_i387 */
    case 176:  /* *floathidf2_i387 */
    case 175:  /* *floathisf2_i387 */
    case 171:  /* *floathixf2_1 */
    case 170:  /* *floathidf2_1 */
    case 169:  /* *floathisf2_1 */
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
    case 128:  /* *extendsfdf2_mixed */
    case 127:  /* extendqihi2 */
    case 126:  /* extendqisi2 */
    case 125:  /* extendhisi2 */
    case 123:  /* *zero_extendqihi2 */
    case 121:  /* *zero_extendhisi2 */
    case 120:  /* *zero_extendqisi2 */
    case 117:  /* *zero_extendsidi2 */
    case 101:  /* *movsi_extzv_1 */
    case 100:  /* *movqi_extv_1 */
    case 99:  /* *movsi_extv_1 */
    case 98:  /* *movhi_extv_1 */
    case 88:  /* *movabsdi_2 */
    case 87:  /* *movabssi_2 */
    case 86:  /* *movabshi_2 */
    case 85:  /* *movabsqi_2 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 1), 0));
      break;

    case 549:  /* *sibcall */
    case 548:  /* *sibcall */
    case 547:  /* *call */
    case 546:  /* *call */
    case 500:  /* *setcc_qi_slp */
    case 103:  /* *movsi_insv_1 */
    case 95:  /* *movstricthi_1 */
    case 94:  /* *movstrictqi_1 */
    case 84:  /* *movabsdi_1 */
    case 83:  /* *movabssi_1 */
    case 82:  /* *movabshi_1 */
    case 81:  /* *movabsqi_1 */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (pat, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (pat, 1));
      break;

    case 497:  /* *setcc_si_1_and */
    case 74:  /* *movsi_or */
    case 73:  /* *movsi_xor */
    case 72:  /* *popdi1_epilogue */
    case 71:  /* *popsi1_epilogue */
    case 68:  /* *pushdi2_prologue */
    case 67:  /* *pushsi2_prologue */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 0), 1));
      break;

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
    case 801:  /* *prefetch_3dnow */
    case 499:  /* *setcc_qi */
    case 498:  /* *setcc_si_1_movzbl */
    case 230:  /* *leasi */
    case 113:  /* *movsf_internal */
    case 112:  /* *movdf_internal */
    case 111:  /* *movxf_internal */
    case 110:  /* *movtf_internal_sse */
    case 109:  /* *pushsf */
    case 108:  /* *pushdf */
    case 107:  /* *pushxf_nointeger */
    case 106:  /* *pushxf */
    case 105:  /* *pushtf */
    case 80:  /* *movqi_internal */
    case 79:  /* *movhi_internal */
    case 78:  /* *movsi_internal */
    case 77:  /* *movdi_internal */
    case 76:  /* *movti_internal_sse */
    case 75:  /* *movoi_internal_avx */
    case 70:  /* *popdi1 */
    case 69:  /* *popsi1 */
    case 66:  /* *pushhi2 */
    case 65:  /* *pushqi2 */
    case 64:  /* *pushsi2 */
    case 63:  /* *pushdi2 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (pat, 1));
      break;

    case 168:  /* x86_fldcw_1 */
    case 48:  /* x86_sahf_1 */
      ro[0] = *(ro_loc[0] = &XVECEXP (XEXP (pat, 1), 0, 0));
      break;

    case 1460:  /* sse_stmxcsr */
    case 824:  /* lwp_slwpcbdi */
    case 823:  /* lwp_slwpcbsi */
    case 816:  /* fxsave */
    case 814:  /* rdtsc */
    case 619:  /* *load_tp_di */
    case 618:  /* *load_tp_si */
    case 617:  /* *load_tp_x32_zext */
    case 616:  /* *load_tp_x32 */
    case 167:  /* x86_fnstcw_1 */
    case 47:  /* x86_fnstsw_1 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      break;

    case 46:  /* *cmpxf_si_cc_i387 */
    case 45:  /* *cmpdf_si_cc_i387 */
    case 44:  /* *cmpsf_si_cc_i387 */
    case 43:  /* *cmpxf_hi_cc_i387 */
    case 42:  /* *cmpdf_hi_cc_i387 */
    case 41:  /* *cmpsf_hi_cc_i387 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1));
      break;

    case 40:  /* *cmpxf_si_i387 */
    case 39:  /* *cmpdf_si_i387 */
    case 38:  /* *cmpsf_si_i387 */
    case 37:  /* *cmpxf_hi_i387 */
    case 36:  /* *cmpdf_hi_i387 */
    case 35:  /* *cmpsf_hi_i387 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (XEXP (pat, 1), 0, 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XVECEXP (XEXP (pat, 1), 0, 0), 1), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (XEXP (pat, 1), 0, 0), 1));
      break;

    case 251:  /* *addsi_4 */
    case 250:  /* *addhi_4 */
    case 249:  /* *addqi_4 */
    case 34:  /* *cmpuxf_cc_i387 */
    case 33:  /* *cmpudf_cc_i387 */
    case 32:  /* *cmpusf_cc_i387 */
    case 28:  /* *cmpdf_cc_i387 */
    case 27:  /* *cmpsf_cc_i387 */
    case 24:  /* *cmpxf_cc_i387 */
    case 22:  /* *cmpxf_0_cc_i387 */
    case 21:  /* *cmpdf_0_cc_i387 */
    case 20:  /* *cmpsf_0_cc_i387 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1));
      break;

    case 31:  /* *cmpuxf_i387 */
    case 30:  /* *cmpudf_i387 */
    case 29:  /* *cmpusf_i387 */
    case 26:  /* *cmpdf_i387 */
    case 25:  /* *cmpsf_i387 */
    case 23:  /* *cmpxf_i387 */
    case 19:  /* *cmpxf_0_i387 */
    case 18:  /* *cmpdf_0_i387 */
    case 17:  /* *cmpsf_0_i387 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (XEXP (pat, 1), 0, 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XVECEXP (XEXP (pat, 1), 0, 0), 1));
      break;

    case 16:  /* *cmpqi_ext_4 */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 0), 0));
      break;

    case 15:  /* *cmpqi_ext_3_insn */
    case 14:  /* *cmpqi_ext_2 */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 1), 1));
      break;

    case 13:  /* *cmpqi_ext_1 */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (pat, 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 0), 0));
      break;

    case 327:  /* *testsi_1 */
    case 326:  /* *testhi_1 */
    case 325:  /* *testqi_1 */
    case 324:  /* *testqi_1_maybe_si */
    case 12:  /* *cmpdi_minus_1 */
    case 11:  /* *cmpsi_minus_1 */
    case 10:  /* *cmphi_minus_1 */
    case 9:  /* *cmpqi_minus_1 */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 0), 1));
      break;

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
    case 8:  /* *cmpdi_1 */
    case 7:  /* *cmpsi_1 */
    case 6:  /* *cmphi_1 */
    case 5:  /* *cmpqi_1 */
    case 4:  /* *cmpdi_ccno_1 */
    case 3:  /* *cmpsi_ccno_1 */
    case 2:  /* *cmphi_ccno_1 */
    case 1:  /* *cmpqi_ccno_1 */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (pat, 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 1), 1));
      break;

    }
}
