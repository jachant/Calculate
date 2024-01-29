#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;
const long divDigits = 1000;

class LongDouble {
private:
    int sign;
    vector<int> digits;
    long exponent;


public:
    void removeZeroes();
    LongDouble();
    LongDouble(const LongDouble& x);
    LongDouble(const string& value);

    // Оператор перегрузки << для вывода значения LongDouble
    friend ostream& operator<<(ostream& os, const LongDouble& value);
    //операто умножения
    LongDouble operator*(const LongDouble& x) const;
    //оператор унаврного минуса
    LongDouble operator-() const;
    //оператор >
    bool operator>(const LongDouble& x) const;
    //оператор +
    LongDouble operator+(const LongDouble& x) const;
    //оператор -
    LongDouble operator-(const LongDouble& x) const;
    //оператор деления
    LongDouble inverse() const;
    LongDouble operator/(const LongDouble& x) const;
    //оператор ==
    bool operator==(const LongDouble& x) const;
    //оператор <
    bool operator<(const LongDouble& x) const;
    //оператор >=
    bool operator>=(const LongDouble& x) const;
    //оператор <=
    bool operator<=(const LongDouble& x) const;
    //оператор !=
    bool operator!=(const LongDouble& x) const;
    //возводим в обычную степень
    LongDouble pow_LongDouble(const LongDouble x,const LongDouble y) const;
    // факториал
    LongDouble fact(const LongDouble x) const;
    //sin
    LongDouble sin( LongDouble x, LongDouble y) const;
    //floor
    LongDouble floor(const LongDouble x, LongDouble y) const;
    //sqrt
    LongDouble sqrt(LongDouble y, LongDouble k) const;
    //cos
    LongDouble cos(LongDouble x, LongDouble y) const;
    //tg
    LongDouble tg(LongDouble x) const;
    //ctg
    LongDouble ctg(LongDouble x) const;
    //print
    void print(const LongDouble& value) const;
    //log and ln
    LongDouble abs(LongDouble x) const;
    //abs
    LongDouble ln(LongDouble y, LongDouble x) const;
    LongDouble log(LongDouble y, LongDouble x) const;
};


void LongDouble::removeZeroes() {
    size_t n = max((long)1, exponent); // определяем, до какого момента нужно будет идти для удаления нулей справа

    // пока справа нули
    while (digits.size() > n && digits[digits.size() - 1] == 0)
        digits.erase(digits.end() - 1); // удаляем их

    // пока число цифр больше одной и вектор начинается с нуля
    while (digits.size() > 1 && digits[0] == 0) {
        digits.erase(digits.begin()); // удаляем нули из начала вектора
        exponent--; // и уменьшаем экспоненту
    }

    // если справа всё ещё остались нули
    while (digits.size() > 1 && digits[digits.size() - 1] == 0)
        digits.erase(digits.end() - 1); // то удалим их

    // если в результате осталась всего одна нулевая цифра, то превратим её в честный ноль
    if (digits.size() == 1 && digits[0] == 0) {
        exponent = 1;
        sign = 1;
    }
}
ostream& operator<<(ostream& os, const LongDouble& value) {
    if (value.sign == -1)
        os << '-'; // если число отрицательное, то сначала выведем знак минус

    // если экспонента положительна, то у числа ненулевая целая часть
    if (value.exponent > 0) {
        size_t i = 0;
        size_t e = value.exponent;

        // выводим первые exponent цифр (или все цифры, если экспонента больше) числа чтобы вывести целую часть
        while (i < value.digits.size() && i < e)
            os << value.digits[i++];

        // если экспонента больше цифр числа, то выводим нули, чтобы дойти до экспоненты
        while (i < e) {
            os << "0";
            i++;
        }

        // если цифры ещё остались
        if (i < value.digits.size()) {
            os << "."; // то выводим точку

            // и выводим оставшиеся цифры как дробную часть
            while (i < value.digits.size())
                os << value.digits[i++];
        }
    }
    else { // иначе эспонента отрицательна или нулевая
        os << "0."; // выводим нулевую целую часть с точкой

        // выводим |exponent| нулей (если экспонента нулевая, то не будет ни одного нуля)
        for (long i = 0; i < -value.exponent; i++)
            os << "0";

        // выводим все цифры числа
        for (size_t i = 0; i < value.digits.size(); i++)
            os << value.digits[i];
    }

    return os; // возвращаем поток вывода
}
void LongDouble::print(const LongDouble& value) const {
    string os= "";
    if (value.sign == -1)
        cout << '-'; // если число отрицательное, то сначала выведем знак минус

    // если экспонента положительна, то у числа ненулевая целая часть
    if (value.exponent > 0) {
        size_t i = 0;
        size_t e = value.exponent;

        // выводим первые exponent цифр (или все цифры, если экспонента больше) числа чтобы вывести целую часть
        while (i < value.digits.size() && i < e)
            cout << value.digits[i++];

        // если экспонента больше цифр числа, то выводим нули, чтобы дойти до экспоненты
        while (i < e) {
            cout << "0";
            i++;
        }

        // если цифры ещё остались
        if (i < value.digits.size()) {
            cout << "."; // то выводим точку

            // и выводим оставшиеся цифры как дробную часть
            while (i < value.digits.size())
                cout << value.digits[i++];
        }
    }
    else { // иначе эспонента отрицательна или нулевая
        cout << "0."; // выводим нулевую целую часть с точкой

        // выводим |exponent| нулей (если экспонента нулевая, то не будет ни одного нуля)
        for (long i = 0; i < -value.exponent; i++)
            cout << "0";

        // выводим все цифры числа
        for (size_t i = 0; i < value.digits.size(); i++)
            cout << value.digits[i];
    }

}


