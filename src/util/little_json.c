#include "little_json.h"

int lj_obj2str(const json_object* obj, unsigned char* str, unsigned int *len, const unsigned int maxlen)
{
  unsigned int count=obj->count;
  unsigned int i;
  unsigned int reqlen=0;
  int pos=0;

  if ((NULL==str)||(NULL==len)){
    return -1;
  }

  // Calculate required buffer len
  for(i=0; i<count, i++){
    reqlen += obj->entries[i].key_len;
    reqlen += obj->entries[i].value_len;
    reqlen += 1; // '=' between key and value
    if(i < (count-1)){
      reqlen += 1; // '&' between entries
    }
  }

  // check for required length
  if (reqlen > maxlen){
    *len=reqlen;
    return -1;
  }

  // Fill up str buffer
  for(i=0; i<count, i++){
    memcpy(str[pos], obj->entries[i].key, obj->entries[i].key_len);
    pos += obj->entries[i].key_len;
    str[pos++] = '=';
    memcpy(str[pos], obj->entries[i].value, obj->entries[i].value_len);
    pos += obj->entries[i].value_len;
    if(i < (count-1)){
      str[pos++] = '&';
    }
  }

  return 0;
}

int lj_str2obj(const unsigned char* str, const unsigned int len, json_object** obj)
{
  unsigned int i, chunk_len, key_len, value_len;
  char* chunk = NULL;

  if ((NULL==str)||(NULL==obj)){
    return -1;
  }

  //split our string into chunks
  chunk = strtok((char*)str, " &");
  if (NULL != chunk) {
    do {
      char* pRef;
      chunk_len = strlen(chunk); // This is the total chunk length
      pRef = strstr(chunk, "=");
      if (NULL!=pRef){
        char* pKey=chunk;
        char* pValue=pRef+1;
        key_len=(pRef-chunk);
        value_len=chunk_len-key_len-1;

        //validate lengths before continue
        if ((key_len>0) && (value_len>0)){
          if(NULL==*obj){
            *obj=(json_object*)malloc(sizeof(json_object));
            if (NULL==*obj) {
              return -1;
            }
            memset(*obj, 0, sizeof(json_object));
          }

          //find an empty position to insert our entry
          *obj->count++;
          obj->entries[obj->count-1]->key_len=key_len;
          obj->entries[obj->count-1]->value_len=value_len;
          obj->entries[obj->count-1]->key = (unsigned char*) malloc(key_len+1);
          obj->entries[obj->count-1]->value = (unsigned char*) malloc(value_len+1);
          if((NULL==obj->entries[obj->count-1]->key) ||
             (NULL==obj->entries[obj->count-1]->value) ) {
               return -1;
          }
          memset(obj->entries[obj->count-1]->key, 0, key_len+1);
          memset(obj->entries[obj->count-1]->value, 0, value_len+1);

          memcpy(obj->entries[obj->count-1]->key, pKey, key_len);
          memcpy(obj->entries[obj->count-1]->value, pValue, value_len);
        }
      }
      else {
        //invalid format... well... ignore it
        printf("Ignoring invalid format chunk\n");
      }
    } while (NULL!=chunk);
  }

  return 0;
}

void lj_free_obj(json_object* obj)
{
  unsigned int i;
  for(i=0;i<obj->count;i++){
    if (NULL!=obj->entries[i].key){
      free(obj->entries[i].key);
      obj->entries[i].key=NULL;
      obj->entries[i].key_len=0;
    }
    if (NULL!=obj->entries[i].value){
      free(obj->entries[i].value);
      obj->entries[i].value=NULL;
      obj->entries[i].value_len=0;
    }
    free(obj->entries[i]);
    obj->entries[i]=NULL;
  }
  free(obj);
  obj=NULL;
}

void lj_print_obj(json_object* obj)
{
  unsigned int i;
  if (NULL==obj){
    printf("-- null pointer --\n");
  }

  if (0==obj->count){
    printf("-- empty object --\n");
  }

  printf("little_json object:\n")
  printf("\t{\n");
  for(i=0;i<obj->count;i++){
    printf("\t\t%s: %s", obj->entries[i].key, obj->entries[i].value);
    if (i<(obj->count-1)){
      printf(",");
    }
    printf("\n");
  }
  printf("\t}\n");
}
