#pragma once
class IInputSystem {
public:
  virtual ~IInputSystem() = default;
  virtual void update()   = 0;
};
class InputHandler;
class InputSystem : public IInputSystem {
public:
  InputSystem(InputHandler* handler);
  void update() override;
  void setRunning(bool& runningFlag);

private:
  bool*         runningFlagPointer = nullptr;
  InputHandler* inputHandler;
};
