%nodefaultctor CCAchievement;
%nodefaultdtor CCAchievement;

/// 
/// \brief
/// Cloud Connection Achievement - Represents the data for an online Achievement
///
class CCAchievement : public VTypedObject
{
public:
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
};


