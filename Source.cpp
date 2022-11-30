#include "Header.h"

token calcPlusMinus(vector<token>&exp)
{


    for (int i = 0; i < exp.size(); i++)
    {


        if (exp[i].t_type == operator_type) {
            vector<token> v;
            for (int j = 0; j <= i - 2; j++) {
                v.push_back(exp[j]);
            }
            int before = exp[i - 1].inte;
            int after = exp[i + 1].inte;
            int ans = 0;
            switch (exp[i].op_type) {
            case plus:
                ans = before + after;
                break;
            case minus:
                ans = before - after;
                break;
            }
            token t;
            t.t_type = int_type;
            t.inte = ans;
            v.push_back(t);

            for (int k = i + 2; k < exp.size(); k++) {

                v.push_back(exp[k]);
            }
            return calcPlusMinus(v);


        }


    }
    return exp[0];
}

static token calcKefelHiluk(vector<token>& exp)
{
    bool found = false;         vector<token> v;
    for (int i = 0; i < exp.size(); i++)
    {
        if (exp[i].op_type == multiply or exp[i].op_type == divide)
        {

            found = true;

            for (int j = 0; j <= i - 2; j++)  v.push_back(exp[j]);
            int before = exp[i - 1].inte;
            int after = exp[i + 1].inte;
            int ans = 0;
            switch (exp[i].op_type) {
            case divide:
                ans = before / after;
                break;
            case multiply:
                ans = before * after;
                break;
            }
            token t;
            t.t_type = int_type;
            t.inte = ans;
            v.push_back(t);
            for (int k = i + 2; k < exp.size(); k++) v.push_back(exp[k]);

        }
    }
    if (found == false)
    {
        return calcPlusMinus(exp);
    }
    else {
        return calcKefelHiluk(v);
    }
}

vector<token> tokenize(const std::string& str) {
    vector<token> v;
    for (int i = 0; i < str.size(); i++)
    {


        token t;
        if (str[i] == '(') {
            t.t_type = operator_type;
            t.op_type = par_open;

        }
        if (str[i] == ')') {
            t.t_type = operator_type;
            t.op_type = par_close;
        }
        if ('+' == str[i]) {
            t.t_type = operator_type;
            t.op_type = plus;


        }
        if (str[i] == '-') {
            t.t_type = operator_type;
            t.op_type = minus;

        }
        if (str[i] == '*') {

            t.t_type = operator_type;
            t.op_type = multiply;
        }
        if (str[i] == '/') {
            t.t_type = operator_type;
            t.op_type = divide;
        }
        if (isdigit(str[i]))
        {

            t.op_type = num;
            t.t_type = int_type;

            std::string str2;
            int j = i;
            while (isdigit(str[j])) {

                str2 += str[j];


                j++;

            }


            t.inte = std::stoi(str2);

        }
        v.push_back(t);

    }
    return v;
}

token Solve(std::vector<token>& exp)
{
    vector<token> v;
    bool found = false;
    for (int i = 0; i < exp.size(); i++)
    {
        if (exp[i].t_type == operator_type)
        {
            if (exp[i].op_type == par_close)
            {
                found = true;


                for (int j = i - 1; j >= 0; j--) {
                    if (exp[j].t_type == operator_type)
                    {
                        if (exp[j].op_type == par_open)
                        {
                            for (int k = j + 1; k <= i - 1; k++) { v.push_back(exp[k]); };
                            token instuff = Solve(v);
                            v.clear();
                            for (int k = 0; k <= j - 1; k++) { v.push_back(exp[k]); };
                            v.push_back(instuff);
                            for (int k = i + 1; k < exp.size(); k++) { v.push_back(exp[k]); };
                            return Solve(v);

                        }
                    }
                }

            }
        }
    }
    return calcKefelHiluk(exp);
}
bool sign(const char& c)
{
    return (c == '+' or c == '-' or c == '*' or c == '/');
}
bool ispar(const char& c)
{
    return (c == '(' or c == ')');
}
bool valid(const char& c)
{
    return (sign(c) or ispar(c) or isdigit(c));
}


bool checkvalid(string& exp)
{
    for (int i = 0; i < exp.size(); i++)
    {
        char tav = exp[i];
        if (!valid(tav)) return false;
        if (i == 0 and tav == ')') return false;
        if (i == exp.size() - 2 and ispar(tav)) return false;
        if (i == exp.size() - 1 and (tav == '(' or sign(tav))) return false;
        if (sign(tav) and sign(exp[i + 1])) return false;
        if (ispar(tav) and ispar(exp[i + 1])) return false;

    }
    return true;
}



int main()
{
    string str;
    bool OK = false;
    while (!OK) {
        cout << "Enter an Equation" << endl;
        std::getline(std::cin, str);
        OK = checkvalid(str);
    }

    vector<token> v = tokenize(str);
    token t = Solve(v);
    cout << "Answer" << t.inte;


    return 0;


}

