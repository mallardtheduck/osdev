/* Generated automatically by the program `genopinit'
   from the machine description file `md'.  */

#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "tm.h"
#include "rtl.h"
#include "tm_p.h"
#include "flags.h"
#include "insn-config.h"
#include "expr.h"
#include "optabs.h"

struct optab_pat {
  unsigned scode;
  enum insn_code icode;
};

static const struct optab_pat pats[NUM_OPTAB_PATTERNS] = {
  { 0x010e0f, CODE_FOR_extendqihi2 },
  { 0x010e10, CODE_FOR_extendqisi2 },
  { 0x010f10, CODE_FOR_extendhisi2 },
  { 0x011011, CODE_FOR_extendsidi2 },
  { 0x012627, CODE_FOR_extendsfdf2 },
  { 0x012628, CODE_FOR_extendsfxf2 },
  { 0x012728, CODE_FOR_extenddfxf2 },
  { 0x022726, CODE_FOR_truncdfsf2 },
  { 0x022826, CODE_FOR_truncxfsf2 },
  { 0x022827, CODE_FOR_truncxfdf2 },
  { 0x030e0f, CODE_FOR_zero_extendqihi2 },
  { 0x030e10, CODE_FOR_zero_extendqisi2 },
  { 0x030f10, CODE_FOR_zero_extendhisi2 },
  { 0x031011, CODE_FOR_zero_extendsidi2 },
  { 0x060f26, CODE_FOR_floathisf2 },
  { 0x060f27, CODE_FOR_floathidf2 },
  { 0x060f28, CODE_FOR_floathixf2 },
  { 0x061026, CODE_FOR_floatsisf2 },
  { 0x061027, CODE_FOR_floatsidf2 },
  { 0x061028, CODE_FOR_floatsixf2 },
  { 0x061126, CODE_FOR_floatdisf2 },
  { 0x061127, CODE_FOR_floatdidf2 },
  { 0x061128, CODE_FOR_floatdixf2 },
  { 0x06414f, CODE_FOR_floatv4siv4sf2 },
  { 0x064152, CODE_FOR_floatv4siv4df2 },
  { 0x064651, CODE_FOR_floatv8siv8sf2 },
  { 0x071026, CODE_FOR_floatunssisf2 },
  { 0x071027, CODE_FOR_floatunssidf2 },
  { 0x071028, CODE_FOR_floatunssixf2 },
  { 0x07414f, CODE_FOR_floatunsv4siv4sf2 },
  { 0x074651, CODE_FOR_floatunsv8siv8sf2 },
  { 0x082610, CODE_FOR_lrintsfsi2 },
  { 0x082710, CODE_FOR_lrintdfsi2 },
  { 0x08280f, CODE_FOR_lrintxfhi2 },
  { 0x082810, CODE_FOR_lrintxfsi2 },
  { 0x082811, CODE_FOR_lrintxfdi2 },
  { 0x09260f, CODE_FOR_lroundsfhi2 },
  { 0x092610, CODE_FOR_lroundsfsi2 },
  { 0x092611, CODE_FOR_lroundsfdi2 },
  { 0x09270f, CODE_FOR_lrounddfhi2 },
  { 0x092710, CODE_FOR_lrounddfsi2 },
  { 0x092711, CODE_FOR_lrounddfdi2 },
  { 0x09280f, CODE_FOR_lroundxfhi2 },
  { 0x092810, CODE_FOR_lroundxfsi2 },
  { 0x092811, CODE_FOR_lroundxfdi2 },
  { 0x0a2610, CODE_FOR_lfloorsfsi2 },
  { 0x0a2710, CODE_FOR_lfloordfsi2 },
  { 0x0a280f, CODE_FOR_lfloorxfhi2 },
  { 0x0a2810, CODE_FOR_lfloorxfsi2 },
  { 0x0a2811, CODE_FOR_lfloorxfdi2 },
  { 0x0b2610, CODE_FOR_lceilsfsi2 },
  { 0x0b2710, CODE_FOR_lceildfsi2 },
  { 0x0b280f, CODE_FOR_lceilxfhi2 },
  { 0x0b2810, CODE_FOR_lceilxfsi2 },
  { 0x0b2811, CODE_FOR_lceilxfdi2 },
  { 0x10260f, CODE_FOR_fix_truncsfhi2 },
  { 0x102610, CODE_FOR_fix_truncsfsi2 },
  { 0x102611, CODE_FOR_fix_truncsfdi2 },
  { 0x10270f, CODE_FOR_fix_truncdfhi2 },
  { 0x102710, CODE_FOR_fix_truncdfsi2 },
  { 0x102711, CODE_FOR_fix_truncdfdi2 },
  { 0x10280f, CODE_FOR_fix_truncxfhi2 },
  { 0x102810, CODE_FOR_fix_truncxfsi2 },
  { 0x102811, CODE_FOR_fix_truncxfdi2 },
  { 0x104f41, CODE_FOR_fix_truncv4sfv4si2 },
  { 0x105146, CODE_FOR_fix_truncv8sfv8si2 },
  { 0x105241, CODE_FOR_fix_truncv4dfv4si2 },
  { 0x11260f, CODE_FOR_fixuns_truncsfhi2 },
  { 0x112610, CODE_FOR_fixuns_truncsfsi2 },
  { 0x11270f, CODE_FOR_fixuns_truncdfhi2 },
  { 0x112710, CODE_FOR_fixuns_truncdfsi2 },
  { 0x114f41, CODE_FOR_fixuns_truncv4sfv4si2 },
  { 0x115146, CODE_FOR_fixuns_truncv8sfv8si2 },
  { 0x120e0f, CODE_FOR_mulqihi3 },
  { 0x121011, CODE_FOR_mulsidi3 },
  { 0x130e0f, CODE_FOR_umulqihi3 },
  { 0x131011, CODE_FOR_umulsidi3 },
  { 0x1f3f3f, CODE_FOR_vcondv16qiv16qi },
  { 0x1f3f40, CODE_FOR_vcondv8hiv16qi },
  { 0x1f3f41, CODE_FOR_vcondv4siv16qi },
  { 0x1f3f42, CODE_FOR_vcondv2div16qi },
  { 0x1f3f4f, CODE_FOR_vcondv4sfv16qi },
  { 0x1f3f50, CODE_FOR_vcondv2dfv16qi },
  { 0x1f403f, CODE_FOR_vcondv16qiv8hi },
  { 0x1f4040, CODE_FOR_vcondv8hiv8hi },
  { 0x1f4041, CODE_FOR_vcondv4siv8hi },
  { 0x1f4042, CODE_FOR_vcondv2div8hi },
  { 0x1f404f, CODE_FOR_vcondv4sfv8hi },
  { 0x1f4050, CODE_FOR_vcondv2dfv8hi },
  { 0x1f413f, CODE_FOR_vcondv16qiv4si },
  { 0x1f4140, CODE_FOR_vcondv8hiv4si },
  { 0x1f4141, CODE_FOR_vcondv4siv4si },
  { 0x1f4142, CODE_FOR_vcondv2div4si },
  { 0x1f414f, CODE_FOR_vcondv4sfv4si },
  { 0x1f4150, CODE_FOR_vcondv2dfv4si },
  { 0x1f4242, CODE_FOR_vcondv2div2di },
  { 0x1f4250, CODE_FOR_vcondv2dfv2di },
  { 0x1f4444, CODE_FOR_vcondv32qiv32qi },
  { 0x1f4445, CODE_FOR_vcondv16hiv32qi },
  { 0x1f4446, CODE_FOR_vcondv8siv32qi },
  { 0x1f4447, CODE_FOR_vcondv4div32qi },
  { 0x1f4451, CODE_FOR_vcondv8sfv32qi },
  { 0x1f4452, CODE_FOR_vcondv4dfv32qi },
  { 0x1f4544, CODE_FOR_vcondv32qiv16hi },
  { 0x1f4545, CODE_FOR_vcondv16hiv16hi },
  { 0x1f4546, CODE_FOR_vcondv8siv16hi },
  { 0x1f4547, CODE_FOR_vcondv4div16hi },
  { 0x1f4551, CODE_FOR_vcondv8sfv16hi },
  { 0x1f4552, CODE_FOR_vcondv4dfv16hi },
  { 0x1f4644, CODE_FOR_vcondv32qiv8si },
  { 0x1f4645, CODE_FOR_vcondv16hiv8si },
  { 0x1f4646, CODE_FOR_vcondv8siv8si },
  { 0x1f4647, CODE_FOR_vcondv4div8si },
  { 0x1f4651, CODE_FOR_vcondv8sfv8si },
  { 0x1f4652, CODE_FOR_vcondv4dfv8si },
  { 0x1f4744, CODE_FOR_vcondv32qiv4di },
  { 0x1f4745, CODE_FOR_vcondv16hiv4di },
  { 0x1f4746, CODE_FOR_vcondv8siv4di },
  { 0x1f4747, CODE_FOR_vcondv4div4di },
  { 0x1f4751, CODE_FOR_vcondv8sfv4di },
  { 0x1f4752, CODE_FOR_vcondv4dfv4di },
  { 0x1f4f3f, CODE_FOR_vcondv16qiv4sf },
  { 0x1f4f40, CODE_FOR_vcondv8hiv4sf },
  { 0x1f4f41, CODE_FOR_vcondv4siv4sf },
  { 0x1f4f42, CODE_FOR_vcondv2div4sf },
  { 0x1f4f4f, CODE_FOR_vcondv4sfv4sf },
  { 0x1f4f50, CODE_FOR_vcondv2dfv4sf },
  { 0x1f503f, CODE_FOR_vcondv16qiv2df },
  { 0x1f5040, CODE_FOR_vcondv8hiv2df },
  { 0x1f5041, CODE_FOR_vcondv4siv2df },
  { 0x1f5042, CODE_FOR_vcondv2div2df },
  { 0x1f504f, CODE_FOR_vcondv4sfv2df },
  { 0x1f5050, CODE_FOR_vcondv2dfv2df },
  { 0x1f5144, CODE_FOR_vcondv32qiv8sf },
  { 0x1f5145, CODE_FOR_vcondv16hiv8sf },
  { 0x1f5146, CODE_FOR_vcondv8siv8sf },
  { 0x1f5147, CODE_FOR_vcondv4div8sf },
  { 0x1f5151, CODE_FOR_vcondv8sfv8sf },
  { 0x1f5152, CODE_FOR_vcondv4dfv8sf },
  { 0x1f5244, CODE_FOR_vcondv32qiv4df },
  { 0x1f5245, CODE_FOR_vcondv16hiv4df },
  { 0x1f5246, CODE_FOR_vcondv8siv4df },
  { 0x1f5247, CODE_FOR_vcondv4div4df },
  { 0x1f5251, CODE_FOR_vcondv8sfv4df },
  { 0x1f5252, CODE_FOR_vcondv4dfv4df },
  { 0x203f3f, CODE_FOR_vconduv16qiv16qi },
  { 0x203f40, CODE_FOR_vconduv8hiv16qi },
  { 0x203f41, CODE_FOR_vconduv4siv16qi },
  { 0x203f42, CODE_FOR_vconduv2div16qi },
  { 0x203f4f, CODE_FOR_vconduv4sfv16qi },
  { 0x203f50, CODE_FOR_vconduv2dfv16qi },
  { 0x20403f, CODE_FOR_vconduv16qiv8hi },
  { 0x204040, CODE_FOR_vconduv8hiv8hi },
  { 0x204041, CODE_FOR_vconduv4siv8hi },
  { 0x204042, CODE_FOR_vconduv2div8hi },
  { 0x20404f, CODE_FOR_vconduv4sfv8hi },
  { 0x204050, CODE_FOR_vconduv2dfv8hi },
  { 0x20413f, CODE_FOR_vconduv16qiv4si },
  { 0x204140, CODE_FOR_vconduv8hiv4si },
  { 0x204141, CODE_FOR_vconduv4siv4si },
  { 0x204142, CODE_FOR_vconduv2div4si },
  { 0x20414f, CODE_FOR_vconduv4sfv4si },
  { 0x204150, CODE_FOR_vconduv2dfv4si },
  { 0x204242, CODE_FOR_vconduv2div2di },
  { 0x204250, CODE_FOR_vconduv2dfv2di },
  { 0x204444, CODE_FOR_vconduv32qiv32qi },
  { 0x204445, CODE_FOR_vconduv16hiv32qi },
  { 0x204446, CODE_FOR_vconduv8siv32qi },
  { 0x204447, CODE_FOR_vconduv4div32qi },
  { 0x204451, CODE_FOR_vconduv8sfv32qi },
  { 0x204452, CODE_FOR_vconduv4dfv32qi },
  { 0x204544, CODE_FOR_vconduv32qiv16hi },
  { 0x204545, CODE_FOR_vconduv16hiv16hi },
  { 0x204546, CODE_FOR_vconduv8siv16hi },
  { 0x204547, CODE_FOR_vconduv4div16hi },
  { 0x204551, CODE_FOR_vconduv8sfv16hi },
  { 0x204552, CODE_FOR_vconduv4dfv16hi },
  { 0x204644, CODE_FOR_vconduv32qiv8si },
  { 0x204645, CODE_FOR_vconduv16hiv8si },
  { 0x204646, CODE_FOR_vconduv8siv8si },
  { 0x204647, CODE_FOR_vconduv4div8si },
  { 0x204651, CODE_FOR_vconduv8sfv8si },
  { 0x204652, CODE_FOR_vconduv4dfv8si },
  { 0x204744, CODE_FOR_vconduv32qiv4di },
  { 0x204745, CODE_FOR_vconduv16hiv4di },
  { 0x204746, CODE_FOR_vconduv8siv4di },
  { 0x204747, CODE_FOR_vconduv4div4di },
  { 0x204751, CODE_FOR_vconduv8sfv4di },
  { 0x204752, CODE_FOR_vconduv4dfv4di },
  { 0x21000e, CODE_FOR_addqi3 },
  { 0x21000f, CODE_FOR_addhi3 },
  { 0x210010, CODE_FOR_addsi3 },
  { 0x210011, CODE_FOR_adddi3 },
  { 0x210026, CODE_FOR_addsf3 },
  { 0x210027, CODE_FOR_adddf3 },
  { 0x210028, CODE_FOR_addxf3 },
  { 0x21003f, CODE_FOR_addv16qi3 },
  { 0x210040, CODE_FOR_addv8hi3 },
  { 0x210041, CODE_FOR_addv4si3 },
  { 0x210042, CODE_FOR_addv2di3 },
  { 0x210044, CODE_FOR_addv32qi3 },
  { 0x210045, CODE_FOR_addv16hi3 },
  { 0x210046, CODE_FOR_addv8si3 },
  { 0x210047, CODE_FOR_addv4di3 },
  { 0x21004f, CODE_FOR_addv4sf3 },
  { 0x210050, CODE_FOR_addv2df3 },
  { 0x210051, CODE_FOR_addv8sf3 },
  { 0x210052, CODE_FOR_addv4df3 },
  { 0x25000e, CODE_FOR_subqi3 },
  { 0x25000f, CODE_FOR_subhi3 },
  { 0x250010, CODE_FOR_subsi3 },
  { 0x250011, CODE_FOR_subdi3 },
  { 0x250026, CODE_FOR_subsf3 },
  { 0x250027, CODE_FOR_subdf3 },
  { 0x250028, CODE_FOR_subxf3 },
  { 0x25003f, CODE_FOR_subv16qi3 },
  { 0x250040, CODE_FOR_subv8hi3 },
  { 0x250041, CODE_FOR_subv4si3 },
  { 0x250042, CODE_FOR_subv2di3 },
  { 0x250044, CODE_FOR_subv32qi3 },
  { 0x250045, CODE_FOR_subv16hi3 },
  { 0x250046, CODE_FOR_subv8si3 },
  { 0x250047, CODE_FOR_subv4di3 },
  { 0x25004f, CODE_FOR_subv4sf3 },
  { 0x250050, CODE_FOR_subv2df3 },
  { 0x250051, CODE_FOR_subv8sf3 },
  { 0x250052, CODE_FOR_subv4df3 },
  { 0x29000e, CODE_FOR_mulqi3 },
  { 0x29000f, CODE_FOR_mulhi3 },
  { 0x290010, CODE_FOR_mulsi3 },
  { 0x290026, CODE_FOR_mulsf3 },
  { 0x290027, CODE_FOR_muldf3 },
  { 0x290028, CODE_FOR_mulxf3 },
  { 0x29003f, CODE_FOR_mulv16qi3 },
  { 0x290040, CODE_FOR_mulv8hi3 },
  { 0x290041, CODE_FOR_mulv4si3 },
  { 0x290042, CODE_FOR_mulv2di3 },
  { 0x290044, CODE_FOR_mulv32qi3 },
  { 0x290045, CODE_FOR_mulv16hi3 },
  { 0x290046, CODE_FOR_mulv8si3 },
  { 0x290047, CODE_FOR_mulv4di3 },
  { 0x29004f, CODE_FOR_mulv4sf3 },
  { 0x290050, CODE_FOR_mulv2df3 },
  { 0x290051, CODE_FOR_mulv8sf3 },
  { 0x290052, CODE_FOR_mulv4df3 },
  { 0x2d0026, CODE_FOR_divsf3 },
  { 0x2d0027, CODE_FOR_divdf3 },
  { 0x2d0028, CODE_FOR_divxf3 },
  { 0x2d004f, CODE_FOR_divv4sf3 },
  { 0x2d0050, CODE_FOR_divv2df3 },
  { 0x2d0051, CODE_FOR_divv8sf3 },
  { 0x2d0052, CODE_FOR_divv4df3 },
  { 0x32000e, CODE_FOR_divmodqi4 },
  { 0x32000f, CODE_FOR_divmodhi4 },
  { 0x320010, CODE_FOR_divmodsi4 },
  { 0x33000e, CODE_FOR_udivmodqi4 },
  { 0x33000f, CODE_FOR_udivmodhi4 },
  { 0x330010, CODE_FOR_udivmodsi4 },
  { 0x37000e, CODE_FOR_andqi3 },
  { 0x37000f, CODE_FOR_andhi3 },
  { 0x370010, CODE_FOR_andsi3 },
  { 0x370029, CODE_FOR_andtf3 },
  { 0x37003f, CODE_FOR_andv16qi3 },
  { 0x370040, CODE_FOR_andv8hi3 },
  { 0x370041, CODE_FOR_andv4si3 },
  { 0x370042, CODE_FOR_andv2di3 },
  { 0x370044, CODE_FOR_andv32qi3 },
  { 0x370045, CODE_FOR_andv16hi3 },
  { 0x370046, CODE_FOR_andv8si3 },
  { 0x370047, CODE_FOR_andv4di3 },
  { 0x37004f, CODE_FOR_andv4sf3 },
  { 0x370050, CODE_FOR_andv2df3 },
  { 0x370051, CODE_FOR_andv8sf3 },
  { 0x370052, CODE_FOR_andv4df3 },
  { 0x38000e, CODE_FOR_iorqi3 },
  { 0x38000f, CODE_FOR_iorhi3 },
  { 0x380010, CODE_FOR_iorsi3 },
  { 0x380029, CODE_FOR_iortf3 },
  { 0x38003f, CODE_FOR_iorv16qi3 },
  { 0x380040, CODE_FOR_iorv8hi3 },
  { 0x380041, CODE_FOR_iorv4si3 },
  { 0x380042, CODE_FOR_iorv2di3 },
  { 0x380044, CODE_FOR_iorv32qi3 },
  { 0x380045, CODE_FOR_iorv16hi3 },
  { 0x380046, CODE_FOR_iorv8si3 },
  { 0x380047, CODE_FOR_iorv4di3 },
  { 0x38004f, CODE_FOR_iorv4sf3 },
  { 0x380050, CODE_FOR_iorv2df3 },
  { 0x380051, CODE_FOR_iorv8sf3 },
  { 0x380052, CODE_FOR_iorv4df3 },
  { 0x39000e, CODE_FOR_xorqi3 },
  { 0x39000f, CODE_FOR_xorhi3 },
  { 0x390010, CODE_FOR_xorsi3 },
  { 0x390029, CODE_FOR_xortf3 },
  { 0x39003f, CODE_FOR_xorv16qi3 },
  { 0x390040, CODE_FOR_xorv8hi3 },
  { 0x390041, CODE_FOR_xorv4si3 },
  { 0x390042, CODE_FOR_xorv2di3 },
  { 0x390044, CODE_FOR_xorv32qi3 },
  { 0x390045, CODE_FOR_xorv16hi3 },
  { 0x390046, CODE_FOR_xorv8si3 },
  { 0x390047, CODE_FOR_xorv4di3 },
  { 0x39004f, CODE_FOR_xorv4sf3 },
  { 0x390050, CODE_FOR_xorv2df3 },
  { 0x390051, CODE_FOR_xorv8sf3 },
  { 0x390052, CODE_FOR_xorv4df3 },
  { 0x3a000e, CODE_FOR_ashlqi3 },
  { 0x3a000f, CODE_FOR_ashlhi3 },
  { 0x3a0010, CODE_FOR_ashlsi3 },
  { 0x3a0011, CODE_FOR_ashldi3 },
  { 0x3a003f, CODE_FOR_ashlv16qi3 },
  { 0x3a0040, CODE_FOR_ashlv8hi3 },
  { 0x3a0041, CODE_FOR_ashlv4si3 },
  { 0x3a0042, CODE_FOR_ashlv2di3 },
  { 0x3a0044, CODE_FOR_ashlv32qi3 },
  { 0x3a0045, CODE_FOR_ashlv16hi3 },
  { 0x3a0046, CODE_FOR_ashlv8si3 },
  { 0x3a0047, CODE_FOR_ashlv4di3 },
  { 0x3d000e, CODE_FOR_ashrqi3 },
  { 0x3d000f, CODE_FOR_ashrhi3 },
  { 0x3d0010, CODE_FOR_ashrsi3 },
  { 0x3d0011, CODE_FOR_ashrdi3 },
  { 0x3d003f, CODE_FOR_ashrv16qi3 },
  { 0x3d0040, CODE_FOR_ashrv8hi3 },
  { 0x3d0041, CODE_FOR_ashrv4si3 },
  { 0x3d0042, CODE_FOR_ashrv2di3 },
  { 0x3d0044, CODE_FOR_ashrv32qi3 },
  { 0x3d0045, CODE_FOR_ashrv16hi3 },
  { 0x3d0046, CODE_FOR_ashrv8si3 },
  { 0x3e000e, CODE_FOR_lshrqi3 },
  { 0x3e000f, CODE_FOR_lshrhi3 },
  { 0x3e0010, CODE_FOR_lshrsi3 },
  { 0x3e0011, CODE_FOR_lshrdi3 },
  { 0x3e003f, CODE_FOR_lshrv16qi3 },
  { 0x3e0040, CODE_FOR_lshrv8hi3 },
  { 0x3e0041, CODE_FOR_lshrv4si3 },
  { 0x3e0042, CODE_FOR_lshrv2di3 },
  { 0x3e0044, CODE_FOR_lshrv32qi3 },
  { 0x3e0045, CODE_FOR_lshrv16hi3 },
  { 0x3e0046, CODE_FOR_lshrv8si3 },
  { 0x3e0047, CODE_FOR_lshrv4di3 },
  { 0x3f000e, CODE_FOR_rotlqi3 },
  { 0x3f000f, CODE_FOR_rotlhi3 },
  { 0x3f0010, CODE_FOR_rotlsi3 },
  { 0x3f0011, CODE_FOR_rotldi3 },
  { 0x3f003f, CODE_FOR_rotlv16qi3 },
  { 0x3f0040, CODE_FOR_rotlv8hi3 },
  { 0x3f0041, CODE_FOR_rotlv4si3 },
  { 0x3f0042, CODE_FOR_rotlv2di3 },
  { 0x40000e, CODE_FOR_rotrqi3 },
  { 0x40000f, CODE_FOR_rotrhi3 },
  { 0x400010, CODE_FOR_rotrsi3 },
  { 0x400011, CODE_FOR_rotrdi3 },
  { 0x40003f, CODE_FOR_rotrv16qi3 },
  { 0x400040, CODE_FOR_rotrv8hi3 },
  { 0x400041, CODE_FOR_rotrv4si3 },
  { 0x400042, CODE_FOR_rotrv2di3 },
  { 0x41003f, CODE_FOR_vashlv16qi3 },
  { 0x410040, CODE_FOR_vashlv8hi3 },
  { 0x410041, CODE_FOR_vashlv4si3 },
  { 0x410042, CODE_FOR_vashlv2di3 },
  { 0x410046, CODE_FOR_vashlv8si3 },
  { 0x410047, CODE_FOR_vashlv4di3 },
  { 0x42003f, CODE_FOR_vashrv16qi3 },
  { 0x420040, CODE_FOR_vashrv8hi3 },
  { 0x420041, CODE_FOR_vashrv4si3 },
  { 0x420042, CODE_FOR_vashrv2di3 },
  { 0x420046, CODE_FOR_vashrv8si3 },
  { 0x43003f, CODE_FOR_vlshrv16qi3 },
  { 0x430040, CODE_FOR_vlshrv8hi3 },
  { 0x430041, CODE_FOR_vlshrv4si3 },
  { 0x430042, CODE_FOR_vlshrv2di3 },
  { 0x430046, CODE_FOR_vlshrv8si3 },
  { 0x430047, CODE_FOR_vlshrv4di3 },
  { 0x44003f, CODE_FOR_vrotlv16qi3 },
  { 0x440040, CODE_FOR_vrotlv8hi3 },
  { 0x440041, CODE_FOR_vrotlv4si3 },
  { 0x440042, CODE_FOR_vrotlv2di3 },
  { 0x45003f, CODE_FOR_vrotrv16qi3 },
  { 0x450040, CODE_FOR_vrotrv8hi3 },
  { 0x450041, CODE_FOR_vrotrv4si3 },
  { 0x450042, CODE_FOR_vrotrv2di3 },
  { 0x460026, CODE_FOR_sminsf3 },
  { 0x460027, CODE_FOR_smindf3 },
  { 0x46003f, CODE_FOR_sminv16qi3 },
  { 0x460040, CODE_FOR_sminv8hi3 },
  { 0x460041, CODE_FOR_sminv4si3 },
  { 0x460042, CODE_FOR_sminv2di3 },
  { 0x460044, CODE_FOR_sminv32qi3 },
  { 0x460045, CODE_FOR_sminv16hi3 },
  { 0x460046, CODE_FOR_sminv8si3 },
  { 0x460047, CODE_FOR_sminv4di3 },
  { 0x46004f, CODE_FOR_sminv4sf3 },
  { 0x460050, CODE_FOR_sminv2df3 },
  { 0x460051, CODE_FOR_sminv8sf3 },
  { 0x460052, CODE_FOR_sminv4df3 },
  { 0x470026, CODE_FOR_smaxsf3 },
  { 0x470027, CODE_FOR_smaxdf3 },
  { 0x47003f, CODE_FOR_smaxv16qi3 },
  { 0x470040, CODE_FOR_smaxv8hi3 },
  { 0x470041, CODE_FOR_smaxv4si3 },
  { 0x470042, CODE_FOR_smaxv2di3 },
  { 0x470044, CODE_FOR_smaxv32qi3 },
  { 0x470045, CODE_FOR_smaxv16hi3 },
  { 0x470046, CODE_FOR_smaxv8si3 },
  { 0x470047, CODE_FOR_smaxv4di3 },
  { 0x47004f, CODE_FOR_smaxv4sf3 },
  { 0x470050, CODE_FOR_smaxv2df3 },
  { 0x470051, CODE_FOR_smaxv8sf3 },
  { 0x470052, CODE_FOR_smaxv4df3 },
  { 0x48003f, CODE_FOR_uminv16qi3 },
  { 0x480040, CODE_FOR_uminv8hi3 },
  { 0x480041, CODE_FOR_uminv4si3 },
  { 0x480042, CODE_FOR_uminv2di3 },
  { 0x480044, CODE_FOR_uminv32qi3 },
  { 0x480045, CODE_FOR_uminv16hi3 },
  { 0x480046, CODE_FOR_uminv8si3 },
  { 0x480047, CODE_FOR_uminv4di3 },
  { 0x49003f, CODE_FOR_umaxv16qi3 },
  { 0x490040, CODE_FOR_umaxv8hi3 },
  { 0x490041, CODE_FOR_umaxv4si3 },
  { 0x490042, CODE_FOR_umaxv2di3 },
  { 0x490044, CODE_FOR_umaxv32qi3 },
  { 0x490045, CODE_FOR_umaxv16hi3 },
  { 0x490046, CODE_FOR_umaxv8si3 },
  { 0x490047, CODE_FOR_umaxv4di3 },
  { 0x4a000e, CODE_FOR_negqi2 },
  { 0x4a000f, CODE_FOR_neghi2 },
  { 0x4a0010, CODE_FOR_negsi2 },
  { 0x4a0011, CODE_FOR_negdi2 },
  { 0x4a0026, CODE_FOR_negsf2 },
  { 0x4a0027, CODE_FOR_negdf2 },
  { 0x4a0028, CODE_FOR_negxf2 },
  { 0x4a0029, CODE_FOR_negtf2 },
  { 0x4a003f, CODE_FOR_negv16qi2 },
  { 0x4a0040, CODE_FOR_negv8hi2 },
  { 0x4a0041, CODE_FOR_negv4si2 },
  { 0x4a0042, CODE_FOR_negv2di2 },
  { 0x4a0044, CODE_FOR_negv32qi2 },
  { 0x4a0045, CODE_FOR_negv16hi2 },
  { 0x4a0046, CODE_FOR_negv8si2 },
  { 0x4a0047, CODE_FOR_negv4di2 },
  { 0x4a004f, CODE_FOR_negv4sf2 },
  { 0x4a0050, CODE_FOR_negv2df2 },
  { 0x4a0051, CODE_FOR_negv8sf2 },
  { 0x4a0052, CODE_FOR_negv4df2 },
  { 0x4e0026, CODE_FOR_abssf2 },
  { 0x4e0027, CODE_FOR_absdf2 },
  { 0x4e0028, CODE_FOR_absxf2 },
  { 0x4e0029, CODE_FOR_abstf2 },
  { 0x4e003b, CODE_FOR_absv8qi2 },
  { 0x4e003c, CODE_FOR_absv4hi2 },
  { 0x4e003d, CODE_FOR_absv2si2 },
  { 0x4e003f, CODE_FOR_absv16qi2 },
  { 0x4e0040, CODE_FOR_absv8hi2 },
  { 0x4e0041, CODE_FOR_absv4si2 },
  { 0x4e0044, CODE_FOR_absv32qi2 },
  { 0x4e0045, CODE_FOR_absv16hi2 },
  { 0x4e0046, CODE_FOR_absv8si2 },
  { 0x4e004f, CODE_FOR_absv4sf2 },
  { 0x4e0050, CODE_FOR_absv2df2 },
  { 0x4e0051, CODE_FOR_absv8sf2 },
  { 0x4e0052, CODE_FOR_absv4df2 },
  { 0x50000e, CODE_FOR_one_cmplqi2 },
  { 0x50000f, CODE_FOR_one_cmplhi2 },
  { 0x500010, CODE_FOR_one_cmplsi2 },
  { 0x50003f, CODE_FOR_one_cmplv16qi2 },
  { 0x500040, CODE_FOR_one_cmplv8hi2 },
  { 0x500041, CODE_FOR_one_cmplv4si2 },
  { 0x500042, CODE_FOR_one_cmplv2di2 },
  { 0x500044, CODE_FOR_one_cmplv32qi2 },
  { 0x500045, CODE_FOR_one_cmplv16hi2 },
  { 0x500046, CODE_FOR_one_cmplv8si2 },
  { 0x500047, CODE_FOR_one_cmplv4di2 },
  { 0x510010, CODE_FOR_bswapsi2 },
  { 0x520010, CODE_FOR_ffssi2 },
  { 0x53000f, CODE_FOR_clzhi2 },
  { 0x530010, CODE_FOR_clzsi2 },
  { 0x54000f, CODE_FOR_ctzhi2 },
  { 0x540010, CODE_FOR_ctzsi2 },
  { 0x56000f, CODE_FOR_popcounthi2 },
  { 0x560010, CODE_FOR_popcountsi2 },
  { 0x570010, CODE_FOR_paritysi2 },
  { 0x570011, CODE_FOR_paritydi2 },
  { 0x620026, CODE_FOR_sqrtsf2 },
  { 0x620027, CODE_FOR_sqrtdf2 },
  { 0x620028, CODE_FOR_sqrtxf2 },
  { 0x62004f, CODE_FOR_sqrtv4sf2 },
  { 0x620050, CODE_FOR_sqrtv2df2 },
  { 0x620051, CODE_FOR_sqrtv8sf2 },
  { 0x620052, CODE_FOR_sqrtv4df2 },
  { 0x71000e, CODE_FOR_movqi },
  { 0x71000f, CODE_FOR_movhi },
  { 0x710010, CODE_FOR_movsi },
  { 0x710011, CODE_FOR_movdi },
  { 0x710012, CODE_FOR_movti },
  { 0x710013, CODE_FOR_movoi },
  { 0x710026, CODE_FOR_movsf },
  { 0x710027, CODE_FOR_movdf },
  { 0x710028, CODE_FOR_movxf },
  { 0x710029, CODE_FOR_movtf },
  { 0x710030, CODE_FOR_movcdi },
  { 0x71003b, CODE_FOR_movv8qi },
  { 0x71003c, CODE_FOR_movv4hi },
  { 0x71003d, CODE_FOR_movv2si },
  { 0x71003e, CODE_FOR_movv1di },
  { 0x71003f, CODE_FOR_movv16qi },
  { 0x710040, CODE_FOR_movv8hi },
  { 0x710041, CODE_FOR_movv4si },
  { 0x710042, CODE_FOR_movv2di },
  { 0x710043, CODE_FOR_movv1ti },
  { 0x710044, CODE_FOR_movv32qi },
  { 0x710045, CODE_FOR_movv16hi },
  { 0x710046, CODE_FOR_movv8si },
  { 0x710047, CODE_FOR_movv4di },
  { 0x710048, CODE_FOR_movv2ti },
  { 0x71004e, CODE_FOR_movv2sf },
  { 0x71004f, CODE_FOR_movv4sf },
  { 0x710050, CODE_FOR_movv2df },
  { 0x710051, CODE_FOR_movv8sf },
  { 0x710052, CODE_FOR_movv4df },
  { 0x72000e, CODE_FOR_movstrictqi },
  { 0x72000f, CODE_FOR_movstricthi },
  { 0x73003b, CODE_FOR_movmisalignv8qi },
  { 0x73003c, CODE_FOR_movmisalignv4hi },
  { 0x73003d, CODE_FOR_movmisalignv2si },
  { 0x73003e, CODE_FOR_movmisalignv1di },
  { 0x73003f, CODE_FOR_movmisalignv16qi },
  { 0x730040, CODE_FOR_movmisalignv8hi },
  { 0x730041, CODE_FOR_movmisalignv4si },
  { 0x730042, CODE_FOR_movmisalignv2di },
  { 0x730043, CODE_FOR_movmisalignv1ti },
  { 0x730044, CODE_FOR_movmisalignv32qi },
  { 0x730045, CODE_FOR_movmisalignv16hi },
  { 0x730046, CODE_FOR_movmisalignv8si },
  { 0x730047, CODE_FOR_movmisalignv4di },
  { 0x730048, CODE_FOR_movmisalignv2ti },
  { 0x73004e, CODE_FOR_movmisalignv2sf },
  { 0x73004f, CODE_FOR_movmisalignv4sf },
  { 0x730050, CODE_FOR_movmisalignv2df },
  { 0x730051, CODE_FOR_movmisalignv8sf },
  { 0x730052, CODE_FOR_movmisalignv4df },
  { 0x740010, CODE_FOR_storentsi },
  { 0x740026, CODE_FOR_storentsf },
  { 0x740027, CODE_FOR_storentdf },
  { 0x740042, CODE_FOR_storentv2di },
  { 0x740047, CODE_FOR_storentv4di },
  { 0x74004f, CODE_FOR_storentv4sf },
  { 0x740050, CODE_FOR_storentv2df },
  { 0x740051, CODE_FOR_storentv8sf },
  { 0x740052, CODE_FOR_storentv4df },
  { 0x7b003b, CODE_FOR_pushv8qi1 },
  { 0x7b003c, CODE_FOR_pushv4hi1 },
  { 0x7b003d, CODE_FOR_pushv2si1 },
  { 0x7b003e, CODE_FOR_pushv1di1 },
  { 0x7b003f, CODE_FOR_pushv16qi1 },
  { 0x7b0040, CODE_FOR_pushv8hi1 },
  { 0x7b0041, CODE_FOR_pushv4si1 },
  { 0x7b0042, CODE_FOR_pushv2di1 },
  { 0x7b0043, CODE_FOR_pushv1ti1 },
  { 0x7b0044, CODE_FOR_pushv32qi1 },
  { 0x7b0045, CODE_FOR_pushv16hi1 },
  { 0x7b0046, CODE_FOR_pushv8si1 },
  { 0x7b0047, CODE_FOR_pushv4di1 },
  { 0x7b0048, CODE_FOR_pushv2ti1 },
  { 0x7b004e, CODE_FOR_pushv2sf1 },
  { 0x7b004f, CODE_FOR_pushv4sf1 },
  { 0x7b0050, CODE_FOR_pushv2df1 },
  { 0x7b0051, CODE_FOR_pushv8sf1 },
  { 0x7b0052, CODE_FOR_pushv4df1 },
  { 0x7e0002, CODE_FOR_cbranchcc4 },
  { 0x7e000e, CODE_FOR_cbranchqi4 },
  { 0x7e000f, CODE_FOR_cbranchhi4 },
  { 0x7e0010, CODE_FOR_cbranchsi4 },
  { 0x7e0011, CODE_FOR_cbranchdi4 },
  { 0x7e0026, CODE_FOR_cbranchsf4 },
  { 0x7e0027, CODE_FOR_cbranchdf4 },
  { 0x7e0028, CODE_FOR_cbranchxf4 },
  { 0x7f000e, CODE_FOR_addqicc },
  { 0x7f000f, CODE_FOR_addhicc },
  { 0x7f0010, CODE_FOR_addsicc },
  { 0x80000e, CODE_FOR_movqicc },
  { 0x80000f, CODE_FOR_movhicc },
  { 0x800010, CODE_FOR_movsicc },
  { 0x800026, CODE_FOR_movsfcc },
  { 0x800027, CODE_FOR_movdfcc },
  { 0x800028, CODE_FOR_movxfcc },
  { 0x820002, CODE_FOR_cstorecc4 },
  { 0x82000e, CODE_FOR_cstoreqi4 },
  { 0x82000f, CODE_FOR_cstorehi4 },
  { 0x820010, CODE_FOR_cstoresi4 },
  { 0x820026, CODE_FOR_cstoresf4 },
  { 0x820027, CODE_FOR_cstoredf4 },
  { 0x820028, CODE_FOR_cstorexf4 },
  { 0x840010, CODE_FOR_smulsi3_highpart },
  { 0x840040, CODE_FOR_smulv8hi3_highpart },
  { 0x840045, CODE_FOR_smulv16hi3_highpart },
  { 0x850010, CODE_FOR_umulsi3_highpart },
  { 0x850040, CODE_FOR_umulv8hi3_highpart },
  { 0x850045, CODE_FOR_umulv16hi3_highpart },
  { 0x880010, CODE_FOR_cmpstrnsi },
  { 0x890010, CODE_FOR_movmemsi },
  { 0x8a0010, CODE_FOR_setmemsi },
  { 0x8b0010, CODE_FOR_strlensi },
  { 0x8b0011, CODE_FOR_strlendi },
  { 0x8c0026, CODE_FOR_fmasf4 },
  { 0x8c0027, CODE_FOR_fmadf4 },
  { 0x8c004f, CODE_FOR_fmav4sf4 },
  { 0x8c0050, CODE_FOR_fmav2df4 },
  { 0x8c0051, CODE_FOR_fmav8sf4 },
  { 0x8c0052, CODE_FOR_fmav4df4 },
  { 0x8d0026, CODE_FOR_fmssf4 },
  { 0x8d0027, CODE_FOR_fmsdf4 },
  { 0x8d004f, CODE_FOR_fmsv4sf4 },
  { 0x8d0050, CODE_FOR_fmsv2df4 },
  { 0x8d0051, CODE_FOR_fmsv8sf4 },
  { 0x8d0052, CODE_FOR_fmsv4df4 },
  { 0x8e0026, CODE_FOR_fnmasf4 },
  { 0x8e0027, CODE_FOR_fnmadf4 },
  { 0x8e004f, CODE_FOR_fnmav4sf4 },
  { 0x8e0050, CODE_FOR_fnmav2df4 },
  { 0x8e0051, CODE_FOR_fnmav8sf4 },
  { 0x8e0052, CODE_FOR_fnmav4df4 },
  { 0x8f0026, CODE_FOR_fnmssf4 },
  { 0x8f0027, CODE_FOR_fnmsdf4 },
  { 0x8f004f, CODE_FOR_fnmsv4sf4 },
  { 0x8f0050, CODE_FOR_fnmsv2df4 },
  { 0x8f0051, CODE_FOR_fnmsv8sf4 },
  { 0x8f0052, CODE_FOR_fnmsv4df4 },
  { 0x900026, CODE_FOR_rintsf2 },
  { 0x900027, CODE_FOR_rintdf2 },
  { 0x900028, CODE_FOR_rintxf2 },
  { 0x910026, CODE_FOR_roundsf2 },
  { 0x910027, CODE_FOR_rounddf2 },
  { 0x910028, CODE_FOR_roundxf2 },
  { 0x91004f, CODE_FOR_roundv4sf2 },
  { 0x910050, CODE_FOR_roundv2df2 },
  { 0x910051, CODE_FOR_roundv8sf2 },
  { 0x910052, CODE_FOR_roundv4df2 },
  { 0x920026, CODE_FOR_floorsf2 },
  { 0x920027, CODE_FOR_floordf2 },
  { 0x920028, CODE_FOR_floorxf2 },
  { 0x930026, CODE_FOR_ceilsf2 },
  { 0x930027, CODE_FOR_ceildf2 },
  { 0x930028, CODE_FOR_ceilxf2 },
  { 0x940026, CODE_FOR_btruncsf2 },
  { 0x940027, CODE_FOR_btruncdf2 },
  { 0x940028, CODE_FOR_btruncxf2 },
  { 0x950026, CODE_FOR_nearbyintsf2 },
  { 0x950027, CODE_FOR_nearbyintdf2 },
  { 0x950028, CODE_FOR_nearbyintxf2 },
  { 0x960026, CODE_FOR_acossf2 },
  { 0x960027, CODE_FOR_acosdf2 },
  { 0x960028, CODE_FOR_acosxf2 },
  { 0x970026, CODE_FOR_asinsf2 },
  { 0x970027, CODE_FOR_asindf2 },
  { 0x970028, CODE_FOR_asinxf2 },
  { 0x980026, CODE_FOR_atan2sf3 },
  { 0x980027, CODE_FOR_atan2df3 },
  { 0x980028, CODE_FOR_atan2xf3 },
  { 0x990026, CODE_FOR_atansf2 },
  { 0x990027, CODE_FOR_atandf2 },
  { 0x990028, CODE_FOR_atanxf2 },
  { 0x9a0026, CODE_FOR_copysignsf3 },
  { 0x9a0027, CODE_FOR_copysigndf3 },
  { 0x9a0029, CODE_FOR_copysigntf3 },
  { 0x9a004f, CODE_FOR_copysignv4sf3 },
  { 0x9a0050, CODE_FOR_copysignv2df3 },
  { 0x9a0051, CODE_FOR_copysignv8sf3 },
  { 0x9a0052, CODE_FOR_copysignv4df3 },
  { 0x9c0026, CODE_FOR_exp10sf2 },
  { 0x9c0027, CODE_FOR_exp10df2 },
  { 0x9c0028, CODE_FOR_exp10xf2 },
  { 0x9d0026, CODE_FOR_exp2sf2 },
  { 0x9d0027, CODE_FOR_exp2df2 },
  { 0x9d0028, CODE_FOR_exp2xf2 },
  { 0x9e0026, CODE_FOR_expsf2 },
  { 0x9e0027, CODE_FOR_expdf2 },
  { 0x9e0028, CODE_FOR_expxf2 },
  { 0x9f0026, CODE_FOR_expm1sf2 },
  { 0x9f0027, CODE_FOR_expm1df2 },
  { 0x9f0028, CODE_FOR_expm1xf2 },
  { 0xa00026, CODE_FOR_fmodsf3 },
  { 0xa00027, CODE_FOR_fmoddf3 },
  { 0xa00028, CODE_FOR_fmodxf3 },
  { 0xa10026, CODE_FOR_ilogbsf2 },
  { 0xa10027, CODE_FOR_ilogbdf2 },
  { 0xa10028, CODE_FOR_ilogbxf2 },
  { 0xa30026, CODE_FOR_ldexpsf3 },
  { 0xa30027, CODE_FOR_ldexpdf3 },
  { 0xa30028, CODE_FOR_ldexpxf3 },
  { 0xa40026, CODE_FOR_log10sf2 },
  { 0xa40027, CODE_FOR_log10df2 },
  { 0xa40028, CODE_FOR_log10xf2 },
  { 0xa50026, CODE_FOR_log1psf2 },
  { 0xa50027, CODE_FOR_log1pdf2 },
  { 0xa50028, CODE_FOR_log1pxf2 },
  { 0xa60026, CODE_FOR_log2sf2 },
  { 0xa60027, CODE_FOR_log2df2 },
  { 0xa60028, CODE_FOR_log2xf2 },
  { 0xa70026, CODE_FOR_logsf2 },
  { 0xa70027, CODE_FOR_logdf2 },
  { 0xa70028, CODE_FOR_logxf2 },
  { 0xa80026, CODE_FOR_logbsf2 },
  { 0xa80027, CODE_FOR_logbdf2 },
  { 0xa80028, CODE_FOR_logbxf2 },
  { 0xaa0026, CODE_FOR_remaindersf3 },
  { 0xaa0027, CODE_FOR_remainderdf3 },
  { 0xaa0028, CODE_FOR_remainderxf3 },
  { 0xab0026, CODE_FOR_scalbsf3 },
  { 0xab0027, CODE_FOR_scalbdf3 },
  { 0xab0028, CODE_FOR_scalbxf3 },
  { 0xac0026, CODE_FOR_signbitsf2 },
  { 0xac0027, CODE_FOR_signbitdf2 },
  { 0xac0028, CODE_FOR_signbitxf2 },
  { 0xad0026, CODE_FOR_significandsf2 },
  { 0xad0027, CODE_FOR_significanddf2 },
  { 0xad0028, CODE_FOR_significandxf2 },
  { 0xaf0026, CODE_FOR_sincossf3 },
  { 0xaf0027, CODE_FOR_sincosdf3 },
  { 0xaf0028, CODE_FOR_sincosxf3 },
  { 0xb00026, CODE_FOR_tansf2 },
  { 0xb00027, CODE_FOR_tandf2 },
  { 0xb00028, CODE_FOR_tanxf2 },
  { 0xb10044, CODE_FOR_reduc_smax_v32qi },
  { 0xb10045, CODE_FOR_reduc_smax_v16hi },
  { 0xb10046, CODE_FOR_reduc_smax_v8si },
  { 0xb10047, CODE_FOR_reduc_smax_v4di },
  { 0xb1004f, CODE_FOR_reduc_smax_v4sf },
  { 0xb10051, CODE_FOR_reduc_smax_v8sf },
  { 0xb10052, CODE_FOR_reduc_smax_v4df },
  { 0xb20044, CODE_FOR_reduc_smin_v32qi },
  { 0xb20045, CODE_FOR_reduc_smin_v16hi },
  { 0xb20046, CODE_FOR_reduc_smin_v8si },
  { 0xb20047, CODE_FOR_reduc_smin_v4di },
  { 0xb2004f, CODE_FOR_reduc_smin_v4sf },
  { 0xb20051, CODE_FOR_reduc_smin_v8sf },
  { 0xb20052, CODE_FOR_reduc_smin_v4df },
  { 0xb3004f, CODE_FOR_reduc_splus_v4sf },
  { 0xb30050, CODE_FOR_reduc_splus_v2df },
  { 0xb30051, CODE_FOR_reduc_splus_v8sf },
  { 0xb30052, CODE_FOR_reduc_splus_v4df },
  { 0xb40044, CODE_FOR_reduc_umax_v32qi },
  { 0xb40045, CODE_FOR_reduc_umax_v16hi },
  { 0xb40046, CODE_FOR_reduc_umax_v8si },
  { 0xb40047, CODE_FOR_reduc_umax_v4di },
  { 0xb50040, CODE_FOR_reduc_umin_v8hi },
  { 0xb50044, CODE_FOR_reduc_umin_v32qi },
  { 0xb50045, CODE_FOR_reduc_umin_v16hi },
  { 0xb50046, CODE_FOR_reduc_umin_v8si },
  { 0xb50047, CODE_FOR_reduc_umin_v4di },
  { 0xb70040, CODE_FOR_sdot_prodv8hi },
  { 0xb70041, CODE_FOR_sdot_prodv4si },
  { 0xb70045, CODE_FOR_sdot_prodv16hi },
  { 0xbb003b, CODE_FOR_vec_extractv8qi },
  { 0xbb003c, CODE_FOR_vec_extractv4hi },
  { 0xbb003d, CODE_FOR_vec_extractv2si },
  { 0xbb003f, CODE_FOR_vec_extractv16qi },
  { 0xbb0040, CODE_FOR_vec_extractv8hi },
  { 0xbb0041, CODE_FOR_vec_extractv4si },
  { 0xbb0042, CODE_FOR_vec_extractv2di },
  { 0xbb0044, CODE_FOR_vec_extractv32qi },
  { 0xbb0045, CODE_FOR_vec_extractv16hi },
  { 0xbb0046, CODE_FOR_vec_extractv8si },
  { 0xbb0047, CODE_FOR_vec_extractv4di },
  { 0xbb004e, CODE_FOR_vec_extractv2sf },
  { 0xbb004f, CODE_FOR_vec_extractv4sf },
  { 0xbb0050, CODE_FOR_vec_extractv2df },
  { 0xbb0051, CODE_FOR_vec_extractv8sf },
  { 0xbb0052, CODE_FOR_vec_extractv4df },
  { 0xbc003b, CODE_FOR_vec_initv8qi },
  { 0xbc003c, CODE_FOR_vec_initv4hi },
  { 0xbc003d, CODE_FOR_vec_initv2si },
  { 0xbc003f, CODE_FOR_vec_initv16qi },
  { 0xbc0040, CODE_FOR_vec_initv8hi },
  { 0xbc0041, CODE_FOR_vec_initv4si },
  { 0xbc0042, CODE_FOR_vec_initv2di },
  { 0xbc0044, CODE_FOR_vec_initv32qi },
  { 0xbc0045, CODE_FOR_vec_initv16hi },
  { 0xbc0046, CODE_FOR_vec_initv8si },
  { 0xbc0047, CODE_FOR_vec_initv4di },
  { 0xbc004e, CODE_FOR_vec_initv2sf },
  { 0xbc004f, CODE_FOR_vec_initv4sf },
  { 0xbc0050, CODE_FOR_vec_initv2df },
  { 0xbc0051, CODE_FOR_vec_initv8sf },
  { 0xbc0052, CODE_FOR_vec_initv4df },
  { 0xbd0050, CODE_FOR_vec_pack_sfix_trunc_v2df },
  { 0xbd0052, CODE_FOR_vec_pack_sfix_trunc_v4df },
  { 0xbf0040, CODE_FOR_vec_pack_trunc_v8hi },
  { 0xbf0041, CODE_FOR_vec_pack_trunc_v4si },
  { 0xbf0042, CODE_FOR_vec_pack_trunc_v2di },
  { 0xbf0045, CODE_FOR_vec_pack_trunc_v16hi },
  { 0xbf0046, CODE_FOR_vec_pack_trunc_v8si },
  { 0xbf0047, CODE_FOR_vec_pack_trunc_v4di },
  { 0xbf0050, CODE_FOR_vec_pack_trunc_v2df },
  { 0xbf0052, CODE_FOR_vec_pack_trunc_v4df },
  { 0xc00050, CODE_FOR_vec_pack_ufix_trunc_v2df },
  { 0xc00052, CODE_FOR_vec_pack_ufix_trunc_v4df },
  { 0xc2003f, CODE_FOR_vec_perm_constv16qi },
  { 0xc20040, CODE_FOR_vec_perm_constv8hi },
  { 0xc20041, CODE_FOR_vec_perm_constv4si },
  { 0xc20042, CODE_FOR_vec_perm_constv2di },
  { 0xc20044, CODE_FOR_vec_perm_constv32qi },
  { 0xc20045, CODE_FOR_vec_perm_constv16hi },
  { 0xc20046, CODE_FOR_vec_perm_constv8si },
  { 0xc20047, CODE_FOR_vec_perm_constv4di },
  { 0xc2004f, CODE_FOR_vec_perm_constv4sf },
  { 0xc20050, CODE_FOR_vec_perm_constv2df },
  { 0xc20051, CODE_FOR_vec_perm_constv8sf },
  { 0xc20052, CODE_FOR_vec_perm_constv4df },
  { 0xc3003f, CODE_FOR_vec_permv16qi },
  { 0xc30040, CODE_FOR_vec_permv8hi },
  { 0xc30041, CODE_FOR_vec_permv4si },
  { 0xc30042, CODE_FOR_vec_permv2di },
  { 0xc30044, CODE_FOR_vec_permv32qi },
  { 0xc30045, CODE_FOR_vec_permv16hi },
  { 0xc30046, CODE_FOR_vec_permv8si },
  { 0xc30047, CODE_FOR_vec_permv4di },
  { 0xc3004f, CODE_FOR_vec_permv4sf },
  { 0xc30050, CODE_FOR_vec_permv2df },
  { 0xc30051, CODE_FOR_vec_permv8sf },
  { 0xc30052, CODE_FOR_vec_permv4df },
  { 0xc5003b, CODE_FOR_vec_setv8qi },
  { 0xc5003c, CODE_FOR_vec_setv4hi },
  { 0xc5003d, CODE_FOR_vec_setv2si },
  { 0xc5003f, CODE_FOR_vec_setv16qi },
  { 0xc50040, CODE_FOR_vec_setv8hi },
  { 0xc50041, CODE_FOR_vec_setv4si },
  { 0xc50042, CODE_FOR_vec_setv2di },
  { 0xc50044, CODE_FOR_vec_setv32qi },
  { 0xc50045, CODE_FOR_vec_setv16hi },
  { 0xc50046, CODE_FOR_vec_setv8si },
  { 0xc50047, CODE_FOR_vec_setv4di },
  { 0xc5004e, CODE_FOR_vec_setv2sf },
  { 0xc5004f, CODE_FOR_vec_setv4sf },
  { 0xc50050, CODE_FOR_vec_setv2df },
  { 0xc50051, CODE_FOR_vec_setv8sf },
  { 0xc50052, CODE_FOR_vec_setv4df },
  { 0xc6003f, CODE_FOR_vec_shl_v16qi },
  { 0xc60040, CODE_FOR_vec_shl_v8hi },
  { 0xc60041, CODE_FOR_vec_shl_v4si },
  { 0xc60042, CODE_FOR_vec_shl_v2di },
  { 0xc7003f, CODE_FOR_vec_shr_v16qi },
  { 0xc70040, CODE_FOR_vec_shr_v8hi },
  { 0xc70041, CODE_FOR_vec_shr_v4si },
  { 0xc70042, CODE_FOR_vec_shr_v2di },
  { 0xc80040, CODE_FOR_vec_unpacks_float_hi_v8hi },
  { 0xc80041, CODE_FOR_vec_unpacks_float_hi_v4si },
  { 0xc80045, CODE_FOR_vec_unpacks_float_hi_v16hi },
  { 0xc80046, CODE_FOR_vec_unpacks_float_hi_v8si },
  { 0xc90040, CODE_FOR_vec_unpacks_float_lo_v8hi },
  { 0xc90041, CODE_FOR_vec_unpacks_float_lo_v4si },
  { 0xc90045, CODE_FOR_vec_unpacks_float_lo_v16hi },
  { 0xc90046, CODE_FOR_vec_unpacks_float_lo_v8si },
  { 0xca003f, CODE_FOR_vec_unpacks_hi_v16qi },
  { 0xca0040, CODE_FOR_vec_unpacks_hi_v8hi },
  { 0xca0041, CODE_FOR_vec_unpacks_hi_v4si },
  { 0xca0044, CODE_FOR_vec_unpacks_hi_v32qi },
  { 0xca0045, CODE_FOR_vec_unpacks_hi_v16hi },
  { 0xca0046, CODE_FOR_vec_unpacks_hi_v8si },
  { 0xca004f, CODE_FOR_vec_unpacks_hi_v4sf },
  { 0xca0051, CODE_FOR_vec_unpacks_hi_v8sf },
  { 0xcb003f, CODE_FOR_vec_unpacks_lo_v16qi },
  { 0xcb0040, CODE_FOR_vec_unpacks_lo_v8hi },
  { 0xcb0041, CODE_FOR_vec_unpacks_lo_v4si },
  { 0xcb0044, CODE_FOR_vec_unpacks_lo_v32qi },
  { 0xcb0045, CODE_FOR_vec_unpacks_lo_v16hi },
  { 0xcb0046, CODE_FOR_vec_unpacks_lo_v8si },
  { 0xcb004f, CODE_FOR_vec_unpacks_lo_v4sf },
  { 0xcb0051, CODE_FOR_vec_unpacks_lo_v8sf },
  { 0xcc0040, CODE_FOR_vec_unpacku_float_hi_v8hi },
  { 0xcc0041, CODE_FOR_vec_unpacku_float_hi_v4si },
  { 0xcc0045, CODE_FOR_vec_unpacku_float_hi_v16hi },
  { 0xcc0046, CODE_FOR_vec_unpacku_float_hi_v8si },
  { 0xcd0040, CODE_FOR_vec_unpacku_float_lo_v8hi },
  { 0xcd0041, CODE_FOR_vec_unpacku_float_lo_v4si },
  { 0xcd0045, CODE_FOR_vec_unpacku_float_lo_v16hi },
  { 0xcd0046, CODE_FOR_vec_unpacku_float_lo_v8si },
  { 0xce003f, CODE_FOR_vec_unpacku_hi_v16qi },
  { 0xce0040, CODE_FOR_vec_unpacku_hi_v8hi },
  { 0xce0041, CODE_FOR_vec_unpacku_hi_v4si },
  { 0xce0044, CODE_FOR_vec_unpacku_hi_v32qi },
  { 0xce0045, CODE_FOR_vec_unpacku_hi_v16hi },
  { 0xce0046, CODE_FOR_vec_unpacku_hi_v8si },
  { 0xcf003f, CODE_FOR_vec_unpacku_lo_v16qi },
  { 0xcf0040, CODE_FOR_vec_unpacku_lo_v8hi },
  { 0xcf0041, CODE_FOR_vec_unpacku_lo_v4si },
  { 0xcf0044, CODE_FOR_vec_unpacku_lo_v32qi },
  { 0xcf0045, CODE_FOR_vec_unpacku_lo_v16hi },
  { 0xcf0046, CODE_FOR_vec_unpacku_lo_v8si },
  { 0xd00041, CODE_FOR_vec_widen_smult_even_v4si },
  { 0xd00046, CODE_FOR_vec_widen_smult_even_v8si },
  { 0xd1003f, CODE_FOR_vec_widen_smult_hi_v16qi },
  { 0xd10040, CODE_FOR_vec_widen_smult_hi_v8hi },
  { 0xd10041, CODE_FOR_vec_widen_smult_hi_v4si },
  { 0xd10044, CODE_FOR_vec_widen_smult_hi_v32qi },
  { 0xd10045, CODE_FOR_vec_widen_smult_hi_v16hi },
  { 0xd10046, CODE_FOR_vec_widen_smult_hi_v8si },
  { 0xd2003f, CODE_FOR_vec_widen_smult_lo_v16qi },
  { 0xd20040, CODE_FOR_vec_widen_smult_lo_v8hi },
  { 0xd20041, CODE_FOR_vec_widen_smult_lo_v4si },
  { 0xd20044, CODE_FOR_vec_widen_smult_lo_v32qi },
  { 0xd20045, CODE_FOR_vec_widen_smult_lo_v16hi },
  { 0xd20046, CODE_FOR_vec_widen_smult_lo_v8si },
  { 0xd30041, CODE_FOR_vec_widen_smult_odd_v4si },
  { 0xd30046, CODE_FOR_vec_widen_smult_odd_v8si },
  { 0xd60041, CODE_FOR_vec_widen_umult_even_v4si },
  { 0xd60046, CODE_FOR_vec_widen_umult_even_v8si },
  { 0xd7003f, CODE_FOR_vec_widen_umult_hi_v16qi },
  { 0xd70040, CODE_FOR_vec_widen_umult_hi_v8hi },
  { 0xd70041, CODE_FOR_vec_widen_umult_hi_v4si },
  { 0xd70044, CODE_FOR_vec_widen_umult_hi_v32qi },
  { 0xd70045, CODE_FOR_vec_widen_umult_hi_v16hi },
  { 0xd70046, CODE_FOR_vec_widen_umult_hi_v8si },
  { 0xd8003f, CODE_FOR_vec_widen_umult_lo_v16qi },
  { 0xd80040, CODE_FOR_vec_widen_umult_lo_v8hi },
  { 0xd80041, CODE_FOR_vec_widen_umult_lo_v4si },
  { 0xd80044, CODE_FOR_vec_widen_umult_lo_v32qi },
  { 0xd80045, CODE_FOR_vec_widen_umult_lo_v16hi },
  { 0xd80046, CODE_FOR_vec_widen_umult_lo_v8si },
  { 0xd90041, CODE_FOR_vec_widen_umult_odd_v4si },
  { 0xd90046, CODE_FOR_vec_widen_umult_odd_v8si },
  { 0xe4000e, CODE_FOR_atomic_addqi },
  { 0xe4000f, CODE_FOR_atomic_addhi },
  { 0xe40010, CODE_FOR_atomic_addsi },
  { 0xe6000e, CODE_FOR_atomic_andqi },
  { 0xe6000f, CODE_FOR_atomic_andhi },
  { 0xe60010, CODE_FOR_atomic_andsi },
  { 0xe7000e, CODE_FOR_atomic_compare_and_swapqi },
  { 0xe7000f, CODE_FOR_atomic_compare_and_swaphi },
  { 0xe70010, CODE_FOR_atomic_compare_and_swapsi },
  { 0xe70011, CODE_FOR_atomic_compare_and_swapdi },
  { 0xe8000e, CODE_FOR_atomic_exchangeqi },
  { 0xe8000f, CODE_FOR_atomic_exchangehi },
  { 0xe80010, CODE_FOR_atomic_exchangesi },
  { 0xe9000e, CODE_FOR_atomic_fetch_addqi },
  { 0xe9000f, CODE_FOR_atomic_fetch_addhi },
  { 0xe90010, CODE_FOR_atomic_fetch_addsi },
  { 0xef000e, CODE_FOR_atomic_loadqi },
  { 0xef000f, CODE_FOR_atomic_loadhi },
  { 0xef0010, CODE_FOR_atomic_loadsi },
  { 0xef0011, CODE_FOR_atomic_loaddi },
  { 0xf3000e, CODE_FOR_atomic_orqi },
  { 0xf3000f, CODE_FOR_atomic_orhi },
  { 0xf30010, CODE_FOR_atomic_orsi },
  { 0xf4000e, CODE_FOR_atomic_storeqi },
  { 0xf4000f, CODE_FOR_atomic_storehi },
  { 0xf40010, CODE_FOR_atomic_storesi },
  { 0xf40011, CODE_FOR_atomic_storedi },
  { 0xf6000e, CODE_FOR_atomic_subqi },
  { 0xf6000f, CODE_FOR_atomic_subhi },
  { 0xf60010, CODE_FOR_atomic_subsi },
  { 0xf8000e, CODE_FOR_atomic_xorqi },
  { 0xf8000f, CODE_FOR_atomic_xorhi },
  { 0xf80010, CODE_FOR_atomic_xorsi },
};

