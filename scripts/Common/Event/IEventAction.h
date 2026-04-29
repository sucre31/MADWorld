#pragma once

class IEventAction {
public:
	virtual ~IEventAction() = default;
	virtual void execute() = 0;
};