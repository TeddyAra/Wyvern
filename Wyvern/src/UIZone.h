#pragma once

#include <vector>
#include <functional>

#include "UIWidget.h"

class UIZone {
public:
	UIZone(std::string title);
	~UIZone();

	void addWidget(WidgetType type, std::string title, const char* icon, std::shared_ptr<ICommand> command);
	std::vector<std::shared_ptr<UIWidget>> getWidgets();
	std::string getTitle();

private:
	std::vector<std::shared_ptr<UIWidget>> widgets;
	std::string title;
};