/* GPLv2 (c) Airbus */
#include <debug.h>
#include <info.h>

extern info_t   *info;
extern uint32_t __kernel_start__;
extern uint32_t __kernel_end__;

void tp() {
   debug("kernel mem [0x%x - 0x%x]\n", &__kernel_start__, &__kernel_end__);
   debug("MBI flags 0x%x\n", info->mbi->flags);
   debug("Memory map address: %x, length: %u bytes\n", info->mbi->mmap_addr, info->mbi->mmap_length);
   multiboot_memory_map_t *map = (multiboot_memory_map_t *) info->mbi->mmap_addr;
   uint64_t total_size = 0;
   while ((uint32_t) map < info->mbi->mmap_addr + info->mbi->mmap_length) {
     printf("address: 0x%X, length: %llu bytes, type: %u\n", map->addr, map->len, map->type);
     total_size += map->len;
     map++;
   }
   debug("Total Memory size: %llu bytes\n", total_size);
   uint32_t *available_addr = (uint32_t *) 0xfffc0000;
   debug("Read: Ox%x -> %d\n", available_addr, *available_addr);
   *available_addr = 42;
   debug("Write: Ox%x -> %d\n", available_addr, *available_addr);
}