// конструктор по-умолчанию
LongDouble::LongDouble() {
    sign = 1; // ноль будем считать положительным числом
    digits = vector<int>(1, 0); // создаём вектор из 1 нулевой цифры
    exponent = 1;
}

// конструктор копирования
LongDouble::LongDouble(const LongDouble& x) {
    sign = x.sign; // копируем знак
    exponent = x.exponent; // копируем экспоненту
    digits = vector<int>(x.digits); // копируем цифры
}

// конструктор из строки
LongDouble::LongDouble(const string& value) {
    size_t index;

    // если первый символ строки - минус, значит число отрицательное
    if (value[0] == '-') {
        sign = -1; // знак отрицательного числа -1
        index = 1; // начинать идти нужно будет с первого символа
    }
    else {
        sign = 1; // иначе число положительное
        index = 0; // и идти нужно будет с нулевого символа
    }

    exponent = value.length() - index; // предполагаем, что всё число будет целым, а значит и экспонента будет равна длине строки

    // идём по всей строке
    while (index < value.length()) {
        if (value[index] == '.')  // если встретили точку
            exponent = sign == 1 ? index : index - 1; // запоминаем экспоненту, так как целая часть закончилась
        else
            digits.push_back(value[index] - '0'); // иначе вставляем в вектор очередную цифру

        index++; // переходим к новому символу
    }
}
LongDouble LongDouble::operator*(const LongDouble& x) const {
    size_t len = digits.size() + x.digits.size(); // максимальная длина нового числа не больше суммы длин перемножаемых чисел

    LongDouble res; // создадим объект для результата

    res.sign = sign * x.sign; // перемножаем знаки
    res.digits = vector<int>(len, 0); // создаём вектор из нулей
    res.exponent = exponent + x.exponent; // складываем экспоненты

    // умножаем числа в столбик
    for (size_t i = 0; i < digits.size(); i++)
        for (size_t j = 0; j < x.digits.size(); j++)
            res.digits[i + j + 1] += digits[i] * x.digits[j]; // прибавляем результат произведения цифр из i-го и j-го разрядов

    // в результате такого перемножения в ячейках могли получиться двузначные числа, поэтому нужно выполнить переносы
    for (size_t i = len - 1; i > 0; i--) {
        res.digits[i - 1] += res.digits[i] / 10; // добавляем к более старшему разряду десятки текущего разряда
        res.digits[i] %= 10; // оставляем только единицы у текущего разряда
    }

    res.removeZeroes(); // удаляем нули, как в конструкторе из строки, если таковые имеются

    return res; // возвращаем результат умножения двух чисел
}


// унарный минус
LongDouble LongDouble::operator-() const {
    LongDouble res; // создаём число
    res.sign = -sign; // меняем знак на противоположный
    res.exponent = exponent; // копируем экспоненту
    res.digits = vector<int>(digits); // копируем цифры

    return res; // возвращаем результат
}

