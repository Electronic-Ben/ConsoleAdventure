#include "engine/headers/Keyboard.h"

Keyboard::Keyboard()
{
  for (Term::Key key : trackedKeys)
  {
    keyStates[key] = KeyState{}; // Initialize with default states
  }
}

Keyboard::~Keyboard()
{
  stop();
}

void Keyboard::start()
{
  running = true;
  inputThread = std::thread(&Keyboard::inputLoop, this);
}

void Keyboard::stop()
{
  if (running)
  {
    running = false;
    if (inputThread.joinable())
    {
      inputThread.join();
    }
  }
}

void Keyboard::inputLoop()
{
  while (running)
  {
    Term::Event key = Term::read_event();

    if (trackedKeys.count(key))
    {
      std::lock_guard<std::mutex> lock(mutex);

      rawKeyState &state = rawStates[key];
      state.down = true;
      state.lastEventTime = std::chrono::steady_clock::now();
    }
  }
}

void Keyboard::update()
{
  std::lock_guard<std::mutex> lock(mutex);

  auto now = std::chrono::steady_clock::now();

  for (auto &[key, state] : keyStates)
  {
    bool isDownNow = state.down;

    if (isDownNow)
    {
      auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - rawStates[key].lastEventTime);
      if (elapsed > Keyboard::releaseTimeout)
      {
        isDownNow = false;
      }
    }

    state.pressed = !state.down && isDownNow;
    state.released = state.down && !isDownNow;
    state.down = isDownNow;
  }
}

bool Keyboard::isDown(Term::Key key) const
{
  return keyStates.at(key).down; // at() is safe, tracked keys are initialized
}

bool Keyboard::isPressed(Term::Key key) const
{
  return keyStates.at(key).pressed;
}

bool Keyboard::isReleased(Term::Key key) const
{
  return keyStates.at(key).released;
}
