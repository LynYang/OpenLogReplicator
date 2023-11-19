/* Definition of a token
   Copyright (C) 2018-2023 Adam Leszczynski (aleszczynski@bersler.com)

This file is part of OpenLogReplicator.

OpenLogReplicator is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License as published
by the Free Software Foundation; either version 3, or (at your option)
any later version.

OpenLogReplicator is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
Public License for more details.

You should have received a copy of the GNU General Public License
along with OpenLogReplicator; see the file LICENSE;  If not see
<http://www.gnu.org/licenses/>.  */

#include <unordered_map>
#include <vector>

#include "types.h"

#ifndef TOKEN_H_
#define TOKEN_H_

#define TOKEN_TYPE_NONE             0
#define TOKEN_TYPE_TRUE             1
#define TOKEN_TYPE_FALSE            2
#define TOKEN_TYPE_NAME             3
#define TOKEN_TYPE_PARENTHESIS      4
#define TOKEN_TYPE_COMMA            5
#define TOKEN_TYPE_OPERATOR         6
#define TOKEN_TYPE_STRING           7
#define TOKEN_TYPE_NUMBER           8

namespace OpenLogReplicator {
    class Expression;

    class Token final {
    public:
        static void buildTokens(const std::string& condition, std::vector<Token>& tokens);
        static void buildExpression(std::vector<Token>& tokens, Expression& expression);

        uint64_t tokenType;
        std::string value;

        Token(uint64_t newTokenType, const std::string& newValue);
        virtual ~Token();

        Token(const Token& other);
        Token& operator=(const Token& other);
    };
}

#endif
