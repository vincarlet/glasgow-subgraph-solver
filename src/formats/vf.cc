/* vim: set sw=4 sts=4 et foldmethod=syntax : */

#include "formats/vf.hh"
#include "formats/input_graph.hh"

#include <fstream>
#include <map>

using std::ifstream;
using std::map;
using std::pair;
using std::string;
using std::to_string;

namespace
{
    auto read_word(ifstream & infile) -> int
    {
        int x;
        infile >> x;
        return x;
    }
}

auto read_vf(ifstream && infile, const string & filename) -> InputGraph
{
    InputGraph result{ 0, false, false };

    //Reading number of nodes
    result.resize(read_word(infile));
    if (! infile)
        throw GraphFileError{ filename, "error reading size", true };

    //Reading nodes
    for (int r = 0 ; r < result.size() ; ++r) {
        int node_id = read_word(infile);
        if (! infile)
            throw GraphFileError{ filename, "error reading edges count", true };
    }

    for (int r = 0 ; r < result.size() ; ++r) {
        int edge_count = read_word(infile);
        if (! infile)
            throw GraphFileError{ filename, "error reading edges count", true };
        
        for (int c = 0 ; c < edge_count ; ++c) {
            int r = read_word(infile);
            int e = read_word(infile);

            if (r < 0 || r >= result.size())
                throw GraphFileError{ filename, "edge index out of bounds on source node", true };

            if (e < 0 || e >= result.size())
                throw GraphFileError{ filename, "edge index out of bounds on destination node", true };

            result.add_edge(r, e);
        }
    }

    string rest;
    if (infile >> rest)
        throw GraphFileError{ filename, "EOF not reached, next text is \"" + rest + "\"", true };
    if (! infile.eof())
        throw GraphFileError{ filename, "EOF not reached", true };

    return result;
}

auto read_labelled_vf(ifstream && infile, const string & filename) -> InputGraph
{
    InputGraph result{ 0, false, false };

    //Reading number of nodes
    result.resize(read_word(infile));
    if (! infile)
        throw GraphFileError{ filename, "error reading size", true };

    //Reading nodes
    for (int r = 0 ; r < result.size() ; ++r) {
        int node_id = read_word(infile);
        if (! infile)
            throw GraphFileError{ filename, "error reading node id", true };

        int node_label = read_word(infile);
        if (! infile)
            throw GraphFileError{ filename, "error reading node label", true };
        
        result.set_vertex_label(node_id, to_string(node_label));
    }

    for (int r = 0 ; r < result.size() ; ++r) {
        int edge_count = read_word(infile);
        if (! infile)
            throw GraphFileError{ filename, "error reading edges count", true };
        
        for (int c = 0 ; c < edge_count ; ++c) {
            int r = read_word(infile);
            int e = read_word(infile);

            if (r < 0 || r >= result.size())
                throw GraphFileError{ filename, "edge index out of bounds on source node", true };

            if (e < 0 || e >= result.size())
                throw GraphFileError{ filename, "edge index out of bounds on destination node", true };

            result.add_edge(r, e);
        }
    }

    string rest;
    if (infile >> rest)
        throw GraphFileError{ filename, "EOF not reached, next text is \"" + rest + "\"", true };
    if (! infile.eof())
        throw GraphFileError{ filename, "EOF not reached", true };

    return result;

    /*InputGraph result{ 0, true, true };

    result.resize(read_word(infile));
    if (! infile)
        throw GraphFileError{ filename, "error reading size" };

    for (int r = 0 ; r < result.size() ; ++r) {
        int l = read_word(infile);
        if (! infile)
            throw GraphFileError{ filename, "error reading label" };

        int c_end = read_word(infile);
        if (! infile)
            throw GraphFileError{ filename, "error reading edges count" };

        result.set_vertex_label(r, to_string(l));

        for (int c = 0 ; c < c_end ; ++c) {
            int e = read_word(infile);

            if (e < 0 || e >= result.size())
                throw GraphFileError{ filename, "edge index out of bounds" };

            int l = read_word(infile);
            if (l < 0)
                throw GraphFileError{ filename, "edge label invalid" };

            result.add_directed_edge(r, e, to_string(l));
        }
    }

    string rest;
    if (infile >> rest)
        throw GraphFileError{ filename, "EOF not reached, next text is \"" + rest + "\"" };
    if (! infile.eof())
        throw GraphFileError{ filename, "EOF not reached" };

    return result;*/

}

