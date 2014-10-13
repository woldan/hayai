#ifndef __HAYAI_PROPERTYTREEOUTPUTTER
#define __HAYAI_PROPERTYTREEOUTPUTTER
#include "hayai_outputter.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace hayai
{
    /// JSON outputter.

    /// Prints the result to standard output.
    class PropertytreeOutputter
        :   public Outputter
    {
        typedef boost::property_tree::ptree ast_type;

    public:
        virtual void Begin(const std::size_t& benchmarksCount)
        {
            ast_.put("benchmarks.count", benchmarksCount);
        }


        virtual void End(const std::size_t& benchmarksCount)
        {
            ast_.put("benchmarks.run", benchmarksCount);
            boost::property_tree::write_json(std::cout, ast_, true);
        }


        virtual void BeginTest(const std::string& fixtureName,
                               const std::string& testName,
                               const std::string& parameters,
                               const std::size_t& runsCount,
                               const std::size_t& iterationsCount)
        {
            /* ast_type::iterator found = ast_.find("benchmarks"); */
            /* found = found->push_back(ast_type::value_type("tests", ast_type())); */
            /* found = found->push_back(ast_type::value_type("", ast_type())); */
            ast_type test;
            test.add("name", testName);
            test.add("fixture", fixtureName);
            test.add("parameters", parameters);
            test.add("runs", runsCount);
            test.add("iterations", iterationsCount);
            ast_.add_child("benchmarks.tests", test);
        }


        virtual void EndTest(const std::string& fixtureName,
                             const std::string& testName,
                             const std::string& parameters,
                             const TestResult& result)
        {
            ast_.put("benchmarks.total_in_ms", result.TimeTotal() / 1000000.0);
            ast_.put("benchmarks.average_run_in_us", result.RunTimeAverage() / 1000.0);
            ast_.put("benchmarks.fastest_run_in_us", result.RunTimeMinimum() / 1000.0);
            ast_.put("benchmarks.slowest_run_in_us", result.RunTimeMaximum() / 1000.0);
            ast_.put("benchmarks.average_runs_per_second", result.RunsPerSecondAverage());
            ast_.put("benchmarks.maximum_runs_per_second", result.RunsPerSecondMaximum());
            ast_.put("benchmarks.minimum_runs_per_second", result.RunsPerSecondMinimum());
            ast_.put("benchmarks.average_iteration_in_us", result.IterationTimeAverage() / 1000.0);
            ast_.put("benchmarks.fastest_iteration_in_us", result.IterationTimeMinimum() / 1000.0);
            ast_.put("benchmarks.slowest_iteration_in_us", result.IterationTimeMaximum() / 1000.0);
            ast_.put("benchmarks.average_iterations_per_second", result.IterationsPerSecondAverage());
            ast_.put("benchmarks.maximum_iterations_per_second", result.IterationsPerSecondMaximum());
            ast_.put("benchmarks.minimum_iterations_per_second", result.IterationsPerSecondMinimum());
        }

    private:
        ast_type ast_;
    };
}
#endif
