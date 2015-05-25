/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "sc_refl_generator.hpp"

#include <boost/program_options.hpp>

int main(int argc, char ** argv)
{
    boost::program_options::options_description options_description("Reflection usage");
    options_description.add_options()
            ("help", "Display this message")
            ("version", "Displays version number")
            ("input-file,i", boost::program_options::value<std::string>(), "Path to header file for processing");

    boost::program_options::variables_map vm;
    boost::program_options::store(boost::program_options::command_line_parser(argc, argv).options(options_description).run(), vm);
    boost::program_options::notify(vm);

    if (vm.count("help") || !vm.count("input-file"))
    {
        std::cout << options_description;
        return 0;
    }

    if (vm.count("input-file"))
    {
        reflection::GeneratorParams params;
        params.mInputFile = vm["input-file"].as<std::string>();

        reflection::Generator generator;
        generator.process(params);
    }

    return 0;
}
