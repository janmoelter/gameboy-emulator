#include "memory.hpp"
#include "bus.hpp"

using namespace gameboy;

memory::memory(void)
{
	this->VRAM = std::span(&this->_vram[0x0000], 0x2000);
	this->XRAM = std::span(&this->_xram[0x0000], 0x2000);
	this->WRAM0 = std::span(&this->_wram0[0x0000], 0x1000);
	this->WRAMn = std::span(&this->_wramn[0x0000], 0x1000);
	this->OAMRAM = std::span(&this->_oamram[0x0000], 0x00A0);
	this->IO = std::span(&this->_io[0x0000], 0x0080);
	this->HRAM = std::span(&this->_hram[0x0000], 0x007F);
	this->IE = std::span(&this->_ie[0x0000], 0x0001);
}

memory::~memory(void)
{
	
}

std::uint8_t& memory::get_value(const std::uint16_t& a)
{
	switch (a)
	{
		case 0x0000 ... 0x3FFF: // ROM0
			if (this->_bus->_BOOTPHASE && a < 0x0100)
			{
				return this->BOOTROM[a - 0x0000];
			}
			else
			{
				return this->ROM0[a - 0x0000];
			}
			break;
		case 0x4000 ... 0x7FFF: // ROMn
			return this->ROMn[a - 0x4000];
			break;
		case 0x8000 ... 0x9FFF: // VRAM
			return this->VRAM[a - 0x8000];
			break;
		case 0xA000 ... 0xBFFF: // XRAM
			return this->XRAM[a - 0xA000];
			break;
		case 0xC000 ... 0xCFFF: // WRAM0
			return this->WRAM0[a - 0xC000];
			break;
		case 0xD000 ... 0xDFFF: // WRAMn
			return this->WRAMn[a - 0xD000];
			break;
		case 0xE000 ... 0xEFFF: // ECHORAM (WRAM0)
			return this->WRAM0[a - 0xE000];
			break;
		case 0xF000 ... 0xFDFF: // ECHORAM (WRAMn)
			return this->WRAMn[a - 0xF000];
			break;
		case 0xFE00 ... 0xFE9F: // OAMRAM
			return this->OAMRAM[a - 0xFE00];
			break;
		case 0xFF00 ... 0xFF7F: // IO
			return this->IO[a - 0xFF00];
			break;
		case 0xFF80 ... 0xFFFE: // HRAM
			return this->HRAM[a - 0xFF80];
			break;
		case 0xFFFF: // IE
			return this->IE[a - 0xFFFF];
			break;
		default:
			return this->_zero;
			break;
	}
}

std::uint8_t& memory::get_value(const memory::$& a)
{
	return this->get_value(static_cast<std::uint16_t>(a));
}

void memory::dump(std::span<std::uint8_t> memory_view)
{
	for (auto it = memory_view.begin(); it != memory_view.end(); ++it)
	{
		auto i = std::distance(memory_view.begin(), it);
		if (i % 0x10 == 0)
		{
			std::cout << std::endl;
			std::cout << hex(4) << i;
			std::cout << "  ";
		}

		std::cout << " " << hex(2) << static_cast<int>(*it);
	}

	std::cout << std::endl;
}

void memory::dump()
{
	//this->dump(this->RAM());
}

void memory::dump(std::ofstream& file, std::span<std::uint8_t> memory_view)
{
	//std::copy(memory_view.begin(), memory_view.end(), std::ostreambuf_iterator<char>(file));
}

void memory::dump(std::ofstream& file)
{
	//this->dump(file, this->RAM());
}

void memory::load_dump(std::ifstream& file)
{
	//std::vector<std::uint8_t> _dump = std::vector<std::uint8_t>((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	//std::copy_n(_dump.begin(), 0x10000, this->_memory.begin());
}
