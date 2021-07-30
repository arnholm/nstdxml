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

#include "xml_tree.h"
#include "xml_node.h"
#include "xmlParser/xmlParser.h"

namespace nstdxml {

   xml_tree::xml_tree()
   {}

   xml_tree::~xml_tree()
   {}

   xml_node xml_tree::read_xml_file(const std::string& path)
   {
      xml_node root;
      if(xml_tree::read_xml(path)) {
         root = get_root();
      }
      return root;
   }

   bool xml_tree::read_xml(const std::string& path)
   {
      XMLResults res;
      m_tree_node = XMLNode::parseFile(path.c_str(),0,&res);
      return (res.error == eXMLErrorNone);
   }

   bool xml_tree::write_xml_file(const std::string& path) const
   {
      XMLError err = m_tree_node.m_xnode.writeToFile(path.c_str());
      return (err == eXMLErrorNone);
   }

   xml_node xml_tree::get_root()
   {
      if(m_root.is_valid()) return m_root;
      if(!m_tree_node.is_valid()) return xml_node();

      std::string name = m_tree_node.m_xnode.getName();
      if(name == "xml") {
         int nch= m_tree_node.m_xnode.nChildNode();
         if(nch > 0) {
            m_root = m_tree_node.m_xnode.getChildNode(0);
         }
      }

      return m_root;
   }

   bool xml_tree::create_root(const std::string& root_name)
   {
      if(m_root.is_valid()) return false;
      m_tree_node = XMLNode::createXMLTopNode(root_name.c_str());
      m_root = m_tree_node;
      return true;
   }

} // namespace nstdxml
