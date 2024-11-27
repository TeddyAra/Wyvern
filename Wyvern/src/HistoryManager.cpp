#include "HistoryManager.h"

#include <string>
#include <iostream>

HistoryManager::HistoryManager() 
	: indexOffset(0), maxSize(10)
{

}

HistoryManager::~HistoryManager() {

}

void HistoryManager::addCommand(std::shared_ptr<ICommand> command) {
	if (indexOffset != 0) { 
		history.erase(history.end() - indexOffset, history.end());
		indexOffset = 0;
	}

	history.push_back(command);
	if (history.size() > maxSize) history.erase(history.begin());
	debug();
}

std::shared_ptr<ICommand> HistoryManager::undo() {
	int index = history.size() - indexOffset - 2;
	if (index >= 0) {
		indexOffset++;
		debug();
		return history[index];
	}

	return nullptr;
}

std::shared_ptr<ICommand> HistoryManager::redo() {
	if (indexOffset != 0) {
		indexOffset--;
		int index = history.size() - indexOffset - 1;
		debug();
		return history[index];
	}

	return nullptr;
}

void HistoryManager::debug() {
	std::string separator = "\n=========================================";
	std::string msg = separator + "\nIndex offset: " + std::to_string(indexOffset) 
		+ "\nSize: " + std::to_string(history.size()) 
		+ "\nVector: { ";
	
	for (int i = 0; i < maxSize; i++) {
		// O = current
		// o = used
		// x = not used
		
		if (i >= history.size()) {
			msg += "x ";
		} else {
			if (i == history.size() - indexOffset - 1) {
				msg += "O ";
			} else {
				msg += "o ";
			}
		}
	}

	msg += "}";
	std::cout << msg.c_str() << std::endl;
}