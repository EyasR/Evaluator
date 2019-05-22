// University of Washington Bothell - CSSE
// CSS342C : Proffesor Munehiro Fukuda
// Created by Eyas Rashid on 3/10/2019
//
// Program 6  : Stack and Compulers
// Purpose: extends the features of the textbook's calculator example
// implementing unary operators and the operato=  and handling
// three variables a, b, and, c.

// Public routine that performs the evaluation. Examines the postfix machine
// to see if a single result is left and if so, return it; otherwise prints
// error.
template<class NumericType>
NumericType Evaluator<NumericType>::getValue( ) {

  Tokenizer<NumericType> tok( str );
  Token<NumericType> lastToken;
  
  do {
    lastToken = tok.getToken( );
    processToken( lastToken );

  } while ( lastToken.getType( ) != EOL );

  if ( postFixStack.empty( ) ) {
    cerr << "Missing operand!" << endl;
    return 0;
  }

  NumericType theResult = postFixStack.back( );
  postFixStack.pop_back( );

  if ( !postFixStack.empty( ) )
    cerr << "Warning: missing operators!" << endl;
  
  return theResult;
}

// After token is read, use operator precedence parsing algorithm to process
// it; missing opening parentheses are detected here.
template<class NumericType>
void Evaluator<NumericType>::
processToken( const Token<NumericType> &lastToken ) {
  TokenType topOp;
  TokenType lastType = lastToken.getType( );

  switch( lastType ) {
  case VALUE:
    postFixVarStack.push_back(' ');
    postFixStack.push_back( lastToken.getValue( ) );
    return;

  case VAR_A:
      postFixVarStack.push_back('a');
      postFixStack.push_back(var_a);
      return;

  case VAR_B:
      postFixVarStack.push_back('b');
      postFixStack.push_back(var_b);
      return;

  case VAR_C:
      postFixVarStack.push_back('c');
      postFixStack.push_back(var_c);
      return;

  case CPAREN:
    while( ( topOp = opStack.back( ) ) != OPAREN &&
	   topOp != EOL )

        if(topOp == UN_PLUS ){
            unaryOp( topOp);

        }else if (topOp == UN_MINUS){
            unaryOp( topOp);

        }else if (topOp == BIT_COMP){
            unaryOp( topOp);

        }else if (topOp == NOT){
            unaryOp( topOp);

        }else{
            binaryOp( topOp );

        }

    if ( topOp == OPAREN ){
        opStack.pop_back( ); // get rid of opening parenthesis
    }else
      cerr << "Missing open parenthesis" << endl;
    break;

  default: // general operator case
    while ( PREC_TABLE[ lastType ].inputSymbol <= 
	    PREC_TABLE[ topOp = opStack.back( ) ].topOfStack )

        // if topOp is a urinary operator
        if (topOp == UN_PLUS || topOp == UN_MINUS || topOp == BIT_COMP || topOp == NOT ){
          unaryOp( topOp );

        } else {
          binaryOp(topOp);

        }


    if ( lastToken.getType( ) != EOL )
      opStack.push_back( lastType );

    break;
  }
}

