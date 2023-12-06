#include <iostream>
#include "Interp4Set.hh"

using std::cerr;
using std::cout;
using std::endl;

extern "C"
{
  AbstractInterp4Command *CreateCmd(void);
  const char *GetCmdName() { return "Set"; }
}

/*!
 * \brief
 *
 *
 */
AbstractInterp4Command *CreateCmd(void)
{
  return Interp4Set::CreateCmd();
}

/*!
 *
 */
Interp4Set::Interp4Set()
{
}

/*!
 *
 */
void Interp4Set::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << _ObjName << " " << _X << " " << _Y << " " << _Z << " " << _OX << " " << _Y << " " << _OZ << endl;
}

/*!
 *
 */
const char *Interp4Set::GetCmdName() const
{
  return ::GetCmdName();
}

/*!
 *
 */
bool Interp4Set::ExecCmd(AbstractScene &rScn)
{
  auto obj = rScn.FindMobileObj(_ObjName);
  if (obj == nullptr)
  {
    cerr << "Brak obiektu o podanej nazwie!" << endl;
    return false;
  }

  Vector3D vec;
  vec[0] = _X;
  vec[1] = _Y;
  vec[2] = _Z;

  rScn.LockAccess();

  obj->SetPosition_m(vec);
  obj->SetAng_Roll_deg(_OX);
  obj->SetAng_Pitch_deg(_OY);
  obj->SetAng_Yaw_deg(_OZ);

  rScn.MarkChange();
  rScn.UnlockAccess();

  return true;
}

/*!
 *
 */
bool Interp4Set::ReadParams(std::istream &Strm_CmdsList)
{
  Strm_CmdsList >> _ObjName >> _X >> _Y >> _Z >> _OX >> _OY >> _OZ;
  return true;
}

/*!
 *
 */
AbstractInterp4Command *Interp4Set::CreateCmd()
{
  return new Interp4Set();
}

/*!
 *
 */
void Interp4Set::PrintSyntax() const
{
  cout << "   Set  NazwaObiektu  X  Y  Z  OX  OY  OZ" << endl;
}
