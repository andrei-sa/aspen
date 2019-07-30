#include <catch2/catch.hpp>
#include "Aspen/StaticCommitHandler.hpp"
#include "Aspen/Queue.hpp"

using namespace Aspen;

TEST_CASE("test_empty_static_commit", "[StaticCommitHandler]") {
  auto reactor = StaticCommitHandler();
  REQUIRE(reactor.commit(0) == State::COMPLETE_EMPTY);
}

TEST_CASE("test_static_immediate_complete", "[StaticCommitHandler]") {
  auto queue = Queue<int>();
  auto reactor = StaticCommitHandler(&queue);
  queue.push(1);
  queue.commit(0);
  queue.set_complete();
  REQUIRE(reactor.commit(1) == State::COMPLETE);
}

TEST_CASE("test_static_complete", "[StaticCommitHandler]") {
  auto queue = Queue<int>();
  auto reactor = StaticCommitHandler(&queue, &queue);
  queue.push(1);
  REQUIRE(reactor.commit(0) == State::EVALUATED);
  queue.set_complete();
  REQUIRE(reactor.commit(1) == State::COMPLETE);
}

TEST_CASE("test_static_empty_and_evaluated", "[CommitHandler]") {
  auto queue_a = Queue<int>();
  auto queue_b = Queue<int>();
  auto reactor = StaticCommitHandler(&queue_a, &queue_b);
  REQUIRE(reactor.commit(0) == State::EMPTY);
  queue_a.push(123);
  REQUIRE(reactor.commit(1) == State::EMPTY);
  queue_b.push(321);
  REQUIRE(reactor.commit(2) == State::EVALUATED);
}