#pragma once
#include "BaseCommon.h"
#include "API/ISystem_001.h"
#include "API/OCBaseSystem.h"
class CVROCSystem_001 : public ocapi::IVROCSystem_001::IVROCSystem, public CVRCommon {
private:
	const std::shared_ptr<OCBaseSystem> base;
public:
	virtual void** _GetStatFuncList() override;
	CVROCSystem_001();
	// Interface methods:
	uint64_t GetExtendedButtonStatus();
};
