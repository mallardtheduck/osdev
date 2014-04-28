/* Generated automatically from machmode.def and config/i386/i386-modes.def
   by genmodes.  */

#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "tm.h"
#include "machmode.h"
#include "real.h"

const char *const mode_name[NUM_MACHINE_MODES] =
{
  "VOID",
  "BLK",
  "CC",
  "CCGC",
  "CCGOC",
  "CCNO",
  "CCA",
  "CCC",
  "CCO",
  "CCS",
  "CCZ",
  "CCFP",
  "CCFPU",
  "BI",
  "QI",
  "HI",
  "SI",
  "DI",
  "TI",
  "OI",
  "QQ",
  "HQ",
  "SQ",
  "DQ",
  "TQ",
  "UQQ",
  "UHQ",
  "USQ",
  "UDQ",
  "UTQ",
  "HA",
  "SA",
  "DA",
  "TA",
  "UHA",
  "USA",
  "UDA",
  "UTA",
  "SF",
  "DF",
  "XF",
  "TF",
  "SD",
  "DD",
  "TD",
  "CQI",
  "CHI",
  "CSI",
  "CDI",
  "CTI",
  "COI",
  "SC",
  "DC",
  "XC",
  "TC",
  "V2QI",
  "V4QI",
  "V2HI",
  "V1SI",
  "V8QI",
  "V4HI",
  "V2SI",
  "V1DI",
  "V16QI",
  "V8HI",
  "V4SI",
  "V2DI",
  "V1TI",
  "V32QI",
  "V16HI",
  "V8SI",
  "V4DI",
  "V2TI",
  "V64QI",
  "V32HI",
  "V16SI",
  "V8DI",
  "V4TI",
  "V2SF",
  "V4SF",
  "V2DF",
  "V8SF",
  "V4DF",
  "V2TF",
  "V16SF",
  "V8DF",
  "V4TF",
};

const unsigned char mode_class[NUM_MACHINE_MODES] =
{
  MODE_RANDOM,             /* VOID */
  MODE_RANDOM,             /* BLK */
  MODE_CC,                 /* CC */
  MODE_CC,                 /* CCGC */
  MODE_CC,                 /* CCGOC */
  MODE_CC,                 /* CCNO */
  MODE_CC,                 /* CCA */
  MODE_CC,                 /* CCC */
  MODE_CC,                 /* CCO */
  MODE_CC,                 /* CCS */
  MODE_CC,                 /* CCZ */
  MODE_CC,                 /* CCFP */
  MODE_CC,                 /* CCFPU */
  MODE_INT,                /* BI */
  MODE_INT,                /* QI */
  MODE_INT,                /* HI */
  MODE_INT,                /* SI */
  MODE_INT,                /* DI */
  MODE_INT,                /* TI */
  MODE_INT,                /* OI */
  MODE_FRACT,              /* QQ */
  MODE_FRACT,              /* HQ */
  MODE_FRACT,              /* SQ */
  MODE_FRACT,              /* DQ */
  MODE_FRACT,              /* TQ */
  MODE_UFRACT,             /* UQQ */
  MODE_UFRACT,             /* UHQ */
  MODE_UFRACT,             /* USQ */
  MODE_UFRACT,             /* UDQ */
  MODE_UFRACT,             /* UTQ */
  MODE_ACCUM,              /* HA */
  MODE_ACCUM,              /* SA */
  MODE_ACCUM,              /* DA */
  MODE_ACCUM,              /* TA */
  MODE_UACCUM,             /* UHA */
  MODE_UACCUM,             /* USA */
  MODE_UACCUM,             /* UDA */
  MODE_UACCUM,             /* UTA */
  MODE_FLOAT,              /* SF */
  MODE_FLOAT,              /* DF */
  MODE_FLOAT,              /* XF */
  MODE_FLOAT,              /* TF */
  MODE_DECIMAL_FLOAT,      /* SD */
  MODE_DECIMAL_FLOAT,      /* DD */
  MODE_DECIMAL_FLOAT,      /* TD */
  MODE_COMPLEX_INT,        /* CQI */
  MODE_COMPLEX_INT,        /* CHI */
  MODE_COMPLEX_INT,        /* CSI */
  MODE_COMPLEX_INT,        /* CDI */
  MODE_COMPLEX_INT,        /* CTI */
  MODE_COMPLEX_INT,        /* COI */
  MODE_COMPLEX_FLOAT,      /* SC */
  MODE_COMPLEX_FLOAT,      /* DC */
  MODE_COMPLEX_FLOAT,      /* XC */
  MODE_COMPLEX_FLOAT,      /* TC */
  MODE_VECTOR_INT,         /* V2QI */
  MODE_VECTOR_INT,         /* V4QI */
  MODE_VECTOR_INT,         /* V2HI */
  MODE_VECTOR_INT,         /* V1SI */
  MODE_VECTOR_INT,         /* V8QI */
  MODE_VECTOR_INT,         /* V4HI */
  MODE_VECTOR_INT,         /* V2SI */
  MODE_VECTOR_INT,         /* V1DI */
  MODE_VECTOR_INT,         /* V16QI */
  MODE_VECTOR_INT,         /* V8HI */
  MODE_VECTOR_INT,         /* V4SI */
  MODE_VECTOR_INT,         /* V2DI */
  MODE_VECTOR_INT,         /* V1TI */
  MODE_VECTOR_INT,         /* V32QI */
  MODE_VECTOR_INT,         /* V16HI */
  MODE_VECTOR_INT,         /* V8SI */
  MODE_VECTOR_INT,         /* V4DI */
  MODE_VECTOR_INT,         /* V2TI */
  MODE_VECTOR_INT,         /* V64QI */
  MODE_VECTOR_INT,         /* V32HI */
  MODE_VECTOR_INT,         /* V16SI */
  MODE_VECTOR_INT,         /* V8DI */
  MODE_VECTOR_INT,         /* V4TI */
  MODE_VECTOR_FLOAT,       /* V2SF */
  MODE_VECTOR_FLOAT,       /* V4SF */
  MODE_VECTOR_FLOAT,       /* V2DF */
  MODE_VECTOR_FLOAT,       /* V8SF */
  MODE_VECTOR_FLOAT,       /* V4DF */
  MODE_VECTOR_FLOAT,       /* V2TF */
  MODE_VECTOR_FLOAT,       /* V16SF */
  MODE_VECTOR_FLOAT,       /* V8DF */
  MODE_VECTOR_FLOAT,       /* V4TF */
};

