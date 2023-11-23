#ifndef CUBOID_HH
#define CUBOID_HH

#include <string>

#include "AbstractMobileObj.hh"
#define STATES_NUMBER 8
class Cuboid : public AbstractMobileObj
{
    std::string _name;

    Vector3D _position;
    Vector3D _scale;
    Vector3D _shift;
    double _roll_deg;
    double _pitch_deg;
    double _yaw_deg;

    int _color[3];

  public:
    Cuboid()
    {
    }

    const std::string &GetName() const override
    {
        return _name;
    }

    const Vector3D &GetPosition_m() const override
    {
        return _position;
    }
    const Vector3D &GetScale() const override
    {
        return _scale;
    }
    const Vector3D &GetShift() const override
    {
        return _shift;
    }
    double GetAng_Roll_deg() const override
    {
        return _roll_deg;
    }
    double GetAng_Pitch_deg() const override
    {
        return _pitch_deg;
    }
    double GetAng_Yaw_deg() const override
    {
        return _yaw_deg;
    }

    int GetColor_R() const override
    {
        return _color[0];
    }
    int GetColor_G() const override
    {
        return _color[1];
    }
    int GetColor_B() const override
    {
        return _color[2];
    }

    void SetName(const char *sName) override
    {
        _name = sName;
    }

    void SetPosition_m(const Vector3D &rPos) override
    {
        _position = rPos;
    }
    void SetScale(const Vector3D &rScale) override
    {
        _scale = rScale;
    }
    void SetShift(const Vector3D &rShift) override
    {
        _shift = rShift;
    }
    void SetAng_Roll_deg(double Ang_Roll_deg) override
    {
        _roll_deg = Ang_Roll_deg;
    }
    void SetAng_Pitch_deg(double Ang_Pitch_deg) override
    {
        _pitch_deg = Ang_Pitch_deg;
    }
    void SetAng_Yaw_deg(double Ang_Yaw_deg) override
    {
        _yaw_deg = Ang_Yaw_deg;
    }
    void SetColor_R(const int &rColor_R) override
    {
        _color[0] = rColor_R;
    }
    void SetColor_G(const int &rColor_G) override
    {
        _color[1] = rColor_G;
    }
    void SetColor_B(const int &rColor_B) override
    {
        _color[2] = rColor_B;
    }   
};

#endif