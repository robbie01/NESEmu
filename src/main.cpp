#include <ios>
#include <map>
#include <vector>
#include <iterator>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <SFML/Graphics.hpp>
#include "cpu.hpp"

constexpr int PIXEL_SIZE = 2;
constexpr int SCREEN_WIDTH = 256 * PIXEL_SIZE;
constexpr int SCREEN_HEIGHT =	240 * PIXEL_SIZE;

constexpr int FREQUENCY = 1789773;

sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "NES Emulator");

std::vector<BYTE> fileToBytes(const std::string filename) {
	std::ifstream fl(filename.c_str(), std::ios_base::in | std::ios_base::binary);
	fl.unsetf(std::ios::skipws);
	fl.seekg(0, std::ios::end);
	std::ios::streampos pos = fl.tellg();
	fl.seekg(0, std::ios::beg);
	std::vector<BYTE> ret;
	ret.reserve(pos);
	ret.insert(ret.begin(),
		std::istream_iterator<BYTE>(fl),
		std::istream_iterator<BYTE>());
	fl.close();
	return ret;
}

void drawGfx(const BYTE* gfx) {
	window.clear(sf::Color(0, 0, 0));
	for (int x = 0; x < 256; x++) {
		for (int y = 0; y < 240; y++) {
			sf::RectangleShape pix;
			pix.setSize(sf::Vector2f(PIXEL_SIZE, PIXEL_SIZE));
			pix.setFillColor(
				sf::Color(
					gfx[x + y * 256 + 0 * 256 * 240],
					gfx[x + y * 256 + 1 * 256 * 240],
					gfx[x + y * 256 + 2 * 256 * 240]
				)
			);
			pix.setPosition(x * PIXEL_SIZE, y * PIXEL_SIZE);
			window.draw(pix);
		}
	}
	window.display();
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cerr << "Usage: " << argv[0] << " <rom>" << std::endl;
		return 1;
	}
	window.clear(sf::Color(0, 0, 0));
	window.display();
	Mos6502_CPU cpu;
	cpu.GfxDraw = drawGfx;
	cpu.init();
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}
	return 0;
}

