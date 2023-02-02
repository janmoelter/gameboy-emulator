#pragma once

#include "common.hpp"

namespace gameboy
{
	class bus;

	class memory
	{
		friend class bus;

	public:
		memory(void);
		~memory(void);

	private:
		bus* _bus;
		std::array<std::uint8_t, 0x10000> _memory;


	public:
		enum struct $ : std::uint16_t
		{
			ROM0 = 0x0000,
			ROMn = 0x4000,
			VRAM = 0x8000,
			XRAM = 0xA000,
			WRAM0 = 0xC000,
			WRAMn = 0xD000,
			ECHORAM = 0xE000,
			OAM = 0xFE00,
			//
			P1 = 0xFF00,
			SB = 0xFF01,
			SC = 0xFF02,
			DIV = 0xFF04,
			TIMA = 0xFF05,
			TMA = 0xFF06,
			TAC = 0xFF07,
			IF = 0xFF0F,
			NR10 = 0xFF10,
			NR11 = 0xFF11,
			NR12 = 0xFF12,
			NR13 = 0xFF13,
			NR14 = 0xFF14,
			NR21 = 0xFF16,
			NR22 = 0xFF17,
			NR23 = 0xFF18,
			NR24 = 0xFF19,
			NR30 = 0xFF1A,
			NR31 = 0xFF1B,
			NR32 = 0xFF1C,
			NR33 = 0xFF1D,
			NR34 = 0xFF1E,
			NR41 = 0xFF20,
			NR42 = 0xFF21,
			NR43 = 0xFF22,
			NR44 = 0xFF23,
			NR50 = 0xFF24,
			NR51 = 0xFF25,
			NR52 = 0xFF26,
			LCDC = 0xFF40,
			STAT = 0xFF41,
			SCY = 0xFF42,
			SCX = 0xFF43,
			LY = 0xFF44,
			LYC = 0xFF45,
			DMA = 0xFF46,
			BGP = 0xFF47,
			OBP0 = 0xFF48,
			OBP1 = 0xFF49,
			WY = 0xFF4A,
			WX = 0xFF4B,
			KEY1 = 0xFF4D,
			VBK = 0xFF4F,
			//
			BOOTROMCTRL = 0xFF50,
			//
			HDMA1 = 0xFF51,
			HDMA2 = 0xFF52,
			HDMA3 = 0xFF53,
			HDMA4 = 0xFF54,
			HDMA5 = 0xFF55,
			RP = 0xFF56,
			BCPS = 0xFF68,
			BCPD = 0xFF69,
			OCPS = 0xFF6A,
			OCPD = 0xFF6B,
			SVBK = 0xFF70,
			//
			HRAM = 0xFF80,
			IE = 0xFFFF,
		};

		std::span<std::uint8_t, 0x10000> RAM(void) {
			return std::span(&_memory[0x0000], 0x10000);
		};

		std::span<std::uint8_t, 0x0100> BOOTROM(void) {
			return std::span(&_memory[0x0000], 0x0100);
		};

		std::span<std::uint8_t, 0x8000> ROM(void) {
			return std::span(&_memory[0x0000], 0x8000);
		};
		std::span<std::uint8_t, 0x4000> ROM0(void) {
			return std::span(&_memory[0x0000], 0x4000);
		};
		std::span<std::uint8_t, 0x4000> ROMn(void) {
			return std::span(&_memory[0x4000], 0x4000);
		};

		std::span<std::uint8_t, 0x2000> VRAM(void) {
			return std::span(&_memory[0x8000], 0x2000);
		};
		std::span<std::uint8_t, 0x2000> XRAM(void) {
			return std::span(&_memory[0xA000], 0x2000);
		};

		std::span<std::uint8_t, 0x2000> WRAM(void) {
			return std::span(&_memory[0xC000], 0x2000);
		};
		std::span<std::uint8_t, 0x1000> WRAM0(void) {
			return std::span(&_memory[0xC000], 0x1000);
		};
		std::span<std::uint8_t, 0x1000> WRAMn(void) {
			return std::span(&_memory[0xD000], 0x1000);
		};

		std::span<std::uint8_t, 0x1E00> ECHORAM(void) {
			return std::span(&_memory[0xE000], 0x1E00);
		};

		std::span<std::uint8_t, 0x00A0> OAMRAM(void) {
			return std::span(&_memory[0xFE00], 0x00A0);
		};

		std::span<std::uint8_t, 0x0080> IO(void) {
			return std::span(&_memory[0xFF00], 0x0080);
		};
		std::uint8_t& IF(void) {
			return _memory[0xFF0F];
		};
		std::span<std::uint8_t, 0x007F> HRAM(void) {
			return std::span(&_memory[0xFF80], 0x007F);
		};
		std::uint8_t& IE(void) {
			return _memory[0xFFFF];
		};

		void dump(std::span<std::uint8_t>);
		void dump();

		void dump(std::ofstream&, std::span<std::uint8_t>);
		void dump(std::ofstream&);
		void load_dump(std::ifstream&);

	};
	
}
