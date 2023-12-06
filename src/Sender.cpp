#include "Sender.hh"

#include <sstream>

Sender::~Sender()
{
    close(_Socket);
}

int Sender::Send(const char *sMesg)
{
    ssize_t IlWyslanych;
    ssize_t IlDoWyslania = (ssize_t)strlen(sMesg);

    while ((IlWyslanych = write(_Socket, sMesg, IlDoWyslania)) > 0)
    {
        IlDoWyslania -= IlWyslanych;
        sMesg += IlWyslanych;
    }
    if (IlWyslanych < 0)
    {
        std::cerr << "*** Blad przeslania napisu." << std::endl;
    }
    return 0;
}

void Sender::Watching_and_Sending()
{
    Send("Clear\n");
    _pScn->LockAccess();

    // Add all elements to the scene
    for (auto &iterator : _pScn->GetWholeMap())
    {
        Send(GetInstruction(*iterator.second, CommandType::Add).c_str());
    }
    _pScn->UnlockAccess();
    while (ShouldCountinueLooping())
    {
        if (!_pScn->IsChanged())
        {
            usleep(1200);
            continue;
        }

        for (auto &iterator : _pScn->GetWholeMap())
        {
            _pScn->LockAccess();
            std::string str = GetInstruction(*iterator.second, CommandType::Update);
            Send(str.c_str());
            _pScn->UnlockAccess();
        }

        _pScn->CancelChange();
    }
}

bool Sender::OpenConnection()
{
    struct sockaddr_in DaneAdSerw;

    bzero((char *)&DaneAdSerw, sizeof(DaneAdSerw));

    DaneAdSerw.sin_family = AF_INET;
    DaneAdSerw.sin_addr.s_addr = inet_addr("127.0.0.1");
    DaneAdSerw.sin_port = htons(PORT);

    _Socket = socket(AF_INET, SOCK_STREAM, 0);

    if (_Socket < 0)
    {
        std::cerr << "*** Blad otwarcia gniazda." << std::endl;
        return false;
    }

    if (connect(_Socket, (struct sockaddr *)&DaneAdSerw, sizeof(DaneAdSerw)) < 0)
    {
        std::cerr << "*** Brak mozliwosci polaczenia do portu: " << PORT << std::endl;
        return false;
    }
    return true;
}

std::string Sender::GetInstruction(Cuboid &obj, CommandType com) const
{
    std::stringstream tmp;
    if (com == CommandType::Add)
    {
        tmp << "AddObj";
    }
    else if (com == CommandType::Update)
    {
        tmp << "UpdateObj";
    }
    Vector3D pos = obj.GetPosition_m();
    Vector3D sca = obj.GetScale();
    Vector3D tra = obj.GetPosition_m();
    tmp << " Name=" << obj.GetName();
    tmp << " Shift=(" << pos[0] << ", " << pos[1] << ", " << pos[2] << ")";
    tmp << " Scale=(" << sca[0] << ", " << sca[1] << ", " << sca[2] << ")";
    tmp << " Trans_m=(" << tra[0] << ", " << tra[1] << ", " << tra[2] << ")";
    tmp << " RGB=(" << obj.GetColor_R() << ", " << obj.GetColor_G() << ", " << obj.GetColor_B() << ")";
    tmp << " RotXYZ_deg=(" << obj.GetAng_Roll_deg() << ", " << obj.GetAng_Pitch_deg() << ", " << obj.GetAng_Yaw_deg() << ")\n";
    return tmp.str();
}
