/**
 * GNUMBER: 01336576
 * NAME: Justin Thomas
 *
 */

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct address_t
{
    char alias[11]; // 10 chars + null terminator
    uint8_t octet1;
    uint8_t octet2;
    uint8_t octet3;
    uint8_t octet4;
    struct address_t *next;
} address_t;

address_t *lookup_address();
void add_address();
void load_addresses(const char *filename);
void delete_address();
void update_address();
void display_list();
void display_aliases_for_location();
void save_to_file();
void free_list();

struct address_t *head = NULL;

/**
 * Main function to load addresses from file
 * and provide a menu for user interaction
 * 'option' variable to hold user choice
 */
int main()
{
    load_addresses("CS531_Inet.txt");
    int option = 0;

    // work on prompting the user for options 1-8 next
    while (option != 8)
    {
        printf("\n1) Add address\n");
        printf("2) Look up address\n");
        printf("3) Update address\n");
        printf("4) Delete address\n");
        printf("5) Display list\n");
        printf("6) Display aliases for location\n");
        printf("7) Save to file\n");
        printf("8) Quit\n\n");
        scanf("%d", &option);

        if (option < 1 || option > 8)
        {
            printf("Invalid option. Please try again.\n");
            continue;
        }

        switch (option)
        {
        case 1:
            add_address();
            break;
        case 2:
            lookup_address();
            break;
        case 3:
            update_address();
            break;
        case 4:
            delete_address();
            break;
        case 5:
            display_list();
            break;
        case 6:
            display_aliases_for_location();
            break;
        case 7:
            save_to_file();
            break;
        case 8:
            free_list();
            printf("Exiting program.\n");
            break;
        }
    }

    return 0;
}

/**
 * Saves the current linked list of addresses to a user-specified file
 * 'filename' variable to hold user input for file name
 * 'fp' variable for file operations
 * 'current' pointer to traverse the linked list
 */
void save_to_file()
{
    char filename[50];
    FILE *fp;
    address_t *current = head;

    printf("Enter filename to save to: ");
    scanf("%50s", filename);

    fp = fopen(filename, "w");
    if (!fp)
    {
        perror("Error: Could not open file for writing");
        return;
    }

    // Write each address to file in the same format as input
    while (current)
    {
        fprintf(fp, "%d.%d.%d.%d %s\n",
                current->octet1,
                current->octet2,
                current->octet3,
                current->octet4,
                current->alias);
        current = current->next;
    }

    fclose(fp);
    printf("Address list saved to %s successfully.\n", filename);
}

void display_aliases_for_location()
{
    int location1, location2;
    address_t *current = head;
    int found = 0;

    // Prompt for first location value
    while (1)
    {
        printf("Enter first location value (0-255): ");
        if (scanf("%d", &location1) != 1 || location1 < 0 || location1 > 255)
        {
            printf("Invalid input. Please enter a value between 0-255.\n");
            while (getchar() != '\n')
                ; // clear input buffer
            continue;
        }
        break;
    }

    // Prompt for second location value
    while (1)
    {
        printf("Enter second location value (0-255): ");
        if (scanf("%d", &location2) != 1 || location2 < 0 || location2 > 255)
        {
            printf("Invalid input. Please enter a value between 0-255.\n");
            while (getchar() != '\n')
                ; // clear input buffer
            continue;
        }
        break;
    }

    printf("\nAliases for location %d.%d:\n", location1, location2);

    // Search for matching addresses
    while (current)
    {
        if (current->octet1 == location1 && current->octet2 == location2)
        {
            printf("  %s IP: %d.%d.%d.%d\n",
                   current->alias,
                   current->octet1,
                   current->octet2,
                   current->octet3,
                   current->octet4);
            found = 1;
        }
        current = current->next;
    }

    if (!found)
    {
        printf("Error: No aliases found for location %d.%d\n", location1, location2);
    }
}

/**
 * Displays all addresses in the linked list
 * 'current' pointer to traverse the linked list
 */
void display_list()
{
    address_t *current = head;
    if (!current)
    {
        printf("The address list is empty.\n");
        return;
    }
    while (current)
    {
        printf("Alias: %s, IP: %u.%u.%u.%u\n", current->alias, current->octet1, current->octet2, current->octet3, current->octet4);
        current = current->next;
    }
}

/**
 * Deletes an address from the linked list based on user-provided alias
 * 'current' pointer to find the node to delete
 * 'prev' pointer to keep track of the previous node
 * 'confirm' variable to confirm deletion
 */
void delete_address()
{

    address_t *current = lookup_address();
    address_t *prev = NULL;
    char confirm;
    // Alias did not exist, leave
    if (current == NULL)
    {
        return;
    }

    printf("Delete %s with IP %d.%d.%d.%d? (y/n): ",
           current->alias, current->octet1, current->octet2, current->octet3, current->octet4);

    scanf(" %c", &confirm);

    if (confirm == 'y' || confirm == 'Y')
    {
        // If the node to be deleted is the head
        if (current == head)
        {
            head = current->next;
        }
        else
        {
            // Find the previous node
            prev = head;
            while (prev && prev->next != current)
            {
                prev = prev->next;
            }
            if (prev)
            {
                prev->next = current->next;
            }
        }
        free(current);
        printf("Address deleted successfully.\n");
    }
    else
    {
        printf("Deletion cancelled.\n");
    }
}

/**
 * Updates an existing address based on user-provided alias
 * 'current' pointer to find the node to update
 * 'o1', 'o2', 'o3', 'o4' variables to hold new IP octets
 */
