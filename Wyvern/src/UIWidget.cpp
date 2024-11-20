#include "UIWidget.h"

UIWidget::UIWidget(WidgetType type, std::string title, const char* icon, std::shared_ptr<ICommand> command)
	: type(type), title(title), icon(icon), command(command), varBool(nullptr), varFloat(nullptr)
{
	if (type == Toggle) 
		varBool = new bool(false);

	if (type == InputFloat)
		varFloat = new float(0.0f);
}

UIWidget::~UIWidget() {
	if (varBool) {
		delete varBool;
		varBool = nullptr;
	}

	if (varFloat) {
		delete varFloat;
		varFloat = nullptr;
	}
}

WidgetType UIWidget::getType() {
	return type;
}

std::string UIWidget::getTitle() {
	return title;
}

const char* UIWidget::getIcon() {
	return icon;
}

bool* UIWidget::getBool() {
	return varBool;
}

float* UIWidget::getFloat() {
	return varFloat;
}

void UIWidget::execute() {
	command->execute();
}