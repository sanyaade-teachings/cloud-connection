#include "CloudConnectionPluginPCH.hpp"
#include "CCAchievement.hpp"

CCAchievement::CCAchievement()
{
  m_valid = false;
  m_currentSteps = -1;
  m_totalSteps = -1;
  m_lastMod = -1;
  m_state = -1;
  m_type = -1;
}

CCAchievement::~CCAchievement()
{
}

bool CCAchievement::Valid() const
{
  return m_valid;
}

const char* CCAchievement::Id() const
{
  return m_id.AsChar();
}

const char* CCAchievement::Name() const
{
  return m_name.AsChar();
}

const char* CCAchievement::Description() const
{
  return m_description.AsChar();
}

unsigned int CCAchievement::Type() const
{
  return m_type;
}

unsigned int CCAchievement::State() const
{
  return m_state;
}

unsigned int CCAchievement::CurrentSteps() const
{
  return m_currentSteps;
}

unsigned int CCAchievement::TotalSteps() const
{
  return m_totalSteps;
}

ULONG64 CCAchievement::LastModified() const
{
  return m_lastMod;
}


void CCAchievement::SetValid( bool valid )
{
  m_valid = valid;
}

void CCAchievement::SetId( const char* id )
{
  m_id = id;
}

void CCAchievement::SetName( const char* name )
{
  m_name = name;
}

void CCAchievement::SetDescription( const char* description )
{
  m_description = description;
}

void CCAchievement::SetType( unsigned int type )
{
  m_type = type;
}

void CCAchievement::SetState( unsigned int state )
{
  m_state = state;
}

void CCAchievement::SetCurrentSteps( unsigned int currentSteps )
{
  m_currentSteps = currentSteps;
}

void CCAchievement::SetTotalSteps( unsigned int totalSteps )
{
  m_totalSteps = totalSteps;
}

void CCAchievement::SetLastModified( ULONG64 time )
{
  m_lastMod = time;
}