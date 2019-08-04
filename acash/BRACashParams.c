//
//  BRChainParams.c
//  BRCore
//
//  Created by Aaron Voisine on 3/11/19.
//  Copyright (c) 2019 breadwallet LLC
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.

//

#include "BRACashParams.h"

static const char *BRMainNetDNSSeeds[] = {
    "seed.dnsseed.acash.io.", "dnsseed.wccoin.wcchain.io.", NULL
};

static const char *BRTestNetDNSSeeds[] = {
    "testnet-seed.breadwallet.com.", "testnet-seed.bitcoin.petertodd.org.", "testnet-seed.bluematt.me.",
    "testnet-seed.bitcoin.schildbach.de.", NULL
};

// blockchain checkpoints - these are also used as starting points for partial chain downloads, so they must be at
// difficulty transition boundaries in order to verify the block difficulty at the immediately following transition
static const BRCheckPoint BRMainNetCheckpoints[] = {
    {      0, uint256("83d9aa408f334750f48ba5b025b4a04b3ff3919e9c867c6eecf839d086a1f07d"), 1537518468, 0x1e0ffff0 }
    //{ 564480,
};

static const BRCheckPoint BRTestNetCheckpoints[] = {
    {       0, uint256("2c56587777470ff3c391d4ffa0e8bfa1e54afaeb5d81d2157a0cd2d9ecb0a638"), 1562057922, 0x1e0ffff0 }
    //{ 1512000,
};

static int BRMainNetVerifyDifficulty(const BRMerkleBlock *block, const BRSet *blockSet)
{
    const BRMerkleBlock *previous, *b = NULL;
    uint32_t i;

    assert(block != NULL);
    assert(blockSet != NULL);

    // check if we hit a difficulty transition, and find previous transition block
    if ((block->height % BLOCK_DIFFICULTY_INTERVAL) == 0) {
        for (i = 0, b = block; b && i < BLOCK_DIFFICULTY_INTERVAL; i++) {
            b = BRSetGet(blockSet, &b->prevBlock);
        }
    }

    previous = BRSetGet(blockSet, &block->prevBlock);
    return BRMerkleBlockVerifyDifficulty(block, previous, (b) ? b->timestamp : 0);
}

static int BRTestNetVerifyDifficulty(const BRMerkleBlock *block, const BRSet *blockSet)
{
    return 1; // XXX skip testnet difficulty check for now
}

static const BRChainParams BRACashParamsRecord = {
    BRMainNetDNSSeeds,
    9779,                  // standardPort
    0xdbf8caac,            // magicNumber
    SERVICES_NODE_WITNESS, // services
    23,                     // publicKey
    23,                   // secretKey
    22,                     // scriptKey
    (100800000LL*SATOSHIS), //maxMoney;
    0x1e0ffff0,            //max_POW;
    (3.5*24*60*60),         //targetTimespan;
    BRMainNetVerifyDifficulty,
    BRMainNetCheckpoints,
    sizeof(BRMainNetCheckpoints)/sizeof(*BRMainNetCheckpoints)
};
const BRChainParams *BRACashParams = &BRACashParamsRecord;

static const BRChainParams BRACashTestNetParamsRecord = {
    BRTestNetDNSSeeds,
    19335,                 // standardPort
    0xf1caa2ac,            // magicNumber
    SERVICES_NODE_WITNESS, // services
    21,                     // publicKey
    21,                   // secretKey
    20,                     // scriptKey
    (100800000LL*SATOSHIS), //maxMoney;
    0x1e0ffff0,            //max_POW;
    (3.5*24*60*60),         //targetTimespan;
    BRTestNetVerifyDifficulty,
    BRTestNetCheckpoints,
    sizeof(BRTestNetCheckpoints)/sizeof(*BRTestNetCheckpoints)
};
const BRChainParams *BRACashTestNetParams = &BRACashTestNetParamsRecord;


