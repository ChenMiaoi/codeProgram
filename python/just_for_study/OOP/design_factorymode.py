
# ! 设计模式 -- 工厂模式
# ? 实现了创建者和调用者的分离
class CarFactory :
    def create_car(self, brand) :
        if brand == "奔驰" :
            return Benz()
        elif brand == "宝马" :
            return BMW()
        elif brand == "比亚迪" :
            return BYD()
        else :
            return "ERROR"

class Benz :
    def create(self) :
        print("奔驰")

class BMW :
    def create(self) :
        print("宝马")

class BYD :
    def create(self) :
        print("比亚迪")

factory = CarFactory()
c1 = factory.create_car("奔驰")
c1.create()
c2 = factory.create_car("宝马")
c2.create()
c3 = factory.create_car("比亚迪")
c3.create()
c4 = factory.create_car("大众")
