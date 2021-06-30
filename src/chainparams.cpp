// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2018 The FLA Developers 
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "libzerocoin/Params.h"
#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"
#include "pow.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"



//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}
 static bool regenerate = false;

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (0, uint256("bd6e852a22cba394b142aa1e589c2dbfe8a44d201e9d3fda5edb642e114cc794"))
    (966, uint256("2b3f8af3434e1017fc1a6c0de0b431f3ff2f6d77b04548ebfb65d55ea9e50b60"))
    (2189, uint256("f2e5462ac7e9d8374f542dd665055e5ac4fe490856c4f453b98c4bb8133053f7"))
    (12500, uint256("90212d1f0260b4d6d1b61bac56fd839d9ce047505d593f1b470ff429332c3754"))
    (28950, uint256("f424fddd5cad79e62a5bcf52e711a83f462b80554f0b26b29ee034ea02e76f18"))
    (69821, uint256("6205337f02ceaa6896c61c05f05d4b68d3d2776234ba71f0d04cbfeffa7559d6"))
    (95900, uint256("4108597307bf7ea8e8c4adc5b154347c064a436992415098ba51f50c2fc13e79"))
    (125000, uint256("1d245402dd92a17e8edf84b52b3931a3376f565b622b6f1e3af9fbfc1dee3328"))
    (157403, uint256("47a62d44ef979f0bbb236904540d99588d841901811291859325abf27593f299"))
    (272719, uint256("c933174bf77a47ab2209d5094c0896bd9e1c4affcb64a70d67176c5cd8fbddd9")); //Hopefully the final checkpoint before we move to the new chain

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1625052952, // * UNIX timestamp of last checkpoint block
    320144 ,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    300        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    0,
    0,
    0};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    0,
    0,
    0};