// проверка, что число больше другого
bool LongDouble::operator>(const LongDouble& x) const {
    if (sign != x.sign)
        return sign > x.sign; // если знаки разные, то положительное число больше

    if (exponent != x.exponent)
        return (exponent > x.exponent) ^ (sign == -1); // если экспоненты разные, то больше число с большей экспонентой с учётом знака

    // копируем вектора
    vector<int> d1(digits);
    vector<int> d2(x.digits);
    size_t size = max(d1.size(), d2.size()); // определяем максимальный размер векторов

    // выравниваем размеры векторов, добавляя в концы нули
    while (d1.size() != size)
        d1.push_back(0);

    while (d2.size() != size)
        d2.push_back(0);

    // проходим по всем цифрам числа
    for (size_t i = 0; i < size; i++)
        if (d1[i] != d2[i])
            return (d1[i] > d2[i]) ^ (sign == -1); // если в каком-то разряде цифры разные, то больше число с большей цифрой с учётом знака

    return false; // иначе числа равны, а значит не больше
}


LongDouble LongDouble::operator+(const LongDouble& x) const {
    if (sign == x.sign) { // если знаки одинаковые
        long exp1 = exponent; // запоминаем экспоненту первого
        long exp2 = x.exponent; // и второго чисел
        long exp = max(exp1, exp2); // находим максимальную экспоненту. К ней будем приводить оба числа

        // создаём вектора из векторов цифр наших чисел
        vector<int> d1(digits);
        vector<int> d2(x.digits);

        // выравниваем экспоненты
        while (exp1 != exp) {
            d1.insert(d1.begin(), 0); // добавляя нули в начало первого
            exp1++;
        }

        while (exp2 != exp) {
            d2.insert(d2.begin(), 0); // и в начало второго векторов
            exp2++;
        }

        size_t size = max(d1.size(), d2.size()); // определяем максимальный размер векторов

        // выравниваем размеры векторов, добавляя нули в конец каждого из них
        while (d1.size() != size)
            d1.push_back(0);

        while (d2.size() != size)
            d2.push_back(0);

        size_t len = 1 + size;

        LongDouble res; // создаём новое число

        res.sign = sign; // знак результата совпадает со знаком чисел
        res.digits = vector<int>(len, 0); // создаём вектор из len нулей

        // заполняем каждую ячейку вектора суммой двух соответствующих цифр
        for (size_t i = 0; i < size; i++)
            res.digits[i + 1] = d1[i] + d2[i];

        // проверяем переполнения
        for (size_t i = len - 1; i > 0; i--) {
            res.digits[i - 1] += res.digits[i] / 10; // прибавляем к более старшему разряду десятки текущего
            res.digits[i] %= 10; // оставляем у текущего разряда только единицы
        }

        res.exponent = exp + 1; // восстанавливаем экспоненту
        res.removeZeroes(); // убираем нули

        return res; // возвращаем число
    }

    if (sign == -1)
        return x - (-(*this)); // если первое число отрицательное, то из второго вычитаем первое с обратным знаком

    return *this - (-x); // иначе из первого вычитаем второе с обратным знаком
}


LongDouble LongDouble::operator-(const LongDouble& x) const {
    if (sign == 1 && x.sign == 1) { // если боа числа положительны
        bool cmp = *this > x; // получаем флаг того, больше ли первое число

        long exp1 = cmp ? exponent : x.exponent; // сохраняем экспоненту большего числа
        long exp2 = cmp ? x.exponent : exponent; // сохраняем экспоненту меньшего числа
        long exp = max(exp1, exp2); // определяем максимальную экспоненту, чтобы к ней привести числа

        vector<int> d1(cmp ? digits : x.digits); // запоминаем вектор цифр большего числа
        vector<int> d2(cmp ? x.digits : digits); // запоминаем вектор цифр меньшего числа

        // выравниваем экспоненты как при сложении (добавляя нули вначале числа)
        while (exp1 != exp) {
            d1.insert(d1.begin(), 0);
            exp1++;
        }

        while (exp2 != exp) {
            d2.insert(d2.begin(), 0);
            exp2++;
        }

        size_t size = max(d1.size(), d2.size()); // определяем максимальный размер

        // добавляем нули в конец векторов цифр
        while (d1.size() != size)
            d1.push_back(0);

        while (d2.size() != size)
            d2.push_back(0);

        size_t len = 1 + size;

        LongDouble res; // создаём число для результата

        res.sign = cmp ? 1 : -1; // знак будет 1, если первое больше второго, и -1, если первое меньше второго
        res.digits = vector<int>(len, 0); // создаём вектор из len нулей

        for (size_t i = 0; i < size; i++)
            res.digits[i + 1] = d1[i] - d2[i]; // вычитаем соответствующие разряды

        // обрабатываем переполнения
        for (size_t i = len - 1; i > 0; i--) {
            if (res.digits[i] < 0) { // если текущий разряд стал меньше нуля
                res.digits[i] += 10; // занимаем у предыдущего, прибавляя 10 к текущему
                res.digits[i - 1]--; // уменьшаем на 1 предыдущий разряд
            }
        }

        res.exponent = exp + 1; // восстанавливаем экспоненту
        res.removeZeroes(); // удаляем лишнии нули

        return res; // возвращаем результат
    }

    if (sign == -1 && x.sign == -1)
        return (-x) - (-(*this)); // если оба числа отрицательны, то из второго с обратным знаком вычитаем первое с обратным знаком

    return *this + (-x); // если знаки разные, прибавляем к первому отрицательное второе
}

