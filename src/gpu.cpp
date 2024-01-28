#include "gpu.hpp"
#include "bus.hpp"

using namespace gameboy;

gpu::gpu()
{
	this->_screenbuffer.create(this->SCREENBUFFER_WIDTH, this->SCREENBUFFER_HEIGHT);
	this->_screenbuffer.setRepeated(true);
}

gpu::~gpu()
{
	
}

void gpu::build_palette(void)
{
	const std::uint8_t& BGP = this->_bus->get_u8_memory_value(memory::$::BGP);

	for (size_t i = 0; i < 4; i++)
	{
		switch (BGP >> 2*i & 0b11)
		{
			case 0:
				this->_palette[i] = gpu::SHADES::WHITE;
				break;
			case 1:
				this->_palette[i] = gpu::SHADES::LIGHT_GRAY;
				break;
			case 2:
				this->_palette[i] = gpu::SHADES::DARK_GRAY;
				break;
			case 3:
				this->_palette[i] = gpu::SHADES::BLACK;
				break;
		}
	}
}

void gpu::build_tileset(void)
{
	std::array<std::uint8_t, 0x2000> _vram;
	std::copy_n(this->_bus->_memory.VRAM.begin(), 0x2000, _vram.begin());

	if (this->_vram_cache != _vram)
	{
		this->_vram_cache = _vram;
	


		this->build_palette();

		//this->_tileset.clear();

		//std::uint64_t

		for (size_t i = 0; i < 0x17F; i++)
		{
			this->_tileset[i] = this->render_tile(i);
		}

		//std::cout << "gpu: Tileset built." << std::endl;
	}
}

sf::Texture gpu::render_tile(const std::uint8_t& i)
{
	sf::Texture _texture;
	_texture.create(8,8);
	
	std::array<std::uint32_t, 8*8> _pixelbuffer;
	std::uint8_t B1;
	std::uint8_t B2;
	std::uint8_t x;

	for (size_t r = 0; r < 8; r++)
	{
		B1 = this->_bus->get_u8_memory_value(static_cast<std::uint16_t>(memory::$::VRAM) + 16*i + 2*r);
		B2 = this->_bus->get_u8_memory_value(static_cast<std::uint16_t>(memory::$::VRAM) + 16*i + 2*r + 1);

		for (size_t c = 0; c < 8; c++)
		{
			x = (((B2 >> (7-c)) & 0b1) << 1) + ((B1 >> (7-c)) & 0b1);
			_pixelbuffer[8*r + c] = static_cast<std::uint32_t>(this->_palette[x]);
		}
	}
	_texture.update(reinterpret_cast<std::uint8_t*>(&_pixelbuffer));
	
	return _texture;
}

void gpu::render_screen(void)
{
	std::bitset<8> LCDC(this->_bus->get_u8_memory_value(memory::$::LCDC));

	if (LCDC[7])
	{
		this->build_tileset();

		this->_screenbuffer.clear(sf::Color::White);

		if (this->_tileset.size() > 0)
		{
			sf::Sprite _sprite;
			std::uint8_t i_tile;

			for (size_t i = 0; i < 32*32; i++)
			{
				i_tile = this->_bus->get_u8_memory_value(0x9800 + LCDC[3] * 0x0400 + i);
				
				_sprite.setTexture(this->_tileset[i_tile]);
				_sprite.setPosition(sf::Vector2f((i % 32)*8, (i / 32)*8));
				this->_screenbuffer.draw(_sprite);
			}
		}

		this->_screenbuffer.display();

		
		const std::uint8_t& SCY = this->_bus->get_u8_memory_value(memory::$::SCY);
		const std::uint8_t& SCX = this->_bus->get_u8_memory_value(memory::$::SCX);
		//std::cout << "SCX: " << hex(2) << (int)SCX << "   " << "SCY: " << hex(2) << (int)SCY << std::endl;

		sf::IntRect _window_rectangle(SCX, SCY, this->SCREEN_WIDTH, this->SCREEN_HEIGHT);
		
		this->_screen = sf::Sprite(this->_screenbuffer.getTexture());
		this->_screen.setTextureRect(_window_rectangle);
	}
}

void gpu::export_tileset(void)
{
	for (size_t i = 0; i < this->_tileset.size(); i++)
	{
		//this->_tileset[i].copyToImage().saveToFile("./tile-" + std::to_string(i) + ".png");
	}
}
