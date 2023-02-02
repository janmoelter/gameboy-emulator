#include "rom.hpp"
#include "bus.hpp"

using namespace gameboy;

rom::rom(std::ifstream& file)
{
	this->_rom = std::vector<std::uint8_t>((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

rom::rom()
{
	this->_rom = std::vector<std::uint8_t>();
}

rom::~rom()
{

}
