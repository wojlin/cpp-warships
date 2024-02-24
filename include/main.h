#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <string.h>
#include <regex>
#include <thread>
#include <chrono>

#include "core.h"

using namespace std;

void run(int argc, char* argv[])
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    Core core(argc, argv);
}

#endif