void update_address()
{

    address_t *current = lookup_address();
    int o1, o2, o3, o4;

    // The alias did not exist, leave
    if (current == NULL)
    {
        return;
    }

    printf("Enter the new IP address (format: x.x.x.x) that will replace the old IP: ");
    while (scanf("%d.%d.%d.%d", &o1, &o2, &o3, &o4) != 4 ||
           o1 < 0 || o1 > 255 || o2 < 0 || o2 > 255 ||
           o3 < 0 || o3 > 255 || o4 < 0 || o4 > 255)
    {

        printf("Invalid IP address format ... Please Try again\n");
        while (getchar() != '\n')
            ; // clear input buffer
    }

    current->octet1 = o1;
    current->octet2 = o2;
    current->octet3 = o3;
    current->octet4 = o4;
}

/**
 * Looks up an address by alias and displays the corresponding IP address
 * 'current' pointer to traverse the linked list
 * 'alias' variable to hold user input for alias
 * 'found' variable to indicate if the alias was found
 *  Returns pointer to the found address_t struct or NULL if not found
 */
address_t *lookup_address()
{
    address_t *current = head;
    char alias[20];
    int found;

    printf("Enter alias: \n");
    scanf("%20s", alias);

    if (strlen(alias) > 10)
    {
        printf("Error: alias is too long ... returning to menu");
        return NULL;
    }

    found = 0;
    // Traverse the linked list to find the alias, if found (with strcmp) print the IP
    while (current)
    {
        if (strcmp(current->alias, alias) == 0)
        {
            printf("The address for %s is %d.%d.%d.%d\n",
                   alias, current->octet1, current->octet2, current->octet3, current->octet4);
            found = 1;
            return current;
        }
        current = current->next;
    }
    printf("There were no aliases matching your input .. returning to menu\n");
    return NULL;
}

/**
 * Adds a new address to the linked list after validating alias and IP uniqueness
 * 'current' pointer to traverse the linked list
 * 'alias' variable to hold user input for alias
 * 'o1', 'o2', 'o3', 'o4' variables to hold user input for IP octets
 * 'alias_exists' and 'ip_exists' flags to check for uniqueness
 */
void add_address()
{

    address_t *current = head;
    char alias[20];
    int o1, o2, o3, o4;

    // Check alias length and uniqueness
    printf("Enter alias (max 10 characters): ");
    scanf("%20s", alias);
    if (strlen(alias) > 10)
    {
        printf("Error: Alias too long ... returning to menu\n");
        return;
    }
    while (current)
    {
        if (strcmp(current->alias, alias) == 0)
        {
            printf("Alias already exists. Please try again.\n");
            return;
        }
        current = current->next;
    }

    // Check IP address format and uniqueness
    printf("Enter IP address (format: x.x.x.x): ");
    if (scanf("%d.%d.%d.%d", &o1, &o2, &o3, &o4) != 4 ||
        o1 < 0 || o1 > 255 || o2 < 0 || o2 > 255 ||
        o3 < 0 || o3 > 255 || o4 < 0 || o4 > 255)
    {

        printf("Invalid IP address format. Please try again.\n");
        while (getchar() != '\n')
            ; // clear input buffer
        return;
    }

    current = head;
    while (current)
    {
        if (current->octet1 == o1 && current->octet2 == o2 &&
            current->octet3 == o3 && current->octet4 == o4)
        {
            printf("IP address already exists. Please try again.\n");
            return;
        }
        current = current->next;
    }

    // If we reach here, both alias and IP are valid and unique
    address_t *new_node = calloc(1, sizeof(address_t));
    if (!new_node)
    {
        perror("Memory allocation failed");
        return;
    }

    strncpy(new_node->alias, alias, 10);
    new_node->alias[10] = '\0';
    new_node->octet1 = o1;
    new_node->octet2 = o2;
    new_node->octet3 = o3;
    new_node->octet4 = o4;
    new_node->next = NULL;

    if (!head)
    {
        head = new_node;
    }
    else
    {
        current = head;
        while (current->next)
        {
            current = current->next;
        }
        current->next = new_node;
    }
    printf("Address added successfully.\n");
}

/**
 * Loads addresses from a specified file into the linked list
 * 'filename' parameter for the input file name
 * 'fp' variable for file operations
 * 'line' buffer to read each line from the file
 * 'prev' pointer to keep track of the last node in the list
 */
void load_addresses(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (!fp)
    {
        perror("File open failed");
        return;
    }

    char line[64];
    address_t *prev = NULL;

    // Read each line and create a new address_t node
    while (fgets(line, sizeof(line), fp))
    {
        address_t *node = calloc(1, sizeof(address_t));
        int o1, o2, o3, o4;
        char alias[11];

        // Parse the line
        if (sscanf(line, "%d.%d.%d.%d %10s", &o1, &o2, &o3, &o4, alias) == 5)
        {
            node->octet1 = o1;
            node->octet2 = o2;
            node->octet3 = o3;
            node->octet4 = o4;
            strncpy(node->alias, alias, 10);
            node->alias[10] = '\0';
            node->next = NULL;

            if (!head)
                head = node;
            else
                prev->next = node;
            prev = node;
        }
        else
        {
            free(node);
        }
    }
    fclose(fp);
}

/**
 * Frees all nodes in the linked list to prevent memory leaks
 * 'current' pointer to traverse the linked list
 * 'next' pointer to hold the next node before freeing the current one
 */
void free_list()
{
    address_t *current = head;
    address_t *next;

    while (current)
    {
        next = current->next;
        free(current);
        current = next;
    }
    head = NULL;
}
