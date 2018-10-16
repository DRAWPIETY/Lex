#--------------------------------------------------------
# 1.py
#
# Lexixal analysis 
#-------------------------------------------------------
import ply.lex as lex

# List of token names. This is always required
tokens =[
	'ID',
	'EQUAL',
	'NUMBER',
	'LPAREN',
	'RPAREN',
	'MINUS',
	'LESS',
	'STREAM',
	'STRING',
	'LKUAI',
	'RKUAI',
	'PLUS',
]

reserved = {
	'int' : 'INT',
	'if' : 'IF',
	'while' : 'WHILE',
	'cout' : 'COUT',
	'endl' : 'ENDL',
}

tokens = tokens + list(reserved.values())

# Regular expression rules for simple tokens
t_INT = r'int'
t_EQUAL =  r'='
t_LPAREN = r'\('
t_RPAREN = r'\)'
t_MINUS = r'-'
t_LESS = r'\<'
t_STREAM = r'\<\<'
t_LKUAI = r'\{'
t_RKUAI = r'\}'
t_PLUS = r'\+'

# A regular ecxpression rule with some action code 
def t_NUMBER(t):
	r'\d+'
	t.value = int(t.value)
	return t

def t_ID(t):
	r'[a-zA-Z]\w*'
	t.type = reserved.get(t.value,'ID')
	return t

def t_STRING(t):
	r'\".*?\"'
	return t 
# Define a rule so we can track line numbers
def t_newline(t):
	r'\n'
	t.lexer.lineno += len(t.value)

# A string containing ignored characters (space and tabs and ;)
t_ignore = ' ;\t'

# Error handing rule
def t_error(t):
	print "Illegal character '%s'" % t.value[0]
	t.lexer.skip(1)
# Build the lexer
lexer = lex.lex()

# Test it out
data = '''
int asd = 0;
int bc = 10;
while ( asd < bs)
{
	if(bc - asd < 2)
		cout<<"they are close."<<endl;
	asd = asd + 1;
}
'''
# Give the lexer some input
lexer.input(data)
# Tokenize
while True:
	tok = lexer.token()
	if not tok: break # No more input
	print tok
