#include "UIZone.h"

UIZone::UIZone() {

}

UIZone::~UIZone() {

}

void UIZone::addWidget(WidgetType type, std::string title, const char* icon, std::shared_ptr<ICommand> command) {
	widgets.push_back(std::make_shared<UIWidget>(type, title, icon, command));
}

std::vector<std::shared_ptr<UIWidget>> UIZone::getWidgets() {
	return widgets;
}