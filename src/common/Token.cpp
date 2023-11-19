/* Token for parsing of expressions
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

#include "Expression.h"
#include "RuntimeException.h"
#include "Token.h"

namespace OpenLogReplicator {
    void Token::buildTokens(const std::string &condition, std::vector<Token> &tokens) {
        uint64_t tokenType = TOKEN_TYPE_NONE;
        uint64_t tokenIndex = 0;

        uint64_t i = 0;
        while (i < condition.length()) {
            switch (tokenType) {
                case TOKEN_TYPE_NONE:
                    if (condition[i] == ' ' || condition[i] == '\t' || condition[i] == '\n' || condition[i] == '\r') {
                        ++i;
                        continue;
                    } else if (condition[i] == '(' || condition[i] == ')') {
                        tokenType = TOKEN_TYPE_PARENTHESIS;
                        tokenIndex = i++;
                        continue;
                    } else if (condition[i] == ',') {
                        tokenType = TOKEN_TYPE_COMMA;
                        tokenIndex = i++;
                        continue;
                    } else if (condition[i] >= 'a' && condition[i] <= 'z') {
                        tokenType = TOKEN_TYPE_NAME;
                        tokenIndex = i++;
                        continue;
                    } else if (condition[i] == '|' || condition[i] == '&' || condition[i] == '!' || condition[i] == '=') {
                        tokenType = TOKEN_TYPE_OPERATOR;
                        tokenIndex = i++;
                        continue;
                    } else if ((condition[i] >= '0' && condition[i] <= '9') || condition[i] == '.') {
                        tokenType = TOKEN_TYPE_NUMBER;
                        tokenIndex = i++;
                        continue;
                    } else if (condition[i] == '\'') {
                        tokenType = TOKEN_TYPE_STRING;
                        tokenIndex = i++;
                        continue;
                    }
                    throw RuntimeException(50002, "invalid condition: " + condition);

                case TOKEN_TYPE_NAME:
                    if ((condition[i] >= 'a' && condition[i] <= 'z') || condition[i] == '_' || (condition[i] >= '0' && condition[i] <= '9')) {
                        ++i;
                        continue;
                    } else if (condition[i] == '.')
                        throw RuntimeException(50002, "invalid condition: " + condition);

                    tokens.push_back(Token(tokenType, condition.substr(tokenIndex, i - tokenIndex)));
                    tokenType = TOKEN_TYPE_NONE;
                    continue;

                case TOKEN_TYPE_PARENTHESIS:
                    tokens.push_back(Token(tokenType, condition.substr(tokenIndex, i - tokenIndex)));
                    tokenType = TOKEN_TYPE_NONE;
                    continue;

                case TOKEN_TYPE_COMMA:
                    tokens.push_back(Token(tokenType, condition.substr(tokenIndex, i - tokenIndex)));
                    tokenType = TOKEN_TYPE_NONE;
                    continue;

                case TOKEN_TYPE_OPERATOR:
                    if (condition[i] == '|' || condition[i] == '&' || condition[i] == '!' || condition[i] == '=') {
                        ++i;
                        continue;
                    }

                    tokens.push_back(Token(tokenType, condition.substr(tokenIndex, i - tokenIndex)));
                    tokenType = TOKEN_TYPE_NONE;
                    continue;

                case TOKEN_TYPE_STRING:
                    if (condition[i] != '\'') {
                        ++i;
                        continue;
                    }

                    // ends with apostrophe
                    ++i;
                    tokens.push_back(Token(tokenType, condition.substr(tokenIndex, i - tokenIndex)));
                    tokenType = TOKEN_TYPE_NONE;
                    continue;

                case TOKEN_TYPE_NUMBER:
                    if ((condition[i] >= '0' && condition[i] <= '9') || condition[i] == '.' || condition[i] == 'e' || condition[i] == 'E') {
                        ++i;
                        continue;
                    } else if ((condition[i] >= 'a' && condition[i] <= 'z') || condition[i] == '_')
                        throw RuntimeException(50002, "invalid condition: " + condition);

                    tokens.push_back(Token(tokenType, condition.substr(tokenIndex, i - tokenIndex)));
                    tokenType = TOKEN_TYPE_NONE;
                    continue;
            }
        }

        // Reached end and the token is not finished
        if (tokenType == TOKEN_TYPE_STRING)
            throw RuntimeException(50002, "invalid condition: " + condition);
        else if (tokenType != TOKEN_TYPE_NONE) {
            tokens.push_back(Token(tokenType, condition.substr(tokenIndex, i - tokenIndex)));
        }
    }

    void Token::buildExpression(std::vector<Token>& tokens, Expression& expression) {
        // ((((((1 + 1) + 1) + 1) + 1) + 1)
        // 1 + (1 + (1 + (1 + (1 + 1))))
        //((1 + 1) + (1 + 1)) + ((1 + 1) + (1 + 1))

        uint64_t i = 0;
        while ( i < tokens.size()) {
            Token& token = tokens[i];
            std::cerr << "token: " << token.value << std::endl;
            // ...
            ++i;
        }
    }

    Token::Token(uint64_t newTokenType, const std::string& newValue) :
        tokenType(newTokenType),
        value(newValue) {
    }

    Token::~Token() {
    }

    Token::Token(const Token& other) :
            tokenType(other.tokenType),
            value(other.value) {
    }

    Token& Token::operator=(const Token& other) {
        if (this == &other)
            return *this;

        tokenType = other.tokenType;
        value = other.value;
        return *this;
    }
}
