//===- ObjectReader.h -----------------------------------------------------===//
//
//                     The MCLinker Project
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
#ifndef MCLD_OBJECT_READER_H
#define MCLD_OBJECT_READER_H
#ifdef ENABLE_UNITTEST
#include <gtest.h>
#endif
#include "mcld/LD/LDReader.h"
#include <llvm/Support/system_error.h>

namespace mcld
{

class Input;

/** \class ObjectReader
 *  \brief ObjectReader provides an common interface for different object
 *  formats.
 */
class ObjectReader : public LDReader
{
protected:
  ObjectReader()
  { }

public:
  virtual ~ObjectReader() { }

  virtual llvm::error_code readObject(Input& pFile) = 0;

  virtual bool readSymbols(Input& pFile) = 0;

  virtual bool readSections(Input& pFile) = 0;

  /// readRelocations - read relocation sections
  ///
  /// This function should be called after symbol resolution.
  virtual bool readRelocations(Input& pFile) = 0;

};

} // namespace of mcld

#endif

