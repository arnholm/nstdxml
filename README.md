# nstdxml
non-standard xml C++ library

non-standard xml C++ library is independent of external dependencies, it is designed to be nice and simple. If you need something really advanced, this is not for you.

##Quick introduction

A basic example:

```
#include <iostream>
#include "nstdxml/nstdxml.h"

void main() 
{
   nstdxml::xml_tree tree;
   nstdxml::xml_node root = tree.read_xml_file("somefile.xml");

   // traverse child nodes directly under root
   for(nstdxml::xml_node child : node) {
      std::cout << child.tag() << std::endl;
   }
}
```

For more details, see the **nstdxml_test** console application.

## installation

You generate build files using [Premake5](https://premake.github.io/). Install Premake5 and generate build files


### Building for Linux:

```
      $ premake5 --file=NSTDXML_premake5.lua gmake2

        Building configurations...
        Running action 'gmake2'...
        Generated build/gmake2/Makefile...
        Generated build/gmake2/nstdxml/Makefile...
        Generated build/gmake2/nstdxml_test/Makefile...
        Done (33ms).
```

The library can then be built:

```
      $ cd build/gmake2
      $ make config=release

        ==== Building nstdxml (release) ====
        Creating obj/release
        xmlParser.cpp
        xml_node.cpp
        xml_tree.cpp
        Creating bin/release
        Linking nstdxml
        Running postbuild commands
        mkdir -p ../release
        cp -f bin/release/* ../release
        ==== Building nstdxml_test (release) ====
        Creating obj/release
        main.cpp
        Creating bin/release
        Linking nstdxml_test
        Running postbuild commands
        mkdir -p ../release
        cp -f bin/release/* ../release
```
The final step is to run the test application


```
      $ cd release/
      $ ./nstdxml_test 
```

The following output is produced
```
xcsg version=1.0
  metadata
    software name=angelcad version=v1.4-00
    model name=csg_wikipedia created=2020-10-11T15:50:48
  difference3d
    intersection3d
      cube size=45 center=true
      sphere r=30
    union3d
      union3d
        cylinder h=60 r=17 center=true
        cylinder h=60 r=17 center=true
          tmatrix
            trow c0=1 c1=0 c2=0 c3=0
            trow c0=0 c1=6.123233995736766e-17 c2=-1 c3=0
            trow c0=0 c1=1 c2=6.123233995736766e-17 c3=0
            trow c0=0 c1=0 c2=0 c3=1
      cylinder h=60 r=17 center=true
        tmatrix
          trow c0=6.123233995736766e-17 c1=0 c2=1 c3=0
          trow c0=0 c1=1 c2=0 c3=0
          trow c0=-1 c1=0 c2=6.123233995736766e-17 c3=0
          trow c0=0 c1=0 c2=0 c3=1

----
The xml data has 23 nodes and 49 attributes
```

### Building for Windows & Visual Studio 2019

Download [Premake5](https://premake.github.io/) for Windows amd generate build files:

```
      C:\somedir> premake5 --file=NSTDXML_premake5.lua vs2019

        Building configurations...
        Running action 'vs2019'...
        Generated build/vs2019/NSTDXML.sln...
        Generated build/vs2019/nstdxml/nstdxml.vcxproj...
        Generated build/vs2019/nstdxml/nstdxml.vcxproj.filters...
        Generated build/vs2019/nstdxml_test/nstdxml_test.vcxproj...
        Generated build/vs2019/nstdxml_test/nstdxml_test.vcxproj.filters...
        Done (103ms).
```

Open the generated NSTDXML.sln file and build using Visual Studio 2019. The rest is exactly as described for Linux.

