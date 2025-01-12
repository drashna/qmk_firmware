// hacky hack to enable GPIOJ and GPIOK on the F429ZI, which are not enabled by default in ChibiOS.


#include <stm32_registry.h>
#undef STM32_HAS_GPIOJ
#define STM32_HAS_GPIOJ TRUE
#undef STM32_HAS_GPIOK
#define STM32_HAS_GPIOK TRUE

#undef STM32_GPIO_EN_MASK
#define STM32_GPIO_EN_MASK (RCC_AHB1ENR_GPIOAEN | \
                            RCC_AHB1ENR_GPIOBEN | \
                            RCC_AHB1ENR_GPIOCEN | \
                            RCC_AHB1ENR_GPIODEN | \
                            RCC_AHB1ENR_GPIOEEN | \
                            RCC_AHB1ENR_GPIOFEN | \
                            RCC_AHB1ENR_GPIOGEN | \
                            RCC_AHB1ENR_GPIOHEN | \
                            RCC_AHB1ENR_GPIOIEN | \
                            RCC_AHB1ENR_GPIOJEN | \
                            RCC_AHB1ENR_GPIOKEN)

#include_next <hal_lld.h>
