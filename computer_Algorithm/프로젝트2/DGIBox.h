#pragma once
extern "C" int InitDGIBox();
extern "C" int closeDGIBox();
extern  "C" int Set(int bid, int index, int value);
extern "C" int Get(int bid, int index);
extern "C" int Empty(int bid);
extern "C" int checker_init(const char* filename);
extern "C" int checker_close();
extern "C" int check();
extern "C" int next();




