
# Game Boy Emulator

An emulator of the original Nintendo Game Boy™.

<p align="center">
	<img src="README/DMG-01_boot-screen.png"/>
</p>


## Overview

This repository provides an emulator for the original Nintendo Game Boy™. Rather than trying to compete with many existing emulators, such as [SameBoy](https://sameboy.github.io/) and [BGB](https://bgb.bircd.org/), this implementation has started as and is an educational exercise as likely one of the best ways to understand how in particular a CPU works. Moreover, it is far from complete and still work in progress.

## Requirements

The implementation has been done using the C++20 standard. Besides that, it utilises the [SFML](https://www.sfml-dev.org/) libraries for the user interface.

## Usage

The emulator can be built using the provided Makefile after which the compiled binary can be found in the directory `bin/`.

Importantly, due to copyright, this repository does not contain the original boot rom or cartridge roms. Those must be acquired elsewhere and provided when starting the programme via command-line arguments. As a matter of fact, the boot rom is not strictly necessary.

### Example

In its current state, this emulator passes all of [Blargg's](https://github.com/retrio/gb-test-roms) CPU instruction behaviour tests.

Assuming the DMG-01 boot rom is located at `data/DMG-01-ROM.gb` (MD5 hash: `32fbbd84168d3482956eb3c5051637f5`) and Blargg's test roms at `data/test-roms/blargg/`, the following executes the test rom for special instructions.

```bash
./bin/emulator --boot-rom=data/DMG-01-ROM.gb --cartridge=data/test-roms/blargg/cpu_instrs/individual/01-special.gb
```

## References

In implementing this emulator, I have drawn on many references that describe the inner workings of the Game Boy™. In the following, I list a few in the hope that others might benefit from it.

* [Pan Docs](https://gbdev.io/pandocs/)
* [Game Boy™ CPU Manual](http://marc.rawer.de/Gameboy/Docs/GBCPUman.pdf)
* "[DMG-01 - How to Emulate a Game Boy](https://rylev.github.io/DMG-01/)" by Ryan Levick
* "[Game Boy: Complete Technical Reference](https://gekkio.fi/files/gb-docs/gbctr.pdf)" by Joonas Javanainen
* "[The Cycle-Accurate Game Boy Docs](https://github.com/AntonioND/giibiiadvance/blob/master/docs/TCAGBD.pdf)" by Antonio Niño Díaz
* [emudev Blog](https://emudev.de/gameboy-emulator/overview/) by LilaQ
* [RealBoy Blog](https://realboyemulator.wordpress.com/) by Sergio G. Del Real
* [Emulation Programming](http://www.codeslinger.co.uk/pages/projects/gameboy.html) by CodeSlinger
* "[gbops, an accurate opcode table for the Game Boy](https://izik1.github.io/gbops/)" by Skyler Ross
* "[GameBoy Opcode Summary](www.devrs.com/gb/files/opcodes.html)" by Jeff Frohwein
* "[A journey into GameBoy emulation](https://robertovaccari.com/blog/2020_09_26_gameboy/)" by Roberto Vaccari
* "[Game Boy boot sequence](https://knight.sc/reverse%20engineering/2018/11/19/game-boy-boot-sequence.html)" by Scott Knight
* "[Gameboy 2BPP Graphics Format](https://www.huderlem.com/demos/gameboy2bpp.html)" by Marcus Huderle

Finally, I found [Gameboy Doctor](https://robertheaton.com/gameboy-doctor/) by Robert Heaton an excellent tool for debugging the implementation of the CPU.
