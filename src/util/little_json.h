#ifndef __LITTLE_JSON_H__
#define __LITTLE_JSON_H__

typedef struct {
  unsigned int key_len;
  unsigned int value_len;
  unsigned char* key;
  unsigned char* value;
} json_entry;

typedef struct {
  unsigned int count;
  json_entry entries;
} json_object;

int lj_obj2str(const json_object* obj, unsigned char* str, unsigned int *len, const unsigned int maxlen);
int lj_str2obj(const unsigned char* str, const unsigned int len, json_object** obj);

#endif
