#include "sc_memory_wrap.h"
#include "sc_debug.h"


namespace sc
{

Stream::Stream(sc_stream * stream)
    : m_stream(stream)
{
    ASSERT_NOT_NULL(m_stream);
}

Stream::~Stream()
{
    sc_stream_free(m_stream);
}

/// ----- Iterators -----
Iterator3::Iterator3(sc_iterator3 * it)
    : m_it(it)
{
}

Iterator3::~Iterator3()
{
}

bool Iterator3::next() const
{
    return sc_iterator3_next(m_it) == SC_TRUE;
}

sc_addr Iterator3::value(uint8_t idx) const
{
    ASSERT(idx < 3, "Invalid index for iterator3 value");
    return sc_iterator3_value(m_it, idx);
}


Iterator5::Iterator5(sc_iterator5 * it)
    : m_it(it)
{
}

Iterator5::~Iterator5()
{
}

bool Iterator5::next() const
{
    return sc_iterator5_next(m_it);
}

sc_addr Iterator5::value(uint8_t idx) const
{
    ASSERT(idx < 5, "Invalid index for iterator5 value");
    return sc_iterator5_value(m_it, idx);
}

// -----------------------------
Memory::Memory(sc_access_levels levels)
{
    m_ctx = sc_memory_context_new(levels);
    ASSERT(m_ctx != 0, "Can't create context");
}

Memory::~Memory()
{
    ASSERT_NOT_NULL(m_ctx);
    sc_memory_context_free(m_ctx);
}


bool Memory::is_element(sc_addr addr)
{
    return sc_memory_is_element(m_ctx, addr) == SC_TRUE;
}

sc_result Memory::element_free(sc_addr addr)
{
    return sc_memory_element_free(m_ctx, addr);
}

sc_result Memory::element_type(sc_addr addr, sc_type & result)
{
    return sc_memory_get_element_type(m_ctx, addr, &result);
}

sc_result Memory::set_element_access_levels(sc_addr addr, sc_access_levels access_levels, sc_access_levels & new_value)
{
    return sc_memory_set_element_access_levels(m_ctx, addr, access_levels, &new_value);
}

sc_result Memory::get_element_access_levels(sc_addr addr, sc_access_levels & result)
{
    return sc_memory_get_element_access_levels(m_ctx, addr, &result);
}

sc_addr Memory::node_new(sc_type type)
{
    return sc_memory_node_new(m_ctx, type);
}

sc_addr Memory::arc_new(sc_type type, sc_addr beg, sc_addr end)
{
    return sc_memory_arc_new(m_ctx, type, beg, end);
}

sc_addr Memory::link_new()
{
    return sc_memory_link_new(m_ctx);
}


sc_result Memory::get_arc_begin(sc_addr addr, sc_addr & result)
{
    return sc_memory_get_arc_begin(m_ctx, addr, &result);
}

sc_result Memory::get_arc_end(sc_addr addr, sc_addr & result)
{
    return sc_memory_get_arc_end(m_ctx, addr, &result);
}

sc_result Memory::set_link_content(sc_addr addr, Stream const & stream)
{
    return sc_memory_set_link_content(m_ctx, addr, stream.m_stream);
}

sc_result Memory::get_link_content(sc_addr addr, Stream ** stream)
{
    sc_stream * s = 0;
    sc_result res = sc_memory_get_link_content(m_ctx, addr, &s);

    if (res == SC_RESULT_OK)
    {
        ASSERT_NOT_NULL(s);
        *stream = new Stream(s);
    }

    return res;
}

sc_result Memory::find_links_with_content(Stream const & stream, ScAddrVectorT & result)
{
    sc_addr *results = 0;
    sc_uint32 count = 0;
    sc_result res = sc_memory_find_links_with_content(m_ctx, stream.m_stream, &results, &count);

    result.clear();
    if (res == SC_RESULT_OK)
    {
        ASSERT_NOT_NULL(results);
        result.assign(results, results + count);

        free(results);
    }

    return res;
}

sc_result Memory::sc_memory_stat(sc_stat & stat)
{
    return sc_memory_stat(stat);
}

Iterator3 Memory::iterator3_f_a_a(sc_addr a0, sc_type t1, sc_type t2)
{
    return Iterator3(sc_iterator3_f_a_a_new(m_ctx, a0, t1, t2));
}

Iterator3 Memory::iterator3_f_a_f(sc_addr a0, sc_type t1, sc_addr a2)
{
    return Iterator3(sc_iterator3_f_a_f_new(m_ctx, a0, t1, a2));
}

Iterator3 Memory::iterator3_a_a_f(sc_type t0, sc_type t1, sc_addr a2)
{
    return Iterator3(sc_iterator3_a_a_f_new(m_ctx, t0, t1, a2));
}

Iterator5 Memory::iterator5_a_a_f_a_f(sc_type t0, sc_type t1, sc_addr a2, sc_type t3, sc_addr a4)
{
    return Iterator5(sc_iterator5_a_a_f_a_f_new(m_ctx, t0, t1, a2, t3, a4));
}

Iterator5 Memory::iterator5_f_a_a_a_f(sc_addr a0, sc_type t1, sc_type t2, sc_type t3, sc_addr a4)
{
    return Iterator5(sc_iterator5_f_a_a_a_f_new(m_ctx, a0, t1, t2, t3, a4));
}

Iterator5 Memory::iterator5_f_a_f_a_f(sc_addr a0, sc_type t1, sc_addr a2, sc_type t3, sc_addr a4)
{
    return Iterator5(sc_iterator5_f_a_f_a_f_new(m_ctx, a0, t1, a2, t3, a4));
}

Iterator5 Memory::iterator5_f_a_f_a_a(sc_addr a0, sc_type t1, sc_addr a2, sc_type t3, sc_type t4)
{
    return Iterator5(sc_iterator5_f_a_f_a_a_new(m_ctx, a0, t1, a2, t3, t4));
}

Iterator5 Memory::iterator5_f_a_a_a_a(sc_addr a0, sc_type t1, sc_type t2, sc_type t3, sc_type t4)
{
    return Iterator5(sc_iterator5_f_a_a_a_a_new(m_ctx, a0, t1, t2, t3, t4));
}

Iterator5 Memory::iterator5_a_a_f_a_a(sc_type t0, sc_type t1, sc_addr a2, sc_type t3, sc_type t4)
{
    return Iterator5(sc_iterator5_a_a_f_a_a_new(m_ctx, t0, t1, a2, t3, t4));
}


}
