// Copyright (c) 2008-2010 Kent State University
// Copyright (c) 2011-2012 Texas A&M University
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#include <cassert>
#include <vector>

#include <origin/algorithm.hpp>
#include <origin/testing.hpp>

#include "query.hpp"

using namespace std;
using namespace origin;
using namespace testing;

template <typename R1, typename R2>
  struct find_first_in_results
  {
    bool operator()(const R1& range1, const R2& range2) const
    {
      auto first1 = begin(range1);
      auto last1 = end(range1);
      auto i = find_first_in(range1, range2);

      if (i != last1)
        return find_first_in(range(first1, i), range2) == i
            && some_equal(range2, *i);
      else
        return true;
    }
  };



int main()
{
  assert_checker<> env;

  using V = vector<int>;

  find_specs<V> specs;
  quick_check(env, specs);


  auto rgen = checkable_var<V>(env);
  quick_check(env, find_first_in_results<V, V> {}, rgen, rgen);
}