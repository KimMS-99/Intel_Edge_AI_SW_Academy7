라즈베리 파이와 STM32를 UART로 연결해 에코백 테스트를 수행하는 예제입니다.<br>
오류 발생 시 자원 해제는 [Linux Kernel Coding Style](https://www.kernel.org/doc/html/v4.10/process/coding-style.html)을 참고하여, 모듈 초기화(init) 함수의 에러 처리 경로에서 `goto` 패턴으로 구현했습니다.

## stm32 주요 코드

```c
/* USER CODE BEGIN PV */
#define RX_BUF_SIZE 256
char rxBuf[RX_BUF_SIZE];
volatile uint8_t rx_ch;
volatile uint8_t rx_index = 0;
volatile uint8_t uart6_flag = 0;
/* USER CODE END PV */
```
```c
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  if (uart6_flag)
	  {
		  rxBuf[rx_index] = '\0'; // null-terminate
		  printf("Received: %s\r\n", rxBuf);

		  strcat(rxBuf, "\n");
		  HAL_UART_Transmit(&huart6, &rxBuf, rx_index + 1, HAL_MAX_DELAY);

		  rx_index = 0;
		  uart6_flag = 0;

		  memset(rxBuf, 0, sizeof(rxBuf));
	  }
  }
  /* USER CODE END 3 */
```
```c
/* USER CODE BEGIN 4 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if (huart->Instance == USART6)
  {
    if (rx_ch == '\n')
    {
    	uart6_flag = 1;
    }
    else
    {
      if (rx_index < RX_BUF_SIZE - 1)
      {
        rxBuf[rx_index++] = rx_ch;
      }
    }

    // 다시 수신 요청
    HAL_UART_Receive_IT(&huart6, &rx_ch, 1);
  }
}
/* USER CODE END 4 */
```