

#ifndef COMMON_ALLOTER_POOL_BLOCK
#define COMMON_ALLOTER_POOL_BLOCK

#ifdef __use_iocp__
#include <mutex>
#endif
#include <cstdint>
#include <memory>
#include <vector>

namespace burongnet {

// all memory must return memory pool before destroy.
class BlockMemoryPool {
 public:
  // bulk memory size.
  // every time add nodes num
  BlockMemoryPool(uint32_t large_sz, uint32_t add_num);
  virtual ~BlockMemoryPool();

  // for bulk memory.
  // return one bulk memory node
  virtual void* PoolLargeMalloc();
  virtual void PoolLargeFree(void*& m);

  // return bulk memory list size
  virtual uint32_t GetSize();
  // return length of bulk memory
  virtual uint32_t GetBlockLength();

  // release half memory
  virtual void ReleaseHalf();
  virtual void Expansion(uint32_t num = 0);

 private:
#ifdef __use_iocp__
  std::mutex _mutex;
#endif
  uint32_t _number_large_add_nodes;  // every time add nodes num
  uint32_t _large_size;              // bulk memory size
  std::vector<void*> _free_mem_vec;  // free bulk memory list
};

std::shared_ptr<BlockMemoryPool> MakeBlockMemoryPoolPtr(uint32_t large_sz,
                                                        uint32_t add_num);

}  // namespace burongnet

#endif