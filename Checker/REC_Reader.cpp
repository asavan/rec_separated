#include "resource.h"

#include "Reader.h"
#include <Windows.h>
#include <fstream>

namespace {
    std::string fname; //�������� ��� � Stats
    static int curr = 0;
    Reader reader;
    Stats stats(&reader);
    HWND hwQuestion, hwAnswer, hwInfo, hwFalse, hwTrue, hwUnchecked, hwNext, hwOnly, hwAuto, hwStatStr, hwStatBn;//, hwTime;

    void LoadState() {
        SetWindowText(hwAnswer, reader.get_answer(curr).c_str());
        SetWindowText(hwInfo, stats.getHeaderString2(curr).c_str());
        int temp_mark = reader.get_mark(curr);
        SendMessage(hwTrue, (UINT)BM_SETCHECK, temp_mark == Reader::true_mark, 0);
        SendMessage(hwFalse, (UINT)BM_SETCHECK, temp_mark == Reader::false_mark, 0);
        SendMessage(hwUnchecked, (UINT)BM_SETCHECK, temp_mark == Reader::unset, 0);
    }
    void EnableWindows()
    {
        EnableWindow(hwUnchecked, true);
        EnableWindow(hwTrue, true);
        ShowWindow(hwFalse, SW_SHOW);
        ShowWindow(hwStatBn, SW_SHOW);
        SetWindowText(hwTrue, "���������");
    }
    void DisableWindows()
    {
        EnableWindow(hwUnchecked, false);
        EnableWindow(hwTrue, false);
        ShowWindow(hwFalse, SW_HIDE);
        ShowWindow(hwStatBn, SW_HIDE);
        SetWindowText(hwTrue, "���������");
    }

    void LoadStatistic(HWND hwAnswerWindow, HWND hwTrueWindow, HWND hwUncheckedWindow, HWND hwNextWindow)
    {
        curr = reader.size();
        SetWindowText(hwInfo, "����������. ");
        bool all_check = stats.isAllCheked();
        std::string str = stats.getStatsString();
        SetWindowText(hwAnswerWindow, str.c_str());

        SendMessage(hwTrueWindow, (UINT)BM_SETCHECK, all_check, 0);
        SendMessage(hwUncheckedWindow, (UINT)BM_SETCHECK, !all_check, 0);

        DisableWindows();
        SetFocus(hwNextWindow);
    }

    void LoadStatisticState(HWND hwStatWindow)
    {
        stats.set_changed(true);
        std::string str = stats.getHeaderString();
        SetWindowText(hwStatWindow, str.c_str());
    }

    void SaveDialog(/*HWND hw*/)
    {
        stats.saveToFile(fname);
        //EndDialog(hw, 0);
    }

    int ErrorEndDialog(HWND hw)
    {
        MessageBox(hw, "Bad exm file", NULL, MB_OK | MB_ICONSTOP);
        EndDialog(hw, -1);
        return -1;
    }

    void ExitDialog(HWND hw)
    {
        if (stats.is_changed())
        {
            if (reader.is_first())
            {
                SaveDialog(/*hw*/);
            }
            else
                switch (MessageBox(hw, "Save on exit?", "Save this file?", MB_YESNOCANCEL))
                {
                case IDNO:
                    break;
                case IDYES:
                    SaveDialog(/*hw*/);
                    break;
                case IDCANCEL:
                    return;
                }
        }
        EndDialog(hw, 0);
    }

    void Go(int step)
    {
        int size, big_size = reader.size() + 1;
        if (SendMessage(hwOnly, (UINT)BM_GETCHECK, 0, 0))
        {
            size = big_size;
        }
        else
        {
            size = 1;
        }
        for (int i = 0; i < size; ++i)
        {
            curr = (curr + step + big_size) % big_size;
            if (curr + 1 == big_size)
            {
                LoadStatistic(hwAnswer, hwTrue, hwUnchecked, hwNext);
                return;
            }
            else if (curr == 0 || curr + 2 == big_size)
            {
                EnableWindows();
            }
            if (reader.get_mark(curr) == Reader::unset) break;
        }
        LoadState();
    }

    void Set_Mark(int mark, HWND hwStatWindow, HWND hwAutoWindow)
    {
        reader.set_mark(curr, mark);
        LoadStatisticState(hwStatWindow);
        if (mark) {
            if (SendMessage(hwAutoWindow, (UINT)BM_GETCHECK, 0, 0)) {
                Go(1);
            }
        }
    }

