#include <iostream>
#include "ortools/linear_solver/linear_solver.h"
#include "ortools/sat/cp_model.h"
#include "ortools/util/sorted_interval_list.h"
#include "absl/types/span.h"

using namespace operations_research::sat;

int main() {
    
    std::cout << "Program starting!" << std::endl;

    // Initialize the model
    CpModelBuilder cp_model;
    const long int heights[9] = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    absl::Span heights_span(heights);

    int len = sizeof heights / sizeof heights[0];

    // line_n represents position (index) of one of the two "lines" that form a container
    const operations_research::Domain domain_pos(0, len-1);
    const IntVar line_one = cp_model.NewIntVar(domain_pos).WithName("line one pos");
    const IntVar line_two = cp_model.NewIntVar(domain_pos).WithName("line two pos");

    // height_n represents the height (value) of one of the two "lines" that form a container
    const operations_research::Domain domain_height(0, INT_MAX);
    const IntVar height_one = cp_model.NewIntVar(domain_height).WithName("height one");
    const IntVar height_two = cp_model.NewIntVar(domain_height).WithName("height two");

    // Need two different lines to form a container for the water
    // one < two makes it so or-tools can find the diff/dist without needing abs val
    cp_model.AddLessThan(line_one, line_two);

    // Constrain height_n to be eq to the val @ heights with index line_n
    cp_model.AddElement(line_one, heights_span, height_one);
    cp_model.AddElement(line_two, heights_span, height_two);

    // Minimum of two lines making a container is as far as up as the water can go
    const IntVar min_of_heights = cp_model.NewIntVar(domain_height).WithName("min height");
    cp_model.AddMinEquality(min_of_heights, {height_one, height_two});

    const IntVar distance_between_lines = cp_model.NewIntVar(domain_height).WithName("distance between lines");
    // ScalProd is same as line_two - line_one
    cp_model.AddEquality(distance_between_lines, LinearExpr::ScalProd({line_two, line_one}, {1, -1}));

    // max_area is eq to the val of the smaller line making a container times the dist between lines
    const IntVar max_area = cp_model.NewIntVar(domain_height).WithName("max area");
    cp_model.AddProductEquality(max_area, {min_of_heights, distance_between_lines});

    // Goal of the problem is to maximize the area
    cp_model.Maximize(max_area);

    const CpSolverResponse response = Solve(cp_model.Build());
    LOG(INFO) << CpSolverResponseStats(response);

    LOG(INFO) << "Area of the container is: " << SolutionIntegerValue(response, max_area);
    
    return 0;
}
