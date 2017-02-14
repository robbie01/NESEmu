#include <array>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <random>
#include <ctime>
#include <string>
#include <cstring>
#include "cpu.hpp"

BYTE& Mos6502_CPU::findInMemory(const SHORT address) {
	if (address < 0x2000) {
		return memory[address % 0x800]; //normalize internal mirrors
	}
	else if (0x2000 <= address && address < 0x4000) {
		return memory[(address % 0x8) + 0x2000]; //normalize PPU mirrors
	}
	else {
		return memory[address];
	}
}

Mos6502_CPU::Mos6502_CPU() {
	memory = new BYTE[65536];
	stack = new SHORT[16];
	gfx = new BYTE[256*240*3];
}

void Mos6502_CPU::init() {
	P = 0x34;
	A = 0;
	X = 0;
	Y = 0;
	S = 0xFD;
	std::fill(memory, memory + sizeof(memory), 0);
	std::fill(gfx, gfx + sizeof(gfx), 0);

	GfxDraw(gfx);
}

Mos6502_CPU::~Mos6502_CPU() {
	delete[] memory;
	delete[] stack;
	delete[] gfx;
}

void Mos6502_CPU::loadProgram(std::vector<BYTE> game) {
	for (unsigned long i = 0; i < game.size(); i++)
		memory[i + 0x4020] = game[i];
}

int Mos6502_CPU::doCycle() {
/*
	opcode = memory[pc] << 8 | memory[pc + 1];
	switch (opcode & 0xF000) {

	}
*/
	return 0;
}
