#include <iostream>
#include "Interp4Rotate.hh"

using std::cout;
using std::endl;

extern "C"
{
  AbstractInterp4Command *CreateCmd(void);
  const char *GetCmdName() { return "Rotate"; }
}

/*!
 * \brief
 *
 *
 */
AbstractInterp4Command *CreateCmd(void)
{
  return Interp4Rotate::CreateCmd();
}

/*!
 *
 */
Interp4Rotate::Interp4Rotate() : _Axis('Z'), _Speed_degS(0), _Angle_deg(0)
{
}

/*!
 *
 */
void Interp4Rotate::PrintCmd() const
{
  cout << GetCmdName() << " " << _Axis << " " << _Speed_degS << " " << _Angle_deg << endl;
}

/*!
 *
 */
const char *Interp4Rotate::GetCmdName() const
{
  return ::GetCmdName();
}

/*!
 *
 */
bool Interp4Rotate::ExecCmd(AbstractScene &rScn,
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
bool Interp4Rotate::ReadParams(std::istream &Strm_CmdsList)
{
  std::string name;
  char temp, axis;
  double s, ang;
  Strm_CmdsList >> name;
  Strm_CmdsList >> temp; // to skip 'O'
  Strm_CmdsList >> axis;
  Strm_CmdsList >> s;
  Strm_CmdsList >> ang;

  if (Strm_CmdsList.good())
  {
    _Axis = axis;
    _Speed_degS = s;
    _Angle_deg = ang;
    return true;
  }

  return false;
}

/*!
 *
 */
AbstractInterp4Command *Interp4Rotate::CreateCmd()
{
  return new Interp4Rotate();
}

/*!
 *
 */
void Interp4Rotate::PrintSyntax() const
{
  cout << "   Rotate  NazwaObiektu  NazwaOsi  SzybkoscKatowa[o/s]  KatObrotu[o]" << endl;
}
