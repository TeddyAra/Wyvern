#include "UIBar.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

UIBar::UIBar(GLFWwindow* window, std::string name, int width, int height, int posX, int posY)
	: window(window), name(name), size(width, height), pos(posX, posY)
{

}

UIBar::~UIBar() {
}

void UIBar::draw() {
	ImGui::SetNextWindowPos(ImVec2(pos.x, pos.y), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(size.x, size.y), ImGuiCond_Always);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::Begin(name.c_str(), nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
	ImGui::Text("Hi");
	ImGui::End();

	ImGui::PopStyleVar();
}