#pragma once

#include <vector>
#include <functional>

#include "UIWidget.h"

class UIZone {
public:
	UIZone();
	~UIZone();

	void addWidget(WidgetType type, std::string title, const char* icon, std::shared_ptr<ICommand> command);
	std::vector<std::shared_ptr<UIWidget>> getWidgets();

private:
	std::vector<std::shared_ptr<UIWidget>> widgets;
};