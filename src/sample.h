// Copyright (C) 2026 Brad Shapcott brad@shapcott.com brash@pyyk.ai

#ifndef _SAMPLE_H_
#define _SAMPLE_H_

// - system includes in alphabetical order
#include <initializer_list>
#include <string>
#include <utility>
#include <vector>

// - project includes in alphabetical order
#include "types.h"

/******************************************************************************
 ** @revision
 ** 2026-02-26 08:01 - Added Sample interface describing map-backed key-value store.
 ** 2026-02-26 08:07 - Added regex-based filter helper per @codex instructions.
 */
// @review 2026-02-26 08:01 - Declared Sample API for map-backed wrapper.

namespace pyyka {
  /****************************************************************************
   ** - Sample wraps KeyValuePairs while providing ergonomic helpers
   */
  class Sample {
  private:
    // - actual storage so instrumentation hooks live in one place
    KeyValuePairs store;
  public:
    // - constructors cover empty, copy, move, map, and initializer seeds
    Sample();
    Sample(const KeyValuePairs &);
    Sample(initializer_list<pair<const string, string>>);
    Sample(const Sample &);
    Sample(Sample &&) noexcept;
    ~Sample();

    // - assignment mirrors constructor coverage
    Sample &operator = (const Sample &);
    Sample &operator = (Sample &&) noexcept;

    // - map-like API for mutation + lookup
    string &operator [] (const string &);
    const string &at(const string &) const;
    string value(const string &, const string &fallback = "") const;
    bool contains(const string &) const;
    // @codex 2026-02-26 08:07
    // - implement a function that returns keys matching the regular
    //   expressions given
    // @review 2026-02-26 08:07 - Added Sample::filter that returns map entries whose keys satisfy regex patterns.
    KeyValuePairs filter(const vector<string> &r) const;
    void set(const string &, const string &);
    bool erase(const string &);
    void clear();

    // - inspectors for callers who only need metadata
    bool empty() const;
    size_t size() const;
    const KeyValuePairs &pairs() const;

    // - comparisons + debug helpers
    bool operator == (const Sample &) const;
    bool operator != (const Sample &) const;
    explicit operator string() const;
  };
}

#endif

// EOF ************************************************************************