const unsigned short mode_precision[NUM_MACHINE_MODES] =
{
  0,                       /* VOID */
  0,                       /* BLK */
  4*BITS_PER_UNIT,         /* CC */
  4*BITS_PER_UNIT,         /* CCGC */
  4*BITS_PER_UNIT,         /* CCGOC */
  4*BITS_PER_UNIT,         /* CCNO */
  4*BITS_PER_UNIT,         /* CCA */
  4*BITS_PER_UNIT,         /* CCC */
  4*BITS_PER_UNIT,         /* CCO */
  4*BITS_PER_UNIT,         /* CCS */
  4*BITS_PER_UNIT,         /* CCZ */
  4*BITS_PER_UNIT,         /* CCFP */
  4*BITS_PER_UNIT,         /* CCFPU */
  1,                       /* BI */
  1*BITS_PER_UNIT,         /* QI */
  2*BITS_PER_UNIT,         /* HI */
  4*BITS_PER_UNIT,         /* SI */
  8*BITS_PER_UNIT,         /* DI */
  16*BITS_PER_UNIT,        /* TI */
  32*BITS_PER_UNIT,        /* OI */
  1*BITS_PER_UNIT,         /* QQ */
  2*BITS_PER_UNIT,         /* HQ */
  4*BITS_PER_UNIT,         /* SQ */
  8*BITS_PER_UNIT,         /* DQ */
  16*BITS_PER_UNIT,        /* TQ */
  1*BITS_PER_UNIT,         /* UQQ */
  2*BITS_PER_UNIT,         /* UHQ */
  4*BITS_PER_UNIT,         /* USQ */
  8*BITS_PER_UNIT,         /* UDQ */
  16*BITS_PER_UNIT,        /* UTQ */
  2*BITS_PER_UNIT,         /* HA */
  4*BITS_PER_UNIT,         /* SA */
  8*BITS_PER_UNIT,         /* DA */
  16*BITS_PER_UNIT,        /* TA */
  2*BITS_PER_UNIT,         /* UHA */
  4*BITS_PER_UNIT,         /* USA */
  8*BITS_PER_UNIT,         /* UDA */
  16*BITS_PER_UNIT,        /* UTA */
  4*BITS_PER_UNIT,         /* SF */
  8*BITS_PER_UNIT,         /* DF */
  80,                      /* XF */
  16*BITS_PER_UNIT,        /* TF */
  4*BITS_PER_UNIT,         /* SD */
  8*BITS_PER_UNIT,         /* DD */
  16*BITS_PER_UNIT,        /* TD */
  2*BITS_PER_UNIT,         /* CQI */
  4*BITS_PER_UNIT,         /* CHI */
  8*BITS_PER_UNIT,         /* CSI */
  16*BITS_PER_UNIT,        /* CDI */
  32*BITS_PER_UNIT,        /* CTI */
  64*BITS_PER_UNIT,        /* COI */
  8*BITS_PER_UNIT,         /* SC */
  16*BITS_PER_UNIT,        /* DC */
  160,                     /* XC */
  32*BITS_PER_UNIT,        /* TC */
  2*BITS_PER_UNIT,         /* V2QI */
  4*BITS_PER_UNIT,         /* V4QI */
  4*BITS_PER_UNIT,         /* V2HI */
  4*BITS_PER_UNIT,         /* V1SI */
  8*BITS_PER_UNIT,         /* V8QI */
  8*BITS_PER_UNIT,         /* V4HI */
  8*BITS_PER_UNIT,         /* V2SI */
  8*BITS_PER_UNIT,         /* V1DI */
  16*BITS_PER_UNIT,        /* V16QI */
  16*BITS_PER_UNIT,        /* V8HI */
  16*BITS_PER_UNIT,        /* V4SI */
  16*BITS_PER_UNIT,        /* V2DI */
  16*BITS_PER_UNIT,        /* V1TI */
  32*BITS_PER_UNIT,        /* V32QI */
  32*BITS_PER_UNIT,        /* V16HI */
  32*BITS_PER_UNIT,        /* V8SI */
  32*BITS_PER_UNIT,        /* V4DI */
  32*BITS_PER_UNIT,        /* V2TI */
  64*BITS_PER_UNIT,        /* V64QI */
  64*BITS_PER_UNIT,        /* V32HI */
  64*BITS_PER_UNIT,        /* V16SI */
  64*BITS_PER_UNIT,        /* V8DI */
  64*BITS_PER_UNIT,        /* V4TI */
  8*BITS_PER_UNIT,         /* V2SF */
  16*BITS_PER_UNIT,        /* V4SF */
  16*BITS_PER_UNIT,        /* V2DF */
  32*BITS_PER_UNIT,        /* V8SF */
  32*BITS_PER_UNIT,        /* V4DF */
  32*BITS_PER_UNIT,        /* V2TF */
  64*BITS_PER_UNIT,        /* V16SF */
  64*BITS_PER_UNIT,        /* V8DF */
  64*BITS_PER_UNIT,        /* V4TF */
};

