/* Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
   file Copyright.txt or https://cmake.org/licensing for details.  */

#include "cmNinjaLinkLineComputer.h"
#include "cmGlobalNinjaGenerator.h"

cmNinjaLinkLineComputer::cmNinjaLinkLineComputer(cmState::Directory stateDir,
                                                 std::string const& prefix)
  : cmLinkLineComputer(stateDir)
  , NinjaPrefix(prefix)
{
}

std::string cmNinjaLinkLineComputer::ConvertToLinkReference(
  std::string const& lib) const
{
  return cmGlobalNinjaGenerator::ConvertToNinjaPath(lib, this->StateDir,
                                                    this->NinjaPrefix);
}
