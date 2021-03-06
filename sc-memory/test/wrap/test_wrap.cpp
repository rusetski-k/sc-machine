/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "wrap/sc_memory_headers.hpp"
#include "test_sc_object.hpp"
#include "test_sc_agent.hpp"
#include <glib.h>

void init_memory()
{
    sc_memory_params params;
    sc_memory_params_clear(&params);

    params.clear = SC_TRUE;
    params.repo_path = "repo";
    params.config_file = "sc-memory.ini";
    params.ext_path = 0;

    ScMemory::initialize(params);
}

void shutdown_memory(bool save)
{
    ScMemory::shutdown(save);
}

bool has_addr(tAddrVector const & v, ScAddr const & addr)
{
    for (tAddrVector::const_iterator it = v.begin(); it != v.end(); ++it)
    {
        if (*it == addr)
            return true;
    }

    return false;
}


void test_common_elements()
{
    init_memory();

    {
        ScMemoryContext ctx;
        ScAddr addr = ctx.createNode(sc_type_const);
        g_assert(addr.isValid());

        ScAddr link = ctx.createLink();
        g_assert(link.isValid());

        ScAddr arc = ctx.createArc(sc_type_arc_pos_const_perm, addr, link);
        g_assert(arc.isValid());

        g_assert(ctx.isElement(addr));
        g_assert(ctx.isElement(link));
        g_assert(ctx.isElement(arc));

        g_assert(ctx.getArcBegin(arc) == addr);
        g_assert(ctx.getArcEnd(arc) == link);

        g_assert(ctx.getElementType(addr) == ScType(sc_type_node | sc_type_const));
        g_assert(ctx.getElementType(link) == ScType(sc_type_link));
        g_assert(ctx.getElementType(arc) == ScType(sc_type_arc_pos_const_perm));

        g_assert(ctx.setElementSubtype(addr, sc_type_var));
        g_assert(ctx.getElementType(addr) == ScType(sc_type_node | sc_type_var));

        g_assert(ctx.eraseElement(addr));
        g_assert(!ctx.isElement(addr));
        g_assert(!ctx.isElement(arc));
        g_assert(ctx.isElement(link));
    }

    shutdown_memory(false);
}