unsigned char mode_size[NUM_MACHINE_MODES] = 
{
  0,                       /* VOID */
  0,                       /* BLK */
  4,                       /* CC */
  4,                       /* CCGC */
  4,                       /* CCGOC */
  4,                       /* CCNO */
  4,                       /* CCA */
  4,                       /* CCC */
  4,                       /* CCO */
  4,                       /* CCS */
  4,                       /* CCZ */
  4,                       /* CCFP */
  4,                       /* CCFPU */
  1,                       /* BI */
  1,                       /* QI */
  2,                       /* HI */
  4,                       /* SI */
  8,                       /* DI */
  16,                      /* TI */
  32,                      /* OI */
  1,                       /* QQ */
  2,                       /* HQ */
  4,                       /* SQ */
  8,                       /* DQ */
  16,                      /* TQ */
  1,                       /* UQQ */
  2,                       /* UHQ */
  4,                       /* USQ */
  8,                       /* UDQ */
  16,                      /* UTQ */
  2,                       /* HA */
  4,                       /* SA */
  8,                       /* DA */
  16,                      /* TA */
  2,                       /* UHA */
  4,                       /* USA */
  8,                       /* UDA */
  16,                      /* UTA */
  4,                       /* SF */
  8,                       /* DF */
  12,                      /* XF */
  16,                      /* TF */
  4,                       /* SD */
  8,                       /* DD */
  16,                      /* TD */
  2,                       /* CQI */
  4,                       /* CHI */
  8,                       /* CSI */
  16,                      /* CDI */
  32,                      /* CTI */
  64,                      /* COI */
  8,                       /* SC */
  16,                      /* DC */
  24,                      /* XC */
  32,                      /* TC */
  2,                       /* V2QI */
  4,                       /* V4QI */
  4,                       /* V2HI */
  4,                       /* V1SI */
  8,                       /* V8QI */
  8,                       /* V4HI */
  8,                       /* V2SI */
  8,                       /* V1DI */
  16,                      /* V16QI */
  16,                      /* V8HI */
  16,                      /* V4SI */
  16,                      /* V2DI */
  16,                      /* V1TI */
  32,                      /* V32QI */
  32,                      /* V16HI */
  32,                      /* V8SI */
  32,                      /* V4DI */
  32,                      /* V2TI */
  64,                      /* V64QI */
  64,                      /* V32HI */
  64,                      /* V16SI */
  64,                      /* V8DI */
  64,                      /* V4TI */
  8,                       /* V2SF */
  16,                      /* V4SF */
  16,                      /* V2DF */
  32,                      /* V8SF */
  32,                      /* V4DF */
  32,                      /* V2TF */
  64,                      /* V16SF */
  64,                      /* V8DF */
  64,                      /* V4TF */
};

const unsigned char mode_nunits[NUM_MACHINE_MODES] =
{
  0,                       /* VOID */
  0,                       /* BLK */
  1,                       /* CC */
  1,                       /* CCGC */
  1,                       /* CCGOC */
  1,                       /* CCNO */
  1,                       /* CCA */
  1,                       /* CCC */
  1,                       /* CCO */
  1,                       /* CCS */
  1,                       /* CCZ */
  1,                       /* CCFP */
  1,                       /* CCFPU */
  1,                       /* BI */
  1,                       /* QI */
  1,                       /* HI */
  1,                       /* SI */
  1,                       /* DI */
  1,                       /* TI */
  1,                       /* OI */
  1,                       /* QQ */
  1,                       /* HQ */
  1,                       /* SQ */
  1,                       /* DQ */
  1,                       /* TQ */
  1,                       /* UQQ */
  1,                       /* UHQ */
  1,                       /* USQ */
  1,                       /* UDQ */
  1,                       /* UTQ */
  1,                       /* HA */
  1,                       /* SA */
  1,                       /* DA */
  1,                       /* TA */
  1,                       /* UHA */
  1,                       /* USA */
  1,                       /* UDA */
  1,                       /* UTA */
  1,                       /* SF */
  1,                       /* DF */
  1,                       /* XF */
  1,                       /* TF */
  1,                       /* SD */
  1,                       /* DD */
  1,                       /* TD */
  2,                       /* CQI */
  2,                       /* CHI */
  2,                       /* CSI */
  2,                       /* CDI */
  2,                       /* CTI */
  2,                       /* COI */
  2,                       /* SC */
  2,                       /* DC */
  2,                       /* XC */
  2,                       /* TC */
  2,                       /* V2QI */
  4,                       /* V4QI */
  2,                       /* V2HI */
  1,                       /* V1SI */
  8,                       /* V8QI */
  4,                       /* V4HI */
  2,                       /* V2SI */
  1,                       /* V1DI */
  16,                      /* V16QI */
  8,                       /* V8HI */
  4,                       /* V4SI */
  2,                       /* V2DI */
  1,                       /* V1TI */
  32,                      /* V32QI */
  16,                      /* V16HI */
  8,                       /* V8SI */
  4,                       /* V4DI */
  2,                       /* V2TI */
  64,                      /* V64QI */
  32,                      /* V32HI */
  16,                      /* V16SI */
  8,                       /* V8DI */
  4,                       /* V4TI */
  2,                       /* V2SF */
  4,                       /* V4SF */
  2,                       /* V2DF */
  8,                       /* V8SF */
  4,                       /* V4DF */
  2,                       /* V2TF */
  16,                      /* V16SF */
  8,                       /* V8DF */
  4,                       /* V4TF */
};

