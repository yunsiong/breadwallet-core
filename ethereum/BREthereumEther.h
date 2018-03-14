
#ifndef BR_Ethereum_Ether_H
#define BR_Ethereum_Ether_H

#include "rlp/BRRlpCoder.h"
#include "BREthereumMath.h"

#ifdef __cplusplus
extern "C" {
#endif

//
// Etherum Boolean
//
typedef enum {
  ETHEREUM_BOOLEAN_TRUE = 0,               // INTENTIONALLY 'backwards'
  ETHEREUM_BOOLEAN_FALSE = 1
} BREthereumBoolean;

#define ETHEREUM_BOOLEAN_IS_TRUE(x)  ((x) == ETHEREUM_BOOLEAN_TRUE)
#define ETHEREUM_BOOLEAN_IS_FALSE(x) ((x) == ETHEREUM_BOOLEAN_FALSE)

//
// Etherum Ether Parse Status
//
typedef enum {
  ETHEREUM_ETHER_PARSE_OK,
  ETHEREUM_ETHER_PARSE_STRANGE_DIGITS,
  ETHEREUM_ETHER_PARSE_UNDERFLOW,
  ETHEREUM_ETHER_PARSE_OVERFLOW
} BREthereumEtherParseStatus;

//
// Ether
//
typedef enum {
    WEI = 0,

    KWEI = 1,
    ADA  = 1,

    MWEI = 2,

    GWEI    = 3,
    SHANNON = 3,

    SZABO = 4,

    FINNEY = 5,

    ETHER = 6,

    KETHER   = 7,
    GRAND    = 7,
    EINSTEIN = 7,

    METHER = 8,
    GETHER = 9,
    TETHER = 10
} BREthereumEtherUnit;

#define NUMBER_OF_ETHER_UNITS  (1 + TETHER)

typedef struct BREthereumEtherStruct {
    UInt256 valueInWEI;
} BREthereumEther;

extern BREthereumEther
etherCreate(const UInt256 value);

extern BREthereumEther
etherCreateUnit(const UInt256 value, BREthereumEtherUnit unit, int *overflow);

extern BREthereumEther
etherCreateNumber (uint64_t number, BREthereumEtherUnit unit);

extern BREthereumEther
etherCreateZero (void);

extern BREthereumEther
etherCreateString(const char *string, BREthereumEtherUnit unit, BREthereumEtherParseStatus *status);

extern UInt256
etherGetValue(const BREthereumEther ether, BREthereumEtherUnit unit);

extern char *
etherGetValueString(const BREthereumEther ether, BREthereumEtherUnit unit);

//extern uint64_t
//etherGetValueNumberDANGEROUS (const BREthereumEther ether, BREthereumEtherUnit unit);

extern BRRlpItem
etherRlpEncode (const BREthereumEther ether, BRRlpCoder coder);

extern BREthereumEther
etherAdd (BREthereumEther e1, BREthereumEther e2, int *overflow);

extern BREthereumEther
etherSub (BREthereumEther e1, BREthereumEther e2, int *negative);

//
// Comparisons
//
extern BREthereumBoolean
etherIsEQ (BREthereumEther e1, BREthereumEther e2);

//
extern BREthereumBoolean
etherIsGT (BREthereumEther e1, BREthereumEther e2);

extern BREthereumBoolean
etherIsGE (BREthereumEther e1, BREthereumEther e2);

extern BREthereumBoolean
etherIsLT (BREthereumEther e1, BREthereumEther e2);

extern BREthereumBoolean
etherIsLE (BREthereumEther e1, BREthereumEther e2);

extern BREthereumBoolean
etherIsZero (BREthereumEther e);

typedef enum {
  ETHEREUM_COMPARISON_LT = -1,
  ETHEREUM_COMPARISON_EQ =  0,
  ETHEREUM_COMPARISON_GT = +1
} BREthereumComparison;

extern BREthereumComparison
etherCompare (BREthereumEther e1, BREthereumEther e2);

#ifdef __cplusplus
}
#endif

#endif /* BR_Ethereum_Ether_H */
