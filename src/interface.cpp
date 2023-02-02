#include "interface.hpp"
#include "bus.hpp"

using namespace gameboy;

interface::interface()
{

}

interface::~interface()
{
	
}

void interface::create_window(void)
{
	this->_window.create(sf::VideoMode(this->SCREEN_WIDTH, this->SCREEN_HEIGHT), "Display", sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close);

	this->_window.setSize(sf::Vector2u(this->SCREEN_ZOOM * this->SCREEN_WIDTH, this->SCREEN_ZOOM * this->SCREEN_HEIGHT));
	this->_window.setPosition(sf::Vector2i(0,0));

	this->_window.clear(sf::Color::Black);
	this->_window.display();

	this->poll_events();
}

void interface::poll_events(void)
{
	sf::Event _event;
	while (this->_window.pollEvent(_event))
	{
		switch (_event.type)
		{
			case sf::Event::Closed:
				//std::cout << "interface: display closed" << std::endl;
				this->_window.close();
				break;
			case sf::Event::EventType::KeyPressed:
				switch (_event.key.code)
				{
					case sf::Keyboard::Escape:
						this->_window.close();
						break;
					case 47:
						this->SCREEN_ZOOM += 0.1;
						this->resize_window();
						break;
					case 52:
						this->SCREEN_ZOOM -= 0.1;
						this->resize_window();
						break;
					case sf::Keyboard::Left:
						this->_bus->request_joypadinput(bus::JOYPAD::Left);
						//std::cout << "interface: joypad press - Left" << std::endl;
						break;
					case sf::Keyboard::Down:
						this->_bus->request_joypadinput(bus::JOYPAD::Down);
						//std::cout << "interface: joypad press - Down" << std::endl;
						break;
					case sf::Keyboard::Right:
						this->_bus->request_joypadinput(bus::JOYPAD::Right);
						//std::cout << "interface: joypad press - Right" << std::endl;
						break;
					case sf::Keyboard::Up:
						this->_bus->request_joypadinput(bus::JOYPAD::Up);
						//std::cout << "interface: joypad press - Up" << std::endl;
						break;
					case sf::Keyboard::A:
						this->_bus->request_joypadinput(bus::JOYPAD::A);
						//std::cout << "interface: joypad press - A" << std::endl;
						break;
					case sf::Keyboard::B:
						this->_bus->request_joypadinput(bus::JOYPAD::B);
						//std::cout << "interface: joypad press - B" << std::endl;
						break;
					case sf::Keyboard::Enter:
						this->_bus->request_joypadinput(bus::JOYPAD::Select);
						//std::cout << "interface: joypad press - Select" << std::endl;
						break;
					case sf::Keyboard::Space:
						this->_bus->request_joypadinput(bus::JOYPAD::Start);
						//std::cout << "interface: joypad press - Start" << std::endl;
						break;
					default:
						this->_bus->request_joypadinput(bus::JOYPAD::None);
						//std::cout << "interface: key press - " << _event.key.code << std::endl;
						break;
				}
				break;
			default:
				this->_bus->request_joypadinput(bus::JOYPAD::None);
				break;
		}
	}
}

void interface::update_window(void)
{
	this->poll_events();

	if (this->_window.isOpen())
	{
		this->_window.clear();
		this->_window.draw(this->_bus->_gpu._screen);
		this->_window.display();
	}
}

void interface::resize_window(void)
{
	if (this->_window.isOpen())
	{
		sf::Vector2i _position = this->_window.getPosition();
		this->_window.setSize(sf::Vector2u(this->SCREEN_ZOOM * this->SCREEN_WIDTH, this->SCREEN_ZOOM * this->SCREEN_HEIGHT));
		this->_window.setPosition(_position);
	}
}
