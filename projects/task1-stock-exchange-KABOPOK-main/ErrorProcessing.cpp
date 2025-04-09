#include "Algoritms.hpp"

void timeInpit(const char* time) {
    for (short i = 0; time[i] != ','; ++i) {
        std::cout << time[i];
    }
}
void timeInpitFormat(const char* time) {
    for (short i = 0; time[i] != 0; ++i) {
        std::cout << time[i];
    }
}
void dateInpitFormat(const char* date) {
    for (short i = 0; date[i] != 0; ++i) {
        std::cout << date[i];
    }
}


int monthCount(int first, int last) {
    const int _31 = 2678400;
    const int _30 = 2592000;
    int _28{};
    if ((last % 4 == 0 && (last % 100 != 0 || last % 400 == 0))) {
        _28 = 2505600;
    }
    else {
        _28 = 2419200;
    }
    switch (first) {
    case 0:
        return 0;
    case 1:
        return _31;
    case 2:
        return _31 + _28;
    case 3:
        return 2 * _31 + _28;
    case 4:
        return 2 * _31 + _28 + _30;
    case 5:
        return 3 * _31 + _28 + _30;
    case 6:
        return 3 * _31 + _28 + 2 * _30;
    case 7:
        return 4 * _31 + _28 + 2 * _30;
    case 8:
        return 5 * _31 + _28 + 2 * _30;
    case 9:
        return 5 * _31 + _28 + 3 * _30;
    case 10:
        return 6 * _31 + _28 + 3 * _30;
    case 11:
        return 6 * _31 + _28 + 4 * _30;
    case 12:
        return 7 * _31 + _28 + 4 * _30;
    }
    return 0;
}

