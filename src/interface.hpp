#pragma once

#include "common.hpp"

#include "memory.hpp"
#include <SFML/Graphics.hpp>

namespace gameboy
{
	class bus;

	class interface
	{
		friend class bus;

	public:
		interface(void);
		~interface(void);

	private:
		
		bus* _bus;

		static const std::uint16_t SCREEN_WIDTH = 160;
		static const std::uint16_t SCREEN_HEIGHT = 144;
		float SCREEN_ZOOM = 2;

		void poll_events(void);

	public:
		sf::RenderWindow _window;

		void create_window(void);
		void resize_window(void);
		void update_window(void);
	};
}
