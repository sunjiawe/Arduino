const int DATA = 8;         //DATA引脚号

byte dat[5];

//发出开始传送数据请求，返回1成功，返回0失败
bool Init(){
  bool ret = true;
	pinMode(DATA, OUTPUT);
	digitalWrite(DATA,LOW);
	delay(30);
	digitalWrite(DATA, HIGH);
	delayMicroseconds(40);
	pinMode(DATA,INPUT);
  unsigned char i = 5000;
  while( i && digitalRead(DATA)==HIGH) i--;

  if(i == 0){
    ret = false;
    Serial.println("Iint failing!");
  }
  return ret;

}


byte readByte( ) {  // 每次读取 8 bits  ( one byte)
   byte data;
   for(int i=0; i<8; i++) {
    if(digitalRead(DATA) == LOW) {   // 一开始要 LOW 才表示要传过来
      while(digitalRead(DATA) == LOW); //等待 50us；
    // 现在已经变成 HIGH 了
      delayMicroseconds(30); //判断高电平持续时间，以判定资料是‘0’还是‘1’；
      if(digitalRead(DATA) == HIGH)  // 持续了 30 us 以上就是 1
        data |= (1<<(7-i)); //高位在前，低位元在后；
    //如果这时已经是 LOW, 表示这 bit 是 0, 不必塞入 data
    //..而且以下的 while 也会立即结束(因为 LOW), 准备接收下一个 bit
      while(digitalRead(DATA) == HIGH); // 等待下一bit的接收；
    //这时一定已经变成 LOW 了
  }// if
 }// for(
 return data;   // 收完 8 bit = one byte = one char
}


void readDate(){
  while( !Init() )  delay(500);
  delayMicroseconds(80);
  while( digitalRead(DATA)==LOW);
  delayMicroseconds(80);
	for(int j=0;j < 5;j++) dat[j] = readByte(); //接收温湿度资料，校验位元；
 	pinMode(DATA,OUTPUT);  // 改为 Output mode, 准备拉高HIGH
 	digitalWrite(DATA,HIGH);
}


void setup()
{
	pinMode(DATA,OUTPUT);
	Serial.begin(9600);
	
}


void loop()
{
	readDate();
	Serial.print("Current humdity = ");
  	Serial.print(dat[0], DEC); //显示湿度的整数部分；
  	Serial.print('.');
  	Serial.print(dat[1],DEC); //显示湿度的小数位；(其实是 0)
  	Serial.println(" %");  // 注意有空格要用 " %"  不可用 ' %'
  	Serial.print("Current temperature = ");
  	Serial.print(dat[2], DEC); //显示温度的整数部分；
  	Serial.print('.');
  	Serial.print(dat[3],DEC); //显示温度的小数位；(其实是 0)
 	 Serial.println(" C");
  	delay(1985);
}
