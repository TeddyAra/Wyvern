#include "UIZone.h"

UIZone::UIZone() {

}

UIZone::~UIZone() {

}

void UIZone::addWidget(WidgetType type, std::string title, const char* icon, std::function<void()> function) {
	UIWidget widget(type, title, icon, function);
	widgets.push_back(widget);
}

std::vector<UIWidget> UIZone::getWidgets() {
	return widgets;
}