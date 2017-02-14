#pragma once

using BYTE = std::uint8_t;
using SHORT = std::uint16_t;

class Mos6502_CPU {
		/* Registers */
		BYTE A;
		BYTE X;
		BYTE Y;
		SHORT PC;
		BYTE S;
		BYTE P;
		BYTE* memory; //[65536]
		SHORT* stack; //[16]
		BYTE* gfx; //[256][240][3] [256*240*3] (accessed [x+y*240+z*256*240]
		BYTE& findInMemory(const SHORT);
	public:
		Mos6502_CPU();
		void init();
		~Mos6502_CPU();
		void loadProgram(std::vector<BYTE> game);
		void (*GfxDraw)(const BYTE*);
		int doCycle();
};
