# encoding: utf-8
#------------------------------------------------------------
#relex.py
#
#lexical analysis
#------------------------------------------------------------
import re

# Dict of keywords
keyVec = {"int":1, "if":2, "while":3, "cout":4, "endl":5}

# Dict of operactor
opeVec = {
        "=":'等号--6', "+":'加号--7', "-":'减号--8',
        "<":'小于号--9', ";":'分号--10', "(":'左括号--11',
        ")":'右括号--12', "{":'左大括号--13',
        "}":'右大括号--14',"<<":'流操作--15',
        }

# Pattern for identifiers
identifier = re.compile('[a-zA-Z]\w*')

# Pattern for nunbers
number = re.compile('\d+')

# Pattern for string
string = re.compile('\".*?\"')

# Pattern for sqlitting
p = re.compile(r'(int|if|while|cout|endl|\;|=|\<\<|\+|\-|\<|\(|\)|\{|\}|[a-zA-Z]\w*|\d+|\".*?\")')

# Judge lexical is keyword or not
def isKeywords(t):
    if t in keyVec:
        return True
    else:
        return False

# Judge lexical is identifier or not
def isIdentifier(t):
    if not isKeywords(t):
        if identifier.match(t):
            return True
    return False

# Judge lexical is number or not
def isDigit(t):
    if number.match(t):
        return True
    return False

# Judge lexical is operator or not
def isOperator(t):
    if t in opeVec:
        return True
    return False

#judge lexical is string or not
def isString(t):
    if string.match(t):
        return True
    return False

# Output
def result(s):
    if isIdentifier(s):
        return "标识符--16" +","+ format(s,'>20')

    if isKeywords(s):
        return "关键字--" + str(keyVec[s])+ "," + format(s,'>20')

    if isDigit(s):
        return "整型常量--17," + format(s,'>20')

    if isOperator(s):
        return opeVec[s]+ "," + format(s,'>20')

    if isString(s):
        return "字符串--18" +","+format(s,'>20')
    return "Error"

#test the py file
if __name__ == '__main__':
    data = '''
        int asd = 0;
        int bc = 10;
        while ( asd < bc )
        {
        if ( bc - asd < 2 )
          	cout << "they are close." << endl;
        asd = asd + 1;
        }
        '''
    s = data.splitlines()
    for m in s:
        m=m.replace(' ','').strip()
        lis = re.split(p,m)
        for n in lis:
                if n == '':     # Go across empty element
                    continue
                print(result(n))