const unsigned char mode_wider[NUM_MACHINE_MODES] =
{
  VOIDmode,                /* VOID */
  VOIDmode,                /* BLK */
  VOIDmode,                /* CC */
  VOIDmode,                /* CCGC */
  VOIDmode,                /* CCGOC */
  VOIDmode,                /* CCNO */
  VOIDmode,                /* CCA */
  VOIDmode,                /* CCC */
  VOIDmode,                /* CCO */
  VOIDmode,                /* CCS */
  VOIDmode,                /* CCZ */
  VOIDmode,                /* CCFP */
  VOIDmode,                /* CCFPU */
  QImode,                  /* BI */
  HImode,                  /* QI */
  SImode,                  /* HI */
  DImode,                  /* SI */
  TImode,                  /* DI */
  OImode,                  /* TI */
  VOIDmode,                /* OI */
  HQmode,                  /* QQ */
  SQmode,                  /* HQ */
  DQmode,                  /* SQ */
  TQmode,                  /* DQ */
  VOIDmode,                /* TQ */
  UHQmode,                 /* UQQ */
  USQmode,                 /* UHQ */
  UDQmode,                 /* USQ */
  UTQmode,                 /* UDQ */
  VOIDmode,                /* UTQ */
  SAmode,                  /* HA */
  DAmode,                  /* SA */
  TAmode,                  /* DA */
  VOIDmode,                /* TA */
  USAmode,                 /* UHA */
  UDAmode,                 /* USA */
  UTAmode,                 /* UDA */
  VOIDmode,                /* UTA */
  DFmode,                  /* SF */
  XFmode,                  /* DF */
  TFmode,                  /* XF */
  VOIDmode,                /* TF */
  DDmode,                  /* SD */
  TDmode,                  /* DD */
  VOIDmode,                /* TD */
  CHImode,                 /* CQI */
  CSImode,                 /* CHI */
  CDImode,                 /* CSI */
  CTImode,                 /* CDI */
  COImode,                 /* CTI */
  VOIDmode,                /* COI */
  DCmode,                  /* SC */
  XCmode,                  /* DC */
  TCmode,                  /* XC */
  VOIDmode,                /* TC */
  V4QImode,                /* V2QI */
  V2HImode,                /* V4QI */
  V1SImode,                /* V2HI */
  V8QImode,                /* V1SI */
  V4HImode,                /* V8QI */
  V2SImode,                /* V4HI */
  V1DImode,                /* V2SI */
  V16QImode,               /* V1DI */
  V8HImode,                /* V16QI */
  V4SImode,                /* V8HI */
  V2DImode,                /* V4SI */
  V1TImode,                /* V2DI */
  V32QImode,               /* V1TI */
  V16HImode,               /* V32QI */
  V8SImode,                /* V16HI */
  V4DImode,                /* V8SI */
  V2TImode,                /* V4DI */
  V64QImode,               /* V2TI */
  V32HImode,               /* V64QI */
  V16SImode,               /* V32HI */
  V8DImode,                /* V16SI */
  V4TImode,                /* V8DI */
  VOIDmode,                /* V4TI */
  V4SFmode,                /* V2SF */
  V2DFmode,                /* V4SF */
  V8SFmode,                /* V2DF */
  V4DFmode,                /* V8SF */
  V2TFmode,                /* V4DF */
  V16SFmode,               /* V2TF */
  V8DFmode,                /* V16SF */
  V4TFmode,                /* V8DF */
  VOIDmode,                /* V4TF */
};

const unsigned char mode_2xwider[NUM_MACHINE_MODES] =
{
  VOIDmode,                /* VOID */
  BLKmode,                 /* BLK */
  VOIDmode,                /* CC */
  VOIDmode,                /* CCGC */
  VOIDmode,                /* CCGOC */
  VOIDmode,                /* CCNO */
  VOIDmode,                /* CCA */
  VOIDmode,                /* CCC */
  VOIDmode,                /* CCO */
  VOIDmode,                /* CCS */
  VOIDmode,                /* CCZ */
  VOIDmode,                /* CCFP */
  VOIDmode,                /* CCFPU */
  VOIDmode,                /* BI */
  HImode,                  /* QI */
  SImode,                  /* HI */
  DImode,                  /* SI */
  TImode,                  /* DI */
  OImode,                  /* TI */
  VOIDmode,                /* OI */
  HQmode,                  /* QQ */
  SQmode,                  /* HQ */
  DQmode,                  /* SQ */
  TQmode,                  /* DQ */
  VOIDmode,                /* TQ */
  UHQmode,                 /* UQQ */
  USQmode,                 /* UHQ */
  UDQmode,                 /* USQ */
  UTQmode,                 /* UDQ */
  VOIDmode,                /* UTQ */
  SAmode,                  /* HA */
  DAmode,                  /* SA */
  TAmode,                  /* DA */
  VOIDmode,                /* TA */
  USAmode,                 /* UHA */
  UDAmode,                 /* USA */
  UTAmode,                 /* UDA */
  VOIDmode,                /* UTA */
  DFmode,                  /* SF */
  TFmode,                  /* DF */
  VOIDmode,                /* XF */
  VOIDmode,                /* TF */
  DDmode,                  /* SD */
  TDmode,                  /* DD */
  VOIDmode,                /* TD */
  CHImode,                 /* CQI */
  CSImode,                 /* CHI */
  CDImode,                 /* CSI */
  CTImode,                 /* CDI */
  COImode,                 /* CTI */
  VOIDmode,                /* COI */
  DCmode,                  /* SC */
  TCmode,                  /* DC */
  VOIDmode,                /* XC */
  VOIDmode,                /* TC */
  V4QImode,                /* V2QI */
  V8QImode,                /* V4QI */
  V4HImode,                /* V2HI */
  V2SImode,                /* V1SI */
  V16QImode,               /* V8QI */
  V8HImode,                /* V4HI */
  V4SImode,                /* V2SI */
  V2DImode,                /* V1DI */
  V32QImode,               /* V16QI */
  V16HImode,               /* V8HI */
  V8SImode,                /* V4SI */
  V4DImode,                /* V2DI */
  V2TImode,                /* V1TI */
  V64QImode,               /* V32QI */
  V32HImode,               /* V16HI */
  V16SImode,               /* V8SI */
  V8DImode,                /* V4DI */
  V4TImode,                /* V2TI */
  VOIDmode,                /* V64QI */
  VOIDmode,                /* V32HI */
  VOIDmode,                /* V16SI */
  VOIDmode,                /* V8DI */
  VOIDmode,                /* V4TI */
  V4SFmode,                /* V2SF */
  V8SFmode,                /* V4SF */
  V4DFmode,                /* V2DF */
  V16SFmode,               /* V8SF */
  V8DFmode,                /* V4DF */
  V4TFmode,                /* V2TF */
  VOIDmode,                /* V16SF */
  VOIDmode,                /* V8DF */
  VOIDmode,                /* V4TF */
};

