#include "common.hpp"

#include "cpu.hpp"
#include "memory.hpp"
#include "gpu.hpp"
#include "rom.hpp"
#include "cartridge.hpp"
#include "interface.hpp"

#include "bus.hpp"


std::ostream& operator<<(std::ostream& os, const std::uint8_t& u8)
{
	os << hex(2) << static_cast<int>(u8);
	return os;
};

class Timer
{
public:
	Timer(void)
	{
		_T_start = std::chrono::steady_clock::now();
	}

	~Timer(void)
	{
		_T_stop = std::chrono::steady_clock::now();

		auto dT = _T_stop - _T_start;
		std::cout << dT.count() << std::endl;
	}

private:

	std::chrono::steady_clock::time_point _T_start;
	std::chrono::steady_clock::time_point _T_stop;
};

void print_array(std::array<std::uint8_t, 0x4> x)
{
	for (size_t i = 0; i < x.size(); i++)
	{
		std::cout << hex(2) << x[i] << " ";
	}
	std::cout << std::endl;
}

std::uint16_t reverse_endianness(std::uint16_t& u16)
{
	return ((u16 & 0x00FF) << 8) + ((u16 & 0xFF00) >> 8);
}


void print_version()
{
	std::cout << "Nintendo Game Boy™ Emulator (Compilation: " << __DATE__ << " @ " << __TIME__ << ")" << std::endl;
}

void print_help(int argc, char** argv)
{
	std::cout << "Usage: " << std::string(argv[0]) << " ..." << std::endl;


	std::cout << "" << std::endl;
	std::cout << "Options:" << std::endl;
	//           "****************************************************************************************************"
	std::cout << "  -r, --boot-rom=FILE            Boot rom."                                                           << std::endl;
	std::cout << "  -c, --cartridge=FILE           Cartridge."                                                          << std::endl;
	std::cout << "  -b, --disable-display          Disable graphics display."                                           << std::endl;
	std::cout << "  -d, --debug                    Enable debug mode."                                                  << std::endl;
	std::cout << ""                                                                                                     << std::endl;
	std::cout << "  -h, --help                     Print this help."                                                    << std::endl;
}

std::filesystem::path _BOOT_ROM;
std::filesystem::path _CARTRIDGE;
bool _ENABLE_GRAPHICS = true;
bool _DEBUG_MODE = false;
bool _SKIP_BOOTROM = false;
bool _PRINT_HELP = false;

void parse_args(int argc, char** argv)
{
	const char* const short_opts = "w:c:bdshV";
	const option long_opts[] = {
		{"boot-rom", required_argument, nullptr, 'r'},
		{"cartridge", required_argument, nullptr, 'c'},
		{"disable-display", no_argument, nullptr, 'b'},
		{"debug", no_argument, nullptr, 'd'},
		{"skip-boot-rom", no_argument, nullptr, 's'},
		{"help", no_argument, nullptr, 'h'},
		{"version", no_argument, nullptr, 'V'},
		{nullptr, no_argument, nullptr, 0}
	};

	while (true)
	{
		const auto opt = getopt_long(argc, argv, short_opts, long_opts, nullptr);

		if (opt == -1)
		{
			break;
		}

		switch (opt)
		{
			case 'r':
				_BOOT_ROM = optarg;
				std::cout << optarg << std::endl;
				break;
			case 'c':
				_CARTRIDGE = optarg;
				break;
			case 'b':
				_ENABLE_GRAPHICS = false;
				break;
			case 'd':
				_DEBUG_MODE = true;
				break;
			case 's':
				_SKIP_BOOTROM = true;
				break;
			case 'V':
				break;
			case 'h':
			case '?':
				_PRINT_HELP = true;
				break;
			default:
				break;
		}
	}
}

