#pragma once

#include <functional>
#include <string>
#include <memory>

#include "ICommand.h"

enum WidgetType {
	LargeButton,
	SmallButton,
	Toggle,
	Input
};

class UIWidget {
public:
	UIWidget(WidgetType type, std::string title, const char* icon, std::shared_ptr<ICommand> command);
	~UIWidget();

	WidgetType getType();
	std::string getTitle();
	const char* getIcon();
	void execute();

private:
	WidgetType type;
	std::string title;
	const char* icon;
	std::shared_ptr<ICommand> command;
};