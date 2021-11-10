#include <iostream>
using namespace std;

#include "nstdxml/nstdxml.h"

// header file 'csg_wikipedia.h' has been created on linux as follows
// $ xxd -i csg_wikipedia.xcsg > csg_wikipedia.h
#include "test_data/csg_wikipedia.h"
#include <sstream>

static size_t num_nodes = 0;
static size_t num_attr = 0;

void print_node(const nstdxml::xml_node& node, int level);

int main(int argc, char **argv)
{
   std::string xml_data = (const char*)(csg_wikipedia_xcsg);

   // parse the data
   nstdxml::xml_tree tree;
   nstdxml::xml_node root = tree.read_xml_string(xml_data);

   // print the data and count the number of nodes
   print_node(root,0);

   cout << endl << "----" << endl;
   cout << "The xml data has " << num_nodes << " nodes and " <<  num_attr << " attributes" << endl;

   cout << endl << "---- writing to output stream" << endl;

   std::ostringstream out;
   tree.write_xml(out);

   cout << out.str();
   cout << "----" << endl;



   return 0;
}


void print_node(const nstdxml::xml_node& node, int level)
{
   num_nodes++;

   // some nice indents
   for(int i=0;i<level;i++) cout << "  ";

   // node tag
   cout << node.tag();

   // print node attributes
   auto attr = node.get_attribs();
   num_attr += attr.size();
   for(auto p : attr) cout << ' ' << p.first << '=' << p.second;
   cout << endl;

   // traverse child nodes
   for(nstdxml::xml_node child : node) {
      print_node(child,level+1);
   }
}
