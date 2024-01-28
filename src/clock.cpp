#include "clock.hpp"
#include "bus.hpp"

using namespace gameboy;

clock::clock()
{
	this->_throttling = std::thread([](std::uint32_t time){std::this_thread::sleep_for(std::chrono::microseconds(time));}, 1000000 * this->_throttling_time);
}

clock::~clock()
{
	this->_throttling.join();
}

void clock::increment(const std::uint8_t& cycles)
{
	this->_cycles += cycles;

	std::uint8_t DIV = this->_bus->get_u8_memory_value(memory::$::DIV);
	std::uint8_t LY = this->_bus->get_u8_memory_value(memory::$::LY);

	std::uint8_t TIMA = this->_bus->get_u8_memory_value(memory::$::TIMA);
	const std::uint8_t& TMA = this->_bus->get_u8_memory_value(memory::$::TMA);
	const std::uint8_t& TAC = this->_bus->get_u8_memory_value(memory::$::TAC);

	std::uint16_t _timer_mod = this->_timer_mod;

	switch (TAC & 0b11)
	{
		case 0b00:
			this->_timer_mod = 1024; // => 1024 t-cycles / tick
			break;
		case 0b01:
			this->_timer_mod = 16; // => 16 t-cycles / tick
			break;
		case 0b10:
			this->_timer_mod = 64; // => 64 t-cycles / tick
			break;
		case 0b11:
			this->_timer_mod = 256; // => 256 t-cycles / tick
			break;
	}

	if (_timer_mod != this->_timer_mod)
	{
		this->_timer_ticks = this->_cycles / this->_timer_mod;
	}

	if (this->_cycles / this->_div_mod > this->_div_ticks)
	{
		this->_div_ticks += 1;
		DIV += 1;
		this->_bus->set_u8_memory_value(memory::$::DIV, DIV);
	}

	if (this->_cycles / this->_ly_mod > this->_ly_ticks)
	{
		this->_ly_ticks += 1;
		LY += 1;
		LY %= 0x99;
		this->_bus->set_u8_memory_value(memory::$::LY, LY);
		
		if (LY == 0x90)
		{
			this->_bus->request_interrupt(bus::INTERRUPT::VBlank);
			this->_gpu_ticks += 1;
			this->_gpu_tick = true;
		}
	}

	if (this->_cycles / this->_timer_mod > this->_timer_ticks)
	{
		
		this->_timer_ticks += 1;
		if (TAC & 0b0100)
		{
			TIMA += 1;
			this->_bus->set_u8_memory_value(memory::$::TIMA, TIMA);

			if (TIMA == 0x00)
			{
				TIMA = TMA;
				this->_bus->request_interrupt(bus::INTERRUPT::Timer);
			}
		}
	}

	if (this->_cycles / this->_throttling_mod > this->_throttling_ticks)
	{
		this->_throttling_ticks += 1;
		if (this->_bus->THROTTLING)
		{
			this->_throttling.join();

			this->_throttling = std::thread([](std::uint32_t time){std::this_thread::sleep_for(std::chrono::microseconds(time));}, 1000000 * this->_throttling_time);
		}
	}

}

const std::uint32_t& clock::gpu_ticks()
{
	return this->_gpu_ticks;
}