LongDouble LongDouble::inverse() const {
    if (digits.size() == 1 && digits[0] == 0)
        throw string("LongDouble LongDouble::inverse() - division by zero!"); // делить на ноль нельзя, поэтому бросим исключение

    LongDouble x(*this); // скопируем число,
    x.sign = 1; // сделав его положительным

    LongDouble d("1"); // создадим то, что будем делить на x

    LongDouble res; // создадит объект для результата
    res.sign = sign; // знак результата совпадёт со знаком числа
    res.exponent = 1; // начнём с единичной экспоненты
    res.digits = vector<int>(); // создадим пустой вектор для цифр обратного элемента

    // пока число меньше 1
    while (x < LongDouble("1")) {
        x.exponent++; // будем увеличивать его экспоненту (умножать на 10 фактически)
        res.exponent++; // и заодно экспоненту результата
    }

    // дальше сдлеаем число d большим x, также умножая его на 10, чтобы получить число 100...0
    while (d < x)
        d.exponent++;

    res.exponent -= d.exponent - 1; // подсчитаем реальное количество цифр в целой части
    size_t numbers = 0; // количество уже вычисленных цифр дробной части
    size_t totalNumbers = divDigits + max((long)0, res.exponent); // количество цифр с учётом целой части
    int ans = 0;
    do {
        ans++;
        int div = 0; // будущая цифра

        // считаем, сколько раз нужно вычесть x из d
        while (d >= x) {
            div++;
            d = d - x;
        }

        // увеличиваем остаток в 10 раз
        d.exponent++;
        d.removeZeroes();
        res.digits.push_back(div); // записываем сформированную цифру
        numbers++; // увеличиваем число вычисленных цифр
    } while (d != LongDouble("0") && numbers < totalNumbers && ans<5); // считаем до тех пор, пока не дойдём до нулевого остатка или пока не превысим точность

    return res; // возвращаем результат
}


bool LongDouble::operator==(const LongDouble& x) const {
    if (sign != x.sign)
        return false;

    if (exponent != x.exponent)
        return false;

    if (digits.size() != x.digits.size())
        return false;

    for (size_t i = 0; i < digits.size(); i++)
        if (digits[i] != x.digits[i])
            return false;

    return true;
}

bool LongDouble::operator<(const LongDouble& x) const {
    return !(*this > x || *this == x);
}

bool LongDouble::operator>=(const LongDouble& x) const {
    return (*this > x || *this == x);
}

bool LongDouble::operator<=(const LongDouble& x) const {
    return *this < x || *this == x;
}

bool LongDouble::operator!=(const LongDouble& x) const {
    return !(*this == x);
}

LongDouble LongDouble::operator/(const LongDouble& x) const {
    LongDouble res = *this * x.inverse(); // выполняем умножение на обратный элемент

    // избавляемся от записи вида d...dd(9), которая эквивалентна d...dd+1
    size_t i = res.digits.size() - 1 - max((long)0, exponent);
    size_t n = max((long)0, res.exponent);
    // если в указанном месте девятка, то ищем место, в котором девятки закончатся
    if (i > n && res.digits[i] == 9) {
        while (i > n && res.digits[i] == 9)
            i--;

        // если дошли до целой части
        if (res.digits[i] == 9) {
            res.digits.erase(res.digits.begin() + n, res.digits.end()); // то удаляем всю вещественную часть
            if (res.sign == 1) {
                res = res + LongDouble("1"); // и прибавляем 1 (или -1 к отрицательному) 
            }
            else {
                res = res - LongDouble("1");
            }
        }

        else {
            res.digits.erase(res.digits.begin() + i + 1, res.digits.end()); // иначе обрезаем с найденного места
            res.digits[i]++; // и увеличиваем на 1 текущий разряд
        }
    }

    return res; // возвращаем результат деления
}

