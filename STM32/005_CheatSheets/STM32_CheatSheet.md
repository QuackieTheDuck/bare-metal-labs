# STM32, 32-bit Cheat Sheet (working on NUCLEO-F0308)

---

## Binary operations

1. Set: can be done using `| (OR)` and `<< (bitwise left shift)`,
2. Clear: can be done using `& (AND)` and `~ (negation)`,
3. Toggle: can be done using `^ (XOR)`,
4. Single bit read: can be done `& (and)` combined with proper mask.

## RCC_AHBENR

## RCC_APB1ENR

## GPIO configuration

1.  `GPIOx_MODER`:

2.  `GPIOx_OTYPER` (Output Port Type Register):

3.  `GPIOx_PUPDR` :

4.  `GPIOx_ODR` :

## `TIM6`, Hardware basic clock configuaration and usage:

## Creating `*.h` files:

## Adding required `*.h` files:
