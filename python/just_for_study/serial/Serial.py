class MySerial:
    verbose=False
    def __init__(self,serial_hard=True) -> None:
        self.serial=0
        self.serial_hard=serial_hard # 严格模式是否开启，默认是True
        self.get_series()
          
    def get_series(self):
        import serial.tools.list_ports
        port_list = [i.device for i in list(serial.tools.list_ports.comports()) if '蓝牙' not in i.description]
        # serial.tools.list_ports.comports() 获取计算机中所特有的port口信息，会自动识别再哪一种系统上
        try:
            assert len(port_list)>0
            self.serial = serialmain.Serial(port_list[-1], 115200, timeout=0.5)
            print(serial)
            return 1
        except:
            if self.serial_hard:
                print("串口异常，严格模式，正在退出")
                exit(0)
            serial =0
            if self.verbose:
                if len(port_list)>0:
                    print(port_list[-1].device+"串口打开失败")
                else:
                    print("没有串口")
            return 0
    def pre_dael_before_sent(self,msg_type,number_list):
        if msg_type==400 or msg_type==401:
            number_list[0]=(number_list[0]+50.625/2)*100
            number_list[1]=(number_list[1]+90/2)*100
            number_list[2]=number_list[2]*100
        return number_list
    def sent(self,msg_type,number_list):
        try:
            if not self.serial:
                if not (self.get_series()):
                    if self.verbose:
                        print("没有串口，写入失败")
                    return 0
            number_list=self.pre_dael_before_sent(msg_type,number_list)
            msg_sent=int(msg_type).to_bytes(4, byteorder='little')
            for i in number_list:
                msg_sent+=int(i).to_bytes(4, byteorder='little')
            self.serial.write(msg_sent)
        except:
            print("串口发送错误")
        return 1
    def receive(self):
        if not self.serial:
            if not (self.get_series()) and self.verbose:
                print("没有串口，读取失败")
                return 0
        try:
            msg_receive_org=self.serial.read_all()
            if not msg_receive_org: 
                return 0
            msg_receive=[]
            for i in range(0,int(len(msg_receive_org)/4),1):
                msg_receive.append(int.from_bytes(msg_receive_org[i*4:i*4+4], 'little'))
            return msg_receive
        except:
            if self.serial_hard:
                print("串口异常，严格模式，正在退出")
                exit(0)
            if self.verbose:
                print("串口信息读取失败")
            return 0