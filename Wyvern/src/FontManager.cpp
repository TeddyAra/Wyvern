#include "FontManager.h"

#include <fstream>
#include <iostream>
#include <errno.h>

std::vector<ImFont*> FontManager::fonts;

void FontManager::addFont(std::string location, float size) {
	ImGuiIO& io = ImGui::GetIO();

	addFontVariant(io, location + "-Regular.ttf", size);
	addFontVariant(io, location + "-Bold.ttf", size);
	addFontVariant(io, location + "-Italic.ttf", size);
}

void FontManager::addFontVariant(ImGuiIO& io, std::string location, float size) {
	ImFont* font;
	FILE* file;
	errno_t err;

	// Check if font exists
	// If it does, add it like normal
	// If it doesn't, add a nullptr
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