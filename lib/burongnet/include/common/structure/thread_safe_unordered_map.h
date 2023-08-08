

#ifndef COMMON_STRUCTURE_THREAD_SAFE_QUEUE
#define COMMON_STRUCTURE_THREAD_SAFE_QUEUE

#include <mutex>
#include <unordered_map>

namespace burongnet {

template <typename K, typename V>
class ThreadSafeUnorderedMap {
 public:
  ThreadSafeUnorderedMap() {}
  ~ThreadSafeUnorderedMap() {}

  V& operator[](const K& key) {
    std::lock_guard<std::mutex> lock(_mutex);
    return _unordered_map[key];
  }

  bool Find(const K& key) {
    std::lock_guard<std::mutex> lock(_mutex);
    return _unordered_map.find(key) != _unordered_map.end();
  }

  void Insert(const std::pair<K, V>& item) {
    std::lock_guard<std::mutex> lock(_mutex);
    _unordered_map.insert(item);
  }

  void Erase(const K& key) {
    std::lock_guard<std::mutex> lock(_mutex);
    _unordered_map.erase(key);
  }

  void Clear() {
    std::lock_guard<std::mutex> lock(_mutex);
    _unordered_map.clear();
  }

  size_t Size() {
    std::lock_guard<std::mutex> lock(_mutex);
    return _unordered_map.size();
  }

  bool Empty() {
    std::lock_guard<std::mutex> lock(_mutex);
    return _unordered_map.empty();
  }

  std::unordered_map<K, V>& GetMap() { return _unordered_map; }

 private:
  std::unordered_map<K, V> _unordered_map;
  std::mutex _mutex;
};

}  // namespace burongnet

#endif