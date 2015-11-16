/*
伺服电机旋转程序：用来测试一个舵机的极限转角
*/

const int servo = 4;  //定义引脚

/*
通过慢慢修改这两个参数，测试出舵机的上下极限转角，每次的改变值不要超过100us
*/
const int lowlimit = 1000;    //单位：us   1ms    
const int highlimit = 2000;		//2ms


void setup()
{
	
}


void loop()
{
     for(int hightime = lowlimit;hightime <= highlimit;hightime++){
     	digitalWrite(servo, HIGH);
     	delayMicroseconds(hightime);
     	digitalWrite(servo, LOW);
     	delay(20-hightime/1000);

     }	
}