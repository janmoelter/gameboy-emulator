#include "cartridge.hpp"
#include "bus.hpp"

using namespace gameboy;

const std::map<cartridge::TYPE, std::string> cartridge::TYPE_DESCRIPTION = {
	{cartridge::TYPE::ROM_Only, "ROM Only"},
	{cartridge::TYPE::MBC1, "MBC1"},
	{cartridge::TYPE::MBC1_RAM, "MBC1 + RAM"},
	{cartridge::TYPE::MBC1_RAM_Battery, "MBC1 + RAM + Battery"},
	{cartridge::TYPE::MBC2, "MBC2"},
	{cartridge::TYPE::MBC2_RAM_Battery, "MBC2 + RAM + Battery "},
	{cartridge::TYPE::ROM_RAM, "ROM + RAM "},
	{cartridge::TYPE::ROM_RAM_Battery, "ROM + RAM + Battery "},
	{cartridge::TYPE::MMM01, "MMM01"},
	{cartridge::TYPE::MMM01_RAM, "MMM01 + RAM "},
	{cartridge::TYPE::MMM01_RAM_Battery, "MMM01 + RAM + Battery "},
	{cartridge::TYPE::MBC3_Timer_Battery, "MBC3 + Timer + Battery "},
	{cartridge::TYPE::MBC3_Timer_RAM_Battery, "MBC3 + Timer + RAM + Battery "},
	{cartridge::TYPE::MBC3, "MBC3 "},
	{cartridge::TYPE::MBC3_RAM, "MBC3 + RAM "},
	{cartridge::TYPE::MBC3_RAM_Battery, "MBC3 + RAM + Battery "},
	{cartridge::TYPE::MBC5, "MBC5"},
	{cartridge::TYPE::MBC5_RAM, "MBC5 + RAM"},
	{cartridge::TYPE::MBC5_RAM_Battery, "MBC5 + RAM + Battery"},
	{cartridge::TYPE::MBC5_Rumble, "MBC5 + Rumble"},
	{cartridge::TYPE::MBC5_Rumble_RAM, "MBC5 + Rumble + RAM"},
	{cartridge::TYPE::MBC5_Rumble_RAM_Battery, "MBC5 + Rumble + RAM + Battery"},
	{cartridge::TYPE::MBC6, "MBC6"},
	{cartridge::TYPE::MBC7_Sensor_Rumble_RAM_Battery, "MBC7 + Sensor + Rumble + RAM + Battery"},
	{cartridge::TYPE::POCKET_CAMERA, "POCKET CAMERA"},
	{cartridge::TYPE::BANDAI_TAMA5, "BANDAI TAMA5"},
	{cartridge::TYPE::HuC3, "HuC3"},
	{cartridge::TYPE::HuC1_RAM_Battery, "HuC1 + RAM + Battery"},
};

