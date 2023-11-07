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
bool Interp4Pause::ExecCmd(AbstractScene &rScn,
                           const char *sMobObjName,
                           AbstractComChannel &rComChann)
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  return true;
}

/*!
 *
 */
bool Interp4Pause::ReadParams(std::istream &Strm_CmdsList)
{
  std::string name;
  double t;
  Strm_CmdsList >> name;
  Strm_CmdsList >> t;

  if (Strm_CmdsList.good())
  {
    _Time_ms = t;
    return true;
  }

  return false;
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