void test_common_iterators()
{
    init_memory();

    {
        ScMemoryContext ctx;
        ScAddr addr1 = ctx.createNode(sc_type_const);
        ScAddr addr2 = ctx.createNode(sc_type_var);
        ScAddr arc1 = ctx.createArc(sc_type_arc_pos_const_perm, addr1, addr2);

        g_assert(addr1.isValid());
        g_assert(addr2.isValid());
        g_assert(arc1.isValid());

        g_assert(ctx.isElement(addr1));
        g_assert(ctx.isElement(addr2));
        g_assert(ctx.isElement(arc1));

        {
            ScIterator3Ptr iter3 = ctx.iterator3(addr1, sc_type_arc_pos_const_perm, addr2);
            g_assert(iter3->next());
            g_assert(iter3->value(0) == addr1);
            g_assert(iter3->value(1) == arc1);
            g_assert(iter3->value(2) == addr2);
        }

        {
            ScIterator3Ptr iter3 = ctx.iterator3(addr1, sc_type_arc_pos_const_perm, sc_type_node);
            g_assert(iter3->next());
            g_assert(iter3->value(0) == addr1);
            g_assert(iter3->value(1) == arc1);
            g_assert(iter3->value(2) == addr2);
        }

        {
            ScIterator3Ptr iter3 = ctx.iterator3(sc_type_node, sc_type_arc_pos_const_perm, addr2);
            g_assert(iter3->next());
            g_assert(iter3->value(0) == addr1);
            g_assert(iter3->value(1) == arc1);
            g_assert(iter3->value(2) == addr2);
        }

        ScAddr addr3 = ctx.createNode(sc_type_const);
        ScAddr arc2 = ctx.createArc(sc_type_arc_pos_const_perm, addr3, arc1);

        g_assert(addr3.isValid());
        g_assert(arc2.isValid());

        g_assert(ctx.isElement(addr3));
        g_assert(ctx.isElement(arc2));

        {
            ScIterator5Ptr iter5 = ctx.iterator5(sc_type_node, sc_type_arc_pos_const_perm, addr2, sc_type_arc_pos_const_perm, sc_type_node);

            g_assert(iter5->next());

            g_assert(iter5->value(0) == addr1);
            g_assert(iter5->value(1) == arc1);
            g_assert(iter5->value(2) == addr2);
            g_assert(iter5->value(3) == arc2);
            g_assert(iter5->value(4) == addr3);
        }

        {
            ScIterator5Ptr iter5 = ctx.iterator5(sc_type_node, sc_type_arc_pos_const_perm, addr2, sc_type_arc_pos_const_perm, addr3);

            g_assert(iter5->next());

            g_assert(iter5->value(0) == addr1);
            g_assert(iter5->value(1) == arc1);
            g_assert(iter5->value(2) == addr2);
            g_assert(iter5->value(3) == arc2);
            g_assert(iter5->value(4) == addr3);
        }

        {
            ScIterator5Ptr iter5 = ctx.iterator5(addr1, sc_type_arc_pos_const_perm, sc_type_node, sc_type_arc_pos_const_perm, sc_type_node);

            g_assert(iter5->next());

            g_assert(iter5->value(0) == addr1);
            g_assert(iter5->value(1) == arc1);
            g_assert(iter5->value(2) == addr2);
            g_assert(iter5->value(3) == arc2);
            g_assert(iter5->value(4) == addr3);
        }

        {
            ScIterator5Ptr iter5 = ctx.iterator5(addr1, sc_type_arc_pos_const_perm, sc_type_node, sc_type_arc_pos_const_perm, addr3);

            g_assert(iter5->next());

            g_assert(iter5->value(0) == addr1);
            g_assert(iter5->value(1) == arc1);
            g_assert(iter5->value(2) == addr2);
            g_assert(iter5->value(3) == arc2);
            g_assert(iter5->value(4) == addr3);
        }

        {
            ScIterator5Ptr iter5 = ctx.iterator5(addr1, sc_type_arc_pos_const_perm, addr2, sc_type_arc_pos_const_perm, sc_type_node);

            g_assert(iter5->next());

            g_assert(iter5->value(0) == addr1);
            g_assert(iter5->value(1) == arc1);
            g_assert(iter5->value(2) == addr2);
            g_assert(iter5->value(3) == arc2);
            g_assert(iter5->value(4) == addr3);
        }

        {
            ScIterator5Ptr iter5 = ctx.iterator5(addr1, sc_type_arc_pos_const_perm, addr2, sc_type_arc_pos_const_perm, addr3);

            g_assert(iter5->next());

            g_assert(iter5->value(0) == addr1);
            g_assert(iter5->value(1) == arc1);
            g_assert(iter5->value(2) == addr2);
            g_assert(iter5->value(3) == arc2);
            g_assert(iter5->value(4) == addr3);
        }

        {
            std::string str("test content string");
            ScStream stream(str.c_str(), (sc_uint32)str.size(), SC_STREAM_FLAG_READ);
            ScAddr link = ctx.createLink();

            g_assert(link.isValid());
            g_assert(ctx.isElement(link));
            g_assert(ctx.setLinkContent(link, stream));

            ScStream stream2;
            g_assert(ctx.getLinkContent(link, stream2));

            g_assert(stream.size() == stream2.size());
            g_assert(stream2.seek(SC_STREAM_SEEK_SET, 0));

            std::string str2;
            str2.resize(stream2.size());
            for (sc_uint i = 0; i < stream2.size(); ++i)
            {
                sc_char c;
                sc_uint32 readBytes;
                g_assert(stream2.read(&c, sizeof(c), readBytes));
                g_assert(readBytes == sizeof(c));

                str2[i] = c;
            }

            g_assert(str == str2);

            tAddrList result;
            g_assert(ctx.findLinksByContent(stream, result));
            g_assert(result.size() == 1);
            g_assert(result.front() == link);
        }

    }

    shutdown_memory(false);
}

