#include "cdap.h"

#define ENQ_GET_HEAD(list) list->flink
#define ENQ_GET_TAIL(list) list->blink
#define ENQ_GET_NEXT(item) item->flink
#define ENQ_GET_PREV(item) item->blink
#define ENQ_GET_LIST_NAME(list) (const char *)list->name
#define ENQ_GET_ITEM_NAME(item) (const char *)item->name

typedef struct enq_item_s {
  struct enq_item_s *flink;
  struct enq_item_s *blink;
  char              *name;
} ENQ_ITEM_t, *ENQ_ITEM_p_t;

typedef ENQ_ITEM_t ENQ_ANCHOR_t, *ENQ_ANCHOR_p_t;

typedef struct address_s {
  ENQ_ITEM_t item;
  char       name[31];
  char       address1[31];
  char       address2[31];
  char       city[31];
  char       state[31];
  char       postal_code[21];
} ADDRESS_t, *ADDRESS_p_t;

ENQ_ANCHOR_p_t ENQ_create_list(const char *name);
ENQ_ITEM_p_t ENQ_create_item(const char *name, size_t size);
CDA_BOOL_t ENQ_is_item_enqueued(ENQ_ITEM_p_t item);
CDA_BOOL_t ENQ_is_list_empty(ENQ_ANCHOR_p_t list);
ENQ_ITEM_p_t ENQ_add_head(ENQ_ANCHOR_p_t list, ENQ_ITEM_p_t item);
ENQ_ITEM_p_t ENQ_add_tail(ENQ_ANCHOR_p_t list, ENQ_ITEM_p_t item);
ENQ_ITEM_p_t ENQ_add_after(ENQ_ITEM_p_t item, ENQ_ITEM_p_t after);
ENQ_ITEM_p_t ENQ_add_before(ENQ_ITEM_p_t item, ENQ_ITEM_p_t before);
ENQ_ITEM_p_t ENQ_dequeue_item(ENQ_ITEM_p_t item);
ENQ_ITEM_p_t ENQ_dequeue_head(ENQ_ANCHOR_p_t list);
ENQ_ITEM_p_t ENQ_dequeue_tail(ENQ_ANCHOR_p_t list);
ENQ_ITEM_p_t ENQ_destroy_item(ENQ_ITEM_p_t item);
ENQ_ANCHOR_p_t ENQ_empty_list(ENQ_ANCHOR_p_t list);
ENQ_ANCHOR_p_t ENQ_destroy_list(ENQ_ANCHOR_p_t list);