const unsigned HOST_WIDE_INT mode_mask_array[NUM_MACHINE_MODES] =
{
#define MODE_MASK(m)                          \
  ((m) >= HOST_BITS_PER_WIDE_INT)             \
   ? ~(unsigned HOST_WIDE_INT) 0              \
   : ((unsigned HOST_WIDE_INT) 1 << (m)) - 1

  MODE_MASK (0),           /* VOID */
  MODE_MASK (0),           /* BLK */
  MODE_MASK (4*BITS_PER_UNIT),   /* CC */
  MODE_MASK (4*BITS_PER_UNIT),   /* CCGC */
  MODE_MASK (4*BITS_PER_UNIT),   /* CCGOC */
  MODE_MASK (4*BITS_PER_UNIT),   /* CCNO */
  MODE_MASK (4*BITS_PER_UNIT),   /* CCA */
  MODE_MASK (4*BITS_PER_UNIT),   /* CCC */
  MODE_MASK (4*BITS_PER_UNIT),   /* CCO */
  MODE_MASK (4*BITS_PER_UNIT),   /* CCS */
  MODE_MASK (4*BITS_PER_UNIT),   /* CCZ */
  MODE_MASK (4*BITS_PER_UNIT),   /* CCFP */
  MODE_MASK (4*BITS_PER_UNIT),   /* CCFPU */
  MODE_MASK (1),           /* BI */
  MODE_MASK (1*BITS_PER_UNIT),   /* QI */
  MODE_MASK (2*BITS_PER_UNIT),   /* HI */
  MODE_MASK (4*BITS_PER_UNIT),   /* SI */
  MODE_MASK (8*BITS_PER_UNIT),   /* DI */
  MODE_MASK (16*BITS_PER_UNIT),    /* TI */
  MODE_MASK (32*BITS_PER_UNIT),    /* OI */
  MODE_MASK (1*BITS_PER_UNIT),   /* QQ */
  MODE_MASK (2*BITS_PER_UNIT),   /* HQ */
  MODE_MASK (4*BITS_PER_UNIT),   /* SQ */
  MODE_MASK (8*BITS_PER_UNIT),   /* DQ */
  MODE_MASK (16*BITS_PER_UNIT),    /* TQ */
  MODE_MASK (1*BITS_PER_UNIT),   /* UQQ */
  MODE_MASK (2*BITS_PER_UNIT),   /* UHQ */
  MODE_MASK (4*BITS_PER_UNIT),   /* USQ */
  MODE_MASK (8*BITS_PER_UNIT),   /* UDQ */
  MODE_MASK (16*BITS_PER_UNIT),    /* UTQ */
  MODE_MASK (2*BITS_PER_UNIT),   /* HA */
  MODE_MASK (4*BITS_PER_UNIT),   /* SA */
  MODE_MASK (8*BITS_PER_UNIT),   /* DA */
  MODE_MASK (16*BITS_PER_UNIT),    /* TA */
  MODE_MASK (2*BITS_PER_UNIT),   /* UHA */
  MODE_MASK (4*BITS_PER_UNIT),   /* USA */
  MODE_MASK (8*BITS_PER_UNIT),   /* UDA */
  MODE_MASK (16*BITS_PER_UNIT),    /* UTA */
  MODE_MASK (4*BITS_PER_UNIT),   /* SF */
  MODE_MASK (8*BITS_PER_UNIT),   /* DF */
  MODE_MASK (80),          /* XF */
  MODE_MASK (16*BITS_PER_UNIT),    /* TF */
  MODE_MASK (4*BITS_PER_UNIT),   /* SD */
  MODE_MASK (8*BITS_PER_UNIT),   /* DD */
  MODE_MASK (16*BITS_PER_UNIT),    /* TD */
  MODE_MASK (2*BITS_PER_UNIT),   /* CQI */
  MODE_MASK (4*BITS_PER_UNIT),   /* CHI */
  MODE_MASK (8*BITS_PER_UNIT),   /* CSI */
  MODE_MASK (16*BITS_PER_UNIT),    /* CDI */
  MODE_MASK (32*BITS_PER_UNIT),    /* CTI */
  MODE_MASK (64*BITS_PER_UNIT),    /* COI */
  MODE_MASK (8*BITS_PER_UNIT),   /* SC */
  MODE_MASK (16*BITS_PER_UNIT),    /* DC */
  MODE_MASK (160),         /* XC */
  MODE_MASK (32*BITS_PER_UNIT),    /* TC */
  MODE_MASK (2*BITS_PER_UNIT),   /* V2QI */
  MODE_MASK (4*BITS_PER_UNIT),   /* V4QI */
  MODE_MASK (4*BITS_PER_UNIT),   /* V2HI */
  MODE_MASK (4*BITS_PER_UNIT),   /* V1SI */
  MODE_MASK (8*BITS_PER_UNIT),   /* V8QI */
  MODE_MASK (8*BITS_PER_UNIT),   /* V4HI */
  MODE_MASK (8*BITS_PER_UNIT),   /* V2SI */
  MODE_MASK (8*BITS_PER_UNIT),   /* V1DI */
  MODE_MASK (16*BITS_PER_UNIT),    /* V16QI */
  MODE_MASK (16*BITS_PER_UNIT),    /* V8HI */
  MODE_MASK (16*BITS_PER_UNIT),    /* V4SI */
  MODE_MASK (16*BITS_PER_UNIT),    /* V2DI */
  MODE_MASK (16*BITS_PER_UNIT),    /* V1TI */
  MODE_MASK (32*BITS_PER_UNIT),    /* V32QI */
  MODE_MASK (32*BITS_PER_UNIT),    /* V16HI */
  MODE_MASK (32*BITS_PER_UNIT),    /* V8SI */
  MODE_MASK (32*BITS_PER_UNIT),    /* V4DI */
  MODE_MASK (32*BITS_PER_UNIT),    /* V2TI */
  MODE_MASK (64*BITS_PER_UNIT),    /* V64QI */
  MODE_MASK (64*BITS_PER_UNIT),    /* V32HI */
  MODE_MASK (64*BITS_PER_UNIT),    /* V16SI */
  MODE_MASK (64*BITS_PER_UNIT),    /* V8DI */
  MODE_MASK (64*BITS_PER_UNIT),    /* V4TI */
  MODE_MASK (8*BITS_PER_UNIT),   /* V2SF */
  MODE_MASK (16*BITS_PER_UNIT),    /* V4SF */
  MODE_MASK (16*BITS_PER_UNIT),    /* V2DF */
  MODE_MASK (32*BITS_PER_UNIT),    /* V8SF */
  MODE_MASK (32*BITS_PER_UNIT),    /* V4DF */
  MODE_MASK (32*BITS_PER_UNIT),    /* V2TF */
  MODE_MASK (64*BITS_PER_UNIT),    /* V16SF */
  MODE_MASK (64*BITS_PER_UNIT),    /* V8DF */
  MODE_MASK (64*BITS_PER_UNIT),    /* V4TF */
#undef MODE_MASK
};