void test_common_streams()
{
    init_memory();

    {
        static int const length = 1024;
        unsigned char buff[length];

        for (int i = 0; i < length; ++i)
            buff[i] = rand() % 256;

        ScStream stream((sc_char*)buff, length, SC_STREAM_FLAG_READ);

        g_assert(stream.isValid());
        g_assert(stream.hasFlag(SC_STREAM_FLAG_READ));
        g_assert(stream.hasFlag(SC_STREAM_FLAG_SEEK));
        g_assert(stream.hasFlag(SC_STREAM_FLAG_TELL));
        g_assert(!stream.eof());
        g_assert(stream.pos() == 0);
        g_assert(stream.size() == length);

        for (int i = 0; i < length; ++i)
        {
            unsigned char c;
            sc_uint32 readBytes;
            g_assert(stream.read((sc_char*)&c, sizeof(c), readBytes));
            g_assert(c == buff[i]);
        }

        g_assert(stream.eof());
        g_assert(stream.pos() == length);

        // random seek
        static int const seekOpCount = 1000000;
        for (int i = 0; i < seekOpCount; ++i)
        {
            sc_uint32 pos = rand() % length;
            g_assert(stream.seek(SC_STREAM_SEEK_SET, pos));


            unsigned char c;
            sc_uint32 readBytes;
            g_assert(stream.read((sc_char*)&c, sizeof(c), readBytes));
            g_assert(c == buff[pos]);
        }
    }

    shutdown_memory(false);
}

