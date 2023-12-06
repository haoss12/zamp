#include <iostream>
#include "Interp4Rotate.hh"

using std::cerr;
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
bool Interp4Rotate::ExecCmd(AbstractScene &rScn)
{
  auto obj = rScn.FindMobileObj(_ObjName);
  if (obj == nullptr)
  {
    cerr << "Brak obiektu o podanej nazwie!" << endl;
    return false;
  }

  double roll = obj->GetAng_Roll_deg();
  double pitch = obj->GetAng_Pitch_deg();
  double yaw = obj->GetAng_Yaw_deg();

  double time_of_move = _Angle_deg / _Speed_degS;
  int steps = 100;
  int time_of_step = static_cast<int>(time_of_move / steps);
  double step = _Angle_deg / steps;

  for (int i = 0; i < steps; ++i)
  {
    rScn.LockAccess();
    switch (_Axis)
    {
    case 'X':
      roll += step;
      obj->SetAng_Roll_deg(roll);
      break;
    case 'Y':
      pitch += step;
      obj->SetAng_Pitch_deg(pitch);
      break;
    case 'Z':
      yaw += step;
      obj->SetAng_Yaw_deg(yaw);
      break;

    default:
      cerr << "Podano złą oś!" << endl;
      rScn.MarkChange();
      rScn.UnlockAccess();
      return false;
      break;
    }
    rScn.MarkChange();
    rScn.UnlockAccess();
    usleep(time_of_step * 1000);
  }

  return true;
}

/*!
 *
 */
bool Interp4Rotate::ReadParams(std::istream &Strm_CmdsList)
{
  std::string obj;
  char temp, axis;
  double s, ang;
  Strm_CmdsList >> obj;
  Strm_CmdsList >> temp; // to skip 'O'
  Strm_CmdsList >> axis;
  Strm_CmdsList >> s;
  Strm_CmdsList >> ang;

  _ObjName = obj;
  _Axis = axis;
  _Speed_degS = s;
  _Angle_deg = ang;
  return true;
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