void
init_all_optabs (struct target_optabs *optabs)
{
  bool *ena = optabs->pat_enable;
  ena[0] = HAVE_extendqihi2;
  ena[1] = HAVE_extendqisi2;
  ena[2] = HAVE_extendhisi2;
  ena[3] = HAVE_extendsidi2;
  ena[4] = HAVE_extendsfdf2;
  ena[5] = HAVE_extendsfxf2;
  ena[6] = HAVE_extenddfxf2;
  ena[7] = HAVE_truncdfsf2;
  ena[8] = HAVE_truncxfsf2;
  ena[9] = HAVE_truncxfdf2;
  ena[10] = HAVE_zero_extendqihi2;
  ena[11] = HAVE_zero_extendqisi2;
  ena[12] = HAVE_zero_extendhisi2;
  ena[13] = HAVE_zero_extendsidi2;
  ena[14] = HAVE_floathisf2;
  ena[15] = HAVE_floathidf2;
  ena[16] = HAVE_floathixf2;
  ena[17] = HAVE_floatsisf2;
  ena[18] = HAVE_floatsidf2;
  ena[19] = HAVE_floatsixf2;
  ena[20] = HAVE_floatdisf2;
  ena[21] = HAVE_floatdidf2;
  ena[22] = HAVE_floatdixf2;
  ena[23] = HAVE_floatv4siv4sf2;
  ena[24] = HAVE_floatv4siv4df2;
  ena[25] = HAVE_floatv8siv8sf2;
  ena[26] = HAVE_floatunssisf2;
  ena[27] = HAVE_floatunssidf2;
  ena[28] = HAVE_floatunssixf2;
  ena[29] = HAVE_floatunsv4siv4sf2;
  ena[30] = HAVE_floatunsv8siv8sf2;
  ena[31] = HAVE_lrintsfsi2;
  ena[32] = HAVE_lrintdfsi2;
  ena[33] = HAVE_lrintxfhi2;
  ena[34] = HAVE_lrintxfsi2;
  ena[35] = HAVE_lrintxfdi2;
  ena[36] = HAVE_lroundsfhi2;
  ena[37] = HAVE_lroundsfsi2;
  ena[38] = HAVE_lroundsfdi2;
  ena[39] = HAVE_lrounddfhi2;
  ena[40] = HAVE_lrounddfsi2;
  ena[41] = HAVE_lrounddfdi2;
  ena[42] = HAVE_lroundxfhi2;
  ena[43] = HAVE_lroundxfsi2;
  ena[44] = HAVE_lroundxfdi2;
  ena[45] = HAVE_lfloorsfsi2;
  ena[46] = HAVE_lfloordfsi2;
  ena[47] = HAVE_lfloorxfhi2;
  ena[48] = HAVE_lfloorxfsi2;
  ena[49] = HAVE_lfloorxfdi2;
  ena[50] = HAVE_lceilsfsi2;
  ena[51] = HAVE_lceildfsi2;
  ena[52] = HAVE_lceilxfhi2;
  ena[53] = HAVE_lceilxfsi2;
  ena[54] = HAVE_lceilxfdi2;
  ena[55] = HAVE_fix_truncsfhi2;
  ena[56] = HAVE_fix_truncsfsi2;
  ena[57] = HAVE_fix_truncsfdi2;
  ena[58] = HAVE_fix_truncdfhi2;
  ena[59] = HAVE_fix_truncdfsi2;
  ena[60] = HAVE_fix_truncdfdi2;
  ena[61] = HAVE_fix_truncxfhi2;
  ena[62] = HAVE_fix_truncxfsi2;
  ena[63] = HAVE_fix_truncxfdi2;
  ena[64] = HAVE_fix_truncv4sfv4si2;
  ena[65] = HAVE_fix_truncv8sfv8si2;
  ena[66] = HAVE_fix_truncv4dfv4si2;
  ena[67] = HAVE_fixuns_truncsfhi2;
  ena[68] = HAVE_fixuns_truncsfsi2;
  ena[69] = HAVE_fixuns_truncdfhi2;
  ena[70] = HAVE_fixuns_truncdfsi2;
  ena[71] = HAVE_fixuns_truncv4sfv4si2;
  ena[72] = HAVE_fixuns_truncv8sfv8si2;
  ena[73] = HAVE_mulqihi3;
  ena[74] = HAVE_mulsidi3;
  ena[75] = HAVE_umulqihi3;
  ena[76] = HAVE_umulsidi3;
  ena[77] = HAVE_vcondv16qiv16qi;
  ena[78] = HAVE_vcondv8hiv16qi;
  ena[79] = HAVE_vcondv4siv16qi;
  ena[80] = HAVE_vcondv2div16qi;
  ena[81] = HAVE_vcondv4sfv16qi;
  ena[82] = HAVE_vcondv2dfv16qi;
  ena[83] = HAVE_vcondv16qiv8hi;
  ena[84] = HAVE_vcondv8hiv8hi;
  ena[85] = HAVE_vcondv4siv8hi;
  ena[86] = HAVE_vcondv2div8hi;
  ena[87] = HAVE_vcondv4sfv8hi;
  ena[88] = HAVE_vcondv2dfv8hi;
  ena[89] = HAVE_vcondv16qiv4si;
  ena[90] = HAVE_vcondv8hiv4si;
  ena[91] = HAVE_vcondv4siv4si;
  ena[92] = HAVE_vcondv2div4si;
  ena[93] = HAVE_vcondv4sfv4si;
  ena[94] = HAVE_vcondv2dfv4si;
  ena[95] = HAVE_vcondv2div2di;
  ena[96] = HAVE_vcondv2dfv2di;
  ena[97] = HAVE_vcondv32qiv32qi;
  ena[98] = HAVE_vcondv16hiv32qi;
  ena[99] = HAVE_vcondv8siv32qi;
  ena[100] = HAVE_vcondv4div32qi;
  ena[101] = HAVE_vcondv8sfv32qi;
  ena[102] = HAVE_vcondv4dfv32qi;
  ena[103] = HAVE_vcondv32qiv16hi;
  ena[104] = HAVE_vcondv16hiv16hi;
  ena[105] = HAVE_vcondv8siv16hi;
  ena[106] = HAVE_vcondv4div16hi;
  ena[107] = HAVE_vcondv8sfv16hi;
  ena[108] = HAVE_vcondv4dfv16hi;
  ena[109] = HAVE_vcondv32qiv8si;
  ena[110] = HAVE_vcondv16hiv8si;
  ena[111] = HAVE_vcondv8siv8si;
  ena[112] = HAVE_vcondv4div8si;
  ena[113] = HAVE_vcondv8sfv8si;
  ena[114] = HAVE_vcondv4dfv8si;
  ena[115] = HAVE_vcondv32qiv4di;
  ena[116] = HAVE_vcondv16hiv4di;
  ena[117] = HAVE_vcondv8siv4di;
  ena[118] = HAVE_vcondv4div4di;
  ena[119] = HAVE_vcondv8sfv4di;
  ena[120] = HAVE_vcondv4dfv4di;
  ena[121] = HAVE_vcondv16qiv4sf;
  ena[122] = HAVE_vcondv8hiv4sf;
  ena[123] = HAVE_vcondv4siv4sf;
  ena[124] = HAVE_vcondv2div4sf;
  ena[125] = HAVE_vcondv4sfv4sf;
  ena[126] = HAVE_vcondv2dfv4sf;
  ena[127] = HAVE_vcondv16qiv2df;
  ena[128] = HAVE_vcondv8hiv2df;
  ena[129] = HAVE_vcondv4siv2df;
  ena[130] = HAVE_vcondv2div2df;
  ena[131] = HAVE_vcondv4sfv2df;
  ena[132] = HAVE_vcondv2dfv2df;
  ena[133] = HAVE_vcondv32qiv8sf;
  ena[134] = HAVE_vcondv16hiv8sf;
  ena[135] = HAVE_vcondv8siv8sf;
  ena[136] = HAVE_vcondv4div8sf;
  ena[137] = HAVE_vcondv8sfv8sf;
  ena[138] = HAVE_vcondv4dfv8sf;
  ena[139] = HAVE_vcondv32qiv4df;
  ena[140] = HAVE_vcondv16hiv4df;
  ena[141] = HAVE_vcondv8siv4df;
  ena[142] = HAVE_vcondv4div4df;
  ena[143] = HAVE_vcondv8sfv4df;
  ena[144] = HAVE_vcondv4dfv4df;
  ena[145] = HAVE_vconduv16qiv16qi;
  ena[146] = HAVE_vconduv8hiv16qi;
  ena[147] = HAVE_vconduv4siv16qi;
  ena[148] = HAVE_vconduv2div16qi;
  ena[149] = HAVE_vconduv4sfv16qi;
  ena[150] = HAVE_vconduv2dfv16qi;
  ena[151] = HAVE_vconduv16qiv8hi;
  ena[152] = HAVE_vconduv8hiv8hi;
  ena[153] = HAVE_vconduv4siv8hi;
  ena[154] = HAVE_vconduv2div8hi;
  ena[155] = HAVE_vconduv4sfv8hi;
  ena[156] = HAVE_vconduv2dfv8hi;
  ena[157] = HAVE_vconduv16qiv4si;
  ena[158] = HAVE_vconduv8hiv4si;
  ena[159] = HAVE_vconduv4siv4si;
  ena[160] = HAVE_vconduv2div4si;
  ena[161] = HAVE_vconduv4sfv4si;
  ena[162] = HAVE_vconduv2dfv4si;
  ena[163] = HAVE_vconduv2div2di;
  ena[164] = HAVE_vconduv2dfv2di;
  ena[165] = HAVE_vconduv32qiv32qi;
  ena[166] = HAVE_vconduv16hiv32qi;
  ena[167] = HAVE_vconduv8siv32qi;
  ena[168] = HAVE_vconduv4div32qi;
  ena[169] = HAVE_vconduv8sfv32qi;
  ena[170] = HAVE_vconduv4dfv32qi;
  ena[171] = HAVE_vconduv32qiv16hi;
  ena[172] = HAVE_vconduv16hiv16hi;
  ena[173] = HAVE_vconduv8siv16hi;
  ena[174] = HAVE_vconduv4div16hi;
  ena[175] = HAVE_vconduv8sfv16hi;
  ena[176] = HAVE_vconduv4dfv16hi;
  ena[177] = HAVE_vconduv32qiv8si;
  ena[178] = HAVE_vconduv16hiv8si;
  ena[179] = HAVE_vconduv8siv8si;
  ena[180] = HAVE_vconduv4div8si;
  ena[181] = HAVE_vconduv8sfv8si;
  ena[182] = HAVE_vconduv4dfv8si;
  ena[183] = HAVE_vconduv32qiv4di;
  ena[184] = HAVE_vconduv16hiv4di;
  ena[185] = HAVE_vconduv8siv4di;
  ena[186] = HAVE_vconduv4div4di;
  ena[187] = HAVE_vconduv8sfv4di;
  ena[188] = HAVE_vconduv4dfv4di;
  ena[189] = HAVE_addqi3;
  ena[190] = HAVE_addhi3;
  ena[191] = HAVE_addsi3;
  ena[192] = HAVE_adddi3;
  ena[193] = HAVE_addsf3;
  ena[194] = HAVE_adddf3;
  ena[195] = HAVE_addxf3;
  ena[196] = HAVE_addv16qi3;
  ena[197] = HAVE_addv8hi3;
  ena[198] = HAVE_addv4si3;
  ena[199] = HAVE_addv2di3;
  ena[200] = HAVE_addv32qi3;
  ena[201] = HAVE_addv16hi3;
  ena[202] = HAVE_addv8si3;
  ena[203] = HAVE_addv4di3;
  ena[204] = HAVE_addv4sf3;
  ena[205] = HAVE_addv2df3;
  ena[206] = HAVE_addv8sf3;
  ena[207] = HAVE_addv4df3;
  ena[208] = HAVE_subqi3;
  ena[209] = HAVE_subhi3;
  ena[210] = HAVE_subsi3;
  ena[211] = HAVE_subdi3;
  ena[212] = HAVE_subsf3;
  ena[213] = HAVE_subdf3;
  ena[214] = HAVE_subxf3;
  ena[215] = HAVE_subv16qi3;
  ena[216] = HAVE_subv8hi3;
  ena[217] = HAVE_subv4si3;
  ena[218] = HAVE_subv2di3;
  ena[219] = HAVE_subv32qi3;
  ena[220] = HAVE_subv16hi3;
  ena[221] = HAVE_subv8si3;
  ena[222] = HAVE_subv4di3;
  ena[223] = HAVE_subv4sf3;
  ena[224] = HAVE_subv2df3;
  ena[225] = HAVE_subv8sf3;
  ena[226] = HAVE_subv4df3;
  ena[227] = HAVE_mulqi3;
  ena[228] = HAVE_mulhi3;
  ena[229] = HAVE_mulsi3;
  ena[230] = HAVE_mulsf3;
  ena[231] = HAVE_muldf3;
  ena[232] = HAVE_mulxf3;
  ena[233] = HAVE_mulv16qi3;
  ena[234] = HAVE_mulv8hi3;
  ena[235] = HAVE_mulv4si3;
  ena[236] = HAVE_mulv2di3;
  ena[237] = HAVE_mulv32qi3;
  ena[238] = HAVE_mulv16hi3;
  ena[239] = HAVE_mulv8si3;
  ena[240] = HAVE_mulv4di3;
  ena[241] = HAVE_mulv4sf3;
  ena[242] = HAVE_mulv2df3;
  ena[243] = HAVE_mulv8sf3;
  ena[244] = HAVE_mulv4df3;
  ena[245] = HAVE_divsf3;
  ena[246] = HAVE_divdf3;
  ena[247] = HAVE_divxf3;
  ena[248] = HAVE_divv4sf3;
  ena[249] = HAVE_divv2df3;
  ena[250] = HAVE_divv8sf3;
  ena[251] = HAVE_divv4df3;
  ena[252] = HAVE_divmodqi4;
  ena[253] = HAVE_divmodhi4;
  ena[254] = HAVE_divmodsi4;
  ena[255] = HAVE_udivmodqi4;
  ena[256] = HAVE_udivmodhi4;
  ena[257] = HAVE_udivmodsi4;
  ena[258] = HAVE_andqi3;
  ena[259] = HAVE_andhi3;
  ena[260] = HAVE_andsi3;
  ena[261] = HAVE_andtf3;
  ena[262] = HAVE_andv16qi3;
  ena[263] = HAVE_andv8hi3;
  ena[264] = HAVE_andv4si3;
  ena[265] = HAVE_andv2di3;
  ena[266] = HAVE_andv32qi3;
  ena[267] = HAVE_andv16hi3;
  ena[268] = HAVE_andv8si3;
  ena[269] = HAVE_andv4di3;
  ena[270] = HAVE_andv4sf3;
  ena[271] = HAVE_andv2df3;
  ena[272] = HAVE_andv8sf3;
  ena[273] = HAVE_andv4df3;
  ena[274] = HAVE_iorqi3;
  ena[275] = HAVE_iorhi3;
  ena[276] = HAVE_iorsi3;
  ena[277] = HAVE_iortf3;
  ena[278] = HAVE_iorv16qi3;
  ena[279] = HAVE_iorv8hi3;
  ena[280] = HAVE_iorv4si3;
  ena[281] = HAVE_iorv2di3;
  ena[282] = HAVE_iorv32qi3;
  ena[283] = HAVE_iorv16hi3;
  ena[284] = HAVE_iorv8si3;
  ena[285] = HAVE_iorv4di3;
  ena[286] = HAVE_iorv4sf3;
  ena[287] = HAVE_iorv2df3;
  ena[288] = HAVE_iorv8sf3;
  ena[289] = HAVE_iorv4df3;
  ena[290] = HAVE_xorqi3;
  ena[291] = HAVE_xorhi3;
  ena[292] = HAVE_xorsi3;
  ena[293] = HAVE_xortf3;
  ena[294] = HAVE_xorv16qi3;
  ena[295] = HAVE_xorv8hi3;
  ena[296] = HAVE_xorv4si3;
  ena[297] = HAVE_xorv2di3;
  ena[298] = HAVE_xorv32qi3;
  ena[299] = HAVE_xorv16hi3;
  ena[300] = HAVE_xorv8si3;
  ena[301] = HAVE_xorv4di3;
  ena[302] = HAVE_xorv4sf3;
  ena[303] = HAVE_xorv2df3;
  ena[304] = HAVE_xorv8sf3;
  ena[305] = HAVE_xorv4df3;
  ena[306] = HAVE_ashlqi3;
  ena[307] = HAVE_ashlhi3;
  ena[308] = HAVE_ashlsi3;
  ena[309] = HAVE_ashldi3;
  ena[310] = HAVE_ashlv16qi3;
  ena[311] = HAVE_ashlv8hi3;
  ena[312] = HAVE_ashlv4si3;
  ena[313] = HAVE_ashlv2di3;
  ena[314] = HAVE_ashlv32qi3;
  ena[315] = HAVE_ashlv16hi3;
  ena[316] = HAVE_ashlv8si3;
  ena[317] = HAVE_ashlv4di3;
  ena[318] = HAVE_ashrqi3;
  ena[319] = HAVE_ashrhi3;
  ena[320] = HAVE_ashrsi3;
  ena[321] = HAVE_ashrdi3;
  ena[322] = HAVE_ashrv16qi3;
  ena[323] = HAVE_ashrv8hi3;
  ena[324] = HAVE_ashrv4si3;
  ena[325] = HAVE_ashrv2di3;
  ena[326] = HAVE_ashrv32qi3;
  ena[327] = HAVE_ashrv16hi3;
  ena[328] = HAVE_ashrv8si3;
  ena[329] = HAVE_lshrqi3;
  ena[330] = HAVE_lshrhi3;
  ena[331] = HAVE_lshrsi3;
  ena[332] = HAVE_lshrdi3;
  ena[333] = HAVE_lshrv16qi3;
  ena[334] = HAVE_lshrv8hi3;
  ena[335] = HAVE_lshrv4si3;
  ena[336] = HAVE_lshrv2di3;
  ena[337] = HAVE_lshrv32qi3;
  ena[338] = HAVE_lshrv16hi3;
  ena[339] = HAVE_lshrv8si3;
  ena[340] = HAVE_lshrv4di3;
  ena[341] = HAVE_rotlqi3;
  ena[342] = HAVE_rotlhi3;
  ena[343] = HAVE_rotlsi3;
  ena[344] = HAVE_rotldi3;
  ena[345] = HAVE_rotlv16qi3;
  ena[346] = HAVE_rotlv8hi3;
  ena[347] = HAVE_rotlv4si3;
  ena[348] = HAVE_rotlv2di3;
  ena[349] = HAVE_rotrqi3;
  ena[350] = HAVE_rotrhi3;
  ena[351] = HAVE_rotrsi3;
  ena[352] = HAVE_rotrdi3;
  ena[353] = HAVE_rotrv16qi3;
  ena[354] = HAVE_rotrv8hi3;
  ena[355] = HAVE_rotrv4si3;
  ena[356] = HAVE_rotrv2di3;
  ena[357] = HAVE_vashlv16qi3;
  ena[358] = HAVE_vashlv8hi3;
  ena[359] = HAVE_vashlv4si3;
  ena[360] = HAVE_vashlv2di3;
  ena[361] = HAVE_vashlv8si3;
  ena[362] = HAVE_vashlv4di3;
  ena[363] = HAVE_vashrv16qi3;
  ena[364] = HAVE_vashrv8hi3;
  ena[365] = HAVE_vashrv4si3;
  ena[366] = HAVE_vashrv2di3;
  ena[367] = HAVE_vashrv8si3;
  ena[368] = HAVE_vlshrv16qi3;
  ena[369] = HAVE_vlshrv8hi3;
  ena[370] = HAVE_vlshrv4si3;
  ena[371] = HAVE_vlshrv2di3;
  ena[372] = HAVE_vlshrv8si3;
  ena[373] = HAVE_vlshrv4di3;
  ena[374] = HAVE_vrotlv16qi3;
  ena[375] = HAVE_vrotlv8hi3;
  ena[376] = HAVE_vrotlv4si3;
  ena[377] = HAVE_vrotlv2di3;
  ena[378] = HAVE_vrotrv16qi3;
  ena[379] = HAVE_vrotrv8hi3;
  ena[380] = HAVE_vrotrv4si3;
  ena[381] = HAVE_vrotrv2di3;
  ena[382] = HAVE_sminsf3;
  ena[383] = HAVE_smindf3;
  ena[384] = HAVE_sminv16qi3;
  ena[385] = HAVE_sminv8hi3;
  ena[386] = HAVE_sminv4si3;
  ena[387] = HAVE_sminv2di3;
  ena[388] = HAVE_sminv32qi3;
  ena[389] = HAVE_sminv16hi3;
  ena[390] = HAVE_sminv8si3;
  ena[391] = HAVE_sminv4di3;
  ena[392] = HAVE_sminv4sf3;
  ena[393] = HAVE_sminv2df3;
  ena[394] = HAVE_sminv8sf3;
  ena[395] = HAVE_sminv4df3;
  ena[396] = HAVE_smaxsf3;
  ena[397] = HAVE_smaxdf3;
  ena[398] = HAVE_smaxv16qi3;
  ena[399] = HAVE_smaxv8hi3;
  ena[400] = HAVE_smaxv4si3;
  ena[401] = HAVE_smaxv2di3;
  ena[402] = HAVE_smaxv32qi3;
  ena[403] = HAVE_smaxv16hi3;
  ena[404] = HAVE_smaxv8si3;
  ena[405] = HAVE_smaxv4di3;
  ena[406] = HAVE_smaxv4sf3;
  ena[407] = HAVE_smaxv2df3;
  ena[408] = HAVE_smaxv8sf3;
  ena[409] = HAVE_smaxv4df3;
  ena[410] = HAVE_uminv16qi3;
  ena[411] = HAVE_uminv8hi3;
  ena[412] = HAVE_uminv4si3;
  ena[413] = HAVE_uminv2di3;
  ena[414] = HAVE_uminv32qi3;
  ena[415] = HAVE_uminv16hi3;
  ena[416] = HAVE_uminv8si3;
  ena[417] = HAVE_uminv4di3;
  ena[418] = HAVE_umaxv16qi3;
  ena[419] = HAVE_umaxv8hi3;
  ena[420] = HAVE_umaxv4si3;
  ena[421] = HAVE_umaxv2di3;
  ena[422] = HAVE_umaxv32qi3;
  ena[423] = HAVE_umaxv16hi3;
  ena[424] = HAVE_umaxv8si3;
  ena[425] = HAVE_umaxv4di3;
  ena[426] = HAVE_negqi2;
  ena[427] = HAVE_neghi2;
  ena[428] = HAVE_negsi2;
  ena[429] = HAVE_negdi2;
  ena[430] = HAVE_negsf2;
  ena[431] = HAVE_negdf2;
  ena[432] = HAVE_negxf2;
  ena[433] = HAVE_negtf2;
  ena[434] = HAVE_negv16qi2;
  ena[435] = HAVE_negv8hi2;
  ena[436] = HAVE_negv4si2;
  ena[437] = HAVE_negv2di2;
  ena[438] = HAVE_negv32qi2;
  ena[439] = HAVE_negv16hi2;
  ena[440] = HAVE_negv8si2;
  ena[441] = HAVE_negv4di2;
  ena[442] = HAVE_negv4sf2;
  ena[443] = HAVE_negv2df2;
  ena[444] = HAVE_negv8sf2;
  ena[445] = HAVE_negv4df2;
  ena[446] = HAVE_abssf2;
  ena[447] = HAVE_absdf2;
  ena[448] = HAVE_absxf2;
  ena[449] = HAVE_abstf2;
  ena[450] = HAVE_absv8qi2;
  ena[451] = HAVE_absv4hi2;
  ena[452] = HAVE_absv2si2;
  ena[453] = HAVE_absv16qi2;
  ena[454] = HAVE_absv8hi2;
  ena[455] = HAVE_absv4si2;
  ena[456] = HAVE_absv32qi2;
  ena[457] = HAVE_absv16hi2;
  ena[458] = HAVE_absv8si2;
  ena[459] = HAVE_absv4sf2;
  ena[460] = HAVE_absv2df2;
  ena[461] = HAVE_absv8sf2;
  ena[462] = HAVE_absv4df2;
  ena[463] = HAVE_one_cmplqi2;
  ena[464] = HAVE_one_cmplhi2;
  ena[465] = HAVE_one_cmplsi2;
  ena[466] = HAVE_one_cmplv16qi2;
  ena[467] = HAVE_one_cmplv8hi2;
  ena[468] = HAVE_one_cmplv4si2;
  ena[469] = HAVE_one_cmplv2di2;
  ena[470] = HAVE_one_cmplv32qi2;
  ena[471] = HAVE_one_cmplv16hi2;
  ena[472] = HAVE_one_cmplv8si2;
  ena[473] = HAVE_one_cmplv4di2;
  ena[474] = HAVE_bswapsi2;
  ena[475] = HAVE_ffssi2;
  ena[476] = HAVE_clzhi2;
  ena[477] = HAVE_clzsi2;
  ena[478] = HAVE_ctzhi2;
  ena[479] = HAVE_ctzsi2;
  ena[480] = HAVE_popcounthi2;
  ena[481] = HAVE_popcountsi2;
  ena[482] = HAVE_paritysi2;
  ena[483] = HAVE_paritydi2;
  ena[484] = HAVE_sqrtsf2;
  ena[485] = HAVE_sqrtdf2;
  ena[486] = HAVE_sqrtxf2;
  ena[487] = HAVE_sqrtv4sf2;
  ena[488] = HAVE_sqrtv2df2;
  ena[489] = HAVE_sqrtv8sf2;
  ena[490] = HAVE_sqrtv4df2;
  ena[491] = HAVE_movqi;
  ena[492] = HAVE_movhi;
  ena[493] = HAVE_movsi;
  ena[494] = HAVE_movdi;
  ena[495] = HAVE_movti;
  ena[496] = HAVE_movoi;
  ena[497] = HAVE_movsf;
  ena[498] = HAVE_movdf;
  ena[499] = HAVE_movxf;
  ena[500] = HAVE_movtf;
  ena[501] = HAVE_movcdi;
  ena[502] = HAVE_movv8qi;
  ena[503] = HAVE_movv4hi;
  ena[504] = HAVE_movv2si;
  ena[505] = HAVE_movv1di;
  ena[506] = HAVE_movv16qi;
  ena[507] = HAVE_movv8hi;
  ena[508] = HAVE_movv4si;
  ena[509] = HAVE_movv2di;
  ena[510] = HAVE_movv1ti;
  ena[511] = HAVE_movv32qi;
  ena[512] = HAVE_movv16hi;
  ena[513] = HAVE_movv8si;
  ena[514] = HAVE_movv4di;
  ena[515] = HAVE_movv2ti;
  ena[516] = HAVE_movv2sf;
  ena[517] = HAVE_movv4sf;
  ena[518] = HAVE_movv2df;
  ena[519] = HAVE_movv8sf;
  ena[520] = HAVE_movv4df;
  ena[521] = HAVE_movstrictqi;
  ena[522] = HAVE_movstricthi;
  ena[523] = HAVE_movmisalignv8qi;
  ena[524] = HAVE_movmisalignv4hi;
  ena[525] = HAVE_movmisalignv2si;
  ena[526] = HAVE_movmisalignv1di;
  ena[527] = HAVE_movmisalignv16qi;
  ena[528] = HAVE_movmisalignv8hi;
  ena[529] = HAVE_movmisalignv4si;
  ena[530] = HAVE_movmisalignv2di;
  ena[531] = HAVE_movmisalignv1ti;
  ena[532] = HAVE_movmisalignv32qi;
  ena[533] = HAVE_movmisalignv16hi;
  ena[534] = HAVE_movmisalignv8si;
  ena[535] = HAVE_movmisalignv4di;
  ena[536] = HAVE_movmisalignv2ti;
  ena[537] = HAVE_movmisalignv2sf;
  ena[538] = HAVE_movmisalignv4sf;
  ena[539] = HAVE_movmisalignv2df;
  ena[540] = HAVE_movmisalignv8sf;
  ena[541] = HAVE_movmisalignv4df;
  ena[542] = HAVE_storentsi;
  ena[543] = HAVE_storentsf;
  ena[544] = HAVE_storentdf;
  ena[545] = HAVE_storentv2di;
  ena[546] = HAVE_storentv4di;
  ena[547] = HAVE_storentv4sf;
  ena[548] = HAVE_storentv2df;
  ena[549] = HAVE_storentv8sf;
  ena[550] = HAVE_storentv4df;
  ena[551] = HAVE_pushv8qi1;
  ena[552] = HAVE_pushv4hi1;
  ena[553] = HAVE_pushv2si1;
  ena[554] = HAVE_pushv1di1;
  ena[555] = HAVE_pushv16qi1;
  ena[556] = HAVE_pushv8hi1;
  ena[557] = HAVE_pushv4si1;
  ena[558] = HAVE_pushv2di1;
  ena[559] = HAVE_pushv1ti1;
  ena[560] = HAVE_pushv32qi1;
  ena[561] = HAVE_pushv16hi1;
  ena[562] = HAVE_pushv8si1;
  ena[563] = HAVE_pushv4di1;
  ena[564] = HAVE_pushv2ti1;
  ena[565] = HAVE_pushv2sf1;
  ena[566] = HAVE_pushv4sf1;
  ena[567] = HAVE_pushv2df1;
  ena[568] = HAVE_pushv8sf1;
  ena[569] = HAVE_pushv4df1;
  ena[570] = HAVE_cbranchcc4;
  ena[571] = HAVE_cbranchqi4;
  ena[572] = HAVE_cbranchhi4;
  ena[573] = HAVE_cbranchsi4;
  ena[574] = HAVE_cbranchdi4;
  ena[575] = HAVE_cbranchsf4;
  ena[576] = HAVE_cbranchdf4;
  ena[577] = HAVE_cbranchxf4;
  ena[578] = HAVE_addqicc;
  ena[579] = HAVE_addhicc;
  ena[580] = HAVE_addsicc;
  ena[581] = HAVE_movqicc;
  ena[582] = HAVE_movhicc;
  ena[583] = HAVE_movsicc;
  ena[584] = HAVE_movsfcc;
  ena[585] = HAVE_movdfcc;
  ena[586] = HAVE_movxfcc;
  ena[587] = HAVE_cstorecc4;
  ena[588] = HAVE_cstoreqi4;
  ena[589] = HAVE_cstorehi4;
  ena[590] = HAVE_cstoresi4;
  ena[591] = HAVE_cstoresf4;
  ena[592] = HAVE_cstoredf4;
  ena[593] = HAVE_cstorexf4;
  ena[594] = HAVE_smulsi3_highpart;
  ena[595] = HAVE_smulv8hi3_highpart;
  ena[596] = HAVE_smulv16hi3_highpart;
  ena[597] = HAVE_umulsi3_highpart;
  ena[598] = HAVE_umulv8hi3_highpart;
  ena[599] = HAVE_umulv16hi3_highpart;
  ena[600] = HAVE_cmpstrnsi;
  ena[601] = HAVE_movmemsi;
  ena[602] = HAVE_setmemsi;
  ena[603] = HAVE_strlensi;
  ena[604] = HAVE_strlendi;
  ena[605] = HAVE_fmasf4;
  ena[606] = HAVE_fmadf4;
  ena[607] = HAVE_fmav4sf4;
  ena[608] = HAVE_fmav2df4;
  ena[609] = HAVE_fmav8sf4;
  ena[610] = HAVE_fmav4df4;
  ena[611] = HAVE_fmssf4;
  ena[612] = HAVE_fmsdf4;
  ena[613] = HAVE_fmsv4sf4;
  ena[614] = HAVE_fmsv2df4;
  ena[615] = HAVE_fmsv8sf4;
  ena[616] = HAVE_fmsv4df4;
  ena[617] = HAVE_fnmasf4;
  ena[618] = HAVE_fnmadf4;
  ena[619] = HAVE_fnmav4sf4;
  ena[620] = HAVE_fnmav2df4;
  ena[621] = HAVE_fnmav8sf4;
  ena[622] = HAVE_fnmav4df4;
  ena[623] = HAVE_fnmssf4;
  ena[624] = HAVE_fnmsdf4;
  ena[625] = HAVE_fnmsv4sf4;
  ena[626] = HAVE_fnmsv2df4;
  ena[627] = HAVE_fnmsv8sf4;
  ena[628] = HAVE_fnmsv4df4;
  ena[629] = HAVE_rintsf2;
  ena[630] = HAVE_rintdf2;
  ena[631] = HAVE_rintxf2;
  ena[632] = HAVE_roundsf2;
  ena[633] = HAVE_rounddf2;
  ena[634] = HAVE_roundxf2;
  ena[635] = HAVE_roundv4sf2;
  ena[636] = HAVE_roundv2df2;
  ena[637] = HAVE_roundv8sf2;
  ena[638] = HAVE_roundv4df2;
  ena[639] = HAVE_floorsf2;
  ena[640] = HAVE_floordf2;
  ena[641] = HAVE_floorxf2;
  ena[642] = HAVE_ceilsf2;
  ena[643] = HAVE_ceildf2;
  ena[644] = HAVE_ceilxf2;
  ena[645] = HAVE_btruncsf2;
  ena[646] = HAVE_btruncdf2;
  ena[647] = HAVE_btruncxf2;
  ena[648] = HAVE_nearbyintsf2;
  ena[649] = HAVE_nearbyintdf2;
  ena[650] = HAVE_nearbyintxf2;
  ena[651] = HAVE_acossf2;
  ena[652] = HAVE_acosdf2;
  ena[653] = HAVE_acosxf2;
  ena[654] = HAVE_asinsf2;
  ena[655] = HAVE_asindf2;
  ena[656] = HAVE_asinxf2;
  ena[657] = HAVE_atan2sf3;
  ena[658] = HAVE_atan2df3;
  ena[659] = HAVE_atan2xf3;
  ena[660] = HAVE_atansf2;
  ena[661] = HAVE_atandf2;
  ena[662] = HAVE_atanxf2;
  ena[663] = HAVE_copysignsf3;
  ena[664] = HAVE_copysigndf3;
  ena[665] = HAVE_copysigntf3;
  ena[666] = HAVE_copysignv4sf3;
  ena[667] = HAVE_copysignv2df3;
  ena[668] = HAVE_copysignv8sf3;
  ena[669] = HAVE_copysignv4df3;
  ena[670] = HAVE_exp10sf2;
  ena[671] = HAVE_exp10df2;
  ena[672] = HAVE_exp10xf2;
  ena[673] = HAVE_exp2sf2;
  ena[674] = HAVE_exp2df2;
  ena[675] = HAVE_exp2xf2;
  ena[676] = HAVE_expsf2;
  ena[677] = HAVE_expdf2;
  ena[678] = HAVE_expxf2;
  ena[679] = HAVE_expm1sf2;
  ena[680] = HAVE_expm1df2;
  ena[681] = HAVE_expm1xf2;
  ena[682] = HAVE_fmodsf3;
  ena[683] = HAVE_fmoddf3;
  ena[684] = HAVE_fmodxf3;
  ena[685] = HAVE_ilogbsf2;
  ena[686] = HAVE_ilogbdf2;
  ena[687] = HAVE_ilogbxf2;
  ena[688] = HAVE_ldexpsf3;
  ena[689] = HAVE_ldexpdf3;
  ena[690] = HAVE_ldexpxf3;
  ena[691] = HAVE_log10sf2;
  ena[692] = HAVE_log10df2;
  ena[693] = HAVE_log10xf2;
  ena[694] = HAVE_log1psf2;
  ena[695] = HAVE_log1pdf2;
  ena[696] = HAVE_log1pxf2;
  ena[697] = HAVE_log2sf2;
  ena[698] = HAVE_log2df2;
  ena[699] = HAVE_log2xf2;
  ena[700] = HAVE_logsf2;
  ena[701] = HAVE_logdf2;
  ena[702] = HAVE_logxf2;
  ena[703] = HAVE_logbsf2;
  ena[704] = HAVE_logbdf2;
  ena[705] = HAVE_logbxf2;
  ena[706] = HAVE_remaindersf3;
  ena[707] = HAVE_remainderdf3;
  ena[708] = HAVE_remainderxf3;
  ena[709] = HAVE_scalbsf3;
  ena[710] = HAVE_scalbdf3;
  ena[711] = HAVE_scalbxf3;
  ena[712] = HAVE_signbitsf2;
  ena[713] = HAVE_signbitdf2;
  ena[714] = HAVE_signbitxf2;
  ena[715] = HAVE_significandsf2;
  ena[716] = HAVE_significanddf2;
  ena[717] = HAVE_significandxf2;
  ena[718] = HAVE_sincossf3;
  ena[719] = HAVE_sincosdf3;
  ena[720] = HAVE_sincosxf3;
  ena[721] = HAVE_tansf2;
  ena[722] = HAVE_tandf2;
  ena[723] = HAVE_tanxf2;
  ena[724] = HAVE_reduc_smax_v32qi;
  ena[725] = HAVE_reduc_smax_v16hi;
  ena[726] = HAVE_reduc_smax_v8si;
  ena[727] = HAVE_reduc_smax_v4di;
  ena[728] = HAVE_reduc_smax_v4sf;
  ena[729] = HAVE_reduc_smax_v8sf;
  ena[730] = HAVE_reduc_smax_v4df;
  ena[731] = HAVE_reduc_smin_v32qi;
  ena[732] = HAVE_reduc_smin_v16hi;
  ena[733] = HAVE_reduc_smin_v8si;
  ena[734] = HAVE_reduc_smin_v4di;
  ena[735] = HAVE_reduc_smin_v4sf;
  ena[736] = HAVE_reduc_smin_v8sf;
  ena[737] = HAVE_reduc_smin_v4df;
  ena[738] = HAVE_reduc_splus_v4sf;
  ena[739] = HAVE_reduc_splus_v2df;
  ena[740] = HAVE_reduc_splus_v8sf;
  ena[741] = HAVE_reduc_splus_v4df;
  ena[742] = HAVE_reduc_umax_v32qi;
  ena[743] = HAVE_reduc_umax_v16hi;
  ena[744] = HAVE_reduc_umax_v8si;
  ena[745] = HAVE_reduc_umax_v4di;
  ena[746] = HAVE_reduc_umin_v8hi;
  ena[747] = HAVE_reduc_umin_v32qi;
  ena[748] = HAVE_reduc_umin_v16hi;
  ena[749] = HAVE_reduc_umin_v8si;
  ena[750] = HAVE_reduc_umin_v4di;
  ena[751] = HAVE_sdot_prodv8hi;
  ena[752] = HAVE_sdot_prodv4si;
  ena[753] = HAVE_sdot_prodv16hi;
  ena[754] = HAVE_vec_extractv8qi;
  ena[755] = HAVE_vec_extractv4hi;
  ena[756] = HAVE_vec_extractv2si;
  ena[757] = HAVE_vec_extractv16qi;
  ena[758] = HAVE_vec_extractv8hi;
  ena[759] = HAVE_vec_extractv4si;
  ena[760] = HAVE_vec_extractv2di;
  ena[761] = HAVE_vec_extractv32qi;
  ena[762] = HAVE_vec_extractv16hi;
  ena[763] = HAVE_vec_extractv8si;
  ena[764] = HAVE_vec_extractv4di;
  ena[765] = HAVE_vec_extractv2sf;
  ena[766] = HAVE_vec_extractv4sf;
  ena[767] = HAVE_vec_extractv2df;
  ena[768] = HAVE_vec_extractv8sf;
  ena[769] = HAVE_vec_extractv4df;
  ena[770] = HAVE_vec_initv8qi;
  ena[771] = HAVE_vec_initv4hi;
  ena[772] = HAVE_vec_initv2si;
  ena[773] = HAVE_vec_initv16qi;
  ena[774] = HAVE_vec_initv8hi;
  ena[775] = HAVE_vec_initv4si;
  ena[776] = HAVE_vec_initv2di;
  ena[777] = HAVE_vec_initv32qi;
  ena[778] = HAVE_vec_initv16hi;
  ena[779] = HAVE_vec_initv8si;
  ena[780] = HAVE_vec_initv4di;
  ena[781] = HAVE_vec_initv2sf;
  ena[782] = HAVE_vec_initv4sf;
  ena[783] = HAVE_vec_initv2df;
  ena[784] = HAVE_vec_initv8sf;
  ena[785] = HAVE_vec_initv4df;
  ena[786] = HAVE_vec_pack_sfix_trunc_v2df;
  ena[787] = HAVE_vec_pack_sfix_trunc_v4df;
  ena[788] = HAVE_vec_pack_trunc_v8hi;
  ena[789] = HAVE_vec_pack_trunc_v4si;
  ena[790] = HAVE_vec_pack_trunc_v2di;
  ena[791] = HAVE_vec_pack_trunc_v16hi;
  ena[792] = HAVE_vec_pack_trunc_v8si;
  ena[793] = HAVE_vec_pack_trunc_v4di;
  ena[794] = HAVE_vec_pack_trunc_v2df;
  ena[795] = HAVE_vec_pack_trunc_v4df;
  ena[796] = HAVE_vec_pack_ufix_trunc_v2df;
  ena[797] = HAVE_vec_pack_ufix_trunc_v4df;
  ena[798] = HAVE_vec_perm_constv16qi;
  ena[799] = HAVE_vec_perm_constv8hi;
  ena[800] = HAVE_vec_perm_constv4si;
  ena[801] = HAVE_vec_perm_constv2di;
  ena[802] = HAVE_vec_perm_constv32qi;
  ena[803] = HAVE_vec_perm_constv16hi;
  ena[804] = HAVE_vec_perm_constv8si;
  ena[805] = HAVE_vec_perm_constv4di;
  ena[806] = HAVE_vec_perm_constv4sf;
  ena[807] = HAVE_vec_perm_constv2df;
  ena[808] = HAVE_vec_perm_constv8sf;
  ena[809] = HAVE_vec_perm_constv4df;
  ena[810] = HAVE_vec_permv16qi;
  ena[811] = HAVE_vec_permv8hi;
  ena[812] = HAVE_vec_permv4si;
  ena[813] = HAVE_vec_permv2di;
  ena[814] = HAVE_vec_permv32qi;
  ena[815] = HAVE_vec_permv16hi;
  ena[816] = HAVE_vec_permv8si;
  ena[817] = HAVE_vec_permv4di;
  ena[818] = HAVE_vec_permv4sf;
  ena[819] = HAVE_vec_permv2df;
  ena[820] = HAVE_vec_permv8sf;
  ena[821] = HAVE_vec_permv4df;
  ena[822] = HAVE_vec_setv8qi;
  ena[823] = HAVE_vec_setv4hi;
  ena[824] = HAVE_vec_setv2si;
  ena[825] = HAVE_vec_setv16qi;
  ena[826] = HAVE_vec_setv8hi;
  ena[827] = HAVE_vec_setv4si;
  ena[828] = HAVE_vec_setv2di;
  ena[829] = HAVE_vec_setv32qi;
  ena[830] = HAVE_vec_setv16hi;
  ena[831] = HAVE_vec_setv8si;
  ena[832] = HAVE_vec_setv4di;
  ena[833] = HAVE_vec_setv2sf;
  ena[834] = HAVE_vec_setv4sf;
  ena[835] = HAVE_vec_setv2df;
  ena[836] = HAVE_vec_setv8sf;
  ena[837] = HAVE_vec_setv4df;
  ena[838] = HAVE_vec_shl_v16qi;
  ena[839] = HAVE_vec_shl_v8hi;
  ena[840] = HAVE_vec_shl_v4si;
  ena[841] = HAVE_vec_shl_v2di;
  ena[842] = HAVE_vec_shr_v16qi;
  ena[843] = HAVE_vec_shr_v8hi;
  ena[844] = HAVE_vec_shr_v4si;
  ena[845] = HAVE_vec_shr_v2di;
  ena[846] = HAVE_vec_unpacks_float_hi_v8hi;
  ena[847] = HAVE_vec_unpacks_float_hi_v4si;
  ena[848] = HAVE_vec_unpacks_float_hi_v16hi;
  ena[849] = HAVE_vec_unpacks_float_hi_v8si;
  ena[850] = HAVE_vec_unpacks_float_lo_v8hi;
  ena[851] = HAVE_vec_unpacks_float_lo_v4si;
  ena[852] = HAVE_vec_unpacks_float_lo_v16hi;
  ena[853] = HAVE_vec_unpacks_float_lo_v8si;
  ena[854] = HAVE_vec_unpacks_hi_v16qi;
  ena[855] = HAVE_vec_unpacks_hi_v8hi;
  ena[856] = HAVE_vec_unpacks_hi_v4si;
  ena[857] = HAVE_vec_unpacks_hi_v32qi;
  ena[858] = HAVE_vec_unpacks_hi_v16hi;
  ena[859] = HAVE_vec_unpacks_hi_v8si;
  ena[860] = HAVE_vec_unpacks_hi_v4sf;
  ena[861] = HAVE_vec_unpacks_hi_v8sf;
  ena[862] = HAVE_vec_unpacks_lo_v16qi;
  ena[863] = HAVE_vec_unpacks_lo_v8hi;
  ena[864] = HAVE_vec_unpacks_lo_v4si;
  ena[865] = HAVE_vec_unpacks_lo_v32qi;
  ena[866] = HAVE_vec_unpacks_lo_v16hi;
  ena[867] = HAVE_vec_unpacks_lo_v8si;
  ena[868] = HAVE_vec_unpacks_lo_v4sf;
  ena[869] = HAVE_vec_unpacks_lo_v8sf;
  ena[870] = HAVE_vec_unpacku_float_hi_v8hi;
  ena[871] = HAVE_vec_unpacku_float_hi_v4si;
  ena[872] = HAVE_vec_unpacku_float_hi_v16hi;
  ena[873] = HAVE_vec_unpacku_float_hi_v8si;
  ena[874] = HAVE_vec_unpacku_float_lo_v8hi;
  ena[875] = HAVE_vec_unpacku_float_lo_v4si;
  ena[876] = HAVE_vec_unpacku_float_lo_v16hi;
  ena[877] = HAVE_vec_unpacku_float_lo_v8si;
  ena[878] = HAVE_vec_unpacku_hi_v16qi;
  ena[879] = HAVE_vec_unpacku_hi_v8hi;
  ena[880] = HAVE_vec_unpacku_hi_v4si;
  ena[881] = HAVE_vec_unpacku_hi_v32qi;
  ena[882] = HAVE_vec_unpacku_hi_v16hi;
  ena[883] = HAVE_vec_unpacku_hi_v8si;
  ena[884] = HAVE_vec_unpacku_lo_v16qi;
  ena[885] = HAVE_vec_unpacku_lo_v8hi;
  ena[886] = HAVE_vec_unpacku_lo_v4si;
  ena[887] = HAVE_vec_unpacku_lo_v32qi;
  ena[888] = HAVE_vec_unpacku_lo_v16hi;
  ena[889] = HAVE_vec_unpacku_lo_v8si;
  ena[890] = HAVE_vec_widen_smult_even_v4si;
  ena[891] = HAVE_vec_widen_smult_even_v8si;
  ena[892] = HAVE_vec_widen_smult_hi_v16qi;
  ena[893] = HAVE_vec_widen_smult_hi_v8hi;
  ena[894] = HAVE_vec_widen_smult_hi_v4si;
  ena[895] = HAVE_vec_widen_smult_hi_v32qi;
  ena[896] = HAVE_vec_widen_smult_hi_v16hi;
  ena[897] = HAVE_vec_widen_smult_hi_v8si;
  ena[898] = HAVE_vec_widen_smult_lo_v16qi;
  ena[899] = HAVE_vec_widen_smult_lo_v8hi;
  ena[900] = HAVE_vec_widen_smult_lo_v4si;
  ena[901] = HAVE_vec_widen_smult_lo_v32qi;
  ena[902] = HAVE_vec_widen_smult_lo_v16hi;
  ena[903] = HAVE_vec_widen_smult_lo_v8si;
  ena[904] = HAVE_vec_widen_smult_odd_v4si;
  ena[905] = HAVE_vec_widen_smult_odd_v8si;
  ena[906] = HAVE_vec_widen_umult_even_v4si;
  ena[907] = HAVE_vec_widen_umult_even_v8si;
  ena[908] = HAVE_vec_widen_umult_hi_v16qi;
  ena[909] = HAVE_vec_widen_umult_hi_v8hi;
  ena[910] = HAVE_vec_widen_umult_hi_v4si;
  ena[911] = HAVE_vec_widen_umult_hi_v32qi;
  ena[912] = HAVE_vec_widen_umult_hi_v16hi;
  ena[913] = HAVE_vec_widen_umult_hi_v8si;
  ena[914] = HAVE_vec_widen_umult_lo_v16qi;
  ena[915] = HAVE_vec_widen_umult_lo_v8hi;
  ena[916] = HAVE_vec_widen_umult_lo_v4si;
  ena[917] = HAVE_vec_widen_umult_lo_v32qi;
  ena[918] = HAVE_vec_widen_umult_lo_v16hi;
  ena[919] = HAVE_vec_widen_umult_lo_v8si;
  ena[920] = HAVE_vec_widen_umult_odd_v4si;
  ena[921] = HAVE_vec_widen_umult_odd_v8si;
  ena[922] = HAVE_atomic_addqi;
  ena[923] = HAVE_atomic_addhi;
  ena[924] = HAVE_atomic_addsi;
  ena[925] = HAVE_atomic_andqi;
  ena[926] = HAVE_atomic_andhi;
  ena[927] = HAVE_atomic_andsi;
  ena[928] = HAVE_atomic_compare_and_swapqi;
  ena[929] = HAVE_atomic_compare_and_swaphi;
  ena[930] = HAVE_atomic_compare_and_swapsi;
  ena[931] = HAVE_atomic_compare_and_swapdi;
  ena[932] = HAVE_atomic_exchangeqi;
  ena[933] = HAVE_atomic_exchangehi;
  ena[934] = HAVE_atomic_exchangesi;
  ena[935] = HAVE_atomic_fetch_addqi;
  ena[936] = HAVE_atomic_fetch_addhi;
  ena[937] = HAVE_atomic_fetch_addsi;
  ena[938] = HAVE_atomic_loadqi;
  ena[939] = HAVE_atomic_loadhi;
  ena[940] = HAVE_atomic_loadsi;
  ena[941] = HAVE_atomic_loaddi;
  ena[942] = HAVE_atomic_orqi;
  ena[943] = HAVE_atomic_orhi;
  ena[944] = HAVE_atomic_orsi;
  ena[945] = HAVE_atomic_storeqi;
  ena[946] = HAVE_atomic_storehi;
  ena[947] = HAVE_atomic_storesi;
  ena[948] = HAVE_atomic_storedi;
  ena[949] = HAVE_atomic_subqi;
  ena[950] = HAVE_atomic_subhi;
  ena[951] = HAVE_atomic_subsi;
  ena[952] = HAVE_atomic_xorqi;
  ena[953] = HAVE_atomic_xorhi;
  ena[954] = HAVE_atomic_xorsi;
}

