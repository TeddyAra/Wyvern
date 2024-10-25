#include "FontManager.h"

#include <fstream>
#include <iostream>
#include <errno.h>

std::vector<ImFont*> FontManager::fonts;

void FontManager::addFont(std::string location, float size) {
	std::cout << "Works" << std::endl;
	ImGuiIO& io = ImGui::GetIO();

	addFontVariant(io, location + "-Regular.ttf", size);
	addFontVariant(io, location + "-Bold.ttf", size);
	addFontVariant(io, location + "-Italic.ttf", size);

	for (ImFont* font : fonts) {
		if (font == nullptr) {
			std::cout << "Empty" << std::endl;
		} else {
			std::cout << "Not empty" << std::endl;
		}
	}
}

void FontManager::addFontVariant(ImGuiIO& io, std::string location, float size) {
	ImFont* font;
	FILE* file;
	errno_t err;

	std::cout << "Opening " << location.c_str() << std::endl;

	if ((err = fopen_s(&file, location.c_str(), "r")) != 0) {
		fonts.push_back(nullptr);
	} else {
		fclose(file);
		font = io.Fonts->AddFontFromFileTTF(location.c_str(), size);
		if (font) {
			io.Fonts->Build();
			fonts.push_back(font);
		} else {
			fonts.push_back(nullptr);
		}
	}
}

ImFont* FontManager::getFont(int index, FontType type) {
	return fonts.at(index * 3 + type);
}