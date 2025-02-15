// Concord
//
// Copyright (c) 2018 VMware, Inc. All Rights Reserved.
//
// This product is licensed to you under the Apache 2.0 license (the "License").
// You may not use this product except in compliance with the Apache 2.0 License.
//
// This product may include a number of subcomponents with separate copyright
// notices and license terms. Your use of these subcomponents is subject to the
// terms and conditions of the subcomponent's license, as noted in the LICENSE
// file.

#pragma once

#include <cstddef>
#include <memory>
#include <stdint.h>
#include <string>
#include "IStateTransfer.hpp"
#include "ICommunication.hpp"
#include "MetadataStorage.hpp"
#include "Metrics.hpp"
#include "ReplicaConfig.hpp"

namespace bftEngine {
class RequestsHandler {
 public:
  virtual int execute(uint16_t clientId,
                      uint64_t sequenceNum,
                      bool readOnly,
                      uint32_t requestSize,
                      const char *request,
                      uint32_t maxReplySize,
                      char *outReply,
                      uint32_t &outActualReplySize) = 0;

  virtual void onFinishExecutingReadWriteRequests() {};
};

class Replica {
 public:
  static Replica *createNewReplica(ReplicaConfig *replicaConfig,
                                   RequestsHandler *requestsHandler,
                                   IStateTransfer *stateTransfer,
                                   ICommunication *communication,
                                   MetadataStorage *metadataStorage);

  virtual ~Replica() = 0;

  virtual bool isRunning() const = 0;

  virtual uint64_t getLastExecutedSequenceNum() const = 0;

  virtual bool requestsExecutionWasInterrupted() const = 0;

  virtual void start() = 0;

  virtual void stop() = 0;

  //TODO(GG) : move the following methods to an "advanced interface"
  virtual void SetAggregator(std::shared_ptr<concordMetrics::Aggregator> a) = 0;
  virtual void restartForDebug(uint32_t delayMillis) = 0; // for debug only.
  virtual void stopWhenStateIsNotCollected() = 0;
};

}  // namespace bftEngine
