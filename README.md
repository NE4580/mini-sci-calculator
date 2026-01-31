This started as simple program, whose purpose was to make a lexer to use for a simple calculater. But on thing lead to another, soo. I try make a full
basic calculater.

1. Basic lexer

2. Added a parser: it works, but...
    a. computes next index manually line: 27| 53

	size_t nextTokenIndex = (current + 1 < tokens.size()) ? current + 1 : 0;

    so three things things reason about position
    current, peek(), nextTokenIndex

    b. Advances twice blindly in expression():line 32 and term()

    c. uses if where gramma needs repetition, in expression and term, line 30(expression)

    d. treats ) like a value in factor and never consumes the used tokens

    e. multiple funtions control cursor expression(), term() and factor()
commit explains updates from this point on.
 ### Text
 This is not a permanent readme file

