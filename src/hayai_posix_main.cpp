#include "hayai.hpp"

int main()
{
    hayai::PropertytreeOutputter jsonOutputter;

    hayai::Benchmarker::AddOutputter(jsonOutputter);
    hayai::Benchmarker::RunAllTests();
    return 0;
}
