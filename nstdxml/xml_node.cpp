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

#include "xml_node.h"
#include "xmlParser/xmlParser.h"
#include <sstream>

namespace nstdxml {

   template <typename T>
   static T lexical_cast(XMLCSTR str)
   {
       T var;
       std::istringstream iss;
       iss.str(str);
       iss >> var;
       // deal with any error bits that may have been set on the stream
       return var;
   }

   template <typename T>
   static std::string to_string_with_precision(const T a_value, const int n = 16)
   {
       std::ostringstream out;
       out.precision(n);
       out << a_value;
       return out.str();
   }

   xml_node::xml_node()
   {}

   xml_node::~xml_node()
   {}

   std::string xml_node::tag() const
   {
      return m_xnode.getName();
   }

   std::vector<xml_attrib> xml_node::get_attribs() const
   {
      std::vector<xml_attrib> v;
      int nat = m_xnode.nAttribute();
      for(int i=0;i<nat;i++) {
         XMLAttribute a = m_xnode.getAttribute(i);
         v.push_back(std::make_pair<std::string,std::string>(a.lpszName,a.lpszValue));
      }
      return v;
   }

   bool xml_node::get_child(const std::string& tag, xml_node& child) const
   {
      XMLNode ch = m_xnode.getChildNode(tag.c_str(),0);
      if(ch.isEmpty())return false;

      child = ch;
      return true;
   }

   bool xml_node::has_attribute(const std::string& name) const
   {
      return (m_xnode.isAttributeSet(name.c_str()) == TRUE);
   }

   std::string xml_node::get_attribute(const std::string& name, const std::string& default_value) const
   {
      if(XMLCSTR ptr_str = m_xnode.getAttribute(name.c_str(),0)) {
         return ptr_str;
      }
      return default_value;
   }

   size_t  xml_node::get_attribute(const std::string& name, size_t default_value) const
   {
      if(XMLCSTR ptr_str = m_xnode.getAttribute(name.c_str(),0)) {
         return lexical_cast<size_t>(ptr_str);
      }
      return default_value;
   }

   int  xml_node::get_attribute(const std::string& name, int default_value) const
   {
      if(XMLCSTR ptr_str = m_xnode.getAttribute(name.c_str(),0)) {
         return lexical_cast<int>(ptr_str);
      }
      return default_value;
   }

   double xml_node::get_attribute(const std::string& name, double default_value) const
   {
      if(XMLCSTR ptr_str = m_xnode.getAttribute(name.c_str(),0)) {
         return lexical_cast<double>(ptr_str);
      }
      return default_value;
   }

   bool xml_node::is_valid() const
   {
      return (!m_xnode.isEmpty());
   }

   bool xml_node::add_attribute(const std::string& name, const std::string& value)
   {
      if(XMLAttribute* attr = m_xnode.addAttribute(name.c_str(),value.c_str())) {
         return true;
      }
      return false;
   }

   bool xml_node::add_attribute(const std::string& name, size_t value)
   {
      return add_attribute(name,to_string_with_precision(value));
   }

   bool xml_node::add_attribute(const std::string& name, int value)
   {
      return add_attribute(name,std::to_string(value));
   }

   bool xml_node::add_attribute(const std::string& name, double value)
   {
      return add_attribute(name,to_string_with_precision(value));
   }

   xml_node xml_node::add_child(const std::string& tag)
   {
      return m_xnode.addChild(tag.c_str());
   }

   bool xml_node::put_value(const std::string& value)
   {
      return m_xnode.updateText(value.c_str());
   }

   bool xml_node::put_value(size_t value)
   {
      return put_value(std::to_string(value));
   }

   bool xml_node::put_value(int value)
   {
      return put_value(std::to_string(value));
   }

   bool xml_node::put_value(double value)
   {
      return put_value(to_string_with_precision(value));
   }

   std::string xml_node::get_value(const std::string& default_value) const
   {
      if(XMLCSTR t = m_xnode.getText()){
         return t;
      }
      return default_value;
   }

   size_t xml_node::get_value(size_t default_value) const
   {
      if(XMLCSTR t = m_xnode.getText()){
         return lexical_cast<size_t>(t);
      }
      return default_value;
   }

   int xml_node::get_value(int default_value) const
   {
      if(XMLCSTR t = m_xnode.getText()){
         return lexical_cast<int>(t);
      }
      return default_value;
   }

   double xml_node::get_value(double default_value) const
   {
      if(XMLCSTR t = m_xnode.getText()){
         return lexical_cast<double>(t);
      }
      return default_value;
   }

   bool xml_node::has_value() const
   {
      if(XMLCSTR t = m_xnode.getText()){
         return true;
      }
      return false;
   }

} // namespace nstdxml