const unsigned char mode_inner[NUM_MACHINE_MODES] =
{
  VOIDmode,                /* VOID */
  VOIDmode,                /* BLK */
  VOIDmode,                /* CC */
  VOIDmode,                /* CCGC */
  VOIDmode,                /* CCGOC */
  VOIDmode,                /* CCNO */
  VOIDmode,                /* CCA */
  VOIDmode,                /* CCC */
  VOIDmode,                /* CCO */
  VOIDmode,                /* CCS */
  VOIDmode,                /* CCZ */
  VOIDmode,                /* CCFP */
  VOIDmode,                /* CCFPU */
  VOIDmode,                /* BI */
  VOIDmode,                /* QI */
  VOIDmode,                /* HI */
  VOIDmode,                /* SI */
  VOIDmode,                /* DI */
  VOIDmode,                /* TI */
  VOIDmode,                /* OI */
  VOIDmode,                /* QQ */
  VOIDmode,                /* HQ */
  VOIDmode,                /* SQ */
  VOIDmode,                /* DQ */
  VOIDmode,                /* TQ */
  VOIDmode,                /* UQQ */
  VOIDmode,                /* UHQ */
  VOIDmode,                /* USQ */
  VOIDmode,                /* UDQ */
  VOIDmode,                /* UTQ */
  VOIDmode,                /* HA */
  VOIDmode,                /* SA */
  VOIDmode,                /* DA */
  VOIDmode,                /* TA */
  VOIDmode,                /* UHA */
  VOIDmode,                /* USA */
  VOIDmode,                /* UDA */
  VOIDmode,                /* UTA */
  VOIDmode,                /* SF */
  VOIDmode,                /* DF */
  VOIDmode,                /* XF */
  VOIDmode,                /* TF */
  VOIDmode,                /* SD */
  VOIDmode,                /* DD */
  VOIDmode,                /* TD */
  QImode,                  /* CQI */
  HImode,                  /* CHI */
  SImode,                  /* CSI */
  DImode,                  /* CDI */
  TImode,                  /* CTI */
  OImode,                  /* COI */
  SFmode,                  /* SC */
  DFmode,                  /* DC */
  XFmode,                  /* XC */
  TFmode,                  /* TC */
  QImode,                  /* V2QI */
  QImode,                  /* V4QI */
  HImode,                  /* V2HI */
  SImode,                  /* V1SI */
  QImode,                  /* V8QI */
  HImode,                  /* V4HI */
  SImode,                  /* V2SI */
  DImode,                  /* V1DI */
  QImode,                  /* V16QI */
  HImode,                  /* V8HI */
  SImode,                  /* V4SI */
  DImode,                  /* V2DI */
  TImode,                  /* V1TI */
  QImode,                  /* V32QI */
  HImode,                  /* V16HI */
  SImode,                  /* V8SI */
  DImode,                  /* V4DI */
  TImode,                  /* V2TI */
  QImode,                  /* V64QI */
  HImode,                  /* V32HI */
  SImode,                  /* V16SI */
  DImode,                  /* V8DI */
  TImode,                  /* V4TI */
  SFmode,                  /* V2SF */
  SFmode,                  /* V4SF */
  DFmode,                  /* V2DF */
  SFmode,                  /* V8SF */
  DFmode,                  /* V4DF */
  TFmode,                  /* V2TF */
  SFmode,                  /* V16SF */
  DFmode,                  /* V8DF */
  TFmode,                  /* V4TF */
};

