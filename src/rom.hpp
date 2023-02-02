#pragma once

#include "common.hpp"

namespace gameboy
{
	class bus;

	class rom
	{
		friend class bus;

	public:
		rom(std::ifstream&);
		rom(void);
		~rom(void);

	protected:
		bus* _bus;
		std::vector<std::uint8_t> _rom;
	};
}
