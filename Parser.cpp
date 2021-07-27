#include<iostream>
#include<conio.h>
#include <sstream> 
#include<fstream>
using namespace std;

typedef enum
{
	LCB, RCB, LB, RB, SEMI, COMM, COLON, PLUS,
	MINUS, DIVIDE, MUL, MOD, DEC, INC, DOUBLEEQUAL, PLUSEQUAL,
	MINUSEQUAL, MULEQUAL, DIVIDEEQUAL, GREATEREQUAL, LESSEQUAL,
	NOTEQUAL, LEFTSHIFT, RIGHTSHIFT, GREATER, LESSER, EQUAL, NUM, ALPHA,
	IF, WHILE, DO, ELSE, FOR, VOID, MAIN, INT, FLOAT, DOUBLE,
	ID, LSB, RSB, COMMENT, BEGIN, END, MODULUS, MODEQUAL, OR, AND, None
} TokenType;

typedef enum { opk, constk, idk } expkind;
typedef enum { ifk, assignk, dok, whilek }stmtkind;
typedef enum { stmtk, expk }nodekind1;

struct treenode
{
	nodekind1 nodek;
	stmtkind stmtk;
	expkind expk;
	TokenType token1;
	int value;
	string name;
	string IDoprVal;
	treenode* leftchild;
	treenode* rightchild;
	treenode* middlechild;
	treenode* sibling;
};