unsigned char mode_base_align[NUM_MACHINE_MODES] = 
{
  0,                       /* VOID */
  0,                       /* BLK */
  4,                       /* CC */
  4,                       /* CCGC */
  4,                       /* CCGOC */
  4,                       /* CCNO */
  4,                       /* CCA */
  4,                       /* CCC */
  4,                       /* CCO */
  4,                       /* CCS */
  4,                       /* CCZ */
  4,                       /* CCFP */
  4,                       /* CCFPU */
  1,                       /* BI */
  1,                       /* QI */
  2,                       /* HI */
  4,                       /* SI */
  8,                       /* DI */
  16,                      /* TI */
  32,                      /* OI */
  1,                       /* QQ */
  2,                       /* HQ */
  4,                       /* SQ */
  8,                       /* DQ */
  16,                      /* TQ */
  1,                       /* UQQ */
  2,                       /* UHQ */
  4,                       /* USQ */
  8,                       /* UDQ */
  16,                      /* UTQ */
  2,                       /* HA */
  4,                       /* SA */
  8,                       /* DA */
  16,                      /* TA */
  2,                       /* UHA */
  4,                       /* USA */
  8,                       /* UDA */
  16,                      /* UTA */
  4,                       /* SF */
  8,                       /* DF */
  4,                       /* XF */
  16,                      /* TF */
  4,                       /* SD */
  8,                       /* DD */
  16,                      /* TD */
  1,                       /* CQI */
  2,                       /* CHI */
  4,                       /* CSI */
  8,                       /* CDI */
  16,                      /* CTI */
  32,                      /* COI */
  4,                       /* SC */
  8,                       /* DC */
  4,                       /* XC */
  16,                      /* TC */
  2,                       /* V2QI */
  4,                       /* V4QI */
  4,                       /* V2HI */
  4,                       /* V1SI */
  8,                       /* V8QI */
  8,                       /* V4HI */
  8,                       /* V2SI */
  8,                       /* V1DI */
  16,                      /* V16QI */
  16,                      /* V8HI */
  16,                      /* V4SI */
  16,                      /* V2DI */
  16,                      /* V1TI */
  32,                      /* V32QI */
  32,                      /* V16HI */
  32,                      /* V8SI */
  32,                      /* V4DI */
  32,                      /* V2TI */
  64,                      /* V64QI */
  64,                      /* V32HI */
  64,                      /* V16SI */
  64,                      /* V8DI */
  64,                      /* V4TI */
  8,                       /* V2SF */
  16,                      /* V4SF */
  16,                      /* V2DF */
  32,                      /* V8SF */
  32,                      /* V4DF */
  32,                      /* V2TF */
  64,                      /* V16SF */
  64,                      /* V8DF */
  64,                      /* V4TF */
};

const unsigned char class_narrowest_mode[MAX_MODE_CLASS] =
{
  MIN_MODE_RANDOM,         /* VOID */
  MIN_MODE_CC,             /* CC */
  MIN_MODE_INT,            /* QI */
  MIN_MODE_PARTIAL_INT,    /* VOID */
  MIN_MODE_FRACT,          /* QQ */
  MIN_MODE_UFRACT,         /* UQQ */
  MIN_MODE_ACCUM,          /* HA */
  MIN_MODE_UACCUM,         /* UHA */
  MIN_MODE_FLOAT,          /* SF */
  MIN_MODE_DECIMAL_FLOAT,  /* SD */
  MIN_MODE_COMPLEX_INT,    /* CQI */
  MIN_MODE_COMPLEX_FLOAT,  /* SC */
  MIN_MODE_VECTOR_INT,     /* V2QI */
  MIN_MODE_VECTOR_FRACT,   /* VOID */
  MIN_MODE_VECTOR_UFRACT,  /* VOID */
  MIN_MODE_VECTOR_ACCUM,   /* VOID */
  MIN_MODE_VECTOR_UACCUM,  /* VOID */
  MIN_MODE_VECTOR_FLOAT,   /* V2SF */
};

const struct real_format *
 real_format_for_mode[MAX_MODE_FLOAT - MIN_MODE_FLOAT + 1 + MAX_MODE_DECIMAL_FLOAT - MIN_MODE_DECIMAL_FLOAT + 1] =
{
  &ieee_single_format,     /* SF */
  &ieee_double_format,     /* DF */
  &ieee_extended_intel_96_format,      /* XF */
  &ieee_quad_format,       /* TF */
  &decimal_single_format,  /* SD */
  &decimal_double_format,  /* DD */
  &decimal_quad_format,    /* TD */
};

void
init_adjust_machine_modes (void)
{
  size_t s ATTRIBUTE_UNUSED;

  /* config/i386/i386-modes.def:34 */
  s = TARGET_128BIT_LONG_DOUBLE ? 16 : 12;
  mode_size[XFmode] = s;
  mode_base_align[XFmode] = s & (~s + 1);
  mode_size[XCmode] = 2*s;
  mode_base_align[XCmode] = s & (~s + 1);

  /* config/i386/i386-modes.def:35 */
  s = TARGET_128BIT_LONG_DOUBLE ? 16 : 4;
  mode_base_align[XFmode] = s;
  mode_base_align[XCmode] = s;

  /* config/i386/i386-modes.def:33 */
  REAL_MODE_FORMAT (XFmode) = (TARGET_128BIT_LONG_DOUBLE ? &ieee_extended_intel_128_format : TARGET_96_ROUND_53_LONG_DOUBLE ? &ieee_extended_intel_96_round_53_format : &ieee_extended_intel_96_format);
}

