#include "bus.hpp"

using namespace gameboy;

bus::bus(clock& clock, memory& memory, cpu& cpu, gpu& gpu, rom& bootrom, cartridge& cartridge, interface& interface)
	: _clock(clock), _memory(memory), _cpu(cpu), _gpu(gpu), _bootrom(bootrom), _cartridge(cartridge), _interface(interface)
{
	this->_clock._bus = this;
	this->_memory._bus = this;
	this->_cpu._bus = this;
	this->_gpu._bus = this;
	this->_bootrom._bus = this;
	this->_cartridge._bus = this;
	this->_interface._bus = this;


	std::uint8_t ROM_u8;
	std::uint8_t CRT_u8;

	for (size_t i = 0; i < 0x30; i++)
	{
		ROM_u8 = this->_bootrom._rom[0x00A8 + i];
		CRT_u8 = this->_cartridge._rom[0x0104 + i];
	}
}

bus::~bus()
{

}

void bus::initialise_system(void)
{
	this->initialise_IO_registers();
	
	this->load_bootrom();
	this->load_cartridge();
	
	if (this->ENABLE_DISPLAY)
	{
		this->_interface.create_window();
	}
}

void bus::load_bootrom(void)
{
	this->_memory.BOOTROM = std::span(&this->_bootrom._rom[0x0000], 0x0100);
}

void bus::load_cartridge(void)
{
	this->load_cartridge_rom(0);
	this->load_cartridge_rom(1);
}

void bus::load_cartridge_rom(const std::uint8_t& n)
{
	if (n == 0)
	{
		this->_memory.ROM0 = std::span(&this->_cartridge._rom[0x0000], 0x4000);
	}
	else
	{
		this->_memory.ROMn = std::span(&this->_cartridge._rom[n * 0x4000], 0x4000);
	}
}

void bus::load_cartridge_ram(const std::uint8_t& n)
{
	
}

void bus::initialise_IO_registers(void)
{
	this->get_u8_memory_value(memory::$::P1) = 0xCF;
	this->get_u8_memory_value(memory::$::SB) = 0x00;
	this->get_u8_memory_value(memory::$::SC) = 0x7E;
	this->get_u8_memory_value(memory::$::DIV) = 0xAB;
	this->get_u8_memory_value(memory::$::TIMA) = 0x00;
	this->get_u8_memory_value(memory::$::TMA) = 0x00;
	this->get_u8_memory_value(memory::$::TAC) = 0xF8;
	this->get_u8_memory_value(memory::$::IF) = 0xE1;
	this->get_u8_memory_value(memory::$::NR10) = 0x80;
	this->get_u8_memory_value(memory::$::NR11) = 0xBF;
	this->get_u8_memory_value(memory::$::NR12) = 0xF3;
	this->get_u8_memory_value(memory::$::NR13) = 0xFF;
	this->get_u8_memory_value(memory::$::NR14) = 0xBF;
	this->get_u8_memory_value(memory::$::NR21) = 0x3F;
	this->get_u8_memory_value(memory::$::NR22) = 0x00;
	this->get_u8_memory_value(memory::$::NR23) = 0xFF;
	this->get_u8_memory_value(memory::$::NR24) = 0xBF;
	this->get_u8_memory_value(memory::$::NR30) = 0x7F;
	this->get_u8_memory_value(memory::$::NR31) = 0xFF;
	this->get_u8_memory_value(memory::$::NR32) = 0x9F;
	this->get_u8_memory_value(memory::$::NR33) = 0xFF;
	this->get_u8_memory_value(memory::$::NR34) = 0xBF;
	this->get_u8_memory_value(memory::$::NR41) = 0xFF;
	this->get_u8_memory_value(memory::$::NR42) = 0x00;
	this->get_u8_memory_value(memory::$::NR43) = 0x00;
	this->get_u8_memory_value(memory::$::NR44) = 0xBF;
	this->get_u8_memory_value(memory::$::NR50) = 0x77;
	this->get_u8_memory_value(memory::$::NR51) = 0xF3;
	this->get_u8_memory_value(memory::$::NR52) = 0xF1;
	this->get_u8_memory_value(memory::$::LCDC) = 0b00010001; // == 0x91;
	this->get_u8_memory_value(memory::$::STAT) = 0x85;
	this->get_u8_memory_value(memory::$::SCY) = 0x00; 
	this->get_u8_memory_value(memory::$::SCX) = 0x00; 
	this->get_u8_memory_value(memory::$::LY) = 0x00;
	this->get_u8_memory_value(memory::$::LYC) = 0x00; 
	this->get_u8_memory_value(memory::$::DMA) = 0xFF; 
	this->get_u8_memory_value(memory::$::BGP) = 0xFC; 
	this->get_u8_memory_value(memory::$::OBP0) = 0x00;
	this->get_u8_memory_value(memory::$::OBP1) = 0x00;
	this->get_u8_memory_value(memory::$::WY) = 0x00;
	this->get_u8_memory_value(memory::$::WX) = 0x00;
	this->get_u8_memory_value(memory::$::KEY1) = 0xFF;
	this->get_u8_memory_value(memory::$::VBK) = 0xFF; 
	this->get_u8_memory_value(memory::$::HDMA1) = 0xFF;
	this->get_u8_memory_value(memory::$::HDMA2) = 0xFF;
	this->get_u8_memory_value(memory::$::HDMA3) = 0xFF;
	this->get_u8_memory_value(memory::$::HDMA4) = 0xFF;
	this->get_u8_memory_value(memory::$::HDMA5) = 0xFF;
	this->get_u8_memory_value(memory::$::RP) = 0xFF;
	this->get_u8_memory_value(memory::$::BCPS) = 0xFF;
	this->get_u8_memory_value(memory::$::BCPD) = 0xFF;
	this->get_u8_memory_value(memory::$::OCPS) = 0xFF;
	this->get_u8_memory_value(memory::$::OCPD) = 0xFF;
	this->get_u8_memory_value(memory::$::SVBK) = 0xFF;
	this->get_u8_memory_value(memory::$::IE) = 0x00;

	this->get_u8_memory_value(memory::$::HRAM) = 0xF0;


	this->get_u8_memory_value(memory::$::BOOTROMCTRL) = 0x00;
}