int main(int argc, char **argv)
{
	parse_args(argc, argv);

	if (_PRINT_HELP)
	{
		print_version();
		print_help(argc, argv);
		return 0;
	}

	print_version();
	std::cout << std::endl;
	std::cout << std::endl;


	using namespace std::chrono_literals;

	// Read boot rom
	gameboy::rom bootrom;
	if (std::filesystem::exists(_BOOT_ROM))
	{
		std::ifstream boot_rom_file(_BOOT_ROM, std::ios::in | std::ios::binary);
		bootrom = gameboy::rom(boot_rom_file);
		boot_rom_file.close();
	}
	else
	{
		//throw std::runtime_error("Boot ROM: " + _BOOT_ROM.u8string() + " does not exist.");
		_SKIP_BOOTROM = true;
	}

	// Read cartridge
	gameboy::cartridge cartridge;
	if (std::filesystem::exists(_CARTRIDGE))
	{
		std::ifstream cartridge_file(_CARTRIDGE, std::ios::in | std::ios::binary);
		cartridge = gameboy::cartridge(cartridge_file);
		cartridge_file.close();
	}
	else
	{
		throw std::runtime_error("Cartridge: " + _CARTRIDGE.string() + " does not exist.");
	}

	// Initialise clock
	gameboy::clock clock;
	// Initialise memory (RAM)
	gameboy::memory memory;
	// Initialise processor (CPU)
	gameboy::cpu cpu;
	// Initialise graphics processor (GPU)
	gameboy::gpu gpu;
	// Initialise user interface (UI)
	gameboy::interface interface;

	// Set up bus
	gameboy::bus bus(clock, memory, cpu, gpu, bootrom, cartridge, interface);
	

	bus.DEBUG_MODE = _DEBUG_MODE;
	bus.ENABLE_DISPLAY = _ENABLE_GRAPHICS;
	bus.THROTTLING = !_DEBUG_MODE;

	bus.initialise_system();


	std::cout << "Initialisation complete. Waiting to start execution...";
	std::cin.get();
	std::cout << std::endl << std::endl;

	// Load memory & register dumps
	if (false)
	{
		//std::ifstream memory_dmp("./memory.dmp", std::ios::in | std::ios::binary);
		//memory.load_dump(memory_dmp);
		//memory_dmp.close();
		//std::ifstream cpu_dmp("./cpu.dmp", std::ios::in | std::ios::binary);
		//cpu.load_dump(cpu_dmp);
		//cpu_dmp.close();
	}

	// Load CPU Dumps
	if (_SKIP_BOOTROM)
	{
		bus.skip_bootrom();
	}

	std::uint16_t PC;
	std::set<std::uint16_t> BREAK_POINTS = {}; // 0xC317, 0xC227, 0x0066
	bool DEBUG_STEPS = false;


	while (!bus.TERMINATE)
	{
		PC = bus.advance();

		if (DEBUG_STEPS)
		{
			std::cin.get();
		}
		
		if (!DEBUG_STEPS && BREAK_POINTS.find(PC) != BREAK_POINTS.end())
		{
			if (!bus._BOOTPHASE)
			{
				DEBUG_STEPS = true;
				bus.CPU_OPS = true;
				std::cout << "---> " << hex(4) << PC;
				std::cin.get();
				std::cout << std::endl;
			}
		}
		
		// Read Serial Output
		if (bus.get_u8_memory_value(0xFF02) == 0x81)
		{
			char c = bus.get_u8_memory_value(0xFF01);
			std::cout << c;
			bus.set_u8_memory_value(0xFF02, 0x00);
		}
	}

	std::cout << "Execution has terminated." << std::endl;
	std::cin.get();

	// Create memory & register dumps
	if (false)
	{
		//std::ofstream memory_dmp("./memory.dmp", std::ios::out | std::ios::binary);
		//memory.dump(memory_dmp);
		//memory_dmp.close();
		//std::ofstream cpu_dmp("./cpu.dmp", std::ios::out | std::ios::binary);
		//cpu.dump(cpu_dmp);
		//cpu_dmp.close();
	}

	return 0;
}
