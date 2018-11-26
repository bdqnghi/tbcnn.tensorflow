/**
 *
 * main
 *
 */

#ifdef _WIN32
#  ifndef _CRT_SECURE_NO_WARNINGS
#    define _CRT_SECURE_NO_WARNINGS
#  endif
#endif

#include <app/app.h>

#include <auxiliary/logger.h>
#include <auxiliary/test.h>

#include <chrono>
#include <cstring>

IMPLEMENT_TESTRUNNER();

int main(int argc, char* argv[]) {
    
    Log::setLogLevel(Log::LevelInfo);

    if (argc >= 2 && 0 == std::strcmp(argv[1], "--test")) {
        RUN_TESTS("");
    } else {

        printf("************************\n");
        printf("* BREADTH-FIRST-SEARCH *\n");
        printf("************************\n\n");
        printf("Performing breadth-first-search...\n");

        auto tStart = std::chrono::high_resolution_clock::now();

        int result = Application().run();

        auto tElapsed = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - tStart).count();

        printf("Execution time was %0.3f seconds.\n", tElapsed);

        return result;
    }

    return 0;
}
