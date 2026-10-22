#pragma once

#include <thread>
#include <mutex>
#include <atomic>
#include <unordered_map>
#include <unordered_set>
#include "extern/cpp-terminal/terminal.hpp"
#include "extern/cpp-terminal/key.hpp"
#include "extern/cpp-terminal/event.hpp"
#include "extern/cpp-terminal/input.hpp"

struct KeyState
{
  bool down = false;
  bool pressed = false;
  bool released = false;
};

struct rawKeyState
{
  bool down;
  std::chrono::steady_clock::time_point lastEventTime;
};

class Keyboard
{
private:
  std::thread inputThread;
  std::atomic<bool> running{false};
  mutable std::mutex mutex;

  static constexpr std::chrono::milliseconds releaseTimeout{120}; // 120 ms key timeout (~4 frames)

  std::unordered_map<Term::Key, rawKeyState> rawStates;
  std::unordered_map<Term::Key, KeyState> keyStates;

  const std::unordered_set<Term::Key> trackedKeys = {
      Term::Key::W, Term::Key::A, Term::Key::S, Term::Key::D,
      Term::Key::B, Term::Key::N, Term::Key::M, Term::Key::Space,
      Term::Key::Esc};

public:
  Keyboard();
  ~Keyboard();

  void start();
  void stop();
  void update();

  bool isDown(Term::Key key) const;
  bool isPressed(Term::Key key) const;
  bool isReleased(Term::Key key) const;

private:
  void inputLoop(); // For Input Thread
};
