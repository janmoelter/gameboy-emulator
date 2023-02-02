#pragma once

#include "common.hpp"

#include "rom.hpp"

namespace gameboy
{
	class bus;

	class cartridge : rom
	{
		friend class bus;

	public:
		cartridge(std::ifstream&);
		cartridge(void);
		~cartridge(void);

		enum struct TYPE : std::uint8_t
		{
			ROM_Only = 0x00,
			MBC1 = 0x01,
			MBC1_RAM = 0x02,
			MBC1_RAM_Battery = 0x03,
			MBC2 = 0x05,
			MBC2_RAM_Battery = 0x06,
			ROM_RAM = 0x08,
			ROM_RAM_Battery = 0x09,
			MMM01 = 0x0B,
			MMM01_RAM = 0x0C,
			MMM01_RAM_Battery = 0x0D,
			MBC3_Timer_Battery = 0x0F,
			MBC3_Timer_RAM_Battery = 0x10,
			MBC3 = 0x11,
			MBC3_RAM = 0x12,
			MBC3_RAM_Battery = 0x13,
			MBC5 = 0x19,
			MBC5_RAM = 0x1A,
			MBC5_RAM_Battery = 0x1B,
			MBC5_Rumble = 0x1C,
			MBC5_Rumble_RAM = 0x1D,
			MBC5_Rumble_RAM_Battery = 0x1E,
			MBC6 = 0x20,
			MBC7_Sensor_Rumble_RAM_Battery = 0x22,
			POCKET_CAMERA = 0xFC,
			BANDAI_TAMA5 = 0xFD,
			HuC3 = 0xFE,
			HuC1_RAM_Battery = 0xFF,
		};

	private:

		static const std::map<cartridge::TYPE, std::string> TYPE_DESCRIPTION;
		static const std::map<std::uint8_t, std::string> OLD_LICENSEE;
		static const std::map<std::uint8_t, std::string> NEW_LICENSEE;

		cartridge::TYPE _type;
		std::uint32_t _size;
		std::uint32_t _rom_size;
		std::uint8_t _rom_banks;
		std::uint32_t _ram_size;
		std::uint8_t _ram_banks;
		std::string _title;
		std::string _licensee;
		bool _destination;

	public:
		
	};
}