const unsigned char mode_ibit[NUM_MACHINE_MODES] = 
{
  0,                       /* VOID */
  0,                       /* BLK */
  0,                       /* CC */
  0,                       /* CCGC */
  0,                       /* CCGOC */
  0,                       /* CCNO */
  0,                       /* CCA */
  0,                       /* CCC */
  0,                       /* CCO */
  0,                       /* CCS */
  0,                       /* CCZ */
  0,                       /* CCFP */
  0,                       /* CCFPU */
  0,                       /* BI */
  0,                       /* QI */
  0,                       /* HI */
  0,                       /* SI */
  0,                       /* DI */
  0,                       /* TI */
  0,                       /* OI */
  0,                       /* QQ */
  0,                       /* HQ */
  0,                       /* SQ */
  0,                       /* DQ */
  0,                       /* TQ */
  0,                       /* UQQ */
  0,                       /* UHQ */
  0,                       /* USQ */
  0,                       /* UDQ */
  0,                       /* UTQ */
  8,                       /* HA */
  16,                      /* SA */
  32,                      /* DA */
  64,                      /* TA */
  8,                       /* UHA */
  16,                      /* USA */
  32,                      /* UDA */
  64,                      /* UTA */
  0,                       /* SF */
  0,                       /* DF */
  0,                       /* XF */
  0,                       /* TF */
  0,                       /* SD */
  0,                       /* DD */
  0,                       /* TD */
  0,                       /* CQI */
  0,                       /* CHI */
  0,                       /* CSI */
  0,                       /* CDI */
  0,                       /* CTI */
  0,                       /* COI */
  0,                       /* SC */
  0,                       /* DC */
  0,                       /* XC */
  0,                       /* TC */
  0,                       /* V2QI */
  0,                       /* V4QI */
  0,                       /* V2HI */
  0,                       /* V1SI */
  0,                       /* V8QI */
  0,                       /* V4HI */
  0,                       /* V2SI */
  0,                       /* V1DI */
  0,                       /* V16QI */
  0,                       /* V8HI */
  0,                       /* V4SI */
  0,                       /* V2DI */
  0,                       /* V1TI */
  0,                       /* V32QI */
  0,                       /* V16HI */
  0,                       /* V8SI */
  0,                       /* V4DI */
  0,                       /* V2TI */
  0,                       /* V64QI */
  0,                       /* V32HI */
  0,                       /* V16SI */
  0,                       /* V8DI */
  0,                       /* V4TI */
  0,                       /* V2SF */
  0,                       /* V4SF */
  0,                       /* V2DF */
  0,                       /* V8SF */
  0,                       /* V4DF */
  0,                       /* V2TF */
  0,                       /* V16SF */
  0,                       /* V8DF */
  0,                       /* V4TF */
};

const unsigned char mode_fbit[NUM_MACHINE_MODES] = 
{
  0,                       /* VOID */
  0,                       /* BLK */
  0,                       /* CC */
  0,                       /* CCGC */
  0,                       /* CCGOC */
  0,                       /* CCNO */
  0,                       /* CCA */
  0,                       /* CCC */
  0,                       /* CCO */
  0,                       /* CCS */
  0,                       /* CCZ */
  0,                       /* CCFP */
  0,                       /* CCFPU */
  0,                       /* BI */
  0,                       /* QI */
  0,                       /* HI */
  0,                       /* SI */
  0,                       /* DI */
  0,                       /* TI */
  0,                       /* OI */
  7,                       /* QQ */
  15,                      /* HQ */
  31,                      /* SQ */
  63,                      /* DQ */
  127,                     /* TQ */
  8,                       /* UQQ */
  16,                      /* UHQ */
  32,                      /* USQ */
  64,                      /* UDQ */
  128,                     /* UTQ */
  7,                       /* HA */
  15,                      /* SA */
  31,                      /* DA */
  63,                      /* TA */
  8,                       /* UHA */
  16,                      /* USA */
  32,                      /* UDA */
  64,                      /* UTA */
  0,                       /* SF */
  0,                       /* DF */
  0,                       /* XF */
  0,                       /* TF */
  0,                       /* SD */
  0,                       /* DD */
  0,                       /* TD */
  0,                       /* CQI */
  0,                       /* CHI */
  0,                       /* CSI */
  0,                       /* CDI */
  0,                       /* CTI */
  0,                       /* COI */
  0,                       /* SC */
  0,                       /* DC */
  0,                       /* XC */
  0,                       /* TC */
  0,                       /* V2QI */
  0,                       /* V4QI */
  0,                       /* V2HI */
  0,                       /* V1SI */
  0,                       /* V8QI */
  0,                       /* V4HI */
  0,                       /* V2SI */
  0,                       /* V1DI */
  0,                       /* V16QI */
  0,                       /* V8HI */
  0,                       /* V4SI */
  0,                       /* V2DI */
  0,                       /* V1TI */
  0,                       /* V32QI */
  0,                       /* V16HI */
  0,                       /* V8SI */
  0,                       /* V4DI */
  0,                       /* V2TI */
  0,                       /* V64QI */
  0,                       /* V32HI */
  0,                       /* V16SI */
  0,                       /* V8DI */
  0,                       /* V4TI */
  0,                       /* V2SF */
  0,                       /* V4SF */
  0,                       /* V2DF */
  0,                       /* V8SF */
  0,                       /* V4DF */
  0,                       /* V2TF */
  0,                       /* V16SF */
  0,                       /* V8DF */
  0,                       /* V4TF */
};
