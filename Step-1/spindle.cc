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
#include <deal.II/grid/grid_generator.h>
#include <deal.II/grid/grid_tools.h>
#include <deal.II/grid/manifold_lib.h>
#include <deal.II/grid/grid_out.h>
#include <deal.II/grid/grid_in.h>

#include <iostream>
#include <fstream>

#include <map>

using namespace dealii;

template <int dim>
void print_mesh_info(const Triangulation<dim> &triangulation,
                     const std::string &       filename)
{
  std::cout << "Mesh info:" << std::endl
            << " dimension: " << dim << std::endl
            << " no. of cells: " << triangulation.n_active_cells() << std::endl;
  {
    std::map<types::boundary_id, unsigned int> boundary_count;
    for (const auto &face : triangulation.active_face_iterators())
      if (face->at_boundary())
        boundary_count[face->boundary_id()]++;
    std::cout << " boundary indicators: ";
    for (const std::pair<const types::boundary_id, unsigned int> &pair :
         boundary_count)
      {
        std::cout << pair.first << "(" << pair.second << " times) ";
      }
    std::cout << std::endl;
  }
  std::ofstream out(filename);
  GridOut       grid_out;
  grid_out.write_vtu(triangulation, out);
  std::cout << " written to " << filename << std::endl << std::endl;
}


void spindle_grid()
{
 Triangulation<2> tri1; Triangulation<2> tri2; 
 const double inner_radius=0.5, outer_radius=0.1,half_length=0.4;

 GridGenerator::truncated_cone(tri1,inner_radius,outer_radius,half_length);

 GridTools::transform(
  [](const Point<2> &in){
    return Point<2>(in[0]+0.40,in[1]);
  }, tri1);

 GridGenerator::truncated_cone(tri2,outer_radius,inner_radius,half_length);
 
 GridTools::transform(
 [](const Point<2> &in){
 return Point<2>(in[0]-0.40,in[1]);
 },tri2);


 Triangulation<2> triangulation;
 GridGenerator::merge_triangulations(tri1,tri2,triangulation);
 triangulation.refine_global(4);

  std::ofstream out("spindle.svg");
  GridOut       grid_out;
  grid_out.write_svg(triangulation, out);
  std::cout << "Grid written to spindle.svg" << std::endl;

  print_mesh_info(tri1, "tri1.vtu");
  print_mesh_info(tri2, "tri2.vtu");
  print_mesh_info(triangulation,"spindle.vtu");

  }

int main()
{
spindle_grid();
}

