#include <iostream>
#include "Interp4Move.hh"

using std::cout;
using std::endl;

extern "C"
{
  AbstractInterp4Command *CreateCmd(void);
  const char *GetCmdName() { return "Move"; }
}

/*!
 * \brief
 *
 *
 */
AbstractInterp4Command *CreateCmd(void)
{
  return Interp4Move::CreateCmd();
}

/*!
 *
 */
Interp4Move::Interp4Move() : _Speed_mmS(0), _Distance_m(0)
{
}

/*!
 *
 */
void Interp4Move::PrintCmd() const
{
  cout << GetCmdName() << " " << _Speed_mmS << " " << _Distance_m << endl;
}

/*!
 *
 */
const char *Interp4Move::GetCmdName() const
{
  return ::GetCmdName();
}

/*!
 *
 */
bool Interp4Move::ExecCmd(AbstractScene &rScn,
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
bool Interp4Move::ReadParams(std::istream &Strm_CmdsList)
{
  std::string obj;
  double s, d;
  Strm_CmdsList >> obj;
  Strm_CmdsList >> s;
  Strm_CmdsList >> d;

  _ObjName = obj;
  _Speed_mmS = s;
  _Distance_m = d;
  return true;
}

/*!
 *
 */
AbstractInterp4Command *Interp4Move::CreateCmd()
{
  return new Interp4Move();
}

/*!
 *
 */
void Interp4Move::PrintSyntax() const
{
  cout << "   Move  NazwaObiektu  Szybkosc[m/s]  DlugoscDrogi[m]" << endl;
}
