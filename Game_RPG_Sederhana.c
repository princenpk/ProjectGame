#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_ITEMS 100

struct Item {
  char name[64];
  int rarity; 
  int power;
};

int compare_rarity(const void* a, const void* b) {
  struct Item* itemA = (struct Item*)a;
  struct Item* itemB = (struct Item*)b;
  return (itemB->rarity - itemA->rarity);
}

struct Item* search_item(struct Item* items, int numItems, char* name) {
  
  if(numItems <= 0) {
    return NULL;
  }
  
  if(strcmp(items->name, name) == 0) {
    return items;
  }

  return search_item(items+1, numItems-1, name); 
}

void generate_random_items(struct Item* items, int numItems) {

  printf("Generating %d random items...\n", numItems);

  for(int i = 0; i < numItems; i++) {
    printf(".");
    items[i].rarity = rand() % 10 + 1; 
    items[i].power = rand() % 100 + 1;


  }

  printf("\nDone!\n");
}

void print_top_items(struct Item* items, int numItems) {
  
  printf("Top %d items:\n", numItems);

  for(int i = 0; i < numItems; i++) {
    printf("%s (Rarity: %d, Power: %d)\n", 
           items[i].name, items[i].rarity, items[i].power); 
  }
}


void print_item(struct Item* item) {
  if(item == NULL) {
    printf("Item not found!\n");
    return;
  }

  printf("Name: %s\nRarity: %d\nPower:%d\n",
    item->name, item->rarity, item->power);
}

int main() {

  struct Item items[MAX_ITEMS];  

  generate_random_items(items, MAX_ITEMS);

  qsort(items, MAX_ITEMS, sizeof(struct Item), compare_rarity);
  
  print_top_items(items, 5);

  char name[64];
  printf("Enter item name to search: ");
  scanf("%s", name);

  printf("Searching for item \"%s\"...\n", name);  
  struct Item* found = search_item(items, MAX_ITEMS, name);
  
  print_item(found);

  return 0;
}
