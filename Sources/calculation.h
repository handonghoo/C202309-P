#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


// 환율 정보를 저장할 구조체
struct ExchangeRate {
    float rate;
    char base[4];
    char target[4];
};

// 계산 결과를 저장할 구조체
struct CalculationResult {
    float priceInUSD;
    float priceInKRW;
    float tax;
    float tip;
    float totalPriceInUSD;
    float totalPriceInKRW;
};