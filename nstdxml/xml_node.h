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

#ifndef XML_NODE_H
#define XML_NODE_H

#include "nstdxml_config.h"

#include <string>
#include <vector>
#include "xmlParser/xmlParser.h"

namespace nstdxml {

   // xml attribute key/value pair
   using xml_attrib  = std::pair<std::string,std::string>;

   class NSTDXML_PUBLIC xml_node {
      friend class xml_tree;
   public:

      // child node iterator
      class iterator {
         friend class xml_node;
      public:
         inline iterator(const XMLNode* parent, int i) : m_parent(parent),m_i(i) {}
         inline void operator++()                   { ++m_i; }
         inline void operator++(int)                { m_i++; }
         inline bool operator==(const iterator& i2) { return ((m_parent==i2.m_parent) && (m_i==i2.m_i)); }
         inline bool operator!=(const iterator& i2) { return !operator==(i2); }
         inline XMLNode operator*()                 { return m_parent->getChildNode(m_i); }
      private:
         const XMLNode* m_parent; // parent node
         int            m_i;      // parent's child index
      };

      xml_node();
      virtual ~xml_node();

      // return true if this is a valid node
      bool is_valid() const;

      // return the tag of the node.
      std::string tag() const;

      // check if named attribute exists
      bool has_attribute(const std::string& name) const;

      // return attribute of this node, return default value if not found
      std::string get_attribute(const std::string& name, const std::string& default_value) const;
      size_t      get_attribute(const std::string& name, size_t default_value) const;
      int         get_attribute(const std::string& name, int default_value) const;
      double      get_attribute(const std::string& name, double default_value) const;

      // return all attributes as vector of string pairs
      std::vector<xml_attrib> get_attribs() const;

      // return the (first) named child if such exists
      bool get_child(const std::string& tag, xml_node& child) const;

      // traverse all the immediate children of the node
      inline iterator begin() const { return iterator(&m_xnode,0); }
      inline iterator end() const   { return iterator(&m_xnode,m_xnode.nChildNode()); }

      // add attribute to this node
      bool add_attribute(const std::string& name, const std::string& value);
      bool add_attribute(const std::string& name, size_t value);
      bool add_attribute(const std::string& name, int value);
      bool add_attribute(const std::string& name, double value);

      // add a child node to this node, return a child reference
      xml_node add_child(const std::string& tag);

      // store a value directly in this node <tag> value </tag>
      bool put_value(const std::string& value);
      bool put_value(size_t value);
      bool put_value(int value);
      bool put_value(double value);

      // return a value directly in this node <tag> value </tag> , return default value if not found
      std::string get_value(const std::string& default_value) const;
      size_t      get_value(size_t default_value) const;
      int         get_value(int default_value) const;
      double      get_value(double default_value) const;

      // check if a value exists on this node
      bool has_value() const;

      // convert iterator to node
      inline xml_node(iterator it): m_xnode(*it) {}
      inline xml_node(const XMLNode& xnode) : m_xnode(xnode) {}


      // compatibility interface
      inline std::string get_property(const std::string& name, const std::string& default_value) const { return get_attribute(name,default_value); }
      inline size_t      get_property(const std::string& name, size_t default_value) const             { return get_attribute(name,default_value); }
      inline int         get_property(const std::string& name, int default_value) const                { return get_attribute(name,default_value); }
      inline double      get_property(const std::string& name, double default_value) const             { return get_attribute(name,default_value); }

      inline bool add_property(const std::string& name, const std::string& value)                      { return add_attribute(name,value); }
      inline bool add_property(const std::string& name, size_t value)                                  { return add_attribute(name,value); }
      inline bool add_property(const std::string& name, int value)                                     { return add_attribute(name,value); }
      inline bool add_property(const std::string& name, double value)                                  { return add_attribute(name,value); }

   private:
      XMLNode m_xnode;
   };

} // namespace nstdxml

#endif // XML_NODE_H
