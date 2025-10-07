#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "HW2.h"

/* Test each function in this file */

void testStructLL();
void testAddrFileRead();
void testAddAddress();
void testUpdate();
void testDeleteAddress();

int testMain() {
    //printf("Struct and linked list test:\n\n");
    //testStructLL(); // test to verify the struct and linked list
    
    printf("File read into linked list test:\n\n");
    testAddrFileRead(); // test to verify reading from file into linked list
    
    //printf("Add address test:\n\n");
    //testAddAddress(); // test to verify adding addresses to linked list

    testUpdate();

    return 0;
}

void testDeleteAddress() {
    delete_address();
    address_t *curr = head;
    while (curr) {
        printf("Alias: %s, IP: %u.%u.%u.%u\n", curr->alias, curr->octet1, curr->octet2, curr->octet3, curr->octet4);
        curr = curr->next;
        printf("\n");
    }
    
}

void testUpdate() {
    update_address();
    address_t *curr = head;
    while (curr) {
        printf("Alias: %s, IP: %u.%u.%u.%u\n", curr->alias, curr->octet1, curr->octet2, curr->octet3, curr->octet4);
        curr = curr->next;
        printf("\n");
    }
    
}

void testAddAddress() {
    add_address();
    add_address();
    add_address();
    address_t *curr = head;
    while (curr) {
        printf("Alias: %s, IP: %u.%u.%u.%u\n", curr->alias, curr->octet1, curr->octet2, curr->octet3, curr->octet4);
        curr = curr->next;
        printf("\n");
    }

}

void testAddrFileRead() {
    load_addresses("CS531_Inet.txt");
    address_t *curr = head;
    while (curr) {
        printf("Alias: %s, IP: %u.%u.%u.%u\n", curr->alias, curr->octet1, curr->octet2, curr->octet3, curr->octet4);
        curr = curr->next;
        printf("\n");
    }
}

void testStructLL() {
    int i = 0;
    address_t *addr1;
    address_t *addr2;
    address_t *addr3;

    addr1 = (address_t *)calloc(1, sizeof(address_t));
    addr2 = (address_t *)calloc(1, sizeof(address_t));
    addr3 = (address_t *)calloc(1, sizeof(address_t));
    
    if (addr1 && addr2 && addr3) {
        // Initialize addr1
        snprintf(addr1->alias, sizeof(addr1->alias), "ServerOne");
        addr1->octet1 = 192;
        addr1->octet2 = 168;
        addr1->octet3 = 1;
        addr1->octet4 = 1;
        addr1->next = addr2; // Link to addr2

        // Initialize addr2
        snprintf(addr2->alias, sizeof(addr2->alias), "ClientA");
        addr2->octet1 = 10;
        addr2->octet2 = 0;
        addr2->octet3 = 0;
        addr2->octet4 = 5;
        addr2->next = addr3; // Link to addr3

        // Initialize addr3
        snprintf(addr3->alias, sizeof(addr3->alias), "ClientB");
        addr3->octet1 = 10;
        addr3->octet2 = 0;
        addr3->octet3 = 0;
        addr3->octet4 = 6;
        addr3->next = NULL; // End of list
    }

    // Traverse and print the linked list
    address_t *current = addr1;
    for(int i = 0; i < 3; i++) {
        printf("Alias: %s, IP: %u.%u.%u.%u\n", current->alias, current->octet1, current->octet2, current->octet3, current->octet4);
        current = current->next;
        printf("\n");
    }
}