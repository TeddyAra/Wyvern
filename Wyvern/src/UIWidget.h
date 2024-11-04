#pragma once

#include <functional>
#include <string>

enum WidgetType {
	LargeButton,
	SmallButton,
	Toggle,
	Input
};

class UIWidget {
public:
	UIWidget(WidgetType type, std::string title, const char* icon, std::function<void()> function);
	~UIWidget();

	WidgetType getType();
	std::string getTitle();
	const char* getIcon();
	void activate();

private:
	WidgetType type;
	std::string title;
	const char* icon;
	std::function<void()> function;
};