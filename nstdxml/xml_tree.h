// BeginLicense:
// Part of: nstdxml - non standard xml library
// Copyright (C) 2021 Carsten Arnholm
// All rights reserved
//
// This file may be used under the terms of the GNU General Public
// License version 3  as published by the Free Software Foundation
// and appearing in the file LICENSE included in the packaging of this file.
//
// This file is provided "AS IS" with NO WARRANTY OF ANY KIND,
// INCLUDING THE WARRANTIES OF DESIGN, MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE. ALL COPIES OF THIS FILE MUST INCLUDE THIS LICENSE.
// EndLicense:

// This library uses "XMLParser library" by Frank Vanden Berghen for implementation
// ref. https://applied-mathematics.net/tools/xmlParser.html

#ifndef XML_TREE_H
#define XML_TREE_H

#include "nstdxml_config.h"

#include <string>
#include "xml_node.h"

namespace nstdxml {

   class NSTDXML_PUBLIC xml_tree {
   public:
      xml_tree();
      virtual ~xml_tree();

      // read xml data from file and return root node,
      // use is_valid() to check result
      xml_node read_xml_file(const std::string& path);

      // return the root node of the tree,
      // use is_valid() to check result
      xml_node get_root();

      // create the root node of the tree, return false if it already exists
      // use get_root to access it later
      bool create_root(const std::string& root_name);

      // write xml data to file
      bool write_xml_file(const std::string& path) const;

   protected:

      // read xml data from file
      bool read_xml(const std::string& path);

   private:
      xml_node m_tree_node;  // points to <xml> tag
      xml_node m_root;       // first child under tree_node
   };

} // namespace nstdxml

#endif // XML_TREE_H
