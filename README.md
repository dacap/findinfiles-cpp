# findinfiles

> Copyright (C) 2014 David Capello
>
> This file is released under the terms of the MIT license.
> Read [LICENSE.txt](LICENSE.txt) for more information.

This little utility searches a piece of regular expression in all
files of the current directory and subdirectories. The idea is to
solve the most common case of a typical `find | grep` command.  It's
not a replacement. It's not fully configurable. It's not what you
want. It's what I need and it may be useful to you.

Usage:

    findinfiles [-1iv] [-.ext] PATTERN [PATTERN2...]

    -1      Do not recurse directories
    -i      Ignore case
    -v      Verbose mode
    -.ext   Search only in files with the given extension `.ext`

Example:

    findinfiles -.cpp -.h class

Finds all lines with `class` word in `.cpp` and `.h` files of the
current directory and subdirectories.

## Notes

At this moment it only compiles in VC2012. It uses some things from
C++11 like std::regex, and other stuff from the TR2 filesystem
library.