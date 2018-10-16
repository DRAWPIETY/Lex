# include<iostream>
# include<string>
# include<fstream>
# include<sstream>//流对象
# include<vector>
# include<map>
using namespace std;

bool isIdentifier(string s);//标识符
bool isKeywords(string s);//关键字
bool isDigit(string s);//整型数字
bool isOperator(string s);//运算符
bool isOperator(char c);//运算符
string result(string s);//根据传入的参数s产生对应的输出
int main()
{
    //=====================测试函数是否正确=============================
    /*if(isIdentifier("_s2ias"))
        cout << "是标识符" << endl;
    if (isKeywords("for"))
        cout << "是关键字" << endl;
    if (isDigit("12a42"))
        cout << "是数字" << endl;
    if (isOperator(">"))
        cout << "是运算符" << endl;
    result("?");*/
    //===================================================================

    string file = ("TestData1.txt");
    ifstream input(file);
    //输入文件流,注意编码，文本文件编码格式需和项目一直，否则乱码

    ofstream output("Result.txt",ofstream::app);
    //先将TtestData.txt内容拷贝到Result.txt中
    string copy;

    getline(input, copy, '\0');
    cout<< copy << endl;//测试是否正确

    //此时input已经指到了文件尾，为了后面的读取，需要关闭再打开
    input.close();
    input.open(file);

    /*测试结果要求以原数据与结果对照的形式输出并保存在Result.txt中，
    同时要把结果输出到屏幕。
    */
    output << "原数据:\n";
    output << copy;
    output << "处理后结果:\n";

    string str;
    string words;

    cout << "处理后结果:\n";
    while (getline(input, str)) //读取文件每一次读取一行,遇到EOF结束
    {
        //从输入流中获取单词，需要用到输入流对象，即istringstream
        istringstream strCin(str);
        string s;
        while (strCin >> words)
        {
            //注意处理逗号，比如int a,b;这里有一个单词"a,b;”,所以要处理一个字符串里面
            //的各种运算符,但是这样会很麻烦，发现没有，用ide写代码写完一句输入分号时，ide
            //会自动加入空格，这样就方便处理多了


            //1.首先可以确定的是关键字肯定是单独作为一个单词的
            if (isKeywords(words))
            {
                s = result(words);
                cout << s << endl;
                output << s << endl;
                continue;
            }

            //2,对单词进行扫描，肯定是标识符，运算符，逗号分号,数字等等混合在一起的单词
            vector<int> index = {0};
            vector<string> mulWords;//将words分解为多个单词
            for (int i = 0; i < words.length(); i++)
            {

                //运算符有两位的，比如"<=",">=","==","!="
                if ((i < words.length() - 1) && isOperator(words[i]) && isOperator(words[i + 1]))
                {
                    //但是要注意只有以上四种两位运算符，比如+-,))就不是,但是))还是要输出),)
                    if (string(words.begin() + i, words.begin() + i + 2) == "<=" ||
                        string(words.begin() + i, words.begin() + i + 2) == ">=" ||
                        string(words.begin() + i, words.begin() + i + 2) == "==" ||
                        string(words.begin() + i, words.begin() + i + 2) == "!=")
                    {
                        index.push_back(i);
                        index.push_back(i + 2);
                        ++i;
                    }
                    else if (isOperator(words[i]))
                    {
                        if (find(index.begin(), index.end(), i) == index.end())
                            index.push_back(i);
                        if (find(index.begin(), index.end(), i + 1) == index.end())
                            index.push_back(i + 1);

                    }
                }
                //逗号，运算符作为分隔
                 else if (isOperator(words[i]))
                {
                    if (find(index.begin(), index.end(), i) == index.end())
                    //比如遇到"a,b"这里下标0和1将a分开，1到2将逗号分开，2到3将b分开
                        index.push_back(i);
                    if (find(index.begin(), index.end(), i+1) == index.end())
                        index.push_back(i + 1);

                    //如果是a<=b这样的呢？一样，先0和1将a分开，1和2将<分开，2和3将=分开
                    //3和4将b分开，然后后面分隔单词时，注意如果相邻都是运算符，则忽略，比如
                    //后面判断到1和2，2和3都是运算符，则忽略2

                }

            }
            for (int i = 0; i < index.size()-1; i++)
            {
                string rel;
                //比如遇到"<="，需要提取”<=“
                /*if (isOperator(words[index[i]]) && isOperator(words[index[i + 1]]))
                {
                    rel = result(string(words.begin() + index[i], words.begin() + index[i + 2]));
                    ++i;
                }
                else*/
                rel=result(string(words.begin() + index[i], words.begin() + index[i + 1]));

                output << rel << endl;
                cout << rel<<endl;
            }

        }
    }
    output << endl;
    output.close();
    input.close();
    system("pause");
    return 0;
}

