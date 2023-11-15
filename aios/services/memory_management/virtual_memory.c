#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define PAGE_SIZE 4096
#define PAGE_TABLE_SIZE 1024

// Example page table entry
typedef struct {
    uint32_t frame_number; // Physical frame number
    uint8_t valid;         // Valid bit to indicate presence in memory
} PageTableEntry;

// Example page table
PageTableEntry page_table[PAGE_TABLE_SIZE];

// Example function to perform virtual to physical address translation
uint32_t translate_virtual_to_physical(uint32_t virtual_address) {
    uint32_t page_number = virtual_address / PAGE_SIZE;
    uint32_t offset = virtual_address % PAGE_SIZE;

    if (page_table[page_number].valid) {
        uint32_t frame_number = page_table[page_number].frame_number;
        uint32_t physical_address = (frame_number * PAGE_SIZE) + offset;
        return physical_address;
    } else {
        printf("Page fault: Page not in memory.\n");
        // In a real system, this would trigger fetching the page from disk, etc.
        return 0; // Returning 0 as an example for a page fault
    }
}

int main() {
    // Example: Simulating a page table entry for page 3 mapped to frame 5
    page_table[3].valid = 1;
    page_table[3].frame_number = 5;

    // Simulating a virtual address to be translated
    uint32_t virtual_address = 3 * PAGE_SIZE + 100;

    // Perform virtual to physical address translation
    uint32_t physical_address = translate_virtual_to_physical(virtual_address);

    if (physical_address != 0) {
        printf("Virtual address %u maps to physical address %u\n", virtual_address, physical_address);
    }

    return 0;
}
