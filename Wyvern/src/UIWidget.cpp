#include "UIWidget.h"

UIWidget::UIWidget(WidgetType type, std::string title, const char* icon, std::function<void()> function)
	: type(type), title(title), icon(icon), function(function)
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

void UIWidget::activate() {
	function();
}