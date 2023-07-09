#include <IOKit/IOLib.h>  // Include necessary IOKit headers
#include <IOKit/IOService.h>
#include <IOKit/firewire/IOFireWireDevice.h>
#include <IOKit/avc/IOFireWireAVCUnit.h>

#include <IOKit/audio/IOAudioControl.h>
#include <IOKit/audio/IOAudioLevelControl.h>
#include <IOKit/audio/IOAudioToggleControl.h>
#include <IOKit/audio/IOAudioDefines.h>
#include <IOKit/audio/IOAudioDevice.h>

#include "OpenFWA.hpp"  // Include the OpenFWA header file

// Define the OpenFWA driver class
class net_mrmidi_driver_OpenFWA : public IOAudioDevice
{
    OSDeclareDefaultStructors(net_mrmidi_driver_OpenFWA)  // Required macro to set up some boilerplate code

public:
    static const uint8_t kSourceSubunitType = 0x01;  // Define the source subunit type

    virtual bool start(IOService *provider) override;  // Declare the start method
    virtual void stop(IOService *provider) override;  // Declare the stop method
    virtual bool initHardware(IOService *provider) override;  // Declare the initHardware method

private:
    IOFireWireAVCUnit *avcUnit = nullptr;  // Initialize avcUnit to nullptr
};

OSDefineMetaClassAndStructors(net_mrmidi_driver_OpenFWA, IOAudioDevice)  // Another required macro to set up some boilerplate code

// Define the initHardware method
bool net_mrmidi_driver_OpenFWA::initHardware(IOService *provider)
{
    bool result = true;  // Initialize the result

    setDeviceName("Apogee Duet (mrmidi driver)");  // Set the device name
    setManufacturerName("Apogee");  // Set the manufacturer name
    setDeviceShortName("Duet");  // Set the short name
    IOLog("%s(%p)::initHardware\n", getName(), this);  // Log the initiation of the hardware

    // Define the command for the sample rate
    uint8_t command[10] = {
        0x00, // Command type (Control command)
        0x00, // Opcode
        0x50, // Apogee proprietary command prefix
        0x43, // Apogee proprietary command prefix
        0x4d, // Apogee proprietary command prefix
        0x01, // Subunit type and ID (Audio)
        0x44, // SAMPLE_RATE control attribute
        0x00, // 44100 Hz expressed in 11.2896 kHz units (High byte)
        0xAC, // 44100 Hz expressed in 11.2896 kHz units (Mid byte)
        0x44  // 44100 Hz expressed in 11.2896 kHz units (Low byte)
    };
    UInt8 response[256];
    UInt32 responseLen = 256;
    UInt32 cmdLen = 10;

    // Get the AVC unit from the provider
    avcUnit = OSDynamicCast(IOFireWireAVCUnit, provider);
    if (!avcUnit) {
        IOLog("%s(%p)::initHardware -> provider is not an IOFireWireAVCUnit\n", getName(), this);
        return false;
    }
    IOLog("%s(%p)::initHardware -> avcUnit = %p\n", getName(), this, avcUnit);

    // Send the AVC command
    IOReturn error = avcUnit->AVCCommand(command, cmdLen, response, &responseLen);
    if (error != kIOReturnSuccess) {
        IOLog("%s(%p)::initHardware -> failed to send AVC command\n", getName(), this);
        return false;
    }

    return result;
}

// Define the start method
bool net_mrmidi_driver_OpenFWA::start(IOService *provider)
{
    IOLog("%s(%p)::start\n", getName(), this);
    // print some info about the provider
    IOLog("%s(%p)::start -> provider = %p\n", getName(), this, provider);
    IOLog("%s(%p)::start -> provider->getName() = %s\n", getName(), this, provider->getName());
    
    IOLog("%s(%p)::start -> provider->getMetaClass()->getClassName() = %s\n", getName(), this, provider->getMetaClass()->getClassName());
    

    if(!IOService::start(provider))
        return false;

    // try a different cast
    IOFireWireDevice *firewireDevice = OSDynamicCast(IOFireWireDevice, provider);
    if (!firewireDevice) {
        IOLog("%s(%p)::start -> provider is not an IOFireWireDevice\n", getName(), this);
    } else {
        IOLog("%s(%p)::start -> firewireDevice = %p\n", getName(), this, firewireDevice);
        // print some data
    }
    IOFireWireAVCUnit *avcUnit = OSDynamicCast(IOFireWireAVCUnit, provider);
    if (!avcUnit) {
        IOLog("%s(%p)::start -> provider is not an IOFireWireAVCUnit\n", getName(), this);
    } else {
        IOLog("%s(%p)::start -> avcUnit = %p\n", getName(), this, avcUnit);
    }
    

    



    // Initialize the hardware.
    if (!initHardware(provider)) {
        IOLog("%s(%p)::start -> failed to initialize hardware\n", getName(), this);
        return false;
    }

    return true;
}

// Define the stop method
void net_mrmidi_driver_OpenFWA::stop(IOService *provider)
{
    IOLog("%s(%p)::stop\n", getName(), this);

    // TODO: Add your own device cleanup code here

    IOService::stop(provider);
}
