#include "../include/tipsp.h"

int main(void) {
  TIPS_init();
  TIPS_addReceipt("alex", 20, 2);
  TIPS_addReceipt("alex", 20, 2);
  TIPS_addReceipt("stef", 10, 1);
  TIPS_addReceipt("stef", 5, 0.5);
  TIPS_addReceipt("zed", 12, 3);
  TIPS_addReceipt("stef", 5, 1);
  TIPS_addReceipt("zed", 15, 4);
  TIPS_printReceipts();
  TIPS_close();
}