void bus::skip_bootrom(void)
{
	this->_cpu.initialise(0x01,0xB0,0x00,0x13,0x00,0xD8,0x01,0x4D,0xFFFE,0x0100);
	
	this->get_u8_memory_value(memory::$::BOOTROMCTRL) = 0x01;
	this->_BOOTPHASE = !static_cast<bool>(this->get_u8_memory_value(memory::$::BOOTROMCTRL));
}

const std::uint16_t& bus::advance(void)
{
	//std::uint8_t& HRAM = this->get_u8_memory_value(memory::$::HRAM);
	//HRAM = 0xF0;

	// Display Interrupts
	//std::uint8_t& IE = this->get_u8_memory_value(memory::$::IE);
	//std::uint8_t& IF = this->get_u8_memory_value(memory::$::IE);
	//
	//if (IF > 0)
	//{
	//	std::cout << "Enabled:   " << std::bitset<8>(IE) << std::endl;
	//	std::cout << "Requested: " << std::bitset<8>(IF) << std::endl;
	//}


	std::uint8_t cpu_cycles;

	cpu_cycles = this->_cpu.next();
	this->_clock.increment(cpu_cycles);

	if (this->_clock._gpu_tick)
	{
		this->_gpu.render_screen();
		this->_clock._gpu_tick = false;

		this->_interface.update_window();
	}

	cpu_cycles = this->_cpu.handle_interrupts();
	this->_clock.increment(cpu_cycles);

	
	this->_BOOTPHASE = !static_cast<bool>(this->get_u8_memory_value(memory::$::BOOTROMCTRL));

	if(this->get_u8_memory_value(this->_cpu.PC()) == 0x18 & this->get_u8_memory_value(this->_cpu.PC() + 1) == 0xFE)
	{
		this->TERMINATE = true;
	}

	if (this->ENABLE_DISPLAY && !this->_interface._window.isOpen())
	{
		this->TERMINATE = true;
	}

	return this->get_program_counter();
}

void bus::request_interrupt(const bus::INTERRUPT& i)
{
	std::uint8_t& IF = this->get_u8_memory_value(memory::$::IF);

	IF |= (0b1 << static_cast<std::uint8_t>(i));
}

void bus::request_joypadinput(const bus::JOYPAD& b)
{
	std::uint8_t& P1 = this->get_u8_memory_value(memory::$::P1);

	P1 = static_cast<std::uint8_t>(b);
	if (b != bus::JOYPAD::None)
	{
		this->request_interrupt(bus::INTERRUPT::Joypad);
	}
}

const std::uint16_t& bus::get_program_counter()
{
	return this->_cpu.PC();
}

std::uint8_t& bus::get_memory_value(const std::uint16_t& a)
{
	if (a == static_cast<std::uint16_t>(memory::$::P1))
	{
		// no button pressed
		std::uint8_t& P1 = this->_memory.get_value(static_cast<std::uint16_t>(memory::$::P1));
		if (P1 & (1 << 5))
		{
			P1 |= 0x0E;
			this->request_interrupt(INTERRUPT::Joypad);
		}
		else
		{
			P1 |= 0x0F;
		}
	}
	
	return this->_memory.get_value(a);
}

std::uint8_t& bus::get_u8_memory_value(const std::uint16_t& a)
{
	return *reinterpret_cast<std::uint8_t*>(&this->get_memory_value(a));
}

std::uint8_t& bus::get_u8_memory_value(const memory::$& a)
{
	return this->get_u8_memory_value(static_cast<std::uint16_t>(a));
}

std::uint16_t& bus::get_u16_memory_value(const std::uint16_t& a)
{
#if !(__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
	#warning "Definition of cpu::u16_memory_value assumes a little-endian system."
#endif

	return *reinterpret_cast<std::uint16_t*>(&this->get_memory_value(a));
}

std::uint16_t& bus::get_u16_memory_value(const memory::$& a)
{
	return this->get_u16_memory_value(static_cast<std::uint16_t>(a));
}

void bus::hook(void)
{
	
}
