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

// API로부터 환율 정보 가져오기
float get_exchange_rate() {
    // API 호출 및 응답 받아오기
    // 여기에 API 호출 및 응답 받아오는 로직을 구현할 것입니다. 
    // 응답은 JSON 형태로 받아와서 구조체에 저장하는 방식으로 처리합니다.
    // 아래는 임시로 환율 정보를 저장하는 코드입니다.

    struct ExchangeRate exchangeRate;
    exchangeRate.rate = 1130.50;  // 임시로 환율을 설정합니다.
    strcpy(exchangeRate.base, "USD");
    strcpy(exchangeRate.target, "KRW");

    return exchangeRate.rate;
}

// 계산 결과를 저장할 구조체
struct CalculationResult {
    float priceInUSD;
    float priceInKRW;
    float tax;
    float tip;
    float totalPriceInUSD;
    float totalPriceInKRW;
};

void calculate_price(float exchangeRate, struct CalculationResult* result) {
    // 미국에서의 가격
    printf("미국에서의 가격을 입력하세요: ");
    scanf("%f", &(result->priceInUSD));

    // 한화로 변환
    result->priceInKRW = result->priceInUSD * exchangeRate;
    printf("한화로 변환한 가격: %.2f KRW   ", result->priceInKRW);

    // 면세 여부
    int isTaxExempt = 0;
    printf("면세인가요? (면세면 1, 아니면 0 입력): ");
    scanf("%d", &isTaxExempt);

    // 주별 세금 비율
    float taxRate = 0.0;
    int state = 0;
    printf("미국 주를 입력하세요 (1: 뉴욕, 2: 캘리포니아, 3: 텍사스): ");
    scanf("%d", &state);

    switch (state) {
    case 1: // 뉴욕
        taxRate = 0.08875;
        break;
    case 2: // 캘리포니아
        taxRate = 0.0825;
        break;
    case 3: // 텍사스
        taxRate = 0.0625;
        break;
    default:
        printf("잘못된 입력입니다.  ");
        return;
    }

    // 세금 계산
    result->tax = 0.0;
    if (!isTaxExempt) {
        result->tax = result->priceInUSD * taxRate;
    }

    // 팁 계산
    float tipRate = 0.15; // 팁 비율
    result->tip = (result->priceInUSD + result->tax) * tipRate;

    // 최종 가격 계산
    result->totalPriceInUSD = result->priceInUSD + result->tax + result->tip;
    result->totalPriceInKRW = result->totalPriceInUSD * exchangeRate;
}

void print_result(struct CalculationResult* result) {
    printf("세금: %.2f USD ", result->tax);
    printf("팁: %.2f USD ", result->tip);
    printf("최종 가격: %.2f USD ", result->totalPriceInUSD);
    printf("최종 가격: %.2f KRW ", result->totalPriceInKRW);
}

int main() {
    // 실시간 환율 가져오기
    float exchangeRate = get_exchange_rate();

    if (exchangeRate == 0.0) {
        printf("실시간 환율을 가져오는데 실패했습니다. 프로그램을 종료합니다. ");
        return 0;
    }

    struct CalculationResult result;

    calculate_price(exchangeRate, &result);

    print_result(&result);

    return 0;
}
