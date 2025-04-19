#pragma once

#include <iostream>
#include <cstring>

#include "../ctp-api/include/ThostFtdcMdApi.h"

class CtpMdSpi : public CThostFtdcMdSpi {
public:
    CtpMdSpi(CThostFtdcMdApi *api) : mApi(api) {}

    void OnFrontConnected() override;

    void OnFrontDisconnected(int reason) override;

    void OnRspUserLogin(CThostFtdcRspUserLoginField *rspUserLogin, CThostFtdcRspInfoField *rspInfo, int requestId,
                        bool isLast) override;

    void OnRspUserLogout(CThostFtdcUserLogoutField *userLogout, CThostFtdcRspInfoField *rspInfo, int requestId,
                         bool isLast) override;

    void OnRspError(CThostFtdcRspInfoField *rspInfo, int requestId, bool isLast) override;

    void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *instrument, CThostFtdcRspInfoField *rspInfo,
                            int requestId, bool isLast) override;

    void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *instrument, CThostFtdcRspInfoField *rspInfo,
                              int requestId, bool isLast) override;

    void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *marketData) override;

private:
    CThostFtdcMdApi *mApi;
};


