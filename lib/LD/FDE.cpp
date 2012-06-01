//===- FDE.cpp ------------------------------------------------------------===//
//
//                     The MCLinker Project
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
#include <mcld/LD/EhFrame.h>
#include <mcld/LD/FDE.h>

using namespace mcld;

//==========================
// FDE

FDE::FDE(const MCRegionFragment& pFrag, const CIE& pCIE)
  : m_Fragment(pFrag), m_CIE(pCIE) {
}
FDE::~FDE()
{
}

uint64_t FDE::length() const
{
  return 0;
}

const CIE& FDE::getCIE() const
{
  return m_CIE;
}

uint64_t FDE::PCBegin() const
{
  return 0;
}

uint64_t FDE::PCRange() const
{
  return 0;
}

