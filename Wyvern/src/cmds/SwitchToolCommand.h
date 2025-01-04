#pragma once

#include "ICommand.h"

#include "TransformTools.h"

class SwitchToolCommand : public ICommand {
public:
	explicit SwitchToolCommand(std::shared_ptr<InteractionController> controller, TransformTools::Tool tool);
	void execute() override;

private:
	TransformTools::Tool tool;
};