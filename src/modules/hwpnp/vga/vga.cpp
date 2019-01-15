#include "vga.hpp"
#include "modes.hpp"
#include "device.hpp"
#include "vbe.hpp"

syscall_table *SYSCALL_TABLE;
char dbgbuf[256];

#pragma GCC diagnostic ignored "-Wunused-parameter"

volatile uint8_t * const vga_memory=(uint8_t*)0xA0000;
volatile uint8_t * const text_memory=(uint8_t*)0xB8000;

void dump_regs();

struct int_lock{
	int_lock() { disable_interrupts(); }
	~int_lock() { enable_interrupts(); }
};

extern "C" int module_main(syscall_table *systbl, char *params){
	SYSCALL_TABLE=systbl;
	//dump_regs();
	init_modes();
	vbe_init();
	init_hwpnp();
	
	return 0;
}

uint8_t read_graphics(uint8_t index){
	int_lock il;
	outb(VGA_Ports::GraphicsAddress, index);
	return inb(VGA_Ports::GraphicsData);
}

void write_graphics(uint8_t index, uint8_t byte){
	int_lock il;
	outb(VGA_Ports::GraphicsAddress, index);
	outb(VGA_Ports::GraphicsData, byte);
}

uint8_t read_sequencer(uint8_t index){
	int_lock il;
	outb(VGA_Ports::SequencerAddress, index);
	return inb(VGA_Ports::SequencerData);
}

void write_sequencer(uint8_t index, uint8_t byte){
	int_lock il;
	outb(VGA_Ports::SequencerAddress, index);
	outb(VGA_Ports::SequencerData, byte);
}

uint8_t read_crtc(uint8_t index){
	int_lock il;
	outb(VGA_Ports::CRTCAddress, index);
	return inb(VGA_Ports::CRTCData);
}

void write_crtc(uint8_t index, uint8_t byte){
	int_lock il;
	outb(VGA_Ports::CRTCAddress, index);
	outb(VGA_Ports::CRTCData, byte);
}

uint8_t read_attribute(uint8_t index){
	int_lock il;
	inb(VGA_Ports::InputStatus1);
	outb(VGA_Ports::AttributeWrite, index);
	return inb(VGA_Ports::AttributeRead);
}

void write_attribute(uint8_t index, uint8_t byte){
	int_lock il;
	inb(VGA_Ports::InputStatus1);
	outb(VGA_Ports::AttributeWrite, index);
	outb(VGA_Ports::AttributeWrite, byte);
}

void write_dac(uint8_t index, uint8_t r, uint8_t g, uint8_t b){
	int_lock il;
	if((r & 0x3F) != r) dbgpf("VGA: Bad red value: %x\n", r);
	if((g & 0x3F) != g) dbgpf("VGA: Bad green value: %x\n", g);
	if((b & 0x3F) != b) dbgpf("VGA: Bad blue value: %x\n", b);
	outb(VGA_Ports::DACWriteAddress, index);
	outb(VGA_Ports::DACData, r);
	outb(VGA_Ports::DACData, g);
	outb(VGA_Ports::DACData, b);
}

void read_dac(uint8_t index, uint8_t &r, uint8_t &g, uint8_t &b){
	int_lock il;
	outb(VGA_Ports::DACReadAddress, index);
	r=inb(VGA_Ports::DACData);
	g=inb(VGA_Ports::DACData);
	b=inb(VGA_Ports::DACData);
}

void unlock_crtc(){
	int_lock il;
	uint8_t reg= read_crtc(CRTC_Registers::EndVrtRetrace);
	reg &= ~(1 << 7);
	write_crtc(CRTC_Registers::EndVrtRetrace, reg);
	reg= read_crtc(CRTC_Registers::EndHrzBlanking);
	reg |= (1 << 7);
	write_crtc(CRTC_Registers::EndHrzBlanking, reg);
}

void lock_crtc(){
	int_lock il;
	uint8_t reg= read_crtc(CRTC_Registers::EndVrtRetrace);
	reg |= (1 << 7);
	write_crtc(CRTC_Registers::EndVrtRetrace, reg);
}

void disable_display(){
	int_lock il;
	uint8_t reg = read_sequencer(Sequencer_Registers::ClockingMode);
	reg |= (1 << 5);
	write_sequencer(Sequencer_Registers::ClockingMode, reg);
}

void enable_display(){
	int_lock il;
	uint8_t reg = read_sequencer(Sequencer_Registers::ClockingMode);
	reg &= ~(1 << 5);
	write_sequencer(Sequencer_Registers::ClockingMode, reg);
}

