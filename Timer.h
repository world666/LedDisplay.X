void StartTimer1()//write to uart timer
{
    // Configure Timer 1.
    // PR1 and TCKPS are set to call interrupt every 500ms.
    // Period = PR1 * prescaler * Tcy = 58594 * 256 * 33.33ns = 500ms
    T1CON = 0;            // Clear Timer 1 configuration
    T1CONbits.TCKPS = 3;  // Set timer 1 prescaler (0=1:1, 1=1:8, 2=1:64, 3=1:256)
    PR1 = 50000;          // Set Timer 1 period (max value is 65535)
    _T1IP = 3;            // Set Timer 1 interrupt priority
    _T1IF = 0;            // Clear Timer 1 interrupt flag
    _T1IE = 1;            // Enable Timer 1 interrupt
    T1CONbits.TON = 1;    // Turn on Timer 1
}
void StartTimer2()//encoder timer f1 f2
{
    // Configure Timer 2.
    // PR2 and TCKPS are set to call interrupt every 500ms.
    // Period = PR2 * prescaler * Tcy = 58594 * 256 * 33.33ns = 500ms
    T2CON = 0;            // Clear Timer 2 configuration
    T2CONbits.TCKPS = 0;  // Set timer 2 prescaler (0=1:1, 1=1:8, 2=1:64, 3=1:256)
    PR2 = 80;          // Set Timer 2 period (max value is 65535)
    _T2IP = 0x5;            // Set Timer 2 interrupt priority
    _T2IF = 0;            // Clear Timer 2 interrupt flag
    _T2IE = 1;            // Enable Timer 2 interrupt
    T2CONbits.TON = 1;    // Turn on Timer 2
}
void StartTimer3()//count V
{
    // Configure Timer 3.
    // PR3 and TCKPS are set to call interrupt every 500ms.
    // Period = PR3 * prescaler * Tcy = 58594 * 256 * 33.33ns = 500ms
    T3CON = 0;            // Clear Timer 2 configuration
    T3CONbits.TCKPS = 3;  // Set timer 3 prescaler (0=1:1, 1=1:8, 2=1:64, 3=1:256)
    PR3 = 10000;          // Set Timer 3 period (max value is 65535)
    _T3IP = 0x4;            // Set Timer 3 interrupt priority
    _T3IF = 0;            // Clear Timer 3 interrupt flag
    _T3IE = 1;            // Enable Timer 3 interrupt
    T3CONbits.TON = 1;    // Turn on Timer 3
}