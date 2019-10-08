/* vim: set sw=4 sts=4 et foldmethod=syntax : */

#ifndef GLASGOW_SUBGRAPH_SOLVER_SOLVER_FORMATS_VF_HH
#define GLASGOW_SUBGRAPH_SOLVER_SOLVER_FORMATS_VF_HH 1

#include "formats/input_graph.hh"
#include "formats/graph_file_error.hh"

#include <iosfwd>
#include <string>

/**
 * Read a VF format file into an InputGraph.
 *
 * \throw GraphFileError
 */
auto read_vf(std::ifstream && infile, const std::string & filename) -> InputGraph;

/**
 * Read a Labelled VF format file into an InputGraph.
 *
 * \throw GraphFileError
 */
auto read_labelled_vf(std::ifstream && infile, const std::string & filename) -> InputGraph;

#endif /* GLASGOW_SUBGRAPH_SOLVER_SOLVER_FORMATS_VF_HH */
