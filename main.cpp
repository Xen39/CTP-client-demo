#include "ctp-api/include/ThostFtdcMdApi.h"

#include <iostream>

#include "src/CtpMdSpi.hpp"

using namespace std;


int main() {
    cout << "正在初始化 md api..." << endl;
    CThostFtdcMdApi *api = CThostFtdcMdApi::CreateFtdcMdApi("./flow");
    if (api == nullptr) {
        cerr << "创建api失败!" << endl;
        exit(-1);
    }
    CtpMdSpi ctpMdSpi(api);
    api->RegisterSpi(&ctpMdSpi);
    char *serverAddr = const_cast<char *>("tcp://127.0.0.1:10031");
    api->RegisterFront(serverAddr);
    api->Init();
    api->Join();
    return 0;
}
