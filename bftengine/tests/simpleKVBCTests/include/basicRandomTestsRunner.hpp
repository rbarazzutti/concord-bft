// Concord
//
// Copyright (c) 2019 VMware, Inc. All Rights Reserved.
//
// This product is licensed to you under the Apache 2.0 license (the "License").
// You may not use this product except in compliance with the Apache 2.0
// License.
//
// This product may include a number of subcomponents with separate copyright
// notices and license terms. Your use of these subcomponents is subject to the
// terms and conditions of the subcomponent's license, as noted in the LICENSE
// file.

#ifndef BASIC_RANDOM_TESTS_HPP
#define BASIC_RANDOM_TESTS_HPP

#include "Logger.hpp"
#include "simpleKVBTestsBuilder.hpp"
#include "KVBCInterfaces.h"

namespace BasicRandomTests {

class BasicRandomTestsRunner {
 public:
  BasicRandomTestsRunner(concordlogger::Logger &logger, SimpleKVBC::IClient &client, size_t numOfOperations);
  ~BasicRandomTestsRunner() { delete testsBuilder_; }
  void run();

 private:
  static void sleep(int ops);
  bool isReplyCorrect(RequestType requestType,
                      const SimpleReply *expectedReply,
                      const char *reply,
                      size_t expectedReplySize,
                      uint32_t actualReplySize);

 private:
  concordlogger::Logger &logger_;
  SimpleKVBC::IClient &client_;
  const size_t numOfOperations_;
  TestsBuilder *testsBuilder_;
};

}  // namespace BasicRandomTests

#endif
