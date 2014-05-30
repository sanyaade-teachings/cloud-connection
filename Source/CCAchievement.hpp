#ifndef _CCACHIEVEMENT_HPP_
#define _CCACHIEVEMENT_HPP_

#include "VisionBaseIncludes.h"
#include "CloudConnectionTypes.h"

/// 
/// \brief
/// Cloud Connection Achievement - Represents the data for an online Achievement
///
class CCAchievement : public IVisCallbackDataObject_cl
{
public:
  CCAchievement();
  virtual ~CCAchievement();

  ///
  /// \note
  /// Returns true when the returned achievement is populated with data and is
  /// accompanied by a successful response status; false for an
  /// unpopulated user-created achievement or for a populated one accompanied by
  /// an unsuccessful response status.
  ///It must be true for the getter functions on this achievement (id, Name, Description, etc.) to be usable.
  virtual bool Valid() const;

  ///
  /// \note
  /// Returns the unique string  Use it to refer to an achievement in your game client.
  /// It can only be called when Valid() returns true.
  virtual const char* Id() const;

  ///
  /// \note
  /// Returns the short name of the achievement. Up to 100 characters.
  /// It can only be called when Valid() returns true.
  virtual const char* Name() const;

  ///
  /// \note
  /// Returns a concise description of your achievement. Usually tells player how
  /// to earn the achievement. Up to 500 characters.
  /// It can only be called when Valid() returns true.
  virtual const char* Description() const;

  ///
  /// \note
  /// Returns the achievement type: incremental or standard.
  /// It can only be called when Valid() returns true
  virtual unsigned int Type() const;

  ///
  /// \note
  /// Returns the achievement state: hidden, revealed, or unlocked.
  /// it can only be called when Valid() returns true.
  virtual unsigned int State() const;

  ///
  /// \note
  /// Returns the number of steps the player has taken toward unlocking an
  /// incremental achievement.
  /// It can only be called when Achievement::Valid() returns true.
  virtual unsigned int CurrentSteps() const;

  ///
  /// \note
  /// Returns the number of steps required, in total, for the player to 
  /// unlock a given incremental achievement.
  /// It can only be called when Achievement::Valid() returns true.
  virtual unsigned int TotalSteps() const;

  ///
  /// \note
  /// Returns time at which the entry was last modified (expressed as
  /// milliseconds since the Unix epoch).
  /// It can only be called when Achievement::Valid() returns true.
  virtual ULONG64 LastModified() const;
    
  ///
  /// \note
  /// true when the returned achievement is populated with data and is
  /// accompanied by a successful response status; false for an
  /// unpopulated user-created achievement or for a populated one accompanied by
  /// an unsuccessful response status.
  /// /param valid true if achievement is valid, false if not
  virtual void SetValid( bool valid );

  ///
  /// \brief Sets the unique string  Use it to refer to an achievement in your game client.
  /// \param id the id of the achievement
  virtual void SetId( const char* id );

  ///
  /// \brief Sets the short name of the achievement. Up to 100 characters.
  /// \param name the short name of the achievement
  virtual void SetName( const char* name );

  ///
  /// \brief Returns a concise description of your achievement. Usually tells player how to earn the achievement. Up to 500 characters.
  /// \param description a concise description of the achievement.
  virtual void SetDescription( const char* description );

  ///
  /// \note Sets the achievement type: incremental or standard.
  /// \param type the achievement type: incremental or standard (see CCAchievementType)
  virtual void SetType( unsigned int type );

  ///
  /// \note Sets the achievement state: hidden, revealed, or unlocked.
  /// \param state the achievement state: hidden, revealed, or unlocked (see CCAchievementState)
  virtual void SetState( unsigned int state );

  ///
  /// \brief Sets the number of steps the player has taken toward unlocking an incremental achievement.
  /// /param currentSteps the number of steps the player has taken toward unlocking an incremental achievement.
  virtual void SetCurrentSteps( unsigned int currentSteps );

  ///
  /// \brief Sets the total number of steps required to complete the achievement
  /// /param totalSteps the number of steps required, in total, for the player to unlock a given incremental achievement.
  virtual void SetTotalSteps( unsigned int totalSteps );

  ///
  /// \brief Sets the time the Achievement was last modified
  /// /param time time at which the entry was last modified (expressed as milliseconds since the Unix epoch).
  virtual void SetLastModified( ULONG64 time );

protected:
private:
  bool m_valid;                 ///< is this a valid achievement
  VString m_id;                 ///< the unique string used to refer to an achievement in the game client
  VString m_name;               ///< the short name of the achievement
  VString m_description;        ///< concise description of your achievement.
  unsigned int m_type;          ///< the achievement type: incremental or standard
  unsigned int m_state;         ///< achievement state: hidden, revealed, or unlocked.
  unsigned int m_currentSteps;  ///< the number of steps the player has taken toward unlocking an incremental achievement.
  unsigned int m_totalSteps;    ///< he number of steps required, in total, for the player to unlock a given incremental achievement.
  ULONG64 m_lastMod;            ///< time at which the entry was last modified (expressed as milliseconds since the Unix epoch).
};

#endif //end inclusion guard