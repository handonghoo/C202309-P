#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 콜백 함수
size_t write_callback(char* ptr, size_t size, size_t nmemb, void* userdata) {
    // 수신한 데이터를 출력하지 않고 무시합니다.
    return size * nmemb;
}

double get_exchange_rate(const char* base_currency, const char* target_currency) {
    FILE* fp;
    char url[256];
    char command[512];
    char response[1024];
    double exchange_rate = 0.0;

    // API 요청 URL 생성
    sprintf(url, "https://openexchangerates.org/api/latest.json?app_id=YOUR_API_KEY&base=%s&symbols=%s", base_currency, target_currency);

    // cURL 명령어 실행
    sprintf(command, "curl -s \"%s\"", url);
    fp = _popen(command, "r");
    if (fp != NULL) {
        // 응답 데이터 읽기
        fread(response, sizeof(char), sizeof(response) - 1, fp);
        _pclose(fp);

        // JSON 파싱
        char* rate_start = strstr(response, "\"") + 1;
        char* rate_end = strstr(rate_start, "\"");
        *rate_end = '\0';
        exchange_rate = atof(rate_start);
    }

    return exchange_rate;
}

int main() {
    const char* base_currency = "USD";  // 기준 통화
    const char* target_currency = "KRW";  // 변환할 통화

    double exchange_rate = get_exchange_rate(base_currency, target_currency);
    printf("1 %s = %.2f %s\n", base_currency, exchange_rate, target_currency);


    //  API 키값 미확보로 인한 임의의 환율 구현
     // 환율을 변수에 저장합니다.
    float exchange_rate = 1225.00;

    // 한화로 물건의 가격을 입력받습니다.
    float won = 0.0;
    printf("물건의 가격을 한화로 입력하세요: ");
    scanf("%f", &won);

    // 한화를 달러로 변환합니다.
    float dollar = won / exchange_rate;

    // 달러로 변환된 가격을 출력합니다.
    printf("물건의 가격은 %.2f 달러입니다.\n", dollar);

    return 0;
}
