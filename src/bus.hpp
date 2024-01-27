#pragma once

#include "common.hpp"

#include "clock.hpp"
#include "memory.hpp"
#include "cpu.hpp"
#include "gpu.hpp"
#include "rom.hpp"
#include "cartridge.hpp"
#include "interface.hpp"

namespace gameboy
{
	class bus
	{
		friend class clock;
		friend class memory;
		friend class cpu;
		friend class gpu;
		friend class rom;
		friend class cartridge;
		friend class interface;

	public:
		bus(clock&, memory&, cpu&, gpu&, rom&, cartridge&, interface&);
		~bus(void);

		bool DEBUG_MODE = false;
		bool CPU_OPS = false;
		bool ENABLE_DISPLAY = true;
		bool THROTTLING = true;

		bool TERMINATE = false;

	private:
		clock& _clock;
		memory& _memory;
		cpu& _cpu;
		gpu& _gpu;

		rom& _bootrom;
		cartridge& _cartridge;

		interface& _interface;

		//bool _BOOTPHASE = true;

		const std::uint16_t& get_program_counter();

		std::uint8_t& get_memory_value(const std::uint16_t&);

	public:
		bool _BOOTPHASE = true;

		void initialise_system(void);

		void load_bootrom(void);
		void load_cartridge(void);
		void load_cartridge_rom(const std::uint8_t&);
		void load_cartridge_ram(const std::uint8_t&);

		void initialise_IO_registers(void);

		void skip_bootrom(void);

		enum struct INTERRUPT : std::uint8_t
		{
			VBlank = 0x00,
			LCD_STAT = 0x01,
			Timer = 0x02,
			Serial = 0x03,
			Joypad = 0x04,
		};

		enum struct JOYPAD : std::uint8_t
		{
			None = 0b11111111,
			Right = 0b11101110,
			Left = 0b11101101,
			Up = 0b11101011,
			Down = 0b11100111,
			A = 0b11011110,
			B = 0b11011101,
			Select = 0b11011011,
			Start = 0b11010111,
		};

		void request_interrupt(const INTERRUPT&);

		void request_joypadinput(const JOYPAD&);

		const std::uint16_t& advance(void);

		std::uint8_t& get_u8_memory_value(const std::uint16_t&);
		std::uint8_t& get_u8_memory_value(const memory::$&);
		std::uint16_t& get_u16_memory_value(const std::uint16_t&);
		std::uint16_t& get_u16_memory_value(const memory::$&);

		void hook(void);
		
	};
}
