#pragma once
#include "ArkThread.h"


class SystemThread : public ArkThreading::ArkThread
{
public:
	// Inherited via ArkThread
	virtual void run() override;
};