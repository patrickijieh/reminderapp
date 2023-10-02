#include "util.h"


void util::sleep(int ms)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}