// Process an operator by taking two items off the postfix stack, applying
// the operator, and pushing the result.
// Print error if missing closing parenthesis or division by 0.
template<class NumericType>
void Evaluator<NumericType>::binaryOp( TokenType topOp ) {
  if ( topOp == OPAREN ) {
    cerr << "Unbalanced parenthss" << endl;
    opStack.pop_back( );
    return;
  }

  NumericType rhs = getTop( );
  NumericType lhs = getTop( );
  postFixVarStack.pop_back();
  char var = getTopVar();

  // the original operators
  if ( topOp == PLUS ){
      postFixVarStack.push_back( ' ' );
      postFixStack.push_back( lhs + rhs );

  } else if ( topOp == MINUS ) {
      postFixVarStack.push_back( ' ' );
      postFixStack.push_back( lhs - rhs );

  } else if ( topOp == MULT ){
      postFixVarStack.push_back( ' ' );
      postFixStack.push_back( lhs * rhs );

  } else if ( topOp == DIV )

      if ( rhs != 0 ){
        postFixVarStack.push_back( ' ' );
        postFixStack.push_back( lhs / rhs );

      } else {
        cerr << "Division by zero" << endl;
        postFixVarStack.push_back( ' ' );
        postFixStack.push_back( lhs );

      }

  // C++ operators
  else if ( topOp == MODULUS ){
      postFixVarStack.push_back( ' ' );
      postFixStack.push_back( lhs % rhs );

  } else if ( topOp == SHIFT_L ){
      postFixVarStack.push_back( ' ' );
      postFixStack.push_back( lhs << rhs );

  } else if ( topOp == SHIFT_R ){
      postFixVarStack.push_back( ' ' );
      postFixStack.push_back( lhs >> rhs );

  } else if ( topOp == LT ){
      postFixVarStack.push_back( ' ' );
      postFixStack.push_back( lhs < rhs );

  } else if ( topOp == LE ){
      postFixVarStack.push_back( ' ' );
      postFixStack.push_back( lhs <= rhs );

  } else if ( topOp == GT ){
      postFixVarStack.push_back( ' ' );
      postFixStack.push_back( lhs > rhs );

  } else if ( topOp == GE ){
      postFixVarStack.push_back( ' ' );
      postFixStack.push_back( lhs >= rhs );

  } else if ( topOp == EQUAL ) {
      postFixVarStack.push_back( ' ' );
      postFixStack.push_back( lhs == rhs );

  } else if ( topOp == NOTEQUAL ){
      postFixVarStack.push_back( ' ' );
      postFixStack.push_back( lhs != rhs );

  } else if ( topOp == BIT_AND ){
      postFixVarStack.push_back( ' ' );
      postFixStack.push_back( lhs & rhs );

  } else if ( topOp == BIT_EOR ){
      postFixVarStack.push_back( ' ' );
      postFixStack.push_back( lhs ^ rhs );

  } else if ( topOp == BIT_IOR ){
      postFixVarStack.push_back( ' ' );
      postFixStack.push_back( lhs | rhs );

  } else if ( topOp == LOG_AND ){
      postFixVarStack.push_back( ' ' );
      postFixStack.push_back( lhs && rhs );

  } else if ( topOp == LOG_OR ){
      postFixVarStack.push_back( ' ' );
      postFixStack.push_back( lhs || rhs );

  } else if ( topOp == ASGN ){

      switch (var){
          case 'a':
            var_a = rhs;

          case 'b':
            var_b = rhs;

          case 'c':
            var_c = rhs;
      }

      postFixStack.push_back(rhs);
      postFixVarStack.push_back(' ');
  }
  opStack.pop_back( );

}

// unary operations
template<class NumericType>
void Evaluator<NumericType>::unaryOp(TokenType topOp) {
    if ( topOp == OPAREN ) {
        cerr << "Unbalanced parenthesis" << endl;
        opStack.pop_back( );
        return;
    }

    NumericType lhs = getTop();

    postFixVarStack.pop_back();

    if ( topOp == UN_PLUS ){
        postFixVarStack.push_back( ' ' );
        postFixStack.push_back( lhs );

    }else if ( topOp == UN_MINUS ){
        postFixVarStack.push_back( ' ' );
        postFixStack.push_back( ((-1) * lhs) );

    }else if ( topOp == BIT_COMP ){
        postFixVarStack.push_back( ' ' );
        postFixStack.push_back( ~lhs );

    }else if ( topOp == NOT ){
          postFixVarStack.push_back( ' ' );
          postFixStack.push_back( !lhs );
    }
    opStack.pop_back( );
}


// top and pop the postfix machine stack; return the result.
// If the stack is empty, print an error message.
template<class NumericType>
NumericType Evaluator<NumericType>::getTop( ) {
  if ( postFixStack.empty( ) ) {
    cerr << "Missing operand" << endl;
    return 0;
  }

  NumericType tmp = postFixStack.back( );
  postFixStack.pop_back( );
  return tmp;
}

// get top and pop the postFixVar machine stack, return the results
// if the stack is empty, print an error message.
template<class NumericType>
char Evaluator<NumericType>::getTopVar( ) {
    if ( postFixVarStack.empty( ) ) {
        cerr << "Missing operand from Var Stack" << endl;
        return 0;
    }

    char tmp = postFixVarStack.back( );
    postFixVarStack.pop_back( );
    return tmp;
}
