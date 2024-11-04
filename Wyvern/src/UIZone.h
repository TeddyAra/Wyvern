#pragma once

#include <vector>
#include <functional>

#include "UIWidget.h"

class UIZone {
public:
	UIZone();
	~UIZone();

	void addWidget(WidgetType type, std::string title, const char* icon, std::function<void()> function);
	std::vector<UIWidget> getWidgets();

private:
	std::vector<UIWidget> widgets;
};