LongDouble LongDouble::pow_LongDouble(const LongDouble x,const LongDouble y) const {
    LongDouble POW("1");
    for (LongDouble i("0"); i < y; i = i + LongDouble("1")) {
        POW = POW * x;
    }
    return POW;
}

LongDouble LongDouble::fact(const LongDouble x) const {
    if (x == LongDouble("0") || x == LongDouble("1")) { return LongDouble("1"); }
    return x * fact(x - LongDouble("1"));
}

LongDouble LongDouble::sin( LongDouble x, LongDouble y) const {
    long long w = 3;
    LongDouble w_2("3");
    x = (x / LongDouble("6.283185") - x.floor(x, LongDouble("6.283185"))) * LongDouble("6.283185");
    y = (y / LongDouble("6.283185") - y.floor(y, LongDouble("6.283185"))) * LongDouble("6.283185");
    for (long long i = 0; i < 10; i++) {
        if (i % 2 == 0) {
            y = y - ((x.pow_LongDouble(x, w_2)) / (w_2.fact(w_2))); w += 2; w_2 = w_2 + LongDouble("2");
        }
        else {
            y = y + ((x.pow_LongDouble(x, w_2)) / (w_2.fact(w_2))); w += 2; w_2 = w_2 + LongDouble("2");
        }

    }
    return y;
}

LongDouble LongDouble::floor(const LongDouble x, LongDouble y) const {
    LongDouble Floor("1");
    while (x - Floor * y >= y) {
        Floor = Floor + LongDouble("1");
    }
    return Floor;
}

LongDouble LongDouble::sqrt(LongDouble y, LongDouble k) const {
    LongDouble x("1");
    for (int i=0; i<1000; i++) {
        x = (LongDouble("1") / y) * ((y - LongDouble("1")) * x + k/x.pow_LongDouble(x, y-LongDouble("1")));
    }
    return x;
}

LongDouble LongDouble::cos(LongDouble x, LongDouble y) const{
    y = (y / LongDouble("3,141592") - y.floor(y, LongDouble("3,141592"))) * LongDouble("3,141592");
    if (y >= LongDouble("-1,570796") && y<= LongDouble("1,570796")) {
    return sqrt(LongDouble("2"), (LongDouble("1") - x.pow_LongDouble(x.sin(x, x), LongDouble("2")))); }
    else {
        return LongDouble("-1")*sqrt(LongDouble("2"), (LongDouble("1") - x.pow_LongDouble(x.sin(x, x), LongDouble("2"))));
    }
}

LongDouble LongDouble::tg(LongDouble x) const {
    return x.sin(x, x) / x.cos(x, x);
}

LongDouble LongDouble::ctg(LongDouble x) const {
    return LongDouble("1") / x.tg(x);
}

LongDouble LongDouble::ln(LongDouble y, LongDouble x) const {
    if (x>LongDouble("0") && LongDouble("2") >= x) {
        x = x-LongDouble("1");
        y = y - LongDouble("1");
        LongDouble w("2");
    for (int i=0; i<800; i++) {
        if (i%2==0) {
            y = y-(x.pow_LongDouble(x, w)/w);
        }
        else {
            y = y+(x.pow_LongDouble(x, w)/w);
        }
        w = w+LongDouble("1");
    }
    return y;
    }
    else {
        x = x/LongDouble("2");
        return ln(LongDouble("2"), LongDouble("2")) + ln(x, x);
    }
}

LongDouble LongDouble::log(LongDouble y, LongDouble x) const {
    return ln(x, x)/ln(y, y);
}



vector <string> stack_op;
vector <LongDouble> stack_num;


int ranc(string x) {
    if (x[0] >= 97 && x[0] <= 122) { return 5; }
    else if (x[0] == '#') { return 4; }
    else if (x[0] == '^') { return 3; }
    else if (x[0] == '*' || x[0] == '/' || x[0] == '%') { return 2; }
    else if (x[0] == '+' || x[0] == '-') { return 1; }
    else { return 0; }
}

LongDouble pop2() {
    LongDouble x = stack_num.back();
    stack_num.pop_back();
    return x;
}

