/**
 * HMD extension for JediAcademy
 *
 *  Copyright 2014 by Jochen Leopold <jochen.leopold@model-view.com>
 */

#ifndef HMDDEVICEOPENHMD_H
#define HMDDEVICEOPENHMD_H

#include "IHmdDevice.h"
#include <openhmd.h>

class HmdDeviceOpenHmd : public IHmdDevice
{
public:

    enum DeviceType
    {
        DEVICE_GENERIC,
        DEVICE_OCULUSRIFT_DK1,
        DEVICE_OCULUSRIFT_DK2
    };

    HmdDeviceOpenHmd();
    virtual ~HmdDeviceOpenHmd();

    virtual bool Init(bool allowDummyDevice = false);
    virtual void Shutdown();

    virtual std::string GetInfo();
    virtual std::string GetAudioDeviceName();
    DeviceType GetDeviceType() { return mDeviceType; }

    virtual bool HasDisplay();
    virtual bool HandlesControllerInput() { return false; }
    virtual std::string GetDisplayDeviceName();
    virtual bool GetDisplayPos(int& rX, int& rY);

    virtual bool GetDeviceResolution(int& rWidth, int& rHeight, bool& rIsRotated, bool& rIsExtendedMode);
    virtual bool GetOrientationRad(float& rPitch, float& rYaw, float& rRoll);
    virtual bool GetPosition(float& rX, float& rY, float& rZ);
    virtual bool GetHandOrientationRad(bool rightHand, float& rPitch, float& rYaw, float& rRoll);
    virtual bool GetHandOrientationGripRad(bool rightHand, float& rPitch, float& rYaw, float& rRoll);
    virtual bool GetHandPosition(bool rightHand, float& rX, float& rY, float& rZ);
    virtual bool HasHand(bool rightHand);
    virtual void Recenter() {}

    ohmd_device* GetHmd() { return mpHmd; }
    bool IsDisplayRotated() { return mDisplayIsRotated; }

protected:
    void ConvertQuatToEuler(const float* quat, float& rYaw, float& rPitch, float& rRoll);
    void DetectDisplay();

private:
    // disable copy constructor
    HmdDeviceOpenHmd(const HmdDeviceOpenHmd&);
    HmdDeviceOpenHmd& operator=(const HmdDeviceOpenHmd&);

    bool mIsInitialized;
    ohmd_context* mpCtx;
    ohmd_device* mpHmd;

    std::string mInfo;
    DeviceType mDeviceType;

    int mDisplayWidth;
    int mDisplayHeight;

    int mDisplayId;
    int mDisplayX;
    int mDisplayY;
    std::string mDisplayDeviceName;

    bool mDisplayIsRotated;
};


#endif
