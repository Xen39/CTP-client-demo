#include "CtpMdSpi.hpp"

#include <iostream>
#include <cstring>
#include <cassert>

using namespace std;

void CtpMdSpi::OnFrontConnected() {
    cout << "连接成功!" << endl;
    CThostFtdcReqUserLoginField reqLogin{};
    memset(reinterpret_cast<void *>(&reqLogin), 0, sizeof(reqLogin));
    strcpy(reqLogin.BrokerID, ""); // 期货公司会员号
    strcpy(reqLogin.UserID, ""); // 投资者在该期货公司客户号
    strcpy(reqLogin.Password, "");
    int ret = mApi->ReqUserLogin(&reqLogin, 1);
    switch (ret) {
        case 0:
            cout << "连接成功，正在登陆..." << endl;
            break;
        case -1:
            cerr << "网络原因连接失败" << endl;
            break;
        case -2:
            cerr << "未处理请求队列总数量超限" << endl;
            break;
        case -3:
            cerr << "每秒发送请求数量超限" << endl;
            break;
        default:
            cerr << "未知错误码: " << ret << endl;
            break;
    }
}

void CtpMdSpi::OnFrontDisconnected(int reason) {
    cerr << "连接断开" << endl;
}

void CtpMdSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *rspUserLogin,
                              CThostFtdcRspInfoField *rspInfo, int requestId, bool isLast) {
    if (rspInfo->ErrorID) {
        cerr << "登陆失败,错误码: " << rspInfo->ErrorID << ", 错误原因: " << rspInfo->ErrorMsg << endl;
        return;
    }
    assert(rspUserLogin != nullptr);
    cout << "登陆成功，当前日期: " << rspUserLogin->TradingDay << endl;
}

void CtpMdSpi::OnRspUserLogout(CThostFtdcUserLogoutField *userLogout, CThostFtdcRspInfoField *rspInfo, int requestId,
                               bool isLast) {
    assert(userLogout != nullptr);
    cout << "用户登出, BrokerId " << userLogout->BrokerID << " UserId " << userLogout->UserID;
}

void CtpMdSpi::OnRspError(CThostFtdcRspInfoField *rspInfo, int requestId, bool isLast) {
    if (rspInfo == nullptr)
        return;
    cerr << "OnRspError:  错误码: " << rspInfo->ErrorID << " 错误原因: " << rspInfo->ErrorMsg << endl;
}

void CtpMdSpi::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *instrument,
                                  CThostFtdcRspInfoField *rspInfo, int requestId, bool isLast) {
    cout << "成功订阅合约 " << instrument->InstrumentID << endl;
}

void CtpMdSpi::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *instrument, CThostFtdcRspInfoField *rspInfo,
                                    int requestId, bool isLast) {
    cout << "取消订阅合约 " << instrument->InstrumentID << endl;
}

void CtpMdSpi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *marketData) {
    assert(marketData != nullptr);
    cout << "收到行情: " << marketData->ExchangeID << " " << marketData->InstrumentID
         << " 买1 " << marketData->AskPrice1 << " x " << marketData->AskVolume1
         << " 卖1 " << marketData->BidPrice1 << " x " << marketData->BidVolume1;
}


