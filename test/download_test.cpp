#include "tracker.h"
#include "gtest/gtest.h"
#include <vector>
#include "torrent.h"
#include "buffer.h"
#include <stdio.h>
#include <iostream>
#include "bencode.h"
#include "peer_id.h"
#include "connection.h"
#include "download.h"

using namespace std;

TEST(torrent, load) {

	torrent t("../goosebumps.torrent");

	// 4201 pieces
	EXPECT_EQ(t.get_piece_length(0), 524288);
	EXPECT_EQ(t.get_piece_length(1), 524288);
	EXPECT_EQ(t.get_piece_length(2000), 524288);
	EXPECT_EQ(t.get_piece_length(4199), 524288);
	EXPECT_EQ(t.get_piece_length(4200), 263713);

	// block size = 16384
	EXPECT_EQ(t.get_n_blocks(0), 32);
	EXPECT_EQ(t.get_n_blocks(1), 32);
	EXPECT_EQ(t.get_n_blocks(2000), 32);
	EXPECT_EQ(t.get_n_blocks(4199), 32);
	EXPECT_EQ(t.get_n_blocks(4200), 17);

	EXPECT_EQ(t.get_block_length(0,0), 16384);
	EXPECT_EQ(t.get_block_length(1,0), 16384);
	EXPECT_EQ(t.get_block_length(2000,0), 16384);
	EXPECT_EQ(t.get_block_length(4199,0), 16384);
	EXPECT_EQ(t.get_block_length(4200,0), 16384);

	EXPECT_EQ(t.get_block_length(0,1), 16384);
	EXPECT_EQ(t.get_block_length(1,2), 16384);
	EXPECT_EQ(t.get_block_length(2000,30), 16384);
	EXPECT_EQ(t.get_block_length(4199,15), 16384);
	EXPECT_EQ(t.get_block_length(4200,15), 16384);

	EXPECT_EQ(t.get_block_length(0,31), 16384);
	EXPECT_EQ(t.get_block_length(1,31), 16384);
	EXPECT_EQ(t.get_block_length(2000,31), 16384);
	EXPECT_EQ(t.get_block_length(4199,31), 16384);
	EXPECT_EQ(t.get_block_length(4200,16), 1569);
}

TEST(connection, goosebumps) {

    peer_id::generate();

    torrent t("../goosebumps.torrent");
    EXPECT_EQ(t.pieces, 4201);

    vector<peer> v = tracker::get_peers(t);

    cout<<"received "<<v.size()<<" peers"<<endl;

    download d(v,t);
    d.start();
}

/*

{
    "announce":"http://tracker.yggtracker.cc:8080/IEBVvI0dWAS5pBBKtKDpggBzr00fImwa/announce",
    "created by":"YggTorrent",
    "creation date":1599953075,
    "info":{
            "length":2202273313,
            "name":"Goosebumps.2.2018.MULTI.TRUEFRENCH.1080p.BluRay.HDLight.x264.AC3-TOXIC.mkv",
            "piece length":524288,
            "pieces":"...",
            "private":1
            }
}

*/
