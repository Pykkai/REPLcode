// Copyright (C) 2026 Brad Shapcott brad@shapcott.com brash@pyyk.ai

// - the @doxygen tag indicates where doxygen documentation should be provided

// - comments should be point form, they are faster to write and faster
//   and easier to read; strip verbiage!

// - system includes go here in alpahbetical order
#include <std.h>

// - project includes go here in alphabetical order
#include "style.h"

// - pyyka is the project's namespace
namespace pyyka
{
  class Style
  {
    // - every private, protected and public section follows the pattern:
    // - member variables in alphabetical order
    // - constructors section
    // - destructors section
    // - methods in alphabetical order
  private:
    // @doxygen
    string my_private_member_variable;
  protected:
    // @doxygen
    string my_protected_member_variable;
  public:
    // @doxygen
    string my_public_member_variable;
    // @doxygen
    Style(string &foo);
    // @doxygen
    ~Styles();
    // @doxygen
    string my_public_method(string &s);
    // @doxygen
    static void my_static_method();
  };
}

// - mark the end of file to guard against accidental truncation
// EOF ************************************************************************
