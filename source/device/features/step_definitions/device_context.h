#ifndef SKELETON_DEVICE_CONTEXT_H
#define SKELETON_DEVICE_CONTEXT_H

class GpioStub
{
public:
};

class PwmSpy
{
public:
};

class DeviceContext
{
public:
  DeviceContext()
    : _button()
    , _bell()
  {
  }

  void start()
  {

  }

  void stop()
  {

  }

  GpioStub & button()
  {
    return _button;
  }

private:
  GpioStub _button;
  PwmSpy _bell;
};

#endif //SKELETON_DEVICE_CONTEXT_H
