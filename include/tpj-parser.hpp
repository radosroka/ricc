/**
 * Library interface
 */

#pragma once

#include <iostream>
#include <memory>

namespace TPJparser {

    class ParserPrivate;
    class Parser {
        public:
            Parser(std::istream& stream);
            ~Parser();
            void Run();

        private:
            std::unique_ptr<ParserPrivate> _d_pointer;
    };

}
