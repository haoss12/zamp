#include <iostream>
#include "Interp4Pause.hh"

using std::cout;
using std::endl;

extern "C"
{
  AbstractInterp4Command *CreateCmd(void);
  const char *GetCmdName() { return "Pause"; }
}

/*!
 * \brief
 *
 *
 */
AbstractInterp4Command *CreateCmd(void)
{
  return Interp4Pause::CreateCmd();
}

/*!
 *
 */
Interp4Pause::Interp4Pause() : _Time_ms(0)
{
}

/*!
 *
 */
void Interp4Pause::PrintCmd() const
{
  cout << GetCmdName() << " " << _Time_ms << endl;
}

/*!
 *
 */
const char *Interp4Pause::GetCmdName() const
{
  return ::GetCmdName();
}

/*!
 *
 */
bool Interp4Pause::ExecCmd(AbstractScene &rScn)
{
  rScn.LockAccess();
  cout << " Pause" << endl;
  usleep(_Time_ms * 1000);
  rScn.MarkChange();
  rScn.UnlockAccess();
  return true;
}

/*!
 *
 */
bool Interp4Pause::ReadParams(std::istream &Strm_CmdsList)
{
  double t;
  Strm_CmdsList >> t;

  _Time_ms = t;
  return true;
}

/*!
 *
 */
AbstractInterp4Command *Interp4Pause::CreateCmd()
{
  return new Interp4Pause();
}

/*!
 *
 */
void Interp4Pause::PrintSyntax() const
{
  cout << "   Pause  CzasPauzy[ms]" << endl;
}
