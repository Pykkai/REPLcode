// Copyright (C) 2026 Brad Shapcott brad@shapcott.com brash@pyyk.ai

// @codex 2026-02-26 08:01
// - implement a Sample class
// - this should be a wrapper around a map<string, string> and function as a key-value store
// - provide appropriate ctors, dtors, accessors and header file
// @review 2026-02-26 08:01 - Added Sample key-value store wrapper with supporting header.

#include <initializer_list>
#include <regex>
#include <sstream>
#include <utility>

#include "sample.h"

/******************************************************************************
 ** @revision
 ** 2026-02-26 08:01 - Implement Sample class as map-backed key-value store per @codex.
 ** 2026-02-26 08:07 - Added Sample::filter regex helper per @codex instructions.
 */

/******************************************************************************
 ** - default to empty store so new samples start clean
 */
CTOR pyyka::Sample::Sample(): store()
{
  return;
}

/******************************************************************************
 ** - seed with an existing KeyValuePairs snapshot
 */
CTOR pyyka::Sample::Sample(const KeyValuePairs &seed): store(seed)
{
  return;
}

/******************************************************************************
 ** - initializer_list convenience for tests and small fixtures
 */
CTOR pyyka::Sample::Sample(initializer_list<pair<const string, string>> seed)
: store()
{
  for (const auto &entry: seed) {
    store[entry.first] = entry.second;
  }
  return;
}

/******************************************************************************
 ** - copy constructor keeps metadata synchronized with source sample
 */
CTOR pyyka::Sample::Sample(const Sample &rhs): store(rhs.store)
{
  return;
}

/******************************************************************************
 ** - move constructor transfers ownership while leaving rhs empty
 */
CTOR pyyka::Sample::Sample(Sample &&rhs) noexcept: store(std::move(rhs.store))
{
  return;
}

/******************************************************************************
 ** - destructor required by style guide even though defaulted behavior suffices
 */
DTOR pyyka::Sample::~Sample()
{
  return;
}

/******************************************************************************
 ** - copy assignment clones key/value pairs for independent mutation
 */
pyyka::Sample &pyyka::Sample::operator = (const Sample &rhs)
{
  if (this == &rhs) return *this;
  store = rhs.store;
  return *this;
}

/******************************************************************************
 ** - move assignment lifts payload from rhs so heavy stores move cheaply
 */
pyyka::Sample &pyyka::Sample::operator = (Sample &&rhs) noexcept
{
  if (this == &rhs) return *this;
  store = std::move(rhs.store);
  return *this;
}

/******************************************************************************
 ** - operator[] inserts default value when key is absent and returns reference
 */
string &pyyka::Sample::operator [] (const string &key)
{
  return store[key];
}

/******************************************************************************
 ** - const at() enforces presence and surfaces std::out_of_range if missing
 */
const string &pyyka::Sample::at(const string &key) const
{
  return store.at(key);
}

/******************************************************************************
 ** - fetch value with fallback for ergonomic read paths where defaults exist
 */
string pyyka::Sample::value(const string &key, const string &fallback) const
{
  auto found = store.find(key);
  if (found == store.end()) return fallback;
  return found->second;
}

/******************************************************************************
 ** - contains lets callers short-circuit expensive parsing when key absent
 */
bool pyyka::Sample::contains(const string &key) const
{
  return store.find(key) != store.end();
}

/******************************************************************************
 ** - expose regex-based filtering so callers can pluck scoped subsets
 */
KeyValuePairs pyyka::Sample::filter(const vector<string> &patterns) const
{
  // - empty pattern list produces empty results without touching regex engine
  KeyValuePairs matches;
  if (patterns.empty()) return matches;

  // - precompile regex patterns once to avoid O(n * m) recompilation costs
  vector<regex> compiled;
  compiled.reserve(patterns.size());
  for (const auto &pattern: patterns) {
    try {
      compiled.emplace_back(pattern);
    } catch (const regex_error &) {
      continue;
    }
  }

  // @review 2026-02-26 08:07 - Iterate keys once, copying entries whose names satisfy any regex.
  for (const auto &entry: store) {
    for (const auto &rule: compiled) {
      if (regex_match(entry.first, rule)) {
        matches[entry.first] = entry.second;
        break;
      }
    }
  }

  return matches;
}

/******************************************************************************
 ** - set mutates or creates a key in one place for clarity
 */
void pyyka::Sample::set(const string &key, const string &value)
{
  store[key] = value;
  return;
}

/******************************************************************************
 ** - erase reports whether the key existed so callers can branch accordingly
 */
bool pyyka::Sample::erase(const string &key)
{
  return store.erase(key) > 0;
}

/******************************************************************************
 ** - clear flushes the internal store when samples are recycled
 */
void pyyka::Sample::clear()
{
  store.clear();
  return;
}

/******************************************************************************
 ** - basic inspectors expose shape without leaking mutability
 */
bool pyyka::Sample::empty() const
{
  return store.empty();
}

size_t pyyka::Sample::size() const
{
  return store.size();
}

const pyyka::KeyValuePairs &pyyka::Sample::pairs() const
{
  return store;
}

/******************************************************************************
 ** - equality uses std::map relational semantics for deterministic diffs
 */
bool pyyka::Sample::operator == (const Sample &rhs) const
{
  return store == rhs.store;
}

bool pyyka::Sample::operator != (const Sample &rhs) const
{
  return !(*this == rhs);
}

/******************************************************************************
 ** - string view serializes keys deterministically for logging + debugging
 */
EXPLICIT pyyka::Sample::operator string() const
{
  ostringstream oss;
  string delim = "";
  oss << "{";
  for (const auto &entry: store) {
    oss << delim << entry.first << "=" << entry.second;
    delim = ", ";
  }
  oss << "}";
  return oss.str();
}

// EOF ************************************************************************
