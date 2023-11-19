/* Header for SchemaXml class
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

#include <map>
#include <unordered_map>
#include "../common/Ctx.h"
#include "../common/XdbXNm.h"
#include "../common/XdbXQn.h"
#include "../common/XdbXPt.h"
#include "../common/typeRowId.h"
#include "../common/types.h"

#ifndef SCHEMA_XML_H_
#define SCHEMA_XML_H_

namespace OpenLogReplicator {

class SchemaXml final {
public:
    // XDB.X$NMxxx
    std::map<typeRowId, XdbXNm*> xdbXNmMapRowId;
    std::unordered_map<std::string, XdbXNm*> xdbXNmMapId;

    // XDB.X$QNxxx
    std::map<typeRowId, XdbXQn*> xdbXQnMapRowId;
    std::unordered_map<std::string, XdbXQn*> xdbXQnMapId;

    // XDB.X$PTxxx
    std::map<typeRowId, XdbXPt*> xdbXPtMapRowId;
    std::unordered_map<std::string, XdbXPt*> xdbXPtMapId;

    Ctx* ctx;
    std::string tokSuf;

    SchemaXml(Ctx* newCtx, const std::string& newTokSuf);
    virtual ~SchemaXml();

    void purgeDicts();

    XdbXNm* dictXdbXNmFind(typeRowId rowId);
    XdbXPt* dictXdbXPtFind(typeRowId rowId);
    XdbXQn* dictXdbXQnFind(typeRowId rowId);

    void dictXdbXNmAdd(XdbXNm* xdbXNm);
    void dictXdbXPtAdd(XdbXPt* xdbXPt);
    void dictXdbXQnAdd(XdbXQn* xdbXQn);

    void dictXdbXNmDrop(XdbXNm* xdbXNm);
    void dictXdbXPtDrop(XdbXPt* xdbXPt);
    void dictXdbXQnDrop(XdbXQn* xdbXQn);
};

}
#endif