static int
lookup_handler (unsigned scode)
{
  int l = 0, h = ARRAY_SIZE (pats), m;
  while (h > l)
    {
      m = (h + l) / 2;
      if (scode == pats[m].scode)
        return m;
      else if (scode < pats[m].scode)
        h = m;
      else
        l = m + 1;
    }
  return -1;
}

enum insn_code
raw_optab_handler (unsigned scode)
{
  int i = lookup_handler (scode);
  return (i >= 0 && this_fn_optabs->pat_enable[i]
          ? pats[i].icode : CODE_FOR_nothing);
}

bool
swap_optab_enable (optab op, enum machine_mode m, bool set)
{
  unsigned scode = (op << 16) | m;
  int i = lookup_handler (scode);
  if (i >= 0)
    {
      bool ret = this_fn_optabs->pat_enable[i];
      this_fn_optabs->pat_enable[i] = set;
      return ret;
    }
  else
    {
      gcc_assert (!set);
      return false;
    }
}

const struct convert_optab_libcall_d convlib_def[NUM_CONVLIB_OPTABS] = {
  { "extend", gen_extend_conv_libfunc },
  { "trunc", gen_trunc_conv_libfunc },
  { NULL, NULL },
  { "fix", gen_fp_to_int_conv_libfunc },
  { "fixuns", gen_fp_to_int_conv_libfunc },
  { "float", gen_int_to_fp_conv_libfunc },
  { NULL, gen_ufloat_conv_libfunc },
  { "lrint", gen_int_to_fp_nondecimal_conv_libfunc },
  { "lround", gen_int_to_fp_nondecimal_conv_libfunc },
  { "lfloor", gen_int_to_fp_nondecimal_conv_libfunc },
  { "lceil", gen_int_to_fp_nondecimal_conv_libfunc },
  { "fract", gen_fract_conv_libfunc },
  { "fractuns", gen_fractuns_conv_libfunc },
  { "satfract", gen_satfract_conv_libfunc },
  { "satfractuns", gen_satfractuns_conv_libfunc },
};

