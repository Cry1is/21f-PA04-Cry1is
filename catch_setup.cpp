//
// Created by MARK FONTENOT on 9/14/21.
//

/**
 * This file is used to create a separate compilation unit just for
 * the CATCH2 header.  *** DO NOT EDIT ***.  Put your tests in another
 * .cpp file.
 *
 */

#define CATCH_CONFIG_RUNNER

int runCatchTests();

#include "catch.hpp"

int main() {
    return runCatchTests();
}

int runCatchTests()
{
    //This line of code causes the Catch library to
    //run the tests in the project.
    return Catch::Session().run();
}