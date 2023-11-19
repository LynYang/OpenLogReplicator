/* Expression for evaluating filter
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
#include "Token.h"

namespace OpenLogReplicator {
    Expression::Expression(uint64_t newTokenType, const std::string& newValue) {
        tokenType = newTokenType;
        value = newValue;
        left = nullptr;
        right = nullptr;
    }

    Expression::Expression() {
        tokenType = TOKEN_TYPE_TRUE;
        value = "";
        left = nullptr;
        right = nullptr;
    }

    Expression::~Expression() {
    }

    bool Expression::isTrue(char operation, std::unordered_map<std::string, std::string> attributes) const {


        return true;
    }
}
