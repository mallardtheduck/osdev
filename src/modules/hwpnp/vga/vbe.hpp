#ifndef _VBE_HPP
#define _VBE_HPP

#include <btos_module.h>
#include <util/ministl.hpp>
#include <dev/video_dev.h>

typedef uint16_t Real_Pointer[2];

struct VBE_Info {
	char Signature[4];
	uint16_t Version;
	Real_Pointer OemStringPtr;
	uint32_t Capabilities;
	Real_Pointer VideoModePtr;
	uint16_t TotalMemory;
	uint32_t OemSoftwareRev;
	Real_Pointer OemVendorNamePtr;
	Real_Pointer OemProductNamePtr;
	Real_Pointer OemProductRevPtr;
} __attribute__((packed));

struct VBE_ModeInfo {
	uint16_t ModeAttributes;
	uint8_t WinAAttributes, WinBAttributes;
	uint16_t WinGranularity;
	uint16_t WinSize;
	uint16_t WinASegment, WinBSegment;
	Real_Pointer WinFuncPtr;
	uint16_t BytesPerScanLine;

	uint16_t XResolution, YResolution;
	uint8_t XCharSize, YCharSize;
	uint8_t NumberOfPlanes, BitsPerPixel, NumberOfBanks;
	uint8_t MemoryModel, BankSize, NumberOfImagePages;
	uint8_t Reserved0;

	uint8_t RedMaskSize, RedFieldPosition;
	uint8_t GreenMaskSize, GreenFieldPosition;
	uint8_t BlueMaskSize, BlueFieldPosition;
	uint8_t RsvdMaskSize, RsvdFieldPosition;
	uint8_t DirectColorModeInfo;

	uint32_t PhysBasePtr; 
	uint32_t OffScreenMemOffset;
	uint16_t OffScreenMemSize;
} __attribute__((packed));

extern map<uint16_t, VBE_ModeInfo> *vbe_modes;

namespace VBE_Attribute{
	static const uint16_t Supported = (1 << 0);
	static const uint16_t Reserved0 = (1 << 1);
	static const uint16_t BiosTTY = (1 << 2);
	static const uint16_t Colour = (1 << 3);
	static const uint16_t Graphics = (1 << 4);
	static const uint16_t NonVGA = (1 << 5);
	static const uint16_t VGAWinMode = (1 << 6);
	static const uint16_t LinearMode = (1 << 7);
}

namespace VBE_MemoryModel{
	static const uint8_t Text = 0x00;
	static const uint8_t CGA = 0x01;
	static const uint8_t Hercules = 0x02;
	static const uint8_t Planar = 0x03;
	static const uint8_t Packed = 0x04;
	static const uint8_t NonChain = 0x05;
	static const uint8_t DirectColour = 0x06;
	static const uint8_t YUV = 0x07;
}

bool vbe_init();

void VBE_ResetToVGA();
VBE_Info VBE_GetInfo();
VBE_ModeInfo VBE_GetModeInfo(uint16_t mode);
void VBE_SetMode(uint16_t modeId, bool linear);
bt_video_palette_entry VBE_GetPaletteEntry(uint8_t index);
void VBE_SetPalette(void *address);

extern uint32_t vbe_current_mode;
extern char *fb;
extern size_t fb_sz;
extern VBE_ModeInfo modeinfo;

bool is_vbe_mode(uint32_t mode_id = vbe_current_mode);
bt_vidmode make_vidmode_from_id(uint16_t id);
void map_fb();
void unmap_fb();
void set_palette();
void vbe_clear_screen();
bt_video_palette_entry get_palette_entry(uint8_t entry);
bt_vidmode make_vidmode_from_index(size_t idx);

#endif
