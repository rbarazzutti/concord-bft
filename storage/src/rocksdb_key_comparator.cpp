// Copyright 2018 VMware, all rights reserved
//
// Storage key comparators implementation.

#ifdef USE_ROCKSDB

#include "rocksdb/key_comparator.h"
#include "Logger.hpp"

#include "hex_tools.h"
#include "sliver.hpp"
#include "rocksdb/client.h"

#include <chrono>

using concordUtils::Sliver;
using concordlogger::Logger;
using concord::storage::rocksdb::copyRocksdbSlice;

namespace concord {
namespace storage {
namespace rocksdb {


int KeyComparator::Compare(const ::rocksdb::Slice& _a,
                           const ::rocksdb::Slice& _b) const {
  int ret = key_manipulator_->composedKeyComparison(reinterpret_cast<const uint8_t*>(_a.data()), _a.size(),
                                                    reinterpret_cast<const uint8_t*>(_b.data()), _b.size());

  LOG_TRACE(logger_, "Compared " << _a.ToString(true) << " with " << _b.ToString(true) << ", returning " << ret);

  return ret;
}

}
}
}
#endif