LongDouble LongDouble::abs(LongDouble x) const {
    if (x<LongDouble("0")) {x = x* LongDouble("-1");}
    return x;
}
void calc(string i) {
    LongDouble x = pop2();
    if (i[0] == '+') {
        stack_num.push_back(x + pop2());
    }
    else if (i[0] == '#') {
        stack_num.push_back(-x);
    }
    else if (i[0] == '%') {
        LongDouble y = pop2();
        stack_num.push_back(y-x.floor(y,x)*x);
    }
    else if (i[0] == '^') {
        if(LongDouble("1")<=x){
            stack_num.push_back(x.pow_LongDouble(pop2(),x));
        }
        else{
            stack_num.push_back(x.sqrt(LongDouble("1")/x,pop2()));
        }
    }
    else if (i[0] == '-') {
        stack_num.push_back(pop2() - x);
    }
    else if (i[0] == '*') {
        stack_num.push_back(x * pop2());
    }
    else if (i[0] == '/') {
        stack_num.push_back(pop2() / x);
    }
    else if (i == "cos") {
        stack_num.push_back(x.cos(x,x));
    }
    else if (i == "sin") {
        stack_num.push_back(x.sin(x,x));
    }
    else if (i == "tg") {
        stack_num.push_back(x.tg(x));
    }
    else if (i == "ctg") {
        stack_num.push_back(x.ctg(x));
    }
    else if (i == "lg") {
        stack_num.push_back(x.log(LongDouble("10"),x));
    }
    else if (i == "ln") {
        stack_num.push_back(x.ln(x,x));
    }
    else if (i == "abs") {
        stack_num.push_back(x.abs(x));
    }
    //Експаненту сделайте выблядки
}

bool is_letter(char x) {
    if (x >= 97 && x <= 122) return 1;
    return 0;
}
bool is_number(char x) {
    if (x >= 48 && x <= 57) return 1;
    return 0;
}
class parcing_function {
public:
    parcing_function(string input) :line(input) {};
    bool is_basic_func(string func) {
        if (func=="sin" || func == "cos"|| func =="abs" || func == "ctg" || func == "tg" || func == "sqrt" || func == "ln" || func == "log" || func == "exp") return 1;
        return 0;
    }
    string is_func(string str,int ind) {
        if (!is_letter(str[ind])) return "";
        string cur_str="";
        for (int i = ind; i < str.length(); i++) {
            if (is_letter(str[i]) || is_number(str[i])) { cur_str += str[i]; }
            else if (str[i] == '(') { 
                return cur_str;
            }
            else { return ""; }
        }
        return "";
    }

    string is_const(string str,int ind) {
        if (!is_letter(str[ind])) return "";
        string cur_str="";
        for (int i = ind; i < str.length(); i++) {
            if (is_letter(str[i]) || is_number(str[i])) {
                cur_str += str[i];
                if (i == str.length() - 1) return cur_str;
            }
            else { 
                if (str[i] != '(')  return cur_str;
                break;
            }
        }
        return "";
    }
    //Проверка: есть ли аргумент в списке
    int in_list(vector <string> list,string arg) {
        for (int i = 0; i < list.size(); i++) {
            if (list[i] == arg) return i;
        }
        return -1;
    }
    //Считка сторонних переменных
    void reading() {
        for (int i = 0; i < this->line.length(); i++) {
            if (is_const(this->line, i) != "") {
                string cur = is_const(this->line, i);
                if (in_list(const_name, cur)==-1) {
                    constants++;
                    const_name.push_back(cur);
                }
                i += cur.length();
            }

            else if (is_func(this->line, i) != "") {
                string cur = is_func(this->line, i);
                if (in_list(func_name, cur)==-1 && (!is_basic_func(cur))) {
                    functions++;
                    func_name.push_back(cur);
                }
                i += cur.length();
            }
        }
    }

    vector <string> func_arguments(string str, int ind) {
        string cur_arg="";
        vector <string> arguments;
        int cnt = 1;
        for (int i = ind; i < str.length(); i++) {
            if (str[i] == ')') cnt--;
            else if (str[i] == '(') cnt++;
            if (cnt==0) {
                arguments.push_back(cur_arg);
                break;
            }
            else if (str[i] == ',') {
                arguments.push_back(cur_arg);
                cur_arg = "";
                i++;
            }
            cur_arg += str[i];
        }
        return arguments;
    }

