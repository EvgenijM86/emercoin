// Copyright (c) 2010-2011 Vincent Durham
// Distributed under the MIT/X11 software license, see the accompanying
// file license.txt or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_HOOKS_H
#define BITCOIN_HOOKS_H

class CWalletTx;
class CScript;
class CTransaction;
class CTxDB;
class uint256;
class CTxIndex;
class CBlockIndex;
class CDiskTxPos;
class CBlock;
class CTxOut;

#include <map>
#include <vector>
#include <string>
using namespace std;

class CHooks
{
public:
    virtual bool IsStandard(const CTransaction& tx) = 0;
    virtual bool CheckTransaction(const CTransaction& tx) = 0;
    virtual bool ConnectInputs(CTxDB& txdb,
            std::map<uint256, CTxIndex>& mapTestPool,
            const CTransaction& tx,
            std::vector<CTransaction>& vTxPrev,
            std::vector<CTxIndex>& vTxindex,
            const CBlockIndex* pindexBlock,
            const CDiskTxPos& txPos,
            bool fBlock,
            bool fMiner) = 0;
    virtual bool DisconnectInputs(CTxDB& txdb,
            const CTransaction& tx,
            CBlockIndex* pindexBlock) = 0;
    virtual bool ConnectBlock(CTxDB& txdb, CBlockIndex* pindex) = 0;
    virtual bool DisconnectBlock(CTxDB& txdb, CBlockIndex* pindex) = 0;
    virtual bool ExtractAddress(const CScript& script, std::string& address) = 0;
    virtual void AcceptToMemoryPool(CTxDB& txdb, const CTransaction& tx) = 0;
    virtual bool IsMine(const CTxOut& txout) = 0;
    virtual bool IsNameTx(int nVersion) = 0;
    virtual bool IsNameScript(CScript scr) = 0;
    virtual bool deletePendingName(const CTransaction& tx) = 0;
    virtual bool getNameValue(const string& name, string& value) = 0;
};

extern CHooks* InitHook();
extern std::string GetDefaultDataDirSuffix();

#endif
