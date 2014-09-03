/*
-----------------------------------------------------------------------------
This source file is part of OSTIS (Open Semantic Technology for Intelligent Systems)
For the latest info, see http://www.ostis.net

Copyright (c) 2010-2014 OSTIS

OSTIS is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

OSTIS is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with OSTIS.  If not, see <http://www.gnu.org/licenses/>.
-----------------------------------------------------------------------------
*/

#ifndef _sctpVersion_h_
#define _sctpVersion_h_

#define SCTP_SERVER_VERSION_MAJOR   0
#define SCTP_SERVER_VERSION_MINOR   2
#define SCTP_SERVER_VERSION_PATCH   0

#define SCTP_SERVER_NAME    "SCTP (Semantic Code Transport Protocol) Server"
#define SCTP_SERVER_VERSION (SCTP_SERVER_VERSION_MAJOR << 2) | (SCTP_SERVER_VERSION_MINOR << 1) | SCTP_SERVER_VERSION_PATCH

#define _SCTP_STR_HELPER(x) #x
#define _SCTP_STR(x) _SCTP_STR_HELPER(x)
#define SCTP_SERVER_VERSION_STR _SCTP_STR(SCTP_SERVER_VERSION_MAJOR) "." _SCTP_STR(SCTP_SERVER_VERSION_MINOR) "." _SCTP_STR(SCTP_SERVER_VERSION_PATCH)

#endif
