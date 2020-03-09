#include "Examination.h"

#include "resource.h"

#include <Windows.h>
#include <WindowsX.h>
#include <strstream>
#include <fstream>

Examination ex;
size_t curr = 0;
HWND hwQuestion, hwAnswer, hwNumber, hwTime;
const int max_username = 1024;
char username[max_username];
std::string REClama()
{
    std::string str;
    str += "�������� �����������-������������� ��������";
    str += "\r\n";
    str += "E-mail: asavan@mail.ru";
    return str;
}

std::string REC_name(const Examination& ex)
{
    return ex.get_set().get_name();
}

void LoadState(const Examination& ex)
{
    Edit_SetText(hwQuestion, ex.get_question(curr).c_str());
    Edit_SetText(hwAnswer, ex.get_answer(curr).c_str());
    char tmp[128];
    sprintf_s(tmp, "������ ����� %zu �� %zu.", curr + 1, ex.size());
    Edit_SetText(hwNumber, tmp);
}

void SaveState(Examination& ex)
{
    int len = Edit_GetTextLength(hwAnswer);
    char* str = new char[len + 1];
    Edit_GetText(hwAnswer, str, len + 1);
    ex.set_answer(curr, str);
    delete[] str;
}

void CALLBACK TimerProc(HWND, UINT, UINT_PTR, DWORD)
{
    Static_SetText(hwTime, ex.get_time_differense().c_str());
}

INT_PTR CALLBACK DlgProcLogin(HWND hw, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg)
    {
    case WM_INITDIALOG:
        //SetItemHeight();
        Edit_SetText(GetDlgItem(hw, ST_ABOUT), REC_name(ex).c_str());
        SetWindowText(hw, REC_name(ex).c_str());
        SetFocus(GetDlgItem(hw, ED_USERNAME));
        break;
    case WM_CLOSE:
        EndDialog(hw, -2);
        break;
    case WM_COMMAND:
        switch (LOWORD(wp))
        {
        case BN_EXIT:
            EndDialog(hw, -1);
            break;
        case BN_LOGIN:
            GetDlgItemText(hw, ED_USERNAME, username, max_username);
            if (username[0] == '\0')
            {
                MessageBox(hw, "������� ��������� ���", NULL, MB_ICONEXCLAMATION | MB_TASKMODAL);// ������
                break;
            }
            EndDialog(hw, 0);
            break;
        }
    }
    return 0;
}

INT_PTR CALLBACK DlgProc(HWND hw, UINT msg, WPARAM wp, LPARAM lp)
{
    std::ofstream ofs;
    switch (msg)
    {
    case WM_INITDIALOG:
        hwQuestion = GetDlgItem(hw, ED_QUESTION);
        hwAnswer = GetDlgItem(hw, ED_ANSWER);
        hwNumber = GetDlgItem(hw, ST_NUMBER);
        hwTime = GetDlgItem(hw, ST_TIME);
        LoadState(ex);
        SetWindowText(hw, REC_name(ex).c_str());
        SetFocus(hwAnswer);
        SetTimer(hw, 0, 50, TimerProc);
        ex.startExamen();
        TimerProc(0, 0, 0, 0);
        break;
    case WM_COMMAND:
        switch (LOWORD(wp))
        {

        case BN_EXIT:
            SaveState(ex);
            setlocale(LC_ALL, ".ACP"); //vs9

            ofs.open((std::string(username) + "." + ex.get_set().get_ext()).c_str(), std::ios::binary);
            if (ofs.is_open())
            {
                ex.SaveToFile(ofs, username);
                ofs.close();
            }
            EndDialog(hw, 0);
            break;
        case BN_NEXT:
            SaveState(ex);
            curr++;
            if (curr == ex.size()) {
                curr = 0;
            }
            LoadState(ex);
            SetFocus(hwAnswer);
            break;
        case BN_PREV:
            SaveState(ex);
            if (curr == 0) {
                curr = ex.size() - 1;
            }
            else {
                curr--;
            }
            LoadState(ex);
            break;
        }
        break;
    }
    return 0;
}

static std::strstream getFileFromResourse() {
    HRSRC hRes = FindResource(NULL, "DataBase", RT_RCDATA);
    if (!hRes)
    {
        throw std::runtime_error("No database");
    }
    HGLOBAL hGlob = LoadResource(NULL, hRes);
    if (!hGlob)
    {
        //��������� ������
        throw std::runtime_error("No database");
    }
    //�, �������, ��������� - �������� ��������� �� ������ �������
    char* lpbArray = (char*)LockResource(hGlob);
    if (!lpbArray)
    {
        //��������� ������
        throw std::runtime_error("No database");
    }
    DWORD dwFileSize = SizeofResource(NULL, hRes);
    if (!dwFileSize)
    {
        //��������� ������
        throw std::runtime_error("No database");
    }
    //std::ifstream ifs("db.rec",std::ios_base::binary);
    std::strstream ifs = std::strstream(lpbArray, dwFileSize, std::ios_base::binary | std::ios_base::in);
    return ifs;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
    try {
        // auto ifs = getFileFromResourse();
        auto ifs = std::ifstream("db.rec", std::ios_base::binary);
        if (ifs)
        {
            bool res = ex.LoadFromFile(ifs);
            if (res)
            {
                ex.MakeAnswerOrder();
                if (0 == DialogBox(hInstance, MAKEINTRESOURCE(IDD_LOGIN), HWND_DESKTOP, DlgProcLogin))
                {

                    DialogBox(hInstance, MAKEINTRESOURCE(IDD_MAIN), HWND_DESKTOP, DlgProc);
                }
            }
            else {
                MessageBox(HWND_DESKTOP, "���� � ��������� ����������", NULL, MB_OK | MB_ICONSTOP);
            }
        }
        else {
            MessageBox(HWND_DESKTOP, "�� ������� ���� � ���������", NULL, MB_OK | MB_ICONSTOP);
        }
    }
    catch (const std::exception & ex)
    {
        MessageBox(HWND_DESKTOP, ex.what(), NULL, MB_OK | MB_ICONSTOP);
        // delete ifs;
    }
    return 0;
}
