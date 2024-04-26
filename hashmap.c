#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) 
{
  if(map == NULL || key == NULL) return;
  
  long posicion = hash(key,map->capacity);
  Pair * par = createPair(key,value);

  while(map->buckets[posicion] != NULL && map->buckets[posicion]->key != NULL)
  {
    posicion = (posicion + 1) % map->capacity;
  }
  map->buckets[posicion] = par;
  map->size++;
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}


HashMap * createMap(long capacity) 
{
  HashMap * mapa = (HashMap *)malloc(sizeof(HashMap));
  mapa->buckets = (Pair **)calloc(capacity,sizeof(Pair *));
  mapa->size = 0;
  mapa->capacity = capacity;
  mapa->current = -1;
  return mapa;
}

void eraseMap(HashMap * map,  char * key) 
{
  if(map == NULL || key == NULL) return;
  long posicion = hash(key,map->capacity);
  while(map->buckets[posicion])
  {
    if(strcmp(map->buckets[posicion]->key,key) == 0)
    {
      map->buckets[posicion]->key = NULL;
      map->size--;
      return;
    }
    posicion = (posicion + 1) % map->capacity;
  }
}

Pair * searchMap(HashMap * map,  char * key) 
{
  if(map == NULL || key == NULL) return NULL;
  long posicion = hash(key,map->capacity);
  while(map->buckets[posicion])
  {
    if(strcmp(map->buckets[posicion]->key, key) == 0)
    {
      map->current = posicion;
      return map->buckets[posicion];
    }
    posicion = (posicion + 1) % map->capacity;
  }
  return NULL;
}



Pair * firstMap(HashMap * map) 
{
  for(long i = 0 ; i < map->capacity ; i++)
  {
    if(map->buckets[i] != NULL && map->buckets[i]->key != NULL)
    {
      map->current = i;
      return map->buckets[i];
    }
  }

  return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