const struct optab_libcall_d normlib_def[NUM_NORMLIB_OPTABS] = {
  { '3', "add", gen_int_fp_fixed_libfunc },
  { '3', "add", gen_intv_fp_libfunc },
  { '3', "ssadd", gen_signed_fixed_libfunc },
  { '3', "usadd", gen_unsigned_fixed_libfunc },
  { '3', "sub", gen_int_fp_fixed_libfunc },
  { '3', "sub", gen_intv_fp_libfunc },
  { '3', "sssub", gen_signed_fixed_libfunc },
  { '3', "ussub", gen_unsigned_fixed_libfunc },
  { '3', "mul", gen_int_fp_fixed_libfunc },
  { '3', "mul", gen_intv_fp_libfunc },
  { '3', "ssmul", gen_signed_fixed_libfunc },
  { '3', "usmul", gen_unsigned_fixed_libfunc },
  { '3', "div", gen_int_fp_signed_fixed_libfunc },
  { '3', "divv", gen_int_libfunc },
  { '3', "ssdiv", gen_signed_fixed_libfunc },
  { '3', "udiv", gen_int_unsigned_fixed_libfunc },
  { '3', "usdiv", gen_unsigned_fixed_libfunc },
  { '4', "divmod", gen_int_libfunc },
  { '4', "udivmod", gen_int_libfunc },
  { '3', "mod", gen_int_libfunc },
  { '3', "umod", gen_int_libfunc },
  { '2', "ftrunc", gen_fp_libfunc },
  { '3', "and", gen_int_libfunc },
  { '3', "ior", gen_int_libfunc },
  { '3', "xor", gen_int_libfunc },
  { '3', "ashl", gen_int_fixed_libfunc },
  { '3', "ssashl", gen_signed_fixed_libfunc },
  { '3', "usashl", gen_unsigned_fixed_libfunc },
  { '3', "ashr", gen_int_signed_fixed_libfunc },
  { '3', "lshr", gen_int_unsigned_fixed_libfunc },
  { '\0', NULL, NULL },
  { '\0', NULL, NULL },
  { '\0', NULL, NULL },
  { '\0', NULL, NULL },
  { '\0', NULL, NULL },
  { '\0', NULL, NULL },
  { '\0', NULL, NULL },
  { '3', "min", gen_int_fp_libfunc },
  { '3', "max", gen_int_fp_libfunc },
  { '3', "umin", gen_int_libfunc },
  { '3', "umax", gen_int_libfunc },
  { '2', "neg", gen_int_fp_fixed_libfunc },
  { '2', "neg", gen_intv_fp_libfunc },
  { '2', "ssneg", gen_signed_fixed_libfunc },
  { '2', "usneg", gen_unsigned_fixed_libfunc },
  { '\0', NULL, NULL },
  { '\0', NULL, NULL },
  { '2', "one_cmpl", gen_int_libfunc },
  { '\0', NULL, NULL },
  { '2', "ffs", gen_int_libfunc },
  { '2', "clz", gen_int_libfunc },
  { '2', "ctz", gen_int_libfunc },
  { '2', "clrsb", gen_int_libfunc },
  { '2', "popcount", gen_int_libfunc },
  { '2', "parity", gen_int_libfunc },
  { '2', "cmp", gen_int_fp_fixed_libfunc },
  { '2', "ucmp", gen_int_libfunc },
  { '2', "eq", gen_fp_libfunc },
  { '2', "ne", gen_fp_libfunc },
  { '2', "gt", gen_fp_libfunc },
  { '2', "ge", gen_fp_libfunc },
  { '2', "lt", gen_fp_libfunc },
  { '2', "le", gen_fp_libfunc },
  { '2', "unord", gen_fp_libfunc },
  { '2', "powi", gen_fp_libfunc },
  { '\0', NULL, NULL },
  { '\0', NULL, NULL },
  { '\0', NULL, NULL },
  { '\0', NULL, NULL },
  { '\0', NULL, NULL },
  { '\0', NULL, NULL },
  { '\0', NULL, NULL },
  { '\0', NULL, NULL },
  { '\0', NULL, NULL },
  { '\0', NULL, NULL },
  { '\0', NULL, NULL },
  { '\0', NULL, NULL },
  { '\0', NULL, NULL },
  { '\0', NULL, NULL },
  { '\0', NULL, NULL },
};