    //Считка сторонних функций
    void read_lines() {
        string str;
        getline(cin, str);
        while (constants != 0 || functions != 0) {
            cout << "Enter: " << constants << " constants and  functions: " << functions << endl;
            cout << "Func:"; for (auto b : func_name) { cout << b << " "; } cout << endl;
            getline(cin, str);
            if (is_func(str, 0) != "") {
                string name = is_func(str, 0);
                int index = in_list(func_name, name);
                if (index == -1) {
                    functions++;
                    func_name.push_back(name);
                    index = func_name.size() - 1;
                }
                else functions--;
                while (func_value.size() < func_name.size()) func_value.push_back("");
                while (func_args.size() < func_name.size()) func_args.push_back(vector <string> ());
                func_args[index]=(func_arguments(str, name.length() + 1));
                string cur_num = ""; for (int i = str.find('=') + 1; i < str.length(); i++) { cur_num += str[i]; } func_value[index] = cur_num;
                for (int i = str.find('=') + 1; i < str.length(); i++) {
                    cout << index << endl;
                    if (is_const(str, i) != "" && in_list(func_args[index], is_const(str, i)) == -1) {
                        string cur = is_const(str, i);
                        if (in_list(const_name, cur) == -1) {
                            constants++;
                            const_name.push_back(cur);
                        }
                        //else constants--;
                        i += cur.length();
                    }
                    else if (is_const(str, i) != "") i += (is_const(str, i)).length();
                    else if (is_func(str, i) != "" && (!is_basic_func(is_func(str, i)))) {
                        string cur = is_func(str, i);
                        if (in_list(func_name, cur) == -1 && (!is_basic_func(cur))) {
                            functions++;
                            func_name.push_back(cur);
                        }
                        //else functions--;
                        i += cur.length();
                    }
                    else if (is_func(str, i) != "") i += (is_func(str, i)).length();
                }
            }

            else if (is_const(str, 0) != "") {
                string name = is_const(str, 0);
                int index = in_list(const_name, name);
                if (index == -1) {
                    constants++;
                    const_name.push_back(name);
                    index = const_name.size() - 1;
                }
                else constants--;
                while (const_value.size() < const_name.size()) const_value.push_back("");
                string cur_num = ""; for (int i = str.find('=') + 1; i < str.length(); i++) { cur_num += str[i]; } const_value[index] = cur_num;
                for (int i = str.find('=') + 1; i < str.length(); i++) {
                    if (is_const(str, i) != "") {
                        string cur = is_const(str, i);
                        if (in_list(const_name, cur) == -1) {
                            constants++;
                            const_name.push_back(cur);
                        }
                        //else constants--;
                        i += cur.length();
                    }

                    else if (is_func(str, i) != "" && (!is_basic_func(is_func(str, i)))) {
                        string cur = is_func(str, i);
                        if (in_list(func_name, cur) == -1 && (!is_basic_func(cur))) {
                            functions++;
                            func_name.push_back(cur);
                        }
                        //else functions--;
                        i += cur.length();
                    }

                }
            }
        }

    }

    string paste(string str,string paster,int index_st,int index_fn) {
        string new_str="";
        for (int i = 0; i < index_st; i++) {
            new_str += str[i];
        }
        new_str += "(";
        for (int i = 0; i < paster.length(); i++) {
            new_str += paster[i];
        }
        new_str += ")";
        for (int i = index_fn; i < str.size(); i++) {
            new_str += str[i];
        }
        return new_str;
    }

    //Вставка функций в исходную строку
    void parcing(){
        for (int i = 0; i < this->line.size(); i++) {
            cout <<endl<< "!!!" << this->line << "!!!" << endl;
            if (is_func(this->line, i) != "" && (!is_basic_func(is_func(this->line, i)))) {
                string name = is_func(this->line, i);
                int index = in_list(func_name, name);
                vector <string> args = func_arguments(this->line, i + name.size() + 1);
                string cur = "";
                for (int k = 0; k < func_value[index].size(); k++) {
                    cout << "|" << i << "|" << endl;
                    if (is_const(func_value[index], k) != "" && in_list(func_args[index], is_const(func_value[index], k)) != -1) {
                        for (int j = 0; j < func_args[index].size(); j++) {
                            if (is_const(func_value[index], k) == func_args[index][j]) {
                                cur += args[j];
                                k += func_args[index][j].length()-1;
                            }
                        }
                    }
                    else cur += func_value[index][k];
                }
                cout << "|" << cur << "|" << endl;
                int right = name.length() + 1;
                for (int l = 0; l < args.size(); l++) {
                    for (int z = 0; z < args[l].length(); z++) {
                        right++;
                    }
                    right++;
                }
                this->line = paste(this->line, cur, i,i+ right);
                i--;
                cout << this->line << endl;
            }
            else if (is_func(this->line, i) != "") i += is_func(this->line, i).size();
            else if (is_const(this->line, i) != "") {
                cout << "|" << this->line[i] << "|";
                string name = is_const(this->line, i);
                for (int j = 0; j < const_value.size(); j++) {
                    if (const_name[j] == name) {
                        cout << i + name.length();
                        this->line = paste(this->line, const_value[j], i, i + name.length());
                        break;
                        i--;
                    }

                }

            }
        }

    }