const std::map<std::uint8_t, std::string> cartridge::OLD_LICENSEE = {
	{0x00, "None"},
	{0x01, "Nintendo"},
	{0x08, "Capcom"},
	{0x09, "HOT-B"},
	{0x0A, "Jaleco"},
	{0x0B, "Coconuts Japan"},
	{0x0C, "Elite Systems"},
	{0x13, "EA (Electronic Arts)"},
	{0x18, "Hudson Soft"},
	{0x19, "ITC Entertainment"},
	{0x1A, "Yanoman"},
	{0x1D, "Japan Clary"},
	{0x1F, "Virgin Games Ltd."},
	{0x24, "PCM Complete"},
	{0x25, "San-X"},
	{0x28, "Kemco"},
	{0x29, "SETA Corporation"},
	{0x30, "Infogrames"},
	{0x31, "Nintendo"},
	{0x32, "Bandai"},
	{0x34, "Konami"},
	{0x35, "HectorSoft"},
	{0x38, "Capcom"},
	{0x39, "Banpresto"},
	{0x3C, "Entertainment Interactive (stub)"},
	{0x3E, "Gremlin"},
	{0x41, "Ubi Soft"},
	{0x42, "Atlus"},
	{0x44, "Malibu Interactive"},
	{0x46, "Angel"},
	{0x47, "Spectrum HoloByte"},
	{0x49, "Irem"},
	{0x4A, "Virgin Games Ltd."},
	{0x4D, "Malibu Interactive"},
	{0x4F, "U.S. Gold"},
	{0x50, "Absolute"},
	{0x51, "Acclaim Entertainment"},
	{0x52, "Activision"},
	{0x53, "Sammy USA Corporation"},
	{0x54, "GameTek"},
	{0x55, "Park Place"},
	{0x56, "LJN"},
	{0x57, "Matchbox"},
	{0x59, "Milton Bradley Company"},
	{0x5A, "Mindscape"},
	{0x5B, "Romstar"},
	{0x5C, "Naxat Soft"},
	{0x5D, "Tradewest"},
	{0x60, "Titus Interactive"},
	{0x61, "Virgin Games Ltd."},
	{0x67, "Ocean Software"},
	{0x69, "EA (Electronic Arts)"},
	{0x6E, "Elite Systems"},
	{0x6F, "Electro Brain"},
	{0x70, "Infogrames"},
	{0x71, "Interplay Entertainment"},
	{0x72, "Broderbund"},
	{0x73, "Sculptured Software"},
	{0x75, "The Sales Curve Limited"},
	{0x78, "THQ"},
	{0x79, "Accolade"},
	{0x7A, "Triffix Entertainment"},
	{0x7C, "MicroProse"},
	{0x7F, "Kemco"},
	{0x80, "Misawa Entertainment"},
	{0x83, "LOZC G."},
	{0x86, "Tokuma Shoten"},
	{0x8B, "Bullet-Proof Software"},
	{0x8C, "Vic Tokai Corp."},
	{0x8E, "Ape Inc."},
	{0x8F, "I'Max"},
	{0x91, "Chunsoft Co."},
	{0x92, "Video System"},
	{0x93, "Tsubaraya Productions"},
	{0x95, "Varie"},
	{0x96, "Yonezawa / S'Pal"},
	{0x97, "Kemco"},
	{0x99, "Arc"},
	{0x9A, "Nihon Bussan"},
	{0x9B, "Tecmo"},
	{0x9C, "Imagineer"},
	{0x9D, "Banpresto"},
	{0x9F, "Nova"},
	{0xA1, "Hori Electric"},
	{0xA2, "Bandai"},
	{0xA4, "Konami"},
	{0xA6, "Kawada"},
	{0xA7, "Takara"},
	{0xA9, "Technos Japan"},
	{0xAA, "Broderbund"},
	{0xAC, "Toei Animation"},
	{0xAD, "Toho"},
	{0xAF, "Namco"},
	{0xB0, "Acclaim Entertainment"},
	{0xB1, "ASCII Corporation or Nexsoft"},
	{0xB2, "Bandai"},
	{0xB4, "Square Enix"},
	{0xB6, "HAL Laboratory"},
	{0xB7, "SNK"},
	{0xB9, "Pony Canyon"},
	{0xBA, "Culture Brain"},
	{0xBB, "Sunsoft"},
	{0xBD, "Sony Imagesoft"},
	{0xBF, "Sammy Corporation"},
	{0xC0, "Taito"},
	{0xC2, "Kemco"},
	{0xC3, "Square"},
	{0xC4, "Tokuma Shoten"},
	{0xC5, "Data East"},
	{0xC6, "Tonkin House"},
	{0xC8, "Koei"},
	{0xC9, "UFL"},
	{0xCA, "Ultra Games"},
	{0xCB, "VAP Inc."},
	{0xCC, "Use Corporation"},
	{0xCD, "Meldac"},
	{0xCE, "Pony Canyon"},
	{0xCF, "Angel"},
	{0xD0, "Taito"},
	{0xD1, "SOFEL (Software Engineering Lab)"},
	{0xD2, "Quest"},
	{0xD3, "Sigma Enterprises"},
	{0xD4, "ASK Kodansha Co."},
	{0xD6, "Naxat Soft"},
	{0xD7, "Copya System"},
	{0xD9, "Banpresto"},
	{0xDA, "Tomy"},
	{0xDB, "LJN"},
	{0xDD, "Nippon Computer Systems"},
	{0xDE, "Human Ent."},
	{0xDF, "Altron"},
	{0xE0, "Jaleco"},
	{0xE1, "Towa Chiki"},
	{0xE2, "Yutaka"},
	{0xE3, "Varie"},
	{0xE5, "Epoch"},
	{0xE7, "Athena"},
	{0xE8, "Asmik Ace Entertainment"},
	{0xE9, "Natsume"},
	{0xEA, "King Records"},
	{0xEB, "Atlus"},
	{0xEC, "Epic/Sony Records"},
	{0xEE, "IGS"},
	{0xF0, "A Wave"},
	{0xF3, "Extreme Entertainment"},
	{0xFF, "LJN"},
};