void test_common_templates()
{
	init_memory();
	{
		ScMemoryContext ctx;
		ScAddr const addr1 = ctx.createNode(0);
		ScAddr const addr2 = ctx.createNode(0);
		ScAddr const addr3 = ctx.createNode(0);

		ScAddr const edge1 = ctx.createArc(sc_type_arc_pos_const_perm, addr1, addr2);
		ScAddr const edge2 = ctx.createArc(sc_type_arc_pos_const_perm, addr3, edge1);

		
		{
			ScTemplate templ;

			templ
				.triple(addr1 >> "addr1",
						ScType(sc_type_arc_pos_const_perm) >> "edge1",
						ScType(sc_type_node) >> "addr2"
				)
                .triple(ScType(sc_type_node),
						ScType(sc_type_arc_pos_const_perm),
						"edge1"
				)
                .triple("addr2",
						ScType(sc_type_arc_common),
						"edge1");

			ScTemplateGenResult result;
			g_assert(ctx.helperGenTemplate(templ, result));

			g_assert(result[0] == result["addr1"]);
			g_assert(result[1] == result["edge1"]);
			g_assert(result[2] == result["addr2"]);
			g_assert(result[5] == result["edge1"]);
			g_assert(result[6] == result["addr2"]);
			g_assert(result[8] == result["edge1"]);

            ScIterator5Ptr it5 = ctx.iterator5(addr1, sc_type_arc_pos_const_perm, sc_type_node, sc_type_arc_pos_const_perm, sc_type_node);
			g_assert(it5->next());
			g_assert(it5->value(0) == result["addr1"]);
			g_assert(it5->value(1) == result["edge1"]);
			g_assert(it5->value(2) == result["addr2"]);
			g_assert(it5->value(3) == result[4]);
			g_assert(it5->value(4) == result[3]);

            ScIterator3Ptr it3 = ctx.iterator3(result["addr2"], sc_type_arc_common, sc_type_arc_pos_const_perm);
			g_assert(it3->next());
			g_assert(it3->value(0) == result["addr2"]);
			g_assert(it3->value(1) == result[7]);
            g_assert(it3->value(2) == result["edge1"]);


            // test template search
            {
                ScTemplateSearchResult searchResult;
                g_assert(ctx.helperSearchTemplate(templ, searchResult));

                g_assert(searchResult.getSize() == 1);

                ScTemplateSearchResultItem const & res = searchResult.getResult(0);
                g_assert(res[0] == res["addr1"]);
                g_assert(res[1] == res["edge1"]);
                g_assert(res[2] == res["addr2"]);
                g_assert(res[5] == res["edge1"]);
                g_assert(res[6] == res["addr2"]);
                g_assert(res[8] == res["edge1"]);

                g_assert(it5->value(0) == res["addr1"]);
                g_assert(it5->value(1) == res["edge1"]);
                g_assert(it5->value(2) == res["addr2"]);
                g_assert(it5->value(3) == res[4]);
                g_assert(it5->value(4) == res[3]);

                g_assert(it3->value(0) == res["addr2"]);
                g_assert(it3->value(1) == res[7]);
                g_assert(it3->value(2) == res["edge1"]);
            }

            // template search test 2
            {
                size_t const testCount = 10;
                tAddrVector nodes, edges;

                ScAddr addrSrc = ctx.createNode(sc_type_const);
                g_assert(addrSrc.isValid());
                for (size_t i = 0; i < testCount; ++i)
                {
                    ScAddr const addrTrg = ctx.createNode(sc_type_var);
                    g_assert(addrTrg.isValid());

                    ScAddr const addrEdge = ctx.createArc(sc_type_arc_pos_const_perm, addrSrc, addrTrg);
                    g_assert(addrEdge.isValid());

                    nodes.push_back(addrTrg);
                    edges.push_back(addrEdge);
                }

                ScTemplate templ2;

                templ2.triple(addrSrc >> "addrSrc",
                    ScType(sc_type_arc_pos_const_perm) >> "edge",
                    ScType(sc_type_node | sc_type_var) >> "addrTrg");

                ScTemplateSearchResult result2;
                g_assert(ctx.helperSearchTemplate(templ2, result2));
                size_t const count = result2.getSize();
                for (size_t i = 0; i < count; ++i)
                {
                    ScTemplateSearchResultItem r = result2.getResult(i);

                    g_assert(r["addrSrc"] == addrSrc);

                    g_assert(has_addr(edges, r["edge"]));
                    g_assert(has_addr(nodes, r["addrTrg"]));
                }
            }
		}

		{
			ScTemplate templ;

			templ
				.tripleWithRelation(
					addr1,
					ScType(sc_type_arc_pos_const_perm),
					ScType(sc_type_node),
					ScType(sc_type_arc_pos_const_perm),
					addr3
				);

			ScTemplateSearchResult result;
			g_assert(ctx.helperSearchTemplate(templ, result));
			g_assert(result.getSize() > 0);

			ScTemplateSearchResultItem item = result.getResult(0);

			g_assert(addr1 == item[0]);
			g_assert(addr2 == item[2]);
			g_assert(addr3 == item[3]);
			g_assert(edge1 == item[1]);
			g_assert(edge2 == item[4]);
		}

		{
			ScTemplate templ;

			templ
				.tripleWithRelation(
					addr1 >> "1",
					ScType(sc_type_arc_pos_const_perm) >> "2",
					ScType(sc_type_node) >> "3",
					ScType(sc_type_arc_pos_const_perm) >> "4",
					addr3 >> "5"
				);

			ScTemplateSearchResult result;
			g_assert(ctx.helperSearchTemplate(templ, result));
			g_assert(result.getSize() > 0);

			ScTemplateSearchResultItem item = result.getResult(0);

			g_assert(addr1 == item["1"]);
			g_assert(addr2 == item["3"]);
			g_assert(addr3 == item["5"]);
			g_assert(edge1 == item["2"]);
			g_assert(edge2 == item["4"]);
		}

	}

	shutdown_memory(false);
}

