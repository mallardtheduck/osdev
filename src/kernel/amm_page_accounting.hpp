#ifndef _AMM_PAGE_ACCOUNTING_HPP
#define _AMM_PAGE_ACCOUNTING_HPP

#include "kernel.hpp"
struct vmm_region;

namespace amm_page_type{
    enum Enum{
        Free,
        PageTable,
        Kernel,
        Userspace,
        IOFixed,
    };
}

uint32_t init_amm_page_accounting(vmm_region regions[], void *kend);
void amm_accounting_add_free_page(uint32_t pageaddr);
void amm_accounting_mark_page(uint32_t pageaddr, amm_page_type::Enum type, void *info);
uint32_t amm_accounting_get_free_page(uint32_t max=0xFFFFFFFF);
size_t amm_accounting_count_free_pages();

#endif