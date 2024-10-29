#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

#include <string>
#include <vector>
#include <map>

enum FontType {
	regular = 0,
	bold = 1,
	italic = 2
};

class FontManager {
public:
	FontManager() = delete;

	static void addFont(std::string location, float size, bool single = false);
	static ImFont* getFont(std::string name, FontType type);

private:
	static bool addFontVariant(ImGuiIO& io, std::string location, float size, bool iconFont = false);

	static std::vector<ImFont*> fonts;
	static std::map<std::string, int> fontIndices;
};