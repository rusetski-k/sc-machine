#pragma once

#include "sc_types.h"

namespace sc
{


class Stream
{
    friend class Memory;
public:
    explicit Stream(sc_stream * stream);
    ~Stream();

private:
    sc_stream * m_stream;
};

// -------- Iterators --------
class Iterator3
{
public:
    explicit Iterator3(sc_iterator3 * it);
    ~Iterator3();

    bool next() const;
    sc_addr value(uint8_t idx) const;

private:
    sc_iterator3 * m_it;
};

class Iterator5
{
public:
    explicit Iterator5(sc_iterator5 * it);
    ~Iterator5();

    bool next() const;
    sc_addr value(uint8_t idx) const;

private:
    sc_iterator5 * m_it;
};

// -------------------
class Memory
{
public:
    explicit Memory(sc_access_levels levels);
    ~Memory();

    bool is_element(sc_addr addr);
    sc_result element_free(sc_addr addr);
    sc_result element_type(sc_addr addr, sc_type & result);
    sc_result set_element_access_levels(sc_addr addr, sc_access_levels access_levels, sc_access_levels & new_value);
    sc_result get_element_access_levels(sc_addr addr, sc_access_levels & result);

    sc_addr node_new(sc_type type);
    sc_addr arc_new(sc_type type, sc_addr beg, sc_addr end);
    sc_addr link_new();


    sc_result get_arc_begin(sc_addr addr, sc_addr & result);
    sc_result get_arc_end(sc_addr addr, sc_addr & result);

    sc_result set_link_content(sc_addr addr, Stream const & stream);
    sc_result get_link_content(sc_addr addr, Stream ** stream);

    sc_result find_links_with_content(Stream const & stream, ScAddrVectorT & result);

    sc_result sc_memory_stat(sc_stat & stat);

    Iterator3 iterator3_f_a_a(sc_addr a0, sc_type t1, sc_type t2);
    Iterator3 iterator3_f_a_f(sc_addr a0, sc_type t1, sc_addr a2);
    Iterator3 iterator3_a_a_f(sc_type t0, sc_type t1, sc_addr a2);

    Iterator5 iterator5_a_a_f_a_f(sc_type t0, sc_type t1, sc_addr a2, sc_type t3, sc_addr a4);
    Iterator5 iterator5_f_a_a_a_f(sc_addr a0, sc_type t1, sc_type t2, sc_type t3, sc_addr a4);
    Iterator5 iterator5_f_a_f_a_f(sc_addr a0, sc_type t1, sc_addr a2, sc_type t3, sc_addr a4);
    Iterator5 iterator5_f_a_f_a_a(sc_addr a0, sc_type t1, sc_addr a2, sc_type t3, sc_type t4);
    Iterator5 iterator5_f_a_a_a_a(sc_addr a0, sc_type t1, sc_type t2, sc_type t3, sc_type t4);
    Iterator5 iterator5_a_a_f_a_a(sc_type t0, sc_type t1, sc_addr a2, sc_type t3, sc_type t4);

private:
    sc_memory_context * m_ctx;
};


}