void test_codegen_keynodes()
{
    init_memory();

    {
        ScMemoryContext ctx(sc_access_lvl_make_min);

        ScAddr addr1 = ctx.createNode(sc_type_const);
        g_assert(addr1.isValid());
        g_assert(ctx.helperSetSystemIdtf("test_keynode1", addr1));

        ScAddr addr2 = ctx.createNode(sc_type_var);
        g_assert(addr2.isValid());
        g_assert(ctx.helperSetSystemIdtf("test_keynode2", addr2));

        ScAddr addr3 = ctx.createNode(sc_type_var);
        g_assert(addr3.isValid());
        g_assert(ctx.helperSetSystemIdtf("test_keynode3", addr3));
        
        n1::n2::TestObject obj1;
        g_assert(addr1 == obj1.mTestKeynode1);
        g_assert(addr2 == obj1.mTestKeynode2);

        obj1.initGlobal();
        g_assert(addr3 == obj1.mTestKeynode3);

        ScAddr addrForce;
        g_assert(ctx.helperFindBySystemIdtf("test_keynode_force", addrForce));
        g_assert(addrForce == obj1.mTestKeynodeForce);
    }

    shutdown_memory(false);
}

void test_codegen_agent()
{
	init_memory();

	{
		ScMemoryContext ctx(sc_access_lvl_make_min);

		SC_AGENT_REGISTER(TestAgent)

		SC_AGENT_UNREGISTER(TestAgent)
	}

	shutdown_memory(false);
}

void test_perfomance_templ()
{
	init_memory();
	{
		ScAddr node1, node2, node3, node4, edge1, edge2, edge3;
		ScMemoryContext ctx(sc_access_lvl_make_min);

		{
			// preapre test
			ScTemplate templ;
			templ
				.triple(ScType(sc_type_node) >> "Node1",
				ScType(sc_type_arc_pos_const_perm) >> "Edge1",
				ScType(sc_type_node) >> "Node2")
				.triple(ScType(sc_type_node) >> "Node3",
				ScType(sc_type_arc_pos_const_perm) >> "Edge2",
				"Edge1")
				.triple(ScType(sc_type_node) >> "Node4",
				ScType(sc_type_arc_pos_const_perm) >> "Edge3",
				"Node1");

			ScTemplateGenResult result;
			if (ctx.helperGenTemplate(templ, result))
			{
				node1 = result["Node1"];
				node2 = result["Node2"];
				node3 = result["Node3"];
				node4 = result["Node4"];
				edge1 = result["Edge1"];
				edge2 = result["Edge2"];
				edge3 = result["Edge3"];
			}
			else
				g_assert(false);
		}


		static size_t const iterCount = 10000;
		printf("Search (template)\n");
		g_test_timer_start();

		for (size_t i = 0; i < iterCount; ++i)
		{
			ScTemplate templ;
			templ
				.triple(node1,
						ScType(sc_type_arc_pos_const_perm) >> "Edge1",
						ScType(sc_type_node))
				.triple(node3,
						ScType(sc_type_arc_pos_const_perm),
						"Edge1")
				.triple(node4,
						ScType(sc_type_arc_pos_const_perm),
						node1);

			ScTemplateSearchResult result;
			g_assert(ctx.helperSearchTemplate(templ, result));
		}

		double const time = g_test_timer_elapsed();
		printf("Time: %.3f\n s", time);
		printf("Time per search: %.8f s", time / iterCount);
	}
	shutdown_memory(false);
}

