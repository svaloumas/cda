#ifndef  TIPS_H
#define TIPS_H

#include "enq.h"

#define NOT_FOUND     0
#define FOUND_EXACT   1
#define FOUND_GREATER 2

typedef struct receipts_s {
  ENQ_ITEM_t  item;
  double      checkTotal;
  double      tipTotal;
  int         numReceipts;
} RECEIPTS_t, *RECEIPTS_p_t;

void TIPS_addReceipt(
  const char *waitperson,
  double check,
  double tip
);

void TIPS_close(void);

void TIPS_init(void);

RECEIPTS_p_t TIPS_create_bucket(
  const char *waitperson,
  double check,
  double tip
);

void TIPS_add_to_receipt(
  RECEIPTS_p_t receipts,
  double check,
  double tip
);

void TIPS_printReceipts(void);

#endif
