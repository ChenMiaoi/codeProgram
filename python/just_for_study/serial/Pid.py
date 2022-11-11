import sys
import os

def errno(file: str, line: int, errno: int = 1) -> None:
    print("FILE: {0}:\nline: {1}\n参数传递过少！".format(file, line))
    exit(errno)

class PidDef:
    def __init__(
            self,
            mode: bool = False,
            PID: list[float] = [],
            max_out: float = 0.0,
            max_iout: float = 0.0
    ) -> None:
        try:
            assert len(PID) == 3
            self.mode = mode
            self.Kp = PID[0]
            self.Ki = PID[1]
            self.Kd = PID[2]

            self.max_out = max_out
            self.max_iout = max_iout

            self.set = 0.0
            self.fdb = 0.0

            self.out = 0.0
            self.p_out = 0.0
            self.i_out = 0.0
            self.d_out = 0.0
            self.d_buf = [0.0, 0.0, 0.0]
            self.errno = [0.0, 0.0, 0.0]
        except:
            if len(PID) != 3:
                errno(__file__, sys._getframe().f_lineno, 1)

class GimbalPidDef:
    def __init__(
            self,
            PID: list[float] = [],
            max_out: float = 0.0,
            max_iout: float = 0.0
    ) -> None:
        try:
            assert len(PID) == 3
            self.Kp = PID[0]
            self.Ki = PID[1]
            self.Kd = PID[2]

            self.set = 0.0
            self.get = 0.0
            self.errno = 0.0

            self.out = 0.0
            self.max_out = max_out
            self.max_iout = max_iout

            self.p_out = 0.0
            self.i_out = 0.0
            self.d_out = 0.0
        except:
            if len(PID) != 3:
                errno(__file__, sys._getframe().f_lineno, 2)

class Pid:
    def __init__(self) -> None:
        self.pid_def_t = PidDef(False, [10, 23, 34])
        self.gimbal_pid_t = GimbalPidDef([4, 5, 6])
        self.hello()

    def __LimitMax(self, input: float, max: float):
        if input > max:
            return max
        elif input < -max:
            return -max

    def PidCalculate(self, ref: float, set: float) -> float:
        self.pid_def_t.errno[2] = self.pid_def_t.errno[1];
        self.pid_def_t.errno[1] = self.pid_def_t.errno[0];
        self.pid_def_t.set = set
        self.pid_def_t.fdb = ref
        self.pid_def_t.errno[0] = set - ref

        if self.pid_def_t.mode: # 如果为True，则是位置式
            self.pid_def_t.p_out = self.pid_def_t.Kp * self.pid_def_t.errno[0]
            self.pid_def_t.i_out = self.pid_def_t.Ki * self.pid_def_t.errno[0]

            self.pid_def_t.d_buf[2] = self.pid_def_t.d_buf[1]
            self.pid_def_t.d_buf[1] = self.pid_def_t.d_buf[0]
            self.pid_def_t.d_buf[0] = self.pid_def_t.errno[0] - self.pid_def_t.errno[1]
            self.pid_def_t.d_out = self.pid_def_t.Kd * self.pid_def_t.d_buf[0]
            self.pid_def_t.i_out = self.__LimitMax(
                self.pid_def_t.i_out, self.pid_def_t.max_iout
            )
            self.pid_def_t.out = self.pid_def_t.p_out + self.pid_def_t.i_out + self.pid_def_t.d_out
            self.pid_def_t.out = self.__LimitMax(
                self.pid_def_t.out, self.pid_def_t.max_out
            )
        else: # 默认为False，对应增量式
            self.pid_def_t.p_out = self.pid_def_t.Kp * (self.pid_def_t.errno[0] - self.pid_def_t.errno[1])
            self.pid_def_t.i_out = self.pid_def_t.Ki * self.pid_def_t.errno[0]
            self.pid_def_t.d_buf[2] = self.pid_def_t.d_buf[1]
            self.pid_def_t.d_buf[1] = self.pid_def_t.d_buf[0]
            self.pid_def_t.d_buf[0] = self.pid_def_t.errno[0] - 2.0 * self.pid_def_t.errno[1] + self.pid_def_t.errno[2]
            self.pid_def_t.d_out = self.pid_def_t.Kd * self.pid_def_t.d_buf[0]
            self.pid_def_t.out += (self.pid_def_t.p_out + self.pid_def_t.i_out + self.pid_def_t.d_out)
            self.pid_def_t.out = self.__LimitMax(
                self.pid_def_t.out, self.pid_def_t.max_out
            )
        return self.pid_def_t.out

    def PidClear(self) -> None:
        self.pid_def_t.errno[0:] = [0.0] * (len(self.pid_def_t.errno))
        self.pid_def_t.d_buf[0:] = [0.0] * (len(self.pid_def_t.d_buf))
        self.pid_def_t.out = self.pid_def_t.p_out = self.pid_def_t.i_out = self.pid_def_t.d_out = 0.0
        self.pid_def_t.fdb = self.pid_def_t.set = 0.0

    def __AbsLimit(self, input: float, limit: float) -> float:
        if input > limit:
            return limit
        elif input < -limit:
            return -limit

    def GCPCalculate(self, get: float, set: float, error_delta: float):
        '''
        Name: GCP: Gimbal Cascade Pid
        Args:
            get:
            set:
            error_delta:
        Returns:
        '''
        err = set - get
        self.gimbal_pid_t.get = get
        self.gimbal_pid_t.set = set
        # TODO 循环限幅 -> 没啥用
        # self.gimbal_pid_t.errno = __RadFormat(err)
        self.gimbal_pid_t.errno = err
        self.gimbal_pid_t.p_out = self.gimbal_pid_t.Kp * self.gimbal_pid_t.errno
        self.gimbal_pid_t.i_out += self.gimbal_pid_t.Ki * self.gimbal_pid_t.errno
        self.gimbal_pid_t.d_out = self.gimbal_pid_t.Kd * error_delta
        # TODO 绝对值限制
        self.gimbal_pid_t.i_out = self.__AbsLimit(self.gimbal_pid_t.i_out, self.gimbal_pid_t.max_iout)
        self.gimbal_pid_t.out = self.gimbal_pid_t.p_out + self.gimbal_pid_t.i_out + self.gimbal_pid_t.d_out
        self.gimbal_pid_t.i_out = self.__AbsLimit(self.gimbal_pid_t.out, self.gimbal_pid_t.max_out)
        return self.gimbal_pid_t.out

    def hello(self):
        print(self.pid_def_t.Kp)
        print(self.gimbal_pid_t.Kp)
        print(self.PidCalculate(50, 60))
        print(self.GCPCalculate(10, 20, 5))

if __name__ == "__main__":
    pid = Pid()