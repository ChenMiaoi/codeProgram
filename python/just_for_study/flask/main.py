from flask import Flask, jsonify, url_for, request, redirect
import config

# 创建一个对象，传入的__name__是一种固定语法，在后期出错之后，方便flask自动检查到错误
app = Flask(__name__)

# config用于设置各种参数信息
# app.config['JSON_AS_ASCII'] = False

# 为了后期维护的便捷性，一般来说，我们都会创建一个config.py用于配置各种配置项，然后使用app.config.from_object(config)
# 来直接将所有的配置信息填入
app.config.from_object(config)

# 设置访问的url，此时是设置为根路径
@app.route('/')

# 与上面的路由进行绑定，此时将返回的内容作为响应正文发送
def index():
    return {"username" : "你好"}

books = [
    {"id" : 1, "name" : "三国演义"},
    {"id" : 2, "name" : "红楼梦"},
    {"id" : 3, "name" : "西游记"},
    {"id" : 4, "name" : "水浒传"}
]

@app.route("/book/list")
def book_list():
    for book in books:
        book["url"] = url_for("book_detail", book_id = book["id"])
        # url_for类似一种回调机制，第一个参数传入callable function, 后面的则是对应的参数列表，返回的是填入后的路由
    return jsonify(books) # 在视频中必须显式转化为json,但是实际测试中，可以直接return books(或许是隐式转化？)

# 当我们想要在url中传参时，就使用<dataType:var>，能够自动的获取到var,传入绑定的函数
#! 这不是传参，更加接近于跳转目录？ --> "GET /book/1 HTTP/1.1" 500
#! 差不多是不定参数作为一个url
@app.route("/book/detail/<int:book_id>", methods = ["GET"]) #! 特别注意，此处的<dataType:var>之间不允许出现空格
# methods方式是规定可以使用哪一种请求方式
def book_detail(book_id):
    for book in books:
        if book_id == book["id"]:
            print(book)
            return "[INFO] success"
    return "[WARNING] fail"

@app.route("/profile")
def profile():
    # url参数的传递
    user_id = request.args.get("id")
    if user_id:
        return "用户个人中心"
    else:
        return redirect(url_for("index")) # redirect,url的重定向， 301代表永久性重定向，302代表暂时性重定向+

if __name__ == "__main__":
    app.run(debug = True) # 简单的运行, 建议在编写的过程中开启DEBUG模式，这样能够实时更改