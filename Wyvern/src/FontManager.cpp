#include "FontManager.h"

#include <fstream>
#include <iostream>
#include <errno.h>

std::vector<ImFont*> FontManager::fonts;
std::map<std::string, int> FontManager::fontIndices;

void FontManager::addFont(std::string location, float size, bool single) {
	ImGuiIO& io = ImGui::GetIO();

	const std::string prefix = "assets/";
	std::string name = location.substr(prefix.size());

	if (single) {
		if (addFontVariant(io, location + ".ttf", size, true)) {
			fontIndices[name] = fonts.size() - 1;
		} else {
			fonts.pop_back();
		}
	} else {
		int num = 0;
		num += addFontVariant(io, location + "-Regular.ttf", size);
		num += addFontVariant(io, location + "-Bold.ttf", size);
		num += addFontVariant(io, location + "-Italic.ttf", size);

		if (num == 0) {
			fonts.pop_back();
			fonts.pop_back();
			fonts.pop_back();
		} else {
			fontIndices[name] = fonts.size() - 3;
		}
	}
}

bool FontManager::addFontVariant(ImGuiIO& io, std::string location, float size, bool iconFont) {
	ImFont* font;
	FILE* file;
	errno_t err;

	// Check if font exists
	// If it does, add it like normal
	// If it doesn't, add a nullptr
	if ((err = fopen_s(&file, location.c_str(), "r")) != 0) {
		fonts.push_back(nullptr);
		return false;
	} else {
		fclose(file);

		if (iconFont) {
			ImFontConfig config;
			config.MergeMode = true;
			static const ImWchar iconRange[] = { 0xf000, 0xf8ff, 0 };
			font = io.Fonts->AddFontFromFileTTF(location.c_str(), size, &config, iconRange);
		} else {
			font = io.Fonts->AddFontFromFileTTF(location.c_str(), size);
		}

		if (font) {
			io.Fonts->Build();
			fonts.push_back(font);
			return true;
		} else {
			fonts.push_back(nullptr);
			return false;
		}
	}
}

ImFont* FontManager::getFont(std::string name, FontType type) {
	return fonts.at(fontIndices[name] + type);
}