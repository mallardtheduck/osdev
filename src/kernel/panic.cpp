#include "panic.hpp"
#include "io.hpp"

#define	VGA_AC_INDEX		0x3C0
#define	VGA_AC_WRITE		0x3C0
#define	VGA_AC_READ		0x3C1
#define	VGA_MISC_WRITE		0x3C2
#define VGA_SEQ_INDEX		0x3C4
#define VGA_SEQ_DATA		0x3C5
#define	VGA_DAC_READ_INDEX	0x3C7
#define	VGA_DAC_WRITE_INDEX	0x3C8
#define	VGA_DAC_DATA		0x3C9
#define	VGA_MISC_READ		0x3CC
#define VGA_GC_INDEX 		0x3CE
#define VGA_GC_DATA 		0x3CF
/*			COLOR emulation		MONO emulation */
#define VGA_CRTC_INDEX		0x3D4		/* 0x3B4 */
#define VGA_CRTC_DATA		0x3D5		/* 0x3B5 */
#define	VGA_INSTAT_READ		0x3DA

#define	VGA_NUM_SEQ_REGS	5
#define	VGA_NUM_CRTC_REGS	25
#define	VGA_NUM_GC_REGS		9
#define	VGA_NUM_AC_REGS		21
#define	VGA_NUM_REGS		(1 + VGA_NUM_SEQ_REGS + VGA_NUM_CRTC_REGS + \
				VGA_NUM_GC_REGS + VGA_NUM_AC_REGS)

unsigned char g_80x25_text[] =
        {
/* MISC */
                0x67,
/* SEQ */
                0x03, 0x00, 0x03, 0x00, 0x02,
/* CRTC */
                0x5F, 0x4F, 0x50, 0x82, 0x55, 0x81, 0xBF, 0x1F,
                0x00, 0x4F, 0x0D, 0x0E, 0x00, 0x00, 0x00, 0x50,
                0x9C, 0x0E, 0x8F, 0x28, 0x1F, 0x96, 0xB9, 0xA3,
                0xFF,
/* GC */
                0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x0E, 0x00,
                0xFF,
/* AC */
                0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x14, 0x07,
                0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,
                0x0C, 0x00, 0x0F, 0x08, 0x00
        };

void write_regs(unsigned char *regs)
{
    unsigned i;

/* write MISCELLANEOUS reg */
    outb(VGA_MISC_WRITE, *regs);
    regs++;
/* write SEQUENCER regs */
    for(i = 0; i < VGA_NUM_SEQ_REGS; i++)
    {
        outb(VGA_SEQ_INDEX, i);
        outb(VGA_SEQ_DATA, *regs);
        regs++;
    }
/* unlock CRTC registers */
    outb(VGA_CRTC_INDEX, 0x03);
    outb(VGA_CRTC_DATA, inb(VGA_CRTC_DATA) | 0x80);
    outb(VGA_CRTC_INDEX, 0x11);
    outb(VGA_CRTC_DATA, inb(VGA_CRTC_DATA) & ~0x80);
/* make sure they remain unlocked */
    regs[0x03] |= 0x80;
    regs[0x11] &= ~0x80;
/* write CRTC regs */
    for(i = 0; i < VGA_NUM_CRTC_REGS; i++)
    {
        outb(VGA_CRTC_INDEX, i);
        outb(VGA_CRTC_DATA, *regs);
        regs++;
    }
/* write GRAPHICS CONTROLLER regs */
    for(i = 0; i < VGA_NUM_GC_REGS; i++)
    {
        outb(VGA_GC_INDEX, i);
        outb(VGA_GC_DATA, *regs);
        regs++;
    }
/* write ATTRIBUTE CONTROLLER regs */
    for(i = 0; i < VGA_NUM_AC_REGS; i++)
    {
        (void)inb(VGA_INSTAT_READ);
        outb(VGA_AC_INDEX, i);
        outb(VGA_AC_WRITE, *regs);
        regs++;
    }
/* lock 16-color palette and unblank display */
    (void)inb(VGA_INSTAT_READ);
    outb(VGA_AC_INDEX, 0x20);
}

void reset_vga(){
    write_regs(g_80x25_text);
    outb(0x3D4, 0x0A);
    outb(0x3D5, (1 << 5));
    memset((char*)0xB8000, 0, 32768);
}

void set_vga_background(uint8_t colour){
    for(size_t r=0; r<25; ++r){
        for(size_t c=0; c<80; ++c){
            ((uint16_t*)0xB8000)[(r*80)+c] |= colour << 8;
        }
    }
}

void write_string_at(size_t row, size_t col, char *string, uint8_t attr=0){
    size_t i=0;
    for(size_t r=row; r<25; ++r){
        for(size_t c=col; c<80; ++c){
            if(!string[i]) return;
            if(string[i]=='\n') string[i]=' ';
            ((char*)0xB8000)[((r*80)+c)*2] = string[i];
            if(attr) ((uint8_t*)0xB8000)[(((r*80)+c)*2)+1] = attr;
            ++i;
        }
        col=0;
    }
}

void panic(char *msg){
    char buf[32]={0};
    dbgout("PANIC: ");dbgout(msg);
    disable_interrupts();
    reset_vga();
    set_vga_background(1<<4);
    write_string_at(2, 33, " SYSTEM ERROR ", 0xF0);
    write_string_at(5, 2, "A system error has occured and " KERNEL_OS_NAME " has been halted to prevent damage to", 0x1F);
    write_string_at(6, 2, "your computer. This may be caused by a hardware error or defective driver.", 0x1F);
    write_string_at(8, 2, "Any unsaved work may have been lost.", 0x1F);
    write_string_at(10, 2, "The technical description of the error was:", 0x1F);
    write_string_at(11, 4, msg, 0x1C);
    write_string_at(12, 2, "Proccess ID:", 0x1F);
    itoa(proc_current_pid, buf, 10);
    write_string_at(12, 15, buf, 0x1C);
    write_string_at(12, 20, "Thread ID:", 0x1F);
    itoa(sch_get_id(), buf, 10);
    write_string_at(12, 31, buf, 0x1C);
    write_string_at(12, 38, "Stored EIP:", 0x1F);
    itoa(sch_get_eip(), buf, 16);
    write_string_at(12, 50, buf, 0x1C);
    write_string_at(14, 2, "Additional information may be available in the error log (if enabled).", 0x1F);
    write_string_at(17, 24, " Please restart your computer. ", 0xF0);
    asm volatile("hlt");
}