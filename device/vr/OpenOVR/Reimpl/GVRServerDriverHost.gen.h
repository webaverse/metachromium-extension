#pragma once
#include "BaseCommon.h"
#include "OpenVR/interfaces/driver_IVRServerDriverHost_005.h"
#include "BaseServerDriverHost.h"
class CVRServerDriverHost_005 : public vr::driver_IVRServerDriverHost_005::IVRServerDriverHost, public CVRCommon {
private:
	const std::shared_ptr<BaseServerDriverHost> base;
public:
	virtual void** _GetStatFuncList() override;
	CVRServerDriverHost_005();
	// Interface methods:
	bool TrackedDeviceAdded(const char* pchDeviceSerialNumber, vr::ETrackedDeviceClass eDeviceClass, vr::driver_ITrackedDeviceServerDriver_005::ITrackedDeviceServerDriver* pDriver);
	void TrackedDevicePoseUpdated(uint32_t unWhichDevice, const vr::driver_ITrackedDeviceServerDriver_005::DriverPose_t& newPose, uint32_t unPoseStructSize);
	void VsyncEvent(double vsyncTimeOffsetSeconds);
	void VendorSpecificEvent(uint32_t unWhichDevice, vr::EVREventType eventType, const vr::VREvent_Data_t& eventData, double eventTimeOffset);
	bool IsExiting();
	bool PollNextEvent(vr::VREvent_t* pEvent, uint32_t uncbVREvent);
	void GetRawTrackedDevicePoses(float fPredictedSecondsFromNow, vr::TrackedDevicePose_t* pTrackedDevicePoseArray, uint32_t unTrackedDevicePoseArrayCount);
	void TrackedDeviceDisplayTransformUpdated(uint32_t unWhichDevice, vr::HmdMatrix34_t eyeToHeadLeft, vr::HmdMatrix34_t eyeToHeadRight);
};
