
===========================================================================

<h2>[UPDATES]: This code can now:</h2>
<ul>
  <li>Parse the varaiable block + variable declaration</li>
  <li>Parse the code block + some statement</li>
  <li>Parse the Number + String Literals</li>
  <li>Parse the ConsoleWrite(PRT) Statment</li>
  <li>Detect unexpected syntax</li>
</ul>
  
===========================================================================

<h1>Facile</h1>

#EBNF for facile language <br/>

Program ::= Block <br/>
Block ::= variable { Declaration } | code { Statement } <br/>
	Declaration ::= DataType { VariableName }; <br/>
		DataType ::= {INT | BLN | STG} <br/>
		VariableName ::= 0-9 | aA-zZ | _ <br/>
	Statement ::= Assignment | ConsoleWrite | ConsoleRead <br/>
		Assignment ::= PUT { Expression | String | Literals | Variable } INTO { Variable }; <br/>
		Expression ::= Expression | Operation | ParenthesizedExpression <br/>
			Operation ::=  ADD { Expression, Expression } 	| <br/> 
					SUB { Expression, Expression } 	| <br/>
					MUL { Expression, Expression }	| <br/>
					DIV { Expression, Expression }	| <br/>
					MOD { Expression, Expression }	| <br/>
					GRT { Expression, Expression }	| <br/>
					GRE { Expression, Expression }	| <br/>
					LET { Expression, Expression }	| <br/>
					LEE { Expression, Expression }	| <br/>
					EQL { Expression, Expression }	| <br/>
					AND { Expression, Expression }	| <br/>
					OR  { Expression, Expression }	| <br/>
					NON { Expression } <br/>
			ParenthesizedExpression ::= Expression <br/>
		String ::= ${Literals}$ <br/>
		Literals ::= 0-9 | aA-zZ | true | false <br/>
	ConsoleWrite ::= PRT { Expression | String | Literals | Variable }; <br/>
	ConsoleRead ::= ASK { Variable }; <br/>

<br/>
#Set Of Firsts <br/>

first(Assignment) = {PUT} <br/>
first(Declaration) = {DataType} <br/>
first(ConsoleRead) = {ASK} <br/>
first(Statement) = {Assignment} U {ConsoleWrite} U {ConsoleRead} <br/>

===========================================================================
	
