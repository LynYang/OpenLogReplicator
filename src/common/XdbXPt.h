/* Definition of schema XDB.X$PTxxx
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

#include "types.h"
#include "typeRowId.h"

#ifndef XDB_XPT_H_
#define XDB_XPT_H_

#define XDB_XPT_PATH_LENGTH 2000
#define XDB_XPT_ID_LENGTH 16

namespace OpenLogReplicator {
    class XdbXPt final {
    public:
        XdbXPt(typeRowId& newRowId, const char* newPath, const char* newId) :
                rowId(newRowId),
                path(newPath),
                id(newId) {
        }

        bool operator!=(const XdbXPt& other) const {
            return (other.rowId != rowId) || (other.path != path) || (other.id != id);
        }

        typeRowId rowId;
        std::string path;
        std::string id;
    };
}

#endif
