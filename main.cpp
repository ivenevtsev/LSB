#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <bitset>

using namespace std;
string *mas, *mas1;

int main() {
    string file;
    int choise;
    cout << "Enter the file" << endl;
    cin >> file;
    cout << "1. Encode 2. Decode" << endl;
    cin >> choise;
    ifstream f;
    f.open(file, ios_base::in|ios_base::binary);
    if (!f.is_open()) {
        cout << "Error" << endl;
        return 2;
    }
    string s;
    int k = 0;

    while (!f.eof()) {
        getline(f, s);
        k++;
    }
    f.clear();
    f.seekg(0, ios_base::beg);
    mas = new string[k];
    mas1 = new string[k];
    int i = 0;
    while (!f.eof()) {
        getline(f, s);
        mas[i] = s;
        mas1[i] = s;
        i++;
    }
    f.close();
    int r = 2, p = 19;
    if (choise == 1) {
        setlocale(LC_ALL, "");
        wchar_t a[] = L"Стеганография форевер";
        bitset<16> b2(wcslen(a));
        cout<<wcslen(a)<<endl;
        for (i = 15; i >= 0; i--) {
            bitset<8> b(mas[r][p]);
            if (b2[i] == 0) {
                if (b[0] == 1)
                    if (mas[r][p] == '\v') {
                        mas[r][p] += 1;
                    }else{
                        mas[r][p] -= 1;
                    }
            } else {
                if (b[0] == 0)
                    mas[r][p] += 1;
            }
            p++;
            if (p >= mas[r].length()) {
                p = 0;
                r++;
            }
        }
        for (int j = 0; j < wcslen(a); j++) {
            bitset<16> b1(a[j]);
            for (i = 15; i >= 0; i--) {
                bitset<8> b(mas[r][p]);
                if (b1[i] == 0) {
                    if (b[0] == 1)
                        if (mas[r][p] == '\v') {
                            mas[r][p] += 1;
                        }else{
                            mas[r][p] -= 1;
                        }
                } else {
                    if (b[0] == 0)
                        mas[r][p] += 1;
                }
                p++;
                if (p >= mas[r].length()) {
                    p = 0;
                    r++;
                }
            }
        }
        ofstream fout;
        fout.open("C:\\Users\\Gamer\\Desktop\\test.bmp",ios_base::out | ios_base::binary);
        for (i = 0; i < k; i++)
            fout<<mas[i]<<endl;
        fout.close();
    }
    r = 2, p = 19;
    if (choise == 2) {
        setlocale(LC_ALL, "");
        bitset<16> b(0);
        for (i = 15; i >= 0; i--) {
            bitset<8> b1(mas[r][p]);
            b[i] = b1[0];
            p++;
            if (p >= mas[r].length()) {
                p = 0;
                r++;
            }
        }
        unsigned long len;
        len = b.to_ulong();
        wchar_t y;
        for (unsigned long j = 0; j < len; j++) {
            for (i = 0; i < 16; i++)
                b[i] = false;
            for (i = 15; i >= 0; i--) {
                bitset<8> b1(mas[r][p]);
                b[i] = b1[0];
                p++;
                if (p >= mas[r].length()) {
                    p = 0;
                    r++;
                }
            }
            y = (int) b.to_ulong();
            printf("%lc", y);
        }
        cout << endl;
    }
    double summ=0.0;
    r =2, p=19;
    for (i=r; i<k ; i++) {
        for (int j = p; j < mas[i].length(); j++)
            summ += pow(abs((int) mas[i][j] - (int)mas1[i][j]), 2);
        p = 0;
    }
    summ /= (400*600*3);
    double psnr;
    psnr = 10*log10(255*255/summ);
    cout<<psnr<<endl;
    return 0;
}
