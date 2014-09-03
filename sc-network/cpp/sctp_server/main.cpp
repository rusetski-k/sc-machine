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

#include <QtCore/QCoreApplication>
#include <QtCore/QCommandLineParser>

#include <iostream>

#include "sctpServer.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName(SCTP_SERVER_NAME);
    QCoreApplication::setApplicationVersion(SCTP_SERVER_VERSION_STR);

    QCommandLineParser parser;
    parser.setApplicationDescription("Implementation of " SCTP_SERVER_NAME);
    const QCommandLineOption optionHelp = parser.addHelpOption();
    const QCommandLineOption optionVersion = parser.addVersionOption();

    parser.process(app);

    if (parser.isSet(optionHelp))
        parser.showHelp();

    if (parser.isSet(optionVersion))
    {
        std::cout << SCTP_SERVER_NAME << " version " << SCTP_SERVER_VERSION_STR << std::endl;
        return 0;
    }

    QString config("config.ini");
    if (argc > 1)
        config = argv[1];

    sctpServer server;
    if (!server.start(config))
        exit(0);

    QObject::connect(&app, SIGNAL(aboutToQuit()), &server, SLOT(stop()));

    
    return app.exec();
}
