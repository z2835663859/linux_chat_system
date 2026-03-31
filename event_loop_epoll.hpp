#pragma once

#include <vector>
#include <memory>
#include <unordered_map>

// Check if we are on Linux to use epoll, otherwise keep kqueue (macOS)
#ifdef __linux__
#include <sys/epoll.h>
#else
#include <sys/event.h>
#endif

namespace im {

class EventHandler;

class EventLoop {
public:
  // Bit flags for polling events (matching the previous manual definition or simplifying)
  static const int EVENT_READ = 1;
  static const int EVENT_WRITE = 2;

  EventLoop();
  ~EventLoop();

  void add_handler(int fd, std::shared_ptr<EventHandler> handler, int events);
  void mod_handler(int fd, int events);
  void del_handler(int fd);

  void run();
  void stop();

private:
  int poll_fd_; // Instead of kq_fd_, renamed for generic polling
  bool running_;
  std::unordered_map<int, std::shared_ptr<EventHandler>> fd_to_handler_;
};

} // namespace im
