// This file is part of the DerpVision Project.
// Licensing information can be found in the LICENSE file.
// (C) 2015 Group 13. All rights reserved.

#include <cstdlib>
#include <iostream>

#include <boost/program_options.hpp>

#include "ProCam.h"
#include "ProCamSystem.h"
#include "MasterServer.h"

using namespace dv;


/**
 * Encapsulates most of the functionality of the application.
 */
class MasterApplication {
 public:
  MasterApplication(uint16_t port)
    : port_(port)
  {
    (void) port_;
  }

  int Run() {
    return EXIT_SUCCESS;
  }

 private:
  /// Port number the server is listening on.
  uint16_t port_;
};


/**
 * Entry point of the application.
 */
int main(int argc, char **argv) {
  try {
    namespace po = boost::program_options;

    // Set up the description of all command line options.
    po::options_description description("DerpVision Master Server");
    description.add_options()
        ("help", "Print this message.")
        ("port", po::value<int>()->default_value(11630), "Set the port to listen on.");

    // Parse options.
    po::variables_map options;
    po::store(po::parse_command_line(argc, argv, description), options);
    po::notify(options);

    // Print help if requested.
    if (options.count("help")) {
      std::cout << description << std::endl;
      return EXIT_SUCCESS;
    }

    // Create & run the app.
    return MasterApplication(
        options["port"].as<int>()
    ).Run();
  } catch (const std::exception &ex) {
    std::cerr << "[Exception] " << ex.what() << std::endl;
    return EXIT_FAILURE;
  } catch (...) {
    std::cerr << "[Exception] Unknown exception." << std::endl;
    return EXIT_FAILURE;
  }
}

