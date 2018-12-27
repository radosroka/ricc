#pragma once

#define SYNTAX_OK 0
#define SYNTAX_ERROR 2
#define EXPRESSION_ERROR 3

#include <iostream>

#include "interpret/Interpret.hpp"
#include "lex/Lex.hpp"
#include "lex/Token.hpp"
#include "semantic/Semantic.hpp"

namespace TPJparser {

    class Syntax {
        public:

            enum nonTerminals {
                START = 100,
                FUNCTIONS,
                FUNCTIONS_CONT,
                FUNCDECL,
                TAIL,
                HEAD ,
                DECL,
                ARGUMENTS,
                ARGUMENTS_N,
                BODY,
                CONTSTMNT,
                STATEMENT,
                STATEMENTS,
                STATEMENTBODY,
                VARIABLEDEF,
                VARS,
                ASSIGN,
                IFSTMNT,
                ELSEBODY,
                LOOPSTATEMENTS,
                WHILESTMT,
                FORSTMT,
                RETURNSTMT,
                ASSIGNMENT,
                OPERATION,
                TYPE,
                NAME,
                FUNCTIONCALL,
                PARAMETERS,
                PARAMETERS_N,
            };

            static std::map<nonTerminals, std::string> nonTerminalsMap;
            //std::string getName(int nonterminal);

            Syntax(std::istream& stream);
            int Parse();
            int ParseExpression();

            Lex& getLex();
            Interpret::Interpret& getIntepreter();

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

            static constexpr const size_t sizeOfLongRule = sizeof(Syntax::longRules[0]);
            static constexpr const size_t numberOfLongRules = sizeof(Syntax::longRules) / Syntax::sizeOfLongRule;

            static constexpr const size_t sizeOfShortRule  = sizeof(Syntax::shortRules[0]);
            static constexpr const size_t numberOfShortRules = sizeof(Syntax::shortRules) / Syntax::sizeOfShortRule;

        private:
            int parseSyntax(int nonTerminal);

            int reduceStack();
            void visualizeStack();
            Token& getFirstTerminalFromTop();
            void putShiftToken(Token& terminal);

            bool isDefined(const std::string& name, SymbolTableItem::Kind);

            void genLongOperation(size_t index);
            void genShortOperation(size_t index);

            Lex _lex;
            Interpret::Interpret _interpret;
            Semantic::Scope _scope;
            std::stack<std::reference_wrapper<Token>> _tokenStack;
    };
}