bool isIdentifier(string s)//标识符,试验要求:ID=letter(letter|digit)*
{
    if (!isKeywords(s))//标识符不能是关键字
    {
        if ((s[0] >= 'a'&&s[0] <= 'z') || (s[0] >= 'A'&&s[0] <= 'Z'))//是字母
        {
            for (int i = 1; i < s.length(); i++)
            {
                if ((s[i] >= 'a'&&s[i] <= 'z') || (s[i] >= 'A'&&s[i] <= 'Z')
                    || (s[i] >= '0'&&s[i] <= '9'))
                    continue;
                else return false;
            }
            return true;
        }
        return false;
    }
    return false;
}
bool isKeywords(string s)//关键字
{
    static vector<string> keyVec = { "main", "int", "float", "double", "char",
        "if", "then","else", "switch", "case", "break", "continue", "while",
        "do", "for" };
    vector<string>::iterator result = find(keyVec.begin(), keyVec.end(),s);
    if (result != keyVec.end())
        return true;
    else return false;
}
bool isDigit(string s)//整型数字,NUM=digit digit*
{
    if (s[0] >= '0'&&s[0] <= '9')
    {
        for (int i = 1; i < s.length(); ++i)
            if (s[i] >= '0'&&s[i] <= '9')
                continue;
            else return false;
        return true;
    }
    return false;
}

bool isOperator(string s)//运算符
{
    static vector<string> opeVec = { "=","+","-","*","/","<","<=","==","!=",
        ">",">=",";","(",")","?",":","," };
    vector<string>::iterator result = find(opeVec.begin(), opeVec.end(), s);
    if (result != opeVec.end())
        return true;
    else return false;
}

bool isOperator(char c)//运算符
{
    static vector<char> opeVec = { '=','+','-','*','/','<',
        //"<=","==","!=",
        '>',
        //">=",
        ';','(',')','?',':',',' };
    vector<char>::iterator result = find(opeVec.begin(), opeVec.end(), c);
    if (result != opeVec.end())
        return true;
    else return false;
}

string result(string s)//根据传入的参数s产生对应的输出
{
    //种别码
    //1.标识符
    if (isIdentifier(s))
        return "(标识符--10,"+s+")";

    //2.关键字
    static map<string, string> keyMap;
    keyMap["int"] = "1";
    keyMap["float"] = "2";
    keyMap["if"] = "3";
    keyMap["switch"] = "4";
    keyMap["while"] = "5";//只写5个吧，没必要全写
    if (isKeywords(s))
        return "(关键字--"+keyMap[s]+"," +s+")";

    //3.整型常量
    if (isDigit(s))
        return "(整型常量--11,"+s+")";

    //4.运算符
    static map<string, string> opeMap;
    opeMap["="] = "(等号--17，=）";
    opeMap["<"] = "(小于号--20,<)";
    opeMap["<="] = "(小于等于号--21,<=)";
    opeMap["=="] = "(赋值运算符--22，==）";
    opeMap["!="] = "(不等于号--23,!=)";
    opeMap[">"] = "(大于号--24,>)";
    opeMap[">="] = "(大于等于号--25,>=)";
    opeMap[";"] = "(分号--26,;)";
    opeMap["+"] = "(加号--13,+)";
    opeMap["("] = "( 左括号--27,( )";
    opeMap["-"] = "(减号--14,-)";
    opeMap[")"] = "(右括号--28,) )";
    opeMap[">"] = "(大于号--24,>)";
    opeMap["*"] = "(星号--15,*)";
    opeMap["?"] = "(问号--29,?)";
    opeMap["/"] = "(除号--16,/)";
    opeMap[":"] = "(冒号--30,:)";
    opeMap[","] = "(逗号--31,,)";
    if (isOperator(s))
        return opeMap[s];
    return "Error";
}
