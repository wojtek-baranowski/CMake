/* Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
   file Copyright.txt or https://cmake.org/licensing for details.  */
#include "cmLinkLibrariesCommand.h"

// cmLinkLibrariesCommand
bool cmLinkLibrariesCommand::InitialPass(std::vector<std::string> const& args,
                                         cmExecutionStatus&)
{
  if (args.empty()) {
    return true;
  }
  // add libraries, nothe that there is an optional prefix
  // of debug and optimized than can be used
  for (std::vector<std::string>::const_iterator i = args.begin();
       i != args.end(); ++i) {
    if (*i == "debug") {
      ++i;
      if (i == args.end()) {
        this->SetError("The \"debug\" argument must be followed by "
                       "a library");
        return false;
      }
      this->Makefile->AppendProperty("LINK_LIBRARIES", "debug");
    } else if (*i == "optimized") {
      ++i;
      if (i == args.end()) {
        this->SetError("The \"optimized\" argument must be followed by "
                       "a library");
        return false;
      }
      this->Makefile->AppendProperty("LINK_LIBRARIES", "optimized");
    }
    this->Makefile->AppendProperty("LINK_LIBRARIES", i->c_str());
  }

  return true;
}

void cmLinkLibrariesCommand::PopulateTarget(cmTarget& target, cmMakefile* mf)
{
  // for these targets do not add anything
  switch (target.GetType()) {
    case cmState::UTILITY:
    case cmState::GLOBAL_TARGET:
    case cmState::INTERFACE_LIBRARY:
      return;
    default:;
  }
  if (const char* linkDirsProp = mf->GetProperty("LINK_DIRECTORIES")) {
    std::vector<std::string> linkDirs;
    cmSystemTools::ExpandListArgument(linkDirsProp, linkDirs);

    for (std::vector<std::string>::iterator j = linkDirs.begin();
         j != linkDirs.end(); ++j) {
      std::string newdir = *j;
      // remove trailing slashes
      if (*j->rbegin() == '/') {
        newdir = j->substr(0, j->size() - 1);
      }
      target.AddLinkDirectory(*j);
    }
  }

  if (const char* linkLibsProp = mf->GetProperty("LINK_LIBRARIES")) {
    std::vector<std::string> linkLibs;
    cmSystemTools::ExpandListArgument(linkLibsProp, linkLibs);

    for (std::vector<std::string>::iterator j = linkLibs.begin();
         j != linkLibs.end(); ++j) {
      std::string libraryName = *j;
      cmTargetLinkLibraryType libType = GENERAL_LibraryType;
      if (libraryName == "optimized")
      {
        libType = OPTIMIZED_LibraryType;
        ++j;
        libraryName = *j;
      } else
      if (libraryName == "debug")
      {
        libType = DEBUG_LibraryType;
        ++j;
        libraryName = *j;
      }
      // This is equivalent to the target_link_libraries plain signature.
      target.AddLinkLibrary(*mf, libraryName, libType);
      target.AppendProperty(
        "INTERFACE_LINK_LIBRARIES",
        target.GetDebugGeneratorExpressions(libraryName, libType).c_str());
    }
  }
}
