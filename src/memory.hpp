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
		
		std::uint8_t _zero = 0x00;
		
		std::array<std::uint8_t, 0x2000> _vram = {0x00};
		std::array<std::uint8_t, 0x2000> _xram = {0x00};
		std::array<std::uint8_t, 0x1000> _wram0 = {0x00};
		std::array<std::uint8_t, 0x7000> _wramn = {0x00};
		std::array<std::uint8_t, 0x00A0> _oamram = {0x00};
		std::array<std::uint8_t, 0x0080> _io = {0x00};
		std::array<std::uint8_t, 0x007F> _hram = {0x00};
		std::array<std::uint8_t, 0x0001> _ie = {0x00};
		

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

		std::uint8_t& get_value(const std::uint16_t&);
		std::uint8_t& get_value(const $&);
		
		std::span<std::uint8_t> BOOTROM;
		std::span<std::uint8_t> ROM0;
		std::span<std::uint8_t> ROMn;
		std::span<std::uint8_t> VRAM;
		std::span<std::uint8_t> XRAM;
		std::span<std::uint8_t> WRAM0;
		std::span<std::uint8_t> WRAMn;
		std::span<std::uint8_t> ECHORAM;
		std::span<std::uint8_t> OAMRAM;
		std::span<std::uint8_t> IO;
		std::span<std::uint8_t> HRAM;
		std::span<std::uint8_t> IE;
		

		void dump(std::span<std::uint8_t>);
		void dump();

		void dump(std::ofstream&, std::span<std::uint8_t>);
		void dump(std::ofstream&);
		void load_dump(std::ifstream&);

	};
	
}
