#pragma once

#include <memory>
#include <vector>
#include <any>

#include "ICommand.h"

class HistoryManager {
public:
	HistoryManager();
	~HistoryManager();

	void addCommand(std::shared_ptr<ICommand> command);
	std::shared_ptr<ICommand> undo();
	std::shared_ptr<ICommand> redo();
	void debug();

private:
	int indexOffset;
	int maxSize;
	std::vector<std::shared_ptr<ICommand>> history;
};