libzerocoin::ZerocoinParams* CChainParams::Zerocoin_Params() const
{
    assert(this);
    static CBigNum bnDecModulus = 0;
    if (!bnDecModulus)
        bnDecModulus.SetDec(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParamsDec = libzerocoin::ZerocoinParams(bnDecModulus);

    return &ZCParamsDec;
}

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x2a;
        pchMessageStart[1] = 0x5c;
        pchMessageStart[2] = 0xe8;
        pchMessageStart[3] = 0xb6;
        vAlertPubKey = ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f");
        nP2pPort = 17000;
        nRpcPort = 16900;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // FLACOIN starting difficulty is 1 / 2^12
        nSubsidyHalvingInterval = 210000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 8100; // 75%
        nRejectBlockOutdatedMajority = 10260; // 95%
        nToCheckBlockUpgradeMajority = 10800; // Approximate expected amount of blocks in 7 days (1440*7.5)
        nMinerThreads = 1;
        nTargetTimespan = 1 * 24 * 60 * 60; // FLACOIN
        nTargetSpacing = 1 * 60;  // FLACOIN 1 minute
        nMaturity = 10;
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 5000000 * COIN;

        /** Height or Time Based Activations **/
        nLastPoWBlock = 300;
        //nModifierUpdateBlock = 1;
        nZerocoinStartHeight = 0;
        nZerocoinStartTime = 0; 
        //nBlockEnforceSerialRange = 400000; 
        //nBlockRecalculateAccumulators = 300000;
        //nBlockFirstFraudulent = 250000;
        nBlockLastGoodCheckpoint = 0;
        //nBlockEnforceInvalidUTXO = 330000; 
        //nInvalidAmountFiltered = 100000 *COIN;
        nBlockZerocoinV2 = 0;
        //nEnforceNewSporkKey = 1612929294;
        //nRejectOldSporkKey = 1628609535;

        /**
         * Build the genesis block. Note that the output of the genesis coinbase cannot
         * be spent as it did not originally exist in the database.
         */
        const char* pszTimestamp = "Flacoin Masternode The Blockchain 2.0.1 10/Aug/2020";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 50 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 4;
        genesis.nAccumulatorCheckpoint = 0;
        genesis.nTime = 1597066854;
        genesis.nBits = 504365040;
        genesis.nNonce = 330698;

        hashGenesisBlock = genesis.GetHash();
        if (regenerate) {
            hashGenesisBlock = uint256S("");
            genesis.nNonce = 0;
            if (true && (genesis.GetHash() != hashGenesisBlock)) {
                while (genesis.GetHash() > bnProofOfWorkLimit)
                {
                    ++genesis.nNonce;
                    if (genesis.nNonce == 0)
                    {
                        ++genesis.nTime;
                    }
                }
                std::cout << "// Mainnet ---";
                std::cout << " nonce: 0" << genesis.nNonce;
                std::cout << " time: 0" << genesis.nTime;
                std::cout << " hash: 0x" << genesis.GetHash().ToString().c_str();
                std::cout << " merklehash: 0x"  << genesis.hashMerkleRoot.ToString().c_str() <<  "\n";
            }
        } else {
           assert(hashGenesisBlock == uint256("bd6e852a22cba394b142aa1e589c2dbfe8a44d201e9d3fda5edb642e114cc794"));
           assert(genesis.hashMerkleRoot == uint256("0b127297c9cd8d010e153cbc286dd2ee2455f60dd3b52a3c20db0bb6b663a1bb"));
        }



        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 35); // Flacoin's wallet address starts with a F
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 95); // f
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 51); // M
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x05)(0x2C)(0x24)(0x43).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x05)(0x2D)(0x35)(0x5A).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x77).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = true;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "04968848f4b5ddb20043eeee40614f6bb2d6831649ae1dccb0c03386062474651e5e07995b15b041277d1cedefbb05138c0aa95f5e39092220e995afdfd01d550a";
        strObfuscationPoolDummyAddress = "FF28rEoqWxP6MSVoDnHr7U6ZXfpCFogECG";
	strSporkKey = "04aced9c0c630e9ca9d8cc0d96cd6e9e1df5dc438efe701224a1233a415162abe244b0cd98bedaf58f584aec31ad8117661ebbd2e6599149c3ffc7196558041765";
        strObfuscationPoolDummyAddress = "FQFSPUyoV4HSqf3BKvnREi1eGcykTyFV3a";

        /** Zerocoin */
        zerocoinModulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
            "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
            "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
            "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
            "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
            "31438167899885040445364023527381951378636564391212010397122822120720357";
        nMaxZerocoinSpendsPerTransaction = 7; // Assume about 20kb each
        nMinZerocoinMintFee = 1 * CENT; //high fee required for zerocoin mints
        nMintRequiredConfirmations = 20; //the maximum amount of confirmations until accumulated in 19
        nRequiredAccumulation = 1;
        nDefaultSecurityLevel = 100; //full security level for accumulators
        nZerocoinHeaderVersion = 4; //Block headers must be this version once zerocoin is active
        nZerocoinRequiredStakeDepth = 200; //The required confirmations for a zfla to be stakable
        nStakeMinAge = 60 * 60; //The number of seconds that a utxo must be old before it can qualify for staking
        nBudget_Fee_Confirmations = 6; // Number of confirmations for the finalization fee
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x4c;
        pchMessageStart[1] = 0x7e;
        pchMessageStart[2] = 0xe5;
        pchMessageStart[3] = 0xd4;
        vAlertPubKey = ParseHex("0441368f7cdaaf61526a27262b255af8c8453f967e543b32faee550439f13138fccdf6b8196ddb290081c2796dc053164a849d64ef9331e8ace3f7ebf9d438d846");
        nP2pPort = 10500;
        nRpcPort = 11000;
        nEnforceBlockUpgradeMajority = 4320; // 75%
        nRejectBlockOutdatedMajority = 5472; // 95%
        nToCheckBlockUpgradeMajority = 5760; // 4 days
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // FLACOIN: 1 day
        nTargetSpacing = 1 * 60;  // FLACOIN: 1 minute
        nLastPoWBlock = 200;
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        //nModifierUpdateBlock = 51197; //approx Mon, 17 Apr 2017 04:00:00 GMT
        nMaxMoneyOut = 43199500 * COIN;
        //nZerocoinStartHeight = 201576;
        //nZerocoinStartTime = 1501776000;
        //nBlockEnforceSerialRange = 1; //Enforce serial range starting this block
        //nBlockRecalculateAccumulators = 9908000; //Trigger a recalculation of accumulators
        //nBlockFirstFraudulent = 9891737; //First block that bad serials emerged
        //nBlockLastGoodCheckpoint = 9891730; //Last valid accumulator checkpoint
        //nBlockEnforceInvalidUTXO = 9902850; //Start enforcing the invalid UTXO's
        //nInvalidAmountFiltered = 0; //Amount of invalid coins filtered through exchanges, that should be considered valid
        //nBlockZerocoinV2 = 444020; //!> The block that zerocoin v2 becomes active
        //nEnforceNewSporkKey = 1521604800; //!> Sporks signed after Wednesday, March 21, 2018 4:00:00 AM GMT must use the new spork key
        //nRejectOldSporkKey = 1522454400; //!> Reject old spork key after Saturday, March 31, 2018 12:00:00 AM GMT

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1549065600;
        genesis.nNonce = 2390925;

        hashGenesisBlock = genesis.GetHash();
        if (regenerate) {
            hashGenesisBlock = uint256S("");
            genesis.nNonce = 0;
            if (true && (genesis.GetHash() != hashGenesisBlock)) {
                while (genesis.GetHash() > bnProofOfWorkLimit)
                {
                    ++genesis.nNonce;
                    if (genesis.nNonce == 0)
                    {
                        ++genesis.nTime;
                    }
                }
                std::cout << "// Testnet ---";
                std::cout << " nonce: " << genesis.nNonce;
                std::cout << " time: " << genesis.nTime;
                std::cout << " hash: 0x" << genesis.GetHash().ToString().c_str();
                std::cout << " merklehash: 0x"  << genesis.hashMerkleRoot.ToString().c_str() <<  "\n";

            }
        } else {
            //assert(hashGenesisBlock == uint256("0x000003df45253cc78109cec5f9f11d602bd55d9665b6f4710ebbe8ddf89e1a37"));
            //assert(genesis.hashMerkleRoot == uint256("0x4dca438430ad9ca73a7b6f5403c4e1ba597501828f3ea5700f23b994facc78b7"));
        }

        //vSeeds.clear();
       //  vSeeds.push_back(CDNSSeedData("tnseeder-01.flacoin.io", "tnseeder-01.flacoin.io"));
      //   vSeeds.push_back(CDNSSeedData("testnode-01.flacoin.io", "testnode-01.flacoin.io"));
        // vSeeds.push_back(CDNSSeedData("testnode-02.flacoin.io", "testnode-02.flacoin.io"));
       //  vSeeds.push_back(CDNSSeedData("testnode-03.flacoin.io", "testnode-03.flacoin.io"));
       //  vSeeds.push_back(CDNSSeedData("testnode-04.flacoin.io", "testnode-04.flacoin.io"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 17); // Testnet flacoin addresses start with '7'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 18);  // Testnet flacoin script addresses start with '8'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 65);     // Testnet private keys start with 'T'
        // Testnet flacoin BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet flacoin BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet flacoin BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "04acff02fc6183191a8f109cd4d7787e4e5c68e760284e7ab22d95337ac2c76669abf2b9350218a43ae56b5b9fa5b6817881a3f901273091232b6ab85bda068e27";
        strObfuscationPoolDummyAddress = "";
        nBudget_Fee_Confirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                       // here because we only have a 8 block finalization window on testnet
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xa1;
        pchMessageStart[1] = 0xcf;
        pchMessageStart[2] = 0x7e;
        pchMessageStart[3] = 0xac;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // FLACOIN: 1 day
        nTargetSpacing = 1 * 60;        // FLACOIN: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1533927507;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 0;
        nP2pPort = 51476;

        hashGenesisBlock = genesis.GetHash();
        if (regenerate) {
            hashGenesisBlock = uint256S("");
            genesis.nNonce = 0;
            if (true && (genesis.GetHash() != hashGenesisBlock)) {
                while (genesis.GetHash() > bnProofOfWorkLimit)
                {
                    ++genesis.nNonce;
                    if (genesis.nNonce == 0)
                    {
                        ++genesis.nTime;
                    }
                }
                std::cout << "// Regtest ---";
                std::cout << " nonce: " << genesis.nNonce;
                std::cout << " time: " << genesis.nTime;
                std::cout << " hash: 0x" << genesis.GetHash().ToString().c_str();
                std::cout << " merklehash: 0x"  << genesis.hashMerkleRoot.ToString().c_str() <<  "\n";

            }
        } else {
           // assert(hashGenesisBlock == uint256("0x7dbb050fde7e11bdfbfed6ef3cee609af3c0a33b0f984e76a3b7c0259dd7e285"));
         //   assert(genesis.hashMerkleRoot == uint256("0x4dca438430ad9ca73a7b6f5403c4e1ba597501828f3ea5700f23b994facc78b7"));
        }
        if (regenerate)
            exit(0);

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nP2pPort = 51478;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
