#include "UIWidget.h"

UIWidget::UIWidget(WidgetType type, std::string title, const char* icon, std::shared_ptr<ICommand> command)
	: type(type), title(title), icon(icon), command(command)
{

}

UIWidget::~UIWidget() {

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

void UIWidget::execute() {
	command->execute();
}