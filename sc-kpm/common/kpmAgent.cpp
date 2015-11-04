/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "kpmAgent.hpp"

namespace kpm
{

	void Agent::initialize(sc::Addr const & addr, KeynodesPtr const & keynodes)
	{
		mAddr = addr;
		check_expr(mAddr.isValid());
		mKeynodes = keynodes;

		onPostInitialize();
	}

	void Agent::shutdown()
	{
		onPreShutdown();

		mKeynodes.reset();
	}

	void Agent::onPostInitialize()
	{

	}

	void Agent::onPreShutdown()
	{

	}

}