    //Геттер строки
    string get_str() {
        return this->line;
    }
    void get_func_name() {
        for (auto b : func_name) cout << b << " "; cout << endl;
    }
    void get_func_args() {
        for (auto b : func_args) for (auto a:b) cout << a << " "; cout << endl;
    }
    void get_func_value() {
        for (auto b : func_value) cout << b << " "; cout << endl;
    }
    void get_const_name() {
        for (auto b : const_name) cout << b << " "; cout << endl;
    }
    void get_const_value() {
        for (auto b : const_value) cout << b << " "; cout << endl;
    }
    void get_lines_counter() {
        cout << functions << " " << constants << endl;
    }
    string get_line() {
        return this->line;
    }
protected:
    string line;
    int functions = 0, constants = 0;
    vector <string> func_name;
    vector <string> func_value;
    vector <vector <string>> func_args;
    vector <string> const_name;
    vector <string> const_value;
};



int main() {
    // Считывание строчки и парсинг ее
    string input;cin >> input;
    parcing_function obj(input);
    cout << endl;
    string str = obj.get_str();
    obj.reading();
    cout << "READING" << endl;
    obj.read_lines();
    cout << "READING_lines" << endl;
    string res = "";
    cout << "Consts" << endl;
    obj.get_const_name();
    obj.get_const_value();
    cout << "Funcs" << endl;
    obj.get_func_args();
    obj.get_func_name();
    obj.get_func_value();
    obj.parcing();
    cout << "DONE";
    cout << obj.get_str() << endl;
    str = obj.get_line();
    cout << "|||||||||" << str << "|||||||||||";
    for (int i = 0; i < str.size(); i++) {
        if (isdigit(str[i])) {
            double c = 0;
            string cc ="";
            while (isdigit(str[i]) && str[i] != 0) {
                cc+=str[i];
                c = c * 10 + (str[i] - '0');
                res += str[i];
                i++;
            }
            int old_i = i;
            if (str[i] == '.') {
                cc+='.';
                res += str[i];
                i++;
                double drob_c = 0;
                while (isdigit(str[i]) && str[i] != 0) {
                    drob_c = drob_c * 10 + (str[i] - '0');
                    cc+=str[i];
                    res += str[i];
                    i++;
                }
                c += drob_c / pow(10, i - old_i - 1);
            }
            LongDouble longstr(cc);
            stack_num.push_back(longstr);
            res += " ";
            i--;
        }
        else {
            if (str[i] != ')' && str[i] != '(') {
                if (str[i] == '-' && ((i == 0) || (!isdigit(str[i - 1]) && str[i - 1] != ')'))) {
                    stack_op.push_back("#");
                }
                else {
                    string function = ""; function += str[i++];
                    while (is_letter(str[i - 1]) && is_letter(str[i])) {
                        function += str[i++];
                    }
                    i--;
                    while (!stack_op.empty() && ranc(stack_op.back()) >= ranc(function)) {
                        calc(stack_op.back());
                        res += stack_op[stack_op.size() - 1];
                        stack_op.pop_back();
                        res += " ";
                    }
                    stack_op.push_back(function);
                }
            }
            else if (str[i] == '(') {
                stack_op.push_back("(");
            }
            else if (str[i] == ')') {
                while (stack_op.back() != "(") {
                    calc(stack_op.back());
                    res += stack_op[stack_op.size() - 1];
                    stack_op.pop_back();
                    res += " ";
                }

                stack_op.pop_back();
            }
        }
    }
    while (!stack_op.empty()) {
        calc(stack_op.back());
        res += stack_op[stack_op.size() - 1];
        stack_op.pop_back();
        res += " ";
    }
    cout << "Expression:\n" << str << "\nReverse Polish Notation:\n" << res << "\nResult:\n" << stack_num[0];
    return 0;
}
