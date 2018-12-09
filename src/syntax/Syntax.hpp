#pragma once

#include <iostream>

#include "SymbolTable.hpp"
#include "lex/Lex.hpp"

namespace TPJparser {

    class Syntax {
        public:
            Syntax(std::istream& stream);
            int Parse();
            int ParseExpression();

            Lex& getLex();

            enum Operations {
                S,    // SHIFT
                R,    // REDUCE
                H,    // ??
                E,    // ERROR
            };

            static Token ImplicitToken;
            static Token ShiftToken;
            static Token ReduceToken;

            static const int SIZE_OF_PRECEDENCE_TABLE = 19;
            static const enum Operations precedence_table[SIZE_OF_PRECEDENCE_TABLE][SIZE_OF_PRECEDENCE_TABLE];
            static const Token::tokenType longRules[14][3];
            static const Token::tokenType shortRules[3][2];

        private:
            int reduceStack();
            void visualizeStack();
            Token& getFirstTerminalFromTop();
            void putShiftToken(Token& terminal);

            Lex _lex;

            std::stack<SymbolTable> _tableStack;
            std::stack<std::reference_wrapper<Token>> _tokenStack;
    };
}