long long checkTime(const char* first, const char* last)
{
    int da = 0;
    int ye = 0;
    int mo = 0;
    //correct
    int cda = 0;
    int cye = 0;
    int cmo = 0;
    int b = 0;
    int c = 0;
    int e = 0;
    //endcorrect
    int d = 0;
    int m = 0;
    int y = 0;
    int a = 0;
    int dY = 0;
    int JD = 0;
    //values
    int ho = 0;
    int mi = 0;
    int se = 0;
    // for days
    int counter = 0;
    int point = 0;
    int i = 0;
    while (point == 0) {
        if (((first[i] < '0' || first[i] > '9') && first[i] != '.') || counter > 2) {
            std::cout << "Wrong date format: ";
            dateInpitFormat(first);
            std::cout << std::endl;
            return -1;
        }
        first[i] == '.' ? point = 1 : ++counter;
        ++i;
    }

    if (counter == 0) {
        std::cout << "Wrong FirstDate format: ";
        dateInpitFormat(first);
        std::cout << std::endl;
        return -1;
    }

    if (counter == 1) {
        da = (first[0] - '0');
    }
    if (counter == 2) {
        da = (first[0] - '0') * 10 + first[1] - '0';
    }
    if (da > 32 || da < 1) {
        std::cout << "Day value is invalid: " << da << std::endl;
        return -1;
    }

    //for months
    counter = 0;
    point = 0;
    while (point == 0) {
        if (((first[i] < '0' || first[i] > '9') && first[i] != '.') || counter > 2) {
            std::cout << "Wrong date format: ";
            dateInpitFormat(first);
            std::cout << std::endl;
            return -1;
        }
        first[i] == '.' ? point = 1 : ++counter;
        ++i;
    }
    if (counter == 0 || counter > 2) {
        std::cout << "Wrong date format: ";
        dateInpitFormat(first);
        std::cout << std::endl;
        return -1;
    }
    if (counter == 1) {
        mo = (first[i - 2] - '0');
    }
    if (counter == 2) {
        mo = (first[i - 3] - '0') * 10 + first[i - 2] - '0';
    }
    if (mo > 12 || mo < 1) {
        std::cout << "Month value is invalid: " << mo << std::endl;
        return -1;
    }
    //for years
    int degree = 0;
    counter = 0;
    while (true) {
        if (first[i] < '0' || first[i] > '9') {
            if (first[i] == '\0') { break; }
            std::cout << "Wrong date format: ";
            dateInpitFormat(first);
            std::cout << std::endl;
            return -1;
        }
        ++i;
        ++counter;
    }
    if (counter == 0) {
        std::cout << "Wrong date format: ";
        dateInpitFormat(first);
        std::cout << std::endl;
        return -1;
    }
    for (int begin = 0; begin < counter; ++begin) {
        ye += int((first[i - 1] - '0') * pow(10, degree));
        ++degree;
        --i;
    }
    if (ye > 9999 || ye < 2000) {
        std::cout << "Year value is invalid: " << ye << std::endl;
        return -1;
    }
    a = (14 - mo) / 12;
    y = ye + 4800 - a;
    m = mo + 12 * a - 3;
    JD = da + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045;

    // to back
    a = JD + 32044;
    b = (4 * a + 3) / 146097;
    c = a - 146097 * b / 4;
    d = (4 * c + 3) / 1461;
    e = c - (1461 * d) / 4;
    m = (5 * e + 2) / 153;
    cda = e - (153 * m + 2) / 5 + 1;
    cmo = m + 3 - 12 * (m / 10);
    cye = 100 * b + d - 4800 + m / 10;
    //std::cout << cda << " " << cmo << " " << cye << " ";

    //real date?
    if (cda != da || cmo != mo || cye != ye) {
        std::cout << "Day value is invalid: " << da << std::endl;
        return -1;
    }

    //work with time set


    //for hours
    counter = 0;
    point = 0;
    i = 0;
    while (point == 0) {
        if (((last[i] < '0' || last[i] > '9') && last[i] != ':') || counter > 2) {
            std::cout << "Wrong time format: ";
            timeInpitFormat(last);
            std::cout << std::endl;
            return -1;
        }
        last[i] == ':' ? point = 1 : ++counter;
        ++i;
    }

    if (counter == 0) {
        std::cout << "Wrong time format: ";
        timeInpitFormat(last);
        std::cout << std::endl;
        return -1;
    }

    if (counter == 1) {
        ho = (last[0] - '0');
    }
    if (counter == 2) {
        ho = (last[0] - '0') * 10 + last[1] - '0';
    }
    if (ho > 32 || ho < 0) {
        std::cout << "Time value is invalid: ";
        timeInpit(last);
        std::cout << std::endl;
        return -1;
    }

    //for minutes
    counter = 0;
    point = 0;
    while (point == 0) {
        if (((last[i] < '0' || last[i] > '9') && last[i] != ':') || counter > 2) {
            std::cout << "Wrong time format: ";
            timeInpitFormat(last);
            std::cout << std::endl;
            return -1;
        }
        last[i] == ':' ? point = 1 : ++counter;
        ++i;
    }
    if (counter == 0 || counter > 2) {
        std::cout << "Wrong time format: ";
        timeInpitFormat(last);
        std::cout << std::endl;
        return -1;
    }
    if (counter == 1) {
        mi = (last[i - 2] - '0');
    }
    if (counter == 2) {
        mi = (last[i - 3] - '0') * 10 + last[i - 2] - '0';
    }
    if (mi > 59 || mi < 0) {
        std::cout << "Time value is invalid: ";
        timeInpit(last);
        std::cout << std::endl;
        return -1;
    }

    //for seconds
    degree = 0;
    counter = 0;
    point = 0;
    while (point == 0) {
        if (((last[i] < '0' || last[i] > '9') && last[i] != ',') || counter > 2) {
            std::cout << "Wrong time format: ";
            timeInpit(last);
            std::cout << std::endl;
        }
        last[i] == ',' ? point = 1 : ++counter;
        ++i;
    }
    if (counter == 0) {
        std::cout << "Wrong time format: ";
        timeInpit(last);
        std::cout << std::endl;
        return -1;
    }
    for (int begin = 0; begin < counter; ++begin) {
        se += int((last[i - 2] - '0') * pow(10, degree));
        ++degree;
        --i;
    }
    if (se > 59 || se < 0) {
        std::cout << "Time value is invalid: ";
        timeInpit(last);
        std::cout << std::endl;
        return -1;
    }
    long long answ = static_cast < long long >(31622400) * ye + static_cast <long long>(monthCount(mo, ye)) + static_cast <long long>(da * 86400) + static_cast <long long>(ho * 3600) + static_cast <long long>(mi * 60) + static_cast <long long>(se);
    return answ;
}

bool Corrector(order& ord) {
    if (ord.title[15] != ',' && ord.title[15] != 0) {
        std::cout << "Invalid title: ";
        for (short i = 0; ord.title[i] != ','; ++i) {
            std::cout << ord.title[i];
        }
        std::cout << std::endl;
        return true;
    }
    if ((strcmp("sell,", ord.status)!=0) && (strcmp("buy,", ord.status)!=0)) {
        std::cout << "Unknown command: ";
        for (short i = 0; ord.status[i] != ','; ++i) {
            std::cout << ord.status[i];
        }
        std::cout << std::endl;
        return true;
    }
    return false;
}
