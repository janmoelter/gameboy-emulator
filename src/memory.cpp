#include "memory.hpp"
#include "bus.hpp"

using namespace gameboy;

memory::memory(void)
{
	for (size_t i = 0; i < this->_memory.size(); i++)
	{
		//this->_memory[i] = rand() % 0x100;
		//this->_memory[i] = 0xFF;
		this->_memory[i] = 0x00;
	}
}

memory::~memory(void)
{
	
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
	this->dump(this->RAM());
}

void memory::dump(std::ofstream& file, std::span<std::uint8_t> memory_view)
{
	std::copy(memory_view.begin(), memory_view.end(), std::ostreambuf_iterator<char>(file));
}

void memory::dump(std::ofstream& file)
{
	this->dump(file, this->RAM());
}

void memory::load_dump(std::ifstream& file)
{
	std::vector<std::uint8_t> _dump = std::vector<std::uint8_t>((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	std::copy_n(_dump.begin(), 0x10000, this->_memory.begin());
}
