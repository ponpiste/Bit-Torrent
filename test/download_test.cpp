#include "tracker/tracker.h"
#include "gtest/gtest.h"
#include <vector>
#include "parsing/torrent.h"
#include "parsing/buffer.h"
#include <stdio.h>
#include <iostream>
#include "parsing/bencode.h"
#include "download/peer_id.h"
#include "download/connection.h"
#include "download/download.h"

using namespace std;

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
