#include <stdio.h>
#include "../include/tipsp.h"

static const char *tipListName = "Tip Queue";

static ENQ_ANCHOR_p_t list = NULL;

void TIPS_init(void) {
  CDA_ASSERT(list == NULL);
  list = ENQ_create_list(tipListName);
}

RECEIPTS_p_t TIPS_create_bucket(
  const char *waitperson,
  double check,
  double tip
) {
  RECEIPTS_p_t bucket = NULL;
  bucket = (RECEIPTS_p_t)ENQ_create_item(waitperson, sizeof(RECEIPTS_t));
  bucket->checkTotal = check;
  bucket->tipTotal = tip;
  bucket->numReceipts = 1;
  return bucket;
}

void TIPS_add_to_receipt(RECEIPTS_p_t receipts, double check, double tip) {
  receipts->checkTotal += check;
  receipts->tipTotal += tip;
  ++receipts->numReceipts;
}

void TIPS_addReceipt(const char *waitperson, double check, double tip) {
  RECEIPTS_p_t receipts  = NULL;
  RECEIPTS_p_t bucket    = NULL;
  int          result    = NOT_FOUND;
  int          compare   = 0;

  CDA_ASSERT(list != NULL);

  receipts = (RECEIPTS_p_t)ENQ_GET_HEAD(list);
  while ((result == NOT_FOUND) && (&receipts->item != list)) {
    compare = strcmp(waitperson, ENQ_GET_ITEM_NAME((&receipts->item)));
    if (compare == 0) {
      result = FOUND_EXACT;
    } else if (compare < 0) {
      result = FOUND_GREATER;
    } else {
      receipts = (RECEIPTS_p_t)ENQ_GET_NEXT((&receipts->item));
    }
  }

  switch (result) {
    case FOUND_EXACT:
      TIPS_add_to_receipt((RECEIPTS_p_t)receipts, check, tip);
      break;
    case FOUND_GREATER:
      bucket = TIPS_create_bucket(waitperson, check, tip);
      ENQ_add_before(&bucket->item, &receipts->item);
      break;
    case NOT_FOUND:
      bucket = TIPS_create_bucket(waitperson, check, tip);
      ENQ_add_tail(list, &bucket->item);
      break;
    default:
      // Should never happen.
      CDA_ASSERT(CDA_FALSE);
      break;
  }
}

void TIPS_printReceipts(void) {
  RECEIPTS_p_t receipts = NULL;
  CDA_ASSERT(list != NULL);

  receipts = (RECEIPTS_p_t)ENQ_GET_HEAD(list);
  while (receipts != (RECEIPTS_p_t)list) {
    printf("%s\n", ENQ_GET_ITEM_NAME(((ENQ_ITEM_p_t)receipts)));
    printf(
      "Total receipts: %.2f (Average: %.2f)\n",
       receipts->checkTotal,
       receipts->checkTotal / receipts->numReceipts
    );
    printf(
      "Total tips: %.2f (Average: %.2f)\n",
       receipts->tipTotal,
       receipts->tipTotal / receipts->numReceipts
    );
    printf("\n");
    receipts = (RECEIPTS_p_t)ENQ_GET_NEXT((&receipts->item));
  }
}

void TIPS_close(void) {
  CDA_ASSERT(list != NULL);
  ENQ_destroy_list(list);
  list = NULL;
}
