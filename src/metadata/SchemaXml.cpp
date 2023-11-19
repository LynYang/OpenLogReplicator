/* Base class for storing xmltype data
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

#include "SchemaXml.h"

namespace OpenLogReplicator {
    SchemaXml::SchemaXml(Ctx* newCtx, const std::string& newTokSuf) :
            ctx(newCtx),
            tokSuf(newTokSuf) {
    }

    SchemaXml::~SchemaXml() {
        purgeDicts();
    }

    void SchemaXml::purgeDicts() {
        while (!xdbXNmMapRowId.empty()) {
            auto xdbXNmMapRowIdIt = xdbXNmMapRowId.cbegin();
            XdbXNm* xdbXNmTmp = xdbXNmMapRowIdIt->second;
            dictXdbXNmDrop(xdbXNmTmp);
            delete xdbXNmTmp;
        }
        if (!xdbXNmMapId.empty())
            ctx->error(50029, "key map XDB.X$NM" + tokSuf + " not empty, left: " + std::to_string(xdbXNmMapId.size()) + " at exit");

        while (!xdbXPtMapRowId.empty()) {
            auto xdbXPtMapRowIdIt = xdbXPtMapRowId.cbegin();
            XdbXPt* xdbXPtTmp = xdbXPtMapRowIdIt->second;
            dictXdbXPtDrop(xdbXPtTmp);
            delete xdbXPtTmp;
        }
        if (!xdbXPtMapId.empty())
            ctx->error(50029, "key map XDB.X$PT" + tokSuf + " not empty, left: " + std::to_string(xdbXPtMapId.size()) + " at exit");

        while (!xdbXQnMapRowId.empty()) {
            auto xdbXQnMapRowIdIt = xdbXQnMapRowId.cbegin();
            XdbXQn* xdbXQnTmp = xdbXQnMapRowIdIt->second;
            dictXdbXQnDrop(xdbXQnTmp);
            delete xdbXQnTmp;
        }
        if (!xdbXQnMapId.empty())
            ctx->error(50029, "key map XDB.X$QN" + tokSuf + " not empty, left: " + std::to_string(xdbXQnMapId.size()) + " at exit");
    }

    XdbXNm* SchemaXml::dictXdbXNmFind(typeRowId rowId) {
        auto xdbXNmMapRowIdIt = xdbXNmMapRowId.find(rowId);
        if (xdbXNmMapRowIdIt != xdbXNmMapRowId.end())
            return xdbXNmMapRowIdIt->second;
        else
            return nullptr;
    }

    XdbXPt* SchemaXml::dictXdbXPtFind(typeRowId rowId) {
        auto xdbXPtMapRowIdIt = xdbXPtMapRowId.find(rowId);
        if (xdbXPtMapRowIdIt != xdbXPtMapRowId.end())
            return xdbXPtMapRowIdIt->second;
        else
            return nullptr;
    }

    XdbXQn* SchemaXml::dictXdbXQnFind(typeRowId rowId) {
        auto xdbXQnMapRowIdIt = xdbXQnMapRowId.find(rowId);
        if (xdbXQnMapRowIdIt != xdbXQnMapRowId.end())
            return xdbXQnMapRowIdIt->second;
        else
            return nullptr;
    }


    void SchemaXml::dictXdbXNmAdd(XdbXNm* xdbXNm) {
        auto xdbXNmMapIdIt = xdbXNmMapId.find(xdbXNm->id);
        if (xdbXNmMapIdIt != xdbXNmMapId.end())
            throw DataException(50024, "duplicate XDB.X$NM" + tokSuf + " value for unique (ID: '" + xdbXNm->id + "')");

        xdbXNmMapRowId.insert_or_assign(xdbXNm->rowId, xdbXNm);
        xdbXNmMapId.insert_or_assign(xdbXNm->id, xdbXNm);
    }

    void SchemaXml::dictXdbXPtAdd(XdbXPt* xdbXPt) {
        auto xdbXPtMapIdIt = xdbXPtMapId.find(xdbXPt->id);
        if (xdbXPtMapIdIt != xdbXPtMapId.end())
            throw DataException(50024, "duplicate XDB.X$PT" + tokSuf + " value for unique (ID: '" + xdbXPt->id + "')");

        xdbXPtMapRowId.insert_or_assign(xdbXPt->rowId, xdbXPt);
        xdbXPtMapId.insert_or_assign(xdbXPt->id, xdbXPt);
    }

    void SchemaXml::dictXdbXQnAdd(XdbXQn* xdbXQn) {
        auto xdbXQnMapIdIt = xdbXQnMapId.find(xdbXQn->id);
        if (xdbXQnMapIdIt != xdbXQnMapId.end())
            throw DataException(50024, "duplicate XDB.X$QN" + tokSuf + " value for unique (ID: '" + xdbXQn->id + "')");

        xdbXQnMapRowId.insert_or_assign(xdbXQn->rowId, xdbXQn);
        xdbXQnMapId.insert_or_assign(xdbXQn->id, xdbXQn);
    }

    void SchemaXml::dictXdbXNmDrop(XdbXNm* xdbXNm) {
        auto xdbXNmMapRowIdIt = xdbXNmMapRowId.find(xdbXNm->rowId);
        if (xdbXNmMapRowIdIt == xdbXNmMapRowId.end())
            return;
        xdbXNmMapRowId.erase(xdbXNmMapRowIdIt);

        auto xdbXNmMapIdIt = xdbXNmMapId.find(xdbXNm->id);
        if (xdbXNmMapIdIt != xdbXNmMapId.end())
            xdbXNmMapId.erase(xdbXNmMapIdIt);
        else
            ctx->warning(50030, "missing index for XDB.X$NM" + tokSuf + " (ID: '" + xdbXNm->id + "')");
    }

    void SchemaXml::dictXdbXPtDrop(XdbXPt* xdbXPt) {
        auto xdbXPtMapRowIdIt = xdbXPtMapRowId.find(xdbXPt->rowId);
        if (xdbXPtMapRowIdIt == xdbXPtMapRowId.end())
            return;
        xdbXPtMapRowId.erase(xdbXPtMapRowIdIt);

        auto xdbXPtMapIdIt = xdbXPtMapId.find(xdbXPt->id);
        if (xdbXPtMapIdIt != xdbXPtMapId.end())
            xdbXPtMapId.erase(xdbXPtMapIdIt);
        else
            ctx->warning(50030, "missing index for XDB.X$PT" + tokSuf + " (ID: '" + xdbXPt->id + "')");
    }

    void SchemaXml::dictXdbXQnDrop(XdbXQn* xdbXQn) {
        auto xdbXQnMapRowIdIt = xdbXQnMapRowId.find(xdbXQn->rowId);
        if (xdbXQnMapRowIdIt == xdbXQnMapRowId.end())
            return;
        xdbXQnMapRowId.erase(xdbXQnMapRowIdIt);

        auto xdbXQnMapIdIt = xdbXQnMapId.find(xdbXQn->id);
        if (xdbXQnMapIdIt != xdbXQnMapId.end())
            xdbXQnMapId.erase(xdbXQnMapIdIt);
        else
            ctx->warning(50030, "missing index for XDB.X$QN" + tokSuf + " (ID: '" + xdbXQn->id + "')");
    }

}