    INT_PTR CALLBACK DlgProc(HWND hw, UINT msg, WPARAM wp, LPARAM /*lp*/) {
        switch (msg) {
        case WM_CLOSE:
            ExitDialog(hw);
            break;
        case WM_INITDIALOG:
        {
            std::ifstream  f(fname.c_str(), std::ios::binary);
            if (!f.is_open())
            {
                return ErrorEndDialog(hw);
            }
            if (reader.LoadFromFile(f) < 1)
            {
                return ErrorEndDialog(hw);
            }
            stats.make_static();
            hwAnswer = GetDlgItem(hw, ED_ANSWER);
            hwInfo = GetDlgItem(hw, ST_INFO);
            hwFalse = GetDlgItem(hw, BN_FALSE);
            hwTrue = GetDlgItem(hw, BN_TRUE);
            hwUnchecked = GetDlgItem(hw, BN_UNCHECKED);
            hwAuto = GetDlgItem(hw, CH_AUTO);
            hwNext = GetDlgItem(hw, BN_NEXT);
            hwOnly = GetDlgItem(hw, CH_ONLY);
            hwStatStr = GetDlgItem(hw, ST_STAT);
            hwStatBn = GetDlgItem(hw, BN_STAT);

            LoadStatistic(hwAnswer, hwTrue, hwUnchecked, hwNext);
            LoadStatisticState(hwStatStr);
            stats.set_changed(false);
            SendMessage(hwOnly, (UINT)BM_SETCHECK, !stats.isAllCheked(), 0);
            SendMessage(hwAuto, (UINT)BM_SETCHECK, true, 0);
        }
        break;
        case WM_COMMAND:
            switch (LOWORD(wp))
            {

            case BN_EXIT:
                ExitDialog(hw);
                break;
            case BN_NEXT:
            case BN_PREV:
                Go(LOWORD(wp) - 1005);// from resurse file constant
                break;
            case BN_UNCHECKED:
            case BN_TRUE:
            case BN_FALSE:
                Set_Mark(LOWORD(wp) - 1021, hwStatStr, hwAuto);// from resurse file constant
                break;
            case BN_STAT:
                LoadStatistic(hwAnswer, hwTrue, hwUnchecked, hwNext);
                break;
            }
            break;
        }
        return 0;
    }

    std::string addOneRow(const std::string& str1, const std::string str2)
    {
        std::string str;
        str += str1;
        str.push_back(0);
        str += "*.";
        str += str2;
        str.push_back(0);
        return str;
    }

    std::string MakeFilter()
    {
        std::string mass[] = { "����� ���������", "���������", "����������", "���������" };
        std::string mass2[] = { "?re", "fre", "sre", "ere" };
        std::string str;
        for (int i = 0; i < sizeof(mass) / sizeof(mass[0]); ++i)
        {
            str += addOneRow(mass[i], mass2[i]);
        }

        str += addOneRow("��� �����", "*");
        return str;
    }

    BOOL GetFName(HINSTANCE hinst) {
        OPENFILENAME ofn;
        const int max_len = 2 * 1024;
        char fname_local[max_len + 1];
        fname_local[0] = 0;
        setlocale(LC_ALL, ".ACP"); //vc9 bag
        ZeroMemory(&ofn, sizeof(ofn));
        ofn.hInstance = hinst;
        ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_ALLOWMULTISELECT;
        ofn.lpstrFile = fname_local;
        ofn.nMaxFile = max_len;
        std::string filter = MakeFilter();
        ofn.lpstrFilter = filter.c_str();
        ofn.lStructSize = sizeof(ofn);
        ofn.lpstrInitialDir = NULL;
        BOOL res = GetOpenFileName(&ofn);
        ::fname = fname_local;
        return res;
    }
}

int APIENTRY WinMain(__in HINSTANCE hInstance, __in_opt HINSTANCE /*hPrevInstance*/, __in LPSTR /*lpCmdLine*/, __in int /*nShowCmd*/)
{
    if (GetFName(hInstance))
        DialogBox(hInstance, MAKEINTRESOURCE(IDD_READER), HWND_DESKTOP, DlgProc);
    return 0;
}
