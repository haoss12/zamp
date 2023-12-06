#include <iostream>
#include "Interp4Move.hh"

using std::cerr;
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
bool Interp4Move::ExecCmd(AbstractScene &rScn)
{
  auto obj = rScn.FindMobileObj(_ObjName);
  if (obj == nullptr)
  {
    cerr << "Brak obiektu o podanej nazwie!" << endl;
    return false;
  }

  Vector3D position = obj->GetPosition_m();
  double yaw = obj->GetAng_Yaw_deg();

  double time_of_move = _Distance_m / _Speed_mmS;
  int steps = 100;
  int time_of_step = static_cast<int>(time_of_move / steps);
  double step = _Distance_m / steps;

  double dx = step * cos(yaw * M_PI / 180);
  double dy = step * sin(yaw * M_PI / 180);

  for (int i = 0; i < steps; ++i)
  {
    rScn.LockAccess();
    position[0] += dx;
    position[1] += dy;

    obj->SetPosition_m(position);
    rScn.MarkChange();
    rScn.UnlockAccess();
    usleep(time_of_step * 1000);
  }
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