const std::map<std::string, std::string> cartridge::NEW_LICENSEE = {
	{"00", "None"},
	{"01", "Nintendo Research & Development 1"},
	{"08", "Capcom"},
	{"13", "EA (Electronic Arts)"},
	{"18", "Hudson Soft"},
	{"19", "B-AI"},
	{"20", "KSS"},
	{"22", "Planning Office WADA"},
	{"24", "PCM Complete"},
	{"25", "San-X"},
	{"28", "Kemco"},
	{"29", "SETA Corporation"},
	{"30", "Viacom"},
	{"31", "Nintendo"},
	{"32", "Bandai"},
	{"33", "Ocean Software/Acclaim Entertainment"},
	{"34", "Konami"},
	{"35", "HectorSoft"},
	{"37", "Taito"},
	{"38", "Hudson Soft"},
	{"39", "Banpresto"},
	{"41", "Ubi Soft"},
	{"42", "Atlus"},
	{"44", "Malibu Interactive"},
	{"46", "Angel"},
	{"47", "Bullet-Proof Software"},
	{"49", "Irem"},
	{"50", "Absolute"},
	{"51", "Acclaim Entertainment"},
	{"52", "Activision"},
	{"53", "Sammy USA Corporation"},
	{"54", "Konami"},
	{"55", "Hi Tech Expressions"},
	{"56", "LJN"},
	{"57", "Matchbox"},
	{"58", "Mattel"},
	{"59", "Milton Bradley Company"},
	{"60", "Titus Interactive"},
	{"61", "Virgin Games Ltd."},
	{"64", "Lucasfilm Games"},
	{"67", "Ocean Software"},
	{"69", "EA (Electronic Arts)"},
	{"70", "Infogrames"},
	{"71", "Interplay Entertainment"},
	{"72", "Broderbund"},
	{"73", "Sculptured Software"},
	{"75", "The Sales Curve Limited"},
	{"78", "THQ"},
	{"79", "Accolade"},
	{"80", "Misawa Entertainment"},
	{"83", "LOZC G."},
	{"86", "Tokuma Shoten"},
	{"87", "Tsukuda Original"},
	{"91", "Chunsoft Co."},
	{"92", "Video System"},
	{"93", "Ocean Software/Acclaim Entertainment"},
	{"95", "Varie"},
	{"96", "Yonezawa / S'Pal"},
	{"97", "Kaneko"},
	{"99", "Pack-In-Video"},
	{"9H", "Bottom Up"},
	{"A4", "Konami (Yu-Gi-Oh!)"},
	{"BL", "MTO"},
	{"DK", "Kodansha"},
};

cartridge::cartridge() : rom::rom()
{
	
}

