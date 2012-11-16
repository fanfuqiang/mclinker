//===- DiagnosticEngine.cpp -----------------------------------------------===//
//
//                     The MCLinker Project
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
#include <mcld/LD/DiagnosticEngine.h>
#include <mcld/LD/DiagnosticPrinter.h>
#include <mcld/LD/DiagnosticLineInfo.h>
#include <mcld/LD/MsgHandler.h>
#include <mcld/LinkerConfig.h>

#include <cassert>

using namespace mcld;

//===----------------------------------------------------------------------===//
// DiagnosticEngine
//===----------------------------------------------------------------------===//
DiagnosticEngine::DiagnosticEngine()
  : m_pConfig(NULL), m_pLineInfo(NULL), m_pPrinter(NULL),
    m_pInfoMap(NULL), m_OwnPrinter(false) {
}

DiagnosticEngine::~DiagnosticEngine()
{
  if (m_OwnPrinter && m_pPrinter != NULL)
    delete m_pPrinter;

  delete m_pInfoMap;
}

void DiagnosticEngine::reset(const LinkerConfig& pConfig)
{
  m_pConfig = &pConfig;
  delete m_pInfoMap;
  m_pInfoMap = new DiagnosticInfos(*m_pConfig);
  m_State.reset();
}

void DiagnosticEngine::setLineInfo(DiagnosticLineInfo& pLineInfo)
{
  m_pLineInfo = &pLineInfo;
}

void DiagnosticEngine::setPrinter(DiagnosticPrinter& pPrinter,
                                  bool pShouldOwnPrinter)
{
  if (m_OwnPrinter && NULL != m_pPrinter)
    delete m_pPrinter;
  m_pPrinter = &pPrinter;
  m_OwnPrinter = pShouldOwnPrinter;
}

// emit - process current diagnostic.
bool DiagnosticEngine::emit()
{
  assert(NULL != m_pInfoMap);
  bool emitted = m_pInfoMap->process(*this);
  m_State.reset();
  return emitted;
}

MsgHandler
DiagnosticEngine::report(uint16_t pID, DiagnosticEngine::Severity pSeverity)
{
  m_State.ID = pID;
  m_State.severity = pSeverity;

  MsgHandler result(*this);
  return result;
}

