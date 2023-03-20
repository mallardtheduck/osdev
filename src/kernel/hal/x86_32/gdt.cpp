#include "../../kernel.hpp"

struct gdt_ptr_struct
{
   uint16_t limit;               // The upper 16 bits of all selector limits.
   uint32_t base;                // The address of the first gdt_entry_t struct.
}
 __attribute__((packed));
typedef struct gdt_ptr_struct gdt_ptr_t;

// This structure contains the value of one GDT entry.
// We use the attribute 'packed' to tell GCC not to change
// any of the alignment in the structure.
struct gdt_entry_struct
{
   uint16_t limit_low;           // The lower 16 bits of the limit.
   uint16_t base_low;            // The lower 16 bits of the base.
   uint8_t  base_middle;         // The next 8 bits of the base.
   uint8_t  access;              // Access flags, determine what ring this segment can be used in.
   uint8_t  granularity;
   uint8_t  base_high;           // The last 8 bits of the base.
} __attribute__((packed));
typedef struct gdt_entry_struct gdt_entry_t;

struct tss_entry{
   uint32_t prev_tss;   // The previous TSS - if we used hardware task switching this would form a linked list.
   uint32_t esp0;       // The stack pointer to load when we change to kernel mode.
   uint32_t ss0;        // The stack segment to load when we change to kernel mode.
   uint32_t esp1;       // everything below here is unusued now..
   uint32_t ss1;
   uint32_t esp2;
   uint32_t ss2;
   uint32_t cr3;
   uint32_t eip;
   uint32_t eflags;
   uint32_t eax;
   uint32_t ecx;
   uint32_t edx;
   uint32_t ebx;
   uint32_t esp;
   uint32_t ebp;
   uint32_t esi;
   uint32_t edi;
   uint32_t es;
   uint32_t cs;
   uint32_t ss;
   uint32_t ds;
   uint32_t fs;
   uint32_t gs;
   uint32_t ldt;
   uint16_t trap;
   uint16_t iomap_base;
} __attribute__((packed));

// Lets us access our ASM functions from our C code.
extern "C" void gdt_flush();
extern "C" void tss_flush(/*uint8_t tss_segment*/);

// Internal function prototypes.
static void gdt_set_gate(int32_t,uint32_t,uint32_t,uint8_t,uint8_t);
static void gdt_set_tss(int32_t num);
static void gdt_set_df_tss(int32_t num);

static const size_t gdt_num_entries = 7;

gdt_entry_t gdt_entries[gdt_num_entries];
gdt_ptr_t   gdt_ptr;
tss_entry tss;
tss_entry df_tss;
uint32_t df_selector = 6;

uint32_t df_stack[1024];

void GDT_init()
{
	dbgout("GDT init\n");
	gdt_ptr.limit = (sizeof(gdt_entry_t) * gdt_num_entries) - 1;
	gdt_ptr.base  = (uint32_t)&gdt_entries;

	gdt_set_gate(0, 0, 0, 0, 0);                // Null segment
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
	gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
	gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment
	gdt_set_tss(5);
	gdt_set_df_tss(6);

	gdt_flush();
	tss_flush(/*0x2B*/);
}

// Set the value of one GDT entry.
static void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
   gdt_entries[num].base_low    = (base & 0xFFFF);
   gdt_entries[num].base_middle = (base >> 16) & 0xFF;
   gdt_entries[num].base_high   = (base >> 24) & 0xFF;

   gdt_entries[num].limit_low   = (limit & 0xFFFF);
   gdt_entries[num].granularity = (limit >> 16) & 0x0F;

   gdt_entries[num].granularity |= gran & 0xF0;
   gdt_entries[num].access      = access;
}

static void gdt_set_tss(int32_t num){
	uint32_t base = (uint32_t) &tss;
   	uint32_t limit = base + sizeof(tss_entry);
	gdt_set_gate(num, base, limit, 0xE9, 0x0F);
	memset(&tss, 0, sizeof(tss_entry));
}

static void df_handler(){
	dbgout("GDT: Double fault. TSS state:\n");
	dbgpf("GDT: ESP: %lx EIP: %lx EFLAGS: %lx\n", tss.esp, tss.eip, tss.eflags);
	dbgpf("GDT: EAX: %lx EBX: %lx ECX: %lx EDX: %lx\n", tss.eax, tss.ebx, tss.ecx, tss.edx);

	panic("(GDT) Double fault!");
}

static void gdt_set_df_tss(int32_t num){
	uint32_t base = (uint32_t) &df_tss;
	uint32_t limit = base + sizeof(tss_entry);
	gdt_set_gate(num, base, limit, 0x89, 0x0F);
	memset(&df_tss, 0, sizeof(tss_entry));
	df_tss.ss0 = 0x10;
	df_tss.esp0 = (uint32_t)&df_stack[1024];
	df_tss.cs = 0x08;
	df_tss.eip = (uint32_t)&df_handler;
	df_tss.ds = 0x10;
	df_tss.es = 0x10;
	df_tss.fs = 0x10;
	df_tss.gs = 0x10;
	df_tss.ss = 0x10;
	df_tss.esp = (uint32_t)&df_stack[1024];
}

void gdt_set_df_cr3(uint32_t cr3){
	df_tss.cr3 = cr3;
}

void gdt_set_kernel_stack(void* ptr){
	tss.ss0 = 0x10;
	tss.esp0 = (uint32_t)ptr;
}
