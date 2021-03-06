// This file is part of MLDB. Copyright 2015 Datacratic. All rights reserved.

/* compact_vector_persistence.h                                    -*- C++ -*-
   Jeremy Barnes, 3 March 2009
   Copyright (c) 2009 Jeremy Barnes.  All rights reserved.

   Persistence of compact vector.
*/

#pragma once

#include "compact_vector.h"
#include "mldb/jml/db/persistent_fwd.h"

namespace ML {

template<typename D, size_t I, typename Sz, bool Sf, typename P, class A>
inline ML::DB::Store_Writer &
operator << (ML::DB::Store_Writer & store,
             const ML::compact_vector<D, I, Sz, Sf, P, A> & v)
{
    DB::serialize_compact_size(store, v.size());
    for (unsigned i = 0;  i < v.size();  ++i)
        store << v[i];
    return store;
}

template<typename D, size_t I, typename Sz, bool Sf, typename P, class A>
inline ML::DB::Store_Reader &
operator >> (ML::DB::Store_Reader & store,
             ML::compact_vector<D, I, Sz, Sf, P, A> & v)
{
    unsigned long long sz = reconstitute_compact_size(store);
    v.resize(sz);
    for (unsigned i = 0;  i < sz;  ++i)
        store >> v[i];
    return store;
}

} // namespace ML

