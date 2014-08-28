#ifndef _AMM_HPP
#define _AMM_HPP

void amm_init();
void amm_mark_alloc(uint32_t pageaddr, uint32_t flags, pid_t owner, void *ptr);
void amm_mark_free(uint32_t pageaddr);
uint32_t amm_get_flags(uint32_t pageaddr);

#endif