void test_common_struct()
{
	init_memory();
	
	{
		ScMemoryContext ctx(sc_access_lvl_make_min);

		ScAddr structAddr = ctx.createNode(sc_type_node_struct | sc_type_const);
		g_assert(structAddr.isValid());

		ScStruct st(&ctx, structAddr);

		ScAddr const addr1 = ctx.createNode(sc_type_node_class);
		g_assert(addr1.isValid());
		ScAddr const addr2 = ctx.createNode(sc_type_node_material);
		g_assert(addr2.isValid());
		
		st << addr1 << addr2;
		g_assert(st.hasElement(addr1));
		g_assert(st.hasElement(addr2));

		st >> addr1;

		g_assert(!st.hasElement(addr1));
		g_assert(st.hasElement(addr2));

		st >> addr2;

		g_assert(!st.hasElement(addr1));
		g_assert(!st.hasElement(addr2));
		g_assert(st.isEmpty());

		// attributes
		ScAddr const attrAddr = ctx.createNode(sc_type_node_role);
		g_assert(attrAddr.isValid());

		g_assert(st.append(addr1, attrAddr));
		ScIterator5Ptr iter5 = ctx.iterator5(
			structAddr,
			SC_TYPE(sc_type_arc_pos_const_perm),
			SC_TYPE(0),
			SC_TYPE(sc_type_arc_pos_const_perm),
			attrAddr);

		bool found = false;
		while (iter5->next())
		{
			g_assert(!found);	// one time
			g_assert(iter5->value(0) == structAddr);
			g_assert(iter5->value(2) == addr1);
			g_assert(iter5->value(4) == attrAddr);
			found = true;
		}
		g_assert(found);

	}

	shutdown_memory(false);
}

void test_common_sc_templates()
{
	init_memory();
	{
		ScMemoryContext ctx(sc_access_lvl_make_min);

		/*			_y
		 *			^
		 *			|
		 *			| <----- _z
		 *			|
		 *			x <----- _s
		 *
		 * scs: x _-> _z:: _y;; _s _-> x;;
		 */ 
		ScAddr templateAddr = ctx.createNode(sc_type_const | sc_type_node_struct);
		g_assert(templateAddr.isValid());

		ScStruct templStruct(&ctx, templateAddr);
		ScAddr xAddr;
		{

			ScAddr _yAddr, _zAddr, _sAddr;

			xAddr = ctx.createNode(sc_type_const | sc_type_node_material);
			g_assert(xAddr.isValid());
			g_assert(ctx.helperSetSystemIdtf("x", xAddr));

			_yAddr = ctx.createNode(sc_type_var);
			g_assert(_yAddr.isValid());
			g_assert(ctx.helperSetSystemIdtf("_y", _yAddr));

			_zAddr = ctx.createNode(sc_type_var | sc_type_node_role);
			g_assert(_zAddr.isValid());
			g_assert(ctx.helperSetSystemIdtf("_z", _zAddr));

			_sAddr = ctx.createNode(sc_type_node_class | sc_type_var);
			g_assert(_sAddr.isValid());
			g_assert(ctx.helperSetSystemIdtf("_s", _sAddr));

			ScAddr xyAddr = ctx.createArc(sc_type_arc_access | sc_type_var, xAddr, _yAddr);
			g_assert(xyAddr.isValid());
			ScAddr zxyAddr = ctx.createArc(sc_type_arc_access | sc_type_var, _zAddr, xyAddr);
			g_assert(zxyAddr.isValid());
			ScAddr sxAddr = ctx.createArc(sc_type_arc_access | sc_type_var, _sAddr, xAddr);
			g_assert(sxAddr.isValid());

			// append created elements into struct
			templStruct << xAddr << _yAddr << _zAddr << xyAddr << zxyAddr << _sAddr << sxAddr;
		}

		ScTemplate templ;
		g_assert(ctx.helperBuildTemplate(templ, templateAddr));

		// create test structure that correspond to template
		{
			ScAddr yAddr, zAddr, sAddr;

			yAddr = ctx.createNode(sc_type_const);
			g_assert(yAddr.isValid());

			zAddr = ctx.createNode(sc_type_const | sc_type_node_role);
			g_assert(zAddr.isValid());

			sAddr = ctx.createNode(sc_type_node_class | sc_type_const);
			g_assert(sAddr.isValid());

			ScAddr xyAddr = ctx.createArc(sc_type_arc_pos_const_perm, xAddr, yAddr);
			g_assert(xyAddr.isValid());
			ScAddr zxyAddr = ctx.createArc(sc_type_arc_pos_const_perm, zAddr, xyAddr);
			g_assert(zxyAddr.isValid());
			ScAddr sxAddr = ctx.createArc(sc_type_arc_pos_const_perm, sAddr, xAddr);
			g_assert(sxAddr.isValid());


			// test search by template
			{
				ScTemplateSearchResult result;
				g_assert(ctx.helperSearchTemplate(templ, result));

				g_assert(result.getSize() == 1);
				ScTemplateSearchResultItem item = result.getResult(0);

				g_assert(item["x"] == xAddr);
				g_assert(item["_y"] == yAddr);
				g_assert(item["_z"] == zAddr);
				g_assert(item["_s"] == sAddr);
			}
		}
	}

	shutdown_memory(false);
}

