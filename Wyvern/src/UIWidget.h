#pragma once

#include <functional>
#include <string>
#include <memory>

#include "ICommand.h"

enum WidgetType {
	LargeButton,
	SmallButton,
	Toggle,
	InputFloat
};

class UIWidget {
public:
	UIWidget(WidgetType type, std::string title, const char* icon, std::shared_ptr<ICommand> command);
	~UIWidget();

	WidgetType getType();
	std::string getTitle();
	const char* getIcon();
	bool* getBool();
	float* getFloat();
	void execute();

private:
	WidgetType type;
	std::string title;
	const char* icon;
	std::shared_ptr<ICommand> command;
	bool* varBool;
	float* varFloat;
};