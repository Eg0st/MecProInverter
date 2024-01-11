#include "foc_pwm.hpp"

using namespace FOC;

/**************************************************************************************************************************************
* Bereich für die Field Oriented Controll
**************************************************************************************************************************************/
void FOC::init(BLDCDriver6PWM** driver,BLDCMotor** motor)
{
    *driver = new BLDCDriver6PWM(HINW, LINW, HINV, LINV, HINU, LINU);
    *motor = new BLDCMotor(POLE_PAIR);
    pinMode(LINW,OUTPUT);
    pinMode(HINW,OUTPUT);
    pinMode(LINV,OUTPUT);
    pinMode(HINV,OUTPUT);
    pinMode(HINU,OUTPUT);
    pinMode(HINU,OUTPUT);
    digitalWrite(LINW, LOW);
    digitalWrite(HINW, LOW);
    digitalWrite(LINV, LOW);
    digitalWrite(HINV, LOW);
    digitalWrite(HINU, LOW);
    digitalWrite(HINU, LOW);

    // Driver-Part
    (*driver)->pwm_frequency = PWM_FREQUENCY;
    (*driver)->dead_zone = DEAD_ZONE;
    (*driver)->voltage_power_supply = VOLTAGE_POWER_SUPPLY;
    (*driver)->voltage_limit = D_VOLTAGE_LIMIT;
    (*driver)->init();
    //driver->enable(); //waere glaube ich ohne motor

    // Motor-Part
    (*motor)->linkDriver(*driver);
    (*motor)->voltage_limit = M_VOLTAGE_LIMIT;   // [V]
    (*motor)->velocity_limit = (float) 2*PI*VELOCITY_LIMIT; // [rad/s] cca 50rpm
    (*motor)->controller = MotionControlType::velocity_openloop;   // open loop control config
    (*motor)->init();
    _delay(1000);
}

void FOC::PWM_Generation(BLDCMotor* motor, float freq)
{
    static float new_target_value=2*PI*freq;
    motor->move(new_target_value);
}

/**************************************************************************************************************************************
* Bereich für die Timing Function

Anmerkungen: 
* static Timing*instance: Globaler Zeiger auf die Timing Instanz, da so die ISR aufgerufen werden kann
* nur eine Timing Klasse erstellen
**************************************************************************************************************************************/
    static Timing*instance; //Globaler Zeiger auf die Timing-Instanz, damit die ISR aufrufen kann
    Timing::Timing(): flag(false)
    {
        instance=this;

       /***************************************************************
        Argumente für die spätere Callback Funktion:
        * callback: Interrupt Funktion, die später aufgerufen wird
        * arg: Argumente keine Übergeben
        * name: myTimer Name
        ***************************************************************/
        const esp_timer_create_args_t timerArgs = {
            .callback = &Timing::timerCallback,
            .arg=NULL,
            .name="myTimer"
        };
        /***************************************************************
        Initialisiert eine neue Instanz für den esp_timer
        ***************************************************************/
        esp_timer_create(&timerArgs,&myTimer);
    }
    Timing::~Timing()
    {
        esp_timer_delete(myTimer);
    }

    /***************************************************************
    Periodendauer: Übergabe der Frequenz in us
    ***************************************************************/
    void Timing::start(uint64_t timer_period_us)
    {
        esp_timer_start_periodic(myTimer,timer_period_us);
    }
    void Timing::stop()
    {
        esp_timer_stop(myTimer);
    }

    /*
    Rückgabefunktion
    */
    void Timing::timerCallback(void* arg) 
    {
        instance->flag=true;
    }



