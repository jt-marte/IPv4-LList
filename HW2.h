#ifndef HW2_H
#define HW2_H

#include <stdint.h>

typedef struct address_t
{
    char alias[11];
    uint8_t octet1;
    uint8_t octet2;
    uint8_t octet3;
    uint8_t octet4;
    struct address_t *next;
} address_t;

extern struct address_t *head; // Head of the linked list global variable that is used in functions

address_t* lookup_address();
void update_address();
void add_address();
void load_addresses(const char *filename);
// We will need to add function prototypes here as we develop the project

#endif