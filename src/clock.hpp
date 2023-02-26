#pragma once

#include "common.hpp"

namespace gameboy
{
	class bus;

	class clock
	{
		friend class bus;

	public:
		clock(void);
		~clock(void);

	private:

		bus* _bus;

		std::uint64_t _cycles = 0;

		const std::uint32_t _base_frequency = 2 * 4194304; // Hz

		const std::uint16_t _div_mod = 256; // => 256 t-cycles / tick
		const std::uint16_t _ly_mod = 456; // => 456 t-cycles / tick
		std::uint16_t _timer_mod = 0; // => ? t-cycles / tick
		
		std::uint64_t _div_ticks = 0;
		std::uint64_t _ly_ticks = 0;
		std::uint64_t _timer_ticks = 0;


		const std::uint32_t _throttling_mod = static_cast<std::uint32_t>(154*456); // => ___ t-cycles / tick
		std::uint64_t _throttling_ticks = 0;
		float _throttling_time = static_cast<float>(this->_throttling_mod) / static_cast<float>(this->_base_frequency); // => s / tick
		std::thread _throttling;


		std::uint32_t _gpu_ticks = 0;
		bool _gpu_tick = false;


		void increment(const std::uint8_t&);

		void wait(const std::uint16_t&);

	public:

		const std::uint32_t& gpu_ticks();

	};
}