enum rtx_code const optab_to_code_[NUM_OPTABS] = {
  UNKNOWN,
  SIGN_EXTEND,
  TRUNCATE,
  ZERO_EXTEND,
  FIX,
  UNSIGNED_FIX,
  FLOAT,
  UNSIGNED_FLOAT,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  FRACT_CONVERT,
  UNSIGNED_FRACT_CONVERT,
  SAT_FRACT,
  UNSIGNED_SAT_FRACT,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  PLUS,
  PLUS,
  SS_PLUS,
  US_PLUS,
  MINUS,
  MINUS,
  SS_MINUS,
  US_MINUS,
  MULT,
  MULT,
  SS_MULT,
  US_MULT,
  DIV,
  DIV,
  SS_DIV,
  UDIV,
  US_DIV,
  UNKNOWN,
  UNKNOWN,
  MOD,
  UMOD,
  UNKNOWN,
  AND,
  IOR,
  XOR,
  ASHIFT,
  SS_ASHIFT,
  US_ASHIFT,
  ASHIFTRT,
  LSHIFTRT,
  ROTATE,
  ROTATERT,
  ASHIFT,
  ASHIFTRT,
  LSHIFTRT,
  ROTATE,
  ROTATERT,
  SMIN,
  SMAX,
  UMIN,
  UMAX,
  NEG,
  NEG,
  SS_NEG,
  US_NEG,
  ABS,
  ABS,
  NOT,
  BSWAP,
  FFS,
  CLZ,
  CTZ,
  CLRSB,
  POPCOUNT,
  PARITY,
  UNKNOWN,
  UNKNOWN,
  EQ,
  NE,
  GT,
  GE,
  LT,
  LE,
  UNORDERED,
  UNKNOWN,
  SQRT,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  SET,
  STRICT_LOW_PART,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  COMPARE,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  FMA,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
};

const optab code_to_optab_[NUM_RTX_CODE] = {
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  mov_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  movstrict_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  cbranch_optab,
  add_optab,
  sub_optab,
  neg_optab,
  smul_optab,
  ssmul_optab,
  usmul_optab,
  sdiv_optab,
  ssdiv_optab,
  usdiv_optab,
  smod_optab,
  udiv_optab,
  umod_optab,
  and_optab,
  ior_optab,
  xor_optab,
  one_cmpl_optab,
  ashl_optab,
  rotl_optab,
  ashr_optab,
  lshr_optab,
  rotr_optab,
  smin_optab,
  smax_optab,
  umin_optab,
  umax_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  ne_optab,
  eq_optab,
  ge_optab,
  gt_optab,
  le_optab,
  lt_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unord_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  abs_optab,
  sqrt_optab,
  bswap_optab,
  ffs_optab,
  clrsb_optab,
  clz_optab,
  ctz_optab,
  popcount_optab,
  parity_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  ssadd_optab,
  usadd_optab,
  sssub_optab,
  ssneg_optab,
  usneg_optab,
  unknown_optab,
  ssashl_optab,
  usashl_optab,
  ussub_optab,
  unknown_optab,
  unknown_optab,
  fma_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
};

