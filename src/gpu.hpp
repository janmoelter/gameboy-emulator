#pragma once

#include "common.hpp"

#include "memory.hpp"
#include <SFML/Graphics.hpp>

namespace gameboy
{
	class bus;

	class gpu
	{
		friend class bus;

	public:
		gpu(void);
		~gpu(void);

	private:
		enum struct SHADES : std::uint32_t
		{
			// 0xAABBGGRR
			//WHITE = 0xFFFFFFFF,
			//LIGHT_GRAY = 0xFF555555,
			//DARK_GRAY = 0xFFAAAAAA,
			//BLACK = 0xFF000000,
			WHITE = 0xFFD0F8E0,
			LIGHT_GRAY = 0xFF70C088,
			DARK_GRAY = 0xFF566834,
			BLACK = 0xFF201808,
		};
		
		bus* _bus;


		static const std::uint16_t SCREEN_WIDTH = 160;
		static const std::uint16_t SCREEN_HEIGHT = 144;
		static const std::uint16_t SCREENBUFFER_WIDTH = 256;
		static const std::uint16_t SCREENBUFFER_HEIGHT = 256;

		std::array<gpu::SHADES, 4> _palette;
		std::array<sf::Texture, 0x17F> _tileset;

		sf::RenderTexture _screenbuffer;

		void build_palette(void);

		std::array<std::uint8_t, 0x2000> _vram_cache;

		sf::Texture render_tile(const std::uint8_t&);
		void build_tileset(void);

	public:
		sf::Sprite _screen;

		void render_screen(void);

		void export_tileset(void);
	};
}
