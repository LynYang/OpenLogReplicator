/* Definition of an expression
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

#ifndef EXPRESSION_H_
#define EXPRESSION_H_

namespace OpenLogReplicator {
    class Expression {
    public:
        uint64_t tokenType;
        std::string value;
        Expression* left;
        Expression* right;

        Expression(uint64_t newTokenType, const std::string& newValue);
        Expression();
        virtual ~Expression();

        virtual bool isTrue(char operation, std::unordered_map<std::string, std::string> attributes) const;
    };
}

#endif