typedef struct variable
{
	TokenType tokenval = ID;
	char * stringval;
	int inumval;
	double doubleval;
	float floatval;
	string variable_name;
	int index;
};
typedef struct TokenRecord
{
	TokenType token;
	string name;
	int val;
	string value;
};
static int index = 0;
variable SymbolTable[100];
TokenRecord record;
ifstream read;
ofstream write;
bool flag = 0;
TokenRecord token;
TokenRecord lexical()
{
	char var;
	while (!read.eof())
	{
		record.name = "";
		read.get(var);
		if (read.eof())
		{
			record.token = END;
			return record;
		}
		if (var == '\n' || var == '\t' || var == ' ')
		{
			continue;
		}
		if (var == '(')
		{
			record.name = "Left Brace";
			record.token = LB;
			record.value = "(";
			return record;

		}
		else if (var == ')')
		{
			record.name = "Right Brace";
			record.token = RB;
			record.value = ")";
			return record;
		}
		else if (var == '{')
		{
			record.name = "Left Curley Bracket";
			record.token = LCB;
			record.value = "{";
			return record;
		}
		else if (var == '}')
		{
			record.name = "Right Curley Brace";
			record.token = RCB;
			record.value = "}";
			return record;
		}
		else if (var == '[')
		{
			record.name = "Left Square Bracket";
			record.token = LSB;
			record.value = "[";
			return record;
		}
		else if (var == ']')
		{
			record.name = "Left Square Brace";
			record.token = RSB;
			record.value = "]";
			return record;
		}
		else if (var == ';')
		{
			record.name = "SemiColon";
			record.token = SEMI;
			record.value = ";";
			return record;
		}
		else if (var == ',')
		{
			record.name = "COMMA";
			record.token = COMM;
			record.value = ",";
			return record;
		}
		else if (var == ':')
		{
			record.name = "Colon";
			record.token = COLON;
			record.value = ":";
			return record;
		}
		else if (var == '|')
		{
			read.get(var);
			if (var == '|')
			{
				record.name = "OR";
				record.token = OR;
				record.value = "|";
				return record;
			}
			else
			{
				read.putback(var);
				record.token = None;
				return record;
			}
		}
		else if (var == '&')
		{
			read.get(var);
			if (var == '&')
			{
				record.name = "AND";
				record.token = AND;
				record.value = "&";
				return record;
			}
			else
			{
				read.putback(var);
				record.token = None;
				return record;
			}
		}

		else if (var == '+')
		{
			read.get(var);
			if (var == '+')
			{
				record.name = "Increment";
				record.token = INC;
				record.value = "++";
				return record;
			}
			else if (var == '=')
			{
				record.name = "Plus Equal";
				record.token = PLUSEQUAL;
				record.value = "+=";
				return record;
			}
			else
			{
				read.putback(var);
				record.name = "Plus";
				record.token = PLUS;
				record.value = "+";
				return record;
			}
		}

		else if (var == '-')
		{
			read.get(var);
			if (var == '-')
			{
				record.name = "Decrement";
				record.token = DEC;
				record.value = "--";
				return record;
			}
			else if (var == '=')
			{
				record.name = "Minus Equal";
				record.token = MINUSEQUAL;
				record.value = "-=";
				return record;
			}
			else
			{
				read.putback(var);
				record.name = "Minus";
				record.token = MINUS;
				record.value = "-";
				return record;
			}
		}

		else if (var == '*')
		{
			read.get(var);
			if (var == '=')
			{
				record.name = "Multiply Equal";
				record.token = MULEQUAL;
				record.value = "*=";
				return record;
			}
			else
			{
				read.putback(var);
				record.name = "Multiply";
				record.token = MUL;
				record.value = "*";
				return record;
			}
		}
		else if (var == '%')
		{
			read.get(var);
			if (var == '=')
			{
				record.name = "Mod Equal";
				record.token = MODEQUAL;
				record.value = "%=";
				return record;
			}
			else
			{
				read.putback(var);
				record.name = "Modulus";
				record.token = MODULUS;
				record.value = "%";
				return record;
			}
		}

		else if (var == '/')
		{
			read.get(var);
			if (var == '=')
			{
				record.name = "Divide Equal";
				record.token = DIVIDEEQUAL;
				record.value = "/=";
				return record;
			}
			else if (var == '/')
			{
				while (var != '\n')
				{
					read.get(var);
				}
				read.putback(var);
				read.get(var);
				record.name = "Comment";
				record.token = COMMENT;
				record.value = "//";
				return record;
			}
			else
			{
				read.putback(var);
				record.name = "Divide";
				record.token = DIVIDE;
				record.value = "/";
				return record;
			}
		}

		else if (var == '>')
		{
			read.get(var);
			if (var == '=')
			{
				record.name = "Great and Equal";
				record.token = GREATEREQUAL;
				record.value = ">=";
				return record;
			}
			else if (var == '>')
			{
				record.name = "Right Shift";
				record.token = RIGHTSHIFT;
				record.value = ">>";
				return record;
			}
			else
			{
				read.putback(var);
				record.name = "Greater";
				record.token = GREATER;
				record.value = ">";
				return record;
			}
		}

		else if (var == '<')
		{
			read.get(var);
			if (var == '=')
			{
				record.name = "Less and Equal";
				record.token = LESSEQUAL;
				record.value = "<=";
				return record;
			}
			else if (var == '<')
			{
				record.name = "Left Shift";
				record.token = LEFTSHIFT;
				record.value = "<<";
				return record;
			}
			else
			{
				read.putback(var);
				record.name = "Lesser";
				record.token = LESSER;
				record.value = "<";
				return record;
			}
		}
		else if (var == '=')
		{
			read.get(var);
			if (var == '=')
			{
				record.name = "Double Equal";
				record.token = DOUBLEEQUAL;
				record.value = "==";
				return record;
			}
			else
			{
				read.putback(var);
				record.name = "Equal";
				record.token = EQUAL;
				record.value = "=";
				return record;
			}
		}
		else if (var == '!')
		{
			read.get(var);
			if (var == '=')
			{
				record.name = "Not Equal";
				record.token = NOTEQUAL;
				record.value = "!=";
				return record;
			}
			else
			{
				read.putback(var);
				record.token = None;
				return record;
			}
		}
		else if (isdigit(var))
		{
			string digit;
			digit = var;
			while (isdigit(var))
			{
				read.get(var);
				if (isdigit(var))
				{
					digit += var;
				}
				else if (!isdigit(var))
				{
					read.putback(var);
					record.name = "Number";
					record.token = NUM;
					istringstream(digit) >> record.val;
					return record;
				}
			}
		}
		else if (isalpha(var) || var == '_')
		{
			bool flag = false;
			bool flag2 = false;
			string character = "";
			string variable = "";
			string value = "";

			do
			{
				character = character + var;
				read.get(var);
			} while (isalpha(var));
			read.putback(var);
			read.get(var);
			if (isdigit(var))
			{
				while (isdigit(var))
				{
					read.get(var);
				}
				flag = true;
			}
			else
			{
				read.putback(var);
			}
			if (character == "BEGIN" && flag == false)
			{
				record.token = BEGIN;
				return record;
			}
			if (character == "END" && flag == false)
			{
				record.token = END;
				return record;
			}
			if (character == "int" && var == ' ' && flag == false)
			{
				read.get(var);
				if ((var >= 'a' && var <= 'z') ||
					(var >= 'A' && var <= 'Z') ||
					(var == '_'))
				{
					read.putback(var);
					while (var != ';')
					{
						read.get(var);
						if ((var >= 'a' && var <= 'z') ||
							(var >= 'A' && var <= 'Z') ||
							(var >= '0' && var <= '9') ||
							(var == '_'))
						{
							variable = variable + var;
						}
						else if (var == ';')
						{
							for (int loop = 0; loop < index; loop++)
							{
								if (SymbolTable[loop].variable_name == variable)
								{
									flag2 = true;
								}
							}
							if (flag2 == false)
							{
								int temp = index;
								SymbolTable[index].variable_name = variable;
								SymbolTable[index].index = temp;
								index++;
								record.token = SymbolTable[temp].tokenval;
								record.name = "INT";
								record.token = INT;
								return record;
							}
						}
						else
						{
							if (var == '=')
							{
								for (int loop = 0; loop < index; loop++)
								{
									if (SymbolTable[loop].variable_name == variable)
									{
										flag2 = true;
									}
								}
								if (flag2 == false)
								{
									int temp = index;
									SymbolTable[index].variable_name = variable;
									SymbolTable[index].index = temp;
									while (var != ';')
									{
										read.get(var);
										if (isdigit(var))
										{
											value = value + var;
										}
										else
										{
											read.putback(var);
											break;
										}
									}
									stringstream int_value(value);
									int temp2 = 0;
									int_value >> temp2;
									SymbolTable[index].inumval = temp2;
								}
							}
							index++;
							record.name = "INT";
							record.token = INT;
							return record;
						}
					}
					read.putback(var);
				}
				else
				{
					SymbolTable[index].inumval = 0;
					SymbolTable[index].variable_name = "NONE";
					record.name = "INT";
					record.token = INT;
					index++;
					return record;
				}

			}
			if (character == "double" && var == ' '&& flag == false)
			{
				read.get(var);
				if ((var >= 'a' && var <= 'z') ||
					(var >= 'A' && var <= 'Z') ||
					(var == '_'))
				{
					read.putback(var);
					while (var != ';')
					{
						read.get(var);
						if ((var >= 'a' && var <= 'z') ||
							(var >= 'A' && var <= 'Z') ||
							(var >= '0' && var <= '9') ||
							(var == '_'))
						{
							variable = variable + var;
						}
						else if (var == ';')
						{
							for (int loop = 0; loop < index; loop++)
							{
								if (SymbolTable[loop].variable_name == variable)
								{
									flag2 = true;
								}
							}
							if (flag2 == false)
							{
								int temp = index;
								SymbolTable[index].variable_name = variable;
								SymbolTable[index].index = temp;
								index++;
								record.name = "DOUBLE";
								record.token = DOUBLE;
								return record;
							}
						}
						else
						{
							if (var == '=')
							{
								for (int loop = 0; loop < index; loop++)
								{
									if (SymbolTable[loop].variable_name == variable)
									{
										flag2 = true;
									}
								}
								if (flag2 == false)
								{
									int temp = index;
									SymbolTable[index].variable_name = variable;
									SymbolTable[index].index = temp;
									record.token = SymbolTable[temp].tokenval;
									while (var != ';')
									{
										read.get(var);
										if (isdigit(var))
										{
											value = value + var;
										}
										else
										{
											read.putback(var);
											break;
										}
									}
									stringstream double_value(value);
									double temp2 = 0;
									double_value >> temp2;
									SymbolTable[index].doubleval = temp2;
								}

							}
							index++;
							record.name = "DOUBLE";
							record.token = DOUBLE;
							return record;
						}
					}
					read.putback(var);
				}
				else
				{
					SymbolTable[index].doubleval = 0.0;
					SymbolTable[index].variable_name = "NONE";
					record.name = "DOUBLE";
					record.token = DOUBLE;
					index++;
					return record;
				}

			}
			if (character == "float" && var == ' '&& flag == false)
			{
				read.get(var);
				if ((var >= 'a' && var <= 'z') ||
					(var >= 'A' && var <= 'Z') ||
					(var == '_'))
				{
					read.putback(var);
					while (var != ';')
					{
						read.get(var);
						if ((var >= 'a' && var <= 'z') ||
							(var >= 'A' && var <= 'Z') ||
							(var >= '0' && var <= '9') ||
							(var == '_'))
						{
							variable = variable + var;
						}
						else if (var == ';')
						{
							for (int loop = 0; loop < index; loop++)
							{
								if (SymbolTable[loop].variable_name == variable)
								{
									flag2 = true;
								}
							}
							if (flag2 == false)
							{
								int temp = index;
								SymbolTable[index].variable_name = variable;
								SymbolTable[index].index = temp;
								index++;
								record.token = SymbolTable[temp].tokenval;
								record.name = "FLOAT";
								record.token = FLOAT;
								return record;
							}
						}
						else
						{
							if (var == '=')
							{
								for (int loop = 0; loop < index; loop++)
								{
									if (SymbolTable[loop].variable_name == variable)
									{
										flag2 = true;
									}
								}
								if (flag2 == false)
								{
									int temp = index;
									SymbolTable[index].variable_name = variable;
									SymbolTable[index].index = temp;
									while (var != ';')
									{
										read.get(var);
										if (isdigit(var))
										{
											value = value + var;
										}
										else
										{
											read.putback(var);
											break;
										}
									}
									stringstream float_value(value);
									float temp2 = 0.0;
									float_value >> temp2;
									SymbolTable[index].floatval = temp2;
								}
							}
							index++;
							record.name = "FLOAT";
							record.token = FLOAT;
							return record;
						}
					}
					read.putback(var);
				}
				else
				{
					SymbolTable[index].floatval = 0.0;
					SymbolTable[index].variable_name = "NONE";
					record.name = "FLOAT";
					record.token = FLOAT;
					index++;
					return record;
				}
			}
			if (character == "if" && flag == false)
			{
				record.name = "IF";
				record.token = IF;
				return record;
			}
			if (character == "while" &&  flag == false)
			{
				record.name = "WHILE";
				record.token = WHILE;
				return record;
			}
			if (character == "do" &&  flag == false)
			{
				record.name = "DO";
				record.token = DO;
				return record;
			}
			if (character == "else" &&  flag == false)
			{
				record.name = "ELSE";
				record.token = ELSE;
				return record;
			}
			if (character == "for" &&  flag == false)
			{
				record.name = "FOR";
				record.token = FOR;
				return record;
			}
			if (character == "void" &&  flag == false)
			{
				record.name = "VOID";
				record.token = VOID;
				return record;
			}
			if (character == "main" && var == ' '&& flag == false)
			{
				record.name = "MAIN";
				record.token = MAIN;
				return record;
			}
			else
			{
				for (int loop = 0; loop < index; loop++)
				{
					if (SymbolTable[loop].variable_name == character)
					{
						flag2 = true;
						record.token = SymbolTable[loop].tokenval;
						record.name = "IDENTIFIER";
						record.value = SymbolTable[loop].variable_name;
						return record;
					}
				}
				if (flag2 == false)
				{
					int temp = index;
					SymbolTable[index].variable_name = character;
					SymbolTable[index].index = temp;
					index++;
					record.token = SymbolTable[temp].tokenval;
					record.name = "IDENTIFIER";
					record.value = SymbolTable[temp].variable_name;
					return record;
				}


			}
		}


		record.token = None;
		return record;

	}
}
TokenRecord current_token;
void ungettoken()
{
	flag = 1;
}
TokenRecord gettoken()
{
	if (flag == 0)
	{

		current_token = lexical();
		return current_token;

	}
	else
	{
		flag = 0;
		return current_token;
	}
}
treenode* expr();
treenode* term();
treenode* factor();
treenode* statement();
treenode* statement_list();
bool program();
void display(struct treenode*);
void main()
{
	read.open("Input.txt");

	if (program() == true)
	{
		cout << "Successful" << endl;
	}
	else
	{
		cout << "Unsuccessful" << endl;
	}

	read.close();
	_getch();
}
treenode* expr()
{
	treenode*t = NULL, *p = NULL;
	int flag = 0;
	do
	{
		t = term();
		if (flag)
		{
			p->rightchild = t;
			flag = 0;
			t = p;
		}
		token = gettoken();
		if (token.token == PLUS || token.token == MINUS)
		{
			p = new treenode();
			p->nodek = expk;
			p->expk = opk;
			p->token1 = token.token;
			p->leftchild = t;
			p->IDoprVal = token.value;
			flag = 1;
		}
	} while (token.token == PLUS || token.token == MINUS);
	ungettoken();
	return (t);
}
treenode* term()
{
	treenode*t = NULL, *p = NULL;
	int flag = 0;
	do
	{
		t = factor();
		if (flag)
		{
			p->rightchild = t;
			flag = 0;
			t = p;
		}
		token = gettoken();
		if (token.token == MUL || token.token == DIVIDE || token.token == MODULUS)
		{
			p = new treenode();
			p->nodek = expk;
			p->expk = opk;
			p->token1 = token.token;
			p->leftchild = t;
			p->IDoprVal = token.value;
			flag = 1;
		}
	} while (token.token == MUL || token.token == DIVIDE || token.token == MODULUS);
	ungettoken();
	return (t);
}
treenode* factor()
{
	treenode*t = NULL;
	TokenRecord previous_token = current_token;
	TokenRecord token = gettoken();
	switch (token.token)
	{
	case NUM:
		t = new treenode();
		t->nodek = expk;
		t->expk = constk;
		t->value = token.val;
		t->leftchild = NULL;
		t->rightchild = NULL;
		return(t);
	case ID:
		t = new treenode();
		t->nodek = expk;
		t->expk = idk;
		t->name = token.name;
		t->IDoprVal = token.value;
		t->leftchild = NULL;
		t->rightchild = NULL;
	case LB:
	{
		return(t);
	}
	case None:
	{
		ungettoken();
	}
	default:
		ungettoken();
	}
}
treenode* statement()
{
	treenode *t1 = NULL;
	treenode *tree = NULL;
	treenode *tree1 = NULL;

	int r = 0;
	token = gettoken();
	if (token.token == ID)
	{
		tree1 = new treenode;  // node for statement
		tree1->leftchild = NULL;
		tree1->rightchild = NULL;
		tree1->value = NULL;
		tree1->nodek = stmtk;
		tree1->stmtk = assignk;
		tree1->IDoprVal = token.value;
		tree1->token1 = ID;
		token = gettoken();
		if (token.token == EQUAL)
		{
			tree = new treenode;  // node for statement
			tree->leftchild = NULL;
			tree->rightchild = NULL;
			tree->value = NULL;
			tree->nodek = expk;
			tree->expk = opk;
			tree->token1 = EQUAL;
			tree->IDoprVal = token.value;
			tree1->leftchild = tree;
			if (t1 = expr())
			{
				tree1->leftchild->leftchild = t1;
				token = gettoken();
				if (token.token == SEMI)
					return  (tree1);

			}
		}
	}
}
treenode* statement_list()  // statement list 
{
	treenode *stree = NULL;
	treenode *prevtree = NULL;
	treenode *stmttree = NULL;
	if (prevtree = statement())
	{
		prevtree->sibling = NULL;
		stmttree = prevtree;
		stmttree->sibling = NULL;
		do
		{
			token = gettoken();
			if (token.token == IF || token.token == DO || token.token == ID)
			{
				ungettoken();
				if ((stree = statement()) == NULL)   // NOT TRUE
					return NULL;

				stree->sibling = NULL;
				prevtree->sibling = stree;
				prevtree = stree;
			}
			else
			{
				ungettoken();
				break;
			}

		} while (1);
		//return true; // if , not, uid not equal then may be else
		return (stmttree);
	}
	return NULL; //otherwise false

}
bool program()
{
	treenode *fulltree;
	token = gettoken();
	if (token.token == BEGIN)
	{
		if ((fulltree = statement_list()) != NULL)
		{
			display(fulltree);
			token = gettoken();
			if (token.token == END)
				return true;
		}
	}
	return false;

}
void display(struct treenode* node)
{
	if (node == NULL)
	{
		return;
	}
	display(node->leftchild);
	if (node->value != NULL)
	{
		cout << node->value << " ";
	}
	else
	{
		cout << node->IDoprVal << " ";
	}
	display(node->rightchild);

}
