#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 환율 정보를 저장하기 위한 구조체
typedef struct {
    char base[4]; // 환율 기준 통화
    char target[4]; // 환율 표시 통화
    double rate; // 환율
} ExchangeRate;

// 파일에서 환율 정보를 가져오는 함수
ExchangeRate get_exchange_rate() {
    // 환율 정보 파일을 열기 위한 파일 포인터
    FILE* file;

    // 파일을 열지 못하면 오류 출력
    if (fopen_s(&file, "exchange_rate.txt", "r") != 0) {
        fprintf(stderr, "환율 정보 파일을 열 수 없습니다.\n");
        return (ExchangeRate) { 0 };
    }

    // 파일에서 한 줄씩 읽기
    char line[256];
    char* rate_start = NULL;
    double exchange_rate = 0.0;

    while (fgets(line, sizeof(line), file) != NULL) {
        // KRW 환율을 찾기 위한 조건
        rate_start = strstr(line, "\"KRW\":");

        // KRW 환율이 있으면 환율을 저장
        if (rate_start != NULL) {
            sscanf_s(rate_start + 7, "%lf", &exchange_rate);
            break;
        }
    }

    // 파일을 닫기
    fclose(file);

    // 환율이 없으면 오류 출력
    if (exchange_rate == 0.0) {
        fprintf(stderr, "환율 정보를 찾을 수 없습니다.\n");
        return (ExchangeRate) { 0 };
    }

    // 환율 정보를 구조체에 저장하여 반환
    return (ExchangeRate) { "USD", "KRW", exchange_rate };
}

// 주별 세율을 구하는 함수
double get_state_tax_rate(char state) {
    // 주별 세율
    double state_tax = 0.0;

    // 주별 세율을 구하기 위한 switch 문
    switch (state) {
    case 'A':
        state_tax = 4.0;
        break;
    case 'B':
        state_tax = 5.0;
        break;
    case 'C':
        state_tax = 5.6;
        break;
    case 'D':
        state_tax = 6.5;
        break;
    case 'E':
        state_tax = 7.25;
        break;
    case 'F':
        state_tax = 2.9;
        break;
    case 'G':
        state_tax = 6.35;
        break;
    case 'H':
        state_tax = 0;
        break;
    case 'I':
        state_tax = 6.0;
        break;
    default:
        break;
    }

    // 주별 세율을 반환
    return state_tax;
}

// 총 비용을 계산하는 함수
double calculate_total_cost(double amount, double exchange_rate, int duty_free, int tip, char state) {
    // 총 비용
    double total_cost = amount;

    // 환율을 적용하여 총 비용을 계산
    total_cost *= exchange_rate;

    // 면세 여부에 따라 총 비용을 계산
    if (duty_free) {
        total_cost *= 1.15;
    }

    // 팁 비율을 적용하여 총 비용을 계산
    double tip_rate = tip / 100.0;
    total_cost += total_cost * tip_rate;

    // 주별 세율을 적용하여 총 비용을 계산
    double state_tax = get_state_tax_rate(state);
    total_cost += total_cost * state_tax;

    // 총 비용을 반환
    return total_cost;
}

