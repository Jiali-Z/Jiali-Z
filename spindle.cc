 /* ---------------------------------------------------------------------
 *
 * Milestone 1: Due: March 25, 2022
 * - Create a spindle-like mesh 
 * -A functioning time-independent Stoke solver. Use the method of manufactured
 * solutions to validate that your code work 
 *
 * ---------------------------------------------------------------------

 */


#include <deal.II/grid/tria.h>
#include <deal.II/grid/tria_accessor.h>
#include <deal.II/grid/tria_iterator.h>
#include <deal.II/grid/grid_generator.h>
#include <deal.II/grid/grid_out.h>

#include <iostream>
#include <fstream>
#include <cmath>

using namespace dealii;

void halfspindle_grid()
{
 Triangulation<2> tri;

 const double inner_radius=0.5, outer_radius=0.1,half_length=1.0;
 GridGenerator::truncated_cone(tri,inner_radius,outer_radius,half_length);
 tri.refine_global(4);

 std::ofstream out("half_spindle_1.svg");
 GridOut       grid_out;
 grid_out.write_svg(triangulation, out);
std::cout << "Grid written to half_spindle_1.svg" << std::endl;
}

int main()
{
halfspindle_grid();:
}

