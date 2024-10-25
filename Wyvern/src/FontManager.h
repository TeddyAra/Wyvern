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

	static void addFont(std::string location, float size);
	static ImFont* getFont(int index, FontType type);

private:
	static void addFontVariant(ImGuiIO& io, std::string location, float size);

	static std::vector<ImFont*> fonts;
};