#include "parser.h"

terminal Parser::nextToken()   // read the text input
{
	std::string word;
	this->inputFile >> word;
	

	if (word == "id")
		return terminal(0);
	else if (word == "+")
		return terminal(1);
	else if (word == "*")
		return terminal(2);
	else if (word == "(")
		return terminal(3);
	else if (word == ")")
		return terminal(4);
	else if (word == "e")
		return terminal(6);

	return terminal(5);
}


void Parser::printLM()  // ptint id□|□T_□E_□\n using print symbol
{
	
	for (vector<Symbol>::iterator it = accepted.begin(); it != accepted.end(); ++it ) { 
		it->printSymbol();
	}
	std::cout << "| ";
	for (vector<Symbol>::reverse_iterator it = stack.rbegin(); it != stack.rend() -1; ++it ) { 
		it->printSymbol();
	}
	std::cout << std::endl;
} 




void Parser::parse()  // 90% of this function is based on class 5 parser.pdf
{
	terminal a = this->nextToken();

	stack.push_back(Symbol(terminal(5), TERM));
	stack.push_back(Symbol(nonTerminal(0), NONTERM));
	Symbol X = stack.back();


	while (X.getSymbol() != terminal(5))
	{


		if (X.getType() == TERM && X.getSymbol() == static_cast<int>(a)) // if we have match
		{
			printLM();
			accepted.push_back(X);
			stack.pop_back();
			a = this->nextToken();
		}

		else if (X.getSymbol() == terminal(6)) // if symbol is epsilon need to pop stack
		{
			stack.pop_back();
		}
		else if (X.getType() == TERM) // if its terminal but not epsilon and not macth . this means error
		{
			printLM();
			std::cout << "syntax error" << std::endl;
			return;
		}
		else if (table.at(X.getSymbol()).at(static_cast<int>(a)) == -1) // if we see in table -1 we have no rule . this means error
		{
			printLM();
			std::cout << "syntax error" << std::endl;
			return;
		}
		else   // if we see in table int !=-1 we have valid rule 
		{
    		printLM();
      		stack.pop_back();
      		int index = table[X.getSymbol()][int(a)];

      		for (std::vector < Symbol > ::iterator it = rules[index].begin(); it != rules[index].end(); ++it)
			{
  
         		stack.push_back( * it);
	    	}
		}
		X = stack.back();
	}
	printLM();
}