void dump_regs(){
	dbgpf("VGA: 1 %x\n", (int)read_sequencer(Sequencer_Registers::Reset));
	dbgpf("VGA: 2 %x\n", (int)read_sequencer(Sequencer_Registers::ClockingMode));
	dbgpf("VGA: 3 %x\n", (int)read_sequencer(Sequencer_Registers::MapMask));
	dbgpf("VGA: 4 %x\n", (int)read_sequencer(Sequencer_Registers::CharMapSelect));
	dbgpf("VGA: 5 %x\n", (int)read_sequencer(Sequencer_Registers::SeqMemoryMode));
	dbgpf("VGA: 6 %x\n", (int)read_crtc(CRTC_Registers::HrzTotal));
	dbgpf("VGA: 7 %x\n", (int)read_crtc(CRTC_Registers::EndHrzDisplay));
	dbgpf("VGA: 8 %x\n", (int)read_crtc(CRTC_Registers::StartHrzBlanking));
	dbgpf("VGA: 9 %x\n", (int)read_crtc(CRTC_Registers::EndHrzBlanking));
	dbgpf("VGA: 0 %x\n", (int)read_crtc(CRTC_Registers::StartHrzRetrace));
	dbgpf("VGA: A %x\n", (int)read_crtc(CRTC_Registers::EndHrzRetrace));
	dbgpf("VGA: B %x\n", (int)read_crtc(CRTC_Registers::VrtTotal));
	dbgpf("VGA: C %x\n", (int)read_crtc(CRTC_Registers::Overflow));
	dbgpf("VGA: D %x\n", (int)read_crtc(CRTC_Registers::PresetRowScan));
	dbgpf("VGA: E %x\n", (int)read_crtc(CRTC_Registers::MaxScanLine));
	dbgpf("VGA: F %x\n", (int)read_crtc(CRTC_Registers::CursorStart));
	dbgpf("VGA: G %x\n", (int)read_crtc(CRTC_Registers::CursorEnd));
	dbgpf("VGA: H %x\n", (int)read_crtc(CRTC_Registers::StartAddrHigh));
	dbgpf("VGA: I %x\n", (int)read_crtc(CRTC_Registers::StartAddrLow));
	dbgpf("VGA: J %x\n", (int)read_crtc(CRTC_Registers::CursorLocHigh));
	dbgpf("VGA: K %x\n", (int)read_crtc(CRTC_Registers::CursorLocLow));
	dbgpf("VGA: L %x\n", (int)read_crtc(CRTC_Registers::StartVrtRetrace));
	dbgpf("VGA: M %x\n", (int)read_crtc(CRTC_Registers::EndVrtRetrace));
	dbgpf("VGA: N %x\n", (int)read_crtc(CRTC_Registers::EndVrtDisplay));
	dbgpf("VGA: O %x\n", (int)read_crtc(CRTC_Registers::Offset));
	dbgpf("VGA: P %x\n", (int)read_crtc(CRTC_Registers::UnderlineLoc));
	dbgpf("VGA: Q %x\n", (int)read_crtc(CRTC_Registers::StartVrtBlanking));
	dbgpf("VGA: R %x\n", (int)read_crtc(CRTC_Registers::EndVrtBlanking));
	dbgpf("VGA: S %x\n", (int)read_crtc(CRTC_Registers::CRTCModeControl));
	dbgpf("VGA: T %x\n", (int)read_crtc(CRTC_Registers::LineCompare));
	dbgpf("VGA: U %x\n", (int)read_graphics(Graphics_Registers::SetReset));
	dbgpf("VGA: V %x\n", (int)read_graphics(Graphics_Registers::EnableSetReset));
	dbgpf("VGA: W %x\n", (int)read_graphics(Graphics_Registers::ColourCompare));
	dbgpf("VGA: X %x\n", (int)read_graphics(Graphics_Registers::DataRotate));
	dbgpf("VGA: Y %x\n", (int)read_graphics(Graphics_Registers::ReadMapSelect));
	dbgpf("VGA: Z %x\n", (int)read_graphics(Graphics_Registers::GraphicsMode));
	dbgpf("VGA: a %x\n", (int)read_graphics(Graphics_Registers::MiscGraphics));
	dbgpf("VGA: b %x\n", (int)read_graphics(Graphics_Registers::ColourDontCare));
	dbgpf("VGA: c %x\n", (int)read_graphics(Graphics_Registers::BitMask));
	dbgpf("VGA: d %x\n", (int)read_attribute(Attribute_Registers::Palette0));
	dbgpf("VGA: e %x\n", (int)read_attribute(Attribute_Registers::Palette1));
	dbgpf("VGA: f %x\n", (int)read_attribute(Attribute_Registers::Palette2));
	dbgpf("VGA: g %x\n", (int)read_attribute(Attribute_Registers::Palette3));
	dbgpf("VGA: h %x\n", (int)read_attribute(Attribute_Registers::Palette4));
	dbgpf("VGA: i %x\n", (int)read_attribute(Attribute_Registers::Palette5));
	dbgpf("VGA: j %x\n", (int)read_attribute(Attribute_Registers::Palette6));
	dbgpf("VGA: k %x\n", (int)read_attribute(Attribute_Registers::Palette7));
	dbgpf("VGA: l %x\n", (int)read_attribute(Attribute_Registers::Palette8));
	dbgpf("VGA: m %x\n", (int)read_attribute(Attribute_Registers::Palette9));
	dbgpf("VGA: n %x\n", (int)read_attribute(Attribute_Registers::PaletteA));
	dbgpf("VGA: o %x\n", (int)read_attribute(Attribute_Registers::PaletteB));
	dbgpf("VGA: p %x\n", (int)read_attribute(Attribute_Registers::PaletteC));
	dbgpf("VGA: q %x\n", (int)read_attribute(Attribute_Registers::PaletteD));
	dbgpf("VGA: r %x\n", (int)read_attribute(Attribute_Registers::PaletteE));
	dbgpf("VGA: s %x\n", (int)read_attribute(Attribute_Registers::PaletteF));
	dbgpf("VGA: t %x\n", (int)read_attribute(Attribute_Registers::ModeControl));
	dbgpf("VGA: u %x\n", (int)read_attribute(Attribute_Registers::OverscanColour));
	dbgpf("VGA: v %x\n", (int)read_attribute(Attribute_Registers::ColourPlaneEnable));
	dbgpf("VGA: w %x\n", (int)read_attribute(Attribute_Registers::PixelPanning));
	dbgpf("VGA: x %x\n", (int)read_attribute(Attribute_Registers::ColourSelect));
}