void test_common_search_in_struct()
{
	init_memory();
	{
		ScMemoryContext ctx(sc_access_lvl_make_min);

		/*
		 *   _y
		 *    ^
		 *    | <--- _z
		 *    x
		 * scs: x _-> _z:: _y;;
		 */

		ScAddr templateAddr = ctx.createNode(*ScType::NODE_CONST_STRUCT);
		g_assert(templateAddr.isValid());

		ScAddr xAddr, _yAddr, _zAddr, _xyEdgeAddr, _zxyEdgeAddr;
		ScStruct templStruct(&ctx, templateAddr);
		{
			xAddr = ctx.createNode(*ScType::NODE_CONST);
			g_assert(xAddr.isValid());
			g_assert(ctx.helperSetSystemIdtf("x", xAddr));

			_yAddr = ctx.createNode(*ScType::NODE_VAR);
			g_assert(_yAddr.isValid());
			g_assert(ctx.helperSetSystemIdtf("_y", _yAddr));

			_zAddr = ctx.createNode(*ScType::NODE_VAR);
			g_assert(_zAddr.isValid());
			g_assert(ctx.helperSetSystemIdtf("_z", _zAddr));

			_xyEdgeAddr = ctx.createArc(*ScType::EDGE_ACCESS_VAR_POS_PERM, xAddr, _yAddr);
			g_assert(_xyEdgeAddr.isValid());
			g_assert(ctx.helperSetSystemIdtf("_xyEdge", _xyEdgeAddr));

			_zxyEdgeAddr = ctx.createArc(*ScType::EDGE_ACCESS_VAR_POS_PERM, _zAddr, _xyEdgeAddr);
			g_assert(_zxyEdgeAddr.isValid());
			g_assert(ctx.helperSetSystemIdtf("_zxyEdge", _zxyEdgeAddr));

			templStruct << xAddr << _yAddr << _zAddr << _xyEdgeAddr << _zxyEdgeAddr;
		}

		ScTemplate templ;
		g_assert(ctx.helperBuildTemplate(templ, templateAddr));

		// create text struct
		ScAddr testStructAddr = ctx.createNode(*ScType::NODE_CONST_STRUCT);
		g_assert(testStructAddr.isValid());

		/*   y ---> u
		 *   ^
		 *   | <--- z
		 *   x
		 *   | <--- s
		 *   v
		 *   g
		 * scs: x -> z: y; s: g;; y -> u;;
		 */
		ScAddr tyAddr, txAddr, tgAddr, tuAddr, tzAddr, tsAddr,
			tyuEdgeAddr, txyEdgeAddr, txgEdgeAddr, tzxyEdgeAddr, tsxgEdgeAddr;

		ScStruct testStruct(&ctx, testStructAddr);
		{
			txAddr = xAddr;

			tyAddr = ctx.createNode(*ScType::NODE_CONST);
			g_assert(tyAddr.isValid());

			tgAddr = ctx.createNode(*ScType::NODE_CONST);
			g_assert(tgAddr.isValid());

			tuAddr = ctx.createNode(*ScType::NODE_CONST);
			g_assert(tuAddr.isValid());

			tzAddr = ctx.createNode(*ScType::NODE_CONST);
			g_assert(tzAddr.isValid());

			tsAddr = ctx.createNode(*ScType::NODE_CONST);
			g_assert(tsAddr.isValid());

			tyuEdgeAddr = ctx.createArc(*ScType::EDGE_ACCESS_CONST_POS_PERM, tyAddr, tuAddr);
			g_assert(tyuEdgeAddr.isValid());

			txyEdgeAddr = ctx.createArc(*ScType::EDGE_ACCESS_CONST_POS_PERM, txAddr, tyAddr);
			g_assert(txyEdgeAddr.isValid());

			txgEdgeAddr = ctx.createArc(*ScType::EDGE_ACCESS_CONST_POS_PERM, txAddr, tgAddr);
			g_assert(txgEdgeAddr.isValid());

			tzxyEdgeAddr = ctx.createArc(*ScType::EDGE_ACCESS_CONST_POS_PERM, tzAddr, txyEdgeAddr);
			g_assert(tzxyEdgeAddr.isValid());

			tsxgEdgeAddr = ctx.createArc(*ScType::EDGE_ACCESS_CONST_POS_PERM, tsAddr, txgEdgeAddr);
			g_assert(tsxgEdgeAddr.isValid());

			testStruct << tyAddr << txAddr << tgAddr 
					   << tuAddr << tzAddr << tsAddr 
					   << tyuEdgeAddr << txyEdgeAddr 
					   << txgEdgeAddr << tzxyEdgeAddr 
					   << tsxgEdgeAddr;
		}

		// add extra edges that not included into struct
		// scs: x -> t: y;;
		ScAddr edge1 = ctx.createArc(*ScType::EDGE_ACCESS_CONST_POS_PERM, txAddr, tyAddr);
		g_assert(edge1.isValid());
		ScAddr edge2 = ctx.createArc(*ScType::EDGE_ACCESS_CONST_POS_PERM, tzAddr, edge1);
		g_assert(edge2.isValid());

		{
			ScTemplateSearchResult result;
			g_assert(ctx.helperSearchTemplateInStruct(templ, *testStruct, result));

			g_assert(result.getSize() == 2);
			for (uint32_t i = 0; i < result.getSize(); ++i)
			{
				ScTemplateSearchResultItem res1 = result.getResult(i);
				g_assert(res1["x"] == xAddr);
				g_assert(res1["_y"] == tyAddr || res1["_y"] == tgAddr);
				g_assert(res1["_z"] == tzAddr || res1["_z"] == tsAddr);
				g_assert(res1["_xyEdge"] == txyEdgeAddr || res1["_xyEdge"] == txgEdgeAddr);
				g_assert(res1["_zxyEdge"] == tsxgEdgeAddr || res1["_zxyEdge"] == tzxyEdgeAddr);
			}

		}

	}
	shutdown_memory(false);
}

int main(int argc, char *argv[])
{
    g_test_init(&argc, &argv, NULL);

    g_test_add_func("/common/elements", test_common_elements);
    g_test_add_func("/common/iterators", test_common_iterators);
    g_test_add_func("/common/streams", test_common_streams);
	g_test_add_func("/common/templates", test_common_templates);
	g_test_add_func("/common/struct", test_common_struct);
	g_test_add_func("/common/sc_templates", test_common_sc_templates);
	g_test_add_func("/common/searchInStruct", test_common_search_in_struct);

    g_test_add_func("/codegen/keynodes", test_codegen_keynodes);
	g_test_add_func("/codegen/agent", test_codegen_agent);
	g_test_add_func("/perfomance/templates", test_perfomance_templ);

    g_test_run();

    return 0;
}