cartridge::cartridge(std::ifstream& file) : rom::rom(file)
{
	this->_type = static_cast<cartridge::TYPE>(this->_rom[0x0147]);
	this->_size = this->_rom.size();

	if (this->_rom[0x0148] < 0x09)
	{
		this->_rom_banks = 2 * (1 << this->_rom[0x0148]);
		this->_rom_size = 16 * (1 << 10) * this->_rom_banks;
	}
	else
	{
		throw std::runtime_error("Unknown ROM size.");
	}

	switch (this->_rom[0x0149])
	{
		case 0x00:
			this->_ram_banks = 0;
			break;
		case 0x02:
			this->_ram_banks = 1;
			break;
		case 0x03:
			this->_ram_banks = 4;
			break;
		case 0x04:
			this->_ram_banks = 16;
			break;
		case 0x05:
			this->_ram_banks = 8;
			break;
		default:
			this->_ram_banks = 0;
			throw std::runtime_error("Unknown RAM size.");
	}
	this->_ram_size = 8 * (1 << 10) * this->_ram_banks;
	
	this->_ram = std::vector<std::uint8_t>(this->_ram_size);
	
	
	if (this->_rom[0x014B] == 0x33)
	{
		std::string code {(char)this->_rom[0x0144], (char)this->_rom[0x0145]};
		
		if (cartridge::NEW_LICENSEE.contains(code))
		{
			this->_licensee = cartridge::NEW_LICENSEE.at(code);
		}
	}
	else
	{
		std::uint8_t code = this->_rom[0x014B];
		
		if (cartridge::OLD_LICENSEE.contains(code))
		{
			this->_licensee = cartridge::OLD_LICENSEE.at(this->_rom[0x014B]);
		}
	}

	this->_title = std::string(reinterpret_cast<char*>(&this->_rom[0x0134]));

	this->_destination = this->_rom[0x014A];
	
	
	

	std::cout << "Cartridge" << std::endl;
	std::cout << "  Title: " << this->_title << std::endl;
	std::cout << "  Licensee: " << this->_licensee << std::endl;
	std::cout << "  Destination: " << (this->_destination ? "World" : "Japan") << std::endl;
	std::cout << "  Type: " << cartridge::TYPE_DESCRIPTION.at(this->_type) << std::endl;
	std::cout << "  Size: " << std::dec << static_cast<int>(this->_size) << std::endl;
	std::cout << "  ROM size: " << std::dec << (this->_rom_size / (1 << 10)) << "KiB" << std::endl;
	if (this->_ram_banks > 0)
	{
		std::cout << "  RAM size: " << std::dec << (this->_ram_size / (1 << 10)) << "KiB" << std::endl;
	}
	std::cout << std::endl;
}

cartridge::~cartridge()
{

}

void cartridge::_memory_bank_controller(const std::uint16_t& a, const std::uint8_t& v)
{
	switch (this->_type)
	{
		case cartridge::TYPE::ROM_Only:
		{
			break;
		}
		case cartridge::TYPE::MBC1:
		case cartridge::TYPE::MBC1_RAM:
		case cartridge::TYPE::MBC1_RAM_Battery:
		{
			switch (a)
			{
				case 0x0000 ... 0x1FFF:
				{
					if ((v & 0x0F) == 0x0A)
					{
						this->_bus->enable_cartridge_ram(true);
					}
					else
					{
						this->_bus->enable_cartridge_ram(false);
					}
					break;
				}
				case 0x2000 ... 0x3FFF:
				{
					std::uint8_t n = std::max(v & 0x1F, 0x01) & (this->_rom_banks - 1);
					this->_bus->load_cartridge_rom((this->_memory_bank_controller_secondary_bank << 5) + n);
					
					break;
				}
				case 0x4000 ... 0x5FFF:
				{
					std::uint8_t n = v & 0x03;
					
					if (this->_memory_bank_controller_banking_mode)
					{
						this->_memory_bank_controller_secondary_bank = n;
					}
					else
					{
						this->_bus->load_cartridge_ram(n);
					}
					
					break;
				}
				case 0x6000 ... 0x7FFF:
				{
					this->_memory_bank_controller_banking_mode = v & 0x01;
					
					break;
				}
			}
			
			break;
		}
		case cartridge::TYPE::MBC5:
		case cartridge::TYPE::MBC5_RAM:
		case cartridge::TYPE::MBC5_RAM_Battery:
		{
			switch (a)
			{
				case 0x0000 ... 0x1FFF:
				{
					if ((v & 0x0F) == 0x0A)
					{
						this->_bus->enable_cartridge_ram(true);
					}
					else
					{
						this->_bus->enable_cartridge_ram(false);
					}
					break;
				}
				case 0x2000 ... 0x2FFF:
				{
					std::uint8_t n = v;
					this->_bus->load_cartridge_rom((this->_memory_bank_controller_secondary_bank << 8) + n);
					
					break;
				}
				case 0x3000 ... 0x3FFF:
				{
					this->_memory_bank_controller_secondary_bank = v & 0x01;
					
					break;
				}
				case 0x4000 ... 0x5FFF:
				{
					std::uint8_t n = v & 0x0F;
					this->_bus->load_cartridge_ram(n);
					
					break;
				}
				default:
				{
					break;
				}
			}
			
			break;
		}
		default:
		{
			throw std::logic_error("<" + cartridge::TYPE_DESCRIPTION.at(this->_type) + ">");
			
			break;
		}
	}
}
