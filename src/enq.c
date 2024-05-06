#include "../include/enqp.h"
#include "string.h"

ENQ_ANCHOR_p_t ENQ_create_list(const char *name) {
  ENQ_ANCHOR_p_t list =  CDA_NEW(ENQ_ANCHOR_t);

  list->flink = list;
  list->blink = list;
  list->name = CDA_NEW_STR_IF(name);
  return list;
}

ENQ_ITEM_p_t ENQ_create_item(const char *name, size_t size) {
  ENQ_ITEM_p_t item = (ENQ_ITEM_p_t)CDA_malloc(size);

  CDA_ASSERT(size >= sizeof(ENQ_ITEM_t));
  item->flink = item;
  item->blink = item;
  item->name = CDA_NEW_STR_IF(name);;
  return item;
}

CDA_BOOL_t ENQ_is_item_enqueued(ENQ_ITEM_p_t item) {
  return (item->flink == item ? CDA_FALSE : CDA_TRUE);
}

CDA_BOOL_t ENQ_is_list_empty(ENQ_ANCHOR_p_t list) {
  return (list->flink == list ? CDA_TRUE : CDA_FALSE);
}

ENQ_ITEM_p_t ENQ_add_head(ENQ_ANCHOR_p_t list, ENQ_ITEM_p_t item) {
  CDA_ASSERT(!ENQ_is_item_enqueued(item));

  if (ENQ_is_list_empty(list)) {
    list->blink = item;
    item->flink = list;
  } else {
    item->flink = list->flink;
    list->flink->blink = item;
  }

  list->flink = item;
  item->blink = list;
  return item;
}

ENQ_ITEM_p_t ENQ_add_tail(ENQ_ANCHOR_p_t list, ENQ_ITEM_p_t item) {
  CDA_ASSERT(!ENQ_is_item_enqueued(item));

  if (ENQ_is_list_empty(list)) {
    list->flink = item;
    item->blink = list;
  } else {
    item->blink = list->blink;
    list->blink->flink = item;
  }

  list->blink = item;
  item->flink = list;
  return item;
}

ENQ_ITEM_p_t ENQ_add_after(ENQ_ITEM_p_t item, ENQ_ITEM_p_t after) {
  CDA_ASSERT(!ENQ_is_item_enqueued(item));

  item->blink = after;
  item->flink = after->flink;

  after->flink->blink = item;
  after->flink = item;
  return item;
}

ENQ_ITEM_p_t ENQ_add_before(ENQ_ITEM_p_t item, ENQ_ITEM_p_t before) {
  CDA_ASSERT(!ENQ_is_item_enqueued(item));

  item->flink = before;
  item->blink = before->blink;

  before->blink->flink = item;
  before->blink = item;
  return item;
}

ENQ_ITEM_p_t ENQ_dequeue_item(ENQ_ITEM_p_t item) {
  item->blink->flink = item->flink;
  item->flink->blink = item->blink;

  // Dequeued item definition
  item->flink = item;
  item->blink = item;
  return item;
}

ENQ_ITEM_p_t ENQ_dequeue_head(ENQ_ANCHOR_p_t list) {
  if (ENQ_is_list_empty(list)) {
    return list;
  }
  ENQ_ITEM_p_t head = list->flink;
  head->flink->blink = list;
  list->flink = head->flink;

  head->flink = head;
  head->blink = head;
  return head;
}

ENQ_ITEM_p_t ENQ_dequeue_tail(ENQ_ANCHOR_p_t list) {
  if (ENQ_is_list_empty(list)) {
    return list;
  }
  ENQ_ITEM_p_t tail = list->blink;
  tail->blink->flink = list;
  list->blink = tail->blink;

  tail->flink = tail;
  tail->blink = tail;
  return tail;
}

ENQ_ITEM_p_t ENQ_destroy_item(ENQ_ITEM_p_t item) {
  ENQ_dequeue_item(item);
  CDA_free(item->name);
  CDA_free(item);
  return NULL;
}

ENQ_ANCHOR_p_t ENQ_empty_list(ENQ_ANCHOR_p_t list) {
  while (!ENQ_is_list_empty(list)) {
    ENQ_destroy_item(list->flink);
  }
  return list;
}

ENQ_ANCHOR_p_t ENQ_destroy_list(ENQ_ANCHOR_p_t list) {
  ENQ_empty_list(list);
  CDA_free(list->name);
  CDA_free(list);
  return NULL;
}
