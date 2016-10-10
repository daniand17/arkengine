#pragma once
#include "ArkThread.h"
class SystemTask : public ArkThreading::WorkerTask
{
public:
	SystemTask() {}

protected:
	void init() override;
	void run() override;
};