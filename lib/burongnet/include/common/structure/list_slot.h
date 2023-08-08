

#ifndef COMMON_STRUCTURE_LIST_SLOT
#define COMMON_STRUCTURE_LIST_SLOT

#include <memory>

namespace burongnet {

template <typename T>
class ListSlot {
 public:
  ListSlot() {}
  virtual ~ListSlot() {}

  void SetNext(std::shared_ptr<T> v) { _next = v; }
  std::shared_ptr<T> GetNext() { return _next; }

  void SetPrev(std::shared_ptr<T> v) { _prev = v; }
  std::shared_ptr<T> GetPrev() { return _prev.lock(); }

 protected:
  std::weak_ptr<T> _prev;
  std::shared_ptr<T> _next;
};

}  // namespace burongnet

#endif